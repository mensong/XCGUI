/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup pane 窗格元素(Pane)
/// @ingroup groupElements
/// 窗格接口列表
/// @{

/// @brief   创建窗格元素
/// @param pTitle  窗格标题.
/// @param hFrameWnd 框架窗口句柄.
/// @return 返回窗格句柄
HELE WINAPI XPane_Create(wchar_t *pTitle, HWINDOW hFrameWnd)
{
	layoutPane_ *pNew = (layoutPane_*)malloc(sizeof(layoutPane_));
	if (pNew)
	{
		memset(pNew, 0, sizeof(layoutPane_));

		Pane_Init((HELE)pNew, 10, 10, 100, 100, XC_PANE, pTitle, hFrameWnd);

		return (HELE)pNew;
	}
	return NULL;
}

void Pane_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_PANE);

	layoutPane_ *pPane = (layoutPane_*)hEle;

	pPane->captionHeight = 20;
	pPane->hTitle = XStr_Create(pTitle);
	pPane->state = pane_state_lock;
	pPane->left = 1;
	pPane->top = 1;
	pPane->right = 1;
	pPane->bottom = 1;
	pPane->bFixedSize = FALSE;
	pPane->bInFrame = FALSE;

	pPane->hBtnClose = XBtn_Create(100, 2, 15, 15, 0, hEle);
	pPane->hAutoHide = XBtn_Create(80, 2, 15, 15, 0, hEle);
	pPane->hBtnMenu = XBtn_Create(60, 2, 15, 15, 0, hEle);

	XEle_EnableFocus(pPane->hBtnClose, FALSE);
	XEle_EnableFocus(pPane->hAutoHide, FALSE);
	XEle_EnableFocus(pPane->hBtnMenu, FALSE);

	pPane->pCell = Cell_Create(NULL, hEle, align_any);
	pPane->pCell->type = cell_type_pane;

	XEle_RegisterEvent(pPane->hBtnClose, XE_BNCLICK, Pane_Btn_Close);
	XEle_RegisterEvent(pPane->hAutoHide, XE_BNCLICK, Pane_Btn_Lock);
	XEle_RegisterEvent(pPane->hBtnMenu, XE_BNCLICK, Pane_Btn_Menu);

	XEle_RegisterMessage(pPane->hBtnClose, XM_PAINT, Pane_BtnClose_OnEleDraw);
	XEle_RegisterMessage(pPane->hAutoHide, XM_PAINT, Pane_BtnLock_OnEleDraw);
	XEle_RegisterMessage(pPane->hBtnMenu, XM_PAINT, Pane_BtnMenu_OnEleDraw);

	XEle_RegisterMessage(hEle, XM_PAINT, Pane_OnEleDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, Pane_EleLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, Pane_EleLButtonUp);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, Pane_EleMouseMove);

	XEle_RegisterEvent(hEle, XE_DESTROY, Pane_OnEventDestroy);
	XEle_RegisterEvent(hEle, XE_SIZE, Pane_OnSize);
	XEle_RegisterEvent(hEle, XE_MENUSELECT, Pane_OnEventMenuSelect);

	//	XEle_RegisterEvent(hEle,XE_SETFOCUS,Pnae_OnEventSetFocus);
	//	XEle_RegisterEvent(hEle,XE_KILLFOCUS,Pnae_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_SHOW, Pane_OnEventShow);

	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, Pane_EventMouseLeave);
}

void Pane_AdjustLayout(HELE hEle)
{
	HWINDOW hWindow = XEle_GetHWindow(hEle);
	if (XC_FLOATWND == XC_GetObjectType(hWindow))
	{
		RECT rect;
		XEle_GetClientRect(hEle, &rect);
		layoutPane_ *pPane = (layoutPane_*)hEle;
		if (pPane->hView)
		{
			RECT rc = rect;
			rc.left = pPane->left;
			rc.top += pPane->top;
			rc.right -= pPane->right;
			rc.bottom -= pPane->bottom;
			XEle_SetRect(pPane->hView, &rc);
		}
	}
	else
	{
		Pane_AdjustLayout2(hEle);
	}
}

void Pane_AdjustLayout2(HELE hEle)
{
	layoutPane_ *pPane = (layoutPane_*)hEle;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	int x = rect.right - rect.left - 5;
	int y = 2;

	RECT rc;
	rc.top = 2;
	rc.bottom = 17;
	if (pPane->hBtnClose)
	{
		x -= 15;
		rc.left = x;
		rc.right = x + 15;
		XEle_SetRect(pPane->hBtnClose, &rc);
	}

	if (pPane->hAutoHide)
	{
		x -= 15;
		rc.left = x;
		rc.right = x + 15;
		XEle_SetRect(pPane->hAutoHide, &rc);
	}
	if (pPane->hBtnMenu)
	{
		x -= 15;
		rc.left = x;
		rc.right = x + 15;
		XEle_SetRect(pPane->hBtnMenu, &rc);
	}

	int top = pPane->captionHeight + pPane->top;
	RECT rcEle;
	rcEle.left = pPane->left;
	rcEle.right = rect.right - pPane->right;
	if (pPane->hMenuBar)
	{
		RECT rcMenuBar;
		XEle_GetClientRect(pPane->hMenuBar, &rcMenuBar);

		rcEle.top = top;
		rcEle.bottom = top + (rcMenuBar.bottom - rcMenuBar.top);

		XEle_SetRect(pPane->hMenuBar, &rcEle);
		top = rcEle.bottom;
	}
	if (pPane->hToolBar)
	{
		RECT rcToolBar;
		XEle_GetClientRect(pPane->hToolBar, &rcToolBar);

		rcEle.top = top;
		rcEle.bottom = top + (rcToolBar.bottom - rcToolBar.top);

		XEle_SetRect(pPane->hToolBar, &rcEle);
		top = rcEle.bottom;
	}

	if (pPane->hView)
	{
		//	RECT rc;
		//	rcEle.left=pPane->left;
		rcEle.top = top;
		//	rcEle.right=rect.right-pPane->right;
		rcEle.bottom = rect.bottom - pPane->bottom;

		XEle_SetRect(pPane->hView, &rcEle);
	}
}

/// @brief   获取窗格标题
/// @param hEle  窗格元素句柄.
/// @return 返回窗格标题.
wchar_t* WINAPI XPane_GetTitle(HELE hEle)
{
	IsPaneDebug(hEle, __FUNCTION__);

	if (((layoutPane_*)hEle)->hTitle)
		return XStr_GetBuffer(((layoutPane_*)hEle)->hTitle);
	return NULL;
}

/// @brief   隐藏窗格
/// @param hEle  窗格元素句柄.
void WINAPI XPane_Hide(HELE hEle)
{
	IsPaneDebug(hEle, __FUNCTION__);

	Pane_EnableLayout(hEle, FALSE); //从布局中排除

	layoutPane_ *pPane = (layoutPane_*)hEle;

	if (pane_state_lock == pPane->state)
	{
		//判断为窗格或组成员...
		if (align_group_member == pPane->pCell->align)
		{
			//从TAB中移除
			layoutCell_ *pParentCell = pPane->pCell->pParentCell;

			int count = XTabBar_GetLabelCount(pParentCell->hTabBar);
			int index = XTabBar_GetPageIndex(pParentCell->hTabBar, hEle);
			if (1 == count)
			{
				XTabBar_DeleteLabelAll(pParentCell->hTabBar);
			}
			else if (2 == count)
			{
				if (0 == index)
				{
					HELE hEleT = XTabBar_GetLabelPage(pParentCell->hTabBar, 1);
					XEle_ShowEle(hEleT, TRUE);
				}
				else
				{
					HELE hEleT = XTabBar_GetLabelPage(pParentCell->hTabBar, 0);
					XEle_ShowEle(hEleT, TRUE);
				}
				XTabBar_DeleteLabelAll(pParentCell->hTabBar);
			}
			else if (count > 2)
			{
				XTabBar_DeleteLabel(pParentCell->hTabBar, index);
			}
			pPane->bInFrame = FALSE;
		}
		else  //独立窗格
		{
			pPane->bInFrame = FALSE;
		}
	}
	else if (pane_state_dock == pPane->state)
	{
		pPane->bInFrame = FALSE;
	}

	XEle_ShowEle(hEle, FALSE); //隐藏
	((layoutPane_*)hEle)->state = pane_state_hide;
}

/// @brief   将窗格停靠到码头.
/// @param hEle  窗格元素句柄.
void WINAPI XPane_Dock(HELE hEle) //停靠窗格
{
	IsPaneDebug(hEle, __FUNCTION__);
	HWINDOW     hWindow = XEle_GetHWindow(hEle);
	frameWnd_   *pFrame = (frameWnd_*)hWindow;
	layoutPane_ *pPane = (layoutPane_*)hEle;
	layoutCell_ *pCell = pPane->pCell;

	//窗格组
	if (align_group_member == pCell->align)
	{
		layoutCell_ *pGroupCell = pCell->pParentCell;
		XTabBar_DeleteLabelAll(pGroupCell->hTabBar);

		int count = XArray_GetCount(pGroupCell->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, i);
			if (((layoutPane_*)pChild->hPane)->bInFrame)
			{
				((layoutPane_*)pChild->hPane)->bInFrame = FALSE;
				((layoutPane_*)pChild->hPane)->state = pane_state_dock;
			}
		}

		XEle_ShowEle(pGroupCell->hTabBar, FALSE);
		FrameWnd_AddPierGroup((HWINDOW)pFrame, pGroupCell);
	}
	else	//单窗格
	{
		Pane_EnableLayout(hEle, FALSE);
		pPane->state = pane_state_dock;
		XEle_ShowEle(hEle, FALSE);
		FrameWnd_AddPier((HWINDOW)pFrame, pCell);
	}
}

BOOL Pane_CellInFrame(layoutCell_ *pFrameCell, layoutCell_ *pCell) //检查单元格是否在框架窗口内
{
	if (pFrameCell)
	{
		if (pFrameCell == pCell)
			return TRUE;

		if (Pane_CellInFrame(pFrameCell->pCell1, pCell))
			return TRUE;
		if (Pane_CellInFrame(pFrameCell->pCell2, pCell))
			return TRUE;
	}
	return FALSE;
}
void Pane_EnableLayout(HELE hEle, BOOL bEnable)
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	if (bEnable)
	{
		//pPane->state=pane_state_any;
	}
	else
	{
		//	pPane->state=pane_state_any;
	}
	pPane->bInFrame = bEnable;
}

/// @brief   锁定窗格到框架窗口.
/// @param hEle  窗格元素句柄.
void WINAPI XPane_Lock(HELE hEle) //锁定窗格
{
	IsPaneDebug(hEle, __FUNCTION__);

	layoutPane_ *pPane = (layoutPane_*)hEle;

	HWINDOW hFrame = XEle_GetHWindow(hEle);
	if (XC_FRAMEWND != XC_GetObjectType(hFrame))
		return;

	frameWnd_ *pFrame = (frameWnd_*)hFrame;
	//检查还原最佳锁定位置
	layoutCell_ *pCell = NULL;
	if (align_group_member == pPane->pCell->align) //原来为组成员
	{
		Pane_Lock_group(hEle);
	}
	else
	{
		Pane_Lock_pane(hEle);
	}
}

void Pane_Lock_group(HELE hEle)
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	if (pane_state_dock == pPane->state)
	{
		//从码头移除窗格
		FrameWnd_RemovePierGroup(hFrame, hEle);
		layoutCell_ *pCellGroup = pPane->pCell->pParentCell;

		XTabBar_DeleteLabelAll(pCellGroup->hTabBar);

		//还原到布局

		//计算显示成员数量
		int countShow = 0;
		int count = XArray_GetCount(pCellGroup->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellGroup->hArrayList, i);
			layoutPane_ *pPane = (layoutPane_*)pChild->hPane;
			if (pane_state_dock == pPane->state || pane_state_lock == pPane->state)
			{
				countShow++;
			}
		}

		if (0 == countShow)
		{
			MessageBox(NULL, L"窗格锁定错误:008", L"炫彩界面库-错误提示", 0);//错误
			exit(0);
		}
		else if (1 == countShow)
		{
			//不需要显示TAB条
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellGroup->hArrayList, i);
				layoutPane_ *pPane = (layoutPane_*)pChild->hPane;
				if (pane_state_dock == pPane->state || pane_state_lock == pPane->state)
				{
					Pane_EnableLayout(pChild->hPane, TRUE);
					((layoutPane_*)pChild->hPane)->state = pane_state_lock;
					XEle_ShowEle(pChild->hPane, TRUE);
					break;
				}
			}
		}
		else  //显示TAB条
		{
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellGroup->hArrayList, i);
				layoutPane_ *pPane = (layoutPane_*)pChild->hPane;
				if (pane_state_dock == pPane->state || pane_state_lock == pPane->state)
				{
					Pane_EnableLayout(pChild->hPane, TRUE);
					((layoutPane_*)pChild->hPane)->state = pane_state_lock;

					XTabBar_AddLabel(pCellGroup->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);

					HELE hBtn = XTabBar_GetLabel(pCellGroup->hTabBar, i);
					XEle_SetUserData(hBtn, (int)pChild);
					XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
					XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
					XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
					XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
				}
			}
			XEle_ShowEle(pCellGroup->hTabBar, TRUE);
		}
	}
	else if (pane_state_hide == pPane->state)
	{
		XPane_Show(hEle);
	}
}

void Pane_Lock_pane(HELE hEle)
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	if (pane_state_dock == pPane->state)
	{
		//从码头移除窗格
		FrameWnd_RemovePier(hFrame, hEle);

		//增加到框架布局
		Pane_EnableLayout(hEle, TRUE);
		pPane->state = pane_state_lock;
		XEle_ShowEle(hEle, TRUE);
	}
	else if (pane_state_hide == pPane->state)
	{
		//增加到框架布局
		Pane_EnableLayout(hEle, TRUE);
		XPane_Show(hEle);
	}
}

int Pane_Lock_scale(layoutPane_ *pPane, layoutCell_ *pCell) //计算比例
{
	//计算比例
	int scale = 50;
	switch (pPane->pCell->align)
	{
	case align_left:
	case align_any:
		if (pCell)
		{
			double t1 = (double)(pPane->pCell->rect.right - pPane->pCell->rect.left);
			double t2 = (double)(pCell->rect.right - pCell->rect.left);

			if (0 != t1 && 0 != t2)
			{
				scale = (int)((t1 / t2) * 100);
				if (scale >= 50)
					scale = 50;
			}
		}
		break;
	case align_top:
		if (pCell)
		{
			double t1 = (double)(pPane->pCell->rect.bottom - pPane->pCell->rect.top);
			double t2 = (double)(pCell->rect.bottom - pCell->rect.top);

			if (0 != t1 && 0 != t2)
			{
				scale = (int)((t1 / t2) * 100);
				if (scale >= 50)
					scale = 50;
			}
		}
		break;
	case align_right:

		if (pCell)
		{
			double t1 = (double)(pPane->pCell->rect.right - pPane->pCell->rect.left);
			double t2 = (double)(pCell->rect.right - pCell->rect.left);
			if (0 != t1 && 0 != t2)
			{
				scale = (int)((t1 / t2) * 100);
				if (scale >= 50)
					scale = 50;
			}
		}
		break;
	case align_bottom:
		if (pCell)
		{
			double t1 = (double)(pPane->pCell->rect.bottom - pPane->pCell->rect.top);
			double t2 = (double)(pCell->rect.bottom - pCell->rect.top);
			if (0 != t1 && 0 != t2)
			{
				scale = (int)((t1 / t2) * 100);
				if (scale >= 50)
					scale = 50;
			}
		}break;
	}
	return scale;
}

/// @brief   弹出窗格,当在码头上.
/// @param hEle  窗格元素句柄.
void WINAPI XPane_popup(HELE hEle) //弹出窗格,当在码头上
{
	IsPaneDebug(hEle, __FUNCTION__);

	FrameWnd_PierPopupPane(XEle_GetHWindow(hEle), hEle);
}

/// @brief  显示隐藏的窗格.
/// @param hEle  窗格元素句柄.
void WINAPI XPane_Show(HELE hEle)     //隐藏-显示浮动窗格
{
	IsPaneDebug(hEle, __FUNCTION__);
	layoutPane_ *pPane = (layoutPane_*)hEle;

	if (pane_state_float == pPane->state)
	{
		HWND hWnd = XEle_GetHWnd(hEle);
		if (NULL == hWnd) return;
		if (FALSE == IsWindowVisible(hWnd))
			ShowWindow(hWnd, SW_SHOW);
		return;
	}

	//前置组成员显示
	if (align_group_member == pPane->pCell->align)
	{
		if (cell_type_pane == pPane->pCell->type)
		{
			if (pPane->bInFrame)
			{
				int index = XTabBar_GetPageIndex(pPane->pCell->pParentCell->hTabBar, hEle);
				XTabBar_SetSelect(pPane->pCell->pParentCell->hTabBar, index);
				return;
			}
		}
	}

	XEle_ShowEle(hEle, TRUE);

	//显示被框架禁用的窗格
	if (pPane->bInFrame)
		return;

	Pane_EnableLayout(hEle, TRUE);
	pPane->state = pane_state_lock;

	//如果为组成员
	if (align_group_member == pPane->pCell->align)
	{
		if (cell_type_pane == pPane->pCell->type)
		{
			int count = XTabBar_GetLabelCount(pPane->pCell->pParentCell->hTabBar);
			if (0 == count) //当前没有显示TAB条
			{
				int countPane = 0;
				count = XArray_GetCount(pPane->pCell->pParentCell->hArrayList);
				for (int i = 0; i < count; i++)
				{
					layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pPane->pCell->pParentCell->hArrayList, i);
					if (((layoutPane_*)pChild->hPane)->bInFrame)
					{
						countPane++;
					}
				}

				if (1 == countPane)
				{
					//XEle_ShowEle(hEle,TRUE);
				}
				else if (2 == countPane)
				{
					for (int i = 0; i < count; i++)
					{
						layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pPane->pCell->pParentCell->hArrayList, i);
						if (((layoutPane_*)pChild->hPane)->bInFrame)
						{
							int index = XTabBar_AddLabel(pPane->pCell->pParentCell->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);
							if (hEle == pChild->hPane)
								XTabBar_SetSelect(pPane->pCell->pParentCell->hTabBar, index);

							HELE hBtn = XTabBar_GetLabel(pPane->pCell->pParentCell->hTabBar, index);

							XEle_SetUserData(hBtn, (int)pChild);

							XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
							XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
							XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
							XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
						}
					}
				}
			}
			else
			{
				int index = XTabBar_AddLabel(pPane->pCell->pParentCell->hTabBar, XPane_GetTitle(hEle), hEle);
				XTabBar_SetSelect(pPane->pCell->pParentCell->hTabBar, index);

				HELE hBtn = XTabBar_GetLabel(pPane->pCell->pParentCell->hTabBar, index);

				XEle_SetUserData(hBtn, (int)pPane->pCell);

				XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
				XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
				XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
				XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
			}
		}
	}
	else if (cell_type_pane == pPane->pCell->type)
	{

	}
}

/// @brief  获取窗格所属组,如果没有组返回空.
/// @param hEle  窗格元素句柄.
/// @return 返回窗格组句柄.
HPANE_GROUP WINAPI XPane_GetGroup(HELE hEle) //获取窗格所属组,如果没有组返回空
{
	IsPaneDebug(hEle, __FUNCTION__);
	if (align_group_member == ((layoutPane_*)hEle)->pCell->align)
	{
		layoutCell_ *pParentCell = ((layoutPane_*)hEle)->pCell->pParentCell;
		if (pParentCell && cell_type_group == pParentCell->type)
		{
			return (HPANE_GROUP)pParentCell;
		}
	}
	return NULL;
}

/// @brief  获取窗格状态.
/// @param hEle  窗格元素句柄.
/// @return 返回窗格状态.
pane_state_ WINAPI XPane_GetState(HELE hEle) //获取状态
{
	IsPaneDebug(hEle, __FUNCTION__);

	HWINDOW hWindow = XEle_GetHWindow(hEle);
	if (hWindow && XC_FLOATWND == XC_GetObjectType(hWindow))
	{
		return pane_state_float;
	}
	return ((layoutPane_*)hEle)->state;
}

/// @brief  拖动窗格.
/// @param hEle  窗格元素句柄.
/// @param pPtDown 鼠标在窗格上位置.
void WINAPI XPane_DragPane(HELE hEle, POINT *pPtDown) //拖动窗格
{
	IsPaneDebug(hEle, __FUNCTION__);

	HWINDOW hWindow = XEle_GetHWindow(hEle);

	if (pane_state_lock == ((layoutPane_*)hEle)->state)
	{
		FrameWnd_DragPane(hWindow, ((layoutPane_*)hEle)->pCell, pPtDown);
	}
}

/// @brief  拖动窗格组.
/// @param hEle  窗格元素句柄.
/// @param pPtDown 鼠标在窗格上位置.
void WINAPI XPane_DragGroup(HELE hEle, POINT *pPtDown)  //拖动窗格组
{
	IsPaneDebug(hEle, __FUNCTION__);

	HWINDOW hWindow = XEle_GetHWindow(hEle);

	if (pane_state_lock == ((layoutPane_*)hEle)->state)
	{
		FrameWnd_DragGroup(hWindow, ((layoutPane_*)hEle)->pCell, pPtDown);
	}
}

/// @brief  浮动窗格.
/// @param hEle  窗格元素句柄.
void WINAPI XPane_FloatPane(HELE hEle) //浮动窗格
{
	IsPaneDebug(hEle, __FUNCTION__);

	HWINDOW hWindow = XEle_GetHWindow(hEle);
	if (pane_state_float != ((layoutPane_*)hEle)->state)
	{
		FrameWnd_FloatPane(hWindow, ((layoutPane_*)hEle)->pCell);
	}
}

/// @brief  设置窗格视图绑定元素,以便当窗格大小改变时自动调整视图坐标.
/// @param hEle  窗格元素句柄.
/// @param hView  视图元素句柄.
void WINAPI XPane_SetView(HELE hEle, HELE hView)
{
	IsPaneDebug(hEle, __FUNCTION__);
	IsEleDebug(hView, __FUNCTION__);
	((layoutPane_*)hEle)->hView = hView;
}

/// @brief  设置窗格工具条,以便当窗格大小改变时自动调整工具条坐标.
/// @param hEle  窗格元素句柄.
/// @param hToolBar  工具条元素句柄.
void WINAPI XPane_SetToolBar(HELE hEle, HELE hToolBar) //设置工具条
{
	IsPaneDebug(hEle, __FUNCTION__);
	IsToolBarDebug(hToolBar, __FUNCTION__);
	((layoutPane_*)hEle)->hToolBar = hToolBar;
}

/// @brief  设置窗格菜单条,以便当窗格大小改变时自动调整菜单条坐标.
/// @param hEle  窗格元素句柄.
/// @param hMenuBar  菜单条元素句柄.
void WINAPI XPane_SetMenuBar(HELE hEle, HELE hMenuBar) //设置菜单条
{
	IsPaneDebug(hEle, __FUNCTION__);
	IsMenuBarDebug(hMenuBar, __FUNCTION__);
	((layoutPane_*)hEle)->hMenuBar = hMenuBar;
}

/// @brief  设置窗格视图与边框的间隔.
/// @param hEle  窗格元素句柄.
/// @param left   左间隔.
/// @param top    上间隔.
/// @param right  右间隔.
/// @param bottom 下间隔.
void WINAPI XPane_SetSpacing(HELE hEle, int left, int top, int right, int bottom)
{
	IsPaneDebug(hEle, __FUNCTION__);
	((layoutPane_*)hEle)->left = left;
	((layoutPane_*)hEle)->top = top;
	((layoutPane_*)hEle)->right = right;
	((layoutPane_*)hEle)->bottom = bottom;
	Pane_AdjustLayout(hEle);
}

/// @brief  启用或关闭窗格固定大小功能;当窗口大小改变时,该窗格宽度或高度不改变.
/// @param hEle  窗格元素句柄.
/// @param bFixedSize 固定大小TRUE,否则相反.
void WINAPI XPane_SetFixedSize(HELE hEle, BOOL bFixedSize) //设置窗格固定大小,如果为-1非固定大小
{
	IsPaneDebug(hEle, __FUNCTION__);
	((layoutPane_*)hEle)->bFixedSize = bFixedSize;
}

/// @brief  设置窗格标题.
/// @param hEle  窗格元素句柄.
/// @param pTitle 窗格标题.
void WINAPI XPane_SetTitle(HELE hEle, wchar_t *pTitle)
{
	IsPaneDebug(hEle, __FUNCTION__);
	XStr_SetString(((layoutPane_*)hEle)->hTitle, pTitle);

	if (pane_state_float == ((layoutPane_*)hEle)->state)
	{
		HWINDOW hWindow = XEle_GetHWindow(hEle);
		XWnd_SetWindowText(hWindow, pTitle);
	}
}

/// @brief  激活窗格,当窗格在框架内有效.
/// @param hEle  窗格元素句柄.
/// @param bActivate 激活TRUE,否则相反.
void WINAPI XPane_SetActivate(HELE hEle, BOOL bActivate) //激活窗格
{
	IsPaneDebug(hEle, __FUNCTION__);
	if (NULL == ((ele_*)hEle)->pWindow)
		return;

	//判断父窗口类型
	HWINDOW hWindow = (HWINDOW)((ele_*)hEle)->pWindow;

	int type = XC_GetObjectType(hWindow);

	if (XC_FRAMEWND == type)
	{
		frameWnd_ *pFrame = (frameWnd_*)((ele_*)hEle)->pWindow;
		if (bActivate)
		{
			if (FALSE == XEle_IsShowEle(hEle)) //显示的窗格才能激活
				return;

			if (hEle != pFrame->hPaneActivate)
			{
				HELE  hDrawEle = NULL;
				if (pFrame->hPaneActivate)
				{
					((layoutPane_*)pFrame->hPaneActivate)->bActivate = FALSE;
					hDrawEle = pFrame->hPaneActivate;
				}

				pFrame->hPaneActivate = hEle;
				((layoutPane_*)pFrame->hPaneActivate)->bActivate = TRUE;

				if (hDrawEle)
					XEle_RedrawEle(hDrawEle);
				XEle_RedrawEle(hEle);
				//	XTRACE("激活 \n");
			}
		}
		else
		{
			if (hEle == pFrame->hPaneActivate)
			{
				((layoutPane_*)pFrame->hPaneActivate)->bActivate = FALSE;
				HELE hDrawEle = pFrame->hPaneActivate;
				pFrame->hPaneActivate = NULL;
				XEle_RedrawEle(hDrawEle);
				//	XTRACE("取消激活 \n");
			}
		}
		return;
	}

	if (XC_FLOATWND == type) //目前浮动窗格不处理
	{
	}
}

/// @brief  判断窗格是否激活,当窗格在框架内有效.
/// @param hEle  窗格元素句柄.
/// @return 如果是活动窗格返回TRUE,否则相反.
BOOL WINAPI XPane_IsActivate(HELE hEle) //判断窗格是否激活,当窗格在框架内有效
{
	IsPaneDebug(hEle, __FUNCTION__);
	return ((layoutPane_*)hEle)->bActivate;
}

/// @brief  设置窗格标题栏高度.
/// @param hEle  窗格元素句柄.
/// @param height 标题栏高度.
void WINAPI XPane_SetCaptionHeight(HELE hEle, int height)  //设置标题栏高度
{
	IsPaneDebug(hEle, __FUNCTION__);
	((layoutPane_*)hEle)->captionHeight = height;
}

/// @brief  获取窗格标题栏高度.
/// @param hEle  窗格元素句柄.
/// @return 标题栏高度.
int WINAPI XPane_GetCaptionHeight(HELE hEle)  //获取标题栏高度
{
	IsPaneDebug(hEle, __FUNCTION__);
	return ((layoutPane_*)hEle)->captionHeight;
}

/// @brief  获取关闭按钮.
/// @param hEle  窗格元素句柄.
/// @return 返回关闭按钮.
HELE WINAPI XPane_GetButtonClose(HELE hEle) //获取关闭按钮
{
	IsPaneDebug(hEle, __FUNCTION__);
	return ((layoutPane_*)hEle)->hBtnClose;
}

/// @brief  获取锁定按钮.
/// @param hEle  窗格元素句柄.
/// @return 返回锁定按钮.
HELE WINAPI XPane_GetButtonLock(HELE hEle) //获取锁定按钮
{
	IsPaneDebug(hEle, __FUNCTION__);
	return ((layoutPane_*)hEle)->hAutoHide;
}

/// @brief  获取下拉菜单按钮.
/// @param hEle  窗格元素句柄.
/// @return 返回下拉菜单按钮.
HELE WINAPI XPane_GetButtonMenu(HELE hEle) //获取菜单按钮
{
	IsPaneDebug(hEle, __FUNCTION__);
	return ((layoutPane_*)hEle)->hBtnMenu;
}

/// @}

layoutCell_* Pane_GetCell(HELE hEle)
{
	return ((layoutPane_*)hEle)->pCell;
}

BOOL WINAPI XPane_Destroy(HELE hEle) //销毁窗格 
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	if (pPane->pCell)		//从框架中移除
	{
		HWINDOW hWindow = XEle_GetHWindow(hEle);
		if (XC_FRAMEWND == XC_GetObjectType(hWindow)) //框架窗口
		{
			if (cell_type_pane == pPane->pCell->type)
			{
				if (align_group_member == pPane->pCell->align)
				{
					FrameWnd_RemoveCell_GroupMenber(hWindow, pPane->pCell);
				}
				else
				{
					FrameWnd_RemoveCell_Pane(hWindow, pPane->pCell);
				}
			}
			else if (cell_type_group == pPane->pCell->type)
			{
				FrameWnd_RemoveCell_Group(hWindow, pPane->pCell);
			}
			else
				return FALSE;

			Cell_Destroy(pPane->pCell);
			return TRUE;
		}
		else //浮动窗口
		{
			floatWindow_ *pFloatWnd = (floatWindow_*)hWindow;
			if (pFloatWnd->pCell == pPane->pCell)
			{
				if (cell_type_pane == pPane->pCell->type)
				{
					DestroyWindow(XWnd_GetHWnd(hWindow));
				}
			}
			else if (cell_type_pane == pPane->pCell->type)//组成员
			{
				if (align_group_member != pPane->pCell->align)
					return FALSE;

				layoutCell_  *pGroupCell = pPane->pCell->pParentCell;

				if (NULL == pGroupCell)
					return FALSE;

				if (cell_type_group != pGroupCell->type)
					return FALSE;

				if (pFloatWnd->pCell != pGroupCell)
					return FALSE;


				int countPane = XArray_GetCount(pGroupCell->hArrayList);

				if (countPane < 2)
				{
					return FALSE;
				}if (2 == countPane) //2个组成员
				{
					XArray_Delete(pGroupCell->hArrayList, pPane->pCell);
					Cell_Destroy(pPane->pCell);

					XTabBar_DeleteLabelAll(pGroupCell->hTabBar);
					pGroupCell->hTabBar = NULL;

					layoutCell_ *pNewCell = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, 0);

					Cell_Destroy(pGroupCell);

					pNewCell->pParentCell = NULL;
					pNewCell->align = align_any;
					pFloatWnd->pCell = pNewCell;
					XEle_Destroy(hEle);
					XEle_ShowEle(pNewCell->hPane, TRUE);

					wchar_t *pTitle = XPane_GetTitle(pNewCell->hPane);
					XWnd_SetWindowText(hWindow, pTitle);

					Cell_OnSize_FloatWnd(pNewCell, hWindow);
				}
				else //多个组成员
				{
					for (int i = 0; i < countPane; i++)
					{
						layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, i);
						if (pPane->pCell == pChild)
						{
							XArray_DeleteIndex(pGroupCell->hArrayList, i);
							XTabBar_DeleteLabel(pGroupCell->hTabBar, i);
							Cell_Destroy(pChild);
						}
					}
					int index = XTabBar_GetSelect(pGroupCell->hTabBar);
					HELE hLabel = XTabBar_GetLabel(pGroupCell->hTabBar, index);
					wchar_t *pTitle = XBtn_GetText(hLabel);
					XWnd_SetWindowText(hWindow, pTitle);
					Cell_OnSize_FloatWnd(pFloatWnd->pCell, hWindow);
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

void CALLBACK Pane_OnEventDestroy(HELE hEle)
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	XStr_Destroy(pPane->hTitle);
	pPane->hTitle = NULL;
}

BOOL CALLBACK Pane_OnEventMenuSelect(HELE hEle, HELE hEventEle, int id)
{
	if (hEle != hEventEle)
		return FALSE;

	layoutPane_ *pPane = (layoutPane_*)hEle;
	HWINDOW hWindow = XEle_GetHWindow(hEle);

	switch (id)
	{
	case IDM_LOCK: if (pane_state_lock != pPane->state) XPane_Lock(hEle); break;
	case IDM_DOCK: if (pane_state_dock != pPane->state) XPane_Dock(hEle); break;
	case IDM_FLOAT: if (pane_state_float != pPane->state) XPane_FloatPane(hEle); break;
	case IDM_HIDE: if (pane_state_hide != pPane->state) XPane_Hide(hEle); break;
	}

	XFrameWnd_AdjustLayout(hWindow);
	XWnd_RedrawWnd(hWindow);
	return FALSE;
}

BOOL CALLBACK Pane_OnEventShow(HELE hEle, HELE hEventEle, BOOL bShow) //元素显示或隐藏事件
{
	if (hEle == hEventEle)
	{
		if (FALSE == bShow)
		{
			XPane_SetActivate(hEle, FALSE);
		}
	}
	return FALSE;
}

BOOL CALLBACK Pane_OnEleDraw(HELE hEle, HDRAW hDraw)
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (pane_state_float == pPane->state)
	{
		if (((ele_*)hEle)->bBorder)
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
			XDraw_FrameRect_(hDraw, &rect, hBrush);
		}
	}
	else
	{
		RECT rcCaption = rect;
		rcCaption.bottom = rect.top + pPane->captionHeight + 1; //实际高度绘制时要+1,因为包含起点0

		if (pPane->bActivate)
		{
			XDraw_FillSolidRect_(hDraw, &rcCaption, RGB(220, 220, 220));
		}
		else
		{
			XDraw_FillSolidRect_(hDraw, &rcCaption, RGB(200, 200, 200));
		}

		//绘制标题
		wchar_t *pTitle = NULL;
		if (pPane->hTitle)
		{
			pTitle = XStr_GetBuffer(pPane->hTitle);
		}

		if (pTitle)
		{
			RECT rc = rcCaption;
			rc.left = 5;
			rc.right -= 55;
			XDraw_DrawText_(hDraw, pTitle, XStr_GetLength(pPane->hTitle), &rc, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
		}

		HBRUSH hBrush = NULL;
		if (pPane->bActivate)
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(0, 128, 255));
		else
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));

		if (((ele_*)hEle)->bBorder)
			XDraw_FrameRect_(hDraw, &rect, hBrush);

		XDraw_FrameRect_(hDraw, &rcCaption, hBrush);
	}

	return TRUE;
}

BOOL CALLBACK Pane_EleLButtonDown(HELE hEle, UINT flags, POINT *pPt) //鼠标按下
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	if (pPt->y < pPane->captionHeight)
	{
		if (FALSE == XEle_IsHitChildEle(hEle, pPt))
		{
			pPane->bDownCaption = TRUE;
			pPane->downPt = *pPt;
			XEle_SetCapture(hEle);
		}
	}

	if (FALSE == pPane->bActivate)
	{
		XPane_SetActivate(hEle, TRUE);
	}

	return FALSE;
}

BOOL CALLBACK Pane_EleLButtonUp(HELE hEle, UINT flags, POINT *pPt) //鼠标弹起
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	if (pPane->bDownCaption)
	{
		pPane->bDownCaption = FALSE;
		XEle_ReleaseCapture(hEle);
	}

	return FALSE;
}

BOOL CALLBACK Pane_EleMouseMove(HELE hEle, UINT flags, POINT *pPt) //鼠标移动
{
	layoutPane_ *pPane = (layoutPane_*)hEle;
	if (pane_state_lock == pPane->state && pPane->bDownCaption)
	{
		if (pPane->downPt.x<(pPt->x + 8) && pPane->downPt.x>(pPt->x - 8))
		{
			if (pPane->downPt.y<(pPt->y + 8) && pPane->downPt.y>(pPt->y - 8))
			{
				return FALSE;
			}
		}

		pPane->bDownCaption = FALSE;
		XEle_ReleaseCapture(hEle);

		HWINDOW hWindow = XEle_GetHWindow(hEle);

		if (pPane->pCell->pParentCell && cell_type_group == pPane->pCell->pParentCell->type)
		{
			HARRAY  hArray = XArray_Create(); //保存要接收事件的窗格句柄

			int count = XArray_GetCount(pPane->pCell->pParentCell->hArrayList);

			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pPane->pCell->pParentCell->hArrayList, i);
				if (((layoutPane_*)(pChild->hPane))->bInFrame)
				{
					XArray_Add(hArray, pChild->hPane);
				}
			}

			XPane_DragGroup(hEle, pPt);

			int count2 = XArray_GetCount(hArray);
			for (int i = 0; i < count2; i++)
			{
				HELE hPaneSend = (HELE)XArray_GetAt(hArray, i);
				Ele_SendEvent(hPaneSend, XE_PANE_FLOAT, 0, 0);
			}
			XArray_Destroy(hArray);
		}
		else
		{
			XPane_DragPane(hEle, pPt);
			Ele_SendEvent(hEle, XE_PANE_FLOAT, 0, 0);
		}

		XFrameWnd_AdjustLayout(hWindow);
		XWnd_RedrawWnd(hWindow);

		//	XTRACE("拖动窗格 \n ");
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK Pane_EventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (((layoutPane_*)hEle)->bDownCaption)
		{
			((layoutPane_*)hEle)->bDownCaption = FALSE;
			XEle_ReleaseCapture(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK Pane_OnSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		Pane_AdjustLayout(hEle);
	}

	return FALSE;
}

BOOL CALLBACK Pane_BtnClose_OnEleDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (BUTTON(hEle)->hImage_check) return FALSE;
	if (BUTTON(hEle)->hImage_disable) return FALSE;

	switch (BUTTON(hEle)->state)
	{
	case STATE_STAY:
	{
		if (BUTTON(hEle)->hImage_stay) return FALSE;
		XDraw_FillSolidRect_(hDraw, &rect, RGB(190, 190, 190));

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}break;
	case STATE_DOWN:
	{
		if (BUTTON(hEle)->hImage_down) return FALSE;
		XDraw_FillSolidRect_(hDraw, &rect, RGB(180, 180, 180));

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(100, 100, 100));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}break;
	case STATE_LEAVE:
	{
		if (BUTTON(hEle)->hImage_leave) return FALSE;
		HELE hParentEle = XEle_GetParentEle(hEle);
		if (((layoutPane_*)hParentEle)->bActivate)
			XDraw_FillSolidRect_(hDraw, &rect, RGB(220, 220, 220));
		else
			XDraw_FillSolidRect_(hDraw, &rect, RGB(200, 200, 200));
	}break;
	}

	HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 2, RGB(0, 0, 0));
	XDraw_SelectObject_(hDraw, hPen);

	XDraw_MoveToEx_(hDraw, rect.left + 3, rect.top + 3, NULL);  //左上 到 右下
	XDraw_LineTo_(hDraw, rect.left + 11, rect.top + 11);

	XDraw_MoveToEx_(hDraw, rect.left + 11, rect.top + 3, NULL);  //右上 到 左下
	XDraw_LineTo_(hDraw, rect.left + 3, rect.top + 11);

	return TRUE;
}

BOOL CALLBACK Pane_BtnLock_OnEleDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (BUTTON(hEle)->hImage_check) return FALSE;
	if (BUTTON(hEle)->hImage_disable) return FALSE;

	switch (BUTTON(hEle)->state)
	{
	case STATE_STAY:
	{
		if (BUTTON(hEle)->hImage_stay) return FALSE;
		XDraw_FillSolidRect_(hDraw, &rect, RGB(190, 190, 190));

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}break;
	case STATE_DOWN:
	{
		if (BUTTON(hEle)->hImage_down) return FALSE;
		XDraw_FillSolidRect_(hDraw, &rect, RGB(180, 180, 180));

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(100, 100, 100));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}break;
	case STATE_LEAVE:
	{
		if (BUTTON(hEle)->hImage_leave) return FALSE;
		HELE hParentEle = XEle_GetParentEle(hEle);
		if (((layoutPane_*)hParentEle)->bActivate)
			XDraw_FillSolidRect_(hDraw, &rect, RGB(220, 220, 220));
		else
			XDraw_FillSolidRect_(hDraw, &rect, RGB(200, 200, 200));
	}break;
	}

	HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(0, 0, 0));
	XDraw_SelectObject_(hDraw, hPen);

	XDraw_MoveToEx_(hDraw, rect.left + 5, rect.top + 3, NULL);
	XDraw_LineTo_(hDraw, rect.left + 11, rect.top + 3);

	XDraw_MoveToEx_(hDraw, rect.left + 5, rect.top + 3, NULL);
	XDraw_LineTo_(hDraw, rect.left + 5, rect.top + 9);

	XDraw_MoveToEx_(hDraw, rect.left + 3, rect.top + 9, NULL);
	XDraw_LineTo_(hDraw, rect.left + 13, rect.top + 9);

	XDraw_MoveToEx_(hDraw, rect.left + 10, rect.top + 3, NULL);
	XDraw_LineTo_(hDraw, rect.left + 10, rect.top + 9);

	XDraw_MoveToEx_(hDraw, rect.left + 9, rect.top + 3, NULL);
	XDraw_LineTo_(hDraw, rect.left + 9, rect.top + 9);

	XDraw_MoveToEx_(hDraw, rect.left + 8, rect.top + 9, NULL);
	XDraw_LineTo_(hDraw, rect.left + 8, rect.top + 13);
	return TRUE;
}

BOOL CALLBACK Pane_BtnMenu_OnEleDraw(HELE hEle, HDRAW hDraw) //绘制菜单按钮
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (BUTTON(hEle)->hImage_check) return FALSE;
	if (BUTTON(hEle)->hImage_disable) return FALSE;

	switch (BUTTON(hEle)->state)
	{
	case STATE_STAY:
	{
		if (BUTTON(hEle)->hImage_stay) return FALSE;
		XDraw_FillSolidRect_(hDraw, &rect, RGB(190, 190, 190));

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}break;
	case STATE_DOWN:
	{
		if (BUTTON(hEle)->hImage_down) return FALSE;
		XDraw_FillSolidRect_(hDraw, &rect, RGB(180, 180, 180));

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(100, 100, 100));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}break;
	case STATE_LEAVE:
	{
		if (BUTTON(hEle)->hImage_leave) return FALSE;
		HELE hParentEle = XEle_GetParentEle(hEle);
		if (((layoutPane_*)hParentEle)->bActivate)
			XDraw_FillSolidRect_(hDraw, &rect, RGB(220, 220, 220));
		else
			XDraw_FillSolidRect_(hDraw, &rect, RGB(200, 200, 200));
	}break;
	}

	int left = (rect.right - rect.left) / 2;
	int top = (rect.bottom - rect.top) / 2 + 2;

	POINT  pt[3];
	pt[0].x = left;
	pt[0].y = top + 3;
	pt[1].x = left - 4;
	pt[1].y = top - 2;
	pt[2].x = left + 5;
	pt[2].y = top - 2;

	HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
	HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
	XDraw_FillRgn_(hDraw, hRgn, hBrush2);

	return TRUE;
}

BOOL CALLBACK Pane_Btn_Close(HELE hEle, HELE hEventEle)   //关闭按钮
{
	if (hEle == hEventEle)
	{
		HWINDOW hWindow = XEle_GetHWindow(hEle);
		XPane_Hide(XEle_GetParentEle(hEle));
		XFrameWnd_AdjustLayout(hWindow);
		XWnd_RedrawWnd(hWindow);
	}
	return FALSE;
}

BOOL CALLBACK Pane_Btn_Lock(HELE hEle, HELE hEventEle) //停靠按钮
{
	if (hEle != hEventEle)
		return FALSE;

	HELE hPane = XEle_GetParentEle(hEle);
	HWINDOW hWindow = XEle_GetHWindow(hEle);
	if (pane_state_lock == ((layoutPane_*)hPane)->state) //锁定
	{
		layoutCell_ *pCell = ((layoutPane_*)hPane)->pCell;
		if (pCell->pParentCell && cell_type_group == pCell->pParentCell->type) //窗格组
		{
			HARRAY hArray = XArray_Create(); //保存要接收事件的窗格句柄

			int count = XArray_GetCount(pCell->pParentCell->hArrayList);
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCell->pParentCell->hArrayList, i);
				if (((layoutPane_*)pChild->hPane)->bInFrame)
				{
					XArray_Add(hArray, pChild->hPane);
				}
			}

			XPane_Dock(hPane);
			XFrameWnd_AdjustLayout(hWindow);

			int count2 = XArray_GetCount(hArray);
			for (int i = 0; i < count2; i++)
			{
				HELE hPaneSend = (HELE)XArray_GetAt(hArray, i);
				Ele_SendEvent(hPaneSend, XE_PANE_DOCK, 0, 0);
			}
			XArray_Destroy(hArray);
		}
		else //独立窗格
		{
			XPane_Dock(hPane);
			XFrameWnd_AdjustLayout(hWindow);

			Ele_SendEvent(hPane, XE_PANE_DOCK, 0, 0);
		}

		XWnd_RedrawWnd(hWindow);
	}
	else if (pane_state_dock == ((layoutPane_*)hPane)->state) //停靠
	{
		layoutCell_ *pCell = ((layoutPane_*)hPane)->pCell;
		if (pCell->pParentCell && cell_type_group == pCell->pParentCell->type) //窗格组
		{
			XPane_Lock(hPane);
			XFrameWnd_AdjustLayout(hWindow);

			int count = XArray_GetCount(pCell->pParentCell->hArrayList);
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCell->pParentCell->hArrayList, i);
				if (((layoutPane_*)pChild->hPane)->bInFrame)
				{
					Ele_SendEvent(pChild->hPane, XE_PANE_LOACK, 0, 0);
				}
			}
		}
		else  //独立窗格
		{
			XPane_Lock(hPane);
			XFrameWnd_AdjustLayout(hWindow);

			Ele_SendEvent(hPane, XE_PANE_LOACK, 0, 0);
		}

		XWnd_RedrawWnd(hWindow);
	}

	return FALSE;
}

BOOL CALLBACK Pane_Btn_Menu(HELE hEle, HELE hEventEle)     //菜单按钮
{
	if (hEle != hEventEle)
		return FALSE;

	HWINDOW hWindow = XEle_GetHWindow(hEle);
	POINT pt = { 0,0 };

	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	XEle_RectToNCWnd(hEle, &rect);

	pt.x = rect.left;
	pt.y = rect.bottom;

	//创建弹出菜单
	HMENUX hMenu = XMenu_Create();
	XMenu_AddItem(hMenu, IDM_LOCK, L"锁定");
	XMenu_AddItem(hMenu, IDM_DOCK, L"停靠");
	XMenu_AddItem(hMenu, IDM_FLOAT, L"浮动");
	XMenu_AddItem(hMenu, -1, NULL, -1, XM_SEPARATOR);
	XMenu_AddItem(hMenu, IDM_HIDE, L"隐藏");

	ClientToScreen(XWnd_GetHWnd(hWindow), &pt);
	XMenu_Popup(hMenu, XWnd_GetHWnd(hWindow), pt.x, pt.y, XEle_GetParentEle(hEle));

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
HHOOK    g_floatWnd_hHook = NULL;
HWINDOW  g_hFloatWnd = NULL;
HWINDOW FloatWnd_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HWINDOW hFrameWnd, layoutCell_ *pCell)
{
	floatWindow_ *pObj = (floatWindow_*)malloc(sizeof(floatWindow_));
	if (pObj)
	{
		memset(pObj, 0, sizeof(floatWindow_));
		if (FALSE == FloatWnd_Init((HWINDOW)pObj, x, y, cx, cy, pTitle, hFrameWnd, pCell, XC_FLOATWND))
		{
			free(pObj);
			return NULL;
		}
		return (HWINDOW)pObj;
	}
	return NULL;
}

BOOL FloatWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, wchar_t *pTitle, HWINDOW hFrameWnd, layoutCell_ *pCell, int exType)
{
	BOOL bRes = Wnd_Init(hWindow, WS_EX_TOOLWINDOW, NULL, pTitle, WS_POPUP, x, y, cx, cy, XWnd_GetHWnd(hFrameWnd),
		XC_SY_CAPTION | XC_SY_BORDER /*| XC_SY_ROUND*/ | XC_SY_DRAW_CAPTION_ICON | XC_SY_DRAW_CAPTION_TITLE | XC_SY_DRAG_BORDER | XC_SY_CLOSE, exType);

	if (bRes)
	{
		AddTypeDebug(hWindow, XC_FLOATWND);

		((floatWindow_*)hWindow)->pCell = pCell;
		((floatWindow_*)hWindow)->hFrameWnd = hFrameWnd;
		((floatWindow_*)hWindow)->bLock = TRUE;

		XWnd_SetBorderSize(hWindow, 2, 2, 2, 2);

		if (pCell->hPane) //去掉标题栏
		{
			layoutPane_   *pPane = (layoutPane_*)pCell->hPane;
			XEle_ShowEle(pPane->hBtnClose, FALSE);
			XEle_ShowEle(pPane->hAutoHide, FALSE);
			XEle_ShowEle(pPane->hBtnMenu, FALSE);
		}
		else if (cell_type_group == pCell->type)
		{
			int count = XArray_GetCount(pCell->hArrayList);
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCell->hArrayList, i);
				layoutPane_   *pPane = (layoutPane_*)pChild->hPane;
				XEle_ShowEle(pPane->hBtnClose, FALSE);
				XEle_ShowEle(pPane->hAutoHide, FALSE);
				XEle_ShowEle(pPane->hBtnMenu, FALSE);
			}
		}

		XWnd_RegisterMessage(hWindow, WM_SIZE, FloatWnd_OnWndSize);
		XWnd_RegisterMessage(hWindow, WM_DESTROY, FloatWnd_OnWndDestroy);
		XWnd_RegisterMessage(hWindow, WM_CLOSE, FloatWnd_OnWndClose);
		XWnd_RegisterMessage(hWindow, WM_KILLFOCUS, FloatWnd_OnWndKillFocus);
		return TRUE;
	}
	return FALSE;
}

/// @defgroup floatWnd 浮动窗口
/// @ingroup groupWindows
/// @{

/// @brief 启用关闭锁定功能,当关闭锁定功能后,用户拖动浮动窗格不能锁定到框架窗口中.
/// @param hWindow  浮动窗口句柄.
/// @param bEnable  启用TRUE,关闭FALSE.
void WINAPI XFloatWnd_EnableLock(HWINDOW hWindow, BOOL bEnable) //启用关闭锁定功能,当关闭锁定功能后,用户拖动浮动窗格不能锁定到框架窗口中
{
	((floatWindow_*)hWindow)->bLock = bEnable;
}

/// @}

void FloatWnd_ExitDragWindow()
{
	if (g_floatWnd_hHook)
	{
		OutputDebugStringA("卸载3 \n");
		if (g_hFloatWnd)
		{
			FrameWnd_OnFloatWnd_Exit(((floatWindow_*)g_hFloatWnd)->hFrameWnd);
		}
		UnhookWindowsHookEx(g_floatWnd_hHook);
		g_floatWnd_hHook = NULL;
		g_hFloatWnd = NULL;
	}
}

void FloatWnd_DragWindow(HWINDOW hWindow, POINT *pPt) //拖动窗口
{
	if (NULL == g_floatWnd_hHook)
	{
		floatWindow_  *pFloatWnd = (floatWindow_*)hWindow;

		pFloatWnd->downPt = *pPt;
		g_hFloatWnd = hWindow;
		((frameWnd_*)(pFloatWnd->hFrameWnd))->hFloatWnd = hWindow;

		//创建停靠提示及停靠位置预览窗口,临时窗口

		if (pFloatWnd->bLock) //不可以锁定到框架
			FrameWnd_CreateTempWindow(pFloatWnd->hFrameWnd);

		HMODULE hModule = GetModuleHandle(NULL);
		g_floatWnd_hHook = SetWindowsHookEx(WH_MOUSE_LL, FloatWnd_LowLevelMouseProc, hModule, 0);
	}
	else
	{
		UnhookWindowsHookEx(g_floatWnd_hHook);
		g_floatWnd_hHook = NULL;
		g_hFloatWnd = NULL;
		MessageBox(NULL, L"拖动窗格错误,code:007", L"炫彩界面库-错误提示!", 0);
	}
}

BOOL CALLBACK FloatWnd_OnWndDestroy(HWINDOW hWindow)
{
	floatWindow_ *pFloat = (floatWindow_*)hWindow;
	if (pFloat->pCell)
	{

		if (cell_type_group == pFloat->pCell->type)
		{
			int count = XArray_GetCount(pFloat->pCell->hArrayList);
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pFloat->pCell->hArrayList, i);
				Cell_Destroy(pChild);
			}
			Cell_Destroy(pFloat->pCell);
		}
		else
		{
			Cell_Destroy(pFloat->pCell);
		}
	}

	return FALSE;
}

BOOL CALLBACK FloatWnd_OnWndSize(HWINDOW hWindow, UINT flags, SIZE *pSize)
{
	HELE hPane = ((floatWindow_*)hWindow)->pCell->hPane;

	Cell_OnSize_FloatWnd(((floatWindow_*)hWindow)->pCell, hWindow);
	return FALSE;
}

BOOL CALLBACK FloatWnd_OnWndClose(HWINDOW hWindow)
{
	XWnd_ShowWindow(hWindow, SW_HIDE);
	return TRUE;
}

BOOL CALLBACK FloatWnd_OnWndKillFocus(HWINDOW hWindow)
{
	XTRACE("失去焦点\n");
	FloatWnd_ExitDragWindow();
	return FALSE;
}

LRESULT CALLBACK FloatWnd_LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_floatWnd_hHook, nCode, wParam, lParam);
	}

	floatWindow_  *pFloatWnd = (floatWindow_*)g_hFloatWnd;
	if (WM_MOUSEMOVE == wParam)
	{
		//	wchar_t buf[256]={0};
		//	swprintf(buf, L"x=%d,y=%d \n",PMSLLHOOKSTRUCT(lParam)->pt.x,PMSLLHOOKSTRUCT(lParam)->pt.y);
		//	OutputDebugStringW(buf);

		POINT  pt = { PMSLLHOOKSTRUCT(lParam)->pt.x,PMSLLHOOKSTRUCT(lParam)->pt.y };

		if (NULL == pFloatWnd)
		{
			OutputDebugStringA("卸载1 \n");
			UnhookWindowsHookEx(g_floatWnd_hHook);
			g_floatWnd_hHook = NULL;
			g_hFloatWnd = NULL;
		}
		else
		{
			SetWindowPos(XWnd_GetHWnd(g_hFloatWnd), NULL, pt.x - pFloatWnd->downPt.x, pt.y - pFloatWnd->downPt.y,
				0, 0, SWP_NOSIZE | SWP_NOZORDER);

			if (pFloatWnd->bLock)
				FrameWnd_OnFloatWnd_Move(((floatWindow_*)g_hFloatWnd)->hFrameWnd, &pt);
		}
	}
	else if (WM_LBUTTONUP == wParam)
	{
		if (g_hFloatWnd)
		{
			if (pFloatWnd->bLock)
				FrameWnd_OnFloatWnd_LButtonUp(((floatWindow_*)g_hFloatWnd)->hFrameWnd);
		}
		UnhookWindowsHookEx(g_floatWnd_hHook);
		g_floatWnd_hHook = NULL;
		g_hFloatWnd = NULL;

		OutputDebugStringA("卸载2 \n");

		//POINT  pt={PMSLLHOOKSTRUCT(lParam)->pt.x,PMSLLHOOKSTRUCT(lParam)->pt.y};
	}

	return CallNextHookEx(g_floatWnd_hHook, nCode, wParam, lParam);
}

BOOL CALLBACK FloatWnd_OnEventTabBarSelect(HELE hEle, HELE hEventEle, int index)
{
	if (hEle == hEventEle)
	{
		if (index >= 0)
		{
			HELE hButton = XTabBar_GetLabel(hEle, index);
			wchar_t *pTitle = XBtn_GetText(hButton);
			if (pTitle)
			{
				HWINDOW hWindow = XEle_GetHWindow(hEle);
				XWnd_SetWindowText(hWindow, pTitle);
				XWnd_RedrawWnd(hWindow);
			}
		}
	}
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////

