#pragma once

#include "UIThread.h"
#include "CustomDialog.h"
#include "ActionThread.h"

// ActionThread

class ActionThread : public CWinThread
{
	DECLARE_DYNCREATE(ActionThread)

public:
	ActionThread();           // 动态创建所使用的受保护的构造函数
	virtual ~ActionThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int Run();
	void setDlg(CDialog* _cDlg);
	void setSample(CWinThread* _sampleThread);

	CWinThread* sampleThread;
	CDialog* cDlg;

	int centerPosX;
	int centerPosY;

};


