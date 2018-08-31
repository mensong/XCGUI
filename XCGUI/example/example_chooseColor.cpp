/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建颜色选择编辑框元素
	HELE hColor=XCHColor_Create(10,10,100,20,hWindow);
//	XEle_SetTextColor(hColor,RGB(200,0,0));

	//XEdit_Create(10,10,100,20,hWindow);

	//HELE hView=XSView_GetView(hColor);
	//XEle_SetBkColor(hView,RGB(0,255,0));
	XRunXCGUI();
	return 0;
}
#endif