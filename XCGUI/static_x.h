/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct static_
{
	ele_  ele; //继承
	//--------------------
	HSTRING hString;
	int    textFlag; //文本对齐
};


//API:
XC_API HELE WINAPI XStatic_Create(int x, int y, int cx, int cy, wchar_t *pTitle = NULL, HXCGUI hParent = NULL);
XC_API void WINAPI XStatic_SetText(HELE hEle, wchar_t *pText);
XC_API wchar_t* WINAPI XStatic_GetText(HELE hEle);
XC_API void WINAPI XStatic_AdjustSize(HELE hEle);  //根据文本内容,调整元素大小


/// @brief 设置文本对齐.
/// @param hEle 元素句柄.
/// @param flag 标识,请参见MSDN  DrawText().
XC_API void WINAPI XStatic_SetTextAlign(HELE hEle, int flag); //设置文本对齐


//私有方法:
void Static_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);


//回调函数:
void CALLBACK Static_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Static_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Static_OnEventSetFocus(HELE hEle, HELE hEventEle); //获得焦点
BOOL CALLBACK Static_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点
