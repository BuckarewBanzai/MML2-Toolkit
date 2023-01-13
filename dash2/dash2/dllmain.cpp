// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "windows.h"
#include "cstdio"
#include "iostream"


// Take the place of ole32 and forward its function calls to the real ole32
#pragma comment(linker,"/export:CoInitialize=ole32.CoInitialize,@927")


DWORD WINAPI dashMain(HINSTANCE hModule)
{
    AllocConsole();

    FILE* fdum;
    freopen_s(&fdum, "conin$", "r", stdin);
    freopen_s(&fdum, "conout$", "w", stdout);
    freopen_s(&fdum, "conout$", "w", stderr);

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"dash2.dll");

    std::cout << "HyperShell v0.1\n\n";
    std::cout << "DLL Base: ";
    std::cout << moduleBase;
    std::cout << "\n";
    std::cout << "Process Base: ";
    std::cout << hModule;

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
        //return InitInstance(hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}