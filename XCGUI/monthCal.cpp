/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup monthCal 月历卡片元素(MonthCal)
/// @ingroup groupElements
/// @{

/// @brief 创建月历卡片元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XMonthCal_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	monthCal_ *pObj = (monthCal_*)malloc(sizeof(monthCal_));
	memset(pObj, 0, sizeof(monthCal_));

	MonthCal_Init((HELE)pObj, x, y, cx, cy, XC_MONTHCAL, NULL, hParent);
	return (HELE)pObj;
}

void MonthCal_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_MONTHCAL);
	COleDateTime time = COleDateTime::GetTickCount();
	((monthCal_*)hEle)->time.SetDate(time.GetYear(), time.GetMonth(), time.GetDay());
	((monthCal_*)hEle)->bAdjust = TRUE;
	((monthCal_*)hEle)->timeOld = ((monthCal_*)hEle)->time;

	//	COleDateTime time(9999,((monthCal_*)hEle)->time.GetMonth(),1,0,0,0);
	//	((monthCal_*)hEle)->time=time;

		//左按钮
	((monthCal_*)hEle)->hBtnLeft = XBtn_Create(((monthCal_*)hEle)->left, ((monthCal_*)hEle)->top + 4, 20, 20, L"<<", hEle);
	//右按钮
	((monthCal_*)hEle)->hBtnRight = XBtn_Create(((monthCal_*)hEle)->left + MONTHCAL_WIDTH - 20, ((monthCal_*)hEle)->top + 4, 20, 20, L">>", hEle);

	XEle_SetBkTransparent(((monthCal_*)hEle)->hBtnLeft, TRUE);
	XEle_SetBkTransparent(((monthCal_*)hEle)->hBtnRight, TRUE);
	XEle_RegisterMessage(hEle, XM_PAINT, MonthCal_OnDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, MonthCal_OnEleLButtonDown);
	XEle_RegisterEvent(((monthCal_*)hEle)->hBtnLeft, XE_BNCLICK, MonthCal_OnEventBtnClickLeft);
	XEle_RegisterEvent(((monthCal_*)hEle)->hBtnRight, XE_BNCLICK, MonthCal_OnEventBtnClickRight);
}

/// @brief 设置月历元素左边间隔.
/// @param hEle  元素句柄.
/// @param left  间隔大小.
void WINAPI XMonthCal_SetSpacingLeft(HELE hEle, int left) //左对齐间距
{
	IsMonthCalDebug(hEle, __FUNCTION__);
	((monthCal_*)hEle)->left = left;
	RECT rect = { left,((monthCal_*)hEle)->top + 4,left + 20,((monthCal_*)hEle)->top + 20 + 4 };
	XEle_SetRect(((monthCal_*)hEle)->hBtnLeft, &rect);

	rect.right = rect.left + MONTHCAL_WIDTH;
	rect.left = rect.right - 20;
	XEle_SetRect(((monthCal_*)hEle)->hBtnRight, &rect);
}

/// @brief 设置月历元素上边框间隔大小.
/// @param hEle  元素句柄.
/// @param top   间隔大小.
void WINAPI XMonthCal_SetSpacingTop(HELE hEle, int top) //上对齐间距
{
	IsMonthCalDebug(hEle, __FUNCTION__);
	((monthCal_*)hEle)->top = top;
	RECT rect = { ((monthCal_*)hEle)->left,top + 4,((monthCal_*)hEle)->left + 20,top + 20 + 4 };
	XEle_SetRect(((monthCal_*)hEle)->hBtnLeft, &rect);

	rect.right = rect.left + MONTHCAL_WIDTH;
	rect.left = rect.right - 20;
	XEle_SetRect(((monthCal_*)hEle)->hBtnRight, &rect);
}

/// @brief 设置月历元素当前日期.
/// @param hEle  元素句柄.
/// @param year   年.
/// @param month  月.
/// @param day    日.
void WINAPI XMonthCal_SetDate(HELE hEle, int year, int month, int day)  //设置时间
{
	IsMonthCalDebug(hEle, __FUNCTION__);
	if (year < 100 || year>9999)
		return;
	((monthCal_*)hEle)->time.SetDate(year, month, day);
	((monthCal_*)hEle)->timeOld.SetDate(year, month, day);
	MonthCal_Adjust(hEle);
}

/// @brief 获取当前年.
/// @param hEle  元素句柄.
/// @return 当前年.
int WINAPI XMonthCal_GetYear(HELE hEle)
{
	IsMonthCalDebug(hEle, __FUNCTION__);
	return ((monthCal_*)hEle)->time.GetYear();
}

/// @brief 获取当前月.
/// @param hEle  元素句柄.
/// @return 当前月.
int WINAPI XMonthCal_GetMonth(HELE hEle)
{
	IsMonthCalDebug(hEle, __FUNCTION__);
	return ((monthCal_*)hEle)->time.GetMonth();
}

/// @brief 获取当前日.
/// @param hEle  元素句柄.
/// @return 当前日.
int WINAPI XMonthCal_GetDay(HELE hEle)
{
	IsMonthCalDebug(hEle, __FUNCTION__);
	return ((monthCal_*)hEle)->time.GetDay();
}

///@}

void MonthCal_Adjust(HELE hEle)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	if (0 == pObj->type) //日期
	{
		MonthCal_AdjustDayWeek(hEle);
	}
	else if (1 == pObj->type) //月
	{
		MonthCal_AdjustMonth(hEle);
	}
	else if (2 == pObj->type) //年
	{
		MonthCal_AdjustYear(hEle);
	}
	else if (3 == pObj->type) //十年间隔
	{
		MonthCal_AdjustYear10Year(hEle);
	}
}

void MonthCal_Change(HELE hEle, BOOL bView1) //检查日期是否改变
{
	monthCal_ *pObj = (monthCal_*)hEle;

	//检查日期是否改变
	if (pObj->time.GetYear() != pObj->timeOld.GetYear() || pObj->time.GetMonth() != pObj->timeOld.GetMonth() || pObj->time.GetDay() != pObj->timeOld.GetDay())
	{
		pObj->timeOld = pObj->time;
		if (bView1)
			Ele_SendEvent(hEle, XE_MONTHCAL_CHANGE, 1, 1); //发生日期改变事件
		else
			Ele_SendEvent(hEle, XE_MONTHCAL_CHANGE, 1, 0);
		//	XTRACE("日期改变\n");
	}
}

void MonthCal_AdjustDayWeek(HELE hEle) //调整
{
	monthCal_ *pObj = (monthCal_*)hEle;

	//检查日期是否改变
//	int y=pObj->time.GetYear();
//	int m=pObj->time.GetMonth();
//	int dd=pObj->time.GetDay();
//	int y2=pObj->timeOld.GetYear();
//	int m2=pObj->timeOld.GetMonth();
//	int dd2=pObj->timeOld.GetDay();
//	if(pObj->time.GetYear()!=pObj->timeOld.GetYear() || pObj->time.GetMonth()!=pObj->timeOld.GetMonth() || pObj->time.GetDay()!=pObj->timeOld.GetDay())
//	{
//		pObj->timeOld=pObj->time;
//		Ele_SendEvent(hEle,XE_MONTHCAL_CHANGE,1,0); //发生日期改变事件
	//	XTRACE("日期改变\n");
//	}

	int day = pObj->time.GetDay(); //当月日
	COleDateTime tmWeek(pObj->time);
	tmWeek -= COleDateTimeSpan(day - 1, 0, 0, 0); //调整到当月的1号

	int week = tmWeek.GetDayOfWeek();//星期
	int d = -1;
	if (1 == week) //星期日
	{
		tmWeek -= COleDateTimeSpan(7, 0, 0, 0); //调到上月周日
	}
	else
	{
		tmWeek -= COleDateTimeSpan(week - 1, 0, 0, 0); //调到上月周日
	}
	d = tmWeek.GetDay();
	int index = 0;
	for (int i = 0; i < 42; i++)
	{
		d = tmWeek.GetDay();
		if (-1 == d) d = 0;
		if (1 == d)
			break;
		pObj->btn[index].value = d;
		pObj->btn[index].flags = 0; //上月
		index++;
		tmWeek += COleDateTimeSpan(1, 0, 0, 0);
	}

	pObj->btn[index].value = d;
	pObj->btn[index].flags = 1; //当月
	index++;
	tmWeek += COleDateTimeSpan(1, 0, 0, 0);

	for (int i = index; i < 42; i++)
	{
		d = tmWeek.GetDay();
		if (1 == d || -1 == d)
			break;
		pObj->btn[index].value = d;
		pObj->btn[index].flags = 1; //当月
		index++;
		tmWeek += COleDateTimeSpan(1, 0, 0, 0);
	}

	for (int i = index; i < 42; i++)
	{
		d = tmWeek.GetDay();
		if (-1 == d) d = 0;
		pObj->btn[index].value = d;
		pObj->btn[index].flags = 2; //下月
		index++;
		tmWeek += COleDateTimeSpan(1, 0, 0, 0);
	}

	//调整坐标
	int posx = 0;
	int posy = pObj->top + 45;
	index = 0;
	for (int j = 0; j < 6; j++)
	{
		posx = pObj->left + 1;
		for (int i = 0; i < 7; i++)
		{
			pObj->btn[index].rect.left = posx;
			pObj->btn[index].rect.top = posy;
			pObj->btn[index].rect.right = posx + 27;
			pObj->btn[index].rect.bottom = posy + 15;

			if (1 == pObj->btn[index].flags && day == pObj->btn[index].value)//当前日
			{
				pObj->pSel = &pObj->btn[index];
			}
			posx += 27;
			index++;
		}
		posy += 15;
	}
}

void MonthCal_AdjustMonth(HELE hEle)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	int posx = 2;
	int posy = pObj->top + 30;

	int month = pObj->time.GetMonth();
	int index = 0;
	for (int j = 0; j < 3; j++)
	{
		posx = pObj->left + 2;
		for (int i = 0; i < 4; i++)
		{
			pObj->btn[index].rect.left = posx;
			pObj->btn[index].rect.top = posy;
			pObj->btn[index].rect.right = posx + 46;
			pObj->btn[index].rect.bottom = posy + 34;
			pObj->btn[index].value = index;
			if (month == (index + 1))
			{
				pObj->pSel = &pObj->btn[index];
			}
			posx += 46;
			index++;
		}
		posy += 34;
	}
}

void MonthCal_AdjustYear(HELE hEle)
{
	monthCal_ *pObj = (monthCal_*)hEle;

	int posx = 0;//pObj->left+8;
	int posy = pObj->top + 28 + 2;

	int curYear = pObj->time.GetYear();;
	int year = curYear;
	year = (year / 10) * 10;
	year--;

	int index = 0;
	for (int j = 0; j < 3; j++)
	{
		posx = pObj->left + 2;
		for (int i = 0; i < 4; i++)
		{
			pObj->btn[index].rect.left = posx;
			pObj->btn[index].rect.top = posy;
			pObj->btn[index].rect.right = posx + 47;
			pObj->btn[index].rect.bottom = posy + 34;
			pObj->btn[index].value = year;
			if (curYear == year)
			{
				pObj->pSel = &pObj->btn[index];
			}
			year++;
			posx += 47;
			index++;
		}
		posy += 34;
	}
}

void MonthCal_AdjustYear10Year(HELE hEle)
{
	monthCal_ *pObj = (monthCal_*)hEle; //94 

	int curYear = pObj->time.GetYear();
	int year = curYear;
	year = (year / 100) * 100;

	int posx = pObj->left + 2;
	int posy = pObj->top + 30;

	int index = 0;
	for (int i = 0; i < 5; i++)
	{
		posx = pObj->left + 2;

		pObj->btn[index].rect.left = posx;
		pObj->btn[index].rect.top = posy;
		pObj->btn[index].rect.right = posx + 94;
		pObj->btn[index].rect.bottom = posy + 20;
		pObj->btn[index].value = year;

		if (curYear >= year && curYear <= (year + 9))
		{
			pObj->pSel = &pObj->btn[index];
		}

		index++;
		year += 10;
		posx += 94;
		pObj->btn[index].rect.left = posx;
		pObj->btn[index].rect.top = posy;
		pObj->btn[index].rect.right = posx + 94;
		pObj->btn[index].rect.bottom = posy + 20;
		pObj->btn[index].value = year;

		if (curYear >= year && curYear <= (year + 9))
		{
			pObj->pSel = &pObj->btn[index];
		}
		posy += 20;
		year += 10;
		index++;
	}
}

BOOL CALLBACK MonthCal_OnDraw(HELE hEle, HDRAW hDraw)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	if (pObj->bAdjust)
	{
		MonthCal_Adjust(hEle);
		pObj->bAdjust = FALSE;
	}

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	RECT rc = { pObj->left,pObj->top,pObj->left + MONTHCAL_WIDTH,pObj->top + 28 };
	XDraw_FillSolidRect_(hDraw, &rc, RGB(10, 36, 106));

	rc.top += 28;
	rc.bottom = pObj->top + MONTHCAL_HEIGHT;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(164, 209, 255));

	//绘制选择
	XDraw_FillSolidRect_(hDraw, &pObj->pSel->rect, RGB(200, 0, 0));

	if (0 == pObj->type) //日期选择
	{
		wchar_t buf[10] = { 0 };
		wsprintf(buf, L"%d年%d月", pObj->time.GetYear(), pObj->time.GetMonth());
		XDraw_SetTextColor_(hDraw, RGB(255, 255, 255));
		XDraw_TextOut_(hDraw, pObj->left + 70, pObj->top + 8, buf, wcslen(buf));
		MonthCal_DrawDayWeek(hEle, hDraw); //绘制日期类型
	}
	else if (1 == pObj->type) //月选择
	{
		wchar_t buf[6] = { 0 };
		wsprintf(buf, L"%d年", pObj->time.GetYear());
		XDraw_SetTextColor_(hDraw, RGB(255, 255, 255));
		XDraw_TextOut_(hDraw, pObj->left + 80, pObj->top + 8, buf, wcslen(buf));
		MonthCal_DrawMonth(hEle, hDraw);
	}
	else if (2 == pObj->type) //年选择
	{
		MonthCal_DrawYear(hEle, hDraw);
	}
	else //十年间隔段选择
	{
		MonthCal_Draw10Year(hEle, hDraw);
	}
	return TRUE;
}

void MonthCal_DrawDayWeek(HELE hEle, HDRAW hDraw) //绘制日期类型
{
	monthCal_ *pObj = (monthCal_*)hEle;

	XDraw_SetTextColor_(hDraw, RGB(10, 36, 106));
	int posx = pObj->left + 8;
	int posy = pObj->top + 28 + 2;
	XDraw_TextOut_(hDraw, posx, posy, L"日", 1); posx += 27;
	XDraw_TextOut_(hDraw, posx, posy, L"一", 1); posx += 27;
	XDraw_TextOut_(hDraw, posx, posy, L"二", 1); posx += 27;

	XDraw_TextOut_(hDraw, posx, posy, L"三", 1); posx += 27;
	XDraw_TextOut_(hDraw, posx, posy, L"四", 1); posx += 27;
	XDraw_TextOut_(hDraw, posx, posy, L"五", 1); posx += 27;
	XDraw_TextOut_(hDraw, posx, posy, L"六", 1); posx += 27;

	posy += 13;
	XDraw_MoveToEx_(hDraw, pObj->left, posy, NULL);
	XDraw_LineTo_(hDraw, pObj->left + MONTHCAL_WIDTH, posy);


	wchar_t des[3] = { 0 };
	int index = 0;
	XDraw_SetTextColor_(hDraw, RGB(128, 128, 128));
	for (int i = 0; i < 7; i++)
	{
		if (0 == pObj->btn[index].flags)
		{
			_itow_s(pObj->btn[index].value, des, 3, 10);
			if (pObj->btn[index].value > 9)
				XDraw_TextOut_(hDraw, pObj->btn[index].rect.left + 8, pObj->btn[index].rect.top + 2, des, 2);
			else
				XDraw_TextOut_(hDraw, pObj->btn[index].rect.left + 8 + 6, pObj->btn[index].rect.top + 2, des, 2);
			index++;
		}
		else
			break;
	}

	XDraw_SetTextColor_(hDraw, RGB(0, 0, 0));
	for (int i = index; i < 42; i++)
	{
		if (1 == pObj->btn[index].flags)
		{
			_itow_s(pObj->btn[index].value, des, 3, 10);
			if (pObj->btn[index].value > 9)
				XDraw_TextOut_(hDraw, pObj->btn[index].rect.left + 8, pObj->btn[index].rect.top + 2, des, 2);
			else
				XDraw_TextOut_(hDraw, pObj->btn[index].rect.left + 8 + 6, pObj->btn[index].rect.top + 2, des, 2);
			index++;
		}
		else
			break;
	}

	XDraw_SetTextColor_(hDraw, RGB(128, 128, 128));
	for (int i = index; i < 42; i++)
	{
		_itow_s(pObj->btn[index].value, des, 3, 10);
		if (pObj->btn[index].value > 9)
			XDraw_TextOut_(hDraw, pObj->btn[index].rect.left + 8, pObj->btn[index].rect.top + 2, des, 2);
		else
			XDraw_TextOut_(hDraw, pObj->btn[index].rect.left + 8 + 6, pObj->btn[index].rect.top + 2, des, 2);
		index++;
	}
}

void MonthCal_DrawMonth(HELE hEle, HDRAW hDraw) //绘制月选择
{
	monthCal_ *pObj = (monthCal_*)hEle; //46 34
	int posx = pObj->left + 12;
	int posy = pObj->top + 28 + 12;
	XDraw_SetTextColor_(hDraw, RGB(0, 0, 0));

	XDraw_TextOut_(hDraw, posx, posy, L"一月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"二月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"三月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"四月", 2);

	posx = pObj->left + 12;
	posy += 34;
	XDraw_TextOut_(hDraw, posx, posy, L"五月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"六月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"七月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"八月", 2);

	posx = pObj->left + 12;
	posy += 34;
	XDraw_TextOut_(hDraw, posx, posy, L"九月", 2); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"十月", 2); posx += 42;
	XDraw_TextOut_(hDraw, posx, posy, L"十一月", 3); posx += 46;
	XDraw_TextOut_(hDraw, posx, posy, L"十二月", 3);
}

void MonthCal_DrawYear(HELE hEle, HDRAW hDraw)  //绘制年选择
{
	monthCal_ *pObj = (monthCal_*)hEle; //47 34

	wchar_t buf[12] = { 0 };
	wsprintf(buf, L"%d年-%d年", pObj->btn[1].value, pObj->btn[1].value + 9);

	XDraw_SetTextColor_(hDraw, RGB(255, 255, 255));
	XDraw_TextOut_(hDraw, pObj->left + 58, pObj->top + 8, buf, wcslen(buf));

	//////////////////////////////////////////////////

	int posx = pObj->left + 2;
	int posy = pObj->top + 30;

	int index = 0;
	wchar_t wcYear[6] = { 0 };

	XDraw_SetTextColor_(hDraw, RGB(128, 128, 128));
	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	XDraw_SetTextColor_(hDraw, RGB(0, 0, 0));
	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	posy += 34;
	posx = pObj->left + 2;
	for (int i = 0; i < 4; i++)
	{
		_itow_s(pObj->btn[index].value, wcYear, 5, 10);
		XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
		index++;
		posx += 47;
	}

	posy += 34;
	posx = pObj->left + 2;
	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	_itow_s(pObj->btn[index].value, wcYear, 5, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
	index++;
	posx += 47;

	XDraw_SetTextColor_(hDraw, RGB(128, 128, 128));
	_itow_s(pObj->btn[index].value, wcYear, 6, 10);
	XDraw_TextOut_(hDraw, posx + 12, posy + 12, wcYear, wcslen(wcYear));
}

void MonthCal_Draw10Year(HELE hEle, HDRAW hDraw) //绘制10年间隔选择
{
	monthCal_ *pObj = (monthCal_*)hEle;

	wchar_t buf3[12] = { 0 };
	wsprintf(buf3, L"%d年-%d年", pObj->btn[0].value, pObj->btn[9].value + 9);

	XDraw_SetTextColor_(hDraw, RGB(255, 255, 255));
	XDraw_TextOut_(hDraw, pObj->left + 58, pObj->top + 8, buf3, wcslen(buf3));

	//////////////////////////////////////////////
	XDraw_SetTextColor_(hDraw, RGB(0, 0, 0));
	int posx = pObj->left + 2;
	int posy = pObj->top + 30;

	wchar_t buf[10] = { 0 };
	int index = 0;
	for (int i = 0; i < 5; i++)
	{
		posx = pObj->left + 2;
		wsprintf(buf, L"%d-%d", pObj->btn[index].value, pObj->btn[index].value + 9);
		XDraw_TextOut_(hDraw, posx + 20, posy + 4, buf, wcslen(buf));

		index++;
		posx += 94;
		wsprintf(buf, L"%d-%d", pObj->btn[index].value, pObj->btn[index].value + 9);
		XDraw_TextOut_(hDraw, posx + 20, posy + 4, buf, wcslen(buf));
		posy += 20;
		index++;
	}
}

BOOL CALLBACK MonthCal_OnEleLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	RECT rect = { pObj->left + 20,pObj->top,pObj->left + MONTHCAL_WIDTH - 20,pObj->top + 28 };

	if (PtInRect(&rect, *pPt))
	{
		if (3 == pObj->type)
			return FALSE;

		pObj->type++;
		MonthCal_Adjust(hEle);
		XEle_RedrawEle(hEle);
		return FALSE;
	}
	if (pPt->y > (pObj->top + 28))
	{
		if (0 == pObj->type)
		{
			MonthCal_LButtonDownDayWeek(hEle, pPt);
		}
		else if (1 == pObj->type)
		{
			MonthCal_LButtonDownMonth(hEle, pPt);
		}
		else if (2 == pObj->type)
		{
			MonthCal_LButtonDownYear(hEle, pPt);
		}
		else if (3 == pObj->type)
		{
			MonthCal_LButtonDown10Year(hEle, pPt);
		}
	}
	return FALSE;
}

void MonthCal_LButtonDownDayWeek(HELE hEle, POINT *pPt)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	for (int i = 0; i < 42; i++)
	{
		if (PtInRect(&pObj->btn[i].rect, *pPt))
		{
			if (0 == pObj->btn[i].flags) //向上翻页
			{
				//调整时间到上月
				if (1 == pObj->time.GetMonth())
				{
					if (100 == pObj->time.GetYear()) //100,1
						return;
					COleDateTime time(pObj->time.GetYear() - 1, 12, pObj->btn[i].value, 0, 0, 0);
					pObj->time = time;
				}
				else
				{
					COleDateTime time(pObj->time.GetYear(), pObj->time.GetMonth() - 1, pObj->btn[i].value, 0, 0, 0);
					pObj->time = time;
				}
				pObj->bAdjust = TRUE;
				MonthCal_Change(hEle, TRUE);
				XEle_RedrawEle(hEle);

				XTRACE("上月 id=%d\n", pObj->btn[i].value);
			}
			else if (1 == pObj->btn[i].flags) //当月
			{
				if (pObj->time.GetDay() == pObj->btn[i].value)
				{
					Ele_SendEvent(hEle, XE_MONTHCAL_CHANGE, 0, 1); //日期选择,但是未改变事件
					return;
				}
				COleDateTime time(pObj->time.GetYear(), pObj->time.GetMonth(), pObj->btn[i].value, 0, 0, 0);
				pObj->time = time;

				//	pObj->pSel=&pObj->btn[i];
				pObj->bAdjust = TRUE;
				MonthCal_Change(hEle, TRUE);
				XEle_RedrawEle(hEle);
				XTRACE("当月 id=%d\n", pObj->btn[i].value);
			}
			else if (2 == pObj->btn[i].flags)//向下翻页
			{
				if (12 == pObj->time.GetMonth())
				{
					if (9999 == pObj->time.GetYear())
						return;
					COleDateTime time(pObj->time.GetYear() + 1, 1, pObj->btn[i].value, 0, 0, 0);
					pObj->time = time;
				}
				else
				{
					COleDateTime time(pObj->time.GetYear(), pObj->time.GetMonth() + 1, pObj->btn[i].value, 0, 0, 0);
					pObj->time = time;
				}
				pObj->bAdjust = TRUE;
				MonthCal_Change(hEle, TRUE);
				XEle_RedrawEle(hEle);

				XTRACE("下月 id=%d\n", pObj->btn[i].value);
			}
			break;
		}
	}
}

void MonthCal_LButtonDownMonth(HELE hEle, POINT *pPt)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&pObj->btn[i].rect, *pPt))
		{
			COleDateTime time(pObj->time.GetYear(), i + 1, 1, 0, 0, 0);
			pObj->time = time;
			pObj->type--;
			pObj->bAdjust = TRUE;
			MonthCal_Change(hEle, FALSE);
			XEle_RedrawEle(hEle);
			break;
		}
	}
}

void MonthCal_LButtonDownYear(HELE hEle, POINT *pPt)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&pObj->btn[i].rect, *pPt))
		{
			if (10000 == pObj->btn[i].value || 99 == pObj->btn[i].value)
				return;
			COleDateTime time(pObj->btn[i].value, pObj->time.GetMonth(), pObj->time.GetDay(), 0, 0, 0);
			pObj->time = time;
			pObj->type--;
			pObj->bAdjust = TRUE;
			XEle_RedrawEle(hEle);
			break;
		}
	}
}

void MonthCal_LButtonDown10Year(HELE hEle, POINT *pPt)
{
	monthCal_ *pObj = (monthCal_*)hEle;
	for (int i = 0; i < 10; i++)
	{
		if (PtInRect(&pObj->btn[i].rect, *pPt))
		{
			if (9999 != pObj->btn[i].value)
			{
				COleDateTime time(pObj->btn[i].value + 1, pObj->time.GetMonth(), 1, 0, 0, 0);
				pObj->time = time;
			}
			pObj->type--;
			pObj->bAdjust = TRUE;
			XEle_RedrawEle(hEle);
			break;
		}
	}
}

BOOL CALLBACK MonthCal_OnEventBtnClickLeft(HELE hEle, HELE hEventEle) //左按钮
{
	if (hEle != hEventEle)
		return FALSE;

	monthCal_ *pObj = (monthCal_*)((ele_*)hEle)->pParentEle;
	if (0 == pObj->type) //调整时间到上月1号
	{
		//检查年限范围
		if (1 == pObj->time.GetMonth())
		{
			int year = pObj->time.GetYear() - 1;
			if (year < 100)
				return TRUE;
			COleDateTime time(year, 12, 1, 0, 0, 0);
			pObj->time = time;
		}
		else
		{
			COleDateTime time(pObj->time.GetYear(), pObj->time.GetMonth() - 1, 1, 0, 0, 0);
			pObj->time = time;
		}
		pObj->bAdjust = TRUE;
		XEle_RedrawEle((HELE)pObj);
	}
	else if (1 == pObj->type) //月
	{
		//检查年限范围
		int year = pObj->time.GetYear() - 1;
		if (year < 100)
			return TRUE;
		COleDateTime time(year, pObj->time.GetMonth(), 1, 0, 0, 0);
		pObj->time = time;
		pObj->bAdjust = TRUE;
		XEle_RedrawEle((HELE)pObj);
	}
	else if (2 == pObj->type) //年
	{
		int year = pObj->time.GetYear() - 10;
		if (year < 100)
			return TRUE;
		COleDateTime time(year, pObj->time.GetMonth(), 1, 0, 0, 0);
		pObj->time = time;
		pObj->bAdjust = TRUE;
		XEle_RedrawEle((HELE)pObj);
	}
	else if (3 == pObj->type) //10年
	{
		//100
		int year = pObj->time.GetYear() - 100;
		if (year < 100)
		{
			return TRUE;
		}
		else
		{
			COleDateTime time(year, pObj->time.GetMonth(), 1, 0, 0, 0);
			pObj->time = time;
			pObj->bAdjust = TRUE;
			XEle_RedrawEle((HELE)pObj);
		}
	}
	return TRUE;
}

BOOL CALLBACK MonthCal_OnEventBtnClickRight(HELE hEle, HELE hEventEle) //右按钮
{
	if (hEle != hEventEle)
		return FALSE;

	monthCal_ *pObj = (monthCal_*)((ele_*)hEle)->pParentEle;
	if (0 == pObj->type)//调整时间到下月1号
	{
		if (12 == pObj->time.GetMonth())
		{
			int year = pObj->time.GetYear() + 1;
			if (year > 9999)
				return TRUE;
			COleDateTime time(year, 1, 1, 0, 0, 0);
			pObj->time = time;
		}
		else
		{
			COleDateTime time(pObj->time.GetYear(), pObj->time.GetMonth() + 1, 1, 0, 0, 0);
			pObj->time = time;
		}
		pObj->bAdjust = TRUE;
		XEle_RedrawEle((HELE)pObj);
	}
	else if (1 == pObj->type) //月
	{
		int year = pObj->time.GetYear() + 1;
		if (year > 9999)
			return TRUE;
		COleDateTime time(year, pObj->time.GetMonth(), 1, 0, 0, 0);
		pObj->time = time;
		pObj->bAdjust = TRUE;
		XEle_RedrawEle((HELE)pObj);
	}
	else if (2 == pObj->type) //年
	{
		int year = pObj->time.GetYear() + 10;
		if (year > 9999)
			return TRUE;
		COleDateTime time(year, pObj->time.GetMonth(), 1, 0, 0, 0);
		pObj->time = time;
		pObj->bAdjust = TRUE;
		XEle_RedrawEle((HELE)pObj);
	}
	else if (3 == pObj->type) //10年
	{
		//9999
		int year = pObj->time.GetYear() + 100;
		if (year > 9999)
		{
			return TRUE;
		}
		else
		{
			COleDateTime time(year, pObj->time.GetMonth(), 1, 0, 0, 0);
			pObj->time = time;
			pObj->bAdjust = TRUE;
			XEle_RedrawEle((HELE)pObj);
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

/// @defgroup dateTime 日期时间元素(DateTime)
/// @ingroup groupElements
/// @{

/// @brief 创建日期时间元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XDateTime_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	dateTime_ *pObj = (dateTime_*)malloc(sizeof(dateTime_));
	memset(pObj, 0, sizeof(dateTime_));
	DateTime_Init((HELE)pObj, x, y, cx, cy, XC_DATETIME, hParent);
	return (HELE)pObj;
}

void DateTime_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_DATETIME);

	dateTime_  *pObj = (dateTime_*)hEle;

	int height = cy - 4;
	pObj->hButton = XBtn_Create(cx - height - 2, 2, height, height, NULL, hEle);
	//	pObj->borderColor=RGB(128,128,128);

	COleDateTime time = COleDateTime::GetTickCount();
	pObj->time.SetDate(time.GetYear(), time.GetMonth(), time.GetDay());
	pObj->year = pObj->time.GetYear();
	pObj->month = pObj->time.GetMonth();
	pObj->day = pObj->time.GetDay();

	pObj->rcYear.left = 3;
	pObj->rcYear.top = 3;
	pObj->rcYear.right = pObj->rcYear.left + 24;
	pObj->rcYear.bottom = cy - 3;

	pObj->rcMonth.left = pObj->rcYear.right + 6;
	pObj->rcMonth.top = 3;
	pObj->rcMonth.right = pObj->rcMonth.left + 12;
	pObj->rcMonth.bottom = cy - 3;

	pObj->rcDay.left = pObj->rcMonth.right + 6;
	pObj->rcDay.top = 3;
	pObj->rcDay.right = pObj->rcDay.left + 12;
	pObj->rcDay.bottom = cy - 3;

	XEle_RegisterMessage(hEle, XM_PAINT, DateTime_OnDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, DateTime_OnLButtonDown);
	XEle_RegisterEvent(hEle, XE_CHAR, DateTime_OnEventChar);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, DateTime_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_SIZE, DateTime_OnEventSize);
	XEle_RegisterEvent(hEle, XE_DESTROY, DateTime_OnDestroy);

	XEle_RegisterEvent(pObj->hButton, XE_BNCLICK, DateTime_OnEventBtnClick);
	XEle_RegisterMessage(pObj->hButton, XM_PAINT, DateTime_OnDrawButton);
}

/// @brief 设置当前日期.
/// @param hEle 元素句柄.
/// @param year   年.
/// @param month  月.
/// @param day    日.
void WINAPI XDateTime_SetDate(HELE hEle, int year, int month, int day)  //设置时间
{
	IsDateTimeDebug(hEle, __FUNCTION__);
	((dateTime_*)hEle)->time.SetDate(year, month, day);
	((dateTime_*)hEle)->year = year;
	((dateTime_*)hEle)->month = month;
	((dateTime_*)hEle)->day = day;
}

/// @brief 获取当前年.
/// @param hEle 元素句柄.
/// @return  当前年.
int WINAPI XDateTime_GetYear(HELE hEle)
{
	IsDateTimeDebug(hEle, __FUNCTION__);
	return ((dateTime_*)hEle)->year;
}

/// @brief 获取当前月.
/// @param hEle 元素句柄.
/// @return  返回当前月.
int WINAPI XDateTime_GetMonth(HELE hEle)
{
	IsDateTimeDebug(hEle, __FUNCTION__);
	return ((dateTime_*)hEle)->month;
}

/// @brief 获取当前日.
/// @param hEle 元素句柄.
/// @return  当前日.
int WINAPI XDateTime_GetDay(HELE hEle)
{
	IsDateTimeDebug(hEle, __FUNCTION__);
	return ((dateTime_*)hEle)->day;
}

/// @brief 获取日期时间元素上弹出月历卡片按钮句柄.句柄类型为Button.
/// @param hEle 元素句柄.
/// @return  日期时间元素上弹出按钮句柄.
HELE WINAPI XDateTime_GetButton(HELE hEle)  //获取下拉按钮
{
	IsDateTimeDebug(hEle, __FUNCTION__);
	return ((dateTime_*)hEle)->hButton;
}

/// @brief 设置日期时间元素背景贴图.
/// @param hEle 元素句柄.
/// @param hImage 图片句柄.
void WINAPI XDateTime_SetImage(HELE hEle, HIMAGE hImage)
{
	IsDateTimeDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	Image_AddImage(DATETIME(hEle)->hImage_bk, hImage);
}

void DateTime_DestroyPopupWnd(HELE hEle, BOOL bSel)  //销毁弹出窗口
{
	if (((dateTime_*)hEle)->hPopupWnd)
	{
		dateTime_ *pObj = (dateTime_*)hEle;
		if (bSel)
		{
			//检查日期是否改变
			int year = DateTimeWnd_GetYear(pObj->hPopupWnd);
			int month = DateTimeWnd_GetMonth(pObj->hPopupWnd);
			int day = DateTimeWnd_GetDay(pObj->hPopupWnd);
			if (year != pObj->year || month != pObj->month || day != pObj->day)
			{
				pObj->year = year;
				pObj->month = month;
				pObj->day = day;
				DateTime_Change(hEle);
			}
		}
		PostMessage(XWnd_GetHWnd(pObj->hPopupWnd), WM_CLOSE, 0, 0);
		pObj->hPopupWnd = NULL;
		//关闭弹出选择窗口
		Ele_SendEvent(hEle, XE_DATETIME_EXIT_MONTHCAL, 0, 0);
	}
}

void DateTime_Change(HELE hEle) //日期改变
{
	dateTime_  *pObj = (dateTime_*)hEle;

	if (pObj->time.GetYear() != pObj->year || pObj->time.GetMonth() != pObj->month || pObj->time.GetDay() != pObj->day)
	{
		//日期改变
		if (pObj->year < 100)
		{
			pObj->year = pObj->time.GetYear();
			XEle_RedrawEle(hEle);
			return;
		}
		if (0 == pObj->month)
		{
			pObj->month = pObj->time.GetMonth();
			XEle_RedrawEle(hEle);
			return;
		}
		if (0 == pObj->day)
		{
			pObj->day = pObj->time.GetDay();
			XEle_RedrawEle(hEle);
			return;
		}
		pObj->time.SetDate(pObj->year, pObj->month, pObj->day);
		Ele_SendEvent(hEle, XE_DATETIME_CHANGE, 0, 0);
		XEle_RedrawEle(hEle);
	}
}

BOOL CALLBACK DateTime_OnDraw(HELE hEle, HDRAW hDraw)
{
	dateTime_  *pObj = (dateTime_*)hEle;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	//填充背景

	XDraw_FillSolidRect_(hDraw, &rect, ((ele_*)hEle)->bkColor);
	if (pObj->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, pObj->hImage_bk, &rect);
	}

	if (pObj->bYear)
		XDraw_FillSolidRect_(hDraw, &pObj->rcYear, RGB(136, 196, 255));
	if (pObj->bMonth)
		XDraw_FillSolidRect_(hDraw, &pObj->rcMonth, RGB(136, 196, 255));
	if (pObj->bDay)
		XDraw_FillSolidRect_(hDraw, &pObj->rcDay, RGB(136, 196, 255));

	//绘制内容
	wchar_t text[6] = { 0 };
	_itow_s(pObj->year, text, 6, 10);
	if (pObj->year >= 1000)
	{
		XDraw_TextOut_(hDraw, 3, 4, text, 4);
	}
	else if (pObj->year >= 100)
	{
		XDraw_TextOut_(hDraw, 9, 4, text, 3);
	}
	else if (pObj->year >= 10)
	{
		XDraw_TextOut_(hDraw, 15, 4, text, 2);
	}
	else
	{
		XDraw_TextOut_(hDraw, 21, 4, text, 1);
	}

	XDraw_TextOut_(hDraw, 27, 4, L"-", 1);
	wsprintf(text, L"%02d", pObj->month);
	XDraw_TextOut_(hDraw, 33, 4, text, 2);

	XDraw_TextOut_(hDraw, 45, 4, L"-", 1);
	wsprintf(text, L"%02d", pObj->day);
	XDraw_TextOut_(hDraw, 51, 4, text, 2);

	//绘制边框
	if (((ele_*)hEle)->bBorder)
	{
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, ((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw, &rect, hBrush);
	}

	return TRUE;
}

BOOL CALLBACK DateTime_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	if (XEle_IsHitChildEle(hEle, pPt))
	{
		return FALSE;
	}
	else
	{
		//XEle_SetFocus(hEle,TRUE);
		dateTime_ *pObj = (dateTime_*)hEle;
		if (FALSE == pObj->bYear)
			if (PtInRect(&pObj->rcYear, *pPt))
			{
				if (pObj->bMonth || pObj->bDay)
					DateTime_Change(hEle);
				pObj->bYear = TRUE;
				pObj->bMonth = FALSE;
				pObj->bDay = FALSE;
				pObj->year = 0;
				XEle_RedrawEle(hEle);
				return TRUE;
			}

		if (FALSE == pObj->bMonth)
			if (PtInRect(&pObj->rcMonth, *pPt))
			{
				if (pObj->bYear || pObj->bDay)
					DateTime_Change(hEle);
				pObj->bMonth = TRUE;
				pObj->bYear = FALSE;
				pObj->bDay = FALSE;
				pObj->month = 0;
				XEle_RedrawEle(hEle);
				return TRUE;
			}
		if (FALSE == pObj->bDay)
			if (PtInRect(&pObj->rcDay, *pPt))
			{
				if (pObj->bYear || pObj->bMonth)
					DateTime_Change(hEle);
				pObj->bDay = TRUE;
				pObj->bYear = FALSE;
				pObj->bMonth = FALSE;
				pObj->day = 0;
				XEle_RedrawEle(hEle);
				return TRUE;
			}
	}
	return FALSE;
}

BOOL CALLBACK DateTime_OnEventKillFocus(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		dateTime_ *pObj = (dateTime_*)hEle;
		if (pObj->bYear || pObj->bMonth || pObj->bDay)
		{
			pObj->bYear = FALSE;
			pObj->bMonth = FALSE;
			pObj->bDay = FALSE;
			DateTime_Change(hEle);
			XEle_RedrawEle(hEle);
		}
		XTRACE("dateTime 失去焦点\n");
	}
	return FALSE;
}

BOOL CALLBACK DateTime_OnEventChar(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam)
{
	if (hEle != hEventEle)
		return FALSE;

	if (wParam >= 48 && wParam <= 57)
	{
		dateTime_ *pObj = (dateTime_*)hEle;
		if (pObj->bYear)
		{
			wchar_t ch = wParam;
			if (pObj->year >= 1000)
			{
				pObj->year = _wtoi(&ch);
			}
			else
			{
				pObj->year = pObj->year * 10 + _wtoi(&ch);
			}
			XEle_RedrawEle(hEle);
		}
		else if (pObj->bMonth)
		{
			//月最大数12
			wchar_t ch = wParam;
			if (pObj->month >= 10)
			{
				pObj->month = _wtoi(&ch);
			}
			else
			{
				if ((pObj->month * 10 + _wtoi(&ch)) <= 12)
					pObj->month = pObj->month * 10 + _wtoi(&ch);
				else
					pObj->month = _wtoi(&ch);
			}
			XEle_RedrawEle(hEle);
		}
		else if (pObj->bDay)
		{
			int day = 0; //当月日最大天数
			if (9999 == pObj->time.GetYear())
			{
				day = 31;
			}
			else
			{
				COleDateTime  time, time2;
				time.SetDate(pObj->time.GetYear(), pObj->time.GetMonth(), 1);
				if (12 == pObj->time.GetMonth())
				{
					time2.SetDate(pObj->time.GetYear() + 1, 1, 1);
				}
				else
					time2.SetDate(pObj->time.GetYear(), pObj->time.GetMonth() + 1, 1);

				COleDateTimeSpan ts = time2 - time;
				double max = ts.GetTotalSeconds();
				day = (int)(max / 86400); //当月日最大天数
			}
			wchar_t ch = wParam;
			if (pObj->day >= 10)
			{
				pObj->day = _wtoi(&ch);;
			}
			else
			{
				if ((pObj->day * 10 + _wtoi(&ch)) <= day)
					pObj->day = pObj->day * 10 + _wtoi(&ch);
				else
					pObj->day = _wtoi(&ch);
			}
			XEle_RedrawEle(hEle);
			//	XTRACE("day=%d\n",day);
		}
	}
	return TRUE;
}

BOOL CALLBACK DateTime_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		//调整下拉按钮
		RECT rect;
		XEle_GetClientRect(hEle, &rect);
		int height = rect.bottom - 4;
		rect.left = rect.right - height - 2;
		rect.top = 2;
		rect.bottom = rect.top + height;
		rect.right = rect.right - 1;
		XEle_SetRect(((dateTime_*)hEle)->hButton, &rect);
	}
	return FALSE;
}

BOOL CALLBACK DateTime_OnEventBtnClick(HELE hEle, HELE hEventEle)  //下拉按钮点击
{
	if (hEle == hEventEle)
	{
		dateTime_ *pObj = (dateTime_*)(((ele_*)hEle)->pParentEle);
		if (NULL == pObj->hPopupWnd) //弹出文本选择列表窗口
		{
			DateTime_Change((HELE)pObj);

			POINT pt;
			pt.x = ((ele_*)hEle)->rect.right - ((ele_*)hEle)->rect.left;
			pt.y = ((ele_*)hEle)->rect.bottom - ((ele_*)hEle)->rect.top;
			XEle_PointToNCWnd(hEle, &pt);

			HWND hWnd = XEle_GetHWnd(hEle);
			ClientToScreen(hWnd, &pt);

			pt.x = pt.x - MONTHCAL_WIDTH - 2;
			pt.y++;
			pObj->hPopupWnd = DateTimeWnd_CreateWindow(pt.x, pt.y, MONTHCAL_WIDTH + 2, MONTHCAL_HEIGHT + 2, hWnd);
			((dateTimeWindow_*)pObj->hPopupWnd)->hDateTime = (HELE)pObj;
			DateTimeWnd_SetDate(pObj->hPopupWnd, pObj->year, pObj->month, pObj->day);
			//弹出选择窗口
			Ele_SendEvent(hEle, XE_DATETIME_POPUP_MONTHCAL, 0, 0);
			XWnd_ShowWindow(pObj->hPopupWnd, SW_SHOW);
		}
	}
	return TRUE;
}

BOOL CALLBACK DateTime_OnDrawButton(HELE hEle, HDRAW hDraw) //绘制下拉按钮
{
	//绘制下拉按钮-------------------------------
	RECT rc;
	XEle_GetClientRect(hEle, &rc);
	RECT rect = rc;

	button_* pObj = (button_*)hEle;

	//下拉按钮颜色
	if (pObj->state == STATE_STAY) //停留
	{
		//XTRACE("停留 \n");
		if (pObj->hImage_stay)
		{
			return FALSE;
		}
		else
		{
			RECT rcBer = { 1,1,rect.right - 1,rect.bottom - 1 };
			HBRUSH hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(200, 200, 200));//182,199,222));
			XDraw_FrameRect_(hDraw, &rcBer, hBrush1);
			//DeleteObject(hBrush1);

			//按钮边框
			HBRUSH hBrush3 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
			XDraw_FrameRect_(hDraw, &rc, hBrush3);
			//DeleteObject(hBrush3);

			//绘制按钮下三角
			POINT  pt[3];
			pt[0].x = rc.left + 2;
			pt[0].y = rc.top + 5;
			pt[1].x = rc.left + 13;
			pt[1].y = rc.top + 5;
			pt[2].x = rc.left + 7;
			pt[2].y = rc.top + 11;

			HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);

			HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
			XDraw_FillRgn_(hDraw, hRgn, hBrush2);

			//DeleteObject(hRgn);
			//DeleteObject(hBrush2);
		}
	}
	else //离开
	{
		//XTRACE("离开 \n");
		//按钮边框
		HBRUSH hBrush3 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rc, hBrush3);
		//DeleteObject(hBrush3);

		//绘制按钮下三角
		POINT  pt[3];
		pt[0].x = rc.left + 2;
		pt[0].y = rc.top + 5;
		pt[1].x = rc.left + 13;
		pt[1].y = rc.top + 5;
		pt[2].x = rc.left + 7;
		pt[2].y = rc.top + 11;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);

		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FillRgn_(hDraw, hRgn, hBrush2);

		//DeleteObject(hRgn);
		//DeleteObject(hBrush2);
	}

	return TRUE;
}

void CALLBACK DateTime_OnDestroy(HELE hEle)  //销毁
{
	if (DATETIME(hEle)->hImage_bk) XImage_Destroy(DATETIME(hEle)->hImage_bk);
}

///@}
