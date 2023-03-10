# MML2 Toolkit
 Framework for reversing and hacking MegaMan Legends 2 on pc!


## Requirements:
 - Python (Tested with 3.11)
 - Visual Studio 2019
 
## How does it work?
Every PE (portable executable) file has a dll import table. This table lists all of the dll requirements and function imports required for the program to work. We can rename a dll in this table to force the executable to load our own dll (dash-patcher.py). In our hack dll we then have to "forward" the functions from the original dll in to the game. After that we can write code to manipulate our games memory as we are now running in the same process. 

## Building dash2.dll
Open the dash2.sln project in Visual Studio 2019. Click Build, Build Solution. This will generate dash2.dll at ```/dash2/Debug/dash2.dll```. Copy this dll and place it in the same folder as your dash2.exe

## Patching dash2.exe
Copy dash-patcher.py to the same folder as dash2.exe. MAKE A BACKUP OF dash2.exe!!! I have taken several steps to prevent this from being corrupted on patching but accidents happen. If you run into issues during patching start over with a clean dash2.exe and try again. Successful output will look like this:

```
python dash-patcher.py patch

Game patched successfully!
```

If everything works when you launch dash2.exe a console will appear that says "DASH2 v0." with data about your graphics card and zenny count. You can now execute code in the games process. You can restore dash2.exe back to default by running:

```
python dash-patcher.py unpatch
```


## Dat Walker
The dat-walker script will scan a mml2 ".dat" file index header and output files contained inside and their length. This script is based on the awesome work of Kion found here: https://docs.dashgl.com/format/mml2/file-formats/dat-pc. It appears there are 9 different file types (I have found so far). Eventually I would like this script to extract these files and save them on disk. 

## Requirements:
 - Python (Tested with 3.11)

Example usage of the dat-walker script:
 
```
python dat-walker.py TITLE.dat

File type: b'\x01'
File Size: 21112

File type: b'\x04'
File Size: 8590042648

File type: b'\x04'
File Size: 8589967480

File type: b'\x04'
File Size: 8589967448

File type: b'\x04'
File Size: 8589967576

File type: b'\x04'
File Size: 33048

File type: b'\t'
File Size: 4295840958

End of file header. Found 7 files.
```
