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
	menu.LoadMenuW(MAIN_MENU);
	SetMenu(&menu);
	webManager = new WebManager(this);
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
	// TODO: 在此添加命令处理程序代码
}


void Wnd::OnAbout()
{
	AboutDialog* p = new AboutDialog;
	p->DoModal();
	// TODO: 在此添加命令处理程序代码
}


void Wnd::OnDisconnect()
{
	webManager->disconnet();
}


void Wnd::OnHost()
{
	CreateHostDialog* p = new CreateHostDialog;
	p->DoModal();
	AllocConsole();
	_cprintf("%d %d", p->ip.GetLength(), p->port.GetLength());
	// TODO: 在此添加命令处理程序代码
}


void Wnd::OnConnect()
{
	ConnectHostDialog* p = new ConnectHostDialog;
	p->DoModal();
	// TODO: 在此添加命令处理程序代码
}
