#pragma once


// WireDialog 对话框

class WireDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WireDialog)

public:
	WireDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WireDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WireInput };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString  str1;
	CString  str2;
	CString  str3;
	CString  str4;
};
