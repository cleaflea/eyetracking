
// eyeTracking_v_1Dlg.h : ͷ�ļ�
//

#pragma once

// #include "G:/opencv/CvvImage/CvvImage.h"
#include "UIThread.h"

// CeyeTracking_v_1Dlg �Ի���
class CeyeTracking_v_1Dlg : public CDialogEx
{
// ����
public:
	CeyeTracking_v_1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EYETRACKING_V_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
public:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void DrawPicToHDC(IplImage *img, UINT ID);
	
	afx_msg void OnBnClickedTrackbtn();
};
