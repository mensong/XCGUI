/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup progressBar 进度条(ProgressBar)
/// @ingroup groupElements
/// @{

/// @brief 创建进度条元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param bHorizon 如果值为TRUE水平进度条,否则相反.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XProgBar_Create(int x, int y, int cx, int cy, BOOL bHorizon, HXCGUI hParent)
{
	progressBar_ *pObj = (progressBar_*)malloc(sizeof(progressBar_));
	memset(pObj, 0, sizeof(progressBar_));
	pObj->bHorizon = bHorizon;
	ProgBar_Init((HELE)pObj, x, y, cx, cy, XC_PROGRESSBAR, hParent);
	return (HELE)pObj;
}

void ProgBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_PROGRESSBAR);
	((progressBar_*)hEle)->range = 100;
	((progressBar_*)hEle)->curPos = 50;
	((progressBar_*)hEle)->bPercent = FALSE;
	XEle_RegisterMessage(hEle, XM_PAINT, ProgBar_OnDraw);
}

/// @brief 设置进度条范围.
/// @param hEle 元素句柄.
/// @param range 进度条范围.
void WINAPI XProgBar_SetRange(HELE hEle, int range)  //设置范围
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	if (range < 0) return;

	if (range < ((progressBar_*)hEle)->range)
		((progressBar_*)hEle)->curPos = range;

	((progressBar_*)hEle)->range = range;
}

/// @brief 设置进度条当前位置点.
/// @param hEle 元素句柄.
/// @param pos  当前位置点.
void WINAPI XProgBar_SetPos(HELE hEle, int pos)  //设置当前位置
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	if (pos < 0) return;

	if (pos > ((progressBar_*)hEle)->range)
		((progressBar_*)hEle)->curPos = ((progressBar_*)hEle)->range;

	((progressBar_*)hEle)->curPos = pos;
}

/// @brief 获取进度条范围.
/// @param hEle 元素句柄.
/// @return  进度条范围.
int  WINAPI XProgBar_GetRange(HELE hEle)
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	return ((progressBar_*)hEle)->range;
}

/// @brief 获取进度条当前位置点.
/// @param hEle 元素句柄.
/// @return  进度条当前位置点.
int  WINAPI XProgBar_GetPos(HELE hEle)
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	return ((progressBar_*)hEle)->curPos;
}

/// @brief 设置进度条元素水平或垂直.
/// @param hEle 元素句柄.
/// @param bHorizon 如果值为TRUE水平进度条,否则相反.
void WINAPI XProgBar_SetHorizon(HELE hEle, BOOL bHorizon)
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	((progressBar_*)hEle)->bHorizon = bHorizon;
}

/// @brief 启用显示百分比功能.
/// @param hEle 元素句柄.
/// @param bPercent 如果值为TRUE显示百分比,否则相反.
void WINAPI XProgBar_EnablePercent(HELE hEle, BOOL bPercent) //显示百分比
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	((progressBar_*)hEle)->bPercent = bPercent;
}

//贴图:

/// @brief 进度条元素背景贴图.
/// @param hEle   元素句柄.
/// @param hImage 图片句柄.
void WINAPI XProgBar_SetImage(HELE hEle, HIMAGE hImage) //背景
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	progressBar_ *pObject = (progressBar_*)hEle;
	Image_AddImage(pObject->hImage_bk, hImage);
}

/// @brief 进度条元素,显示当前进度贴图.
/// @param hEle   元素句柄.
/// @param hImage 图片句柄.
void WINAPI XProgBar_SetImage2(HELE hEle, HIMAGE hImage) //显示当前进度图片
{
	IsProgressBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	progressBar_ *pObject = (progressBar_*)hEle;
	Image_AddImage(pObject->hImage, hImage);
}

BOOL CALLBACK ProgBar_OnDraw(HELE hEle, HDRAW hDraw)
{
	progressBar_ *pObj = (progressBar_*)hEle;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (pObj->bHorizon) //水平
	{
		//绘制背景
		ProgBar_OnDrawHorizon(hEle, hDraw, rect);
	}
	else //垂直
	{
		ProgBar_OnDrawVertical(hEle, hDraw, rect);
	}

	return TRUE;
}

void ProgBar_OnDrawHorizon(HELE hEle, HDRAW hDraw, RECT &rect)
{
	progressBar_ *pObj = (progressBar_*)hEle;

	//绘制背景
	if (pObj->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, pObj->hImage_bk, &rect);
	}
	else
	{
		//设置绘制区域
		HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 3, 3);
		XDraw_SelectClipRgn_(hDraw, hRgn);

		//渐变填充
		XDraw_GradientFill4_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), RGB(200, 200, 200), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);

		//绘制外边线
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(180, 180, 180));
		XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
		//DeleteObject(hBrush);

		//DeleteObject(hRgn);
	}
	//绘制进度
	double pos = 0;
	if (0 != pObj->range)
		pos = ((double)pObj->curPos / (double)pObj->range);

	int width = (int)(pos*(rect.right - rect.left));
	RECT rc = rect;
	rc.right = rc.left + width;
	if (pObj->hImage)
	{
		switch (XImage_GetDrawType(pObj->hImage))
		{
		case XC_IMAGE_DEFAULT: //普通:
		case XC_IMAGE_ADAPTIVE:
			XDraw_HImage2_(hDraw, pObj->hImage, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
			break;
		case XC_IMAGE_STRETCH: //拉伸
			XDraw_HImageStretch_(hDraw, pObj->hImage, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
			break;
		case XC_IMAGE_TILE://平铺
			XDraw_HImageExTile_(hDraw, pObj->hImage, &rc, 0);
			break;
		}
	}
	else
	{
		//设置绘制区域
		HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom, 3, 3);
		XDraw_SelectClipRgn_(hDraw, hRgn);

		//渐变填充
		XDraw_GradientFill4_(hDraw, RGB(208, 255, 220), RGB(0, 210, 53), RGB(0, 189, 48), RGB(208, 255, 220), &rc, GRADIENT_FILL_RECT_V);

		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(0, 210, 53));
		HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
		XDraw_MoveToEx_(hDraw, rc.right, 0, NULL);
		XDraw_LineTo_(hDraw, rc.right, rc.bottom);
		//SelectObject(hdc,hOldPen);
		//DeleteObject(hPen);

		if (pObj->bPercent)
		{
			int  percent = (int)(pos * 100); //百分比
			wchar_t percentW[10] = { 0 };
			wsprintf(percentW, L"%d%%", percent);
			XDraw_DrawText_(hDraw, percentW, wcslen(percentW), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}

		XDraw_SelectClipRgn_(hDraw, NULL);
		//	DeleteObject(hRgn);
	}
}


void ProgBar_OnDrawVertical(HELE hEle, HDRAW hDraw, RECT &rect)
{
	progressBar_ *pObj = (progressBar_*)hEle;
	//绘制背景
	if (pObj->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, pObj->hImage_bk, &rect);
	}
	else
	{
		//设置绘制区域
		HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 3, 3);
		XDraw_SelectClipRgn_(hDraw, hRgn);
		//渐变填充
		XDraw_GradientFill4_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), RGB(200, 200, 200), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_H);

		//绘制外边线
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(180, 180, 180));
		XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
		//DeleteObject(hBrush);

		XDraw_SelectClipRgn_(hDraw, NULL);
		//	DeleteObject(hRgn);
	}

	//绘制进度
	double pos = 0;
	if (0 != pObj->range)
		pos = ((double)pObj->curPos / (double)pObj->range);

	int height = (int)(pos*(rect.bottom - rect.top));
	RECT rc = rect;
	rc.top = rect.bottom - height;
	if (pObj->hImage)
	{
		switch (XImage_GetDrawType(pObj->hImage))
		{
		case XC_IMAGE_DEFAULT: //普通:
		case XC_IMAGE_ADAPTIVE:
		{
			RECT rc2 = rc;
			rc2.bottom = XImage_GetHeight(pObj->hImage);
			rc2.top = rc2.bottom - height;
			XDraw_HImageSuper2_(hDraw, pObj->hImage, &rc, &rc2);
		}
		break;
		case XC_IMAGE_STRETCH: //拉伸
			XDraw_HImageStretch_(hDraw, pObj->hImage, rc.left, rc.top, rc.right - rc.left, height);
			break;
		case XC_IMAGE_TILE://平铺
			XDraw_HImageExTile_(hDraw, pObj->hImage, &rc, 1);
			break;
		}
	}
	else
	{
		//设置绘制区域
		HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom, 3, 3);
		XDraw_SelectClipRgn_(hDraw, hRgn);

		//渐变填充
		XDraw_GradientFill4_(hDraw, RGB(208, 255, 220), RGB(0, 210, 53), RGB(0, 189, 48), RGB(208, 255, 220), &rc, GRADIENT_FILL_RECT_H);

		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(0, 210, 53));
		HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
		XDraw_MoveToEx_(hDraw, 0, rc.top, NULL);
		XDraw_LineTo_(hDraw, rc.right, rc.top);
		//	SelectObject(hdc,hOldPen);
		//	DeleteObject(hPen);

		if (pObj->bPercent)
		{
			int  percent = (int)(pos * 100); //百分比
			wchar_t percentW[10] = { 0 };
			wsprintf(percentW, L"%d%%", percent);
			XDraw_DrawText_(hDraw, percentW, wcslen(percentW), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}

		XDraw_SelectClipRgn_(hDraw, NULL);
	}
}


///@}