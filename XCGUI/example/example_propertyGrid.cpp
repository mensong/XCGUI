/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"



///////////////////////////////////////////
//测试属性网格////////////////////////////////
#if 0

//属性网格项选择改变事件
BOOL CALLBACK OnEventPGridSelChange(HELE hEle,HELE hEventEle,int prevID,int id)
{
	XTRACE("属性网格项选择改变=%d \n",id);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,260,260,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建属性网格元素
	HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
	//添加组
	int group1=XPGrid_AddGroup(hPGrid,L"一级 组1");
	//添加项
	int item1=XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	int item2=XPGrid_AddItem(hPGrid,L"二级 color",PGRID_CHOOSECOLOR,group1);

	int group2=XPGrid_AddGroup(hPGrid,L"一级 组2");
	//添加值为静态字符串类型项
	XPGrid_AddItemString(hPGrid,L"二级 字符串1",L"值",group2);
	XPGrid_AddItemString(hPGrid,L"二级 字符串2",L"值",group2);


	int id=XPGrid_AddItem(hPGrid,L"组合框",PGRID_COMBOBOX);//,group2);
	HELE hCom=XPGrid_GetItemHEle(hPGrid,id);

	XComboBox_AddString(hCom,L"FALSE");
	XComboBox_AddString(hCom,L"TRUE");

	PGrid_Adjust(hPGrid);

	XEle_RegisterEvent(hPGrid,XE_PGRID_SELCHANGE,OnEventPGridSelChange);

	XRunXCGUI();
	return 0;
}
#endif


//1608
#if 0

//属性网格 多个项
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"炫彩界面库-窗口");


	//创建属性网格元素
	HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
	//添加组
	int group1=XPGrid_AddGroup(hPGrid,L"一级 组1");
	//添加项
	int item1=XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	int item2=XPGrid_AddItem(hPGrid,L"二级 color",PGRID_CHOOSECOLOR,group1);

	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);

	int group2=XPGrid_AddGroup(hPGrid,L"一级 组2");
	//添加值为静态字符串类型项
	XPGrid_AddItemString(hPGrid,L"二级 字符串1",L"值",group2);
	XPGrid_AddItemString(hPGrid,L"二级 字符串2",L"值",group2);


	int id=XPGrid_AddItem(hPGrid,L"组合框",PGRID_COMBOBOX);//,group2);
	HELE hCom=XPGrid_GetItemHEle(hPGrid,id);

	XComboBox_AddString(hCom,L"FALSE");
	XComboBox_AddString(hCom,L"TRUE");

	PGrid_Adjust(hPGrid);

	Resource_Test();
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
#endif


#if 0
//属性网格项 值改变事件
BOOL CALLBACK EventPGridValueChange(HELE hEle,HELE hEventEle,int id)
{
	XTRACE("属性网格项值改变=%d \n",id);
	return TRUE;
}


//属性网格 多个项
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XWnd_SetBorderSize(hWindow,1,1,1,1);

//	HELE hEditFile=XEditFile_Create(10,10,100,20,hWindow);
//	XEditFile_SetDefaultFile(hEditFile,L"F:\\项目\\XCGUI(2012_03_31)(v1.4.2+)\\*");
//	XEditFile_SetRelativeDir(hEditFile,L"F:\\项目");
	//XComboBox_Create(10,10,100,20,hWindow);


	//创建属性网格元素
	HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
	//添加组
	int group1=XPGrid_AddGroup(hPGrid,L"一级 组1");
	//添加项
	int item1=XPGrid_AddItem(hPGrid,L"二级 editFile",PGRID_EDIT_FILE,group1);
	int item2=XPGrid_AddItem(hPGrid,L"二级 color",PGRID_CHOOSECOLOR,group1);

	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);

	int group2=XPGrid_AddGroup(hPGrid,L"一级 组2");
	//添加值为静态字符串类型项
	XPGrid_AddItemString(hPGrid,L"二级 字符串1",L"值",group2);
	XPGrid_AddItemString(hPGrid,L"二级 字符串2",L"值",group2);


	int id=XPGrid_AddItem(hPGrid,L"组合框",PGRID_COMBOBOX);//,group2);
	HELE hCom=XPGrid_GetItemHEle(hPGrid,id);

	XComboBox_AddString(hCom,L"FALSE");
	XComboBox_AddString(hCom,L"TRUE");

	PGrid_Adjust(hPGrid);
	XEle_RegisterEvent(hPGrid,XE_PGRID_VALUECHANGE,EventPGridValueChange);

	XRunXCGUI();
	return 0;
}
#endif


#if 0
//属性网格项 值改变事件
BOOL CALLBACK EventPGridValueChange(HELE hEle,HELE hEventEle,int id)
{
	XTRACE("属性网格项值改变=%d \n",id);
	return TRUE;
}

BOOL CALLBACK EventPGridValueChange2(HELE hEle,HELE hEventEle,int id)
{
	XTRACE("属性网格项值改变2=%d \n",id);
	return TRUE;
}

//多个属性网格
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,600,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	{
		//创建属性网格元素
		HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
		//添加组
		int group1=XPGrid_AddGroup(hPGrid,L"一级 组1");
		//添加项
		int item1=XPGrid_AddItem(hPGrid,L"二级 editFile",PGRID_EDIT_FILE,group1);
		int item2=XPGrid_AddItem(hPGrid,L"二级 color",PGRID_CHOOSECOLOR,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);

		XEle_RegisterEvent(hPGrid,XE_PGRID_VALUECHANGE,EventPGridValueChange);
	}
	/////////////////////////////////////////////////
	{
		//创建属性网格元素
		HELE hPGrid2=XPGrid_Create(220,10,200,200,hWindow);
		//添加组
		int group1=XPGrid_AddGroup(hPGrid2,L"一级 组1");
		//添加项
		XPGrid_AddItem(hPGrid2,L"二级 editFile",PGRID_EDIT_FILE,group1);
		XPGrid_AddItem(hPGrid2,L"二级 color",PGRID_CHOOSECOLOR,group1);
		XPGrid_AddItem(hPGrid2,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid2,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid2,L"二级 edit",PGRID_EDIT,group1);

		XEle_RegisterEvent(hPGrid2,XE_PGRID_VALUECHANGE,EventPGridValueChange2);
	}

	XRunXCGUI();
	return 0;
}
#endif


#if 0
HELE hPGrid=NULL;
BOOL CALLBACK OnBtnClick(HELE hEle,HELE hEventEle)
{
	XPGrid_DeleteAll(hPGrid);
	int group1=XPGrid_AddGroup(hPGrid,L"一级 组1");
	//添加项
	int item1=XPGrid_AddItem(hPGrid,L"二级 editFile",PGRID_EDIT_FILE,group1);
	int item2=XPGrid_AddItem(hPGrid,L"二级 color",PGRID_CHOOSECOLOR,group1);
	XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);

	XEle_RedrawEle(hPGrid);
	return TRUE;
}

//多个属性网格
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,600,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	{
		//创建属性网格元素
		hPGrid=XPGrid_Create(10,10,200,200,hWindow);
		//添加组
		int group1=XPGrid_AddGroup(hPGrid,L"一级 组1");
		//添加项
		int item1=XPGrid_AddItem(hPGrid,L"二级 editFile",PGRID_EDIT_FILE,group1);
		int item2=XPGrid_AddItem(hPGrid,L"二级 color",PGRID_CHOOSECOLOR,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"二级 edit",PGRID_EDIT,group1);
	}

	HELE hButton=XBtn_Create(220,10,60,20,L"button",hWindow);
	XEle_RegisterEvent(hButton,XE_BNCLICK,OnBtnClick);

	//XEle_EnableFocus(hPGrid,TRUE);
	/////////////////////////////////////////////////

	XRunXCGUI();
	return 0;
}
#endif