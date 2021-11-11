#include "Wnd.h"
BEGIN_MESSAGE_MAP(Wnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


int Wnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	menu.LoadMenuW(MAIN_MENU);
	SetMenu(&menu);
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
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
