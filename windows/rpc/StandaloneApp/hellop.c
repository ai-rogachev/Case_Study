/* file hellop.c */
#pragma once

// IDL - interface definition file contains 
//      type definitions, 
//      attributes 
//      function prototypes 
//      that describe how data is transmitted on the network.
//
// ACF - application configuration file contains 
//      attributes that configure your 
//      application for a particular operating 
//      environment without affecting its network characteristics.
//
// The following command generates a UUID and creates a template
//  file called Hello.idl.
// 
// uuidgen /i /ohello.idl
//
// Generate stub and header files
// 
// midl hello.idl


#include <stdio.h>
#include <windows.h>

void HelloProc(const char* pszString)
{
    printf("%s\n", pszString);
}
