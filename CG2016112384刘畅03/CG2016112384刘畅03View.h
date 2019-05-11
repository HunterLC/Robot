
// CG2016112384刘畅03View.h: CCG2016112384刘畅03View 类的接口
//

#pragma once

typedef struct { 
	double x, y, z; 
}point;//定义点结构

class CCG2016112384刘畅03View : public CScrollView
{
protected: // 仅从序列化创建
	CCG2016112384刘畅03View() noexcept;
	DECLARE_DYNCREATE(CCG2016112384刘畅03View)

// 特性
public:
	CCG2016112384刘畅03Doc * GetDocument() const;
	HGLRC m_hGLRC;  //OpenGL 绘制描述表
	CDC* m_pDC; //OpenGL 设备描述表
	HPALETTE m_hPalette;  //OpenGL 调色板

// 操作
public:
	

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	BOOL Basic();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void  RenderScene(void);
	BOOL  SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL wireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings);//参数是圆环体半径、圆环体段半径、圆环体段侧面数、圆环体段数
	BOOL solidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings); //参数 innerRadius 表示圆环体半径，outerRadius 表示圆环体段半径，nsides表示圆环体段的侧面数，rings 表示圆环体段数
	

// 实现
public:
	virtual ~CCG2016112384刘畅03View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBasic();
	afx_msg void OnTorus();
	afx_msg void OnWire();
	afx_msg void OnSolid();
	afx_msg void OnBnClickedOk();
	afx_msg void OnWireClickedOk();
	afx_msg void OnIdok();
	void init(void);
	void display(void);
	void SolidCube();
	void LineCube();
	void drawshoulder();
	void drawelbow();
	void drawpalm();
	void drawforefinger();
	void drawhead();
	void drawbody();
	void drawthigh();
	void drawshank();
	void drawfoot();
	
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnWireRobot();
	afx_msg void OnSolidRobot();
	afx_msg void OnPerspective1();
	afx_msg void OnPerspective2();
	afx_msg void OnWander();
};

#ifndef _DEBUG  // CG2016112384刘畅03View.cpp 中的调试版本
inline CCG2016112384刘畅03Doc* CCG2016112384刘畅03View::GetDocument() const
   { return reinterpret_cast<CCG2016112384刘畅03Doc*>(m_pDocument); }
#endif

