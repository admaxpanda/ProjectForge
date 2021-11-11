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
END_MESSAGE_MAP()


// CreateHostDialog 消息处理程序
