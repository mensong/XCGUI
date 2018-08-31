/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup textLink 静态文本连接元素(TextLink)
/// @ingroup groupElements
/// @{

/// @brief 创建静态文本连接元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param pTitle 文本内容.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XTextLink_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent)
{
	textLink_ *pNew = (textLink_*)malloc(sizeof(textLink_));
	memset(pNew, 0, sizeof(textLink_));

	TextLink_Init((HELE)pNew, x, y, cx, cy, XC_TEXTLINK, pTitle, hParent);
	return (HELE)pNew;
}

void TextLink_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent)
{
	Btn_Init(hEle, x, y, cx, cy, eleType, pTitle, hParent);

	AddTypeDebug(hEle, XC_TEXTLINK);

	((button_*)hEle)->textFlag = DT_VCENTER | DT_SINGLELINE;
	((textLink_*)hEle)->colorStay = RGB(0, 0, 255);
	((textLink_*)hEle)->bUnderline_leave = FALSE;
	((textLink_*)hEle)->bUnderline_stay = TRUE;

	XEle_RegisterMessage(hEle, XM_PAINT, TextLink_OnDraw);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, TextLink_OnMouseMove);

	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, TextLink_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, TextLink_OnLButtonUp);
}

/// @brief 设置鼠标停留时文本颜色.
/// @param hEle   元素句柄
/// @param color  文本颜色.
void WINAPI XTextLink_SetStayColor(HELE hEle, COLORREF color)
{
	IsTextLinkDebug(hEle, __FUNCTION__);
	((textLink_*)hEle)->colorStay = color;
}

/// @brief 获取鼠标停留时文本颜色.
/// @param hEle   元素句柄
/// @return  文本颜色.
COLORREF WINAPI XTextLink_GetStayColor(HELE hEle)
{
	IsTextLinkDebug(hEle, __FUNCTION__);
	return ((textLink_*)hEle)->colorStay;
}

/// @brief 根据文本内容,调整元素大小.
/// @param hEle   元素句柄
void WINAPI XTextLink_AdjustSize(HELE hEle)  //根据文本内容,调整元素大小
{
	IsTextLinkDebug(hEle, __FUNCTION__);
	wchar_t *pText = XBtn_GetText(hEle);
	if (NULL == pText) return;

	RECT rc = { 0,0,20,20 };
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOld = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	if (0 == DrawText(hdc, pText, wcslen(pText), &rc, (BUTTON(hEle)->textFlag | DT_CALCRECT) & ~DT_END_ELLIPSIS))
	{
		SelectObject(hdc, hOld);
		ReleaseDC(NULL, hdc);
		return;
	}
	SelectObject(hdc, hOld);
	ReleaseDC(NULL, hdc);

	rc.left += ((ele_*)hEle)->rect.left;
	rc.top += ((ele_*)hEle)->rect.top;
	rc.right += ((ele_*)hEle)->rect.left;
	rc.bottom += ((ele_*)hEle)->rect.top;
	rc.right += 4;
	rc.bottom += 4;
	XEle_SetRect(hEle, &rc);
}

/// @brief 显示下划线.
/// @param hEle   元素句柄
/// @param bLeave 当鼠标离开状态,是否显示下划线.
/// @param bStay  当鼠标停留状态,是否显示下划线.
void WINAPI XTextLink_ShowUnderline(HELE hEle, BOOL bLeave, BOOL bStay)  //显示下划线
{
	IsTextLinkDebug(hEle, __FUNCTION__);
	((textLink_*)hEle)->bUnderline_leave = bLeave;
	((textLink_*)hEle)->bUnderline_stay = bStay;
}

BOOL CALLBACK TextLink_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	RECT rcText = rect;

	button_ *pObj = BUTTON(hEle);
	wchar_t *pText = NULL;
	if (pObj->hString)
		pText = XStr_GetBuffer(pObj->hString);

	if (FALSE == ((ele_*)hEle)->bEnable) //禁用
	{
		if (pObj->hImage_disable)
		{
			XDraw_HImageSuper_(hDraw, pObj->hImage_disable, &rect);
		}
		else
		{
		}
		//绘制禁用状态按钮
/*		COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		if(pText)
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		XDraw_SetTextColor_(hDraw,color);
		return TRUE;*/
	}
	if (BUTTON(hEle)->bCheck && pObj->hImage_check) //选中 有图片
	{
		XDraw_HImageSuper_(hDraw, pObj->hImage_check, &rect);
		if (pText)
			XDraw_DrawText_(hDraw, pText, XStr_GetLength(pObj->hString), &rcText, ((button_*)hEle)->textFlag);

		if (((ele_*)hEle)->bDrawFocus && hEle == XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //绘制焦点
		{
			RECT rcFocus = { 2,2,rect.right - 2,rect.bottom - 2 };
			XDraw_FocusRect_(hDraw, &rcFocus);
		}
		return TRUE;
	}
	if (STATE_LEAVE == BUTTON(hEle)->state)
	{
		if (pObj->hImage_leave)
		{
			XDraw_HImageSuper_(hDraw, pObj->hImage_leave, &rect);
		}
		else
		{
			if (pText)
			{
				XDraw_DrawText_(hDraw, pText, XStr_GetLength(pObj->hString), &rcText, ((button_*)hEle)->textFlag);

				//绘制下划线
				if (((textLink_*)hEle)->bUnderline_leave)
				{
					HDC hdc = XDraw_GetHDC_(hDraw);
					SIZE size;
					GetTextExtentPoint32W(hdc, pText, XStr_GetLength(pObj->hString), &size);

					HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, ((ele_*)hEle)->textColor);
					HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
					int top = rcText.top + (rcText.bottom - rcText.top) / 2 + size.cy / 2;
					XDraw_MoveToEx_(hDraw, rcText.left, top, NULL);
					XDraw_LineTo_(hDraw, size.cx, top);
				}
			}
		}
	}
	else if (STATE_STAY == BUTTON(hEle)->state)
	{
		if (pObj->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw, pObj->hImage_stay, &rect);
		}
		else
		{
			if (pText)
			{
				COLORREF color = XDraw_SetTextColor_(hDraw, ((textLink_*)hEle)->colorStay);
				XDraw_DrawText_(hDraw, pText, XStr_GetLength(pObj->hString), &rcText, ((button_*)hEle)->textFlag);
				XDraw_SetTextColor_(hDraw, color);

				//绘制下划线
				if (((textLink_*)hEle)->bUnderline_stay)
				{
					HDC hdc = XDraw_GetHDC_(hDraw);
					SIZE size;
					GetTextExtentPoint32W(hdc, pText, XStr_GetLength(pObj->hString), &size);

					HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, ((textLink_*)hEle)->colorStay);
					HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
					int top = rcText.top + (rcText.bottom - rcText.top) / 2 + size.cy / 2;
					XDraw_MoveToEx_(hDraw, rcText.left, top, NULL);
					XDraw_LineTo_(hDraw, size.cx, top);
				}
			}
		}
	}
	else if (STATE_DOWN == BUTTON(hEle)->state || BUTTON(hEle)->bCheck)
	{
		if (pObj->hImage_down)
		{
			XDraw_HImageSuper_(hDraw, pObj->hImage_down, &rect);
		}
		else
		{
			COLORREF color = XDraw_SetTextColor_(hDraw, ((textLink_*)hEle)->colorStay);
			XDraw_DrawText_(hDraw, pText, XStr_GetLength(pObj->hString), &rcText, ((button_*)hEle)->textFlag);
			XDraw_SetTextColor_(hDraw, color);

			//绘制下划线
			if (((textLink_*)hEle)->bUnderline_stay)
			{
				HDC hdc = XDraw_GetHDC_(hDraw);
				SIZE size;
				GetTextExtentPoint32W(hdc, pText, XStr_GetLength(pObj->hString), &size);

				HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, ((textLink_*)hEle)->colorStay);
				HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
				int top = rcText.top + (rcText.bottom - rcText.top) / 2 + size.cy / 2;
				XDraw_MoveToEx_(hDraw, rcText.left, top, NULL);
				XDraw_LineTo_(hDraw, size.cx, top);
			}
		}
	}

	if (((ele_*)hEle)->bDrawFocus && hEle == XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //绘制焦点
	{
		RECT rcFocus = { 0,0,rect.right,rect.bottom };
		XDraw_FocusRect_(hDraw, &rcFocus);
	}
	return TRUE;
}

BOOL CALLBACK TextLink_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	return FALSE;
}
BOOL CALLBACK TextLink_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	return FALSE;
}

BOOL CALLBACK TextLink_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	return FALSE;
}


///@}