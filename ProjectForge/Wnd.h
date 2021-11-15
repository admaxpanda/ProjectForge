#pragma once
#include "pch.h"
#include "HelpDialog.h"
#include "AboutDialog.h"
#include "Player.h"
#include "CreateHostDialog.h"
#include "ConnectHostDialog.h"
class WebManager;
class Wnd:public CFrameWnd
{
public:
    CMenu menu;
    WebManager* webManager;
    Player* player;
    CreateHostDialog* create;
    ConnectHostDialog* connect;

public:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg void OnHelp();
    afx_msg void OnAbout();
    afx_msg void OnDisconnect();
    afx_msg void OnHost();
    afx_msg void OnConnect();
};

