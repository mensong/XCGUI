/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct tabBar_item_
{
	HELE   hButton; //button_*
	HELE   hPage;

	int    width; //字符串显示宽度,像素
};

//tab条元素
struct tabBar_
{
	ele_ ele; //基础
	//--------------------
	HARRAY hArrayList;  //标签列表 tabBar_item_*
	BOOL   bAdjust;     //TRUE:需要调整
	int    indent;      //当前缩进深度  向左缩进1个TAB +1, 向右-1
	int    height;      //标签高度
	int    widthBtn;    //滚动按钮区域宽度
	int    spacing;     //标签间距 0没有间距
	BOOL   bTile;       //平铺标签,每个标签显示相同大小

	tabBar_item_  *pSelectItem; //当前选择标签
	HELE  hBtnUp;    //上按钮
	HELE  hBtnDown;  //下按钮

	align_type_ align;  //样式,上下左右
};



//API:
XC_API HELE WINAPI XTabBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int WINAPI XTabBar_AddLabel(HELE hEle, wchar_t *pName, HELE hPage = NULL); //添加一个标签
XC_API int WINAPI XTabBar_InsertLabel(HELE hEle, int index, wchar_t *pName, HELE hPage = NULL);

XC_API void WINAPI XTabBar_DeleteLabel(HELE hEle, int index, BOOL deletePage = FALSE);  //删除
XC_API void WINAPI XTabBar_DeleteLabelAll(HELE hEle, BOOL deletePage = FALSE);  //删除所有TAB

XC_API HELE WINAPI XTabBar_GetLabel(HELE hEle, int index);//获取标签按钮Button
XC_API HELE WINAPI XTabBar_GetLabelPage(HELE hEle, int index); //获取标签对应的页
XC_API int  WINAPI XTabBar_GetPageIndex(HELE hEle, HELE hPage); //检索绑定页对应标签索引
XC_API int  WINAPI XTabBar_GetSelect(HELE hEle);  //获取选择的标签
XC_API int  WINAPI XTabBar_GetLabelSpacing(HELE hEle); //获取标签间距, 0没有间距
XC_API int  WINAPI XTabBar_GetLabelCount(HELE hEle); //获取标签项数量

XC_API void WINAPI XTabBar_SetLabelSpacing(HELE hEle, int spacing);//设置标签间距, 0没有间距
XC_API BOOL WINAPI XTabBar_SetBindEle(HELE hEle, int index, HELE hPage); //绑定视图元素到标签
XC_API void WINAPI XTabBar_SetSelect(HELE hEle, int index, BOOL reDraw = TRUE);   //设置选择标签
XC_API void WINAPI XTabBar_SetAlign(HELE hEle, align_type_ align);

XC_API void WINAPI XTabBar_SetUp(HELE hEle);    //左滚动
XC_API void WINAPI XTabBar_SetDown(HELE hEle);  //右滚动

XC_API void WINAPI XTabBar_EnableTile(HELE hEle, BOOL bTile);  //平铺标签,每个标签显示相同大小


//私有方法:
void TabBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void TabBar_Adjust(HELE hEle);
tabBar_item_* TabBar_AddLabel(HELE hEle, wchar_t *pName, HELE hPage);


//回调函数:
BOOL CALLBACK TabBar_OnDraw(HELE hEle, HDRAW hDraw);
void CALLBACK TabBar_OnDestroy(HELE hEle); //销毁
BOOL CALLBACK TabBar_OnEventSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK TabBar_OnDraw_Up(HELE hEle, HDRAW hDraw);   //绘制上按钮
BOOL CALLBACK TabBar_OnDraw_Down(HELE hEle, HDRAW hDraw); //绘制下按钮
BOOL CALLBACK TabBar_OnEventBtnClick_Up(HELE hEle, HELE hEventEle); //按钮事件
BOOL CALLBACK TabBar_OnEventBtnClick_Down(HELE hEle, HELE hEventEle); //按钮事件

BOOL CALLBACK TabBar_Btn_OnDrawLabel(HELE hEle, HDRAW hDraw);
BOOL TabBar_Btn_OnDrawLabel_Top(HELE hEle, HDRAW hDraw);
BOOL TabBar_Btn_OnDrawLabel_Bottom(HELE hEle, HDRAW hDraw);

BOOL CALLBACK TabBar_OnEventBtnClick(HELE hEle, HELE hEventEle); //标签选择
