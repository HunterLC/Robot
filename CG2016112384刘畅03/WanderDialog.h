#pragma once


// WanderDialog 对话框

class WanderDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WanderDialog)

public:
	WanderDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WanderDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Wdialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString  str1;
	CString  str2;
	CString  str3;
};
