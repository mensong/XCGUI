/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct listHeader_  //列表头
{
	RECT rect;
	HSTRING  hString;

	int minWidth;//限制最小宽度
	int width;

	int state;  //状态
	int imageId; //图片
};

struct listSubItem_ //子项
{
	HSTRING  hString; //文本
	RECT  rect;
	int   imageId;   //图标ID

	HARRAY hArrayBindEle; //绑定的元素 itemBindEle_*
};

struct listItem_  //项
{
	int state;   //状态
	int index;   //所处列表中的索引

	void*	userData;  //用户数据

	BOOL    bCheck;    //复选框是否选择
	RECT    rcCheck;   //复选框
	HARRAY  hArrayItem;  //子项
};

#define  XLIST_CHECK_SIZE   13 //复选框大小
#define  XLIST_ITEM_LEFT    3  //项左边间隔

struct list_
{
	scrollView_  scrollView; //继承
	//-------------
	//列表头*****************
	HARRAY        hArrayHeader;  //列表头 listHeader_*
	listHeader_   *pCurrHeader;  //当前鼠标所在列表头项
	BOOL          bAdjustHeader; //是否需要调整列表头,TRUE需要调整
	BOOL          bShowHeader;   //是否显示列表头
	int           headerHeight;  //列表头高度
	int           downIndex;     //鼠标按下, 所在列表头拖动分割线索引
	//int           minRange;      //列表头拖动最小范围
	BOOL          bGrid;         //绘制网格


	//列表视图*************
	HARRAY  hArrayItem;     //项列表 listItem_*
	HARRAY  hArrayCurrItem; //当前选择项列表 listItem_*
	listItem_  *pCurrItem;  //当前最近时间选择的项
	BOOL   bAdjustItem;   //是否需要调整列表项,TRUE调整
	int    spacingLeft;   //左间距
	int    spacingRight;  //右间距
	int    itemHeight;    //项高
	HXCGUI hImageList;    //图片列表

	//拖动选择---------
	BOOL   down;
	BOOL   bDrag;  //拖动矩形
	POINT  dragPt;
	POINT  dragEndPt;

	BOOL   bMultilineSelect;  //是否多行选择 Multi-line

	//复选框
	BOOL   bCheck;  //是否显示复选框

	//鼠标移动高亮显示
	BOOL  bLineHighlight; //是否启用高亮显示
	listItem_   *pItemMouseStay; //当前鼠标停留的项

//-----------------------------
	pFunList_DrawItem  pDrawItem; //用户自绘列表项
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info_Item;//消息事件回调函数信息指针
#endif
//----------------------------
	pFunListHeader_DrawItem pDrawItemHeader;//用户自绘列表头项
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info_ItemHeader;//消息事件回调函数信息指针
#endif
};

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
XC_API void WINAPI XList_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘列表项
XC_API void WINAPI XList_SetUserDrawItemHeaderEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘列表头项
#endif

//API:
XC_API HELE WINAPI XList_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int WINAPI XList_AddColumn(HELE hEle, int width, wchar_t *pText, int imageId = -1); //增加列
XC_API int WINAPI XList_AddItem(HELE hEle, wchar_t *pText, int imageId = -1);  //增加项
XC_API BOOL WINAPI XList_InsertColumn(HELE hEle, int index, int width, wchar_t *pText, int imageId = -1);  //插入列
XC_API BOOL WINAPI XList_InsertItem(HELE hEle, int index, wchar_t *pText, int imageId = -1);  //插入项
XC_API BOOL WINAPI XList_SetItemText(HELE hEle, int item, int subItem, wchar_t *pText, int imageId = -1); //设置子项
XC_API BOOL WINAPI XList_SetColumnWidth(HELE hEle, int index, int width);   //设置列宽
XC_API BOOL WINAPI XList_SetItemImage(HELE hEle, int item, int subItem, int imageId);   //设置子项图片
XC_API void WINAPI XList_SetImageList(HELE hEle, HXCGUI hImageList); //设置图片列表
XC_API void WINAPI XList_SetItemHeight(HELE hEle, int height);  //设置项高度
XC_API void WINAPI XList_SetHeaderHeight(HELE hEle, int height); //设置列表头高度
XC_API BOOL WINAPI XList_SetSelectItem(HELE hEle, int index);   //设置选择项
XC_API void WINAPI XList_SetSelectItemAll(HELE hEle);     //全选
XC_API void WINAPI XList_SetSpacingLeft(HELE hEle, int spacing);  //设置内容左间距
XC_API void WINAPI XList_SetSpacingRight(HELE hEle, int spacing); //设置内容右间距
XC_API void WINAPI XList_SetItemData(HELE hEle, int index, void* data);   //设置用户数据
XC_API BOOL WINAPI XList_SetItemBindEle(HELE hEle, int item, int subItem, itemBindEle_ *pInfo); //绑定元素
XC_API void WINAPI XList_SetColumnMinWidth(HELE hEle, int index, int minWidth); //设置列最小宽度

XC_API int WINAPI XList_GetHeaderHeight(HELE hEle);        //获取列表头高度
XC_API wchar_t* WINAPI XList_GetHeaderItemText(HELE hEle, int index);  //获取列表头项文本

XC_API int WINAPI XList_GetColumnWidth(HELE hEle, int index);     //获取列宽
XC_API int WINAPI XList_GetSpacingLeft(HELE hEle);  //获取内容左间距
XC_API int WINAPI XList_GetSpacingRight(HELE hEle); //获取内容右间距

XC_API HXCGUI WINAPI XList_GetImageList(HELE hEle);     //获取图片列表
XC_API wchar_t* WINAPI XList_GetItemText(HELE hEle, int index, int subItem); //获取项文本
XC_API int WINAPI XList_GetItemImage(HELE hEle, int item, int subItem); //获取子项图片
XC_API int WINAPI XList_GetItemHeight(HELE hEle);       //获取项高
XC_API void* WINAPI XList_GetItemData(HELE hEle, int index);   //设置用户数据
XC_API int WINAPI XList_GetSelectCount(HELE hEle);      //获取选择项数量
XC_API int WINAPI XList_GetSelectItem(HELE hEle);       //获取选择项
XC_API int WINAPI XList_GetSelectAllItem(HELE hEle, out_ int *pArray, int arrayLength);  //获取所有选择项
XC_API int WINAPI XList_GetItemCount(HELE hEle);        //获取项数量

XC_API BOOL WINAPI XList_GetHeaderItemRect(HELE hEle, int item, out_ RECT *pRect); //获取列表头项坐标
XC_API BOOL WINAPI XList_GetSubItemRect(HELE hEle, int item, int sub, out_ RECT *pRect);//获取子项坐标
XC_API BOOL WINAPI XList_GetItemCheckRect(HELE hEle, int item, out_ RECT *pRect); //获取复选按钮坐标
XC_API int  WINAPI XList_GetItemBindEleCount(HELE hEle, int item, int subItem);
XC_API BOOL WINAPI XList_GetItemBindEleInfo(HELE hEle, int item, int subItem, out_ itemBindEle_ *pInfo, int index);//获取绑定项信息

XC_API void WINAPI XList_CancelSelectAll(HELE hEle); //取消选择所有项
XC_API void WINAPI XList_CancelSelect(HELE hEle, int index); //取消选择指定项
XC_API BOOL WINAPI XList_DeleteItem(HELE hEle, int index);  //删除项
XC_API BOOL WINAPI XList_DeleteColumn(HELE hEle, int index);  //删除列
XC_API void WINAPI XList_DeleteAllItems(HELE hEle);  //删除所有项
XC_API void WINAPI XList_DeleteAllColumns(HELE hEle);   //删除所有列
XC_API void WINAPI XList_EnableGrid(HELE hEle, BOOL bGrid); //启用网格样式
XC_API int  WINAPI XList_HitTest(HELE hEle, POINT *pPt);  //测试鼠标点在哪个项上,-1没有在任何项上
XC_API BOOL WINAPI XList_HitTestEx(HELE hEle, POINT *pPt, out_ int *item, out_ int *sub); //测试鼠标点在哪个项上及子项,-1没有在任何项上
XC_API void WINAPI XList_ShowHeader(HELE hEle, BOOL bShow);//显示隐藏列表头

XC_API void WINAPI XList_SetUserDrawItem(HELE hEle, pFunList_DrawItem pFunDrawItem); //设置用户自绘列表项
XC_API void WINAPI XList_SetUserDrawItemHeader(HELE hEle, pFunListHeader_DrawItem pFunDrawItem); //设置用户自绘列表头项

XC_API void WINAPI XList_EnableCheckBox(HELE hEle, BOOL bEnable); //启用复选框
XC_API void WINAPI XList_EnableMultilineSelect(HELE hEle, BOOL bEnable);  //启用关闭多行选择 XEdit_EnableMultiLine
XC_API void WINAPI XLsit_EnableLineHighlight(HELE hEle, BOOL bEnable); //启用或关闭行高亮显示

XC_API BOOL WINAPI XList_IsItemCheck(HELE hEle, int index); //判断项的复选框是否勾选
XC_API void WINAPI XList_SetItemCheck(HELE hEle, int index, BOOL bCheck); //设置项的复选框

//鼠标移动高亮显示

//私有方法:
void List_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void List_AdjustHeader(HELE hEle);  //调整列表头
void List_AdjustItem(HELE hEle);
void List_AdjustDragHeader(HELE hEle, POINT &pt, int index);

void List_DrawItemHeader(HELE hEle, HDRAW hDraw); //绘制列表头
void List_DrawHeader_BG(HELE hEle, HDRAW hDraw, RECT *pRect);   //绘制列表头背景
void List_DrawHeader_Item(HELE hEle, HDRAW hDraw);  //绘制列表头项
void List_DrawHeader_Item_SYS(HELE hEle, HDRAW hDraw); //系统绘制列表项

void List_DrawList(HELE hEle, HDRAW hDraw);

void List_CancelSelectAll(HELE hEle); //取消选择所有项,不触发事件

BOOL List_MouseMoveHeader(HELE hEle, POINT *pPt);
BOOL List_LButtonDownHeader(HELE hEle, POINT *pPt);
BOOL List_LButtonUpHeader(HELE hEle, POINT *pPt);
BOOL List_MouseMoveDragHeaderEnd(HELE hEle);
void List_MouseLeaveHeader(HELE hEle);

BOOL List_MouseMove_View(HELE hEleView, POINT *pPt);
void List_LButtonDown(HELE hEle, POINT *pPt);

void List_MouseMoveDragBegin_View(HELE hEleView, POINT *pPt); //准备拖动选择
void List_MouseMoveDrag_View(HELE hEleView, POINT *pPt); //拖动选择
void List_MouseMoveDragUp(HELE hEle, int index1, int index2); //向上拖动
void List_MouseMoveDragDown(HELE hEle, int index1, int index2); //向下拖动

BOOL List_MouseMoveDragEnd_View(HELE hEleView); //鼠标拖动结束


//回调函数:
void CALLBACK List_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK List_OnEleDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK List_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK List_OnEventMouseLeave(HELE hEle, HELE hEventEle); //鼠标离开
BOOL CALLBACK List_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnEventKillCapture(HELE hEle, HELE hEventEle);


BOOL CALLBACK List_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnMouseMove_View(HELE hEleView, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnEventMouseLeave_View(HELE hEleView, HELE hEventEle); //鼠标离开
BOOL CALLBACK List_OnEventKillCapture_View(HELE hEleView, HELE hEventEle);  //失去鼠标捕获

extern HELE  g_hList;
VOID CALLBACK List_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


