#pragma once


// ConnectHostDialog 对话框

class ConnectHostDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectHostDialog)

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
};
