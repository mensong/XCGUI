/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

//弹出日历选择窗口
struct dateTimeWindow_
{
	window_ window; //继承
	//-------------------------
	HELE hDateTime; //事件控制
	HELE hMonthCal; //日历元素
};

//窗口API:
HWINDOW DateTimeWnd_CreateWindow(int x, int y, int cx, int cy, HWND hWndParent);


//私有方法:
BOOL DateTimeWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, HWND hWndParent, int exType);
void DateTimeWnd_SetDate(HWINDOW hWindow, int year, int month, int day);
int  DateTimeWnd_GetYear(HWINDOW hWindow);
int  DateTimeWnd_GetMonth(HWINDOW hWindow);
int  DateTimeWnd_GetDay(HWINDOW hWindow);

//回调函数
BOOL CALLBACK DateTimeWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK DateTimeWnd_OnNCLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK DateTimeWnd_OnKillFocus(HWINDOW hWindow); //窗口失去焦点

BOOL CALLBACK DateTimeWnd_OnEventMonthSelect(HELE hEle, HELE hEventEle, BOOL bChange, BOOL bDownDayNum);
