/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

////////////////////////////////////////////
//测试属性页///////////////////////////////

#if 0

BOOL CALLBACK MyEventPPageSelect(HELE hEle,HELE hEventEle,int id) //标签选择改变
{
	XTRACE("id=%d\n",id);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,350,300,L"炫彩界面库-窗口");


	//创建属性页元素页面
	HELE hPPage=XPPage_Create(10,10,300,200,hWindow);
	HELE hPage1=XEle_Create(0,0,10,10,hPPage);
	HELE hPage2=XEle_Create(0,0,10,10,hPPage);
	HELE hPage3=XEle_Create(0,0,10,10,hPPage);
	HELE hPage4=XEle_Create(0,0,10,10,hPPage);

	//设置页背景颜色,以便观察属性页切换的改变
	XEle_SetBkColor(hPage1,RGB(100,100,100));
	XEle_SetBkColor(hPage2,RGB(100,100,200));
	XEle_SetBkColor(hPage3,RGB(100,200,100));
	XEle_SetBkColor(hPage4,RGB(200,100,100));

	//创建静态文件元素,以便观察属性页切换的改变
	XStatic_Create(10,10,100,20,L"111",hPage1);
	XStatic_Create(10,10,100,20,L"222",hPage2);
	XStatic_Create(10,10,100,20,L"333",hPage3);
	XStatic_Create(10,10,100,20,L"444",hPage4);

	//将页添加到属性页元素
	XPPage_AddLabel(hPPage,L"111",hPage1);
	XPPage_AddLabel(hPPage,L"222",hPage2);
	XPPage_AddLabel(hPPage,L"333",hPage3);
	XPPage_AddLabel(hPPage,L"444",hPage4);

	XPPage_SetLabelSpacing(hPPage,1);

	XEle_RegisterEvent(hPPage,XE_PPAGE_SELECT,MyEventPPageSelect);
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}
#endif

#if 0
HELE hPPage=NULL;
BOOL CALLBACK OnBtnClick(HELE hEle,HELE hEleEvent)
{
//	XPPage_SetUp(hPPage);
//	XPPage_SetSelect(hPPage,3);
	XPPage_DeleteLabelAll(hPPage,0);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,300,L"测试窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建属性页
	hPPage=XPPage_Create(10,10,300,200,hWindow);
	XPPage_AddLabel(hPPage,L"111");
	XPPage_AddLabel(hPPage,L"222");
	XPPage_AddLabel(hPPage,L"333",NULL);
	XPPage_AddLabel(hPPage,L"444",NULL);

	XPPage_SetLabelSpacing(hPPage,2); //设置标签之间的间隔

	//创建页面
	HELE hPage1=XEle_Create(0,0,100,100);
	//HELE hPage2=XEle_Create(0,0,10,10);

	XPPage_SetBindEle(hPPage,1,hPage1);
	//XPPage_SetBindEle(hPPage,2,hPage2);

	XPPage_SetLabelText(hPPage,1,L"gggggggggg");
	XPPage_SetLabelWidth(hPPage,0,100);

	HELE hButton=XBtn_Create(320,10,60,20,L"button",hWindow);
	XEle_RegisterEvent(hButton,XE_BNCLICK,OnBtnClick);
	//XPPage_EnableScrollButton(hPPage,FALSE);
	//XEle_EnableBorder(hPPage,FALSE);
	XRunXCGUI();
	return 0;
}
#endif