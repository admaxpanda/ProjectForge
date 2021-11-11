#pragma once
#include "pch.h"
class Wnd:public CFrameWnd
{
public:
    CMenu menu;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};

