/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



/////////////月历元素/////////////////////////////////

#if 0

//月历元素事件响应
BOOL CALLBACK MyEventMonthChange(HELE hEle,HELE hEventEle,BOOL bChenge,BOOL bDownDayNum)
{
	if(bDownDayNum)
		XTRACE("第一视图");

	if(bChenge)
		XTRACE("日期改变\n");
	else
		XTRACE("日期未改变\n");

	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//创建月历元素
	HELE hMonth=XMonthCal_Create(10,10,220,200,hWindow);

	XEle_RegisterEvent(hMonth,XE_MONTHCAL_CHANGE,MyEventMonthChange);
	XRunXCGUI();
	return 0;
}
#endif

#if 0
//日期改变事件
BOOL CALLBACK MyEventDateTimeChange(HELE hEle,HELE hEventEle)
{
	XTRACE("日期改变\n");
	return false;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建日期编辑框元素
	HELE hMonth=XDateTime_Create(10,10,100,20,hWindow);
	//XEle_EnableBorder(hMonth,FALSE);

	XEle_RegisterEvent(hMonth,XE_DATETIME_CHANGE,MyEventDateTimeChange);
	XRunXCGUI();
	return 0;
}
#endif