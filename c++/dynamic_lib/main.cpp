// https://www.ibm.com/support/pages/part-one-how-dynamically-link-pure-c-function-dll-library-rhapsody-executable-project
// https://stackoverflow.com/questions/3742090/custom-directory-for-cmake-library-output

#include <windows.h>
#include <iostream>

typedef int (__stdcall *f_func)(int a, int b);

int main()
{
    HINSTANCE hGetProcIDDLL = LoadLibrary("lib.dll");

    if (!hGetProcIDDLL) {
        std::cout << "Could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    f_func addFun = (f_func) GetProcAddress(hGetProcIDDLL, "add");
    if (!addFun) {
        std::cout << "Could not locate the function" << std::endl;
        FreeLibrary(hGetProcIDDLL);
        return EXIT_FAILURE;
    }

    std::cout << "int add(int a, int b) is = " << addFun(10, 5) << std::endl;

    FreeLibrary(hGetProcIDDLL);
    return EXIT_SUCCESS;
}