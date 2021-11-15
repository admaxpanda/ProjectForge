#include "WebManager.h"
#include "conio.h"
WebManager::WebManager(Wnd* wnd) {
	this->wnd = wnd;
	WSADATA data;
	WORD w = MAKEWORD(2, 0);
	::WSAStartup(w, &data);
	sock=::socket(AF_INET, SOCK_DGRAM, 0);
}
UINT WebManager::thread(LPVOID pParam) {
	WebManager* w = (WebManager*)pParam;
	while (1) {
		recvfrom(w->sock, (char*)(w->recive), sizeof(w->recive), 0, (sockaddr*)&(w->targetAddr), &(w->targetLen));
	}
}
void WebManager::connectHost(string ip,const int port) {
	targetAddr.sin_family = AF_INET;
	targetAddr.sin_port = htons(port);
	char* c;
	strcpy(c, ip.c_str());
	targetAddr.sin_addr.S_un.S_addr = inet_addr(c);
	targetLen = sizeof(targetAddr);
	sendto(sock, (char*)send, sizeof(send), 0, (sockaddr*)&targetAddr, targetLen);
	recvfrom(sock, (char*)recive, sizeof(recive), 0, (sockaddr*)&targetAddr, &targetLen);
	getsockname(sock, (struct sockaddr*)&localAddr, &localLen);
	AfxBeginThread(thread, this);
}
void WebManager::createHost(string ip, const int port) {
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(port);
	char* c;
	strcpy(c, ip.c_str());
	localAddr.sin_addr.S_un.S_addr = inet_addr(c);
	bind(sock, (sockaddr*)&localAddr, localLen=sizeof(localAddr));
	targetLen = sizeof(targetAddr);
	recvfrom(sock, (char*)recive, sizeof(recive), 0, (sockaddr*)&targetAddr, &targetLen);

	sendto(sock, (char*)send, sizeof(send), 0, (sockaddr*)&targetAddr, targetLen);
	
	AfxBeginThread(thread, this);
}
void WebManager::disconnet() {

	return;
}