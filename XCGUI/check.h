/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

struct check_
{
	button_  button; //继承
	//---------------

	HIMAGE  hImage_leave_check;   //勾选 鼠标离开
	HIMAGE  hImage_stay_check;    //勾选 鼠标停留
	HIMAGE  hImage_down_check;    //勾选 鼠标按下
	HIMAGE  hImage_disable_check; //勾选 禁用
};

//API:

XC_API HELE WINAPI XCheck_Create(int x, int y, int cx, int cy, wchar_t *pTitle = NULL, HXCGUI hParent = NULL);

//贴图:
XC_API void WINAPI XCheck_SetImageLeave_UnCheck(HELE hEle, HIMAGE hImage);   //鼠标离开时图片  未选择
XC_API void WINAPI XCheck_SetImageStay_UnCheck(HELE hEle, HIMAGE hImage);    //鼠标停留时图片  未选择
XC_API void WINAPI XCheck_SetImageDown_UnCheck(HELE hEle, HIMAGE hImage);    //鼠标按下时图片  未选择
XC_API void WINAPI XCheck_SetImageDisable_UnCheck(HELE hEle, HIMAGE hImage); //按钮禁用状态图片  未选择

XC_API void WINAPI XCheck_SetImageLeave_Check(HELE hEle, HIMAGE hImage);   //鼠标离开时图片   选择
XC_API void WINAPI XCheck_SetImageStay_Check(HELE hEle, HIMAGE hImage);    //鼠标停留时图片   选择
XC_API void WINAPI XCheck_SetImageDown_Check(HELE hEle, HIMAGE hImage);    //鼠标按下时图片   选择
XC_API void WINAPI XCheck_SetImageDisable_Check(HELE hEle, HIMAGE hImage); //按钮禁用状态图片  选择


//私有方法:
void Check_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);
void Check_DrawCheck(HELE hEle, HDRAW hDraw, RECT &rect); //绘制勾选状态
void Check_DrawUnCheck(HELE hEle, HDRAW hDraw, RECT &rect); //绘制未勾选状态


//回调函数:
void CALLBACK Check_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Check_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Check_OnEventBtnClick(HELE hEle, HELE hEventEle);
