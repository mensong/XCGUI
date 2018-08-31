/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0
 BOOL CALLBACK OnEleDraw(HELE hEle,HDC hdc)
 {
//	 RECT rc={10,10,30,30};
//	 XDraw_FillSolidRect(hdc,&rc,RGB(100,100,100));
	return TRUE;
 }

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XWnd_SetBkColor(hWindow,RGB(255,0,0));

//	HELE hBtn=XBtn_Create(10,10,100,100,L"123",hWindow);
//	XEle_SetId(hBtn,111);
	//XEle_RegisterMessage(hBtn,XM_PAINT,OnEleDraw);
//	XEle_SetBkTransparent(hBtn,TRUE);


	XCHColor_Create(10,10,100,20,hWindow);

	XWnd_SetImageBorderBottom(hWindow,XImage_LoadFile(L"image\\111.jpg"));
	XWnd_SetBorderSize(hWindow,8,8,8,110);

//	XWnd_SetImage(hWindow,XImage_LoadFile(L"image\\frame.jpg"));

	XRunXCGUI();

	return 0;
}
#endif

#if 0

#define IDB_BUTTON1  L"IDB_BUTTON1"  //在资源文件中按钮ID名称

//加载XML文件创建窗口 - 演示2
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //初始化界面库

	HXMLRES  hRes=XXmlRes_Load(L"xml1\\resource.res");	//加载资源
	if(NULL==hRes)
	{
		MessageBox(NULL,L"加载资源失败",L"错误",0);
		return 0;
	}

	HWINDOW hWindow=XC_LoadXML_Window(L"xml1\\layout_QQ新版.xml",hRes); //创建窗口
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"加载XML失败",L"错误",0);
		return 0;
	}

	if(FALSE==XC_LoadXML_Style(hWindow,L"xml1\\style.css",hRes))	//加载样式文件
	{
		MessageBox(NULL,L"加载样式失败",L"错误",0);
		return 0;
	}

	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口

// 	//下面测试我们的UI文件
// 	int idButton1=XXmlRes_FindId(hRes,IDB_BUTTON1); //通过按钮资源名,查找到ID
// 	HELE hbutton1=XWnd_GetEle(hWindow,idButton1);   //通过ID获取按钮句柄
// 	if(XC_BUTTON==XC_GetObjectType(hbutton1))       //判断是否为按钮
// 	{
// 		wchar_t *pBtnText=XBtn_GetText(hbutton1);  //获取按钮文本内容
// 
// 		wchar_t buf[MAX_PATH]={0};
// 		swprintf_s(buf,MAX_PATH,L"测试按钮[%s]文本是:[%s]",IDB_BUTTON1,pBtnText);
// 
// 		XMessageBox(hWindow,buf,L"炫彩界面库-测试"); //显示结果信息
// 	}else
// 	{
// 		XTRACE("测试资源有错误\n");
// 	}
// 	XXmlRes_Destroy(hRes); //不使用了销毁资源文件

	XRunXCGUI(); //运行

	return 0;
}
#endif

#if 0
//测试XML布局文件
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//SSLWnd_Init("3BAJ-G934-A6H1-8AVB-A14C-9009-FAAC-908F");
	XInitXCGUI(); //初始化界面库

	XC_LoadXML_WindowRes(1,L"123");
	HXMLRES  hRes=XXmlRes_Load(L"360\\mainFrame.res");	//加载资源
	if(NULL==hRes)
	{
		MessageBox(NULL,L"加载资源失败",L"错误",0);
		return 0;
	}

	HWINDOW hWindow=XC_LoadXML_Window(L"360\\mainFrame.xml",hRes); //创建窗口
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"加载XML失败",L"错误",0);
		return 0;
	}

	if(FALSE==XC_LoadXML_Style(hWindow,L"360\\mainFrame.css",hRes))	//加载样式文件
	{
		MessageBox(NULL,L"加载样式失败",L"错误",0);
		return 0;
	}

	//XWnd_EnableBorderStrokeOuter(hWindow,FALSE);
	XWnd_SetBorderStrokeOuterColor(hWindow,RGB(30,30,30),RGB(0,0,0));
	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口

	XXmlRes_Destroy(hRes); //不使用了销毁资源文件

	XRunXCGUI(); //运行

	return 0;
}
#endif


#if 0
//测试XML布局页文件
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//XInitXCGUI("3BAJ-G934-A6H1-8AVB-A14C-9009-FAAC-908F"); //初始化界面库
	XInitXCGUI(); //初始化界面库

	HXMLRES  hRes=XXmlRes_Load(L"360v2\\resources.res");	//加载资源
	if(NULL==hRes)
	{
		MessageBox(NULL,L"加载资源失败",L"错误",0);
		return 0;
	}

	HWINDOW hWindow=XC_LoadXML_Window(L"360v2\\layout.xml",hRes); //创建窗口
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"加载XML失败",L"错误",0);
		return 0;
	}

	//XC_LoadXML_Page(hWindow,L"360\\mainPage2.xml",hRes);

	if(FALSE==XC_LoadXML_Style(hWindow,L"360v2\\style.css",hRes))	//加载样式文件
	{
		MessageBox(NULL,L"加载样式失败",L"错误",0);
		return 0;
	}

//	HELE hBtn=XWnd_GetEle(hWindow,188);
//	XBtn_SetImageLeave(hBtn,XImage_LoadFile(L"360v2\\image\\frame.jpg"));

	//HELE hParentEle=XWnd_GetEle(hWindow,501);

	//XWnd_EnableBorderStrokeOuter(hWindow,FALSE);
	//XWnd_SetBorderStrokeOuterColor(hWindow,RGB(30,30,30),RGB(0,0,0));
	//XWnd_SetBorderStrokeOuterColor(hWindow,RGB(255,0,0),RGB(0,255,0));
	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口

	XXmlRes_Destroy(hRes); //不使用了销毁资源文件

	XRunXCGUI(); //运行

	return 0;
}
#endif

#if 0
//测试XML布局页文件 主测试布局文件
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //初始化界面库

	//HWINDOW hWindow=XC_LoadXML_Window(L"F:\\项目\\UI设计器\\GuiDesigner(2012_03_10)\\Debug\\MyProject\\layout.xml"); //创建窗口
	HWINDOW hWindow=XC_LoadXML_Window(L"360\\mainFrame.xml"); //创建窗口
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"加载XML失败",L"错误",0);
		return 0;
	}
	//XWnd_SetBkColor(hWindow,RGB(255,0,0));
	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口
	XRunXCGUI(); //运行

	return 0;
}
#endif