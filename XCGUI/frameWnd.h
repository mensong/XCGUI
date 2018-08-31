/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//框架窗口
struct frameWnd_
{
	window_ window;
	//---------------------------------------
	layoutCell_  *pCell;  //布局单元,第一个窗格为最顶层,整个窗口的客户区

	HWINDOW hFloatWnd; //当前拖动的浮动窗口
	HELE    hPaneActivate;     //当前激活的窗格

	//停靠提示
	HWINDOW hDockPane;     //停靠提示 十字
	HWINDOW hDockLeft;     //停靠提示 窗口边框 left
	HWINDOW hDockTop;      //停靠提示 窗口边框 top
	HWINDOW hDockRight;    //停靠提示 窗口边框 right
	HWINDOW hDockBottom;   //停靠提示 窗口边框 bottom

	HWINDOW hDockPreview;  //停靠预览
	align_type_  dockAlign; //预览窗口方向 left,top,right,bottom

	//窗口内
	layoutCell_  *pCell_stay;  //当前浮动窗口所在窗格
	int   dockType;    //停靠类型, 1组合,2合并,3边框

	//停靠码头
	HELE  hPierLeft;   //left
	HELE  hPierTop;    //top
	HELE  hPierRight;  //right
	HELE  hPierBottom; //bottom

	HELE hPaneExpand;//当前展开的窗格

	//组成员的拖动
	BOOL  bDown_TabBar; //按在TabBar按钮上
	POINT ptDown_TabBar;
};


/// @defgroup frameWindow  框架窗口
/// @ingroup groupWindows
/// 框架窗口接口列表


//窗口API:
XC_API HWINDOW WINAPI XFrameWnd_CreateWindow(int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent = NULL, int XCStyle = XC_SY_DEFAULT);

//增加窗格到框架窗口
XC_API BOOL WINAPI XFrameWnd_AddPane(HWINDOW hWindow, HELE hPaneDest, HELE hPaneNew, align_type_ align = align_any, int scale = 50);


XC_API HPANE_GROUP WINAPI XFrameWnd_MergePane(HWINDOW hWindow, HELE hPaneDest, HELE hPaneNew, int proportion = 50);
XC_API BOOL WINAPI XFrameWnd_MergePaneToGroup(HWINDOW hWindow, HPANE_GROUP hGroup, HELE hPaneNew, int proportion = 50); //窗格合并到组


XC_API void WINAPI XFrameWnd_AdjustLayout(HWINDOW hWindow, BOOL bFixedSize = FALSE);
XC_API void WINAPI XFrameWnd_GetLayoutAreaRect(HWINDOW hWindow, out_ RECT *pRect); //获取客户区布局区域坐标
XC_API HELE WINAPI XFrameWnd_GetActivatePane(HWINDOW hWindow);//获取框架窗口内激活的窗格,不包含浮动窗格

BOOL FrameWnd_RemoveCell(HWINDOW hWindow, layoutCell_ *pCell); //移除单元格,只是从布局管理中移除
BOOL FrameWnd_RemoveCell_Pane(HWINDOW hWindow, layoutCell_ *pCell);
BOOL FrameWnd_RemoveCell_Group(HWINDOW hWindow, layoutCell_ *pCell);
BOOL FrameWnd_RemoveCell_GroupMenber(HWINDOW hWindow, layoutCell_ *pCell);

void FrameWnd_DragPane(HWINDOW hWindow, layoutCell_ *pCell, POINT *pPtDown); //拖动窗格
void FrameWnd_DragGroup(HWINDOW hWindow, layoutCell_ *pCell, POINT *pPtDown); //拖动窗格组
void FrameWnd_FloatPane(HWINDOW hWindow, layoutCell_ *pCell); //浮动窗格
void FrameWnd_FloatGroup(HWINDOW hWindow, layoutCell_ *pGroupCell); //浮动窗格组


//私有方法:
BOOL FrameWnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle, int exType);

//组合
BOOL FrameWnd_AddT(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align = align_any, int scale = 50);
BOOL FrameWnd_Add_Pane(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);
BOOL FrameWnd_Add_GroupToPane(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);
BOOL FrameWnd_Add_PaneToGroup(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);

//合并
BOOL FrameWnd_Add_MergeT(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align = align_any, int scale = 50);
HPANE_GROUP FrameWnd_Add_Merge_Pane2(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);
BOOL FrameWnd_Add_Merge_Group2(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);
BOOL FrameWnd_Add_Merge_PaneToGroup(HWINDOW hWindow, layoutCell_ *pCellGroup, layoutCell_ *pCellPane/*,align_type_ align,int scale*/);
BOOL FrameWnd_Add_Merge_GroupToPane(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);

BOOL FrameWnd_AddPaneGroup(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale);


void FrameWnd_AddPier(HWINDOW hWindow, layoutCell_ *pCell); //窗格添加到码头
void FrameWnd_AddPierGroup(HWINDOW hWindow, layoutCell_ *pGroupCell); //窗格组添加到码头
void FrameWnd_RemovePier(HWINDOW hWindow, HELE hPane); //从码头移除窗格
void FrameWnd_RemovePierGroup(HWINDOW hWindow, HELE hPane); //从码头移除窗格组

BOOL FrameWnd_PierShrink(HWINDOW hWindow);  //收缩展开的窗格

//创建停靠提示及停靠位置预览窗口,临时窗口
void FrameWnd_CreateTempWindow(HWINDOW hWindow);


//回调函数:
BOOL CALLBACK FrameWnd_OnSize(HWINDOW hWindow, UINT type, SIZE *pSize);  //ON SIZE 窗口大小改变

BOOL CALLBACK FrameWnd_OnWndDestroy(HWINDOW hWindow);
void FrameWnd_DestroyCell(layoutCell_ *pCell);
BOOL CALLBACK FrameWnd_OnLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);

//TabBar事件,拖动子单元格
BOOL CALLBACK FrameWnd_TabBar_Btn_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK FrameWnd_TabBar_Btn_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK FrameWnd_TabBar_Btn_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK FrameWnd_TabBar_Btn_OnEventMouseLeave(HELE hEle, HELE hEventEle);

BOOL FrameWnd_PierPopupPane(HWINDOW hWindow, HELE hPane); //弹出窗格,当在码头上时

//浮动窗口移动
void FrameWnd_OnFloatWnd_Move(HWINDOW hWindow, POINT *pPt); //根据鼠标位置,判断浮动窗口在哪个布局格上
BOOL FrameWnd_OnFloatWnd_Move2(HWINDOW hWindow, layoutCell_ *pCell, POINT *pPt, POINT *pPtWindow); //遍历单元格

//鼠标在框架窗口内
void FrameWnd_OnFloatWnd_Move_inFrame(HWINDOW hWindow, POINT *pPt);
BOOL FrameWnd_OnFloatWnd_CheckInDockPrompt(HWINDOW hWindow, POINT *pPt); //检查是否在停靠提示上
BOOL FrameWnd_OnFloatWnd_CeckInDockPrompt_border(HWINDOW hWindow, POINT *pPt); //判断是否在框架窗口边框停靠提示上
void FrameWnd_OnFloatWnd_Exit(HWINDOW hWindow);

//浮动窗口鼠标左键弹起,pPt屏幕坐标
//处理鼠标移动浮动窗口
void FrameWnd_OnFloatWnd_LButtonUp(HWINDOW hWindow);
void FrameWnd_OnFloatWnd_AddPane(HWINDOW hWindow, layoutCell_ *pCellNew);
void FrameWnd_OnFloatWnd_AddGroup(HWINDOW hWindow, layoutCell_ *pCellNew);

//绘制窗格停靠提示,十字,窗格内部停靠
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockPane(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockLeft(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockTop(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockRight(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockBottom(HWINDOW hWindow, HDRAW hDraw);

