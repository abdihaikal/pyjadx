import os
import re
import sys
import platform
import subprocess
import glob
import setuptools
import pathlib

from setuptools import setup, Extension
from setuptools import Extension
from setuptools.command.build_ext import build_ext, copy_file

from distutils.version import LooseVersion

from distutils import log

MIN_SETUPTOOLS_VERSION = "31.0.0"
assert (LooseVersion(setuptools.__version__) >= LooseVersion(MIN_SETUPTOOLS_VERSION)), "pyJadx requires a setuptools version '{}' or higher (pip install setuptools --upgrade)".format(MIN_SETUPTOOLS_VERSION)

CURRENT_DIR = pathlib.Path(__file__).parent

class Module(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(os.path.join(CURRENT_DIR))


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        for ext in self.extensions:
            self.build_extension(ext)
        self.copy_extensions_to_source()


    def build_extension(self, ext):
        jobs = self.parallel if self.parallel else 1

        fullname = self.get_ext_fullname(ext.name)
        filename = self.get_ext_filename(fullname)

        source_dir                     = ext.sourcedir
        build_temp                     = self.build_temp
        extdir                         = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_library_output_directory = os.path.abspath(os.path.dirname(build_temp))
        cmake_args = [
            '-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}'.format(cmake_library_output_directory),
            '-DPYTHON_EXECUTABLE={}'.format(sys.executable),
        ]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), cmake_library_output_directory)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            else:
                cmake_args += ['-A', 'x86']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]

        env = os.environ.copy()

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)

        log.info("Using {} jobs".format(jobs))
        subprocess.check_call(['make', '-j', str(jobs), 'pyjadx'], cwd=self.build_temp)

        pyjadx_dst  = os.path.join(self.build_lib, self.get_ext_filename(self.get_ext_fullname(ext.name)))

        libsuffix = pyjadx_dst.split(".")[-1]

        pyjadx_path = os.path.join(cmake_library_output_directory, "pyjadx.{}".format(libsuffix))
        if not os.path.exists(self.build_lib):
            os.makedirs(self.build_lib)

        copy_file(
                pyjadx_path, pyjadx_dst, verbose=self.verbose,
                dry_run=self.dry_run)



# From setuptools-git-version
command       = 'git describe --tags --long --dirty'
is_tagged_cmd = 'git tag --list --points-at=HEAD'
fmt           = '{tag}.dev2'
fmt_tagged    = '{tag}'

def format_version(version, fmt=fmt):
    parts = version.split('-')
    assert len(parts) in (3, 4)
    dirty = len(parts) == 4
    tag, count, sha = parts[:3]
    if count == '0' and not dirty:
        return tag
    return fmt.format(tag=tag, gitsha=sha.lstrip('g'))


def get_git_version(is_tagged):
    git_version = subprocess.check_output(command.split()).decode('utf-8').strip()
    if is_tagged:
        return format_version(version=git_version, fmt=fmt_tagged)
    return format_version(version=git_version, fmt=fmt)

def check_if_tagged():
    output = subprocess.check_output(is_tagged_cmd.split()).decode('utf-8').strip()
    return output != ""

def get_pkg_info_version(pkg_info_file):
    dist_info = Distribution.from_filename(CURRENT_DIR / "pyjadx.egg-info")
    pkg = get_distribution('pyjadx')
    return pkg.version


def get_version():
    version   = "0.0.0"
    pkg_info  = CURRENT_DIR / "pyjadx.egg-info" / "PKG-INFO"
    git_dir   = CURRENT_DIR / ".git"
    if git_dir.is_dir():
        is_tagged = False
        try:
            is_tagged = check_if_tagged()
        except:
            is_tagged = False

        try:
            return get_git_version(is_tagged)
        except:
            pass

    if pkg_info.is_file():
        return get_pkg_info_version(pkg_info)



version = get_version()



setup(
    ext_modules=[Module('pyjadx')],
    cmdclass=dict(build_ext=CMakeBuild),
    version=version
)
