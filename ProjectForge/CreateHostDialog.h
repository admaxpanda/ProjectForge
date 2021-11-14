#pragma once
#include "pch.h"

// CreateHostDialog 对话框

class CreateHostDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CreateHostDialog)

public:
	string ip;
	int port;
public:
	CreateHostDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CreateHostDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = CREATE_HOST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit2();
};
