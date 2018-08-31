/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

HWINDOW ComboBoxWnd_CreateWindow(int x, int y, int cx, int cy, HWND hWndParent, HELE hComboBox)
{
	comboBoxWindow_ *pObj = (comboBoxWindow_*)malloc(sizeof(comboBoxWindow_));
	memset(pObj, 0, sizeof(comboBoxWindow_));
	pObj->hComboBox = hComboBox;
	if (FALSE == ComboBoxWnd_Init((HWINDOW)pObj, x, y, cx, cy, hWndParent, XC_COMBOBOXWINDOW))
	{
		free(pObj);
		return NULL;
	}
	return (HWINDOW)pObj;
}

BOOL ComboBoxWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, HWND hWndParent, int exType)
{
	BOOL res = Wnd_Init(hWindow, WS_EX_PALETTEWINDOW | WS_EX_TOOLWINDOW | WS_EX_TOPMOST, NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS, x, y, cx, cy, hWndParent, 0, exType);
	if (res)
	{
		AddTypeDebug(hWindow, XC_COMBOBOXWINDOW);

		HARRAY hArrayStr = ((comboBox_*)((comboBoxWindow_*)hWindow)->hComboBox)->hArrayStr;
		HELE hListBox = ((comboBoxWindow_*)hWindow)->hListBox = XListBox_Create(0, 0, cx, cy, hWindow);

		XListBox_SetItemHeight(hListBox, XComboBox_GetItemHeight(((comboBoxWindow_*)hWindow)->hComboBox));

		int count = XArray_GetCount(hArrayStr);
		for (int i = 0; i < count; i++)
			XListBox_AddString(hListBox, (wchar_t*)XArray_GetAt(hArrayStr, i));

		XWnd_RegisterMessage(hWindow, WM_PAINT, ComboBoxWnd_OnDrawWindow);;
		XWnd_RegisterMessage(hWindow, WM_KILLFOCUS, ComboBoxWnd_OnKillFocus);
		XEle_RegisterEvent(hListBox, XE_LISTBOX_SELECT, ComboBoxWnd_OnEventListBoxSelect);
	}
	return res;
}

BOOL CALLBACK ComboBoxWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	RECT rect;
	GetClientRect(((window_*)hWindow)->hWnd, &rect);

	HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(130, 130, 130));
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(255, 255, 255));
	HGDIOBJ hOld1 = XDraw_SelectObject_(hDraw, hPen);
	HGDIOBJ hOld2 = XDraw_SelectObject_(hDraw, hBrush);

	XDraw_Rectangle_(hDraw, 0, 0, rect.right, rect.bottom);//填充背景

//	SelectObject(hdc,hOld1);
//	SelectObject(hdc,hOld2);
//	DeleteObject(hPen);
//	DeleteObject(hBrush);

	return TRUE;
}

BOOL CALLBACK ComboBoxWnd_OnKillFocus(HWINDOW hWindow)
{
	//	comboBoxWindow_ *pWnd=COMBOBOXWINDOW(hWindow);
		//ComboBox_DestroyPopupWnd(pWnd->hComboBox);
	return TRUE;
}

BOOL CALLBACK ComboBoxWnd_OnEventListBoxSelect(HELE hEle, HELE hEventEle, int index)
{
	if (hEle == hEventEle)
	{
		if (index >= 0)
		{
			HWINDOW hWindow = XEle_GetHWindow(hEle);
			comboBoxWindow_ *pWnd = COMBOBOXWINDOW(hWindow);
			comboBox_ *pComboBox = (comboBox_*)pWnd->hComboBox;
			HWND hWnd = XWnd_GetHWnd(hWindow);

			ComboBoxWnd_SendEvent(pComboBox, index);
			if (IsWindow(hWnd))
			{
				ComboBox_DestroyPopupWnd(pWnd->hComboBox);
			}
		}
	}
	return TRUE;
}

void ComboBoxWnd_SendEvent(comboBox_ *pComboBox, int index)
{
	HELE hComboBox = (HELE)pComboBox;

	wchar_t *pTextSel = (wchar_t*)XArray_GetAt(pComboBox->hArrayStr, index);
	//检查如果内容不一样,内容改变
	int length = XEdit_GetTextLength(hComboBox);
	if (length > 0)
	{
		length++;
		wchar_t *pText = (wchar_t*)malloc(sizeof(wchar_t)*length);
		XComboBox_GetText(hComboBox, pText, length);
		if (0 == wcscmp(pText, pTextSel))
		{
			free(pText);
			return;
		}
		else
		{
			free(pText);
		}
	}
	if (pComboBox->curSel != index)
	{
		pComboBox->curSel = index;
	}
	//发送事件 下拉列表,选择项 正在改变
	BOOL bChange = FALSE;
	Ele_SendEvent(hComboBox, XE_COMBOBOX_SELECT_ING, index, (LPARAM)&bChange);

	//发送事件 下拉界面,选择项 已经改变
	if (!bChange)
	{
		XEdit_SetText(hComboBox, pTextSel);
		Ele_SendEvent(hComboBox, XE_COMBOBOX_SELECT, index, 0);  //发送下拉列表项选择事件
	}
}