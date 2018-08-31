/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//图标元素
struct picture_
{
	ele_ ele; //继承
	//---------------------
	HIMAGE hImage_bk; //图片
};


//API:
XC_API HELE WINAPI XPic_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);

//贴图
XC_API void WINAPI XPic_SetImage(HELE hEle, HIMAGE hImage);  //设置图片


//私有方法:
void Pic_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);


//回调函数:
BOOL CALLBACK Pic_OnDraw(HELE hEle, HDRAW hDraw);
void CALLBACK Pic_OnDestroy(HELE hEle);  //销毁