/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0
/////////////////////////////////////////////////
////组合框测试//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建组框
	//HELE hGroup=XGBox_Create(10,10,100,100,L"组框元素",hWindow);
	HELE hGroup=XEle_Create(10,10,100,100,hWindow);

	XRadio_Create(10,10,50,20,L"Radio",hGroup);
	XBtn_Create(10,50,50,20,L"Radio",hGroup);

	//隐藏组，子控件也一起隐藏
	XEle_ShowEle(hGroup, FALSE);

	XRunXCGUI();
	return 0;
}
#endif