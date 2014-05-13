#define WIN32_LEAN_AND_MEAN	
#include <Windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

#define PORTA "4444"