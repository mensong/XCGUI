/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#include "StdAfx.h"

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持

void WINAPI XListView_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //设置用户自绘项
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawItem = (pFunListView_DrawItem)pCallBackFun;
	((listView_*)hEle)->pClass_Fun_Info = pClass_Fun_Info;
}

void WINAPI XListView_SetUserDrawGroupEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //设置用户自绘组
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawGroup = (pFunListView_DrawGroup)pCallBackFun;
	((listView_*)hEle)->pClass_Fun_Info_group = pClass_Fun_Info;
}

#endif

/// @defgroup listView 列表视图(ListView)
/// @ingroup groupElements
/// @{

/// @brief 创建列表视图元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或U I元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XListView_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	listView_ *pObj = (listView_*)malloc(sizeof(listView_));
	memset(pObj, 0, sizeof(listView_));

	ListView_Init((HELE)pObj, x, y, cx, cy, XC_LISTVIEW, hParent);
	return (HELE)pObj;
}

void ListView_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_LISTVIEW);
	listView_ *pListView = (listView_*)hEle;
	pListView->hArrayList = XArray_Create();
	pListView->hArrayGroupList = XArray_Create();
	pListView->hArrayCurrItem = XArray_Create();
	pListView->pCurrItem = NULL;
	pListView->bExpandButton = TRUE;
	pListView->bMultiSelect = TRUE;
	pListView->bDragItem = TRUE;
	pListView->hWndDrag = NULL;
	pListView->insertGroup = -1;
	pListView->insertItem = -1;

	pListView->iconSize.cx = 100;
	pListView->iconSize.cy = 100;
	pListView->left = 5;
	pListView->top = 5;
	pListView->right = 5;
	pListView->bottom = 5;
	pListView->columnSpace = 5;
	pListView->rowSpace = 5;
	pListView->iconTextSpace = 5;
	pListView->leftAlign = 5;
	pListView->topAlign = 5;
	pListView->groupHeight = 20;

	XSView_SetDrawScrollView(hEle, ListView_OnDrawScrollView);

	XEle_RegisterEvent(hEle, XE_DESTROY, ListView_OnDestroy);

	XEle_RegisterMessage(hEle, XM_PAINT, ListView_OnEleDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, ListView_OnEleLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, ListView_OnEleLButtonUp);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, ListView_OnEleMouseMove);

	XEle_RegisterEvent(hEle, XE_KILLFOCUS, ListView_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, ListView_OnEventMouseLeave);
}

/// @brief 增加项.
/// @param hEle 元素句柄.
/// @param pName 名称.
/// @param imageID 图片ID.
/// @param groupIndex 组索引.
/// @return 返回项索引，失败返回-1.
int WINAPI XListView_AddItem(HELE hEle, wchar_t *pName, int imageID, int groupIndex) //增加项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	listView_item_ *pItem = (listView_item_*)malloc(sizeof(listView_item_));
	memset(pItem, 0, sizeof(listView_item_));
	pItem->imageID = imageID;
	pItem->hString = XStr_Create(pName);

	HDC hdc;
	hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	pItem->rcText.left = 0;
	pItem->rcText.top = 0;
	pItem->rcText.right = ((listView_*)hEle)->iconSize.cx;
	pItem->rcText.bottom = 100;

	DrawText(hdc, (LPCWSTR)pName, wcslen(pName), &pItem->rcText, DT_CALCRECT);

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	int index = -1;
	if (groupIndex >= 0)
	{
		int countGroup = XArray_GetCount(pListView->hArrayGroupList);
		if (groupIndex < countGroup)
		{
			listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
			index = XArray_Add(pGroup->hArrayList, pItem);
		}
		else
		{
			XStr_Destroy(pItem->hString);
			free(pItem);
			return -1;
		}
	}
	else
	{
		index = XArray_Add(((listView_*)hEle)->hArrayList, pItem);
	}
	((listView_*)hEle)->bAdjust = TRUE;

	return index;
}

/// @brief 增加组.
/// @param hEle 元素句柄.
/// @param pName 名称.
/// @param bExpand 组是否展开.
/// @return 返回组索引，失败返回-1.
int  WINAPI XListView_AddGroup(HELE hEle, wchar_t *pName, BOOL bExpand) //增加组
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = (listView_group_*)malloc(sizeof(listView_group_));
	memset(pGroup, 0, sizeof(listView_group_));
	pGroup->hArrayList = XArray_Create();
	pGroup->hString = XStr_Create(pName);
	pGroup->bExpand = bExpand;
	int index = XArray_Add(((listView_*)hEle)->hArrayGroupList, pGroup);
	return index;
}

/// @brief 插入项.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引
/// @param itemIndex 项索引
/// @param pName 名称.
/// @param imageID 图片ID.
/// @return 返回项索引，失败返回-1.
int WINAPI XListView_InsertItem(HELE hEle, int groupIndex, int itemIndex, wchar_t *pName, int imageID)  //插入项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	listView_item_ *pItem = (listView_item_*)malloc(sizeof(listView_item_));
	memset(pItem, 0, sizeof(listView_item_));
	pItem->imageID = imageID;
	pItem->hString = XStr_Create(pName);

	HDC hdc;
	hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	pItem->rcText.left = 0;
	pItem->rcText.top = 0;
	pItem->rcText.right = ((listView_*)hEle)->iconSize.cx;
	pItem->rcText.bottom = 100;

	DrawText(hdc, (LPCWSTR)pName, wcslen(pName), &pItem->rcText, DT_CALCRECT);

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (-1 == groupIndex) //没有分组
	{
		int count = XArray_GetCount(pListView->hArrayList);
		if (groupIndex >= 0 && groupIndex < count)
		{
			int index = XArray_insert(pListView->hArrayList, pItem, groupIndex);
			pListView->bAdjust = TRUE;
			return index;
		}
	}
	else //子项
	{
		int countGroup = XArray_GetCount(pListView->hArrayGroupList);
		if (groupIndex >= 0 && groupIndex < countGroup)
		{
			listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
			int index = XArray_insert(pGroup->hArrayList, pItem, itemIndex);
			pListView->bAdjust = TRUE;
			return index;
		}
	}

	if (pItem->hString) XStr_Destroy(pItem->hString);
	free(pItem);

	return -1;
}

/// @brief 插入组.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引
/// @param pName 名称.
/// @param bExpand 是否展开组.
/// @return 返回组索引，失败返回-1.
int WINAPI XListView_InsertGroup(HELE hEle, int groupIndex, wchar_t *pName, BOOL bExpand)  //插入组
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)malloc(sizeof(listView_group_));
		memset(pGroup, 0, sizeof(listView_group_));
		pGroup->hArrayList = XArray_Create();
		pGroup->hString = XStr_Create(pName);
		pGroup->bExpand = bExpand;
		pListView->bAdjust = TRUE;

		XArray_insert(pListView->hArrayGroupList, pGroup, groupIndex);
		return groupIndex;
	}
	return -1;
}

/// @brief 设置图片列表.
/// @param hEle 元素句柄.
/// @param hImageList 图片列表
void WINAPI XListView_SetImageList(HELE hEle, HXCGUI hImageList)
{
	IsListViewDebug(hEle, __FUNCTION__);
	IsImageListDebug(hImageList, "在API:XListView_SetImageList()参数[hImageList]可能无效");

	listView_  *pListView = ((listView_*)hEle);
	if (pListView->hImageList)
	{
		XImageList_Destroy(pListView->hImageList);
		pListView->hImageList = NULL;
	}
	if (hImageList)
	{
		IsImageListDebug(hImageList, __FUNCTION__);
		pListView->hImageList = ImageList_AddRef(hImageList);
	}
}

/// @brief 启用或关闭展开按钮.
/// @param hEle 元素句柄.
/// @param bEnable 启用TRUE，关闭FALSE.
void WINAPI XListView_EnableExpandButton(HELE hEle, BOOL bEnable) //启用/关闭展开按钮
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->bExpandButton = bEnable;
	((listView_*)hEle)->bAdjust = TRUE;
}

/// @brief 取消选择指定项.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex  项索引.
void WINAPI XListView_CancelSelectItem(HELE hEle, int groupIndex, int itemIndex) //取消选择指定项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	if (pListView->bMultiSelect)
	{
		if (pListView->pCurrItem)
		{
			int count = Array_GetCount(pListView->hArrayCurrItem);
			if (count > 0)
			{
				listView_item_ *pItem = NULL;
				for (int i = 0; i < count; i++)
				{
					pItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i);
					if (groupIndex == pItem->groupIndex && itemIndex == pItem->index)
					{
						XArray_DeleteIndex(pListView->hArrayCurrItem, i);

						if (pItem == pListView->pCurrItem)
						{
							if (Array_GetCount(pListView->hArrayCurrItem) > 0)
								pListView->pCurrItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, 0);
							else
								pListView->pCurrItem = NULL;
						}
						if (STATE_SELECT == pItem->state)
							pItem->state = STATE_LEAVE;

						break;
					}
				}
			}
		}
	}
	else if (pListView->pCurrItem)
	{
		if (groupIndex == pListView->pCurrItem->groupIndex && itemIndex == pListView->pCurrItem->index)
		{
			if (STATE_SELECT == pListView->pCurrItem->state)
				pListView->pCurrItem->state = STATE_LEAVE;
			pListView->pCurrItem = NULL;
		}
	}
}

/// @brief 取消选择所有项.
/// @param hEle 元素句柄.
void WINAPI XListView_CancelSelectAll(HELE hEle) //取消选择所有项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	if (pListView->bMultiSelect)
	{
		if (pListView->pCurrItem)
		{
			int count = Array_GetCount(pListView->hArrayCurrItem);
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					((listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
				}
				XArray_DeleteAll(pListView->hArrayCurrItem);
				pListView->pCurrItem = NULL;
			}
		}
	}
	else if (pListView->pCurrItem)
	{
		if (STATE_SELECT == pListView->pCurrItem->state)
			pListView->pCurrItem->state = STATE_LEAVE;
		pListView->pCurrItem = NULL;
	}
}

/// @brief 获取选择项.
/// @param hEle 元素句柄.
/// @param pGroupIndex 接收组索引.
/// @param pItemIndex 接收项索引.
void WINAPI XListView_GetSelectItem(HELE hEle, out_ int *pGroupIndex, out_ int *pItemIndex)  //获取选择项
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (((listView_*)hEle)->pCurrItem)
	{
		*pGroupIndex = ((listView_*)hEle)->pCurrItem->groupIndex;
		*pItemIndex = ((listView_*)hEle)->pCurrItem->index;
	}
	else
	{
		*pGroupIndex = -1;
		*pItemIndex = -1;
	}
}

/// @brief 获取选择项数量.
/// @param hEle 元素句柄.
/// @return 选择项数量.
int  WINAPI XListView_GetSelectCount(HELE hEle)  //获取选择项数量
{
	IsListViewDebug(hEle, __FUNCTION__);

	if (((listView_*)hEle)->bMultiSelect)
	{
		return Array_GetCount(((listView_*)hEle)->hArrayCurrItem);
	}

	if (((listView_*)hEle)->pCurrItem)
		return 1;
	return 0;
}

/// @brief 获取所有选择项.
/// @param hEle 元素句柄.
/// @param pArrayGroupIndex 接收组索引数组.
/// @param pArrayItemIndex 接收项索引数组.
/// @param arrayLength 数组大小.
/// @return 返回的项实际数量.
int WINAPI XListView_GetSelectAllItem(HELE hEle, int *pArrayGroupIndex, int *pArrayItemIndex, int arrayLength) //获取所有选择项
{
	IsListViewDebug(hEle, __FUNCTION__);

	if (arrayLength < 1)
	{
		MessageBox(NULL, L"API:XListView_GetSelectAllItem(),参数[arrayLength]错误", L"炫彩界面库-错误提示", 0);
		exit(0);
	}

	listView_ *pListView = (listView_*)hEle;

	if (pListView->bMultiSelect)
	{
		int count = Array_GetCount(pListView->hArrayCurrItem);

		int counts = 0;
		if (arrayLength < count)
			counts = arrayLength;
		else
			counts = count;

		for (int i = 0; i < counts; i++)
		{
			listView_item_ *pItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i);
			pArrayGroupIndex[i] = pItem->groupIndex;
			pArrayItemIndex[i] = pItem->index;
		}

		return counts;
	}

	if (pListView->pCurrItem)
	{
		pArrayGroupIndex[0] = pListView->pCurrItem->groupIndex;
		pArrayItemIndex[0] = pListView->pCurrItem->index;
		return 1;
	}
	return 0;
}

/// @brief 获取组数量.
/// @param hEle 元素句柄.
/// @return 组数量.
int  WINAPI XListView_GetGroupCount(HELE hEle) //获取组数量
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	return XArray_GetCount(pListView->hArrayGroupList);
}

/// @brief 获取组成员数量.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引
/// @return 组成员数量.
int  WINAPI XListView_GetGroupMemberCount(HELE hEle, int groupIndex) //获取组成员数量
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	if (-1 == groupIndex)
	{
		return XArray_GetCount(pListView->hArrayList);
	}

	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
		return XArray_GetCount(pGroup->hArrayList);
	return -1;
}

/// @brief 获取未分组项数量.
/// @param hEle 元素句柄.
/// @return 成员数量.
int  WINAPI XListView_GetUngroupMemberCount(HELE hEle)  //获取未分组项数量
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	return XArray_GetCount(pListView->hArrayList);
}

/// @brief 获取图片列表.
/// @param hEle 元素句柄.
/// @return 图片列表句柄.
HXCGUI WINAPI XListView_GetImageList(HELE hEle) //获取图片列表
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	return pListView->hImageList;
}

/// @brief 获取项坐标.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param pRect 接收坐标.
/// @return 成功返回TRUE，否则相反.
BOOL WINAPI XListView_GetItemRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect) //获取项坐标
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		*pRect = pItem->rect;
		return TRUE;
	}
	return FALSE;
}

/// @brief 获取项图标坐标.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param pRect 接收坐标.
/// @return 成功返回TRUE，否则相反.
BOOL WINAPI XListView_GetItemIconRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect) //获取项图标坐标
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		*pRect = pItem->rcIcon;
		return TRUE;
	}
	return FALSE;
}

/// @brief 获取项文本坐标.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param pRect 接收坐标.
/// @return 成功返回TRUE，否则相反.
BOOL WINAPI XListView_GetItemTextRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect) //获取项文本坐标
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		*pRect = pItem->rcText;
		return TRUE;
	}
	return FALSE;
}

/// @brief 获取项文本.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @return 文本内容.
wchar_t* WINAPI XListView_GetItemText(HELE hEle, int groupIndex, int itemIndex) //获取项文本
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return XStr_GetBuffer(pItem->hString);
	}
	return NULL;
}

/// @brief 获取项图标ID.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @return 项图标ID,失败返回-1.
int WINAPI XListView_GetItemIcon(HELE hEle, int groupIndex, int itemIndex) //获取项图标ID
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return pItem->imageID;
	}
	return -1;
}

/// @brief 获取组文本.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @return 文本内容.
wchar_t* WINAPI XListView_GetGroupText(HELE hEle, int groupIndex)  //获取组文本
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		return XStr_GetBuffer(pGroup->hString);
	}
	return NULL;
}

/// @brief 获取组坐标.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param pRect  接收组坐标.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XListView_GetGroupRect(HELE hEle, int groupIndex, out_ RECT *pRect)  //获取组坐标
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		*pRect = pGroup->rect;
		return TRUE;
	}
	return NULL;
}

/// @brief 设置项绑定数据.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param data 绑定数据.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetItemData(HELE hEle, int groupIndex, int itemIndex, int data) //设置项绑定数据
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		pItem->userData = data;
		return TRUE;
	}
	return FALSE;
}

/// @brief 获取项绑定数据.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @return 项绑定数据，失败返回-1.
int  WINAPI XListView_GetItemData(HELE hEle, int groupIndex, int itemIndex) //获取项绑定数据
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return pItem->userData;
	}
	return -1;
}

/// @brief 设置组绑定数据.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param data 绑定数据.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetGroupData(HELE hEle, int groupIndex, int data) //设置组绑定数据
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		pGroup->userData = data;
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置选择项.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param bSelect 选择TRUE.未选择FALSE.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetSelectItem(HELE hEle, int groupIndex, int itemIndex, BOOL bSelect) //设置选择项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		if (bSelect)
		{
			if (STATE_SELECT != pItem->state)
			{
				if (pListView->bMultiSelect)
				{
					XArray_Add(pListView->hArrayCurrItem, pItem);
				}
				else
				{
					if (pListView->pCurrItem)
						pListView->pCurrItem->state = STATE_LEAVE;
				}
				pItem->state = STATE_SELECT;
				pListView->pCurrItem = pItem;
			}
		}
		else
		{
			if (STATE_SELECT == pItem->state)
			{
				if (pListView->bMultiSelect)
				{
					pItem->state = STATE_LEAVE;
					XArray_Delete(pListView->hArrayCurrItem, pItem);
					if (pItem == pListView->pCurrItem)
					{
						pListView->pCurrItem = NULL;
						if (XArray_GetCount(pListView->hArrayCurrItem) > 0)
							pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
					}
				}
				else
				{
					if (pItem == pListView->pCurrItem)
					{
						pListView->pCurrItem->state = STATE_LEAVE;
						pListView->pCurrItem = NULL;
					}
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置项文本.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param pText 文本内容.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetItemText(HELE hEle, int groupIndex, int itemIndex, wchar_t *pText) //设置项文本
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem && pText)
	{
		XStr_SetString(pItem->hString, pText);
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置组文本.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引..
/// @param pText 文本内容.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetGroupText(HELE hEle, int groupIndex, wchar_t *pText) //设置组文本
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup && pText)
	{
		XStr_SetString(pGroup->hString, pText);
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置项图标ID.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @param imageID 图标ID.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetItemIcon(HELE hEle, int groupIndex, int itemIndex, int imageID) //设置项图标ID
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		pItem->imageID = imageID;
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置图标区域大小,并不是图标的大小.
/// @param hEle 元素句柄.
/// @param cx 宽度.
/// @param cy 高度.
void WINAPI XListView_SetIconSize(HELE hEle, int cx, int cy)
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->iconSize.cx = cx;
	((listView_*)hEle)->iconSize.cy = cy;
}

/// @brief 设置项边间隔
/// @param hEle   元素句柄.
/// @param left   左边间隔.
/// @param top    上边间隔.
/// @param right  右边间隔.
/// @param bottom 下边间隔.
void WINAPI XListView_SetItemBorderSpacing(HELE hEle, int left, int top, int right, int bottom) //设置项边间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->left = left;
	((listView_*)hEle)->top = top;
	((listView_*)hEle)->right = right;
	((listView_*)hEle)->bottom = bottom;
}

/// @brief 设置项列间隔
/// @param hEle   元素句柄.
/// @param width  列间隔.
void WINAPI XListView_SetColumnSpacing(HELE hEle, int width) //设置项列间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->columnSpace = width;
}

/// @brief 设置项行间隔
/// @param hEle   元素句柄.
/// @param height  行间隔.
void WINAPI XListView_SetRowSpacing(HELE hEle, int height)  //设置项行间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->rowSpace = height;
}

/// @brief 设置图标与文本间隔
/// @param hEle   元素句柄.
/// @param height  间隔大小.
void WINAPI XListView_SetItemIconTextSpacing(HELE hEle, int height) //设置图标与文本间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->iconTextSpace = height;
}

/// @brief 设置视图左对齐间隔
/// @param hEle   元素句柄.
/// @param size  间隔大小.
void WINAPI XListView_SetViewLeftAlign(HELE hEle, int size)  //设置视图左对齐
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->leftAlign = size;
}

/// @brief 设置视图上对齐间隔
/// @param hEle   元素句柄.
/// @param size  间隔大小.
void WINAPI XListView_SetViewTopAlign(HELE hEle, int size) //设置视图上对齐
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->topAlign = size;
}

/// @brief 设置组高度
/// @param hEle   元素句柄.
/// @param height  组高度.
void WINAPI XListView_SetGroupHeight(HELE hEle, int height) //设置组高度
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->groupHeight = height;
}

/// @brief 获取图标区域大小,并不是图标的大小.
/// @param hEle   元素句柄.
/// @param pSize  接收图标区域大小.
void WINAPI XListView_GetIconSize(HELE hEle, out_ SIZE *pSize) //获取图标区域大小,并不是图标的大小.
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (pSize)
		*pSize = ((listView_*)hEle)->iconSize;
}

/// @brief 获取项左边间隔.
/// @param hEle   元素句柄.
/// @return 返回左边间隔大小.
int  WINAPI XListView_GetItemBorderLeft(HELE hEle) //获取项边间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->left;
}

/// @brief 获取项上边间隔.
/// @param hEle   元素句柄.
/// @return 返回上边间隔大小.
int  WINAPI XListView_GetItemBorderTop(HELE hEle)
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->top;
}

/// @brief 获取项右边间隔.
/// @param hEle   元素句柄.
/// @return 返回右边间隔大小.
int  WINAPI XListView_GetItemBorderRight(HELE hEle)
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->right;
}

/// @brief 获取项下边间隔.
/// @param hEle   元素句柄.
/// @return 返回下边间隔大小.
int  WINAPI XListView_GetItemBorderBottom(HELE hEle)
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->bottom;
}

/// @brief 获取项列间隔.
/// @param hEle   元素句柄.
/// @return 返回项列间隔大小.
int  WINAPI XListView_GetColumnSpacing(HELE hEle) //获取项列间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->columnSpace;
}

/// @brief 获取项行间隔.
/// @param hEle   元素句柄.
/// @return 返回项行间隔大小.
int  WINAPI XListView_GetRowSpacing(HELE hEle)  //获取项行间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->rowSpace;
}

/// @brief 获取图标与文本间隔.
/// @param hEle   元素句柄.
/// @return 返回图标与文本间隔大小.
int  WINAPI XListView_GetItemIconTextSpacing(HELE hEle)  //获取图标与文本间隔
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->iconTextSpace;
}

/// @brief 获取视图左对齐间隔.
/// @param hEle   元素句柄.
/// @return 返回视图左对齐间隔大小.
int  WINAPI XListView_GetViewLeftAlign(HELE hEle)  //获取视图左对齐
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->leftAlign;
}

/// @brief 获取视图上对齐间隔.
/// @param hEle   元素句柄.
/// @return 返回视图上对齐间隔大小.
int  WINAPI XListView_GetViewTopAlign(HELE hEle) //获取视图上对齐
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->topAlign;
}

/// @brief 获取组高度.
/// @param hEle   元素句柄.
/// @return 返回组高度.
int  WINAPI XListView_GetGroupHeight(HELE hEle) //获取组高度
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->groupHeight;
}

/// @brief 获取组绑定数据.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @return 组绑定数据,失败返回-1.
int  WINAPI XListView_GetGroupData(HELE hEle, int groupIndex) //获取组绑定数据
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		return pGroup->userData;
	}
	return -1;
}

/// @brief 删除项.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex  项索引.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_DeleteItem(HELE hEle, int groupIndex, int itemIndex) //删除项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
		int count = XArray_GetCount(pGroup->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, itemIndex);
			XArray_DeleteIndex(pGroup->hArrayList, itemIndex);
			ListView_DeleteItem_XC(hEle, pItem); //检查选择项是否改变,并且释放项
			pListView->bAdjust = TRUE;
			return TRUE;
		}
	}
	else if (-1 == groupIndex)
	{
		int count = XArray_GetCount(pListView->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, itemIndex);
			XArray_DeleteIndex(pListView->hArrayList, itemIndex);
			ListView_DeleteItem_XC(hEle, pItem); //检查选择项是否改变,并且释放项
			pListView->bAdjust = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}

/// @brief 删除组.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_DeleteGroup(HELE hEle, int groupIndex) //删除组
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex <= countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
		XArray_DeleteIndex(pListView->hArrayGroupList, groupIndex);
		ListView_DeleteGroup_XC(hEle, pGroup);//检查选择项是否改变,并且释放组及子项
		pListView->bAdjust = TRUE;
		return TRUE;
	}
	return FALSE;
}

/// @brief 删除所有组.
/// @param hEle 元素句柄.
void WINAPI XListView_DeleteAllGroups(HELE hEle) //删除所有组
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = 0; i < countGroup; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		ListView_DeleteGroup_XC(hEle, pGroup);
	}
	XArray_DeleteAll(pListView->hArrayGroupList);
}

/// @brief 删除所有,清空列表视图.
/// @param hEle 元素句柄.
void WINAPI XListView_DeleteAll(HELE hEle) //删除所有,清空数据
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	XListView_DeleteAllGroups(hEle);

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		ListView_DeleteItem_XC(hEle, pItem);
	}
	XArray_DeleteAll(pListView->hArrayList);
}

/// @brief 判断项是否被选择.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex 项索引.
/// @return 选择1,未选择0,失败-1.
int WINAPI XListView_IsItemSelect(HELE hEle, int groupIndex, int itemIndex)  //判断项是否被选择
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return STATE_SELECT == pItem->state ? 1 : 0;
	}
	return -1;
}

/// @brief 测试鼠标点击,组,项.
/// @param hEle 元素句柄.
/// @param pPt 坐标点.
/// @param pGroupIndex 接收组索引.
/// @param pItemIndex 接收项索引.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_HitTest(HELE hEle, POINT *pPt, out_ int *pGroupIndex, out_ int *pItemIndex) //测试鼠标点击,组,项
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	POINT  pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);

	//组
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		if (PtInRect(&pGroup->rcButton, pt)) //组啊展开收缩
		{
			*pGroupIndex = g;
			*pItemIndex = -1;
			return TRUE;
		}
		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (PtInRect(&pItem->rect, pt)) //选择项
				{
					*pGroupIndex = g;
					*pItemIndex = i;
					return TRUE;
				}
			}
		}
	}

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (PtInRect(&pItem->rect, pt))
		{
			*pGroupIndex = -1;
			*pItemIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

/// @brief 判断组是否展开.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @return 展开1,未展开0,失败-1.
int WINAPI XListView_IsGroupExpand(HELE hEle, int groupIndex) //判断组是否展开
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		return pGroup->bExpand ? 1 : 0;
	}
	return -1;
}

/// @brief 展开指定组.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param bExpand 展开TRUE,不展开FALSE.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListView_SetGroupExpand(HELE hEle, int groupIndex, BOOL bExpand) //展开指定组
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		pGroup->bExpand = bExpand;
		return TRUE;
	}
	return FALSE;
}

void ListView_DeleteItem_XC(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	BOOL  bSelItemChange = FALSE; //选择项改变

	int countSelItem = XArray_GetCount(pListView->hArrayCurrItem);
	for (int i = 0; i < countSelItem; i++)
	{
		if (pItem == ((listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, i)))
		{
			XArray_DeleteIndex(pListView->hArrayCurrItem, i);
			bSelItemChange = TRUE;
			break;
		}
	}

	if (pItem == pListView->pCurrItem)
	{
		bSelItemChange = TRUE;
		pListView->pCurrItem = NULL;

		int count = XArray_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
			pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
	}

	if (pItem->hString) XStr_Destroy(pItem->hString);
	if (pItem->hImage_select) XImage_Destroy(pItem->hImage_select);
	if (pItem->hImage_stay) XImage_Destroy(pItem->hImage_stay);
	free(pItem);

	if (bSelItemChange)
	{
		//		if(pListView->pCurrItem)
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,pListView->pCurrItem->id,0);
		//		else
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,-1,0);
	}
}

void ListView_DeleteGroup_XC(HELE hEle, listView_group_ *pGroup)
{
	listView_ *pListView = (listView_*)hEle;

	BOOL  bSelItemChange = FALSE; //选择项改变

	int count = XArray_GetCount(pGroup->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
		int countSelItem = XArray_GetCount(pListView->hArrayCurrItem);
		for (int s = 0; s < countSelItem; s++)
		{
			listView_item_ *pSelItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, s);
			if (pSelItem == pItem)
			{
				XArray_DeleteIndex(pListView->hArrayCurrItem, s);
				bSelItemChange = TRUE;
				break;
			}
		}
		if (pListView->pCurrItem == pItem)
		{
			bSelItemChange = TRUE;
			pListView->pCurrItem = NULL;

			int count = XArray_GetCount(pListView->hArrayCurrItem);
			if (count > 0)
				pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
		}

		if (pItem->hString) XStr_Destroy(pItem->hString);
		free(pItem);
	}
	XArray_Destroy(pGroup->hArrayList);
	if (pGroup->hString) XStr_Destroy(pGroup->hString);
	free(pGroup);

	if (bSelItemChange)
	{
		//		if(pListView->pCurrItem)
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,pListView->pCurrItem->id,0);
		//		else
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,-1,0);
	}
}

listView_item_  *ListView_GetItem_XC(HELE hEle, int groupIndex, int itemIndex) //获取项
{
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
		int count = XArray_GetCount(pGroup->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			return (listView_item_*)XArray_GetAt(pGroup->hArrayList, itemIndex);
		}
	}
	else if (-1 == groupIndex)
	{
		int count = XArray_GetCount(pListView->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			return (listView_item_*)XArray_GetAt(pListView->hArrayList, itemIndex);
		}
	}
	return NULL;
}

listView_group_  *ListView_GetGroup_XC(HELE hEle, int groupIndex) //获取组
{
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		return (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
	}
	return NULL;
}

/// @brief 启用或关闭多项选择.
/// @param hEle 元素句柄.
/// @param bEnable 启用TRUE,关闭FALSE.
void WINAPI XListView_EnableMultiSelect(HELE hEle, BOOL bEnable) //启用关闭多项选择
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	if (bEnable)
	{
		if (bEnable != pListView->bMultiSelect)
		{
			pListView->bMultiSelect = bEnable;
			int count = XArray_GetCount(pListView->hArrayCurrItem);
			if (count < 1)
				XArray_Add(pListView->hArrayCurrItem, pListView->pCurrItem);
		}
	}
	else if (bEnable != pListView->bMultiSelect)
	{
		pListView->bMultiSelect = bEnable;
		int count = XArray_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				((listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
			}
			XArray_DeleteAll(pListView->hArrayCurrItem);
			pListView->pCurrItem->state = STATE_SELECT;
		}
	}
}

/// @brief 设置用户自绘项.
/// @param hEle 元素句柄.
/// @param pFunDrawItem 自绘函数名,格式如下:
/// @code void CALLBACK ListView_DrawItem(HELE hEle,listView_drawItem_ *pDrawItem); @endcode
void WINAPI XListView_SetUserDrawItem(HELE hEle, pFunListView_DrawItem pFunDrawItem) //设置用户自绘项
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	((listView_*)hEle)->pClass_Fun_Info = NULL;
#endif
}

/// @brief 设置用户自绘组.
/// @param hEle 元素句柄.
/// @param pFunDrawGroup 自绘函数名,格式如下:
/// @code void CALLBACK ListView_DrawGroup(HELE hEle,listView_drawGroup_ *pDrawGroup); @endcode
void WINAPI XListView_SetUserDrawGroup(HELE hEle, pFunListView_DrawGroup pFunDrawGroup) //设置用户自绘组
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawGroup = pFunDrawGroup;
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	((listView_*)hEle)->pClass_Fun_Info_group = NULL;
#endif
}

/// @brief 设置项选择状态贴图.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex  项索引.
/// @param hImage    图片句柄.
void WINAPI XListView_SetItemImageSelect(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage)
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	listView_item_ *pItem = (listView_item_*)ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		Image_AddImage(pItem->hImage_select, hImage);
	}
}

/// @brief 设置项鼠标停留状态贴图.
/// @param hEle 元素句柄.
/// @param groupIndex 组索引.
/// @param itemIndex  项索引.
/// @param hImage   图片句柄.
void WINAPI XListView_SetItemImageStay(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage)
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	listView_item_ *pItem = (listView_item_*)ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		Image_AddImage(pItem->hImage_stay, hImage);
	}
}

//计算视图大小
void ListView_CalculateView(HELE hEle)
{
	listView_ *pListView = (listView_*)hEle;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	int right = rect.right - XSView_GetSpacingRight(hEle);
	right = right - XSView_GetScrollBarWidth(hEle);

	int t1 = XSView_GetSpacingLeft(hEle);
	int t2 = XSView_GetSpacingTop(hEle);

	//计算分组项
	int leftSpace = t1 + pListView->leftAlign; //边框左间隔
	int topSpace = t2 + pListView->topAlign;  //边框上间隔

	int x = leftSpace; //X叠加
	int y = topSpace;  //Y叠加
	int y2 = topSpace; //计算每行最大的bottom值

	int count = XArray_GetCount(pListView->hArrayList);
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	int itemCX = pListView->iconSize.cx + pListView->left + pListView->right; //项宽度

	//计算视图//////////////////////////////////////////////////
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		y += pListView->groupHeight;
		int countItem = XArray_GetCount(pGroup->hArrayList);
		if (pGroup->bExpand)
		{
			if (countItem < 1)
			{
				y += pListView->groupHeight; //空行高度
			}
			else
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);

					x = x + itemCX + pListView->columnSpace;
					int bottpm = y + pListView->top + pListView->bottom + pListView->iconSize.cy + pListView->iconTextSpace + (pItem->rcText.bottom - pItem->rcText.top);

					if (bottpm > y2)
					{
						y2 = bottpm;
					}

					if ((x + itemCX + pListView->columnSpace) > right) //换行
					{
						x = leftSpace;
						y = y2 + pListView->rowSpace; //行间隔
					}
				}
				y = y2 + pListView->rowSpace; //行间隔
				x = leftSpace;
			}
		}
	}
	y2 = y;
	//计算未分组项
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);

		x = x + itemCX + pListView->columnSpace;

		int bottom = y + pListView->top + pListView->bottom + pListView->iconSize.cy + pListView->iconTextSpace + (pItem->rcText.bottom - pItem->rcText.top);

		if (bottom > y2)
		{
			y2 = bottom;
		}

		if ((x + itemCX + pListView->columnSpace) > right) //换行
		{
			x = leftSpace;
			y = y2 + pListView->rowSpace; //行间隔
		}
	}
	y = y2 + pListView->rowSpace; //列间隔
	XSView_SetSize(hEle, 10, y);
	XTRACE("y2= %d \n", y2);
}

/// @brief 调整布局.
/// @param hEle 元素句柄.
void WINAPI XListView_Adjust(HELE hEle) //调整布局
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	pListView->bAdjust = FALSE;

	ListView_CalculateView(hEle); //计算视图大小

	int count = XArray_GetCount(pListView->hArrayList);
	int viewWidth = XSView_GetViewWidth(hEle);

	int t1 = XSView_GetSpacingLeft(hEle);
	int t2 = XSView_GetSpacingTop(hEle);

	//计算分组项
	int leftSpace = t1 + pListView->leftAlign; //边框左间隔
	int topSpace = t2 + pListView->topAlign;  //边框上间隔

	int x = leftSpace; //X叠加
	int y = topSpace;  //Y叠加
	int y2 = topSpace; //计算每行最大的bottom值

	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	int itemCX = pListView->iconSize.cx + pListView->left + pListView->right; //项宽度
	//计算坐标//////////////////////////////////////////////////////
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		pGroup->index = g;

		pGroup->rect.left = x;
		pGroup->rect.top = y;
		pGroup->rect.right = viewWidth;
		pGroup->rect.bottom = y + pListView->groupHeight - 1;

		if (pListView->bExpandButton) //展开按钮
		{
			pGroup->rcButton.left = x + 3;
			pGroup->rcButton.top = y + (pListView->groupHeight - 12) / 2;
			pGroup->rcButton.right = pGroup->rcButton.left + 12;
			pGroup->rcButton.bottom = pGroup->rcButton.top + 12;

			//组文本区域
			pGroup->rcText.left = pGroup->rcButton.left + 15;
			pGroup->rcText.top = y;
			pGroup->rcText.right = viewWidth;
			pGroup->rcText.bottom = (y += pListView->groupHeight);
		}
		else
		{
			//组文本区域
			pGroup->rcText.left = x + 3;
			pGroup->rcText.top = y;
			pGroup->rcText.right = viewWidth;
			pGroup->rcText.bottom = (y += pListView->groupHeight);
		}

		int countItem = XArray_GetCount(pGroup->hArrayList);
		if (pGroup->bExpand)
		{
			if (countItem < 1)
			{
				y += pListView->groupHeight; //空行高度
			}
			else
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
					pItem->index = i;
					pItem->groupIndex = g;

					ListView_AdjustItem(hEle, pItem, x, y);

					if (pItem->rect.bottom > y2)
					{
						y2 = pItem->rect.bottom;
					}
					x = pItem->rect.right + pListView->columnSpace;

					if ((x + itemCX + pListView->columnSpace) > viewWidth)
					{
						x = leftSpace;
						y = y2 + pListView->rowSpace; //行间隔
					}
				}
				y = y2 + pListView->rowSpace; //行间隔
				x = leftSpace;
			}
		}
		else
		{
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				pItem->index = i;
				pItem->groupIndex = g;
			}
		}
	}

	//计算未分组项
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		pItem->index = i;
		pItem->groupIndex = -1;

		ListView_AdjustItem(hEle, pItem, x, y);

		if (pItem->rect.bottom > y2)
		{
			y2 = pItem->rect.bottom;
		}
		x = pItem->rect.right + pListView->columnSpace;

		if ((x + itemCX + pListView->columnSpace) > viewWidth)
		{
			x = leftSpace;
			y = y2 + pListView->rowSpace; //行间隔
		}
	}
	XTRACE("x2= %d \n", y2);
}

void ListView_AdjustItem(HELE hEle, listView_item_ *pItem, int x, int y)  //计算项
{
	listView_ *pListView = (listView_*)hEle;

	pItem->rcIcon.left = x + pListView->left;
	pItem->rcIcon.top = y + pListView->top;
	pItem->rcIcon.right = pItem->rcIcon.left + pListView->iconSize.cx;
	pItem->rcIcon.bottom = pItem->rcIcon.top + pListView->iconSize.cy;

	//计算图标绘制区域
	if (pListView->hImageList)
	{
		int imageWidth = 0;
		int imageHeight = 0;
		if (XImageList_IsFixedSize(pListView->hImageList))
		{
			imageWidth = XImageList_GetWidth(pListView->hImageList);
			imageHeight = XImageList_GetHeight(pListView->hImageList);
		}
		else
		{
			HIMAGE hImage = XImageList_GetImage(pListView->hImageList, pItem->imageID);
			if (hImage)
			{
				imageWidth = XImage_GetWidth(hImage);
				imageHeight = XImage_GetHeight(hImage);
			}
		}

		int width = pListView->iconSize.cx;
		int height = pListView->iconSize.cy;
		if (imageWidth > width || imageHeight > height)
		{
			if (imageWidth > imageHeight)
			{
				int imageHeight2 = 0;
				if (0 != imageWidth && 0 != width)
				{
					double  t = ((double)width) / imageWidth;
					if (FALSE == IsFlaotZero(t))
						imageHeight2 = (int)(imageHeight*t);
				}

				pItem->rcIconDraw.top = pItem->rcIcon.bottom - imageHeight2;
				pItem->rcIconDraw.bottom = pItem->rcIcon.bottom;

				pItem->rcIconDraw.left = x + pListView->left;
				pItem->rcIconDraw.right = pItem->rcIconDraw.left + width;
			}
			else
			{
				int imageWidth2 = 0;
				if (0 != imageHeight && 0 != height)
				{
					double  t = ((double)height) / imageHeight;
					if (FALSE == IsFlaotZero(t))
						imageWidth2 = (int)(imageWidth*t);
				}

				pItem->rcIconDraw.left = x + pListView->left + (width - imageWidth2) / 2;
				pItem->rcIconDraw.right = pItem->rcIconDraw.left + imageWidth2;
				pItem->rcIconDraw.top = pItem->rcIcon.bottom - height;
				pItem->rcIconDraw.bottom = pItem->rcIcon.bottom;
			}
		}
		else
		{
			pItem->rcIconDraw.left = x + pListView->left + (width - imageWidth) / 2;
			pItem->rcIconDraw.right = pItem->rcIconDraw.left + imageWidth;
			pItem->rcIconDraw.top = pItem->rcIcon.bottom - imageHeight;
			pItem->rcIconDraw.bottom = pItem->rcIcon.bottom;
		}
	}

	int textHeight = pItem->rcText.bottom - pItem->rcText.top;

	pItem->rcText.left = x;
	pItem->rcText.right = pItem->rcIcon.right + pListView->right;
	pItem->rcText.top = pItem->rcIcon.bottom + pListView->iconTextSpace;
	pItem->rcText.bottom = pItem->rcText.top + textHeight;

	pItem->rect.left = x;
	pItem->rect.top = y;
	pItem->rect.right = pItem->rcIcon.right + pListView->right;
	pItem->rect.bottom = pItem->rcText.bottom + pListView->bottom;
}

void CALLBACK ListView_OnDestroy(HELE hEle) //销毁
{
	//删除所有项
	listView_ *pListView = (listView_*)hEle;

	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		int countItem = XArray_GetCount(pGroup->hArrayList);
		for (int i = 0; i < countItem; i++)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
			if (pItem->hString) XStr_Destroy(pItem->hString);
			if (pItem->hImage_select) XImage_Destroy(pItem->hImage_select);
			if (pItem->hImage_stay) XImage_Destroy(pItem->hImage_stay);
			free(pItem);
		}
		XArray_Destroy(pGroup->hArrayList);
		if (pGroup->hString) XStr_Destroy(pGroup->hString);
		free(pGroup);
	}

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (pItem->hString) XStr_Destroy(pItem->hString);
		if (pItem->hImage_select) XImage_Destroy(pItem->hImage_select);
		if (pItem->hImage_stay) XImage_Destroy(pItem->hImage_stay);
		free(pItem);
	}

	XArray_Destroy(pListView->hArrayList);
	XArray_Destroy(pListView->hArrayGroupList);
	if (pListView->hArrayCurrItem) XArray_Destroy(pListView->hArrayCurrItem);
	if (pListView->hImageList) XImageList_Destroy(pListView->hImageList);

#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	if (pListView->pClass_Fun_Info)
		free(pListView->pClass_Fun_Info);
	if (pListView->pClass_Fun_Info_group)
		free(pListView->pClass_Fun_Info_group);
#endif
}

BOOL CALLBACK ListView_OnEleDraw(HELE hEle, HDRAW hDraw)
{
	if (((listView_*)hEle)->bAdjust)
		XListView_Adjust(hEle);
	return FALSE;
}

BOOL CALLBACK ListView_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	listView_ *pListView = (listView_*)hEle;

	//绘制组
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);

		listView_drawGroup_ group;
		group.bExpand = pGroup->bExpand;
		group.hDraw = hDraw;
		group.rcButton = pGroup->rcButton;
		group.rcText = pGroup->rcText;
		group.pText = XStr_GetBuffer(pGroup->hString);
		group.userData = pGroup->userData;
		group.rect = pGroup->rect;
		ListView_DrawGroup(hEle, &group);

		XDraw_RestoreGDIOBJ_(hDraw);

		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++) //绘制项
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				listView_drawItem_  item;
				item.hDraw = hDraw;
				item.groupIndex = g;
				item.itemIndex = i;
				item.imageID = pItem->imageID;
				item.pText = XStr_GetBuffer(pItem->hString);
				item.rcIcon = pItem->rcIcon;
				item.rcIconDraw = pItem->rcIconDraw;
				item.rcText = pItem->rcText;
				item.rect = pItem->rect;
				item.userData = pItem->userData;
				item.state = pItem->state;
				item.hImage_select = pItem->hImage_select;
				item.hImage_stay = pItem->hImage_stay;

				ListView_DrawItem(hEle, &item);

				XDraw_RestoreGDIOBJ_(hDraw);
			}
		}
	}

	//绘制未分组项
	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);

		listView_drawItem_  item;
		item.hDraw = hDraw;
		item.groupIndex = -1;
		item.itemIndex = i;
		item.imageID = pItem->imageID;
		item.pText = XStr_GetBuffer(pItem->hString);
		item.rcIcon = pItem->rcIcon;
		item.rcIconDraw = pItem->rcIconDraw;
		item.rcText = pItem->rcText;
		item.rect = pItem->rect;
		item.userData = pItem->userData;
		item.state = pItem->state;
		item.hImage_select = pItem->hImage_select;
		item.hImage_stay = pItem->hImage_stay;

		ListView_DrawItem(hEle, &item);

		XDraw_RestoreGDIOBJ_(hDraw);
	}

	//绘制拖动矩形---------
	if (pListView->bDrag)
	{
		RECT rcDrag;
		if (pListView->dragEndPt.x > pListView->dragPt.x)
		{
			rcDrag.left = pListView->dragPt.x;
			rcDrag.right = pListView->dragEndPt.x;
		}
		else
		{
			rcDrag.left = pListView->dragEndPt.x;
			rcDrag.right = pListView->dragPt.x;
		}

		if (pListView->dragEndPt.y > pListView->dragPt.y)
		{
			rcDrag.top = pListView->dragPt.y;
			rcDrag.bottom = pListView->dragEndPt.y;
		}
		else
		{
			rcDrag.top = pListView->dragEndPt.y;
			rcDrag.bottom = pListView->dragPt.y;
		}

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(80, 168, 220));
		XDraw_FrameRect_(hDraw, &rcDrag, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}

	return TRUE;
}

void ListView_DrawItem(HELE hEle, listView_drawItem_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	if (pListView->pDrawItem)	//用户自绘
	{
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		if (pListView->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)pItem;
			event_.lParam = NULL;
			event_.pClass_fun = pListView->pClass_Fun_Info;
			((pFunClassEventMsg)pListView->pDrawItem)(&event_, xc_fun_v_e_listView_item);
		}
		else
		{
			pListView->pDrawItem(hEle, pItem);
		}
#else
		pList->pDrawItem(hEle, &pItem);
#endif
	}
	else  //系统绘制
	{
		if (STATE_SELECT == pItem->state)
		{
			if (pItem->hImage_select)
			{
				XDraw_HImageSuper_(pItem->hDraw, pItem->hImage_select, &pItem->rect);
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(pItem->hDraw, pItem->rect.left, pItem->rect.top, pItem->rect.right + 1, pItem->rect.bottom + 1, 3, 3);
				XDraw_GradientFill2_(pItem->hDraw, RGB(250, 250, 250), RGB(200, 200, 200), &pItem->rect, GRADIENT_FILL_RECT_V);
				HBRUSH hBrush = XDraw_CreateSolidBrush_(pItem->hDraw, RGB(160, 160, 160));
				XDraw_FrameRgn_(pItem->hDraw, hRgn, hBrush, 1, 1);
			}
		}
		else if (STATE_STAY == pItem->state)
		{
			if (pItem->hImage_stay)
			{
				XDraw_HImageSuper_(pItem->hDraw, pItem->hImage_stay, &pItem->rect);
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(pItem->hDraw, pItem->rect.left, pItem->rect.top, pItem->rect.right + 1, pItem->rect.bottom + 1, 3, 3);
				XDraw_GradientFill2_(pItem->hDraw, RGB(255, 255, 255), RGB(230, 230, 230), &pItem->rect, GRADIENT_FILL_RECT_V);
				HBRUSH hBrush = XDraw_CreateSolidBrush_(pItem->hDraw, RGB(220, 220, 220));
				XDraw_FrameRgn_(pItem->hDraw, hRgn, hBrush, 1, 1);
			}
		}

		if (pListView->hImageList)
			XImageList_DrawImage2(pListView->hImageList, pItem->hDraw, pItem->imageID, &pItem->rcIconDraw);

		if (pItem->pText)
			XDraw_DrawText_(pItem->hDraw, pItem->pText, wcslen(pItem->pText), &pItem->rcText, DT_CENTER);

		//绘制插入点
		if (pListView->hWndDrag)
		{
			if ((pListView->insertGroup == pItem->groupIndex) && (pListView->insertItem == pItem->itemIndex))
			{
				HPEN hPen = XDraw_CreatePen_(pItem->hDraw, PS_SOLID, 2, RGB(0, 162, 232));
				HGDIOBJ hOldPen = XDraw_SelectObject_(pItem->hDraw, hPen);

				XDraw_MoveToEx_(pItem->hDraw, pItem->rect.left - 2, pItem->rect.top);
				XDraw_LineTo_(pItem->hDraw, pItem->rect.left - 2, pItem->rect.bottom);

				XDraw_SelectObject_(pItem->hDraw, hOldPen);
				XDraw_DeleteObject_(pItem->hDraw, hPen);
			}
			else if (pListView->insertGroup == pItem->groupIndex)
			{
				int memberCount = XListView_GetGroupMemberCount(hEle, pItem->groupIndex);
				if (memberCount > 0 && pListView->insertItem > 0)
				{
					if (pListView->insertItem == memberCount && pItem->itemIndex + 1 == memberCount)
					{
						HPEN hPen = XDraw_CreatePen_(pItem->hDraw, PS_SOLID, 2, RGB(0, 162, 232));
						HGDIOBJ hOldPen = XDraw_SelectObject_(pItem->hDraw, hPen);

						XDraw_MoveToEx_(pItem->hDraw, pItem->rect.right + 2, pItem->rect.top);
						XDraw_LineTo_(pItem->hDraw, pItem->rect.right + 2, pItem->rect.bottom);

						XDraw_SelectObject_(pItem->hDraw, hOldPen);
						XDraw_DeleteObject_(pItem->hDraw, hPen);
					}
				}
			}
		}
	}
}

void ListView_DrawGroup(HELE hEle, listView_drawGroup_ *pGroup)
{
	listView_  *pListView = (listView_*)hEle;

	if (pListView->pDrawGroup)	//用户自绘
	{
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		if (pListView->pClass_Fun_Info_group)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)pGroup;
			event_.lParam = NULL;
			event_.pClass_fun = pListView->pClass_Fun_Info_group;
			((pFunClassEventMsg)pListView->pDrawGroup)(&event_, xc_fun_v_e_listView_group);
		}
		else
		{
			pListView->pDrawGroup(hEle, pGroup);
		}
#else
		pList->pDrawGroup(hEle, &pGroup);
#endif
	}
	else  //系统绘制
	{

		//绘制背景
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(pGroup->hDraw, RGB(200, 200, 200));
			XDraw_GradientFill2_(pGroup->hDraw, RGB(255, 255, 255), RGB(230, 230, 230), &pGroup->rect, 1);
			XDraw_FrameRect_(pGroup->hDraw, &pGroup->rect, hBrush);
			XDraw_DeleteObject_(pGroup->hDraw, hBrush);
		}

		//组展开按钮
		if (pListView->bExpandButton)
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(pGroup->hDraw, RGB(128, 128, 128));
			XDraw_GradientFill2_(pGroup->hDraw, RGB(255, 255, 255), RGB(200, 200, 200), &pGroup->rcButton, 1);
			XDraw_FrameRect_(pGroup->hDraw, &pGroup->rcButton, hBrush);

			XDraw_MoveToEx_(pGroup->hDraw, pGroup->rcButton.left + 2, pGroup->rcButton.top + (pGroup->rcButton.bottom - pGroup->rcButton.top) / 2, NULL);
			XDraw_LineTo_(pGroup->hDraw, pGroup->rcButton.right - 2, pGroup->rcButton.top + (pGroup->rcButton.bottom - pGroup->rcButton.top) / 2);
			if (!pGroup->bExpand)  //收缩
			{
				XDraw_MoveToEx_(pGroup->hDraw, pGroup->rcButton.left + (pGroup->rcButton.right - pGroup->rcButton.left) / 2, pGroup->rcButton.top + 2, NULL);
				XDraw_LineTo_(pGroup->hDraw, pGroup->rcButton.left + (pGroup->rcButton.right - pGroup->rcButton.left) / 2, pGroup->rcButton.bottom - 2);
			}
		}

		//组名
		if (pGroup->pText)
			XDraw_DrawText_(pGroup->hDraw, pGroup->pText, wcslen(pGroup->pText), &pGroup->rcText, DT_VCENTER | DT_SINGLELINE);
	}
}


BOOL CALLBACK ListView_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	listView_ *pListView = (listView_*)hEle;
	if (pListView->bDragItem && FALSE == pListView->bMultiSelect)//拖动项
	{
		//如果鼠标按下,并选中元素,那么拖动项
		//创建拖动项窗口
		//鼠标移动窗口 

		if (pListView->down && pListView->pCurrItem && NULL == pListView->hWndDrag)
		{

			if (pListView->dragPt.x > (pPt->x - 5) && pListView->dragPt.x < (pPt->x + 5))
			{
				if (pListView->dragPt.y > (pPt->y - 5) && pListView->dragPt.y < (pPt->y + 5))
				{
					return FALSE;
				}
			}

			pListView->down = FALSE;

			//创建拖动窗口
			POINT pt;
			GetCursorPos(&pt);
			int cx = pListView->pCurrItem->rect.right - pListView->pCurrItem->rect.left + 14;
			int cy = pListView->pCurrItem->rect.bottom - pListView->pCurrItem->rect.top + 14;
			int y = pt.y - cy / 2; //+20-cy;
			int x = pt.x - cx / 2; //-cx/2;
			HWND hWnd = XEle_GetHWnd(hEle);

			HWINDOW hWindow = XWnd_CreateWindowEx(WS_EX_TOOLWINDOW, NULL, L"dragItem", WS_POPUP, x, y, cx, cy, hWnd, 0);

			XWnd_SetUserData(hWindow, (int)hEle);
			XWnd_RegisterMessage(hWindow, WM_PAINT, ListView_OnDrawWindow_DragItem);

			XWnd_RegisterMessage(hWindow, WM_MOUSEMOVE, ListView_OnWndMouseMove_DragItem);
			XWnd_RegisterNCMessage(hWindow, XWM_NCMOUSEMOVE, ListView_OnWndMouseMove_DragItem);

			XWnd_RegisterMessage(hWindow, WM_LBUTTONUP, ListView_OnWndLButtonUp_DragItem);
			XWnd_RegisterNCMessage(hWindow, XWM_NCLBUTTONUP, ListView_OnWndLButtonUp_DragItem);

			XWnd_RegisterMessage(hWindow, WM_NCDESTROY, ListView_OnWndNCDestroy_DragItem);
			XWnd_ShowWindow(hWindow, SW_SHOW);

			XWnd_SetTransparentAlpha(hWindow, 128);
			XWnd_SetTransparentFlag(hWindow, XC_WIND_TRANSPARENT_SHADOW);//启动透明窗口,边框阴影

			pListView->hWndDrag = hWindow;

			//设置鼠标捕获
			SetCapture(XWnd_GetHWnd(hWindow));

			//	if(0!=SendMessage(XWnd_GetHWnd(hWindow),WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(0,0)))
			//	{
			//	XTRACE("SendMessage 失败 \n");
			//	}//else
			//	XTRACE("SendMessage 成功 \n");

			//	XWnd_CloseWindow(hWindow);

			return FALSE;
		}
		else if (pListView->hWndDrag)
		{
			pListView->down = FALSE;

			XWnd_CloseWindow(pListView->hWndDrag);
			//pListView->hWndDrag=NULL;
			XTRACE("if(pListView->hWndDrag) \n");
			return FALSE;
		}
	}
	if (FALSE == ((listView_*)hEle)->bDrag)
	{
		ListView_MouseMoveDragBegin(hEle, pPt);

		//鼠标停留项
		listView_item_ *pItem = ListView_CheckDownItem(hEle, pPt);
		if (pItem)
		{
			if (pItem == pListView->pCurrItemStay)
			{
				return FALSE;
			}

			if (STATE_SELECT == pItem->state)
			{
				if (pListView->pCurrItemStay)
				{
					if (pListView->pCurrItemStay != pItem)
					{
						pListView->pCurrItemStay->state = STATE_LEAVE;
					}
				}

				pListView->pCurrItemStay = pItem;
				XEle_RedrawEle(hEle);
				return FALSE;
			}

			if (pListView->pCurrItemStay)
			{
				if (STATE_SELECT != pListView->pCurrItemStay->state)
					pListView->pCurrItemStay->state = STATE_LEAVE;
			}

			pListView->pCurrItemStay = pItem;
			pListView->pCurrItemStay->state = STATE_STAY;

			XEle_RedrawEle(hEle);
		}
		else
		{
			if (pListView->pCurrItemStay)
			{
				if (STATE_SELECT != pListView->pCurrItemStay->state)
					pListView->pCurrItemStay->state = STATE_LEAVE;

				pListView->pCurrItemStay = NULL;

				XEle_RedrawEle(hEle);
			}
		}
	}
	else
	{
		ListView_MouseMoveDrag(hEle, pPt);
	}
	return FALSE;
}

void ListView_MouseMoveDragBegin(HELE hEle, POINT *pPt) //准备拖动选择
{
	listView_ *pListView = (listView_*)hEle;
	if (FALSE == pListView->bMultiSelect)
		return;
	if (pListView->down)
	{
		if (pPt->x<(pListView->dragPt.x - 5) || pPt->x>(pListView->dragPt.x + 5)
			|| pPt->y<(pListView->dragPt.y - 5) || pPt->y>(pListView->dragPt.y + 5))
		{
			pListView->bDrag = TRUE;

			pListView->dragPt.x = pListView->dragPt.x - XSView_GetHViewPos(hEle);
			pListView->dragPt.y = pListView->dragPt.y - XSView_GetVViewPos(hEle);
			pListView->dragEndPt.x = pPt->x - XSView_GetHViewPos(hEle);
			pListView->dragEndPt.y = pPt->y - XSView_GetVViewPos(hEle);

			g_hListView = hEle;
			SetTimer(XEle_GetHWnd(hEle), IDT_LISTVIEW_DRAG_RECT, 50, ListView_TimerProc);
			XEle_SetCapture(hEle);
		}
	}
}


void ListView_MouseMoveDrag(HELE hEle, POINT *pPt) //拖动选择
{
	listView_ *pListView = (listView_*)hEle;
	pListView->dragEndPt.x = pPt->x - XSView_GetHViewPos(hEle);
	pListView->dragEndPt.y = pPt->y - XSView_GetVViewPos(hEle);

	//拖动矩形--------------------
	RECT rcDrag;
	if (pListView->dragEndPt.x > pListView->dragPt.x)
	{
		rcDrag.left = pListView->dragPt.x;
		rcDrag.right = pListView->dragEndPt.x;
	}
	else
	{
		rcDrag.left = pListView->dragEndPt.x;
		rcDrag.right = pListView->dragPt.x;
	}
	if (pListView->dragEndPt.y > pListView->dragPt.y)
	{
		rcDrag.top = pListView->dragPt.y;
		rcDrag.bottom = pListView->dragEndPt.y;
	}
	else
	{
		rcDrag.top = pListView->dragEndPt.y;
		rcDrag.bottom = pListView->dragPt.y;
	}

	//计算哪些项在拖动区域
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (XC_RectInRect(&pItem->rect, &rcDrag))
				{
					pItem->state = STATE_SELECT;
				}
				else
				{
					pItem->state = STATE_LEAVE;
				}
			}
		}
	}

	int countItem = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < countItem; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (XC_RectInRect(&pItem->rect, &rcDrag))
		{
			pItem->state = STATE_SELECT;
		}
		else
		{
			pItem->state = STATE_LEAVE;
		}
	}
}

BOOL CALLBACK ListView_OnEleLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	listView_ *pListView = (listView_*)hEle;

	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (FALSE == PtInRect(&rect, *pPt))
		return FALSE;

	listView_group_ *pGroup = ListView_CheckDownGroup(hEle, pPt);
	if (pGroup)
	{
		if (pGroup->bExpand)
		{
			pGroup->bExpand = FALSE;
		}
		else
		{
			pGroup->bExpand = TRUE;
		}
		XListView_Adjust(hEle);
		Ele_SendEvent(hEle, XE_LISTVIEW_EXPAND, pGroup->index, pGroup->bExpand);
		if (!XC_IsHELE(hEle)) return FALSE;
		XEle_RedrawEle(hEle);
		return FALSE;
	}

	pListView->down = TRUE;
	pListView->dragPt = *pPt;

	listView_item_ *pItem = ListView_CheckDownItem(hEle, pPt);
	//单项选择//////////////////////////////////////////////////////
	if (FALSE == pListView->bMultiSelect)
	{
		if (0x8000 & GetKeyState(VK_CONTROL)) //ctrl 按下状态
			return FALSE;
		if (0x8000 & GetKeyState(VK_SHIFT)) //shift 按下状态
			return FALSE;

		if (pItem)
		{
			if (pItem != pListView->pCurrItem)
			{
				if (pListView->pCurrItem)
					pListView->pCurrItem->state = STATE_LEAVE;
				pListView->pCurrItem = pItem;
				pListView->pCurrItem->state = STATE_SELECT;
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
				if (!XC_IsHELE(hEle)) return FALSE;
				XEle_RedrawEle(hEle);
			}
		}
		else
		{
			if (pListView->pCurrItem)
			{
				pListView->pCurrItem->state = STATE_LEAVE;
				pListView->pCurrItem = NULL;
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
				if (!XC_IsHELE(hEle)) return FALSE;
				XEle_RedrawEle(hEle);
			}
		}
		return FALSE;
	}

	//多选选择////////////////////////////////////////////////////////////
	if (0x8000 & GetKeyState(VK_CONTROL) && pItem) //ctrl 按下状态
	{
		if (STATE_SELECT != pItem->state)
		{
			pItem->state = STATE_SELECT;
			pListView->pCurrItem = pItem;
			XArray_Add(pListView->hArrayCurrItem, pItem);
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
		}
		else
		{
			if (pListView->pCurrItem == pItem)
			{
				pItem->state = 0;
				XArray_Delete(pListView->hArrayCurrItem, pItem);

				if (Array_GetCount(pListView->hArrayCurrItem) > 0)
				{
					pListView->pCurrItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, Array_GetCount(pListView->hArrayCurrItem) - 1);
				}
				else
					pListView->pCurrItem = NULL;
			}
			else
			{
				pItem->state = STATE_LEAVE;
				XArray_Delete(pListView->hArrayCurrItem, pItem);
			}

			if (pListView->pCurrItem)
			{
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
			}
			else
			{
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
			}
		}
		if (!XC_IsHELE(hEle)) return FALSE;
		XEle_RedrawEle(hEle);

	}
	else if (0x8000 & GetKeyState(VK_SHIFT) && pItem) //shift 按下状态
	{
		ListView_ShiftDown(hEle, pItem);
	}
	else if (pItem)
	{
		BOOL bDraw = FALSE;
		if (STATE_SELECT == pItem->state)
			bDraw = FALSE;
		else
			bDraw = TRUE;

		int count = Array_GetCount(pListView->hArrayCurrItem);
		for (int i = 0; i < count; i++)
		{
			((listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
		}
		XArray_DeleteAll(pListView->hArrayCurrItem);

		pListView->pCurrItem = pItem;
		XArray_Add(pListView->hArrayCurrItem, pItem);

		Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
		if (bDraw || count > 0)
		{
			pItem->state = STATE_SELECT;
			XEle_RedrawEle(hEle);
		}
	}
	else  //空白区域
	{
		pListView->pCurrItem = NULL;
		int count = Array_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				((listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
			}
			XArray_DeleteAll(pListView->hArrayCurrItem);
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
			if (!XC_IsHELE(hEle)) return FALSE;
			XEle_RedrawEle(hEle);
		}
	}

	return FALSE;
}

BOOL CALLBACK ListView_OnEleLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	listView_ *pListView = (listView_*)hEle;

	if (pListView->down)
		pListView->down = FALSE;

	if (pListView->bDrag)
	{
		XArray_DeleteAll(pListView->hArrayCurrItem);
		pListView->pCurrItem = NULL;

		pListView->bDrag = FALSE;
		KillTimer(XEle_GetHWnd(hEle), IDT_LISTVIEW_DRAG_RECT);
		XEle_ReleaseCapture(hEle);
		XEle_RedrawEle(hEle);

		int countGroup = XArray_GetCount(pListView->hArrayGroupList);
		for (int g = 0; g < countGroup; g++)
		{
			listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (STATE_SELECT == pItem->state)
				{
					//add
					XArray_Add(pListView->hArrayCurrItem, pItem);
				}
			}
		}

		int countItem = XArray_GetCount(pListView->hArrayList);
		for (int i = 0; i < countItem; i++)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
			if (STATE_SELECT == pItem->state)
			{
				//add
				XArray_Add(pListView->hArrayCurrItem, pItem);
			}
		}

		int count = XArray_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
		{
			pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
		}

		if (pListView->pCurrItem)
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pListView->pCurrItem->groupIndex, pListView->pCurrItem->index);
		else
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK ListView_OnEventKillFocus(HELE hEle, HELE hEventEle) //失去焦点
{
	if (hEle == hEventEle)
	{
		listView_ *pListView = (listView_*)hEle;
		if (pListView->bDrag)
		{
			((listView_*)hEle)->bDrag = FALSE;
		}

		if (pListView->pCurrItemStay)
		{
			if (STATE_SELECT != pListView->pCurrItemStay->state)
				pListView->pCurrItemStay->state = STATE_LEAVE;

			pListView->pCurrItemStay = NULL;

			XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK ListView_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	listView_ *pListView = (listView_*)hEle;
	if (pListView->pCurrItemStay)
	{
		if (STATE_SELECT != pListView->pCurrItemStay->state)
			pListView->pCurrItemStay->state = STATE_LEAVE;

		pListView->pCurrItemStay = NULL;

		XEle_RedrawEle(hEle);
	}
	return FALSE;
}

listView_group_ *ListView_CheckDownGroup(HELE hEle, POINT *pPt) //检查鼠标所按组
{
	listView_ *pListView = (listView_*)hEle;

	POINT  pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);

	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		if (PtInRect(&pGroup->rcButton, pt)) //组啊展开收缩
		{
			return pGroup;
		}
	}
	return NULL;
}

listView_item_ *ListView_CheckDownItem(HELE hEle, POINT *pPt)  //检查鼠标所按项
{
	listView_ *pListView = (listView_*)hEle;

	POINT  pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);

	//组
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		/*	if(PtInRect(&pGroup->rcButton,pt)) //组啊展开收缩
		{
		if(pGroup->bExpand)
		{
		pGroup->bExpand=FALSE;
		}else
		{
		pGroup->bExpand=TRUE;
		}
		ListView_Adjust(hEle);
		XEle_RedrawEle(hEle);
		return (listView_item_*)1;
		}*/
		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (PtInRect(&pItem->rect, pt)) //选择项
				{
					return pItem;
				}
			}
		}
	}

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (PtInRect(&pItem->rect, pt))
		{
			return pItem;
		}
	}
	return NULL;
}

void ListView_ShiftDown(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	int count = Array_GetCount(pListView->hArrayCurrItem);
	if (0 == count)
	{
		pItem->state = STATE_SELECT;
		XArray_Add(pListView->hArrayCurrItem, pItem);
		pListView->pCurrItem = pItem;
		Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
		if (!XC_IsHELE(hEle)) return;
		XEle_RedrawEle(hEle);
	}
	else if (pListView->pCurrItem)
	{
		int count = XArray_GetCount(pListView->hArrayCurrItem);
		for (int i = 0; i < count; i++)
		{
			((listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
		}
		XArray_DeleteAll(pListView->hArrayCurrItem);
		pListView->pCurrItem->state = STATE_SELECT;
		XArray_Add(pListView->hArrayCurrItem, pListView->pCurrItem);

		if (pItem->groupIndex == pListView->pCurrItem->groupIndex)//选择项在同一个组
		{
			int begin = 0, end = 0;
			if (pListView->pCurrItem->index < pItem->index)
			{
				begin = pListView->pCurrItem->index;
				end = pItem->index;
			}
			else
			{
				begin = pItem->index;
				end = pListView->pCurrItem->index;
			}
			if ((end - begin) > 0)
			{
				HARRAY hArray = NULL;
				if (-1 == pItem->groupIndex) //没有组
					hArray = pListView->hArrayList;
				else
				{
					listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
					hArray = pGroup->hArrayList;
				}

				int countItem = Array_GetCount(hArray);
				for (int i = begin; i <= end; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pListView->pCurrItem->groupIndex, pListView->pCurrItem->index);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
		else  //选择项在不同组
		{
			if (-1 == pListView->pCurrItem->groupIndex)
			{
				ListView_ShiftDown1(hEle, pItem);
			}
			else if (-1 == pItem->groupIndex)
			{
				ListView_ShiftDown2(hEle, pItem);
			}
			else if (pListView->pCurrItem->groupIndex < pItem->groupIndex)
			{
				ListView_ShiftDown3(hEle, pItem);
			}
			else if (pListView->pCurrItem->groupIndex > pItem->groupIndex)
			{
				ListView_ShiftDown4(hEle, pItem);
			}
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pListView->pCurrItem->groupIndex, pListView->pCurrItem->index);
		}
	}
}

void ListView_ShiftDown1(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;

	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pItem->index; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pItem->groupIndex + 1; i < groupCount; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	hArray = pListView->hArrayList;
	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i <= pListView->pCurrItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

void ListView_ShiftDown2(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pListView->pCurrItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pListView->pCurrItem->index + 1; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pListView->pCurrItem->groupIndex + 1; i < groupCount; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	hArray = pListView->hArrayList;
	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i <= pItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

void ListView_ShiftDown3(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pListView->pCurrItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pListView->pCurrItem->index + 1; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pListView->pCurrItem->groupIndex + 1; i < pItem->groupIndex; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
	hArray = pGroup->hArrayList;

	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i <= pItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

void ListView_ShiftDown4(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pListView->pCurrItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i < pListView->pCurrItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pItem->groupIndex + 1; i < pListView->pCurrItem->groupIndex; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
	hArray = pGroup->hArrayList;

	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pItem->index; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

///@}


HELE  g_hListView = NULL;
VOID CALLBACK ListView_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (IDT_LISTVIEW_DRAG_RECT == idEvent)
	{
		XEle_RedrawEle(g_hListView);
	}
}

BOOL CALLBACK ListView_OnDrawWindow_DragItem(HWINDOW hWindow, HDRAW hDraw)
{
	listView_ *pListView = (listView_*)XWnd_GetUserData(hWindow);

	listView_item_ *pItem = pListView->pCurrItem;
	RECT rcIcon = pItem->rcIcon;

	RECT rc = pItem->rect;
	RECT rcIconDraw = pItem->rcIconDraw;
	RECT rcText = pItem->rcText;

	int cx = rcIconDraw.right - rcIconDraw.left;
	int cy = rcIconDraw.bottom - rcIconDraw.top;
	rcIconDraw.left = rcIconDraw.left - rc.left;
	rcIconDraw.top = rcIconDraw.top - rc.top;
	rcIconDraw.right = rcIconDraw.left + cx;
	rcIconDraw.bottom = rcIconDraw.top + cy;

	cx = rcText.right - rcText.left;
	cy = rcText.bottom - rcText.top;
	rcText.left = rcText.left - rc.left;
	rcText.top = rcText.top - rc.top;
	rcText.right = rcText.left + cx;
	rcText.bottom = rcText.top + cy;

	if (pListView->hImageList)
		XImageList_DrawImage2(pListView->hImageList, hDraw, pItem->imageID, &rcIconDraw);

	if (pItem->hString)
	{
		wchar_t *pText = XStr_GetBuffer(pItem->hString);
		if (pText)
			XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_CENTER);
	}
	return TRUE;
}

//鼠标移动
BOOL CALLBACK ListView_OnWndMouseMove_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	POINT pt;
	GetCursorPos(&pt);

	RECT rect;
	XWnd_GetWindowRect(hWindow, &rect);

	int x = pt.x - (rect.right - rect.left) / 2;
	int y = pt.y - (rect.bottom - rect.top) / 2;

	XWnd_SetWindowPos(hWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	////////////////////////////////////////////////////////////////////
	listView_ *pListView = (listView_*)XWnd_GetUserData(hWindow);
	HELE hListView = (HELE)pListView;

	//转换到窗口坐标
	ScreenToClient(XEle_GetHWnd(hListView), &pt);

	//转换到listView坐标
	XEle_PointNCWndToEle(hListView, &pt);

	RECT rcListView;
	XEle_GetClientRect(hListView, &rcListView);

	if (PtInRect(&rcListView, pt)) //在列表视图内
	{
		int groupIndex = -1;
		int itemIndex = -1;
		XListView_HitTest(hListView, &pt, &groupIndex, &itemIndex);
		listView_item_ *pHitItem = ListView_GetItem_XC(hListView, groupIndex, itemIndex);
		if (pHitItem)
		{
			if (pt.x > (pHitItem->rect.left + (pHitItem->rect.right - pHitItem->rect.left) / 2))
			{
				itemIndex++;
				//	XTRACE("右 \n");
			}
			else
			{
				//	XTRACE("左 \n");
			}
		}

		if (groupIndex != pListView->insertGroup || itemIndex != pListView->insertItem)
		{
			//XTRACE("XEle_RedrawEle(hListView) \n");
			pListView->insertGroup = groupIndex;
			pListView->insertItem = itemIndex;
			XEle_RedrawEle(hListView);
		}

	}
	else //在列表视图外
	{
		pListView->insertGroup = -1;
		pListView->insertItem = -1;
		if (pt.y > (rcListView.bottom - 10)) //向下滚动
		{
			XSView_ScrollDownLine(hListView);
		}
		else if (pt.y < 10)
		{
			XSView_ScrollTopLine(hListView);
		}
	}

	return FALSE;
}

BOOL CALLBACK ListView_OnWndLButtonUp_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	XWnd_CloseWindow(hWindow);
	return TRUE;
}

BOOL CALLBACK ListView_OnWndNCDestroy_DragItem(HWINDOW hWindow)
{
	//XTRACE("ListView_OnWndNCDestroy_DragItem() \n");
	listView_ *pListView = (listView_*)XWnd_GetUserData(hWindow);
	pListView->hWndDrag = NULL;

	if (pListView->insertGroup == pListView->pCurrItem->groupIndex && pListView->insertItem == pListView->pCurrItem->index)
	{
		XEle_RedrawEle((HELE)pListView);
		return FALSE;
	}

	if (-1 == pListView->insertItem || NULL == pListView->pCurrItem)
	{
		XEle_RedrawEle((HELE)pListView);
		return FALSE;
	}

	listView_item_ *pItem = pListView->pCurrItem;
	listView_dragInsert_  info;
	info.groupIndex = pItem->groupIndex;
	info.itemIndex = pItem->index;

	if (-1 == pItem->groupIndex)
	{
		XArray_DeleteIndex(pListView->hArrayList, pItem->index);
	}
	else
	{
		listView_group_ *pGroup = ListView_GetGroup_XC((HELE)pListView, pItem->groupIndex);
		XArray_DeleteIndex(pGroup->hArrayList, pItem->index);
	}

	if (-1 == pListView->insertGroup) //没有分组
	{
		if (-1 != pItem->groupIndex) //有分组
		{
			XArray_insert(pListView->hArrayList, pItem, pListView->insertItem);
		}
		else //没分组
		{
			if (pListView->insertItem < pItem->index)
			{
				XArray_insert(pListView->hArrayList, pItem, pListView->insertItem);
			}
			else
			{
				XArray_insert(pListView->hArrayList, pItem, pListView->insertItem - 1);
			}
		}
	}
	else //有分组
	{

		if (pListView->insertGroup == pItem->groupIndex) //在同一个分组
		{
			listView_group_ *pGroup = ListView_GetGroup_XC((HELE)pListView, pItem->groupIndex);
			if (pListView->insertItem < pItem->index)
			{
				XArray_insert(pGroup->hArrayList, pItem, pListView->insertItem);
			}
			else
			{
				XArray_insert(pGroup->hArrayList, pItem, pListView->insertItem - 1);
			}
		}
		else //不同分组
		{
			listView_group_ *pGroup = ListView_GetGroup_XC((HELE)pListView, pListView->insertGroup);

			XArray_insert(pGroup->hArrayList, pItem, pListView->insertItem);

		}
	}

	XListView_Adjust((HELE)pListView);

	info.groupIndex_new = pItem->groupIndex;
	info.itemIndex_new = pItem->index;

	info.groupIndex_insert = pListView->insertGroup;
	info.itemIndex_insert = pListView->insertItem;

	pListView->insertGroup = -1;
	pListView->insertItem = -1;

	//发送事件
	Ele_SendEvent((HELE)pListView, XE_LISTVIEW_DRAG_INSERT, (WPARAM)&info, 0);
	if (!XC_IsHELE((HELE)pListView)) return FALSE;
	XEle_RedrawEle((HELE)pListView);
	return FALSE;
}
