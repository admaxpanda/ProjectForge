#include "WebManager.h"
#include "conio.h"
WebManager::WebManager(Wnd* wnd) {
	this->wnd = wnd;
	WSADATA data;
	WORD w = MAKEWORD(2, 0);
	::WSAStartup(w, &data);
	sock=::socket(AF_INET, SOCK_DGRAM, 0);
	//send[STATEID] = 1;
}
UINT WebManager::thread(LPVOID pParam) {
	WebManager* w = (WebManager*)pParam;
	_cprintf("thread\n");
	while (1) {
		recvfrom(w->sock, (char*)(w->recive), sizeof(w->recive), 0, (sockaddr*)&(w->targetAddr), &(w->targetLen));
		if (w->recive[STATEID] == 0) {
			_cprintf("recive disconnect\n");
			w->send[STATEID] = 0;
			w->isconnecting = 0;
			sendto(w->sock, (char*)w->send, sizeof(send), 0, (sockaddr*)&w->targetAddr, w->targetLen);
			closesocket(w->sock);
			w->wnd->menu.EnableMenuItem(DISCONNECT, MF_GRAYED);
			w->wnd->menu.EnableMenuItem(CREATE_HOST, MF_ENABLED);
			w->wnd->menu.EnableMenuItem(CONNECT_HOST, MF_ENABLED);
			//memset(&(w->sock), 0, sizeof(sock));
			w->wnd->webManager = new WebManager(w->wnd);
			delete w;
			return 0;
		}
		else
		{
			w->isconnecting = 1;
		}
	}
}
void WebManager::connectHost(string ip,const int port) {
	_cprintf("connect\n");
	isconnecting = 1;
	targetAddr.sin_family = AF_INET;
	targetAddr.sin_port = htons(port);
	char* c=new char[20];
	strcpy(c, ip.c_str());
	targetAddr.sin_addr.S_un.S_addr = inet_addr(c);
	targetLen = sizeof(targetAddr);
	sendto(sock, (char*)send, sizeof(send), 0, (sockaddr*)&targetAddr, targetLen);
	getsockname(sock, (struct sockaddr*)&localAddr, &localLen);
	AfxBeginThread(thread, this);
}
void WebManager::createHost(string ip, const int port) {
	_cprintf("create\n");
	//isconnecting = 1;
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(port);
	char* c=new char[20];
	strcpy(c, ip.c_str());
	localAddr.sin_addr.S_un.S_addr = inet_addr(c);
	bind(sock, (sockaddr*)&localAddr, localLen=sizeof(localAddr));
	targetLen = sizeof(targetAddr);	
	AfxBeginThread(thread, this);
}
void WebManager::sendOnTimer() {
	sendto(sock, (char*)send, sizeof(send), 0, (sockaddr*)&targetAddr, targetLen);
}
void WebManager::disconnet() {
	_cprintf("disconnect\n");
	isconnecting = 0;
	send[STATEID] = 0;
	sendto(sock, (char*)send, sizeof(send), 0, (sockaddr*)&localAddr, localLen);
	sendto(sock, (char*)send, sizeof(send), 0, (sockaddr*)&targetAddr, targetLen);
	closesocket(sock);
	wnd->menu.EnableMenuItem(DISCONNECT, MF_GRAYED);
	wnd->menu.EnableMenuItem(CREATE_HOST, MF_ENABLED);
	wnd->menu.EnableMenuItem(CONNECT_HOST, MF_ENABLED);
	return;
}