#include "Wnd.h"
#include "conio.h"
#include "WebManager.h"
#include "CreateHostDialog.h"
#include "ConnectHostDialog.h"

BEGIN_MESSAGE_MAP(Wnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(HELP, &Wnd::OnHelp)
	ON_COMMAND(ABOUT, &Wnd::OnAbout)
	ON_COMMAND(DISCONNECT, &Wnd::OnDisconnect)
	ON_COMMAND(CREATE_HOST, &Wnd::OnHost)
	ON_COMMAND(CONNECT_HOST, &Wnd::OnConnect)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


int Wnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	AllocConsole();
	this->m_bAutoMenuEnable = 0;
	menu.LoadMenuW(MAIN_MENU);
	SetMenu(&menu);
	menu.EnableMenuItem(DISCONNECT, MF_GRAYED);
	webManager = new WebManager(this);
	create = new CreateHostDialog;
	connect = new ConnectHostDialog;
	// TODO:  在此添加您专用的创建代码
	SetTimer(0, 17, 0);
	return 0;
}

void Wnd::OnTimer(UINT_PTR nIDEvnet) {
	//_cprintf("QUQ\n");
	//GetCursorPos(&player->mousepos);
	//ScreenToClient(&player->mousepos);
	if (webManager->isconnecting) {
		memcpy(webManager->send, player->toWebMessage(),sizeof(webManager->send));
		webManager->sendOnTimer();
	}
	controlmanager();
	queue<ControlMessage> tmp;
	memcpy(&tmp, &player->messageQ, sizeof(player->messageQ));
	while (!tmp.empty()) {
		_cprintf("%d", tmp.front().ID);
		tmp.pop();
	}
	//player->stateCalculation(webManager->recive);
}
int Wnd::keydown(int key) {
	return GetKeyState(VK_LSHIFT) < 0;
}
double Wnd::getRadian(CPoint o, CPoint p) {
	if (p.x > o.x)
		if (p.y > o.y)
			return atan(1.0 * (p.x - o.x) / (p.y - o.y));
		else if (p.y < o.y)
			return atan(1.0 * (o.y - p.y) / (p.x - o.x)) + MATHPI / 2;
		else
			return MATHPI / 2;
	if (p.x < o.x)
		if (p.y > o.y)
			return atan(1.0 * (p.y - o.y) / (o.x - p.x)) + MATHPI / 2 * 3;
		else if (p.y < o.y)
			return atan(1.0 * (o.x - p.x) / (o.y - p.y)) + MATHPI;
		else
			return MATHPI / 2 * 3;
	else
		if (p.y > o.y)
			return 0;
		else if (p.y < o.y)
			return MATHPI;
		else
			return 0;
}
void Wnd::controlmanager() {
	if (player->stepCD > 0)
		player->stepCD--;
	if (keydown(VK_SHIFT)) {
		while (!player->messageQ.empty())
			player->messageQ.pop();
		if (!player->stepCD)
		{
			double cnt = 0;
			int horizontal = 0, vertical = 0;
			if (keydown('W'))vertical++;
			if (keydown('S'))vertical--;
			if (keydown('A'))horizontal--;
			if (keydown('D'))horizontal++;
			if (vertical > 0)
				if (horizontal > 0)
					cnt = MATHPI / 4;
				else if (horizontal < 0)
					cnt = MATHPI / 4 * 7;
				else
					cnt = 0;
			else if (vertical < 0)
				if (horizontal > 0)
					cnt = MATHPI / 4 * 3;
				else if (horizontal < 0)
					cnt = MATHPI / 4 * 5;
				else
					cnt = MATHPI;
			else
				if (horizontal > 0)
					cnt = MATHPI / 2;
				else if (horizontal < 0)
					cnt = MATHPI / 2 * 3;
				else
					cnt = getRadian(player->pos,player->mousepos);
			player->stepCD = 60;
			player->messageQ.push(ControlMessage(MESSAGESTEP, cnt));
			return;
		}
	}
	if (keydown(VK_RBUTTON)) {
		if (player->messageQ.empty() || player->messageQ.back().ID != MESSAGEDEFEND)
			player->messageQ.push(ControlMessage(MESSAGEDEFEND, getRadian(player->pos, player->mousepos)));
		return;
	}
	if (keydown(VK_LBUTTON)) {
		attacktime++;
		if (attacktime > 20){
			if (player->messageQ.empty() || player->messageQ.back().ID != MESSAGESPIKE)
				player->messageQ.push(ControlMessage(MESSAGESPIKE, getRadian(player->pos, player->mousepos)));
			return;
		}

	}
	int c = 0;
	if (keydown('C')) {
		if (player->messageQ.empty() || player->messageQ.back().ID != MESSAGESQUAT)
			player->messageQ.push(ControlMessage(MESSAGESQUAT, 0));
		c++;
	}
	if (!c && keydown(VK_SPACE)) {
		if (player->messageQ.empty() || player->messageQ.back().ID != MESSAGEJUMP)
			player->messageQ.push(ControlMessage(MESSAGEJUMP, 0));
		c++;
	}
	if (!keydown(VK_LBUTTON)&&attacktime) {
		if (attacktime <= 20) {
			player->messageQ.push(ControlMessage(MESSAGEATTACK, getRadian(player->pos, player->mousepos)));
			return;
		}
	}
	if(!c){
		double cnt = 0;
		int horizontal = 0, vertical = 0;
		if (keydown('W'))vertical++;
		if (keydown('S'))vertical--;
		if (keydown('A'))horizontal--;
		if (keydown('D'))horizontal++;
		if (vertical > 0)
			if (horizontal > 0)
				cnt = MATHPI / 4;
			else if (horizontal < 0)
				cnt = MATHPI / 4 * 7;
			else
				cnt = 0;
		else if (vertical < 0)
			if (horizontal > 0)
				cnt = MATHPI / 4 * 3;
			else if (horizontal < 0)
				cnt = MATHPI / 4 * 5;
			else
				cnt = MATHPI;
		else
			if (horizontal > 0)
				cnt = MATHPI / 2;
			else if (horizontal < 0)
				cnt = MATHPI / 2 * 3;
			else
				cnt = -1;
		if (cnt != -1){
			while (!player->messageQ.empty())
				player->messageQ.pop();
			player->messageQ.push(ControlMessage(MESSAGEMOVE, cnt));
		}
	}
}
void Wnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = 1366; 
	lpMMI->ptMinTrackSize.y = 768; 
	lpMMI->ptMaxTrackSize.x = 1366; 
	lpMMI->ptMaxTrackSize.y = 768; 
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}


void Wnd::OnHelp()
{
	HelpDialog* p = new HelpDialog;
	p->DoModal();
	delete p;
	// TODO: 在此添加命令处理程序代码
}


void Wnd::OnAbout()
{
	AboutDialog* p = new AboutDialog;
	p->DoModal();
	delete p;
	// TODO: 在此添加命令处理程序代码
}


void Wnd::OnDisconnect()
{
	webManager->disconnet();
}


void Wnd::OnHost()
{
	create->DoModal();
	if (create->confirm)
	{
		menu.EnableMenuItem(DISCONNECT, MF_ENABLED);
		menu.EnableMenuItem(CREATE_HOST, MF_GRAYED);
		menu.EnableMenuItem(CONNECT_HOST, MF_GRAYED);
		create->confirm--;
		webManager->createHost(create->ip, create->port);
	}
}

void Wnd::OnConnect()
{
	connect->DoModal();
	if (connect->confirm)
	{
		menu.EnableMenuItem(DISCONNECT, MF_ENABLED);
		menu.EnableMenuItem(CREATE_HOST, MF_GRAYED);
		menu.EnableMenuItem(CONNECT_HOST, MF_GRAYED);
		connect->confirm--;
		webManager->connectHost(connect->ip, connect->port);
	}
	// TODO: 在此添加命令处理程序代码
}

void Wnd::BufferDraw(CDC* pDC) {

}

void Wnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()
}


BOOL Wnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;
}
