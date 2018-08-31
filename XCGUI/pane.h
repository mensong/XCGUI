/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

//布局窗格

struct layoutCell_;

struct layoutPane_
{
	ele_  ele; //继承
	//----------------------------------
	layoutCell_  *pCell;          //窗格绑定的单元格
	pane_state_  state;           //锁定1 停靠2 浮动3 关闭4
	int          captionHeight;   //标题栏高度
	HSTRING      hTitle;          //标题

	BOOL         bDownCaption;    //鼠标按在窗格标题栏上
	POINT        downPt;          //鼠标在标题栏上的坐标

	int          bFixedSize;      //窗格固定大小,如果为-1非固定大小
	BOOL         bActivate;     //窗格是否激活 WA_ACTIVE

	BOOL         bInFrame; //窗格是否在框架视图

	HELE hBtnClose;  //关闭按钮
	HELE hAutoHide;  //自动隐藏
	HELE hBtnMenu;   //菜单按钮

	align_type_  dockAlign;  //窗格在哪个码头上

	HELE  hView;    //客户区绑定视图元素
	HELE  hToolBar; //工具条
	HELE  hMenuBar; //菜单条

	int left, top, right, bottom; //视图边框间隔
};

//每个窗格附带一个布局单元格


//API:
XC_API HELE WINAPI XPane_Create(wchar_t *pTitle = NULL, HWINDOW hFrameWnd = NULL);  //创建按钮
XC_API wchar_t* WINAPI XPane_GetTitle(HELE hEle);
XC_API void WINAPI XPane_Hide(HELE hEle);      //隐藏窗格
XC_API void WINAPI XPane_Dock(HELE hEle);      //停靠窗格,自动隐藏
XC_API void WINAPI XPane_Lock(HELE hEle);      //锁定窗格
XC_API void WINAPI XPane_popup(HELE hEle);     //弹出窗格,当在码头上
XC_API void WINAPI XPane_Show(HELE hEle);     //隐藏-显示浮动窗格

XC_API HPANE_GROUP WINAPI XPane_GetGroup(HELE hEle); //获取窗格所属组,如果没有组返回空

//显示窗格,可以激活窗格组中隐藏的窗格

XC_API BOOL WINAPI XPane_Destroy(HELE hEle); //销毁窗格 


XC_API pane_state_ WINAPI XPane_GetState(HELE hEle);  //获取状态

XC_API void WINAPI XPane_DragPane(HELE hEle, POINT *pPtDown); //拖动窗格
XC_API void WINAPI XPane_DragGroup(HELE hEle, POINT *pPtDown);//拖动窗格组
XC_API void WINAPI XPane_FloatPane(HELE hEle); //浮动窗格


XC_API void WINAPI XPane_SetView(HELE hEle, HELE hView);
XC_API void WINAPI XPane_SetToolBar(HELE hEle, HELE hToolBar); //设置工具条
XC_API void WINAPI XPane_SetMenuBar(HELE hEle, HELE hMenuBar); //设置菜单条

//设置边框间隔
XC_API void WINAPI XPane_SetSpacing(HELE hEle, int left, int top, int right, int bottom);

XC_API void WINAPI XPane_SetFixedSize(HELE hEle, BOOL bFixedSize); //设置窗格固定大小,如果为FALSE非固定大小
XC_API void WINAPI XPane_SetTitle(HELE hEle, wchar_t *pTitle);

XC_API void WINAPI XPane_SetActivate(HELE hEle, BOOL bActivate); //激活窗格
XC_API BOOL WINAPI XPane_IsActivate(HELE hEle); //判断窗格是否激活,当窗格在框架内有效

XC_API void WINAPI XPane_SetCaptionHeight(HELE hEle, int height);//设置标题栏高度
XC_API int  WINAPI XPane_GetCaptionHeight(HELE hEle);//获取标题栏高度

XC_API HELE WINAPI XPane_GetButtonClose(HELE hEle); //获取关闭按钮
XC_API HELE WINAPI XPane_GetButtonLock(HELE hEle); //获取锁定按钮
XC_API HELE WINAPI XPane_GetButtonMenu(HELE hEle); //获取菜单按钮


//启用或禁用窗格布局,禁用的窗格将被框架忽略,当框架调整时,不会对禁用的窗格调整
void Pane_EnableLayout(HELE hEle, BOOL bEnable);

//私有方法:
void Pane_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);
void Pane_AdjustLayout(HELE hEle);
void Pane_AdjustLayout2(HELE hEle);

layoutCell_* Pane_GetCell(HELE hEle);

void Pane_Lock_group(HELE hEle);
void Pane_Lock_pane(HELE hEle);
int  Pane_Lock_scale(layoutPane_ *pPane, layoutCell_ *pCell); //计算比例

BOOL Pane_CellInFrame(layoutCell_ *pFrameCell, layoutCell_ *pCell); //检查单元格是否在框架窗口内


//回调函数
BOOL CALLBACK Pane_OnEleDraw(HELE hEle, HDRAW hDraw);
void CALLBACK Pane_OnEventDestroy(HELE hEle);
BOOL CALLBACK Pane_OnEventMenuSelect(HELE hEle, HELE hEventEle, int id);

BOOL CALLBACK Pane_OnEventShow(HELE hEle, HELE hEventEle, BOOL bShow); //元素显示或隐藏事件

BOOL CALLBACK Pane_EleLButtonDown(HELE hEle, UINT flags, POINT *pPt);//鼠标按下
BOOL CALLBACK Pane_EleLButtonUp(HELE hEle, UINT flags, POINT *pPt); //鼠标弹起
BOOL CALLBACK Pane_EleMouseMove(HELE hEle, UINT flags, POINT *pPt);//鼠标移动
BOOL CALLBACK Pane_EventMouseLeave(HELE hEle, HELE hEventEle);
BOOL CALLBACK Pane_OnSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK Pane_BtnClose_OnEleDraw(HELE hEle, HDRAW hDraw);//绘制关闭按钮
BOOL CALLBACK Pane_BtnLock_OnEleDraw(HELE hEle, HDRAW hDraw); //绘制自动隐藏按钮
BOOL CALLBACK Pane_BtnMenu_OnEleDraw(HELE hEle, HDRAW hDraw); //绘制菜单按钮

BOOL CALLBACK Pane_Btn_Close(HELE hEle, HELE hEventEle);    //关闭按钮
BOOL CALLBACK Pane_Btn_Lock(HELE hEle, HELE hEventEle);     //停靠按钮
BOOL CALLBACK Pane_Btn_Menu(HELE hEle, HELE hEventEle);     //菜单按钮



/////////////////////////////////////////////////////////////////
//窗格浮动窗口

struct floatWindow_
{
	window_ window; //继承
	//------------------------
	layoutCell_  *pCell;  //布局单元,第一个窗格为最顶层,整个窗口的客户区
	HWINDOW      hFrameWnd; //框架窗口句柄
	POINT        downPt; //鼠标按下位置

	BOOL        bLock;  //是否允许锁定到框架窗口中
};



//API:
XC_API void WINAPI XFloatWnd_EnableLock(HWINDOW hWindow, BOOL bEnable); //启用关闭锁定功能,当关闭锁定功能后,用户拖动浮动窗格不能锁定到框架窗口中


//私有方法:
HWINDOW FloatWnd_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HWINDOW hFrameWnd, layoutCell_ *pCell);

void FloatWnd_DragWindow(HWINDOW hWindow, POINT *pPt); //拖动窗口
BOOL FloatWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, wchar_t *pTitle, HWINDOW hFrameWnd, layoutCell_ *pCell, int exType);

void FloatWnd_ExitDragWindow(); //退出拖动窗口

//回调函数:
BOOL CALLBACK FloatWnd_OnWndDestroy(HWINDOW hWindow);
BOOL CALLBACK FloatWnd_OnWndSize(HWINDOW hWindow, UINT flags, SIZE *pSize);
BOOL CALLBACK FloatWnd_OnWndClose(HWINDOW hWindow);
BOOL CALLBACK FloatWnd_OnWndKillFocus(HWINDOW hWindow);

LRESULT CALLBACK FloatWnd_LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);


//浮动窗口,TabBar切换事件
BOOL CALLBACK FloatWnd_OnEventTabBarSelect(HELE hEle, HELE hEventEle, int index);
