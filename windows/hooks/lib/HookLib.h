#pragma once

#if !defined(HOOKLIBAPI)
#define HOOKLIBAPI __declspec(dllimport)
#endif

HOOKLIBAPI BOOL WINAPI SetHook(DWORD dwThreadId);