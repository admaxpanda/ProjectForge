#include "App.h"
App a;
BOOL App::InitInstance()
{
	Wnd* p = new Wnd;
	p->Create(0, L"ProjectForge");
	p->SetWindowPos(0, 200, 200, 1366, 768, 0);
	p->ShowWindow(m_nCmdShow);
	m_pMainWnd = p;
	return 1;
}