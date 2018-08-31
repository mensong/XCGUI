/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/////////////////////////////////////////////////
/////滑动条//////////////////////////////////////

#if 0
//滑动条事件
BOOL CALLBACK MyEventSliderChange(HELE hEle,HELE hEventEle,int pos)
{
	XTRACE("pos=%d\n",pos);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//创建滑动条
	HELE hSlider=XSliderBar_Create(10,10,200,9,TRUE,hWindow);
	XSliderBar_SetRange(hSlider,100); //设置滑动范围
	//XEle_SetBkColor(hSlider,RGB(200,200,200));
	//XSliderBar_SetRange(hSlider2,100); //设置滑动范围
	XSliderBar_SetPos(hSlider,0); //设置滑动范围

	XSliderBar_SetImage(hSlider,XImage_LoadFile(L"Image/sliderBar1.jpg"));
	//XSliderBar_SetImage2(hSlider,XImage_LoadFile(L"Image/sliderBar2.jpg"));
	XSliderBar_SetImage2(hSlider,XImage_LoadFile(L"Image/tt2.jpg"));
	//XSliderBar_EnableImageStretch(hSlider,TRUE);

	HELE hButton=XSliderBar_GetButton(hSlider);

	XSliderBar_SetButtonWidth(hSlider,50);
	//XEle_ShowEle(hButton,FALSE);
	XEle_RegisterEvent(hSlider,XE_SLIDER_CHANGE,MyEventSliderChange);
	XRunXCGUI();
	return 0;
}
#endif

#if 0
//滑动条事件
BOOL CALLBACK MyEventSliderChange(HELE hEle,HELE hEventEle,int pos)
{
	XTRACE("pos=%d\n",pos);
	return TRUE;
}
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//创建滑动条
	HELE hSlider=XSliderBar_Create(10,10,20,100,FALSE,hWindow);
	XSliderBar_SetRange(hSlider,100); //设置滑动范围

	XSliderBar_SetPos(hSlider,30); //设置位置

	XSliderBar_SetImage(hSlider,XImage_LoadFile(L"Image/bkimageBar.jpg"));
	XSliderBar_SetImage2(hSlider,XImage_LoadFile(L"Image/222.jpg"));

//	HELE hButton=XSliderBar_GetButton(hSlider);

	XEle_RegisterEvent(hSlider,XE_SLIDER_CHANGE,MyEventSliderChange);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//修改水平为垂直
int  bHorizon=TRUE;
HELE hSlider=NULL;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(bHorizon)
	{
		bHorizon=FALSE;
		XSliderBar_SetHorizon(hSlider,FALSE);
	}else
	{
		bHorizon=TRUE;
		XSliderBar_SetHorizon(hSlider,TRUE);
	}
	XEle_RedrawEle(hSlider);
	return FALSE;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建滑动条
	hSlider=XSliderBar_Create(10,10,100,9,TRUE,hWindow);
	XSliderBar_SetRange(hSlider,100); //设置滑动范围

	HELE hButton=XBtn_Create(120,10,100,22,L"改变",hWindow);
	//XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XRunXCGUI();
	return 0;
}
#endif


#if 0
//媒体播放器演示
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	XWnd_CloseWindow(XEle_GetHWindow(hEle));
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,310,186,L"炫彩界面库-窗口",NULL,XC_SY_ROUND | XC_SY_CENTER);
	XWnd_SetImage(hWindow,XImage_LoadFile(L"image2\\player_skin.bmp"));

	XWnd_EnableDragWindow(hWindow,TRUE);
	XWnd_ShowWindow(hWindow,SW_SHOW);


	//创建滑动条
	HELE hSlider=XSliderBar_Create(12,119,288,11,TRUE,hWindow);
	XSliderBar_SetRange(hSlider,100); //设置滑动范围
	XSliderBar_SetPos(hSlider,30);
	XSliderBar_SetImage(hSlider,XImage_LoadFile(L"image2\\sliderBar_bk.bmp"));
	XSliderBar_SetImage2(hSlider,XImage_LoadFile(L"image2\\progress_fill.bmp"));

	HELE hButton=XSliderBar_GetButton(hSlider);
	XBtn_SetImageLeave(hButton,XImage_LoadFile(L"image2\\progress_leave.bmp"));
	XBtn_SetImageStay(hButton,XImage_LoadFile(L"image2\\progress_stay.bmp"));
	XBtn_SetImageDown(hButton,XImage_LoadFile(L"image2\\progress_stay.bmp"));

	HELE hStop=XBtn_Create(10,136,35,35,NULL,hWindow);
	XBtn_SetImageLeave(hStop,XImage_LoadFile(L"image2\\stop_leave.bmp"));
	XBtn_SetImageStay(hStop,XImage_LoadFile(L"image2\\stop_stay.bmp"));
	XBtn_SetImageDown(hStop,XImage_LoadFile(L"image2\\stop_down.bmp"));
	XEle_EnableFocus(hStop,FALSE);


	HELE hPrev=XBtn_Create(53,136,35,35,NULL,hWindow);
	XBtn_SetImageLeave(hPrev,XImage_LoadFile(L"image2\\prev_leave.bmp"));
	XBtn_SetImageStay(hPrev,XImage_LoadFile(L"image2\\prev_stay.bmp"));
	XBtn_SetImageDown(hPrev,XImage_LoadFile(L"image2\\prev_down.bmp"));
	XEle_EnableFocus(hPrev,FALSE);


	HELE hPlay=XBtn_Create(96,130,50,50,NULL,hWindow);
	XBtn_SetImageLeave(hPlay,XImage_LoadFile(L"image2\\play_leave.bmp"));
	XBtn_SetImageStay(hPlay,XImage_LoadFile(L"image2\\play_stay.bmp"));
	XBtn_SetImageDown(hPlay,XImage_LoadFile(L"image2\\play_down.bmp"));
	XEle_EnableFocus(hPlay,FALSE);

	HELE hNext=XBtn_Create(154,136,35,35,NULL,hWindow);
	XBtn_SetImageLeave(hNext,XImage_LoadFile(L"image2\\next_leave.bmp"));
	XBtn_SetImageStay(hNext,XImage_LoadFile(L"image2\\next_stay.bmp"));
	XBtn_SetImageDown(hNext,XImage_LoadFile(L"image2\\next_down.bmp"));
	XEle_EnableFocus(hNext,FALSE);

	HELE hOpen=XBtn_Create(197,136,35,35,NULL,hWindow);
	XBtn_SetImageLeave(hOpen,XImage_LoadFile(L"image2\\open_leave.bmp"));
	XBtn_SetImageStay(hOpen,XImage_LoadFile(L"image2\\open_stay.bmp"));
	XBtn_SetImageDown(hOpen,XImage_LoadFile(L"image2\\open_down.bmp"));
	XEle_EnableFocus(hOpen,FALSE);

	HELE hBrowser=XBtn_Create(238,134,64,21,NULL,hWindow);
	XBtn_SetImageLeave(hBrowser,XImage_LoadFile(L"image2\\browser_leave.bmp"));
	XBtn_SetImageStay(hBrowser,XImage_LoadFile(L"image2\\browser_stay.bmp"));
	XBtn_SetImageDown(hBrowser,XImage_LoadFile(L"image2\\browser_down.bmp"));
	XEle_EnableFocus(hBrowser,FALSE);

	HELE hSliderAudio=XSliderBar_Create(207,78,89,9,TRUE,hWindow);
	XSliderBar_SetRange(hSliderAudio,100); //设置滑动范围
	XSliderBar_SetPos(hSliderAudio,50);
	XSliderBar_SetImage(hSliderAudio,XImage_LoadFile(L"image2\\progressAudio_bk.bmp"));
	XSliderBar_SetImage2(hSliderAudio,XImage_LoadFile(L"image2\\progressAudio_prog.bmp"));
	XSliderBar_SetButtonWidth(hSliderAudio,9);
	hButton=XSliderBar_GetButton(hSliderAudio);
	XEle_SetBkTransparent(hButton,TRUE);
	XBtn_SetImageLeave(hButton,XImage_LoadFile(L"image2\\thumb_leave.png"));
	XBtn_SetImageStay(hButton,XImage_LoadFile(L"image2\\thumb_stay.png"));
	XBtn_SetImageDown(hButton,XImage_LoadFile(L"image2\\thumb_stay.png"));


	HELE hMute=XBtn_Create(188,78,16,14,NULL,hWindow);
	XBtn_SetImageLeave(hMute,XImage_LoadFile(L"image2\\mute_leave.bmp"));
	XBtn_SetImageStay(hMute,XImage_LoadFile(L"image2\\mute_stay.bmp"));
	XBtn_SetImageDown(hMute,XImage_LoadFile(L"image2\\mute_down.bmp"));
	XEle_EnableFocus(hMute,FALSE);


	HELE hClose=XBtn_Create(285,6,17,15,NULL,hWindow);
	XBtn_SetImageLeave(hClose,XImage_LoadFile(L"image2\\close_leave.bmp"));
	XBtn_SetImageStay(hClose,XImage_LoadFile(L"image2\\close_stay.bmp"));
	XBtn_SetImageDown(hClose,XImage_LoadFile(L"image2\\close_down.bmp"));
	XEle_EnableFocus(hClose,FALSE);
	XEle_RegisterEvent(hClose,XE_BNCLICK,MyEventBtnClick);


	HELE hPic=XPic_Create(8,6,16,16,hWindow);
	XEle_SetBkTransparent(hPic,TRUE);
	XPic_SetImage(hPic,XImage_LoadFile(L"image2\\player.ico"));

	HELE hStatic=XStatic_Create(28,6,175,15,L"Media Player - 炫彩界面库演示",hWindow);
	XEle_SetBkTransparent(hStatic,TRUE);
	XEle_SetTextColor(hStatic,RGB(255,255,255));

	XRunXCGUI();
	return 0;
}
#endif