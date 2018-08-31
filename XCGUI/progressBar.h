/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//进度条

struct progressBar_
{
	ele_  ele; //继承
	//---------------------
	BOOL bHorizon; //TRUE:水平, FALSE:垂直
	BOOL bPercent;//显示百分比

	int  range;   //范围
	int  curPos;  //当前进度点

	HIMAGE hImage_bk;  //背景图片
	HIMAGE hImage;     //当前进度图片
};


//API:
XC_API HELE WINAPI XProgBar_Create(int x, int y, int cx, int cy, BOOL bHorizon, HXCGUI hParent = NULL);
XC_API void WINAPI XProgBar_SetRange(HELE hEle, int range);  //设置范围
XC_API void WINAPI XProgBar_SetPos(HELE hEle, int pos);   //设置当前位置
XC_API int  WINAPI XProgBar_GetRange(HELE hEle);
XC_API int  WINAPI XProgBar_GetPos(HELE hEle);

XC_API void WINAPI XProgBar_SetHorizon(HELE hEle, BOOL bHorizon); //水平显示或垂直
XC_API void WINAPI XProgBar_EnablePercent(HELE hEle, BOOL bPercent); //显示百分比

//设置进度颜色

//贴图:
XC_API void WINAPI XProgBar_SetImage(HELE hEle, HIMAGE hImage); //背景
XC_API void WINAPI XProgBar_SetImage2(HELE hEle, HIMAGE hImage); //显示当前进度图片



//私有方法:
void ProgBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);

//回调函数:
BOOL CALLBACK ProgBar_OnDraw(HELE hEle, HDRAW hDraw);
void ProgBar_OnDrawHorizon(HELE hEle, HDRAW hDraw, RECT &rect);
void ProgBar_OnDrawVertical(HELE hEle, HDRAW hDraw, RECT &rect);
