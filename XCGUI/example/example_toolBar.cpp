/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


//图标显示在文字左标
//图标显示在文字右边
//图标显示在文字上边
//图标显示在文件下边
//仅显示图标
//仅显示文字
#if 0
////////////工具条//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"测试窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hToolBtn1=XToolBarBtn_Create(2,2,L"测试1");
	HELE hToolBtn2=XToolBarBtn_Create(2,2,L"测试2");
	HELE hToolBtn3=XToolBarBtn_Create(2,2,L"禁用3");
	HELE hToolBtn4=XToolBarBtn_Create(2,2,L"测试4");
	HELE hToolBtn5=XToolBarBtn_Create(2,2,L"文本5");

	//XToolBarBtn_SetImage(hToolBtn1, XImage_LoadFile(L"image/1073.ico"));
	//XToolBarBtn_SetImage(hToolBtn2, XImage_LoadFile(L"image/save.ico"));
	//XToolBarBtn_SetImage(hToolBtn3, XImage_LoadFile(L"image/open.ico"));
	//XToolBarBtn_SetImage(hToolBtn4, XImage_LoadFile(L"image/open.ico"));

	HELE hEdit=XEdit_Create(0,0,60,20);
	HELE hCheck=XCheck_Create(0,0,60,20,L"check");

	HXCGUI hToolBar=XToolBar_Create(0,30,200,28,hWindow);
	
	XToolBar_InsertEle((HELE)hToolBar, hToolBtn1);
	XToolBar_InsertEle((HELE)hToolBar, hToolBtn2);
	XToolBar_InsertEle((HELE)hToolBar, hEdit);
	XToolBar_InsertEle((HELE)hToolBar, hToolBtn3);
	XToolBar_InsertEle((HELE)hToolBar, hToolBtn4);
	XToolBar_InsertEle((HELE)hToolBar, hToolBtn5);
	XToolBar_InsertEle((HELE)hToolBar, hCheck);
	XToolBar_InsertSeparator((HELE)hToolBar, 1);

	XEle_EnableEle(hToolBtn3,FALSE);

	XToolBarBtn_Adjust(hToolBtn1);
	XToolBarBtn_Adjust(hToolBtn2);
	XToolBarBtn_Adjust(hToolBtn3);
	XToolBarBtn_Adjust(hToolBtn4);
	XToolBarBtn_Adjust(hToolBtn5);


	XBtn_Create(10,50,100,25,L"button",hWindow);

	HELE hMenuBar=XMenuBar_Create(10,10,300,26);
	
	XMenuBar_AddButton(hMenuBar,L"文件");
	XMenuBar_AddButton(hMenuBar,L"编辑");
	XMenuBar_AddButton(hMenuBar,L"视图");

	XMenuBar_AddMenuItem(hMenuBar,0,1,L"111");
	XMenuBar_AddMenuItem(hMenuBar,0,2,L"222");
	XMenuBar_AddMenuItem(hMenuBar,0,3,L"333");

	XMenuBar_AddMenuItem(hMenuBar,1,4,L"444");
	XMenuBar_AddMenuItem(hMenuBar,1,5,L"555");
	XMenuBar_AddMenuItem(hMenuBar,1,6,L"666");

	XMenuBar_AddMenuItem(hMenuBar,2,7,L"777");
	XMenuBar_AddMenuItem(hMenuBar,2,8,L"888");

	XWnd_AddMenuBar(hWindow,hMenuBar);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    XInitXCGUI();

    //创建窗口:
    HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"炫彩界面库-窗口");
    XWnd_ShowWindow(hWindow,SW_SHOW);

    //创建工具条按钮
    HELE hToolBtn1=XToolBarBtn_Create(2,2,L"测试1");
    HELE hToolBtn2=XToolBarBtn_Create(2,2,L"测试2");
    HELE hToolBtn3=XToolBarBtn_Create(2,2,L"禁用3");
    HELE hToolBtn4=XToolBarBtn_Create(2,2,L"测试4");
    HELE hToolBtn5=XToolBarBtn_Create(2,2,L"文本5");
    //设置图标
	XBtn_SetIcon(hToolBtn1,XImage_LoadFile(L"image/1073.ico"));
	XBtn_SetIcon(hToolBtn2,XImage_LoadFile(L"image/save.ico"));
	XBtn_SetIcon(hToolBtn3,XImage_LoadFile(L"image/open.ico"));
	XBtn_SetIcon(hToolBtn4,XImage_LoadFile(L"image/open.ico"));

    HELE hEdit=XEdit_Create(0,0,60,20);
    HELE hCheck=XCheck_Create(0,0,60,20,L"check");
    XEle_SetBkTransparent(hCheck,TRUE);
    //创建工具条
    HELE hToolBar=XToolBar_Create(0,30,200,28,hWindow);
    //将元素添加到工具条上
    XToolBar_InsertEle(hToolBar,hToolBtn1);
    XToolBar_InsertEle(hToolBar,hToolBtn2);
    XToolBar_InsertEle(hToolBar,hEdit);
    XToolBar_InsertEle(hToolBar,hToolBtn3);
    XToolBar_InsertEle(hToolBar,hToolBtn4);
    XToolBar_InsertEle(hToolBar,hToolBtn5);
    XToolBar_InsertEle(hToolBar,hCheck);
    XToolBar_InsertSeparator(hToolBar,1);
    //禁用指定元素
    XEle_EnableEle(hToolBtn3,FALSE);
    //自动调整工具条按钮大小
    XToolBarBtn_Adjust(hToolBtn1);
    XToolBarBtn_Adjust(hToolBtn2);
    XToolBarBtn_Adjust(hToolBtn3);
    XToolBarBtn_Adjust(hToolBtn4);
    XToolBarBtn_Adjust(hToolBtn5);

    XRunXCGUI();
    return 0;
}
#endif