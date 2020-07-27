#pragma once

#include "3D.h"
#include "3DView.h"
#include "MainFrm.h"
#include "FormViewBar.h"

// FormViewBar form view

class FormViewBar : public CFormView
{
	DECLARE_DYNCREATE(FormViewBar)

protected:
	FormViewBar();           // protected constructor used by dynamic creation
	virtual ~FormViewBar();
public:
	bool is_cube_;
	bool is_sphere_;
	bool is_teapot_;
	My3DView* FormViewBar::GetAppView();
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckCube();
	afx_msg void OnBnClickedCheckSphere();
	afx_msg void OnBnClickedCheckTeapot();
};


