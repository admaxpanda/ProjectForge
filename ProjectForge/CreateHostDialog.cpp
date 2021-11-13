// CreateHostDialog.cpp: 实现文件
//

#include "pch.h"
#include "CreateHostDialog.h"
#include "afxdialogex.h"


// CreateHostDialog 对话框

IMPLEMENT_DYNAMIC(CreateHostDialog, CDialogEx)

CreateHostDialog::CreateHostDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CREATE_HOST_DIALOG, pParent)
{

}

CreateHostDialog::~CreateHostDialog()
{
}

void CreateHostDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateHostDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CreateHostDialog::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CreateHostDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CreateHostDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &CreateHostDialog::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CreateHostDialog 消息处理程序


void CreateHostDialog::OnEnChangeEdit1()
{
	
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}


void CreateHostDialog::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT1, ip);
	GetDlgItemText(IDC_EDIT2, port);
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CreateHostDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CreateHostDialog::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
