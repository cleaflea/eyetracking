#pragma once
#include "cv.h"
#include "highgui.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <core/core.hpp>
#include <highgui.h>
#include<stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

//#include "eyeTracking_v_1.h"
#include "CustomDialog.h"

using namespace cv;

static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
static const char* cascade_name = "./source/haarcascade_eye_tree_eyeglasses.xml";

// typedef unsigned int UINT;

// CUIThread

class CUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIThread)

public:
	CUIThread();
	//CUIThread(CustomDialog* _dlg);           // 动态创建所使用的受保护的构造函数
	virtual ~CUIThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	const char* CString2ConstChar(CString str);
	void detect_and_draw(IplImage* img);
	void setDlg(CDialog* _dlg);

	void detectEyeOnly(IplImage *img);  

	float min(float width, float height);
	void drawEllipseContours(CvSeq *contours, IplImage *img, const int px, const int py, int flag);
	float isRightEllipse(CvBox2D box);

	void startWorking();
	int Run();

	CvSeq* cannyContoursEye(IplImage *img);

	IplImage* image;
	CvCapture* pCapture;
	//CeyeTracking_v_1Dlg* dlg;
	IplImage* getImage();
	CDialog* cDlg;
	int eyePosX;
	int eyePosY;

	int eyeAnotherPosX;
	int eyeAnotherPosY;

	int eyeCenterPosX;
	int eyeCenterPosY;

	IplImage* leftEyeImage;
	IplImage* rightEyeImage;

	IplImage* leftEyeContoursImage;
	IplImage* rightEyeContoursImage;

	CvSeq* leftEyeContours;
	CvSeq* rightEyeContours;

	const char* cascade_name2;
	CvHaarClassifierCascade* cascade_e;
protected:
	DECLARE_MESSAGE_MAP()
};


