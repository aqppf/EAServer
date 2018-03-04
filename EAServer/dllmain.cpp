// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <stdio.h> 
#include <tchar.h>
#include <windows.h> 
#include <winsock2.h>    

#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
SOCKET slisten, client;
/***
 *	CString STemp; #include <atlstr.h>
 *	STemp.Format(_T("%d"), code);
 *	MessageBox(0, STemp, 0, 0);
***/

DWORD WINAPI ListenSocketThread(LPVOID lpParameter);

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, ListenSocketThread, (LPVOID)10, NULL, 0);
		MessageBox(0, _T("EA start 888"), 0, 0);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		closesocket(client); closesocket(slisten);
        break;
    }
    return TRUE;
}

void SendData(double *data) 
{
	char sendData[1024];
	sprintf_s(sendData, "%.5f %.1f\r\n", data[0],data[1]);
	send(client, sendData, strlen(sendData), 0);
}

DWORD WINAPI RecvDataThread(LPVOID lpParameter) 
{
	SOCKET sClient = (SOCKET)lpParameter;
	
	closesocket(client); // 关闭上一个client
	client = sClient;

	char revData[1024];

	while (true)
	{
		int ret = recv(client, revData, 1024, 0);
		if (ret == SOCKET_ERROR)  break;
	}
	return 0;
}

DWORD WINAPI ListenSocketThread(LPVOID lpParameter) {

	//初始化WSA    
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) 
		return 0;

	//创建套接字    
	slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)  return 0;

	//绑定IP和端口    
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) return 0;

	if (listen(slisten, 5) == SOCKET_ERROR) return 0;

	//循环接收数据    
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	while (true)
	{
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET) break;	

		CreateThread(0, 0, RecvDataThread, (LPVOID)sClient, NULL, 0);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}

