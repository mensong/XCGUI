/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once



struct eventList_  //事件结构
{
	HELE     hEle;	 //发生事件的元素句柄
	int      type;	 //事件类型
	WPARAM   wParam;
	LPARAM   lParam;
	BOOL     bEvent;  //TRUE:有事件, FALSE:没有事件
};


#define            EVENT_LIST_SIZE          10         //事件队列大小
extern int         g_event_write_pos;                  //事件当前位置游标,写入
extern eventList_  g_eventList[EVENT_LIST_SIZE];       //事件队列
extern ULONG_PTR   gdiplusToken;

extern HMODULE    g_resourcesModule;  //资源模块句柄

//剪贴板格式
extern int  g_clipbroad_RichEditFormat;
extern int  g_clipborad_HTMLFormat;

//应用程序API:
XC_API BOOL WINAPI XC_RegisterWndClass(wchar_t *pClassName, HICON hIcon = NULL); //注册窗口类


XC_API BOOL WINAPI XInitXCGUI(const wchar_t* pIconFileName = NULL, const wchar_t* pSmallIconFileName = NULL, wchar_t *pText = NULL);
XC_API void WINAPI XRunXCGUI();
XC_API void WINAPI XExitProcess(); //退出进程(相当析构函数)

LRESULT CALLBACK XCGUI_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


XC_API void WINAPI xtrace(char *pszFormat, ...);
XC_API void WINAPI xtracew(wchar_t *pszFormat, ...);



