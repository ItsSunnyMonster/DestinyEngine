import sys
import build
import os

def _main(argc, argv):
    if argc != 3:
        print("Usage: run.py <platform> <configuration>")
        return
    
    print("===== run.py: Building ========================")
    build.invoke(4, [argv[0], "build", argv[1], argv[2]])
    print("===== run.py: Running =========================")
    if argv[1] == "linux":
        os.system(f"cd cmake-linux-{argv[2]} && bin/Sandbox")
    elif argv[1] == "windows":
        os.system(f"cd cmake-windows-{argv[2]} && WINEDEBUG=-all wine bin/Sandbox.exe")

if __name__ == "__main__":
    _main(len(sys.argv), sys.argv)