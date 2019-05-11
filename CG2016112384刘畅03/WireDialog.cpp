// WireDialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2016112384刘畅03.h"
#include "WireDialog.h"
#include "afxdialogex.h"


// WireDialog 对话框

IMPLEMENT_DYNAMIC(WireDialog, CDialogEx)

WireDialog::WireDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WireInput, pParent)
{

}

WireDialog::~WireDialog()
{
}

void WireDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WireDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &WireDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// WireDialog 消息处理程序


void WireDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str1);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(str2);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(str3);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(str4);
}
