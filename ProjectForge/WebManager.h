#pragma once
#include "WebMessage.h"
#include "Wnd.h"
class WebManager{
public:
	Wnd* wnd;
	int localport;
	char* localIP;
	int targetPort;
	char* targetIP;
	SOCKET sendSock;
	SOCKET reciveSock;
	UINT _cdecl ThreadProc(LPVOID lpParameter);
	void createHost();
	void connectHost();
	void disconnet();
	void send();
	void rest();
	WebManager(Wnd*);
};

