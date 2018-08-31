/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//属性项节点数据 , 一级节点或二级节点
struct PGridItem_
{
	int     id;       //项ID
	wchar_t *pName;   //名称,需要释放 malloc
	wchar_t *pValue;  //值,需要释放,当类型为PGRID_STRING时使用 malloc
	HELE    hEle;     //值对应元素句柄
	int     type;     //类型 ,字符串类型,元素类型,如果是元素类型
	int     posy;     //Y坐标


	PGridItem_ *pNext; //如果是二级节点使用
};


//属性组项节点数据 , 一级节点
struct  PGridGroup_
{
	int      id;      //项ID
	wchar_t  *pName;  //组名,需要释放
	BOOL     bExpand; //展开收缩
	int      posy;    //Y坐标

	PGridItem_  *pItemList; //二级项节点列表
	PGridItem_  *pItemLast; //指向pIten末尾节点
};


//项节点, 一级节点
struct PGridNode_
{
	int   type;    //项的类型, 1组 ,2项
	void  *pItem;  //项数据指针 PGridGroup_* 或 PGridItem_*
	PGridNode_ *pNext;
};


//在一级节点有组和项,在二级节点只允许有项,最大二级节点;


//属性网格
struct propertyGrid_
{
	scrollView_ scrollView; //继承
	//------------------------
	PGridNode_  *pItemList;	//项列表
	PGridNode_  *pItemLast; //指向1级末尾节点

	int   itemHeight;     //项高
	int   spacePoint;     //中间分隔点
	int   indent;         //缩进
	int   indentBtn;      //展开按钮缩进值
	int   bottom;         //最低部项位置
	int   uid;            //递增ID,  标示符从1开始,因为0代表一级跟节点
	int   selId;          //当前选择项id, -1没有选择项
	BOOL  bAdjust;        //调整布局

	BOOL  bDown;      //鼠标按下
	wchar_t *pTemp;   //临时缓存数据,对比值是否修改 malloc
};


//API:
XC_API HELE WINAPI XPGrid_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);


//  功能     :  添加分组
//  pName    :  组名称
//  bExpand  :  是否展开
XC_API int WINAPI XPGrid_AddGroup(HELE hEle, wchar_t *pName, BOOL bExpand = TRUE); //添加分组


//  功能   :  添加项到指定的分组
//  pName  :  项名称
//  type   :  类型
//  group  :  所属分组的ID,如果是-1,不属于任何组
//  return :  返回项的标示符
XC_API int WINAPI XPGrid_AddItem(HELE hEle, wchar_t *pName, int type, int groupID = -1); //添加项


//  功能    :  添加项到指定的分组,值为字符串
//  pName   :  项名称
//  pValue  :  项值
//  group   :  所属分组的ID,如果是-1,不属于任何组
//  return  :  返回项的标示符
XC_API int WINAPI XPGrid_AddItemString(HELE hEle, wchar_t *pName, wchar_t *pValue, int groupID = -1); //添加项


//  功能   :  获取指定项元素句柄,通过返回的句柄,修改值内容
//  id     :  项ID
XC_API HELE WINAPI XPGrid_GetItemHEle(HELE hEle, int itemID);


//  功能  :  设置字符串项内容,必须是PGRID_STRING,PGRID_EDIT,PGRID_COMBOBOX类型的项
//  id    :  项ID
XC_API BOOL WINAPI XPGrid_SetItemString(HELE hEle, int itemID, wchar_t *pText);

//  功能  :  设置字符串项内容,必须是PGRID_CHOOSECOLOR类型的项
//  id    :  项ID
XC_API BOOL WINAPI XPGrid_SetItemColor(HELE hEle, int itemID, COLORREF color);

//  功能  :  获取指定项的值
//  pOut  :  字符串缓冲区,存储返回的字符串
//  len   :  pOut可接收字符长度
XC_API void WINAPI XPGrid_GetItemValue(HELE hEle, int itemID, wchar_t *pOut, int len);


XC_API void WINAPI XPGrid_DeleteItem(HELE hEle, int itemID);   //删除项

XC_API void WINAPI XPGrid_DeleteGroup(HELE hEle, int groupID);  //删除组

XC_API void WINAPI XPGrid_DeleteAll(HELE hEle);  //删除所有

XC_API void WINAPI XPGrid_SetSpacePoint(HELE hEle, int point);//设置分隔线基于X坐标位置

XC_API int WINAPI XPGrid_GetSelectItem(HELE hEle); //获取当前选择项

XC_API void WINAPI XPGrid_Adjust(HELE hEle); //调整布局

//事件处理
//TODO: 项获得焦点失去焦点事件, 通过项的句柄,注册回调事件,检测值的修改

//私有方法:
void PGrid_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
int  PGrid_AddID(HELE hEle); //递增新ID
BOOL PGrid_AddIDTest(PGridNode_ *pNodeList, int id); //检查ID是否使用

void PGrid_Adjust(HELE hEle); //调整一级项
void PGrid_AdjustChildItem(HELE hEle, PGridGroup_ *pGroup, int &posy, int right, int posyPort); //调整二级项

void PGrid_DrawGroup(HELE hEle, PGridGroup_ *pGroup, int left, int right, HDRAW hDraw, HBRUSH hBrush); //绘制组
void PGrid_DrawItem(HELE hEle, PGridItem_ *pItem, int left, int right, HDRAW hDraw); //绘制项
void PGrid_HideEle(HELE hEle); //隐藏指定元素
void PGrid_ShowEle(HELE hEle, PGridItem_ *pItem);//显示指定项

//检查属性值改变
void PGrid_CheckValueChange(HELE hEle, PGridItem_ *pItem);

// 功能  : 获取指定组节点
PGridGroup_ *PGrid_GetGroup(HELE hEle, int groupID);

PGridItem_  *PGrid_GetItem(HELE hEle, int itemID);  //获取指定项节点

BOOL PGrid_LButtonDownItem(HELE hEle, PGridItem_ *pItem, POINT *pPt);

//回调函数:
BOOL CALLBACK PGrid_OnEleDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK PGrid_OnDrawScrollView(HELE hEle, HDRAW hDraw);


BOOL CALLBACK PGrid_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK PGrid_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK PGrid_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK PGrid_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点
BOOL CALLBACK PGrid_OnEventSize(HELE hEle, HELE hEventEle);

void CALLBACK PGrid_OnDestroy(HELE hEle);  //元素销毁 - 释放资源
