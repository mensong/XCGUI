/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//创建图片元素
	HELE hPic=XPic_Create(10,10,100,100,hWindow);
	XPic_SetImage(hPic,XImage_LoadFile(L"image\\123.jpg")); //设置图片

	HELE hPic2=XPic_Create(150,10,100,100,hWindow);
	XPic_SetImage(hPic2,XImage_LoadFile(L"image\\123.jpg"));

	//XEle_ShowEle(hPic2,FALSE);
	XRunXCGUI();
	return 0;
}
#endif