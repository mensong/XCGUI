/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct propertyPage_item_
{
	HELE   hButton; //button_*
	HELE   hPage;

	int    width; //字符串显示宽度,像素
	int    widthUser;  //用户指定宽度,如果为0,不使用
};

struct propertyPage_
{
	ele_  ele; //继承
	//--------------------
	HARRAY hArrayList;  //标签列表 propertyPage_item_*
	BOOL   bAdjust;     //TRUE:需要调整
	BOOL   bScrollButton;//是否显示滚动按钮
	int    indent;      //当前缩进深度  向左缩进1个TAB +1, 向右-1
	int    height;      //标签高度
	int    widthBtn;    //滚动按钮区域宽度
	int    spacing;     //标签间距 0没有间距

	propertyPage_item_  *pSelectItem; //当前选择标签
	HELE  hBtnUp;    //上按钮
	HELE  hBtnDown;  //下按钮
};

//属性页元素

//API:
XC_API HELE WINAPI XPPage_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int WINAPI XPPage_AddLabel(HELE hEle, wchar_t *pName, HELE hPage = NULL); //添加一个标签
XC_API int WINAPI XPPage_InsertLabel(HELE hEle, int index, wchar_t *pName, HELE hPage = NULL);

XC_API void WINAPI XPPage_Adjust(HELE hEle);
XC_API BOOL WINAPI XPPage_SetBindEle(HELE hEle, int index, HELE hPage); //绑定视图元素到标签
XC_API void WINAPI XPPage_SetLabelHeight(HELE hEle, int height);  //设置标签高度
XC_API void WINAPI XPPage_SetLabelWidth(HELE hEle, int index, int width);   //设置标签宽度
XC_API void WINAPI XPPage_SetSelect(HELE hEle, int index, BOOL reDraw = TRUE);   //设置选择标签
XC_API void WINAPI XPPage_SetLabelText(HELE hEle, int index, wchar_t *pText);  //设置标签文本
XC_API void WINAPI XPPage_SetLabelSpacing(HELE hEle, int spacing);//设置标签间距, 0没有间距
XC_API void WINAPI XPPage_SetUp(HELE hEle);    //左滚动
XC_API void WINAPI XPPage_SetDown(HELE hEle);  //右滚动

XC_API int  WINAPI XPPage_GetSelect(HELE hEle);  //获取选择的标签
XC_API int  WINAPI XPPage_GetLabelHeight(HELE hEle);  //获取标签高度
XC_API int  WINAPI XPPage_GetLabelWidth(HELE hEle, int index);  //获取标签宽度
XC_API int  WINAPI XPPage_GetLabelCount(HELE hEle); //获取标签项数量

XC_API wchar_t * WINAPI XPPage_GetLabelText(HELE hEle, int index);  //获取文本
XC_API HELE WINAPI XPPage_GetLabel(HELE hEle, int index);//获取标签按钮Button
XC_API HELE WINAPI XPPage_GetLabelPage(HELE hEle, int index);//获取标签对应的页
XC_API int WINAPI XPPage_GetPageIndex(HELE hEle, HELE hPage); //检索绑定页对应标签索引
XC_API int WINAPI XPPage_GetLabelIndex(HELE hEle, HELE hLabel); //获取属性页标签按钮元素位置索引值
XC_API int WINAPI XPPage_GetLabelSpacing(HELE hEle);//获取标签间距, 0没有间距

XC_API void WINAPI XPPage_DeleteLabel(HELE hEle, int index, BOOL deletePage = FALSE);  //删除
XC_API void WINAPI XPPage_DeleteLabelAll(HELE hEle, BOOL deletePage = FALSE);  //删除所有TAB

XC_API void WINAPI XPPage_EnableScrollButton(HELE hEle, BOOL bEnable); //是否显示滚动按钮



//贴图:

//标签贴图,通过获取标签按钮操作
//标签图标

//私有方法:
void PPage_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
propertyPage_item_* PPage_AddLabel(HELE hEle, wchar_t *pName, HELE hPage);


//回调函数:
void CALLBACK PPage_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK PPage_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK PPage_OnEventSize(HELE hEle, HELE hEventEle);
//ONSIZE

BOOL CALLBACK PPage_OnDraw_Up(HELE hEle, HDRAW hDraw);   //绘制上按钮
BOOL CALLBACK PPage_OnDraw_Down(HELE hEle, HDRAW hDraw); //绘制下按钮
BOOL CALLBACK PPage_OnEventBtnClick_Up(HELE hEle, HELE hEventEle); //按钮事件
BOOL CALLBACK PPage_OnEventBtnClick_Down(HELE hEle, HELE hEventEle); //按钮事件

//绘制标签
BOOL CALLBACK PPage_OnEventBtnClick(HELE hEle, HELE hEventEle); //标签选择



///属性页标签按钮//////////////////////////////////////////////////////
HELE XPPageBtn_Create(int x, int y, int cx, int cy, wchar_t *pTitle = NULL, HXCGUI hParent = NULL);  //创建按钮
void PPageBtn_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);
BOOL CALLBACK PPageBtn_OnDrawLabel(HELE hEle, HDRAW hDraw);