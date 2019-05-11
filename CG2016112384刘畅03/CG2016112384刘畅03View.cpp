
// CG2016112384刘畅03View.cpp: CCG2016112384刘畅03View 类的实现
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2016112384刘畅03.h"
#endif

#include "CG2016112384刘畅03Doc.h"
#include "CG2016112384刘畅03View.h"
#include <math.h>
#include <cmath>
#include "WireDialog.h"
#include "PerspectiveDiialog.h"
#include "WanderDialog.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
//初始化旋转角度
static int m_rebot = 0; //机器人整体旋转角0

static int head_rangle = 0;		//头的旋转角为0

static int thigh_right = 0, thigh_left = 0;	//初始化左右大腿的旋转角为0
static int shank_right = 0, shank_left = 0;	//初始化左右小腿的旋转角为0
static int foot_right = 0, foot_left = 0; //初始化左右脚的旋转角为0

static int shoulder_right = 0, shoulder_left = 0;	//初始化左右肩膀的旋转角为0
static int elbow_right = 0, elbow_left = 0;	//初始化左右手肘的旋转角为0
static int palm_right = 0, palm_left = 0;	//初始化左右手掌的旋转角为0

static int finger1_right = 0, finger1_left = 0;	//初始化左右手指1关节的旋转角为0
static int finger2_right = 0, finger2_left = 0; //初始化左右手指2关节的旋转角为0
static int finger3_right = 0, finger3_left = 0; //初始化左右手指3关节的旋转角为0

 //glLookAt 机器人观察角度
static float eyex = 0, eyey = 0, eyez = 5;  //相机
static float centerx = 0, centery = 0, centerz = 0;
static float upx = 0, upy = 1.0, upz = 0;
static float flvy = 10,aspect = 1,zNear = 1,zFar = 100;  //透视设置
static int m_mode = 0;			//初始化绘制模式为框架模式
static int p_mode = 0;          //初始化透视模式
static double scale_x = 2, scale_y = 2, scale_z = 1;
static double translate_x = 0, translate_y = 0, translate_z = 0;
// CCG2016112384刘畅03View

IMPLEMENT_DYNCREATE(CCG2016112384刘畅03View, CScrollView)

BEGIN_MESSAGE_MAP(CCG2016112384刘畅03View, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_Basic, &CCG2016112384刘畅03View::OnBasic)
	ON_COMMAND(ID_Torus, &CCG2016112384刘畅03View::OnTorus)
	ON_COMMAND(ID_Wire, &CCG2016112384刘畅03View::OnWire)
	ON_COMMAND(ID_Solid, &CCG2016112384刘畅03View::OnSolid)
	ON_BN_CLICKED(IDOK, &CCG2016112384刘畅03View::OnBnClickedOk)
	ON_BN_CLICKED(IDOK, &CCG2016112384刘畅03View::OnWireClickedOk)
	ON_COMMAND(IDOK, &CCG2016112384刘畅03View::OnIdok)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_WireRobot, &CCG2016112384刘畅03View::OnWireRobot)
	ON_COMMAND(ID_SolidRobot, &CCG2016112384刘畅03View::OnSolidRobot)
	ON_COMMAND(ID_Perspective1, &CCG2016112384刘畅03View::OnPerspective1)
	ON_COMMAND(ID_Perspective2, &CCG2016112384刘畅03View::OnPerspective2)
	ON_COMMAND(32791, &CCG2016112384刘畅03View::OnWander)
END_MESSAGE_MAP()

// CCG2016112384刘畅03View 构造/析构

CCG2016112384刘畅03View::CCG2016112384刘畅03View() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2016112384刘畅03View::~CCG2016112384刘畅03View()
{
}

BOOL CCG2016112384刘畅03View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//设置窗口类型
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CScrollView::PreCreateWindow(cs);
}

// CCG2016112384刘畅03View 绘图

void CCG2016112384刘畅03View::OnDraw(CDC* /*pDC*/)
{
	CCG2016112384刘畅03Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//绘制场景，自定义的一个绘制函数，如绘制三维模型或其他三维场景。
	RenderScene(); //视图中要显示的三维场景的绘制代码写在 RenderScene()中或通过 RenderScene()调用。
}

BOOL CCG2016112384刘畅03View::Basic()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存 
	glPushMatrix();
	glPointSize(5.0);//点的宽度，缺省为1

	glBegin(GL_POINTS); //绘制点
	glColor3f(1.0, 1.0, 0.0); //当前颜色
	//OpenGl中设置颜色，一般可以使用glColor3f()。参数应该有三个，类型是float型的。另外一点是它的参数值的范围是[0.0, 1.0]
	glVertex2f(-0.9, 0.96);//顶点坐标
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	//Color4f,红、绿、蓝、不透明度，值域均为[0, 1]
	glVertex2d(-0.98, 0.98);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex2d(-0.95, 0.95);
	glEnd();

	glBegin(GL_LINES);	//多组双顶点线段
	glColor3f(1.0, 0.0, 1.0);
	glVertex2d(1, 0);
	glVertex2d(0, 1);
	glColor3f(1.0, 0.5, 0.0); //当前颜色
	glVertex2d(0, 1);
	glVertex2d(0, -1);
	glColor3f(0.5, 0.5, 0.0); //当前颜色
	glVertex2d(0, -1);
	glVertex2d(1, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);	//不闭合折线
	glColor3f(0, 0.6, 0.8);
	glVertex2d(0.6, 0.9);
	glVertex2d(0.5, -0.5);
	glVertex2d(0.2, 0.3);
	glVertex2d(0.4, 0.6);
	glEnd();

	/*glBegin(GL_LINE_STRIP);	//不闭合折线
	glColor3f(0, 0.6, 0.8);
	glVertex2d(-0.3, 1);
	glVertex2d(-0.3, -1);

	glEnd();
	glBegin(GL_POINTS);	//不闭合折线
	glColor3f(0, 0.6, 0.8);
	glutWireTorus(0.5, 0.1, 30, 100);
	glEnd();*/

	glBegin(GL_LINE_LOOP);	//闭合折线
	glColor3f(0.85, 0.8, 0.8);
	glVertex2d(-0.98, 0.9);
	glVertex2d(-0.96, 0.88);
	glVertex2d(-0.9, 0.92);
	glVertex2d(-0.85, 0.85);
	glEnd();

	glBegin(GL_POLYGON);	//单个简单填充凸多边形
	glColor3f(0.4, 0.0, 0.0);
	glVertex2d(-0.2, 0.95);
	glVertex2d(-0.3, 0.9);
	glVertex2d(-0.2, 0.8);
	glVertex2d(-0.4, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);//多组独立填充三角形
	glColor3f(0.4, 0.5, 0.3);
	glVertex2d(-0.2, -0.3);
	glVertex2d(-0.4, -0.2);
	glVertex2d(-0.3, -0.3);
	glEnd();

	glBegin(GL_QUADS);//多组独立填充四边形
	glColor3f(0.5, 0.7, 0.1);
	glVertex2d(-0.87, 0.83);
	glVertex2d(-0.84, 0.75);
	glVertex2d(-0.8, 0.8);
	glVertex2d(-0.85, 0.84);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串
	glColor3f(0.7, 1, 1);
	glVertex2d(-0.78, 0.8);
	glVertex2d(-0.7, 0.9);
	glVertex2d(-0.69, 0.84);
	glVertex2d(-0.69, 0.77);
	glVertex2d(-0.7, 0.7);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);//三角条带
	glColor3f(0.6, 0.2, 0.4);
	glVertex2d(-0.65, 0.8);
	glVertex2d(-0.62, 0.71);
	glColor3f(0.1, 0.2, 0.8);
	glVertex2d(-0.58, 0.82);
	glColor3f(0.2, 0.7, 0.3);
	glVertex2d(-0.52, 0.74);
	glVertex2d(-0.44, 0.79);
	glEnd();


	glBegin(GL_QUAD_STRIP);//四边形条带
	glColor3f(1, 0.4, 0.8);
	glVertex2d(-0.98, 0.7);
	glVertex2d(-0.95, 0.6);
	glVertex2d(-0.85, 0.72);
	glVertex2d(-0.82, 0.57);
	glVertex2d(-0.8, 0.7);
	glVertex2d(-0.75, 0.6);
	glEnd();

	glPopMatrix();
	SwapBuffers(m_pDC->GetSafeHdc()); //双缓存
	return TRUE;
}

//参数是圆环体半径、圆环体段半径、圆环体段侧面数、圆环体段数
BOOL CCG2016112384刘畅03View::wireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存 
	glPushMatrix();

	double sideDelta = 2.0 *  M_PI/ nsides;
	double ringDelta = 2.0 * M_PI / rings;
	double theta = 0;
	double cosTheta = 1.0;
	double sinTheta = 0.0;

	double phi, sinPhi, cosPhi;
	double dist;
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < rings; i++)
	{
		double theta1 = theta + ringDelta;
		double cosTheta1 = cos(theta1);
		double sinTheta1 = sin(theta1);

		glBegin(GL_LINE_STRIP);
		phi = 0;
		for (int j = 0; j <= nsides; j++)
		{
			phi = phi + sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = innerRadius + (outerRadius * cosPhi);

			glNormal3f(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);
			glColor3f(cosTheta, sinTheta, sinPhi);
			glVertex3f(cosTheta * dist, sinTheta * dist, outerRadius * sinPhi);

			glNormal3f(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);
			glColor3f(cosTheta1, sinTheta1, sinPhi);
			glVertex3f(cosTheta1 * dist, sinTheta1 * dist, outerRadius * sinPhi);
		}
		glEnd();
		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}

	glPopMatrix();
	SwapBuffers(m_pDC->GetSafeHdc()); //双缓存
	return TRUE;
}

//参数 innerRadius 表示圆环体半径，outerRadius 表示圆环体段半径，nsides表示圆环体段的侧面数，rings 表示圆环体段数
BOOL CCG2016112384刘畅03View::solidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存 
	glPushMatrix();

	double sideDelta = 2.0 * M_PI / nsides;
	double ringDelta = 2.0 * M_PI / rings;
	double theta = 0;
	double cosTheta = 1.0;
	double sinTheta = 0.0;
	double phi, sinPhi, cosPhi;
	double dist;
	glColor3f(1.00f, 0.0f, 0.0f);

	for (int i = 0; i < rings; i++)
	{
		double theta1 = theta + ringDelta;
		double cosTheta1 = cos(theta1);
		double sinTheta1 = sin(theta1);

		glBegin(GL_QUAD_STRIP);
		phi = 0;
		for (int j = 0; j <= nsides; j++)
		{
			phi = phi + sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = innerRadius + (outerRadius * cosPhi);

			glNormal3d(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);
			glColor3f(cosTheta, sinTheta, sinPhi);
			glVertex3d(cosTheta * dist, sinTheta * dist, outerRadius * sinPhi);

			glNormal3d(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);
			glColor3f(cosTheta1, sinTheta1, sinPhi);
			glVertex3d(cosTheta1 * dist, sinTheta1 * dist, outerRadius * sinPhi);
		}
		glEnd();
		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;

	}
	glPopMatrix();
	SwapBuffers(m_pDC->GetSafeHdc()); //双缓存
	return TRUE;
}

void CCG2016112384刘畅03View::RenderScene(void)
{
	//调用 OpenGL 绘图函数进行图形绘制
//根据需要自行修改，也可在派生类中重载此函数
//本例中以绘制一个三棱柱
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存
	glPushMatrix();
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存  
	glLoadIdentity();

	/*视点转换
		函数原型
		void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy, GLdouble upz);
	    该函数定义一个视图矩阵，并与当前矩阵相乘。
		第一组eyex, eyey, eyez 相机在世界坐标的位置
		第二组centerx, centery, centerz 相机镜头对准的物体在世界坐标的位置
		第三组upx, upy, upz 相机向上的方向在世界坐标中的方向
		你把相机想象成为你自己的脑袋：
		第一组数据就是脑袋的位置
		第二组数据就是眼睛看的物体的位置
		第三组就是头顶朝向的方向（因为你可以歪着头看同一个物体）。
	*/
	//选择模式
	if (p_mode == 0)  //透视模式
	{
		gluPerspective(flvy,aspect,zNear,zFar);
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	}
	else //非透视模式
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	glPushMatrix();//整个图形左移
	glTranslatef(translate_x, translate_y, translate_z);
	glScalef(scale_x, scale_y, scale_z);
	glTranslatef(0, 0, -2);
	glRotatef((GLfloat)m_rebot, 0.0, 1.0, 0.0);	//绕y轴旋转
	//glRotatef((GLfloat)90, 0.0, 1.0, 0.0);	//绕y轴旋转

	//头
	glPushMatrix();
	glRotatef((GLfloat)head_rangle, 0.0, 1.0, 0.0);
	glTranslatef(-0.05, 1, 0);
	drawhead();
	//身体
	glPopMatrix();
	glTranslatef(-0.05, 1.2, 0);
	drawbody();
	glPushMatrix();

	glTranslatef(0.4, -1.7, 0);
	glRotatef((GLfloat)thigh_left, 0.0, 0.0, 1.0);
	drawthigh();//左大腿

	glTranslatef(-0.4, -0.8, 0);
	glRotatef((GLfloat)shank_left, 1.0, 0.0, 0.0);
	drawshank();//左小腿

	glTranslatef(-0.05, -0.35, 0);
	glRotatef((GLfloat)foot_left, 1.0, 0.0, 0.0);
	drawfoot();//左脚

	//为右腿定位准备
	glPopMatrix();
	glPushMatrix();	
	glTranslatef(0.95, -1.7, 0);
	glRotatef((GLfloat)thigh_right, 0.0, 0.0, 1.0);
	drawthigh();//右大腿

	glTranslatef(-0.4, -0.8, 0);
	glRotatef((GLfloat)shank_right, 1.0, 0.0, 0.0);
	drawshank();//右小腿

	glTranslatef(-0.05, -0.35, 0);
	glRotatef((GLfloat)foot_right, 1.0, 0.0, 0.0);
	drawfoot();//右脚

	//左手
	//为左手定位
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.72, 0.8, 0);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(-90, 0, 0, 1);
	//上臂绕肩关节旋转
	glRotatef((GLfloat)shoulder_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	drawshoulder();

	//下臂绕肘关节旋转
	glTranslatef(1.0, 0.3, 0.0);
	glRotatef((GLfloat)elbow_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.3, 0.0);
	drawelbow();

	//手掌绕腕关节旋转
	glTranslatef(1.0, 0.3, 0.0);
	glRotatef((GLfloat)palm_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.2, 0.0);
	drawpalm();

	//所有手指相对于手掌定位
	glPushMatrix();//为中指定位准备

	//大拇指
	glTranslatef(1.0, 0.2, 0);
	glRotatef((GLfloat)finger1_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, 0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glPopMatrix();
	glPushMatrix();//为中指定位准备

	//食指
	glTranslatef(1.0, 0.2, -0.3);
	glRotatef((GLfloat)finger1_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, 0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_left, 0.0, 0.0, 1.0);
	glTranslatef(1, -0.10, 0.0);
	drawforefinger();

	//中指
	glPopMatrix();
	glPushMatrix();	//为中指定位准备

	glTranslatef(1.0, 0.2, 0.0);
	glRotatef((GLfloat)finger1_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, 0.0);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_left, 0.0, 0.0, 1.0);
	glTranslatef(1, -0.10, 0.0);
	drawforefinger();

	//无名指
	glPopMatrix();
	glPushMatrix();	//为无名指定位准备
	glTranslatef(1.0, 0.2, 0.35);
	glRotatef((GLfloat)finger1_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, -0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.10, 0.0);
	drawforefinger();

	//小指
	glPopMatrix();
	glPushMatrix();	//为小指定位准备
	glTranslatef(1.0, 0.2, 0);
	glRotatef((GLfloat)finger1_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, -0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_left, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.10, 0.0);
	drawforefinger();

	//右手
	//为右手定位
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.72, 0.8, 0);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(-90, 0, 0, 1);
	//上臂绕肩关节旋转
	glRotatef((GLfloat)shoulder_right, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	drawshoulder();

	//下臂绕肘关节旋转
	glTranslatef(1.0, 0.3, 0.0);
	glRotatef((GLfloat)elbow_right, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.3, 0.0);
	drawelbow();

	//手掌绕腕关节旋转
	glTranslatef(1.0, 0.3, 0.0);
	glRotatef((GLfloat)palm_right, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.2, 0.0);
	drawpalm();

	//所有手指相对于手掌定位
	glPushMatrix();//为中指定位准备

	//大拇指
	glTranslatef(1.0, 0.2, 0);
	glRotatef((GLfloat)finger1_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, 0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glPopMatrix();
	glPushMatrix();//为中指定位准备

	//食指
	glTranslatef(1.0, 0.2, -0.3);
	glRotatef((GLfloat)finger1_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, 0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_right, 0.0, 0.0, 1.0);
	glTranslatef(1, -0.10, 0.0);
	drawforefinger();

	//中指
	glPopMatrix();
	glPushMatrix();	//为中指定位准备

	glTranslatef(1.0, 0.2, 0.0);
	glRotatef((GLfloat)finger1_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, 0.0);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_right, 0.0, 0.0, 1.0);
	glTranslatef(1, -0.10, 0.0);
	drawforefinger();

	//无名指
	glPopMatrix();
	glPushMatrix();	//为无名指定位准备
	glTranslatef(1.0, 0.2, 0.35);
	glRotatef((GLfloat)finger1_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, -0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_right, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.10, 0.0);
	drawforefinger();

	//小指
	glPopMatrix();
	glPushMatrix();	//为小指定位准备
	glTranslatef(1.0, 0.2, 0);
	glRotatef((GLfloat)finger1_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.2, -0.75);
	drawforefinger();

	glTranslatef(0.5, 0.15, 0.0);
	glRotatef((GLfloat)finger2_right, 0.0, 0.0, 1.0);
	glTranslatef(0.5, -0.15, 0.0);
	drawforefinger();

	glTranslatef(0.0, 0.10, 0.0);
	glRotatef((GLfloat)finger3_right, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.10, 0.0);
	drawforefinger();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//glutSwapBuffers();
	/*glFlush();*/
	SwapBuffers(m_pDC->GetSafeHdc()); //双缓存交换
	
	
}

BOOL CCG2016112384刘畅03View::SetupPixelFormat(void)
{
	PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR), // pfd 结构的大小
	1, // 版本号
	PFD_DRAW_TO_WINDOW | // 支持在窗口中绘图
	PFD_SUPPORT_OPENGL | // 支持 OpenGL
	PFD_DOUBLEBUFFER, // 双缓存模式
	PFD_TYPE_RGBA, // RGBA 颜色模式
	24, // 24 位颜色深度
	0, 0, 0, 0, 0, 0, // 忽略颜色位
	0, // 没有非透明度缓存
	0, // 忽略移位位
	0, // 无累加缓存
	0, 0, 0, 0, // 忽略累加位
	32, // 32 位深度缓存
	0, // 无模板缓存
	0, // 无辅助缓存
	PFD_MAIN_PLANE, // 主层
	0, // 保留
	0, 0, 0 // 忽略层,可见性和损毁掩模
	};
	int iPixelFormat;
	// 为设备描述表得到最匹配的像素格式
	if ((iPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox(_T("ChoosePixelFormat Failed"), NULL, MB_OK);
		return FALSE;
	}
	// 设置最匹配的像素格式为当前的像素格式
	if (SetPixelFormat(m_pDC->GetSafeHdc(), iPixelFormat, &pfd) == FALSE)
	{
		MessageBox(_T("SetPixelFormat Failed"), NULL, MB_OK);
		return FALSE;
	}
	if (pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();//设置逻辑调色板
	return TRUE;
}
void CCG2016112384刘畅03View::SetLogicalPalette(void)
{
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	} logicalPalette = { 0x300, 256 };
	BYTE reds[] = { 0, 36, 72, 109, 145, 182, 218, 255 };
	BYTE greens[] = { 0, 36, 72, 109, 145, 182, 218, 255 };
	BYTE blues[] = { 0, 85, 170, 255 };
	for (int colorNum = 0; colorNum < 256; ++colorNum)
	{
		logicalPalette.aEntries[colorNum].peRed =
			reds[colorNum & 0x07];
		logicalPalette.aEntries[colorNum].peGreen =
			greens[(colorNum >> 0x03) & 0x07];
		logicalPalette.aEntries[colorNum].peBlue =
			blues[(colorNum >> 0x06) & 0x03];
		logicalPalette.aEntries[colorNum].peFlags = 0;
	}
	m_hPalette = CreatePalette((LOGPALETTE*)& logicalPalette);
}

void CCG2016112384刘畅03View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CCG2016112384刘畅03View 打印

BOOL CCG2016112384刘畅03View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCG2016112384刘畅03View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCG2016112384刘畅03View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCG2016112384刘畅03View 诊断

#ifdef _DEBUG
void CCG2016112384刘畅03View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCG2016112384刘畅03View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCG2016112384刘畅03Doc* CCG2016112384刘畅03View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2016112384刘畅03Doc)));
	return (CCG2016112384刘畅03Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG2016112384刘畅03View 消息处理程序


int CCG2016112384刘畅03View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//初始化 OpenGL
	m_pDC = new CClientDC(this);
	if (!SetupPixelFormat())
		return -1;
	m_hGLRC = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hGLRC);

	return 0;
}


void CCG2016112384刘畅03View::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//删除调色板、渲染上下文
	::wglMakeCurrent(NULL, NULL);
	::wglDeleteContext(m_hGLRC);
	if (m_hPalette)
		DeleteObject(m_hPalette);
	if (m_pDC)
		delete m_pDC;
}


void CCG2016112384刘畅03View::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//添加窗口缩放是的视口变换
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (cx < cy)
		glOrtho(-10.0, 100.0, -10.0 * (GLfloat)cy / (GLfloat)cx, 10.0 * (GLfloat)cy / (GLfloat)cx, -100.0, 100.0);
	else
		glOrtho(-10.0 * (GLfloat)cx / (GLfloat)cy, 10.0 * (GLfloat)cx / (GLfloat)cy, -10.0, 10.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(translate_x, translate_y, translate_z);
	glLoadIdentity();
}


void CCG2016112384刘畅03View::OnBasic()
{
	// TODO: 在此添加命令处理程序代码
	Basic();
}


void CCG2016112384刘畅03View::OnTorus()
{
	// TODO: 在此添加命令处理程序代码
	RenderScene(); //视图中要显示的三维场景的绘制代码写在 RenderScene()中或通过 RenderScene()调用。
}


void CCG2016112384刘畅03View::OnWire()
{
	// TODO: 在此添加命令处理程序代码
	/*CWireDlg* dlg = new CWireDlg;
	dlg->Create(IDD_WireInput, NULL);
	dlg->ShowWindow(SW_SHOW);*/
	WireDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		wireTorus(GLdouble(_ttof(dlg.str1)), GLdouble(_ttof(dlg.str2)), GLint(_ttoi(dlg.str3)), GLint(_ttoi(dlg.str4)));
	}
	
}


void CCG2016112384刘畅03View::OnSolid()
{
	// TODO: 在此添加命令处理程序代码
	WireDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		solidTorus(GLdouble(_ttof(dlg.str1)), GLdouble(_ttof(dlg.str2)), GLint(_ttoi(dlg.str3)), GLint(_ttoi(dlg.str4)));
	}
}


void CCG2016112384刘畅03View::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	CString  str1 = E_innerRadius;
	CString  str2 = E_outerRadius;
	CString  str3 = E_nsides;
	CString  str4 = E_rings;
	wireTorus(GLdouble(_ttof(str1)), GLdouble(_ttof(str2)), GLint(_ttoi(str3)), GLint(_ttoi(str4)));*/
}


void CCG2016112384刘畅03View::OnWireClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  str1;
	CString  str2;
	CString  str3;
	CString  str4;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str1);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(str2);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(str3);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(str4);
	wireTorus(GLdouble(_ttof(str1)), GLdouble(_ttof(str2)), GLint(_ttoi(str3)), GLint(_ttoi(str4)));
}


void CCG2016112384刘畅03View::OnIdok()
{
	// TODO: 在此添加命令处理程序代码

	
}


void CCG2016112384刘畅03View::init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void CCG2016112384刘畅03View::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow_left, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void CCG2016112384刘畅03View::SolidCube()//着色单位立方体
{
	GLfloat color[6][3] = //顶点颜色
	{ {1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{1.0f,1.0f,0.0f},{1.0f,0.0f,1.0f},{0.0f,1.0f,1.0f} };
	int i;
	point v_up[5] = { {-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,0.5,-0.5} };//上底面
	point v_down[5] = { {-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,-0.5,-0.5} };//下底面
	glBegin(GL_POLYGON);//下底面
	glNormal3f(0, -0.5, 0);//法向量，从上往下看 
	for (i = 0; i <= 4; i++)
	{
		glColor3fv(color[i % 6]);
		glVertex3f(v_down[i].x, v_down[i].y, v_down[i].z);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//侧面用四边形画
	for (i = 0; i <= 4; i++)
	{
		glColor3fv(color[(i + 1) % 6]);
		glVertex3f(v_up[i].x, v_up[i].y, v_up[i].z);
		glColor3fv(color[(4 - i) % 6]);
		glVertex3f(v_down[i].x, v_down[i].y, v_down[i].z);
	}
	glEnd();
	glBegin(GL_POLYGON); //上底面
	glNormal3f(0, 0.5, 0);
	for (i = 0; i <= 4; i++)
	{
		glColor3fv(color[(6 - i) % 6]);
		glVertex3f(v_up[i].x, v_up[i].y, v_up[i].z);
	}
	glEnd();
}

void CCG2016112384刘畅03View::LineCube()
{
	point v_up[5] = { {-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,0.5,-0.5} };//上底面回路
	point v_down[5] = { {-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,-0.5,-0.5} };//下底面回路
	int i;
	glBegin(GL_LINE_STRIP);//上底面
	for (i = 0; i <= 4; i++)
		glVertex3f(v_up[i].x, v_up[i].y, v_up[i].z);
	glEnd();
	glBegin(GL_LINE_STRIP);//下底面
	for (i = 0; i <= 4; i++)
		glVertex3f(v_down[i].x, v_down[i].y, v_down[i].z);
	glEnd();
	glBegin(GL_LINES);//侧面四条线
	for (i = 0; i < 4; i++)
	{
		glVertex3f(v_up[i].x, v_up[i].y, v_up[i].z);
		glVertex3f(v_down[i].x, v_down[i].y, v_down[i].z);
	}
	glEnd();
}


//画肩膀
void CCG2016112384刘畅03View::drawshoulder()
{
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);	//缩放倍数
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画肘部
void CCG2016112384刘畅03View::drawelbow()
{
	glPushMatrix();
	glScalef(2.0, 0.4, 2.0);
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画手掌
void CCG2016112384刘畅03View::drawpalm()
{
	glPushMatrix();
	glScalef(2.0, 0.4, 2.0);
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画手指
void CCG2016112384刘畅03View::drawforefinger()
{
	glPushMatrix();
	glScalef(1.0, 0.4, 0.2);
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画头部
void CCG2016112384刘畅03View::drawhead()
{
	glPushMatrix();
	glTranslatef(0, 1.4, 0);
	if (m_mode == 0)
		glutWireSphere(0.4f, 15, 15);
	else
	{
		glColor3f(0.0, 1.0, 0.0);
		//glutSolidSphere(0.4f, 15, 15);
		glutWireSphere(0.4f, 15, 15);
		glColor3f(1, 1, 1);
	}
	glPopMatrix();
}
//画身体
void CCG2016112384刘畅03View::drawbody()
{
	glPushMatrix();
	glScalef(1.3, 1.6, 1.2);
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画大腿
void CCG2016112384刘畅03View::drawthigh()
{
	glPushMatrix();
	glScalef(0.4, 1, 0.4);
	glTranslatef(-1.7, 0.4, 0.1);
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画小腿
void CCG2016112384刘畅03View::drawshank()
{
	glPushMatrix();
	glScalef(0.4, 0.8, 0.4);
	glTranslatef(-0.7, 0.4, 0.1);
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}
//画脚
void CCG2016112384刘畅03View::drawfoot()
{
	glPushMatrix();
	glScalef(0.5, 0.3, 0.7);//缩放
	glTranslatef(-0.5, 0.3, 0.3);//位置
	if (m_mode == 0)
		LineCube();
	else
		SolidCube();
	glPopMatrix();
}

BOOL CCG2016112384刘畅03View::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CScrollView::OnCommand(wParam, lParam);
}


void CCG2016112384刘畅03View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{

	//右手相关
	case 'Q':
		shoulder_right = (shoulder_right + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'A':
		shoulder_right = (shoulder_right - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'W':
		elbow_right = (elbow_right + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'S':
		elbow_right = (elbow_right - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'E':
		palm_right = (palm_right + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'D':
		palm_right = (palm_right - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'R':
		eyex = eyex + 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'F':
		eyex = eyex - 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'T':
		eyey = eyey + 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'G':
		eyey = eyey - 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'Y':
		eyez = eyez + 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'H':
		eyez = eyez - 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	//左手相关
	case 'U':
		shoulder_left = (shoulder_left + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'J':
		shoulder_left = (shoulder_left - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'I':
		elbow_left = (elbow_left + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'K':
		elbow_left = (elbow_left - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'O':
		palm_left = (palm_left + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'L':
		palm_left = (palm_left - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'Z':
		upx = upx + 0.1;
		if (upx > 1)
			upx = -1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'X':
		upx = upx - 0.1;
		if (upx < -1)
			upx = 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'C':
		upy = upy + 0.1;
		if (upy > 1)
			upy = -1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'V':
		upy = upy - 0.1;
		if (upy < -1)
			upy = 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'B':
		upz = upz + 0.1;
		if (upz > 1)
			upz = -1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case 'N':
		upz = upz - 0.1;
		if (upz < -1)
			upz = 1;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '1':
		thigh_right = (thigh_right + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '2':
		thigh_right = (thigh_right - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '0':
		flvy = flvy + 5;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '3':
		thigh_left = (thigh_left + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '4':
		thigh_left = (thigh_left - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '9':
		flvy = flvy - 5;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '5':
		head_rangle = (head_rangle + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '6':
		head_rangle = (head_rangle - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '7':
		m_rebot = (m_rebot + 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	case '8':
		m_rebot = (m_rebot - 5) % 360;
		this->Invalidate(TRUE);
		this->UpdateWindow();
		break;
	default:
		break;
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CCG2016112384刘畅03View::OnWireRobot()
{
	// TODO: 在此添加命令处理程序代码
	m_mode = 0;
	OnDraw(m_pDC);
}


void CCG2016112384刘畅03View::OnSolidRobot()
{
	// TODO: 在此添加命令处理程序代码
	m_mode = 1;
	OnDraw(m_pDC);
}


void CCG2016112384刘畅03View::OnPerspective1()
{
	// TODO: 在此添加命令处理程序代码
	PerspectiveDiialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		p_mode = 0;  //设置透视模式
		aspect = _ttof(dlg.str1);
		zNear = _ttof(dlg.str2);
		zFar = _ttof(dlg.str3);
	}
	OnDraw(m_pDC);
}


void CCG2016112384刘畅03View::OnPerspective2()
{
	// TODO: 在此添加命令处理程序代码
	p_mode = 1;  //设置透视模式
	OnDraw(m_pDC);
}


void CCG2016112384刘畅03View::OnWander()
{
	// TODO: 在此添加命令处理程序代码
	WanderDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		p_mode = 0;  //设置透视模式
		centerx = _ttof(dlg.str1);
		centery = _ttof(dlg.str2);
		centerz = _ttof(dlg.str3);
	}
	OnDraw(m_pDC);
}
