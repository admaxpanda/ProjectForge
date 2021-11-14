#pragma once
#include "Wnd.h"
#include "pch.h"
class WebManager{
public:
	Wnd* wnd;
	int localport;
	char* localIP;
	int targetPort;
	char* targetIP;
	SOCKET sendSock;
	SOCKET reciveSock;
	static UINT thread(LPVOID pParam);
	void createHost(string localIP, const int localport);
	void connectHost(string ip, const int port);
	void disconnet();
	void send();
	void rest();
	int recive[10];
	int send[10];
	WebManager(Wnd*);
};

