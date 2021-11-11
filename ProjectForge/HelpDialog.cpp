// HelpDialog.cpp: 实现文件
//

#include "pch.h"
#include "HelpDialog.h"
#include "afxdialogex.h"


// HelpDialog 对话框

IMPLEMENT_DYNAMIC(HelpDialog, CDialogEx)

HelpDialog::HelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(HELP_DIALOG, pParent)
{

}

HelpDialog::~HelpDialog()
{
}

void HelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDialog, CDialogEx)
END_MESSAGE_MAP()


// HelpDialog 消息处理程序
