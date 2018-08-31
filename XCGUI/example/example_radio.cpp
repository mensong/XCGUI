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
		XTRACEW(L"%s 按钮已经是选择状态,不处理\n",pText);
	}else
	{
		XTRACEW(L"%s 被选择\n",pText);
	}
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHADOW);

	HELE hRadio1=XRadio_Create(10,10,100,20,L"radio1",hWindow);
	HELE hRadio2=XRadio_Create(10,30,100,20,L"radio2",hWindow);
	HELE hRadio3=XRadio_Create(10,50,100,20,L"radio3",hWindow);
	HELE hRadio4=XRadio_Create(10,70,100,20,L"radio4",hWindow);
	HELE hRadio5=XRadio_Create(10,90,100,50,L"radio5",hWindow);
	XBtn_SetCheck(hRadio3,TRUE);

	//设置ID以便分组
	XEle_SetId(hRadio1,201);
	XEle_SetId(hRadio2,202);
	XEle_SetId(hRadio3,203);
	XEle_SetId(hRadio4,204);
	XEle_SetId(hRadio5,205);

//	XBtn_SetImageLeave(hRadio2,XImage_LoadFile(L"image/btn_leave.bmp"));
//	XBtn_EnableImageStretch(hRadio2,TRUE);

	XEle_SetBkColor(hRadio5,RGB(220,220,220));
	XEle_EnableEle(hRadio3,FALSE);

	//注册事件
	XEle_RegisterEvent(hRadio1,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hRadio2,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hRadio3,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hRadio4,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hRadio5,XE_BNCLICK,My_EventBtnClick);
	
	XRunXCGUI();
	return 0;
}
#endif

#if 0

//按钮分组测试
HWINDOW hWindow=NULL;
HIMAGE hImage1=NULL;
HIMAGE hImage2=NULL;
HIMAGE hImage3=NULL;
HIMAGE hImage4=NULL;
HIMAGE hImage5=NULL;

HIMAGE hImage1_check=NULL;
HIMAGE hImage2_check=NULL;
HIMAGE hImage3_check=NULL;
HIMAGE hImage4_check=NULL;
HIMAGE hImage5_check=NULL;

HELE  CreateRadio(int x,int y,wchar_t *pName)
{
	HELE hRadio=XRadio_Create(x,y,96,34,pName,hWindow);

	XRadio_SetImageLeave_UnCheck(hRadio,hImage1);
	XRadio_SetImageStay_UnCheck(hRadio,hImage2);
	XRadio_SetImageDown_UnCheck(hRadio,hImage3);

	XRadio_SetImageLeave_Check(hRadio,hImage1_check);
	XRadio_SetImageStay_Check(hRadio,hImage2_check);
	XRadio_SetImageDown_Check(hRadio,hImage3_check);

	XRadio_EnableButtonStyle(hRadio,TRUE);
	XRadio_SetGroupID(hRadio,1);

	return hRadio;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	hWindow=XWnd_CreateWindow(0,0,400,300,L"炫彩界面库-窗口");

	hImage1=XImage_LoadFile(L"image\\button_leave.png");
	hImage2=XImage_LoadFile(L"image\\button_stay.png");
	hImage3=XImage_LoadFile(L"image\\button_down.png");
	hImage1_check=XImage_LoadFile(L"image\\button_check_leave.png");
	hImage2_check=XImage_LoadFile(L"image\\button_check_stay.png");
	hImage3_check=XImage_LoadFile(L"image\\button_check_down.png");

	HELE hRadio1=CreateRadio(10,10,L"Radio1");
	HELE hRadio2=CreateRadio(10,50,L"Radio2");
	HELE hRadio3=CreateRadio(10,90,L"Radio3");
	HELE hRadio4=CreateRadio(10,130,L"Radio4");
	HELE hRadio5=CreateRadio(10,170,L"Radio5");
	XBtn_SetCheck(hRadio1,TRUE);

///////////////////////////////////////////////////////
	HELE  hEle1=XEle_Create(130,10,200,35,hWindow);
	HELE  hEle2=XEle_Create(130,50,200,35,hWindow);
	HELE  hEle3=XEle_Create(130,90,200,35,hWindow);
	HELE  hEle4=XEle_Create(130,130,200,35,hWindow);
	HELE  hEle5=XEle_Create(130,170,200,35,hWindow);

	XRadio_SetBindEle(hRadio1,hEle1);
	XRadio_SetBindEle(hRadio2,hEle2);
	XRadio_SetBindEle(hRadio3,hEle3);
	XRadio_SetBindEle(hRadio4,hEle4);
	XRadio_SetBindEle(hRadio5,hEle5);

	XEle_SetBkColor(hEle1,RGB(249,141,235));
	XEle_SetBkColor(hEle2,RGB(105,20,193));
	XEle_SetBkColor(hEle3,RGB(0,179,138));
	XEle_SetBkColor(hEle4,RGB(213,48,68));
	XEle_SetBkColor(hEle5,RGB(42,110,187));

	XEle_ShowEle(hEle2,FALSE);
	XEle_ShowEle(hEle3,FALSE);
	XEle_ShowEle(hEle4,FALSE);
	XEle_ShowEle(hEle5,FALSE);
	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();

	return 0;
}
#endif
