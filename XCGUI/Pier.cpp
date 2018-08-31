#include "StdAfx.h"

HELE Pier_Create(align_type_ align, HWINDOW hWindow)
{
	pier_ *pPier = (pier_*)malloc(sizeof(pier_));
	if (pPier)
	{
		memset(pPier, 0, sizeof(pier_));
		pPier->align = align;
		Pier_Init(pPier, XC_PIER, hWindow);
		return (HELE)pPier;
	}
	return NULL;
}

void Pier_Init(pier_ *pPier, int eleType, HWINDOW hWindow)
{
	Ele_Init((HELE)pPier, 0, 0, 100, 100, eleType, hWindow);

	AddTypeDebug((HELE)pPier, XC_PIER);

	LOGFONT info;
	info.lfHeight = 12;
	info.lfWidth = 0;
	info.lfEscapement = -900;
	info.lfOrientation = 0;
	info.lfWeight = FW_NORMAL;
	info.lfItalic = FALSE;
	info.lfUnderline = FALSE;
	info.lfStrikeOut = FALSE;
	info.lfCharSet = GB2312_CHARSET;
	info.lfOutPrecision = OUT_DEFAULT_PRECIS;
	info.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	info.lfQuality = DEFAULT_QUALITY;
	info.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(info.lfFaceName, L"宋体");

	pPier->hFontX = XFont_CreateEx(&info);
	Font_AddRef(pPier->hFontX);

	XEle_RegisterEvent((HELE)pPier, XE_DESTROY, Pier_OnEventDestroy);
}

void Pier_AddCell(HELE hEle, layoutCell_ *pCell) //增加窗格
{
	pier_ *pPier = (pier_*)hEle;
	pier_item_gtoup_  *pItem = (pier_item_gtoup_*)malloc(sizeof(pier_item_gtoup_));
	memset(pItem, 0, sizeof(pier_item_gtoup_));
	pItem->type = 1;
	pItem->Child.pCell = pCell;
	pItem->Child.Parent = pItem;
	((layoutPane_*)pCell->hPane)->state = pane_state_dock;

	wchar_t *pText = XPane_GetTitle(pCell->hPane);
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
	SIZE size;
	GetTextExtentPoint32(hdc, pText, wcslen(pText), &size);
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (align_left == pPier->align || align_right == pPier->align)
	{
		pItem->Child.hButton = XBtn_Create(0, 0, 20, size.cx + 10, XPane_GetTitle(pCell->hPane), hEle);
	}
	else
	{
		pItem->Child.hButton = XBtn_Create(0, 0, size.cx + 10, 100, XPane_GetTitle(pCell->hPane), hEle);
	}

	if (NULL == pPier->hArrayList)
		pPier->hArrayList = XArray_Create();

	XArray_Add(pPier->hArrayList, pItem);

	XEle_SetUserData(pItem->Child.hButton, (int)(&pItem->Child));
	XEle_RegisterEvent(pItem->Child.hButton, XE_BNCLICK, Pier_Btn_OnClick);

	if (align_left == pPier->align || align_right == pPier->align)
	{
		XEle_SetFont(pItem->Child.hButton, pPier->hFontX);
	}

	XEle_RegisterMessage(pItem->Child.hButton, XM_PAINT, Pier_Btn_OnEleDraw);
}

void Pier_AddCellGroup(HELE hEle, layoutCell_ *pGroupCell) //增加组到码头
{
	pier_ *pPier = (pier_*)hEle;
	pier_item_gtoup_  *pItem = (pier_item_gtoup_*)malloc(sizeof(pier_item_gtoup_));
	memset(pItem, 0, sizeof(pier_item_gtoup_));
	pItem->hArrayList = XArray_Create();
	pItem->type = 2;

	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

	HWINDOW hWindow = XEle_GetHWindow(hEle);
	int count = XArray_GetCount(pGroupCell->hArrayList);
	for (int i = 0; i < count; i++)
	{
		layoutCell_ *pChildCell = (layoutCell_*)XArray_GetAt(pGroupCell->hArrayList, i);
		if (pane_state_dock == ((layoutPane_*)pChildCell->hPane)->state)
		{
			XEle_ShowEle(pChildCell->hPane, FALSE);

			pier_item_gtoup_child_ *pChild = (pier_item_gtoup_child_*)malloc(sizeof(pier_item_gtoup_child_));
			pChild->pCell = pChildCell;

			wchar_t *pText = XPane_GetTitle(pChildCell->hPane);
			SIZE size;
			GetTextExtentPoint32(hdc, pText, wcslen(pText), &size);

			if (align_left == pPier->align || align_right == pPier->align)
			{
				pChild->hButton = XBtn_Create(0, 0, 20, size.cx + 10, XPane_GetTitle(pChildCell->hPane), hEle);
				XEle_SetFont(pChild->hButton, pPier->hFontX);
			}
			else
			{
				pChild->hButton = XBtn_Create(0, 0, size.cx + 10, 100, XPane_GetTitle(pChildCell->hPane), hEle);
			}

			pChild->Parent = pItem;
			((layoutPane_*)pChildCell->hPane)->state = pane_state_dock;
			((layoutPane_*)pChildCell->hPane)->dockAlign = pPier->align;

			XArray_Add(pItem->hArrayList, pChild);

			XEle_SetUserData(pChild->hButton, (int)pChild);
			XEle_RegisterEvent(pChild->hButton, XE_BNCLICK, Pier_Btn_OnClick);
			XEle_RegisterMessage(pChild->hButton, XM_PAINT, Pier_Btn_OnEleDraw);
		}
	}
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (NULL == pPier->hArrayList)
		pPier->hArrayList = XArray_Create();
	XArray_Add(pPier->hArrayList, pItem);

}

void Pier_RemoveCell(HELE hEle, layoutCell_ *pCell) //移除窗格
{
	pier_ *pPier = (pier_*)hEle;
	int count = XArray_GetCount(pPier->hArrayList);
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		XTRACE("---\n");
		if (1 == pGroup->type)
		{
			if (pCell == pGroup->Child.pCell)
			{
				XEle_Destroy(pGroup->Child.hButton);
				XArray_DeleteIndex(pPier->hArrayList, i);
				free(pGroup);
				count--;
				break;
			}
		}
	}
	if (count < 1)
	{
		frameWnd_ *pFrame = (frameWnd_*)XEle_GetHWindow(hEle);

		switch (pPier->align)
		{
		case align_left:   XEle_Destroy(pFrame->hPierLeft);   pFrame->hPierLeft = NULL;   break;
		case align_top:    XEle_Destroy(pFrame->hPierTop);    pFrame->hPierTop = NULL;    break;
		case align_right:  XEle_Destroy(pFrame->hPierRight);  pFrame->hPierRight = NULL;  break;
		case align_bottom: XEle_Destroy(pFrame->hPierBottom); pFrame->hPierBottom = NULL; break;
		}
	}

	if (pCell->hDragBar)
	{
		XEle_Destroy(pCell->hDragBar);
		pCell->hDragBar = NULL;
	}
}

//pCell:组中的一个布局单元格
void Pier_RemoveCellGroup(HELE hEle, layoutCell_ *pCell) //移除组
{
	layoutCell_ *pGroupCell = pCell->pParentCell;

	pier_ *pPier = (pier_*)hEle;
	int count = XArray_GetCount(pPier->hArrayList);
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		XTRACE("---\n");
		if (2 == pGroup->type)
		{
			pier_item_gtoup_child_ *pItem = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, 0);
			if (pGroupCell == pItem->pCell->pParentCell)
			{
				int count2 = XArray_GetCount(pGroup->hArrayList);
				for (int j = 0; j < count2; j++)
				{
					pItem = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, j);
					XEle_Destroy(pItem->hButton);
					free(pItem);
				}
				XArray_Destroy(pGroup->hArrayList);
				XArray_DeleteIndex(pPier->hArrayList, i);
				free(pGroup);
				count--;
				break;
			}
		}
	}

	if (count < 1)
	{
		frameWnd_ *pFrame = (frameWnd_*)XEle_GetHWindow(hEle);

		switch (pPier->align)
		{
		case align_left:   XEle_Destroy(pFrame->hPierLeft);   pFrame->hPierLeft = NULL;   break;
		case align_top:    XEle_Destroy(pFrame->hPierTop);    pFrame->hPierTop = NULL;    break;
		case align_right:  XEle_Destroy(pFrame->hPierRight);  pFrame->hPierRight = NULL;  break;
		case align_bottom: XEle_Destroy(pFrame->hPierBottom); pFrame->hPierBottom = NULL; break;
		}
	}

	if (pCell->hDragBar)
	{
		XEle_Destroy(pCell->hDragBar);
		pCell->hDragBar = NULL;
	}
}

void Pier_SetCheck(HELE hEle, layoutCell_ *pCell)
{
	pier_ *pPier = (pier_*)hEle;
	int count = XArray_GetCount(pPier->hArrayList);
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		if (1 == pGroup->type)
		{
			if (pCell == pGroup->Child.pCell)
			{
				XBtn_SetCheck(pGroup->Child.hButton, FALSE);
				break;
			}
		}
		else if (2 == pGroup->type)
		{
			pier_item_gtoup_child_ *pItem = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, 0);
			int count2 = XArray_GetCount(pGroup->hArrayList);
			for (int j = 0; j < count2; j++)
			{
				pItem = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, j);
				if (pCell == pItem->pCell)
				{
					XBtn_SetCheck(pItem->hButton, FALSE);
					break;
				}
			}
		}
	}
}

void Pier_AdjustLayout(HELE hEle)
{
	pier_ *pPier = (pier_*)hEle;

	switch (pPier->align)
	{
	case align_left:    Pier_AdjustLayout_Left(hEle);   break;
	case align_top:     Pier_AdjustLayout_Top(hEle);    break;
	case align_right:   Pier_AdjustLayout_Right(hEle);  break;
	case align_bottom:  Pier_AdjustLayout_Bottom(hEle); break;
	}
}

void Pier_AdjustLayout_Left(HELE hEle)
{
	pier_ *pPier = (pier_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	int count = XArray_GetCount(pPier->hArrayList);

	int y = 5;
	if (pFrame->hPierTop)
		y = y + FRAME_PIER_WIDTH;

	RECT rcBtn;
	rcBtn.left = 0;
	rcBtn.right = FRAME_PIER_WIDTH - 2;

	int height = 0;
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);

		if (1 == pGroup->type) //单一窗格
		{
			height = ((ele_*)pGroup->Child.hButton)->rect.bottom - ((ele_*)pGroup->Child.hButton)->rect.top;

			rcBtn.top = y;
			rcBtn.bottom = y + height;
			y = rcBtn.bottom + 5;
			XEle_SetRect(pGroup->Child.hButton, &rcBtn);
		}
		else if (2 == pGroup->type)//窗格组
		{
			int count2 = XArray_GetCount(pGroup->hArrayList);
			for (int j = 0; j < count2; j++)
			{
				pier_item_gtoup_child_ *pChild = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, j);

				height = ((ele_*)pChild->hButton)->rect.bottom - ((ele_*)pChild->hButton)->rect.top;

				rcBtn.top = y;
				rcBtn.bottom = y + height;
				if (j == (count2 - 1))
					y = rcBtn.bottom + 5;
				else
					y = rcBtn.bottom + 1;
				XEle_SetRect(pChild->hButton, &rcBtn);
			}
		}
	}
}

void Pier_AdjustLayout_Top(HELE hEle)
{
	pier_ *pPier = (pier_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	int count = XArray_GetCount(pPier->hArrayList);

	int x = 5;

	RECT rcBtn;
	rcBtn.top = 0;
	rcBtn.bottom = FRAME_PIER_WIDTH - 2;

	int width = 0;
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		if (1 == pGroup->type) //单一窗格
		{
			width = ((ele_*)pGroup->Child.hButton)->rect.right - ((ele_*)pGroup->Child.hButton)->rect.left;

			rcBtn.left = x;
			rcBtn.right = x + width;
			x = rcBtn.right + 5;
			XEle_SetRect(pGroup->Child.hButton, &rcBtn);
		}
		else if (2 == pGroup->type)//窗格组
		{
			int count2 = XArray_GetCount(pGroup->hArrayList);
			for (int j = 0; j < count2; j++)
			{
				pier_item_gtoup_child_ *pChild = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, j);

				width = ((ele_*)pChild->hButton)->rect.right - ((ele_*)pChild->hButton)->rect.left;

				rcBtn.left = x;
				rcBtn.right = x + width;
				if (j == (count2 - 1))
					x = rcBtn.right + 5;
				else
					x = rcBtn.right + 1;
				XEle_SetRect(pChild->hButton, &rcBtn);
			}
		}
	}
}

void Pier_AdjustLayout_Right(HELE hEle)
{
	pier_ *pPier = (pier_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	int count = XArray_GetCount(pPier->hArrayList);

	int y = 5;
	if (pFrame->hPierTop)
		y = y + FRAME_PIER_WIDTH;

	RECT rcBtn;
	rcBtn.left = 2;
	rcBtn.right = FRAME_PIER_WIDTH;

	int height = 0;
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		if (1 == pGroup->type) //单一窗格
		{
			height = ((ele_*)pGroup->Child.hButton)->rect.bottom - ((ele_*)pGroup->Child.hButton)->rect.top;

			rcBtn.top = y;
			rcBtn.bottom = y + height;
			y = rcBtn.bottom + 5;
			XEle_SetRect(pGroup->Child.hButton, &rcBtn);
		}
		else if (2 == pGroup->type)//窗格组
		{
			int count2 = XArray_GetCount(pGroup->hArrayList);
			for (int j = 0; j < count2; j++)
			{
				pier_item_gtoup_child_ *pChild = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, j);
				height = ((ele_*)pChild->hButton)->rect.bottom - ((ele_*)pChild->hButton)->rect.top;

				rcBtn.top = y;
				rcBtn.bottom = y + height;
				if (j == (count2 - 1))
					y = rcBtn.bottom + 5;
				else
					y = rcBtn.bottom + 1;
				XEle_SetRect(pChild->hButton, &rcBtn);
			}
		}
	}
}

void Pier_AdjustLayout_Bottom(HELE hEle)
{
	pier_ *pPier = (pier_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	int count = XArray_GetCount(pPier->hArrayList);

	int x = 5;

	RECT rcBtn;
	rcBtn.top = 2;
	rcBtn.bottom = FRAME_PIER_WIDTH;

	int width = 0;
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		if (1 == pGroup->type) //单一窗格
		{
			width = ((ele_*)pGroup->Child.hButton)->rect.right - ((ele_*)pGroup->Child.hButton)->rect.left;

			rcBtn.left = x;
			rcBtn.right = x + width;
			x = rcBtn.right + 5;
			XEle_SetRect(pGroup->Child.hButton, &rcBtn);
		}
		else if (2 == pGroup->type)//窗格组
		{
			int count2 = XArray_GetCount(pGroup->hArrayList);
			for (int j = 0; j < count2; j++)
			{
				pier_item_gtoup_child_ *pChild = (pier_item_gtoup_child_*)XArray_GetAt(pGroup->hArrayList, j);
				width = ((ele_*)pChild->hButton)->rect.right - ((ele_*)pChild->hButton)->rect.left;

				rcBtn.left = x;
				rcBtn.right = x + width;
				if (j == (count2 - 1))
					x = rcBtn.right + 5;
				else
					x = rcBtn.right + 1;
				XEle_SetRect(pChild->hButton, &rcBtn);
			}
		}
	}
}

void CALLBACK Pier_OnEventDestroy(HELE hEle)
{
	pier_ *pPier = (pier_*)hEle;
	HWINDOW hFrame = XEle_GetHWindow(hEle);
	frameWnd_ *pFrame = (frameWnd_*)hFrame;

	if (NULL == pPier->hArrayList) return;

	int count = XArray_GetCount(pPier->hArrayList);
	for (int i = 0; i < count; i++)
	{
		pier_item_gtoup_ *pGroup = (pier_item_gtoup_*)XArray_GetAt(pPier->hArrayList, i);
		if (1 == pGroup->type) //单一窗格
		{
		}
		else if (2 == pGroup->type)//窗格组
		{
			int count2 = XArray_GetCount(pGroup->hArrayList);
			for (int j = 0; j < count2; j++)
			{
				layoutCell_ *pChildCell = (layoutCell_*)XArray_GetAt(pGroup->hArrayList, j);
				Cell_Destroy(pChildCell);
			}
			XArray_Destroy(pGroup->hArrayList);
		}
		free(pGroup);
	}
	XArray_Destroy(pPier->hArrayList);

	if (pPier->hFontX) XFont_Destroy(pPier->hFontX);
}

BOOL CALLBACK Pier_Btn_OnClick(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	HWINDOW hFrame = XEle_GetHWindow(hEle);
	pier_item_gtoup_child_  *info = (pier_item_gtoup_child_*)XEle_GetUserData(hEle);

	if (FrameWnd_PierPopupPane(hFrame, info->pCell->hPane))
		XBtn_SetCheck(info->hButton, TRUE);
	return FALSE;
}



BOOL CALLBACK Pier_Btn_OnEleDraw(HELE hEle, HDRAW hDraw)  //按钮自绘
{
	HELE hParent = XEle_GetParentEle(hEle);
	pier_ *pPier = (pier_*)hParent;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	HBRUSH hBrush = NULL;
	if (XBtn_IsCheck(hEle))
	{
		hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(140, 140, 140));
		XDraw_FillSolidRect_(hDraw, &rect, RGB(160, 160, 160));
	}
	else
	{
		int state = XBtn_GetState(hEle);
		switch (state)
		{
		case STATE_LEAVE:
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(180, 180, 180));
			XDraw_FillSolidRect_(hDraw, &rect, RGB(200, 200, 200));
			break;
		case STATE_STAY:
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(160, 160, 160));
			XDraw_FillSolidRect_(hDraw, &rect, RGB(180, 180, 180));
			break;
		case STATE_DOWN:
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(140, 140, 140));
			XDraw_FillSolidRect_(hDraw, &rect, RGB(160, 160, 160));
			break;
		}
	}

	wchar_t *pText = XBtn_GetText(hEle);
	if (align_left == pPier->align || align_right == pPier->align)
	{
		XDraw_TextOut_(hDraw, 0 + 12 + 3, 5, pText, wcslen(pText));
	}
	else
	{
		XDraw_TextOut_(hDraw, 5, 5, pText, wcslen(pText));
	}

	if (hBrush)
	{
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}
	return TRUE;
}