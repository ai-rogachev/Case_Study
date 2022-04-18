/* file: hello.c, a stand-alone application */
#include "hellop.c"

int main()
{
    const char* pszString = "Hello, World";
    HelloProc(pszString);

    return 0;
}