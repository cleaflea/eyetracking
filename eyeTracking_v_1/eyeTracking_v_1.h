
// eyeTracking_v_1.h : PROJECT_NAME 应用程序的主头文件
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
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CeyeTracking_v_1App:
// 有关此类的实现，请参阅 eyeTracking_v_1.cpp
//

class CeyeTracking_v_1App : public CWinApp
{
public:
	CeyeTracking_v_1App();
	IplImage* image;

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CeyeTracking_v_1App theApp;