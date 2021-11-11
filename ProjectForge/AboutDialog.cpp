// AboutDialog.cpp: 实现文件
//

#include "pch.h"
#include "AboutDialog.h"
#include "afxdialogex.h"


// AboutDialog 对话框

IMPLEMENT_DYNAMIC(AboutDialog, CDialogEx)

AboutDialog::AboutDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ABOUT_DIALOG, pParent)
{

}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDialog, CDialogEx)
END_MESSAGE_MAP()


// AboutDialog 消息处理程序
