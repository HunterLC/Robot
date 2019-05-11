#pragma once


// PerspectiveDiialog 对话框

class PerspectiveDiialog : public CDialogEx
{
	DECLARE_DYNAMIC(PerspectiveDiialog)

public:
	PerspectiveDiialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PerspectiveDiialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Pdialog };
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
