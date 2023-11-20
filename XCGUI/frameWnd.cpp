/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"



/// @addtogroup frameWindow
/// @{

/// @brief 创建框架窗口
/// @param x   窗口左上角x坐标.
/// @param y   窗口左上角y坐标.
/// @param cx  窗口宽度.
/// @param cy  窗口高度.
/// @param pTitle  窗口标题.
/// @param hWndParent  父窗口.
/// @param XCStyle    GUI库窗口样式,样式请参见宏定义.
/// @return  GUI库窗口资源句柄.
HWINDOW WINAPI XFrameWnd_CreateWindow(int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent, int XCStyle)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)malloc(sizeof(frameWnd_));
	memset(pFrameWnd, 0, sizeof(frameWnd_));

	if (FALSE == FrameWnd_Init((HWINDOW)pFrameWnd, NULL, NULL, pTitle, NULL, x, y, cx, cy, hWndParent, XCStyle, XC_FRAMEWND))
	{
		delete pFrameWnd;
		return NULL;
	}
	return (HWINDOW)pFrameWnd;
}

BOOL FrameWnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle, int exType)
{
	if (Wnd_Init((HWINDOW)hWindow, dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, cx, cy, hWndParent, XCStyle, XC_FRAMEWND))
	{
		AddTypeDebug(hWindow, XC_FRAMEWND);

		frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

		XWnd_RegisterMessage(hWindow, WM_SIZE, FrameWnd_OnSize);
		XWnd_RegisterMessage(hWindow, WM_DESTROY, FrameWnd_OnWndDestroy);
		XWnd_RegisterMessage(hWindow, WM_LBUTTONDOWN, FrameWnd_OnLButtonDown);

		return TRUE;
	}
	return FALSE;
}

/// @brief 添加窗格到框架窗口.
/// @param hWindow  窗口资源句柄.
/// @param hPaneDest  目标窗格.
/// @param hPaneNew   新增窗格.
/// @param align      对齐方式.
/// @param scale      大小比例.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XFrameWnd_AddPane(HWINDOW hWindow, HELE hPaneDest, HELE hPaneNew, align_type_ align, int scale)
{
	IsFrameWindowDebug(hWindow, __FUNCTION__);

	if (hPaneDest)
	{
		IsPaneDebug(hPaneDest, __FUNCTION__);
	}

	IsPaneDebug(hPaneNew, __FUNCTION__);

	if (NULL == hPaneNew) return FALSE;

	return FrameWnd_AddT(hWindow, hPaneDest ? Pane_GetCell(hPaneDest) : NULL,
		hPaneNew ? Pane_GetCell(hPaneNew) : NULL, align, scale);
}

/// @brief 将新窗格与目标窗格合并为组.
/// @param hWindow  窗口资源句柄.
/// @param hPaneDest  目标窗格.
/// @param hPaneNew   新增窗格.
/// @param proportion 窗格比例,0--100.
/// @return 返回窗格组句柄.
HPANE_GROUP	WINAPI XFrameWnd_MergePane(HWINDOW hWindow, HELE hPaneDest, HELE hPaneNew, int proportion)
{
	IsPaneDebug(hPaneDest, __FUNCTION__);
	IsPaneDebug(hPaneNew, __FUNCTION__);

	layoutCell_ *pDest = Pane_GetCell(hPaneDest);
	layoutCell_ *pNew = Pane_GetCell(hPaneNew);

	if (pDest->pParentCell && cell_type_group == pDest->pParentCell->type)
	{
		//窗格1为组成员不能合并
		MessageBox(NULL, L"窗格1为组成员不能合并", L"炫彩界面库-错误提示!", 0);
		return NULL;
	}
	if (pNew->pParentCell && cell_type_group == pNew->pParentCell->type)
	{
		//窗格2为组成员不能合并
		MessageBox(NULL, L"窗格2为组成员不能合并", L"炫彩界面库-错误提示!", 0);
		return NULL;
	}

	if (cell_type_pane == pDest->type && cell_type_pane == pNew->type)
	{
		return FrameWnd_Add_Merge_Pane2(hWindow, pDest, pNew, align_group_member, proportion);
	}

	return NULL;
}

/// @brief 将窗格合并到组.
/// @param hWindow  窗口资源句柄.
/// @param hGroup    窗格组句柄.
/// @param hPaneNew   新增窗格.
/// @param proportion 窗格比例,0--100.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XFrameWnd_MergePaneToGroup(HWINDOW hWindow, HPANE_GROUP hGroup, HELE hPaneNew, int proportion) //窗格合并到组
{
	layoutCell_ *pGroup = (layoutCell_*)hGroup;
	layoutCell_ *pCell = Pane_GetCell(hPaneNew);
	pCell->scale = proportion;
	return FrameWnd_Add_Merge_PaneToGroup(hWindow, pGroup, pCell);
}

//组合
BOOL FrameWnd_AddT(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	//窗格到窗格, 窗格 -> 窗格
	//组到窗格,   组   -> 窗格
	//窗格到组,   窗格 -> 组

	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	pCellNew->scale = scale;
	pCellNew->align = align;

	if (pCellNew->hPane)
	{
		if (NULL == XEle_GetHWindow(pCellNew->hPane))
			XWnd_AddEle(hWindow, pCellNew->hPane);

		layoutPane_ *pPane = (layoutPane_*)pCellNew->hPane;

		pPane->state = pane_state_lock;
		XEle_ShowEle(pCellNew->hPane, TRUE);
	}

	if (NULL == pFrameWnd->pCell)
	{
		pFrameWnd->pCell = pCellNew;
		if (cell_type_pane == pCellNew->type)
		{
			Pane_EnableLayout(pCellNew->hPane, TRUE);
		}if (cell_type_group == pCellNew->type)
		{
			if (NULL == pCellNew->hTabBar)
			{
				pCellNew->hTabBar = XTabBar_Create(10, 10, 100, 100, hWindow);
				XTabBar_SetAlign(pCellNew->hTabBar, align_bottom);
				int count = XArray_GetCount(pCellNew->hArrayList);
				for (int i = 0; i < count; i++)
				{
					layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellNew->hArrayList, i);
					XWnd_AddEle(hWindow, pChild->hPane);
					((layoutPane_*)(pChild->hPane))->state = pane_state_lock;
					Pane_EnableLayout(pChild->hPane, TRUE);

					int index = XTabBar_AddLabel(pCellNew->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);
					HELE hButton = XTabBar_GetLabel(pCellNew->hTabBar, index);
					XEle_SetUserData(hButton, (void*)pChild);
					XEle_RegisterMessage(hButton, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
					XEle_RegisterMessage(hButton, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
					XEle_RegisterMessage(hButton, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
					XEle_RegisterEvent(hButton, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
				}
			}
		}
		return TRUE;
	}
	if (NULL == pCellDest) //添加到顶级窗格
	{
		pCellDest = pFrameWnd->pCell;

		if (cell_type_pane == pCellNew->type)
		{
			return FrameWnd_Add_Pane(hWindow, pCellDest, pCellNew, align, scale); //窗格 -> 窗格
		}
	}

	if (cell_type_pane == pCellDest->type && cell_type_pane == pCellNew->type)
	{
		FrameWnd_Add_Pane(hWindow, pCellDest, pCellNew, align, scale); //窗格 -> 窗格
	}
	else if (cell_type_pane == pCellDest->type && cell_type_group == pCellNew->type)
	{
		FrameWnd_Add_GroupToPane(hWindow, pCellDest, pCellNew, align, scale); //组   -> 窗格
	}
	else if (cell_type_group == pCellDest->type && cell_type_pane == pCellNew->type)
	{
		FrameWnd_Add_PaneToGroup(hWindow, pCellDest, pCellNew, align, scale); // 窗格 -> 组
	}
	else if (cell_type_group == pCellNew->type) //增加组到布局
	{
		FrameWnd_Add_GroupToPane(hWindow, pCellDest, pCellNew, align, scale);
	}
	else
	{
		if (pCellDest && cell_type_pane == pCellNew->type)
		{
			return FrameWnd_Add_Pane(hWindow, pCellDest, pCellNew, align, scale); //窗格 -> 窗格
		}
	}
	return TRUE;
}

//合并
BOOL FrameWnd_Add_MergeT(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	//两个窗格合并,   窗格 + 窗格 ok
	//组合并,         组   + 组 ok
	//窗格到组,       窗格 + 组 ok
	//组与窗格合并,   组   + 窗格

	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	pCellNew->scale = scale;
	//pCellNew->hWindow=hWindow;
	pCellNew->align = align;

	if (pCellNew->hPane)
	{
		if (NULL == XEle_GetHWindow(pCellNew->hPane))
			XWnd_AddEle(hWindow, pCellNew->hPane);

		layoutPane_ *pPane = (layoutPane_*)pCellNew->hPane;

		pPane->state = pane_state_lock;
		XEle_ShowEle(pCellNew->hPane, TRUE);
	}

	if (cell_type_pane == pCellDest->type && cell_type_pane == pCellNew->type)
	{
		FrameWnd_Add_Merge_Pane2(hWindow, pCellDest, pCellNew, align, scale);
	}
	else if (cell_type_group == pCellDest->type && cell_type_group == pCellNew->type)
	{
		FrameWnd_Add_Merge_Group2(hWindow, pCellDest, pCellNew, align, scale);
	}
	else if (cell_type_group == pCellDest->type && cell_type_pane == pCellNew->type)
	{
		FrameWnd_Add_Merge_PaneToGroup(hWindow, pCellDest, pCellNew);//,align,scale);
	}
	else if (cell_type_pane == pCellDest->type && cell_type_group == pCellNew->type)
	{
		FrameWnd_Add_Merge_GroupToPane(hWindow, pCellDest, pCellNew, align, scale);
	}

	return TRUE;
}

BOOL FrameWnd_Add_Pane(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	if (pCellNew->hPane)
	{
		Pane_EnableLayout(pCellNew->hPane, TRUE);
		((layoutPane_*)(pCellNew->hPane))->state = pane_state_lock;
	}

	layoutCell_ *pCellParent = Cell_Create(hWindow, NULL, pCellDest->align);
	pCellParent->scale = pCellDest->scale;
	pCellDest->scale = 100 - pCellNew->scale;
	pCellParent->pParentCell = pCellDest->pParentCell;

	pCellNew->pParentCell = pCellParent;
	pCellDest->pParentCell = pCellParent;
	switch (align)
	{
	case align_any:
	case align_left:
	{
		pCellParent->type = cell_type_left_right;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellNew;
		pCellParent->pCell2 = pCellDest;

		pCellParent->pCell1->align = align_left;
		pCellParent->pCell2->align = align_right;
	}break;
	case align_top:
	{
		pCellParent->type = cell_type_top_bottom;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellNew;
		pCellParent->pCell2 = pCellDest;

		pCellParent->pCell1->align = align_top; //ALIGN_TOP;
		pCellParent->pCell2->align = align_bottom;//ALIGN_BOTTOM;
	}break;
	case align_right:
	{
		pCellParent->type = cell_type_left_right;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellDest;
		pCellParent->pCell2 = pCellNew;

		pCellParent->pCell1->align = align_left; //ALIGN_LEFT;
		pCellParent->pCell2->align = align_right;// ALIGN_RIGHT;
	}break;
	case align_bottom:
	{
		pCellParent->type = cell_type_top_bottom;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellDest;
		pCellParent->pCell2 = pCellNew;

		pCellParent->pCell1->align = align_top; //ALIGN_TOP;
		pCellParent->pCell2->align = align_bottom;//ALIGN_BOTTOM;
	}break;
	default: XMessageBox(hWindow, L"在API:XFrameWnd_AddPane()中,参数[align]错误", L"炫彩界面库-错误提示!");
		return FALSE;
	}
	return TRUE;
}

//组到窗格
BOOL FrameWnd_Add_GroupToPane(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	layoutCell_ *pGroupCell = pCellNew;

	if (NULL == pGroupCell->hTabBar)
	{
		pGroupCell->hTabBar = XTabBar_Create(10, 10, 100, 100, hWindow);
		XTabBar_SetAlign(pGroupCell->hTabBar, align_bottom);
		int count = XArray_GetCount(pGroupCell->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, i);
			XWnd_AddEle(hWindow, pChild->hPane);
			((layoutPane_*)(pChild->hPane))->state = pane_state_lock;
			Pane_EnableLayout(pChild->hPane, TRUE);

			int index = XTabBar_AddLabel(pGroupCell->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);
			HELE hButton = XTabBar_GetLabel(pGroupCell->hTabBar, index);
			XEle_SetUserData(hButton, (void*)pChild);
			XEle_RegisterMessage(hButton, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
			XEle_RegisterMessage(hButton, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
			XEle_RegisterMessage(hButton, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
			XEle_RegisterEvent(hButton, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
		}
	}

	FrameWnd_Add_Pane(hWindow, pCellDest, pCellNew, align, scale);
	return TRUE;
}

BOOL FrameWnd_Add_PaneToGroup(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	FrameWnd_Add_Pane(hWindow, pCellDest, pCellNew, align, scale);
	return TRUE;
}

//窗格合并
HPANE_GROUP FrameWnd_Add_Merge_Pane2(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	((layoutPane_*)(pCellNew->hPane))->state = pane_state_lock;
	Pane_EnableLayout(pCellNew->hPane, TRUE);

	layoutCell_ *pCellParent = Cell_Create(hWindow, NULL, pCellDest->align);
	pCellParent->pParentCell = pCellDest->pParentCell;
	if (NULL == pCellParent->pParentCell)
	{
		pFrameWnd->pCell = pCellParent;
	}
	else
	{
		if (align_right == pCellParent->align || align_bottom == pCellParent->align)
			pCellParent->pParentCell->pCell2 = pCellParent;
		else
			pCellParent->pParentCell->pCell1 = pCellParent;
	}

	pCellParent->type = cell_type_group;
	pCellParent->scale = pCellDest->scale;
	pCellNew->pParentCell = pCellParent;
	pCellNew->align = align_group_member;
	pCellDest->pParentCell = pCellParent;
	pCellDest->align = align_group_member;

	pCellParent->hTabBar = XTabBar_Create(10, 10, 100, 100, hWindow);
	XTabBar_SetAlign(pCellParent->hTabBar, align_bottom);

	XTabBar_AddLabel(pCellParent->hTabBar, XPane_GetTitle(pCellDest->hPane), pCellDest->hPane);
	XTabBar_AddLabel(pCellParent->hTabBar, XPane_GetTitle(pCellNew->hPane), pCellNew->hPane);

	HELE hBtn1 = XTabBar_GetLabel(pCellParent->hTabBar, 0);
	HELE hBtn2 = XTabBar_GetLabel(pCellParent->hTabBar, 1);
	XEle_SetUserData(hBtn1, (void*)pCellDest);
	XEle_SetUserData(hBtn2, (void*)pCellNew);

	XArray_Add(pCellParent->hArrayList, pCellDest);
	XArray_Add(pCellParent->hArrayList, pCellNew);

	XEle_RegisterMessage(hBtn1, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
	XEle_RegisterMessage(hBtn1, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
	XEle_RegisterMessage(hBtn1, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
	XEle_RegisterEvent(hBtn1, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);

	XEle_RegisterMessage(hBtn2, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
	XEle_RegisterMessage(hBtn2, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
	XEle_RegisterMessage(hBtn2, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
	XEle_RegisterEvent(hBtn2, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
	return (HPANE_GROUP)pCellParent;
}

//将窗格添加到组
BOOL FrameWnd_Add_Merge_PaneToGroup(HWINDOW hWindow, layoutCell_ *pCellGroup, layoutCell_ *pCellPane)
{
	if (cell_type_group == pCellGroup->type)
	{
		frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
		((layoutPane_*)(pCellPane->hPane))->state = pane_state_lock;
		pCellPane->align = align_group_member;
		Pane_EnableLayout(pCellPane->hPane, TRUE);

		layoutCell_ *pCellParent = pCellGroup;
		pCellPane->pParentCell = pCellParent;

		int index = XTabBar_AddLabel(pCellParent->hTabBar, XPane_GetTitle(pCellPane->hPane), pCellPane->hPane);
		XTabBar_SetSelect(pCellParent->hTabBar, index);
		HELE hBtn = XTabBar_GetLabel(pCellParent->hTabBar, index);
		XEle_SetUserData(hBtn, (void*)pCellPane);

		XArray_Add(pCellParent->hArrayList, pCellPane);

		XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
		XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
		XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
		XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
		return TRUE;
	}
	return FALSE;
}

//组到组,合并
BOOL FrameWnd_Add_Merge_Group2(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	if (cell_type_group == pCellDest->type && cell_type_group == pCellNew->type) //合并组
	{
		int countDest = XArray_GetCount(pCellDest->hArrayList);
		int count = XArray_GetCount(pCellNew->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_  *pChildCell = (layoutCell_*)XArray_GetAt(pCellNew->hArrayList, i);
			pChildCell->pParentCell = pCellDest;
			XWnd_AddEle(hWindow, pChildCell->hPane);
			((layoutPane_*)(pChildCell->hPane))->state = pane_state_lock;
			Pane_EnableLayout(pChildCell->hPane, TRUE);

			int index = XTabBar_AddLabel(pCellDest->hTabBar, XPane_GetTitle(pChildCell->hPane), pChildCell->hPane);

			/////////////////////////////////////////////

			HELE hBtn = XTabBar_GetLabel(pCellDest->hTabBar, index);
			XEle_SetUserData(hBtn, (void*)pChildCell);

			XArray_Add(pCellDest->hArrayList, pChildCell);

			XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
			XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
			XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
			XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
		}

		if (pCellNew->hTabBar)
		{
			XEle_Destroy(pCellNew->hTabBar);
			pCellNew->hTabBar = NULL;
		}
		Cell_Destroy(pCellNew);

		return TRUE;
	}
	return TRUE;
}

//组到窗格合并
BOOL FrameWnd_Add_Merge_GroupToPane(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	//将窗格合并到组中,增加到框架

	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	layoutCell_ *pGroupCell = pCellNew;

	if (NULL == pGroupCell->hTabBar)
	{
		pGroupCell->hTabBar = XTabBar_Create(10, 10, 100, 100, hWindow);
		XTabBar_SetAlign(pGroupCell->hTabBar, align_bottom);
		int count = XArray_GetCount(pGroupCell->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, i);
			XWnd_AddEle(hWindow, pChild->hPane);
			((layoutPane_*)(pChild->hPane))->state = pane_state_lock;
			Pane_EnableLayout(pChild->hPane, TRUE);

			int index = XTabBar_AddLabel(pGroupCell->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);
			HELE hButton = XTabBar_GetLabel(pGroupCell->hTabBar, index);
			XEle_SetUserData(hButton, (void*)pChild);
			XEle_RegisterMessage(hButton, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
			XEle_RegisterMessage(hButton, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
			XEle_RegisterMessage(hButton, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
			XEle_RegisterEvent(hButton, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
		}
	}

	pGroupCell->align = pCellDest->align;

	if (NULL == pCellDest->pParentCell)
	{
		if (pCellDest != pFrameWnd->pCell)
		{
			MessageBox(NULL, L"合并组到窗口错误:0022", L"炫彩界面库-错误提示!", 0);
			exit(0);
			return FALSE;
		}
		pFrameWnd->pCell = pGroupCell;
		pGroupCell->pParentCell = NULL;
	}
	else
	{
		pGroupCell->pParentCell = pCellDest->pParentCell;

		if (pCellDest->pParentCell->pCell1 == pCellDest)
			pCellDest->pParentCell->pCell1 = pGroupCell;
		else if (pCellDest->pParentCell->pCell2 == pCellDest)
			pCellDest->pParentCell->pCell2 = pGroupCell;
		else
			return FALSE;
	}

	pCellDest->pParentCell = pGroupCell;
	pCellDest->align = align_group_member;

	int index = XTabBar_AddLabel(pGroupCell->hTabBar, XPane_GetTitle(pCellDest->hPane), pCellDest->hPane);
	XTabBar_SetSelect(pGroupCell->hTabBar, index);

	HELE hBtn = XTabBar_GetLabel(pGroupCell->hTabBar, index);
	XEle_SetUserData(hBtn, (void*)pCellDest);

	XArray_Add(pGroupCell->hArrayList, pCellDest);

	XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
	XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
	XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
	XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);

	return TRUE;
}

BOOL FrameWnd_AddPaneGroup(HWINDOW hWindow, layoutCell_ *pCellDest, layoutCell_ *pCellNew, align_type_ align, int scale)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;


	if (cell_type_group == pCellDest->type && cell_type_group == pCellNew->type) //合并组
	{
		int countDest = XArray_GetCount(pCellDest->hArrayList);
		int count = XArray_GetCount(pCellNew->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_  *pChildCell = (layoutCell_*)XArray_GetAt(pCellNew->hArrayList, i);
			pChildCell->pParentCell = pCellDest;
			XWnd_AddEle(hWindow, pChildCell->hPane);
			int index = XTabBar_AddLabel(pCellDest->hTabBar, XPane_GetTitle(pChildCell->hPane), pChildCell->hPane);

			/////////////////////////////////////////////

			HELE hBtn = XTabBar_GetLabel(pCellDest->hTabBar, index);
			XEle_SetUserData(hBtn, (void*)pChildCell);

			XEle_RegisterMessage(hBtn, XM_LBUTTONDOWN, FrameWnd_TabBar_Btn_OnLButtonDown);
			XEle_RegisterMessage(hBtn, XM_LBUTTONUP, FrameWnd_TabBar_Btn_OnLButtonUp);
			XEle_RegisterMessage(hBtn, XM_MOUSEMOVE, FrameWnd_TabBar_Btn_OnMouseMove);
			XEle_RegisterEvent(hBtn, XE_MOUSELEAVE, FrameWnd_TabBar_Btn_OnEventMouseLeave);
		}

		if (pCellNew->hTabBar)
		{
			XEle_Destroy(pCellNew->hTabBar);
			pCellNew->hTabBar = NULL;
		}
		Cell_Destroy(pCellNew);

		XTRACE("合并组 \n");
		return TRUE;
	}

	if (cell_type_group == pCellNew->type)
	{
		int count = XTabBar_GetLabelCount(pCellNew->hTabBar);
		for (int i = 0; i < count; i++)
		{
			HELE hBtn = XTabBar_GetLabel(pCellNew->hTabBar, i);
			layoutCell_ *pChildCell = (layoutCell_*)XEle_GetUserData(hBtn);
			XWnd_AddEle(hWindow, pChildCell->hPane);

		}
		XWnd_AddEle(hWindow, pCellNew->hTabBar);
	}

	layoutCell_ *pCellParent = Cell_Create(hWindow, NULL, pCellDest->align);
	pCellParent->scale = pCellDest->scale;
	pCellDest->scale = 100 - pCellNew->scale;
	pCellParent->pParentCell = pCellDest->pParentCell;

	pCellNew->pParentCell = pCellParent;
	pCellDest->pParentCell = pCellParent;
	switch (align)
	{
	case align_any:
	case align_left:
	{
		pCellParent->type = cell_type_left_right;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellNew;
		pCellParent->pCell2 = pCellDest;

		pCellParent->pCell1->align = align_left;
		pCellParent->pCell2->align = align_right;
	}break;
	case align_top:
	{
		pCellParent->type = cell_type_top_bottom;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellNew;
		pCellParent->pCell2 = pCellDest;

		pCellParent->pCell1->align = align_top; //ALIGN_TOP;
		pCellParent->pCell2->align = align_bottom;//ALIGN_BOTTOM;
	}break;
	case align_right:
	{
		pCellParent->type = cell_type_left_right;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellDest;
		pCellParent->pCell2 = pCellNew;

		pCellParent->pCell1->align = align_left; //ALIGN_LEFT;
		pCellParent->pCell2->align = align_right;// ALIGN_RIGHT;
	}break;
	case align_bottom:
	{
		pCellParent->type = cell_type_top_bottom;
		if (NULL == pCellParent->pParentCell)
		{
			pFrameWnd->pCell = pCellParent;
		}
		else
		{
			if (align_right == pCellParent->align || align_bottom == pCellParent->align)
				pCellParent->pParentCell->pCell2 = pCellParent;
			else
				pCellParent->pParentCell->pCell1 = pCellParent;
		}

		pCellParent->pCell1 = pCellDest;
		pCellParent->pCell2 = pCellNew;

		pCellParent->pCell1->align = align_top; //ALIGN_TOP;
		pCellParent->pCell2->align = align_bottom;//ALIGN_BOTTOM;
	}break;
	default: XMessageBox(hWindow, L"在API:XFrameWnd_AddPane()中,参数[align]错误", L"炫彩界面库-错误提示!");
		return FALSE;
	}

	return TRUE;
}

/// @brief 调整框架窗口布局.
/// @param hWindow  窗口资源句柄.
/// @param bFixedSize   是否检查窗格为固定大小.
void WINAPI XFrameWnd_AdjustLayout(HWINDOW hWindow, BOOL bFixedSize)
{
	IsFrameWindowDebug(hWindow, __FUNCTION__);
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	if (pFrameWnd->hPierLeft)
	{
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.bottom = rect.bottom;
		rc.right = FRAME_PIER_WIDTH;
		XEle_SetRect(pFrameWnd->hPierLeft, &rc);

		Pier_AdjustLayout(pFrameWnd->hPierLeft);
	}
	if (pFrameWnd->hPierRight)
	{
		RECT rc;
		rc.top = 0;
		rc.bottom = rect.bottom;
		rc.left = rect.right - FRAME_PIER_WIDTH;
		rc.right = rect.right;
		XEle_SetRect(pFrameWnd->hPierRight, &rc);

		Pier_AdjustLayout(pFrameWnd->hPierRight);
	}

	if (pFrameWnd->hPierTop)
	{
		RECT rc;
		if (pFrameWnd->hPierLeft)
			rc.left = FRAME_PIER_WIDTH;
		else
			rc.left = 0;
		if (pFrameWnd->hPierRight)
			rc.right = rect.right - FRAME_PIER_WIDTH;
		else
			rc.right = rect.right;

		rc.top = 0;
		rc.bottom = FRAME_PIER_WIDTH;
		XEle_SetRect(pFrameWnd->hPierTop, &rc);

		Pier_AdjustLayout(pFrameWnd->hPierTop);
	}

	if (pFrameWnd->hPierBottom)
	{
		RECT rc;
		if (pFrameWnd->hPierLeft)
			rc.left = FRAME_PIER_WIDTH;
		else
			rc.left = 0;
		if (pFrameWnd->hPierRight)
			rc.right = rect.right - FRAME_PIER_WIDTH;
		else
			rc.right = rect.right;

		rc.top = rect.bottom - FRAME_PIER_WIDTH;
		rc.bottom = rect.bottom;
		XEle_SetRect(pFrameWnd->hPierBottom, &rc);

		Pier_AdjustLayout(pFrameWnd->hPierBottom);
	}

	Cell_OnSize(pFrameWnd->pCell, hWindow, bFixedSize);
}

/// @brief 获取客户区布局区域坐标.
/// @param hWindow  窗口资源句柄.
/// @param pRect  接收坐标.
void WINAPI XFrameWnd_GetLayoutAreaRect(HWINDOW hWindow, out_ RECT *pRect) //获取客户区布局区域坐标
{
	IsFrameWindowDebug(hWindow, __FUNCTION__);

	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	if (pFrameWnd->pCell)
	{
		*pRect = pFrameWnd->pCell->rect;
		return;
	}

	XWnd_GetClientRect(hWindow, pRect);
	if (pFrameWnd->hPierLeft)
		pRect->left += FRAME_PIER_WIDTH;

	if (pFrameWnd->hPierTop)
		pRect->top += FRAME_PIER_WIDTH;

	if (pFrameWnd->hPierRight)
		pRect->right -= FRAME_PIER_WIDTH;

	if (pFrameWnd->hPierBottom)
		pRect->bottom -= FRAME_PIER_WIDTH;
}

/// @brief 获取框架窗口内激活的窗格,不包含浮动窗格.
/// @param hWindow  窗口资源句柄.
/// @return 返回当前活动窗格.
HELE WINAPI XFrameWnd_GetActivatePane(HWINDOW hWindow)  //获取框架窗口内激活的窗格,不包含浮动窗格
{
	IsFrameWindowDebug(hWindow, __FUNCTION__);
	return ((frameWnd_*)hWindow)->hPaneActivate;
}

///@}

BOOL CALLBACK FrameWnd_OnSize(HWINDOW hWindow, UINT type, SIZE *pSize)  //ON SIZE 窗口大小改变
{
	if (FALSE == IsIconic(XWnd_GetHWnd(hWindow)))
	{
		frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
		if (pFrameWnd->hPaneExpand)
		{
			FrameWnd_PierShrink(hWindow);
		}
		XFrameWnd_AdjustLayout(hWindow, TRUE);
	}
	return FALSE;
}

BOOL CALLBACK FrameWnd_OnWndDestroy(HWINDOW hWindow)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	FrameWnd_DestroyCell(pFrameWnd->pCell);
	return FALSE;
}

void FrameWnd_DestroyCell(layoutCell_ *pCell)
{
	if (pCell)
	{
		if (cell_type_group == pCell->type)
		{
			int count = XArray_GetCount(pCell->hArrayList);
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCell->hArrayList, i);
				Cell_Destroy(pChild);
			}
		}
		else
		{
			FrameWnd_DestroyCell(pCell->pCell1);
			FrameWnd_DestroyCell(pCell->pCell2);
		}
		Cell_Destroy(pCell);
	}
}

BOOL FrameWnd_PierShrink(HWINDOW hWindow) //收缩展开的窗格
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	if (pFrameWnd->hPaneExpand)
	{
		layoutPane_ *pPane = (layoutPane_*)pFrameWnd->hPaneExpand;
		layoutCell_ *pCell = Pane_GetCell(pFrameWnd->hPaneExpand);

		switch (pPane->dockAlign)
		{
		case align_left:
			Pier_SetCheck(pFrameWnd->hPierLeft, pCell);
			break;
		case align_top:
			Pier_SetCheck(pFrameWnd->hPierTop, pCell);
			break;
		case align_right:
			Pier_SetCheck(pFrameWnd->hPierRight, pCell);
			break;
		case align_bottom:
			Pier_SetCheck(pFrameWnd->hPierBottom, pCell);
			break;
		}
		//收缩展开的窗格
		XEle_ShowEle(pFrameWnd->hPaneExpand, FALSE);
		XEle_ShowEle(pCell->hDragBar, FALSE);
		pFrameWnd->hPaneExpand = NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK FrameWnd_OnLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	if (pFrameWnd->hPaneExpand)
	{
		layoutCell_ *pCell = Pane_GetCell(pFrameWnd->hPaneExpand);
		if (FALSE == PtInRect(&pCell->rect, *pPt))
		{
			//收缩展开的窗格
			FrameWnd_PierShrink(hWindow);
			XWnd_RedrawWnd(hWindow);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK FrameWnd_TabBar_Btn_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	frameWnd_ *pFrame = (frameWnd_*)XEle_GetHWindow(hEle);
	pFrame->bDown_TabBar = TRUE;
	pFrame->ptDown_TabBar = *pPt;
	return FALSE;
}

BOOL CALLBACK FrameWnd_TabBar_Btn_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	frameWnd_ *pFrame = (frameWnd_*)XEle_GetHWindow(hEle);
	pFrame->bDown_TabBar = FALSE;
	return FALSE;
}

BOOL CALLBACK FrameWnd_TabBar_Btn_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	frameWnd_ *pFrame = (frameWnd_*)XEle_GetHWindow(hEle);
	if (pFrame->bDown_TabBar)
	{
		if (pPt->x<(pFrame->ptDown_TabBar.x - 5) || pPt->x>(pFrame->ptDown_TabBar.x + 5)
			|| pPt->y<(pFrame->ptDown_TabBar.y - 5) || pPt->y>(pFrame->ptDown_TabBar.y + 5))
		{
			pFrame->bDown_TabBar = FALSE;

			layoutCell_  *pCell = (layoutCell_*)XEle_GetUserData(hEle);

			FrameWnd_DragPane((HWINDOW)pFrame, pCell, pPt);
			Ele_SendEvent(pCell->hPane, XE_PANE_FLOAT, 0, 0);

			XFrameWnd_AdjustLayout((HWINDOW)pFrame);
			XWnd_RedrawWnd((HWINDOW)pFrame);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK FrameWnd_TabBar_Btn_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	frameWnd_ *pFrame = (frameWnd_*)XEle_GetHWindow(hEle);
	pFrame->bDown_TabBar = FALSE;
	return FALSE;
}

BOOL FrameWnd_PierPopupPane(HWINDOW hWindow, HELE hPane) //弹出窗格,当在码头上时
{
	HWINDOW hFrame = hWindow;
	frameWnd_ *pFrame = (frameWnd_*)hFrame;
	layoutPane_ *pPane = (layoutPane_*)hPane;
	if (pFrame->hPaneExpand)
		return FALSE;

	layoutCell_ *pCell = Pane_GetCell(hPane);

	XEle_SetZOrder(hPane);

	XEle_ShowEle(hPane, SW_SHOW);
	pFrame->hPaneExpand = hPane;

	RECT rect;
	XWnd_GetClientRect(hFrame, &rect);

	RECT rcPane;
	XEle_GetClientRect(pCell->hPane, &rcPane);

	//调整窗格大小
	switch (pPane->dockAlign)
	{
	case align_left:
	{
		if (pFrame->hPierTop)
			rect.top = FRAME_PIER_WIDTH;
		if (pFrame->hPierBottom)
			rect.bottom -= FRAME_PIER_WIDTH;

		int width = rcPane.right - rcPane.left;
		pCell->rect.left = FRAME_PIER_WIDTH;
		pCell->rect.top = rect.top;
		pCell->rect.right = pCell->rect.left + width + PANE_DRAGBAR_WIDTH;
		pCell->rect.bottom = rect.bottom;
	}break;
	case align_top:
	{
		if (pFrame->hPierLeft)
			rect.left = FRAME_PIER_WIDTH;
		if (pFrame->hPierRight)
			rect.right -= FRAME_PIER_WIDTH;

		int height = rcPane.bottom - rcPane.top;
		pCell->rect.left = rect.left;
		pCell->rect.top = FRAME_PIER_WIDTH;
		pCell->rect.right = rect.right;
		pCell->rect.bottom = pCell->rect.top + height + PANE_DRAGBAR_WIDTH;
	}break;
	case align_right:
	{
		if (pFrame->hPierTop)
			rect.top = FRAME_PIER_WIDTH;
		if (pFrame->hPierBottom)
			rect.bottom -= FRAME_PIER_WIDTH;

		int width = rcPane.right - rcPane.left;
		pCell->rect.left = rect.right - FRAME_PIER_WIDTH - width - PANE_DRAGBAR_WIDTH;
		pCell->rect.top = rect.top;
		pCell->rect.right = rect.right - FRAME_PIER_WIDTH;
		pCell->rect.bottom = rect.bottom;
	}break;
	case align_bottom:
	{
		if (pFrame->hPierLeft)
			rect.left = FRAME_PIER_WIDTH;
		if (pFrame->hPierRight)
			rect.right -= FRAME_PIER_WIDTH;

		int height = rcPane.bottom - rcPane.top;
		pCell->rect.left = rect.left;
		pCell->rect.top = rect.bottom - FRAME_PIER_WIDTH - height - PANE_DRAGBAR_WIDTH;
		pCell->rect.right = rect.right;
		pCell->rect.bottom = rect.bottom - FRAME_PIER_WIDTH;
	}break;
	}

	Cell_OnSize2(pCell, hWindow, TRUE);

	XEle_ShowEle(pCell->hDragBar, TRUE);
	XEle_SetZOrder(pCell->hDragBar);
	//	XEle_RedrawEle(hPane);
	//	XEle_RedrawEle(pCell->hDragBar);
	XWnd_RedrawWnd(hWindow);

	return TRUE;
}

void FrameWnd_DragPane(HWINDOW hWindow, layoutCell_ *pCell, POINT *pPtDown) //拖动窗格
{
	//判断是窗格还是窗格组
	if (align_group_member == pCell->align)//窗格组成员
	{
		XPane_Hide(pCell->hPane);
		XEle_RemoveEle(pCell->hPane);
		FrameWnd_RemoveCell_GroupMenber(hWindow, pCell);

		pCell->type = cell_type_pane;
		pCell->align = align_any;
		pCell->pParentCell = NULL;

		POINT pt;
		GetCursorPos(&pt);

		int width = pCell->rect.right - pCell->rect.left + 16;
		int height = pCell->rect.bottom - pCell->rect.top + 28 + 8;

		HWINDOW hFloatWnd = FloatWnd_Create(pt.x - pPtDown->x, pt.y - pPtDown->y, width, height, XPane_GetTitle(pCell->hPane), hWindow, pCell);

		//添加到浮动窗口上
		XWnd_AddEle(hFloatWnd, pCell->hPane);
		XEle_ShowEle(pCell->hPane, TRUE);
		((layoutPane_*)pCell->hPane)->state = pane_state_float;
		Cell_OnSize_FloatWnd(pCell, hFloatWnd);

		XWnd_ShowWindow(hFloatWnd, SW_SHOW);
		FloatWnd_DragWindow(hFloatWnd, pPtDown);

	}
	else if (cell_type_pane == pCell->type)  //独立窗格
	{
		Pane_EnableLayout(pCell->hPane, FALSE);
		FrameWnd_RemoveCell(hWindow, pCell); //从布局中移除
		XEle_RemoveEle(pCell->hPane);

		POINT pt;
		GetCursorPos(&pt);

		int width = pCell->rect.right - pCell->rect.left + 16;
		int height = pCell->rect.bottom - pCell->rect.top + 28 + 8;

		HWINDOW hFloatWnd = FloatWnd_Create(pt.x - pPtDown->x, pt.y - pPtDown->y, width, height, XPane_GetTitle(pCell->hPane), hWindow, pCell);

		//添加到浮动窗口上
		XWnd_AddEle(hFloatWnd, pCell->hPane);
		((layoutPane_*)pCell->hPane)->state = pane_state_float;
		Cell_OnSize_FloatWnd(pCell, hFloatWnd);

		XWnd_ShowWindow(hFloatWnd, SW_SHOW);
		FloatWnd_DragWindow(hFloatWnd, pPtDown);
	}
}

//pCell:为窗格组成员
void FrameWnd_DragGroup(HWINDOW hWindow, layoutCell_ *pCell, POINT *pPtDown) //拖动窗格组
{
	if (pCell->pParentCell && cell_type_group == pCell->pParentCell->type) //窗格组成员
	{
		layoutCell_ *pCellCroup = pCell->pParentCell;
		int width = pCell->rect.right - pCell->rect.left + 16;
		int height = pCell->rect.bottom - pCell->rect.top + 28 + 8;

		//脱离框架
		HARRAY hArray = XArray_Create();

		int count = XArray_GetCount(pCellCroup->hArrayList);
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellCroup->hArrayList, i);

			if (TRUE == ((layoutPane_*)pChild->hPane)->bInFrame)
			{
				XArray_Add(hArray, pChild);
			}
		}

		count = XArray_GetCount(hArray);

		if (count < 1)
		{
			MessageBox(NULL, L"拖动窗格组错误,code:009", L"炫彩界面库-错误提示", 0);
			exit(0);
			return;
		}

		//从框架中移除
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(hArray, i);
			Pane_EnableLayout(pChild->hPane, FALSE);
			XEle_RemoveEle(pChild->hPane);
			FrameWnd_RemoveCell(hWindow, pChild);
		}

		if (1 == count) //为窗格
		{
			layoutCell_ *pCellPane = (layoutCell_*)XArray_GetAt(hArray, 0);
			pCellPane->align = align_any;
			pCellPane->type = cell_type_pane;
			pCellPane->pParentCell = NULL;
			((layoutPane_*)pCellPane->hPane)->state = pane_state_float;

			POINT pt;
			GetCursorPos(&pt);

			HWINDOW hFloatWnd = FloatWnd_Create(pt.x - pPtDown->x, pt.y - pPtDown->y, width, height, XPane_GetTitle(pCellPane->hPane), hWindow, pCellPane);

			XWnd_AddEle(hFloatWnd, pCellPane->hPane);
			Cell_OnSize_FloatWnd(pCellPane, hFloatWnd);
			XWnd_ShowWindow(hFloatWnd, SW_SHOW);

			FloatWnd_DragWindow(hFloatWnd, pPtDown);
		}
		else //为组
		{
			layoutCell_ *pCellGroupNew = Cell_Create(hWindow, NULL, align_any);
			pCellGroupNew->type = cell_type_group;

			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(hArray, i);
				pChild->align = align_group_member;
				pChild->pParentCell = pCellGroupNew;
				((layoutPane_*)pChild->hPane)->state = pane_state_float;
				XArray_Add(pCellGroupNew->hArrayList, pChild);
			}

			POINT pt;
			GetCursorPos(&pt);

			HWINDOW hFloatWnd = FloatWnd_Create(pt.x - pPtDown->x, pt.y - pPtDown->y, width, height, XPane_GetTitle(pCell->hPane), hWindow, pCellGroupNew);

			pCellGroupNew->hTabBar = XTabBar_Create(0, 0, 20, 20, hFloatWnd);
			for (int i = 0; i < count; i++)
			{
				layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(hArray, i);

				XWnd_AddEle(hFloatWnd, pChild->hPane);
				XTabBar_AddLabel(pCellGroupNew->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);
			}

			Cell_OnSize_FloatWnd(pCellGroupNew, hFloatWnd);

			XEle_RegisterEvent(pCellGroupNew->hTabBar, XE_TABBAR_SELECT, FloatWnd_OnEventTabBarSelect);
			XWnd_ShowWindow(hFloatWnd, SW_SHOW);
			FloatWnd_DragWindow(hFloatWnd, pPtDown);
		}

		XArray_Destroy(hArray);
	}
}

void FrameWnd_FloatPane(HWINDOW hWindow, layoutCell_ *pCell) //浮动窗格
{
	//从框架窗口移除窗格
	//创建浮动窗口
	//将窗格添加到浮动窗口上
	//拖动浮动窗口,如果需要拖动

	layoutPane_ *pPane = (layoutPane_*)pCell->hPane;

	if (align_group_member == pCell->align)//窗格组
	{
		FrameWnd_FloatGroup(hWindow, pCell->pParentCell);
		////////////////////////////////////////
	}
	else if (cell_type_pane == pCell->type)//独立窗格
	{
		RECT rect;
		XEle_GetClientRect(pCell->hPane, &rect);

		XEle_RectToNCWnd(pCell->hPane, &rect);
		POINT pt = { rect.left,rect.top };
		int width = rect.right - rect.left + 16;
		int height = rect.bottom - rect.top + 28 + 8;

		ClientToScreen(XWnd_GetHWnd(hWindow), &pt);

		Pane_EnableLayout(pCell->hPane, FALSE);
		FrameWnd_RemoveCell(hWindow, pCell); //从布局中移除
		XEle_RemoveEle(pCell->hPane);

		HWINDOW hFloatWnd = FloatWnd_Create(pt.x, pt.y, width, height, XPane_GetTitle(pCell->hPane), hWindow, pCell);

		//添加到浮动窗口上
		XWnd_AddEle(hFloatWnd, pCell->hPane);
		XEle_ShowEle(pCell->hPane, SW_SHOW);
		((layoutPane_*)pCell->hPane)->state = pane_state_float;
		Cell_OnSize_FloatWnd(pCell, hFloatWnd);
		XWnd_ShowWindow(hFloatWnd, SW_SHOW);
	}
}

void FrameWnd_FloatGroup(HWINDOW hWindow, layoutCell_ *pGroupCell) //浮动窗格组
{
	layoutCell_ *pCellCroup = pGroupCell;

	//脱离框架
	HARRAY hArray = XArray_Create();

	int count = XArray_GetCount(pCellCroup->hArrayList);
	for (int i = 0; i < count; i++)
	{
		layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellCroup->hArrayList, i);

		if (TRUE == ((layoutPane_*)pChild->hPane)->bInFrame)
		{
			XArray_Add(hArray, pChild);
		}
	}

	count = XArray_GetCount(hArray);

	if (count < 1)
	{
		MessageBox(NULL, L"拖动窗格组错误,code:010", L"炫彩界面库-错误提示", 0);
		exit(0);
		return;
	}

	layoutCell_ *pChild_1 = (layoutCell_*)XArray_GetAt(hArray, 0);

	RECT rect;
	XEle_GetClientRect(pChild_1->hPane, &rect);

	XEle_RectToNCWnd(pChild_1->hPane, &rect);
	POINT pt = { rect.left,rect.top };
	int width = rect.right - rect.left + 16;
	int height = rect.bottom - rect.top + 28 + 8;

	ClientToScreen(XWnd_GetHWnd(hWindow), &pt);

	//从框架中移除
	for (int i = 0; i < count; i++)
	{
		layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(hArray, i);
		Pane_EnableLayout(pChild->hPane, FALSE);
		FrameWnd_RemoveCell(hWindow, pChild);
		XEle_RemoveEle(pChild->hPane);
	}

	if (1 == count) //为窗格
	{
		pChild_1->align = align_any;
		pChild_1->type = cell_type_pane;
		((layoutPane_*)pChild_1->hPane)->state = pane_state_float;

		HWINDOW hFloatWnd = FloatWnd_Create(pt.x, pt.y, width, height, XPane_GetTitle(pChild_1->hPane), hWindow, pChild_1);

		//添加到浮动窗口上
		XWnd_AddEle(hFloatWnd, pChild_1->hPane);
		XEle_ShowEle(pChild_1->hPane, SW_SHOW);
		((layoutPane_*)pChild_1->hPane)->state = pane_state_float;
		Cell_OnSize_FloatWnd(pChild_1, hFloatWnd);
		XWnd_ShowWindow(hFloatWnd, SW_SHOW);

	}
	else //为组
	{
		layoutCell_ *pCellGroupNew = Cell_Create(hWindow, NULL, align_any);
		pCellGroupNew->type = cell_type_group;

		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(hArray, i);
			pChild->align = align_group_member;
			pChild->pParentCell = pCellGroupNew;
			((layoutPane_*)pChild->hPane)->state = pane_state_float;
			XArray_Add(pCellGroupNew->hArrayList, pChild);
		}

		HWINDOW hFloatWnd = FloatWnd_Create(pt.x, pt.y, width, height, XPane_GetTitle(pChild_1->hPane), hWindow, pCellGroupNew);

		pCellGroupNew->hTabBar = XTabBar_Create(0, 0, 20, 20, hFloatWnd);
		for (int i = 0; i < count; i++)
		{
			layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(hArray, i);

			XWnd_AddEle(hFloatWnd, pChild->hPane);
			XTabBar_AddLabel(pCellGroupNew->hTabBar, XPane_GetTitle(pChild->hPane), pChild->hPane);
		}

		Cell_OnSize_FloatWnd(pCellGroupNew, hFloatWnd);

		XEle_RegisterEvent(pCellGroupNew->hTabBar, XE_TABBAR_SELECT, FloatWnd_OnEventTabBarSelect);
		XWnd_ShowWindow(hFloatWnd, SW_SHOW);
	}

	XArray_Destroy(hArray);
}

//当前版本不处理移除带子单元格
BOOL FrameWnd_RemoveCell(HWINDOW hWindow, layoutCell_ *pCell) //移除窗格
{
	//独立单元格
	//移除组
	//移除组成员

	if (cell_type_group == pCell->type) //移除组
	{
		FrameWnd_RemoveCell_Group(hWindow, pCell);
	}
	else if (pCell->pParentCell && cell_type_group == pCell->pParentCell->type) //移除组成员
	{
		FrameWnd_RemoveCell_GroupMenber(hWindow, pCell);
	}
	else if (cell_type_pane == pCell->type)//独立单元格
	{
		FrameWnd_RemoveCell_Pane(hWindow, pCell);
	}
	return TRUE;
}

BOOL FrameWnd_RemoveCell_Pane(HWINDOW hWindow, layoutCell_ *pCell)
{
	frameWnd_   *pFrameWnd = (frameWnd_*)hWindow;
	layoutCell_ * const pParentCell = pCell->pParentCell;

	if (pFrameWnd->pCell == pCell || NULL == pParentCell) //顶级单元格
	{
		pFrameWnd->pCell = NULL;
	}
	else //子单元格
	{
		if (pParentCell->hDragBar)
		{
			XEle_Destroy(pParentCell->hDragBar);
			pParentCell->hDragBar = NULL;
		}

		layoutCell_  *pCell_new;
		if (pParentCell->pCell1 == pCell)
		{
			pCell_new = pParentCell->pCell2;
		}
		else if (pParentCell->pCell2 == pCell)
		{
			pCell_new = pParentCell->pCell1;
		}
		else
			return FALSE;

		pCell_new->scale = pCell_new->pParentCell->scale;

		if (pCell_new->pParentCell->pParentCell)
		{
			if (pCell_new->pParentCell->pParentCell->pCell1 == pCell_new->pParentCell)
				pCell_new->pParentCell->pParentCell->pCell1 = pCell_new;
			else if (pCell_new->pParentCell->pParentCell->pCell2 == pCell_new->pParentCell)
				pCell_new->pParentCell->pParentCell->pCell2 = pCell_new;
			else
				return FALSE;
		}
		else
		{
			pFrameWnd->pCell = pCell_new;
		}

		pCell_new->align = pCell_new->pParentCell->align;
		pCell_new->pParentCell = pCell_new->pParentCell->pParentCell;
	}

	pCell->pParentCell = NULL;

	Cell_Destroy(pParentCell);
	return TRUE;
}

BOOL FrameWnd_RemoveCell_Group(HWINDOW hWindow, layoutCell_ *pCell)
{
	FrameWnd_RemoveCell_Pane(hWindow, pCell);

	int count = XArray_GetCount(pCell->hArrayList);
	for (int i = 0; i < count; i++)
	{
		layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCell->hArrayList, i);
		XEle_RemoveEle(pChild->hPane);
	}

	XEle_Destroy(pCell->hTabBar);
	pCell->hTabBar = NULL;

	return TRUE;
}

//pCell:为组成员
BOOL FrameWnd_RemoveCell_GroupMenber(HWINDOW hWindow, layoutCell_ *pCell)
{
	frameWnd_   *pFrameWnd = (frameWnd_*)hWindow;

	if (cell_type_pane != pCell->type)
		return FALSE;

	layoutCell_  *pGroupCell = pCell->pParentCell;

	XArray_Delete(pGroupCell->hArrayList, pCell);
	pCell->pParentCell = NULL;
	pCell->align = align_any;

	int index = XTabBar_GetPageIndex(pGroupCell->hTabBar, pCell->hPane);
	if (index >= 0)
		XTabBar_DeleteLabel(pGroupCell->hTabBar, index);

	int count = XArray_GetCount(pGroupCell->hArrayList);
	if (1 == count)//如果组成员为1,将转换为独立窗格
	{
		XEle_Destroy(pGroupCell->hTabBar);
		pGroupCell->hTabBar = NULL;

		layoutCell_ *pNewCell = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, 0);

		if (NULL == pGroupCell->pParentCell)
		{
			pFrameWnd->pCell = pNewCell;
			pFrameWnd->pCell->align = align_any;
			pFrameWnd->pCell->pParentCell = NULL;
		}
		else
		{
			if (pGroupCell->pParentCell->pCell1 == pGroupCell)
			{
				pGroupCell->pParentCell->pCell1 = pNewCell;
			}
			else if (pGroupCell->pParentCell->pCell2 == pGroupCell)
			{
				pGroupCell->pParentCell->pCell2 = pNewCell;
			}
			else
				return FALSE;

			pNewCell->pParentCell = pGroupCell->pParentCell;
			pNewCell->scale = pGroupCell->scale;
			pNewCell->align = pGroupCell->align;
			pNewCell->type = cell_type_pane;
		}
		Cell_Destroy(pGroupCell);
		return TRUE;
	}
	else
	{
		int c = XTabBar_GetLabelCount(pGroupCell->hTabBar);
		if (1 == c)
		{
			XTabBar_DeleteLabelAll(pGroupCell->hTabBar);
			XEle_ShowEle(pGroupCell->hTabBar, FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

void FrameWnd_AddPier(HWINDOW hWindow, layoutCell_ *pCell)
{
	frameWnd_   *pFrameWnd = (frameWnd_*)hWindow;
	layoutCell_ *pPaneCell = pCell;//Pane_GetCell(hPane);
	layoutPane_ *pPane = (layoutPane_*)pCell->hPane;

	switch (pPaneCell->align)
	{
	case align_any:
	case align_left:
		if (NULL == pFrameWnd->hPierLeft)
		{
			pFrameWnd->hPierLeft = Pier_Create(align_left, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierLeft, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierLeft, RGB(220, 220, 220));
		}
		pPane->dockAlign = align_left;
		Pier_AddCell(pFrameWnd->hPierLeft, pPane->pCell);
		break;
	case align_top:
		if (NULL == pFrameWnd->hPierTop)
		{
			pFrameWnd->hPierTop = Pier_Create(align_top, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierTop, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierTop, RGB(220, 220, 220));
		}
		pPane->dockAlign = align_top;
		Pier_AddCell(pFrameWnd->hPierTop, pPane->pCell);
		break;
	case align_right:
		if (NULL == pFrameWnd->hPierRight)
		{
			pFrameWnd->hPierRight = Pier_Create(align_right, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierRight, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierRight, RGB(220, 220, 220));
		}
		pPane->dockAlign = align_right;
		Pier_AddCell(pFrameWnd->hPierRight, pPane->pCell);
		break;
	case align_bottom:
		if (NULL == pFrameWnd->hPierBottom)
		{
			pFrameWnd->hPierBottom = Pier_Create(align_bottom, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierBottom, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierBottom, RGB(220, 220, 220));
		}
		pPane->dockAlign = align_bottom;
		Pier_AddCell(pFrameWnd->hPierBottom, pPane->pCell);
		break;
	}
}

void FrameWnd_AddPierGroup(HWINDOW hWindow, layoutCell_ *pGroupCell)
{
	frameWnd_   *pFrameWnd = (frameWnd_*)hWindow;
	switch (pGroupCell->align)
	{
	case align_any:
	case align_left:
		if (NULL == pFrameWnd->hPierLeft)
		{
			pFrameWnd->hPierLeft = Pier_Create(align_left, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierLeft, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierLeft, RGB(220, 220, 220));
		}
		Pier_AddCellGroup(pFrameWnd->hPierLeft, pGroupCell);
		break;
	case align_top:
		if (NULL == pFrameWnd->hPierTop)
		{
			pFrameWnd->hPierTop = Pier_Create(align_top, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierTop, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierTop, RGB(220, 220, 220));
		}
		Pier_AddCellGroup(pFrameWnd->hPierTop, pGroupCell);
		break;
	case align_right:
		if (NULL == pFrameWnd->hPierRight)
		{
			pFrameWnd->hPierRight = Pier_Create(align_right, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierRight, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierRight, RGB(220, 220, 220));
		}
		Pier_AddCellGroup(pFrameWnd->hPierRight, pGroupCell);
		break;
	case align_bottom:
		if (NULL == pFrameWnd->hPierBottom)
		{
			pFrameWnd->hPierBottom = Pier_Create(align_bottom, hWindow);
			XEle_EnableBorder(pFrameWnd->hPierBottom, FALSE);
			XEle_SetBkColor(pFrameWnd->hPierBottom, RGB(220, 220, 220));
		}
		Pier_AddCellGroup(pFrameWnd->hPierBottom, pGroupCell);
		break;
	}
}

void FrameWnd_RemovePier(HWINDOW hWindow, HELE hPane) //从码头移除窗格
{
	layoutCell_ *pPaneCell = Pane_GetCell(hPane);
	if (pPaneCell->pParentCell && cell_type_group == pPaneCell->pParentCell->type)
	{
		FrameWnd_RemovePierGroup(hWindow, hPane);
		return;
	}

	frameWnd_ *pFrame = (frameWnd_*)hWindow;
	layoutPane_ *pPane = (layoutPane_*)hPane;

	if (pFrame->hPaneExpand)
		FrameWnd_PierShrink(hWindow);

	switch (pPane->dockAlign)
	{
	case align_left:
	case align_any:	   Pier_RemoveCell(pFrame->hPierLeft, pPaneCell);    break;
	case align_top:    Pier_RemoveCell(pFrame->hPierTop, pPaneCell);     break;
	case align_right:  Pier_RemoveCell(pFrame->hPierRight, pPaneCell);   break;
	case align_bottom: Pier_RemoveCell(pFrame->hPierBottom, pPaneCell);  break;
	}
}

void FrameWnd_RemovePierGroup(HWINDOW hWindow, HELE hPane) //从码头移除窗格组
{
	frameWnd_ *pFrame = (frameWnd_*)hWindow;
	layoutCell_ *pPaneCell = Pane_GetCell(hPane);

	if (pFrame->hPaneExpand)
		FrameWnd_PierShrink(hWindow);

	layoutPane_ *pPane = (layoutPane_*)hPane;

	switch (pPane->dockAlign)
	{
	case align_left:
	case align_any:	   Pier_RemoveCellGroup(pFrame->hPierLeft, pPane->pCell);    break;
	case align_top:    Pier_RemoveCellGroup(pFrame->hPierTop, pPane->pCell);     break;
	case align_right:  Pier_RemoveCellGroup(pFrame->hPierRight, pPane->pCell);   break;
	case align_bottom: Pier_RemoveCellGroup(pFrame->hPierBottom, pPane->pCell);  break;
	}
}

//创建停靠提示及停靠位置预览窗口,临时窗口
void FrameWnd_CreateTempWindow(HWINDOW hWindow)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	if (NULL == pFrameWnd->hDockPane)
	{
		HWND hWnd = XWnd_GetHWnd(pFrameWnd->hFloatWnd);

		RECT rcWindow;
		XWnd_GetWindowRect(hWindow, &rcWindow);
		RECT rcClient;
		XWnd_GetClientRect(hWindow, &rcClient);

		int headerHeight = XWnd_GetClientTop(hWindow);

		int topCenter = rcWindow.top + headerHeight + (rcClient.bottom - rcClient.top) / 2 - 35 / 2;

		int left = XWnd_GetClientLeft(hWindow);

		int leftCenter = rcWindow.left + (rcWindow.right - rcWindow.left) / 2 - 35 / 2;

		//创建窗格停靠提示,十字
		pFrameWnd->hDockPane = XWnd_CreateWindow(50, 50, 115, 115, L"dockPane", hWnd, 0);
		XWnd_SetBkColor(pFrameWnd->hDockPane, RGB(255, 0, 0));
		XWnd_SetTransparentColor(pFrameWnd->hDockPane, RGB(255, 0, 0));
		XWnd_SetTransparentAlpha(pFrameWnd->hDockPane, 255);
		XWnd_SetTransparentFlag(pFrameWnd->hDockPane, XC_WIND_TRANSPARENT_SIMPLE);

		//注册自绘
		XWnd_RegisterMessage(pFrameWnd->hDockPane, WM_PAINT, FrameWnd_OnWndDrawWindow_dockPane);

		//创建边框停靠提示
		//left
		pFrameWnd->hDockLeft = XWnd_CreateWindow(rcWindow.left + left + 10, topCenter, 35, 35, L"dockLeft", hWnd, 0);
		//	XWnd_ShowWindow(pFrameWnd->hDockLeft,SW_SHOW);

		//top
		pFrameWnd->hDockTop = XWnd_CreateWindow(leftCenter, rcWindow.top + headerHeight + 10, 35, 35, L"dockTop", hWnd, 0);
		//	XWnd_ShowWindow(pFrameWnd->hDockTop,SW_SHOW);

		//right
		pFrameWnd->hDockRight = XWnd_CreateWindow(rcWindow.left + left + rcClient.right - 35 - 10, topCenter, 35, 35, L"dockRight", hWnd, 0);
		//	XWnd_ShowWindow(pFrameWnd->hDockRight,SW_SHOW);

		//bottom
		pFrameWnd->hDockBottom = XWnd_CreateWindow(leftCenter, rcWindow.top + headerHeight + rcClient.bottom - 35 - 10, 35, 35, L"dockBottom", hWnd, 0);
		//	XWnd_ShowWindow(pFrameWnd->hDockBottom,SW_SHOW);

		//	XWnd_SetBkColor(pFrameWnd->hDockLeft,RGB(100,100,100));
		//	XWnd_SetBkColor(pFrameWnd->hDockTop,RGB(100,100,100));
		//	XWnd_SetBkColor(pFrameWnd->hDockRight,RGB(100,100,100));
		//	XWnd_SetBkColor(pFrameWnd->hDockBottom,RGB(100,100,100));

		XWnd_RegisterMessage(pFrameWnd->hDockLeft, WM_PAINT, FrameWnd_OnWndDrawWindow_dockLeft);
		XWnd_RegisterMessage(pFrameWnd->hDockTop, WM_PAINT, FrameWnd_OnWndDrawWindow_dockTop);
		XWnd_RegisterMessage(pFrameWnd->hDockRight, WM_PAINT, FrameWnd_OnWndDrawWindow_dockRight);
		XWnd_RegisterMessage(pFrameWnd->hDockBottom, WM_PAINT, FrameWnd_OnWndDrawWindow_dockBottom);

		//停靠预览
		pFrameWnd->hDockPreview = XWnd_CreateWindow(0, 0, 100, 100, L"dockPreview", hWnd, 0);
		XWnd_SetBkColor(pFrameWnd->hDockPreview, RGB(100, 100, 100));
		XWnd_SetTransparentAlpha(pFrameWnd->hDockPreview, 128);
		XWnd_SetTransparentFlag(pFrameWnd->hDockPreview, XC_WIND_TRANSPARENT_SIMPLE);
	}
}

void FrameWnd_OnFloatWnd_Move(HWINDOW hWindow, POINT *pPt)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	//判断是否在框架窗口内
	RECT rcWindow;
	XWnd_GetWindowRect(hWindow, &rcWindow);
	if (PtInRect(&rcWindow, *pPt)) //在框架内
	{
		//	XTRACE("in \n");
		FrameWnd_OnFloatWnd_Move_inFrame(hWindow, pPt); //处理

	}
	else //在框架外
	{
		//隐藏题库提示

		//XTRACE("out \n");

		HWND hWnd = ((window_*)(pFrameWnd->hDockLeft))->hWnd;
		if (IsWindowVisible(hWnd)) //显示窗口边框停靠提示
		{
			XWnd_ShowWindow(pFrameWnd->hDockLeft, SW_HIDE);
			XWnd_ShowWindow(pFrameWnd->hDockTop, SW_HIDE);
			XWnd_ShowWindow(pFrameWnd->hDockRight, SW_HIDE);
			XWnd_ShowWindow(pFrameWnd->hDockBottom, SW_HIDE);
		}

		if (XWnd_IsWindowVisible(pFrameWnd->hDockPane))
		{
			XWnd_ShowWindow(pFrameWnd->hDockPane, SW_HIDE);
			pFrameWnd->pCell_stay = NULL;
		}
	}
}

BOOL FrameWnd_OnFloatWnd_Move2(HWINDOW hWindow, layoutCell_ *pCell, POINT *pPt, POINT *pPtWindow) //遍历单元格
{
	if (NULL == pCell)
		return FALSE;

	if (cell_type_pane == pCell->type || cell_type_group == pCell->type)
	{
		if (FALSE == Cell_IsChildInLayout(pCell))
			return FALSE;

		if (PtInRect(&pCell->rect, *pPt))
		{
			frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
			if (pFrameWnd->pCell_stay != pCell)
			{
				pFrameWnd->pCell_stay = pCell;

				if (pCell->hPane)
				{
					wchar_t *pTitle = XPane_GetTitle(pCell->hPane);

					//停靠提示
					if (pTitle)
						XTRACEW(L"title=%s \n", pTitle);
				}

				//更新提示显示坐标
				RECT rcWindow;
				XWnd_GetWindowRect(hWindow, &rcWindow);
				int left = XWnd_GetClientLeft(hWindow);
				int top = XWnd_GetClientTop(hWindow);

				int x = rcWindow.left + pCell->rect.left + (pCell->rect.right - pCell->rect.left) / 2 - 115 / 2 + left;
				int y = rcWindow.top + pCell->rect.top + (pCell->rect.bottom - pCell->rect.top) / 2 - 115 / 2 + top;
				XWnd_SetWindowPos(pFrameWnd->hDockPane, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			}
			return TRUE;
		}
		return FALSE;
	}
	if (FrameWnd_OnFloatWnd_Move2(hWindow, pCell->pCell1, pPt, pPtWindow))
		return TRUE;
	if (FrameWnd_OnFloatWnd_Move2(hWindow, pCell->pCell2, pPt, pPtWindow))
		return TRUE;

	return FALSE;
}

void FrameWnd_OnFloatWnd_Move_inFrame(HWINDOW hWindow, POINT *pPt)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	RECT rcWindow;
	XWnd_GetWindowRect(hWindow, &rcWindow);

	HWND hWnd = ((window_*)(pFrameWnd->hDockLeft))->hWnd;
	if (FALSE == IsWindowVisible(hWnd)) //显示窗口边框停靠提示
	{
		XWnd_SetWindowPos(pFrameWnd->hDockLeft, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
		XWnd_SetWindowPos(pFrameWnd->hDockTop, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
		XWnd_SetWindowPos(pFrameWnd->hDockRight, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
		XWnd_SetWindowPos(pFrameWnd->hDockBottom, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}

	//检查在布局中是否有显示的窗格
	BOOL bShowPane = FALSE;
	if (pFrameWnd->pCell)
		bShowPane = Cell_IsChildInLayout(pFrameWnd->pCell);

	//没有布局单元格
	if (FALSE == bShowPane)
	{
		BOOL res = FrameWnd_OnFloatWnd_CeckInDockPrompt_border(hWindow, pPt);
		if (FALSE == res)
		{
			//不在停靠提示上,隐藏停靠预览
			if (XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
			{
				//	XTRACE("out-1 \n");
				XWnd_ShowWindow(pFrameWnd->hDockPreview, SW_HIDE);
			}
		}
		return;
	}

	//转换到窗口客户区坐标
	POINT pt = *pPt;
	ScreenToClient(XWnd_GetHWnd(hWindow), &pt);
	pt.x -= XWnd_GetClientLeft(hWindow);
	pt.y -= XWnd_GetClientTop(hWindow);

	BOOL res = FrameWnd_OnFloatWnd_Move2(hWindow, pFrameWnd->pCell, &pt, pPt);//在窗格内返回true

	BOOL bShow = FALSE;
	//如果停靠提示显示,判断是否在停靠提示上
	//如果在停靠提示上,显示停靠位置预览
	if (XWnd_IsWindowVisible(pFrameWnd->hDockPane))
	{
		if (FALSE == res)
		{
			XWnd_ShowWindow(pFrameWnd->hDockPane, SW_HIDE);
			pFrameWnd->pCell_stay = NULL;
		}

		bShow = FrameWnd_OnFloatWnd_CheckInDockPrompt(hWindow, pPt);//在停靠提示上
	}

	if (FALSE == bShow)
	{
		//判断是否在框架窗口边框停靠提示上
		bShow = FrameWnd_OnFloatWnd_CeckInDockPrompt_border(hWindow, pPt);
		if (FALSE == bShow)
		{
			//不在停靠提示上,隐藏停靠预览
			if (XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
			{
				//	XTRACE("out-1 \n");
				XWnd_ShowWindow(pFrameWnd->hDockPreview, SW_HIDE);
			}
		}
	}
}

BOOL FrameWnd_OnFloatWnd_CheckInDockPrompt(HWINDOW hWindow, POINT *pPt)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	RECT rcWindow;
	XWnd_GetWindowRect(hWindow, &rcWindow);

	POINT ptWindow = *pPt;

	RECT rcPanePrompt;
	XWnd_GetWindowRect(pFrameWnd->hDockPane, &rcPanePrompt);

	RECT rcPane;
	XWnd_GetClientRect(pFrameWnd->hFloatWnd, &rcPane);

	///////////////////////////////////////////
	RECT rcLeft;
	rcLeft.left = rcPanePrompt.left;
	rcLeft.top = rcPanePrompt.top + 40;
	rcLeft.right = rcPanePrompt.left + 35;
	rcLeft.bottom = rcLeft.top + 35;

	if (PtInRect(&rcLeft, ptWindow)) //在停靠提示上 left
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			//	XTRACE("in-1 \n");

			int x = rcWindow.left + pFrameWnd->pCell_stay->rect.left;
			int y = rcWindow.top + pFrameWnd->pCell_stay->rect.top;
			int cx = pFrameWnd->pCell_stay->rect.right - pFrameWnd->pCell_stay->rect.left;
			int cy = pFrameWnd->pCell_stay->rect.bottom - pFrameWnd->pCell_stay->rect.top;

			double scale = 0.5;
			if (0 != cx)
				scale = (double)rcPane.right / cx;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cx = (int)(cx*scale);

			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);
			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_left;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 1;
		}
		return TRUE;
	}

	////////////////////////////////////////////////////
	RECT rcTop;
	rcTop.left = rcPanePrompt.left + 40;
	rcTop.top = rcPanePrompt.top;
	rcTop.right = rcTop.left + 35;
	rcTop.bottom = rcTop.top + 35;

	if (PtInRect(&rcTop, ptWindow))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			int x = rcWindow.left + pFrameWnd->pCell_stay->rect.left;
			int y = rcWindow.top + pFrameWnd->pCell_stay->rect.top;
			int cx = pFrameWnd->pCell_stay->rect.right - pFrameWnd->pCell_stay->rect.left;
			int cy = pFrameWnd->pCell_stay->rect.bottom - pFrameWnd->pCell_stay->rect.top;
			//cy=(cy*scale)/100;

			double scale = 0.5;
			if (0 != cy)
				scale = (double)rcPane.bottom / cy;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cy = (int)(cy*scale);

			//	Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_top;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 1;
		}
		return TRUE;
	}

	/////////////////////////////////////////////
	RECT rcRight;
	rcRight.left = rcPanePrompt.right - 35;
	rcRight.top = rcPanePrompt.top + 40;
	rcRight.right = rcRight.left + 35;
	rcRight.bottom = rcRight.top + 35;
	if (PtInRect(&rcRight, ptWindow))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			int cx = pFrameWnd->pCell_stay->rect.right - pFrameWnd->pCell_stay->rect.left;
			int cy = pFrameWnd->pCell_stay->rect.bottom - pFrameWnd->pCell_stay->rect.top;

			double scale = 0.5;
			if (0 != cx)
				scale = (double)rcPane.right / cx;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cx = (int)(cx*scale);

			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			int x = rcWindow.left + pFrameWnd->pCell_stay->rect.right - cx;
			int y = rcWindow.top + pFrameWnd->pCell_stay->rect.top;

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_right;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 1;
		}
		return TRUE;
	}

	/////////////////////////////////////////////////////
	RECT rcBottom;
	rcBottom.left = rcPanePrompt.left + 40;
	rcBottom.top = rcPanePrompt.bottom - 35;
	rcBottom.right = rcBottom.left + 35;
	rcBottom.bottom = rcBottom.top + 35;
	if (PtInRect(&rcBottom, ptWindow))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			int cx = pFrameWnd->pCell_stay->rect.right - pFrameWnd->pCell_stay->rect.left;
			int cy = pFrameWnd->pCell_stay->rect.bottom - pFrameWnd->pCell_stay->rect.top;

			double scale = 0.5;
			if (0 != cy)
				scale = (double)rcPane.bottom / cy;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cy = (int)(cy*scale);

			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			int x = rcWindow.left + pFrameWnd->pCell_stay->rect.left;
			int y = rcWindow.top + pFrameWnd->pCell_stay->rect.bottom - cy;

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_bottom;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 1;
		}
		return TRUE;
	}

	////////////////////////////////////
	RECT rcCenter;
	rcCenter.left = rcPanePrompt.left + 40;
	rcCenter.top = rcPanePrompt.top + 40;
	rcCenter.right = rcCenter.left + 35;
	rcCenter.bottom = rcCenter.top + 35;
	if (PtInRect(&rcCenter, ptWindow))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			int cx = pFrameWnd->pCell_stay->rect.right - pFrameWnd->pCell_stay->rect.left;
			int cy = pFrameWnd->pCell_stay->rect.bottom - pFrameWnd->pCell_stay->rect.top;

			//	double scale=(double)rcPane.bottom/cy;
			//	if(scale>0.5)
			//		scale=0.5;
			//	cy=(int)(cy*scale);

			//	Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);

			int x = rcWindow.left + pFrameWnd->pCell_stay->rect.left;
			int y = rcWindow.top + pFrameWnd->pCell_stay->rect.bottom - cy;

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_group_member;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 2;
		}
		return TRUE;
	}

	return FALSE;
}

BOOL FrameWnd_OnFloatWnd_CeckInDockPrompt_border(HWINDOW hWindow, POINT *pPt) //判断是否在框架窗口边框停靠提示上
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;

	RECT rcPane;
	XWnd_GetClientRect(pFrameWnd->hFloatWnd, &rcPane);

	RECT rcWindow;
	XWnd_GetWindowRect(hWindow, &rcWindow);

	RECT rcClient;//=pFrameWnd->pCell->rect;

	XFrameWnd_GetLayoutAreaRect(hWindow, &rcClient);

	RECT rcLeft;
	rcLeft.left = rcWindow.left + XWnd_GetClientLeft(hWindow) + 10;
	rcLeft.top = rcWindow.top + XWnd_GetClientTop(hWindow) + rcClient.bottom / 2 - 35 / 2;
	rcLeft.right = rcLeft.left + 35;
	rcLeft.bottom = rcLeft.top + 35;

	if (PtInRect(&rcLeft, *pPt))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			XTRACE("in frame \n");
			//	XTRACE("in-1 \n");

			int x = rcWindow.left;
			int y = rcWindow.top;
			int cx = rcClient.right - rcClient.left;
			int cy = rcClient.bottom - rcClient.top;

			double scale = 0.5;
			if (0 != cx)
				scale = (double)rcPane.right / cx;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cx = (int)(cx*scale);

			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_left;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 3;
		}
		else
		{
			XTRACE("in frame no \n");
		}
		return TRUE;
	}

	RECT rcTop;
	rcTop.left = rcWindow.left + XWnd_GetClientLeft(hWindow) + rcClient.right / 2 - 35 / 2;
	rcTop.top = rcWindow.top + XWnd_GetClientTop(hWindow) + 10;
	rcTop.right = rcTop.left + 35;
	rcTop.bottom = rcTop.top + 35;
	if (PtInRect(&rcTop, *pPt))
	{
		//XTRACE("in frame \n");
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			//	XTRACE("in-1 \n");

			int x = rcWindow.left;
			int y = rcWindow.top;
			int cx = rcClient.right - rcClient.left;
			int cy = rcClient.bottom - rcClient.top;

			double scale = 0.5;
			if (0 != cy)
				scale = (double)rcPane.bottom / cy;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cy = (int)(cy*scale);

			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_top;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 3;
		}
		return TRUE;
	}

	RECT rcRight;
	rcRight.left = rcWindow.right - XWnd_GetClientRight(hWindow) - 10 - 35;
	rcRight.top = rcWindow.top + XWnd_GetClientTop(hWindow) + rcClient.bottom / 2 - 35 / 2;
	rcRight.right = rcRight.left + 35;
	rcRight.bottom = rcRight.top + 35;
	if (PtInRect(&rcRight, *pPt))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			int cx = rcClient.right - rcClient.left;
			int cy = rcClient.bottom - rcClient.top;

			double scale = 0.5;
			if (0 != cx)
				scale = (double)rcPane.right / cx;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cx = (int)(cx*scale);

			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			int x = rcWindow.left + rcClient.right - cx;
			int y = rcWindow.top;

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_right;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 3;
		}
		return TRUE;
	}

	RECT rcBottom;
	rcBottom.left = rcWindow.left + XWnd_GetClientLeft(hWindow) + rcClient.right / 2 - 35 / 2;
	rcBottom.top = rcWindow.bottom - XWnd_GetClientBottom(hWindow) - 10 - 35;
	rcBottom.right = rcBottom.left + 35;
	rcBottom.bottom = rcBottom.top + 35;
	if (PtInRect(&rcBottom, *pPt))
	{
		if (FALSE == XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
		{
			int cx = rcClient.right - rcClient.left;
			int cy = rcClient.bottom - rcClient.top;

			double scale = 0.5;
			if (0 != cy)
				scale = (double)rcPane.bottom / cy;

			if (IsFlaotZero(scale))
				scale = 0.5;

			if (scale > 0.5)
				scale = 0.5;
			cy = (int)(cy*scale);

			//Pane_GetCell(((floatWindow_*)pFrameWnd->hFloatWnd)->hPane)->scale=(int)(scale*100);
			((floatWindow_*)pFrameWnd->hFloatWnd)->pCell->scale = (int)(scale * 100);

			int x = rcWindow.left;
			int y = rcWindow.top + rcClient.bottom - cy;

			x = x + XWnd_GetClientLeft(hWindow);
			y = y + XWnd_GetClientTop(hWindow);
			pFrameWnd->dockAlign = align_bottom;
			XWnd_SetWindowPos(pFrameWnd->hDockPreview, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			pFrameWnd->dockType = 3;
		}
		return TRUE;
	}

	return FALSE;
}

void FrameWnd_OnFloatWnd_LButtonUp(HWINDOW hWindow)
{
	//判断停靠预览窗口是否显示
	//将浮动窗口移动到框架窗口上
	//修改属性
	//销毁浮动窗口 

	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	if (XWnd_IsWindowVisible(pFrameWnd->hDockPreview))
	{
		layoutCell_ *pCellNew = ((floatWindow_*)pFrameWnd->hFloatWnd)->pCell;
		if (NULL == pCellNew)
		{
			XTRACE("错误:FrameWnd_OnFloatWnd_LButtonUp() \n");
		}
		if (cell_type_pane == pCellNew->type)
		{
			FrameWnd_OnFloatWnd_AddPane(hWindow, pCellNew);
		}
		else if (cell_type_group == pCellNew->type)
		{
			FrameWnd_OnFloatWnd_AddGroup(hWindow, pCellNew);
		}

		XFrameWnd_AdjustLayout(hWindow, FALSE);
		XWnd_RedrawWnd(hWindow);
	}
	FrameWnd_OnFloatWnd_Exit(hWindow);
}

void FrameWnd_OnFloatWnd_Exit(HWINDOW hWindow)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	XWnd_CloseWindow(pFrameWnd->hDockPane);
	XWnd_CloseWindow(pFrameWnd->hDockLeft);
	XWnd_CloseWindow(pFrameWnd->hDockTop);
	XWnd_CloseWindow(pFrameWnd->hDockRight);
	XWnd_CloseWindow(pFrameWnd->hDockBottom);
	XWnd_CloseWindow(pFrameWnd->hDockPreview);
	pFrameWnd->hDockPane = NULL;
	pFrameWnd->hDockLeft = NULL;
	pFrameWnd->hDockTop = NULL;
	pFrameWnd->hDockRight = NULL;
	pFrameWnd->hDockBottom = NULL;
	pFrameWnd->hDockPreview = NULL;
	pFrameWnd->hFloatWnd = NULL;
	pFrameWnd->pCell_stay = NULL;
}

void FrameWnd_OnFloatWnd_AddPane(HWINDOW hWindow, layoutCell_ *pCellNew)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	int scale = pCellNew->scale;
	XEle_RemoveEle(pCellNew->hPane);
	((floatWindow_*)pFrameWnd->hFloatWnd)->pCell = NULL;
	XWnd_CloseWindow(pFrameWnd->hFloatWnd);

	////////////////////////////////////////////////////////////////
	//将窗格从布局中移除
	//将窗格添加到布局新位置

	if (3 == pFrameWnd->dockType) //停留到窗口边框
	{
		FrameWnd_AddT(hWindow, NULL, pCellNew, pFrameWnd->dockAlign, scale);
	}
	else if (2 == pFrameWnd->dockType) //合并
	{
		FrameWnd_Add_MergeT(hWindow, pFrameWnd->pCell_stay, pCellNew, pFrameWnd->dockAlign, scale);
	}
	else if (1 == pFrameWnd->dockType) //组合
	{
		FrameWnd_AddT(hWindow, pFrameWnd->pCell_stay, pCellNew, pFrameWnd->dockAlign, scale);
	}
	layoutPane_ *pPane = (layoutPane_*)pCellNew->hPane;
	XEle_ShowEle(pPane->hBtnClose, TRUE);
	XEle_ShowEle(pPane->hAutoHide, TRUE);
	XEle_ShowEle(pPane->hBtnMenu, TRUE);

	Ele_SendEvent(pCellNew->hPane, XE_PANE_LOACK, 0, 0);
}

void FrameWnd_OnFloatWnd_AddGroup(HWINDOW hWindow, layoutCell_ *pCellNew)
{
	frameWnd_ *pFrameWnd = (frameWnd_*)hWindow;
	int scale = pCellNew->scale;

	//从浮动窗口移除UI元素
	int count = XArray_GetCount(pCellNew->hArrayList);

	if (count < 1)
		return;

	//保存窗格组成员
	HARRAY hArray = XArray_Create();

	for (int i = 0; i < count; i++)
	{
		layoutCell_ *pChild = (layoutCell_*)XArray_GetAt(pCellNew->hArrayList, i);
		layoutPane_   *pPane = (layoutPane_*)pChild->hPane;
		XEle_ShowEle(pPane->hBtnClose, TRUE);
		XEle_ShowEle(pPane->hAutoHide, TRUE);
		XEle_ShowEle(pPane->hBtnMenu, TRUE);
		XEle_RemoveEle(pChild->hPane);

		XArray_Add(hArray, pChild->hPane);
	}

	if (pCellNew->hTabBar)
	{
		XEle_Destroy(pCellNew->hTabBar);
		pCellNew->hTabBar = NULL;
	}

	((floatWindow_*)pFrameWnd->hFloatWnd)->pCell = NULL;
	XWnd_CloseWindow(pFrameWnd->hFloatWnd);

	if (3 == pFrameWnd->dockType) //停留到窗口边框
	{
		FrameWnd_AddT(hWindow, NULL, pCellNew, pFrameWnd->dockAlign, scale);
	}
	else if (2 == pFrameWnd->dockType)
	{
		FrameWnd_Add_MergeT(hWindow, pFrameWnd->pCell_stay, pCellNew, pFrameWnd->dockAlign, scale);
	}
	else if (1 == pFrameWnd->dockType)
	{
		FrameWnd_AddT(hWindow, pFrameWnd->pCell_stay, pCellNew, pFrameWnd->dockAlign, scale);
	}

	int count2 = XArray_GetCount(hArray);
	for (int i = 0; i < count2; i++)
	{
		HELE hPaneSend = (HELE)XArray_GetAt(hArray, i);
		Ele_SendEvent(hPaneSend, XE_PANE_LOACK, 0, 0);
	}
	XArray_Destroy(hArray);
}

BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockPane(HWINDOW hWindow, HDRAW hDraw)
{
	RECT rc = { 0,40,35,75 };
	XDraw_FillSolidRect_(hDraw, &rc, RGB(220, 220, 220));

	RECT rcTop = { 40,0,75,35 };
	XDraw_FillSolidRect_(hDraw, &rcTop, RGB(220, 220, 220));

	RECT rcRight = { 80,40,115,75 };
	XDraw_FillSolidRect_(hDraw, &rcRight, RGB(220, 220, 220));

	RECT rcBottom = { 40,80,75,115 };
	XDraw_FillSolidRect_(hDraw, &rcBottom, RGB(220, 220, 220));

	RECT rcCenter = { 40,40,75,75 };
	XDraw_FillSolidRect_(hDraw, &rcCenter, RGB(220, 220, 220));

	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(160, 160, 160));
	XDraw_FrameRect_(hDraw, &rc, hBrush);
	XDraw_FrameRect_(hDraw, &rcTop, hBrush);
	XDraw_FrameRect_(hDraw, &rcRight, hBrush);
	XDraw_FrameRect_(hDraw, &rcBottom, hBrush);
	XDraw_FrameRect_(hDraw, &rcCenter, hBrush);

	int left = rc.left + (rc.right - rc.left) / 2;
	int top = rc.top + (rc.bottom - rc.top) / 2;
	XDraw_TriangularArrow(hDraw, hBrush, 1, left, top, 7, 12);

	left = rcTop.left + (rcTop.right - rcTop.left) / 2;
	top = rcTop.top + (rcTop.bottom - rcTop.top) / 2;
	XDraw_TriangularArrow(hDraw, hBrush, 2, left, top, 12, 7);

	left = rcRight.left + (rcRight.right - rcRight.left) / 2;
	top = rcRight.top + (rcRight.bottom - rcRight.top) / 2;
	XDraw_TriangularArrow(hDraw, hBrush, 3, left, top, 7, 12);

	left = rcBottom.left + (rcBottom.right - rcBottom.left) / 2;
	top = rcBottom.top + (rcBottom.bottom - rcBottom.top) / 2;
	XDraw_TriangularArrow(hDraw, hBrush, 4, left, top, 12, 7);

	RECT rc1 = { 45,45,60,60 };
	RECT rc2 = { 50,50,70,70 };
	XDraw_FrameRect_(hDraw, &rc1, hBrush);
	XDraw_FrameRect_(hDraw, &rc2, hBrush);

	XDraw_DeleteObject_(hDraw, hBrush);

	return TRUE;
}

BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockLeft(HWINDOW hWindow, HDRAW hDraw)
{
	int left = 35 / 2;
	int top = 35 / 2;
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(160, 160, 160));

	RECT rc = { 0,0,35,35 };
	XDraw_FillSolidRect_(hDraw, &rc, RGB(220, 220, 220));

	XDraw_TriangularArrow(hDraw, hBrush, 1, left, top, 7, 12);
	XDraw_FrameRect_(hDraw, &rc, hBrush);

	XDraw_DeleteObject_(hDraw, hBrush);
	return TRUE;
}

BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockTop(HWINDOW hWindow, HDRAW hDraw)
{
	int left = 35 / 2;
	int top = 35 / 2;
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(160, 160, 160));

	RECT rc = { 0,0,35,35 };
	XDraw_FillSolidRect_(hDraw, &rc, RGB(220, 220, 220));

	XDraw_TriangularArrow(hDraw, hBrush, 2, left, top, 12, 7);
	XDraw_FrameRect_(hDraw, &rc, hBrush);

	XDraw_DeleteObject_(hDraw, hBrush);
	return TRUE;
}

BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockRight(HWINDOW hWindow, HDRAW hDraw)
{
	int left = 35 / 2;
	int top = 35 / 2;
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(160, 160, 160));

	RECT rc = { 0,0,35,35 };
	XDraw_FillSolidRect_(hDraw, &rc, RGB(220, 220, 220));

	XDraw_TriangularArrow(hDraw, hBrush, 3, left, top, 7, 12);
	XDraw_FrameRect_(hDraw, &rc, hBrush);

	XDraw_DeleteObject_(hDraw, hBrush);
	return TRUE;
}
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockBottom(HWINDOW hWindow, HDRAW hDraw)
{
	int left = 35 / 2;
	int top = 35 / 2;
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(160, 160, 160));

	RECT rc = { 0,0,35,35 };
	XDraw_FillSolidRect_(hDraw, &rc, RGB(220, 220, 220));

	XDraw_TriangularArrow(hDraw, hBrush, 4, left, top, 12, 7);
	XDraw_FrameRect_(hDraw, &rc, hBrush);

	XDraw_DeleteObject_(hDraw, hBrush);
	return TRUE;
}