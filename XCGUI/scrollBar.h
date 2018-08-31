/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//scrollBar

//假如是水平滚动条
struct scrollBar_
{
	ele_  ele; //继承
	//---------------
	BOOL  bHorizon;      //TRUE:水平滚动条, FALSE:垂直滚动条
	BOOL  bShowButton2;  //是否显示上下滚动按钮
	int   fixedSizeButton;    //滚动条是否指定大小,-1为默认长度

	RECT  rcUp;    //上按钮
	RECT  rcDown;  //下按钮
	RECT  rcBar;   //滑动按钮

	int   rcUpState;  //状态
	int   rcDownState;
	int   rcBarState;

	int   btnLength; //按钮长度,上滚动按钮和下滚动按钮
	int   barLength; //滑块长度,拖动滑块 -1为默认长度

	int   curPos;   //当前滚动点  比例点
	int   range;    //滚动范围    比例点 当范围是0是,注意浮动运算
	int   spacing;  //两个按钮间距-2 像素

	BOOL  bDownUp;   //鼠标按在上按钮
	BOOL  bDownDown; //鼠标按在下按钮
	BOOL  bDownBar;  //鼠标按在滑块上
	BOOL  bDownNull; //鼠标按在空白区
	int   downBarPos; //按在滚动条上坐标 像素

	int   MouseTop; //1:up, 2:down, 3:bar

//贴图:
	HIMAGE hImage_bk; //背景图片
//上按钮图片:
	HIMAGE  hImage_Leave_up;
	HIMAGE  hImage_stay_up;
	HIMAGE  hImage_down_up;
	//下按钮图片:
	HIMAGE  hImage_Leave_down;
	HIMAGE  hImage_stay_down;
	HIMAGE  hImage_down_down;
	//滑块:
	HIMAGE  hImage_Leave_slider;
	HIMAGE  hImage_stay_slider;
	HIMAGE  hImage_down_slider;
};

//API:
XC_API HELE WINAPI XSBar_Create(int x, int y, int cx, int cy, BOOL bHorizon, HXCGUI hParent = NULL);

XC_API BOOL WINAPI XSBar_ScrollUp(HELE hEle);       //向左滚动
XC_API BOOL WINAPI XSBar_ScrollDown(HELE hEle);     //向右滚动
XC_API BOOL WINAPI XSBar_ScrollTop(HELE hEle);      //滚动到顶部
XC_API BOOL WINAPI XSBar_ScrollBottom(HELE hEle);   //滚动到底部

XC_API BOOL WINAPI XSBar_ScrollPos(HELE hEle, int pos); //滚动到指定点

XC_API void WINAPI XSBar_SetScrollRange(HELE hEle, int range);
XC_API void WINAPI XSBar_SetSliderLength(HELE hEle, int length); //设置滑块长度
XC_API void WINAPI XSBar_SetHorizon(HELE hEle, BOOL bHorizon);  //水平显示或垂直

XC_API int WINAPI XSBar_GetScrollPos(HELE hEle); //获取当前滚动点
XC_API int WINAPI XSBar_GetButtonLength(HELE hEle); //按钮长度
XC_API int WINAPI XSBar_GetSliderLength(HELE hEle); //滑块长度
XC_API int WINAPI XSBar_GetScrollRange(HELE hEle);  //获取滚动范围

XC_API void WINAPI XSBar_EnableScrollButton2(HELE hEle, BOOL bEnable); //是否显示上下滚动按钮

XC_API void WINAPI XSBar_Adjust(HELE hEle);            //调整滚动条

//贴图:
XC_API void WINAPI XSBar_SetImage(HELE hEle, HIMAGE hImage);     //设置背景图片


//以下贴图自动拉伸
XC_API void WINAPI XSBar_SetImageLeaveUp(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageStayUp(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageDownUp(HELE hEle, HIMAGE hImage);

XC_API void WINAPI XSBar_SetImageLeaveDown(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageStayDown(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageDownDown(HELE hEle, HIMAGE hImage);

XC_API void WINAPI XSBar_SetImageLeaveSlider(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageStaySlider(HELE hEle, HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageDownSlider(HELE hEle, HIMAGE hImage);


//私有方法:
void SBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void Sbar_DrawButtonUp(HELE hEle, HDRAW hDraw);
void Sbar_DrawButtonDown(HELE hEle, HDRAW hDraw);
void Sbar_DrawButtonBar(HELE hEle, HDRAW hDraw);


//回调函数:
void CALLBACK SBar_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK SBar_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK SBar_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SBar_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SBar_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SBar_OnEventMouseLeave(HELE hEle, HELE hEventEle);
BOOL CALLBACK SBar_OnEventSize(HELE hEle, HELE hEventEle);

//定时器
extern scrollBar_  *g_pScrollBar;  //正在滚动的滚动条
VOID CALLBACK SBar_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

