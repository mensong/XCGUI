/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 1

HELE hEdit;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle) //按钮点击事件
{
	XEdit_SetText(hEdit,L"0123\r\n45\r\n789123");
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick2(HELE hEle,HELE hEventEle) //获取内容
{
	wchar_t str[256]=L"------------------------------------";
	XEdit_GetText(hEdit,str,256);
	XMessageBox(hEle,str,L"获取内容");
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick3(HELE hEle,HELE hEventEle) //获取选择内容
{
	wchar_t str[256]=L"----------------------------------";
	XEdit_GetSelectText(hEdit,str,256);
	XMessageBox(hEle,str,L"获取选择内容");
	
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick4(HELE hEle, HELE hEventEle) //设置选择内容
{
	//XEdit_SetSelectText(hEdit, 0, 1, 0, 5);

	return TRUE;
}

////////////////////////////////////////////
//测试编辑框/密码框///////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,350,300,L"炫彩界面库-窗口");
	XWnd_SetBkColor(hWindow,RGB(200,200,200));
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建编辑框
	hEdit=XEdit_Create(10,10,200,200,hWindow);
	XEdit_EnableMultiLine(hEdit,TRUE); //启用多行输入
//	XEdit_EnableNumber(hEdit,TRUE);

	HELE hButton=XBtn_Create(220,10,80,20,L"设置内容",hWindow);
	XEle_EnableFocus(hButton,FALSE);

	HELE hButton2=XBtn_Create(220,40,80,20,L"获取内容",hWindow);
	HELE hButton3=XBtn_Create(220,80,80,20,L"获取选择内容",hWindow);

	HELE hButton4 = XBtn_Create(220, 120, 80, 20, L"设置选择内容", hWindow);

	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,MyEventBtnClick2);
	XEle_RegisterEvent(hButton3, XE_BNCLICK, MyEventBtnClick3);
	XEle_RegisterEvent(hButton4, XE_BNCLICK, MyEventBtnClick4);

	XRunXCGUI();
	return 0;
}
#endif


#if 0
//////////////////////////////////////////////////////////////////
//测试密码框///////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"测试窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hEdit=XEdit_Create(10,10,200,200,hWindow);
	XSView_SetImage(hEdit, XImage_LoadFile(L"image/123.jpg"));
	//XSView_EnableImageStretch(hEdit,TRUE);
	XEdit_EnableMultiLine(hEdit,TRUE);
	XRunXCGUI();
	return 0;
}
#endif


#if 0

//测试编辑框框//////修改字体/////////////////////////
HELE hEdit=NULL;
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	
	HFONT hFont=CreateFont(
		26,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));                 // lpszFacename

	
	XEle_SetFont(hEdit, (HFONTX)hFont);//(HFONT)GetStockObject(DEVICE_DEFAULT_FONT));

	//XEdit_InsertText(hEdit,L"末尾",-1,-1);
	XEle_RedrawEle(hEdit);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"测试窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	hEdit=XEdit_Create(10,50,200,200,hWindow);
	XEdit_EnableMultiLine(hEdit,TRUE);
	XEdit_SetText(hEdit,L"测试字体");

	XEle_SetTextColor(hEdit,RGB(255,0,0));

	HELE hButton=XBtn_Create(10,10,100,20,L"修改字体",hWindow);
	XEle_EnableFocus(hButton,FALSE);
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);
	XRunXCGUI();
	return 0;
}
#endif

#if 0
//测试编辑框/设置插入符位置///////////////////////////////
HELE hEdit;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle) //按钮点击事件
{
//	XEdit_SetPos(hEdit,0,20);
//	XComboBox_SetText(hEdit,NULL);
//	XEle_SetFocus(hEdit,TRUE);
//	XEle_RedrawEle(hEdit);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,350,300,L"炫彩界面库-窗口");

	//创建编辑框
//	hEdit=XEdit_Create(10,10,200,200,hWindow);

	hEdit=XEdit_Create(10,10,100,100,hWindow);
	//XEdit_EnableMultiLine(hEdit,TRUE); //启用多行输入

//	hEdit=XComboBox_Create(10,10,100,20,hWindow);
//	XEdit_Create(10,50,100,20,hWindow);
	HELE hButton=XBtn_Create(220,10,80,20,L"设置内容",hWindow);
	//XEle_EnableFocus(hButton,FALSE);

	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//测试编辑框/设置插入符位置///////////////////////////////
HELE hEdit;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle) //按钮点击事件
{
	//XEdit_SetPos(hEdit,0,20);
	XMessageBox(hEle,L"test",L"tt",XMB_OK);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
//SSLWnd_Init("GAC5-3P9A-BU48-7C11-B66A-7EFB-E5C5-718B");
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,350,300,L"炫彩界面库-窗口",NULL);

	//创建编辑框
//	hEdit=XEdit_Create(10,10,200,200,hWindow);
	hEdit=XEdit_Create(10,10,100,20,hWindow);
	hEdit=XEdit_Create(10,50,100,20,hWindow);
	XWnd_SetCaretColor(hWindow,RGB(0,255,0));
	XEdit_SetCaretWidth(hEdit,3);
	XEle_SetTextColor(hEdit,RGB(255,0,0));

//	XEdit_EnableMultiLine(hEdit,TRUE); //启用多行输入

	HELE hButton=XBtn_Create(220,10,80,20,L"设置内容",hWindow);
//	XEle_EnableFocus(hButton,FALSE);

	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();
	return 0;
}
#endif


#if 0
//编辑框贴图
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,260,150,L"炫彩界面库-窗口");

	HELE hEdit=XEdit_Create(10,10,100,22,hWindow);
	XEle_EnableBorder(hEdit,FALSE); //不绘制边框
	XEdit_SetImageLeave(hEdit,XImage_LoadFile(L"image//edit_leave.jpg"));
	XEdit_SetImageStay(hEdit,XImage_LoadFile(L"image//edit_stay.jpg"));

	XBtn_Create(130,10,60,20,L"button",hWindow);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
#endif


#if 0
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,260,260,L"炫彩界面库-窗口");

	HELE hEdit=XEdit_Create(10,10,200,200,hWindow);
	XSView_SetSpacing(hEdit,10,10,10,10);
	XEdit_SetTextSpacingLeft(hEdit,30);
	XEdit_EnableMultiLine(hEdit, TRUE);
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
#endif