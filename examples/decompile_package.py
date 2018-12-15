import pyjadx
import sys
import argparse
import pygments
import pathlib

jadx = pyjadx.Jadx()

def decompile_pkg(apk, package):
    apk_path   = pathlib.Path(apk).resolve().absolute()
    decompiler = jadx.load(apk_path.as_posix())
    for pkg in decompiler.packages:
        if pkg.fullname != package:
            continue
        pkg.save(pathlib.Path("."))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Example of pyjadx associated with pygments")
    parser.add_argument("apk", help="Target apk")
    parser.add_argument("package", help="Package name")

    args = parser.parse_args()
    decompile_pkg(args.apk, args.package)



