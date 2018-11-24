import pyjadx
import sys
import argparse
import pygments
import pathlib
from pygments.lexers     import get_lexer_by_name
from pygments.formatters import get_formatter_by_name

lexer     = get_lexer_by_name("java")
formatter = get_formatter_by_name("terminal")
jadx      = pyjadx.Jadx()

def pretty_print(apk, classes):
    apk_path = pathlib.Path(apk).resolve().absolute()
    decompiler = jadx.load(apk_path.as_posix())
    if classes:
        for cls in classes:
            try:
                cls_decompiled = decompiler.get_class(cls)
                hl = pygments.highlight(cls_decompiled.code, lexer, formatter)
                print(hl)
            except Exception as e:
                print(f"Error while dealing with '{cls}': '{e}'!", file=sys.stderr)
    else:
        for c in decompiler.classes:
            hl = pygments.highlight(c.code, lexer, formatter)
            print(hl)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Example of pyjadx associated with pygments")
    parser.add_argument("apk", help="Target apk")
    parser.add_argument("--classes", type=str, nargs='*', help="List of classes to decompile")

    args = parser.parse_args()
    pretty_print(args.apk, args.classes)



