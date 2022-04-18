/* file: helloc.c */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "hello.h" 
#include <windows.h>

void main()
{
    RPC_STATUS status;
    RPC_WSTR pszUuid = NULL;
    RPC_WSTR pszProtocolSequence = (RPC_WSTR)L"ncacn_np";
    RPC_WSTR pszNetworkAddress = NULL;
    RPC_WSTR pszEndpoint = (RPC_WSTR)L"\\pipe\\hello";
    RPC_WSTR pszOptions = NULL;
    RPC_WSTR pszStringBinding = NULL;
    const unsigned char* pszString = (unsigned char*)"hello, world";
    unsigned long ulCode;

    status = RpcStringBindingCompose(pszUuid,
        pszProtocolSequence,
        pszNetworkAddress,
        pszEndpoint,
        pszOptions,
        &pszStringBinding);
    if (status) 
        exit(status);

    status = RpcBindingFromStringBinding(pszStringBinding, &hello_IfHandle);

    if (status) 
        exit(status);

    RpcTryExcept
    {
        HelloProc(pszString);
        Shutdown();
    }
    RpcExcept(1)
    {
        ulCode = RpcExceptionCode();
        printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
    }
    RpcEndExcept

    status = RpcStringFree(&pszStringBinding);

    if (status) 
        exit(status);

    status = RpcBindingFree(&hello_IfHandle);

    if (status) 
        exit(status);

    exit(0);
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR* ptr)
{
    free(ptr);
}