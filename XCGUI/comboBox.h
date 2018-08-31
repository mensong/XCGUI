/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//组合框
struct comboBox_
{
	edit_  edit; //继承
	//-------------
	HWINDOW hPopupWnd; //弹出窗口指针
	HARRAY  hArrayStr;  //字符串列表 new wchar_t*
	HARRAY  hArrayData; //用户绑定数据
	BOOL    bEdit;      //可编辑内容
	int     heights;    //总高度
	int     height;     //项高
	int     curSel;     //当前选择项索引 ...

	DWORD   listEndTime; //下拉列表最后关闭时间

	//下拉按钮:
	struct
	{
		RECT rcButton;//下拉按钮
		int  state;   //状态
	}button_;

	//贴图
	HIMAGE hImage_stay; //鼠标停留
	HIMAGE hImage_down; //鼠标按下
};

//API:
XC_API HELE WINAPI XComboBox_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API BOOL WINAPI XComboBox_AddString(HELE hEle, wchar_t *pText, int data = 0);  //增加一个字符串到组合框

XC_API void WINAPI XComboBox_DeleteItem(HELE hEle, int index);//删除项
XC_API void WINAPI XComboBox_DeleteItemAll(HELE hEle);  //删除所有项
XC_API void WINAPI XComboBox_EnableEdit(HELE hEle, BOOL bEdit);  //启动编辑内容

XC_API void WINAPI XComboBox_SetSelectItem(HELE hEle, int index);  //设置选择项
XC_API void WINAPI XComboBox_SetText(HELE hEle, wchar_t *pText);     //设置编辑框内容
XC_API void WINAPI XComboBox_SetItemHeight(HELE hEle, int height); //设置下拉列表项高
XC_API void WINAPI XComboBox_SetListHeight(HELE hEle, int height);   //设置下拉列表高度
XC_API void WINAPI XComboBox_SetButtonWidth(HELE hEle, int width); //设置下拉按钮宽度
XC_API void WINAPI XComboBox_SetItemData(HELE hEle, int index, int data);

XC_API int  WINAPI XComboBox_GetButtonWidth(HELE hEle); //获取下拉按钮宽度
XC_API void WINAPI XComboBox_GetText(HELE hEle, wchar_t *pOut, int len);  //获取编辑框文本
XC_API int  WINAPI XComboBox_GetItemHeight(HELE hEle);  //获取项高
XC_API int  WINAPI XComboBox_GetListHeight(HELE hEle); //获取下拉列表高度
XC_API wchar_t* WINAPI XComboBox_GetItemText(HELE hEle, int index); //获取下拉列表文本
XC_API int  WINAPI XComboBox_GetSelectItem(HELE hEle);  //获取当前选择项索引
XC_API int WINAPI XComboBox_GetItemData(HELE hEle, int index);
XC_API int WINAPI XComboBox_GetItemCount(HELE hEle); //获取项数量

XC_API void WINAPI XComboBox_PopupDropDownList(HELE hEle); //弹出下拉列表

//贴图
XC_API void WINAPI XComboBox_SetImageLeave(HELE hEle, HIMAGE hImage = NULL); //鼠标离开
XC_API void WINAPI XComboBox_SetImageStay(HELE hEle, HIMAGE hImage = NULL); //鼠标停留
XC_API void WINAPI XComboBox_SetImageDown(HELE hEle, HIMAGE hImage = NULL); //鼠标按下

//私有方法:
void ComboBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void ComboBox_PopupDropDownList(HELE hEle); //弹出下拉列表
void ComboBox_DestroyPopupWnd(HELE hEle);  //销毁弹出窗口
void ComboBox_DrawBk(HELE hEle, HDRAW hDraw); //绘制背景
void ComboBox_Adjust(HELE hEle);

//回调函数:
void CALLBACK ComboBox_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK ComboBox_OnDraw(HELE hEle, HDRAW hDraw);

BOOL CALLBACK ComboBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnEventMouseLeave(HELE hEle, HELE hEventEle);
BOOL CALLBACK ComboBox_OnEventKillFocus(HELE hEle, HELE hEventEle);

BOOL CALLBACK ComboBox_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnEventSetFocus(HELE hEle, HELE hEventEle);
BOOL CALLBACK ComboBox_OnEventSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK ComboBox_OnEventMouseWheel(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt);

BOOL CALLBACK ComboBox_OnDrawButton(HELE hEle, HDRAW hDraw); //绘制下拉按钮

