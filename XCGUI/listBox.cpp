/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup listBox 列表框(ListBox)
/// @ingroup groupElements
/// @{

/// @brief 创建列表框元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XListBox_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	listBox_ *pObj = (listBox_*)malloc(sizeof(listBox_));
	memset(pObj, 0, sizeof(listBox_));

	ListBox_Init((HELE)pObj, x, y, cx, cy, XC_LISTBOX, hParent);
	return (HELE)pObj;
}

void ListBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_LISTBOX);
	listBox_ *pListBox = LISTBOX(hEle);
	pListBox->height = 20;
	pListBox->curSel = -1;
	pListBox->hImageList = NULL;
	pListBox->bAdjust = FALSE;
	pListBox->hArrayListItem = XArray_Create();
	pListBox->bLineHighlight = TRUE;
	pListBox->mouseStayId = -1;
	pListBox->selectItemColor = RGB(126, 206, 244);
	pListBox->mouseStayColor = RGB(192, 232, 250);

	XSView_SetDrawScrollView(hEle, ListBox_OnDrawScrollView);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, ListBox_OnLButtonDown);
	XEle_RegisterEvent(hEle, XE_DESTROY, ListBox_OnDestroy);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, ListBox_OnEleMouseMove);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, ListBox_OnEventMouseLeave);
}

void CALLBACK ListBox_OnDestroy(HELE hEle)  //销毁
{
	listBox_item_ *pItem = NULL;
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	for (int i = 0; i < count; i++)
	{
		pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, i);
		XStr_Destroy(pItem->hString);

		if (pItem->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pItem->hArrayBindEle);
			for (int j = 0; j < bindEleCount; j++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, j);
				free(pBindEle);
			}
			XArray_Destroy(pItem->hArrayBindEle);
		}

		free(pItem);
	}
	XArray_Destroy(LISTBOX(hEle)->hArrayListItem);

	if (LISTBOX(hEle)->hImageList)
		XImageList_Destroy(LISTBOX(hEle)->hImageList);

#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	if (LISTBOX(hEle)->pClass_Fun_Info)
		free(LISTBOX(hEle)->pClass_Fun_Info);
#endif
}

/// @brief 添加一个字符串到列表.
/// @param hEle   元素句柄.
/// @param pText  文本内容.
/// @param imageId  项图标ID.
/// @return 项索引位置.
int WINAPI XListBox_AddString(HELE hEle, wchar_t *pText, int imageId)  //增加一个字符串到列表
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);

	if (NULL == pText) return -1;

	int len = wcslen(pText);
	//	if(len<1) return -1;

	if (len > 0)
	{
		HDC hdc;
		SIZE size;
		hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
		GetTextExtentPoint32(hdc, pText, len, &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

		if (size.cx > pObj->maxTextWidth)
			pObj->maxTextWidth = size.cx;
	}

	listBox_item_ *pItem = (listBox_item_*)malloc(sizeof(listBox_item_));
	memset(pItem, 0, sizeof(listBox_item_));
	pItem->hString = XStr_Create();
	XStr_SetString(pItem->hString, pText);
	pItem->imageID = imageId;

	XArray_Add(pObj->hArrayListItem, pItem);

	pObj->bAdjust = TRUE;
	return XArray_GetCount(pObj->hArrayListItem) - 1;
}

/// @brief 插入一个字符串到列表.
/// @param hEle   元素句柄.
/// @param index  插入位置索引.
/// @param pText  文本内容.
/// @param imageId  项图标ID.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListBox_InsertString(HELE hEle, int index, wchar_t *pText, int imageId)
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);

	if (NULL == pText) return FALSE;

	int len = wcslen(pText);
	if (len < 1) return FALSE;

	if (index < 0)
		return FALSE;

	if (index > XArray_GetCount(pObj->hArrayListItem))
		return FALSE;

	HDC hdc;
	SIZE size;
	hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
	GetTextExtentPoint32(hdc, pText, len, &size);
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (size.cx > pObj->maxTextWidth)
		pObj->maxTextWidth = size.cx;

	listBox_item_ *pItem = (listBox_item_*)malloc(sizeof(listBox_item_));
	memset(pItem, 0, sizeof(listBox_item_));
	pItem->hString = XStr_Create();
	XStr_SetString(pItem->hString, pText);
	pItem->imageID = imageId;

	XArray_insert(pObj->hArrayListItem, pItem, index);

	pObj->bAdjust = TRUE;
	return TRUE;;
}

/// @brief 调整布局.
/// @param hEle   元素句柄.
void WINAPI XListBox_Adjust(HELE hEle)
{
	IsListBoxDebug(hEle, __FUNCTION__);

	listBox_ *pObj = LISTBOX(hEle);

	pObj->bAdjust = FALSE;
	int count = Array_GetCount(pObj->hArrayListItem);

	int left = XSView_GetSpacingLeft(hEle) + 1 + XLISTBOX_LEFT;
	if (pObj->bCheck)
	{
		left += XLISTBOX_CHECK_SIZE;
		left += 3;
	}

	if (pObj->hImageList)
	{
		left += XImageList_GetWidth(pObj->hImageList);
		left += 3;
	}

	int right = XSView_GetSpacingRight(hEle) + 1 + XLISTBOX_RIGHT;
	XSView_SetSize(hEle, pObj->maxTextWidth + left + right, count*pObj->height);

	int posx = XSView_GetHViewPos(hEle);
	int posy = XSView_GetVViewPos(hEle);

	//绑定的元素
	for (int i = 0; i < count; i++)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, i);
		if (pItem->hArrayBindEle)
		{
			int bandEleCount = XArray_GetCount(pItem->hArrayBindEle);
			for (int j = 0; j < bandEleCount; j++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, j);
				((ele_*)pBindEle->hEle)->rect.left = pBindEle->left + posx;
				((ele_*)pBindEle->hEle)->rect.top = i*pObj->height + pBindEle->top + posy;
				((ele_*)pBindEle->hEle)->rect.right = ((ele_*)pBindEle->hEle)->rect.left + pBindEle->width;
				((ele_*)pBindEle->hEle)->rect.bottom = ((ele_*)pBindEle->hEle)->rect.top + pBindEle->height;
				((ele_*)pBindEle->hEle)->elePt.x = pBindEle->left;
				((ele_*)pBindEle->hEle)->elePt.y = i*pObj->height + pBindEle->top;
			}
		}
	}

}

/// @brief 设置用户自绘列表框项.
/// @param hEle   元素句柄.
/// @param pFunDrawItem 自绘函数名,格式如下:
/// @code void CALLBACK ListBox_DrawItem(HELE hEle,listBox_drawItem_ *pDrawItem); @endcode
void WINAPI XListBox_SetUserDrawItem(HELE hEle, pFunListBox_DrawItem pFunDrawItem) //设置用户自绘列表项
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	LISTBOX(hEle)->pClass_Fun_Info = NULL;
#endif
}

#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
void WINAPI XListBox_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //设置用户自绘列表框项
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->pDrawItem = (pFunListBox_DrawItem)pCallBackFun;
	LISTBOX(hEle)->pClass_Fun_Info = pClass_Fun_Info;
}
#endif

/// @brief 启用或关闭复选框功能.
/// @param hEle   元素句柄.
/// @param bEnable 值为TRUE启用,否则相反.
void WINAPI XListBox_EnableCheckBox(HELE hEle, BOOL bEnable) //启用复选框
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->bCheck = bEnable;
	LISTBOX(hEle)->bAdjust = TRUE;
}

/// @brief 启用或关闭行高亮显示.
/// @param hEle   元素句柄.
/// @param bEnable 值为TRUE启用,否则相反.
void WINAPI XLsitBox_EnableLineHighlight(HELE hEle, BOOL bEnable)  //启用或关闭行高亮显示
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->bLineHighlight = bEnable;
}

/// @brief 判断列表框项复选框是否选中.
/// @param hEle   元素句柄.
/// @param index  列表项索引.
/// @return 如果复选框选中为TRUE,否则相反.
BOOL WINAPI XListBox_IsItemCheck(HELE hEle, int index)      //判断项的复选框是否勾选
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		return pItem->bCheck;
	}
	else
	{
		XERROR("XListBox_IsItemCheck(),参数[index]错误\n");
	}
	return FALSE;
}

/// @brief 设置列表框项的复选框.
/// @param hEle   元素句柄.
/// @param index  列表项索引.
/// @param bCheck 值为TRUE复选框选中,否则相反.
void WINAPI XListBox_SetItemCheck(HELE hEle, int index, BOOL bCheck) //设置项的复选框
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		pItem->bCheck = bCheck;
	}
	else
	{
		XERROR("XListBox_SetItemCheck(),参数[index]错误\n");
	}
}

/// @brief 设置项绑定元素.
/// @param hEle   元素句柄.
/// @param index    项索引.
/// @param pInfo    绑定元素信息
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XListBox_SetItemBindEle(HELE hEle, int index, itemBindEle_ *pInfo) //绑定元素
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		if (NULL == pItem) return FALSE;

		if (NULL == XEle_GetParentEle(pInfo->hEle))
			XSView_AddEle(hEle, pInfo->hEle);

		itemBindEle_ *pBindEle = (itemBindEle_*)malloc(sizeof(itemBindEle_));
		pBindEle->hEle = pInfo->hEle;
		pBindEle->left = pInfo->left;
		pBindEle->top = pInfo->top;
		pBindEle->width = pInfo->width;
		pBindEle->height = pInfo->height;

		if (NULL == pItem->hArrayBindEle)
			pItem->hArrayBindEle = XArray_Create();

		XArray_Add(pItem->hArrayBindEle, pBindEle);
		return TRUE;
	}
	else
	{
		XERROR("XListBox_SetItemCheck(),参数[index]错误\n");
	}
	return FALSE;
}

/// @brief 获取行高.
/// @param hEle   元素句柄.
/// @return 行高.
int WINAPI XListBox_GetItemHeight(HELE hEle) //获取行高
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return  LISTBOX(hEle)->height;
}

/// @brief 获取选择行.
/// @param hEle   元素句柄.
/// @return 选择项索引,如果返回-1没有选择项.
int WINAPI XListBox_GetSelectItem(HELE hEle) //获取选择行
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return LISTBOX(hEle)->curSel;
}

/// @brief 获取指定行文本.
/// @param hEle   元素句柄.
/// @param index 指定行索引.
/// @return 文本内容.
wchar_t* WINAPI XListBox_GetItemText(HELE hEle, int index) //获取指定行文本
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (count > 0)
	{
		if (index >= 0 && index < count)
		{
			listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
			if (pItem)
			{
				return XStr_GetBuffer(pItem->hString);
			}
		}
	}
	return NULL;
}

/// @brief 设置指定行文本.
/// @param hEle   元素句柄.
/// @param index  指定行索引.
/// @param pText 文本内容.
void WINAPI XListBox_SetItemText(HELE hEle, int index, wchar_t *pText) //设置指定行文本
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);
	int count = Array_GetCount(pObj->hArrayListItem);
	if (index >= 0 && index < count)
	{
		int len = wcslen(pText);
		if (len < 1) return;

		HDC hdc;
		SIZE size;
		hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
		GetTextExtentPoint32(hdc, pText, len, &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

		if (size.cx > pObj->maxTextWidth)
			pObj->maxTextWidth = size.cx;

		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, index);
		XStr_SetString(pItem->hString, pText);

		XSView_SetSize(hEle, pObj->maxTextWidth, count*pObj->height);
	}
}

/// @brief 设置选择项.
/// @param hEle   元素句柄.
/// @param index  选择项索引,如果index为-1那么不选择任何项.
void WINAPI XListBox_SetSelectItem(HELE hEle, int index) //设置选择项
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		LISTBOX(hEle)->curSel = index;
	}
	else if (-1 == index)
	{
		LISTBOX(hEle)->curSel = -1;
	}
}

/// @brief 设置行高.
/// @param hEle   元素句柄.
/// @param height  行高.
void WINAPI XListBox_SetItemHeight(HELE hEle, int height) //设置行高
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->height = height;
}

/// @brief 删除行.
/// @param hEle   元素句柄.
/// @param index  行索引.
void WINAPI XListBox_DeleteItem(HELE hEle, int index)  //删除行
{
	IsListBoxDebug(hEle, __FUNCTION__);
	if (index < 0) return;
	int count = Array_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		XStr_Destroy(pItem->hString);

		if (pItem->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pItem->hArrayBindEle);
			for (int i = 0; i < bindEleCount; i++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, i);
				if (pBindEle->hEle)
					XEle_Destroy(pBindEle->hEle);
				free(pBindEle);
			}
			XArray_Destroy(pItem->hArrayBindEle);
		}

		free(pItem);

		XArray_DeleteIndex(LISTBOX(hEle)->hArrayListItem, index);
	}
}

/// @brief 删除所有行.
/// @param hEle  元素句柄.
void WINAPI XListBox_DeleteAll(HELE hEle) //删除所有行
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);
	int count = Array_GetCount(pObj->hArrayListItem);
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, i);
			XStr_Destroy(pItem->hString);

			if (pItem->hArrayBindEle)
			{
				int bindEleCount = XArray_GetCount(pItem->hArrayBindEle);
				for (int j = 0; j < bindEleCount; j++)
				{
					itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, j);
					if (pBindEle->hEle)
						XEle_Destroy(pBindEle->hEle);
					free(pBindEle);
				}
				XArray_Destroy(pItem->hArrayBindEle);
			}

			free(pItem);
		}
		XArray_DeleteAll(LISTBOX(hEle)->hArrayListItem);
	}
}

/// @brief 设置列表框元素关联图片列表.
/// @param hEle  元素句柄.
/// @param hImageList  图片列表元素句柄.
void WINAPI XListBox_SetImageList(HELE hEle, HXCGUI hImageList) //设置图标列表
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);
	if (pObj->hImageList)
	{
		XImageList_Destroy(pObj->hImageList);
		pObj->hImageList = NULL;
	}
	if (hImageList)
	{
		IsImageListDebug(hImageList, __FUNCTION__);
		pObj->hImageList = ImageList_AddRef(hImageList);
	}
}

/// @brief 设置项图标.
/// @param hEle  元素句柄.
/// @param index  项索引.
/// @param imageId 图标ID.
void WINAPI XListBox_SetItemImage(HELE hEle, int index, int imageId) //设置项图标
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		pItem->imageID = imageId;
	}
}

/// @brief 获取项图标ID.
/// @param hEle  元素句柄.
/// @param index  项索引.
/// @return 图标ID.
int WINAPI XListBox_GetItemImage(HELE hEle, int index) //获取项图标
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		return pItem->imageID;
	}
	return -1;
}

/// @brief 获取项数量.
/// @param hEle  元素句柄.
/// @return 项数量.
int WINAPI XListBox_GetItemCount(HELE hEle) //获取项数量
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
}

/// @brief 获取图片列表.
/// @param hEle  元素句柄.
/// @return 图片列表句柄.
HXCGUI WINAPI XListBox_GetImageList(HELE hEle) //获取图片列表
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return LISTBOX(hEle)->hImageList;
}

/// @brief 获取项可视区域坐标.
/// @param hEle  元素句柄.
/// @param index  项索引.
/// @param pRect  接收返回坐标.
/// @return 如果项不可见返回FALSE,否则相反..
BOOL WINAPI XListBox_GetItemRect(HELE hEle, in_ int index, out_ RECT *pRect)  //获取项坐标...
{
	if (index > -1 && index < Array_GetCount(LISTBOX(hEle)->hArrayListItem))
	{
		int y = index*LISTBOX(hEle)->height;
		y = y - XSView_GetVViewPos(hEle);
		y = y + XSView_GetSpacingTop(hEle);

		RECT rcView;
		XSView_GetViewRect(hEle, &rcView);

		pRect->left = rcView.left;
		pRect->right = rcView.right;
		pRect->top = y;
		pRect->bottom = y + LISTBOX(hEle)->height;

		if (pRect->top >= rcView.bottom)
		{
			pRect->top = rcView.bottom;
			pRect->bottom = rcView.bottom;
			return FALSE;
		}
		else if (pRect->bottom > rcView.bottom)
		{
			pRect->bottom = rcView.bottom;
		}
		return TRUE;
	}
	return FALSE;
}

/// @brief 测试鼠标在哪个项上,如果没有在任何项上返回-1.
/// @param hEle 元素句柄
/// @param pPt  坐标点.
/// @return 鼠标所在项索引,如果没有在任何项上返回-1.
int  WINAPI XListBox_HitTest(HELE hEle, POINT *pPt)  //测试鼠标点在哪个项上,-1没有在任何项上
{
	IsListBoxDebug(hEle, __FUNCTION__);
	POINT pt = *pPt;
	int pos = -1;

	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (PtInRect(&rect, pt))
	{
		int y = pPt->y - XSView_GetVViewPos(hEle) - XSView_GetSpacingTop(hEle) - 1;

		pos = y / LISTBOX(hEle)->height;
		if (pos >= Array_GetCount(LISTBOX(hEle)->hArrayListItem))
		{
			pos = -1;
		}
	}
	return pos;
}

/// @brief 获取项绑定数据.
/// @param hEle   元素句柄
/// @param index  项索引.
/// @return 项绑定数据,如果失败返回-1.
int  WINAPI XListBox_GetItemData(HELE hEle, int index) //获取项绑定数据
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_  *pListBox = LISTBOX(hEle);
	int count = XArray_GetCount(pListBox->hArrayListItem);

	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pListBox->hArrayListItem, index);
		return pItem->userData;
	}
	return -1;
}

/// @brief 设置项绑定数据.
/// @param hEle   元素句柄
/// @param index  项索引.
/// @param data   项绑定数据.
void WINAPI XListBox_SetItemData(HELE hEle, int index, int data) //设置项绑定数据
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_  *pListBox = LISTBOX(hEle);
	int count = XArray_GetCount(pListBox->hArrayListItem);

	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pListBox->hArrayListItem, index);
		pItem->userData = data;
	}
}

/// @brief 设置选择项颜色.
/// @param hEle   元素句柄
/// @param color  RGB颜色.
void WINAPI XListBox_SetSelectItemColor(HELE hEle, COLORREF color) //设置选择项颜色
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->selectItemColor = color;
}

/// @brief 设置鼠标停留项颜色.
/// @param hEle   元素句柄
/// @param color  RGB颜色.
void WINAPI XListBox_SetItemMouseStayColor(HELE hEle, COLORREF color) //设置鼠标停留高亮项颜色
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->mouseStayColor = color;
}

///@}


BOOL CALLBACK ListBox_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	listBox_ *pObj = LISTBOX(hEle);
	if (pObj->bAdjust)
	{
		XListBox_Adjust(hEle);
	}
	int right = XSView_GetViewWidth(hEle) - XSView_GetHViewPos(hEle) - 1;

	//绘制列表项
	RECT rcItem;
	rcItem.left = XSView_GetSpacingLeft(hEle) + 1;
	rcItem.right = right;
	int y = XSView_GetSpacingTop(hEle) + 1;
	int count = Array_GetCount(pObj->hArrayListItem);

	//用户自绘----------------------------------------------
	if (pObj->pDrawItem)
	{
		for (int i = 0; i < count; i++)
		{
			listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, i);
			rcItem.top = y;
			y += pObj->height;
			rcItem.bottom = y;

			listBox_drawItem_ drawItem;
			memset(&drawItem, 0, sizeof(drawItem));
			drawItem.hDraw = hDraw;
			drawItem.index = i;
			drawItem.imageId = pItem->imageID;
			if (pObj->curSel == i) //选择项
				drawItem.state = STATE_SELECT;
			else
				drawItem.state = STATE_LEAVE;
			drawItem.rcItem = rcItem;
			drawItem.pText = XStr_GetBuffer(pItem->hString);

			if (pObj->bCheck)
			{
				int left = XSView_GetSpacingLeft(hEle) + 1;
				int top = XSView_GetSpacingTop(hEle) + 1;
				drawItem.rcCheck.left = left + XLISTBOX_LEFT;
				drawItem.rcCheck.top = top + i*pObj->height;
				drawItem.rcCheck.right = left + XLISTBOX_CHECK_SIZE;
				drawItem.rcCheck.bottom = drawItem.rcCheck.top + pObj->height;
			}
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			if (pObj->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hEle = hEle;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)&drawItem;
				event_.lParam = NULL;
				event_.pClass_fun = pObj->pClass_Fun_Info;
				((pFunClassEventMsg)pObj->pDrawItem)(&event_, xc_fun_v_e_listBox);
			}
			else
			{
				pObj->pDrawItem(hEle, &drawItem);
			}
#else
			pObj->pDrawItem(hEle, &drawItem);
#endif
			XDraw_RestoreGDIOBJ_(hDraw);
		}
		return TRUE;
	}
	//---系统自绘---------------------------------------------
	RECT rcText;
	int  imageWidth = 0;
	if (pObj->hImageList)
	{
		imageWidth = XImageList_GetWidth(pObj->hImageList) + 3;
	}

	for (int i = 0; i < count; i++)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, i);

		int  left = rcItem.left + XLISTBOX_LEFT;
		rcItem.top = y;
		y += pObj->height;
		rcItem.bottom = y;

		rcText = rcItem;

		//高亮行
		if (pObj->bLineHighlight && pObj->mouseStayId == i)
		{
			XDraw_FillSolidRect_(hDraw, &rcItem, pObj->mouseStayColor);//200,200,200));
		}

		if (pObj->curSel == i) //选择项
		{
			XDraw_FillSolidRect_(hDraw, &rcItem, pObj->selectItemColor);//83,132,213));//126,206,244
		}

		//绘制复选框
		if (pObj->bCheck)
		{
			int top = rcItem.top + pObj->height / 2 - 6 - 1;
			XDraw_Check_(hDraw, left, top, RGB(80, 80, 80), pItem->bCheck);

			left += (XLISTBOX_CHECK_SIZE + 3);
		}

		//绘制图标
		if (pObj->hImageList && pItem->imageID != -1)
		{
			XImageList_DrawImage(pObj->hImageList, hDraw, pItem->imageID, left, rcItem.top + (pObj->height / 2) - imageWidth / 2);
			left += imageWidth;
		}

		wchar_t *pText = XStr_GetBuffer(pItem->hString);
		if (pText)
		{
			rcText.left = left;
			XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_VCENTER | DT_SINGLELINE);
		}
	}
	return TRUE;
}

void ListBox_MouseDown(HELE hEle, POINT *pPt)
{
	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (FALSE == PtInRect(&rect, *pPt))
		return;

	int posy = XSView_GetVViewPos(hEle) + XSView_GetSpacingTop(hEle) + 1;

	int y = pPt->y + (-posy);
	int line = y / LISTBOX(hEle)->height;

	if (line < Array_GetCount(LISTBOX(hEle)->hArrayListItem))
	{
		if (LISTBOX(hEle)->bCheck)
		{
			int left = XSView_GetSpacingLeft(hEle) + 1;
			int posx = XSView_GetHViewPos(hEle);
			int x = pPt->x + (-posx);
			if (x > (left + XLISTBOX_LEFT) && x < (left + XLISTBOX_LEFT + XLISTBOX_CHECK_SIZE))
			{
				listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, line);
				pItem->bCheck = pItem->bCheck ? FALSE : TRUE;
				XEle_RedrawEle(hEle);
				return;
			}
		}
		if (LISTBOX(hEle)->curSel != line)
		{
			BOOL bChange = FALSE;
			Ele_SendEvent(hEle, XE_LISTBOX_SELECT_ING, line, (LPARAM)&bChange);
			if (!bChange)
			{
				LISTBOX(hEle)->curSel = line;
				Ele_SendEvent(hEle, XE_LISTBOX_SELECT, line, 0);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
	}
	else
	{
		if (LISTBOX(hEle)->curSel != -1)
		{
			BOOL bChange = FALSE;
			Ele_SendEvent(hEle, XE_LISTBOX_SELECT_ING, line, (LPARAM)&bChange);
			if (!bChange)
			{
				LISTBOX(hEle)->curSel = -1;
				Ele_SendEvent(hEle, XE_LISTBOX_SELECT, -1, 0);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
	}
}

BOOL CALLBACK ListBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	ListBox_MouseDown(hEle, pPt);
	return FALSE;
}

BOOL CALLBACK ListBox_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	if (LISTBOX(hEle)->bLineHighlight)
	{
		RECT rect;
		XSView_GetViewRect(hEle, &rect);
		if (PtInRect(&rect, *pPt))
		{
			int posy = XSView_GetVViewPos(hEle) + XSView_GetSpacingTop(hEle) + 1;

			int y = pPt->y + (-posy);
			int line = y / LISTBOX(hEle)->height;

			if (line < Array_GetCount(LISTBOX(hEle)->hArrayListItem))
			{
				if (LISTBOX(hEle)->mouseStayId != line)
				{
					LISTBOX(hEle)->mouseStayId = line;
					XEle_RedrawEle(hEle);
				}
				return FALSE;
			}
		}
		if (-1 != LISTBOX(hEle)->mouseStayId)
		{
			LISTBOX(hEle)->mouseStayId = -1;
			XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK ListBox_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	if (-1 != LISTBOX(hEle)->mouseStayId)
	{
		LISTBOX(hEle)->mouseStayId = -1;
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}