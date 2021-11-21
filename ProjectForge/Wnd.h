#pragma once
#include "pch.h"
#include "HelpDialog.h"
#include "AboutDialog.h"
#include "Player.h"
#include "CreateHostDialog.h"
#include "ConnectHostDialog.h"
class WebManager;
class Wnd:public CFrameWnd{
public:
    CMenu menu;
    WebManager* webManager;
    Player* player;
    CreateHostDialog* create;
    ConnectHostDialog* connect;
    CDC bufferdc;
    CBitmap bufferbmp;
    CPen penHealth, penHealthEmpty, penBody, penBodyEmpty;
    CBitmap* characterA, * characterB;
    int attacktime=0;
    void BufferDraw(CDC* pdc);
    void controlmanager();
    static int keydown(int key);
    static double getRadian(CPoint o, CPoint p);
    static int getToward(double toward);
    static int getToward(int toward);
public:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg void OnHelp();
    afx_msg void OnAbout();
    afx_msg void OnDisconnect();
    afx_msg void OnHost();
    afx_msg void OnConnect();
    afx_msg void OnTimer(UINT_PTR nIDEvnet);
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

