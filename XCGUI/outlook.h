/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

struct outlook_Item_
{
	HELE  hButton; //按钮句柄
	HELE  hView;   //绑定的视图
};

struct outlook_
{
	ele_  ele;
	//--------------------------
	HARRAY  hArrayItem;    //outlook_Item_*
	int     index;         //当前显示的视图索引
	int     buttonHeight;  //视图展开按钮高度
	BOOL    bAdjust;

};

//API:
XC_API HELE WINAPI XOutlook_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);

XC_API void WINAPI XOutlook_AddView(HELE hEle, HELE hView, wchar_t *pTitle);

XC_API void WINAPI XOutlook_Adjust(HELE hEle);

XC_API void WINAPI XOutlook_Expand(HELE hEle, int index);  //展开指定项

XC_API int WINAPI XOutlook_GetExpand(HELE hEle); //获取当前展开的项索引


//私有方法:
void Outlook_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);

//回调函数
void CALLBACK Outlook_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Outlook_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Outlook_OnDrawButton(HELE hEle, HDRAW hDraw);

BOOL CALLBACK Outlook_OnEventBtnClick(HELE hEle, HELE hEventEle);
BOOL CALLBACK Outlook_OnEventSize(HELE hEle, HELE hEventEle);