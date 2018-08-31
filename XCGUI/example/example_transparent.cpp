/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0

//测试透明窗口
HWINDOW hWindow=NULL;
BOOL CALLBACK OnButtonClick1(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHAPED);//启动透明窗口
	return TRUE;
}
BOOL CALLBACK OnButtonClick2(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_NO); //关闭透明窗口
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(L""); //初始化界面库
// FD8I-32NR-82N4-1HF81  934
	hWindow=XWnd_CreateWindow(0,0,282,250,L"炫彩界面库-窗口");
	XWnd_SetImageNC(hWindow,XImage_LoadFile(L"image\\bk.png")); //设置窗口背景图片
	//XWnd_EnableImageNCStretch(hWindow,TRUE);
	XWnd_SetTransparentAlpha(hWindow,255); //设置透明度

	HELE hButton1=XBtn_Create(20,20,80,22,L"启动透明",hWindow); //创建按钮
	XEle_SetBkTransparent(hButton1,TRUE);
	XEle_RegisterEvent(hButton1,XE_BNCLICK,OnButtonClick1);

	HELE hButton2=XBtn_Create(20,50,80,22,L"关闭透明",hWindow); //创建按钮
	XEle_SetBkTransparent(hButton2,TRUE);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,OnButtonClick2);

	XEdit_Create(20,80,100,20,hWindow); //创建编辑框


	HELE hTT=XBtn_Create(250,100,200,200,L"tt",hWindow);
//	XBtn_SetImageLeave(hTT,XImage_LoadFile(L"image\\ico_dsmain.png"));
//	XBtn_SetImageLeave(hTT,XImage_LoadFile(L"image\\tt2.jpg"));
//	XBtn_SetImageStay(hTT,XImage_LoadFile(L"image\\tt2.jpg"));
//	XBtn_SetImageDown(hTT,XImage_LoadFile(L"image\\tt2.jpg"));
	XEle_SetBkTransparent(hTT,TRUE);
	XEle_EnableTransparentChannel(hTT,TRUE);

	//XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHAPED);//启动透明窗口

	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口


	XRunXCGUI(); //运行

	return 0;
}
#endif 

#if 0
//测试透明阴影窗口
HWINDOW hWindow=NULL;
BOOL CALLBACK OnButtonClick1(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHADOW);//启动透明窗口,边框阴影
	return FALSE;
}
BOOL CALLBACK OnButtonClick2(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_NO); //关闭透明窗口
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //初始化界面库

	hWindow=XWnd_CreateWindow(0,0,300,300,L"炫彩界面库-窗口");
	XWnd_SetTransparentAlpha(hWindow,180); //设置透明度

	HELE hButton1=XBtn_Create(20,20,80,22,L"启动透明",hWindow); //创建按钮
	XEle_SetBkTransparent(hButton1,TRUE);
	XEle_RegisterEvent(hButton1,XE_BNCLICK,OnButtonClick1);

	HELE hButton2=XBtn_Create(20,50,80,22,L"关闭透明",hWindow); //创建按钮
	XEle_SetBkTransparent(hButton2,TRUE);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,OnButtonClick2);

	XEdit_Create(20,80,100,20,hWindow); //创建编辑框

	XWnd_ShowWindow(hWindow,SW_SHOW);  //显示窗口
	XRunXCGUI(); //运行

	return 0;
}
#endif