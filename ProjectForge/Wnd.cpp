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
	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(0, 100, 0);
	return 0;
}

void Wnd::OnTimer(UINT_PTR nIDEvnet) {
	//_cprintf("QUQ\n");
	if (webManager->isconnecting) {
		memcpy(webManager->send, player->toWebMessage(),sizeof(webManager->send));
		webManager->sendOnTimer();
	}
	if (webManager->recive[STATEID])
	{

	}
}

void Wnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
}


void Wnd::OnAbout()
{
	AboutDialog* p = new AboutDialog;
	p->DoModal();
	delete p;
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
}
