// CustomDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eyeTracking_v_1.h"
#include "CustomDialog.h"
#include "afxdialogex.h"


// CustomDialog �Ի���

IMPLEMENT_DYNAMIC(CustomDialog, CDialog)

CustomDialog::CustomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CustomDialog::IDD, pParent)
{

	//  m_PosX = _T("");
	//  m_PosX = _T("");
	//  m_PosY = _T("");
	//  m_PosX = _T("");
	//  m_PosY = _T("");
	this->rect = cvRect(0, 0, OFFSETX, OFFSETY);
	this->eyeCenterPosX = 350;
	this->eyeCenterPosY = 170;
// 	mapPicPath = "./image/map.jpg";
// 	mapPicPath = "./image/save.jpg";
	mapPicPath = "./image/newmap.jpg";
	realImage = cvLoadImage(mapPicPath);
}

CustomDialog::~CustomDialog()
{
}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_POSX, m_PosX);
	//  DDX_Control(pDX, IDC_POSY, m_PosY);
	//  DDX_Text(pDX, IDC_POSY, m_PosX);
	//  DDX_Text(pDX, IDC_POSX, m_PosX);
	//  DDX_Text(pDX, IDC_POSY, m_PosY);
	//  DDX_Control(pDX, IDC_POSX, m_PosX);
	//  DDX_Control(pDX, IDC_POSY, m_PosY);
	//  DDX_Text(pDX, IDC_POSX, m_PosX);
	//  DDX_Control(pDX, IDC_POSY, m_PosY);
	//  DDX_Control(pDX, IDC_POSY, m_PosY);
	//  DDX_Text(pDX, IDC_POSY, m_PosY);
	DDX_Control(pDX, IDC_POSX, m_PosX);
	DDX_Control(pDX, IDC_POSY, m_PosY);
}


BEGIN_MESSAGE_MAP(CustomDialog, CDialog)
	ON_BN_CLICKED(IDC_CLEABTN, &CustomDialog::OnBnClickedCleabtn)
	ON_BN_CLICKED(IDC_SUBIMAGEBTN, &CustomDialog::OnBnClickedSubimagebtn)
	ON_BN_CLICKED(IDC_UPBTN, &CustomDialog::OnBnClickedUpbtn)
	ON_BN_CLICKED(IDC_DOWNBTN, &CustomDialog::OnBnClickedDownbtn)
	ON_BN_CLICKED(IDC_LEFTBTN, &CustomDialog::OnBnClickedLeftbtn)
	ON_BN_CLICKED(IDC_INITBTN, &CustomDialog::OnBnClickedInitbtn)
	ON_BN_CLICKED(IDOK, &CustomDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CustomDialog ��Ϣ�������
void CustomDialog::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC =	GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img); // ����ͼƬ
	cimg.DrawToHDC(hDC, &rect); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	cimg.Destroy();
	ReleaseDC(pDC);
}

void CustomDialog::OnBnClickedCleabtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CUIThread* pThread = new CUIThread();
	pThread->setDlg(this);
	pThread->CreateThread();

// 	ActionThread* aThread = new ActionThread();
// 	aThread->setDlg(this);
// 	aThread->setSample(pThread);
// 	aThread->CreateThread();
	//pThread->startWorking();
}

void CustomDialog::movePicLeft(){
// 	IplImage* realImage = cvLoadImage("./image/result.jpg");
// 	rect.x -= 10;
	rect.x -= MOVESTEP;
	if(this->rect.x<0){
		this->rect.x = 0;
	}
	cvSetImageROI(realImage, this->rect);
	IplImage* subImage = cvCreateImage(cvSize(this->rect.width, this->rect.height), realImage->depth, realImage->nChannels);
	cvCopy(realImage, subImage);
	cvResetImageROI(realImage);
	this->DrawPicToHDC(subImage, IDC_RIGHTPIC);
}

void CustomDialog::movePicRight(){
// 	IplImage* realImage = cvLoadImage("./image/result.jpg");
// 	rect.x += 10;
	rect.x += MOVESTEP;
	if(this->rect.x>realImage->width-OFFSETX){
		this->rect.x = realImage->width-OFFSETX;
	}
	cvSetImageROI(realImage, this->rect);
	IplImage* subImage = cvCreateImage(cvSize(this->rect.width, this->rect.height), realImage->depth, realImage->nChannels);
	cvCopy(realImage, subImage);
	cvResetImageROI(realImage);
	this->DrawPicToHDC(subImage, IDC_RIGHTPIC);
}

void CustomDialog::movePicUp(){
// 	IplImage* realImage = cvLoadImage("./image/result.jpg");
// 	rect.y -= 10;
	rect.y -= MOVESTEP;
	if(this->rect.y<0){
		this->rect.y = 0;
	}
	cvSetImageROI(realImage, this->rect);
	IplImage* subImage = cvCreateImage(cvSize(this->rect.width, this->rect.height), realImage->depth, realImage->nChannels);
	cvCopy(realImage, subImage);
	cvResetImageROI(realImage);
	this->DrawPicToHDC(subImage, IDC_RIGHTPIC);
}

void CustomDialog::movePicDown(){
// 	IplImage* realImage = cvLoadImage("./image/result.jpg");
// 	rect.y += 10;
	rect.y += MOVESTEP;
	if(this->rect.y>realImage->height-OFFSETY){
		this->rect.y = realImage->height-OFFSETY;
	}
	cvSetImageROI(realImage, this->rect);
	IplImage* subImage = cvCreateImage(cvSize(this->rect.width, this->rect.height), realImage->depth, realImage->nChannels);
	cvCopy(realImage, subImage);
	cvResetImageROI(realImage);
	this->DrawPicToHDC(subImage, IDC_RIGHTPIC);
}

void CustomDialog::alert(){
	CString* alertStr = new CString("cascade can not create");
	MessageBox(*alertStr);
}

void CustomDialog::OnBnClickedSubimagebtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->movePicRight();
	
}


void CustomDialog::OnBnClickedUpbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->movePicUp();
}


void CustomDialog::OnBnClickedDownbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->movePicDown();
}


void CustomDialog::OnBnClickedLeftbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->movePicLeft();
	
}


void CustomDialog::OnBnClickedInitbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage* beforeImage = cvLoadImage("./image/map.jpg");
	CvSize newSize = cvSize(2733, 2000);
	IplImage* afterImage = cvCreateImage(newSize, beforeImage->depth, beforeImage->nChannels);
	cvResize(beforeImage, afterImage, CV_INTER_CUBIC);
	cvSaveImage("./image/save.jpg", afterImage);
}


void CustomDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
