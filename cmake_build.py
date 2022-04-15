import os
import sys

def invoke():
    _main(2, [sys.argv[0], "build"])

def _main(argc, argv):
    if argc > 1 and argv[1] == "clean":
        print("==== cmake_build.py: Cleaning... =============")
        os.system("rm -rf cmake-linux-debug")
        os.system("rm -rf cmake-linux-release")
        os.system("rm -rf cmake-windows-debug")
        os.system("rm -rf cmake-windows-release")
        print("==== cmake_build.py: Cleaned. ================")
        return

    print("==== cmake_build.py: Building Linux Debug ==============")
    os.system("cmake -DCMAKE_BUILD_TYPE=Debug -B cmake-linux-debug")
    print("==== cmake_build.py: Building Linux Release ============")
    os.system("cmake -DCMAKE_BUILD_TYPE=Release -B cmake-linux-release")
    print("==== cmake_build.py: Building Windows Debug ============")
    os.system("cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./mingw-w64.cmake -B cmake-windows-debug")
    print("==== cmake_build.py: Building Windows Release ==========")
    os.system("cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./mingw-w64.cmake -B cmake-windows-release")

if __name__ == "__main__":
    _main(len(sys.argv), sys.argv)