// ConnectHostDialog.cpp: 实现文件
//

#include "pch.h"
#include "ConnectHostDialog.h"
#include "afxdialogex.h"


// ConnectHostDialog 对话框

IMPLEMENT_DYNAMIC(ConnectHostDialog, CDialogEx)

ConnectHostDialog::ConnectHostDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CONNECT_HOST_DIALOG, pParent)
{

}

ConnectHostDialog::~ConnectHostDialog()
{
}

void ConnectHostDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConnectHostDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ConnectHostDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &ConnectHostDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ConnectHostDialog 消息处理程序


void ConnectHostDialog::OnBnClickedOk()
{
	USES_CONVERSION;
	CString a, b;
	GetDlgItemText(IDC_EDIT1, a);
	GetDlgItemText(IDC_EDIT2, b);
	ip = CT2A(a.GetBuffer());
	port = _ttoi(b);
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void ConnectHostDialog::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
