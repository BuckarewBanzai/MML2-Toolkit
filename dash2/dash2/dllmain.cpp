// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <TlHelp32.h>


// Take the place of ole32 and forward its function calls to the real ole32
#pragma comment(linker,"/export:CoInitialize=ole32.CoInitialize,@927")


DWORD GetModuleBase(const wchar_t* ModuleName, DWORD ProcessId) {
    // This structure contains lots of goodies about a module
    MODULEENTRY32 ModuleEntry = { 0 };
    // Grab a snapshot of all the modules in the specified process
    HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

    if (!SnapShot)
        return NULL;

    // You have to initialize the size, otherwise it will not work
    ModuleEntry.dwSize = sizeof(ModuleEntry);

    // Get the first module in the process
    if (!Module32First(SnapShot, &ModuleEntry))
        return NULL;

    do {
        // Check if the module name matches the one we're looking for
        if (!wcscmp(ModuleEntry.szModule, ModuleName)) {
            // If it does, close the snapshot handle and return the base address
            CloseHandle(SnapShot);
            return (DWORD)ModuleEntry.modBaseAddr;
        }
        // Grab the next module in the snapshot
    } while (Module32Next(SnapShot, &ModuleEntry));

    // We couldn't find the specified module, so return NULL
    CloseHandle(SnapShot);
    return NULL;
}


struct
{
    // Title constructor
    const char*     title = "DASH2 v0.1";
    uintptr_t       modBase;
    DWORD           procBase;
    DWORD           procId;
    int             zenny;
    char            graphicsCard[32];

} DASH2;


DWORD WINAPI dashMain(HINSTANCE hModule)
{
    AllocConsole();

    FILE* fdum;
    freopen_s(&fdum, "conin$", "r", stdin);
    freopen_s(&fdum, "conout$", "w", stdout);
    freopen_s(&fdum, "conout$", "w", stderr);

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"dash2.dll");
    DASH2.procId = GetCurrentProcessId();
    HANDLE dashProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, DASH2.procId);
    DASH2.procBase = GetModuleBase(L"dash2.exe", DASH2.procId);

    DWORD graphicsCardAddress = 0x0092726C;
    DWORD zennyAddress        = 0x00A6D1A8;
 
    Sleep(1000);

    ReadProcessMemory(dashProcessHandle, (LPVOID)graphicsCardAddress, &DASH2.graphicsCard, sizeof(DASH2.graphicsCard), 0);

    std::cout << DASH2.title;
    std::cout << "\nGraphics Card: " << DASH2.graphicsCard;

    while (true) {
        ReadProcessMemory(dashProcessHandle, (LPVOID)zennyAddress, &DASH2.zenny, sizeof(DASH2.zenny), 0);
        std::cout << "\nZenny: " << DASH2.zenny;

        Sleep(10000);
    }

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)dashMain, hModule, 0, nullptr));

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}