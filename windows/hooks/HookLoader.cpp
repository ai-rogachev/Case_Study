#include <iostream>
#include <Windows.h>
#include <cassert>

#include <filesystem>
#include <string>

#include "lib\HookLib.h"

int main()
{
	HWND hWndNotepad, hEditWnd;
	hWndNotepad = FindWindowA("Notepad", NULL);
	if (hWndNotepad)
	{
		hEditWnd = FindWindowEx(hWndNotepad, NULL, "Edit", NULL);
		if (hEditWnd) {
			BOOL bOk = SetHook(GetWindowThreadProcessId(hEditWnd, NULL));
            std::cout << "Notepad hooked!" << std::endl;
        }
	}
    else 
    {
        std::cout << "Hook failed!" << std::endl;
    }

	MSG msg;
	GetMessage(&msg, NULL, 0, 0);

	return 0;
}