/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//日历元素
#define MONTHCAL_WIDTH   192  //MonthCal_width  宽度
#define MONTHCAL_HEIGHT  136  //MonthCal_height 高度


struct monthCalBtn_
{
	RECT rect;  //坐标
	int  value; //值
	int  state; //状态
	int  flags; //0上月 1当月 2下月
};

struct monthCal_  //月历元素
{
	ele_  ele; //继承
	//---------------------------
	int   type; //当前操作类型 0:日期选择 1:月选择 2:年选择 3:十年间隔段选择
	BOOL  bAdjust; //调整
	monthCalBtn_  btn[42]; //选项

	HELE hBtnLeft;  //左按钮
	HELE hBtnRight; //右按钮
	int  left;      //左对齐间距
	int  top;       //上对齐间距
	COleDateTime  time;    //当前日期
	COleDateTime  timeOld; //保存先前时间,用来检查日期是否改变
	monthCalBtn_ *pSel;  //当前选择
};


//API:
XC_API HELE WINAPI XMonthCal_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XMonthCal_SetSpacingLeft(HELE hEle, int left); //左对齐间距
XC_API void WINAPI XMonthCal_SetSpacingTop(HELE hEle, int top); //上对齐间距
XC_API void WINAPI XMonthCal_SetDate(HELE hEle, int year, int month, int day);  //设置时间

XC_API int WINAPI XMonthCal_GetYear(HELE hEle);
XC_API int WINAPI XMonthCal_GetMonth(HELE hEle);
XC_API int WINAPI XMonthCal_GetDay(HELE hEle);

//私有方法:
void MonthCal_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);
void MonthCal_Adjust(HELE hEle);
void MonthCal_AdjustDayWeek(HELE hEle); //调整
void MonthCal_AdjustMonth(HELE hEle);
void MonthCal_AdjustYear(HELE hEle);
void MonthCal_AdjustYear10Year(HELE hEle);

void MonthCal_DrawDayWeek(HELE hEle, HDRAW hDraw); //绘制日期类型
void MonthCal_DrawMonth(HELE hEle, HDRAW hDraw);  //绘制月选择
void MonthCal_DrawYear(HELE hEle, HDRAW hDraw);   //绘制年选择
void MonthCal_Draw10Year(HELE hEle, HDRAW hDraw); //绘制10年间隔选择

void MonthCal_LButtonDownDayWeek(HELE hEle, POINT *pPt);
void MonthCal_LButtonDownMonth(HELE hEle, POINT *pPt);
void MonthCal_LButtonDownYear(HELE hEle, POINT *pPt);
void MonthCal_LButtonDown10Year(HELE hEle, POINT *pPt);

void MonthCal_Change(HELE hEle, BOOL bView1); //检查日期是否改变

//回调函数:
BOOL CALLBACK MonthCal_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK MonthCal_OnEleLButtonDown(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK MonthCal_OnEventBtnClickLeft(HELE hEle, HELE hEventEle); //左按钮
BOOL CALLBACK MonthCal_OnEventBtnClickRight(HELE hEle, HELE hEventEle);//右按钮


//////////////////////////////////

//DateTime
struct dateTime_  //日期元素
{
	ele_  ele; //继承
	//------------------------
	HELE  hButton;  //下拉按钮

	int   state; //状态
	COleDateTime  time; //时间
	int   year;  //年
	int   month;  //月
	int   day;   //日

	BOOL  bYear;  //年是否选择 TRUE选择
	BOOL  bMonth; //月是否选择
	BOOL  bDay;   //日是否选择

	RECT rcYear;  //年显示区域
	RECT rcMonth; //月显示区域
	RECT rcDay;   //日显示区域
	HWINDOW hPopupWnd; //弹出窗口

	//贴图:
	HIMAGE   hImage_bk;
	//	COLORREF borderColor; //边框颜色
};

//API:
XC_API HELE WINAPI XDateTime_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XDateTime_SetDate(HELE hEle, int year, int month, int day);  //设置时间
XC_API int WINAPI XDateTime_GetYear(HELE hEle);
XC_API int WINAPI XDateTime_GetMonth(HELE hEle);
XC_API int WINAPI XDateTime_GetDay(HELE hEle);
XC_API HELE WINAPI XDateTime_GetButton(HELE hEle);  //获取下拉按钮


//贴图:
XC_API void WINAPI XDateTime_SetImage(HELE hEle, HIMAGE hImage);


//私有方法:
void DateTime_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void DateTime_DestroyPopupWnd(HELE hEle, BOOL bSel);  //销毁弹出窗口,如果bSel是真,改变日期
void DateTime_Change(HELE hEle);//日期改变

//回调函数:
void CALLBACK DateTime_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK DateTime_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK DateTime_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK DateTime_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点
BOOL CALLBACK DateTime_OnEventChar(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DateTime_OnEventSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK DateTime_OnEventBtnClick(HELE hEle, HELE hEventEle);  //下拉按钮点击
BOOL CALLBACK DateTime_OnDrawButton(HELE hEle, HDRAW hDraw); //绘制下拉按钮