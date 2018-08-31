/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//模态窗口
struct modalWindow_
{
	window_ window; //继承
	//------------------------

	HARRAY  hArrayWnd;//记录禁用的窗口列表
};
extern int  g_modal_returnValue;  //返回值

//窗口API:
XC_API HWINDOW WINAPI XModalWnd_CreateWindow(int width, int height, wchar_t *pTitle, HWND hWndParent, int XCStyle = XC_SY_MODAL_WINDOW);//基于父窗口坐标
XC_API int WINAPI XModalWnd_DoModal(HWINDOW hWindow);     //启动模态窗口
XC_API void WINAPI XModalWnd_DoOk(HWINDOW hWindow);       //确定
XC_API void WINAPI XModalWnd_DoCancel(HWINDOW hWindow);   //取消

//私有方法:
BOOL ModalWnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int cx, int cy, HWND hWndParent, int XCStyle, int exType);

//回调函数
BOOL CALLBACK ModalWnd_OnClose(HWINDOW hWindow);
BOOL CALLBACK ModalWnd_OnDestroy(HWINDOW hWindow);


//////内部使用//////////////////////////////////////////
struct messageBoxWnd_
{
	modalWindow_ modalWindow; //继承
	//----------------------------------
	HSTRING hString;  //消息框内容
	SIZE    sizeText; //文本区域大小
	int     type;
	HELE    hBtnOk;
	HELE    hBtnCancel;
};

//API:
int MsgBox_DoModal(HWND hWndParent, wchar_t *pText, wchar_t *pCaption, int type);     //启动模态窗口

//私有方法:
void MsgBox_CreateButton(HWINDOW hWindow); //创建按钮

//回调函数:
BOOL CALLBACK MsgBox_OnDestroy(HWINDOW hWindow);
BOOL CALLBACK MsgBox_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK MsgBox_OnEventBtnClickOk(HELE hEle, HELE hEventEle);
BOOL CALLBACK MsgBox_OnEventBtnClickCancel(HELE hEle, HELE hEventEle);


//hXCGUI:可以是元素句柄或窗口资源句柄,失败返回-1,如果按标题栏上的关闭按钮返回0
XC_API int WINAPI XMessageBox(HXCGUI hXCGUI, wchar_t *pText, wchar_t *pCaption = L"提示", int type = XMB_OK);