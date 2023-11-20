/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup comboBox 下拉组合框(ComboBox)
/// @ingroup groupElements
/// @{

/// @brief 创建下拉组合框元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XComboBox_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	comboBox_ *pObj = (comboBox_*)malloc(sizeof(comboBox_));
	if (pObj)
	{
		memset(pObj, 0, sizeof(comboBox_));

		ComboBox_Init((HELE)pObj, x, y, cx, cy, XC_COMBOBOX, hParent);
		return (HELE)pObj;
	}
	return NULL;
}

void ComboBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Edit_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_COMBOBOX);

	comboBox_ *pComboBox = COMBOBOX(hEle);
	pComboBox->bEdit = TRUE;
	pComboBox->height = 20;
	pComboBox->heights = 0;
	pComboBox->curSel = -1;
	pComboBox->hArrayStr = XArray_Create();
	pComboBox->hArrayData = XArray_Create();

	XSView_SetSpacing(hEle, 2, 2, cy - 2, 2);

	ComboBox_Adjust(hEle);

	XEle_RegisterMessage(hEle, XM_PAINT, ComboBox_OnDraw);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, ComboBox_OnMouseMove);

	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, ComboBox_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, ComboBox_OnLButtonUp);

	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, ComboBox_OnEventMouseLeave);

	XEle_RegisterMessage(hEle, XM_RBUTTONDOWN, ComboBox_OnRButtonDown);
	XEle_RegisterMessage(hEle, XM_RBUTTONUP, ComboBox_OnRButtonUp);

	XEle_RegisterEvent(hEle, XE_DESTROY, ComboBox_OnDestroy);
	XEle_RegisterEvent(hEle, XE_SIZE, ComboBox_OnEventSize);
	XEle_RegisterEvent(hEle, XE_SETFOCUS, ComboBox_OnEventSetFocus);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, ComboBox_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_MOUSEWHEEL, ComboBox_OnEventMouseWheel);
}

/// @brief 增加一个字符串到组合框.
/// @param hEle  元素句柄.
/// @param pText 文本内容.
/// @param data  项绑定用户数据.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XComboBox_AddString(HELE hEle, wchar_t *pText, void* data) //增加一个字符串到组合框
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	if (NULL == pText) return FALSE;

	int len = wcslen(pText);
	if (len < 1) return FALSE;

	len++;
	wchar_t *pStr = new wchar_t[len];

	wcscpy_s(pStr, len, pText);
	XArray_Add(COMBOBOX(hEle)->hArrayStr, pStr);
	XArray_Add(COMBOBOX(hEle)->hArrayData, (void*)data);
	return TRUE;
}

/// @brief 组合框下拉列表删除项.
/// @param hEle  元素句柄.
/// @param index 要删除的项索引
void WINAPI XComboBox_DeleteItem(HELE hEle, int index) //删除项
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(COMBOBOX(hEle)->hArrayStr);
	if (index >= 0 && index < count)
	{
		wchar_t *pText = Array_GetAtW(COMBOBOX(hEle)->hArrayStr, index);
		delete[]pText;
		XArray_DeleteIndex(COMBOBOX(hEle)->hArrayStr, index);
	}
}

/// @brief 组合框下拉列表删除所有项.
/// @param hEle  元素句柄.
void WINAPI XComboBox_DeleteItemAll(HELE hEle) //删除所有项
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(COMBOBOX(hEle)->hArrayStr);
	for (int i = 0; i < count; i++)
	{
		delete[] Array_GetAtW(COMBOBOX(hEle)->hArrayStr, i);
	}
	XArray_DeleteAll(COMBOBOX(hEle)->hArrayStr);
}

/// @brief 设置组合框显示内容.
/// @param hEle  元素句柄.
/// @param pText 文本内容.
void WINAPI XComboBox_SetText(HELE hEle, wchar_t *pText) //设置编辑框内容
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	XEdit_SetText(hEle, pText);
}

/// @brief 设置下拉列表项高.
/// @param hEle  元素句柄.
/// @param height 下拉列表项高.
void WINAPI XComboBox_SetItemHeight(HELE hEle, int height) //设置下拉列表项高
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	COMBOBOX(hEle)->height = height;
}

/// @brief 从组合框下拉列表中选择指定项.
/// @param hEle  元素句柄.
/// @param index 文本内容在下拉列表中的索引.
void WINAPI XComboBox_SetSelectItem(HELE hEle, int index) //设置显示文本
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(COMBOBOX(hEle)->hArrayStr);
	if (count > 0 && index >= 0 && index < count)
	{
		COMBOBOX(hEle)->curSel = index;
		XEdit_SetText(hEle, Array_GetAtW(COMBOBOX(hEle)->hArrayStr, index));
	}
}

/// @brief 获取下拉列表项高.
/// @param hEle  元素句柄.
/// @return 下拉列表项高.
int  WINAPI XComboBox_GetItemHeight(HELE hEle) //获取行高
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	return COMBOBOX(hEle)->height;
}

/// @brief 获取下拉列表高度.
/// @param hEle  元素句柄.
/// @return 下拉列表高度.
int  WINAPI XComboBox_GetListHeight(HELE hEle) //获取下拉列表高度
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	return COMBOBOX(hEle)->heights;
}

/// @brief 获取下拉列表指定行文本.
/// @param hEle  元素句柄.
/// @param index 行索引.
/// @return 文本内容.
wchar_t* WINAPI XComboBox_GetItemText(HELE hEle, int index) //获取下拉列表文本
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	if (index >= 0 && index < Array_GetCount(COMBOBOX(hEle)->hArrayStr))
		return Array_GetAtW(COMBOBOX(hEle)->hArrayStr, index);
	return NULL;
}

/// @brief 获取组合框的编辑框文本.
/// @param hEle  元素句柄.
/// @param pOut 接收内容缓冲区.
/// @param len pOut缓冲区长度.
void WINAPI XComboBox_GetText(HELE hEle, wchar_t *pOut, int len)  //获取编辑框文本
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	XEdit_GetText(hEle, pOut, len);
}

/// @brief 获取当前选择项索引(基于0索引).
/// @param hEle  元素句柄.
/// @return 选择项索引.
int WINAPI XComboBox_GetSelectItem(HELE hEle)  //获取当前选择项索引
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	return COMBOBOX(hEle)->curSel;
}

/// @brief 获取项用户数据.
/// @param hEle  元素句柄.
/// @param index 项索引(基于0索引).
/// @return 用户数据.
void* WINAPI XComboBox_GetItemData(HELE hEle, int index)
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	return XArray_GetAt(COMBOBOX(hEle)->hArrayData, index);
}

/// @brief 获取项数量.
/// @param hEle  元素句柄.
/// @return 返回项数量.
int WINAPI XComboBox_GetItemCount(HELE hEle) //获取项数量
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	return XArray_GetCount(COMBOBOX(hEle)->hArrayStr);
}

XC_API void WINAPI XComboBox_PopupDropDownList(HELE hEle)
{
	comboBox_  *pComboBox = COMBOBOX(hEle);

	pComboBox->button_.state = STATE_DOWN;
	XEle_RedrawEle(hEle);
	//弹出下拉列表
	XEle_SetFocus(hEle, TRUE);
	ComboBox_PopupDropDownList(hEle);
	XEle_SetCapture(hEle);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

/// @brief 启用可编辑显示的文本内容.
/// @param hEle  元素句柄.
/// @param bEdit TRUE可编辑,否则相反.
void WINAPI XComboBox_EnableEdit(HELE hEle, BOOL bEdit)  //启动编辑内容
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	COMBOBOX(hEle)->bEdit = bEdit;
	XEdit_SetReadOnly(hEle, !bEdit);
}

/// @brief 设置下拉列表高度.
/// @param hEle  元素句柄.
/// @param height 高度.
void WINAPI XComboBox_SetListHeight(HELE hEle, int height)  //设置下拉列表高度
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	COMBOBOX(hEle)->heights = height;
}

/// @brief 设置下拉按钮宽度.
/// @param hEle 元素句柄
/// @param width 下拉按钮宽度
void WINAPI XComboBox_SetButtonWidth(HELE hEle, int width) //设置下拉按钮宽度
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	XSView_SetSpacing(hEle, 2, 2, 19, 2);
	ComboBox_Adjust(hEle);
}

/// @brief 设置项用户数据.
/// @param hEle 元素句柄.
/// @param index 项索引(基于0索引).
/// @param data  用户数据.
void WINAPI XComboBox_SetItemData(HELE hEle, int index, void* data)
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	XArray_SetAt(COMBOBOX(hEle)->hArrayData, index, (void*)data);
}

/// @brief 获取下拉按钮宽度.
/// @param hEle 元素句柄
/// @return 下拉按钮宽度.
int WINAPI XComboBox_GetButtonWidth(HELE hEle) //获取下拉按钮宽度
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	return COMBOBOX(hEle)->button_.rcButton.right - COMBOBOX(hEle)->button_.rcButton.left;
}

/// @brief 设置鼠标离开状态显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
void WINAPI XComboBox_SetImageLeave(HELE hEle, HIMAGE hImage) //鼠标离开
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	XSView_SetImage(hEle, hImage);
}

/// @brief 设置鼠标在元素上停留状态时显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
void WINAPI XComboBox_SetImageStay(HELE hEle, HIMAGE hImage) //鼠标停留
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(COMBOBOX(hEle)->hImage_stay, hImage);
}

/// @brief 设置元素按下状态时显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
void WINAPI XComboBox_SetImageDown(HELE hEle, HIMAGE hImage) //鼠标按下
{
	IsComboBoxDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(COMBOBOX(hEle)->hImage_down, hImage);
}

void CALLBACK ComboBox_OnDestroy(HELE hEle) //销毁
{
	XComboBox_DeleteItemAll(hEle);
	XArray_Destroy(COMBOBOX(hEle)->hArrayStr);
	XArray_Destroy(COMBOBOX(hEle)->hArrayData);

	if (COMBOBOX(hEle)->hImage_stay) XImage_Destroy(COMBOBOX(hEle)->hImage_stay);
	if (COMBOBOX(hEle)->hImage_down) XImage_Destroy(COMBOBOX(hEle)->hImage_down);
}

//绘制背景
void ComboBox_DrawBk(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	switch (COMBOBOX(hEle)->button_.state)
	{
	case STATE_LEAVE:
	{
		if (SCROLLVIEW(hEle)->hImage_bk)
		{
			XDraw_HImageSuper_(hDraw, SCROLLVIEW(hEle)->hImage_bk, &rect);
		}
		else //绘制下拉按钮
			ComboBox_OnDrawButton(hEle, hDraw);
	}break;
	case STATE_STAY:
	{
		if (COMBOBOX(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw, COMBOBOX(hEle)->hImage_stay, &rect);
		}
		else //绘制下拉按钮
			ComboBox_OnDrawButton(hEle, hDraw);
	}
	break;
	case STATE_DOWN:
	{
		if (COMBOBOX(hEle)->hImage_down)
		{
			XDraw_HImageSuper_(hDraw, COMBOBOX(hEle)->hImage_down, &rect);
		}
		else //绘制下拉按钮
			ComboBox_OnDrawButton(hEle, hDraw);
	}
	break;
	}

	if (((ele_*)hEle)->bBorder)
	{
		COLORREF color = ((ele_*)hEle)->borderColor;
		if (XEle_IsFocus(hEle) || EDIT(hEle)->bMouseStay || COMBOBOX(hEle)->hPopupWnd)
		{
			HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(GetRValue(color) + 80, GetGValue(color) + 80, GetBValue(color) + 80));
			HGDIOBJ hOld = XDraw_SelectObject_(hDraw, hPen);
			if (SCROLLVIEW(hEle)->left > 0)
			{
				XDraw_MoveToEx_(hDraw, 0, 0, NULL);
				XDraw_LineTo_(hDraw, 0, rect.bottom);
			}
			if (SCROLLVIEW(hEle)->top > 0)
			{
				XDraw_MoveToEx_(hDraw, 0, 0, NULL);
				XDraw_LineTo_(hDraw, rect.right, 0);
			}
			if (SCROLLVIEW(hEle)->right > 0)
			{
				XDraw_MoveToEx_(hDraw, rect.right - 1, 0, NULL);
				XDraw_LineTo_(hDraw, rect.right - 1, rect.bottom);
			}
			if (SCROLLVIEW(hEle)->bottom > 0)
			{
				XDraw_MoveToEx_(hDraw, 0, rect.bottom - 1, NULL);
				XDraw_LineTo_(hDraw, rect.right, rect.bottom - 1);
			}

			HPEN hPen2 = XDraw_CreatePen_(hDraw, PS_SOLID, 1, color);
			XDraw_SelectObject_(hDraw, hPen2);
			if (SCROLLVIEW(hEle)->left > 1)
			{
				XDraw_MoveToEx_(hDraw, 1, 1, NULL);
				XDraw_LineTo_(hDraw, 1, rect.bottom - 1);
			}
			if (SCROLLVIEW(hEle)->top > 1)
			{
				XDraw_MoveToEx_(hDraw, 1, 1, NULL);
				XDraw_LineTo_(hDraw, rect.right - 1, 1);
			}
			if (SCROLLVIEW(hEle)->right > 1)
			{
				XDraw_MoveToEx_(hDraw, rect.right - 2, 1, NULL);
				XDraw_LineTo_(hDraw, rect.right - 2, rect.bottom - 1);
			}
			if (SCROLLVIEW(hEle)->bottom > 1)
			{
				XDraw_MoveToEx_(hDraw, 1, rect.bottom - 2, NULL);
				XDraw_LineTo_(hDraw, rect.right - 1, rect.bottom - 2);
			}
		}
		else
		{
			HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, color);
			HGDIOBJ hOld = XDraw_SelectObject_(hDraw, hPen);
			if (SCROLLVIEW(hEle)->left > 0)
			{
				XDraw_MoveToEx_(hDraw, 0, 0, NULL);
				XDraw_LineTo_(hDraw, 0, rect.bottom);
			}
			if (SCROLLVIEW(hEle)->top > 0)
			{
				XDraw_MoveToEx_(hDraw, 0, 0, NULL);
				XDraw_LineTo_(hDraw, rect.right, 0);
			}
			if (SCROLLVIEW(hEle)->right > 0)
			{
				XDraw_MoveToEx_(hDraw, rect.right - 1, 0, NULL);
				XDraw_LineTo_(hDraw, rect.right - 1, rect.bottom);
			}
			if (SCROLLVIEW(hEle)->bottom > 0)
			{
				XDraw_MoveToEx_(hDraw, 0, rect.bottom - 1, NULL);
				XDraw_LineTo_(hDraw, rect.right, rect.bottom - 1);
			}
		}
	}
}

BOOL CALLBACK ComboBox_OnDraw(HELE hEle, HDRAW hDraw)
{
	ComboBox_DrawBk(hEle, hDraw);
	return TRUE;
}

BOOL CALLBACK ComboBox_OnDrawButton(HELE hEle, HDRAW hDraw) //绘制下拉按钮
{
	comboBox_ *pComboBox = COMBOBOX(hEle);
	RECT rect = pComboBox->button_.rcButton;
	rect.right -= 3;

	switch (COMBOBOX(hEle)->button_.state)
	{
	case STATE_LEAVE:
	{
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rect, hBrush);

		//绘制按钮下三角
		int left = rect.left + (rect.right - rect.left) / 2;
		int top = rect.top + (rect.bottom - rect.top) / 2;

		POINT  pt[3];
		pt[0].x = left;
		pt[0].y = top + 3;
		pt[1].x = left - 5;
		pt[1].y = top - 2;
		pt[2].x = left + 5;
		pt[2].y = top - 2;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);

		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FillRgn_(hDraw, hRgn, hBrush2);
	}
	break;
	case STATE_STAY:
	{
		RECT rcBer = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(200, 200, 200));
		XDraw_FrameRect_(hDraw, &rcBer, hBrush1);

		//按钮边框
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rect, hBrush2);

		//绘制按钮下三角
		int left = rect.left + (rect.right - rect.left) / 2;
		int top = rect.top + (rect.bottom - rect.top) / 2;

		POINT  pt[3];
		pt[0].x = left;
		pt[0].y = top + 3;
		pt[1].x = left - 5;
		pt[1].y = top - 2;
		pt[2].x = left + 5;
		pt[2].y = top - 2;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);

		HBRUSH hBrush3 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FillRgn_(hDraw, hRgn, hBrush3);
	}
	break;
	case STATE_DOWN:
	{
		RECT rcBer = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(200, 200, 200));
		XDraw_FrameRect_(hDraw, &rcBer, hBrush1);

		//按钮边框
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rect, hBrush2);

		//绘制按钮下三角
		int left = rect.left + (rect.right - rect.left) / 2;
		int top = rect.top + (rect.bottom - rect.top) / 2;
		top++;

		POINT  pt[3];
		pt[0].x = left;
		pt[0].y = top + 3;
		pt[1].x = left - 5;
		pt[1].y = top - 2;
		pt[2].x = left + 5;
		pt[2].y = top - 2;

		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);

		HBRUSH hBrush3 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FillRgn_(hDraw, hRgn, hBrush3);
	}
	break;
	}

	return TRUE;
}

BOOL CALLBACK ComboBox_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	comboBox_  *pComboBox = COMBOBOX(hEle);

	if (pComboBox->hPopupWnd)
	{
		//1转换到窗口坐标
		//2转换到下拉列表窗口坐标
		//3传递打牌下拉列表窗口

		POINT pt = *pPt;
		XEle_PointToNCWnd(hEle, &pt);
		ClientToScreen(XEle_GetHWnd(hEle), &pt);
		HWND hListHWND = XWnd_GetHWnd(pComboBox->hPopupWnd);
		ScreenToClient(hListHWND, &pt);

		//XTRACE("MouseMove x=%d ,y=%d \n",pt.x,pt.y);
		Wnd_OnMouseMove(pComboBox->hPopupWnd, flags, &pt);

		return TRUE;
	}

	if (PtInRect(&pComboBox->button_.rcButton, *pPt))
	{
		if (STATE_STAY != pComboBox->button_.state)
		{
			pComboBox->button_.state = STATE_STAY;
			XEle_RedrawEle(hEle);
		}
	}
	else
	{
		if (STATE_LEAVE != pComboBox->button_.state)
		{
			pComboBox->button_.state = STATE_LEAVE;
			XEle_RedrawEle(hEle);
		}
	}

	if (FALSE == pComboBox->bEdit) //不可以编辑
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CALLBACK ComboBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	comboBox_  *pComboBox = COMBOBOX(hEle);

	if (pComboBox->hPopupWnd)
	{
		//1转换到窗口坐标
		//2转换到下拉列表窗口坐标
		//3传递打牌下拉列表窗口

		POINT pt = *pPt;
		XEle_PointToNCWnd(hEle, &pt);
		ClientToScreen(XEle_GetHWnd(hEle), &pt);
		HWND hListHWND = XWnd_GetHWnd(pComboBox->hPopupWnd);
		ScreenToClient(hListHWND, &pt);

		RECT rcPopup;
		GetClientRect(hListHWND, &rcPopup);

		if (PtInRect(&rcPopup, pt))
		{
			Wnd_WindowProc(pComboBox->hPopupWnd, WM_LBUTTONDOWN, flags, MAKELPARAM(pt.x, pt.y));
		}
		else
		{
			ComboBox_DestroyPopupWnd(hEle);
		}
		return TRUE;
	}

	if (FALSE == pComboBox->bEdit)
	{
		pComboBox->button_.state = STATE_DOWN;
		XEle_RedrawEle(hEle);
		//弹出下拉列表
		XEle_SetFocus(hEle, TRUE);
		ComboBox_PopupDropDownList(hEle);
		XEle_SetCapture(hEle);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return TRUE;
	}
	else
	{
		if (PtInRect(&pComboBox->button_.rcButton, *pPt))
		{
			pComboBox->button_.state = STATE_DOWN;
			XEle_RedrawEle(hEle);

			//弹出下拉列表
			XEle_SetFocus(hEle, TRUE);
			ComboBox_PopupDropDownList(hEle);
			XEle_SetCapture(hEle);
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CALLBACK ComboBox_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	//	if(NULL==COMBOBOX(hEle)->hPopupWnd)
	//	{
	//		COMBOBOX(hEle)->button_.state=STATE_STAY;
	//		XEle_RedrawEle(hEle);
	//	}

	if (FALSE == COMBOBOX(hEle)->bEdit)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK ComboBox_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (NULL == COMBOBOX(hEle)->hPopupWnd)
		{
			if (STATE_LEAVE != COMBOBOX(hEle)->button_.state)
			{
				if (FALSE == XEle_IsFocus(hEle))
				{
					COMBOBOX(hEle)->button_.state = STATE_LEAVE;
					XEle_RedrawEle(hEle);
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK ComboBox_OnEventKillFocus(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (COMBOBOX(hEle)->hPopupWnd)
		{
			ComboBox_DestroyPopupWnd(hEle);
		}
		else
		{
			if (STATE_LEAVE != COMBOBOX(hEle)->button_.state)
			{
				COMBOBOX(hEle)->button_.state = STATE_LEAVE;
				XEle_RedrawEle(hEle);
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK ComboBox_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	if (COMBOBOX(hEle)->hPopupWnd)
		return TRUE;

	if (FALSE == COMBOBOX(hEle)->bEdit) //不可以编辑
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CALLBACK ComboBox_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	if (COMBOBOX(hEle)->hPopupWnd)
		return TRUE;

	if (FALSE == COMBOBOX(hEle)->bEdit) //不可以编辑
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK ComboBox_OnEventSetFocus(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (FALSE == COMBOBOX(hEle)->bEdit) //不可以编辑
		{
			return TRUE;
		}
	}
	return FALSE;
}

void ComboBox_Adjust(HELE hEle)
{
	//调整下拉按钮
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	comboBox_ *pObject = COMBOBOX(hEle);

	pObject->button_.rcButton.right = rect.right;
	pObject->button_.rcButton.left = rect.right - XSView_GetSpacingRight(hEle);
	pObject->button_.rcButton.top = XSView_GetSpacingTop(hEle) + 1;
	pObject->button_.rcButton.bottom = rect.bottom - XSView_GetSpacingBottom(hEle) - 1;
}

BOOL CALLBACK ComboBox_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		//调整下拉按钮
		ComboBox_Adjust(hEle);
	}
	return FALSE;
}

BOOL CALLBACK ComboBox_OnEventMouseWheel(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt)
{
	if (hEle == hEventEle)
	{
		comboBox_ *pComboBox = COMBOBOX(hEle);
		if (pComboBox->hPopupWnd)
		{
			HWND hListHWND = XWnd_GetHWnd(pComboBox->hPopupWnd);
			SendMessage(hListHWND, WM_MOUSEWHEEL, flags, MAKELPARAM(pPt->x, pPt->y));
		}
	}
	return FALSE;
}

void ComboBox_PopupDropDownList(HELE hEle) //弹出下拉列表
{
	comboBox_ *pObj = COMBOBOX(hEle);

	if ((GetTickCount() - pObj->listEndTime) < 200)
	{
		return;
	}

	int count = Array_GetCount(pObj->hArrayStr);
	RECT rc;
	POINT  pt = { 0,1 };
	XEle_PointToNCWnd(hEle, &pt);
	GetWindowRect(((ele_*)hEle)->pWindow->hWnd, &rc);
	int cx = ((ele_*)hEle)->rect.right - ((ele_*)hEle)->rect.left;
	int cy = 0;
	if (pObj->heights > pObj->height)
	{
		cy = pObj->heights;
	}
	else
	{
		cy = pObj->height*count;
		if (cy > 200) cy = 200;
	}
	if (cy < pObj->height) cy = pObj->height;

	pt.y += ((ele_*)hEle)->rect.bottom - ((ele_*)hEle)->rect.top;

	HWND hParentWnd = ((ele_*)hEle)->pWindow->hWnd;

	HWND hDesktop = GetDesktopWindow();
	ClientToScreen(hParentWnd, &pt);

	pObj->hPopupWnd = ComboBoxWnd_CreateWindow(pt.x, pt.y, cx, cy + 4, hParentWnd, hEle);

	XEle_SetFocus(((comboBoxWindow_*)pObj->hPopupWnd)->hListBox, TRUE);
	Ele_SendEvent(hEle, XE_COMBOBOX_POPUP_LIST, (WPARAM)pObj->hPopupWnd, (LPARAM)((comboBoxWindow_*)pObj->hPopupWnd)->hListBox);

	HWND hWnd = XWnd_GetHWnd(pObj->hPopupWnd);

	HWND hWndT = SetParent(hWnd, hDesktop);

	SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER/* | SWP_NOACTIVATE*/ | SWP_SHOWWINDOW);//SWP_NOACTIVATE

	((window_*)pObj->hPopupWnd)->pFocus = (ele_*)((comboBoxWindow_*)pObj->hPopupWnd)->hListBox;
}

void ComboBox_DestroyPopupWnd(HELE hEle)  //销毁弹出窗口
{
	if (COMBOBOX(hEle)->hPopupWnd)
	{
		XEle_ReleaseCapture(hEle);
		HWND hwnd = ((window_*)(COMBOBOX(hEle)->hPopupWnd))->hWnd;
		::PostMessage(hwnd, WM_CLOSE, 0, 0);
		COMBOBOX(hEle)->hPopupWnd = NULL;

		if (STATE_LEAVE != COMBOBOX(hEle)->button_.state)
		{
			COMBOBOX(hEle)->button_.state = STATE_LEAVE;
			XEle_RedrawEle(hEle);
		}

		//记录下拉列表最后关闭时间
		COMBOBOX(hEle)->listEndTime = GetTickCount();

		//发送弹出下拉列表关闭事件
		Ele_SendEvent(hEle, XE_COMBOBOX_EXIT_LIST, 0, 0);
	}
}
///@}