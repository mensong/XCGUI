/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0
HELE hTabBar=NULL;//元素句柄
BOOL CALLBACK OnButtonClick(HELE hEle,HELE hEventEle) //按钮事件
{
	XTabBar_SetSelect(hTabBar,1); //选择TabBar标签
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"炫彩界面库-窗口");

	HELE hButton1=XBtn_Create(10,50,100,20,L"111",hWindow);
	HELE hButton2=XBtn_Create(10,80,100,20,L"222",hWindow);
	HELE hButton3=XBtn_Create(10,110,100,20,L"333",hWindow);
	XEle_ShowEle(hButton2,FALSE);
	XEle_ShowEle(hButton3,FALSE);

	hTabBar=XTabBar_Create(10,10,180,25,hWindow);
	XTabBar_AddLabel(hTabBar,L"aaaaaaa",hButton1);
	XTabBar_AddLabel(hTabBar,L"bbbbbb",hButton2);
	XTabBar_AddLabel(hTabBar,L"ccccccc",hButton3);
	XTabBar_AddLabel(hTabBar,L"dddddd");
	XTabBar_AddLabel(hTabBar,L"eeeeee");

//	XTabBar_SetAlign(hTabBar,align_bottom);
//	XTabBar_EnableTile(hTabBar,TRUE);

	HELE hButton=XBtn_Create(230,10,80,20,L"选择 b",hWindow);

	XEle_RegisterEvent(hButton,XE_BNCLICK,OnButtonClick);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}
#endif