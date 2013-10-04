// UIThread.cpp : 实现文件
//

#include "stdafx.h"
#include "eyeTracking_v_1.h"
#include "UIThread.h"


// CUIThread

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CUIThread::CUIThread(){
	this->eyePosX = 33;
	this->eyePosY = 33;

	this->eyeAnotherPosX = 33;
	this->eyeAnotherPosY = 33;

	this->eyeCenterPosX = 350;
	this->eyeCenterPosY = 170;

// 	this->cascade_e = 0;
// 	this->cascade_name2 = "G:/opencv/opencv244/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
// 	this->cascade_e = (CvHaarClassifierCascade*)cvLoad(this->cascade_name2, 0, 0, 0);
// 	assert(cascade_e != NULL);

	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);
	assert(cascade!= NULL);
	if( !cascade )
	{
		((CustomDialog*)this->cDlg)->alert();
	}
	//storage = cvCreateMemStorage(0);

}

// CUIThread::CUIThread(CustomDialog* _dlg)
// {
// 	this->cDlg = _dlg;
// }

CUIThread::~CUIThread()
{
}

void CUIThread::setDlg(CDialog* _dlg){
	this->cDlg = _dlg;
}

BOOL CUIThread::InitInstance()
{
	this->pCapture= cvCreateCameraCapture(-1);
	storage = cvCreateMemStorage(0);

	return TRUE;
}

int CUIThread::Run(){
// 	IplImage* pFrame = NULL;
// 	while(1)
// 	{
// 		pFrame=cvQueryFrame( pCapture );
// 		if(!pFrame) {
// 			break;
// 		}else{
// 			((CustomDialog*)this->cDlg)->DrawPicToHDC(pFrame, IDC_REALPIC);
// 		}
// 	}
// 
// 	cvReleaseCapture(&pCapture);

// 	ActionThread* aThread = new ActionThread();
// 	aThread->setSample(this);
// 	aThread->CreateThread();

	this->startWorking();
// 	return 1;
	return CWinThread::Run();
}

void CUIThread::startWorking(){
	while(1)
	{
		// 		((CeyeTracking_v_1App*)AfxGetApp())->image = cvQueryFrame(this->pCapture);
		this->image = cvQueryFrame(this->pCapture);
		if(!this->image)
			break;
		else{
			// 			detect_and_draw(this->image);

			// 			detect_and_draw(((CeyeTracking_v_1App*)AfxGetApp())->image);


			cvFlip(this->image, NULL, 1);
			cvLine(this->image, cvPoint(eyePosX-15, eyePosY), cvPoint(eyePosX+15, eyePosY), cvScalar(0, 0, 255));
			cvLine(this->image, cvPoint(eyePosX, eyePosY-15), cvPoint(eyePosX, eyePosY+15), cvScalar(0, 0, 255));

			cvLine(this->image, cvPoint(eyeAnotherPosX-15, eyeAnotherPosY), cvPoint(eyeAnotherPosX+15, eyeAnotherPosY), cvScalar(255, 0, 0));
			cvLine(this->image, cvPoint(eyeAnotherPosX, eyeAnotherPosY-15), cvPoint(eyeAnotherPosX, eyeAnotherPosY+15), cvScalar(255, 0, 0));

			cvLine(this->image, cvPoint(eyeCenterPosX-15, eyeCenterPosY), cvPoint(eyeCenterPosX+15, eyeCenterPosY), cvScalar(0, 255, 0));
			cvLine(this->image, cvPoint(eyeCenterPosX, eyeCenterPosY-15), cvPoint(eyeCenterPosX, eyeCenterPosY+15), cvScalar(0, 255, 0));

			cvRectangle(this->image, cvPoint(eyePosX-33, eyePosY-33), cvPoint(eyePosX+33, eyePosY+33), CV_RGB(255, 0, 0), 1, 8, 0);
			cvRectangle(this->image, cvPoint(eyeAnotherPosX-33, eyeAnotherPosY-33), cvPoint(eyeAnotherPosX+33, eyeAnotherPosY+33), CV_RGB(0, 0, 255), 1, 8, 0);

			cvEllipse(this->image, cvPoint(this->eyePosX, this->eyePosY), cvSize(20, 20), 0, 0, 360, CV_RGB(255, 0, 0), 1, CV_AA, 0);
			cvEllipse(this->image, cvPoint(this->eyeAnotherPosX, this->eyeAnotherPosY), cvSize(20, 20), 0, 0, 360, CV_RGB(0, 0, 255), 1, CV_AA, 0);
// 			cvShowImage("face", this->image);

			// 			this->image = cvCreateImage(cvGetSize(((CeyeTracking_v_1App*)AfxGetApp())->image), ((CeyeTracking_v_1App*)AfxGetApp())->image->depth, ((CeyeTracking_v_1App*)AfxGetApp())->image->nChannels);
			// 			cvCopy(((CeyeTracking_v_1App*)AfxGetApp())->image, this->image, NULL);
			// 			int coordinateX, coordinateY;


			if(eyeCenterPosX > 400){
				((CustomDialog*)this->cDlg)->movePicRight();
			}

			if(eyeCenterPosX < 300){
				((CustomDialog*)this->cDlg)->movePicLeft();
			}

			if(eyeCenterPosY > 200){
				((CustomDialog*)this->cDlg)->movePicDown();
			}

			if(eyeCenterPosY < 150){
				((CustomDialog*)this->cDlg)->movePicUp();
			}

			((CustomDialog*)this->cDlg)->SetDlgItemInt(IDC_POSX, eyeCenterPosX, 1);
			((CustomDialog*)this->cDlg)->SetDlgItemInt(IDC_POSY, eyeCenterPosY, 1);


			this->detectEyeOnly(this->image);
			((CustomDialog*)this->cDlg)->DrawPicToHDC(this->image, IDC_REALPIC);

			Sleep(33);
// 			char c=cvWaitKey(33);
// 
// 			if(c==27)break;

		}
	}

	cvReleaseCapture(&pCapture);
}

IplImage* CUIThread::getImage(){
	IplImage* temp = cvCreateImage(cvGetSize(this->image), this->image->depth, this->image->nChannels);
	//return this->image;
	cvCopy(this->image, temp, NULL);
	cvSaveImage("./image/temp.jpg", temp);
	return temp;
}

int CUIThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

const char* CUIThread::CString2ConstChar(CString str){
#ifdef UNICODE
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, str.GetBuffer(0), -1, NULL, 0, NULL, FALSE);
	char* psText;
	psText = new char[dwNum];
	if(!psText){
		delete []psText;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, str.GetBuffer(0), -1, psText, dwNum, NULL, FALSE);
	return (const char*)psText;
#else
	return (LPCTSTR)str;
#endif
}

void CUIThread::detect_and_draw(IplImage* img)
{
	static CvScalar colors[] = 
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}}
	};

	double scale = 1.3;
	IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
	IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
		cvRound (img->height/scale)),
		8, 1 );
	int i;

	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvResize(gray, small_img, CV_INTER_LINEAR);
	cvEqualizeHist( small_img, small_img );
// 	cvClearMemStorage(storage);

	if(cascade)
	{
		double t = (double)cvGetTickCount();
		CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
			1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
			cvSize(30, 30) );
		t = (double)cvGetTickCount() - t;
		printf( "detection time = %gms/n", t/((double)cvGetTickFrequency()*1000.) );
		for( i = 0; i < (faces ? faces->total : 0); i++ )
		{
			CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
		}
	}

	//cvShowImage("result", img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
}

CvSeq* CUIThread::cannyContoursEye(IplImage *img){
	if(img == NULL) {
		return NULL;
	}

// 	cvClearMemStorage(storage);
	
	CvSeq *contours = 0;

	cvSmooth( img, img, CV_GAUSSIAN, 3, 3, 0, 0 );

	cvNot( img, img );

	int threld = 40;
	cvCanny(img,img,threld,threld*3,3);   

	//cvFloodFill( gray, cvPoint(0,0), cvScalar(255,255,255));

	cvFindContours(img, storage, &contours,sizeof(CvContour),CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	if(contours > 0) {
		cvDrawContours(img, contours, cvScalarAll(255),cvScalarAll(255), 100);
	}

	return contours;
}

float CUIThread::min(float width, float height){
	if(width < height){
		return width;
	}else{
		return height;
	}
}

void CUIThread::drawEllipseContours(CvSeq *contours, IplImage *img, const int px, const int py, int flag) {
	if(contours != NULL && CV_IS_SEQ_CURVE(contours)) {
		CvBox2D box;
		CvPoint center;
		CvSize size;
		float angle;
		float e = 0.0f;

		while(contours != NULL) {
			int count = contours->total;
			double area = cvContourArea(contours);

			if(count > 6 && area >= 30) {
				box = cvFitEllipse2(contours);

				float scale = 2.0f/3;
				float temp = this->isRightEllipse(box);
				float width = min(box.size.width, box.size.height);
				float S = fabs(1 - (area / (CV_PI * powf(width/4, 2))));

				if( temp > e && S >= 0.8) {
					e = temp;

					center.x = cvRound(box.center.x*scale) + px;
					center.y = cvRound(box.center.y*scale) + py;
					size.width = cvRound(box.size.width*0.5*scale);
					size.height = cvRound(box.size.height*0.5*scale);
					angle = -1 * box.angle*scale;
				}
			}

			contours = contours->h_next;
		}


		if(e != 0.0f) {
			if(flag == 0){
				//left;
				cvEllipse(img, center, size, angle, 0, 360, CV_RGB(255, 0, 0), 1, CV_AA, 0);
			}else{
				//right;
				cvEllipse(img, center, size, angle, 0, 360, CV_RGB(0, 0, 255), 1, CV_AA, 0);
			}
		} else {

		}
	} else {

	}

// 	cvShowImage("new", img);
}

float CUIThread::isRightEllipse(CvBox2D box){
	float a = box.size.width / 2.0;
	float b = box.size.height / 2.0;
	float pi = 3.141592657;

	if(a < b) {
		float temp = a;
		a = b;
		b = temp;
	}

	float L = 2 * pi * b + 4*(a-b);
	float S = pi * a * b;
	float e = 4 * pi * S / (L*L);

	return e;

	//    if( e >= 0.8) {
	//        return true;
	//    } else {
	//        return false;
	//    }
}


void CUIThread::detectEyeOnly(IplImage *img){
    IplImage* gray = cvCreateImage(cvSize(img->width,img->height),8,1);

    cvCvtColor(img,gray, CV_BGR2GRAY);

// 	storage = cvCreateMemStorage(0);
	cvClearMemStorage(storage);

    CvSeq *eyes = cvHaarDetectObjects(gray, cascade, storage, 1.15, 3, 0, cvSize(25, 15));

    if (eyes->total != 2) {
		return;
    }

    CvRect* eye = (CvRect*)cvGetSeqElem(eyes, 0);
	CvRect* eyeAnother = (CvRect*)cvGetSeqElem(eyes, 1);

	if(eye->x < eyeAnother->x){
		cvSetImageROI(gray, cvRect(eye->x, eye->y, eye->width, eye->height));
		this->leftEyeImage = cvCreateImage(cvSize(eye->width, eye->height), IPL_DEPTH_8U, gray->nChannels);
		cvCopy(gray, this->leftEyeImage, 0);
		cvResetImageROI(gray);

		cvSetImageROI(gray, cvRect(eyeAnother->x, eyeAnother->y, eyeAnother->width, eyeAnother->height));
		this->rightEyeImage = cvCreateImage(cvSize(eyeAnother->width, eyeAnother->height), IPL_DEPTH_8U, gray->nChannels);
		cvCopy(gray, this->rightEyeImage, 0);
		cvResetImageROI(gray);

		this->leftEyeContoursImage = cvCreateImage(cvGetSize(this->leftEyeImage), this->leftEyeImage->depth, this->leftEyeImage->nChannels);
		this->rightEyeContoursImage = cvCreateImage(cvGetSize(this->rightEyeImage), this->rightEyeImage->depth, this->rightEyeImage->nChannels);
		cvCopyImage(leftEyeImage, leftEyeContoursImage, NULL);
		cvCopyImage(rightEyeImage, rightEyeContoursImage, NULL);
		this->leftEyeContours = this->cannyContoursEye(this->leftEyeContoursImage);
		this->rightEyeContours = this->cannyContoursEye(this->rightEyeContoursImage);
// 		this->drawEllipseContours(this->leftEyeContours, this->image, eye->x, eye->y, 0);
// 		this->drawEllipseContours(this->rightEyeContours, this->image, eyeAnother->x, eyeAnother->y, 1);

		eyePosX = eye->x+EYEOFFSETX;
		eyePosY = eye->y+EYEOFFSETY;

		eyeAnotherPosX = eyeAnother->x+EYEOFFSETX;
		eyeAnotherPosY = eyeAnother->y+EYEOFFSETY;
	}else{
		cvSetImageROI(gray, cvRect(eye->x, eye->y, eye->width, eye->height));
		this->rightEyeImage = cvCreateImage(cvSize(eye->width, eye->height), IPL_DEPTH_8U, gray->nChannels);
		cvCopy(gray, this->rightEyeImage, 0);
		cvResetImageROI(gray);

		cvSetImageROI(gray, cvRect(eyeAnother->x, eyeAnother->y, eyeAnother->width, eyeAnother->height));
		this->leftEyeImage = cvCreateImage(cvSize(eyeAnother->width, eyeAnother->height), IPL_DEPTH_8U, gray->nChannels);
		cvCopy(gray, this->leftEyeImage, 0);
		cvResetImageROI(gray);

		this->leftEyeContoursImage = cvCreateImage(cvGetSize(this->leftEyeImage), this->leftEyeImage->depth, this->leftEyeImage->nChannels);
		this->rightEyeContoursImage = cvCreateImage(cvGetSize(this->rightEyeImage), this->rightEyeImage->depth, this->rightEyeImage->nChannels);
		cvCopyImage(leftEyeImage, leftEyeContoursImage, NULL);
		cvCopyImage(rightEyeImage, rightEyeContoursImage, NULL);
		this->leftEyeContours = this->cannyContoursEye(this->leftEyeContoursImage);
		this->rightEyeContours = this->cannyContoursEye(this->rightEyeContoursImage);
// 		this->drawEllipseContours(this->leftEyeContours, this->image, eyeAnother->x, eyeAnother->y, 0);
// 		this->drawEllipseContours(this->rightEyeContours, this->image, eye->x, eye->y, 1);

		eyePosX = eyeAnother->x+EYEOFFSETX;
		eyePosY = eyeAnother->y+EYEOFFSETY;

		eyeAnotherPosX = eye->x+EYEOFFSETX;
		eyeAnotherPosY = eye->y+EYEOFFSETY;
	}

	((CustomDialog*)this->cDlg)->DrawPicToHDC(this->leftEyeImage, IDC_REALLEFTEYEPIC);
	((CustomDialog*)this->cDlg)->DrawPicToHDC(this->rightEyeImage, IDC_REALRIGHTEYEPIC);
	((CustomDialog*)this->cDlg)->DrawPicToHDC(this->leftEyeContoursImage, IDC_LEFTEYEPIC);
	((CustomDialog*)this->cDlg)->DrawPicToHDC(this->rightEyeContoursImage, IDC_RIGHTEYEPIC);
// 	cvShowImage("leftEyeImage", this->leftEyeImage);
// 	cvShowImage("rightEyeImage", this->rightEyeImage);
// 	cvShowImage("leftEyeContours", this->leftEyeContoursImage);
// 	cvShowImage("rightEyeContours", this->rightEyeContoursImage);

//     eye->width = 70;
//     eye->height = 50;
//     eye->y += 15;

//     cvSetImageROI(gray, cvRect(eye->x, eye->y, eye->width, eye->height));
//     IplImage *dst = cvCreateImage(cvSize(eye->width, eye->height), IPL_DEPTH_8U, gray->nChannels);
//     cvCopy(gray,dst,0);
//     cvResetImageROI(gray);

//     posX = eye->x;
//     posY = eye->y;

//     cvRectangle(gray, cvPoint(eye->x, eye->y), cvPoint(eye->x+eye->width, eye->y+eye->height), CV_RGB(255, 0, 0), 1, 8, 0);

// 	CString eye_x, eye_y;
//  	eye_x.Format(_T("x is %d"), eye->x);
//  	eye_y.Format(_T("y is %d"), eye->y);

// 	((CustomDialog*)this->cDlg)->m_PosX.SetWindowTextW((LPCTSTR)&eye->x);
// 	((CustomDialog*)this->cDlg)->m_PosY.SetWindowTextW((LPCTSTR)&eye->y);
// 	((CustomDialog*)this->cDlg)->SetDlgItemTextW(IDC_POSX, (LPCTSTR)&eye->x);
// 	((CustomDialog*)this->cDlg)->SetDlgItemTextW(IDC_POSY, (LPCTSTR)&eye->y);

	eyeCenterPosX = (eyePosX+eyeAnotherPosX)/2;
	eyeCenterPosY = (eyePosY+eyeAnotherPosY)/2;
// 	((CustomDialog*)this->cDlg)->eyeCenterPosX = (eyePosX+eyeAnotherPosX)/2;
// 	((CustomDialog*)this->cDlg)->eyeCenterPosY = (eyePosY+eyeAnotherPosY)/2;

// 	if(eyeCenterPosX > 400){
// 		((CustomDialog*)this->cDlg)->movePicRight();
// 	}
// 
// 	if(eyeCenterPosX < 300){
// 		((CustomDialog*)this->cDlg)->movePicLeft();
// 	}
// 	
// 	if(eyeCenterPosY > 200){
// 		((CustomDialog*)this->cDlg)->movePicDown();
// 	}
// 
// 	if(eyeCenterPosY < 150){
// 		((CustomDialog*)this->cDlg)->movePicUp();
// 	}
// 
// 	((CustomDialog*)this->cDlg)->SetDlgItemInt(IDC_POSX, eyeCenterPosX, 1);
// 	((CustomDialog*)this->cDlg)->SetDlgItemInt(IDC_POSY, eyeCenterPosY, 1);


// 	int heheX = eye->x+13;
// 	int heheY = eye->y+13;
// 
// 	cvLine(gray, cvPoint(heheX-10, heheY), cvPoint(heheX+10, heheY), cvScalar(0, 0, 255));
// 	cvLine(gray, cvPoint(heheX, heheY-10), cvPoint(heheX, heheY+10), cvScalar(0, 0, 255));
// 
// 	((CustomDialog*)this->cDlg)->DrawPicToHDC(gray, IDC_RIGHTPIC);

//     IplImage *dst2 = cvCreateImage(cvSize(eye->width*1.5, eye->height*1.5), IPL_DEPTH_8U, dst->nChannels);
//     cvResize(dst,dst2, CV_INTER_CUBIC);
    //cvFloodFill( dst2, cvPoint(0,0), cvScalar(255,255,255));

//     return dst2;
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
END_MESSAGE_MAP()


// CUIThread 消息处理程序
