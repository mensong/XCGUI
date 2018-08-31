/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup propertyPage 属性页元素(PropertyPage)
/// @ingroup groupElements
/// @{

/// @brief 创建属性页元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XPPage_Create(int x, int y, int cx, int cy, HXCGUI hParent) //创建按钮
{
	propertyPage_ *pObj = (propertyPage_*)malloc(sizeof(propertyPage_));
	memset(pObj, 0, sizeof(propertyPage_));

	PPage_Init((HELE)pObj, x, y, cx, cy, XC_PROPERTYPAGE, hParent);
	return (HELE)pObj;
}

void PPage_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_PROPERTYPAGE);
	propertyPage_ *pObj = PPAGE(hEle);
	pObj->height = 25;
	pObj->widthBtn = 45;
	pObj->hArrayList = XArray_Create();
	pObj->spacing = 1;
	pObj->bScrollButton = TRUE;

	pObj->hBtnUp = XBtn_Create(cx - 39, pObj->height - 22, 20, 20, L"<<");
	XEle_AddEle(hEle, pObj->hBtnUp);

	pObj->hBtnDown = XBtn_Create(cx - 20, pObj->height - 22, 20, 20, L">>");
	XEle_AddEle(hEle, pObj->hBtnDown);

	XEle_ShowEle(pObj->hBtnUp, FALSE);
	XEle_ShowEle(pObj->hBtnDown, FALSE);

	XEle_RegisterMessage(hEle, XM_PAINT, PPage_OnDraw);
	XEle_RegisterEvent(hEle, XE_SIZE, PPage_OnEventSize);

	XEle_RegisterMessage(pObj->hBtnUp, XM_PAINT, PPage_OnDraw_Up);
	XEle_RegisterMessage(pObj->hBtnDown, XM_PAINT, PPage_OnDraw_Down);
	XEle_RegisterEvent(pObj->hBtnUp, XE_BNCLICK, PPage_OnEventBtnClick_Up);
	XEle_RegisterEvent(pObj->hBtnDown, XE_BNCLICK, PPage_OnEventBtnClick_Down);
	XEle_RegisterEvent(hEle, XE_DESTROY, PPage_OnDestroy);
}

void CALLBACK PPage_OnDestroy(HELE hEle) //销毁
{
	int count = XArray_GetCount(PPAGE(hEle)->hArrayList);
	void  *pItem = NULL;
	for (int i = 0; i < count; i++)
	{
		pItem = Array_GetAt(PPAGE(hEle)->hArrayList, i);
		free(pItem);
	}
	XArray_Destroy(PPAGE(hEle)->hArrayList);
}

/// @brief 添加一个标签.
/// @param hEle 元素句柄.
/// @param pName  标签名.
/// @param hPage  绑定的子页面元素.
/// @return 标签索引.
int WINAPI XPPage_AddLabel(HELE hEle, wchar_t *pName, HELE hPage) //添加一个标签
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (hPage)
	{
		IsEleDebug(hPage, __FUNCTION__);
		if (NULL == ((ele_*)hPage)->pParentEle)
		{
			XEle_AddEle(hEle, hPage);
		}
	}

	propertyPage_item_ *pItem = PPage_AddLabel(hEle, pName, hPage);
	XArray_Add(PPAGE(hEle)->hArrayList, pItem);
	PPAGE(hEle)->bAdjust = TRUE;
	return Array_GetCount(PPAGE(hEle)->hArrayList) - 1;
}

/// @brief 插入一个标签.
/// @param hEle 元素句柄.
/// @param index  插入位置索引.
/// @param pName  标签名.
/// @param hPage  绑定的子页面元素.
/// @return 标签索引.
int WINAPI XPPage_InsertLabel(HELE hEle, int index, wchar_t *pName, HELE hPage)//插入一个标签
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (hPage)
	{
		IsEleDebug(hPage, __FUNCTION__);
	}

	propertyPage_item_ *pItem = PPage_AddLabel(hEle, pName, hPage);
	XArray_insert(PPAGE(hEle)->hArrayList, pItem, index);
	PPAGE(hEle)->bAdjust = TRUE;

	return index;
}

propertyPage_item_* PPage_AddLabel(HELE hEle, wchar_t *pName, HELE hPage)
{
	propertyPage_item_  *pItem = (propertyPage_item_*)malloc(sizeof(propertyPage_item_));
	memset(pItem, 0, sizeof(propertyPage_item_));

	pItem->hButton = XPPageBtn_Create(0, 0, 10, 10, pName, hEle);
	pItem->hPage = hPage;

	if (hPage && NULL == ((ele_*)hPage)->pParentEle)
	{
		XEle_AddEle(hEle, hPage);
	}

	//XEle_RegisterMessage(pItem->hButton,XM_PAINT,PPage_OnDrawLabel);
	XEle_RegisterEvent(pItem->hButton, XE_BNCLICK, PPage_OnEventBtnClick);
	if (pName)
	{
		SIZE size;    //字符长度
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)pItem->hButton)->hFontX));
		GetTextExtentPoint32(hdc, pName, wcslen(pName), &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

		pItem->width = size.cx + 10;
	}
	if (pItem->width < 50)
		pItem->width = 50;

	if (NULL == PPAGE(hEle)->pSelectItem)
	{
		PPAGE(hEle)->pSelectItem = pItem;
		XBtn_SetCheck(pItem->hButton, TRUE);
	}

	if (hPage)
	{
		//调整页大小
		RECT rc;
		XEle_GetClientRect(hEle, &rc);
		rc.top = PPAGE(hEle)->height;
		rc.left++;
		rc.right--;
		rc.bottom--;
		XEle_SetRect(hPage, &rc);
	}
	return pItem;
}

/// @brief 绑定视图元素到标签.
/// @param hEle 元素句柄.
/// @param index  标签索引.
/// @param hPage  要绑定的视图元素.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XPPage_SetBindEle(HELE hEle, int index, HELE hPage)
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	IsEleDebug(hPage, __FUNCTION__);

	propertyPage_ *pObj = PPAGE(hEle);
	if (index < 0 || index >= Array_GetCount(pObj->hArrayList))
		return FALSE;

	if (NULL == ((ele_*)hPage)->pParentEle)
	{
		XEle_AddEle(hEle, hPage);
	}

	propertyPage_item_ *pItem = (propertyPage_item_*)Array_GetAt(pObj->hArrayList, index);
	pItem->hPage = hPage;


	if (pItem == pObj->pSelectItem)
	{
		XEle_ShowEle(hPage, TRUE);
	}
	else
	{
		XEle_ShowEle(hPage, FALSE);
	}
	pObj->bAdjust = TRUE;
	return TRUE;
}

/// @brief 设置标签高度.
/// @param hEle  元素句柄.
/// @param height 标签高度.
void WINAPI XPPage_SetLabelHeight(HELE hEle, int height) //设置标签高度
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	PPAGE(hEle)->height = height;
	XPPage_Adjust(hEle);
	XEle_RedrawEle(hEle);
}

/// @brief 设置指定标签宽度.
/// @param hEle  元素句柄.
/// @param index 标签索引.
/// @param width 标签宽度.
void WINAPI XPPage_SetLabelWidth(HELE hEle, int index, int width)  //设置标签宽度
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	propertyPage_ *pObj = PPAGE(hEle);
	int count = XArray_GetCount(pObj->hArrayList);
	if (index >= 0 && index < count)
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(pObj->hArrayList, index);
		pItem->widthUser = width;
		pObj->bAdjust = TRUE;
	}
}

/// @brief 获取指定标签宽度.
/// @param hEle  元素句柄.
/// @param index 标签索引.
/// @return  返回标签宽度.
int  WINAPI XPPage_GetLabelWidth(HELE hEle, int index)  //获取标签宽度
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	propertyPage_ *pObj = PPAGE(hEle);
	int count = XArray_GetCount(pObj->hArrayList);
	if (index >= 0 && index < count)
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(pObj->hArrayList, index);
		return pItem->widthUser;
	}
	return -1;
}

/// @brief 获取标签项数量.
/// @param hEle  元素句柄.
/// @return  标签项数量.
int  WINAPI XPPage_GetLabelCount(HELE hEle) //获取标签项数量
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	return XArray_GetCount(PPAGE(hEle)->hArrayList);
}

/// @brief 设置选择标签.
/// @param hEle  元素句柄.
/// @param index 标签位置索引.
/// @param reDraw 是否重绘.
void WINAPI XPPage_SetSelect(HELE hEle, int index, BOOL reDraw)  //设置选择标签
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (index < 0 || index >= Array_GetCount(PPAGE(hEle)->hArrayList))
		return;

	propertyPage_item_ *pNewSel = (propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList, index);
	if (PPAGE(hEle)->pSelectItem != pNewSel)
	{
		if (PPAGE(hEle)->pSelectItem)
		{
			if (PPAGE(hEle)->pSelectItem->hPage)
				XEle_ShowEle(PPAGE(hEle)->pSelectItem->hPage, FALSE);
			XBtn_SetCheck(PPAGE(hEle)->pSelectItem->hButton, FALSE);
		}
		PPAGE(hEle)->pSelectItem = pNewSel;
		if (PPAGE(hEle)->pSelectItem->hPage)
			XEle_ShowEle(PPAGE(hEle)->pSelectItem->hPage, TRUE);
		XBtn_SetCheck(PPAGE(hEle)->pSelectItem->hButton, TRUE);

		if (FALSE == XEle_IsShowEle(pNewSel->hButton))
		{
			PPAGE(hEle)->indent = index;
			PPAGE(hEle)->bAdjust = TRUE;
		}
		Ele_SendEvent(hEle, XE_PPAGE_SELECT, index, 0);

		if (reDraw)
			XEle_RedrawEle(hEle);
	}
}

/// @brief 设置标签文本.
/// @param hEle  元素句柄.
/// @param index 标签位置索引.
/// @param pText 文本内容.
void WINAPI XPPage_SetLabelText(HELE hEle, int index, wchar_t *pText)  //设置
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (NULL == pText) return;

	if (pText && index >= 0 && index < Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList, index);

		SIZE size;    //字符长度
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)pItem->hButton)->hFontX));
		GetTextExtentPoint32(hdc, pText, wcslen(pText), &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);
		pItem->width = size.cx + 10;

		XBtn_SetText(pItem->hButton, pText);
		PPAGE(hEle)->bAdjust = TRUE;
		XEle_RedrawEle(hEle);
	}
}

/// @brief 获取选择的标签索引.
/// @param hEle  元素句柄.
/// @return 标签位置索引.
int WINAPI XPPage_GetSelect(HELE hEle) //获取选择的标签
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (PPAGE(hEle)->pSelectItem)
	{
		propertyPage_item_  *pItem = NULL;
		int count = XArray_GetCount(PPAGE(hEle)->hArrayList);
		for (int i = 0; i < count; i++)
		{
			pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, i);
			if (PPAGE(hEle)->pSelectItem == pItem)
			{
				return i;
			}
		}
	}
	return -1;
}

/// @brief 获取标签高度.
/// @param hEle  元素句柄.
/// @return 标签高度.
int WINAPI XPPage_GetLabelHeight(HELE hEle) //获取标签高度
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	return PPAGE(hEle)->height;
}

/// @brief 获取标签文本.
/// @param hEle  元素句柄.
/// @param index 标签位置索引
/// @return 文本内容.
wchar_t* WINAPI XPPage_GetLabelText(HELE hEle, int index)  //获取文本
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (index >= 0 && index < Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, index);
		return XBtn_GetText(pItem->hButton);
	}
	return NULL;
}

/// @brief 获取标签按钮.返回按钮句柄类型为Button.
/// @param hEle  元素句柄.
/// @param index 标签位置索引
/// @return 标签按钮句柄.
HELE WINAPI XPPage_GetLabel(HELE hEle, int index) //获取标签按钮
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (index >= 0 && index < Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, index);
		return pItem->hButton;
	}
	return NULL;
}

/// @brief 获取标签对应的页.
/// @param hEle  元素句柄.
/// @param index 标签位置索引
/// @return 绑定的页元素.
HELE WINAPI XPPage_GetLabelPage(HELE hEle, int index)
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (index >= 0 && index < Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, index);
		return pItem->hPage;
	}
	return NULL;
}

/// @brief 获取属性页元素绑定的页元素,对应标签基于0的索引值.
/// @param hEle  元素句柄.
/// @param hPage 属性页元素绑定的页元素句柄
/// @return 页对应标签位置索引值.
int WINAPI XPPage_GetPageIndex(HELE hEle, HELE hPage) //检索绑定页对应标签索引
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	IsEleDebug(hPage, __FUNCTION__);
	int count = XArray_GetCount(PPAGE(hEle)->hArrayList);
	for (int i = 0; i < count; i++)
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, i);
		if (hPage == pItem->hPage)
		{
			return i;
		}
	}
	return -1;
}

/// @brief 获取属性页标签按钮元素位置索引值.
/// @param hEle  元素句柄.
/// @param hLabel 标签按钮元素句柄.
/// @return 标签位置索引值.
int WINAPI XPPage_GetLabelIndex(HELE hEle, HELE hLabel) //获取属性页标签按钮元素位置索引值
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	IsButtonDebug(hLabel, __FUNCTION__);
	int count = XArray_GetCount(PPAGE(hEle)->hArrayList);
	for (int i = 0; i < count; i++)
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, i);
		if (hLabel == pItem->hButton)
		{
			return i;
		}
	}
	return -1;
}

/// @brief 删除指定标签.
/// @param hEle  元素句柄.
/// @param index 要删除的标签位置索引
/// @param deletePage 如果参数为TRUE,同时删除该标签绑定的页,并且销毁页,否则相反.
void WINAPI XPPage_DeleteLabel(HELE hEle, int index, BOOL deletePage) //删除
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(PPAGE(hEle)->hArrayList);
	if (index >= 0 && index < count)
	{
		propertyPage_item_ *pDel = (propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList, index);
		XArray_DeleteIndex(PPAGE(hEle)->hArrayList, index);
		count--;
		XEle_Destroy(pDel->hButton);
		if (deletePage)
		{
			if (pDel->hPage)	XEle_Destroy(pDel->hPage);
		}

		if (PPAGE(hEle)->pSelectItem == pDel)
		{
			if (index >= count) index--;

			if (index >= 0)
			{
				PPAGE(hEle)->pSelectItem = (propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList, index);
				XBtn_SetCheck(PPAGE(hEle)->pSelectItem->hButton, TRUE);

				Ele_SendEvent(hEle, XE_PPAGE_SELECT, index, 0);
			}
			else
			{
				PPAGE(hEle)->pSelectItem = NULL;
				Ele_SendEvent(hEle, XE_PPAGE_SELECT, -1, 0);
			}
			PPage_OnEventSize(hEle, hEle);
		}
		free(pDel);
		PPAGE(hEle)->bAdjust = TRUE;
		XEle_RedrawEle(hEle);
	}
}

/// @brief 删除所有标签.
/// @param hEle  元素句柄.
/// @param deletePage 如果参数为TRUE,同时删除该标签绑定的页,并且销毁页,否则相反.
void WINAPI XPPage_DeleteLabelAll(HELE hEle, BOOL deletePage) //删除所有PPAGE
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(PPAGE(hEle)->hArrayList);
	propertyPage_item_ *pDel = NULL;
	for (int i = 0; i < count; i++)
	{
		pDel = (propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList, i);
		XEle_Destroy(pDel->hButton);
		if (deletePage)
		{
			if (pDel->hPage)	XEle_Destroy(pDel->hPage);
		}
		free(pDel);
	}
	XArray_DeleteAll(PPAGE(hEle)->hArrayList);

	if (PPAGE(hEle)->pSelectItem)
	{
		PPAGE(hEle)->pSelectItem = NULL;
		Ele_SendEvent(hEle, XE_PPAGE_SELECT, -1, 0);
	}
	PPAGE(hEle)->indent = 0;
	PPAGE(hEle)->bAdjust = TRUE;
	XEle_RedrawEle(hEle);
}

/// @brief 启用或关闭滚动按钮.
/// @param hEle  元素句柄.
/// @param bEnable TRUE启用,否则相反.
void WINAPI XPPage_EnableScrollButton(HELE hEle, BOOL bEnable) //是否显示滚动按钮
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (PPAGE(hEle)->bScrollButton != bEnable)
	{
		PPAGE(hEle)->bScrollButton = bEnable;
		XEle_ShowEle(PPAGE(hEle)->hBtnUp, FALSE);
		XEle_ShowEle(PPAGE(hEle)->hBtnDown, FALSE);
		XPPage_Adjust(hEle);
	}
}

/// @brief 设置标签与标签之间的间隔.
/// @param hEle  元素句柄.
/// @param spacing 间隔大小.
void WINAPI XPPage_SetLabelSpacing(HELE hEle, int spacing)
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	((propertyPage_*)hEle)->spacing = spacing;
	((propertyPage_*)hEle)->bAdjust = TRUE;
}

/// @brief 获取标签与标签之间的间隔.
/// @param hEle  元素句柄.
/// @return 间隔大小.
int WINAPI XPPage_GetLabelSpacing(HELE hEle)
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	return ((propertyPage_*)hEle)->spacing;
}

/// @brief 属性页元素调整布局.
/// @param hEle  元素句柄.
void WINAPI XPPage_Adjust(HELE hEle)
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	propertyPage_ *pObj = PPAGE(hEle);
	pObj->bAdjust = FALSE;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	int width = 0;//TAB按钮可用区域宽度
	int count = Array_GetCount(pObj->hArrayList);
	int index = 0;

	if (count < 1)
	{
		pObj->indent = 0;
		XEle_ShowEle(pObj->hBtnUp, FALSE);
		XEle_ShowEle(pObj->hBtnDown, FALSE);
		return;
	}
	if (pObj->indent >= count)
	{
		pObj->indent = 0;
	}

	if (pObj->bScrollButton)
		width = rect.right - rect.left - pObj->widthBtn;
	else
		width = rect.right - rect.left;

	propertyPage_item_ *pItem = NULL;
	for (; index < pObj->indent; index++) //隐藏不显示的tab
	{
		pItem = (propertyPage_item_*)Array_GetAt(pObj->hArrayList, index);
		XEle_ShowEle(pItem->hButton, FALSE);
	}

	RECT rcItem;
	int left = 0;
	int  tabWidth = 0;
	for (; index < count; index++)
	{
		pItem = (propertyPage_item_*)Array_GetAt(pObj->hArrayList, index);

		if (0 == pItem->widthUser)
			tabWidth = pItem->width;
		else
			tabWidth = pItem->widthUser;

		if ((left + tabWidth) > width)
			break;

		rcItem.left = left;
		rcItem.top = 0;
		rcItem.right = left + tabWidth;
		rcItem.bottom = pObj->height;
		XEle_SetRect(pItem->hButton, &rcItem);
		if (pItem->hPage)
		{
			if (pObj->pSelectItem == pItem)
			{
				XEle_ShowEle(pItem->hPage, TRUE);
			}
			else
			{
				XEle_ShowEle(pItem->hPage, FALSE);
			}
		}
		XEle_ShowEle(pItem->hButton, TRUE);

		left += tabWidth;
		left += pObj->spacing;
	}

	//调整滚动按钮
	if (pObj->bScrollButton)
	{
		if (0 != pObj->indent || index != count)
		{
			XEle_ShowEle(pObj->hBtnUp, TRUE);
			XEle_ShowEle(pObj->hBtnDown, TRUE);
		}
		else
		{
			XEle_ShowEle(pObj->hBtnUp, FALSE);
			XEle_ShowEle(pObj->hBtnDown, FALSE);
		}
		//调整滚动按钮位置
		RECT rcButton; //20*20
		rcButton.top = PPAGE(hEle)->height - 22;
		rcButton.bottom = rcButton.top + 20;
		rcButton.right = rect.right;
		rcButton.left = rcButton.right - 20;

		XEle_SetRect(PPAGE(hEle)->hBtnDown, &rcButton);

		rcButton.right = rcButton.left;
		rcButton.left = rcButton.right - 20;
		XEle_SetRect(PPAGE(hEle)->hBtnUp, &rcButton);
	}

	for (; index < count; index++) //隐藏不显示的tab
	{
		pItem = (propertyPage_item_*)Array_GetAt(pObj->hArrayList, index);
		XEle_ShowEle(pItem->hButton, FALSE);
	}

	//调整页大小
	{
		rect.top = PPAGE(hEle)->height;
		rect.left++;
		rect.right--;
		rect.bottom--;

		propertyPage_item_ *pItem = NULL;
		int count = Array_GetCount(PPAGE(hEle)->hArrayList);
		for (int i = 0; i < count; i++)
		{
			pItem = (propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList, i);
			if (pItem->hPage)
			{
				XEle_SetRect(pItem->hPage, &rect);
			}
		}
	}
}

/// @brief 左按钮滚动.
/// @param hEle  元素句柄.
void WINAPI XPPage_SetUp(HELE hEle)  //左滚动
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	if (PPAGE(hEle)->indent > 0)
	{
		PPAGE(hEle)->indent--;
		PPAGE(hEle)->bAdjust = TRUE;
		XEle_RedrawEle(hEle);
	}
	//	OutputDebugStringA("左滚动\n");
}

/// @brief 右按钮滚动.
/// @param hEle  元素句柄.
void WINAPI XPPage_SetDown(HELE hEle) //右滚动
{
	IsPropertyPageDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(PPAGE(hEle)->hArrayList);
	if (count <= 0) return;

	if (PPAGE(hEle)->indent < (count - 1))
	{
		propertyPage_item_ *pItem = (propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList, count - 1);
		if (FALSE == XEle_IsShowEle(pItem->hButton))
		{
			PPAGE(hEle)->indent++;
			PPAGE(hEle)->bAdjust = TRUE;
			XEle_RedrawEle(hEle);
		}
	}
	//	OutputDebugStringA("右滚动\n");
}

BOOL CALLBACK PPage_OnEventBtnClick_Up(HELE hEle, HELE hEventEle) //按钮事件
{
	if (hEle != hEventEle)
		return FALSE;

	XPPage_SetUp((HELE)((ele_*)hEle)->pParentEle);
	return TRUE;
}

BOOL CALLBACK PPage_OnEventBtnClick_Down(HELE hEle, HELE hEventEle) //按钮事件
{
	if (hEle != hEventEle)
		return FALSE;

	XPPage_SetDown((HELE)((ele_*)hEle)->pParentEle);
	return TRUE;
}

BOOL CALLBACK PPage_OnDraw(HELE hEle, HDRAW hDraw)
{
	propertyPage_ *pObj = PPAGE(hEle);
	if (pObj->bAdjust)
	{
		XPPage_Adjust(hEle);
	}

	RECT rectEle;
	XEle_GetClientRect(hEle, &rectEle);

	if (((ele_*)hEle)->bBorder)
	{
		rectEle.top = pObj->height - 1;
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, ((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw, &rectEle, hBrush);
		//DeleteObject(hBrush);
	}
	return TRUE;
}

BOOL CALLBACK PPage_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		XPPage_Adjust(hEle);
	}
	return FALSE;
}

BOOL CALLBACK PPage_OnDraw_Up(HELE hEle, HDRAW hDraw)   //绘制上按钮
{
	button_ *pObj = BUTTON(hEle);
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (STATE_LEAVE == pObj->state)
	{
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);
	}
	else if (STATE_STAY == pObj->state)
	{
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);

		RECT rc = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(253, 183, 53));
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//		DeleteObject(hBrush);
	}
	else if (STATE_DOWN == pObj->state)
	{
		XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);

		RECT rc = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(253, 183, 53));
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//DeleteObject(hBrush);
	}

	POINT  pt[3];
	pt[0].x = rect.left + 5 + 2;
	pt[0].y = rect.top + 7 + 2;
	pt[1].x = rect.left + 10 + 2;
	pt[1].y = rect.top + 2 + 2;
	pt[2].x = rect.left + 10 + 2;
	pt[2].y = rect.top + 13 + 2;
	HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
	HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
	XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	//	DeleteObject(hRgn);
	//	DeleteObject(hBrush2);

		//绘制边框
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	XDraw_FrameRect_(hDraw, &rect, hBrush);
	//	DeleteObject(hBrush);

	return TRUE;
}

BOOL CALLBACK PPage_OnDraw_Down(HELE hEle, HDRAW hDraw) //绘制下按钮
{
	button_ *pObj = BUTTON(hEle);
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (STATE_LEAVE == pObj->state)
	{
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);
	}
	else if (STATE_STAY == pObj->state)
	{
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);

		RECT rc = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(253, 183, 53));
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//DeleteObject(hBrush);
	}
	else if (STATE_DOWN == pObj->state)
	{
		XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);

		RECT rc = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(253, 183, 53));
		XDraw_FrameRect_(hDraw, &rc, hBrush);
		//DeleteObject(hBrush);
	}
	POINT  pt[3];
	pt[0].x = rect.left + 5 + 2;
	pt[0].y = rect.top + 2 + 2;
	pt[1].x = rect.left + 5 + 2;
	pt[1].y = rect.top + 12 + 2;
	pt[2].x = rect.left + 10 + 2;
	pt[2].y = rect.top + 7 + 2;
	HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
	HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
	XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	//	DeleteObject(hRgn);
	//	DeleteObject(hBrush2);

		//绘制边框
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	XDraw_FrameRect_(hDraw, &rect, hBrush);
	//	DeleteObject(hBrush);
	return TRUE;
}

BOOL CALLBACK PPage_OnEventBtnClick(HELE hEle, HELE hEventEle) //标签选择
{
	if (hEle == hEventEle)
	{
		propertyPage_ *pLabel = (propertyPage_*)XEle_GetParentEle(hEle);

		int count = XArray_GetCount(pLabel->hArrayList);
		for (int i = 0; i < count; i++)
		{
			propertyPage_item_  *pItem = (propertyPage_item_*)XArray_GetAt(pLabel->hArrayList, i);
			if (pItem->hButton == hEle)
			{
				if (pLabel->pSelectItem->hButton != hEle)
				{
					if (pLabel->pSelectItem->hPage)
						XEle_ShowEle(pLabel->pSelectItem->hPage, FALSE);
					XBtn_SetCheck(pLabel->pSelectItem->hButton, FALSE);

					if (pItem->hPage)
						XEle_ShowEle(pItem->hPage, TRUE);
					XBtn_SetCheck(hEle, TRUE);
					pLabel->pSelectItem = pItem;

					Ele_SendEvent((HELE)pLabel, XE_PPAGE_SELECT, i, 0);
					XEle_RedrawEle((HELE)pLabel);
				}
				break;
			}
		}
	}
	return TRUE;
}

///@}


//////////////////////////////////////////////////////////////////////////////
HELE XPPageBtn_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent)
{
	button_ *pNew = (button_*)malloc(sizeof(button_));
	memset(pNew, 0, sizeof(button_));

	PPageBtn_Init((HELE)pNew, x, y, cx, cy, XC_PROPERTYPAGE_LABEL, pTitle, hParent);

	return (HELE)pNew;
}

void PPageBtn_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent)
{
	Btn_Init(hEle, x, y, cx, cy, eleType, pTitle, hParent);

	AddTypeDebug(hEle, XC_PROPERTYPAGE_LABEL);

	XEle_EnableFocus(hEle, FALSE);
	XEle_RegisterMessage(hEle, XM_PAINT, PPageBtn_OnDrawLabel);
}


BOOL CALLBACK PPageBtn_OnDrawLabel(HELE hEle, HDRAW hDraw)
{
	button_ *pObj = BUTTON(hEle);
	if (pObj->hImage_leave || pObj->hImage_stay || pObj->hImage_down
		|| pObj->hImage_check || pObj->hImage_disable || pObj->hImage_icon)
	{
		Btn_OnDraw(hEle, hDraw);
		return TRUE;
	}

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (pObj->bCheck)
	{
		if (pObj->hImage_check)
		{
			return FALSE;
		}
		else
		{
			XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);

			//绘制内浅黄色线
			HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(253, 183, 53));
			HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
			XDraw_MoveToEx_(hDraw, rect.left + 1, rect.bottom - 1, NULL);
			XDraw_LineTo_(hDraw, rect.left + 1, rect.top + 1);
			XDraw_LineTo_(hDraw, rect.right - 2, rect.top + 1);
			XDraw_LineTo_(hDraw, rect.right - 2, rect.bottom - 1);
			//	SelectObject(hdc,hOldPen);
			//	DeleteObject(hPen);

				//绘制外边框
			HPEN hPen2 = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(128, 128, 128));
			HGDIOBJ hOldPen2 = XDraw_SelectObject_(hDraw, hPen2);
			XDraw_MoveToEx_(hDraw, rect.left, rect.bottom - 1, NULL);
			XDraw_LineTo_(hDraw, rect.left, rect.top);
			XDraw_LineTo_(hDraw, rect.right - 1, rect.top);
			XDraw_LineTo_(hDraw, rect.right - 1, rect.bottom);
			//	SelectObject(hdc,hOldPen2);
			//	DeleteObject(hPen2);
		}
	}
	else if (STATE_LEAVE == pObj->state)
	{
		rect.top += 2;
		if (pObj->hImage_leave)
		{
			return FALSE;
		}
		else
		{
			XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);
			//绘制外边框
			HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
			XDraw_FrameRect_(hDraw, &rect, hBrush);
			//DeleteObject(hBrush);
		}
	}
	else if (STATE_STAY == pObj->state)
	{
		if (pObj->hImage_stay)
		{
			return FALSE;
		}
		else
		{
			XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);
			//绘制内边框
			HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(253, 183, 53));
			HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
			XDraw_MoveToEx_(hDraw, rect.left + 1, rect.bottom - 1, NULL);
			XDraw_LineTo_(hDraw, rect.left + 1, rect.top + 1);
			XDraw_LineTo_(hDraw, rect.right - 2, rect.top + 1);
			XDraw_LineTo_(hDraw, rect.right - 2, rect.bottom - 1);
			//SelectObject(hdc,hOldPen);
			//DeleteObject(hPen);

			//绘制外边框
			HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
			XDraw_FrameRect_(hDraw, &rect, hBrush);
			//DeleteObject(hBrush);
		}
	}
	else if (STATE_DOWN == pObj->state)
	{
		if (pObj->hImage_down)
		{
			return FALSE;
		}
		else
		{
			XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);
			//绘制内边框
			HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(253, 183, 53));
			HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
			XDraw_MoveToEx_(hDraw, rect.left + 1, rect.bottom - 1, NULL);
			XDraw_LineTo_(hDraw, rect.left + 1, rect.top + 1);
			XDraw_LineTo_(hDraw, rect.right - 2, rect.top + 1);
			XDraw_LineTo_(hDraw, rect.right - 2, rect.bottom - 1);
			//	SelectObject(hdc,hOldPen);
			//	DeleteObject(hPen);

				//绘制外边框
			HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
			XDraw_FrameRect_(hDraw, &rect, hBrush);
			//DeleteObject(hBrush);
		}
	}

	Btn_DrawIconAndText(hEle, hDraw, rect);
	return TRUE;
}