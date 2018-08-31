/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0
////////////进度条//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建进度条
	HELE hProgBar1=XProgBar_Create(10,10,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar1,0); //设置进度

	HELE hProgBar2=XProgBar_Create(10,50,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar2,30);

	HELE hProgBar3=XProgBar_Create(10,90,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar3,60);

	HELE hProgBar4=XProgBar_Create(10,130,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar4,100);

	HELE hProgBar5=XProgBar_Create(220,10,20,200,FALSE,hWindow);
	XProgBar_SetPos(hProgBar5,60);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//修改水平为垂直
int  bHorizon=TRUE;
HELE hProgBar=NULL;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(bHorizon)
	{
		bHorizon=FALSE;
		XProgBar_SetHorizon(hProgBar,FALSE);
	}else
	{
		bHorizon=TRUE;
		XProgBar_SetHorizon(hProgBar,TRUE);
	}
	XEle_RedrawEle(hProgBar);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建进度条
	hProgBar=XProgBar_Create(10,10,100,100,TRUE,hWindow);
	XProgBar_SetPos(hProgBar,30); //设置进度

	HELE hButton=XBtn_Create(120,10,100,22,L"改变",hWindow);
	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//水平
////////////进度条贴图//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,500,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//XWnd_SetBorderSize(hWindow,8,8,8,30);
	//创建进度条
	HELE hProgBar=XProgBar_Create(10,10,200,9,TRUE,hWindow);
//	HELE hProgBar=XProgBar_Create(10,10,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar,60); //设置进度

	XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/sliderBar1.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/sliderBar2.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt2.jpg"));

	//XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/bkimageBar.jpg"));
	//XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/222.jpg"));
	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt.png"));

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//垂直
////////////进度条贴图//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,500,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//XWnd_SetBorderSize(hWindow,8,8,8,30);
	//创建进度条
	HELE hProgBar=XProgBar_Create(10,10,20,300,FALSE,hWindow);
//	HELE hProgBar=XProgBar_Create(10,10,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar,60); //设置进度

//	XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/sliderBar1.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/sliderBar2.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt2.jpg"));

	XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/bkimageBar.jpg"));
	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/222.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt.png"));

	XRunXCGUI();
	return 0;
}
#endif