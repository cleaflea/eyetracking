
// eyeTracking_v_1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include "cv.h"
#include "highgui.h"
// #include "G:/opencv/CvvImage/CvvImage.h"

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



#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CeyeTracking_v_1App:
// �йش����ʵ�֣������ eyeTracking_v_1.cpp
//

class CeyeTracking_v_1App : public CWinApp
{
public:
	CeyeTracking_v_1App();
	IplImage* image;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CeyeTracking_v_1App theApp;