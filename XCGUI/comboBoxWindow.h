/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


struct comboBoxWindow_
{
	window_ window; //继承
	//-------------------------------------
	HELE  hComboBox;

	HELE   hListBox; //列表框
};


//窗口API:
HWINDOW ComboBoxWnd_CreateWindow(int x, int y, int cx, int cy, HWND hWndParent, HELE hComboBox);


//私有方法:
BOOL ComboBoxWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, HWND hWndParent, int exType);

void ComboBoxWnd_SendEvent(comboBox_ *pComboBox, int index);

//回调函数:
BOOL CALLBACK ComboBoxWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK ComboBoxWnd_OnKillFocus(HWINDOW hWindow); //窗口失去焦点

BOOL CALLBACK ComboBoxWnd_OnEventListBoxSelect(HELE hEle, HELE hEventEle, int index);