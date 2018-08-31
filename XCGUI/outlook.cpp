/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HELE WINAPI XOutlook_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	outlook_ *pObj = (outlook_*)malloc(sizeof(outlook_));
	memset(pObj, 0, sizeof(outlook_));

	Outlook_Init((HELE)pObj, x, y, cx, cy, XC_OUTLOOK, NULL, hParent);
	return (HELE)pObj;
}

void Outlook_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_OUTLOOK);
	((outlook_*)hEle)->hArrayItem = XArray_Create();
	((outlook_*)hEle)->index = 0;
	((outlook_*)hEle)->bAdjust = FALSE;
	((outlook_*)hEle)->buttonHeight = 25;

	XEle_RegisterMessage(hEle, XM_PAINT, Outlook_OnDraw);
	XEle_RegisterEvent(hEle, XE_SIZE, Outlook_OnEventSize);
	XEle_RegisterEvent(hEle, XE_DESTROY, Outlook_OnDestroy);
}

void CALLBACK Outlook_OnDestroy(HELE hEle)
{
	outlook_  *pObj = (outlook_*)hEle;
	int count = XArray_GetCount(pObj->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		void *pItem = XArray_GetAt(pObj->hArrayItem, i);
		free(pItem);
	}
	XArray_Destroy(pObj->hArrayItem);
}

void WINAPI XOutlook_AddView(HELE hEle, HELE hView, wchar_t *pTitle)
{
	if (NULL == pTitle)
		return;

	outlook_ *pObj = (outlook_*)hEle;

	outlook_Item_ *pItem = (outlook_Item_*)malloc(sizeof(outlook_Item_));
	pItem->hButton = XBtn_Create(0, 0, 10, 10, pTitle, hEle);
	pItem->hView = hView;

	XArray_Add(pObj->hArrayItem, pItem);
	XEle_AddEle(hEle, hView);

	pObj->bAdjust = TRUE;

	XEle_EnableFocus(pItem->hButton, FALSE);
	XEle_RegisterMessage(pItem->hButton, XM_PAINT, Outlook_OnDrawButton);
	XEle_RegisterEvent(pItem->hButton, XE_BNCLICK, Outlook_OnEventBtnClick);
}

void WINAPI XOutlook_Adjust(HELE hEle)
{
	outlook_  *pObj = (outlook_*)hEle;
	pObj->bAdjust = FALSE;
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	RECT rcEle;
	int count = XArray_GetCount(pObj->hArrayItem);
	int posy = 2;
	outlook_Item_ *pItem = NULL;
	for (int i = 0; i < count; i++)
	{
		pItem = (outlook_Item_*)XArray_GetAt(pObj->hArrayItem, i);

		rcEle.left = 2;
		rcEle.right = rect.right - 2;
		rcEle.top = posy;
		rcEle.bottom = rcEle.top + pObj->buttonHeight;
		XEle_SetRect(pItem->hButton, &rcEle);

		if (pItem->hView)
		{
			if (pObj->index == i)
			{
				rcEle.top = rcEle.bottom + 1;
				rcEle.bottom = rect.bottom - (count - i - 1)*(pObj->buttonHeight + 1) - 2;
				XEle_SetRect(pItem->hView, &rcEle);
				XEle_ShowEle(pItem->hView, TRUE);
			}
			else
			{
				XEle_ShowEle(pItem->hView, FALSE);
			}
		}
		posy = rcEle.bottom + 1;
	}
}

void WINAPI XOutlook_Expand(HELE hEle, int index)
{
	((outlook_*)hEle)->index = index;
	XOutlook_Adjust(hEle);
	XEle_RedrawEle(hEle);
}

int WINAPI XOutlook_GetExpand(HELE hEle) //获取当前展开的项索引
{
	return ((outlook_*)hEle)->index;
}

BOOL CALLBACK Outlook_OnDraw(HELE hEle, HDRAW hDraw)
{
	if (((outlook_*)hEle)->bAdjust)
		XOutlook_Adjust(hEle);

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (((ele_*)hEle)->bBorder)
	{
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, ((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		//DeleteObject(hBrush);
	}

	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	XDraw_FrameRect_(hDraw, &rect, hBrush);
	//DeleteObject(hBrush);
	return TRUE;
}

BOOL CALLBACK Outlook_OnDrawButton(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	RECT rcText = rect;

	wchar_t *pText = XBtn_GetText(hEle);
	int state = XBtn_GetState(hEle);

	if (STATE_LEAVE == state)
	{
		//渐变填充
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);

		//绘制内边线
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
		RECT rc = { 1,1,rect.right - 1,rect.bottom - 1 };
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//DeleteObject(hBrush);

		//绘制外边线
		hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_SelectClipRgn_(hDraw, NULL);
		//DeleteObject(hBrush);

	}
	else if (STATE_STAY == state)
	{
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		//DeleteObject(hBrush);

		RECT rc = { 1,1,rect.right - 1,rect.bottom - 1 };
		hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(252, 194, 71));
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//DeleteObject(hBrush);
	}
	else if (STATE_DOWN == state)
	{
		XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
		RECT rc = { 1,1,rect.right - 1,rect.bottom - 1 };
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//DeleteObject(hBrush);

		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
		XDraw_FrameRect_(hDraw, &rect, hBrush2);
		//DeleteObject(hBrush2);

		rcText.left += 2;
		rcText.top += 2;
	}

	if (pText)
		XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	return TRUE;
}

BOOL CALLBACK Outlook_OnEventBtnClick(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	outlook_ *pObj = (outlook_*)XEle_GetParentEle(hEventEle);
	if (pObj)
	{
		int count = XArray_GetCount(pObj->hArrayItem);
		if (count < 2) return TRUE;

		for (int i = 0; i < count; i++)
		{
			if (hEventEle == ((outlook_Item_*)XArray_GetAt(pObj->hArrayItem, i))->hButton)
			{
				if (i == pObj->index)
				{
					XOutlook_Expand((HELE)pObj, count - 1);
				}
				else
				{
					XOutlook_Expand((HELE)pObj, i);
				}
				break;
			}
		}
	}

	return TRUE;
}

BOOL CALLBACK Outlook_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		XOutlook_Adjust(hEle);
	}
	return FALSE;
}