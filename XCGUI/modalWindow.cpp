/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

int  g_modal_returnValue = 0;  //返回值


/// @defgroup modalWindow 模态窗口
/// @ingroup groupWindows
/// @{

/// @brief 创建模态窗口;当模态窗口关闭时,会自动销毁模态窗口资源句柄. 默认情况下,模态窗口会基于父窗口坐标居中显示.
/// @param width  宽度.
/// @param height 高度.
/// @param pTitle 窗口标题内容.
/// @param hWndParent 父窗口句柄.
/// @param XCStyle  炫彩窗口样式,样式请参见宏定义.
/// @return 模态窗口句柄.
HWINDOW WINAPI XModalWnd_CreateWindow(int width, int height, wchar_t *pTitle, HWND hWndParent, int XCStyle)
{
	modalWindow_ *pObj = (modalWindow_*)malloc(sizeof(modalWindow_));
	memset(pObj, 0, sizeof(modalWindow_));
	BOOL res = ModalWnd_Init((HWINDOW)pObj, NULL, NULL, pTitle, NULL, width, height, hWndParent, XCStyle, XC_MODALWINDOW);
	//XC_SY_CLOSE | XC_SY_CAPTION | XC_SY_BORDER | XC_SY_ROUND | XC_SY_CENTER,XC_MODALWINDOW);
	if (res)
		return (HWINDOW)pObj;

	return NULL;
}

BOOL ModalWnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int width, int height, HWND hWndParent, int XCStyle, int exType)
{
	int posx = 0;
	int posy = 0;
	RECT rect;
	if (hWndParent)
	{
		GetWindowRect(hWndParent, &rect);
		posx = rect.left + (rect.right - rect.left) / 2;
		posx = posx - width / 2;

		posy = rect.top + (rect.bottom - rect.top) / 2;
		posy = posy - height / 2;
	}
	else
	{
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		posx = (rect.right - rect.left) / 2;
		posx = posx - width / 2;

		posy = (rect.bottom - rect.top) / 2;
		posy = posy - height / 2;
	}
	BOOL res = Wnd_Init(hWindow, dwExStyle, lpClassName, lpWindowName, dwStyle, posx, posy, width, height, hWndParent, XCStyle, exType);
	if (res)
	{
		AddTypeDebug(hWindow, XC_MODALWINDOW);

		g_modal_returnValue = 0;

		//	XWnd_EnableDragBorder(hWindow,FALSE);
		XWnd_RegisterMessage(hWindow, WM_DESTROY, ModalWnd_OnDestroy);
		XWnd_RegisterMessage(hWindow, WM_CLOSE, ModalWnd_OnClose);
	}
	return res;
}

/// @brief  启动显示模态窗口,当窗口关闭时返回.
/// @param  hWindow 模态窗口句柄.
/// @return XMB_OK:点击确定按钮退出.XMB_CANCEL:点击取消按钮退出.如果返回0,其他方式退出.
int WINAPI XModalWnd_DoModal(HWINDOW hWindow)     //启动模态窗口
{
	IsModalWindowDebug(hWindow, __FUNCTION__);

	modalWindow_ *pModalWnd = MODALWINDOW(hWindow);
	HWND hWnd = pModalWnd->window.hWnd;
	HWND hWndParent = GetParent(hWnd);
	if (NULL == hWndParent)
	{
		return -1;
	}

	if (NULL == IsWindow(hWnd))
	{
		::MessageBox(NULL, L"该窗口未创建", L"错误提示", MB_OK);
		return FALSE;
	}
	if (!IsWindowVisible(hWnd))
		::ShowWindow(hWnd, SW_SHOW);

	if (((window_*)hWindow)->transparentFlag & XC_WIND_TRANSPARENT_SHAPED || ((window_*)hWindow)->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
	{
		XWnd_RedrawWnd(hWindow);
	}

	if (GetCapture())
		ReleaseCapture();


	if (NULL == pModalWnd->hArrayWnd)
		pModalWnd->hArrayWnd = XArray_Create();

	while (hWndParent)
	{
		LONG_PTR style = GetWindowLongPtr(hWndParent, GWL_STYLE);
		if (!(style & WS_DISABLED))
		{
			style = style | WS_DISABLED;
			SetWindowLongPtr(hWndParent, GWL_STYLE, style);
			XArray_Add(pModalWnd->hArrayWnd, hWndParent);
		}
		hWndParent = GetParent(hWndParent);
	}

	MSG msg;
	while (IsWindow(hWnd) && GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//	XTRACE("退出循环 \n");
	return g_modal_returnValue;
}

/// @brief  关闭模态窗口,XModalWnd_DoModal()返回XMB_OK.
/// @param  hWindow 模态窗口句柄.
void WINAPI XModalWnd_DoOk(HWINDOW hWindow)       //确定
{
	IsModalWindowDebug(hWindow, __FUNCTION__);
	g_modal_returnValue = XMB_OK;
	::PostMessage(WINDOW(hWindow)->hWnd, WM_CLOSE, 0, 0);
}

/// @brief  关闭模态窗口,触发取消按钮;XModalWnd_DoModal()返回XMB_CANCEL.
/// @param  hWindow 模态窗口句柄.
void WINAPI XModalWnd_DoCancel(HWINDOW hWindow)   //取消
{
	IsModalWindowDebug(hWindow, __FUNCTION__);
	g_modal_returnValue = XMB_CANCEL;
	::PostMessage(WINDOW(hWindow)->hWnd, WM_CLOSE, 0, 0);
}

BOOL CALLBACK ModalWnd_OnClose(HWINDOW hWindow)
{
	modalWindow_ *pModalWnd = MODALWINDOW(hWindow);
	if (pModalWnd->hArrayWnd)
	{
		int count = XArray_GetCount(pModalWnd->hArrayWnd);
		for (int i = 0; i < count; i++)
		{
			HWND hWndParent = (HWND)XArray_GetAt(pModalWnd->hArrayWnd, i);
			if (IsWindow(hWndParent))
			{
				LONG_PTR style = GetWindowLongPtr(hWndParent, GWL_STYLE);
				if (style & WS_DISABLED)
				{
					style = style & (~WS_DISABLED);
					SetWindowLongPtr(hWndParent, GWL_STYLE, style);
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK ModalWnd_OnDestroy(HWINDOW hWindow)
{
	modalWindow_ *pModalWnd = MODALWINDOW(hWindow);
	if (pModalWnd->hArrayWnd)
		XArray_Destroy(pModalWnd->hArrayWnd);

	PostQuitMessage(0);
	return FALSE;
}

///@}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

int MsgBox_DoModal(HWND hWndParent, wchar_t *pText, wchar_t *pCaption, int type) //启动模态窗口
{
	//if(NULL==hWndParent) return -1;

	//获取父窗口坐标
	RECT rect;
	GetClientRect(hWndParent, &rect);

	//获取文本区域大小
	RECT rcText = { 0,0,0,0 };
	if (pText)
	{
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
		DrawText(hdc, pText, wcslen(pText), &rcText, DT_CALCRECT);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);
	}
	int cx = rcText.right + 40;
	int cy = rcText.bottom + 30 + 70;

	if (cx < 170) cx = 170;

	////////////////////////////////////////////
	messageBoxWnd_ *pObj = (messageBoxWnd_*)malloc(sizeof(messageBoxWnd_));
	memset(pObj, 0, sizeof(messageBoxWnd_));

	BOOL res = ModalWnd_Init((HWINDOW)pObj, NULL, NULL, pCaption, NULL, cx, cy, hWndParent, XC_SY_MODAL_WINDOW, XC_MSGBOXWINDOW);//XC_SY_CAPTION | XC_SY_BORDER| XC_SY_CLOSE | XC_SY_ROUND | XC_SY_CENTER,XC_MSGBOXWINDOW);
	if (res)
	{
		AddTypeDebug(pObj, XC_MSGBOXWINDOW);

		pObj->sizeText.cx = rcText.right;
		pObj->sizeText.cy = rcText.bottom;
		pObj->type = type;
		XWnd_SetBorderSize((HWINDOW)pObj, 4, 4, 4, 4);

		MsgBox_CreateButton((HWINDOW)pObj);
		if (pText)
		{
			pObj->hString = XStr_Create();
			XStr_SetString(pObj->hString, pText);
		}
		XWnd_EnableDragBorder((HWINDOW)pObj, FALSE);
		XWnd_RegisterMessage((HWINDOW)pObj, WM_PAINT, MsgBox_OnDrawWindow);
		XWnd_RegisterMessage((HWINDOW)pObj, WM_DESTROY, MsgBox_OnDestroy);
		return XModalWnd_DoModal((HWINDOW)pObj);
	}
	return -1;
}

BOOL CALLBACK MsgBox_OnDestroy(HWINDOW hWindow)
{
	if (((messageBoxWnd_*)hWindow)->hString)
		XStr_Destroy(((messageBoxWnd_*)hWindow)->hString);
	return FALSE;
}

void MsgBox_CreateButton(HWINDOW hWindow)
{
	messageBoxWnd_ *pObj = (messageBoxWnd_*)hWindow;
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	if ((pObj->type & XMB_OK) && (pObj->type & XMB_CANCEL))
	{
		pObj->hBtnOk = XBtn_Create(rect.right / 2 - 70, rect.bottom - 35, 60, 22, L"确定", hWindow);
		pObj->hBtnCancel = XBtn_Create(rect.right / 2 + 10, rect.bottom - 35, 60, 22, L"取消", hWindow);
		XEle_SetFocus(pObj->hBtnOk, TRUE);
		XEle_RegisterEvent(pObj->hBtnOk, XE_BNCLICK, MsgBox_OnEventBtnClickOk);
		XEle_RegisterEvent(pObj->hBtnCancel, XE_BNCLICK, MsgBox_OnEventBtnClickCancel);
	}
	else if (pObj->type & XMB_OK)
	{
		pObj->hBtnOk = XBtn_Create(rect.right / 2 - 30, rect.bottom - 35, 60, 22, L"确定", hWindow);
		XEle_SetFocus(pObj->hBtnOk, TRUE);
		XEle_RegisterEvent(pObj->hBtnOk, XE_BNCLICK, MsgBox_OnEventBtnClickOk);
	}
	else if (pObj->type & XMB_CANCEL)
	{
		pObj->hBtnCancel = XBtn_Create(rect.right / 2 - 30, rect.bottom - 35, 60, 22, L"取消", hWindow);
		XEle_SetFocus(pObj->hBtnCancel, TRUE);
		XEle_RegisterEvent(pObj->hBtnCancel, XE_BNCLICK, MsgBox_OnEventBtnClickCancel);
	}
}

BOOL CALLBACK MsgBox_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	messageBoxWnd_ *pObj = (messageBoxWnd_*)hWindow;
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	XDraw_FillSolidRect_(hDraw, &rect, RGB(240, 240, 240));

	if (pObj->hString)
	{
		wchar_t *pText = XStr_GetBuffer(pObj->hString);
		if (pText)
		{
			RECT rc = { 20,20,pObj->sizeText.cx + 40,pObj->sizeText.cy + 45 };
			XDraw_DrawText_(hDraw, pText, XStr_GetLength(pObj->hString), &rc, 0);;
		}
	}
	return TRUE;
}

BOOL CALLBACK MsgBox_OnEventBtnClickOk(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	XModalWnd_DoOk((HWINDOW)((ele_*)hEle)->pWindow);
	return TRUE;
}

BOOL CALLBACK MsgBox_OnEventBtnClickCancel(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	XModalWnd_DoCancel((HWINDOW)((ele_*)hEle)->pWindow);
	return TRUE;
}

///////////////////////////////////////////////////////

///@addtogroup groupGlobalAPI
///@{

///@brief 弹出消息框
///@param hXCGUI 元素句柄或窗口资源句柄.
///@param pText  文本内容.
///@param pCaption  窗口标题内容.
///@param type      类型, @ref XMB_OK :确定按钮, @ref XMB_CANCEL :取消按钮.
///@return XMB_OK或XMB_CANCEL,如果失败返回-1,如果按标题栏上的关闭按钮返回0.
int WINAPI XMessageBox(HXCGUI hXCGUI, wchar_t *pText, wchar_t *pCaption, int type)
{
	if (hXCGUI && 0 == IsBadReadPtr(hXCGUI, sizeof(object_)))
	{
		HWND hWndParent = NULL;
		if (XC_WINDOW == ((object_*)hXCGUI)->type)
		{
			hWndParent = ((window_*)hXCGUI)->hWnd;
		}
		else if (XC_ELE == ((object_*)hXCGUI)->type)
		{
			hWndParent = ((ele_*)hXCGUI)->pWindow->hWnd;
		}
		else
			return -1;
		return MsgBox_DoModal(hWndParent, pText, pCaption, type);
	}
	return -1;
}

///@}
