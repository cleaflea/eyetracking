// ActionThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eyeTracking_v_1.h"
#include "ActionThread.h"


// ActionThread

IMPLEMENT_DYNCREATE(ActionThread, CWinThread)

ActionThread::ActionThread()
{
}

ActionThread::~ActionThread()
{
}

BOOL ActionThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

void ActionThread::setDlg(CDialog* _cDlg){
	this->cDlg = _cDlg;
}

void ActionThread::setSample(CWinThread* _sampleThread){
	this->sampleThread = _sampleThread;
}

int ActionThread::Run(){
	while (1)
	{
// 		centerPosX = ((CUIThread*)sampleThread)->eyeCenterPosX;
// 		centerPosY = ((CUIThread*)sampleThread)->eyeCenterPosY;
		centerPosX = ((CustomDialog*)cDlg)->eyeCenterPosX;
		centerPosY = ((CustomDialog*)cDlg)->eyeCenterPosY;

		if(centerPosX > 400){
			((CustomDialog*)this->cDlg)->movePicRight();
		}

		if(centerPosX < 300){
			((CustomDialog*)this->cDlg)->movePicLeft();
		}

		if(centerPosY > 200){
			((CustomDialog*)this->cDlg)->movePicDown();
		}

		if(centerPosY < 150){
			((CustomDialog*)this->cDlg)->movePicUp();
		}

		((CustomDialog*)this->cDlg)->SetDlgItemInt(IDC_POSX, centerPosX, 1);
		((CustomDialog*)this->cDlg)->SetDlgItemInt(IDC_POSY, centerPosY, 1);

	}
}

int ActionThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(ActionThread, CWinThread)
END_MESSAGE_MAP()


// ActionThread ��Ϣ�������
