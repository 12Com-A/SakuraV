#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

bool SendAll(SOCKET s, const char* buf, int len);

bool SendFrame(SOCKET s, const std::string& payload);

int RecvAll(SOCKET s, char* buf, int len);

int RecvFrame(SOCKET s, std::string& out);

std::string GetConsoleContent();