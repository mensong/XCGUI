/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0

//void SSLWnd_Init(char *SS);
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//SSLWnd_Init("4326-5807-DFC7-FF3A-A54D-6DF2-F6CE-6E6C");

	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,500,L"炫彩界面库-窗口");

	//HWINDOW hWindow=XWnd_CreateWindowEx(NULL,L"XCGUI",L"炫彩界面库-窗口",WS_POPUP,10,10,200,200,NULL);

	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hOutlook=XOutlook_Create(10,10,200,300,hWindow);

	HELE hView=XEle_Create(10,10,100,100);
	XOutlook_AddView(hOutlook,hView,L"1111");
	XEle_SetBkColor(hView,RGB(255,0,0));

	HELE hView2=XEle_Create(10,10,100,100);
	XOutlook_AddView(hOutlook,hView2,L"2222");
	XEle_SetBkColor(hView2,RGB(200,0,0));

	HELE hView3=XEle_Create(10,10,100,100);
	XOutlook_AddView(hOutlook,hView3,L"3333");
	XEle_SetBkColor(hView3,RGB(100,0,0));

	XRunXCGUI();
	return 0;
}

#endif