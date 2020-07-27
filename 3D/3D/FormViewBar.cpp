// FormViewBar.cpp : implementation file
//

#include "pch.h"
#include "3D.h"
#include "3DView.h"
#include "FormViewBar.h"


// FormViewBar

IMPLEMENT_DYNCREATE(FormViewBar, CFormView)

FormViewBar::FormViewBar()
	: CFormView(IDD_FORMVIEW)
{
	//is_draw_ = false;
	is_cube_ = false;
	is_sphere_ = false;
	is_teapot_ = false;
}

FormViewBar::~FormViewBar()
{
}

void FormViewBar::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(FormViewBar, CFormView)
	ON_BN_CLICKED(IDC_CHECK_CUBE, &FormViewBar::OnBnClickedCheckCube)
	ON_BN_CLICKED(IDC_CHECK_SPHERE, &FormViewBar::OnBnClickedCheckSphere)
	ON_BN_CLICKED(IDC_CHECK_TEAPOT, &FormViewBar::OnBnClickedCheckTeapot)
END_MESSAGE_MAP()


// FormViewBar diagnostics

#ifdef _DEBUG
void FormViewBar::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FormViewBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// FormViewBar message handlers
My3DView* FormViewBar::GetAppView()
{
	My3DApp *pApp = (My3DApp*)AfxGetApp();
	MainFrame *pMainFrame = (MainFrame*)pApp->m_pMainWnd;
	My3DView *pView = pMainFrame->GetMainView();
	return pView;
}

void FormViewBar::OnBnClickedCheckCube()
{
	// TODO: Add your control notification handler code here
	is_cube_ = !is_cube_;
	if (GetAppView() != NULL)
	{
		GetAppView()->set_draw_cube(is_cube_);
		GetAppView()->Invalidate();
	}
}


void FormViewBar::OnBnClickedCheckSphere()
{
	// TODO: Add your control notification handler code here
	is_sphere_ = !is_sphere_;
	if (GetAppView() != NULL)
	{
		GetAppView()->set_draw_sphere(is_sphere_);
		GetAppView()->Invalidate();
	}
}


void FormViewBar::OnBnClickedCheckTeapot()
{
	// TODO: Add your control notification handler code here
	is_teapot_ = !is_teapot_;
	if (GetAppView() != NULL)
	{
		GetAppView()->set_draw_teapot(is_teapot_);
		GetAppView()->Invalidate();
	}
}
