#pragma once
#include "Wnd.h"
#include "pch.h"
class WebManager{
public:
	Wnd* wnd;
	SOCKET sock;
	SOCKADDR_IN localAddr, targetAddr;
	int localLen, targetLen;
	static UINT thread(LPVOID pParam);
	void createHost(string localIP, const int localport);
	void connectHost(string ip, const int port);
	void disconnet();
	void sendOnTimer();
	int recive[11] = { 0 };
	int send[11] = { 0 };
	int isconnecting=0;
	WebManager(Wnd*);
};

