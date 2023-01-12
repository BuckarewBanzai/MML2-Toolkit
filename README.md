# MML2 Toolkit
 Framework for reversing and hacking MegaMan Legends 2 on pc!


## Requirements:
 - Python (Tested with 3.11)
 - Visual Studio 2019
 
## How does it work?
Every PE (portable executable) file has a dll import table. This table lists all of the dll requirments and function imports required for the program to work. We can rename a dll in this table to force the executable to load our own dll (dash-patcher.py). In our hack dll we then have to "forward" the functions from the original dll in to the game. After that we can write code to manipulate our games memory as we are now running in the same process. 

## Building dash2.dll
Open the dash2.sln project in Visual Studio 2019. Click Build, Build Solution. This will generate dash2.dll at ```/dash2/Debug/dash2.dll```. Copy this dll and place it in the same folder as your dash2.exe

## Patching dash2.exe
Copy dash-patcher.py to the same folder as dash2.exe. MAKE A BACKUP OF dash2.exe!!! I have taken several steps to prevent this from being corrupted on patching but accidents happen. If you run into issues during patching start over with a clean dash2.exe and try again. Successful output will look like this:

```
python dash-patcher.py

ole32.dll
Game patched successfully!
```


## Verify
If everything works when you launch dash2.exe a console will appear that says "HyperShell v0.1". You can now execute code in the games process. :) 
