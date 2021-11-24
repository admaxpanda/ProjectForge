#include "Wnd.h"
#include "conio.h"
#include "WebManager.h"
#include "CreateHostDialog.h"
#include "ConnectHostDialog.h"
#include "wingdi.h"
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

int Wnd::getToward(double toward) {
	while (toward < 0)
		toward += 2 * MATHPI;
	while (toward > 2 * MATHPI)
		toward -= 2 * MATHPI;
	if (toward <= MATHPI)
		return 1;
	else
		return 0;
}
int Wnd::getToward(int toward) {
	while (toward < 0)
		toward += 360;
	while (toward > 360)
		toward -= 360;
	if (toward <= 180)
		return 1;
	else
		return 0;
}
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
	player = new Player;
	player->create(player);
	penHealth.CreatePen(PS_SOLID, 22, RGB(46, 139, 87));
	penHealthEmpty.CreatePen(PS_SOLID, 20, RGB(139, 0, 0));
	penBody.CreatePen(PS_SOLID, 22, RGB(255, 215, 0));
	penBodyEmpty.CreatePen(PS_SOLID, 20, RGB(55, 42, 8));
	characterA = new CBitmap;
	characterB = new CBitmap;
	characterA->m_hObject=(HBITMAP)::LoadImage(0, L"characterA.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	characterB->m_hObject = (HBITMAP)::LoadImage(0, L"characterB.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	// TODO:  在此添加您专用的创建代码
	SetTimer(0, TICK1, 0);
	return 0;
}

void Wnd::OnTimer(UINT_PTR nIDEvnet) {
	//_cprintf("QUQ\n");
	Invalidate();
	//_cprintf("%x", player->state->ID);
	memcpy(webManager->send, player->toWebMessage(), sizeof(webManager->send));
	GetCursorPos(&player->mousepos);
	ScreenToClient(&player->mousepos);
	if (webManager->isconnecting)
		//memcpy(webManager->send, player->toWebMessage(),sizeof(webManager->send));
		webManager->sendOnTimer();
	
	//for (int i = 0; i < 11; i++)
	//	_cprintf("%d ", webManager->recive[i]);
	//_cprintf("\n");
	controlmanager();
	player->stateCalculation(webManager->recive);
	//if (player->stateToDelete)
	//	delete player->stateToDelete;
	//queue<ControlMessage> tmp(player->messageQ);
	//_cprintf("\n");
	//while (!tmp.empty()) {
	//	_cprintf("%d ", tmp.front().ID);
	//	tmp.pop();
	//}
	//player->stateCalculation(webManager->recive);
}
int Wnd::keydown(int key) {
	return GetKeyState(key) < 0;
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
	//int d =(int)( r2a(getRadian(player->pos, player->mousepos)));
	//_cprintf("%d\n", d);
	//_cprintf("%d %f", d, r2a(getRadian(player->pos, player->mousepos)));
	if (player->stepCD > 0)
		player->stepCD--;
	if (keydown(VK_SHIFT)) {
		while (!player->messageQ.empty())
			player->messageQ.pop();
		if (!player->stepCD)
		{
			//_cprintf("%d", keydown(VK_SHIFT));
			int cnt = 0;
			int horizontal = 0, vertical = 0;
			if (keydown('W'))vertical++;
			if (keydown('S'))vertical--;
			if (keydown('A'))horizontal--;
			if (keydown('D'))horizontal++;
			if (vertical > 0)
				if (horizontal > 0)
					cnt = 45;
				else if (horizontal < 0)
					cnt = 315;
				else
					cnt = 0;
			else if (vertical < 0)
				if (horizontal > 0)
					cnt = 135;
				else if (horizontal < 0)
					cnt = 225;
				else
					cnt = 180;
			else
				if (horizontal > 0)
					cnt = 90;
				else if (horizontal < 0)
					cnt = 270;
				else
					cnt = r2a(getRadian(player->pos,player->mousepos));
			player->stepCD = 10;
			//printf("*%d\n", cnt);
			//_cprintf("MESSAGESTEP\n");
			player->messageQ.push(ControlMessage(MESSAGESTEP, cnt));
			//_cprintf("PUSHED\n");
			return;
		}
	}
	//_cprintf("%d", keydown(VK_RBUTTON));
	if (keydown(VK_RBUTTON)) {
		if (player->messageQ.empty() || player->messageQ.back().ID != MESSAGEDEFEND)
			player->messageQ.push(ControlMessage(MESSAGEDEFEND, r2a(getRadian(player->pos, player->mousepos))));
		return;
	}
	if (keydown(VK_LBUTTON)) {
		attacktime++;
		if (attacktime > 5){
			if (player->messageQ.empty() || player->messageQ.back().ID != MESSAGESPIKE)
				player->messageQ.push(ControlMessage(MESSAGESPIKE, r2a(getRadian(player->pos, player->mousepos))));
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
		if (attacktime <= 5) {
			player->messageQ.push(ControlMessage(MESSAGEATTACK, r2a(getRadian(player->pos, player->mousepos))));
			attacktime = 0;
			return;
		}
		attacktime = 0;
	}
	if(!c){
		int cnt=0;
		int horizontal = 0, vertical = 0;
		if (keydown('W'))vertical++;
		if (keydown('S'))vertical--;
		if (keydown('A'))horizontal--;
		if (keydown('D'))horizontal++;
		if (vertical > 0)
			if (horizontal > 0)
				cnt = 45;
			else if (horizontal < 0)
				cnt = 315;
			else
				cnt = 0;
		else if (vertical < 0)
			if (horizontal > 0)
				cnt = 135;
			else if (horizontal < 0)
				cnt = 225;
			else
				cnt = 180;
		else
			if (horizontal > 0)
				cnt = 90;
			else if (horizontal < 0)
				cnt = 270;
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
	CPaintDC dc(this);
	CRect rectClient;
	CDC dcMem, dcBkgnd;
	CBitmap bitmapTemp, * pOldBitmap;
	GetClientRect(&rectClient);//获取窗口信息
	bitmapTemp.CreateCompatibleBitmap(&dc, rectClient.Width(), rectClient.Height());//创建内存位图
	dcMem.CreateCompatibleDC(&dc); //依附窗口DC创建兼容的DC
	pOldBitmap = dcMem.SelectObject(&bitmapTemp);//将内存位图选入内存dc
	//填充颜色
	dcMem.FillSolidRect(rectClient, RGB(255, 255, 255));   //填充颜色

	/*
	各种绘图操作在这里进行
	*/
	CDC*playerA = new CDC,*playerB=new CDC;
	playerA->CreateCompatibleDC(&dc);
	playerA->SelectObject(characterA);
	playerB->CreateCompatibleDC(&dc);
	playerB->SelectObject(characterB);
	if (webManager->recive[STATEID]) {
		if (getToward(webManager->recive[TOWARD]))
			dcMem.BitBlt(webManager->recive[POSX] - CHARACTERWIDTH / 2, webManager->recive[POSY] - CHARACTERWIDTH, CHARACTERWIDTH, CHARACTERWIDTH, playerB, 1024 + webManager->recive[PICTUREX] * CHARACTERWIDTH, webManager->recive[PICTUREY] * CHARACTERWIDTH, SRCAND);
		else
			dcMem.BitBlt(webManager->recive[POSX] - CHARACTERWIDTH / 2, webManager->recive[POSY] - CHARACTERWIDTH, CHARACTERWIDTH, CHARACTERWIDTH, playerB, 896 - webManager->recive[PICTUREX] * CHARACTERWIDTH, -webManager->recive[PICTUREY] * CHARACTERWIDTH, SRCAND);
	}
	//_cprintf("%d %d\n", player->gettoward(), getToward(player->gettoward()));
	if (getToward(player->gettoward()))
		dcMem.BitBlt(player->pos.x - CHARACTERWIDTH / 2, player->pos.y - CHARACTERWIDTH, CHARACTERWIDTH, CHARACTERWIDTH, playerA, 1024 + player->getpicutre().x * CHARACTERWIDTH, player->getpicutre().y * CHARACTERWIDTH, SRCAND);
	else
		dcMem.BitBlt(player->pos.x - CHARACTERWIDTH / 2, player->pos.y - CHARACTERWIDTH, CHARACTERWIDTH, CHARACTERWIDTH, playerA, 896 - player->getpicutre().x * CHARACTERWIDTH, player->getpicutre().y * CHARACTERWIDTH, SRCAND);
	if (webManager->recive[STATEID]) {
		dcMem.SelectObject(&penHealthEmpty);
		dcMem.MoveTo(CPoint(1000, 30));
		dcMem.LineTo(CPoint(1300, 30));
		if (webManager->recive[HEALTH]) {
			dcMem.SelectObject(&penHealth);
			dcMem.MoveTo(CPoint(1000, 30));
			dcMem.LineTo(CPoint(1000 + webManager->recive[HEALTH] * 3, 30));
		}
		if (webManager->recive[BODY]) {
			dcMem.SelectObject(&penBodyEmpty);
			dcMem.MoveTo(CPoint(483, 30));
			dcMem.LineTo(CPoint(883, 30));
			dcMem.SelectObject(&penBody);
			dcMem.MoveTo(CPoint(683 - webManager->recive[BODY] * 2, 30));
			dcMem.LineTo(CPoint(683 + webManager->recive[BODY] * 2, 30));
		}
		
	}
	dcMem.SelectObject(&penHealthEmpty);
	dcMem.MoveTo(CPoint(66, 680));
	dcMem.LineTo(CPoint(366, 680));
	if (player->health) {
		dcMem.SelectObject(&penHealth);
		dcMem.MoveTo(CPoint(66, 680));
		dcMem.LineTo(CPoint(66 + player->health * 3, 680));
	}
	if (player->body) {
		dcMem.SelectObject(&penBodyEmpty);
		dcMem.MoveTo(CPoint(483, 680));
		dcMem.LineTo(CPoint(883, 680));
		dcMem.SelectObject(&penBody);
		dcMem.MoveTo(CPoint(683 - player->body * 2, 680));
		dcMem.LineTo(CPoint(683 + player->body * 2, 680));
	}
	

	//dcMem.BitBlt(0, 0, 1024, 512, mdc, 0, 0, SRCCOPY);
	dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &dcMem, 0, 0, SRCCOPY);//绘制图片到主dc
	//dc.BitBlt(0, 0, 1024, 512, mdc, 0, 0, SRCCOPY);
	//dcMem.SelectObject(pOldBitmap);//清理
	dcMem.DeleteDC();
	playerA->DeleteDC();
	playerB->DeleteDC();
}


BOOL Wnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;
}
