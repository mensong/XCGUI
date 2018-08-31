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
	XInitXCGUI(); //初始化界面库
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,220,L"炫彩界面库-窗口");

	HELE hGif=XGif_Create(10,10,200,150,hWindow);

	//设置图片
	//XGif_SetImage(hGif,L"image\\hearts.gif"); //从文件
	//XGif_SetImageRes(hGif,IDR_GIF2,L"GIF");  //从资源
	XGif_SetImageZip(hGif,L"image//hearts.zip",L"hearts.gif"); //从压缩包

	//XBtn_Create(10,10,100,25,L"button",hWindow);

	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口
	XRunXCGUI(); //运行

	return 0;
}
#endif