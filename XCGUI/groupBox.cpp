/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup groupBox 组框元素(GroupBox)
/// @ingroup groupElements
/// @{

/// @brief 创建组框元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param pTitle 文本内容.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XGBox_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent) //创建
{
	groupBox_ *pObj = (groupBox_*)malloc(sizeof(groupBox_));
	memset(pObj, 0, sizeof(groupBox_));
	GBox_Init((HELE)pObj, x, y, cx, cy, pTitle, XC_GROUPBOX, hParent);
	return (HELE)pObj;
}

void GBox_Init(HELE hEle, int x, int y, int cx, int cy, wchar_t *pTitle, int eleType, HXCGUI hParent) //初始化注册
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_GROUPBOX);
	XEle_SetBkTransparent(hEle, TRUE);
	if (pTitle)
	{
		GROUPBOX(hEle)->hString = XStr_Create();
		XStr_SetString(GROUPBOX(hEle)->hString, pTitle);
	}
	XEle_RegisterMessage(hEle, XM_PAINT, GBox_OnDraw);
	XEle_RegisterEvent(hEle, XE_DESTROY, GBox_OnDestroy);
}

void CALLBACK GBox_OnDestroy(HELE hEle)  //销毁
{
	if (GROUPBOX(hEle)->hString)//
		XStr_Destroy(GROUPBOX(hEle)->hString);
}

/// @brief 获取文本内容.
/// @param hEle 元素句柄.
/// return 文本内容.
wchar_t* WINAPI XGBox_GetText(HELE hEle)
{
	IsGroupBoxDebug(hEle, __FUNCTION__);
	if (GROUPBOX(hEle)->hString)
	{
		return XStr_GetBuffer(GROUPBOX(hEle)->hString);
	}
	return NULL;
}

/// @brief 设置文本内容.
/// @param hEle 元素句柄.
/// @param pText 文本内容.
void WINAPI XGBox_SetText(HELE hEle, wchar_t *pText)
{
	IsGroupBoxDebug(hEle, __FUNCTION__);
	if (pText)
	{
		if (NULL == GROUPBOX(hEle)->hString)
			GROUPBOX(hEle)->hString = XStr_Create();
		XStr_SetString(GROUPBOX(hEle)->hString, pText);
	}
}

BOOL CALLBACK GBox_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	HDC hdc = XDraw_GetHDC_(hDraw);
	SIZE size = { 0,0 };
	if (GROUPBOX(hEle)->hString)
	{
		GetTextExtentPoint32(hdc, XStr_GetBuffer(GROUPBOX(hEle)->hString), XStr_GetLength(GROUPBOX(hEle)->hString), &size);
	}

	int posx, posy;
	XDraw_GetOffset_(hDraw, &posx, &posy);
	RECT rc = { 0,size.cy / 2,rect.right - 1,rect.bottom - 1 };
	rc.left += posx;
	rc.right += posx;
	rc.top += posy;
	rc.bottom += posy;

	GraphicsPath path;
	path.AddLine(rc.left + size.cx + 12, rc.top, rc.right - 5, rc.top);
	path.AddArc(rc.right - 10, rc.top, 10, 10, 270, 90);
	path.AddLine(rc.right, rc.top + 5, rc.right, rc.bottom - 5);
	path.AddArc(rc.right - 10, rc.bottom - 10, 10, 10, 0, 90);
	path.AddLine(rc.right - 5, rc.bottom, rc.left + 5, rc.bottom);
	path.AddArc(rc.left, rc.bottom - 10, 10, 10, 90, 90);
	path.AddLine(rc.left, rc.bottom - 5, rc.left, rc.top + 5);
	path.AddArc(rc.left, rc.top, 10, 10, 180, 90);
	path.AddLine(rc.left + 5, rc.top, rc.left + 10, rc.top);
	Pen blackPen(Color(255, 128, 128, 128), 1);
	Graphics  graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.DrawPath(&blackPen, &path);

	if (GROUPBOX(hEle)->hString)
	{
		wchar_t *pText = XStr_GetBuffer(GROUPBOX(hEle)->hString);
		if (pText)
		{
			RECT rcText = { 11,0,11 + size.cx,20 };
			XDraw_DrawText_(hDraw, pText, XStr_GetLength(GROUPBOX(hEle)->hString), &rcText, 0);
		}
	}
	return TRUE;
}

///@}