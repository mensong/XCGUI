/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//布局单元格

enum cell_type_
{
	cell_type_left_right = 2,
	cell_type_top_bottom,
	cell_type_pane,
	cell_type_group,
};

#define PANE_DRAGBAR_WIDTH  6  //拖动条宽度
#define FRAME_PIER_WIDTH    25  //停靠码头宽度

struct layoutCell_ //布局单元格
{
	object_ object;
	//-----------------------------------
	align_type_  align; //单元格对齐方式
	cell_type_   type;  //单元格类型

	HELE	  hPane;        //单元格填充窗格,如果不是末端单元格,那么为空
	HELE	  hDragBar;     //单元格拖动条

	RECT	  rect;         //单元格坐标,窗口客户区坐标

//	int       minSize;      //窗格的最小宽度,限制窗格的拖动范围

	layoutCell_  *pParentCell; //父单元格
	layoutCell_  *pCell1;      //子单元格1
	layoutCell_  *pCell2;      //子单元格2
	int  scale;        //第一个单元格所占比例 0-100

	//分组,当为组时有效
	HARRAY   hArrayList; //组成员列表,layoutCell_*
	HELE     hTabBar;    //组TAB元素
};

layoutCell_* Cell_Create(HWINDOW hWindow, HELE hPane, align_type_ align);


//是否检查固定大小状态
void Cell_OnSize(layoutCell_ *pCell, HWINDOW hWindow, BOOL bFixedSize = FALSE); //调整坐标
void Cell_OnSize2(layoutCell_ *pCell, HWINDOW hWindow, BOOL bAdjust, BOOL bFixedSize = FALSE); //调整坐标

void Cell_OnSize_top_bottom(layoutCell_ *pCell, HWINDOW hWindow, BOOL bAdjust, BOOL bFixedSize);
BOOL Cell_OnSize_top_bottom_1(layoutCell_ *pCell, HWINDOW hWindow, BOOL bFixedSize);
int  Cell_OnSize_top_bottom_FixedSize(layoutCell_ *pCell);

void Cell_OnSize_left_right(layoutCell_ *pCell, HWINDOW hWindow, BOOL bAdjust, BOOL bFixedSize);
BOOL Cell_OnSize_left_right_1(layoutCell_ *pCell, HWINDOW hWindow, BOOL bFixedSize);
int  Cell_OnSize_left_right_FixedSize(layoutCell_ *pCell);

void Cell_OnSize_pane(layoutCell_ *pCell, HWINDOW hWindow, BOOL bAdjust);
void Cell_OnSize_group(layoutCell_ *pCell, HWINDOW hWindow, BOOL bAdjust);

BOOL Cell_IsChildInLayout(layoutCell_ *pCell); //检查子节点窗格是否在布局内

void Cell_OnSize_FloatWnd(layoutCell_ *pCell, HWINDOW hWindow); //浮动窗口调整
void Cell_OnSize_FloatWnd_Group(layoutCell_ *pCell);
void Cell_OnSize_FloatWnd_Pane(layoutCell_ *pCell);

void Cell_Destroy(layoutCell_ *pCell);



////////////////////////////////////////////////////////////////
//窗格拖动条

struct  layout_dragBar_
{
	ele_  ele; //继承
	//-------------------------------
	BOOL  bHorizontal; //水平TRUE ,垂直FALSE
	BOOL  bDown;
	layoutCell_  *pCell; //布局单元格
};


HELE DragBar_Create(int x, int y, int cx, int cy, BOOL bHorizontal, HWINDOW hWindow);

void DrawBar_SetCell(HELE hEle, layoutCell_ *pCell);


void DragBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, BOOL bHorizontal, HWINDOW hWindow);


//回调函数
BOOL CALLBACK DragBar_EleLButtonDown(HELE hEle, UINT flags, POINT *pPt);//鼠标按下
BOOL CALLBACK DragBar_EleLButtonUp(HELE hEle, UINT flags, POINT *pPt); //鼠标弹起
BOOL CALLBACK DragBar_EleMouseMove(HELE hEle, UINT flags, POINT *pPt);//鼠标移动