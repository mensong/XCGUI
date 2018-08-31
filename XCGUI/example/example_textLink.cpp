/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


#if 0
BOOL CALLBACK OnLinkClick(HELE hEle,HELE hEventEle) //事件响应
{
	XMessageBox(hEle,L"打开网站:http://www.xcgui.com/",L"提示",XMB_OK);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"炫彩界面库-窗口");

	//创建文件链接元素
	HELE hLink=XTextLink_Create(10,10,138,20,L"http://www.xcgui.com/",hWindow);

	XEle_RegisterEvent(hLink,XE_BNCLICK,OnLinkClick);//注册事件

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}
#endif



#if 0
BOOL CALLBACK OnLinkClick(HELE hEle,HELE hEventEle) //事件响应
{
	XMessageBox(hEle,L"打开网站:http://www.xcgui.com/",L"提示",XMB_OK);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"炫彩界面库-窗口");

	//创建文件链接元素
	HELE hLink=XTextLink_Create(10,10,200,20,L"http://www.xcgui.com/",hWindow);
	XEle_SetBkColor(hLink,RGB(255,0,0));

	XTextLink_ShowUnderline(hLink,TRUE,TRUE);

	XTextLink_AdjustSize(hLink);
	XEle_RegisterEvent(hLink,XE_BNCLICK,OnLinkClick);//注册事件

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}
#endif