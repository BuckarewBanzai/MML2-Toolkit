import sys

def printHelp():
    print("Usage: dash-patcher.py [OPTIONS]\n")
    print("Options: ")
    print("patch        Patch dash2.dll into dash2.exe")
    print("unpatch      Restore dash2.exe back to default")
    print("-h           Print help menu")

#mml2 exe we want to patch
pe = 'dash2.exe'

def byte2ascii(hval):
    ascii_object = hval.decode("utf-8")

    return ascii_object

def byte2int(hval):
    int_object = int.from_bytes(hval, "little")

    return int_object

def patchCheck(dll):
    dll = byte2ascii(dll)
    if dll == "dash2.dll":
        return True

    elif dll == "ole32.dll":
        return False

def patchDll(f):
    f.seek(0x23083E, 0)
    f.write(str.encode("dash2.dll"))

def unpatchDll(f):
    f.seek(0x23083E, 0)
    f.write(str.encode("ole32.dll"))

def patch():
    with open(pe, "r+b") as f:
        f.seek(0x23083E, 0)
        dll = f.read(9)

        if patchCheck(dll):
            print("Game is already patched.")
            return
    
        else:
            patchDll(f)
            f.seek(0x23083E, 0)
            dll = f.read(9)

            if patchCheck(dll):
                print("Game patched successfully!")

            if not patchCheck(dll):
                print("Patching failed. Please restore dash2.exe from a backup and try again.")


def unpatch():
    with open(pe, "r+b") as f:
        f.seek(0x23083E, 0)
        dll = f.read(9)

        if not patchCheck(dll):
            print("No patch detetcted.")
            return
    
        else:
            unpatchDll(f)
            f.seek(0x23083E, 0)
            dll = f.read(9)

            if patchCheck(dll):
                print("Patching revert failed. Please restore dash2.exe from a backup")

            if not patchCheck(dll):
                print("Patch reverted successfully!")


if __name__ == "__main__":

    if len(sys.argv) > 1:
        patchMode = sys.argv[1]
    else:
        printHelp()
        exit()

    if patchMode == "patch":
        patch()
    elif patchMode == "unpatch":
        unpatch()
    else:
        printHelp()