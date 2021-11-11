#pragma once


// CreateHostDialog 对话框

class CreateHostDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CreateHostDialog)

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
};
