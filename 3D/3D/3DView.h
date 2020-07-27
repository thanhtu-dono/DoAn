
// 3DView.h : interface of the My3DView class
//

#pragma once
#include "3DDoc.h"
#include "include/GL/glut.h"
#include "include/GL/GL.H"
#include "include/GL/GLU.H"
//#include "include/glui.h"
#include "include/GL/GLAux.h"

class My3DView : public CView
{
protected: // create from serialization only
	My3DView() noexcept;
	DECLARE_DYNCREATE(My3DView)

// Attributes
public:
	My3DDoc* GetDocument() const;
	HGLRC m_hglrc;
	//Biến này để lưu ngữ cảnh thiết bị để tô bóng
	//void Init();
	void HeToaDo(CDC* pDC);
	//Hàm vẽ hệ toạ độ
	void DrawCube(CDC* pDC); //, CPoint StartPoint, CPoint EndPoint, COLORREF
	void DrawSphere(CDC* pDC);
	void DrawTeaPot(CDC* pDC);
// Operations
public:
	bool is_draw_cube;
	bool is_draw_sphere;
	bool is_draw_teapot;
	void set_draw_sphere(bool is_draw_) { is_draw_sphere = is_draw_; };
	void set_draw_teapot(bool is_draw_) { is_draw_teapot = is_draw_; };
	void set_draw_cube(bool is_draw_) { is_draw_cube = is_draw_; };
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~My3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in 3DView.cpp
inline My3DDoc* My3DView::GetDocument() const
   { return reinterpret_cast<My3DDoc*>(m_pDocument); }
#endif

