/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct listView_item_
{
	HSTRING hString; //字符串列表 wchar_t*
	int   imageID;   //字符串对应图标ID

	RECT  rcIcon; //图标坐标
	RECT  rcText; //文字坐标
	RECT  rect; //整个区域,包含边框
	RECT  rcIconDraw; //图标绘制坐标

	int   state;  //状态 选中 停留 离开
	int   groupIndex; //项所述组索引 -1没有组
	int   index;  //项在数组中位置索引

	//状态贴图
	HIMAGE hImage_stay;
	HIMAGE hImage_select;

	void* userData; //用户绑定数据
};

//组
struct listView_group_
{
	HARRAY hArrayList;   //listView_item_*

	HSTRING hString;
	RECT  rcText;
	RECT  rcButton;    //展开按钮 rcButton
	RECT  rect;    //组区域

	int   index;  //组在数组中位置索引

	BOOL  bExpand;    //是否展开
	void* userData;   //用户绑定数据
};

struct listView_
{
	scrollView_  scrollView; //继承
	//-------------

	HARRAY  hArrayList;      //未分组项 listView_item_*
	HARRAY  hArrayGroupList; //分组列表 listView_group_*

	HXCGUI  hImageList;      //图片列表

	//当前插入项位置
	int    insertGroup;
	int    insertItem;

	SIZE  iconSize;    //项图标区域大小
	int   left, top, right, bottom; //项边框间隔大小
	int   columnSpace; //项列间隔 X
	int   rowSpace;    //项行间隔 Y
	int   iconTextSpace; //图标与文本间隔
	int   leftAlign;  //视图左对齐
	int   topAlign;   //视图上对齐
	int   groupHeight; //组高度

	BOOL    bAdjust;
	BOOL    bExpandButton; //是否显示展开按钮 
	BOOL    bDragItem;     //拖动项
	HWINDOW hWndDrag;     //正在拖动项窗口


	//启用关闭多选选择
	BOOL   bMultiSelect;  //是否多项选择 Multi-Item
	HARRAY  hArrayCurrItem; //当前选择项列表 listView_item_* ,当单选时不使用
	listView_item_  *pCurrItem;  //当前最近时间选择的项

	listView_item_  *pCurrItemStay; //当前鼠标停留项

	//拖动选择---------
	BOOL   down;
	BOOL   bDrag;  //拖动矩形
	POINT  dragPt;
	POINT  dragEndPt;


	//----------------------
	pFunListView_DrawItem  pDrawItem; //用户自绘
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info;//消息事件回调函数信息指针
#endif

	//----------------------
	pFunListView_DrawGroup  pDrawGroup; //用户自绘
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info_group;//消息事件回调函数信息指针
#endif
};

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
XC_API void WINAPI XListView_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘项
XC_API void WINAPI XListView_SetUserDrawGroupEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘组
#endif

//API:
XC_API HELE WINAPI XListView_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XListView_AddItem(HELE hEle, wchar_t *pName, int imageID = -1, int groupIndex = -1); //增加项
XC_API int  WINAPI XListView_AddGroup(HELE hEle, wchar_t *pName, BOOL bExpand = TRUE); //增加组
XC_API int  WINAPI XListView_InsertItem(HELE hEle, int groupIndex, int itemIndex, wchar_t *pName, int imageID = -1);  //插入项
XC_API int  WINAPI XListView_InsertGroup(HELE hEle, int groupIndex, wchar_t *pName, BOOL bExpand = TRUE);  //插入组

XC_API void WINAPI XListView_SetImageList(HELE hEle, HXCGUI hImageList);
XC_API BOOL WINAPI XListView_SetItemData(HELE hEle, int groupIndex, int itemIndex, void* data); //设置项绑定数据
XC_API BOOL WINAPI XListView_SetGroupData(HELE hEle, int groupIndex, void* data); //设置组绑定数据
XC_API BOOL WINAPI XListView_SetSelectItem(HELE hEle, int goupIndex, int itemIndex, BOOL bSelect);//设置选择项

XC_API BOOL WINAPI XListView_SetItemText(HELE hEle, int groupIndex, int itemIndex, wchar_t *pText);//设置项文本
XC_API BOOL WINAPI XListView_SetGroupText(HELE hEle, int groupIndex, wchar_t *pText);//设置组文本
XC_API BOOL WINAPI XListView_SetItemIcon(HELE hEle, int groupIndex, int itemIndex, int imageID);//设置项图标ID

XC_API void WINAPI XListView_SetIconSize(HELE hEle, int cx, int cy); //设置图标区域大小,并不是图标的大小.
XC_API void WINAPI XListView_SetItemBorderSpacing(HELE hEle, int left, int top, int right, int bottom); //设置项边间隔
XC_API void WINAPI XListView_SetColumnSpacing(HELE hEle, int width); //设置项列间隔
XC_API void WINAPI XListView_SetRowSpacing(HELE hEle, int height);  //设置项行间隔
XC_API void WINAPI XListView_SetItemIconTextSpacing(HELE hEle, int height);  //设置图标与文本间隔
XC_API void WINAPI XListView_SetViewLeftAlign(HELE hEle, int size);  //设置视图左对齐
XC_API void WINAPI XListView_SetViewTopAlign(HELE hEle, int size); //设置视图上对齐
XC_API void WINAPI XListView_SetGroupHeight(HELE hEle, int height); //设置组高度

XC_API void WINAPI XListView_GetIconSize(HELE hEle, out_ SIZE *pSize); //获取图标区域大小,并不是图标的大小.
XC_API int  WINAPI XListView_GetItemBorderLeft(HELE hEle); //获取项边间隔
XC_API int  WINAPI XListView_GetItemBorderTop(HELE hEle);
XC_API int  WINAPI XListView_GetItemBorderRight(HELE hEle);
XC_API int  WINAPI XListView_GetItemBorderBottom(HELE hEle);
XC_API int  WINAPI XListView_GetColumnSpacing(HELE hEle); //获取项列间隔
XC_API int  WINAPI XListView_GetRowSpacing(HELE hEle);  //获取项行间隔
XC_API int  WINAPI XListView_GetItemIconTextSpacing(HELE hEle);  //获取图标与文本间隔
XC_API int  WINAPI XListView_GetViewLeftAlign(HELE hEle);  //获取视图左对齐
XC_API int  WINAPI XListView_GetViewTopAlign(HELE hEle); //获取视图上对齐
XC_API int  WINAPI XListView_GetGroupHeight(HELE hEle); //获取组高度

XC_API void  WINAPI XListView_GetSelectItem(HELE hEle, out_ int *pGroupIndex, out_ int *pItemIndex);    //获取选择项
XC_API int  WINAPI XListView_GetSelectCount(HELE hEle);  //获取选择项数量
XC_API int  WINAPI XListView_GetSelectAllItem(HELE hEle, int *pArrayGroupIndex, int *pArrayItemIndex, int arrayLength); //获取所有选择项

XC_API int  WINAPI XListView_GetGroupCount(HELE hEle); //获取组数量
XC_API int  WINAPI XListView_GetGroupMemberCount(HELE hEle, int groupIndex); //获取组成员数量
XC_API int  WINAPI XListView_GetUngroupMemberCount(HELE hEle);//获取未分组项数量

XC_API HXCGUI WINAPI XListView_GetImageList(HELE hEle); //获取图片列表
XC_API BOOL WINAPI XListView_GetItemRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect); //获取项坐标
XC_API BOOL WINAPI XListView_GetItemIconRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect);//获取项图标坐标
XC_API BOOL WINAPI XListView_GetItemTextRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect); //获取项文本坐标
XC_API wchar_t* WINAPI XListView_GetItemText(HELE hEle, int groupIndex, int itemIndex);//获取项文本
XC_API int  WINAPI XListView_GetItemIcon(HELE hEle, int groupIndex, int itemIndex);//获取项图标ID

XC_API wchar_t* WINAPI XListView_GetGroupText(HELE hEle, int groupIndex);//获取组文本
XC_API BOOL WINAPI XListView_GetGroupRect(HELE hEle, int groupIndex, out_ RECT *pRect);//获取组坐标

XC_API void* WINAPI XListView_GetItemData(HELE hEle, int groupIndex, int itemIndex); //获取项绑定数据
XC_API void* WINAPI XListView_GetGroupData(HELE hEle, int groupIndex); //获取组绑定数据

XC_API BOOL WINAPI XListView_DeleteItem(HELE hEle, int groupIndex, int itemIndex); //删除项
XC_API BOOL WINAPI XListView_DeleteGroup(HELE hEle, int groupIndex); //删除组
XC_API void WINAPI XListView_DeleteAllGroups(HELE hEle); //删除所有组
XC_API void WINAPI XListView_DeleteAll(HELE hEle); //删除所有,清空数据

XC_API int WINAPI XListView_IsItemSelect(HELE hEle, int groupIndex, int itemIndex);//检查项是否被选择
XC_API BOOL WINAPI XListView_HitTest(HELE hEle, POINT *pPt, out_ int *pGroupIndex, out_ int *pItemIndex);//测试用户点击,组,项

XC_API int WINAPI XListView_IsGroupExpand(HELE hEle, int groupIndex);//判断组是否展开
XC_API BOOL WINAPI XListView_SetGroupExpand(HELE hEle, int groupIndex, BOOL bExpand); //展开指定组

XC_API void WINAPI XListView_EnableMultiSelect(HELE hEle, BOOL bEnable); //启用关闭多项选择
XC_API void WINAPI XListView_EnableExpandButton(HELE hEle, BOOL bEnable); //启用/关闭展开按钮
XC_API void WINAPI XListView_CancelSelectItem(HELE hEle, int groupIndex, int itemIndex); //取消选择指定项
XC_API void WINAPI XListView_CancelSelectAll(HELE hEle); //取消选择所有项

XC_API void WINAPI XListView_SetUserDrawItem(HELE hEle, pFunListView_DrawItem pFunDrawItem); //设置用户自绘项
XC_API void WINAPI XListView_SetUserDrawGroup(HELE hEle, pFunListView_DrawGroup pFunDrawGroup); //设置用户自绘组

//设置贴图
XC_API void WINAPI XListView_SetItemImageSelect(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage);
XC_API void WINAPI XListView_SetItemImageStay(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage);

XC_API void WINAPI XListView_Adjust(HELE hEle); //调整布局

//私有方法:
void ListView_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
listView_group_ *ListView_CheckDownGroup(HELE hEle, POINT *pPt); //检查鼠标所按组
listView_item_  *ListView_CheckDownItem(HELE hEle, POINT *pPt);  //检查鼠标所按项

void ListView_DeleteItem_XC(HELE hEle, listView_item_ *pItem); //删除项,配合API删除项使用
void ListView_DeleteGroup_XC(HELE hEle, listView_group_ *pGroup); //删除组,配合API删除组使用

listView_item_  *ListView_GetItem_XC(HELE hEle, int groupIndex, int itemIndex); //获取项
listView_group_  *ListView_GetGroup_XC(HELE hEle, int groupIndex); //获取组

void ListView_AdjustItem(HELE hEle, listView_item_ *pItem, int x, int y);//计算项
void ListView_CalculateView(HELE hEle);

void ListView_DrawItem(HELE hEle, listView_drawItem_ *pItem);
void ListView_DrawGroup(HELE hEle, listView_drawGroup_ *pGroup);

void ListView_ShiftDown(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown1(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown2(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown3(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown4(HELE hEle, listView_item_ *pItem);

void ListView_MouseMoveDragBegin(HELE hEle, POINT *pPt); //准备拖动选择
void ListView_MouseMoveDrag(HELE hEle, POINT *pPt); //拖动选择


//回调函数
void CALLBACK ListView_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK ListView_OnEleDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ListView_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ListView_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnEleLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnEleLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点
BOOL CALLBACK ListView_OnEventMouseLeave(HELE hEle, HELE hEventEle);


extern HELE  g_hListView;
VOID CALLBACK ListView_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


//绘制拖动项窗口
BOOL CALLBACK ListView_OnDrawWindow_DragItem(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK ListView_OnWndMouseMove_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnWndLButtonUp_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnWndNCDestroy_DragItem(HWINDOW hWindow);
