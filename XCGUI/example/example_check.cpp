/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0

//事件响应
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	wchar_t *pText=XBtn_GetText(hEventEle);
	if(XBtn_IsCheck(hEventEle)) //先前状态
	{
		XTRACEW(L"%s FALSE\n",pText);
	}else
	{
		XTRACEW(L"%s TRUE\n",pText);
	}
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");

	//创建复选按钮
	HELE hCheck1=XCheck_Create(10,10,60,20,L"check1",hWindow);
	HELE hCheck2=XCheck_Create(10,30,60,20,L"check2",hWindow);
	HELE hCheck3=XCheck_Create(10,50,60,20,L"check3",hWindow);
	HELE hCheck4=XCheck_Create(10,70,60,20,L"check4",hWindow);
	HELE hCheck5=XCheck_Create(10,90,60,20,L"check5",hWindow);
	XBtn_SetCheck(hCheck2,TRUE);
	XEle_EnableEle(hCheck2,FALSE);

	//注册事件
	XEle_RegisterEvent(hCheck1,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck2,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck3,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck4,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck5,XE_BNCLICK,My_EventBtnClick);

	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();
	return 0;
}
#endif