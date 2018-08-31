/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0

BOOL CALLBACK MyEventComboBoxPopupList(HELE hEle,HELE hEventEle,HWINDOW hWindow,HELE hListBox)  //XE_COMBOBOX_POPUP_LIST
{
	XTRACE("pop 弹出 \n");
	return TRUE;
}

BOOL CALLBACK MyEventComboBoxCloseList(HELE hEle,HELE hEventEle) //XE_COMBOBOX_EXIT_LIST
{
	XTRACE("pop 关闭 \n");
	return TRUE;
}

HELE hEdit;
BOOL CALLBACK OnEventComboBoxSelecting(HELE hEle,HELE hEventEle,int index,BOOL *pBOOL)
{
	XTRACE("选择项正在改变...\n");
//	*pBOOL=TRUE;
	return TRUE;
}

BOOL CALLBACK MyEventComboBoxSelect(HELE hEle,HELE hEventEle,int id) //下拉组合框选择事件
{
	if(id>-1)
	{
		wchar_t buf[100]={0};
		wchar_t *pText=XComboBox_GetItemText(hEle,id);
		wsprintf(buf,L"选择项:\n%s",pText);
		XEdit_SetText(hEdit,buf);
		XEle_RedrawEle(hEdit);
		XTRACEW(L"选择项:%s \n",pText);
	}
	return TRUE;
}


//组合框
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建下拉组合框元素
	HELE hComboBox=XComboBox_Create(10,120,100,20,hWindow);
	XComboBox_EnableEdit(hComboBox,FALSE); //禁止编辑内容
	XComboBox_SetListHeight(hComboBox,100); //设置下拉列表高度
	XComboBox_AddString(hComboBox,L"1111");
	XComboBox_AddString(hComboBox,L"2222");
	XComboBox_AddString(hComboBox,L"3333");
	XComboBox_AddString(hComboBox,L"4444");
	XComboBox_AddString(hComboBox,L"5555");
	XComboBox_AddString(hComboBox,L"666");
	XComboBox_AddString(hComboBox,L"7777");
	XComboBox_AddString(hComboBox,L"8888");
	XComboBox_SetText(hComboBox,0); //设置当前选择项

	//创建编辑框来显示追踪事件
	hEdit=XEdit_Create(120,10,100,50,hWindow);
	XEdit_EnableMultiLine(hEdit,TRUE);
	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_SELECT,MyEventComboBoxSelect);
	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_SELECT_ING,OnEventComboBoxSelecting);

	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_POPUP_LIST,MyEventComboBoxPopupList);
	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_EXIT_LIST,MyEventComboBoxCloseList);
	
	XEle_SetBkColor(XSView_GetView(hEdit),RGB(255,0,0));
	//XSView_SetImage(hComboBox,L"image/123.jpg");
//XComboBox_SetBtnImageStay(hComboBox,L"image/btn_stay.bmp");

	XComboBox_PopupDropDownList(hComboBox);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//组合框
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

//	HELE hEdit=XEdit_Create(10,10,200,200,hWindow);
//	XEdit_SetTextSpacingLeft(hEdit,10);


	//创建下拉组合框元素
	HELE hComboBox=XComboBox_Create(10,10,100,20,hWindow);
//	XComboBox_EnableEdit(hComboBox,FALSE); //禁止编辑内容
	XComboBox_SetListHeight(hComboBox,100); //设置下拉列表高度
	XComboBox_AddString(hComboBox,L"1111");
	XComboBox_AddString(hComboBox,L"2222");
	XComboBox_AddString(hComboBox,L"3333");
	XComboBox_AddString(hComboBox,L"4444");
	XComboBox_AddString(hComboBox,L"5555");
	XComboBox_AddString(hComboBox,L"666");
	XComboBox_AddString(hComboBox,L"7777");
	XComboBox_AddString(hComboBox,L"8888");
	XComboBox_SetText(hComboBox,0); //设置当前选择项

	HELE hStatic=XStatic_Create(10,50,100,20,L"12345678901234567890",hWindow);
	XStatic_AdjustSize(hStatic);
	XEle_SetBkColor(hStatic,RGB(255,0,0));

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//下拉列表弹出事件
BOOL CALLBACK MyEventComboBoxPopupList(HELE hEle,HELE hEventEle,HWINDOW hWindow,HELE hListBox)
{
	XEle_SetBorderColor(hListBox,RGB(86,165,213)); //设置下拉列表边框颜色
	return TRUE;
}

//组合框贴图
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,150,L"炫彩界面库-窗口");

	//创建下拉组合框元素
	HELE hComboBox=XComboBox_Create(10,10,100,22,hWindow);
	XComboBox_EnableEdit(hComboBox,FALSE); //禁止编辑内容
	XComboBox_SetListHeight(hComboBox,100); //设置下拉列表高度
	XComboBox_AddString(hComboBox,L"1111"); //增加项
	XComboBox_AddString(hComboBox,L"2222");
	XComboBox_AddString(hComboBox,L"3333");
	XComboBox_AddString(hComboBox,L"4444");
	XComboBox_AddString(hComboBox,L"5555");
	XComboBox_AddString(hComboBox,L"666");
	XComboBox_AddString(hComboBox,L"7777");
	XComboBox_AddString(hComboBox,L"8888");
	XComboBox_SetSelectItem(hComboBox,0); //设置当前选择项

	XEle_EnableBorder(hComboBox,FALSE); //不绘制边框
	//设置贴图
	XComboBox_SetImageLeave(hComboBox,XImage_LoadFile(L"image//combo_leave.png"));
	XComboBox_SetImageStay(hComboBox,XImage_LoadFile(L"image//combo_stay.png"));
	XComboBox_SetImageDown(hComboBox,XImage_LoadFile(L"image//combo_down.png"));
//	XSView_EnableImageStretch(hComboBox,TRUE);

	//编辑框贴图
	HELE hEdit=XEdit_Create(150,10,100,22,hWindow);
	XEle_EnableBorder(hEdit,FALSE); //不绘制边框
	XEdit_SetImageLeave(hEdit,XImage_LoadFile(L"image//edit_leave.jpg"));
	XEdit_SetImageStay(hEdit,XImage_LoadFile(L"image//edit_stay.jpg"));

	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_POPUP_LIST,MyEventComboBoxPopupList); //注册事件

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
#endif