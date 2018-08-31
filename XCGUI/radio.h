/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct radio_
{
	button_  button; //继承
	//-------------
	int   groupID;  //组ID
	BOOL  bButtonStyle;

	HELE  hBindEle;  //绑定页元素

	HIMAGE  hImage_leave_check;   //勾选 鼠标离开
	HIMAGE  hImage_stay_check;    //勾选 鼠标停留
	HIMAGE  hImage_down_check;    //勾选 鼠标按下
	HIMAGE  hImage_disable_check; //勾选 禁用
};

//API:
XC_API HELE WINAPI XRadio_Create(int x, int y, int cx, int cy, wchar_t *pTitle = NULL, HXCGUI hParent = NULL);  //创建按钮


//贴图:
XC_API void WINAPI XRadio_SetImageLeave_UnCheck(HELE hEle, HIMAGE hImage = NULL);  //鼠标离开时图片  未选择
XC_API void WINAPI XRadio_SetImageStay_UnCheck(HELE hEle, HIMAGE hImage = NULL);   //鼠标停留时图片  未选择
XC_API void WINAPI XRadio_SetImageDown_UnCheck(HELE hEle, HIMAGE hImage = NULL);   //鼠标按下时图片  未选择
XC_API void WINAPI XRadio_SetImageDisable_UnCheck(HELE hEle, HIMAGE hImage = NULL); //按钮禁用状态图片  未选择

XC_API void WINAPI XRadio_SetImageLeave_Check(HELE hEle, HIMAGE hImage = NULL);  //鼠标离开时图片  选择
XC_API void WINAPI XRadio_SetImageStay_Check(HELE hEle, HIMAGE hImage = NULL);   //鼠标停留时图片  选择
XC_API void WINAPI XRadio_SetImageDown_Check(HELE hEle, HIMAGE hImage = NULL);   //鼠标按下时图片  选择
XC_API void WINAPI XRadio_SetImageDisable_Check(HELE hEle, HIMAGE hImage = NULL); //按钮禁用状态图片  选择

XC_API void WINAPI XRadio_SetGroupID(HELE hEle, int groupID);  //设置组ID
XC_API int  WINAPI XRadio_GetGroupID(HELE hEle);  //获取组ID
XC_API void WINAPI XRadio_EnableButtonStyle(HELE hEle, BOOL bStyle); //启用按钮样式

XC_API void WINAPI XRadio_SetBindEle(HELE hEle, HELE bindEle);


//私有方法:
void Radio_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);
void Radio_DrawCheck(HELE hEle, HDRAW hDraw, RECT &rect); //绘制勾选状态
void Radio_DrawUnCheck(HELE hEle, HDRAW hDraw, RECT &rect); //绘制未勾选状态

void Radio_Draw_Check2(HDRAW hDraw, int x, int y, COLORREF color_dot, COLORREF color_border);
void Radio_Draw_UnCheck2(HDRAW hDraw, int x, int y, COLORREF color_dot1, COLORREF color_dot2, COLORREF color_border);


//回调函数
void CALLBACK Radio_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Radio_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Radio_OnEventBtnClick(HELE hEle, HELE hEventEle);
