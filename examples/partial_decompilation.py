import pyjadx

import sys
import argparse
import pygments
import pathlib

CWD = pathlib.Path(".").resolve().absolute()

try:
    import pyAMI
except ImportError as e:
    print("This script requires pyAMI (https://github.com/romainthomas/AMI)")
    sys.exit(1)

jadx = pyjadx.Jadx()

def resolve_worklist(japp, wl, outputdir):
    jclasses = japp.classes
    for jcls in jclasses:
        fname = jcls.fullname
        if any(c == fname for c in wl):
            wl.remove(fname)
            path_list = fname.split(".")
            cwd = outputdir
            for subdir in path_list[:-1]:
                cwd /= subdir
                cwd.mkdir(exist_ok=True)
            java_output = cwd / f'{path_list[-1]}.java'
            jcls.save(java_output.as_posix())
    if len(wl) > 0:
        print("The following classes are not found (packed ?):")
        for rem in wl:
            print(rem)

def decompile(apk_path, outputdir, main_pkg=None):
    manifest = pyAMI.Manifest.open(apk_path)
    if manifest is None:
        print(f"Can't open manifest for '{apk_path}'!", file=sys.stderr)
        return 1

    japp = jadx.load(apk_path)
    if japp is None:
        print(f"Can't decompile for '{apk_path}'!", file=sys.stderr)
        return 1


    decompile_worklist = set()

    # 1. Add '<application>'
    mapplication = manifest.application
    decompile_worklist.add(mapplication.cls)

    # 2. Add '<activities>'
    decompile_worklist |= {c.cls for c in manifest.activities}

    # 3. Add '<service>'
    decompile_worklist |= {c.cls for c in manifest.services}

    # 4. Add '<receivers>'
    decompile_worklist |= {c.cls for c in manifest.receivers}

    if main_pkg and japp.has_package(manifest.package_name):
        mpkg = japp.get_package(manifest.package_name)
        decompile_worklist |= {c.fullname for c in mpkg.classes}

    decompile_worklist_normalize = {manifest.package_name + f if f[0] == "." else f for f in decompile_worklist}

    print(f"Number of classes to decompile: {len(decompile_worklist_normalize)}")
    resolve_worklist(japp, decompile_worklist_normalize, outputdir)


def main():
    parser = argparse.ArgumentParser(description="Decompile classes based on Manifest")
    parser.add_argument("-i", "--include-package",
            action="store_true",
            help="Decompile the main package of the application",
            default=False)
    parser.add_argument("-o", "--output", help=f"output directory (default: '{CWD}')", default=CWD)

    parser.add_argument("apk", help="Target apk")

    args = parser.parse_args()
    decompile(args.apk, args.output, main_pkg=args.include_package)

if __name__ == "__main__":
    sys.exit(main())

