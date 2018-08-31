/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


/////日期元素//////////////////////////////

#if 0

BOOL CALLBACK MyEventDateTimePopupMonthCal(HELE hEle,HELE hEventEle)
{
	XTRACE("popup \n");
	return FALSE;
}

BOOL CALLBACK MyEventDateTimeExitMonthCal(HELE hEle,HELE hEventEle)
{
	XTRACE("exit \n");
	return FALSE;
}

//日期改变事件
BOOL CALLBACK MyEventDateTimeChange(HELE hEle,HELE hEventEle)
{
	XTRACE("日期改变\n");
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建日期编辑框元素
	HELE hMonth=XDateTime_Create(10,10,100,20,hWindow);

	//XDateTime_SetImage(hMonth,XImage_LoadFile(L"image/123.jpg"));

	XEle_RegisterEvent(hMonth,XE_DATETIME_CHANGE,MyEventDateTimeChange);

	XEle_RegisterEvent(hMonth,XE_DATETIME_POPUP_MONTHCAL,MyEventDateTimePopupMonthCal);
	XEle_RegisterEvent(hMonth,XE_DATETIME_EXIT_MONTHCAL,MyEventDateTimeExitMonthCal);

	XRunXCGUI();
	return 0;
}
#endif