/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



/////////////////////////////////////////////////
//测试滚动条ScrollBar////////////////////////////
#if 0

BOOL CALLBACK MyEventHScroll(HELE hEle,HELE hEventEle,int pos)
{
	XTRACE("当前位置:%d\n",pos);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,280,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建水平滚动条
	HELE hHScrollBar=XSBar_Create(10,100,200,18,SY_HSCROLL,hWindow);
	XSBar_SetScrollRange(hHScrollBar,20); //设置滚动范围
//	XSBar_ScrollPos(hHScrollBar,10); //滚动到指定位置

	//创建垂直滚动条
//	HELE hVScrollBar=XSBar_Create(250,10,18,200,SY_VSCROLL,hWindow);

	//XSBar_SetImage(hHScrollBar,L"image/123.jpg");
	//XSBar_EnableImageStretch(hHScrollBar,TRUE);

	//XSBar_SetImageLeaveUp(hHScrollBar,L"image/123.jpg");

	//注册事件
	XEle_RegisterEvent(hHScrollBar,XE_VSCROLL,MyEventHScroll);
	XRunXCGUI();
	return 0;
}
#endif


#if 0
//修改水平滚动条为垂直滚动条
int  bHorizon=TRUE;
HELE hHScrollBar=NULL;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(bHorizon)
	{
		bHorizon=FALSE;
		XSBar_SetHorizon(hHScrollBar,FALSE);
	}else
	{
		bHorizon=TRUE;
		XSBar_SetHorizon(hHScrollBar,TRUE);
	}
	XEle_RedrawEle(hHScrollBar);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,280,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建水平滚动条
	hHScrollBar=XSBar_Create(10,10,200,200,SY_HSCROLL,hWindow);
	XSBar_SetScrollRange(hHScrollBar,100); //设置滚动范围
	XSBar_ScrollPos(hHScrollBar,10);   //滚动到指定位置

	HELE hButton=XBtn_Create(220,10,100,22,L"改变",hWindow);

	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XRunXCGUI();
	return 0;
}
#endif
