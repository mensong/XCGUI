/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//静态链接文本

struct textLink_
{
	button_  button; //继承
	//-------------------------------
	BOOL   bUnderline_leave; //鼠标离开 下划线
	BOOL   bUnderline_stay;  //鼠标停留 下划线
	COLORREF colorStay;//鼠标停留时文本颜色
};


//API:
XC_API HELE WINAPI XTextLink_Create(int x, int y, int cx, int cy, wchar_t *pTitle = NULL, HXCGUI hParent = NULL);


XC_API void WINAPI XTextLink_SetStayColor(HELE hEle, COLORREF color); //设置鼠标停留时文本颜色
XC_API COLORREF WINAPI XTextLink_GetStayColor(HELE hEle);  //获取鼠标停留时文本颜色
XC_API void WINAPI XTextLink_AdjustSize(HELE hEle);  //根据文本内容,调整元素大小
XC_API void WINAPI XTextLink_ShowUnderline(HELE hEle, BOOL bLeave, BOOL bStay);  //显示下划线

//私有方法:
void TextLink_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);

//回调函数
BOOL CALLBACK TextLink_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK TextLink_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK TextLink_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK TextLink_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);

