/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


ULONG_PTR   gdiplusToken;

int         g_event_write_pos = 0;               //事件当前位置游标,写入
eventList_  g_eventList[EVENT_LIST_SIZE] = { 0 };  //事件队列

HMODULE    g_resourcesModule = NULL;  //资源模块句柄

int  g_clipbroad_RichEditFormat = 0;
int  g_clipborad_HTMLFormat = 0;

HMODULE    g_XCGUI_Dll_Module = NULL; //DLL文件模块句柄

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

#ifdef XCDLL
	g_XCGUI_Dll_Module = hModule;
#endif

	return TRUE;
}


///@addtogroup groupGlobalAPI
///@{

///@brief 注册窗口类,免费版不提供该API.
///@param pClassName 窗口类名.
///@param hIcon  窗口图标.
///@return 如果成功返回true,否则相反.
BOOL WINAPI XC_RegisterWndClass(wchar_t *pClassName, HICON hIcon)
{
#ifdef XCGUI_Free_version
	MessageBox(NULL, L"炫彩界面库免费版,不提供该功能", L"提示", 0);
	return FALSE;
#else
	HMODULE hInstance = GetModuleHandle(NULL);

	WNDCLASSW wndClassw;
	wndClassw.style = CS_HREDRAW | CS_VREDRAW;
	wndClassw.lpfnWndProc = XCGUI_WndProc;
	wndClassw.cbClsExtra = 0;
	wndClassw.cbWndExtra = 0;
	wndClassw.hInstance = hInstance;
	wndClassw.hIcon = hIcon;
	wndClassw.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassw.hbrBackground = NULL;
	wndClassw.lpszMenuName = NULL;
	wndClassw.lpszClassName = pClassName;

	if (0 == ::RegisterClass(&wndClassw))
		return FALSE;
	else
		return true;
#endif
}

///@brief 界面库初始化,不得重复调用.
BOOL WINAPI XInitXCGUI(const wchar_t* pIconFileName/*=NULL*/, const wchar_t* pSmallIconFileName/*=NULL*/, wchar_t *pText/*=NULL*/)
{
#ifdef  XCVGUI_Business_license_serial_number
	char text[MAX_PATH] = { 0 };
	XC_UnicodeToAnsi(pText, wcslen(pText), text, MAX_PATH);

	if (text)
		SSLWnd_Init(text);
#endif

	//	sendEMailReport();  //发送调试报告

	HMODULE hInstance = GetModuleHandle(NULL);

	HMODULE hInsIcon = NULL;
#ifdef XCDLL
	hInsIcon = g_XCGUI_Dll_Module;
#else
	hInsIcon = hInstance;
#endif

	/*
		hInsIcon=GetModuleHandle(L"XCGUI.exe");

		if(NULL==hInsIcon)
			hInsIcon=GetModuleHandle(L"XCGUI.dll");

		if(NULL==hInsIcon)
			hInsIcon=GetModuleHandle(L"XCGUId.dll");

		if(NULL==hInsIcon)
			hInsIcon=GetModuleHandle(L"XCGUId.lib");

		if(NULL==hInsIcon)
			hInsIcon=GetModuleHandle(L"XCGUI.lib");
	*/

	HICON hIcon = NULL;
	HICON hSmalIcon = NULL;
	if (NULL != pIconFileName)
		hIcon = (HICON)LoadImageW(hInstance, pIconFileName, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	if (NULL != pSmallIconFileName)
		hSmalIcon = (HICON)LoadImageW(hInstance, pSmallIconFileName, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = XCGUI_WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = hIcon;//LoadIcon(hInsIcon,MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = XCGUI_CLASS_NAME;
	wcex.hIconSm = hSmalIcon;//LoadIcon(hInsIcon,MAKEINTRESOURCE(IDI_SMALL));

	if (0 == ::RegisterClassExW(&wcex))
		return FALSE;

	g_clipborad_HTMLFormat = RegisterClipboardFormat(L"HTML Format");
	g_clipbroad_RichEditFormat = RegisterClipboardFormat(L"XCGUI_RichEdit_Format");

	Resource_Init();  //初始化

	GdiplusStartupInput gdiplusStartInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartInput, NULL);

	if (g_fun_init && FALSE == g_fun_init())
	{
		MsgError(XC_ERROR_0009);
		return FALSE;
	}

	InitializeCriticalSection(&g_timer_CriticalSection);
	InitializeCriticalSection(&g_CriticalSection_Animation_button);
	InitializeCriticalSection(&g_CriticalSection_Animation_richEdit);
	InitializeCriticalSection(&g_CriticalSection_WindowDraw);

	//后台循环线程
	g_hThread_Loop = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		XCGUI_Loop_ThreadProc,          // thread function 
		0,             // argument to thread function 
		0,                 // use default creation flags 
		NULL);   // returns the thread identifier 

	if (NULL == g_hThread_Loop)
	{
		XTRACE("创建后台线程失败 \n");
		return FALSE;
	}
	return TRUE;
}

///@brief 运行程序,不得重复调用.
void WINAPI XRunXCGUI()
{
	MSG msg;
	// 主消息循环:
	while (true)
	{
		if (Resource_GetWindowCount() < 1)
			break;

		GetMessage(&msg, NULL, 0, 0);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	XExitProcess();
}

///@}

void WINAPI XExitProcess() //退出进程(相当析构函数)
{
	GdiplusShutdown(gdiplusToken);
	Resource_Release();

	if (XCom_GetCount() > 0)
	{
		XCom_AppExit();
	}

	if (g_hThread_Loop)
	{
		CloseHandle(g_hThread_Loop);
		g_hThread_Loop = NULL;
	}

	EnterCriticalSection(&g_timer_CriticalSection);
	if (g_hArray_Timer)
	{
		int count = XArray_GetCount(g_hArray_Timer);
		for (int i = 0; i < count; i++)
		{
			xc_timer_ *p = (xc_timer_*)XArray_GetAt(g_hArray_Timer, i);
			free(p);
		}
		XArray_Destroy(g_hArray_Timer);
		g_hArray_Timer = NULL;
	}
	LeaveCriticalSection(&g_timer_CriticalSection);

	EnterCriticalSection(&g_CriticalSection_Animation_button);
	if (g_hArray_Animation_button)
	{
		XArray_Destroy(g_hArray_Animation_button);
		g_hArray_Animation_button = NULL;
	}
	LeaveCriticalSection(&g_CriticalSection_Animation_button);

	EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
	if (g_hArray_Animation_RichEdit)
	{
		XArray_Destroy(g_hArray_Animation_RichEdit);
		g_hArray_Animation_RichEdit = NULL;
	}
	LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);


	DeleteCriticalSection(&g_timer_CriticalSection);
	DeleteCriticalSection(&g_CriticalSection_Animation_button);
	DeleteCriticalSection(&g_CriticalSection_Animation_richEdit);
	DeleteCriticalSection(&g_CriticalSection_WindowDraw);

	//	char *p=new char[1]; //查看是否启用内存泄露检查
	//	_CrtDumpMemoryLeaks();

#ifdef XCVGUI_Business_license_serial_number
	extern void *pUI_Set1;
	extern void *pUI_Set2;

	free(pUI_Set1);
	free(pUI_Set2);
#endif

	if (g_fun_exit && FALSE == g_fun_exit())
	{
		MsgError(XC_ERROR_0010);
		return;
	}

#ifndef XCDLL
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif

}
bool  bbs = FALSE;
//总窗口消息过程
LRESULT CALLBACK XCGUI_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_CREATE == message)
	{
		LONG L = (LONG)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		SetWindowLong(hWnd, GWLP_USERDATA, L);

		window_ *pWindow = (window_*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		if (XC_IsHWINDOW((HWINDOW)pWindow))
		{
			windowProc_ *pFunT = pWindow->pWndProc;
			while (pFunT)
			{
				if (((pFunWndMsgProc)pFunT->pFun)((HWINDOW)pWindow, message, wParam, lParam))
					return 0;
				pFunT = pFunT->pNext;
			}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	window_ *pWindow = (window_*)GetWindowLong(hWnd, GWLP_USERDATA);
	if (FALSE == XC_IsHWINDOW((HWINDOW)pWindow))
		return DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_KILLFOCUS:
	{
		//	XTRACE("失去焦点 \n");
	}break;
	case WM_SETFOCUS:
	{
		//	XTRACE("获得焦点 \n");
	}break;
	}

	windowProc_ *pFunT = pWindow->pWndProc;
	while (pFunT)
	{
		if (((pFunWndMsgProc)pFunT->pFun)((HWINDOW)pWindow, message, wParam, lParam))
			return 0;
		pFunT = pFunT->pNext;
	}

	switch (message)
	{
	case WM_NCPAINT:     return 0;
	case WM_ERASEBKGND:  return 1;
	case WM_NCACTIVATE:	 return 1;
	case WM_ACTIVATE:
	{
		//XTRACE("激活 WM_ACTIVATE \n");
		XWnd_RedrawWnd((HWINDOW)pWindow);
	}break;
	case WM_NCCALCSIZE:
		if (pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW)
		{
			if (wParam)
			{
				NCCALCSIZE_PARAMS *pInfo = (NCCALCSIZE_PARAMS*)lParam;
				pInfo->rgrc[0].left += XC_WIND_SHADOW_SIZE;
				pInfo->rgrc[0].top += XC_WIND_SHADOW_SIZE;
				pInfo->rgrc[0].right -= XC_WIND_SHADOW_SIZE;
				pInfo->rgrc[0].bottom -= XC_WIND_SHADOW_SIZE;
				return 0;
			}
		}
		else
		{
			if (wParam)
				return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WINAPI xtrace(char *pszFormat, ...)
{
	va_list pArgs;

	char szMessageBuffer[1024] = { 0 };
	va_start(pArgs, pszFormat);
	vsnprintf_s(szMessageBuffer, 1024, _TRUNCATE, pszFormat, pArgs);
	va_end(pArgs);

	OutputDebugStringA(szMessageBuffer);
}

void WINAPI xtracew(wchar_t *pszFormat, ...)
{
	va_list pArgs;

	wchar_t szMessageBuffer[1024] = { 0 };
	va_start(pArgs, pszFormat);
	_vsnwprintf_s(szMessageBuffer, 1024, _TRUNCATE, pszFormat, pArgs);
	va_end(pArgs);

	OutputDebugStringW(szMessageBuffer);
}

