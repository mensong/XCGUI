/**************************************************************************\
*
* Copyright (c)  ìÅ²Ê½çÃæ¿â. All Rights Reserved.
*
* ìÅ²Ê½çÃæ¿â - ¹Ù·½ÍøÕ¾ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"
#include "dateTimeWindow.h"

HWINDOW DateTimeWnd_CreateWindow(int x, int y, int cx, int cy, HWND hWndParent)
{
	dateTimeWindow_ *pObj = (dateTimeWindow_*)malloc(sizeof(dateTimeWindow_));
	memset(pObj, 0, sizeof(dateTimeWindow_));
	DateTimeWnd_Init((HWINDOW)pObj, x, y, cx, cy, hWndParent, XC_DATETIMEWINDOW);
	return (HWINDOW)pObj;
}

BOOL DateTimeWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, HWND hWndParent, int exType)
{
	BOOL res = Wnd_Init(hWindow, NULL, NULL, NULL, WS_POPUP, x, y, cx, cy, hWndParent, 0, exType);
	if (res)
	{
		AddTypeDebug(hWindow, XC_DATETIMEWINDOW);

		XWnd_RegisterMessage(hWindow, WM_PAINT, DateTimeWnd_OnDrawWindow);
		XWnd_RegisterMessage(hWindow, WM_KILLFOCUS, DateTimeWnd_OnKillFocus);
		XWnd_RegisterNCMessage(hWindow, XWM_NCLBUTTONDOWN, DateTimeWnd_OnNCLButtonDown);

		((dateTimeWindow_*)hWindow)->hMonthCal = XMonthCal_Create(1, 1, MONTHCAL_WIDTH, MONTHCAL_HEIGHT, hWindow);

		XEle_RegisterEvent(((dateTimeWindow_*)hWindow)->hMonthCal, XE_MONTHCAL_CHANGE, DateTimeWnd_OnEventMonthSelect);
		SetCapture(XWnd_GetHWnd(hWindow));
	}
	return res;
}

void DateTimeWnd_SetDate(HWINDOW hWindow, int year, int month, int day)
{
	XMonthCal_SetDate(((dateTimeWindow_*)hWindow)->hMonthCal, year, month, day);
}

int  DateTimeWnd_GetYear(HWINDOW hWindow)
{
	return XMonthCal_GetYear(((dateTimeWindow_*)hWindow)->hMonthCal);
}

int  DateTimeWnd_GetMonth(HWINDOW hWindow)
{
	return XMonthCal_GetMonth(((dateTimeWindow_*)hWindow)->hMonthCal);
}

int  DateTimeWnd_GetDay(HWINDOW hWindow)
{
	return XMonthCal_GetDay(((dateTimeWindow_*)hWindow)->hMonthCal);
}

BOOL CALLBACK DateTimeWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	XDraw_FrameRect_(hDraw, &rect, hBrush);
	//DeleteObject(hBrush);
	return TRUE;
}

BOOL CALLBACK DateTimeWnd_OnNCLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	//XTRACE("date-Time Kill nc down\n");
	DateTime_DestroyPopupWnd(((dateTimeWindow_*)hWindow)->hDateTime, FALSE);
	return FALSE;
}

BOOL CALLBACK DateTimeWnd_OnKillFocus(HWINDOW hWindow)
{
	//XTRACE("date-Time Kill \n");
	DateTime_DestroyPopupWnd(((dateTimeWindow_*)hWindow)->hDateTime, FALSE);
	return FALSE;
}

BOOL CALLBACK DateTimeWnd_OnEventMonthSelect(HELE hEle, HELE hEventEle, BOOL bChange, BOOL bDownDayNum)
{
	if (hEle == hEventEle)
	{
		if (bDownDayNum)
			DateTime_DestroyPopupWnd(((dateTimeWindow_*)((ele_*)hEle)->pWindow)->hDateTime, TRUE);
		return TRUE;
	}
	return FALSE;
}