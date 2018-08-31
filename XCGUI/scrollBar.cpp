/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup scrollBar 滚动条(ScrollBar)
/// @ingroup groupElements
/// @{

/// @brief 创建滚动条元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param bHorizon TRUE水平滚动条,否则垂直滚动条.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XSBar_Create(int x, int y, int cx, int cy, BOOL bHorizon, HXCGUI hParent)
{
	scrollBar_ *pScrollBar = (scrollBar_*)malloc(sizeof(scrollBar_));
	if (pScrollBar)
	{
		memset(pScrollBar, 0, sizeof(scrollBar_));

		pScrollBar->bHorizon = bHorizon;
		SBar_Init((HELE)pScrollBar, x, y, cx, cy, XC_SCROLLBAR, hParent);
	}
	return (HELE)pScrollBar;
}

void SBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_SCROLLBAR);
	((ele_*)hEle)->bkColor = RGB(240, 240, 240);

	//////////////////////////////////////////////////////////
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	pScrollBar->btnLength = 16; //按钮长度
	pScrollBar->barLength = 0;
	pScrollBar->fixedSizeButton = -1;
	pScrollBar->range = 10;
	pScrollBar->bShowButton2 = TRUE;

	XEle_RegisterMessage(hEle, XM_PAINT, SBar_OnDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, SBar_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, SBar_OnLButtonUp);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, SBar_OnMouseMove);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, SBar_OnEventMouseLeave);
	XEle_RegisterEvent(hEle, XE_DESTROY, SBar_OnDestroy);
	XEle_RegisterEvent(hEle, XE_SIZE, SBar_OnEventSize);

	XSBar_Adjust(hEle);
}

/// @brief 调整滚动条.
/// @param hEle  元素句柄.
void WINAPI XSBar_Adjust(HELE hEle) //调整滚动条
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (pScrollBar->bHorizon) //水平滚动条
	{
		int cx = rect.right - rect.left;
		if (pScrollBar->bShowButton2)
		{
			pScrollBar->spacing = cx - pScrollBar->btnLength - pScrollBar->btnLength - 2;

			if (cx < (pScrollBar->btnLength * 2))  //检查滚动条区域大小
				XEle_ShowEle(hEle, FALSE); //区域太小,那么隐藏
			else
				XEle_ShowEle(hEle, TRUE);

			//修改左按钮位置
			pScrollBar->rcUp.left = 0;
			pScrollBar->rcUp.right = pScrollBar->btnLength;
			pScrollBar->rcUp.top = 1;
			pScrollBar->rcUp.bottom = rect.bottom - 1;


			//修改右按钮位置
			pScrollBar->rcDown.left = cx - pScrollBar->btnLength;
			pScrollBar->rcDown.right = cx;
			pScrollBar->rcDown.top = 1;
			pScrollBar->rcDown.bottom = rect.bottom - 1;
		}
		else
		{
			pScrollBar->spacing = cx - 2;
			if (cx < (pScrollBar->btnLength * 2))  //检查滚动条区域大小
				XEle_ShowEle(hEle, FALSE); //区域太小,那么隐藏
			else
				XEle_ShowEle(hEle, TRUE);

			//修改左按钮位置
			pScrollBar->rcUp.left = 0;
			pScrollBar->rcUp.right = 0;
			pScrollBar->rcUp.top = 0;
			pScrollBar->rcUp.bottom = 0;

			//修改右按钮位置
			pScrollBar->rcDown.left = 0;
			pScrollBar->rcDown.right = 0;
			pScrollBar->rcDown.top = 0;
			pScrollBar->rcDown.bottom = 0;
		}
	}
	else //垂直滚动条
	{
		int cy = rect.bottom - rect.top;
		if (pScrollBar->bShowButton2)
		{
			pScrollBar->spacing = cy - pScrollBar->btnLength - pScrollBar->btnLength - 2;

			if (cy < (pScrollBar->btnLength * 2))  //检查滚动条区域大小
				XEle_ShowEle(hEle, FALSE);
			else
				XEle_ShowEle(hEle, TRUE);

			pScrollBar->rcUp.top = 0;
			pScrollBar->rcUp.bottom = pScrollBar->btnLength;
			pScrollBar->rcUp.left = 1;
			pScrollBar->rcUp.right = rect.right - 1;

			pScrollBar->rcDown.top = cy - pScrollBar->btnLength;
			pScrollBar->rcDown.bottom = cy;
			pScrollBar->rcDown.left = 1;
			pScrollBar->rcDown.right = rect.right - 1;
		}
		else
		{
			pScrollBar->spacing = cy - 2;

			if (cy < (pScrollBar->btnLength * 2))  //检查滚动条区域大小
				XEle_ShowEle(hEle, FALSE);
			else
				XEle_ShowEle(hEle, TRUE);

			pScrollBar->rcUp.top = 0;
			pScrollBar->rcUp.bottom = 0;
			pScrollBar->rcUp.left = 0;
			pScrollBar->rcUp.right = 0;

			pScrollBar->rcDown.top = 0;
			pScrollBar->rcDown.bottom = 0;
			pScrollBar->rcDown.left = 0;
			pScrollBar->rcDown.right = 0;
		}
	}

	//检查滑块长度
	if (-1 == pScrollBar->fixedSizeButton)
	{
		pScrollBar->barLength = pScrollBar->spacing / 2;
	}
	else
	{
		pScrollBar->barLength = pScrollBar->fixedSizeButton;
	}
	if (pScrollBar->barLength < 10)
	{
		if (pScrollBar->spacing > 10)
			pScrollBar->barLength = 10;
		else
			pScrollBar->barLength = 0;
	}
	else if (pScrollBar->barLength > pScrollBar->spacing)
	{
		pScrollBar->barLength = pScrollBar->spacing;
		//pScrollBar->range=0; TODO:取消修改滚动范围,以免滚动条无效. by 2011/11/30
	}

	//调整滑块位置 按比例
	double posSize = 0; //每个点大小
	if (0 != pScrollBar->range)
	{
		int size = pScrollBar->spacing - pScrollBar->barLength;
		if (0 != size)
			posSize = ((double)size) / pScrollBar->range;
	}

	//如果当前滚动点小于滚动范围
	if (pScrollBar->curPos > pScrollBar->range)
	{
		pScrollBar->curPos = pScrollBar->range;
		if (pScrollBar->bHorizon)
		{
			Ele_SendEvent(hEle, XE_HSCROLL, pScrollBar->curPos, 0);
		}
		else
		{
			Ele_SendEvent(hEle, XE_VSCROLL, pScrollBar->curPos, 0);
		}
	}

	int left = (int)(pScrollBar->curPos*posSize);

	if (pScrollBar->bHorizon)
	{
		if (pScrollBar->bShowButton2)
			pScrollBar->rcBar.left = left + pScrollBar->btnLength + 1;
		else
			pScrollBar->rcBar.left = left + 1;
		pScrollBar->rcBar.right = pScrollBar->rcBar.left + pScrollBar->barLength;
		pScrollBar->rcBar.top = 1;
		pScrollBar->rcBar.bottom = rect.bottom - 1;
	}
	else
	{
		if (pScrollBar->bShowButton2)
			pScrollBar->rcBar.top = left + pScrollBar->btnLength + 1;
		else
			pScrollBar->rcBar.top = left + 1;
		pScrollBar->rcBar.bottom = pScrollBar->rcBar.top + pScrollBar->barLength;
		pScrollBar->rcBar.left = 1;
		pScrollBar->rcBar.right = rect.right - 1;
	}
}

/// @brief 设置滚动范围.
/// @param hEle  元素句柄.
/// @param range 滚动范围.
void WINAPI XSBar_SetScrollRange(HELE hEle, int range)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (range < 0)
		SCROLLBAR(hEle)->range = 0;
	else
		SCROLLBAR(hEle)->range = range;

	XSBar_Adjust(hEle);
}

/// @brief 获取滚动条两头小按钮长度.
/// @param hEle  元素句柄.
/// @return 滚动条两头小按钮长度.
int WINAPI XSBar_GetButtonLength(HELE hEle) //按钮长度
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return SCROLLBAR(hEle)->btnLength;
}

/// @brief 获取滑块长度.
/// @param hEle  元素句柄.
/// @return 滑块长度.
int WINAPI XSBar_GetSliderLength(HELE hEle) //滑块长度
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return SCROLLBAR(hEle)->barLength;
}

/// @brief 获取滚动范围.
/// @param hEle  元素句柄.
/// @return 滚动范围.
int WINAPI XSBar_GetScrollRange(HELE hEle) //获取滚动范围
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return SCROLLBAR(hEle)->range;
}

/// @brief 是否显示上下滚动按钮.
/// @param hEle  元素句柄.
/// @param bEnable  显示上下滚动按钮:TRUE,不显示上下滚动按钮:FALSE.
void WINAPI XSBar_EnableScrollButton2(HELE hEle, BOOL bEnable) //是否显示上下滚动按钮
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	SCROLLBAR(hEle)->bShowButton2 = bEnable;
	XSBar_Adjust(hEle);
}

/// @brief 设置滑块长度.
/// @param hEle  元素句柄.
/// @param length 滑块长度.
void WINAPI XSBar_SetSliderLength(HELE hEle, int length) //设置滑块长度
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	//SCROLLBAR(hEle)->barLength=length;
	SCROLLBAR(hEle)->fixedSizeButton = length;
	XSBar_Adjust(hEle);
}

/// @brief 设置水平显示或垂直显示.
/// @param hEle  元素句柄.
/// @param bHorizon 如果值为TRUE水平显示,否则相反.
void WINAPI XSBar_SetHorizon(HELE hEle, BOOL bHorizon)  //水平显示或垂直
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	SCROLLBAR(hEle)->bHorizon = bHorizon;
	XSBar_Adjust(hEle);
}

/// @brief 获取当前滚动点.
/// @param hEle  元素句柄.
/// @return 当前滚动点.
int WINAPI XSBar_GetScrollPos(HELE hEle) //获取当前滚动点
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return SCROLLBAR(hEle)->curPos;
}

//贴图:

/// @brief 设置滚动条背景贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImage(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_bk, hImage);
}

/// @brief 设置滚动条上滚动按钮,鼠标离开状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageLeaveUp(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_Leave_up, hImage);
}

/// @brief 设置滚动条上滚动按钮,鼠标停留状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageStayUp(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_stay_up, hImage);
}

/// @brief 设置滚动条上滚动按钮,鼠标按下状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageDownUp(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_down_up, hImage);
}

/// @brief 设置滚动条下滚动按钮,鼠标离开状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageLeaveDown(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_Leave_down, hImage);
}

/// @brief 设置滚动条下滚动按钮,鼠标停留状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageStayDown(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_stay_down, hImage);
}

/// @brief 设置滚动条下滚动按钮,鼠标按下状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageDownDown(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_down_down, hImage);
}

/// @brief 设置滚动条滑块,鼠标离开状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageLeaveSlider(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_Leave_slider, hImage);
}

/// @brief 设置滚动条滑块,鼠标停留状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageStaySlider(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_stay_slider, hImage);
}

/// @brief 设置滚动条滑块,鼠标按下状态时贴图.
/// @param hEle  元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSBar_SetImageDownSlider(HELE hEle, HIMAGE hImage)
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLBAR(hEle)->hImage_down_slider, hImage);
}

BOOL CALLBACK SBar_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);

	if (SCROLLBAR(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, SCROLLBAR(hEle)->hImage_bk, &rect);
	}
	else if (FALSE == ((ele_*)hEle)->bBkTransparent)
	{
		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(230, 230, 230));
		HGDIOBJ hOld = XDraw_SelectObject_(hDraw, hPen);
		if (pScrollBar->bHorizon)
		{
			XDraw_MoveToEx_(hDraw, 0, 0, 0);
			XDraw_LineTo_(hDraw, rect.right, 0);
		}
		else
		{
			XDraw_MoveToEx_(hDraw, 0, 0, 0);
			XDraw_LineTo_(hDraw, 0, rect.bottom);
		}
	}

	if (pScrollBar->bShowButton2)
	{
		Sbar_DrawButtonUp(hEle, hDraw);
		Sbar_DrawButtonDown(hEle, hDraw);
	}
	Sbar_DrawButtonBar(hEle, hDraw);

	return TRUE;
}

void Sbar_DrawButtonUp(HELE hEle, HDRAW hDraw)
{
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	if (pScrollBar->bHorizon) //水平滚动条
	{
		if (STATE_LEAVE == pScrollBar->rcUpState)
		{
			if (pScrollBar->hImage_Leave_up)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_Leave_up, &pScrollBar->rcUp);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left, pScrollBar->rcUp.top, pScrollBar->rcUp.right + 1, pScrollBar->rcUp.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcUp, GRADIENT_FILL_RECT_V);

				//绘制内边线
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left + 1, pScrollBar->rcUp.top + 1, pScrollBar->rcUp.right, pScrollBar->rcUp.bottom, 3, 3);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				//绘制外边线
				hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_STAY == pScrollBar->rcUpState)
		{
			if (pScrollBar->hImage_stay_up)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_stay_up, &pScrollBar->rcUp);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left, pScrollBar->rcUp.top, pScrollBar->rcUp.right + 1, pScrollBar->rcUp.bottom + 1, 3, 3);
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left + 1, pScrollBar->rcUp.top + 1, pScrollBar->rcUp.right, pScrollBar->rcUp.bottom, 3, 3);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(233, 225, 101));

				XDraw_SelectClipRgn_(hDraw, hRgn);

				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcUp, GRADIENT_FILL_RECT_V);

				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);

				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_DOWN == pScrollBar->rcUpState)
		{
			if (pScrollBar->hImage_down_up)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_down_up, &pScrollBar->rcUp);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left, pScrollBar->rcUp.top, pScrollBar->rcUp.right + 1, pScrollBar->rcUp.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &pScrollBar->rcUp, GRADIENT_FILL_RECT_V);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left + 1, pScrollBar->rcUp.top + 1, pScrollBar->rcUp.right, pScrollBar->rcUp.bottom + 1, 3, 3);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}

		int left = pScrollBar->rcUp.left + (pScrollBar->rcUp.right - pScrollBar->rcUp.left) / 2;
		int top = pScrollBar->rcUp.top + (pScrollBar->rcUp.bottom - pScrollBar->rcUp.top) / 2;

		POINT  pt[3];
		pt[0].x = left - 3;
		pt[0].y = top;
		pt[1].x = left + 2;
		pt[1].y = top + 5;
		pt[2].x = left + 2;
		pt[2].y = top - 5;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
		XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	}
	else //垂直滚动条
	{
		if (STATE_LEAVE == pScrollBar->rcUpState)
		{
			if (pScrollBar->hImage_Leave_up)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_Leave_up, &pScrollBar->rcUp);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left, pScrollBar->rcUp.top, pScrollBar->rcUp.right + 1, pScrollBar->rcUp.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcUp, GRADIENT_FILL_RECT_V);

				//绘制内边线
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left + 1, pScrollBar->rcUp.top + 1, pScrollBar->rcUp.right, pScrollBar->rcUp.bottom, 3, 3);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				//绘制外边线
				hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_STAY == pScrollBar->rcUpState)
		{
			if (pScrollBar->hImage_stay_up)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_stay_up, &pScrollBar->rcUp);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left, pScrollBar->rcUp.top, pScrollBar->rcUp.right + 1, pScrollBar->rcUp.bottom + 1, 3, 3);
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left + 1, pScrollBar->rcUp.top + 1, pScrollBar->rcUp.right, pScrollBar->rcUp.bottom, 3, 3);

				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(233, 225, 101));
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));

				XDraw_SelectClipRgn_(hDraw, hRgn);

				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcUp, GRADIENT_FILL_RECT_V);

				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);

				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_DOWN == pScrollBar->rcUpState)
		{
			if (pScrollBar->hImage_down_up)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_down_up, &pScrollBar->rcUp);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left, pScrollBar->rcUp.top, pScrollBar->rcUp.right + 1, pScrollBar->rcUp.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &pScrollBar->rcUp, GRADIENT_FILL_RECT_V);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcUp.left + 1, pScrollBar->rcUp.top + 1, pScrollBar->rcUp.right, pScrollBar->rcUp.bottom + 1, 3, 3);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}

		int left = pScrollBar->rcUp.left + (pScrollBar->rcUp.right - pScrollBar->rcUp.left) / 2;
		int top = pScrollBar->rcUp.top + (pScrollBar->rcUp.bottom - pScrollBar->rcUp.top) / 2;

		POINT  pt[3];
		pt[0].x = left;
		pt[0].y = top - 3;
		pt[1].x = left - 5;
		pt[1].y = top + 2;
		pt[2].x = left + 5;
		pt[2].y = top + 2;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
		XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	}
}

void Sbar_DrawButtonDown(HELE hEle, HDRAW hDraw)
{
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	if (pScrollBar->bHorizon) //水平滚动条
	{
		if (STATE_LEAVE == pScrollBar->rcDownState)
		{
			if (pScrollBar->hImage_Leave_down)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_Leave_down, &pScrollBar->rcDown);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left, pScrollBar->rcDown.top, pScrollBar->rcDown.right + 1, pScrollBar->rcDown.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcDown, GRADIENT_FILL_RECT_V);

				//绘制内边线
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left + 1, pScrollBar->rcDown.top + 1, pScrollBar->rcDown.right, pScrollBar->rcDown.bottom, 3, 3);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				//绘制外边线
				hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_STAY == pScrollBar->rcDownState)
		{
			if (pScrollBar->hImage_stay_down)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_stay_down, &pScrollBar->rcDown);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left, pScrollBar->rcDown.top, pScrollBar->rcDown.right + 1, pScrollBar->rcDown.bottom + 1, 3, 3);
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left + 1, pScrollBar->rcDown.top + 1, pScrollBar->rcDown.right, pScrollBar->rcDown.bottom, 3, 3);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(233, 225, 101));

				XDraw_SelectClipRgn_(hDraw, hRgn);

				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcDown, GRADIENT_FILL_RECT_V);

				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);

				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_DOWN == pScrollBar->rcDownState)
		{
			if (pScrollBar->hImage_down_down)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_down_down, &pScrollBar->rcDown);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left, pScrollBar->rcDown.top, pScrollBar->rcDown.right + 1, pScrollBar->rcDown.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &pScrollBar->rcDown, GRADIENT_FILL_RECT_V);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left + 1, pScrollBar->rcDown.top + 1, pScrollBar->rcDown.right, pScrollBar->rcDown.bottom + 1, 3, 3);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}

		int left = pScrollBar->rcDown.left + (pScrollBar->rcDown.right - pScrollBar->rcDown.left) / 2;
		int top = pScrollBar->rcDown.top + (pScrollBar->rcDown.bottom - pScrollBar->rcDown.top) / 2;

		POINT  pt[3];
		pt[0].x = left + 3;
		pt[0].y = top;
		pt[1].x = left - 2;
		pt[1].y = top + 5;
		pt[2].x = left - 2;
		pt[2].y = top - 5;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
		XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	}
	else //垂直滚动条
	{
		if (STATE_LEAVE == pScrollBar->rcDownState)
		{
			if (pScrollBar->hImage_Leave_down)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_Leave_down, &pScrollBar->rcDown);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left, pScrollBar->rcDown.top, pScrollBar->rcDown.right + 1, pScrollBar->rcDown.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcDown, GRADIENT_FILL_RECT_V);

				//绘制内边线
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left + 1, pScrollBar->rcDown.top + 1, pScrollBar->rcDown.right, pScrollBar->rcDown.bottom, 3, 3);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				//绘制外边线
				hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_STAY == pScrollBar->rcDownState)
		{
			if (pScrollBar->hImage_stay_down)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_stay_down, &pScrollBar->rcDown);

				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left, pScrollBar->rcDown.top, pScrollBar->rcDown.right + 1, pScrollBar->rcDown.bottom + 1, 3, 3);
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left + 1, pScrollBar->rcDown.top + 1, pScrollBar->rcDown.right, pScrollBar->rcDown.bottom, 3, 3);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(233, 225, 101));

				XDraw_SelectClipRgn_(hDraw, hRgn);

				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcDown, GRADIENT_FILL_RECT_V);

				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);

				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else  if (STATE_DOWN == pScrollBar->rcDownState)
		{
			if (pScrollBar->hImage_down_down)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_down_down, &pScrollBar->rcDown);

				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left, pScrollBar->rcDown.top, pScrollBar->rcDown.right + 1, pScrollBar->rcDown.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &pScrollBar->rcDown, GRADIENT_FILL_RECT_V);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcDown.left + 1, pScrollBar->rcDown.top + 1, pScrollBar->rcDown.right, pScrollBar->rcDown.bottom + 1, 3, 3);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);
				//	DeleteObject(hRgn2);
				//	DeleteObject(hBrush);

				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
				//DeleteObject(hRgn);
				//DeleteObject(hBrush2);
			}
		}
		int left = pScrollBar->rcDown.left + (pScrollBar->rcDown.right - pScrollBar->rcDown.left) / 2;
		int top = pScrollBar->rcDown.top + (pScrollBar->rcDown.bottom - pScrollBar->rcDown.top) / 2;

		POINT  pt[3];
		pt[0].x = left;
		pt[0].y = top + 3;
		pt[1].x = left - 5;
		pt[1].y = top - 2;
		pt[2].x = left + 5;
		pt[2].y = top - 2;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
		XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	}
}

void Sbar_DrawButtonBar(HELE hEle, HDRAW hDraw)
{
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	if (pScrollBar->bHorizon) //水平滚动条
	{
		if (STATE_LEAVE == pScrollBar->rcBarState)
		{
			if (pScrollBar->hImage_Leave_slider)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_Leave_slider, &pScrollBar->rcBar);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left, pScrollBar->rcBar.top, pScrollBar->rcBar.right + 1, pScrollBar->rcBar.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcBar, GRADIENT_FILL_RECT_V);

				//绘制内边线
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left + 1, pScrollBar->rcBar.top + 1, pScrollBar->rcBar.right, pScrollBar->rcBar.bottom, 3, 3);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				//绘制外边线
				hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else if (STATE_STAY == pScrollBar->rcBarState)
		{
			if (pScrollBar->hImage_stay_slider)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_stay_slider, &pScrollBar->rcBar);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left, pScrollBar->rcBar.top, pScrollBar->rcBar.right + 1, pScrollBar->rcBar.bottom + 1, 3, 3);
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left + 1, pScrollBar->rcBar.top + 1, pScrollBar->rcBar.right, pScrollBar->rcBar.bottom, 3, 3);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(233, 225, 101));

				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcBar, GRADIENT_FILL_RECT_V);

				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);
			}
		}
		else if (STATE_DOWN == pScrollBar->rcBarState)
		{
			if (pScrollBar->hImage_down_slider)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_down_slider, &pScrollBar->rcBar);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left, pScrollBar->rcBar.top, pScrollBar->rcBar.right + 1, pScrollBar->rcBar.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &pScrollBar->rcBar, GRADIENT_FILL_RECT_V);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left + 1, pScrollBar->rcBar.top + 1, pScrollBar->rcBar.right, pScrollBar->rcBar.bottom + 1, 3, 3);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);


				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
	}
	else //垂直滚动条
	{
		if (STATE_LEAVE == pScrollBar->rcBarState)
		{
			if (pScrollBar->hImage_Leave_slider)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_Leave_slider, &pScrollBar->rcBar);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left, pScrollBar->rcBar.top, pScrollBar->rcBar.right + 1, pScrollBar->rcBar.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcBar, GRADIENT_FILL_RECT_H);

				//绘制内边线
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left + 1, pScrollBar->rcBar.top + 1, pScrollBar->rcBar.right, pScrollBar->rcBar.bottom, 3, 3);

				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				//绘制外边线
				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
			}
		}
		else if (STATE_STAY == pScrollBar->rcBarState)
		{
			if (pScrollBar->hImage_stay_slider)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_stay_slider, &pScrollBar->rcBar);
				return;
			}
			else
			{
				//设置绘制区域
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left, pScrollBar->rcBar.top, pScrollBar->rcBar.right + 1, pScrollBar->rcBar.bottom + 1, 3, 3);
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left + 1, pScrollBar->rcBar.top + 1, pScrollBar->rcBar.right, pScrollBar->rcBar.bottom, 3, 3);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(233, 225, 101));

				XDraw_SelectClipRgn_(hDraw, hRgn);

				//渐变填充
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &pScrollBar->rcBar, GRADIENT_FILL_RECT_H);

				//绘制内边线
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);

				//绘制外边线
				XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
		else if (STATE_DOWN == pScrollBar->rcBarState)
		{
			if (pScrollBar->hImage_down_slider)
			{
				XDraw_HImageSuper_(hDraw, pScrollBar->hImage_down_slider, &pScrollBar->rcBar);
				return;
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left, pScrollBar->rcBar.top, pScrollBar->rcBar.right + 1, pScrollBar->rcBar.bottom + 1, 3, 3);
				XDraw_SelectClipRgn_(hDraw, hRgn);
				XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &pScrollBar->rcBar, GRADIENT_FILL_RECT_H);

				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
				HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, pScrollBar->rcBar.left + 1, pScrollBar->rcBar.top + 1, pScrollBar->rcBar.right, pScrollBar->rcBar.bottom + 1, 3, 3);
				XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

				HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
				XDraw_SelectClipRgn_(hDraw, NULL);
			}
		}
	}
}

/// @brief 向左滚动或向上滚动.
/// @param hEle  元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSBar_ScrollUp(HELE hEle)   //向左滚动
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return XSBar_ScrollPos(hEle, SCROLLBAR(hEle)->curPos - 1);
}

/// @brief 向右滚动或向下滚动.
/// @param hEle  元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSBar_ScrollDown(HELE hEle)   //向右滚动
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return XSBar_ScrollPos(hEle, SCROLLBAR(hEle)->curPos + 1);
}

/// @brief 滚动到顶部.
/// @param hEle  元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSBar_ScrollTop(HELE hEle)     //滚动到顶部
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return XSBar_ScrollPos(hEle, 0);
}

/// @brief 滚动到底部.
/// @param hEle  元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSBar_ScrollBottom(HELE hEle) //滚动到底部
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	return XSBar_ScrollPos(hEle, SCROLLBAR(hEle)->range);
}

/// @brief 滚动到指定点.
/// @param hEle  元素句柄.
/// @param pos   指定滚动点.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSBar_ScrollPos(HELE hEle, int pos)  //滚动到指定点
{
	IsScrollBarDebug(hEle, __FUNCTION__);
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	if (pos < 0) pos = 0;

	if (pos > pScrollBar->range) pos = pScrollBar->range;

	if (pos == pScrollBar->curPos)
		return FALSE;

	pScrollBar->curPos = pos;

	double posSize = 0;
	if (0 != pScrollBar->range)
	{
		int size = pScrollBar->spacing - pScrollBar->barLength;
		if (0 != size)
			posSize = ((double)size) / pScrollBar->range;
	}

	int left = (int)(pos*posSize);

	if (pScrollBar->bHorizon)
	{
		if (pScrollBar->bShowButton2)
			pScrollBar->rcBar.left = left + pScrollBar->btnLength + 1;
		else
			pScrollBar->rcBar.left = left + 1;
		pScrollBar->rcBar.right = pScrollBar->rcBar.left + pScrollBar->barLength;
		Ele_SendEvent(hEle, XE_HSCROLL, pScrollBar->curPos, 0);
	}
	else
	{
		if (pScrollBar->bShowButton2)
			pScrollBar->rcBar.top = left + pScrollBar->btnLength + 1;
		else
			pScrollBar->rcBar.top = left + 1;

		pScrollBar->rcBar.bottom = pScrollBar->rcBar.top + pScrollBar->barLength;
		Ele_SendEvent(hEle, XE_VSCROLL, pScrollBar->curPos, 0);
	}
	XEle_RedrawEle(hEle);
	return TRUE;
}

BOOL CALLBACK SBar_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);

	if (pScrollBar->bShowButton2 && PtInRect(&pScrollBar->rcUp, *pPt)) //左滚动
	{
		pScrollBar->rcUpState = STATE_DOWN;
		window_ *pWindow = (window_*)XEle_GetHWindow(hEle);
		pWindow->pScrollBar = pScrollBar;
		pScrollBar->bDownUp = TRUE;
		SetTimer(pWindow->hWnd, IDT_HSCROLL_UP, 100, NULL);
		XEle_SetCapture(hEle);
		XEle_RedrawEle(hEle);
	}
	else if (pScrollBar->bShowButton2 && PtInRect(&pScrollBar->rcDown, *pPt)) //右滚动
	{
		pScrollBar->rcDownState = STATE_DOWN;
		window_ *pWindow = (window_*)XEle_GetHWindow(hEle);
		pWindow->pScrollBar = pScrollBar;
		pScrollBar->bDownDown = TRUE;
		SetTimer(pWindow->hWnd, IDT_HSCROLL_DOWN, 100, NULL);
		XEle_SetCapture(hEle);
		XEle_RedrawEle(hEle);
	}
	else
	{
		if (pScrollBar->bHorizon)
		{
			int cx = rect.right - rect.left;
			BOOL bIn = FALSE;
			if (pScrollBar->bShowButton2)
			{
				if (pPt->x > pScrollBar->btnLength && pPt->x < (cx - pScrollBar->btnLength))
					bIn = TRUE;
			}
			else
			{
				bIn = TRUE;
			}

			if (bIn)//按在滚动范围内
			{
				if (pPt->x > pScrollBar->rcBar.left && pPt->x < pScrollBar->rcBar.right)//按在滚动条上
				{
					pScrollBar->rcBarState = STATE_DOWN;
					pScrollBar->downBarPos = pPt->x - pScrollBar->rcBar.left;
					pScrollBar->bDownBar = TRUE;
					XEle_SetCapture(hEle);
					XEle_RedrawEle(hEle);
				}
				else //按在空白区
				{
					pScrollBar->bDownNull = TRUE;

					double posSize = 0;
					if (0 != pScrollBar->range)
					{
						int size = pScrollBar->spacing - pScrollBar->barLength;
						if (0 != size)
							posSize = ((double)(size)) / pScrollBar->range;
					}

					int t = 0;
					if (pScrollBar->bShowButton2)
						t = pPt->x - 1 - pScrollBar->btnLength - pScrollBar->barLength / 2;
					else
						t = pPt->x - 1 - pScrollBar->barLength / 2;

					int pos = 0;;

					if (0 != t && (FALSE == IsFlaotZero(posSize)))
						pos = (int)((t) / posSize);

					if (pos < 0)
						pos = 0;
					else if (pos > pScrollBar->range)
						pos = pScrollBar->range;
					XSBar_ScrollPos(hEle, pos);
				}
			}
		}
		else
		{
			int cy = rect.bottom - rect.top;
			BOOL bIn = FALSE;
			if (pScrollBar->bShowButton2)
			{
				if (pPt->y > pScrollBar->btnLength && pPt->y < (cy - pScrollBar->btnLength))
					bIn = TRUE;
			}
			else
			{
				bIn = TRUE;
			}

			if (bIn)//按在滚动范围内
			{
				if (pPt->y > pScrollBar->rcBar.top && pPt->y < pScrollBar->rcBar.bottom)//按在滚动条上
				{
					pScrollBar->rcBarState = STATE_DOWN;
					pScrollBar->downBarPos = pPt->y - pScrollBar->rcBar.top;
					pScrollBar->bDownBar = TRUE;
					XEle_SetCapture(hEle);
					XEle_RedrawEle(hEle);
				}
				else //按在空白区
				{
					pScrollBar->bDownNull = TRUE;

					double posSize = 0;
					if (0 != pScrollBar->range)
					{
						int size = pScrollBar->spacing - pScrollBar->barLength;
						if (0 != size)
							posSize = ((double)(size)) / pScrollBar->range;
					}

					int t = 0;
					if (pScrollBar->bShowButton2)
						t = pPt->y - 1 - pScrollBar->btnLength - pScrollBar->barLength / 2;
					else
						t = pPt->y - 1 - pScrollBar->barLength / 2;

					int pos = 0;

					if (0 != t && (FALSE == IsFlaotZero(posSize)))
						pos = (int)((t) / posSize);

					if (pos < 0)
						pos = 0;
					else if (pos > pScrollBar->range)
						pos = pScrollBar->range;
					XSBar_ScrollPos(hEle, pos);
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK SBar_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	window_ *pWindow = (window_*)XEle_GetHWindow(hEle);
	//	if(pScrollBar->bDownBar)
	if (pWindow->pCapture && hEle == pWindow->pCapture)
	{
		XEle_ReleaseCapture(hEle);
	}

	pScrollBar->bDownBar = FALSE;
	pScrollBar->bDownUp = FALSE;
	pScrollBar->bDownDown = FALSE;
	pScrollBar->bDownNull = FALSE;
	if (g_pScrollBar)
	{
		g_pScrollBar = NULL;
	}

	if (pWindow->pScrollBar)
	{
		pWindow->pScrollBar = NULL;
	}

	if (STATE_DOWN == pScrollBar->rcBarState)
	{
		pScrollBar->rcBarState = STATE_STAY;
		XEle_RedrawEle(hEle);
	}

	if (pScrollBar->bShowButton2)
	{
		if (STATE_DOWN == pScrollBar->rcUpState)
		{
			pScrollBar->rcUpState = STATE_STAY;
			XEle_RedrawEle(hEle);
		}
		else if (STATE_DOWN == pScrollBar->rcDownState)
		{
			pScrollBar->rcDownState = STATE_STAY;
			XEle_RedrawEle(hEle);
		}

	}
	return FALSE;
}

BOOL CALLBACK SBar_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	scrollBar_ *pScrollBar = SCROLLBAR(hEle);
	if (pScrollBar->bDownBar) //鼠标按在滚动条上
	{
		RECT rect;
		XEle_GetClientRect(hEle, &rect);
		if (pScrollBar->bHorizon) //水平滚动条
		{
			int left = pPt->x - pScrollBar->downBarPos;
			int cx = rect.right - rect.left;
			int up = 0;  //上范围
			int down = 0; //下范围

			if (pScrollBar->bShowButton2)
				up = pScrollBar->btnLength + 1;
			else
				up = 1;

			if (pScrollBar->bShowButton2)
				down = cx - pScrollBar->btnLength - pScrollBar->barLength - 1;
			else
				down = cx - pScrollBar->barLength - 1;

			if (left < up)
				left = up;
			else if (left > down)
				left = down;

			if (left != pScrollBar->rcBar.left) //移动滚动条
			{
				pScrollBar->rcBar.left = left;
				pScrollBar->rcBar.right = left + pScrollBar->barLength;

				double posSize = 0;
				if (0 != pScrollBar->range)
				{
					int size = pScrollBar->spacing - pScrollBar->barLength;
					if (0 != size)
						posSize = ((double)(size)) / pScrollBar->range; //每个滚动点大小
				}

				int t = left - up;
				int curPos = 0;
				if (0 != t && (FALSE == IsFlaotZero(posSize)))
					curPos = (int)((t) / posSize);

				if (curPos < 0)
					curPos = 0;
				else if (curPos > pScrollBar->range)
					curPos = pScrollBar->range;
				if (curPos != pScrollBar->curPos) //发送滚动事件
				{
					pScrollBar->curPos = curPos;
					if (NULL == g_pScrollBar)  //延时滚动事件
					{
						g_pScrollBar = pScrollBar;
						SetTimer(((ele_*)hEle)->pWindow->hWnd, IDT_HSCROLLDELAY, 50, SBar_TimerProc);
					}
					//Ele_SendEvent(hEle,XE_HSCROLL,pScrollBar->curPos,0);
				}
				XEle_RedrawEle(hEle);
			}
		}
		else //垂直滚动条
		{
			int top = pPt->y - pScrollBar->downBarPos;
			int cy = rect.bottom - rect.top;
			int up = pScrollBar->btnLength + 1;  //上范围
			int down = cy - pScrollBar->btnLength - pScrollBar->barLength - 1; //下范围

			if (pScrollBar->bShowButton2)
				up = pScrollBar->btnLength + 1;
			else
				up = 1;

			if (pScrollBar->bShowButton2)
				down = cy - pScrollBar->btnLength - pScrollBar->barLength - 1;
			else
				down = cy - pScrollBar->barLength - 1;

			if (top < up)
				top = up;
			else if (top > down)
				top = down;

			if (top != pScrollBar->rcBar.top) //移动滚动条
			{
				pScrollBar->rcBar.top = top;
				pScrollBar->rcBar.bottom = top + pScrollBar->barLength;

				double posSize = 0;
				if (0 != pScrollBar->range)
				{
					int size = pScrollBar->spacing - pScrollBar->barLength;
					if (0 != size)
						posSize = ((double)(size)) / pScrollBar->range; //每个滚动点大小
				}

				int curPos = 0;
				if (FALSE == IsFlaotZero(posSize))
				{
					int t = top - up;
					if (0 != t)
						curPos = (int)(t / posSize);
				}

				if (curPos < 0)
					curPos = 0;
				else if (curPos > pScrollBar->range)
					curPos = pScrollBar->range;

				if (curPos != pScrollBar->curPos) //发送滚动事件
				{
					pScrollBar->curPos = curPos;
					if (NULL == g_pScrollBar) //延时滚动事件
					{
						g_pScrollBar = pScrollBar;
						SetTimer(((ele_*)hEle)->pWindow->hWnd, IDT_VSCROLLDELAY, 50, SBar_TimerProc);
					}
					//	Ele_SendEvent(hEle,XE_VSCROLL,pScrollBar->curPos,0);
				}
				XEle_RedrawEle(hEle);
			}
		}
		return FALSE;
	}
	else if (pScrollBar->bDownUp) //鼠标按在上按钮
	{
		return FALSE;
	}
	else if (pScrollBar->bDownDown) //鼠标按在下按钮
	{
		return FALSE;
	}
	/////////////////////////////////////////////////////////////

	if (pScrollBar->bShowButton2 && PtInRect(&pScrollBar->rcUp, *pPt))
	{
		if (pScrollBar->MouseTop != 1)
		{
			if (2 == pScrollBar->MouseTop)
			{
				pScrollBar->rcDownState = STATE_LEAVE;
			}
			else if (3 == pScrollBar->MouseTop)
			{
				pScrollBar->rcBarState = STATE_LEAVE;
			}
			pScrollBar->MouseTop = 1;
			pScrollBar->rcUpState = STATE_STAY;
			XEle_RedrawEle(hEle);
		}
	}
	else if (pScrollBar->bShowButton2 && PtInRect(&pScrollBar->rcDown, *pPt))
	{
		if (pScrollBar->MouseTop != 2)
		{
			if (1 == pScrollBar->MouseTop)
			{
				pScrollBar->rcUpState = STATE_LEAVE;
			}
			else if (3 == pScrollBar->MouseTop)
			{
				pScrollBar->rcBarState = STATE_LEAVE;
			}
			pScrollBar->MouseTop = 2;
			pScrollBar->rcDownState = STATE_STAY;
			XEle_RedrawEle(hEle);
		}
	}
	else if (PtInRect(&pScrollBar->rcBar, *pPt))
	{
		if (pScrollBar->MouseTop != 3)
		{
			if (1 == pScrollBar->MouseTop)
			{
				pScrollBar->rcUpState = STATE_LEAVE;
			}
			else if (2 == pScrollBar->MouseTop)
			{
				pScrollBar->rcDownState = STATE_LEAVE;
			}
			pScrollBar->MouseTop = 3;
			pScrollBar->rcBarState = STATE_STAY;
			XEle_RedrawEle(hEle);
		}
	}
	else
	{
		if (1 == pScrollBar->MouseTop)
		{
			pScrollBar->rcUpState = STATE_LEAVE;
			pScrollBar->MouseTop = 0;
			XEle_RedrawEle(hEle);
		}if (2 == pScrollBar->MouseTop)
		{
			pScrollBar->rcDownState = STATE_LEAVE;
			pScrollBar->MouseTop = 0;
			XEle_RedrawEle(hEle);
		}
		else if (3 == pScrollBar->MouseTop)
		{
			pScrollBar->rcBarState = STATE_LEAVE;
			pScrollBar->MouseTop = 0;
			XEle_RedrawEle(hEle);
		}
	}

	return FALSE;
}

BOOL CALLBACK SBar_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		scrollBar_ *pScrollBar = SCROLLBAR(hEle);
		if (1 == pScrollBar->MouseTop)
		{
			pScrollBar->rcUpState = STATE_LEAVE;
			pScrollBar->MouseTop = 0;
			XEle_RedrawEle(hEle);
			//XTRACE("离开\n");
		}if (2 == pScrollBar->MouseTop)
		{
			pScrollBar->rcDownState = STATE_LEAVE;
			pScrollBar->MouseTop = 0;
			XEle_RedrawEle(hEle);
		}
		else if (3 == pScrollBar->MouseTop)
		{
			pScrollBar->rcBarState = STATE_LEAVE;
			pScrollBar->MouseTop = 0;
			XEle_RedrawEle(hEle);
		}

		if (((ele_*)hEle)->pWindow->pScrollBar)
		{
			((ele_*)hEle)->pWindow->pScrollBar = NULL;
		}
	}
	return FALSE;
}

BOOL CALLBACK SBar_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		XSBar_Adjust(hEle);
	}
	return FALSE;
}

void CALLBACK SBar_OnDestroy(HELE hEle)  //销毁
{
	if (SCROLLBAR(hEle)->hImage_bk) XImage_Destroy(SCROLLBAR(hEle)->hImage_bk);
	if (SCROLLBAR(hEle)->hImage_Leave_up) XImage_Destroy(SCROLLBAR(hEle)->hImage_Leave_up);
	if (SCROLLBAR(hEle)->hImage_stay_up) XImage_Destroy(SCROLLBAR(hEle)->hImage_stay_up);
	if (SCROLLBAR(hEle)->hImage_down_up) XImage_Destroy(SCROLLBAR(hEle)->hImage_down_up);
	if (SCROLLBAR(hEle)->hImage_Leave_down) XImage_Destroy(SCROLLBAR(hEle)->hImage_Leave_down);
	if (SCROLLBAR(hEle)->hImage_stay_down) XImage_Destroy(SCROLLBAR(hEle)->hImage_stay_down);
	if (SCROLLBAR(hEle)->hImage_down_down) XImage_Destroy(SCROLLBAR(hEle)->hImage_down_down);
	if (SCROLLBAR(hEle)->hImage_Leave_slider) XImage_Destroy(SCROLLBAR(hEle)->hImage_Leave_slider);
	if (SCROLLBAR(hEle)->hImage_stay_slider) XImage_Destroy(SCROLLBAR(hEle)->hImage_stay_slider);
	if (SCROLLBAR(hEle)->hImage_down_slider) XImage_Destroy(SCROLLBAR(hEle)->hImage_down_slider);
}
///@}


//定时器，增加滚动延时
scrollBar_  *g_pScrollBar = NULL;
int         g_previou = -1;        //先前滚动点
VOID CALLBACK SBar_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (g_pScrollBar)
	{
		if (IDT_HSCROLLDELAY == idEvent) //水平滚动条
		{
			if (g_previou != g_pScrollBar->curPos)
			{
				g_previou = g_pScrollBar->curPos;
				Ele_SendEvent((HELE)g_pScrollBar, XE_HSCROLL, g_pScrollBar->curPos, 0);
				//	XTRACE("水平滚动,pos=%d\n",g_pScrollBar->curPos);
			}
		}
		else if (IDT_VSCROLLDELAY == idEvent) //垂直滚动条
		{
			if (g_previou != g_pScrollBar->curPos)
			{
				g_previou = g_pScrollBar->curPos;
				Ele_SendEvent((HELE)g_pScrollBar, XE_VSCROLL, g_pScrollBar->curPos, 0);
				//	XTRACE("垂直滚动,pos=%d\n",g_pScrollBar->curPos);
			}
		}
	}
	else
	{
		g_previou = -1;
		KillTimer(hwnd, idEvent);
	}
}