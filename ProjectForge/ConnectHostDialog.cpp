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
END_MESSAGE_MAP()


// ConnectHostDialog 消息处理程序
