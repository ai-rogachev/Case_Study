// dllmain.cpp : Defines the entry point for the DLL application.
#include <cassert>
#include <Windows.h>
#include <stdio.h>

#include <string>
#include <filesystem>
#include <fstream>

#define HOOKLIBAPI __declspec(dllexport)
#include "HookLib.h"

// Instruct the compiler to put the g_hhook data variable in 
// its own data section called Shared. We then instruct the 
// linker that we want to share the data in this section 
// with all instances of this application.
#pragma data_seg("Shared")
HHOOK g_hhook = NULL;
DWORD g_dwThreadId = 0;
#pragma data_seg()

// Instruct the linker to make the Shared section
// readable, writable, and shared.
#pragma comment(linker, "/section:Shared,rws")

///////////////////////////////////////////////////////////////////////////////

// Nonshared variables
HINSTANCE g_hinstDll = NULL;

//////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK hookFunction(int nCode, WPARAM wParam, LPARAM lParam) {
    static const std::string fName = "WindowsHook.log";
    auto path = std::filesystem::temp_directory_path();
    std::string strPath = path.string();

    path += fName;

    std::ofstream log(path, std::ios_base::app);
    if (log.is_open())
    {
        log << "Keyboard event detected - " << wParam << std::endl;
        log.close();
    }
    return CallNextHookEx(g_hhook, nCode, wParam, lParam);  //Optional;
}

///////////////////////////////////////////////////////////////////////////////

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // DLL is attaching to the address space of the current process.
        g_hinstDll = hModule;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        SetHook(0);
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

BOOL WINAPI SetHook(DWORD dwThreadId) 
{
    BOOL fOK = FALSE;
    if (dwThreadId != 0) {
        g_dwThreadId = GetCurrentThreadId();
        g_hhook = SetWindowsHookEx(WH_KEYBOARD, hookFunction, g_hinstDll, dwThreadId);
        fOK = (g_hhook != NULL);
        if (fOK) {
            fOK = PostThreadMessage(dwThreadId, WM_NULL, 0, 0);
        }
    }
    else {
        assert(g_hhook != NULL);
        fOK = UnhookWindowsHookEx(g_hhook);
        g_hhook = NULL;
        PostThreadMessage(g_dwThreadId, WM_NULL, 0, 0);
    }

    return fOK;
}