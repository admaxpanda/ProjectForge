#include "WebManager.h"
#include "conio.h"
WebManager::WebManager(Wnd* wnd) {
	this->wnd = wnd;
	WSADATA data;
	WORD w = MAKEWORD(2, 0);
	::WSAStartup(w, &data);
	reciveSock=::socket(AF_INET, SOCK_DGRAM, 0);
	sendSock=::socket(AF_INET, SOCK_DGRAM, 0);
}
UINT WebManager::thread(LPVOID pParam) {
	WebManager* w = (WebManager*)pParam;
	AllocConsole();
	_cprintf("%d",w->localport);
}
void WebManager::connectHost(string ip,const int port) {
	strcpy(targetIP, ip.c_str());
	targetPort = port;
	sockaddr_in addr;
	int nSockAddrSize = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(targetIP);
	sendto(sendSock, (char*)send, sizeof(send), 0, (sockaddr*)&addr, nSockAddrSize);
}
void WebManager::createHost(string ip, const int port) {
	strcpy(localIP, ip.c_str());
	localport = port;

	sockaddr_in reciveaddr;
	reciveaddr.sin_family = AF_INET;
	reciveaddr.sin_port = htons(port);
	reciveaddr.sin_addr.S_un.S_addr = inet_addr(localIP);
	bind(reciveSock, (sockaddr*)&reciveaddr, sizeof(reciveaddr));
	sockaddr_in sendaddr;
	int nSockAddrSize = sizeof(sendaddr);
	recvfrom(reciveSock, (char*)recive, sizeof(recive), 0, (sockaddr*)&sendaddr, &nSockAddrSize);

	targetPort = sendaddr.sin_port;
	targetIP = inet_ntoa(sendaddr.sin_addr);
	sendto(sendSock, (char*)send, sizeof(send), 0, (sockaddr*)&sendaddr, nSockAddrSize);

	AfxBeginThread(thread, this);
}
void WebManager::disconnet() {
	return;
}