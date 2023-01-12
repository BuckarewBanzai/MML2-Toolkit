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

def patch():
    f.seek(0x23083E, 0)
    f.write(str.encode("dash2.dll"))

def unpatch():
    f.seek(0x23083E, 0)
    f.write(str.encode("ole32.dll"))

with open(pe, "r+b") as f:
    f.seek(0x23083E, 0)
    dll = f.read(9)
    print(byte2ascii(dll))

    if patchCheck(dll):
        print("Game is already patched.")
    
    else:
        patch()
        f.seek(0x23083E, 0)
        dll = f.read(9)

        if patchCheck(dll):
            print("Game patched successfully!")

        if not patchCheck(dll):
            print("Patching failed. Please restore dash2.exe from a backup and try again.")
            print(byte2ascii(dll))