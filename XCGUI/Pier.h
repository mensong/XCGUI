#pragma once

//框架窗口停靠码头

struct pier_item_gtoup_;
struct pier_item_gtoup_child_
{
	layoutCell_ *pCell;
	HELE        hButton;
	pier_item_gtoup_ *Parent;
};

struct pier_item_gtoup_
{
	int  type;   //类型, 单一窗格1,窗格组2
	pier_item_gtoup_child_  Child; //如果是单一窗格有效

	HARRAY  hArrayList;     //窗格组成员 pier_item_gtoup_child_*
};

struct pier_
{
	ele_  ele; //继承
	//---------------------
	align_type_   align; //码头方向
	HARRAY        hArrayList; //成员类表 pier_item_gtoup_*

	HFONTX  hFontX;
};


HELE Pier_Create(align_type_ align, HWINDOW hWindow);
void Pier_AddCell(HELE hEle, layoutCell_ *pCell);  //增加窗格到码头
void Pier_AddCellGroup(HELE hEle, layoutCell_ *pGroupCell); //增加组到码头

void Pier_RemoveCell(HELE hEle, layoutCell_ *pCell); //移除窗格
void Pier_RemoveCellGroup(HELE hEle, layoutCell_ *pCell); //移除组

void Pier_SetCheck(HELE hEle, layoutCell_ *pCell);

//私有方法
void Pier_Init(pier_ *pPier, int eleType, HWINDOW hWindow);
void Pier_AdjustLayout(HELE hEle);
void Pier_AdjustLayout_Left(HELE hEle);
void Pier_AdjustLayout_Top(HELE hEle);
void Pier_AdjustLayout_Right(HELE hEle);
void Pier_AdjustLayout_Bottom(HELE hEle);

void CALLBACK Pier_OnEventDestroy(HELE hEle);
BOOL CALLBACK Pier_Btn_OnClick(HELE hEle, HELE hEventEle);


BOOL CALLBACK Pier_Btn_OnEleDraw(HELE hEle, HDRAW hDraw); //按钮自绘
