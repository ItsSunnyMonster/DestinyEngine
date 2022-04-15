import cmake_build
import sys
import os

def _main(argc, argv): 
    if argc != 2 and argc != 4:
        print("Usage: build.py <clean|build> [platform] [configuration]")
        return

    if argv[1] == "build":
        print("==== build.py: Making CMake files =========================")
        cmake_build.invoke()

    # Clean all binaries
    if argc == 2 and argv[1] == "clean":
        print("==== build.py: Cleaning... ================================")

        if not os.path.exists("cmake-linux-debug"):
            print("build.py: Nothing to clean for cmake-linux-debug.")
        else:
            os.system("cd cmake-linux-debug && make clean")

        if not os.path.exists("cmake-linux-release"):
            print("build.py: Nothing to clean for cmake-linux-release.")
        else:
            os.system("cd cmake-linux-release && make clean")

        if not os.path.exists("cmake-windows-debug"):
            print("build.py: Nothing to clean for cmake-windows-debug.")
        else:
            os.system("cd cmake-windows-debug && make clean")

        if not os.path.exists("cmake-windows-release"):
            print("build.py: Nothing to clean for cmake-windows-release.")
        else:
            os.system("cd cmake-windows-release && make clean")
        
        print("==== build.py: Cleaned. ===================================")
        return

    # Build all binaries
    if argc == 2 and argv[1] == "build":
        print("===== build.py: Building Linux Debug ======================")
        os.system("cd cmake-linux-debug && make")
        print("===== build.py: Building Linux Release ====================")
        os.system("cd cmake-linux-release && make")
        print("===== build.py: Building Windows Debug ====================")
        os.system("cd cmake-windows-debug && make")
        print("===== build.py: Building Windows Release ==================")
        os.system("cd cmake-windows-release && make")
        return

    # Clean specified binaries
    if argc == 4 and argv[1] == "clean":
        if argv[2] == "linux":
            if argv[3] == "debug":
                print("==== build.py: Cleaning Linux Debug ===================")
                os.system("cd cmake-linux-debug && make clean")
            elif argv[3] == "release":
                print("==== build.py: Cleaning Linux Release =================")
                os.system("cd cmake-linux-release && make clean")
            else:
                print("build.py: Invalid configuration: " + argv[3])
                return
        elif argv[2] == "windows":
            if argv[3] == "debug":
                print("==== build.py: Cleaning Windows Debug =================")
                os.system("cd cmake-windows-debug && make clean")
            elif argv[3] == "release":
                print("==== build.py: Cleaning Windows Release ===============")
                os.system("cd cmake-windows-release && make clean")
            else:
                print("build.py: Invalid configuration: " + argv[3])
                return
        else:
            print("build.py: Invalid platform: " + argv[2])
            return
        return

    # Build specified binaries
    if argc == 4 and argv[1] == "build":
        if argv[2] == "linux":
            if argv[3] == "debug":
                print("==== build.py: Building Linux Debug ===================")
                os.system("cd cmake-linux-debug && make")
            elif argv[3] == "release":
                print("==== build.py: Building Linux Release =================")
                os.system("cd cmake-linux-release && make")
            else:
                print("build.py: Invalid configuration: " + argv[3])
                return
        elif argv[2] == "windows":
            if argv[3] == "debug":
                print("==== build.py: Building Windows Debug =================")
                os.system("cd cmake-windows-debug && make")
            elif argv[3] == "release":
                print("==== build.py: Building Windows Release ===============")
                os.system("cd cmake-windows-release && make")
            else:
                print("build.py: Invalid configuration: " + argv[3])
                return
        else:
            print("build.py: Invalid platform: " + argv[2])
            return
        return

def invoke(argc, argv):
    _main(argc, argv)

if __name__ == "__main__":
    _main(len(sys.argv), sys.argv)