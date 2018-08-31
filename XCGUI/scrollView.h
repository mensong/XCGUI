/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//scrollView

struct drawScrollView_
{
	pFunDrawScrollView  pFun;
#ifdef	XCGUI_PLUS          //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
	drawScrollView_ *pNext;
};


struct scrollView_
{
	ele_  ele; //继承
	//---------------
	HELE  hView;  //视图元素
	ele_  *pScrollBarH;  //水平滚动条
	ele_  *pScrollBarV;  //垂直滚动条
	int  left, top, right, bottom; //四条边间距
	SIZE  sizeTotal;  //视图总大小
	SIZE  sizeView;   //视口大小
	SIZE  sizeLine;   //行大小

	BOOL  bHScroll;  //显示水平滚动条
	BOOL  bVScroll;  //显示垂直滚动条

	int   barWidth;  //滚动条宽度或高度

	int hPos;   //水平滚动点
	int vPos;   //垂直滚动点

	HIMAGE   hImage_bk;//背景图片

	//------------------------------------------------------------
	drawScrollView_  *pDrawScrollViewList; //绘制滚动视图函数
};

#ifdef	XCGUI_PLUS          //C++类支持,对类成员函数注册的支持
XC_API void WINAPI XSView_SetDrawScrollViewEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
#endif

//API:
XC_API HELE WINAPI XSView_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XSView_SetDrawScrollView(HELE hEle, pFunDrawScrollView pFun);

XC_API HELE WINAPI XSView_GetView(HELE hEle); //获取视元素
XC_API BOOL WINAPI XSView_AddEle(HELE hEle, HELE hNewEle); //添加元素到滚动视图

XC_API int WINAPI XSView_GetHViewPos(HELE hEle);   //获取视口原点X坐标
XC_API int WINAPI XSView_GetVViewPos(HELE hEle);   //获取视口原点Y坐标

XC_API int WINAPI XSView_GetSpacingLeft(HELE hEle);
XC_API int WINAPI XSView_GetSpacingTop(HELE hEle);
XC_API int WINAPI XSView_GetSpacingRight(HELE hEle);
XC_API int WINAPI XSView_GetSpacingBottom(HELE hEle);
XC_API int WINAPI XSView_GetScrollBarWidth(HELE hEle);  //获取滚动条宽度
XC_API int WINAPI XSView_GetViewWidth(HELE hEle);  //获取视口宽度(不含边框间隔及滚动条)
XC_API int WINAPI XSView_GetViewHeight(HELE hEle); //获取视口高度(不含边框间隔及滚动条)
XC_API int WINAPI XSView_GetHSizeTotalAccurate(HELE hEle); //获取内容总宽度,精确的(不含边框间隔及滚动条),当内容大小小于视口大小时,返回的是视口大小
XC_API int WINAPI XSView_GetVSizeTotalAccurate(HELE hEle); //获取内容总高度,精确的(不含边框间隔及滚动条),当内容大小小于视口大小时,返回的是视口大小
XC_API void WINAPI XSView_GetViewRect(HELE hEle, out_ RECT *pRect); //获取视口坐标(不含边框间隔),left为视口左间隔大小,top为视口上间隔大小,非(0,0).
XC_API void WINAPI XSView_GetSize(HELE hEle, SIZE *pSize);  //获取设置的内容大小

XC_API HELE WINAPI XSView_GetHScrollBar(HELE hEle); //获取水平滚动条
XC_API HELE WINAPI XSView_GetVScrollBar(HELE hEle); //获取垂直滚动条

XC_API void WINAPI XSView_SetSize(HELE hEle, int cx, int cy); //设置视图内容总大小(不包含边框间隔)
XC_API void WINAPI XSView_SetSpacing(HELE hEle, int left, int top, int right, int bottom);
XC_API void WINAPI XSView_SetScrollSize(HELE hEle, int line, int column);  //设置滚动行和列大小

//贴图
XC_API void WINAPI XSView_SetImage(HELE hEle, HIMAGE hImage);//设置贴图


XC_API void WINAPI XSView_EnableHScroll(HELE hEle, BOOL bEnable); //启用水平滚动条
XC_API void WINAPI XSView_EnableVScroll(HELE hEle, BOOL bEnable); //启用垂直滚动条
XC_API BOOL WINAPI XSView_IsHScrollBarVisible(HELE hEle); //水平滚动条当前是否可见
XC_API BOOL WINAPI XSView_IsVScrollBarVisible(HELE hEle); //垂直滚动条当前是否可见

XC_API void WINAPI XSView_Adjust(HELE hEle);

//滚动视图
XC_API BOOL WINAPI XSView_ScrollHPos(HELE hEle, int pos); //滚动到指定点
XC_API BOOL WINAPI XSView_ScrollVPos(HELE hEle, int pos); //滚动到指定点

//滚动到指定坐标
XC_API BOOL WINAPI XSView_ScrollHPosX(HELE hEle, int posX); //滚动到指定坐标
XC_API BOOL WINAPI XSView_ScrollVPosY(HELE hEle, int posY); //滚动到指定坐标

XC_API BOOL WINAPI XSView_ScrollLeftLine(HELE hEle);    //向左滚动
XC_API BOOL WINAPI XSView_ScrollRightLine(HELE hEle);   //向右滚动
XC_API BOOL WINAPI XSView_ScrollTopLine(HELE hEle);     //向上滚动
XC_API BOOL WINAPI XSView_ScrollDownLine(HELE hEle);    //向下滚动

XC_API BOOL WINAPI XSView_ScrollLeft(HELE hEle);    //水平滚动到左侧
XC_API BOOL WINAPI XSView_ScrollRight(HELE hEle);   //水平滚动到右侧
XC_API BOOL WINAPI XSView_ScrollTop(HELE hEle);     //滚动到顶部
XC_API BOOL WINAPI XSView_ScrollBottom(HELE hEle);  //滚动到底部


//私有方法:
void SView_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);

//回调函数:
void CALLBACK SView_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK SView_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK SView_OnEventHScroll(HELE hEle, HELE hEventEle, int pos);
BOOL CALLBACK SView_OnEventVScroll(HELE hEle, HELE hEventEle, int pos);
BOOL CALLBACK SView_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SView_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SView_OnEventMouseWheel(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt); //滚轮事件
BOOL CALLBACK SView_OnEventSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK SView_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt);