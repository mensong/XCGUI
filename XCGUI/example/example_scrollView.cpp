/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0
/////////////////////////////////////////////////
//测试滚动视图 ScrollView////////////////////////

BOOL CALLBACK MyEventHScrollView(HELE hEle,HELE hEventEle,int pos)
{
	XTRACE("视图水平滚动,位置:%d\n",pos);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,500,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建滚动视图
	//HELE hScrollView=XSView_Create(10,10,200,200,hWindow);

	HELE hScrollView=XSView_Create(10,10,100,100,hWindow);
	RECT rect={10,10,300,300};
	XEle_SetRect(hScrollView,&rect);
	XSView_SetSize(hScrollView,500,500); //设置滚动视图内容大小

	//XSView_SetBorderColor(hScrollView,RGB(255,0,0));

	//在滚动视图内容放置一个按钮,以便看见滚动效果
	HELE hView=XSView_GetView(hScrollView);
	HELE hButtn=XBtn_Create(10,150,100,100,L"button",hView);

	XEle_RegisterEvent(hScrollView,XE_HSCROLLVIEW,MyEventHScrollView);
	XRunXCGUI();

	return 0;
}
#endif