/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct groupBox_
{
	ele_ ele; //继承
	//--------------------
	HSTRING hString;
};


//API:
XC_API HELE WINAPI XGBox_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent = NULL); //创建
XC_API wchar_t* WINAPI XGBox_GetText(HELE hEle);
XC_API void WINAPI XGBox_SetText(HELE hEle, wchar_t *pText);

//私有方法:
void GBox_Init(HELE hEle, int x, int y, int cx, int cy, wchar_t *pTitle, int eleType, HXCGUI hParent); //初始化注册


//回调函数:
void CALLBACK GBox_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK GBox_OnDraw(HELE hEle, HDRAW hDraw);