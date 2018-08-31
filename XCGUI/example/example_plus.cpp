/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0
class CButtonBase : public CXEventMsg
{
public:
BOOL OnEventBtnClick(HELE hEle,HELE hEleEvent)
{
XTRACE("鼠标点击 base \n");
return FALSE;
}
int  yy;
};


class CButton : public CXEventMsg
{
public:
	HELE m_hButton;
	BOOL Create(HWINDOW hWindow)
	{
		m_hButton=XBtn_Create(10,10,100,25,L"演示按钮",hWindow);

		XCGUI_RegEleEvent(m_hButton,XE_BNCLICK,&CButton::OnEventBtnClick);
		XCGUI_RegEleEvent(m_hButton,XE_KEYDOWN,&CButton::OnEventKeyDown);
		XCGUI_RegEleEvent(m_hButton,XE_DESTROY,&CButton::OnBtnDestroy);
		XCGUI_RegEleMessage(m_hButton,XM_LBUTTONUP,&CButton::EleLButtonUp);
		return TRUE;
	}
	BOOL OnEventBtnClick(HELE hEle,HELE hEleEvent)
	{
		XTRACE("鼠标点击\n");
		return FALSE;
	}
	BOOL OnEventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam)
	{
		XTRACE("鼠标按键\n");
		return FALSE;
	}
	void OnBtnDestroy(HELE hEle)  //销毁
	{
		XTRACE("按钮销毁\n");
	}
	BOOL EleLButtonUp(HELE hEle,UINT flags,POINT *pPt)
	{
		XTRACE("按钮 EleLButtonUp\n");
		return FALSE;
	}
};

class CMyWnd : public CXEventMsg
{
public:
	HWINDOW m_hWindow;
	CButton  m_button;
	BOOL Create()
	{
		//创建窗口
		m_hWindow=XWnd_CreateWindow(400,200,400,300,L"炫彩界面库-窗口");
		XWnd_ShowWindow(m_hWindow,SW_SHOW);
		m_button.Create(m_hWindow);

		XCGUI_RegWndMessage(m_hWindow,WM_LBUTTONUP,&CMyWnd::OnWndLButtonUp);
		XCGUI_RegWndNCMessage(m_hWindow,XWM_NCLBUTTONUP,&CMyWnd::OnWndNCLButtonUp);
		return TRUE;
	}
	BOOL OnWndLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt)
	{
		XTRACE("窗口 OnWndLButtonUp\n");
		return FALSE;
	}
	BOOL OnWndNCLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt)
	{
		XTRACE("窗口 OnWndNCLButtonUp\n");
		return FALSE;
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(1874); 
	XInitXCGUI();

	CMyWnd  MyWnd;
	MyWnd.Create();

	XRunXCGUI();
	return 0;
}
#endif



#if 0

//CXEventMsg:C++消息事件接口类
//CMyWnd:我的窗口类
class CMyWnd : public CXEventMsg
{
public:
	HWINDOW m_hWindow; //窗口句柄
	HELE    m_hButton; //按钮句柄
	
	BOOL Create() //创建窗口和按钮
	{
		m_hWindow=XWnd_CreateWindow(0,0,400,300,L"炫彩界面库-窗口"); //创建窗口
		if(m_hWindow)
		{
			m_hButton =XBtn_Create(10,10,80,25,L"按钮",m_hWindow); //创建按钮
			XCGUI_RegEleEvent(m_hButton,XE_BNCLICK,&CMyWnd::OnEventBtnClick); //注册按钮点击事件
			
			XWnd_ShowWindow(m_hWindow,SW_SHOW); //显示窗口
			return TRUE;
		}
		return FALSE;
	}
	BOOL OnEventBtnClick(HELE hEle,HELE hEleEvent) //按钮点击事件响应
	{
		//弹出消息框
		XMessageBox(hEle,L"你点击了按钮",L"提示",XMB_OK | XMB_CANCEL);
		return FALSE;
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	CMyWnd  MyWnd;
	if(MyWnd.Create())
	{
		XRunXCGUI();
	}
	return 0;
}
#endif

/*
XCGUI_RegWndMessage(hWindow,type,memberFunction);//注册窗口消息

XCGUI_RegWndNCMessage(hWindow,type,memberFunction);//注册窗口逻辑非客户区消息

XCGUI_RegWndMsgProc(hWindow,memberFunction);//注册窗口消息处理过程

XCGUI_RegEleEvent(hEle,type,memberFunction);//注册元素事件

XCGUI_RegEleMessage(hEle,type,memberFunction);//注册元素消息

XCGUI_RegEleMsgProc(hEle,type,memberFunction);//注册元素消息处理过程

XCGUI_RegEleEventProc(hEle,type,memberFunction);//注册元素事件处理过程

XCGUI_SView_SetDrawScrollView(hEle,memberFunction);//注册滚动视图绘制

XCGUI_List_SetUserDrawItem(hEle,memberFunction);//注册列表项绘制

XCGUI_List_SetUserDrawItemHeader(hEle,memberFunction);//列表头项绘制

XCGUI_Tree_SetUserDrawItem(hEle,memberFunction); //树项绘制

XCGUI_ListBox_SetUserDrawItem(hEle,memberFunction); //列表框项绘制

*/