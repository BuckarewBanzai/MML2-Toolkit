import sys


#Convert bytes to ascii
def byte2ascii(hval):
    #wrapped this in a try catch because we can't always decode to ascii. Returns none type on failure.
    try:
        ascii_object = hval.decode("utf-8")

    except:
        ascii_object = None

    return ascii_object

#Convert bytes to integer
def byte2int(hval):
    int_object = int.from_bytes(hval, "little")

    return int_object

#Check if we are at the end of the file definitions
def dummyCheck(address, file):
    #Take our current address and set our cursor to that location in the file
    file.seek(address, 0)

    #Dummy header is 26 bytes (yes it's actually 32 bytes but this is all we need to check)
    header = file.read(12)

    if byte2ascii(header) == "dummy header":
        return True

    else:
        return False


#https://docs.dashgl.com/format/mml2/file-formats/dat-pc
#Header index padding always ends at 0x7FF
validTypes = { 0x00:"undefined",
               0x01:"undefined",
               0x02:"undefined",  
               0x03:"undefined", 
               0x04:"texture",
               0x05:"undefined",
               0x06:"undefined",
               0x07:"undefined",
               0x08:"undefined", 
               0x09:"undefined" }


def main(datFile):
    with open(datFile, "r+b") as f:
        workingAddress = 0x0
        fileCount = 0
        while True:
            #Verify we havent hit padding yet
            if not dummyCheck(workingAddress, f):
                f.seek(workingAddress, 0)
                print("File type: " + str(f.read(1)))

                f.seek(workingAddress + 0x4)
                print("File Size: " + str(byte2int(f.read(12))) + "\n")

                workingAddress = workingAddress + 0x10
                fileCount += 1

            else:
                print("End of file header. Found " + str(fileCount) + " files.")
                break

if __name__ == "__main__":
    if len(sys.argv) > 1:
        datFile = sys.argv[1]
    
    main(datFile)
    
