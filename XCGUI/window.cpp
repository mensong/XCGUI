/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#ifdef XCGUI_PLUS  //C++��֧��
void WINAPI XWnd_RegisterMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---����Ϣ����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pWindow->hArray_msg);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (message == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)malloc(sizeof(windowMsg_Header_));
		pHeader->message = message;

		switch (message)
		{
		case XWM_MOUSECLICK:     pHeader->pFunConv = Wnd_ConvMouseClick; break;
		case XWM_MOUSEDBCLICK:   pHeader->pFunConv = Wnd_ConvMouseDBClick; break;
		case XWM_REDRAW_ELE:     pHeader->pFunConv = Wnd_ConvRedrawEle; break;
		case XWM_MENUSELECT:     pHeader->pFunConv = Wnd_ConvMenuSelect; break;
		case XWM_MENUEXIT:       pHeader->pFunConv = Wnd_ConvMenuExit; break;
		case XWM_SETFONT:        pHeader->pFunConv = Wnd_ConvSetFont; break;

		case WM_PAINT:           pHeader->pFunConv = Wnd_ConvPaint; break;
		case WM_MOUSEMOVE:       pHeader->pFunConv = Wnd_ConvMouseMove; break;
		case WM_LBUTTONDOWN:     pHeader->pFunConv = Wnd_ConvLButtonDown; break;
		case WM_LBUTTONUP:       pHeader->pFunConv = Wnd_ConvLButtonUp; break;
		case WM_RBUTTONDOWN:     pHeader->pFunConv = Wnd_ConvRButtonDown; break;
		case WM_RBUTTONUP:       pHeader->pFunConv = Wnd_ConvRButtonUp; break;
		case WM_EXITSIZEMOVE:    pHeader->pFunConv = Wnd_ConvExitSizeMove; break;
		case WM_MOUSELEAVE:      pHeader->pFunConv = Wnd_ConvMouseLeave; break;
		case WM_SIZE:            pHeader->pFunConv = Wnd_ConvSize; break;
		case WM_TIMER:           pHeader->pFunConv = Wnd_ConvTimer; break;
		case XWM_TIMER:          pHeader->pFunConv = Wnd_ConvTimer2; break;
		case WM_SETFOCUS:        pHeader->pFunConv = Wnd_ConvSetFocus; break;
		case WM_KILLFOCUS:       pHeader->pFunConv = Wnd_ConvKillFocus; break;
		case WM_CAPTURECHANGED:  pHeader->pFunConv = Wnd_ConvCaptureChanged; break;
		case WM_MOUSEWHEEL:      pHeader->pFunConv = Wnd_ConvMouseWheel; break;
		case WM_DESTROY:         pHeader->pFunConv = Wnd_ConvDestroy; break;
		case WM_NCDESTROY:       pHeader->pFunConv = Wnd_ConvNCDestroy; break;
		case WM_CLOSE:           pHeader->pFunConv = Wnd_ConvClose; break;

		default: pHeader->pFunConv = Wnd_ConvOther; break;
		}

		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;
		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pWindow->hArray_msg, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;

		windowMsg_Header_  *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XWnd_RegisterNCMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //ע��ǿͻ�����Ϣ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---����Ϣ����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pWindow->hArray_NCmsg);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (message == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)malloc(sizeof(windowMsg_Header_));
		pHeader->message = message;

		switch (message)
		{
		case XWM_NCPAINT: pHeader->pFunConv = Wnd_ConvNCPaint; break;
		case XWM_NCENDPAINT: pHeader->pFunConv = Wnd_ConvNCEndPaint; break;

		case XWM_NCMOUSEMOVE: pHeader->pFunConv = Wnd_ConvNCMouseMove; break;

		case XWM_NCLBUTTONDOWN: pHeader->pFunConv = Wnd_ConvNCLButtonDown; break;
		case XWM_NCLBUTTONUP: pHeader->pFunConv = Wnd_ConvNCLButtonUp; break;

		case XWM_NCRBUTTONDOWN: pHeader->pFunConv = Wnd_ConvNCRButtonDown; break;
		case XWM_NCRBUTTONUP: pHeader->pFunConv = Wnd_ConvNCRButtonUp; break;

		case XWM_NCMOUSECLICK: pHeader->pFunConv = Wnd_ConvNCMouseClick; break;
		case XWM_NCMOUSEDBCLICK: pHeader->pFunConv = Wnd_ConvNCMouseDBClick; break;

		default:XTRACE("XWnd_RegisterNCMessage() δ֪��Ϣ���� \n"); pHeader->pFunConv = NULL; break;
		}

		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;

		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pWindow->hArray_NCmsg, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;

		windowMsg_Header_  *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XWnd_RegisterMsgProcEx(HWINDOW hWindow, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)	//ע�ᴰ����Ϣ�������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	windowProc_  *&pProcT = ((window_*)hWindow)->pWndProc;
	if (NULL == pProcT)
	{
		pProcT = (windowProc_*)malloc(sizeof(windowProc_));
		pProcT->pFun = pCallBackFun;
		pProcT->pNext = NULL;
	}
	else  //���뿪ʼλ��
	{
		windowProc_ *pNew = (windowProc_*)malloc(sizeof(windowProc_));
		pNew->pNext = pProcT;
		pProcT = pNew;
		pProcT->pFun = pCallBackFun;
	}
	pProcT->pClass_Fun_Info = pClass_Fun_Info;
}
#endif



/// @addtogroup window
/// @{

/// @brief ��������
/// @param x   �������Ͻ�x����.
/// @param y   �������Ͻ�y����.
/// @param cx  ���ڿ��.
/// @param cy  ���ڸ߶�.
/// @param pTitle  ���ڱ���.
/// @param hWndParent  ������.
/// @param XCStyle    GUI�ⴰ����ʽ,��ʽ��μ��궨��.
/// @return  GUI�ⴰ����Դ���.
HWINDOW WINAPI XWnd_CreateWindow(int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent, int XCStyle)
{
	window_ *pWindow = (window_*)malloc(sizeof(window_));
	if (pWindow)
	{
		memset(pWindow, 0, sizeof(window_));
		if (FALSE == Wnd_Init((HWINDOW)pWindow, NULL, NULL, pTitle, NULL, x, y, cx, cy, hWndParent, XCStyle, XC_WINDOW))
		{
			delete pWindow;
			return NULL;
		}

		if (g_fun_create_window && FALSE == g_fun_create_window((HWINDOW)pWindow))
		{
			MsgError(XC_ERROR_0011);
			return FALSE;
		}
	}
	return (HWINDOW)pWindow;
}

/// @brief ��������,��ǿ����.
/// @param dwExStyle ������չ��ʽ.
/// @param lpClassName   ��������,��Ѱ�Ըò�����Ч.
/// @param lpWindowName   ������.
/// @param dwStyle     ������ʽ
/// @param x   �������Ͻ�x����.
/// @param y   �������Ͻ�y����.
/// @param cx  ���ڿ��.
/// @param cy  ���ڸ߶�.
/// @param hWndParent  ������.
/// @param XCStyle     GUI�ⴰ����ʽ,��ʽ��μ��궨��.
/// @return  GUI�ⴰ����Դ���.
HWINDOW WINAPI XWnd_CreateWindowEx(DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle)
{
	window_ *pWindow = (window_*)malloc(sizeof(window_));
	if (pWindow)
	{
		memset(pWindow, 0, sizeof(window_));

		if (FALSE == Wnd_Init((HWINDOW)pWindow, dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, cx, cy, hWndParent, XCStyle, XC_WINDOW))
		{
			delete pWindow;
			return NULL;
		}
	}
	return (HWINDOW)pWindow;
}

BOOL Wnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle, int exType)
{
	HMODULE hModule = GetModuleHandle(NULL);

	window_ *pWindow = (window_*)hWindow;
	pWindow->exType = exType;
	pWindow->xcStyle = XCStyle;
	pWindow->hArrayEle = XArray_Create();
	pWindow->hArrayEleNC = XArray_Create();
	pWindow->hMenuBar = NULL;
	pWindow->hToolBar = NULL;
	pWindow->minWidth = 150;
	pWindow->minHeight = 100;
	pWindow->caretColor = RGB(0, 0, 0);
	pWindow->chartletStyle |= XC_CS_STROKE_INNER;
	pWindow->chartletStyle |= XC_CS_STROKE_OUTER;

	pWindow->strokeOuter_color1 = RGB(6, 108, 156);
	pWindow->strokeOuter_color2 = RGB(143, 217, 253);
	pWindow->strokeInner_color1 = RGB(6, 108, 156);
	pWindow->strokeInner_color2 = RGB(143, 217, 253);
	pWindow->transparentAlpha = 230;

	pWindow->iconSize.cx = 24;
	pWindow->iconSize.cy = 24;
	pWindow->roundSize = 5;

#ifdef XCGUI_Free_version     //��Ѱ治����ָ����������
	lpClassName = XCGUI_CLASS_NAME;
#else
	if (NULL == lpClassName)
		lpClassName = XCGUI_CLASS_NAME;
#endif

	if (NULL == lpWindowName)
		lpWindowName = L"XCGUI-Window";

	if (NULL == dwStyle)
		dwStyle = WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	//WS_MINIMIZEBOX | WS_SIZEBOX | WS_CAPTION | WS_MINIMIZEBOX

//	dwStyle |= WS_CLIPCHILDREN;
//	dwStyle |= WS_CLIPSIBLINGS;

	if (XCStyle & XC_SY_CENTER) //���ھ���
	{
		RECT rect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		x = (rect.right - rect.left) / 2 - cx / 2;
		y = (rect.bottom - rect.top) / 2 - cy / 2;
	}

	if (dwStyle & WS_CAPTION)
	{
		dwStyle = dwStyle & ~WS_CAPTION;
	}
#if 0
	if (XCStyle & XC_SY_MAXIMIZE)
	{
		if (FALSE == (dwStyle & WS_MAXIMIZEBOX))
		{
			dwStyle = dwStyle | WS_MAXIMIZEBOX;
		}
	}
	else
	{
		if (dwStyle & WS_MAXIMIZEBOX)
		{
			dwStyle = dwStyle & ~WS_MAXIMIZEBOX;
		}
	}

	if (XCStyle & XC_SY_MINIMIZE)
	{
		if (FALSE == (dwStyle & WS_MINIMIZEBOX))
		{
			dwStyle = dwStyle | WS_MINIMIZEBOX;
		}
	}
	else
	{
		if (dwStyle & WS_MINIMIZEBOX)
		{
			dwStyle = dwStyle & ~WS_MINIMIZEBOX;
		}
	}
#endif

	((object_*)hWindow)->type = XC_WINDOW;
	AddTypeDebug(hWindow, XC_WINDOW);

	HWND hWnd = CreateWindowExW(dwExStyle, lpClassName, lpWindowName,
		//WS_VISIBLE | WS_CAPTION |WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_SIZEBOX | WS_CAPTION| WS_MINIMIZEBOX,
		//| WS_MAXIMIZEBOX, ����WIN7�����ƶ�����Ļ���ϣ��Զ���󻯵���ȫ������
		dwStyle,
		x, y, cx - 1, cy, hWndParent, NULL, hModule, hWindow);

	//DWORD err= GetLastError();

	if (hWnd)
	{
		((object_*)hWindow)->type = XC_WINDOW;
		pWindow->hWnd = hWnd;
		Resource_AddWindow(hWindow);

		pWindow->bkColor = RGB(255, 255, 255);
		pWindow->hArray_msg = XArray_Create();
		pWindow->hArray_NCmsg = XArray_Create();

		::SetWindowPos(hWnd, NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		if (pWindow->xcStyle & XC_SY_ROUND)
		{
			HRGN hrgn = CreateRoundRectRgn(0, 0, cx + 1, cy + 1, pWindow->roundSize, pWindow->roundSize);
			SetWindowRgn(hWnd, hrgn, FALSE);
			DeleteObject(hrgn);
		}

		if (XC_SY_CAPTION & XCStyle)
			XWnd_SetCaptionHeight(hWindow, 28);

		if (XC_SY_BORDER & XCStyle)
		{
			XWnd_SetBorderSize(hWindow, 8, 8, 8, 8);
		}

		XWnd_RegisterMsgProc(hWindow, Wnd_WindowProc);//���ڹ���

		XWnd_RegisterNCMessage(hWindow, XWM_NCMOUSEMOVE, Wnd_OnNCMouseMove);
		XWnd_RegisterNCMessage(hWindow, XWM_NCLBUTTONDOWN, Wnd_OnNCLButtonDown);
		XWnd_RegisterNCMessage(hWindow, XWM_NCLBUTTONUP, Wnd_OnNCLButtonUp);
		XWnd_RegisterNCMessage(hWindow, XWM_NCRBUTTONDOWN, Wnd_OnNCRButtonDown);
		XWnd_RegisterNCMessage(hWindow, XWM_NCRBUTTONUP, Wnd_OnNCRButtonUp);
		XWnd_RegisterNCMessage(hWindow, XWM_NCPAINT, Wnd_OnNCDrawWindow);
		XWnd_RegisterNCMessage(hWindow, XWM_NCMOUSECLICK, Wnd_OnNCMouseClick);
		XWnd_RegisterNCMessage(hWindow, XWM_NCMOUSEDBCLICK, Wnd_OnNCMouseDBClick);

		XWnd_RegisterMessage(hWindow, WM_PAINT, Wnd_OnDrawWindow);
		XWnd_RegisterMessage(hWindow, WM_DESTROY, Wnd_OnDestroy);
		XWnd_RegisterMessage(hWindow, WM_NCDESTROY, Wnd_OnNCDestroy);
		XWnd_RegisterMessage(hWindow, WM_MOUSEMOVE, Wnd_OnMouseMove);
		XWnd_RegisterMessage(hWindow, WM_LBUTTONDOWN, Wnd_OnLButtonDown);
		XWnd_RegisterMessage(hWindow, WM_LBUTTONUP, Wnd_OnLButtonUp);
		XWnd_RegisterMessage(hWindow, WM_RBUTTONDOWN, Wnd_OnRButtonDown);
		XWnd_RegisterMessage(hWindow, WM_RBUTTONUP, Wnd_OnRButtonUp);

		XWnd_RegisterMessage(hWindow, WM_MOUSELEAVE, Wnd_OnMouseLeave);
		XWnd_RegisterMessage(hWindow, WM_SIZE, Wnd_OnSize);
		XWnd_RegisterMessage(hWindow, XWM_MOUSECLICK, Wnd_OnMouseClick);
		XWnd_RegisterMessage(hWindow, XWM_MOUSEDBCLICK, Wnd_OnMouseDBClick);
		XWnd_RegisterMessage(hWindow, XWM_DRAW_T, Wnd_OnDrawT);
		XWnd_RegisterMessage(hWindow, XWM_REDRAW_ELE, Wnd_OnRedrawEle);
		XWnd_RegisterMessage(hWindow, WM_SETFOCUS, Wnd_OnSetFocus);
		XWnd_RegisterMessage(hWindow, WM_KILLFOCUS, Wnd_OnKillFocus);
		XWnd_RegisterMessage(hWindow, WM_KEYDOWN, Wnd_OnKeyDown);
		XWnd_RegisterMessage(hWindow, WM_TIMER, Wnd_OnTimer);
		XWnd_RegisterMessage(hWindow, XWM_TIMER, Wnd_OnTimerEx);

		XWnd_RegisterMessage(hWindow, WM_CHAR, Wnd_OnChar);
		XWnd_RegisterMessage(hWindow, WM_CAPTURECHANGED, Wnd_OnCaptureChanged);
		XWnd_RegisterMessage(hWindow, WM_MOUSEWHEEL, Wnd_OnMouseWheel);
		XWnd_RegisterMessage(hWindow, XWM_REDRAW, Wnd_OnRedraw);
		XWnd_RegisterMessage(hWindow, WM_GETMINMAXINFO, Wnd_OnMinMaxInfo);

		//	HFONT hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT);
		//	XWnd_SetFont(hWindow,hFont);

		if (pWindow->xcStyle & XC_SY_CLOSE)
		{
			pWindow->hClose = XBtn_Create(1, 1, 40, 20);
			XWnd_AddEleNC(hWindow, pWindow->hClose);
			Ele_SetType(pWindow->hClose, XC_BUTTON_CLOSE);
			XEle_EnableFocus(pWindow->hClose, FALSE);
			XEle_RegisterMessage(pWindow->hClose, XM_PAINT, Wnd_OnBtnCloseDraw);
			XEle_RegisterEvent(pWindow->hClose, XE_BNCLICK, Wnd_OnEventBtnCloseClick);
		}
		if (pWindow->xcStyle & XC_SY_MAXIMIZE)
		{
			pWindow->hMaxinize = XBtn_Create(1, 1, 25, 20);
			XWnd_AddEleNC(hWindow, pWindow->hMaxinize);
			Ele_SetType(pWindow->hMaxinize, XC_BUTTON_MAX);
			XEle_EnableFocus(pWindow->hMaxinize, FALSE);
			XEle_RegisterMessage(pWindow->hMaxinize, XM_PAINT, Wnd_OnBtnMaximizeDraw);
			XEle_RegisterEvent(pWindow->hMaxinize, XE_BNCLICK, Wnd_OnEventBtnMaximizeClick);
		}
		if (pWindow->xcStyle & XC_SY_MINIMIZE) //��С����ť
		{
			pWindow->hMinimize = XBtn_Create(1, 1, 25, 20);
			XWnd_AddEleNC(hWindow, pWindow->hMinimize);
			Ele_SetType(pWindow->hMinimize, XC_BUTTON_MIN);
			XEle_EnableFocus(pWindow->hMinimize, FALSE);
			XEle_RegisterMessage(pWindow->hMinimize, XM_PAINT, Wnd_OnBtnMinimizeDraw);
			XEle_RegisterEvent(pWindow->hMinimize, XE_BNCLICK, Wnd_OnEventBtnMinimizeClick);
		}

		Wnd_AdjustCaption(hWindow, cx);

		return TRUE;
	}
	return FALSE;
}

/// @brief ���ô��ڱ߿��С,ע�����Ų�GUI���߼��ϵı߿��С,����ϵͳ�߿��С.
/// @param hWindow  ������Դ���.
/// @param left  ��߿��С.
/// @param top   �ϱ߿��С.
/// @param right �ұ߿��С.
/// @param bottom �±߿��С.
void WINAPI XWnd_SetBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom) //���ô��ڱ߿�
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->borderLeft = left;
	((window_*)hWindow)->borderTop = top;
	((window_*)hWindow)->borderRight = right;
	((window_*)hWindow)->borderBottom = bottom;
	XWnd_Adjust(hWindow);
}

/// @brief ���ô��ڱ������߶�,�������Ҫ���������ø߶�Ϊ0.
/// @param hWindow  ������Դ���.
/// @param captionHeight  �������߶�.
void WINAPI XWnd_SetCaptionHeight(HWINDOW hWindow, int captionHeight) //���ñ�����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->captionHeight = captionHeight;
	XWnd_Adjust(hWindow);
}

/// @brief ���ô���ͼ��.
/// @param hWindow  ������Դ���.
/// @param hIcon    ͼ����.
/// @param bBigIcon  tru��ͼ��,FALSEСͼ��.
/// @return ���ʧ�ܷ���0.
DWORD WINAPI XWnd_SetIcon(HWINDOW hWindow, HICON hIcon, BOOL bBigIcon)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bBigIcon)
	{
		return SetClassLongPtr(((window_*)hWindow)->hWnd, GCLP_HICON, (LONG_PTR)hIcon);
	}
	else
	{
		return SetClassLongPtr(((window_*)hWindow)->hWnd, GCLP_HICONSM, (LONG_PTR)hIcon);
	}
}

/// @brief ���ô���ͼ��.
/// @param hWindow  ������Դ���.
/// @param pFileName  ͼ���ļ�.
/// @param bBigIcon  TRUE��ͼ��,FALSEСͼ��.
/// @return ���ʧ�ܷ���0.
DWORD WINAPI XWnd_SetIcon2(HWINDOW hWindow, wchar_t *pFileName, BOOL bBigIcon)
{
	IsWindowDebug(hWindow, __FUNCTION__);

	HMODULE hIns = GetModuleHandle(NULL);
	HICON hIcon = (HICON)LoadImage(hIns, pFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	if (bBigIcon)
	{
		return SetClassLongPtr(((window_*)hWindow)->hWnd, GCLP_HICON, (LONG_PTR)hIcon);
	}
	else
	{
		return SetClassLongPtr(((window_*)hWindow)->hWnd, GCLP_HICONSM, (LONG_PTR)hIcon);
	}
}

/// @brief ��ȡ����ͼ��.
/// @param hWindow  ������Դ���.
/// @param bBigIcon  tru��ͼ��,FALSEСͼ��.
/// @return ͼ����,���ʧ�ܷ���0.
HICON WINAPI XWnd_GetIcon(HWINDOW hWindow, BOOL bBigIcon) //��ȡ����ͼ��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bBigIcon)
	{
		return (HICON)GetClassLongPtr(((window_*)hWindow)->hWnd, GCLP_HICON);
	}
	else
	{
		return (HICON)GetClassLongPtr(((window_*)hWindow)->hWnd, GCLP_HICONSM);
	}
}

/// @brief ���ñ�����ͼ����ʾ��С.
/// @param hWindow  ������Դ���.
/// @param width    ͼ����.
/// @param height   ͼ��߶�.
void WINAPI XWnd_SetIconSize(HWINDOW hWindow, int width, int height)  //����ͼ����ʾ��С
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->iconSize.cx = width;
	((window_*)hWindow)->iconSize.cy = height;
}

/// @brief ��󻯻�ԭ���ڴ�С.
/// @param hWindow  ������Դ���.
/// @param bMax     TRUE��󻯴���,FALSE��ԭ���ڴ�С.
void WINAPI XWnd_MaximizeWnd(HWINDOW hWindow, BOOL bMax) //��� ��ԭ����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (bMax) //��󻯴���
	{
		GetWindowRect(pWindow->hWnd, &pWindow->rcOld);

		//	RECT rect;
		//	SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);
		//	::SetWindowPos(pWindow->hWnd,NULL,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_NOZORDER );//| SWP_NOACTIVATE);
		//	pWindow->bMaxWnd=TRUE;
		ShowWindow(pWindow->hWnd, SW_MAXIMIZE);
	}
	else
	{
		//	::SetWindowPos(pWindow->hWnd,NULL,pWindow->rcOld.left,pWindow->rcOld.top,pWindow->rcOld.right-pWindow->rcOld.left,pWindow->rcOld.bottom-pWindow->rcOld.top,SWP_NOZORDER);// | SWP_NOACTIVATE);
		//	pWindow->bMaxWnd=FALSE;
		ShowWindow(pWindow->hWnd, SW_RESTORE);
	}
}

/// @brief �жϴ����Ƿ����.
/// @param hWindow  ������Դ���.
/// @return ���������󻯷���TRUE,���򷵻�FALSE.
BOOL WINAPI XWnd_IsMaximizeWnd(HWINDOW hWindow)  //�����Ƿ����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (IsZoomed(((window_*)hWindow)->hWnd))
		return  TRUE;
	else
		return FALSE;
}

/// @brief ���ö�ʱ��.
/// @param hWindow  ������Դ���.
/// @param nIDEvent ��ʱ����ʶ��.
/// @param uElapse  ���ʱ�����.
/// @return ��ʱ����ʶ��.
UINT WINAPI XWnd_SetTimer(HWINDOW hWindow, UINT nIDEvent, UINT uElapse)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return SetTimer(((window_*)hWindow)->hWnd, nIDEvent, uElapse, NULL);
}

/// @brief �رն�ʱ��.
/// @param hWindow  ���ھ��.
/// @param nIDEvent ��ʱ����ʶ��.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XWnd_KillTimer(HWINDOW hWindow, UINT nIDEvent)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return KillTimer(((window_*)hWindow)->hWnd, nIDEvent);
}

/// @brief ���ö�ʱ��,��ϵͳ��ʱ��.
/// @param hWindow  ���ھ��
/// @param nIDEvent ��ʱ����ʶ��.
/// @param uElapse  ���ʱ�����.
/// @param userData ������.
/// @return �ɹ�����TRUE,�����෴.
UINT WINAPI XWnd_SetTimerEx(HWINDOW hWindow, UINT nIDEvent, UINT uElapse, int userData)
{
	return Timer_SetTimerWindow(hWindow, nIDEvent, uElapse, userData);
}

/// @brief �رն�ʱ��,��ϵͳ��ʱ��.
/// @param hWindow  ���ھ��.
/// @param nIDEvent ��ʱ����ʶ��.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XWnd_KillTimerEx(HWINDOW hWindow, UINT nIDEvent)
{
	return Timer_KillTimerWindow(nIDEvent);
}

/// @brief ���ô��ڱ�����ɫ,RGBֵ.
/// @param hWindow  ������Դ���.
/// @param color  RGB��ɫֵ.
void WINAPI XWnd_SetBkColor(HWINDOW hWindow, COLORREF color) //���ñ�����ɫ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->bkColor = color;
}

/// @brief ���ô�����С���.
/// @param hWindow  ������Դ���.
/// @param width    �����ڱ߿��϶�ʱ�������С���.
void WINAPI XWnd_SetMinWidth(HWINDOW hWindow, int width)  //���ô�����С���
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->minWidth = width;
}

/// @brief ���ô�����С�߶�.
/// @param hWindow  ������Դ���.
/// @param height   ���϶����ڱ߿�ʱ,��������С�߶�.
void WINAPI XWnd_SetMinHeight(HWINDOW hWindow, int height) //���ô�����С�߶�
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->minHeight = height;
}

/// @brief ���ô���Բ�Ǵ�С,��Բ�Ǵ�����Ч.
/// @param hWindow  ������Դ���.
/// @param size   Բ�Ǵ�С.
void WINAPI XWnd_SetRoundSize(HWINDOW hWindow, int size)   //���ô���Բ�Ǵ�С,��Բ�Ǵ�����Ч
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->roundSize = size;

	RECT rect;
	GetWindowRect(WINDOW(hWindow)->hWnd, &rect);
	HRGN hrgn = CreateRoundRectRgn(0, 0, rect.right - rect.left + 1, rect.bottom - rect.top + 1, WINDOW(hWindow)->roundSize, WINDOW(hWindow)->roundSize);
	SetWindowRgn(WINDOW(hWindow)->hWnd, hrgn, TRUE);
	DeleteObject(hrgn);
}

/// @brief �ػ洰��ָ������.
/// @param hWindow  ������Դ���.
/// @param pRect    ��Ҫ�ػ����������,����GUI��ǿͻ�������ϵ,������ϵͳ�ǿͻ���.
/// @param bImmediately   TRUE�����ػ�,FALSE������Ϣ�����ӳ��ػ�.
void WINAPI XWnd_RedrawWndRect(HWINDOW hWindow, RECT *pRect, BOOL bImmediately) //�ػ洰��ָ������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (FALSE == IsWindowVisible(((window_*)hWindow)->hWnd))
		return;

	//	if(bImmediately) //�����ػ�
	//	{
			//----����Ϣ����
	window_ *pWindow = (window_*)hWindow;
	//		HDC hdc=GetDC(pWindow->hWnd);
	//		if(NULL==hdc)
	//		{
	//			MessageBox(NULL,L"XWnd_RedrawWndRect()��ȡHDC����",L"�Ųʽ����-������ʾ",0);
	//			exit(0);
	//			return ;
	//		}
	int count = Array_GetCount(pWindow->hArray_msg);
	for (int i = 0; i < count; i++)
	{
		if (WM_PAINT == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->message)
		{
			Wnd_DrawWindowHandle(hWindow, pRect);
			break;
		}
	}
	//		ReleaseDC(pWindow->hWnd,hdc);
	//	}else //������Ϣ����,�Ժ����
	//	{
	//		PostMessage(((window_*)hWindow)->hWnd,XWM_REDRAW,MAKELPARAM(pRect->left,pRect->top),MAKELPARAM(pRect->right,pRect->bottom));
	//	}
}

/// @brief �ػ洰��,���ػ��������ڰ����ǿͻ�.
/// @param hWindow  ������Դ���.
/// @param bImmediately  TRUE�����ػ�,FALSE������Ϣ�����ӳ��ػ�.
void WINAPI XWnd_RedrawWnd(HWINDOW hWindow, BOOL bImmediately)//�ػ洰��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	//	if(bImmediately) //�����ػ�
	//	{
	RECT rect;
	GetClientRect(((window_*)hWindow)->hWnd, &rect);
	XWnd_RedrawWndRect(hWindow, &rect, TRUE);
	//	}else //������Ϣ����,�Ժ����
	//	{
	//		if(FALSE==IsWindowVisible(((window_*)hWindow)->hWnd))
	//			return;
	//		PostMessage(((window_*)hWindow)->hWnd,XWM_REDRAW,0,0);
	//	}
}

/// @brief �ػ�ָ��Ԫ��.
/// @param hWindow  ������Դ���.
/// @param hEle   Ҫ�ػ��Ԫ�ؾ��
/// @param pRect  �ػ�����,���ڴ��ڷǿͻ�������.
void WINAPI XWnd_RedrawEleRectNC(HWINDOW hWindow, HELE hEle, RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	Wnd_RedrawEle(hWindow, hEle, pRect);
}


/// @brief ��ȡ��ǰ�ػ���������..
/// @param hWindow  ������Դ���.
/// @param pRect    �����ػ���������
void WINAPI XWnd_GetDrawRect(HWINDOW hWindow, RECT *pRect) //��ȡ��ǰ��������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	*pRect = ((window_*)hWindow)->rcDraw;
}

/// @brief ���ӵ�����뽹���Ԫ��.
/// @param hWindow  ������Դ���.
HELE WINAPI XWnd_GetFocusEle(HWINDOW hWindow) //��ȡӵ�н����Ԫ��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return (HELE)((window_*)hWindow)->pFocus;
}

/// @brief ���ô�������..
/// @param hWindow  ������Դ���.
/// @param hFontX    �Ų�������.
void WINAPI XWnd_SetFont(HWINDOW hWindow, HFONTX hFontX)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	Font_AddFontX(((window_*)hWindow)->hFontX, hFontX);
}

/// @brief ��ʾ������һ������.
/// @param hWindow  ������Դ���.
/// @param nCmdShow  SW_SHOW��ʾ����,SW_HIDE���ش���.
/// @note ����μ�MSDN:ShowWindow()
BOOL WINAPI XWnd_ShowWindow(HWINDOW hWindow, int nCmdShow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ShowWindow(((window_*)hWindow)->hWnd, nCmdShow);
}

/// @brief ���ô��ڴ�Сλ�ü�����.
/// @param hWindow  ������Դ���.
/// @param hWndInsertAfter ����μ�MSDN.
/// @param x ����μ�MSDN.
/// @param y ����μ�MSDN.
/// @param cx ����μ�MSDN.
/// @param cy ����μ�MSDN.
/// @param uFlags ����μ�MSDN.
/// @note ʧ�ܷ���0,����μ�MSDN:SetWindowPos().
BOOL WINAPI XWnd_SetWindowPos(HWINDOW hWindow, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::SetWindowPos(((window_*)hWindow)->hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
}

/// @brief ���ô�������,������Ļ����.
/// @param hWindow  ���ھ��.
/// @param pRect   ����.
/// @note ʧ�ܷ���0.
BOOL WINAPI XWnd_SetWindowRect(HWINDOW hWindow, in_ RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::SetWindowPos(((window_*)hWindow)->hWnd, NULL, pRect->left, pRect->top,
		pRect->right - pRect->left, pRect->bottom - pRect->top, SWP_NOZORDER);
}

/// @brief ���ô��ڴ�С,���ı䴰��λ��.
/// @param hWindow  ���ھ��.
/// @param width  ���ڿ��.
/// @param height ���ڸ߶�.
/// @note ʧ�ܷ���0.
BOOL WINAPI XWnd_SetWindowSize(HWINDOW hWindow, int width, int height)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::SetWindowPos(((window_*)hWindow)->hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}

/// @brief ��ȡ��������,������Ļ����.
/// @param hWindow  ���ھ��.
/// @param pRect   ����.
/// @note ʧ�ܷ���0.
BOOL WINAPI XWnd_GetWindowRect(HWINDOW hWindow, out_ RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::GetWindowRect(((window_*)hWindow)->hWnd, pRect);
}

/// @brief �жϴ����Ƿ���ʾ.
/// @param hWindow  ���ھ��.
/// @note ���������ʾ����TRUE,���򷵻�FALSE.
BOOL WINAPI XWnd_IsWindowVisible(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return IsWindowVisible(((window_*)hWindow)->hWnd);
}

/// @brief ���û�ر��϶����ڱ߿���,��������б߿�Ļ�.
/// @param hWindow  ������Դ���.
/// @param bDrag    TRUE���ڱ߿�����϶�,���򲻿����϶�.
void WINAPI XWnd_EnableDragBorder(HWINDOW hWindow, BOOL bDrag)  //ʹ���϶��߿�
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bDrag)
	{
		LONG_PTR style = GetWindowLongPtr(((window_*)hWindow)->hWnd, GWL_STYLE);
		if (FALSE == (style & WS_THICKFRAME))
		{
			style |= WS_THICKFRAME;
			SetWindowLongPtr(((window_*)hWindow)->hWnd, GWL_STYLE, style);
		}
		((window_*)hWindow)->xcStyle |= XC_SY_DRAG_BORDER;
	}
	else
	{
		LONG_PTR style = GetWindowLongPtr(((window_*)hWindow)->hWnd, GWL_STYLE);
		if (style & WS_THICKFRAME)
		{
			style &= (~WS_THICKFRAME);
			SetWindowLongPtr(((window_*)hWindow)->hWnd, GWL_STYLE, style);
		}
		((window_*)hWindow)->xcStyle &= (~XC_SY_DRAG_BORDER);
	}
}

/// @brief ���û�ر��϶����ڹ���,��ʹ��갴�ڿͻ���Ҳ���϶�����.
/// @param hWindow  ������Դ���.
/// @param bDrag    TRUE���ڿ����϶�,���򲻿����϶�.
void WINAPI XWnd_EnableDragWindow(HWINDOW hWindow, BOOL bDrag)  //�϶�����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bDrag)
	{
		((window_*)hWindow)->xcStyle |= XC_SY_DRAG_WINDOW;
	}
	else
	{
		((window_*)hWindow)->xcStyle &= (~XC_SY_DRAG_WINDOW);
	}
}


/// @brief ��ȡ���ڱ���������С����ť���.
/// @param hWindow  ���ھ��.
/// @return ������С����ť���.
HELE WINAPI XWnd_GetButtonMin(HWINDOW hWindow)   //��С����ť
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return WINDOW(hWindow)->hMinimize;
}

/// @brief ��ȡ���ڱ���������󻯰�ť���.
/// @param hWindow  ���ھ��.
/// @return ������󻯰�ť���.
HELE WINAPI XWnd_GetButtonMax(HWINDOW hWindow)   //��󻯰�ť
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return WINDOW(hWindow)->hMaxinize;
}

/// @brief ��ȡ���ڱ������Ϲرհ�ť���.
/// @param hWindow  ���ھ��.
/// @return ���ڹرհ�ť���.
HELE WINAPI XWnd_GetButtonClose(HWINDOW hWindow) //�رհ�ť
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return WINDOW(hWindow)->hClose;
}

/// @brief �������û�ر���С����ť.
/// @param hWindow  ���ھ��.
/// @param bEnable  ֵΪTRUE����,�����෴.
/// @param bRedraw  ֵΪTRUE�ػ�,�����෴.
void WINAPI XWnd_EnableMinButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw) //������С����ť
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);
	LONG_PTR dwStyle = 0;
	if (bEnable)
	{
		if (pWindow->hMinimize) return;

		dwStyle = GetWindowLongPtr(pWindow->hWnd, GWL_STYLE);
		if (FALSE == (dwStyle & WS_MINIMIZEBOX))
			dwStyle = dwStyle | WS_MINIMIZEBOX;
		SetWindowLongPtr(pWindow->hWnd, GWL_STYLE, dwStyle);

		pWindow->hMinimize = XBtn_Create(1, 1, 25, 20, L"-");
		XWnd_AddEleNC(hWindow, pWindow->hMinimize);
		XEle_EnableFocus(pWindow->hMinimize, FALSE);
		XEle_RegisterMessage(pWindow->hMinimize, XM_PAINT, Wnd_OnBtnMinimizeDraw);
		XEle_RegisterEvent(pWindow->hMinimize, XE_BNCLICK, Wnd_OnEventBtnMinimizeClick);
	}
	else
	{
		if (NULL == pWindow->hMinimize) return;

		dwStyle = GetWindowLongPtr(pWindow->hWnd, GWL_STYLE);
		if (dwStyle & WS_MINIMIZEBOX)
			dwStyle = dwStyle & ~WS_MINIMIZEBOX;
		SetWindowLongPtr(pWindow->hWnd, GWL_STYLE, dwStyle);

		XEle_Destroy(pWindow->hMinimize);
		pWindow->hMinimize = NULL;
	}
	RECT rect;
	GetWindowRect(pWindow->hWnd, &rect);
	Wnd_AdjustCaption(hWindow, rect.right - rect.left);
	if (bRedraw)
		XWnd_RedrawWnd(hWindow);
}

/// @brief �������û�ر���󻯰�ť.
/// @param hWindow  ���ھ��.
/// @param bEnable  ֵΪTRUE����,�����෴.
/// @param bRedraw  ֵΪTRUE�ػ�,�����෴.
void WINAPI XWnd_EnableMaxButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw) //������󻯰�ť
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);
	LONG_PTR dwStyle = 0;
	if (bEnable)
	{
		if (pWindow->hMaxinize) return;

		dwStyle = GetWindowLongPtr(pWindow->hWnd, GWL_STYLE);
		if (FALSE == (dwStyle & WS_MAXIMIZEBOX))
			dwStyle = dwStyle | WS_MAXIMIZEBOX;
		SetWindowLongPtr(pWindow->hWnd, GWL_STYLE, dwStyle);

		pWindow->hMaxinize = XBtn_Create(1, 1, 25, 20, L"o");
		XWnd_AddEleNC(hWindow, pWindow->hMaxinize);
		XEle_EnableFocus(pWindow->hMaxinize, FALSE);
		XEle_RegisterMessage(pWindow->hMaxinize, XM_PAINT, Wnd_OnBtnMaximizeDraw);
		XEle_RegisterEvent(pWindow->hMaxinize, XE_BNCLICK, Wnd_OnEventBtnMaximizeClick);
	}
	else
	{
		if (NULL == pWindow->hMaxinize) return;

		dwStyle = GetWindowLongPtr(pWindow->hWnd, GWL_STYLE);
		if (dwStyle & WS_MAXIMIZEBOX)
			dwStyle = dwStyle & ~WS_MAXIMIZEBOX;
		SetWindowLongPtr(pWindow->hWnd, GWL_STYLE, dwStyle);

		XEle_Destroy(pWindow->hMaxinize);
		pWindow->hMaxinize = NULL;
	}
	RECT rect;
	GetWindowRect(pWindow->hWnd, &rect);
	Wnd_AdjustCaption(hWindow, rect.right - rect.left);
	if (bRedraw)
		XWnd_RedrawWnd(hWindow);
}

/// @brief �������û�رչرհ�ť.
/// @param hWindow  ���ھ��.
/// @param bEnable  ֵΪTRUE����,�����෴.
/// @param bRedraw  ֵΪTRUE�ػ�,�����෴.
void WINAPI XWnd_EnableCloseButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw)  //���ùرհ�ť
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);
	if (bEnable)
	{
		if (pWindow->hClose) return;

		pWindow->hClose = XBtn_Create(1, 1, 40, 20, L"x");
		XWnd_AddEleNC(hWindow, pWindow->hClose);
		XEle_EnableFocus(pWindow->hClose, FALSE);
		XEle_RegisterMessage(pWindow->hClose, XM_PAINT, Wnd_OnBtnCloseDraw);
		XEle_RegisterEvent(pWindow->hClose, XE_BNCLICK, Wnd_OnEventBtnCloseClick);
	}
	else
	{
		if (NULL == pWindow->hClose) return;

		XEle_Destroy(pWindow->hClose);
		pWindow->hClose = NULL;
	}
	RECT rect;
	GetWindowRect(pWindow->hWnd, &rect);
	Wnd_AdjustCaption(hWindow, rect.right - rect.left);
	if (bRedraw)
		XWnd_RedrawWnd(hWindow);
}

/// @brief ���û�رմ���Բ��.
/// @param hWindow  ���ھ��.
/// @param bEnable  ֵΪTRUE����,�����෴.
/// @param bRedraw  ֵΪTRUE�ػ�,�����෴.
void WINAPI XWnd_EnableRound(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw) //Բ�ǹ��ܵ�������ر�
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);
	RECT rect;
	GetWindowRect(pWindow->hWnd, &rect);
	if (bEnable)
	{
		if (pWindow->xcStyle & XC_SY_ROUND)
			return;

		pWindow->xcStyle = pWindow->xcStyle | XC_SY_ROUND;

		HRGN hrgn = CreateRoundRectRgn(0, 0, rect.right - rect.left + 1, rect.bottom - rect.top + 1, pWindow->roundSize, pWindow->roundSize);
		SetWindowRgn(pWindow->hWnd, hrgn, FALSE);
		DeleteObject(hrgn);

	}
	else
	{
		if (FALSE == (pWindow->xcStyle & XC_SY_ROUND))
			return;

		pWindow->xcStyle = pWindow->xcStyle & ~XC_SY_ROUND;

		SetWindowRgn(pWindow->hWnd, NULL, FALSE);
	}
	if (bRedraw)
	{
		XWnd_RedrawWnd(hWindow);
	}
}

/// @brief ��ȡ�����ͻ���Ԫ������,������������Ԫ�ص���Ԫ��.
/// @param hWindow  ���ھ��.
/// @return ����Ԫ������.
int  WINAPI XWnd_GetChildEleCount(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return XArray_GetCount(WINDOW(hWindow)->hArrayEle);
}

/// @brief ��ȡ�����ǿͻ���Ԫ������,������������Ԫ�ص���Ԫ��.
/// @param hWindow  ���ھ��.
/// @return ����Ԫ������.
int  WINAPI XWnd_GetChildEleCountNC(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return XArray_GetCount(WINDOW(hWindow)->hArrayEleNC);
}

/// @brief ��ȡָ��������Ԫ��,���ڿͻ���.
/// @param hWindow  ���ھ��.
/// @param index  ��Ԫ��λ������.
/// @return ��Ԫ�ؾ��.
HELE WINAPI XWnd_GetChildEleByIndex(HWINDOW hWindow, int index)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);
	if (index >= 0 && index < XArray_GetCount(pWindow->hArrayEle))
	{
		return (HELE)XArray_GetAt(pWindow->hArrayEle, index);
	}
	return NULL;
}

/// @brief ��ȡָ��������Ԫ��,���ڷǿͻ���.
/// @param hWindow  ���ھ��.
/// @param index  ��Ԫ��λ������.
/// @return ��Ԫ�ؾ��.
HELE WINAPI XWnd_GetChildEleByIndexNC(HWINDOW hWindow, int index)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);
	if (index >= 0 && index < XArray_GetCount(pWindow->hArrayEleNC))
	{
		return (HELE)XArray_GetAt(pWindow->hArrayEleNC, index);
	}
	return NULL;
}

/// @brief ����͸������,ͬʱ����ͨ���ú����ر�͸������.
/// @param hWindow  ���ھ��.
/// @param flag  ����͸����ʶ.
void WINAPI XWnd_SetTransparentFlag(HWINDOW hWindow, int flag)  //����͸������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);

	if (pWindow->transparentFlag == flag) return;

	switch (flag)
	{
	case XC_WIND_TRANSPARENT_NO:
	{
		//�رմ��ڷֲ���ʽ
		LONG_PTR dwExStyle = GetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) == 0x80000)
			SetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);

		if (pWindow->xcStyle & XC_SY_ROUND)
		{
			if (XC_WIND_TRANSPARENT_SHADOW == pWindow->transparentFlag)
			{
				RECT rect;
				XWnd_GetWindowRect(hWindow, &rect);
				int cx = rect.right - rect.left;
				int cy = rect.bottom - rect.top;

				pWindow->transparentFlag = flag;
				HRGN hrgn = CreateRoundRectRgn(0, 0, cx + 1, cy + 1, pWindow->roundSize, pWindow->roundSize);
				if (hrgn)
				{
					SetWindowRgn(pWindow->hWnd, hrgn, TRUE);
					DeleteObject(hrgn);
				}
			}
		}

		pWindow->transparentFlag = flag;
		XWnd_RedrawWnd(hWindow);
	}break;
	case XC_WIND_TRANSPARENT_SHAPED: //͸������,��͸��ͨ��,����.
	{
		//���ô��ڷֲ���ʽ
		LONG_PTR dwExStyle = GetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) != 0x80000) //WS_EX_LAYERED
			SetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);
		pWindow->transparentFlag = flag;
		XWnd_RedrawWnd(hWindow);
	}break;
	case XC_WIND_TRANSPARENT_SHADOW: //��Ӱ����,��͸��ͨ��,�߿���Ӱ,����͸�����͸��.
	{
		//���ô��ڷֲ���ʽ
		LONG_PTR dwExStyle = GetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) != 0x80000) //WS_EX_LAYERED
			SetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);

		pWindow->transparentFlag = flag;

		RECT rect;
		XWnd_GetWindowRect(hWindow, &rect);
		int cx = rect.right - rect.left;
		int cy = rect.bottom - rect.top;

		HRGN hrgn = CreateRoundRectRgn(0, 0, cx + XC_WIND_SHADOW_SIZE * 2 + 1, cy + XC_WIND_SHADOW_SIZE * 2 + 1, pWindow->roundSize, pWindow->roundSize);
		if (hrgn)
		{
			SetWindowRgn(pWindow->hWnd, hrgn, TRUE);
			DeleteObject(hrgn);
		}
	}break;
	case XC_WIND_TRANSPARENT_SIMPLE: //͸������,����͸��ͨ��,ָ����͸����,ָ��͸��ɫ.
	{
		//���ô��ڷֲ���ʽ
		LONG_PTR dwExStyle = GetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) != 0x80000) //WS_EX_LAYERED
			SetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);

		pWindow->transparentFlag = flag;
		SetLayeredWindowAttributes(pWindow->hWnd, pWindow->transparentColor, pWindow->transparentAlpha, LWA_COLORKEY | LWA_ALPHA);
	}break;
	case XC_WIND_TRANSPARENT_WIN7:   //WIN7��������,��ҪWIN7������Ч.
		break;
	default: break;
	}
}

/// @brief ����͸�����ڵ�͸����,���ú�����ػ洰��API������.
/// @param hWindow  ���ھ��.
/// @param alpha    ����͸����,��Χ0-255֮��,0͸��,255��͸��.
void WINAPI XWnd_SetTransparentAlpha(HWINDOW hWindow, BYTE alpha)  //���ô���͸����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->transparentAlpha = alpha;

	if (XC_WIND_TRANSPARENT_SIMPLE == WINDOW(hWindow)->transparentFlag)
		SetLayeredWindowAttributes(WINDOW(hWindow)->hWnd, RGB(255, 255, 255), WINDOW(hWindow)->transparentAlpha, LWA_COLORKEY | LWA_ALPHA);
}

/// @brief ����͸�����ڵ�͸��ɫ.
/// @param hWindow  ���ھ��.
/// @param color    ����͸��ɫ.
void WINAPI XWnd_SetTransparentColor(HWINDOW hWindow, COLORREF color) //���ô���͸��ɫ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->transparentColor = color;
}

/// @brief ���ô��ڱ���ͼƬ,���ļ��м���ͼƬ.
/// @param hWindow  ���ھ��.
/// @param hImage   ͼƬ���.
void WINAPI XWnd_SetImage(HWINDOW hWindow, HIMAGE hImage)    //�ͻ���ͼƬ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImage_client, hImage);
}

/// @brief ���ô��ڷǿͻ�����ͼ.
/// @param hWindow  ���ھ��.
/// @param hImage   ͼƬ���.
void WINAPI XWnd_SetImageNC(HWINDOW hWindow, HIMAGE hImage)  //�ǿͻ�������ͼƬ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageNC, hImage);
}

/// @brief ���ô��ڱ�������ͼ.
/// @param hWindow  ���ھ��.
/// @param hImage   ͼƬ���.
void WINAPI XWnd_SetImageCaption(HWINDOW hWindow, HIMAGE hImage)   //������ͼƬ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageCaption, hImage);
}

/// @brief ���ô������߿���ͼ.
/// @param hWindow  ���ھ��.
/// @param hImage   ͼƬ���.
void WINAPI XWnd_SetImageBorderLeft(HWINDOW hWindow, HIMAGE hImage)    //�߿�ͼƬ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageLeft, hImage);
}

/// @brief ���ô����Ҳ�߿���ͼ.
/// @param hWindow  ���ھ��.
/// @param hImage   ͼƬ���.
void WINAPI XWnd_SetImageBorderRight(HWINDOW hWindow, HIMAGE hImage)    //�߿�ͼƬ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageRight, hImage);
}

/// @brief ���ô��ڵײ��߿���ͼ.
/// @param hWindow  ���ھ��.
/// @param hImage   ͼƬ���.
void WINAPI XWnd_SetImageBorderBottom(HWINDOW hWindow, HIMAGE hImage)    //�߿�ͼƬ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageBottom, hImage);
}

/// @brief ���ô��ڱ߿����,���ڱ߿���ڲ�.
/// @param hWindow  ���ھ��.
/// @param bStroke  ���ֵΪTRUE���,�����෴.
void WINAPI XWnd_EnableBorderStrokeInner(HWINDOW hWindow, BOOL bStroke) //���û������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bStroke)
		((window_*)hWindow)->chartletStyle |= XC_CS_STROKE_INNER;
	else
		((window_*)hWindow)->chartletStyle &= ~XC_CS_STROKE_INNER;
}

/// @brief ���ô��ڱ߿����,���ڱ߿�����.
/// @param hWindow  ���ھ��.
/// @param bStroke  ���ֵΪTRUE���,�����෴.
void WINAPI XWnd_EnableBorderStrokeOuter(HWINDOW hWindow, BOOL bStroke) //���û������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bStroke)
		((window_*)hWindow)->chartletStyle |= XC_CS_STROKE_OUTER;
	else
		((window_*)hWindow)->chartletStyle &= ~XC_CS_STROKE_OUTER;
}

/// @brief ���ô��ڱ߿������ɫ,���ڱ߿���ڲ�.
/// @param hWindow  ���ھ��.
/// @param color1   RGB��ɫ,���ڵ��ڲ�,�߿�����λ��.
/// @param color2   RGB��ɫ,���ڵ��ڲ�,�߿���ڲ�λ��.
void WINAPI XWnd_SetBorderStrokeInnerColor(HWINDOW hWindow, COLORREF color1, COLORREF color2) //���������ɫ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->strokeInner_color1 = color1;
	((window_*)hWindow)->strokeInner_color2 = color2;
}

/// @brief ���ô��ڱ߿���������ɫ.
/// @param hWindow  ���ھ��.
/// @param color1   RGB��ɫ,���ڵ����,�߿�����λ��.
/// @param color2   RGB��ɫ,���ڵ����,�߿���ڲ�λ��.
void WINAPI XWnd_SetBorderStrokeOuterColor(HWINDOW hWindow, COLORREF color1, COLORREF color2) //���������ɫ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->strokeOuter_color1 = color1;
	((window_*)hWindow)->strokeOuter_color2 = color2;
}
/// @brief �رմ���.
/// @param hWindow  ���ھ��.
void WINAPI XWnd_CloseWindow(HWINDOW hWindow)  //�رմ���
{
	IsWindowDebug(hWindow, __FUNCTION__);
	::PostMessage(((window_*)hWindow)->hWnd, WM_CLOSE, 0, 0);
}

/// @brief ���������.
/// @param hWindow  ���ھ��.
/// @param hEle   Ԫ�ؾ��.
/// @param width  ���.
/// @param height �߶�.
void WINAPI XWnd_CreateCaret(HWINDOW hWindow, HELE hEle, int width, int height) //���������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretBitmap)
	{
		XTRACE("edit ��������� \n");
		return;
	}

	//�����
	pWindow->hCaretBitmap = XDraw_CreateDIBSection(NULL, width, height);

	pWindow->bCaretShow = FALSE;
	pWindow->hCaretEle = hEle;
	pWindow->caretWidth = width;
	pWindow->caretHeight = height;
	XWnd_SetTimer(hWindow, IDT_CARET, 500);
}

/// @brief ���ò������С.
/// @param hWindow  ���ھ��.
/// @param width    ��������.
/// @param height   ������߶�.
void WINAPI XWnd_SetCaretSize(HWINDOW hWindow, int width, int height) //���ò������С
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;

	if (width == pWindow->caretWidth && height == pWindow->caretHeight)
		return;

	if (pWindow->hCaretBitmap)
		DeleteObject(pWindow->hCaretBitmap);

	if (pWindow->bCaretShow && pWindow->bCaretErase) //��Ҫ���������
	{
		Wnd_EraseCaret(hWindow); //����
	}

	pWindow->hCaretBitmap = XDraw_CreateDIBSection(NULL, width, height);
	pWindow->caretWidth = width;
	pWindow->caretHeight = height;
	Wnd_GetCaretBk(hWindow); //��ȡ���������
}

void Wnd_GetCaretBk(HWINDOW hWindow) //��ȡ���������
{
	window_ *pWindow = (window_*)hWindow;
	//��ȡ��λ�ñ���
	POINT  ptCaret = pWindow->caretPt;
	XEle_PointToNCWnd(pWindow->hCaretEle, &ptCaret);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED)
	{
		HDC hdcBk = CreateCompatibleDC(NULL);
		SelectObject(hdcBk, pWindow->hBtimap);

		HDC hdcCaret = CreateCompatibleDC(NULL);
		SelectObject(hdcCaret, pWindow->hCaretBitmap);

		int borderSize = 0;
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
			borderSize = XC_WIND_SHADOW_SIZE;

		BitBlt(hdcCaret, 0, 0, pWindow->caretWidth, pWindow->caretHeight, hdcBk, ptCaret.x + borderSize, ptCaret.y + borderSize, SRCCOPY);

		DeleteDC(hdcBk);
		DeleteDC(hdcCaret);
		return;
	}

	HDC hdc = GetDC(pWindow->hWnd);
	HDC hdcCaret = CreateCompatibleDC(NULL);
	SelectObject(hdcCaret, pWindow->hCaretBitmap);

	BitBlt(hdcCaret, 0, 0, pWindow->caretWidth, pWindow->caretHeight, hdc, ptCaret.x, ptCaret.y, SRCCOPY);

	DeleteDC(hdcCaret);
	ReleaseDC(pWindow->hWnd, hdc);
}

/// @brief ���ò����λ��,������ڲ�������ڵ�Ԫ��.
/// @param hWindow  ���ھ��.
/// @param x  �����x����.
/// @param y  �����y����.
void WINAPI XWnd_SetCaretPos(HWINDOW hWindow, int x, int y) //���ò����λ��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle)
	{
		if (pWindow->bCaretShow && pWindow->bCaretErase) //��Ҫ���������
		{
			Wnd_EraseCaret(hWindow); //����
		}

		//��λ��
		pWindow->caretPt.x = x;
		pWindow->caretPt.y = y;
		Wnd_GetCaretBk(hWindow); //��ȡ���������
		pWindow->bCaretErase = TRUE;
	}
}

/// @brief ���ò����λ�ü���С,������ڲ�������ڵ�Ԫ��.
/// @param hWindow  ���ھ��.
/// @param x  �����x����.
/// @param y  �����y����.
/// @param width  ��������.
/// @param height ������߶� .
void WINAPI XWnd_SetCaretPosEx(HWINDOW hWindow, int x, int y, int width, int height) //���ò����λ��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle)
	{
		if (pWindow->bCaretShow && pWindow->bCaretErase) //��Ҫ���������
		{
			Wnd_EraseCaret(hWindow); //����
		}

		//�޸Ĳ������С
		if (width != pWindow->caretWidth || height != pWindow->caretHeight)
		{
			if (pWindow->hCaretBitmap)
				DeleteObject(pWindow->hCaretBitmap);

			pWindow->hCaretBitmap = XDraw_CreateDIBSection(NULL, width, height);
			pWindow->caretWidth = width;
			pWindow->caretHeight = height;
		}

		//��λ��
		pWindow->caretPt.x = x;
		pWindow->caretPt.y = y;
		Wnd_GetCaretBk(hWindow); //��ȡ���������
		pWindow->bCaretErase = TRUE;
	}
}

/// @brief ���ò������ɫ.
/// @param hWindow  ���ھ��.
/// @param color  �������ɫ.
void WINAPI XWnd_SetCaretColor(HWINDOW hWindow, COLORREF color) //���ò������ɫ
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->caretColor = color;
}

/// @brief ��ʾ�����.
/// @param hWindow  ���ھ��.
/// @param bShow  TRUE��ʾ�����,�������ز����.
void WINAPI XWnd_ShowCaret(HWINDOW hWindow, BOOL bShow)  //��ʾ�����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (NULL == pWindow->hCaretEle)
		return;

	if (bShow) //��ʾ�����
	{
		Wnd_GetCaretBk(hWindow);
		pWindow->bCaretErase = TRUE;
		pWindow->bCaretShow = TRUE;
	}
	else //���ز����
	{
		if (pWindow->bCaretErase) //��Ҫ���������
		{
			Wnd_EraseCaret(hWindow); //����
			pWindow->bCaretErase = FALSE;
		}
		pWindow->bCaretShow = FALSE;
	}
}

/// @brief ���ٲ����.
/// @param hWindow  ���ھ��.
void WINAPI XWnd_DestroyCaret(HWINDOW hWindow) //���ٲ����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle)
	{
		//-----------------------------------------
		if (pWindow->bCaretShow && pWindow->bCaretErase) //��Ҫ���������
		{
			Wnd_EraseCaret(hWindow); //����
		}
		pWindow->bCaretErase = FALSE;

		pWindow->bCaretShow = FALSE;
		pWindow->hCaretEle = NULL;
		KillTimer(pWindow->hWnd, IDT_CARET);

		if (pWindow->hCaretBitmap)
		{
			DeleteObject(pWindow->hCaretBitmap);
			pWindow->hCaretBitmap = NULL;
		}
	}
}

void Wnd_DrawCaret(HWINDOW hWindow) //������Ʋ����
{
	window_ *pWindow = (window_*)hWindow;
	if (FALSE == IsWindowVisible(pWindow->hWnd))
		return;

	if (NULL == pWindow->hCaretEle || FALSE == pWindow->bCaretShow)
		return;
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //͸������
	{
		Wnd_DrawCaretTransparent(hWindow);
		return;
	}

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);


	RECT rcCare; //���������
	rcCare.left = pt.x;
	rcCare.top = pt.y;
	rcCare.right = pt.x + pWindow->caretWidth;
	rcCare.bottom = pt.y + pWindow->caretHeight;

	//����Ƿ񳬳���Χ
	ele_ *pParentEle = (ele_*)pWindow->hCaretEle;//((ele_*)pWindow->hCaretEle)->pParentEle;
	RECT rcParent;
	while (pParentEle)
	{
		XEle_GetClientRect((HELE)pParentEle, &rcParent);
		XEle_RectToNCWnd((HELE)pParentEle, &rcParent);

		if (rcCare.left<rcParent.left || rcCare.right>rcParent.right ||
			rcCare.top<rcParent.top || rcCare.bottom>rcParent.bottom)
		{
			return;
		}
		pParentEle = pParentEle->pParentEle;
	}

	HDC hdc = GetDC(pWindow->hWnd);
	HDC hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, pWindow->hCaretBitmap);

	if (pWindow->bCaretErase) //����
	{
		//	XTRACE("����� show \n");

		RECT rc = { pt.x,pt.y,pt.x + pWindow->caretWidth,pt.y + pWindow->caretHeight };
		HBRUSH hBrush = CreateSolidBrush(pWindow->caretColor);
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hBrush);
	}
	else //����
	{
		//	XTRACE("����� hide \n");

		BitBlt(hdc, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDC);
	ReleaseDC(pWindow->hWnd, hdc);
}

void Wnd_DrawCaretMenDC(HWINDOW hWindow, HDRAW hDraw) //������Ʋ�������ڴ�DC
{
	window_ *pWindow = (window_*)hWindow;
	if (FALSE == IsWindowVisible(pWindow->hWnd))
		return;

	if (NULL == pWindow->hCaretEle || FALSE == pWindow->bCaretShow)
		return;

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //͸������
	{
		Wnd_DrawCaretTransparentMemDC(hWindow, hDraw);
		return;
	}

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	RECT rcCare; //���������
	rcCare.left = pt.x;
	rcCare.top = pt.y;
	rcCare.right = pt.x + pWindow->caretWidth;
	rcCare.bottom = pt.y + pWindow->caretHeight;

	//����Ƿ񳬳���Χ
	ele_ *pParentEle = (ele_*)pWindow->hCaretEle;//((ele_*)pWindow->hCaretEle)->pParentEle;
	RECT rcParent;
	while (pParentEle)
	{
		XEle_GetClientRect((HELE)pParentEle, &rcParent);
		XEle_RectToNCWnd((HELE)pParentEle, &rcParent);

		if (rcCare.left<rcParent.left || rcCare.right>rcParent.right ||
			rcCare.top<rcParent.top || rcCare.bottom>rcParent.bottom)
		{
			return;
		}
		pParentEle = pParentEle->pParentEle;
	}

	HDC hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, pWindow->hCaretBitmap);

	if (pWindow->bCaretErase) //����
	{
		//	XTRACE("����� show \n");

		RECT rc = { pt.x,pt.y,pt.x + pWindow->caretWidth,pt.y + pWindow->caretHeight };
		HBRUSH hBrush = CreateSolidBrush(pWindow->caretColor);
		XDraw_FillRect_(hDraw, &rc, hBrush);
		DeleteObject(hBrush);
	}
	else //����
	{
		//	XTRACE("����� hide \n");

		XDraw_BitBlt_(hDraw, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDC);
}

void Wnd_EraseCaret(HWINDOW hWindow) //���������
{
	window_ *pWindow = (window_*)hWindow;

	if (FALSE == pWindow->bCaretErase)
		return;

	pWindow->bCaretErase = FALSE;

	if (FALSE == IsWindowVisible(pWindow->hWnd))
		return;

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	HDC hdc = GetDC(pWindow->hWnd);
	HDC hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, pWindow->hCaretBitmap);

	BitBlt(hdc, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(hMemDC);
	ReleaseDC(pWindow->hWnd, hdc);
}

void Wnd_DrawCaretTransparent(HWINDOW hWindow) //������Ʋ����,������͸��ʱ
{
	window_ *pWindow = (window_*)hWindow;

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	//����Ƿ񳬳�����ͼ
	ele_ *pParentEle = ((ele_*)pWindow->hCaretEle)->pParentEle;
	RECT rcParent;
	while (pParentEle)
	{
		XEle_GetNCWndRect((HELE)pParentEle, &rcParent);
		if (FALSE == PtInRect(&rcParent, pt))
		{
			return;
		}
		pParentEle = pParentEle->pParentEle;
	}

	//�����ػ���������
	HDC memDC = CreateCompatibleDC(NULL);         //��������DC ���� (�����ǿͻ���)
	SelectObject(memDC, pWindow->hBtimap);

	HDC hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, pWindow->hCaretBitmap);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
	{
		pt.x += XC_WIND_SHADOW_SIZE;
		pt.y += XC_WIND_SHADOW_SIZE;
	}

	if (pWindow->bCaretErase) //����
	{
		Graphics graphics(memDC);
		SolidBrush blackBrush(Color(255, GetRValue(pWindow->caretColor), GetGValue(pWindow->caretColor), GetBValue(pWindow->caretColor)));
		Rect fillRect(pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight);
		graphics.FillRectangle(&blackBrush, fillRect);

		//pWindow->bCaretErase=FALSE;
	}
	else //����
	{
		//pWindow->bCaretErase=TRUE;
		BitBlt(memDC, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDC);

	RECT rcSysNCClient;
	GetWindowRect(pWindow->hWnd, &rcSysNCClient);
	rcSysNCClient.right = rcSysNCClient.right - rcSysNCClient.left;
	rcSysNCClient.bottom = rcSysNCClient.bottom - rcSysNCClient.top;
	rcSysNCClient.left = 0;
	rcSysNCClient.top = 0;

	HDC hdc = GetWindowDC(pWindow->hWnd);

	BLENDFUNCTION m_blend;
	m_blend.BlendOp = 0;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = 1;
	m_blend.SourceConstantAlpha = pWindow->transparentAlpha;

	RECT rcWnd;
	GetWindowRect(pWindow->hWnd, &rcWnd);
	POINT ptDst = { rcWnd.left, rcWnd.top };
	POINT ptSrc = { 0, 0 };
	SIZE m_sizeWnd = { rcSysNCClient.right,rcSysNCClient.bottom };
	//int res=
	UpdateLayeredWindow(pWindow->hWnd, hdc, &ptDst, &m_sizeWnd, memDC, &ptSrc, 0, &m_blend, ULW_ALPHA);
	//	if(0==res)
	//	{
	//		DWORD err= GetLastError();
	//		XTRACE("Wnd_DrawCaretTransparent() err=%d \n",err);
	//	}else
	//		XTRACE("Wnd_DrawCaretTransparent() \n");

	DeleteDC(memDC);
	ReleaseDC(pWindow->hWnd, hdc);
}

void Wnd_DrawCaretTransparentMemDC(HWINDOW hWindow, HDRAW hDraw) //������Ʋ�������ڴ�DC
{
	window_ *pWindow = (window_*)hWindow;

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	//����Ƿ񳬳�����ͼ
	ele_ *pParentEle = ((ele_*)pWindow->hCaretEle)->pParentEle;
	RECT rcParent;
	while (pParentEle)
	{
		XEle_GetNCWndRect((HELE)pParentEle, &rcParent);
		if (FALSE == PtInRect(&rcParent, pt))
		{
			return;
		}
		pParentEle = pParentEle->pParentEle;
	}

	HDC hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, pWindow->hCaretBitmap);

	if (pWindow->bCaretErase) //����
	{
		XTRACE("����� show \n");

		HDC hdc = XDraw_GetHDC_(hDraw);
		int posx = 0;
		int posy = 0;
		XDraw_GetOffset_(hDraw, &posx, &posy);

		Graphics graphics(hdc);
		SolidBrush blackBrush(Color(255, GetRValue(pWindow->caretColor), GetGValue(pWindow->caretColor), GetBValue(pWindow->caretColor)));
		Rect fillRect(pt.x + posx, pt.y + posy, pWindow->caretWidth, pWindow->caretHeight);
		graphics.FillRectangle(&blackBrush, fillRect);

	}
	else //����
	{
		XTRACE("����� hide \n");

		XDraw_BitBlt_(hDraw, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}

	DeleteDC(hMemDC);
}

/// @brief ��ȡ���ڿͻ�������,���Ͻ�(0,0).
/// @param hWindow  ���ھ��.
/// @param pRect    ���մ��ڿͻ�������.
BOOL WINAPI XWnd_GetClientRect(HWINDOW hWindow, RECT *pRect) //��ȡ�ͻ�������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (NULL == hWindow || NULL == pRect)
		return FALSE;
	window_ *pWindow = (window_*)hWindow;
	GetClientRect(pWindow->hWnd, pRect);

	pRect->left = 0;
	pRect->top = 0;
	pRect->right = pRect->right - pWindow->borderLeft - pWindow->borderRight;

	pRect->bottom = pRect->bottom - pWindow->borderBottom;

	pRect->bottom = pRect->bottom - XWnd_GetClientTop(hWindow);

	return TRUE;
}

/// @brief ��ȡ���ڷǿͻ�����С,���ڷǿͻ�������ϵ.
/// @param hWindow  ���ھ��.
/// @param pRect    ���մ��ڷǿͻ�����С����.
void WINAPI XWnd_GetNCClientRect(HWINDOW hWindow, RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	GetClientRect(pWindow->hWnd, pRect);
}

/// @brief ��ȡ������߿���.
/// @param hWindow  ���ھ��.
/// @return �ͻ�������.
int WINAPI XWnd_GetClientLeft(HWINDOW hWindow) //�ͻ�������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->borderLeft;
}

/// @brief ��ȡ���ڿͻ����Ҽ��.
/// @param hWindow  ���ھ��.
/// @return �ͻ����Ҽ��.
int WINAPI XWnd_GetClientRight(HWINDOW hWindow) //�ͻ����Ҽ��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->borderRight;
}

/// @brief ��ȡ���ڿͻ����¼��.
/// @param hWindow  ���ھ��.
/// @return �ͻ����¼��.
int WINAPI XWnd_GetClientBottom(HWINDOW hWindow) //�ͻ����¼��
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->borderBottom;
}

/// @brief ��ȡ���ڿͻ����ϼ��.��ʾ�ͻ��������봰�ڶ�������.
/// @param hWindow  ���ھ��.
/// @return �ͻ����ϼ��.
int WINAPI XWnd_GetClientTop(HWINDOW hWindow)  //�ͻ����ϼ��
{
	IsWindowDebug(hWindow, __FUNCTION__);

	int height = XWnd_GetCaptionHeight(hWindow);

	//�˵���
	if (((window_*)hWindow)->hMenuBar)
	{
		RECT rc;
		XEle_GetClientRect(((window_*)hWindow)->hMenuBar, &rc);
		height += rc.bottom;
	}
	//������
	if (((window_*)hWindow)->hToolBar)
	{
		RECT rc;
		XEle_GetClientRect(((window_*)hWindow)->hToolBar, &rc);
		height += rc.bottom;
	}
	return height;
}

/// @brief ��ȡ�������߶�,�������������Ͳ˵����ĸ߶�.
/// @param hWindow  ���ھ��.
/// @return �������߶�.
int WINAPI XWnd_GetCaptionHeight(HWINDOW hWindow) //��ȡ�������߶�
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (((window_*)hWindow)->captionHeight > 0)
		return ((window_*)hWindow)->captionHeight;
	else
		return ((window_*)hWindow)->borderTop;
}

/// @brief ���ڷǿͻ�������ת�����ͻ�������.
/// @param hWindow  ���ھ��.
/// @param pRect  ����ǿͻ�������,ת��Ϊ�ͻ����������.
void WINAPI XWnd_WindowToClientRect(HWINDOW hWindow, RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);

	int top = XWnd_GetClientTop(hWindow);
	int left = XWnd_GetClientLeft(hWindow);
	pRect->top -= top;
	pRect->bottom -= top;

	pRect->left -= left;
	pRect->right -= left;
}

/// @brief ���ڷǿͻ�����ת�����ͻ��������.
/// @param hWindow  ���ھ��.
/// @param pPt    ���봰�ڷǿͻ��������,ת�����ͻ�����������.
void WINAPI XWnd_WindowToClientPt(HWINDOW hWindow, POINT *pPt)
{
	IsWindowDebug(hWindow, __FUNCTION__);

	pPt->y -= XWnd_GetClientTop(hWindow);
	pPt->x -= ((window_*)hWindow)->borderLeft;
}

/// @brief ���ڰ��û�����
/// @param hWindow  ���ھ��.
/// @param data   �û�����.
void WINAPI XWnd_SetUserData(HWINDOW hWindow, int data)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->userData = data;
}

/// @brief ���ڻ�ȡ�󶨵��û�����
/// @param hWindow  ���ھ��.
/// @return data   �û�����.
int  WINAPI XWnd_GetUserData(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->userData;
}

//���ڴ������
BOOL CALLBACK Wnd_WindowProc(HWINDOW hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	//����ϵͳ���ƴ��ڱ߿�
	//	if( WM_NCACTIVATE==message)
	//		XWnd_RedrawWnd(hWindow);

	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	//TODO:�Ƿ��лص�����
	if (XWM_EVENT_ALL == message)
	{
		if (wParam < EVENT_LIST_SIZE && g_eventList[wParam].bEvent)
		{
			if (g_eventList[wParam].hEle && (XC_ELE == *(UINT*)g_eventList[wParam].hEle)) //ȷ��Ԫ�ؾ����Ч
			{
				Ele_EventDispatch(g_eventList[wParam].hEle, g_eventList[wParam].type, g_eventList[wParam].wParam, g_eventList[wParam].lParam);
			}
			g_eventList[wParam].bEvent = FALSE;
			//XTRACE("����:  ����(%d),�¼�(%d)\n",wParam,g_eventList[wParam].type);
			return TRUE;
		}
		XTRACE("δ�����¼�: ����(%d),�¼�(%d)\n", wParam, g_eventList[wParam].type);
		return TRUE;
	}

	window_ *pWindow = (window_*)hWindow;
	int count = Array_GetCount(pWindow->hArray_msg);
	for (int i = 0; i < count; i++)
	{
		if (message == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->message)
		{
			return ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->pFunConv(hWindow, (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i), wParam, lParam);
		}
	}
	return FALSE;
}

BOOL CALLBACK Wnd_OnDrawT(HWINDOW hWindow, WPARAM wParam, LPARAM lParam)
{
	window_ *pWindow = (window_*)hWindow;

	BOOL bResult = FALSE;
	RECT rect;
	HELE hEle = NULL;
	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	if (pWindow->drawWindow.bValid)
	{
		pWindow->drawWindow.bValid = FALSE;
		rect = pWindow->drawWindow.rect;
		hEle = pWindow->drawWindow.hEle;
		bResult = TRUE;
	}
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);

	if (bResult)
	{
		HDC hdc = GetDC(pWindow->hWnd);
		if (pWindow->drawWindow.hEle)
		{
			//XTRACE("Wnd_OnDrawT() Ԫ�� ...\n");
			Wnd_PaintEle2(hWindow, hEle, hdc, &rect);

		}
		else  //���ƴ���
		{
			int count = Array_GetCount(pWindow->hArray_msg);
			for (int i = 0; i < count; i++)
			{
				if (WM_PAINT == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->message)
				{
					//XTRACE("Wnd_OnDrawT()  ����...\n");
					Wnd_DrawWindowHandle2(hWindow, (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i), &rect, hdc);
					break;
				}
			}
		}
		ReleaseDC(pWindow->hWnd, hdc);
	}

	return TRUE;
}

BOOL Wnd_NCWindowProc(HWINDOW hWindow, UINT NCmessage, WPARAM wParam, LPARAM lParam)  //�ǿͻ�����Ϣ����
{
	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	window_ *pWindow = (window_*)hWindow;
	int count = Array_GetCount(pWindow->hArray_NCmsg);
	for (int i = 0; i < count; i++)
	{
		if (NCmessage == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i))->message)
		{
			return ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i))->pFunConv(hWindow, (windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i), wParam, lParam);
		}
	}
	return FALSE;
}

//���ƴ���
BOOL CALLBACK Wnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;

	if (NULL == pWindow->hImage_client)
		return TRUE;

	RECT rcDraw = pWindow->rcDraw;

	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);

	int cx = rcDraw.right - rcDraw.left;
	int cy = rcDraw.bottom - rcDraw.top;

	if (cx < 1 || cy < 1) return TRUE; //����Ҫ����

	XDraw_HImageSuper_(hDraw, pWindow->hImage_client, &rect);
	return TRUE;
}

BOOL CALLBACK Wnd_OnDestroy(HWINDOW hWindow)
{
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCDestroy(HWINDOW hWindow) //�ͷ��ڴ�
{
	if (0 == Wnd_GetWindowCount())
		PostQuitMessage(0);

	window_ *pWindow = (window_*)hWindow;
	//�ͷų�Ա����
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		XEle_Destroy((HELE)Array_GetAtEle(pWindow->hArrayEle, 0)); //������Ԫ��
	}
	count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		XEle_Destroy((HELE)Array_GetAtEle(pWindow->hArrayEleNC, 0)); //������Ԫ��
	}
	XArray_Destroy(pWindow->hArrayEle); //��Ԫ���б�
	XArray_Destroy(pWindow->hArrayEleNC);//��Ԫ���б�,�ǿͻ���
	pWindow->hArrayEle = NULL;
	pWindow->hArrayEleNC = NULL;

	//������Ϣ�����������
	windowProc_ *pProc = pWindow->pWndProc;
	void *pDel = NULL;
	while (pProc)
	{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pProc->pClass_Fun_Info) free(pProc->pClass_Fun_Info);
#endif
		pDel = pProc;
		pProc = pProc->pNext;
		free(pDel);
	}
	pWindow->pWndProc = NULL;
	//////////////////////�ͷ���Ϣ��

	//��Ϣ�����
	int Array_msg_count = Array_GetCount(pWindow->hArray_msg);
	for (int i = 0; i < Array_msg_count; i++)
	{
		windowMsg_Header_ *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i);
		windowMsg_ *pMsg = pHeader->pList;
		windowMsg_ *pDel = NULL;
		while (pMsg)
		{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
			if (pMsg->pClass_Fun_Info) free(pMsg->pClass_Fun_Info);
#endif
			pDel = pMsg;
			pMsg = pMsg->pNext;
			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pWindow->hArray_msg);

	//�ǿͻ�����Ϣ�����
	int Array_event_count = Array_GetCount(pWindow->hArray_NCmsg);
	for (int i = 0; i < Array_event_count; i++)
	{
		windowMsg_Header_ *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i);
		windowMsg_ *pEvent = pHeader->pList;
		windowMsg_ *pDel = NULL;
		while (pEvent)
		{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
			if (pEvent->pClass_Fun_Info) free(pEvent->pClass_Fun_Info);
#endif
			pDel = pEvent;
			pEvent = pEvent->pNext;
			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pWindow->hArray_NCmsg);

	//��ͼ
	if (pWindow->hImage_client) XImage_Destroy(pWindow->hImage_client);
	if (pWindow->hImageNC)      XImage_Destroy(pWindow->hImageNC);
	if (pWindow->hImageCaption) XImage_Destroy(pWindow->hImageCaption);
	if (pWindow->hImageLeft)    XImage_Destroy(pWindow->hImageLeft);
	if (pWindow->hImageRight)   XImage_Destroy(pWindow->hImageRight);
	if (pWindow->hImageBottom)  XImage_Destroy(pWindow->hImageBottom);

	if (pWindow->hFontX)        XFont_Destroy(pWindow->hFontX);

	if (pWindow->hBtimap)
		DeleteObject(pWindow->hBtimap);

	if (pWindow->hArrayPGrids)
		XArray_Destroy(pWindow->hArrayPGrids);


	object_type_  *pNode = pWindow->object.pTypeList;
	object_type_  *pDelNode = NULL;
	while (pNode)
	{
		pDelNode = pNode;
		pNode = pNode->pNext;
		free(pDelNode);
	}

	free(hWindow);
	return TRUE;
}

/// @brief ����ע����Ϣ������
/// @param hWindow ���ھ��
/// @param message ������Ϣ����.
/// @param pFun    ������Ϣ������
void WINAPI XWnd_RegisterMessage(HWINDOW hWindow, int message, void *pFun)  //����ע����Ϣ������
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---����Ϣ����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pWindow->hArray_msg);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (message == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)malloc(sizeof(windowMsg_Header_));
		pHeader->message = message;

		switch (message)
		{
		case XWM_MOUSECLICK:     pHeader->pFunConv = Wnd_ConvMouseClick; break;
		case XWM_MOUSEDBCLICK:   pHeader->pFunConv = Wnd_ConvMouseDBClick; break;
		case XWM_REDRAW_ELE:     pHeader->pFunConv = Wnd_ConvRedrawEle; break;
		case XWM_MENUSELECT:     pHeader->pFunConv = Wnd_ConvMenuSelect; break;
		case XWM_MENUEXIT:       pHeader->pFunConv = Wnd_ConvMenuExit; break;
		case XWM_SETFONT:        pHeader->pFunConv = Wnd_ConvSetFont; break;

		case WM_PAINT:           pHeader->pFunConv = Wnd_ConvPaint; break;
		case WM_MOUSEMOVE:       pHeader->pFunConv = Wnd_ConvMouseMove; break;
		case WM_LBUTTONDOWN:     pHeader->pFunConv = Wnd_ConvLButtonDown; break;
		case WM_LBUTTONUP:       pHeader->pFunConv = Wnd_ConvLButtonUp; break;
		case WM_RBUTTONDOWN:     pHeader->pFunConv = Wnd_ConvRButtonDown; break;
		case WM_RBUTTONUP:       pHeader->pFunConv = Wnd_ConvRButtonUp; break;
		case WM_EXITSIZEMOVE:    pHeader->pFunConv = Wnd_ConvExitSizeMove; break;
		case WM_MOUSELEAVE:      pHeader->pFunConv = Wnd_ConvMouseLeave; break;
		case WM_SIZE:            pHeader->pFunConv = Wnd_ConvSize; break;
		case WM_TIMER:           pHeader->pFunConv = Wnd_ConvTimer; break;
		case XWM_TIMER:          pHeader->pFunConv = Wnd_ConvTimer2; break;
		case WM_SETFOCUS:        pHeader->pFunConv = Wnd_ConvSetFocus; break;
		case WM_KILLFOCUS:       pHeader->pFunConv = Wnd_ConvKillFocus; break;
		case WM_CAPTURECHANGED:  pHeader->pFunConv = Wnd_ConvCaptureChanged; break;
		case WM_MOUSEWHEEL:      pHeader->pFunConv = Wnd_ConvMouseWheel; break;
		case WM_DESTROY:         pHeader->pFunConv = Wnd_ConvDestroy; break;
		case WM_NCDESTROY:       pHeader->pFunConv = Wnd_ConvNCDestroy; break;
		case WM_CLOSE:           pHeader->pFunConv = Wnd_ConvClose; break;

		default: pHeader->pFunConv = Wnd_ConvOther; break;
		}

		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pWindow->hArray_msg, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

/// @brief ע�ᴰ�ڷǿͻ�����Ϣ,ע������ķǿͻ�����GUI���߼��ϵķǿͻ���.
/// @param hWindow ���ھ��
/// @param message ������Ϣ����.
/// @param pFun    ������Ϣ������
void WINAPI XWnd_RegisterNCMessage(HWINDOW hWindow, int message, void *pFun)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---����Ϣ����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pWindow->hArray_NCmsg);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (message == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)malloc(sizeof(windowMsg_Header_));
		pHeader->message = message;

		switch (message)
		{
		case XWM_NCPAINT: pHeader->pFunConv = Wnd_ConvNCPaint; break;
		case XWM_NCENDPAINT: pHeader->pFunConv = Wnd_ConvNCEndPaint; break;

		case XWM_NCMOUSEMOVE: pHeader->pFunConv = Wnd_ConvNCMouseMove; break;

		case XWM_NCLBUTTONDOWN: pHeader->pFunConv = Wnd_ConvNCLButtonDown; break;
		case XWM_NCLBUTTONUP: pHeader->pFunConv = Wnd_ConvNCLButtonUp; break;

		case XWM_NCRBUTTONDOWN: pHeader->pFunConv = Wnd_ConvNCRButtonDown; break;
		case XWM_NCRBUTTONUP: pHeader->pFunConv = Wnd_ConvNCRButtonUp; break;

		case XWM_NCMOUSECLICK: pHeader->pFunConv = Wnd_ConvNCMouseClick; break;
		case XWM_NCMOUSEDBCLICK: pHeader->pFunConv = Wnd_ConvNCMouseDBClick; break;

		default:XTRACE("XWnd_RegisterNCMessage() δ֪��Ϣ���� \n"); pHeader->pFunConv = NULL; break;
		}

		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pWindow->hArray_NCmsg, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

/// @brief ע�ᴰ����Ϣ�������,��������������������Ϣ.
/// @param hWindow ���ھ��
/// @param pFun    ������Ϣ������,��������
/// @code  BOOL CALLBACK WndProc(HWINDOW hWindow,UINT message, WPARAM wParam, LPARAM lParam); @endcode
void WINAPI XWnd_RegisterMsgProc(HWINDOW hWindow, pFunWndMsgProc pFun)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	windowProc_  *&pProcT = ((window_*)hWindow)->pWndProc;
	if (NULL == pProcT)
	{
		pProcT = (windowProc_*)malloc(sizeof(windowProc_));
		pProcT->pFun = pFun;
		pProcT->pNext = NULL;
	}
	else  //���뿪ʼλ��
	{
		windowProc_ *pNew = (windowProc_*)malloc(sizeof(windowProc_));
		pNew->pNext = pProcT;
		pProcT = pNew;
		pProcT->pFun = pFun;
	}
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	pProcT->pClass_Fun_Info = NULL;
#endif
}

/// @brief ���Ԫ�ص����ڿͻ���,�����ӵ��ǿͻ�����ʹ�ú��� @ref XWnd_AddEleNC.
/// @param hWindow ���ھ��
/// @param hEle    ��ӵ�Ԫ����Դ���.
void WINAPI XWnd_AddEle(HWINDOW hWindow, HELE hEle)
{
#ifdef _DEBUG
	IsWindowDebug(hWindow, __FUNCTION__);
	IsEleDebug(hEle, __FUNCTION__);
	//����Ƿ����и�Ԫ��
	if (((ele_*)hEle)->pParentEle || ((ele_*)hEle)->pWindow)
	{
		MessageBox(NULL, L"XWnd_AddEle()�ظ����Ԫ��,��Ԫ���Ѿ��и�Ԫ�ػ򴰿�,���Ƚ��Ƴ�!", L"�Ųʽ����-������ʾ!", MB_OK);
		exit(0);
	}
	//�ж�Ԫ���Ƿ��ظ����
	int count = Array_GetCount(((window_*)hWindow)->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEle, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() �ظ����Ԫ��", L"�Ųʽ����-������ʾ!", MB_OK);
			exit(0);
		}
	}
	count = Array_GetCount(((window_*)hWindow)->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEleNC, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() �ظ����Ԫ��", L"�Ųʽ����-������ʾ!", MB_OK);
			exit(0);
		}
	}
#endif
	((ele_*)hEle)->bTopLevel = TRUE;
	XArray_Add(((window_*)hWindow)->hArrayEle, hEle);
	Ele_SetWindow(hEle, hWindow, TRUE);
	//	if(hWindow)
	//		Resource_AddEle(hEle);
}

/// @brief ���Ԫ�ص����ڷǿͻ���.
/// @param hWindow ���ھ��
/// @param hEle    ��ӵ�Ԫ����Դ���.
void WINAPI XWnd_AddEleNC(HWINDOW hWindow, HELE hEle) //��ӵ��ǿͻ���
{
#ifdef _DEBUG
	IsWindowDebug(hWindow, __FUNCTION__);
	IsEleDebug(hEle, __FUNCTION__);
	//����Ƿ����и�Ԫ��
	if (((ele_*)hEle)->pParentEle || ((ele_*)hEle)->pWindow)
	{
		MessageBox(NULL, L"XWnd_AddEle()�ظ����Ԫ��,��Ԫ���Ѿ��и�Ԫ�ػ򴰿�,���Ƚ��Ƴ�!", L"�Ųʽ����-������ʾ!", MB_OK);
		exit(0);
	}
	//�ж�Ԫ���Ƿ��ظ����
	int count = Array_GetCount(((window_*)hWindow)->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEle, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() �ظ����Ԫ��", L"�Ųʽ����-������ʾ!", MB_OK);
			exit(0);
		}
	}
	count = Array_GetCount(((window_*)hWindow)->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEleNC, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() �ظ����Ԫ��", L"�Ųʽ����-������ʾ!", MB_OK);
			exit(0);
		}
	}
#endif
	((ele_*)hEle)->pWindow = (window_*)hWindow;
	((ele_*)hEle)->bTopLevel = TRUE;
	((ele_*)hEle)->bClient = FALSE;
	XArray_Add(((window_*)hWindow)->hArrayEleNC, hEle);
	Ele_SetWindow(hEle, hWindow, FALSE);
	//	if(hWindow)
	//		Resource_AddEle(hEle);
}

/// @brief ��Ӳ˵��������ڵķǿͻ���,�����ڴ�С�ı�ʱ,�Զ������˵�����С.
/// �������ӵ����ڿͻ���,��ʹ�� @ref XWnd_AddEle ����,����㴴����ʱ,�����˴��ھ��,���Զ���ӵ����ڵķǿͻ���.
/// @param hWindow ���ھ��
/// @param hEle    �˵������.
void WINAPI XWnd_AddMenuBar(HWINDOW hWindow, HELE hEle) //��ӹ�����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	IsMenuBarDebug(hEle, __FUNCTION__);

	if (((window_*)hWindow)->hMenuBar)
	{
		XMessageBox(hWindow, L"�ظ���ӹ�����");
		return;
	}
	XWnd_AddEleNC(hWindow, hEle);
	((window_*)hWindow)->hMenuBar = hEle;

	XWnd_Adjust(hWindow);
}

/// @brief ��ӹ����������ڵķǿͻ���,�����ڴ�С�ı�ʱ,�Զ������������Ĵ�С.
/// �������ӵ����ڵĿͻ���,��ʹ�� @ref XWnd_AddEle ����,����㴴����ʱ,�����˴��ھ��,���Զ���ӵ����ڵķǿͻ���.
/// @param hWindow ���ھ��
/// @param hEle    ���������.
void WINAPI XWnd_AddToolBar(HWINDOW hWindow, HELE hEle)  //��ӹ�����
{
	IsWindowDebug(hWindow, __FUNCTION__);
	IsToolBarDebug(hEle, __FUNCTION__);

	if (((window_*)hWindow)->hToolBar)
	{
		XMessageBox(hWindow, L"�ظ���ӹ�����");
		return;
	}

	if (((ele_*)hEle)->pWindow)
	{
		if (NULL == ((ele_*)hEle)->pParentEle)
		{
			if (FALSE == ((ele_*)hEle)->bClient)
			{
				((window_*)hWindow)->hToolBar = hEle;
				return;
			}
		}
		else
			XEle_RemoveEle(hEle);
	}

	XWnd_AddEleNC(hWindow, hEle);
	((window_*)hWindow)->hToolBar = hEle;

	XWnd_Adjust(hWindow);
}

/// @brief �������ڲ���.
/// @param hWindow ���ھ��.
void WINAPI XWnd_Adjust(HWINDOW hWindow)  //�������ڲ���
{
	IsWindowDebug(hWindow, __FUNCTION__);

	window_ *pWindow = (window_*)hWindow;
	RECT rcWindow;
	GetClientRect(pWindow->hWnd, &rcWindow);

	Wnd_AdjustCaption(hWindow, rcWindow.right - rcWindow.left);

	RECT rClient;
	XWnd_GetClientRect(hWindow, &rClient);
	int  MenuBarHeight = 0;
	int  ToolBarHeight = 0;

	if (pWindow->hMenuBar)
	{
		RECT rcMenuBar;
		XEle_GetClientRect(pWindow->hMenuBar, &rcMenuBar);
		MenuBarHeight = rcMenuBar.bottom - rcMenuBar.top;

		rcMenuBar.left = XWnd_GetClientLeft(hWindow);
		rcMenuBar.right = rClient.right + XWnd_GetClientLeft(hWindow);

		rcMenuBar.top = XWnd_GetCaptionHeight(hWindow);
		rcMenuBar.bottom = rcMenuBar.top + MenuBarHeight;
		XEle_SetRect(pWindow->hMenuBar, &rcMenuBar);
	}

	//�˵���
	if (pWindow->hToolBar)
	{
		RECT rcTool;
		XEle_GetClientRect(pWindow->hToolBar, &rcTool);
		ToolBarHeight = rcTool.bottom - rcTool.top;

		rcTool.left = XWnd_GetClientLeft(hWindow);
		rcTool.right = rClient.right + XWnd_GetClientLeft(hWindow);

		rcTool.top = XWnd_GetCaptionHeight(hWindow) + MenuBarHeight;
		rcTool.bottom = rcTool.top + ToolBarHeight;

		XEle_SetRect(pWindow->hToolBar, &rcTool);
	}
	//״̬��
}

/// @brief ��ȡ���ھ��HWND.
/// @param hWindow ���ھ��.
/// @return ����HWND���.
HWND WINAPI XWnd_GetHWnd(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->hWnd;
}

HELE Wnd_GetChildEle(HELE hEle, int eleID)
{
	IsEleDebug(hEle, __FUNCTION__);

	ele_ *pEle = (ele_*)hEle;
	int count = Array_GetCount(pEle->hArrayEle);
	ele_  *pElement = NULL;
	for (int i = 0; i < count; i++)
	{
		pElement = Array_GetAtEle(pEle->hArrayEle, i);
		if (eleID == pElement->id)
			return (HELE)pElement;

		pElement = (ele_*)Wnd_GetChildEle((HELE)pElement, eleID);
		if (pElement)
			return (HELE)pElement;
	}
	return NULL;
}

/// @brief ͨ��ID��ȡ��Ԫ�ؾ��.
/// @param hWindow ���ھ��.
/// @param eleID   ��Ԫ��ID.
/// @return DI�Ŷ�Ӧ��Ԫ�ؾ��.
HELE WINAPI XWnd_GetEle(HWINDOW hWindow, int eleID) //ͨ��ID��ȡԪ�ؾ��
{
	IsWindowDebug(hWindow, __FUNCTION__);

	window_ *pWindow = (window_*)hWindow;
	ele_ *pEle = NULL;

	//�ͻ���
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		pEle = Array_GetAtEle(pWindow->hArrayEle, i);
		if (eleID == pEle->id)
		{
			return (HELE)pEle;
		}
		pEle = (ele_*)Wnd_GetChildEle((HELE)pEle, eleID);
		if (pEle)
			return (HELE)pEle;
	}

	//�ǿͻ���
	count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
		if (eleID == pEle->id)
		{
			return (HELE)pEle;
		}
		pEle = (ele_*)Wnd_GetChildEle((HELE)pEle, eleID);
		if (pEle)
			return (HELE)pEle;
	}

	return NULL;
}

/// @brief ��ȡ���ڱ������ı�.
/// @param hWindow ���ھ��.
/// @param pOut   �����ı����ݵĻ�����.
/// @param len    ����������.
/// @return ��������ɹ�������ֵ�Ǹ��Ƶ��ַ������ȣ�����������ֹ�ַ�,�������û�б������ı����򴰿ڻ�����Ч������ֵΪ��.
int WINAPI XWnd_GetWindowText(HWINDOW hWindow, wchar_t *pOut, int len)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return GetWindowText(((window_*)hWindow)->hWnd, pOut, len);
}

/// @brief ���ô��ڱ������ı�.
/// @param hWindow ���ھ��.
/// @param pText   �ı�����.
/// @return   �ɹ�����TRUE,�����෴.
BOOL WINAPI XWnd_SetWindowText(HWINDOW hWindow, wchar_t *pText)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (SetWindowText(((window_*)hWindow)->hWnd, pText))
		return TRUE;
	return FALSE;
}

///@}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

//pRect: �ǿͻ�������
void  Wnd_DrawWindowHandle(HWINDOW hWindow, RECT *pRect)
{
	if (FALSE == IsWindowVisible(((window_*)hWindow)->hWnd))
		return;

	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	Wnd_DrawWindow_Optimization(hWindow, pRect); //�Ż�����
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);

	return;
}

void Wnd_DrawWindow_Optimization(HWINDOW hWindow, RECT *pRect)
{
	window_ *pWindow = (window_*)hWindow;
	//��ǰΪ��
	if (FALSE == pWindow->drawWindow.bValid)
	{
		pWindow->drawWindow.rect = *pRect;
		pWindow->drawWindow.bValid = TRUE;
		pWindow->drawWindow.hEle = NULL;
		//XTRACE("Wnd_DrawWindow_Optimization() ��ǰΪ�� ... \n");
		return;
	}

	//��ǰΪ�ػ�Ԫ��
	if (pWindow->drawWindow.hEle)
	{
		RECT rect;
		XEle_GetNCWndRect(pWindow->drawWindow.hEle, &rect);

		RECT rcDest;
		XC_CombineRect(&rcDest, &rect, pRect);
		pWindow->drawWindow.rect = rcDest;
		pWindow->drawWindow.hEle = NULL;
		//XTRACE("Wnd_DrawWindow_Optimization() ��ǰΪ�ػ�Ԫ�� ... \n");
		return;
	}

	//��ǰΪ�ػ洰��
	{
		RECT rcDest;
		XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
		pWindow->drawWindow.rect = rcDest;
		//XTRACE("Wnd_DrawWindow_Optimization() ��ǰΪ�ػ洰�� ... \n");
	}
}

void Wnd_DrawWindowHandle2(HWINDOW hWindow, windowMsg_Header_ *pHeader, RECT *pRect, HDC hdc)
{
	window_ *pWindow = (window_*)hWindow;

	pWindow->rcDraw = *pRect;  //��¼��ǰ��Ҫ���Ƶ�����

	int cx = pRect->right - pRect->left;
	int cy = pRect->bottom - pRect->top;

	HBITMAP hWndBitmap = XDraw_CreateDIBSection(NULL, cx, cy);

	pWindow->hBkDC = CreateCompatibleDC(NULL);  //��������DC ���� (�����ǿͻ���)
	SelectObject(pWindow->hBkDC, hWndBitmap);
	SetBkMode(pWindow->hBkDC, TRANSPARENT);

	HGDIOBJ hOldFont = NULL;
	if (pWindow->hFontX)
		hOldFont = SelectObject(pWindow->hBkDC, XFont_GetHFONT(pWindow->hFontX));
	else
		hOldFont = SelectObject(pWindow->hBkDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));

	HDRAW hDraw = XDraw_Create_(pWindow->hBkDC);
	XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top));

	if (FALSE == (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED))
	{
		XDraw_FillSolidRect_(hDraw, pRect, pWindow->bkColor);
	}

	//////////////////////////////////////////////////////////////////////////
	//�ǿͻ�����ͼ
	Wnd_DrawWindow_NCClient(hWindow, hDraw);

	//�ͻ���///////////////////////////////////////////////////
	Wnd_DrawWindow_Client(hWindow, hDraw, pHeader);  //���ƿͻ���

	//////////////////////////////////////////////////////////////////
	//���ڻ�����ɺ����,������Ч�ϳ�
	XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top)); //���ڷǿͻ���
	Wnd_NCWindowProc(hWindow, XWM_NCENDPAINT, (WPARAM)hDraw, 0);

	//////////////////////////////////////////////////////////////////////////
	//�����//////////////////////////////////////////////////////////////////
	if (pWindow->hCaretEle && pWindow->bCaretShow)
	{
		Wnd_DrawWindow_Caret(hWindow, hDraw);
	}

	XDraw_Destroy_(hDraw);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //͸������
	{
		Wnd_DrawWindow_Shadow(hWindow, hdc);
	}
	else
	{
		BitBlt(hdc, pRect->left, pRect->top, cx, cy, pWindow->hBkDC, 0, 0, SRCCOPY);
	}

	////////////////////////////////////////////////////////////////////////
	pWindow->rcDraw.left = 0;
	pWindow->rcDraw.top = 0;
	pWindow->rcDraw.right = 0;
	pWindow->rcDraw.bottom = 0;
	SelectObject(pWindow->hBkDC, hOldFont);
	DeleteDC(pWindow->hBkDC);
	pWindow->hBkDC = NULL;
	DeleteObject(hWndBitmap);

}

void Wnd_DrawWindow_NCClient(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;
	//�ǿͻ�����ͼ
	if (pWindow->hImageNC)
	{
		RECT rcWindow;
		XWnd_GetNCClientRect(hWindow, &rcWindow);

		XDraw_HImageSuper_(hDraw, pWindow->hImageNC, &rcWindow);
	}

	//���ƴ��ڷǿͻ���
	Wnd_NCWindowProc(hWindow, XWM_NCPAINT, (WPARAM)hDraw, 0);

	//���Ʒǿͻ���Ԫ��
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
		if (pEle->bShow)
		{
			if (XC_RectInRect(&pWindow->rcDraw, &pEle->rect))
			{
				Ele_SendEleMsg((HELE)pEle, XM_PAINT, (WPARAM)hDraw, 0);
			}
		}
	}
}

void Wnd_DrawWindow_Client(HWINDOW hWindow, HDRAW hDraw, windowMsg_Header_ *pHeader)  //���ƿͻ���
{
	window_ *pWindow = (window_*)hWindow;
	//�ͻ���///////////////////////////////////////////////////
	//ӳ�䵽�ͻ���
	XDraw_SetOffset_(hDraw, -(pWindow->rcDraw.left) + pWindow->borderLeft, -(pWindow->rcDraw.top) + XWnd_GetClientTop(hWindow));

	RECT rcClip; //������
	XWnd_GetClientRect(hWindow, &rcClip);
	HRGN hRngClip = CreateRectRgn(0, 0, rcClip.right + XWnd_GetClientLeft(hWindow), rcClip.bottom + XWnd_GetClientTop(hWindow));
	SelectClipRgn(pWindow->hBkDC, hRngClip);

	//���ƴ��ڿͻ���
	windowMsg_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)hDraw;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_hdraw))
				break;
		}
		else
		{
			if (((pFunWndDrawWindow)pFunT->pFun)(hWindow, hDraw))
				break;
		}

		if (!XC_IsHWINDOW(hWindow))
		{
			MsgError(XC_ERROR_0008);
		}

		XDraw_RestoreGDIOBJ_(hDraw);
		pFunT = pFunT->pNext;
	}

	SelectClipRgn(pWindow->hBkDC, NULL);
	DeleteObject(hRngClip);

	//��Ҫ���ƵĿͻ�������
	RECT rcDrawClient = pWindow->rcDraw;
	XWnd_WindowToClientRect(hWindow, &rcDrawClient);

	//����Ԫ���б�  ������Ԫ��
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
		if (pEle->bShow)
		{
			if (XC_RectInRect(&rcDrawClient, &pEle->rect))
			{
				Ele_SendEleMsg((HELE)pEle, XM_PAINT, (WPARAM)hDraw, 0);
			}
		}
	}
}

void Wnd_DrawWindow_Shadow(HWINDOW hWindow, HDC hdc) //������Ӱ
{
	window_ *pWindow = (window_*)hWindow;

	int cx = pWindow->rcDraw.right - pWindow->rcDraw.left;
	int cy = pWindow->rcDraw.bottom - pWindow->rcDraw.top;

	RECT rcWindow;
	GetClientRect(pWindow->hWnd, &rcWindow);

	RECT rcSysNCClient;
	GetWindowRect(pWindow->hWnd, &rcSysNCClient);
	rcSysNCClient.right = rcSysNCClient.right - rcSysNCClient.left;
	rcSysNCClient.bottom = rcSysNCClient.bottom - rcSysNCClient.top;
	rcSysNCClient.top = 0;
	rcSysNCClient.left = 0;

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
		Draw_SetTransparent(pWindow->hBkDC, 255);

	int borderWidth = 0; //GetSystemMetrics(SM_CXDRAG); //SM_CXBORDER 
	//��Ӱ����
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
		borderWidth = XC_WIND_SHADOW_SIZE;

	//�����ػ���������
	HDC memDC = NULL;
	if (NULL == pWindow->hBtimap || pWindow->sizeWnd.cx != rcSysNCClient.right || pWindow->sizeWnd.cy != rcSysNCClient.bottom)
	{
		if (pWindow->hBtimap)
			DeleteObject(pWindow->hBtimap);

		pWindow->hBtimap = XDraw_CreateDIBSection(NULL, rcSysNCClient.right, rcSysNCClient.bottom);

		pWindow->sizeWnd.cx = rcSysNCClient.right;
		pWindow->sizeWnd.cy = rcSysNCClient.bottom;
	}
	memDC = CreateCompatibleDC(NULL);         //��������DC ���� (�����ǿͻ���)
	SelectObject(memDC, pWindow->hBtimap);

	BitBlt(memDC, pWindow->rcDraw.left + borderWidth, pWindow->rcDraw.top + borderWidth, cx, cy, pWindow->hBkDC, 0, 0, SRCCOPY);

	//������Ӱ
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
	{
		RECT rcShadow = { borderWidth,borderWidth,rcSysNCClient.right - borderWidth,rcSysNCClient.bottom - borderWidth };
		Draw_DrawWndShadow(memDC, &rcShadow);
	}

	BLENDFUNCTION m_blend;
	m_blend.BlendOp = 0;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = 1;
	m_blend.SourceConstantAlpha = pWindow->transparentAlpha;

	RECT rcWnd;
	GetWindowRect(pWindow->hWnd, &rcWnd);
	POINT ptDst = { rcWnd.left, rcWnd.top };
	POINT ptSrc = { 0, 0 };
	SIZE m_sizeWnd = { rcSysNCClient.right,rcSysNCClient.bottom };
	//int res=
	UpdateLayeredWindow(pWindow->hWnd, hdc, &ptDst, &m_sizeWnd, memDC, &ptSrc, 0, &m_blend, ULW_ALPHA);
	//	if(0==res)
	//	{
	//		DWORD err= GetLastError();
	//		XTRACE("DrawWindowHandle() err=%d \n",err);
	//	}else
	//		XTRACE("DrawWindowHandle() \n");

	DeleteDC(memDC);
}

void Wnd_DrawWindow_Caret(HWINDOW hWindow, HDRAW hDraw) //��������
{
	window_ *pWindow = (window_*)hWindow;

	POINT ptOld;
	SetViewportOrgEx(pWindow->hBkDC, -(pWindow->rcDraw.left), -(pWindow->rcDraw.top), &ptOld);

	POINT  ptCaret = pWindow->caretPt;
	XEle_PointToNCWnd(pWindow->hCaretEle, &ptCaret);

	//���ݲ��������
	HDC hdcCaret = CreateCompatibleDC(NULL);
	SelectObject(hdcCaret, pWindow->hCaretBitmap);
	BitBlt(hdcCaret, 0, 0, pWindow->caretWidth, pWindow->caretHeight, pWindow->hBkDC, ptCaret.x, ptCaret.y, SRCCOPY);
	DeleteDC(hdcCaret);

	SetViewportOrgEx(pWindow->hBkDC, ptOld.x, ptOld.y, 0);

	//����ڻ��Ʒ�Χ��
	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);
	if (PtInRect(&pWindow->rcDraw, pt))
	{
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW) //͸������
		{
			Wnd_DrawCaretTransparentMemDC(hWindow, hDraw); //���Ʋ����
		}
		else
		{
			Wnd_DrawCaretMenDC(hWindow, hDraw);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

HDC Wnd_GetBkDC(HWINDOW hWindow)
{
	return ((window_*)hWindow)->hBkDC;
}

void Wnd_AdjustCaption(HWINDOW hWindow, int cx)
{
	window_ *pWindow = (window_*)hWindow;
	int right = cx - 8;
	if (pWindow->hClose)
	{
		RECT rect;
		XEle_GetRect(pWindow->hClose, &rect);
		int cx = rect.right - rect.left;
		rect.right = right;
		rect.left = rect.right - cx;
		XEle_SetRect(pWindow->hClose, &rect);
		right -= cx; //right++;
	}
	if (pWindow->hMaxinize)
	{
		RECT rect;
		XEle_GetRect(pWindow->hMaxinize, &rect);
		int cx = rect.right - rect.left;
		rect.right = right;
		rect.left = rect.right - cx;
		XEle_SetRect(pWindow->hMaxinize, &rect);
		right -= cx; //right++;
	}
	if (pWindow->hMinimize) //��С����ť
	{
		RECT rect;
		XEle_GetRect(pWindow->hMinimize, &rect);
		int cx = rect.right - rect.left;
		rect.right = right;
		rect.left = rect.right - cx;
		XEle_SetRect(pWindow->hMinimize, &rect);
	}
}

/////////////////////////////////////////////////////////////
BOOL Wnd_ConvPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	if (IsWindow(((window_*)hWindow)->hWnd))
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(((window_*)hWindow)->hWnd, &ps);

		Wnd_DrawWindowHandle(hWindow, &ps.rcPaint);

		EndPaint(((window_*)hWindow)->hWnd, &ps);
	}
	return TRUE;
}
BOOL Wnd_ConvClose(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndClose)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_CLOSE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}
BOOL Wnd_ConvDestroy(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndDestroy)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_DESTROY]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvNCDestroy(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	Resource_RemoveWindow(hWindow);

	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCDestroy)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_NCDESTROY]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvMouseMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);

	window_ *pWindow = (window_*)hWindow;

	//ӵ����겶��Ȩ��Ԫ��
	if (pWindow->pCapture)
	{
		//������ת����Ԫ�ؿͻ��� ����
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_MOUSEMOVE, wParam, (LPARAM)&InPt);
		//XTRACE("�����в��� x=%d \n",InPt.x);
		return TRUE;
	}

	if (!pWindow->bTrackLeave) //��������뿪
	{
		//bTrackLeave=TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = pWindow->hWnd;
		tme.dwFlags = TME_LEAVE;
		pWindow->bTrackLeave = TrackMouseEvent(&tme);
	}

	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);

	POINT pt = { xPos,yPos };
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = wParam;
				event_.lParam = (LPARAM)&pt;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndMouseMove)pFunT->pFun)(hWindow, wParam, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_MOUSEMOVE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCMOUSEMOVE, wParam, (LPARAM)&pt);
	}
	return TRUE;
}
BOOL Wnd_ConvLButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	window_ *pWindow = (window_*)hWindow;

	//��鴰���Ƿ��н���
	if (pWindow->hWnd != GetFocus())
		SetFocus(pWindow->hWnd);

	////////////////////////////////////////////////////
	//�����������Ԫ�� hArrayPGrids
	if (pWindow->hArrayPGrids)
	{
		int countPGrid = XArray_GetCount(pWindow->hArrayPGrids);
		for (int i = 0; i < countPGrid; i++)
		{
			HELE hPGrid = (HELE)XArray_GetAt(pWindow->hArrayPGrids, i);  //
			if (XEle_IsShowEle(hPGrid))
			{
				int id = XPGrid_GetSelectItem(hPGrid);
				if (id >= 0)
				{
					PGridItem_ *pItem = PGrid_GetItem(hPGrid, id);
					if (pItem->hEle)
					{
						RECT rect;
						XEle_GetClientRect(pItem->hEle, &rect);
						XEle_RectToNCWnd(pItem->hEle, &rect);
						//	if(FALSE==PtInRect(&rect,pt))
						//	{
						PGrid_CheckValueChange(hPGrid, pItem);
						//	XTRACE("ok... \n");
						//	}else
						//	{
						//	XTRACE("no... \n");
						//	}
					}
					//	break;
				}
			}
		}
	}

	//ӵ����겶��Ȩ��Ԫ��
	if (pWindow->pCapture)
	{
		//������ת����Ԫ�ؿͻ��� ����
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_LBUTTONDOWN, wParam, (LPARAM)&InPt);
		return TRUE;
	}

	if (FALSE == pWindow->bClickTimer) //����һ�ΰ���
	{
		pWindow->bClickTimer = TRUE;
		pWindow->mouseDown.x = pt.x;
		pWindow->mouseDown.y = pt.y;
		pWindow->bMouseDown2 = FALSE;
		XWnd_SetTimer(hWindow, IDT_CLICK, 300);
	}
	else if ((TRUE == pWindow->bClickTimer) && (FALSE == pWindow->bMouseDown2)) //���ڶ��ΰ���
	{
		pWindow->bMouseDown2 = TRUE;
		pWindow->mouseDown2.x = pt.x;
		pWindow->mouseDown2.y = pt.y;
		//--------------
		pWindow->bClickTimer = FALSE;
		pWindow->bMouseUp = FALSE;
		KillTimer(pWindow->hWnd, IDT_CLICK);

		RECT rcDB = { pWindow->mouseDown.x - 2,pWindow->mouseDown.y - 2,pWindow->mouseDown.x + 2,pWindow->mouseDown.y + 2 };
		if (PtInRect(&rcDB, pt))
		{
			PostMessage(pWindow->hWnd, XWM_MOUSEDBCLICK, xPos, yPos);
			//DBClick=TRUE;
			//XTRACE("˫��\n");
		}
		//return TRUE;
	}

	////////////////////////////////////////////////////
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);

	//POINT pt={xPos,yPos};
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = wParam;
				event_.lParam = (LPARAM)&pt;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndLButtonDown)pFunT->pFun)(hWindow, wParam, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_LBUTTONDOWN]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCLBUTTONDOWN, wParam, (LPARAM)&pt);
	}

	return TRUE;
}

BOOL Wnd_ConvLButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);

	window_ *pWindow = (window_*)hWindow;

	//ӵ����겶��Ȩ��Ԫ��
	if (pWindow->pCapture)
	{
		//������ת����Ԫ�ؿͻ��� ����
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_LBUTTONUP, wParam, (LPARAM)&InPt);
		return TRUE;
	}

	if (pWindow->bClickTimer && (FALSE == pWindow->bMouseUp)) //���������˫��
	{
		pWindow->bMouseUp = TRUE;
		pWindow->mouseUp.x = xPos;
		pWindow->mouseUp.y = yPos;
	}

	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);

	POINT pt = { xPos,yPos };
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = wParam;
				event_.lParam = (LPARAM)&pt;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndLButtonUp)pFunT->pFun)(hWindow, wParam, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_LBUTTONUP]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else  //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCLBUTTONUP, wParam, (LPARAM)&pt);
	}
	return TRUE;
}

BOOL Wnd_ConvRButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);

	window_ *pWindow = (window_*)hWindow;
	//ӵ����겶��Ȩ��Ԫ��
	if (pWindow->pCapture)
	{
		//������ת����Ԫ�ؿͻ��� ����
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_RBUTTONDOWN, wParam, (LPARAM)&InPt);
		return TRUE;
	}

	////////////////
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);

	POINT pt = { xPos,yPos };
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = wParam;
				event_.lParam = (LPARAM)&pt;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndRButtonDown)pFunT->pFun)(hWindow, wParam, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_RBUTTONDOWN]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCRBUTTONDOWN, wParam, (LPARAM)&pt);
	}

	return TRUE;
}
BOOL Wnd_ConvRButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);

	window_ *pWindow = (window_*)hWindow;
	//ӵ����겶��Ȩ��Ԫ��
	if (pWindow->pCapture)
	{
		//������ת����Ԫ�ؿͻ��� ����
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_RBUTTONUP, wParam, (LPARAM)&InPt);
		return TRUE;
	}

	////////////////////////
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);

	POINT pt = { xPos,yPos };
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = wParam;
				event_.lParam = (LPARAM)&pt;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndRButtonUp)pFunT->pFun)(hWindow, wParam, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_RBUTTONUP]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCRBUTTONUP, wParam, (LPARAM)&pt);
	}
	return TRUE;
}
BOOL Wnd_ConvExitSizeMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndExitSizeMove)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_EXITSIZEMOVE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvMouseLeave(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndMouseLeave)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_MOUSELEAVE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvSize(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	//int xPos = GET_X_LPARAM(lParam); 
	//int yPos = GET_Y_LPARAM(lParam);

	while (pFunT)
	{
		SIZE size = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = (LPARAM)&size;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_size))
				return TRUE;
		}
		else
		{
			if (((pFunWndSize)pFunT->pFun)(hWindow, wParam, &size))
			{
				return TRUE;
			}
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_SIZE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}

BOOL Wnd_ConvTimer(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //��ʱ��
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_i))
				return TRUE;
		}
		else
		{
			if (((pFunWndTimer)pFunT->pFun)(hWindow, wParam, lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_TIMER]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}

BOOL Wnd_ConvTimer2(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //��ʱ��
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		HELE  hEleTimer = NULL;
		HWINDOW hWindowTimer = NULL;

		if (NULL == g_hArray_Timer)
			return TRUE;

		EnterCriticalSection(&g_timer_CriticalSection);
		int count = XArray_GetCount(g_hArray_Timer);
		for (int i = 0; i < count; i++)
		{
			xc_timer_ *p = (xc_timer_*)XArray_GetAt(g_hArray_Timer, i);
			if (wParam == p->timerID)
			{
				hEleTimer = p->hEle;
				hWindowTimer = p->hWindow;
				break;
			}
		}
		LeaveCriticalSection(&g_timer_CriticalSection);

		if (hWindowTimer != hWindow)
			return TRUE;

		if (hEleTimer)
		{
			if (Ele_SendEleMsg(hEleTimer, XM_TIMER, wParam, 0))
				return TRUE;
		}
		else
		{
			//////////////////////////////////////
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = wParam;
				event_.lParam = lParam;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_i))
					return TRUE;
			}
			else
			{
				if (((pFunWndTimerEx)pFunT->pFun)(hWindow, wParam, lParam))
					return TRUE;
			}
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_TIMER]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}

BOOL Wnd_ConvMouseClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	window_ *pWindow = (window_*)hWindow;
	POINT pt = { wParam,lParam };
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)&pt;
				event_.lParam = NULL;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndMouseClick)pFunT->pFun)(hWindow, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_MOUSECLICK]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else  //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCMOUSECLICK, (WPARAM)&pt, 0);
	}
	return TRUE;
}
BOOL Wnd_ConvMouseDBClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	window_ *pWindow = (window_*)hWindow;
	POINT pt = { wParam,lParam };
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	rect.left += XWnd_GetClientLeft(hWindow);
	rect.right += XWnd_GetClientLeft(hWindow);
	rect.top += XWnd_GetClientTop(hWindow);
	rect.bottom += XWnd_GetClientTop(hWindow);
	if (PtInRect(&rect, pt)) //�ͻ���
	{
		XWnd_WindowToClientPt(hWindow, &pt);
		windowMsg_  *pFunT = pHeader->pList;
		while (pFunT)
		{
			if (pFunT->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hWindow = hWindow;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)&pt;
				event_.lParam = NULL;
				event_.pClass_fun = pFunT->pClass_Fun_Info;
				if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_pt))
					return TRUE;
			}
			else
			{
				if (((pFunWndMouseDBClick)pFunT->pFun)(hWindow, &pt))
					return TRUE;
			}

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_MOUSEDBCLICK]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else  //�ǿͻ���
	{
		Wnd_NCWindowProc(hWindow, XWM_NCMOUSEDBCLICK, (WPARAM)&pt, 0);
	}
	return TRUE;
}
BOOL Wnd_ConvRedrawEle(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_e))
				return TRUE;
		}
		else
		{
			if (((pFunWndRedrawEle)pFunT->pFun)(hWindow, (HELE)wParam, (RECT*)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_REDRAW_ELE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvSetFocus(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndSetFocus)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_SETFOCUS]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvKillFocus(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndKillFocus)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_KILLFOCUS]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvCaptureChanged(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = lParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_hwnd))
				return TRUE;
		}
		else
		{
			if (((pFunWndCaptureChanged)pFunT->pFun)(hWindow, (HWND)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_CAPTURECHANGED]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvMouseWheel(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	ScreenToClient(((window_*)hWindow)->hWnd, &pt);
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = lParam;
			event_.lParam = (LPARAM)&pt;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndMouseWheel)pFunT->pFun)(hWindow, wParam, &pt))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[WM_MOUSEWHEEL]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvMenuSelect(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i))
				return TRUE;
		}
		else
		{
			if (((pFunWndMenuSelect)pFunT->pFun)(hWindow, wParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_MENUSELECT]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvMenuExit(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndMenuExit)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_MENUEXIT]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}
BOOL Wnd_ConvSetFont(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w))
				return TRUE;
		}
		else
		{
			if (((pFunWndSetFont)pFunT->pFun)(hWindow))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_SETFONT]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}

BOOL Wnd_ConvOther(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_i))
				return TRUE;
		}
		else
		{
			if (((pFunWndOther)pFunT->pFun)(hWindow, wParam, lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[%d]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n", pHeader->message);
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////
BOOL Wnd_ConvNCPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_hdraw))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCDrawWindow)pFunT->pFun)(hWindow, (HDRAW)wParam))
				return TRUE;
		}

		XDraw_RestoreGDIOBJ_((HDRAW)wParam);

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCPAINT]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCEndPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_hdraw))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCEndDrawWindow)pFunT->pFun)(hWindow, (HDRAW)wParam))
				return TRUE;
		}

		XDraw_RestoreGDIOBJ_((HDRAW)wParam);
		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCENDPAINT]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCMouseMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCMouseMove)pFunT->pFun)(hWindow, wParam, (POINT*)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCMOUSEMOVE]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}
BOOL Wnd_ConvNCLButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCLButtonDown)pFunT->pFun)(hWindow, wParam, (POINT*)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCLBUTTONDOWN]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCLButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCLButtonUp)pFunT->pFun)(hWindow, wParam, (POINT*)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCLBUTTONUP]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCRButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCRButtonDown)pFunT->pFun)(hWindow, wParam, (POINT*)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCRBUTTONDOWN]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCRButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_i_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCRButtonUp)pFunT->pFun)(hWindow, wParam, (POINT*)lParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCRBUTTONUP]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCMouseClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCMouseClick)pFunT->pFun)(hWindow, (POINT*)wParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCMOUSECLICK]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Wnd_ConvNCMouseDBClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	windowMsg_  *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hWindow = hWindow;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_w_pt))
				return TRUE;
		}
		else
		{
			if (((pFunWndNCMouseDBClick)pFunT->pFun)(hWindow, (POINT*)wParam))
				return TRUE;
		}

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

#ifdef _DEBUG  //������
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XWM_NCMOUSEDBCLICK]��Ϣ�������з�������,�򴰿�[HWINDOW]���ʧЧ,����������˸þ��,Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////
void Wnd_RedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect) //�ػ�Ԫ��ָ������
{
	window_ *pWindow = (window_*)hWindow;
	ele_ *pEle = (ele_*)hEle;

	ele_ *pEleShow = pEle;
	while (pEleShow) //��鸸�����Ƿ���ʾ
	{
		if (pEleShow->bShow)
			pEleShow = pEleShow->pParentEle;
		else
			return;
	}

	RECT rect = *pRect; //Ҫ�ػ������

	//��ֹ��������Χ
	RECT rcEleSelf;
	XEle_GetNCWndRect(hEle, &rcEleSelf);
	if (rect.left < rcEleSelf.left)	   rect.left = rcEleSelf.left;
	if (rect.top < rcEleSelf.top)	       rect.top = rcEleSelf.top;
	if (rect.right > rcEleSelf.right)	   rect.right = rcEleSelf.right;
	if (rect.bottom > rcEleSelf.bottom)   rect.bottom = rcEleSelf.bottom;

	int windowLeft = XWnd_GetClientLeft(hWindow);
	int windowTop = XWnd_GetClientTop(hWindow);

	//��ֹ�����ͻ���
	if (pEle->bClient)
	{
		RECT rcClient; //�ͻ�����Χ
		XWnd_GetClientRect(hWindow, &rcClient);
		rcClient.left = windowLeft;
		rcClient.top = windowTop;
		rcClient.right += windowLeft;
		rcClient.bottom += windowTop;
		if (rect.left < rcClient.left) rect.left = rcClient.left;
		if (rect.top < rcClient.top) rect.top = rcClient.top;
		if (rect.right > rcClient.right) rect.right = rcClient.right;
		if (rect.bottom > rcClient.bottom) rect.bottom = rcClient.bottom;
	}

	ele_ *pPar = pEle->pParentEle; //��Ԫ��ָ��
	RECT  rect2;
	while (pPar) //��ֹ������Ԫ�ػ��Ʒ�Χ
	{
		XEle_GetNCWndRect((HELE)pPar, &rect2); //��Ԫ�ػ��ڴ��ڿͻ�������

		if (rect.left < rect2.left) rect.left = rect2.left;
		if (rect.top < rect2.top) rect.top = rect2.top;
		if (rect.right > rect2.right) rect.right = rect2.right;
		if (rect.bottom > rect2.bottom) rect.bottom = rect2.bottom;

		pPar = pPar->pParentEle;
	}

	/////////////////////���Ԫ���Ƿ��ص�///////////////////////////////////////
	if (Wnd_ReDrawEle_Overlapping(hWindow, hEle, &rect))
		return;

	if (rect.right > rect.left && rect.bottom > rect.top)
	{
		Wnd_PaintEle(hWindow, (HELE)pEle, &rect);
	}
}

BOOL Wnd_ReDrawEle_Overlapping(HWINDOW hWindow, HELE hEle, RECT *pRect) //���Ԫ���ص�
{
	ele_ *pEle = (ele_*)hEle;
	ele_ *pEleCur = pEle;
	HELE hChild = NULL;
	RECT rcEle;
	HARRAY  hArrayEle;

	while (pEleCur->pParentEle)
	{
		hArrayEle = pEleCur->pParentEle->hArrayEle;

		int count = XArray_GetCount(hArrayEle);
		for (int i = 0; i < count; i++)
		{
			hChild = (HELE)XArray_GetAt(hArrayEle, i);
			if (hChild == (HELE)pEleCur)
			{
				for (int j = i + 1; j < count; j++)
				{
					hChild = (HELE)XArray_GetAt(hArrayEle, j);
					XEle_GetNCWndRect(hChild, &rcEle);

					if (XC_RectInRect(pRect, &rcEle)) //�ص�
					{
						XWnd_RedrawEleRectNC(hWindow, (HELE)pEleCur->pParentEle, pRect);
						return TRUE;
					}
				}
				break;
			}
		}
		pEleCur = pEleCur->pParentEle;
	}

	//����Ԫ��
	if (pEle->pWindow)
	{
		//pEleCur=pEle;
		hArrayEle = pEle->pWindow->hArrayEle;

		int count = XArray_GetCount(hArrayEle);
		for (int i = 0; i < count; i++)
		{
			hChild = (HELE)XArray_GetAt(hArrayEle, i);
			if (hChild == (HELE)pEleCur)
			{
				for (int j = i + 1; j < count; j++)
				{
					hChild = (HELE)XArray_GetAt(hArrayEle, j);
					XEle_GetNCWndRect(hChild, &rcEle);

					if (XC_RectInRect(pRect, &rcEle)) //�ص�
					{
						XWnd_RedrawWndRect(hWindow, pRect, true);
						return TRUE;
					}
				}
				break;
			}
		}
	}

	return FALSE;
}

BOOL CALLBACK Wnd_OnRedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect)
{
	window_ *pWindow = (window_*)hWindow;
	IsEleDebug(hEle, "Ԫ���ػ����(00356783465456)");

	if (pRect)
	{
		Wnd_RedrawEle(hWindow, hEle, pRect);
	}
	else
	{
		RECT rect; //Ҫ�ػ������
		XEle_GetNCWndRect(hEle, &rect); //���ڴ�������(�����ǿͻ���)
		Wnd_RedrawEle(hWindow, hEle, &rect);
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnSetFocus(HWINDOW hWindow)  //���ڻ�ý���
{
	//	OutputDebugStringA("���� ��ý���\n");
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->pOldFocus)  //�ָ�Ԫ�ؽ���
	{
		pWindow->pFocus = pWindow->pOldFocus;
		pWindow->pOldFocus = NULL;
		Ele_SendEvent((HELE)pWindow->pFocus, XE_SETFOCUS, 0, 0);
	}
	//XWnd_RedrawWnd(hWindow,TRUE);
	return TRUE;
}

BOOL CALLBACK Wnd_OnKillFocus(HWINDOW hWindow) //����ʧȥ����
{
	//	OutputDebugStringA("���� ʧȥ����\n");

	window_ *pWindow = (window_*)hWindow;

	if (pWindow->pCapture)
	{
		HELE hEleSend = pWindow->pCapture;
		pWindow->pCapture = NULL;
		Ele_SendEvent(hEleSend, XE_KILLCAPTURE, 0, 0);
	}

	if (pWindow->pMouseTop)
	{
		HELE hEleSend = (HELE)pWindow->pMouseTop;
		pWindow->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}
	if (pWindow->pFocus)
	{
		pWindow->pOldFocus = pWindow->pFocus;

		HELE hOld = (HELE)pWindow->pFocus;
		pWindow->pFocus = NULL;
		Ele_SendEvent(hOld, XE_KILLFOCUS, 0, 0);
	}
	//XWnd_RedrawWnd(hWindow,TRUE);
	return TRUE;
}

BOOL CALLBACK Wnd_OnCaptureChanged(HWINDOW hWindow, HWND hWnd)
{
	if (NULL == hWnd)
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->pCapture)
		{
			HELE hEleSend = pWindow->pCapture;
			pWindow->pCapture = NULL;
			Ele_SendEvent(hEleSend, XE_KILLCAPTURE, 0, 0);
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnMouseWheel(HWINDOW hWindow, UINT flags, POINT *pPt) //WM_MOUSEWHEEL ������Ϣ
{
	if (((window_*)hWindow)->pFocus)
	{
		//������ת����Ԫ�ؿͻ��� ����
		POINT InPt = *pPt;
		XEle_PointNCWndToEle((HELE)((window_*)hWindow)->pFocus, &InPt);

		Ele_SendEvent((HELE)((window_*)hWindow)->pFocus, XE_MOUSEWHEEL, (WPARAM)flags, MAKELPARAM(InPt.x, InPt.y));
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnTimerEx(HWINDOW hWindow, UINT timerID, int userData) //��ʱ����Ϣ
{
	return TRUE;
}

BOOL CALLBACK Wnd_OnRedraw(HWINDOW hWindow, WPARAM wParam, LPARAM lParam) //�Զ�����Ϣ,Ϊ���ػ��ӳ�
{
	if (wParam && lParam) //�ػ�ָ������
	{
		RECT rect;
		rect.left = GET_X_LPARAM(wParam);
		rect.top = GET_Y_LPARAM(wParam);
		rect.right = GET_X_LPARAM(lParam);
		rect.bottom = GET_Y_LPARAM(lParam);
		XWnd_RedrawWndRect(hWindow, &rect, TRUE);
	}
	else //�ػ���������
	{
		XWnd_RedrawWnd(hWindow, TRUE);
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnMinMaxInfo(HWINDOW hWindow, WPARAM wParam, LPARAM lParam)
{
	//if(((window_*)hWindow)->bDrag)
	if (((window_*)hWindow)->xcStyle & XC_SY_DRAG_BORDER)
	{
		MINMAXINFO  *pInfo = (MINMAXINFO*)lParam;
		pInfo->ptMinTrackSize.x = ((window_*)hWindow)->minWidth;
		pInfo->ptMinTrackSize.y = ((window_*)hWindow)->minHeight;
	}
	return FALSE;
}

BOOL CALLBACK Wnd_OnKeyDown(HWINDOW hWindow, WPARAM wParam, LPARAM lParam)
{
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle && pWindow->bCaretShow)
	{
		HIMC hImc = ImmGetContext(pWindow->hWnd);
		COMPOSITIONFORM form;
		form.dwStyle = CFS_POINT;
		form.ptCurrentPos.x = pWindow->caretPt.x;
		form.ptCurrentPos.y = pWindow->caretPt.y;
		XEle_PointToNCWnd(pWindow->hCaretEle, &form.ptCurrentPos);
		ImmSetCompositionWindow(hImc, &form);
		ImmReleaseContext(pWindow->hWnd, hImc);
	}
	if (Wnd_KeyDown(hWindow, wParam))
		return TRUE;

	if (pWindow->pFocus)
		Ele_SendEvent((HELE)pWindow->pFocus, XE_KEYDOWN, wParam, lParam);
	return TRUE;
}

BOOL CALLBACK Wnd_OnChar(HWINDOW hWindow, WPARAM wParam, LPARAM lParam)
{
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->pFocus)
	{
		Ele_SendEvent((HELE)pWindow->pFocus, XE_CHAR, wParam, lParam);
	}
	return TRUE;
}

void Wnd_PaintEle(HWINDOW hWindow, HELE hEle, RECT *pRect)
{
	window_ *pWindow = (window_*)hWindow;
	if (FALSE == IsWindowVisible(pWindow->hWnd))
		return;

	//�����Ż� 
	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	Wnd_PaintEle_Optimization(hWindow, hEle, pRect); //�Ż�����
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);

	//XTRACE("�Ż��������� \n");
}

void Wnd_PaintEle2(HWINDOW hWindow, HELE hEle, HDC hdc, RECT *pRect)
{
	window_ *pWindow = (window_*)hWindow;
	////////////////////////////////////////////////////////////

	pWindow->rcDraw = *pRect; //��¼��ǰ��Ҫ���Ƶ�����

	ele_ *pEleTran = Wnd_PaintEle_IsDrawEle(hWindow, hEle);
	if (NULL == pEleTran)
		return;

	////////////////////////////////////////////////////////////
	int cx = pRect->right - pRect->left;
	int cy = pRect->bottom - pRect->top;

	HBITMAP hWndBitmap = XDraw_CreateDIBSection(NULL, cx, cy);

	pWindow->hBkDC = CreateCompatibleDC(NULL);                      //��������DC ����
	SelectObject(pWindow->hBkDC, hWndBitmap);
	SetBkMode(pWindow->hBkDC, TRANSPARENT);
	////////////////////////////////////////////////////////////////
	HDRAW hDraw = XDraw_Create_(pWindow->hBkDC);
	if (FALSE == pEleTran->bClient) //�ǿͻ���
	{
		XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top));//������DCת�������ڿͻ�������ռ�
	}
	else //�ͻ���
	{
		//ӳ�䵽�ͻ���
		XDraw_SetOffset_(hDraw, -(pRect->left) + pWindow->borderLeft, -(pRect->top) + XWnd_GetClientTop(hWindow));
	}

	Ele_SendEleMsg((HELE)pEleTran, XM_PAINT, (WPARAM)hDraw, 0);
	//////////////////////////////////////////////////////////////////
	//���ڻ�����ɺ����,������Ч�ϳ�
	XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top)); //���ڷǿͻ���
	Wnd_NCWindowProc(hWindow, XWM_NCENDPAINT, (WPARAM)hDraw, 0);

	//�����//////////////////////////////////////////////////////////////////
	if (pWindow->hCaretEle && pWindow->bCaretShow)
	{
		Wnd_PaintEle_Caret(hWindow, hDraw);
	}

	XDraw_SetOffset_(hDraw, 0, 0);
	XDraw_Destroy_(hDraw);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //͸������
	{
		Wnd_PaintEle_Shadow(hWindow, hdc);
	}
	else
	{
		BitBlt(hdc, pRect->left, pRect->top, cx, cy, pWindow->hBkDC, 0, 0, SRCCOPY);
	}

	pWindow->rcDraw.left = 0;
	pWindow->rcDraw.top = 0;
	pWindow->rcDraw.right = 0;
	pWindow->rcDraw.bottom = 0;
	DeleteDC(pWindow->hBkDC);
	pWindow->hBkDC = NULL;
	DeleteObject(hWndBitmap);
}

void Wnd_PaintEle_Optimization(HWINDOW hWindow, HELE hEle, RECT *pRect) //�Ż�����
{
	window_ *pWindow = (window_*)hWindow;

	//��ǰΪ��
	if (FALSE == pWindow->drawWindow.bValid)
	{
		//XTRACE("��ǰΪ�� .... \n");
		Wnd_PaintEle_Optimization1(hWindow, hEle, pRect);
		return;
	}

	//ͬһ��Ԫ��
	if (hEle == pWindow->drawWindow.hEle)
	{
		//XTRACE("ͬһ��Ԫ�� .... \n");
		Wnd_PaintEle_Optimization2(hWindow, hEle, pRect);
		return;
	}

	//��ǰΪ�ػ洰��
	if (NULL == pWindow->drawWindow.hEle)
	{
		//XTRACE("��ǰΪ�ػ洰�� .... \n");
		Wnd_PaintEle_Optimization4(hWindow, hEle, pRect);
		return;
	}

	//��ǰΪ�ػ�ָ������
	//XTRACE("��ǰΪ�ػ�ָ������ .... \n");
	Wnd_PaintEle_Optimization3(hWindow, hEle, pRect);
}

void Wnd_PaintEle_Optimization1(HWINDOW hWindow, HELE hEle, RECT *pRect) //��ǰΪ��
{
	window_ *pWindow = (window_*)hWindow;

	pWindow->drawWindow.hEle = hEle;
	pWindow->drawWindow.rect = *pRect;
	pWindow->drawWindow.bValid = TRUE;
	return;
}

void Wnd_PaintEle_Optimization2(HWINDOW hWindow, HELE hEle, RECT *pRect)  //ͬһ��Ԫ��
{
	window_ *pWindow = (window_*)hWindow;

	//�ϲ��ػ�����,�ػ游Ԫ��ָ������
	RECT rcDest;
	XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
	pWindow->drawWindow.rect = rcDest;
}

void Wnd_PaintEle_Optimization3(HWINDOW hWindow, HELE hEle, RECT *pRect) //��ǰΪ�ػ�ָ������
{
	window_ *pWindow = (window_*)hWindow;

	//�ػ�ָ������
	HELE hParentEle1 = XEle_GetParentEle(hEle);
	HELE hParentEle2 = XEle_GetParentEle(pWindow->drawWindow.hEle);

	//�ϲ���������
	RECT rcDest;
	XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
	pWindow->drawWindow.rect = rcDest;

	if (hParentEle1 == hParentEle2) //ͬ��Ԫ��
	{
		//XTRACE("ͬ��Ԫ�� ....\n");
		pWindow->drawWindow.hEle = hParentEle1;

		if (NULL == hParentEle1) //�����Ϊ��,��ôΪ����
		{
			//XTRACE("ͬ��Ԫ�� ��Ϊ�� ....\n");
			pWindow->drawWindow.hEle = NULL;
		}
		return;
	}

	//�����ǰԪ������Ԫ��
	HELE hParentEle = XEle_GetParentEle(hEle);
	while (hParentEle)
	{
		if (hParentEle == pWindow->drawWindow.hEle)
		{
			//XTRACE("��ǰԪ������Ԫ��  ....\n");
			return;
		}
		hParentEle = XEle_GetParentEle(hParentEle);
	}

	//��ǰԪ���Ǹ�Ԫ��
	hParentEle = XEle_GetParentEle(pWindow->drawWindow.hEle);
	while (hParentEle)
	{
		if (hParentEle == hEle)
		{
			pWindow->drawWindow.hEle = hEle;
			//XTRACE("��ǰԪ���Ǹ�Ԫ��  ....\n");
			return;
		}
		hParentEle = XEle_GetParentEle(hParentEle);
	}


	hParentEle = XEle_GetParentEle(hEle);
	while (hParentEle)
	{
		HELE hP = XEle_GetParentEle(pWindow->drawWindow.hEle);
		while (hP)
		{
			if (hParentEle == hP)
			{
				pWindow->drawWindow.hEle = hParentEle;
				//XTRACE("����Ԫ���й�ͬ�ĸ� ΪԪ�� ....\n");
				return;
			}
			hP = XEle_GetParentEle(hP);
		}
		hParentEle = XEle_GetParentEle(hParentEle);
	}

	//XTRACE("����Ԫ���й�ͬ�ĸ� Ϊ���� ....\n");
	pWindow->drawWindow.hEle = NULL;

	//û�и��ӹ�ϵ

}

void Wnd_PaintEle_Optimization4(HWINDOW hWindow, HELE hEle, RECT *pRect) //��ǰΪ�ػ洰��
{
	window_ *pWindow = (window_*)hWindow;

	//�ϲ���������
	RECT rcDest;
	XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
	pWindow->drawWindow.rect = rcDest;
}

ele_* Wnd_PaintEle_IsDrawEle(HWINDOW hWindow, HELE hEle) //����Ƿ�ֱ���ػ�Ԫ��
{
	window_ *pWindow = (window_*)hWindow;

	ele_ *pEleTran = (ele_*)hEle;
	while (pEleTran) //���Ԫ��͸��
	{
		if (pEleTran->bBkTransparent)
		{
			if (pEleTran->pParentEle)
			{
				pEleTran = pEleTran->pParentEle;
			}
			else
			{
				if (pEleTran->bTopLevel)
				{
					XWnd_RedrawWndRect(hWindow, &pWindow->rcDraw, TRUE);
					return NULL;
				}
				break;
			}
		}
		else
		{
			break;
		}
	}
	return pEleTran;
}

void Wnd_PaintEle_Shadow(HWINDOW hWindow, HDC hdc) //������Ӱ
{
	window_ *pWindow = (window_*)hWindow;

	int cx = pWindow->rcDraw.right - pWindow->rcDraw.left;
	int cy = pWindow->rcDraw.bottom - pWindow->rcDraw.top;

	RECT rcWindow;
	GetClientRect(pWindow->hWnd, &rcWindow);

	RECT rcSysNCClient;
	GetWindowRect(pWindow->hWnd, &rcSysNCClient);
	rcSysNCClient.right = rcSysNCClient.right - rcSysNCClient.left;
	rcSysNCClient.bottom = rcSysNCClient.bottom - rcSysNCClient.top;
	rcSysNCClient.left = 0;
	rcSysNCClient.top = 0;

	//�����ػ���������
	HDC memDC = NULL;

	memDC = CreateCompatibleDC(NULL);         //��������DC ���� (�����ǿͻ���)
	SelectObject(memDC, pWindow->hBtimap);

	int borderSize = 0; //�ǿͻ����߿���Ӱ��С
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
		borderSize = XC_WIND_SHADOW_SIZE;

	BitBlt(memDC, borderSize + pWindow->rcDraw.left, borderSize + pWindow->rcDraw.top, cx, cy, pWindow->hBkDC, 0, 0, SRCCOPY);

	BLENDFUNCTION m_blend;
	m_blend.BlendOp = 0;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = 1;
	m_blend.SourceConstantAlpha = pWindow->transparentAlpha;

	RECT rcWnd;
	GetWindowRect(pWindow->hWnd, &rcWnd);
	POINT ptDst = { rcWnd.left, rcWnd.top };
	POINT ptSrc = { 0, 0 };
	SIZE m_sizeWnd = { rcSysNCClient.right,rcSysNCClient.bottom };
	//int res=
	UpdateLayeredWindow(pWindow->hWnd, hdc, &ptDst, &m_sizeWnd, memDC, &ptSrc, 0, &m_blend, ULW_ALPHA);
	//	if(0==res)
	//	{
	//		DWORD err= GetLastError();
	//		XTRACE("PaintEle() err=%d \n",err);
	//	}else
	//		XTRACE("PaintEle() \n");

	DeleteDC(memDC);
}

void Wnd_PaintEle_Caret(HWINDOW hWindow, HDRAW hDraw) //��������
{
	window_ *pWindow = (window_*)hWindow;

	POINT ptOld;
	SetViewportOrgEx(pWindow->hBkDC, -(pWindow->rcDraw.left), -(pWindow->rcDraw.top), &ptOld);

	POINT  ptCaret = pWindow->caretPt;
	XEle_PointToNCWnd(pWindow->hCaretEle, &ptCaret);

	//���ݲ��������
	HDC hdcCaret = CreateCompatibleDC(NULL);
	SelectObject(hdcCaret, pWindow->hCaretBitmap);
	BitBlt(hdcCaret, 0, 0, pWindow->caretWidth, pWindow->caretHeight, pWindow->hBkDC, ptCaret.x, ptCaret.y, SRCCOPY);
	DeleteDC(hdcCaret);

	SetViewportOrgEx(pWindow->hBkDC, ptOld.x, ptOld.y, 0);

	//����ڻ��Ʒ�Χ��
	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);
	if (PtInRect(&pWindow->rcDraw, pt))
	{
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW) //͸������
		{
			Wnd_DrawCaretTransparentMemDC(hWindow, hDraw); //���Ʋ����
		}
		else
		{
			Wnd_DrawCaretMenDC(hWindow, hDraw);
		}
	}
}

BOOL Wnd_KeyDown(HWINDOW hWindow, int key) //Ԫ�ؽ����л�����
{
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->pFocus && pWindow->pFocus->bClient) //�ͻ���
	{
		if (XC_RICHEDIT == pWindow->pFocus->eleType)
			return FALSE;

		if (VK_TAB == key)  //TAB
		{
			return Wnd_HandleFocusDown(hWindow); //�������л�
		}if (XC_IsEditExtend((HELE)pWindow->pFocus)) //�༭��֧�ּ�ͷ�л�
		{
			return FALSE;
		}
		else if (37 == key || 38 == key)  //���л�
		{
			if (pWindow->pFocus && pWindow->pFocus->bShow)
			{
				return Wnd_HandleFocusUp(hWindow);   //�������л�
			}
		}
		else if (39 == key || 40 == key)   //���л�
		{
			if (pWindow->pFocus && pWindow->pFocus->bShow)
			{
				return Wnd_HandleFocusDown(hWindow); //�������л�
			}
		}
	}
	else //�ǿͻ���
	{
		//TODO:�ǿͻ���Ԫ�ؽ����л�
	}
	return FALSE;
}

BOOL Wnd_HandleFocusUp(HWINDOW hWindow)   //�������л�
{
	window_ *pWindow = (window_*)hWindow;

	if (NULL == pWindow->pFocus) return FALSE;

	ele_ *curEle = NULL;
	ele_ *pParent = pWindow->pFocus->pParentEle;
	if (pParent)  //�и�Ԫ��
	{
		int count = Array_GetCount(pParent->hArrayEle);
		int index = 0;
		for (int i = 0; i < count; i++)
		{
			if (pWindow->pFocus == Array_GetAtEle(pParent->hArrayEle, i))
			{
				index = i;
				break;
			}
		}
		ele_  *pEle = NULL;
		for (int i = index - 1; i > -1; i--)
		{
			curEle = Array_GetAtEle(pParent->hArrayEle, i);
			if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
			{
				pEle = curEle;
				break;
			}
		}
		if (NULL == pEle)
		{
			for (int i = index; i < count; i++)
			{
				curEle = Array_GetAtEle(pParent->hArrayEle, i);
				if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
				{
					pEle = curEle;
					break;
				}
			}
		}
		if (pEle && pEle != pWindow->pFocus)
		{
			XEle_SetFocus((HELE)pEle, TRUE);
			return TRUE;
		}
	}
	else  //û�и�Ԫ��
	{
		int count = Array_GetCount(pWindow->hArrayEle);

		int index = 0;
		for (int i = 0; i < count; i++)
		{
			if (pWindow->pFocus == Array_GetAtEle(pWindow->hArrayEle, i))
			{
				index = i;
				break;
			}
		}

		ele_  *pEle = NULL;
		ele_ *curEle = NULL;
		for (int i = index - 1; i > -1; i--)
		{
			curEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
			{
				pEle = curEle;
				break;
			}
		}
		if (NULL == pEle)
		{
			for (int i = index; i < count; i++)
			{
				curEle = Array_GetAtEle(pWindow->hArrayEle, i);
				if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
				{
					pEle = curEle;
					break;
				}
			}
		}
		if (pEle && pEle != pWindow->pFocus)
		{
			XEle_SetFocus((HELE)pEle, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Wnd_HandleFocusDown(HWINDOW hWindow) //�������л�
{
	window_ *pWindow = (window_*)hWindow;
	ele_ *curEle = NULL;
	if (NULL == pWindow->pFocus)
	{
		int count = Array_GetCount(pWindow->hArrayEle);
		for (int i = 0; i < count; i++)
		{
			curEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
			{
				XEle_SetFocus((HELE)curEle, TRUE);
				return TRUE;
			}
		}
		return FALSE;
	}

	ele_ *pParent = pWindow->pFocus->pParentEle;
	if (pParent)  //�и�Ԫ��
	{
		int count = Array_GetCount(pParent->hArrayEle);
		int index = 0;
		for (int i = 0; i < count; i++)
		{
			if (pWindow->pFocus == Array_GetAtEle(pParent->hArrayEle, i))
			{
				index = i;
				break;
			}
		}
		ele_ *pEle = NULL;
		for (int i = index + 1; i < count; i++)
		{
			curEle = Array_GetAtEle(pParent->hArrayEle, i);
			if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
			{
				pEle = curEle;
				break;
			}
		}
		if (NULL == pEle)
		{
			for (int i = 0; i < index; i++)
			{
				curEle = Array_GetAtEle(pParent->hArrayEle, i);
				if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
				{
					pEle = curEle;
					break;
				}
			}
		}
		if (pEle && pEle != pWindow->pFocus)
		{
			XEle_SetFocus((HELE)pEle, TRUE);
			return TRUE;
		}
	}
	else  //û�и�Ԫ��
	{
		int count = Array_GetCount(pWindow->hArrayEle);

		int index = 0;
		for (int i = 0; i < count; i++)
		{
			if (pWindow->pFocus == Array_GetAtEle(pWindow->hArrayEle, i))
			{
				index = i;
				break;
			}
		}
		ele_ *pEle = NULL;
		for (int i = index + 1; i < count; i++)
		{
			curEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
			{
				pEle = curEle;
				break;
			}
		}
		if (NULL == pEle)
		{
			for (int i = 0; i < index; i++)
			{
				curEle = Array_GetAtEle(pWindow->hArrayEle, i);
				if (curEle->bShow && curEle->bEnable && curEle->bEnableFocus)
				{
					pEle = curEle;
					break;
				}
			}
		}
		if (pEle && pEle != pWindow->pFocus)
		{
			XEle_SetFocus((HELE)pEle, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

int Wnd_GetWindowCount()//��ȡ��������
{
	return Resource_GetWindowCount();
}

//pPt:�ͻ�������
BOOL CALLBACK Wnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;
	//pWindow->bTitleBarDown=FALSE;
	//�ж�������ĸ�Ԫ����
	ele_ *curEle = NULL;
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		curEle = Array_GetAtEle(pWindow->hArrayEle, i);
		if (curEle->bShow && FALSE == curEle->bMouseThrough)
		{
			if (PtInRect(&curEle->rect, *pPt))
			{
				if (pWindow->pMouseTop != curEle)
				{
					if (pWindow->pMouseTop)
					{
						HELE hEleSend = (HELE)pWindow->pMouseTop;
						pWindow->pMouseTop = NULL;
						Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
					}
					if (curEle->bEnable)
					{
						pWindow->pMouseTop = curEle;
						Ele_SendEvent((HELE)pWindow->pMouseTop, XE_MOUSESTAY, 0, 0);
					}
				}
				//������ת����Ԫ�ؿͻ��� ����
				if (curEle->bEnable)
				{
					POINT InPt = { pPt->x - curEle->rect.left, pPt->y - curEle->rect.top };
					Ele_SendEleMsg((HELE)curEle, XM_MOUSEMOVE, (WPARAM)flags, (LPARAM)&InPt);
				}
				return TRUE;
			}
		}
	}

	//���û�����κ�Ԫ��֮��
	if (pWindow->pMouseTop) //����뿪
	{
		HELE hEleSend = (HELE)pWindow->pMouseTop;
		pWindow->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}
	return TRUE;
}

//pPt:�ͻ�������
BOOL CALLBACK Wnd_OnLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEle, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (pEle->bShow && FALSE == pEle->bMouseThrough)
			{
				if (PtInRect(&pEle->rect, *pPt))
				{
					POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
					Ele_SendEleMsg((HELE)pEle, XM_LBUTTONDOWN, (WPARAM)flags, (LPARAM)&pt);
					return TRUE;
				}
			}
		}
	}

	if (pWindow->xcStyle & XC_SY_DRAG_WINDOW) //�϶�����
	{
		SendMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}

	return TRUE;
}

//pPt:�ͻ�������
BOOL CALLBACK Wnd_OnLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEle, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (pEle->bShow && FALSE == pEle->bMouseThrough && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_LBUTTONUP, (WPARAM)flags, (LPARAM)&pt);
				break;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnRButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEle, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (pEle->bShow && FALSE == pEle->bMouseThrough && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_RBUTTONDOWN, (WPARAM)flags, (LPARAM)&pt);
				break;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnRButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEle, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
			if (pEle->bShow && FALSE == pEle->bMouseThrough && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_RBUTTONUP, (WPARAM)flags, (LPARAM)&pt);
				break;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnMouseLeave(HWINDOW hWindow)
{
	window_ *pWindow = (window_*)hWindow;
	//	pWindow->downBorder=0;
	pWindow->bTrackLeave = FALSE;
	//pWindow->bTitleBarDown=FALSE;
	if (pWindow->pMouseTop)
	{
		HELE hEleSend = (HELE)pWindow->pMouseTop;
		pWindow->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnSize(HWINDOW hWindow, UINT type, SIZE *pSize)
{
	int cx = pSize->cx;
	int cy = pSize->cy;
	window_ *pWindow = (window_*)hWindow;

	if (IsZoomed(pWindow->hWnd)) //��󻯴���
	{
		RECT rect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

		RECT rcWnd;
		GetWindowRect(pWindow->hWnd, &rcWnd);
		//	if(cx!=(rect.right-rect.left) || cy!=(rect.bottom-rect.top))
		if ((rcWnd.right - rcWnd.left) != (rect.right - rect.left) || (rcWnd.bottom - rcWnd.top) != (rect.bottom - rect.top))
		{
			cx = rect.right - rect.left;
			cy = rect.bottom - rect.top;
			::SetWindowPos(pWindow->hWnd, NULL, rect.left, rect.top, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);
			//	return TRUE;
		}
	}

	if (pWindow->xcStyle & XC_SY_ROUND)
	{
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW) //�ֲ㴰��
		{
			HRGN hrgn = CreateRoundRectRgn(0, 0, cx + XC_WIND_SHADOW_SIZE * 2 + 1, cy + XC_WIND_SHADOW_SIZE * 2 + 1, pWindow->roundSize, pWindow->roundSize);
			SetWindowRgn(pWindow->hWnd, hrgn, TRUE);
			DeleteObject(hrgn);
		}
		else
		{
			HRGN hrgn = CreateRoundRectRgn(0, 0, cx + 1, cy + 1, pWindow->roundSize, pWindow->roundSize);
			SetWindowRgn(pWindow->hWnd, hrgn, TRUE);
			DeleteObject(hrgn);
		}
	}
	XWnd_Adjust(hWindow);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //�ֲ㴰��
	{
		XWnd_RedrawWnd(hWindow);
	}
	//XWnd_RedrawWnd(hWindow,TRUE);
	//RedrawWindow(pWindow->hWnd,NULL,NULL,RDW_INVALIDATE);
	return TRUE;
}


BOOL CALLBACK Wnd_OnTimer(HWINDOW hWindow, UINT_PTR nIDEvent, UINT uElapse)
{
	switch (nIDEvent)
	{
	case IDT_CLICK:   //���������˫��
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->bMouseUp && pWindow->bClickTimer) //����
		{
			int posx = pWindow->mouseDown.x;
			int posy = pWindow->mouseDown.y;
			if (posx == pWindow->mouseUp.x && posy == pWindow->mouseUp.y)
			{
				PostMessage(pWindow->hWnd, XWM_MOUSECLICK, posx, posy);
				//	XTRACE("��굥��\n");
			}
		}
		pWindow->bClickTimer = FALSE;
		pWindow->bMouseUp = FALSE;
		//pWindow->bMouseDown2=FALSE;
		KillTimer(pWindow->hWnd, IDT_CLICK);
	}break;
	case IDT_HSCROLL_UP: //�Ϲ���
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->pScrollBar)
		{
			if (0 == pWindow->pScrollBar->curPos)
			{
				KillTimer(pWindow->hWnd, IDT_HSCROLL_UP); //TRACE("kill111 \n");
				pWindow->pScrollBar = NULL;
				break;
			}
			XSBar_ScrollUp((HELE)pWindow->pScrollBar);
		}
		else
			KillTimer(pWindow->hWnd, IDT_HSCROLL_UP);
	}break;
	case IDT_HSCROLL_DOWN: //�¹���
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->pScrollBar)
		{
			if (pWindow->pScrollBar->range == pWindow->pScrollBar->curPos)
			{
				KillTimer(pWindow->hWnd, IDT_HSCROLL_DOWN); //TRACE("kill222 \n");
				pWindow->pScrollBar = NULL;
				break;
			}
			XSBar_ScrollDown((HELE)pWindow->pScrollBar);
		}
		else
			KillTimer(pWindow->hWnd, IDT_HSCROLL_DOWN);
	}break;
	case IDT_CARET: //������Ʋ����
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->bCaretErase)
			pWindow->bCaretErase = FALSE;
		else
			pWindow->bCaretErase = TRUE;

		Wnd_DrawCaret(hWindow);
		//OutputDebugStringA("���Ʋ����\n");
	}break;
	}
	//OutputDebugStringA("on - timer \n");
	return TRUE;
}

BOOL CALLBACK Wnd_OnMouseClick(HWINDOW hWindow, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;
	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
		if (pEle->bShow)
		{
			if (PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_MOUSECLICK, (WPARAM)&pt, 0);
				break;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnMouseDBClick(HWINDOW hWindow, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;
	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = count - 1; i > -1; i--)
	{
		ele_ *pEle = Array_GetAtEle(pWindow->hArrayEle, i);
		if (pEle->bShow)
		{
			if (PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_MOUSEDBCLICK, (WPARAM)&pt, 0);
				break;
			}
		}
	}
	return TRUE;
}

//���Ʊ�����
void Wnd_DrawCaption(HWINDOW hWindow, HDRAW hDraw)
{
	//���û�б�����������
	int clientTop = XWnd_GetCaptionHeight(hWindow); //XWnd_GetClientTop(hWindow);
	if (clientTop < 1)
		return;

	window_ *pWindow = (window_*)hWindow;

	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	RECT rcTitle = rect; //����������
	rcTitle.bottom = clientTop;

	//1.����Ƿ��ڻ��Ʒ�Χ��
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcTitle))
		return; //���ڻ���������

	//2.�����µĻ�������
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcTitle))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;
	if (pWindow->hImageCaption)
	{
		HBITMAP hWndBitmap = XDraw_CreateDIBSection(NULL, cx, cy);
		HDC memDC = CreateCompatibleDC(NULL);
		SelectObject(memDC, hWndBitmap);
		RECT rcFill = { 0,0,cx,cy };
		XDraw_FillSolidRect(memDC, &rcFill, pWindow->bkColor);

		RECT rc;
		rc.left = -rcDest.left;
		rc.top = -rcDest.top;
		rc.right = rc.left + rcTitle.right - rcTitle.left;
		rc.bottom = rc.top + rcTitle.bottom - rcTitle.top;

		XDraw_HImageSuper(memDC, pWindow->hImageCaption, &rc);

		XDraw_BitBlt_(hDraw, rcDest.left, rcDest.top, cx, cy, memDC, 0, 0, SRCCOPY);

		DeleteObject(memDC);
		DeleteObject(hWndBitmap);
	}
	else
	{
		if (NULL == pWindow->hImageNC)
		{
			RECT rc = rcTitle;
			rc.left = rcDest.left;
			rc.right = rcDest.right;

			if (pWindow->hWnd == GetActiveWindow())
			{
				XDraw_GradientFill2_(hDraw, RGB(72, 164, 219), RGB(39, 135, 194), &rc, GRADIENT_FILL_RECT_V);
			}
			else
			{
				XDraw_GradientFill2_(hDraw, RGB(123, 190, 230), RGB(74, 165, 219), &rc, GRADIENT_FILL_RECT_V);
			}
		}
	}
	int halfY = rcTitle.bottom / 2; //�м�����

	//����ͼ��
	HICON hIcon = (HICON)GetClassLongPtr(pWindow->hWnd, GCLP_HICONSM);
	if (hIcon && pWindow->xcStyle & XC_SY_DRAW_CAPTION_ICON)
	{
		XDraw_DrawIconEx_(hDraw, 8, halfY - pWindow->iconSize.cy / 2, hIcon, pWindow->iconSize.cx, pWindow->iconSize.cy, 0, 0, DI_NORMAL);
		rcTitle.left = pWindow->iconSize.cx + 8 + 5;
	}
	else
	{
		rcTitle.left = 8;
	}

	if (pWindow->xcStyle & XC_SY_DRAW_CAPTION_TITLE)
	{
		if ((rcTitle.right - rcTitle.left) > 20) //����ı���ʾ����
		{
			wchar_t title[256] = { 0 };
			int len = GetWindowText(pWindow->hWnd, title, 256);
			if (len > 0) //���Ʊ����ı�
			{
				XDraw_DrawText_(hDraw, title, len, &rcTitle, DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
}

//���Ʊ߿�left
void Wnd_DrawBorderLeft(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;
	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	RECT  rcLeft;
	rcLeft.left = 0;
	rcLeft.top = XWnd_GetCaptionHeight(hWindow);
	rcLeft.right = XWnd_GetClientLeft(hWindow);
	rcLeft.bottom = rect.bottom - XWnd_GetClientBottom(hWindow);

	//1.����Ƿ��ڻ��Ʒ�Χ��
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcLeft))
		return; //���ڻ���������

	//2.�����µĻ�������
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcLeft))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;

	//��߿�
	if (pWindow->hImageLeft)
	{
		BITMAPINFO info;
		memset(&info.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biWidth = cx;
		info.bmiHeader.biHeight = cy;
		HBITMAP hWndBitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, NULL, NULL, 0);
		HDC memDC = CreateCompatibleDC(NULL);
		SelectObject(memDC, hWndBitmap);
		RECT rcFill = { 0,0,cx,cy };
		XDraw_FillSolidRect(memDC, &rcFill, pWindow->bkColor);

		int srcX = rcDest.left;
		int srcY = rcDest.top - rcLeft.top;

		RECT rc;
		rc.left = -srcX;
		rc.top = -srcY;
		rc.right = rc.left + rcLeft.right - rcLeft.left;
		rc.bottom = rc.top + rcLeft.bottom - rcLeft.top;
		XDraw_HImageSuper(memDC, pWindow->hImageLeft, &rc);

		XDraw_BitBlt_(hDraw, rcDest.left, rcDest.top, cx, cy, memDC, 0, 0, SRCCOPY);

		DeleteObject(memDC);
		DeleteObject(hWndBitmap);
	}
	else
	{
		if (pWindow->hWnd == GetActiveWindow())
		{
			XDraw_FillSolidRect_(hDraw, &rcDest, RGB(39, 135, 194));
		}
		else
		{
			XDraw_FillSolidRect_(hDraw, &rcDest, RGB(74, 165, 219));
		}
	}
}

//���Ʊ߿�right
void Wnd_DrawBorderRight(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;
	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	RECT  rcRight;
	rcRight.left = rect.right - XWnd_GetClientRight(hWindow);
	rcRight.top = XWnd_GetCaptionHeight(hWindow);
	rcRight.right = rect.right;
	rcRight.bottom = rect.bottom - XWnd_GetClientBottom(hWindow);

	//1.����Ƿ��ڻ��Ʒ�Χ��
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcRight))
		return; //���ڻ���������

	//2.�����µĻ�������
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcRight))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;

	//��߿�
	if (pWindow->hImageRight)
	{
		HBITMAP hWndBitmap = XDraw_CreateDIBSection(NULL, cx, cy);
		HDC memDC = CreateCompatibleDC(NULL);
		SelectObject(memDC, hWndBitmap);
		RECT rcFill = { 0,0,cx,cy };
		XDraw_FillSolidRect(memDC, &rcFill, pWindow->bkColor);

		int srcX = rcDest.left - rcRight.left;
		int srcY = rcDest.top - rcRight.top;

		RECT rc;
		rc.left = -srcX;
		rc.top = -srcY;
		rc.right = rc.left + rcRight.right - rcRight.left;
		rc.bottom = rc.top + rcRight.bottom - rcRight.top;
		XDraw_HImageSuper(memDC, pWindow->hImageRight, &rc);

		XDraw_BitBlt_(hDraw, rcDest.left, rcDest.top, cx, cy, memDC, 0, 0, SRCCOPY);

		DeleteObject(memDC);
		DeleteObject(hWndBitmap);
	}
	else
	{
		if (pWindow->hWnd == GetActiveWindow())
		{
			XDraw_FillSolidRect_(hDraw, &rcDest, RGB(39, 135, 194));
		}
		else
		{
			XDraw_FillSolidRect_(hDraw, &rcDest, RGB(74, 165, 219));
		}
	}
}

//���Ʊ߿�bottom
void Wnd_DrawBorderBottom(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;
	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	RECT  rcBottom;
	rcBottom.left = 0;
	rcBottom.top = rect.bottom - XWnd_GetClientBottom(hWindow);
	rcBottom.right = rect.right;
	rcBottom.bottom = rect.bottom;

	//1.����Ƿ��ڻ��Ʒ�Χ��
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcBottom))
		return; //���ڻ���������

	//2.�����µĻ�������
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcBottom))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;
	//��߿�
	if (pWindow->hImageBottom)
	{
		BITMAPINFO info;
		memset(&info.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biWidth = cx;
		info.bmiHeader.biHeight = cy;
		HBITMAP hWndBitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, NULL, NULL, 0);
		HDC memDC = CreateCompatibleDC(NULL);
		SelectObject(memDC, hWndBitmap);
		RECT rcFill = { 0,0,cx,cy };
		XDraw_FillSolidRect(memDC, &rcFill, pWindow->bkColor);

		int srcX = rcDest.left;
		int srcY = rcDest.top - rcBottom.top;

		RECT rc;
		rc.left = -srcX;
		rc.top = -srcY;
		rc.right = rc.left + rcBottom.right - rcBottom.left;
		rc.bottom = rc.top + rcBottom.bottom - rcBottom.top;
		XDraw_HImageSuper(memDC, pWindow->hImageBottom, &rc);

		XDraw_BitBlt_(hDraw, rcDest.left, rcDest.top, cx, cy, memDC, 0, 0, SRCCOPY);

		DeleteObject(memDC);
		DeleteObject(hWndBitmap);
	}
	else
	{
		if (pWindow->hWnd == GetActiveWindow())
		{
			XDraw_FillSolidRect_(hDraw, &rcDest, RGB(39, 135, 194));
		}
		else
		{
			XDraw_FillSolidRect_(hDraw, &rcDest, RGB(74, 165, 219));
		}
	}
}

//�ǿͻ�����ͼʱ����
void Wnd_DrawCaptionImageNC(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;
	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	//������---------------------------------------
	if (pWindow->captionHeight > 0)
	{
		RECT rcTitle = rect;
		rcTitle.bottom = pWindow->captionHeight;

		int halfY = rcTitle.bottom / 2; //�м�����

		//����ͼ��
		HICON hIcon = (HICON)GetClassLongPtr(pWindow->hWnd, GCLP_HICONSM);
		if (hIcon && pWindow->xcStyle & XC_SY_DRAW_CAPTION_ICON)
		{
			XDraw_DrawIconEx_(hDraw, 8, halfY - pWindow->iconSize.cy / 2, hIcon, pWindow->iconSize.cx, pWindow->iconSize.cy, 0, 0, DI_NORMAL);
			rcTitle.left = pWindow->iconSize.cx + 8 + 3;
		}
		else
		{
			rcTitle.left = 8;
		}
		if (pWindow->xcStyle & XC_SY_DRAW_CAPTION_TITLE)
		{
			if ((rcTitle.right - rcTitle.left) > 20) //����ı���ʾ����
			{
				wchar_t title[256] = { 0 };
				int len = GetWindowText(pWindow->hWnd, title, 256);
				if (len > 0) //���Ʊ����ı�
				{
					XDraw_DrawText_(hDraw, title, len, &rcTitle, DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
	}
}

BOOL CALLBACK Wnd_OnNCDrawWindow(HWINDOW hWindow, HDRAW hDraw) //�ǿͻ�������
{
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED)
	{
		return TRUE;
	}

	//�ǿͻ�����ͼ
	if (((window_*)hWindow)->hImageNC)
	{
		Wnd_DrawCaptionImageNC(hWindow, hDraw);
	}
	else
	{
		Wnd_DrawCaption(hWindow, hDraw);
		Wnd_DrawBorderLeft(hWindow, hDraw);
		Wnd_DrawBorderRight(hWindow, hDraw);
		Wnd_DrawBorderBottom(hWindow, hDraw);
	}

	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	int borderLeft = XWnd_GetClientLeft(hWindow);
	int borderTop = XWnd_GetClientTop(hWindow);
	int borderRight = XWnd_GetClientRight(hWindow);
	int borderBottom = XWnd_GetClientBottom(hWindow);

	if (pWindow->chartletStyle & XC_CS_STROKE_INNER) //�����
	{
		RECT rcBorder = { borderLeft - 1,XWnd_GetCaptionHeight(hWindow) - 1,
			rect.right - borderRight + 1,rect.bottom - borderBottom + 1 };

		if (rcBorder.left > 5 && rcBorder.top > 5 && (rect.right - rcBorder.right) > 5 && (rect.bottom - rcBorder.bottom) > 5)
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeInner_color1);//��ɫ
			HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeInner_color2);//��ɫ
			//�ں�ɫ
			XDraw_FrameRect_(hDraw, &rcBorder, hBrush);

			//�ڰ�ɫ
			rcBorder.left--; rcBorder.top--; rcBorder.right++; rcBorder.bottom++;
			XDraw_FrameRect_(hDraw, &rcBorder, hBrush2);
		}
	}

	if (pWindow->chartletStyle & XC_CS_STROKE_OUTER) //�����
	{
		//�������
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeOuter_color1);//��ɫ
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeOuter_color2);//��ɫ

		if (pWindow->xcStyle & XC_SY_ROUND)
		{
			HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, pWindow->roundSize, pWindow->roundSize);
			XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);

			if (borderLeft > 1 && borderTop > 1 && borderRight > 1 && borderBottom > 1)
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom, pWindow->roundSize - 2, pWindow->roundSize - 2);
				XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
			}
		}
		else
		{
			//���ɫ
			if (borderLeft > 1 && borderTop > 1 && borderRight > 1 && borderBottom > 1)
			{
				RECT rcBorder2 = rect;
				rcBorder2.left++; rcBorder2.top++; rcBorder2.right--; rcBorder2.bottom--;
				XDraw_FrameRect_(hDraw, &rcBorder2, hBrush2);
			}

			//���ɫ
			if (borderLeft > 0 && borderTop > 0 && borderRight > 0 && borderBottom > 0)
				XDraw_FrameRect_(hDraw, &rect, hBrush);
		}
	}

	return TRUE;
}

BOOL CALLBACK Wnd_OnNCMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;
	ele_ *curEle = NULL;
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		curEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
		if (curEle->bShow)
		{
			if (PtInRect(&curEle->rect, *pPt))
			{
				if (pWindow->pMouseTop != curEle)
				{
					if (pWindow->pMouseTop)
					{
						HELE hEleSned = (HELE)pWindow->pMouseTop;
						pWindow->pMouseTop = NULL;
						Ele_SendEvent(hEleSned, XE_MOUSELEAVE, 0, 0);
					}
					pWindow->pMouseTop = curEle;
					Ele_SendEvent((HELE)pWindow->pMouseTop, XE_MOUSESTAY, 0, 0);
				}
				//������ת����Ԫ�ؿͻ��� ����
				POINT InPt = { pPt->x - curEle->rect.left, pPt->y - curEle->rect.top };
				Ele_SendEleMsg((HELE)curEle, XM_MOUSEMOVE, (WPARAM)flags, (LPARAM)&InPt);
				return TRUE;
			}
		}
	}

	//���û�����κ�Ԫ��֮��
	if (pWindow->pMouseTop) //����뿪
	{
		HELE hEleSend = (HELE)pWindow->pMouseTop;
		pWindow->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}

	//�ı���//////////////////////////////////////
	if (FALSE == IsZoomed(pWindow->hWnd) && pWindow->xcStyle & XC_SY_DRAG_BORDER)//pWindow->bMaxWnd)
	{
		if (pWindow->xcStyle & XC_SY_DRAG_BORDER)
		{
			int top = 3;
			if (pWindow->captionHeight > 0)
				top = 3;
			else
				top = pWindow->borderTop;

			RECT rect;
			GetClientRect(pWindow->hWnd, &rect);
			if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x >= 0 && pPt->x < 8)//pPt->x<pWindow->borderLeft) //��
			{
				if (pPt->y < 10) //�Ͻ�
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else if (pPt->y > rect.bottom - 10) //�½�
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE)); return TRUE;
				}
			}
			else if (pPt->x > 0 && pPt->x < rect.right && pPt->y>0 && pPt->y < top) //��
			{
				if (pPt->x < 10) //���Ͻ�
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else if (pPt->x > rect.right - 10) //���Ͻ�
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENS)); return TRUE;
				}
			}
			else if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x<rect.right && pPt->x>rect.right - 8)//pPt->x>rect.right-pWindow->borderRight) //��
			{
				if (pPt->y < 10) //���Ͻ�
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else if (pPt->y > rect.bottom - 10) //���½�
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE)); return TRUE;
				}
			}
			else if (pPt->x > 0 && pPt->x < rect.right && pPt->y<rect.bottom && pPt->y>rect.bottom - 8)//pPt->y>rect.bottom-pWindow->borderBottom) //��
			{
				if (pPt->x < 10)
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else if (pPt->x > rect.right - 10)
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENS)); return TRUE;
				}
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEleNC, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
			if (pEle->bShow && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_LBUTTONDOWN, (WPARAM)flags, (LPARAM)&pt);
				return TRUE;
			}
		}
	}

	//	//���û������Ԫ����
	//	if(pWindow->pFocus)
	//	{
	//		//ʧȥ����
	//		Ele_SendEvent(pWindow->pFocus,XE_KILLFOCUS,0,0);
	//		pWindow->pFocus=NULL;
	//	}

	//��갴�ڱ߿���
	if (FALSE == IsZoomed(pWindow->hWnd) && pWindow->xcStyle & XC_SY_DRAG_BORDER)//pWindow->bMaxWnd
	{
		//downBorder
		int top = 3;
		if (pWindow->captionHeight > 0)
			top = 3;
		else
			top = pWindow->borderTop;

		RECT rect;
		GetClientRect(pWindow->hWnd, &rect);
		if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x >= 0 && pPt->x < 8)//pPt->x<pWindow->borderLeft) //��
		{
			if (pPt->y < 10) //�Ͻ�
			{
				//	pWindow->downBorder=5;
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->y > rect.bottom - 10) //�½�
			{
				//	pWindow->downBorder=6;
				SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTBOTTOMLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else
			{
				//	pWindow->downBorder=1;
				SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
		}
		else if (pPt->x > 0 && pPt->x < rect.right && pPt->y>0 && pPt->y < top) //��
		{
			if (pPt->x < 10) //���Ͻ�
			{
				//	pWindow->downBorder=5;
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->x > rect.right - 10) //���Ͻ�
			{
				//	pWindow->downBorder=7;
				SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPRIGHT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else
			{
				//	pWindow->downBorder=2;
				SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOP, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
		}
		else if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x<rect.right && pPt->x>rect.right - 8)//pPt->x>rect.right-pWindow->borderRight) //��
		{
			if (pPt->y < 10) //���Ͻ�
			{
				//	pWindow->downBorder=7;
				SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPRIGHT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->y > rect.bottom - 10) //���½�
			{
				//	pWindow->downBorder=8;
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else
			{
				//	pWindow->downBorder=3;
				SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTRIGHT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
		}
		else if (pPt->x > 0 && pPt->x < rect.right && pPt->y<rect.bottom && pPt->y>rect.bottom - 8)//pPt->y>rect.bottom-pWindow->borderBottom) //��
		{
			if (pPt->x < 10)
			{
				//	pWindow->downBorder=6;
				SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTBOTTOMLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->x > rect.right - 10)
			{
				//	pWindow->downBorder=8;
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else
			{
				//	pWindow->downBorder=4;
				SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTBOTTOM, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
		}
	}

	//��갴�ڱ�����
	if (pWindow->captionHeight > 0)
	{
		if (pPt->y > 0 && pPt->y < pWindow->captionHeight)
		{
			if (FALSE == pWindow->bMouseDown2)
			{
				if (XC_FLOATWND == XC_GetObjectType(hWindow))
				{
					FloatWnd_DragWindow(hWindow, pPt);
				}
				else
				{
					SendMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(100, 100));
				}
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEleNC, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
			if (pEle->bShow && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_LBUTTONUP, (WPARAM)flags, (LPARAM)&pt);
				return TRUE;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCRButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEleNC, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
			if (pEle->bShow && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_RBUTTONDOWN, (WPARAM)flags, (LPARAM)&pt);
				return TRUE;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCRButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEleNC, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
			if (pEle->bShow && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_RBUTTONUP, (WPARAM)flags, (LPARAM)&pt);
				return TRUE;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCMouseClick(HWINDOW hWindow, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEleNC, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
			if (pEle->bShow && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				//	Ele_SendEvent(pEle,XE_MOUSECLICK,MAKEWPARAM(pt.x,pt.y),0);
				Ele_SendEleMsg((HELE)pEle, XM_MOUSECLICK, (WPARAM)&pt, 0);
				return TRUE;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCMouseDBClick(HWINDOW hWindow, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//������Ԫ����Ϣ
	int count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = count - 1; i > -1; i--)
	{
		if (Array_GetAtEle(pWindow->hArrayEleNC, i)->bShow)
		{
			ele_ *pEle = Array_GetAtEle(pWindow->hArrayEleNC, i);
			if (pEle->bShow && PtInRect(&pEle->rect, *pPt))
			{
				POINT pt = { pPt->x - pEle->rect.left,pPt->y - pEle->rect.top };
				Ele_SendEleMsg((HELE)pEle, XM_MOUSEDBCLICK, (WPARAM)&pt, 0);
				return TRUE;
			}
		}
	}

	//û�����κ�Ԫ����
	if (XC_SY_MAXIMIZE & pWindow->xcStyle) //������󻯻�ԭ��С
	{
		RECT rect;
		GetClientRect(pWindow->hWnd, &rect);
		rect.bottom = XWnd_GetClientTop(hWindow);
		rect.left = XWnd_GetClientLeft(hWindow);
		rect.right -= XWnd_GetClientRight(hWindow);
		if (PtInRect(&rect, *pPt))
		{
			//	if(pWindow->bMaxWnd)
			//		XWnd_MaximizeWnd(hWindow,FALSE);
			//	else
			//		XWnd_MaximizeWnd(hWindow,TRUE);
			SendMessage(pWindow->hWnd, WM_NCLBUTTONDBLCLK, HTCAPTION, 0);

		}
	}
	return TRUE;
}

///////////////////////////////////////
BOOL CALLBACK Wnd_OnBtnCloseDraw(HELE hEle, HDRAW hDraw)
{
	if (BUTTON(hEle)->hImage_check) return FALSE;
	if (BUTTON(hEle)->hImage_disable) return FALSE;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	switch (BUTTON(hEle)->state)
	{
	case STATE_STAY:
	{
		if (BUTTON(hEle)->hImage_stay) return FALSE;
		XDraw_GradientFill4_(hDraw, RGB(227, 144, 140), RGB(212, 99, 95), RGB(200, 27, 11), RGB(205, 62, 48), &rect, GRADIENT_FILL_RECT_V);
	}
	break;
	case STATE_DOWN:
	case STATE_LEAVE:
	{
		if (BUTTON(hEle)->hImage_leave) return FALSE;
		if (BUTTON(hEle)->hImage_down) return FALSE;
		XDraw_GradientFill4_(hDraw, RGB(211, 147, 166), RGB(184, 117, 115), RGB(158, 62, 53), RGB(180, 115, 107), &rect, GRADIENT_FILL_RECT_V);
	}
	break;
	}

	HBRUSH  hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(6, 108, 156));
	HBRUSH  hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(143, 217, 253));
	XDraw_FrameRect_(hDraw, &rect, hBrush1);
	RECT rc1 = { 1,0,rect.right - 1,rect.bottom - 1 };
	XDraw_FrameRect_(hDraw, &rc1, hBrush2);

	//	DeleteObject(hBrush1);
	//	DeleteObject(hBrush2);

	HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 2, RGB(255, 255, 255));
	HGDIOBJ hold = XDraw_SelectObject_(hDraw, hPen);
	XDraw_MoveToEx_(hDraw, rect.left + 14, rect.top + 4, NULL);  //���� �� ����
	XDraw_LineTo_(hDraw, rect.left + 23, rect.top + 13);

	XDraw_MoveToEx_(hDraw, rect.left + 23, rect.top + 4, NULL);  //���� �� ����
	XDraw_LineTo_(hDraw, rect.left + 14, rect.top + 13);

	//	SelectObject(hdc,hold);
	//	DeleteObject(hPen);

	return TRUE;
}

BOOL CALLBACK Wnd_OnBtnMaximizeDraw(HELE hEle, HDRAW hDraw)
{
	if (BUTTON(hEle)->hImage_check) return FALSE;
	if (BUTTON(hEle)->hImage_disable) return FALSE;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	window_ *pWindow = (window_*)XEle_GetHWindow(hEle);
	if (pWindow)
	{
		if (pWindow->hClose)
			rect.right++;
	}
	switch (BUTTON(hEle)->state)
	{
	case STATE_STAY:
	{
		if (BUTTON(hEle)->hImage_stay) return FALSE;
		XDraw_GradientFill4_(hDraw, RGB(143, 217, 253), RGB(58, 189, 252), RGB(39, 135, 194), RGB(58, 189, 252), &rect, GRADIENT_FILL_RECT_V);
	}
	break;
	case STATE_DOWN:
	case STATE_LEAVE:
	{
		if (BUTTON(hEle)->hImage_leave) return FALSE;
		if (BUTTON(hEle)->hImage_down) return FALSE;
		XDraw_GradientFill4_(hDraw, RGB(92, 200, 252), RGB(4, 151, 221), RGB(3, 117, 171), RGB(4, 151, 221), &rect, GRADIENT_FILL_RECT_V);
	}
	break;
	}

	HBRUSH  hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(6, 108, 156));
	HBRUSH  hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(143, 217, 253));
	XDraw_FrameRect_(hDraw, &rect, hBrush1);
	RECT rc1 = { 1,0,rect.right - 1,rect.bottom - 1 };
	XDraw_FrameRect_(hDraw, &rc1, hBrush2);
	//	DeleteObject(hBrush1);
	//	DeleteObject(hBrush2);

	RECT rc;
	rc.left = rect.left + 8;
	rc.top = rect.top + 5;
	rc.right = rc.left + 10;
	rc.bottom = rc.top + 2;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //�Ϻ���

	rc.left = rect.left + 8;
	rc.top = rect.top + 7;
	rc.right = rc.left + 2;
	rc.bottom = rc.top + 5;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //������

	rc.left = rect.left + 16;
	rc.top = rect.top + 7;
	rc.right = rc.left + 2;
	rc.bottom = rc.top + 5;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //������

	rc.left = rect.left + 8;
	rc.top = rect.top + 11;
	rc.right = rc.left + 10;
	rc.bottom = rc.top + 2;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //�º���

	return TRUE;
}
BOOL CALLBACK Wnd_OnBtnMinimizeDraw(HELE hEle, HDRAW hDraw)
{
	if (BUTTON(hEle)->hImage_check) return FALSE;
	if (BUTTON(hEle)->hImage_disable) return FALSE;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	window_ *pWindow = (window_*)XEle_GetHWindow(hEle);
	if (pWindow)
	{
		if (pWindow->hClose || pWindow->hMaxinize)
			rect.right++;
	}

	switch (BUTTON(hEle)->state)
	{
	case STATE_STAY:
	{
		if (BUTTON(hEle)->hImage_stay) return FALSE;
		XDraw_GradientFill4_(hDraw, RGB(143, 217, 253), RGB(58, 189, 252), RGB(39, 135, 194), RGB(58, 189, 252), &rect, GRADIENT_FILL_RECT_V);
	}
	break;
	case STATE_DOWN:
	case STATE_LEAVE:
	{
		if (BUTTON(hEle)->hImage_leave) return FALSE;
		if (BUTTON(hEle)->hImage_down) return FALSE;
		XDraw_GradientFill4_(hDraw, RGB(92, 200, 252), RGB(4, 151, 221), RGB(3, 117, 171), RGB(4, 151, 221), &rect, GRADIENT_FILL_RECT_V);
	}
	break;
	}

	HBRUSH  hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(6, 108, 156));
	HBRUSH  hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(143, 217, 253));
	XDraw_FrameRect_(hDraw, &rect, hBrush1);
	RECT rc1 = { 1,0,rect.right - 1,rect.bottom - 1 };
	XDraw_FrameRect_(hDraw, &rc1, hBrush2);
	//	DeleteObject(hBrush1);
	//	DeleteObject(hBrush2);

	RECT rc;
	rc.left = rect.left + 8;
	rc.top = rect.top + 10;
	rc.right = rc.left + 11;
	rc.bottom = rc.top + 3;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //���ƴ�����

	return TRUE;
}

BOOL CALLBACK Wnd_OnEventBtnCloseClick(HELE hEle, HELE hButton)
{
	if (hEle != hButton)
		return FALSE;

	PostMessage(XEle_GetHWnd(hButton), WM_CLOSE, 0, 0);
	return TRUE;
}

BOOL CALLBACK Wnd_OnEventBtnMaximizeClick(HELE hEle, HELE hButton)
{
	if (hEle != hButton)
		return FALSE;

	SendMessage(XEle_GetHWnd(hEle), WM_NCLBUTTONDBLCLK, HTCAPTION, 0);
	return TRUE;
}

BOOL CALLBACK Wnd_OnEventBtnMinimizeClick(HELE hEle, HELE hButton)
{
	if (hEle != hButton)
		return FALSE;

	PostMessage(XEle_GetHWnd(hButton), WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	return TRUE;
}
