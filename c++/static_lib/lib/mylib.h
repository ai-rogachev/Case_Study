#pragma once

//#ifdef MYLILB_EXPORT
//#define MYLIB_API __declspec(dllexport)
//#else
//#define MYLIB_API __declspec(dllimport)
//#endif

//extern "C" MYLIB_API int __stdcall add(int a, int b);
//extern "C" MYLIB_API int __stdcall sub(int a, int b);

int add(int a, int b);
int sub(int a, int b);