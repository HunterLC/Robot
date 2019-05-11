// WanderDialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2016112384刘畅03.h"
#include "WanderDialog.h"
#include "afxdialogex.h"


// WanderDialog 对话框

IMPLEMENT_DYNAMIC(WanderDialog, CDialogEx)

WanderDialog::WanderDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Wdialog, pParent)
{

}

WanderDialog::~WanderDialog()
{
}

void WanderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WanderDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &WanderDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// WanderDialog 消息处理程序


void WanderDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	GetDlgItem(IDC_CenterX)->GetWindowTextW(str1);
	GetDlgItem(IDC_CenterY)->GetWindowTextW(str2);
	GetDlgItem(IDC_CenterZ)->GetWindowTextW(str3);
}
