/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct slider_
{
	ele_  ele; //继承
	//---------------------
	BOOL bHorizon; //TRUE:水平, FALSE:垂直

	HELE hButton;   //滑块
	BOOL   bDown;     //鼠标是否按下
	int    range;     //范围
	int    pos;       //当前位置
	double minPos;    //每个点大小

	int    btnWidth; //按钮宽度

	HIMAGE hImage_bk;  //背景图片
	HIMAGE hImage;     //当前进度图片
};

//API:
XC_API HELE WINAPI XSliderBar_Create(int x, int y, int cx, int cy, BOOL bHorizon, HXCGUI hParent = NULL);
XC_API void WINAPI XSliderBar_SetRange(HELE hEle, int range);  //设置滑动范围
XC_API void WINAPI XSliderBar_SetPos(HELE hEle, int pos);     //设置滑块位置
XC_API int  WINAPI XSliderBar_GetPos(HELE hEle);            //获取滑块位置
XC_API HELE WINAPI XSliderBar_GetButton(HELE hEle);        //获取滑块指针
XC_API int  WINAPI XSliderBar_GetButtonWidth(HELE hEle); //获取滑块宽度

XC_API void WINAPI XSliderBar_SetHorizon(HELE hEle, BOOL bHorizon);  //水平显示或垂直
XC_API void WINAPI XSliderBar_SetButtonWidth(HELE hEle, int width); //设置滑块宽度

//设置进度颜色1
//设置进度颜色2

//贴图:
XC_API void WINAPI XSliderBar_SetImage(HELE hEle, HIMAGE hImage); //背景
XC_API void WINAPI XSliderBar_SetImage2(HELE hEle, HIMAGE hImage); //显示当前进度图片


//私有方法:
void SliderBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void SliderBar_Adjust(HELE hEle);


//回调函数:
void CALLBACK SliderBar_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK SliderBar_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK SliderBar_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SliderBar_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SliderBar_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK SliderBar_OnEventMouseLeave(HELE hEle, HELE hEventEle);

BOOL CALLBACK SliderBar_OnDrawButton(HELE hEle, HDRAW hDraw);