#pragma once


// CustomDialog 对话框

#include "UIThread.h"
// #include "G:/opencv/CvvImage/CvvImage.h"
// #include "./source/CvvImage.h"
#include "CvvImage.h"
#include "ActionThread.h"

#define OFFSETX 333
#define OFFSETY 333
#define MOVESTEP 100
#define EYEOFFSETX 33
#define EYEOFFSETY 33

static IplImage* realImage;
static const char* mapPicPath;

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CustomDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CustomDialog();

// 对话框数据
	enum { IDD = IDD_CUSTOMDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCleabtn();
	void DrawPicToHDC(IplImage *img, UINT ID);
//	CEdit m_PosX;
//	CEdit m_PosY;
//	CString m_PosX;
//	CString m_PosX;
//	CString m_PosY;
//	CEdit m_PosX;
//	CEdit m_PosY;
//	CString m_PosX;
//	CEdit m_PosY;
//	CEdit m_PosY;
//	CString m_PosY;

	CvRect rect;

	CEdit m_PosX;
	CEdit m_PosY;
	afx_msg void OnBnClickedSubimagebtn();
	afx_msg void OnBnClickedUpbtn();
	afx_msg void OnBnClickedDownbtn();
	afx_msg void OnBnClickedLeftbtn();

	int eyeCenterPosX;
	int eyeCenterPosY;

	void movePicLeft();
	void movePicRight();
	void movePicUp();
	void movePicDown();
	void alert();
	afx_msg void OnBnClickedInitbtn();
	afx_msg void OnBnClickedOk();
};
