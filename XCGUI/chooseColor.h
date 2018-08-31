/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

//颜色选择元素

struct chooseColor_
{
	edit_  edit; //继承
	//---------------------
	COLORREF color; //当前颜色
};


//API:
XC_API HELE WINAPI XCHColor_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);

XC_API COLORREF WINAPI XCHColor_GetColor(HELE hEle); //获取颜色RGB值

XC_API void WINAPI XCHColor_SetColor(HELE hEle, COLORREF color);//设置颜色

//私有方法:
void CHColor_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
BOOL CALLBACK CHColor_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK CHColor_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK CHColor_OnEventKillFocus(HELE hEle, HELE hEventEle);
BOOL CALLBACK CHColor_OnEventSize(HELE hEle, HELE hEventEle);

