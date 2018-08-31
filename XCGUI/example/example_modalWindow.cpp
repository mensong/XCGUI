/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


#if 0

class CModalX : public CXEventMsg
{
public:
	void Reg(HWINDOW hModal)
	{
		XCGUI_RegWndMessage(hModal,500,&CModalX::OnWndOther);
	}

	BOOL OnWndOther(HWINDOW hWindow,WPARAM wParam,LPARAM lParam)
	{
		return TRUE;
	}
};

//BOOL CALLBACK OnWndOther(HWINDOW hWindow,WPARAM wParam,LPARAM lParam)
//{
//	return TRUE;
//}

//模态窗口关闭 - 确定按钮
BOOL CALLBACK My_EventBtnClick_OK(HELE hEle,HELE hEventEle)
{

	//PostMessage(XEle_GetHWnd(hEle),500,2,2);
	XModalWnd_DoOk(XEle_GetHWindow(hEle));
	return TRUE;
}

//模态窗口关闭 - 取消按钮
BOOL CALLBACK My_EventBtnClick_Cancel(HELE hEle,HELE hEventEle)
{
	XModalWnd_DoCancel(XEle_GetHWindow(hEle));
	return TRUE;
}

//事件响应
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	//创建模态窗口
	HWINDOW hModal=XModalWnd_CreateWindow(200,200,L"炫彩界面库-模态窗口",XEle_GetHWnd(hEle));
	XWnd_EnableDragBorder(hModal,FALSE);
//	XWnd_SetTransparentFlag(hModal,XC_WIND_TRANSPARENT_SHADOW);
//	XWnd_SetTransparentAlpha(hModal,180); //设置透明度

	HELE hBtnOk=XBtn_Create(10,10,60,22,L"确定",hModal);
	HELE hBtnCancel=XBtn_Create(100,10,60,22,L"取消",hModal);
	//注册事件
	XEle_RegisterEvent(hBtnOk,XE_BNCLICK,My_EventBtnClick_OK);
	XEle_RegisterEvent(hBtnCancel,XE_BNCLICK,My_EventBtnClick_Cancel);

//	XWnd_RegisterMessage(hModal,500,&mm::OnWndOther);
	CModalX  mm;
	mm.Reg(hModal);

	//弹出模态窗口
	int result=XModalWnd_DoModal(hModal);
	if(XMB_OK==result)
	{
		//确定按钮
	}else if(XMB_CANCEL==result)
	{
		//取消按钮
	}else if(0==result)
	{
		//其他方式
	}

	return TRUE;
}

//模态窗口测试/////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"炫彩界面库-模态窗口测试");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHADOW);
//	XWnd_SetTransparentAlpha(hWindow,220); //设置透明度

	HELE hButton=XBtn_Create(10,10,100,25,L"弹出模态窗口",hWindow);

	//注册事件
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);

	XRunXCGUI();

	return 0;
}

#endif


#if 0
//模态窗口关闭 - 确定按钮
BOOL CALLBACK My_EventBtnClick_OK(HELE hEle,HELE hEventEle)
{

	XModalWnd_DoOk(XEle_GetHWindow(hEle));
	return TRUE;
}

//模态窗口关闭 - 取消按钮
BOOL CALLBACK My_EventBtnClick_Cancel(HELE hEle,HELE hEventEle)
{
	XModalWnd_DoCancel(XEle_GetHWindow(hEle));
	return TRUE;
}

BOOL CALLBACK My_EventBtnClick2(HELE hEle,HELE hEventEle)
{

	//创建模态窗口
	HWINDOW hModal=XModalWnd_CreateWindow(200,200,L"炫彩界面库-模态窗口",XEle_GetHWnd(hEle));
	XWnd_EnableDragBorder(hModal,FALSE);
	//	XWnd_SetTransparentFlag(hModal,XC_WIND_TRANSPARENT_SHADOW);
	//	XWnd_SetTransparentAlpha(hModal,180); //设置透明度

	HELE hBtnOk=XBtn_Create(10,10,60,22,L"确定",hModal);
	HELE hBtnCancel=XBtn_Create(100,10,60,22,L"取消",hModal);
	//注册事件
	XEle_RegisterEvent(hBtnOk,XE_BNCLICK,My_EventBtnClick_OK);
	XEle_RegisterEvent(hBtnCancel,XE_BNCLICK,My_EventBtnClick_Cancel);

	//	XWnd_RegisterMessage(hModal,500,&mm::OnWndOther);
//	CModalX  mm;
//	mm.Reg(hModal);

	//弹出模态窗口
	int result=XModalWnd_DoModal(hModal);
	if(XMB_OK==result)
	{
		//确定按钮
	}else if(XMB_CANCEL==result)
	{
		//取消按钮
	}else if(0==result)
	{
		//其他方式
	}

	return TRUE;
}
HWINDOW hWindow=NULL;
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	HWND hWnd=XWnd_GetHWnd(hWindow);
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"炫彩界面库-模态窗口测试2",hWnd);
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hButton=XBtn_Create(10,10,100,25,L"弹出模态窗口2",hWindow);

	//注册事件
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick2);

	return TRUE;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//创建窗口
	hWindow=XWnd_CreateWindow(0,0,300,300,L"炫彩界面库-模态窗口测试");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hButton=XBtn_Create(10,10,100,25,L"弹出模态窗口",hWindow);

	//注册事件
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);

	XRunXCGUI();

	return 0;
}
#endif

