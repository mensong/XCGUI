/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


#if 1

//事件响应
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	//弹出消息框
	int res=XMessageBox(XEle_GetHWindow(hEle),L"123\n456",L"提示",XMB_OK | XMB_CANCEL);

	RECT rc={120,10,200,30};
	XEle_SetRect(hEle,&rc,TRUE);

	return FALSE;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(/*L"E:\\Work\\炫彩界面库源码(DirectUI,v1.5.1)\\XCGUI\\XCGUI.ico", L"E:\\Work\\炫彩界面库源码(DirectUI,v1.5.1)\\XCGUI\\small.ico"*/);

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);


	//工具提示按钮
	HELE hButton=XBtn_Create(10,10,100,25,L"工具提示按钮",hWindow);
	XEle_EnableToolTips(hButton,TRUE);
	XEle_SetToolTips(hButton,L"工具提示...");

	//贴图按钮
	HELE hButton2=XBtn_Create(10,50,80,25,NULL,hWindow);
	//XBtn_SetImageLeave(hButton2,XImage_LoadFile(L"image\\btn_leave.bmp"));
	//XBtn_SetImageStay(hButton2,XImage_LoadFile(L"image\\2.bmp"));
	//XBtn_SetImageDown(hButton2,XImage_LoadFile(L"image\\3.bmp"));

	//弹出消息框
	HELE hButton3=XBtn_Create(10,90,80,25,L"弹出消息框",hWindow);

	//禁用状态按钮
	HELE hButton4=XBtn_Create(10,130,80,25,L"禁用按钮",hWindow);
	XEle_EnableEle(hButton4,FALSE);

	//注册事件
	XEle_RegisterEvent(hButton3,XE_BNCLICK,My_EventBtnClick);

	
	XRunXCGUI();
	return 0;
}
#endif

#if 0
//测试图标按钮
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
XInitXCGUI();

//创建窗口
HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"炫彩界面库-窗口");
XWnd_ShowWindow(hWindow,SW_SHOW);

//工具提示按钮
HELE hButton=XBtn_Create(10,10,100,100,L"按钮",hWindow);
///	XBtn_SetIcon(hButton,XImage_LoadFile(L"image\\149.gif"));
XBtn_SetTextAlign(hButton, DT_CENTER | DT_SINGLELINE);

XBtn_SetIconAlign(hButton,XC_ICON_ALIGN_BOTTOM);
//贴图按钮
//	HELE hButton2=XBtn_Create(10,50,80,25,NULL,hWindow);
//	XBtn_SetImageLeave(hButton2,XImage_LoadFile(L"image\\btn_leave.bmp"));
//	XBtn_SetImageStay(hButton2,XImage_LoadFile(L"image\\2.bmp"));
//	XBtn_SetImageDown(hButton2,XImage_LoadFile(L"image\\3.bmp"));


XRunXCGUI();
return 0;
}
#endif

#if 0
//测试按钮
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	XWnd_SetCaptionHeight(hWindow,100);


	HIMAGE hImage=XImage_LoadFile(L"image\\logo.png");
	XImage_SetDrawType(hImage,XC_IMAGE_TILE);
	XWnd_SetImageCaption(hWindow,hImage);



	//工具提示按钮
	HELE hButton=XBtn_Create(10,10,100,60,L"");
//	HIMAGE hImage=XImage_LoadFile(L"image\\logo.png");
	HIMAGE hImage_down=XImage_LoadFile(L"image\\logo_down.png");
	HIMAGE hImage_stay=XImage_LoadFile(L"image\\logo_hover.png");
	XImage_SetDrawType(hImage,XC_IMAGE_TILE);
	XImage_SetDrawType(hImage_down,XC_IMAGE_TILE);
	XImage_SetDrawType(hImage_stay,XC_IMAGE_TILE);

	XBtn_SetImageLeave(hButton,hImage);
	XBtn_SetImageDown(hButton,hImage_down);
	XBtn_SetImageStay(hButton,hImage_stay);
	XEle_SetBkTransparent(hButton,TRUE);

	XEle_EnableFocus(hButton,FALSE);

	XWnd_AddEleNC(hWindow,hButton);

	XRunXCGUI();
	return 0;
}
#endif


#if 0
//动画按钮

HIMAGE hImage1=NULL;
HIMAGE hImage2=NULL;
HIMAGE hImage3=NULL;
HIMAGE hImage4=NULL;
HIMAGE hImage5=NULL;
HIMAGE hImage6=NULL;
void CreateButton(HWINDOW hWindow,int x,int y)
{
	HELE hButton=XBtn_Create(x,y,37,42,L"B",hWindow);
	XBtn_AddAnimationFrame(hButton,hImage1,50); //添加动画帧
	XBtn_AddAnimationFrame(hButton,hImage2,50);
	XBtn_AddAnimationFrame(hButton,hImage3,50);
	XBtn_AddAnimationFrame(hButton,hImage4,50);
	XBtn_AddAnimationFrame(hButton,hImage5,50);
	XBtn_AddAnimationFrame(hButton,hImage6,50);
	XBtn_EnableAnimation(hButton,TRUE); //启动动画
}

void CreateButtonLoop(HWINDOW hWindow,int x,int y)
{
	HELE hButton=XBtn_Create(x,y,37,42,L"B",hWindow);
	XBtn_AddAnimationFrame(hButton,hImage1,50); //添加动画帧
	XBtn_AddAnimationFrame(hButton,hImage2,50);
	XBtn_AddAnimationFrame(hButton,hImage3,50);
	XBtn_AddAnimationFrame(hButton,hImage4,50);
	XBtn_AddAnimationFrame(hButton,hImage5,50);
	XBtn_AddAnimationFrame(hButton,hImage6,50);
	XBtn_EnableAnimation(hButton,TRUE,TRUE); //循环播放
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,200,L"炫彩界面库-窗口");

	hImage1=XImage_LoadFile(L"animation\\1.png");
	hImage2=XImage_LoadFile(L"animation\\2.png");
	hImage3=XImage_LoadFile(L"animation\\3.png");
	hImage4=XImage_LoadFile(L"animation\\4.png");
	hImage5=XImage_LoadFile(L"animation\\5.png");
	hImage6=XImage_LoadFile(L"animation\\6.png");

	int left=10;
	CreateButton(hWindow,left,20); left+=38;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;
	CreateButton(hWindow,left,20); left+=35;

	left=10;
	CreateButtonLoop(hWindow,left,50); left+=35;
	CreateButtonLoop(hWindow,left,50); left+=35;

	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();

	return 0;
}
#endif

