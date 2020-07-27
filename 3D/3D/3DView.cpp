
// 3DView.cpp : implementation of the My3DView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "3D.h"
#endif

#include "3DDoc.h"
#include "3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// My3DView

IMPLEMENT_DYNCREATE(My3DView, CView)

BEGIN_MESSAGE_MAP(My3DView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &My3DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// My3DView construction/destruction

My3DView::My3DView() noexcept
{
	// TODO: add construction code here

}

My3DView::~My3DView()
{
}

BOOL My3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// My3DView drawing

void My3DView::OnDraw(CDC* pDC)
{
	My3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//OnCreate(lpCreateStruct);
	wglMakeCurrent(pDC->m_hDC, m_hglrc);
	HeToaDo(pDC);
	if (is_draw_cube)
	{
		//Tạo ra ngữ cảnh thiết bị để tô bóng .

		
		DrawCube(pDC); //, m_StartPoint, m_EndPoint, RGB(0,0,0)
		SwapBuffers(pDC->m_hDC);
	}
	if (is_draw_sphere)
	{
		//Tạo ra ngữ cảnh thiết bị để tô bóng .


		DrawSphere(pDC); //, m_StartPoint, m_EndPoint, RGB(0,0,0)
		SwapBuffers(pDC->m_hDC);
	}
	if (is_draw_teapot)
	{
		//Tạo ra ngữ cảnh thiết bị để tô bóng .


		DrawTeaPot(pDC); //, m_StartPoint, m_EndPoint, RGB(0,0,0)
		SwapBuffers(pDC->m_hDC);
	}
	
	// TODO: add draw code for native data here
}


// My3DView printing


void My3DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL My3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void My3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void My3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void My3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void My3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// My3DView diagnostics

#ifdef _DEBUG
void My3DView::AssertValid() const
{
	CView::AssertValid();
}

void My3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

My3DDoc* My3DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(My3DDoc)));
	return (My3DDoc*)m_pDocument;
}
#endif //_DEBUG


// My3DView message handlers


int My3DView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);

	//GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	//GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	//GLfloat diff_use[] = { 0.0, 0.5, 0.0, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	//GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	//GLfloat shininess = 50.0f;
	//glMateriali(GL_FRONT, GL_SHININESS, shininess);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormat;
	CDC* pDC;
	pDC = GetDC();
	CDC* pdc;
	pdc = GetDC();
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	//Chọn và thiết lập Pixel
	iPixelFormat = ChoosePixelFormat(pdc->m_hDC, &pfd);
	SetPixelFormat(pdc->m_hDC, iPixelFormat, &pfd);
	//Tạo ngữ cảnh thiết bị tô bóng RC
	m_hglrc = wglCreateContext(pdc->m_hDC);
	ReleaseDC(pDC);
	
	return 0;
}
void My3DView::HeToaDo(CDC* pDc)
{
	glEnable(GL_LIGHT0);
	//Tạo ra các chùm tối , sáng để tạo sự tương phản
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Xoá khung đệm, màu của màn hình ứng dụng sẽ từ trắng sang đen .
	glEnable(GL_COLOR_MATERIAL);
	//Sẽ làm cho chức năng tô màu cho vật thể có hiệu lực với màu được định nghĩa ở 

	//dưới glColor4d
	glViewport(0, 0, 100, 100);
	//Tạo góc quan sát vật thể
	glLoadIdentity();
	glColor4d(0.0, 0.0, 1.0, 1.0);
	//Tạo màu cho nét vẽ
	//Tiến hành quay đối tượng
	glRotated(10.0, 1.0, 0.0, 0.0); //Quay quanh trục X
	glRotated(30.0, 0.0, 1.0, 0.0); //Quay quanh trục Y
	glRotated(-10.0, 0.0, 0.0, 1.0); //Quay quanh trục Z

	//glTranslatef(0.0, 0.0, -5.0);

	glBegin(GL_LINES); //Tiến hành vẽ đường thẳng .
	//Mọi công việc vẽ đều nằm trong cấu trúc glBegin( ) ->glEnd( );
	//Vẽ trục toạ độ
	glVertex3f(0, 0, 0);// Di chuyển tới điểm gốc 0 để vẽ
	glVertex3f(0, 0, 1);  //Vẽ trục Z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1.0, 0); //Vẽ trục Y
	glVertex3f(0, 0, 0);
	glVertex3f(1.0, 0, 0); //Vẽ trục X
	//Vẽ các mũi tên chỉ hướng
	glVertex3f(1, 0, 0);
	glVertex3f(0.8, 0.1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0.8, -0.1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0.8, 0, 0.1);
	glVertex3f(0, 1, 0);
	glVertex3f(-0.1, 0.8, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0.1, 0.8, 0);
	glEnd();

	glFlush();

}

void My3DView::DrawCube(CDC* pDC) //, CPoint StartPoint, CPoint EndPoint, COLORREF
{
	glViewport(500, 50, 400, 400); //Đặt góc nhìn
	//glViewport(500, 50, 400, 400);
	glLoadIdentity();
	glClear(GL_UNSIGNED_INT);
	GLfloat light[4] = { -10.0F,20.0F,100.0F,0.0F };
	/*Tham số đầu là độ tương phản giữa mặt bên trái và mặt trước
	 Tham số thứ 2 là độ tương phản giữa mặt bên trái và mặt trên
	 Tham số thứ 3 là độ tương phản giữa mặt trên và mặt trước
	 Tham số thứ 3 là độ tương phản giữa mặt trước và các mặt còn lại*/
	glColor4d(0.7, 0.2, 0.5, 1.0); //Tạo màu cho đối tượng
	glRotated(30.0, 0.0, 1.0, 0.0); //Quay đối tượng 30 độ quanh trục Y
	glRotated(45.0, 1.0, 0.0, 0.0); //quay đối tượng 15 độ quanh trục X

	//glTranslatef(0.0, 0.0, 20.0);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light);
	//Chiếu sáng lên đối tượng bằng chùm sáng light
	glEnable(GL_COLOR_MATERIAL);// Thiết lập chế độ tô màu cho bề mặt

	glBegin(GL_QUADS); //Vẽ khối hộp
	glNormal3d(88.0, -5666.0, 0.0);
	glVertex3d(0.5, -0.5, 0.5);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(0.5, -0.5, -0.5);

	glNormal3d(2.0, 99.0, -88.0);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(0.5, -0.5, -0.5);

	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d(0.5, -0.5, -0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, -0.5, 0.5);

	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, -0.5, 0.5);

	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glVertex3d(-0.5, -0.5, -0.5);
	glNormal3d(0.0, 1.0, 0.0);

	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(-0.5, 0.5, -0.5);

	glEnd();
	glFlush();
	wglMakeCurrent(NULL, NULL);

}

void My3DView::DrawSphere(CDC* pDC)
{
	glViewport(500, 50, 400, 400); //Đặt góc nhìn
	//glViewport(500, 50, 400, 400);
	glLoadIdentity();
	glClear(GL_UNSIGNED_INT);
	glPushMatrix();
	// vẽ Teapot trong khoảng giữa hai cmt này th nha 
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.5);
	glutWireCone(1.0, 0.2, 16, 64);
	// vẽ Teapot trong khoảng giữa hai cmt này th nha 
	glPopMatrix();
	glFlush();
	wglMakeCurrent(NULL, NULL);
}

void My3DView::DrawTeaPot(CDC* pDC)
{
	glViewport(500, 50, 400, 400); //Đặt góc nhìn
	//glViewport(500, 50, 400, 400);
	glLoadIdentity();
	glClear(GL_UNSIGNED_INT);
	glPushMatrix();
	// vẽ Teapot trong khoảng giữa hai cmt này th nha 
	glTranslatef(-2.0, 0.0, 0.0);
	glColor3f(1.0, 0.5, 0.5);
	glutWireTeapot(1.0);
	// vẽ teapot
	glPopMatrix();
	glFlush();
	wglMakeCurrent(NULL, NULL);
}
