// PerspectiveDiialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2016112384刘畅03.h"
#include "PerspectiveDiialog.h"
#include "afxdialogex.h"


// PerspectiveDiialog 对话框

IMPLEMENT_DYNAMIC(PerspectiveDiialog, CDialogEx)

PerspectiveDiialog::PerspectiveDiialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Pdialog, pParent)
{

}

PerspectiveDiialog::~PerspectiveDiialog()
{
}

void PerspectiveDiialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PerspectiveDiialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &PerspectiveDiialog::OnBnClickedOk)
END_MESSAGE_MAP()


// PerspectiveDiialog 消息处理程序


void PerspectiveDiialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	GetDlgItem(IDC_Paspect)->GetWindowTextW(str1);
	GetDlgItem(IDC_Pznear)->GetWindowTextW(str2);
	GetDlgItem(IDC_Pzfar)->GetWindowTextW(str3);
}
