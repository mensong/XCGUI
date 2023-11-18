/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#ifdef XCGUI_PLUS  //C++类支持
void WINAPI XWnd_RegisterMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---新消息机制
	BOOL bResult = FALSE;
	int index = -1; //插入位置
	int count = Array_GetCount(pWindow->hArray_msg);
	if (0 == count) //需要消息头
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

	if (bResult) //需要消息头
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

		//TODO:排序
		XArray_Add(pWindow->hArray_msg, pHeader);

	}
	else //不需要消息头
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
		else  //插入到首位
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XWnd_RegisterNCMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //注册非客户区消息
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---新消息机制
	BOOL bResult = FALSE;
	int index = -1; //插入位置
	int count = Array_GetCount(pWindow->hArray_NCmsg);
	if (0 == count) //需要消息头
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

	if (bResult) //需要消息头
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

		default:XTRACE("XWnd_RegisterNCMessage() 未知消息类型 \n"); pHeader->pFunConv = NULL; break;
		}

		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;

		pHeader->pList = pMsg;

		//TODO:排序
		XArray_Add(pWindow->hArray_NCmsg, pHeader);

	}
	else //不需要消息头
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
		else  //插入到首位
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XWnd_RegisterMsgProcEx(HWINDOW hWindow, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)	//注册窗口消息处理过程
{
	IsWindowDebug(hWindow, __FUNCTION__);
	windowProc_  *&pProcT = ((window_*)hWindow)->pWndProc;
	if (NULL == pProcT)
	{
		pProcT = (windowProc_*)malloc(sizeof(windowProc_));
		pProcT->pFun = pCallBackFun;
		pProcT->pNext = NULL;
	}
	else  //插入开始位置
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

/// @brief 创建窗口
/// @param x   窗口左上角x坐标.
/// @param y   窗口左上角y坐标.
/// @param cx  窗口宽度.
/// @param cy  窗口高度.
/// @param pTitle  窗口标题.
/// @param hWndParent  父窗口.
/// @param XCStyle    GUI库窗口样式,样式请参见宏定义.
/// @return  GUI库窗口资源句柄.
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

/// @brief 创建窗口,增强功能.
/// @param dwExStyle 窗口扩展样式.
/// @param lpClassName   窗口类名,免费版对该参数无效.
/// @param lpWindowName   窗口名.
/// @param dwStyle     窗口样式
/// @param x   窗口左上角x坐标.
/// @param y   窗口左上角y坐标.
/// @param cx  窗口宽度.
/// @param cy  窗口高度.
/// @param hWndParent  父窗口.
/// @param XCStyle     GUI库窗口样式,样式请参见宏定义.
/// @return  GUI库窗口资源句柄.
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

#ifdef XCGUI_Free_version     //免费版不可以指定窗口类名
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

	if (XCStyle & XC_SY_CENTER) //窗口居中
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
		//| WS_MAXIMIZEBOX, 屏蔽WIN7窗口移动到屏幕边上，自动最大化导致全屏错误
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

		XWnd_RegisterMsgProc(hWindow, Wnd_WindowProc);//窗口过程

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
		if (pWindow->xcStyle & XC_SY_MINIMIZE) //最小化按钮
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

/// @brief 设置窗口边框大小,注意是炫彩GUI库逻辑上的边框大小,并非系统边框大小.
/// @param hWindow  窗口资源句柄.
/// @param left  左边框大小.
/// @param top   上边框大小.
/// @param right 右边框大小.
/// @param bottom 下边框大小.
void WINAPI XWnd_SetBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom) //设置窗口边框
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->borderLeft = left;
	((window_*)hWindow)->borderTop = top;
	((window_*)hWindow)->borderRight = right;
	((window_*)hWindow)->borderBottom = bottom;
	XWnd_Adjust(hWindow);
}

/// @brief 设置窗口标题栏高度,如果不需要标题栏设置高度为0.
/// @param hWindow  窗口资源句柄.
/// @param captionHeight  标题栏高度.
void WINAPI XWnd_SetCaptionHeight(HWINDOW hWindow, int captionHeight) //设置标题栏
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->captionHeight = captionHeight;
	XWnd_Adjust(hWindow);
}

/// @brief 设置窗口图标.
/// @param hWindow  窗口资源句柄.
/// @param hIcon    图标句柄.
/// @param bBigIcon  tru大图标,FALSE小图标.
/// @return 如果失败返回0.
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

/// @brief 设置窗口图标.
/// @param hWindow  窗口资源句柄.
/// @param pFileName  图标文件.
/// @param bBigIcon  TRUE大图标,FALSE小图标.
/// @return 如果失败返回0.
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

/// @brief 获取窗口图标.
/// @param hWindow  窗口资源句柄.
/// @param bBigIcon  tru大图标,FALSE小图标.
/// @return 图标句柄,如果失败返回0.
HICON WINAPI XWnd_GetIcon(HWINDOW hWindow, BOOL bBigIcon) //获取窗口图标
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

/// @brief 设置标题栏图标显示大小.
/// @param hWindow  窗口资源句柄.
/// @param width    图标宽度.
/// @param height   图标高度.
void WINAPI XWnd_SetIconSize(HWINDOW hWindow, int width, int height)  //设置图标显示大小
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->iconSize.cx = width;
	((window_*)hWindow)->iconSize.cy = height;
}

/// @brief 最大化或还原窗口大小.
/// @param hWindow  窗口资源句柄.
/// @param bMax     TRUE最大化窗口,FALSE还原窗口大小.
void WINAPI XWnd_MaximizeWnd(HWINDOW hWindow, BOOL bMax) //最大化 还原窗口
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (bMax) //最大化窗口
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

/// @brief 判断窗口是否最大化.
/// @param hWindow  窗口资源句柄.
/// @return 如果窗口最大化返回TRUE,否则返回FALSE.
BOOL WINAPI XWnd_IsMaximizeWnd(HWINDOW hWindow)  //窗口是否最大化
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (IsZoomed(((window_*)hWindow)->hWnd))
		return  TRUE;
	else
		return FALSE;
}

/// @brief 设置定时器.
/// @param hWindow  窗口资源句柄.
/// @param nIDEvent 定时器标识符.
/// @param uElapse  间隔时间毫秒.
/// @return 定时器标识符.
UINT WINAPI XWnd_SetTimer(HWINDOW hWindow, UINT nIDEvent, UINT uElapse)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return SetTimer(((window_*)hWindow)->hWnd, nIDEvent, uElapse, NULL);
}

/// @brief 关闭定时器.
/// @param hWindow  窗口句柄.
/// @param nIDEvent 定时器标识符.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XWnd_KillTimer(HWINDOW hWindow, UINT nIDEvent)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return KillTimer(((window_*)hWindow)->hWnd, nIDEvent);
}

/// @brief 设置定时器,非系统定时器.
/// @param hWindow  窗口句柄
/// @param nIDEvent 定时器标识符.
/// @param uElapse  间隔时间毫秒.
/// @param userData 绑定数据.
/// @return 成功返回TRUE,否则相反.
UINT WINAPI XWnd_SetTimerEx(HWINDOW hWindow, UINT nIDEvent, UINT uElapse, int userData)
{
	return Timer_SetTimerWindow(hWindow, nIDEvent, uElapse, userData);
}

/// @brief 关闭定时器,非系统定时器.
/// @param hWindow  窗口句柄.
/// @param nIDEvent 定时器标识符.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XWnd_KillTimerEx(HWINDOW hWindow, UINT nIDEvent)
{
	return Timer_KillTimerWindow(nIDEvent);
}

/// @brief 设置窗口背景颜色,RGB值.
/// @param hWindow  窗口资源句柄.
/// @param color  RGB颜色值.
void WINAPI XWnd_SetBkColor(HWINDOW hWindow, COLORREF color) //设置背景颜色
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->bkColor = color;
}

/// @brief 设置窗口最小宽度.
/// @param hWindow  窗口资源句柄.
/// @param width    当窗口边框拖动时允许的最小宽度.
void WINAPI XWnd_SetMinWidth(HWINDOW hWindow, int width)  //设置窗口最小宽度
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->minWidth = width;
}

/// @brief 设置窗口最小高度.
/// @param hWindow  窗口资源句柄.
/// @param height   当拖动窗口边框时,允许窗口最小高度.
void WINAPI XWnd_SetMinHeight(HWINDOW hWindow, int height) //设置窗口最小高度
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->minHeight = height;
}

/// @brief 设置窗口圆角大小,对圆角窗口有效.
/// @param hWindow  窗口资源句柄.
/// @param size   圆角大小.
void WINAPI XWnd_SetRoundSize(HWINDOW hWindow, int size)   //设置窗口圆角大小,对圆角窗口有效
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->roundSize = size;

	RECT rect;
	GetWindowRect(WINDOW(hWindow)->hWnd, &rect);
	HRGN hrgn = CreateRoundRectRgn(0, 0, rect.right - rect.left + 1, rect.bottom - rect.top + 1, WINDOW(hWindow)->roundSize, WINDOW(hWindow)->roundSize);
	SetWindowRgn(WINDOW(hWindow)->hWnd, hrgn, TRUE);
	DeleteObject(hrgn);
}

/// @brief 重绘窗口指定区域.
/// @param hWindow  窗口资源句柄.
/// @param pRect    需要重绘的区域坐标,基于GUI库非客户区坐标系,不包含系统非客户区.
/// @param bImmediately   TRUE立即重绘,FALSE放入消息队列延迟重绘.
void WINAPI XWnd_RedrawWndRect(HWINDOW hWindow, RECT *pRect, BOOL bImmediately) //重绘窗口指定区域
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (FALSE == IsWindowVisible(((window_*)hWindow)->hWnd))
		return;

	//	if(bImmediately) //立刻重绘
	//	{
			//----新消息机制
	window_ *pWindow = (window_*)hWindow;
	//		HDC hdc=GetDC(pWindow->hWnd);
	//		if(NULL==hdc)
	//		{
	//			MessageBox(NULL,L"XWnd_RedrawWndRect()获取HDC错误",L"炫彩界面库-错误提示",0);
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
	//	}else //放入消息队列,稍后绘制
	//	{
	//		PostMessage(((window_*)hWindow)->hWnd,XWM_REDRAW,MAKELPARAM(pRect->left,pRect->top),MAKELPARAM(pRect->right,pRect->bottom));
	//	}
}

/// @brief 重绘窗口,是重绘整个窗口包含非客户.
/// @param hWindow  窗口资源句柄.
/// @param bImmediately  TRUE立即重绘,FALSE放入消息队列延迟重绘.
void WINAPI XWnd_RedrawWnd(HWINDOW hWindow, BOOL bImmediately)//重绘窗口
{
	IsWindowDebug(hWindow, __FUNCTION__);
	//	if(bImmediately) //立刻重绘
	//	{
	RECT rect;
	GetClientRect(((window_*)hWindow)->hWnd, &rect);
	XWnd_RedrawWndRect(hWindow, &rect, TRUE);
	//	}else //放入消息队列,稍后绘制
	//	{
	//		if(FALSE==IsWindowVisible(((window_*)hWindow)->hWnd))
	//			return;
	//		PostMessage(((window_*)hWindow)->hWnd,XWM_REDRAW,0,0);
	//	}
}

/// @brief 重绘指定元素.
/// @param hWindow  窗口资源句柄.
/// @param hEle   要重绘的元素句柄
/// @param pRect  重绘区域,基于窗口非客户区坐标.
void WINAPI XWnd_RedrawEleRectNC(HWINDOW hWindow, HELE hEle, RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	Wnd_RedrawEle(hWindow, hEle, pRect);
}


/// @brief 获取当前重绘区域坐标..
/// @param hWindow  窗口资源句柄.
/// @param pRect    接收重绘区域坐标
void WINAPI XWnd_GetDrawRect(HWINDOW hWindow, RECT *pRect) //获取当前绘制区域
{
	IsWindowDebug(hWindow, __FUNCTION__);
	*pRect = ((window_*)hWindow)->rcDraw;
}

/// @brief 获得拥有输入焦点的元素.
/// @param hWindow  窗口资源句柄.
HELE WINAPI XWnd_GetFocusEle(HWINDOW hWindow) //获取拥有焦点的元素
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return (HELE)((window_*)hWindow)->pFocus;
}

/// @brief 设置窗口字体..
/// @param hWindow  窗口资源句柄.
/// @param hFontX    炫彩字体句柄.
void WINAPI XWnd_SetFont(HWINDOW hWindow, HFONTX hFontX)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	Font_AddFontX(((window_*)hWindow)->hFontX, hFontX);
}

/// @brief 显示或隐藏一个窗口.
/// @param hWindow  窗口资源句柄.
/// @param nCmdShow  SW_SHOW显示窗口,SW_HIDE隐藏窗口.
/// @note 详情参见MSDN:ShowWindow()
BOOL WINAPI XWnd_ShowWindow(HWINDOW hWindow, int nCmdShow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ShowWindow(((window_*)hWindow)->hWnd, nCmdShow);
}

/// @brief 设置窗口大小位置及属性.
/// @param hWindow  窗口资源句柄.
/// @param hWndInsertAfter 详情参见MSDN.
/// @param x 详情参见MSDN.
/// @param y 详情参见MSDN.
/// @param cx 详情参见MSDN.
/// @param cy 详情参见MSDN.
/// @param uFlags 详情参见MSDN.
/// @note 失败返回0,详情参见MSDN:SetWindowPos().
BOOL WINAPI XWnd_SetWindowPos(HWINDOW hWindow, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::SetWindowPos(((window_*)hWindow)->hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
}

/// @brief 设置窗口坐标,基于屏幕坐标.
/// @param hWindow  窗口句柄.
/// @param pRect   坐标.
/// @note 失败返回0.
BOOL WINAPI XWnd_SetWindowRect(HWINDOW hWindow, in_ RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::SetWindowPos(((window_*)hWindow)->hWnd, NULL, pRect->left, pRect->top,
		pRect->right - pRect->left, pRect->bottom - pRect->top, SWP_NOZORDER);
}

/// @brief 设置窗口大小,不改变窗口位置.
/// @param hWindow  窗口句柄.
/// @param width  窗口宽度.
/// @param height 窗口高度.
/// @note 失败返回0.
BOOL WINAPI XWnd_SetWindowSize(HWINDOW hWindow, int width, int height)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::SetWindowPos(((window_*)hWindow)->hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}

/// @brief 获取窗口坐标,基于屏幕坐标.
/// @param hWindow  窗口句柄.
/// @param pRect   坐标.
/// @note 失败返回0.
BOOL WINAPI XWnd_GetWindowRect(HWINDOW hWindow, out_ RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ::GetWindowRect(((window_*)hWindow)->hWnd, pRect);
}

/// @brief 判断窗口是否显示.
/// @param hWindow  窗口句柄.
/// @note 如果窗口显示返回TRUE,否则返回FALSE.
BOOL WINAPI XWnd_IsWindowVisible(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return IsWindowVisible(((window_*)hWindow)->hWnd);
}

/// @brief 启用或关闭拖动窗口边框功能,如果窗口有边框的话.
/// @param hWindow  窗口资源句柄.
/// @param bDrag    TRUE窗口边框可以拖动,否则不可以拖动.
void WINAPI XWnd_EnableDragBorder(HWINDOW hWindow, BOOL bDrag)  //使用拖动边框
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

/// @brief 启用或关闭拖动窗口功能,即使鼠标按在客户区也能拖动窗口.
/// @param hWindow  窗口资源句柄.
/// @param bDrag    TRUE窗口可以拖动,否则不可以拖动.
void WINAPI XWnd_EnableDragWindow(HWINDOW hWindow, BOOL bDrag)  //拖动窗口
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


/// @brief 获取窗口标题栏上最小化按钮句柄.
/// @param hWindow  窗口句柄.
/// @return 窗口最小化按钮句柄.
HELE WINAPI XWnd_GetButtonMin(HWINDOW hWindow)   //最小化按钮
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return WINDOW(hWindow)->hMinimize;
}

/// @brief 获取窗口标题栏上最大化按钮句柄.
/// @param hWindow  窗口句柄.
/// @return 窗口最大化按钮句柄.
HELE WINAPI XWnd_GetButtonMax(HWINDOW hWindow)   //最大化按钮
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return WINDOW(hWindow)->hMaxinize;
}

/// @brief 获取窗口标题栏上关闭按钮句柄.
/// @param hWindow  窗口句柄.
/// @return 窗口关闭按钮句柄.
HELE WINAPI XWnd_GetButtonClose(HWINDOW hWindow) //关闭按钮
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return WINDOW(hWindow)->hClose;
}

/// @brief 窗口启用或关闭最小化按钮.
/// @param hWindow  窗口句柄.
/// @param bEnable  值为TRUE启用,否则相反.
/// @param bRedraw  值为TRUE重绘,否则相反.
void WINAPI XWnd_EnableMinButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw) //启用最小化按钮
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

/// @brief 窗口启用或关闭最大化按钮.
/// @param hWindow  窗口句柄.
/// @param bEnable  值为TRUE启用,否则相反.
/// @param bRedraw  值为TRUE重绘,否则相反.
void WINAPI XWnd_EnableMaxButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw) //启用最大化按钮
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

/// @brief 窗口启用或关闭关闭按钮.
/// @param hWindow  窗口句柄.
/// @param bEnable  值为TRUE启用,否则相反.
/// @param bRedraw  值为TRUE重绘,否则相反.
void WINAPI XWnd_EnableCloseButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw)  //启用关闭按钮
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

/// @brief 启用或关闭窗口圆角.
/// @param hWindow  窗口句柄.
/// @param bEnable  值为TRUE启用,否则相反.
/// @param bRedraw  值为TRUE重绘,否则相反.
void WINAPI XWnd_EnableRound(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw) //圆角功能的启用与关闭
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

/// @brief 获取顶级客户区元素数量,不包含窗口子元素的子元素.
/// @param hWindow  窗口句柄.
/// @return 返回元素数量.
int  WINAPI XWnd_GetChildEleCount(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return XArray_GetCount(WINDOW(hWindow)->hArrayEle);
}

/// @brief 获取顶级非客户区元素数量,不包含窗口子元素的子元素.
/// @param hWindow  窗口句柄.
/// @return 返回元素数量.
int  WINAPI XWnd_GetChildEleCountNC(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return XArray_GetCount(WINDOW(hWindow)->hArrayEleNC);
}

/// @brief 获取指定索引子元素,窗口客户区.
/// @param hWindow  窗口句柄.
/// @param index  子元素位置索引.
/// @return 子元素句柄.
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

/// @brief 获取指定索引子元素,窗口非客户区.
/// @param hWindow  窗口句柄.
/// @param index  子元素位置索引.
/// @return 子元素句柄.
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

/// @brief 设置透明窗口,同时可以通过该函数关闭透明窗口.
/// @param hWindow  窗口句柄.
/// @param flag  窗口透明标识.
void WINAPI XWnd_SetTransparentFlag(HWINDOW hWindow, int flag)  //设置透明窗口
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = WINDOW(hWindow);

	if (pWindow->transparentFlag == flag) return;

	switch (flag)
	{
	case XC_WIND_TRANSPARENT_NO:
	{
		//关闭窗口分层样式
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
	case XC_WIND_TRANSPARENT_SHAPED: //透明窗口,带透明通道,异型.
	{
		//启用窗口分层样式
		LONG_PTR dwExStyle = GetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) != 0x80000) //WS_EX_LAYERED
			SetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);
		pWindow->transparentFlag = flag;
		XWnd_RedrawWnd(hWindow);
	}break;
	case XC_WIND_TRANSPARENT_SHADOW: //阴影窗口,带透明通道,边框阴影,窗口透明或半透明.
	{
		//启用窗口分层样式
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
	case XC_WIND_TRANSPARENT_SIMPLE: //透明窗口,不带透明通道,指定半透明度,指定透明色.
	{
		//启用窗口分层样式
		LONG_PTR dwExStyle = GetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) != 0x80000) //WS_EX_LAYERED
			SetWindowLongPtr(pWindow->hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);

		pWindow->transparentFlag = flag;
		SetLayeredWindowAttributes(pWindow->hWnd, pWindow->transparentColor, pWindow->transparentAlpha, LWA_COLORKEY | LWA_ALPHA);
	}break;
	case XC_WIND_TRANSPARENT_WIN7:   //WIN7玻璃窗口,需要WIN7开启特效.
		break;
	default: break;
	}
}

/// @brief 设置透明窗口的透明度,设置后调用重绘窗口API来更新.
/// @param hWindow  窗口句柄.
/// @param alpha    窗口透明度,范围0-255之间,0透明,255不透明.
void WINAPI XWnd_SetTransparentAlpha(HWINDOW hWindow, BYTE alpha)  //设置窗口透明度
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->transparentAlpha = alpha;

	if (XC_WIND_TRANSPARENT_SIMPLE == WINDOW(hWindow)->transparentFlag)
		SetLayeredWindowAttributes(WINDOW(hWindow)->hWnd, RGB(255, 255, 255), WINDOW(hWindow)->transparentAlpha, LWA_COLORKEY | LWA_ALPHA);
}

/// @brief 设置透明窗口的透明色.
/// @param hWindow  窗口句柄.
/// @param color    窗口透明色.
void WINAPI XWnd_SetTransparentColor(HWINDOW hWindow, COLORREF color) //设置窗口透明色
{
	IsWindowDebug(hWindow, __FUNCTION__);
	WINDOW(hWindow)->transparentColor = color;
}

/// @brief 设置窗口背景图片,从文件中加载图片.
/// @param hWindow  窗口句柄.
/// @param hImage   图片句柄.
void WINAPI XWnd_SetImage(HWINDOW hWindow, HIMAGE hImage)    //客户区图片
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImage_client, hImage);
}

/// @brief 设置窗口非客户区贴图.
/// @param hWindow  窗口句柄.
/// @param hImage   图片句柄.
void WINAPI XWnd_SetImageNC(HWINDOW hWindow, HIMAGE hImage)  //非客户区窗口图片
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageNC, hImage);
}

/// @brief 设置窗口标题栏贴图.
/// @param hWindow  窗口句柄.
/// @param hImage   图片句柄.
void WINAPI XWnd_SetImageCaption(HWINDOW hWindow, HIMAGE hImage)   //标题栏图片
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageCaption, hImage);
}

/// @brief 设置窗口左侧边框贴图.
/// @param hWindow  窗口句柄.
/// @param hImage   图片句柄.
void WINAPI XWnd_SetImageBorderLeft(HWINDOW hWindow, HIMAGE hImage)    //边框图片
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageLeft, hImage);
}

/// @brief 设置窗口右侧边框贴图.
/// @param hWindow  窗口句柄.
/// @param hImage   图片句柄.
void WINAPI XWnd_SetImageBorderRight(HWINDOW hWindow, HIMAGE hImage)    //边框图片
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageRight, hImage);
}

/// @brief 设置窗口底部边框贴图.
/// @param hWindow  窗口句柄.
/// @param hImage   图片句柄.
void WINAPI XWnd_SetImageBorderBottom(HWINDOW hWindow, HIMAGE hImage)    //边框图片
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(WINDOW(hWindow)->hImageBottom, hImage);
}

/// @brief 启用窗口边框描边,窗口边框的内侧.
/// @param hWindow  窗口句柄.
/// @param bStroke  如果值为TRUE描边,否则相反.
void WINAPI XWnd_EnableBorderStrokeInner(HWINDOW hWindow, BOOL bStroke) //启用绘制描边
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bStroke)
		((window_*)hWindow)->chartletStyle |= XC_CS_STROKE_INNER;
	else
		((window_*)hWindow)->chartletStyle &= ~XC_CS_STROKE_INNER;
}

/// @brief 启用窗口边框描边,窗口边框的外侧.
/// @param hWindow  窗口句柄.
/// @param bStroke  如果值为TRUE描边,否则相反.
void WINAPI XWnd_EnableBorderStrokeOuter(HWINDOW hWindow, BOOL bStroke) //启用绘制描边
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (bStroke)
		((window_*)hWindow)->chartletStyle |= XC_CS_STROKE_OUTER;
	else
		((window_*)hWindow)->chartletStyle &= ~XC_CS_STROKE_OUTER;
}

/// @brief 设置窗口边框描边颜色,窗口边框的内侧.
/// @param hWindow  窗口句柄.
/// @param color1   RGB颜色,窗口的内侧,边框的外侧位置.
/// @param color2   RGB颜色,窗口的内侧,边框的内侧位置.
void WINAPI XWnd_SetBorderStrokeInnerColor(HWINDOW hWindow, COLORREF color1, COLORREF color2) //设置描边颜色
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->strokeInner_color1 = color1;
	((window_*)hWindow)->strokeInner_color2 = color2;
}

/// @brief 设置窗口边框外侧描边颜色.
/// @param hWindow  窗口句柄.
/// @param color1   RGB颜色,窗口的外侧,边框的外侧位置.
/// @param color2   RGB颜色,窗口的外侧,边框的内侧位置.
void WINAPI XWnd_SetBorderStrokeOuterColor(HWINDOW hWindow, COLORREF color1, COLORREF color2) //设置描边颜色
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->strokeOuter_color1 = color1;
	((window_*)hWindow)->strokeOuter_color2 = color2;
}
/// @brief 关闭窗口.
/// @param hWindow  窗口句柄.
void WINAPI XWnd_CloseWindow(HWINDOW hWindow)  //关闭窗口
{
	IsWindowDebug(hWindow, __FUNCTION__);
	::PostMessage(((window_*)hWindow)->hWnd, WM_CLOSE, 0, 0);
}

/// @brief 创建插入符.
/// @param hWindow  窗口句柄.
/// @param hEle   元素句柄.
/// @param width  宽度.
/// @param height 高度.
void WINAPI XWnd_CreateCaret(HWINDOW hWindow, HELE hEle, int width, int height) //创建插入符
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretBitmap)
	{
		XTRACE("edit 插入符错误 \n");
		return;
	}

	//插入符
	pWindow->hCaretBitmap = XDraw_CreateDIBSection(NULL, width, height);

	pWindow->bCaretShow = FALSE;
	pWindow->hCaretEle = hEle;
	pWindow->caretWidth = width;
	pWindow->caretHeight = height;
	XWnd_SetTimer(hWindow, IDT_CARET, 500);
}

/// @brief 设置插入符大小.
/// @param hWindow  窗口句柄.
/// @param width    插入符宽度.
/// @param height   插入符高度.
void WINAPI XWnd_SetCaretSize(HWINDOW hWindow, int width, int height) //设置插入符大小
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;

	if (width == pWindow->caretWidth && height == pWindow->caretHeight)
		return;

	if (pWindow->hCaretBitmap)
		DeleteObject(pWindow->hCaretBitmap);

	if (pWindow->bCaretShow && pWindow->bCaretErase) //需要擦出插入符
	{
		Wnd_EraseCaret(hWindow); //擦出
	}

	pWindow->hCaretBitmap = XDraw_CreateDIBSection(NULL, width, height);
	pWindow->caretWidth = width;
	pWindow->caretHeight = height;
	Wnd_GetCaretBk(hWindow); //获取插入符背景
}

void Wnd_GetCaretBk(HWINDOW hWindow) //获取插入符背景
{
	window_ *pWindow = (window_*)hWindow;
	//获取新位置背景
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

/// @brief 设置插入符位置,坐标基于插入符所在的元素.
/// @param hWindow  窗口句柄.
/// @param x  插入符x坐标.
/// @param y  插入符y坐标.
void WINAPI XWnd_SetCaretPos(HWINDOW hWindow, int x, int y) //设置插入符位置
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle)
	{
		if (pWindow->bCaretShow && pWindow->bCaretErase) //需要擦出插入符
		{
			Wnd_EraseCaret(hWindow); //擦出
		}

		//新位置
		pWindow->caretPt.x = x;
		pWindow->caretPt.y = y;
		Wnd_GetCaretBk(hWindow); //获取插入符背景
		pWindow->bCaretErase = TRUE;
	}
}

/// @brief 设置插入符位置及大小,坐标基于插入符所在的元素.
/// @param hWindow  窗口句柄.
/// @param x  插入符x坐标.
/// @param y  插入符y坐标.
/// @param width  插入符宽度.
/// @param height 插入符高度 .
void WINAPI XWnd_SetCaretPosEx(HWINDOW hWindow, int x, int y, int width, int height) //设置插入符位置
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle)
	{
		if (pWindow->bCaretShow && pWindow->bCaretErase) //需要擦出插入符
		{
			Wnd_EraseCaret(hWindow); //擦出
		}

		//修改插入符大小
		if (width != pWindow->caretWidth || height != pWindow->caretHeight)
		{
			if (pWindow->hCaretBitmap)
				DeleteObject(pWindow->hCaretBitmap);

			pWindow->hCaretBitmap = XDraw_CreateDIBSection(NULL, width, height);
			pWindow->caretWidth = width;
			pWindow->caretHeight = height;
		}

		//新位置
		pWindow->caretPt.x = x;
		pWindow->caretPt.y = y;
		Wnd_GetCaretBk(hWindow); //获取插入符背景
		pWindow->bCaretErase = TRUE;
	}
}

/// @brief 设置插入符颜色.
/// @param hWindow  窗口句柄.
/// @param color  插入符颜色.
void WINAPI XWnd_SetCaretColor(HWINDOW hWindow, COLORREF color) //设置插入符颜色
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->caretColor = color;
}

/// @brief 显示插入符.
/// @param hWindow  窗口句柄.
/// @param bShow  TRUE显示插入符,否则隐藏插入符.
void WINAPI XWnd_ShowCaret(HWINDOW hWindow, BOOL bShow)  //显示插入符
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (NULL == pWindow->hCaretEle)
		return;

	if (bShow) //显示插入符
	{
		Wnd_GetCaretBk(hWindow);
		pWindow->bCaretErase = TRUE;
		pWindow->bCaretShow = TRUE;
	}
	else //隐藏插入符
	{
		if (pWindow->bCaretErase) //需要擦出插入符
		{
			Wnd_EraseCaret(hWindow); //擦出
			pWindow->bCaretErase = FALSE;
		}
		pWindow->bCaretShow = FALSE;
	}
}

/// @brief 销毁插入符.
/// @param hWindow  窗口句柄.
void WINAPI XWnd_DestroyCaret(HWINDOW hWindow) //销毁插入符
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->hCaretEle)
	{
		//-----------------------------------------
		if (pWindow->bCaretShow && pWindow->bCaretErase) //需要擦出插入符
		{
			Wnd_EraseCaret(hWindow); //擦出
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

void Wnd_DrawCaret(HWINDOW hWindow) //处理绘制插入符
{
	window_ *pWindow = (window_*)hWindow;
	if (FALSE == IsWindowVisible(pWindow->hWnd))
		return;

	if (NULL == pWindow->hCaretEle || FALSE == pWindow->bCaretShow)
		return;
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //透明窗口
	{
		Wnd_DrawCaretTransparent(hWindow);
		return;
	}

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);


	RECT rcCare; //插入符坐标
	rcCare.left = pt.x;
	rcCare.top = pt.y;
	rcCare.right = pt.x + pWindow->caretWidth;
	rcCare.bottom = pt.y + pWindow->caretHeight;

	//检查是否超出范围
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

	if (pWindow->bCaretErase) //擦出
	{
		//	XTRACE("插入符 show \n");

		RECT rc = { pt.x,pt.y,pt.x + pWindow->caretWidth,pt.y + pWindow->caretHeight };
		HBRUSH hBrush = CreateSolidBrush(pWindow->caretColor);
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hBrush);
	}
	else //绘制
	{
		//	XTRACE("插入符 hide \n");

		BitBlt(hdc, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDC);
	ReleaseDC(pWindow->hWnd, hdc);
}

void Wnd_DrawCaretMenDC(HWINDOW hWindow, HDRAW hDraw) //处理绘制插入符到内存DC
{
	window_ *pWindow = (window_*)hWindow;
	if (FALSE == IsWindowVisible(pWindow->hWnd))
		return;

	if (NULL == pWindow->hCaretEle || FALSE == pWindow->bCaretShow)
		return;

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //透明窗口
	{
		Wnd_DrawCaretTransparentMemDC(hWindow, hDraw);
		return;
	}

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	RECT rcCare; //插入符坐标
	rcCare.left = pt.x;
	rcCare.top = pt.y;
	rcCare.right = pt.x + pWindow->caretWidth;
	rcCare.bottom = pt.y + pWindow->caretHeight;

	//检查是否超出范围
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

	if (pWindow->bCaretErase) //擦出
	{
		//	XTRACE("插入符 show \n");

		RECT rc = { pt.x,pt.y,pt.x + pWindow->caretWidth,pt.y + pWindow->caretHeight };
		HBRUSH hBrush = CreateSolidBrush(pWindow->caretColor);
		XDraw_FillRect_(hDraw, &rc, hBrush);
		DeleteObject(hBrush);
	}
	else //绘制
	{
		//	XTRACE("插入符 hide \n");

		XDraw_BitBlt_(hDraw, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDC);
}

void Wnd_EraseCaret(HWINDOW hWindow) //擦出插入符
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

void Wnd_DrawCaretTransparent(HWINDOW hWindow) //处理绘制插入符,当窗口透明时
{
	window_ *pWindow = (window_*)hWindow;

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	//检查是否超出父视图
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

	//拷贝重绘内容区域
	HDC memDC = CreateCompatibleDC(NULL);         //创建背静DC 窗口 (包含非客户区)
	SelectObject(memDC, pWindow->hBtimap);

	HDC hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, pWindow->hCaretBitmap);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
	{
		pt.x += XC_WIND_SHADOW_SIZE;
		pt.y += XC_WIND_SHADOW_SIZE;
	}

	if (pWindow->bCaretErase) //擦出
	{
		Graphics graphics(memDC);
		SolidBrush blackBrush(Color(255, GetRValue(pWindow->caretColor), GetGValue(pWindow->caretColor), GetBValue(pWindow->caretColor)));
		Rect fillRect(pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight);
		graphics.FillRectangle(&blackBrush, fillRect);

		//pWindow->bCaretErase=FALSE;
	}
	else //绘制
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

void Wnd_DrawCaretTransparentMemDC(HWINDOW hWindow, HDRAW hDraw) //处理绘制插入符到内存DC
{
	window_ *pWindow = (window_*)hWindow;

	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);

	//检查是否超出父视图
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

	if (pWindow->bCaretErase) //擦出
	{
		XTRACE("插入符 show \n");

		HDC hdc = XDraw_GetHDC_(hDraw);
		int posx = 0;
		int posy = 0;
		XDraw_GetOffset_(hDraw, &posx, &posy);

		Graphics graphics(hdc);
		SolidBrush blackBrush(Color(255, GetRValue(pWindow->caretColor), GetGValue(pWindow->caretColor), GetBValue(pWindow->caretColor)));
		Rect fillRect(pt.x + posx, pt.y + posy, pWindow->caretWidth, pWindow->caretHeight);
		graphics.FillRectangle(&blackBrush, fillRect);

	}
	else //绘制
	{
		XTRACE("插入符 hide \n");

		XDraw_BitBlt_(hDraw, pt.x, pt.y, pWindow->caretWidth, pWindow->caretHeight, hMemDC, 0, 0, SRCCOPY);
	}

	DeleteDC(hMemDC);
}

/// @brief 获取窗口客户区坐标,左上角(0,0).
/// @param hWindow  窗口句柄.
/// @param pRect    接收窗口客户区坐标.
BOOL WINAPI XWnd_GetClientRect(HWINDOW hWindow, RECT *pRect) //获取客户区坐标
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

/// @brief 获取窗口非客户区大小,基于非客户区坐标系.
/// @param hWindow  窗口句柄.
/// @param pRect    接收窗口非客户区大小坐标.
void WINAPI XWnd_GetNCClientRect(HWINDOW hWindow, RECT *pRect)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = (window_*)hWindow;
	GetClientRect(pWindow->hWnd, pRect);
}

/// @brief 获取窗口左边框宽度.
/// @param hWindow  窗口句柄.
/// @return 客户区左间距.
int WINAPI XWnd_GetClientLeft(HWINDOW hWindow) //客户区左间距
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->borderLeft;
}

/// @brief 获取窗口客户区右间距.
/// @param hWindow  窗口句柄.
/// @return 客户区右间距.
int WINAPI XWnd_GetClientRight(HWINDOW hWindow) //客户区右间距
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->borderRight;
}

/// @brief 获取窗口客户区下间距.
/// @param hWindow  窗口句柄.
/// @return 客户区下间距.
int WINAPI XWnd_GetClientBottom(HWINDOW hWindow) //客户区下间距
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->borderBottom;
}

/// @brief 获取窗口客户区上间距.表示客户区顶部与窗口顶部距离.
/// @param hWindow  窗口句柄.
/// @return 客户区上间距.
int WINAPI XWnd_GetClientTop(HWINDOW hWindow)  //客户区上间距
{
	IsWindowDebug(hWindow, __FUNCTION__);

	int height = XWnd_GetCaptionHeight(hWindow);

	//菜单条
	if (((window_*)hWindow)->hMenuBar)
	{
		RECT rc;
		XEle_GetClientRect(((window_*)hWindow)->hMenuBar, &rc);
		height += rc.bottom;
	}
	//工具条
	if (((window_*)hWindow)->hToolBar)
	{
		RECT rc;
		XEle_GetClientRect(((window_*)hWindow)->hToolBar, &rc);
		height += rc.bottom;
	}
	return height;
}

/// @brief 获取标题栏高度,不包含工具条和菜单条的高度.
/// @param hWindow  窗口句柄.
/// @return 标题栏高度.
int WINAPI XWnd_GetCaptionHeight(HWINDOW hWindow) //获取标题栏高度
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (((window_*)hWindow)->captionHeight > 0)
		return ((window_*)hWindow)->captionHeight;
	else
		return ((window_*)hWindow)->borderTop;
}

/// @brief 窗口非客户区坐标转换到客户区坐标.
/// @param hWindow  窗口句柄.
/// @param pRect  输入非客户区坐标,转换为客户区坐标输出.
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

/// @brief 窗口非客户区点转换到客户区坐标点.
/// @param hWindow  窗口句柄.
/// @param pPt    输入窗口非客户区坐标点,转换到客户区坐标点输出.
void WINAPI XWnd_WindowToClientPt(HWINDOW hWindow, POINT *pPt)
{
	IsWindowDebug(hWindow, __FUNCTION__);

	pPt->y -= XWnd_GetClientTop(hWindow);
	pPt->x -= ((window_*)hWindow)->borderLeft;
}

/// @brief 窗口绑定用户数据
/// @param hWindow  窗口句柄.
/// @param data   用户数据.
void WINAPI XWnd_SetUserData(HWINDOW hWindow, int data)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	((window_*)hWindow)->userData = data;
}

/// @brief 窗口获取绑定的用户数据
/// @param hWindow  窗口句柄.
/// @return data   用户数据.
int  WINAPI XWnd_GetUserData(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return ((window_*)hWindow)->userData;
}

//窗口处理过程
BOOL CALLBACK Wnd_WindowProc(HWINDOW hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	//处理系统绘制窗口边框
	//	if( WM_NCACTIVATE==message)
	//		XWnd_RedrawWnd(hWindow);

	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	//TODO:是否有回调函数
	if (XWM_EVENT_ALL == message)
	{
		if (wParam < EVENT_LIST_SIZE && g_eventList[wParam].bEvent)
		{
			if (g_eventList[wParam].hEle && (XC_ELE == *(UINT*)g_eventList[wParam].hEle)) //确保元素句柄有效
			{
				Ele_EventDispatch(g_eventList[wParam].hEle, g_eventList[wParam].type, g_eventList[wParam].wParam, g_eventList[wParam].lParam);
			}
			g_eventList[wParam].bEvent = FALSE;
			//XTRACE("处理:  队列(%d),事件(%d)\n",wParam,g_eventList[wParam].type);
			return TRUE;
		}
		XTRACE("未处理事件: 队列(%d),事件(%d)\n", wParam, g_eventList[wParam].type);
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
			//XTRACE("Wnd_OnDrawT() 元素 ...\n");
			Wnd_PaintEle2(hWindow, hEle, hdc, &rect);

		}
		else  //绘制窗口
		{
			int count = Array_GetCount(pWindow->hArray_msg);
			for (int i = 0; i < count; i++)
			{
				if (WM_PAINT == ((windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i))->message)
				{
					//XTRACE("Wnd_OnDrawT()  窗口...\n");
					Wnd_DrawWindowHandle2(hWindow, (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i), &rect, hdc);
					break;
				}
			}
		}
		ReleaseDC(pWindow->hWnd, hdc);
	}

	return TRUE;
}

BOOL Wnd_NCWindowProc(HWINDOW hWindow, UINT NCmessage, WPARAM wParam, LPARAM lParam)  //非客户区消息调度
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

//绘制窗口
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

	if (cx < 1 || cy < 1) return TRUE; //不需要绘制

	XDraw_HImageSuper_(hDraw, pWindow->hImage_client, &rect);
	return TRUE;
}

BOOL CALLBACK Wnd_OnDestroy(HWINDOW hWindow)
{
	return TRUE;
}

BOOL CALLBACK Wnd_OnNCDestroy(HWINDOW hWindow) //释放内存
{
	if (0 == Wnd_GetWindowCount())
		PostQuitMessage(0);

	window_ *pWindow = (window_*)hWindow;
	//释放成员数据
	int count = Array_GetCount(pWindow->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		XEle_Destroy((HELE)Array_GetAtEle(pWindow->hArrayEle, 0)); //析构子元素
	}
	count = Array_GetCount(pWindow->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		XEle_Destroy((HELE)Array_GetAtEle(pWindow->hArrayEleNC, 0)); //析构子元素
	}
	XArray_Destroy(pWindow->hArrayEle); //子元素列表
	XArray_Destroy(pWindow->hArrayEleNC);//子元素列表,非客户区
	pWindow->hArrayEle = NULL;
	pWindow->hArrayEleNC = NULL;

	//窗口消息处理过程链表
	windowProc_ *pProc = pWindow->pWndProc;
	void *pDel = NULL;
	while (pProc)
	{
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		if (pProc->pClass_Fun_Info) free(pProc->pClass_Fun_Info);
#endif
		pDel = pProc;
		pProc = pProc->pNext;
		free(pDel);
	}
	pWindow->pWndProc = NULL;
	//////////////////////释放消息表

	//消息数组表
	int Array_msg_count = Array_GetCount(pWindow->hArray_msg);
	for (int i = 0; i < Array_msg_count; i++)
	{
		windowMsg_Header_ *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, i);
		windowMsg_ *pMsg = pHeader->pList;
		windowMsg_ *pDel = NULL;
		while (pMsg)
		{
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			if (pMsg->pClass_Fun_Info) free(pMsg->pClass_Fun_Info);
#endif
			pDel = pMsg;
			pMsg = pMsg->pNext;
			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pWindow->hArray_msg);

	//非客户区消息数组表
	int Array_event_count = Array_GetCount(pWindow->hArray_NCmsg);
	for (int i = 0; i < Array_event_count; i++)
	{
		windowMsg_Header_ *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, i);
		windowMsg_ *pEvent = pHeader->pList;
		windowMsg_ *pDel = NULL;
		while (pEvent)
		{
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			if (pEvent->pClass_Fun_Info) free(pEvent->pClass_Fun_Info);
#endif
			pDel = pEvent;
			pEvent = pEvent->pNext;
			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pWindow->hArray_NCmsg);

	//贴图
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

/// @brief 窗口注册消息处理函数
/// @param hWindow 窗口句柄
/// @param message 窗口消息类型.
/// @param pFun    处理消息函数名
void WINAPI XWnd_RegisterMessage(HWINDOW hWindow, int message, void *pFun)  //窗口注册消息处理函数
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---新消息机制
	BOOL bResult = FALSE;
	int index = -1; //插入位置
	int count = Array_GetCount(pWindow->hArray_msg);
	if (0 == count) //需要消息头
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

	if (bResult) //需要消息头
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
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		pMsg->pClass_Fun_Info = NULL;
#endif
		pHeader->pList = pMsg;

		//TODO:排序
		XArray_Add(pWindow->hArray_msg, pHeader);

	}
	else //不需要消息头
	{
		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		pMsg->pClass_Fun_Info = NULL;
#endif
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_msg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //插入到首位
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

/// @brief 注册窗口非客户区消息,注意这里的非客户区是GUI库逻辑上的非客户区.
/// @param hWindow 窗口句柄
/// @param message 窗口消息类型.
/// @param pFun    处理消息函数名
void WINAPI XWnd_RegisterNCMessage(HWINDOW hWindow, int message, void *pFun)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	window_ *pWindow = ((window_*)hWindow);

	//---新消息机制
	BOOL bResult = FALSE;
	int index = -1; //插入位置
	int count = Array_GetCount(pWindow->hArray_NCmsg);
	if (0 == count) //需要消息头
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

	if (bResult) //需要消息头
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

		default:XTRACE("XWnd_RegisterNCMessage() 未知消息类型 \n"); pHeader->pFunConv = NULL; break;
		}

		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		pMsg->pClass_Fun_Info = NULL;
#endif
		pHeader->pList = pMsg;

		//TODO:排序
		XArray_Add(pWindow->hArray_NCmsg, pHeader);

	}
	else //不需要消息头
	{
		windowMsg_ *pMsg = (windowMsg_*)malloc(sizeof(windowMsg_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		pMsg->pClass_Fun_Info = NULL;
#endif
		windowMsg_Header_  *pHeader = (windowMsg_Header_*)Array_GetAt(pWindow->hArray_NCmsg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //插入到首位
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

/// @brief 注册窗口消息处理过程,可以在这里拦截所有消息.
/// @param hWindow 窗口句柄
/// @param pFun    处理消息函数名,类型如下
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
	else  //插入开始位置
	{
		windowProc_ *pNew = (windowProc_*)malloc(sizeof(windowProc_));
		pNew->pNext = pProcT;
		pProcT = pNew;
		pProcT->pFun = pFun;
	}
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
	pProcT->pClass_Fun_Info = NULL;
#endif
}

/// @brief 添加元素到窗口客户区,如果添加到非客户区请使用函数 @ref XWnd_AddEleNC.
/// @param hWindow 窗口句柄
/// @param hEle    添加的元素资源句柄.
void WINAPI XWnd_AddEle(HWINDOW hWindow, HELE hEle)
{
#ifdef _DEBUG
	IsWindowDebug(hWindow, __FUNCTION__);
	IsEleDebug(hEle, __FUNCTION__);
	//检测是否已有父元素
	if (((ele_*)hEle)->pParentEle || ((ele_*)hEle)->pWindow)
	{
		MessageBox(NULL, L"XWnd_AddEle()重复添加元素,该元素已经有父元素或窗口,请先将移除!", L"炫彩界面库-错误提示!", MB_OK);
		exit(0);
	}
	//判断元素是否重复添加
	int count = Array_GetCount(((window_*)hWindow)->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEle, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() 重复添加元素", L"炫彩界面库-错误提示!", MB_OK);
			exit(0);
		}
	}
	count = Array_GetCount(((window_*)hWindow)->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEleNC, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() 重复添加元素", L"炫彩界面库-错误提示!", MB_OK);
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

/// @brief 添加元素到窗口非客户区.
/// @param hWindow 窗口句柄
/// @param hEle    添加的元素资源句柄.
void WINAPI XWnd_AddEleNC(HWINDOW hWindow, HELE hEle) //添加到非客户区
{
#ifdef _DEBUG
	IsWindowDebug(hWindow, __FUNCTION__);
	IsEleDebug(hEle, __FUNCTION__);
	//检测是否已有父元素
	if (((ele_*)hEle)->pParentEle || ((ele_*)hEle)->pWindow)
	{
		MessageBox(NULL, L"XWnd_AddEle()重复添加元素,该元素已经有父元素或窗口,请先将移除!", L"炫彩界面库-错误提示!", MB_OK);
		exit(0);
	}
	//判断元素是否重复添加
	int count = Array_GetCount(((window_*)hWindow)->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEle, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() 重复添加元素", L"炫彩界面库-错误提示!", MB_OK);
			exit(0);
		}
	}
	count = Array_GetCount(((window_*)hWindow)->hArrayEleNC);
	for (int i = 0; i < count; i++)
	{
		if (hEle == Array_GetAt(((window_*)hWindow)->hArrayEleNC, i))
		{
			MessageBox(NULL, L"XWnd_AddEle() 重复添加元素", L"炫彩界面库-错误提示!", MB_OK);
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

/// @brief 添加菜单条到窗口的非客户区,当窗口大小改变时,自动调整菜单条大小.
/// 如果想添加到窗口客户区,请使用 @ref XWnd_AddEle 函数,如果你创建它时,传递了窗口句柄,将自动添加到窗口的非客户区.
/// @param hWindow 窗口句柄
/// @param hEle    菜单条句柄.
void WINAPI XWnd_AddMenuBar(HWINDOW hWindow, HELE hEle) //添加工具条
{
	IsWindowDebug(hWindow, __FUNCTION__);
	IsMenuBarDebug(hEle, __FUNCTION__);

	if (((window_*)hWindow)->hMenuBar)
	{
		XMessageBox(hWindow, L"重复添加工具条");
		return;
	}
	XWnd_AddEleNC(hWindow, hEle);
	((window_*)hWindow)->hMenuBar = hEle;

	XWnd_Adjust(hWindow);
}

/// @brief 添加工具条到窗口的非客户区,当窗口大小改变时,自动调整工具条的大小.
/// 如果想添加到窗口的客户区,请使用 @ref XWnd_AddEle 函数,如果你创建它时,传递了窗口句柄,将自动添加到窗口的非客户区.
/// @param hWindow 窗口句柄
/// @param hEle    工具条句柄.
void WINAPI XWnd_AddToolBar(HWINDOW hWindow, HELE hEle)  //添加工具条
{
	IsWindowDebug(hWindow, __FUNCTION__);
	IsToolBarDebug(hEle, __FUNCTION__);

	if (((window_*)hWindow)->hToolBar)
	{
		XMessageBox(hWindow, L"重复添加工具条");
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

/// @brief 调整窗口布局.
/// @param hWindow 窗口句柄.
void WINAPI XWnd_Adjust(HWINDOW hWindow)  //调整窗口布局
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

	//菜单条
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
	//状态条
}

/// @brief 获取窗口句柄HWND.
/// @param hWindow 窗口句柄.
/// @return 窗口HWND句柄.
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

/// @brief 通过ID获取子元素句柄.
/// @param hWindow 窗口句柄.
/// @param eleID   子元素ID.
/// @return DI号对应的元素句柄.
HELE WINAPI XWnd_GetEle(HWINDOW hWindow, int eleID) //通过ID获取元素句柄
{
	IsWindowDebug(hWindow, __FUNCTION__);

	window_ *pWindow = (window_*)hWindow;
	ele_ *pEle = NULL;

	//客户区
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

	//非客户区
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

/// @brief 获取窗口标题栏文本.
/// @param hWindow 窗口句柄.
/// @param pOut   接收文本内容的缓冲区.
/// @param len    缓冲区长度.
/// @return 如果函数成功，返回值是复制的字符串长度，不包括空终止字符,如果窗口没有标题栏文本，或窗口或句柄无效，返回值为零.
int WINAPI XWnd_GetWindowText(HWINDOW hWindow, wchar_t *pOut, int len)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	return GetWindowText(((window_*)hWindow)->hWnd, pOut, len);
}

/// @brief 设置窗口标题栏文本.
/// @param hWindow 窗口句柄.
/// @param pText   文本内容.
/// @return   成功返回TRUE,否则相反.
BOOL WINAPI XWnd_SetWindowText(HWINDOW hWindow, wchar_t *pText)
{
	IsWindowDebug(hWindow, __FUNCTION__);
	if (SetWindowText(((window_*)hWindow)->hWnd, pText))
		return TRUE;
	return FALSE;
}

///@}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

//pRect: 非客户区坐标
void  Wnd_DrawWindowHandle(HWINDOW hWindow, RECT *pRect)
{
	if (FALSE == IsWindowVisible(((window_*)hWindow)->hWnd))
		return;

	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	Wnd_DrawWindow_Optimization(hWindow, pRect); //优化绘制
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);

	return;
}

void Wnd_DrawWindow_Optimization(HWINDOW hWindow, RECT *pRect)
{
	window_ *pWindow = (window_*)hWindow;
	//先前为空
	if (FALSE == pWindow->drawWindow.bValid)
	{
		pWindow->drawWindow.rect = *pRect;
		pWindow->drawWindow.bValid = TRUE;
		pWindow->drawWindow.hEle = NULL;
		//XTRACE("Wnd_DrawWindow_Optimization() 先前为空 ... \n");
		return;
	}

	//先前为重绘元素
	if (pWindow->drawWindow.hEle)
	{
		RECT rect;
		XEle_GetNCWndRect(pWindow->drawWindow.hEle, &rect);

		RECT rcDest;
		XC_CombineRect(&rcDest, &rect, pRect);
		pWindow->drawWindow.rect = rcDest;
		pWindow->drawWindow.hEle = NULL;
		//XTRACE("Wnd_DrawWindow_Optimization() 先前为重绘元素 ... \n");
		return;
	}

	//先前为重绘窗口
	{
		RECT rcDest;
		XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
		pWindow->drawWindow.rect = rcDest;
		//XTRACE("Wnd_DrawWindow_Optimization() 先前为重绘窗口 ... \n");
	}
}

void Wnd_DrawWindowHandle2(HWINDOW hWindow, windowMsg_Header_ *pHeader, RECT *pRect, HDC hdc)
{
	window_ *pWindow = (window_*)hWindow;

	pWindow->rcDraw = *pRect;  //记录当前需要绘制的区域

	int cx = pRect->right - pRect->left;
	int cy = pRect->bottom - pRect->top;

	HBITMAP hWndBitmap = XDraw_CreateDIBSection(NULL, cx, cy);

	pWindow->hBkDC = CreateCompatibleDC(NULL);  //创建背静DC 窗口 (包含非客户区)
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
	//非客户区贴图
	Wnd_DrawWindow_NCClient(hWindow, hDraw);

	//客户区///////////////////////////////////////////////////
	Wnd_DrawWindow_Client(hWindow, hDraw, pHeader);  //绘制客户区

	//////////////////////////////////////////////////////////////////
	//窗口绘制完成后调用,便于特效合成
	XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top)); //窗口非客户区
	Wnd_NCWindowProc(hWindow, XWM_NCENDPAINT, (WPARAM)hDraw, 0);

	//////////////////////////////////////////////////////////////////////////
	//插入符//////////////////////////////////////////////////////////////////
	if (pWindow->hCaretEle && pWindow->bCaretShow)
	{
		Wnd_DrawWindow_Caret(hWindow, hDraw);
	}

	XDraw_Destroy_(hDraw);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //透明窗口
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
	//非客户区贴图
	if (pWindow->hImageNC)
	{
		RECT rcWindow;
		XWnd_GetNCClientRect(hWindow, &rcWindow);

		XDraw_HImageSuper_(hDraw, pWindow->hImageNC, &rcWindow);
	}

	//绘制窗口非客户区
	Wnd_NCWindowProc(hWindow, XWM_NCPAINT, (WPARAM)hDraw, 0);

	//绘制非客户区元素
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

void Wnd_DrawWindow_Client(HWINDOW hWindow, HDRAW hDraw, windowMsg_Header_ *pHeader)  //绘制客户区
{
	window_ *pWindow = (window_*)hWindow;
	//客户区///////////////////////////////////////////////////
	//映射到客户区
	XDraw_SetOffset_(hDraw, -(pWindow->rcDraw.left) + pWindow->borderLeft, -(pWindow->rcDraw.top) + XWnd_GetClientTop(hWindow));

	RECT rcClip; //剪切区
	XWnd_GetClientRect(hWindow, &rcClip);
	HRGN hRngClip = CreateRectRgn(0, 0, rcClip.right + XWnd_GetClientLeft(hWindow), rcClip.bottom + XWnd_GetClientTop(hWindow));
	SelectClipRgn(pWindow->hBkDC, hRngClip);

	//绘制窗口客户区
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

	//需要绘制的客户区坐标
	RECT rcDrawClient = pWindow->rcDraw;
	XWnd_WindowToClientRect(hWindow, &rcDrawClient);

	//窗口元素列表  绘制子元素
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

void Wnd_DrawWindow_Shadow(HWINDOW hWindow, HDC hdc) //窗口阴影
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
	//阴影窗口
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
		borderWidth = XC_WIND_SHADOW_SIZE;

	//拷贝重绘内容区域
	HDC memDC = NULL;
	if (NULL == pWindow->hBtimap || pWindow->sizeWnd.cx != rcSysNCClient.right || pWindow->sizeWnd.cy != rcSysNCClient.bottom)
	{
		if (pWindow->hBtimap)
			DeleteObject(pWindow->hBtimap);

		pWindow->hBtimap = XDraw_CreateDIBSection(NULL, rcSysNCClient.right, rcSysNCClient.bottom);

		pWindow->sizeWnd.cx = rcSysNCClient.right;
		pWindow->sizeWnd.cy = rcSysNCClient.bottom;
	}
	memDC = CreateCompatibleDC(NULL);         //创建背静DC 窗口 (包含非客户区)
	SelectObject(memDC, pWindow->hBtimap);

	BitBlt(memDC, pWindow->rcDraw.left + borderWidth, pWindow->rcDraw.top + borderWidth, cx, cy, pWindow->hBkDC, 0, 0, SRCCOPY);

	//绘制阴影
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

void Wnd_DrawWindow_Caret(HWINDOW hWindow, HDRAW hDraw) //处理插入符
{
	window_ *pWindow = (window_*)hWindow;

	POINT ptOld;
	SetViewportOrgEx(pWindow->hBkDC, -(pWindow->rcDraw.left), -(pWindow->rcDraw.top), &ptOld);

	POINT  ptCaret = pWindow->caretPt;
	XEle_PointToNCWnd(pWindow->hCaretEle, &ptCaret);

	//备份插入符背景
	HDC hdcCaret = CreateCompatibleDC(NULL);
	SelectObject(hdcCaret, pWindow->hCaretBitmap);
	BitBlt(hdcCaret, 0, 0, pWindow->caretWidth, pWindow->caretHeight, pWindow->hBkDC, ptCaret.x, ptCaret.y, SRCCOPY);
	DeleteDC(hdcCaret);

	SetViewportOrgEx(pWindow->hBkDC, ptOld.x, ptOld.y, 0);

	//如果在绘制范围内
	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);
	if (PtInRect(&pWindow->rcDraw, pt))
	{
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW) //透明窗口
		{
			Wnd_DrawCaretTransparentMemDC(hWindow, hDraw); //绘制插入符
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
	if (pWindow->hMinimize) //最小化按钮
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_CLOSE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_DESTROY]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_NCDESTROY]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

	//拥有鼠标捕获权限元素
	if (pWindow->pCapture)
	{
		//将坐标转换到元素客户区 坐标
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_MOUSEMOVE, wParam, (LPARAM)&InPt);
		//XTRACE("窗口有捕获 x=%d \n",InPt.x);
		return TRUE;
	}

	if (!pWindow->bTrackLeave) //跟踪鼠标离开
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_MOUSEMOVE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //非客户区
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

	//检查窗口是否有焦点
	if (pWindow->hWnd != GetFocus())
		SetFocus(pWindow->hWnd);

	////////////////////////////////////////////////////
	//配合属性网格元素 hArrayPGrids
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

	//拥有鼠标捕获权限元素
	if (pWindow->pCapture)
	{
		//将坐标转换到元素客户区 坐标
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_LBUTTONDOWN, wParam, (LPARAM)&InPt);
		return TRUE;
	}

	if (FALSE == pWindow->bClickTimer) //鼠标第一次按下
	{
		pWindow->bClickTimer = TRUE;
		pWindow->mouseDown.x = pt.x;
		pWindow->mouseDown.y = pt.y;
		pWindow->bMouseDown2 = FALSE;
		XWnd_SetTimer(hWindow, IDT_CLICK, 300);
	}
	else if ((TRUE == pWindow->bClickTimer) && (FALSE == pWindow->bMouseDown2)) //鼠标第二次按下
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
			//XTRACE("双击\n");
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_LBUTTONDOWN]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //非客户区
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

	//拥有鼠标捕获权限元素
	if (pWindow->pCapture)
	{
		//将坐标转换到元素客户区 坐标
		POINT InPt = { xPos,yPos };
		XEle_PointNCWndToEle(pWindow->pCapture, &InPt);
		Ele_SendEleMsg(pWindow->pCapture, XM_LBUTTONUP, wParam, (LPARAM)&InPt);
		return TRUE;
	}

	if (pWindow->bClickTimer && (FALSE == pWindow->bMouseUp)) //解析鼠标点击双击
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_LBUTTONUP]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else  //非客户区
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
	//拥有鼠标捕获权限元素
	if (pWindow->pCapture)
	{
		//将坐标转换到元素客户区 坐标
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_RBUTTONDOWN]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //非客户区
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
	//拥有鼠标捕获权限元素
	if (pWindow->pCapture)
	{
		//将坐标转换到元素客户区 坐标
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_RBUTTONUP]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else //非客户区
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_EXITSIZEMOVE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_MOUSELEAVE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_SIZE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}

BOOL Wnd_ConvTimer(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //定时器
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_TIMER]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return TRUE;
}

BOOL Wnd_ConvTimer2(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //定时器
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_TIMER]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_MOUSECLICK]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else  //非客户区
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
	if (PtInRect(&rect, pt)) //客户区
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

			if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
			if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
			{
				XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_MOUSEDBCLICK]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
				exit(0);
			}
#endif
			pFunT = pFunT->pNext;
		}
	}
	else  //非客户区
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_REDRAW_ELE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_SETFOCUS]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_KILLFOCUS]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_CAPTURECHANGED]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[WM_MOUSEWHEEL]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_MENUSELECT]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_MENUEXIT]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_SETFONT]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[%d]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n", pHeader->message);
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCPAINT]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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
		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCENDPAINT]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCMOUSEMOVE]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCLBUTTONDOWN]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCLBUTTONUP]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCRBUTTONDOWN]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCRBUTTONUP]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCMOUSECLICK]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
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

		if (!XC_IsHWINDOW(hWindow)) return TRUE; //如果句柄无效，终止消息事件

#ifdef _DEBUG  //错误检查
		if (NULL == hWindow || 0 != IsBadReadPtr(hWindow, sizeof(object_)) || XC_WINDOW != ((object_*)hWindow)->type)
		{
			XTRACE("炫彩界面库-debug提示-严重错误:在您注册的[XWM_NCMOUSEDBCLICK]消息处理函数中发生错误,因窗口[HWINDOW]句柄失效,如果您销毁了该句柄,应该返回[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////
void Wnd_RedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect) //重回元素指定区域
{
	window_ *pWindow = (window_*)hWindow;
	ele_ *pEle = (ele_*)hEle;

	ele_ *pEleShow = pEle;
	while (pEleShow) //检查父窗口是否显示
	{
		if (pEleShow->bShow)
			pEleShow = pEleShow->pParentEle;
		else
			return;
	}

	RECT rect = *pRect; //要重绘的区域

	//防止超出自身范围
	RECT rcEleSelf;
	XEle_GetNCWndRect(hEle, &rcEleSelf);
	if (rect.left < rcEleSelf.left)	   rect.left = rcEleSelf.left;
	if (rect.top < rcEleSelf.top)	       rect.top = rcEleSelf.top;
	if (rect.right > rcEleSelf.right)	   rect.right = rcEleSelf.right;
	if (rect.bottom > rcEleSelf.bottom)   rect.bottom = rcEleSelf.bottom;

	int windowLeft = XWnd_GetClientLeft(hWindow);
	int windowTop = XWnd_GetClientTop(hWindow);

	//防止超出客户区
	if (pEle->bClient)
	{
		RECT rcClient; //客户区范围
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

	ele_ *pPar = pEle->pParentEle; //父元素指针
	RECT  rect2;
	while (pPar) //防止超出父元素绘制范围
	{
		XEle_GetNCWndRect((HELE)pPar, &rect2); //父元素基于窗口客户区坐标

		if (rect.left < rect2.left) rect.left = rect2.left;
		if (rect.top < rect2.top) rect.top = rect2.top;
		if (rect.right > rect2.right) rect.right = rect2.right;
		if (rect.bottom > rect2.bottom) rect.bottom = rect2.bottom;

		pPar = pPar->pParentEle;
	}

	/////////////////////检查元素是否重叠///////////////////////////////////////
	if (Wnd_ReDrawEle_Overlapping(hWindow, hEle, &rect))
		return;

	if (rect.right > rect.left && rect.bottom > rect.top)
	{
		Wnd_PaintEle(hWindow, (HELE)pEle, &rect);
	}
}

BOOL Wnd_ReDrawEle_Overlapping(HWINDOW hWindow, HELE hEle, RECT *pRect) //检查元素重叠
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

					if (XC_RectInRect(pRect, &rcEle)) //重叠
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

	//顶层元素
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

					if (XC_RectInRect(pRect, &rcEle)) //重叠
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
	IsEleDebug(hEle, "元素重绘错误(00356783465456)");

	if (pRect)
	{
		Wnd_RedrawEle(hWindow, hEle, pRect);
	}
	else
	{
		RECT rect; //要重绘的区域
		XEle_GetNCWndRect(hEle, &rect); //基于窗口坐标(包含非客户区)
		Wnd_RedrawEle(hWindow, hEle, &rect);
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnSetFocus(HWINDOW hWindow)  //窗口获得焦点
{
	//	OutputDebugStringA("窗口 获得焦点\n");
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->pOldFocus)  //恢复元素焦点
	{
		pWindow->pFocus = pWindow->pOldFocus;
		pWindow->pOldFocus = NULL;
		Ele_SendEvent((HELE)pWindow->pFocus, XE_SETFOCUS, 0, 0);
	}
	//XWnd_RedrawWnd(hWindow,TRUE);
	return TRUE;
}

BOOL CALLBACK Wnd_OnKillFocus(HWINDOW hWindow) //窗口失去焦点
{
	//	OutputDebugStringA("窗口 失去焦点\n");

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

BOOL CALLBACK Wnd_OnMouseWheel(HWINDOW hWindow, UINT flags, POINT *pPt) //WM_MOUSEWHEEL 滚轮消息
{
	if (((window_*)hWindow)->pFocus)
	{
		//将坐标转换到元素客户区 坐标
		POINT InPt = *pPt;
		XEle_PointNCWndToEle((HELE)((window_*)hWindow)->pFocus, &InPt);

		Ele_SendEvent((HELE)((window_*)hWindow)->pFocus, XE_MOUSEWHEEL, (WPARAM)flags, MAKELPARAM(InPt.x, InPt.y));
	}
	return TRUE;
}

BOOL CALLBACK Wnd_OnTimerEx(HWINDOW hWindow, UINT timerID, int userData) //定时器消息
{
	return TRUE;
}

BOOL CALLBACK Wnd_OnRedraw(HWINDOW hWindow, WPARAM wParam, LPARAM lParam) //自定义消息,为了重绘延迟
{
	if (wParam && lParam) //重绘指定区域
	{
		RECT rect;
		rect.left = GET_X_LPARAM(wParam);
		rect.top = GET_Y_LPARAM(wParam);
		rect.right = GET_X_LPARAM(lParam);
		rect.bottom = GET_Y_LPARAM(lParam);
		XWnd_RedrawWndRect(hWindow, &rect, TRUE);
	}
	else //重绘整个窗口
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

	//绘制优化 
	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	Wnd_PaintEle_Optimization(hWindow, hEle, pRect); //优化绘制
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);

	//XTRACE("优化跳过绘制 \n");
}

void Wnd_PaintEle2(HWINDOW hWindow, HELE hEle, HDC hdc, RECT *pRect)
{
	window_ *pWindow = (window_*)hWindow;
	////////////////////////////////////////////////////////////

	pWindow->rcDraw = *pRect; //记录当前需要绘制的区域

	ele_ *pEleTran = Wnd_PaintEle_IsDrawEle(hWindow, hEle);
	if (NULL == pEleTran)
		return;

	////////////////////////////////////////////////////////////
	int cx = pRect->right - pRect->left;
	int cy = pRect->bottom - pRect->top;

	HBITMAP hWndBitmap = XDraw_CreateDIBSection(NULL, cx, cy);

	pWindow->hBkDC = CreateCompatibleDC(NULL);                      //创建背静DC 窗口
	SelectObject(pWindow->hBkDC, hWndBitmap);
	SetBkMode(pWindow->hBkDC, TRANSPARENT);
	////////////////////////////////////////////////////////////////
	HDRAW hDraw = XDraw_Create_(pWindow->hBkDC);
	if (FALSE == pEleTran->bClient) //非客户区
	{
		XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top));//将背景DC转换到窗口客户区坐标空间
	}
	else //客户区
	{
		//映射到客户区
		XDraw_SetOffset_(hDraw, -(pRect->left) + pWindow->borderLeft, -(pRect->top) + XWnd_GetClientTop(hWindow));
	}

	Ele_SendEleMsg((HELE)pEleTran, XM_PAINT, (WPARAM)hDraw, 0);
	//////////////////////////////////////////////////////////////////
	//窗口绘制完成后调用,便于特效合成
	XDraw_SetOffset_(hDraw, -(pRect->left), -(pRect->top)); //窗口非客户区
	Wnd_NCWindowProc(hWindow, XWM_NCENDPAINT, (WPARAM)hDraw, 0);

	//插入符//////////////////////////////////////////////////////////////////
	if (pWindow->hCaretEle && pWindow->bCaretShow)
	{
		Wnd_PaintEle_Caret(hWindow, hDraw);
	}

	XDraw_SetOffset_(hDraw, 0, 0);
	XDraw_Destroy_(hDraw);

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //透明窗口
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

void Wnd_PaintEle_Optimization(HWINDOW hWindow, HELE hEle, RECT *pRect) //优化绘制
{
	window_ *pWindow = (window_*)hWindow;

	//先前为空
	if (FALSE == pWindow->drawWindow.bValid)
	{
		//XTRACE("先前为空 .... \n");
		Wnd_PaintEle_Optimization1(hWindow, hEle, pRect);
		return;
	}

	//同一个元素
	if (hEle == pWindow->drawWindow.hEle)
	{
		//XTRACE("同一个元素 .... \n");
		Wnd_PaintEle_Optimization2(hWindow, hEle, pRect);
		return;
	}

	//先前为重绘窗口
	if (NULL == pWindow->drawWindow.hEle)
	{
		//XTRACE("先前为重绘窗口 .... \n");
		Wnd_PaintEle_Optimization4(hWindow, hEle, pRect);
		return;
	}

	//先前为重绘指定区域
	//XTRACE("先前为重绘指定区域 .... \n");
	Wnd_PaintEle_Optimization3(hWindow, hEle, pRect);
}

void Wnd_PaintEle_Optimization1(HWINDOW hWindow, HELE hEle, RECT *pRect) //先前为空
{
	window_ *pWindow = (window_*)hWindow;

	pWindow->drawWindow.hEle = hEle;
	pWindow->drawWindow.rect = *pRect;
	pWindow->drawWindow.bValid = TRUE;
	return;
}

void Wnd_PaintEle_Optimization2(HWINDOW hWindow, HELE hEle, RECT *pRect)  //同一个元素
{
	window_ *pWindow = (window_*)hWindow;

	//合并重绘区域,重绘父元素指定坐标
	RECT rcDest;
	XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
	pWindow->drawWindow.rect = rcDest;
}

void Wnd_PaintEle_Optimization3(HWINDOW hWindow, HELE hEle, RECT *pRect) //先前为重绘指定区域
{
	window_ *pWindow = (window_*)hWindow;

	//重绘指定区域
	HELE hParentEle1 = XEle_GetParentEle(hEle);
	HELE hParentEle2 = XEle_GetParentEle(pWindow->drawWindow.hEle);

	//合并绘制区域
	RECT rcDest;
	XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
	pWindow->drawWindow.rect = rcDest;

	if (hParentEle1 == hParentEle2) //同层元素
	{
		//XTRACE("同层元素 ....\n");
		pWindow->drawWindow.hEle = hParentEle1;

		if (NULL == hParentEle1) //如果父为空,那么为窗口
		{
			//XTRACE("同层元素 父为空 ....\n");
			pWindow->drawWindow.hEle = NULL;
		}
		return;
	}

	//如果当前元素是子元素
	HELE hParentEle = XEle_GetParentEle(hEle);
	while (hParentEle)
	{
		if (hParentEle == pWindow->drawWindow.hEle)
		{
			//XTRACE("当前元素是子元素  ....\n");
			return;
		}
		hParentEle = XEle_GetParentEle(hParentEle);
	}

	//当前元素是父元素
	hParentEle = XEle_GetParentEle(pWindow->drawWindow.hEle);
	while (hParentEle)
	{
		if (hParentEle == hEle)
		{
			pWindow->drawWindow.hEle = hEle;
			//XTRACE("当前元素是父元素  ....\n");
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
				//XTRACE("两个元素有共同的父 为元素 ....\n");
				return;
			}
			hP = XEle_GetParentEle(hP);
		}
		hParentEle = XEle_GetParentEle(hParentEle);
	}

	//XTRACE("两个元素有共同的父 为窗口 ....\n");
	pWindow->drawWindow.hEle = NULL;

	//没有父子关系

}

void Wnd_PaintEle_Optimization4(HWINDOW hWindow, HELE hEle, RECT *pRect) //先前为重绘窗口
{
	window_ *pWindow = (window_*)hWindow;

	//合并绘制区域
	RECT rcDest;
	XC_CombineRect(&rcDest, &pWindow->drawWindow.rect, pRect);
	pWindow->drawWindow.rect = rcDest;
}

ele_* Wnd_PaintEle_IsDrawEle(HWINDOW hWindow, HELE hEle) //检查是否直接重绘元素
{
	window_ *pWindow = (window_*)hWindow;

	ele_ *pEleTran = (ele_*)hEle;
	while (pEleTran) //配合元素透明
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

void Wnd_PaintEle_Shadow(HWINDOW hWindow, HDC hdc) //窗口阴影
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

	//拷贝重绘内容区域
	HDC memDC = NULL;

	memDC = CreateCompatibleDC(NULL);         //创建背静DC 窗口 (包含非客户区)
	SelectObject(memDC, pWindow->hBtimap);

	int borderSize = 0; //非客户区边框阴影大小
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

void Wnd_PaintEle_Caret(HWINDOW hWindow, HDRAW hDraw) //处理插入符
{
	window_ *pWindow = (window_*)hWindow;

	POINT ptOld;
	SetViewportOrgEx(pWindow->hBkDC, -(pWindow->rcDraw.left), -(pWindow->rcDraw.top), &ptOld);

	POINT  ptCaret = pWindow->caretPt;
	XEle_PointToNCWnd(pWindow->hCaretEle, &ptCaret);

	//备份插入符背景
	HDC hdcCaret = CreateCompatibleDC(NULL);
	SelectObject(hdcCaret, pWindow->hCaretBitmap);
	BitBlt(hdcCaret, 0, 0, pWindow->caretWidth, pWindow->caretHeight, pWindow->hBkDC, ptCaret.x, ptCaret.y, SRCCOPY);
	DeleteDC(hdcCaret);

	SetViewportOrgEx(pWindow->hBkDC, ptOld.x, ptOld.y, 0);

	//如果在绘制范围内
	POINT pt = { pWindow->caretPt.x,pWindow->caretPt.y };
	XEle_PointToNCWnd(pWindow->hCaretEle, &pt);
	if (PtInRect(&pWindow->rcDraw, pt))
	{
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW) //透明窗口
		{
			Wnd_DrawCaretTransparentMemDC(hWindow, hDraw); //绘制插入符
		}
		else
		{
			Wnd_DrawCaretMenDC(hWindow, hDraw);
		}
	}
}

BOOL Wnd_KeyDown(HWINDOW hWindow, int key) //元素焦点切换方向
{
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->pFocus && pWindow->pFocus->bClient) //客户区
	{
		if (XC_RICHEDIT == pWindow->pFocus->eleType)
			return FALSE;

		if (VK_TAB == key)  //TAB
		{
			return Wnd_HandleFocusDown(hWindow); //焦点下切换
		}if (XC_IsEditExtend((HELE)pWindow->pFocus)) //编辑框不支持箭头切换
		{
			return FALSE;
		}
		else if (37 == key || 38 == key)  //上切换
		{
			if (pWindow->pFocus && pWindow->pFocus->bShow)
			{
				return Wnd_HandleFocusUp(hWindow);   //焦点上切换
			}
		}
		else if (39 == key || 40 == key)   //下切换
		{
			if (pWindow->pFocus && pWindow->pFocus->bShow)
			{
				return Wnd_HandleFocusDown(hWindow); //焦点下切换
			}
		}
	}
	else //非客户区
	{
		//TODO:非客户区元素焦点切换
	}
	return FALSE;
}

BOOL Wnd_HandleFocusUp(HWINDOW hWindow)   //焦点上切换
{
	window_ *pWindow = (window_*)hWindow;

	if (NULL == pWindow->pFocus) return FALSE;

	ele_ *curEle = NULL;
	ele_ *pParent = pWindow->pFocus->pParentEle;
	if (pParent)  //有父元素
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
	else  //没有父元素
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

BOOL Wnd_HandleFocusDown(HWINDOW hWindow) //焦点下切换
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
	if (pParent)  //有父元素
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
	else  //没有父元素
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

int Wnd_GetWindowCount()//获取窗口数量
{
	return Resource_GetWindowCount();
}

//pPt:客户区坐标
BOOL CALLBACK Wnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;
	//pWindow->bTitleBarDown=FALSE;
	//判断鼠标在哪个元素上
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
				//将坐标转换到元素客户区 坐标
				if (curEle->bEnable)
				{
					POINT InPt = { pPt->x - curEle->rect.left, pPt->y - curEle->rect.top };
					Ele_SendEleMsg((HELE)curEle, XM_MOUSEMOVE, (WPARAM)flags, (LPARAM)&InPt);
				}
				return TRUE;
			}
		}
	}

	//鼠标没有在任何元素之上
	if (pWindow->pMouseTop) //鼠标离开
	{
		HELE hEleSend = (HELE)pWindow->pMouseTop;
		pWindow->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}
	return TRUE;
}

//pPt:客户区坐标
BOOL CALLBACK Wnd_OnLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//处理子元素消息
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

	if (pWindow->xcStyle & XC_SY_DRAG_WINDOW) //拖动窗口
	{
		SendMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}

	return TRUE;
}

//pPt:客户区坐标
BOOL CALLBACK Wnd_OnLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;

	//处理子元素消息
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

	//处理子元素消息
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

	//处理子元素消息
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

	if (IsZoomed(pWindow->hWnd)) //最大化窗口
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
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW) //分层窗口
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

	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED) //分层窗口
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
	case IDT_CLICK:   //分析鼠标点击双击
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->bMouseUp && pWindow->bClickTimer) //单击
		{
			int posx = pWindow->mouseDown.x;
			int posy = pWindow->mouseDown.y;
			if (posx == pWindow->mouseUp.x && posy == pWindow->mouseUp.y)
			{
				PostMessage(pWindow->hWnd, XWM_MOUSECLICK, posx, posy);
				//	XTRACE("鼠标单击\n");
			}
		}
		pWindow->bClickTimer = FALSE;
		pWindow->bMouseUp = FALSE;
		//pWindow->bMouseDown2=FALSE;
		KillTimer(pWindow->hWnd, IDT_CLICK);
	}break;
	case IDT_HSCROLL_UP: //上滚动
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
	case IDT_HSCROLL_DOWN: //下滚动
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
	case IDT_CARET: //处理绘制插入符
	{
		window_ *pWindow = (window_*)hWindow;
		if (pWindow->bCaretErase)
			pWindow->bCaretErase = FALSE;
		else
			pWindow->bCaretErase = TRUE;

		Wnd_DrawCaret(hWindow);
		//OutputDebugStringA("绘制插入符\n");
	}break;
	}
	//OutputDebugStringA("on - timer \n");
	return TRUE;
}

BOOL CALLBACK Wnd_OnMouseClick(HWINDOW hWindow, POINT *pPt)
{
	window_ *pWindow = (window_*)hWindow;
	//处理子元素消息
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
	//处理子元素消息
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

//绘制标题栏
void Wnd_DrawCaption(HWINDOW hWindow, HDRAW hDraw)
{
	//如果没有标题栏不绘制
	int clientTop = XWnd_GetCaptionHeight(hWindow); //XWnd_GetClientTop(hWindow);
	if (clientTop < 1)
		return;

	window_ *pWindow = (window_*)hWindow;

	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	RECT rcTitle = rect; //标题栏矩形
	rcTitle.bottom = clientTop;

	//1.检查是否在绘制范围内
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcTitle))
		return; //不在绘制区域内

	//2.计算新的绘制区域
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
	int halfY = rcTitle.bottom / 2; //中间坐标

	//绘制图标
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
		if ((rcTitle.right - rcTitle.left) > 20) //检查文本显示长度
		{
			wchar_t title[256] = { 0 };
			int len = GetWindowText(pWindow->hWnd, title, 256);
			if (len > 0) //绘制标题文本
			{
				XDraw_DrawText_(hDraw, title, len, &rcTitle, DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
}

//绘制边框left
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

	//1.检查是否在绘制范围内
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcLeft))
		return; //不在绘制区域内

	//2.计算新的绘制区域
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcLeft))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;

	//左边框
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

//绘制边框right
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

	//1.检查是否在绘制范围内
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcRight))
		return; //不在绘制区域内

	//2.计算新的绘制区域
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcRight))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;

	//左边框
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

//绘制边框bottom
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

	//1.检查是否在绘制范围内
	if (FALSE == XC_RectInRect(&pWindow->rcDraw, &rcBottom))
		return; //不在绘制区域内

	//2.计算新的绘制区域
	RECT rcDest = { 0 };
	if (0 == IntersectRect(&rcDest, &pWindow->rcDraw, &rcBottom))
		return;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;
	//左边框
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

//非客户区贴图时绘制
void Wnd_DrawCaptionImageNC(HWINDOW hWindow, HDRAW hDraw)
{
	window_ *pWindow = (window_*)hWindow;
	RECT rect;
	XWnd_GetNCClientRect(hWindow, &rect);

	//标题栏---------------------------------------
	if (pWindow->captionHeight > 0)
	{
		RECT rcTitle = rect;
		rcTitle.bottom = pWindow->captionHeight;

		int halfY = rcTitle.bottom / 2; //中间坐标

		//绘制图标
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
			if ((rcTitle.right - rcTitle.left) > 20) //检查文本显示长度
			{
				wchar_t title[256] = { 0 };
				int len = GetWindowText(pWindow->hWnd, title, 256);
				if (len > 0) //绘制标题文本
				{
					XDraw_DrawText_(hDraw, title, len, &rcTitle, DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
	}
}

BOOL CALLBACK Wnd_OnNCDrawWindow(HWINDOW hWindow, HDRAW hDraw) //非客户区绘制
{
	window_ *pWindow = (window_*)hWindow;
	if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED)
	{
		return TRUE;
	}

	//非客户区贴图
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

	if (pWindow->chartletStyle & XC_CS_STROKE_INNER) //描边内
	{
		RECT rcBorder = { borderLeft - 1,XWnd_GetCaptionHeight(hWindow) - 1,
			rect.right - borderRight + 1,rect.bottom - borderBottom + 1 };

		if (rcBorder.left > 5 && rcBorder.top > 5 && (rect.right - rcBorder.right) > 5 && (rect.bottom - rcBorder.bottom) > 5)
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeInner_color1);//黑色
			HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeInner_color2);//白色
			//内黑色
			XDraw_FrameRect_(hDraw, &rcBorder, hBrush);

			//内白色
			rcBorder.left--; rcBorder.top--; rcBorder.right++; rcBorder.bottom++;
			XDraw_FrameRect_(hDraw, &rcBorder, hBrush2);
		}
	}

	if (pWindow->chartletStyle & XC_CS_STROKE_OUTER) //描边外
	{
		//绘制描边
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeOuter_color1);//黑色
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, pWindow->strokeOuter_color2);//白色

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
			//外白色
			if (borderLeft > 1 && borderTop > 1 && borderRight > 1 && borderBottom > 1)
			{
				RECT rcBorder2 = rect;
				rcBorder2.left++; rcBorder2.top++; rcBorder2.right--; rcBorder2.bottom--;
				XDraw_FrameRect_(hDraw, &rcBorder2, hBrush2);
			}

			//外黑色
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
				//将坐标转换到元素客户区 坐标
				POINT InPt = { pPt->x - curEle->rect.left, pPt->y - curEle->rect.top };
				Ele_SendEleMsg((HELE)curEle, XM_MOUSEMOVE, (WPARAM)flags, (LPARAM)&InPt);
				return TRUE;
			}
		}
	}

	//鼠标没有在任何元素之上
	if (pWindow->pMouseTop) //鼠标离开
	{
		HELE hEleSend = (HELE)pWindow->pMouseTop;
		pWindow->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}

	//改变光标//////////////////////////////////////
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
			if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x >= 0 && pPt->x < 8)//pPt->x<pWindow->borderLeft) //左
			{
				if (pPt->y < 10) //上角
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else if (pPt->y > rect.bottom - 10) //下角
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE)); return TRUE;
				}
			}
			else if (pPt->x > 0 && pPt->x < rect.right && pPt->y>0 && pPt->y < top) //上
			{
				if (pPt->x < 10) //左上角
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else if (pPt->x > rect.right - 10) //右上角
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENS)); return TRUE;
				}
			}
			else if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x<rect.right && pPt->x>rect.right - 8)//pPt->x>rect.right-pWindow->borderRight) //右
			{
				if (pPt->y < 10) //右上角
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENESW)); return TRUE;
				}
				else if (pPt->y > rect.bottom - 10) //右下角
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZENWSE)); return TRUE;
				}
				else
				{
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE)); return TRUE;
				}
			}
			else if (pPt->x > 0 && pPt->x < rect.right && pPt->y<rect.bottom && pPt->y>rect.bottom - 8)//pPt->y>rect.bottom-pWindow->borderBottom) //下
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

	//处理子元素消息
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

	//	//鼠标没有在子元素上
	//	if(pWindow->pFocus)
	//	{
	//		//失去焦点
	//		Ele_SendEvent(pWindow->pFocus,XE_KILLFOCUS,0,0);
	//		pWindow->pFocus=NULL;
	//	}

	//鼠标按在边框上
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
		if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x >= 0 && pPt->x < 8)//pPt->x<pWindow->borderLeft) //左
		{
			if (pPt->y < 10) //上角
			{
				//	pWindow->downBorder=5;
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->y > rect.bottom - 10) //下角
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
		else if (pPt->x > 0 && pPt->x < rect.right && pPt->y>0 && pPt->y < top) //上
		{
			if (pPt->x < 10) //左上角
			{
				//	pWindow->downBorder=5;
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPLEFT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->x > rect.right - 10) //右上角
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
		else if (pPt->y > 0 && pPt->y < rect.bottom && pPt->x<rect.right && pPt->x>rect.right - 8)//pPt->x>rect.right-pWindow->borderRight) //右
		{
			if (pPt->y < 10) //右上角
			{
				//	pWindow->downBorder=7;
				SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
				::PostMessage(pWindow->hWnd, WM_NCLBUTTONDOWN, HTTOPRIGHT, MAKELPARAM(pPt->x, pPt->y));
				return TRUE;
			}
			else if (pPt->y > rect.bottom - 10) //右下角
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
		else if (pPt->x > 0 && pPt->x < rect.right && pPt->y<rect.bottom && pPt->y>rect.bottom - 8)//pPt->y>rect.bottom-pWindow->borderBottom) //下
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

	//鼠标按在标题栏
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

	//处理子元素消息
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

	//处理子元素消息
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

	//处理子元素消息
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

	//处理子元素消息
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

	//处理子元素消息
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

	//没有在任何元素上
	if (XC_SY_MAXIMIZE & pWindow->xcStyle) //窗口最大化或还原大小
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
	XDraw_MoveToEx_(hDraw, rect.left + 14, rect.top + 4, NULL);  //左上 到 右下
	XDraw_LineTo_(hDraw, rect.left + 23, rect.top + 13);

	XDraw_MoveToEx_(hDraw, rect.left + 23, rect.top + 4, NULL);  //右上 到 左下
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
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //上横线

	rc.left = rect.left + 8;
	rc.top = rect.top + 7;
	rc.right = rc.left + 2;
	rc.bottom = rc.top + 5;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //左竖线

	rc.left = rect.left + 16;
	rc.top = rect.top + 7;
	rc.right = rc.left + 2;
	rc.bottom = rc.top + 5;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //右竖线

	rc.left = rect.left + 8;
	rc.top = rect.top + 11;
	rc.right = rc.left + 10;
	rc.bottom = rc.top + 2;
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //下横线

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
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255)); //绘制粗线条

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
