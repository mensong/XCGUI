/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


ULONG_PTR   gdiplusToken;

int         g_event_write_pos = 0;               //�¼���ǰλ���α�,д��
eventList_  g_eventList[EVENT_LIST_SIZE] = { 0 };  //�¼�����

HMODULE    g_resourcesModule = NULL;  //��Դģ����

int  g_clipbroad_RichEditFormat = 0;
int  g_clipborad_HTMLFormat = 0;

HMODULE    g_XCGUI_Dll_Module = NULL; //DLL�ļ�ģ����

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

///@brief ע�ᴰ����,��Ѱ治�ṩ��API.
///@param pClassName ��������.
///@param hIcon  ����ͼ��.
///@return ����ɹ�����true,�����෴.
BOOL WINAPI XC_RegisterWndClass(wchar_t *pClassName, HICON hIcon)
{
#ifdef XCGUI_Free_version
	MessageBox(NULL, L"�Ųʽ������Ѱ�,���ṩ�ù���", L"��ʾ", 0);
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

///@brief ������ʼ��,�����ظ�����.
BOOL WINAPI XInitXCGUI(const wchar_t* pIconFileName/*=NULL*/, const wchar_t* pSmallIconFileName/*=NULL*/, wchar_t *pText/*=NULL*/)
{
#ifdef  XCVGUI_Business_license_serial_number
	char text[MAX_PATH] = { 0 };
	XC_UnicodeToAnsi(pText, wcslen(pText), text, MAX_PATH);

	if (text)
		SSLWnd_Init(text);
#endif

	//	sendEMailReport();  //���͵��Ա���

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

	Resource_Init();  //��ʼ��

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

	//��̨ѭ���߳�
	g_hThread_Loop = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		XCGUI_Loop_ThreadProc,          // thread function 
		0,             // argument to thread function 
		0,                 // use default creation flags 
		NULL);   // returns the thread identifier 

	if (NULL == g_hThread_Loop)
	{
		XTRACE("������̨�߳�ʧ�� \n");
		return FALSE;
	}
	return TRUE;
}

///@brief ���г���,�����ظ�����.
void WINAPI XRunXCGUI()
{
	MSG msg;
	// ����Ϣѭ��:
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

void WINAPI XExitProcess() //�˳�����(�൱��������)
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

	//	char *p=new char[1]; //�鿴�Ƿ������ڴ�й¶���
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
//�ܴ�����Ϣ����
LRESULT CALLBACK XCGUI_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_CREATE == message)
	{
		LONG_PTR L = (LONG_PTR)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, L);

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

	window_ *pWindow = (window_*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (FALSE == XC_IsHWINDOW((HWINDOW)pWindow))
		return DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_KILLFOCUS:
	{
		//	XTRACE("ʧȥ���� \n");
	}break;
	case WM_SETFOCUS:
	{
		//	XTRACE("��ý��� \n");
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
		//XTRACE("���� WM_ACTIVATE \n");
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

