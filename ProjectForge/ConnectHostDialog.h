#pragma once
#include "pch.h"

// ConnectHostDialog 对话框

class ConnectHostDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectHostDialog)
public:
	int port;
	string ip;

public:
	ConnectHostDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ConnectHostDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = CONNECT_HOST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
