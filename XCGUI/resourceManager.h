/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//////////////////////////////////////////////////////////////
//新的资源管理器


//列表大小
//100    10
//500    50
//1000   100
//2000   200
//5000   500
//5000+  1000


//窗口列表窗口 -> 元素列表

struct resource_manager_window_
{
	HWINDOW   hWindow;

	resource_manager_window_  *pNext;
};

struct resource_manager_element_
{
	HELE  hEle;
	resource_manager_element_  *pNext;
};

struct resource_manager_element_header_
{
	resource_manager_element_  *pNode;
	int    count; //数量
};


//窗口资源数据
struct resource_manager_
{
	resource_manager_window_          *pWindowList;   //resources_manager_window_*
	resource_manager_element_header_  *pArrayEle; //resource_manager_element_header_ []

	int  countWindow;//窗口数量
	int  countEle;   //元素数量
	int  ArraySize;  //元素数组大小

	//其他资源,例如字符串,数组,图片
};


extern  resource_manager_   resource_manager;
void Resource_Init();
void Resource_AddWindow(HWINDOW hWindow);
BOOL Resource_RemoveWindow(HWINDOW hWindow);
int  Resource_GetWindowCount();

BOOL Resource_IsHWINDOW(HWINDOW hWindow);
/////////////////////////////////////////
BOOL Resource_IsHELE(HELE hEle); //检查元素句柄是否有效

void Resource_AddEle(HELE hEle);
BOOL Resource_RemoveEle(HELE hEle);
void Resource_Release();
/////////////////////////////////////////
int  Resource_Hash(int data);  //哈希

void Resource_Allocate(); //检查内存空间大小是否合适
void Resource_Allocate_X(int ArraySizeNew);
void Resource_Allocate_Add(resource_manager_element_  *pNew);

void Resource_Test();
