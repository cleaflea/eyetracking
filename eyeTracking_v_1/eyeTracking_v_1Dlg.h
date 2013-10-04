
// eyeTracking_v_1Dlg.h : 头文件
//

#pragma once

// #include "G:/opencv/CvvImage/CvvImage.h"
#include "UIThread.h"

// CeyeTracking_v_1Dlg 对话框
class CeyeTracking_v_1Dlg : public CDialogEx
{
// 构造
public:
	CeyeTracking_v_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EYETRACKING_V_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
public:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void DrawPicToHDC(IplImage *img, UINT ID);
	
	afx_msg void OnBnClickedTrackbtn();
};
