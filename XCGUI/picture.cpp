/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup picture 图片元素(Picture)
/// @ingroup groupElements
/// @{

/// @brief 创建图片元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XPic_Create(int x, int y, int cx, int cy, HXCGUI hParent)  //创建按钮
{
	picture_ *pObj = (picture_*)malloc(sizeof(picture_));
	memset(pObj, 0, sizeof(picture_));
	Pic_Init((HELE)pObj, x, y, cx, cy, XC_PICTURE, hParent);
	return (HELE)pObj;
}

void Pic_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_PICTURE);

	((ele_*)hEle)->bBorder = FALSE;
	XEle_RegisterMessage(hEle, XM_PAINT, Pic_OnDraw);
	XEle_RegisterEvent(hEle, XE_DESTROY, Pic_OnDestroy);
}

/// @brief 设置图片.
/// @param hEle 元素句柄.
/// @param hImage 图片句柄.
void WINAPI XPic_SetImage(HELE hEle, HIMAGE hImage)
{
	IsPictureDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(PICTURE(hEle)->hImage_bk, hImage);
}

BOOL CALLBACK Pic_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (PICTURE(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, PICTURE(hEle)->hImage_bk, &rect);
	}

	if (((ele_*)hEle)->bBorder)
	{
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, ((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		//DeleteObject(hBrush);
	}
	return TRUE;
}

void CALLBACK Pic_OnDestroy(HELE hEle)  //销毁
{
	if (PICTURE(hEle)->hImage_bk) XImage_Destroy(PICTURE(hEle)->hImage_bk);
}

///@}
