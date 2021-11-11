#include "WebManager.h"
WebManager::WebManager(Wnd* wnd) {
	this->wnd = wnd;
	WSADATA data;
	WORD w = MAKEWORD(2, 0);
	::WSAStartup(w, &data);
	reciveSock=::socket(AF_INET, SOCK_DGRAM, 0);
	sendSock=::socket(AF_INET, SOCK_DGRAM, 0);
}
void WebManager::disconnet() {
	return;
}