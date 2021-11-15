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
END_MESSAGE_MAP()


int Wnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->m_bAutoMenuEnable = 0;
	menu.LoadMenuW(MAIN_MENU);
	SetMenu(&menu);
	menu.EnableMenuItem(DISCONNECT, MF_GRAYED);
	webManager = new WebManager(this);
	create = new CreateHostDialog;
	connect = new ConnectHostDialog;
	// TODO:  在此添加您专用的创建代码

	return 0;
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
	//webManager->createHost(p->ip, p->port);
	//AllocConsole();
	//_cprintf("%s %d\n", p->ip.c_str(), p->port);
	// TODO: 在此添加命令处理程序代码
}


void Wnd::OnConnect()
{
	connect->DoModal();
	
	// TODO: 在此添加命令处理程序代码
}
