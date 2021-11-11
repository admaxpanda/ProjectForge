#pragma once


// HelpDialog 对话框

class HelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDialog)

public:
	HelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HelpDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = HELP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
