/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once



struct  toolBarBtn_
{
	button_  button;
	//--------------------------
	//int      style;       //样式

	//小图片:
//	HIMAGE   hImage_small;        //图标
//	HIMAGE   hImage_small_disable; //禁用状态图标
};

//如果按钮设置有背景图片,那么要绘制背景图片

//工具条按钮
XC_API HELE WINAPI XToolBarBtn_Create(int cx, int cy, wchar_t *pTitle);
XC_API void WINAPI XToolBarBtn_Adjust(HELE hEle);  //调整到合适大小, 在添加到工具条上之后才可调用,因为需要知道工具条大小后才能做调整


//私有方法
void  ToolBarBtn_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);


//回调函数:
BOOL CALLBACK ToolBarBtn_OnDraw(HELE hEle, HDRAW hDraw);
void CALLBACK ToolBarBtn_OnEventDestroy(HELE hEle);


//////////////////////////////////////////////////////////////////////////////////

#define  TOOLBAR_BUTTONS_WIDTH   40 //滚动按钮区域宽度
#define  TOOLBAR_BUTTONS_HEIGHT  20 //滚动按钮区域高度

struct toolBar_
{
	ele_  ele; //继承
	//--------------------
	HARRAY  hArrayEle;  //元素列表

	int    indent;      //当前缩进深度  向左缩进 +1, 向右-1

	HELE  hLeftButton;  //左按钮
	HELE  hRightButton; //右按钮
	BOOL  bAdjust;

	HIMAGE  hImage_bk;  //背景图片
};

//API:
XC_API HELE WINAPI XToolBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);

XC_API int WINAPI XToolBar_InsertEle(HELE hEle, HELE hNewEle, int index = -1); //添加元素到工具条, -1插入到末尾
XC_API int WINAPI XToolBar_InsertSeparator(HELE hEle, int index = -1); //添加分隔符, -1插入到末尾

XC_API HELE WINAPI XToolBar_GetHEle(HELE hEle, int index);  //获取工具条上元素句柄
XC_API HELE WINAPI XToolBar_GetButtonLeft(HELE hEle);   //获取工具条左滚动按钮Button
XC_API HELE WINAPI XToolBar_GetButtonRight(HELE hEle);  //获取工具条右滚动按钮Button

XC_API void WINAPI XToolBar_DeleteEle(HELE hEle, int index); //移除工具条上元素并销毁
XC_API void WINAPI XToolBar_Adjust(HELE hEle);          //调整布局


//贴图:
XC_API void WINAPI XToolBar_SetImage(HELE hEle, HIMAGE hImage);

//私有方法:
void ToolBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent); //初始化注册


//回调函数:
BOOL CALLBACK ToolBar_OnDraw(HELE hEle, HDRAW hDraw);
void CALLBACK ToolBar_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK ToolBar_OnEventBtnClickLeft(HELE hEle, HELE hEventEle);
BOOL CALLBACK ToolBar_OnEventBtnClickRight(HELE hEle, HELE hEventEle);
BOOL CALLBACK ToolBar_OnEventSize(HELE hEle, HELE hEventEle);

//工具条上按钮绘制
BOOL CALLBACK ToolBar_OnDrawScrollButtonLeft(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ToolBar_OnDrawScrollButtonRight(HELE hEle, HDRAW hDraw);

