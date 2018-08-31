/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

/// @defgroup richEdit 富文本编辑框(RichEdit)
/// @ingroup groupElements
/// @{

/// @brief 创建富文本编辑框.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XRichEdit_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	edit_ *pRichEdit = (edit_*)malloc(sizeof(edit_));
	if (pRichEdit)
	{
		memset(pRichEdit, 0, sizeof(edit_));
		RichEdit_Init((HELE)pRichEdit, x, y, cx, cy, XC_RICHEDIT, hParent);
	}
	return (HELE)pRichEdit;
}

void RichEdit_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_RICHEDIT);

	richEdit_  *pRichEdit = (richEdit_*)hEle;

	pRichEdit->spacLeft = 0;
	pRichEdit->spacTop = 0;
	pRichEdit->rowCount = 1;
	pRichEdit->lineHeight = 20;
	pRichEdit->caretHeight = 16;
	pRichEdit->hArrayFont = XArray_Create();

	pRichEdit->hArrayLine = XArray_Create();
	richEdit_line_ *pLine = (richEdit_line_*)malloc(sizeof(richEdit_line_));
	pLine->hArrayItem = XArray_Create();
	pLine->lenPixel = 0;
	pLine->maxItemHeight = pRichEdit->lineHeight;
	pLine->top = 0;
	XArray_Add(pRichEdit->hArrayLine, pLine); //第一行

	XSView_SetScrollSize(hEle, pRichEdit->lineHeight, pRichEdit->lineHeight);
	HELE hView = XSView_GetView(hEle);

	XSView_SetDrawScrollView(hEle, RichEdit_OnDrawScrollView);

	XEle_RegisterEvent(hEle, XE_CHAR, RichEdit_OnEventChar);
	XEle_RegisterEvent(hEle, XE_HSCROLLVIEW, RichEdit_OnEventHScrollView);
	XEle_RegisterEvent(hEle, XE_VSCROLLVIEW, RichEdit_OnEventVScrollView);
	XEle_RegisterEvent(hEle, XE_DESTROY, RichEdit_OnEventDestroy);
	XEle_RegisterEvent(hEle, XE_KEYDOWN, RichEdit_OnEventKeyDown);
	XEle_RegisterEvent(hEle, XE_SETFOCUS, RichEdit_OnEventSetFocus);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, RichEdit_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_SETFONT, RichEdit_OnEventSetFont);

	XEle_RegisterMessage(hView, XM_LBUTTONDOWN, RichEdit_OnLButtonDown_View);
	XEle_RegisterMessage(hView, XM_LBUTTONUP, RichEdit_OnLButtonUp_View);
	XEle_RegisterMessage(hView, XM_MOUSEMOVE, RichEdit_OnMouseMove_View);
}

/// @brief 插入文本内容.
/// @param hEle   元素句柄.
/// @param pText  插入的文本内容.
/// @param row    插入的行位置,如果值为-1插入到末尾行.
/// @param column  插入的列位置,如果值为-1插入末尾列.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_InsertText(HELE hEle, wchar_t *pText, int row, int column) //插入文本内容
{
	IsRichEditDebug(hEle, __FUNCTION__);
	return XRichEdit_InsertTextEx(hEle, pText, row, column, NULL);
}

/// @brief 插入文本内容,可指定字体及颜色.
/// @param hEle   元素句柄.
/// @param pText  插入的文本内容.
/// @param row    插入的行位置,如果值为-1插入到末尾行.
/// @param column  插入的列位置,如果值为-1插入末尾列.
/// @param pFont   字体信息.
/// @param bColor  是否指定颜色.
/// @param color   颜色值.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_InsertTextEx(HELE hEle, wchar_t *pText, int row, int column, LOGFONT *pFont, BOOL bColor, COLORREF color)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	if (NULL == pText)
		return FALSE;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bDrawSelect)
		RichEdit_DeleteSelect(hEle); //删除选择文本

	if (row < -1 || column < -1)
	{
		return FALSE;
	}

	if (-1 == row)
	{
		row = pRichEdit->rowCount - 1;
	}

	if (row >= pRichEdit->rowCount)
	{
		return FALSE;
	}

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (-1 == column)
		column = countItem;
	else if (column > countItem)
		return FALSE;

	//0插入符在插入位置前面不需处理,1与插入符同行,插入符在后面,2插入符在当前行之后
	int caertOffet = 0;
	int type = 0;
	if (pRichEdit->row == row)
	{
		if (pRichEdit->column >= column)
		{
			caertOffet = pRichEdit->column - column;
			type = 1;
		}
	}
	else if (pRichEdit->row > row)
	{
		type = 2;
	}

	HFONT hFont = XFont_GetHFONT(((ele_*)hEle)->hFontX);
	richEdit_font_Info_ *pFontInf = NULL;
	if (pFont)
	{
		pFontInf = RichEdit_GetFont(hEle, pFont);
		hFont = pFontInf->hFont;
	}

	int index = column;
	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, hFont);

	while (*pText)
	{
		if (L'\n' == *pText)
		{
			row++;
			pRichEdit->rowCount++;

			if (1 == type || 2 == type)
			{
				pRichEdit->row++;
			}

			//新增加行
			richEdit_line_ *pLineNew = (richEdit_line_*)malloc(sizeof(richEdit_line_));
			pLineNew->hArrayItem = XArray_Create();
			pLineNew->lenPixel = 0;
			pLineNew->maxItemHeight = pRichEdit->lineHeight;
			pLineNew->top = 0;
			XArray_insert(pRichEdit->hArrayLine, pLineNew, row);

			//如果插入符后面的内容,切换到下一行
			int countItem = XArray_GetCount(pLine->hArrayItem);
			if (countItem != index)
			{
				int count = countItem - index;
				for (int i = 0; i < count; i++)
				{
					richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, index);
					index++;
					pLine->lenPixel -= pItem->size.cx;

					XArray_Add(pLineNew->hArrayItem, pItem);
					pLineNew->lenPixel += pItem->size.cx;
				}
			}

			XArray_DeleteEnd(pLine->hArrayItem, countItem - XArray_GetCount(pLineNew->hArrayItem));
			pLine = pLineNew;
			index = 0;

			RichEdit_Calculate_LineMaxHeight(hEle, row - 1);
		}
		else if (L'\r' == *pText)
		{
		}
		else
		{
			richEdit_item_char_ *pItemChar = (richEdit_item_char_*)malloc(sizeof(richEdit_item_char_));
			pItemChar->bColor = FALSE;
			pItemChar->color = 0;
			pItemChar->hFont = NULL;
			pItemChar->pFontInfo = pFontInf;
			pItemChar->item.type = richEdit_itemType_char;
			pItemChar->ch = *pText;

			if (bColor)
			{
				pItemChar->bColor = TRUE;
				pItemChar->color = color;
			}

			GetTextExtentPoint32(hdc, pText, 1, &size);
			if (VK_TAB == *pText)
				size.cx = size.cy * 2;

			XArray_insert(pLine->hArrayItem, pItemChar, index);
			index++;

			pItemChar->item.size = size;
			pLine->lenPixel += size.cx;
		}
		pText++;
	}
	RichEdit_Calculate_LineMaxHeight(hEle, row);
	if (1 == type)
	{
		pRichEdit->column = index + caertOffet;
	}

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (1 == type || 2 == type)
	{
		//	RichEdit_Calculate_CaretPos(hEle);
		pRichEdit->bAdjustCalculate = TRUE;
		pRichEdit->bAdjustCaret = TRUE;
	}
	pRichEdit->bAdjust = TRUE;
	return TRUE;
}

/// @brief 插入数据内容,包含字体,图片,颜色信息.
/// @param hEle   元素句柄.
/// @param pData  数据指针.
/// @param row    插入的行位置,如果值为-1插入到末尾行.
/// @param column  插入的列位置,如果值为-1插入末尾列.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_InsertData(HELE hEle, void *pData, int row, int column)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (NULL == pData)  return FALSE;

	if (row < -1 || column < -1)
	{
		return FALSE;
	}

	if (-1 == row)
	{
		row = pRichEdit->rowCount - 1;
	}

	if (row >= pRichEdit->rowCount)
	{
		return FALSE;
	}

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (-1 == column)
		column = countItem;
	else if (column > countItem)
		return FALSE;

	if (pRichEdit->bDrawSelect)
		XRichEdit_CancelSelect(hEle); //删除选择文本

	//0插入符在插入位置前面不需处理,1与插入符同行,插入符在后面,2插入符在当前行之后
	int caertOffet = 0;
	int type = 0;
	if (pRichEdit->row == row)
	{
		if (pRichEdit->column >= column)
		{
			caertOffet = pRichEdit->column - column;
			type = 1;
		}
	}
	else if (pRichEdit->row > row)
	{
		type = 2;
	}

	HFONT hFont = XFont_GetHFONT(((ele_*)hEle)->hFontX);
	int index = column;
	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	///////////////////////////////////////////////////////
	byte *pPosition = (byte*)pData;

	richEdit_clipboard_header_  *pHeader = (richEdit_clipboard_header_*)pPosition;
	pPosition += sizeof(richEdit_clipboard_header_);

	//字体表
	HARRAY hArrayFont = XArray_Create();
	for (int i = 0; i < pHeader->fontCount; i++)
	{
		XArray_Add(hArrayFont, pPosition);
		pPosition += sizeof(LOGFONT);
	}

	richEdit_font_Info_  *pFontInfo = NULL;
	LOGFONT *pFont = NULL;
	richEdit_clipboard_char_   *pItemChar = NULL;
	richEdit_clipboard_iamge_  *pItemImage = NULL;

	richEdit_item_char_   *pItemCharNew = NULL;
	for (int i = 0; i < pHeader->itemCount; i++)
	{
		//XRichEdit_GetCurrentPos(hEle,&row,&column);
		if (richEdit_itemType_char == *(rictEdit_ItemType_*)pPosition)
		{
			pItemChar = (richEdit_clipboard_char_*)pPosition;
			if (L'\n' == pItemChar->ch)
			{
				row++;
				pRichEdit->rowCount++;
				if (1 == type || 2 == type)
				{
					pRichEdit->row++;
				}

				//新增加行
				richEdit_line_ *pLineNew = (richEdit_line_*)malloc(sizeof(richEdit_line_));
				pLineNew->hArrayItem = XArray_Create();
				pLineNew->lenPixel = 0;
				pLineNew->maxItemHeight = pRichEdit->lineHeight;
				pLineNew->top = 0;
				XArray_insert(pRichEdit->hArrayLine, pLineNew, row);

				//如果插入符后面的内容,切换到下一行
				int countItem = XArray_GetCount(pLine->hArrayItem);
				if (countItem != index)
				{
					int count = countItem - index;
					for (int i = 0; i < count; i++)
					{
						richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, index);
						index++;
						pLine->lenPixel -= pItem->size.cx;

						XArray_Add(pLineNew->hArrayItem, pItem);
						pLineNew->lenPixel += pItem->size.cx;
					}
				}

				XArray_DeleteEnd(pLine->hArrayItem, countItem - XArray_GetCount(pLineNew->hArrayItem));
				pLine = pLineNew;
				index = 0;

				RichEdit_Calculate_LineMaxHeight(hEle, row - 1);
			}
			else if (L'\r' == pItemChar->ch)
			{
			}
			else
			{
				pItemCharNew = (richEdit_item_char_*)malloc(sizeof(richEdit_item_char_));
				pItemCharNew->pFontInfo = NULL;
				pItemCharNew->ch = pItemChar->ch;
				pItemCharNew->bColor = pItemChar->bColor;
				pItemCharNew->color = pItemChar->color;
				pItemCharNew->item.type = pItemChar->type;
				pItemCharNew->item.pLine = pLine;
				pItemCharNew->pFontInfo = NULL;;

				if (pItemChar->fontIndex >= 0)
				{
					pFont = (LOGFONT*)XArray_GetAt(hArrayFont, pItemChar->fontIndex);
					pFontInfo = RichEdit_GetFont(hEle, pFont);
					SelectObject(hdc, pFontInfo->hFont);
					pItemCharNew->pFontInfo = pFontInfo;;
				}
				else
				{
					SelectObject(hdc, hFont);
				}

				GetTextExtentPoint32(hdc, &pItemChar->ch, 1, &size);
				if (VK_TAB == pItemChar->ch)
					size.cx = size.cy * 2;

				XArray_insert(pLine->hArrayItem, pItemCharNew, index);
				index++;
				pItemCharNew->item.size = size;
				pLine->lenPixel += size.cx;
			}
			pPosition += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == *(rictEdit_ItemType_*)pPosition)
		{
			pItemImage = (richEdit_clipboard_iamge_*)pPosition;
			HIMAGE hImage = XImage_LoadFile((wchar_t*)&pItemImage->chs);
			if (hImage)
			{
				richEdit_item_iamge_  *pItemImageNew = (richEdit_item_iamge_*)malloc(sizeof(richEdit_item_iamge_));
				pItemImageNew->item.pLine = pLine;
				pItemImageNew->item.type = richEdit_itemType_image;
				pItemImageNew->hImage = NULL;
				Image_AddImage(pItemImageNew->hImage, hImage);
				pItemImageNew->item.size.cx = XImage_GetWidth(hImage);
				pItemImageNew->item.size.cy = XImage_GetHeight(hImage);
				pItemImageNew->hString = XStr_Create((wchar_t*)&pItemImage->chs);

				XArray_insert(pLine->hArrayItem, pItemImageNew, index);
				index++;
				pLine->lenPixel += pItemImageNew->item.size.cx;
			}
			pPosition += pItemImage->size;
		}
		else if (richEdit_itemType_gif == *(rictEdit_ItemType_*)pPosition)
		{
			pItemImage = (richEdit_clipboard_iamge_*)pPosition;

			ImageEx *pGif = new ImageEx((wchar_t*)&pItemImage->chs);
			if (pGif && pGif->InitAnimation(0, 0))
			{
				richEdit_item_gif_  *pItemGifNew = (richEdit_item_gif_*)malloc(sizeof(richEdit_item_gif_));
				pItemGifNew->item.pLine = pLine;
				pItemGifNew->item.type = richEdit_itemType_gif;
				pItemGifNew->pGif = pGif;
				pItemGifNew->ms = 100;
				pItemGifNew->item.size.cx = pGif->GetWidth();
				pItemGifNew->item.size.cy = pGif->GetHeight();
				pItemGifNew->hView = XSView_GetView(hEle);
				pItemGifNew->hString = XStr_Create((wchar_t*)&pItemImage->chs);

				XArray_insert(pLine->hArrayItem, pItemGifNew, index);
				index++;
				pLine->lenPixel += pItemGifNew->item.size.cx;
				Animation_Add_RichEdit(pItemGifNew);
			}
			pPosition += pItemImage->size;
		}
		else
		{
			XTRACE("RichEdit 剪贴板粘贴错误 \n");
			exit(0);
		}
	}
	XArray_Destroy(hArrayFont);

	RichEdit_Calculate_LineMaxHeight(hEle, row);
	if (1 == type)
	{
		pRichEdit->column = index + caertOffet;
	}

	SelectObject(hdc, hFont);
	ReleaseDC(NULL, hdc);
	if (1 == type || 2 == type)
	{
		pRichEdit->bAdjustCalculate = TRUE;
		pRichEdit->bAdjustCaret = TRUE;
	}
	pRichEdit->bAdjust = TRUE;
	return TRUE;
}

/*
//TODO: 暂时不实现
BOOL WINAPI XRichEdit_InsertEle(HELE hEle,HELE hNew) //插入图片
{
	IsRichEditDebug(hEle,__FUNCTION__);
	richEdit_ *pRichEdit=(richEdit_*)hEle;

	RECT rcEle;
	XEle_GetClientRect(hNew,&rcEle);

	richEdit_item_ele_  *pItem=(richEdit_item_ele_*)malloc(sizeof(richEdit_item_ele_));
	pItem->item.type=richEdit_itemType_ele;
	pItem->hEle=hNew;
	pItem->item.size.cx=rcEle.right-rcEle.left;
	pItem->item.size.cy=rcEle.bottom-rcEle.top;

	richEdit_line_ *pLine=(richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine,pRichEdit->row);
	XArray_insert(pLine->hArrayItem,pItem,pRichEdit->column);
	pItem->item.pLine=pLine;
	if (pItem->item.size.cy>pLine->maxItemHeight)
	{
		pLine->maxItemHeight=pItem->item.size.cy;
	}

	RECT rect;
	rect.left=pRichEdit->caretPt.x;
	rect.right=rect.left+pItem->item.size.cx;
	rect.bottom=pRichEdit->caretPt.y+pLine->maxItemHeight;  //rect.top+pItem->item.size.cy;
	rect.top=rect.bottom-pItem->item.size.cy;

	XEle_SetRect(hNew,&rect);
	XEle_EnableFocus(hNew,FALSE);

	pLine->lenPixel+=pItem->item.size.cx;

	pRichEdit->column++;
	pRichEdit->caretPt.x+=pItem->item.size.cx;


	RichEdit_SetCaretPos(hEle);

	pRichEdit->bAdjust=TRUE;
	return TRUE;
}
*/


/// @brief 插入图片.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
/// @param pImagePath  图片路径,用于图片的复制.
/// @param row     插入的行位置,如果值为-1插入到末尾行.
/// @param column  插入的列位置,如果值为-1插入末尾列.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_InsertImage(HELE hEle, HIMAGE hImage, wchar_t *pImagePath, int row, int column) //插入图片
{
	IsRichEditDebug(hEle, __FUNCTION__);
	IsHImageDebug(hImage, __FUNCTION__);

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bDrawSelect)
		RichEdit_DeleteSelect(hEle); //删除选择文本

	if (row < -1 || column < -1)
	{
		return FALSE;
	}

	if (-1 == row)
	{
		row = pRichEdit->rowCount - 1;
	}

	if (row >= pRichEdit->rowCount)
	{
		return FALSE;
	}

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (-1 == column)
		column = countItem;
	else if (column > countItem)
		return FALSE;

	//0插入符在插入位置前面不需处理,1与插入符同行,插入符在后面,2插入符在当前行之后
	int type = 0;
	if (pRichEdit->row == row)
	{
		if (pRichEdit->column >= column)
		{
			type = 1;
		}
	}
	else if (pRichEdit->row > row)
	{
		type = 2;
	}

	richEdit_item_iamge_  *pItem = (richEdit_item_iamge_*)malloc(sizeof(richEdit_item_iamge_));
	pItem->item.type = richEdit_itemType_image;
	pItem->hImage = NULL;
	Image_AddImage(pItem->hImage, hImage);
	pItem->item.size.cx = XImage_GetWidth(hImage);
	pItem->item.size.cy = XImage_GetHeight(hImage);

	if (pImagePath)
	{
		if (NULL == wcschr(pImagePath, L':'))
		{
			wchar_t dir[MAX_PATH] = { 0 };
			GetCurrentDirectory(MAX_PATH, dir);
			wchar_t filePaht[MAX_PATH] = { 0 };
			PathCombine(filePaht, dir, pImagePath);
			pItem->hString = XStr_Create(pImagePath);
		}
		else
			pItem->hString = XStr_Create(pImagePath);
	}
	else
		pItem->hString = NULL;

	XArray_insert(pLine->hArrayItem, pItem, column);
	pItem->item.pLine = pLine;

	RichEdit_Calculate_LineMaxHeight(hEle, row);
	pLine->lenPixel += pItem->item.size.cx;
	if (1 == type)
	{
		pRichEdit->column++;
		pRichEdit->caretPt.x += pItem->item.size.cx;
	}
	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;

	//	RichEdit_Adjust(hEle);
	//	RichEdit_SetCaretPos(hEle);
	//	RichEdit_ScrollH(hEle);

	return TRUE;
}

/// @brief 插入GIF动画图片.
/// @param hEle    元素句柄.
/// @param pImageName  GIF图片文件名.
/// @param row     插入的行位置,如果值为-1插入到末尾行.
/// @param column  插入的列位置,如果值为-1插入末尾列.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_InsertImageGif(HELE hEle, wchar_t *pImageName, int row, int column)  //插入GIF图片
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bDrawSelect)
		RichEdit_DeleteSelect(hEle); //删除选择文本

	if (NULL == pImageName)
		return FALSE;

	wchar_t *pFile = wcsrchr(pImageName, L'.');
	if (NULL == pFile)
		return FALSE;

	if (0 != wcscmp(pFile, L".gif") && 0 != wcscmp(pFile, L".GIF"))
		return FALSE;

	ImageEx *pGif = new ImageEx(pImageName);

	if (false == pGif->InitAnimation(0, 0))
		return FALSE;

	if (row < -1 || column < -1)
	{
		return FALSE;
	}

	if (-1 == row)
	{
		row = pRichEdit->rowCount - 1;
	}

	if (row >= pRichEdit->rowCount)
	{
		return FALSE;
	}

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (-1 == column)
		column = countItem;
	else if (column > countItem)
		return FALSE;

	//0插入符在插入位置前面不需处理,1与插入符同行,插入符在后面,2插入符在当前行之后
	int type = 0;
	if (pRichEdit->row == row)
	{
		if (pRichEdit->column >= column)
		{
			type = 1;
		}
	}
	else if (pRichEdit->row > row)
	{
		type = 2;
	}

	richEdit_item_gif_  *pItem = (richEdit_item_gif_*)malloc(sizeof(richEdit_item_gif_));
	pItem->item.type = richEdit_itemType_gif;
	pItem->pGif = pGif;
	pItem->ms = 100;
	pItem->item.size.cx = pGif->GetWidth();
	pItem->item.size.cy = pGif->GetHeight();

	if (NULL == wcschr(pImageName, L':'))
	{
		wchar_t dir[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, dir);
		wchar_t filePaht[MAX_PATH] = { 0 };
		PathCombine(filePaht, dir, pImageName);
		pItem->hString = XStr_Create(filePaht);
	}
	else
		pItem->hString = XStr_Create(pImageName);

	XArray_insert(pLine->hArrayItem, pItem, pRichEdit->column);
	pItem->item.pLine = pLine;

	RichEdit_Calculate_LineMaxHeight(hEle, row);
	pLine->lenPixel += pItem->item.size.cx;
	if (1 == type)
	{
		pRichEdit->column++;
		pRichEdit->caretPt.x += pItem->item.size.cx;
	}

	pItem->hView = XSView_GetView(hEle);
	Animation_Add_RichEdit(pItem);

	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;

	//	RichEdit_SetCaretPos(hEle);
	//	RichEdit_Adjust(hEle);
	//	RichEdit_ScrollH(hEle);
	return TRUE;
}

/// @brief 设置文本内容.
/// @param hEle  元素句柄.
/// @param pText 文本内容.
void WINAPI XRichEdit_SetText(HELE hEle, wchar_t *pText)  //设置文本内容,会清空之前的内容
{
	IsRichEditDebug(hEle, __FUNCTION__);

	richEdit_ *pRichEdit = (richEdit_*)hEle;
	//清空内容
	XRichEdit_DeleteAll(hEle);

	if (NULL == pText)
		return;

	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, 0);
	while (*pText)
	{
		if (L'\n' == *pText)
		{
			pLine = (richEdit_line_*)malloc(sizeof(richEdit_line_));
			pLine->hArrayItem = XArray_Create();
			pLine->lenPixel = 0;
			pLine->maxItemHeight = pRichEdit->lineHeight;
			pLine->top = 0;

			XArray_Add(pRichEdit->hArrayLine, pLine);
			pRichEdit->rowCount++;
		}
		else if (L'\r' == *pText)
		{
		}
		else
		{
			richEdit_item_char_ *pItemChar = (richEdit_item_char_*)malloc(sizeof(richEdit_item_char_));
			pItemChar->bColor = FALSE;
			pItemChar->color = 0;
			pItemChar->hFont = 0;
			pItemChar->pFontInfo = NULL;
			pItemChar->item.type = richEdit_itemType_char;
			pItemChar->item.pLine = pLine;
			pItemChar->ch = *pText;

			GetTextExtentPoint32(hdc, pText, 1, &size);
			if (VK_TAB == *pText)
				size.cx = size.cy * 2;

			pItemChar->item.size = size;

			XArray_Add(pLine->hArrayItem, pItemChar);
			pLine->lenPixel += size.cx;
		}
		pText++;
	}

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	pRichEdit->bAdjust = TRUE;
}

/// @brief 设置插入符位置.
/// @param hEle    元素句柄.
/// @param  row     行索引.
/// @param  column  列索引.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_SetPos(HELE hEle, int row, int column) //设置插入符位置
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (row < 0 || column < 0)
		return FALSE;

	if (row >= XArray_GetCount(pRichEdit->hArrayLine))
	{
		return FALSE;
	}

	richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (column > countItem)
	{
		return FALSE;
	}
	int x = 0;
	richEdit_item_  *pItem = NULL;
	for (int i = 0; i < countItem; i++)
	{
		if (i == column)
			break;

		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		x += pItem->size.cx;
	}
	pRichEdit->caretPt.x = x;
	pRichEdit->caretPt.y = pLine->top;

	pRichEdit->row = row;
	pRichEdit->column = column;

	RichEdit_SetCaretPos(hEle);
	return TRUE;
}

/*
/// @brief 设置字体.
/// @param hEle    元素句柄.
/// @param row     行索引.
/// @param column  列索引.
/// @param hFont   字体句柄.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_SetItemFont(HELE hEle,int row,int column, HFONT hFont)
{
	IsRichEditDebug(hEle,__FUNCTION__);
	if(row<0 || column<0)
		return FALSE;

	richEdit_ *pRichEdit=(richEdit_*)hEle;

	if(row>=XArray_GetCount(pRichEdit->hArrayLine))
		return FALSE;

	richEdit_line_ *pLine=(richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine,row);
	if (column>=XArray_GetCount(pLine->hArrayItem))
		return FALSE;

	richEdit_item_ *pItem=(richEdit_item_*)XArray_GetAt(pLine->hArrayItem,column);
	if(richEdit_itemType_char!=pItem->type)
		return FALSE;

	richEdit_item_char_ *pItemChar=(richEdit_item_char_*)pItem;
	pItemChar->hFont=hFont;

	//字符长度
	SIZE size;
	HDC hdc=GetDC(NULL);
	HGDIOBJ hOldFont=SelectObject(hdc,hFont);
	GetTextExtentPoint32(hdc,&pItemChar->ch,1,&size);
	if(VK_TAB==pItemChar->ch)
		size.cx=size.cy*2;

	SelectObject(hdc,hOldFont);
	ReleaseDC(NULL,hdc);

	if(  pItem->size.cy==pLine->maxItemHeight || size.cy>pLine->maxItemHeight) //需要调整行高
	{
		pItem->size.cy=size.cy;
		RichEdit_Calculate_LineMaxHeight(hEle,row);
	}else
	{
		pItem->size.cy=size.cy;
	}

	//需要调整行长
	if (pItem->size.cx!=size.cx)
	{
		int cx=size.cx-pItem->size.cx;
		pLine->lenPixel+=cx;

		pItem->size.cx=size.cx;
	}

	//调整插入符
	RichEdit_Calculate_CaretPos(hEle);

	return TRUE;
}*/

/// @brief 设置指定内容字体.
/// @param hEle    元素句柄.
/// @param beginRow     开始行索引.
/// @param beginColumn  开始行列索引.
/// @param endRow       结束行索引.
/// @param endColumn    结束行列索引.
/// @param pFont        字体信息.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_SetItemFontEx(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, LOGFONT *pFont)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	if (beginRow > endRow)
		return FALSE;

	if (beginRow < 0 || endRow < 0 || beginColumn < 0 || endColumn < 0)
		return FALSE;

	richEdit_ *pRichEdit = (richEdit_*)hEle;
	richEdit_font_Info_  *pFontInfo = RichEdit_GetFont(hEle, pFont);

	if (beginRow == endRow) //单行
	{
		return RichEdit_SetItemFontExSingleLine(hEle, beginRow, beginColumn, endRow, endColumn, pFontInfo);
	}
	else	//多行
	{
		return RichEdit_SetItemFontExMultiLine(hEle, beginRow, beginColumn, endRow, endColumn, pFontInfo);
	}
}

BOOL RichEdit_SetItemFontExSingleLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, richEdit_font_Info_ *pFontInfo)
{
	if (beginColumn >= endColumn)
		return FALSE;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	if (endColumn > XArray_GetCount(pLine->hArrayItem))
		return FALSE;

	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, pFontInfo->hFont);

	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;
	int lenPixel = 0;
	for (int i = beginColumn; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			//pItemChar->hFont=hFont;
			pItemChar->pFontInfo = pFontInfo;
			GetTextExtentPoint32(hdc, &pItemChar->ch, 1, &size);
			if (VK_TAB == pItemChar->ch)
				size.cx = size.cy * 2;

			lenPixel += size.cx - pItem->size.cx;
			pItem->size = size;
		}
	}
	pLine->lenPixel += lenPixel;

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	RichEdit_Calculate_LineMaxHeight(hEle, beginRow);

	if (pRichEdit->row >= beginRow)
	{
		//RichEdit_Calculate_CaretPos(hEle);	//计算插入符新位置
		pRichEdit->bAdjustCalculate = TRUE;
		pRichEdit->bAdjustCaret = TRUE;
	}
	pRichEdit->bAdjust = TRUE;
	return TRUE;
}

BOOL RichEdit_SetItemFontExMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, richEdit_font_Info_ *pFontInfo)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (endRow >= pRichEdit->rowCount)
		return FALSE;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	int countItemBegin = XArray_GetCount(pLine->hArrayItem);
	if (beginColumn > countItemBegin)
		return FALSE;

	richEdit_line_ *pLineEnd = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, endRow);
	int countItemEnd = XArray_GetCount(pLineEnd->hArrayItem);
	if (endColumn > countItemEnd)
		return FALSE;

	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, pFontInfo->hFont);

	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;

	//开始行
	int lenPixel = 0;
	for (int i = beginColumn; i < countItemBegin; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			//	pItemChar->hFont=hFont;
			pItemChar->pFontInfo = pFontInfo;
			GetTextExtentPoint32(hdc, &pItemChar->ch, 1, &size);
			if (VK_TAB == pItemChar->ch)
				size.cx = size.cy * 2;

			lenPixel += (size.cx - pItem->size.cx);

			pItem->size = size;
		}
	}
	pLine->lenPixel += lenPixel;
	RichEdit_Calculate_LineMaxHeight(hEle, beginRow);

	//中间行
	int countLine = endRow - beginRow - 1;
	for (int i = 0; i < countLine; i++)
	{
		richEdit_line_ *pLineT = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + 1 + i);
		int count = XArray_GetCount(pLineT->hArrayItem);
		lenPixel = 0;
		for (int j = 0; j < count; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineT->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				//pItemChar->hFont=hFont;
				pItemChar->pFontInfo = pFontInfo;
				GetTextExtentPoint32(hdc, &pItemChar->ch, 1, &size);
				if (VK_TAB == pItemChar->ch)
					size.cx = size.cy * 2;

				lenPixel += (size.cx - pItem->size.cx);

				pItem->size = size;
			}
		}
		pLineT->lenPixel += lenPixel;
		RichEdit_Calculate_LineMaxHeight(hEle, beginRow + 1 + i);
	}

	//结束行
	lenPixel = 0;
	for (int i = 0; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineEnd->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			//pItemChar->hFont=hFont;
			pItemChar->pFontInfo = pFontInfo;
			GetTextExtentPoint32(hdc, &pItemChar->ch, 1, &size);
			if (VK_TAB == pItemChar->ch)
				size.cx = size.cy * 2;

			lenPixel += (size.cx - pItem->size.cx);

			pItem->size = size;
		}
	}
	pLineEnd->lenPixel += lenPixel;

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	RichEdit_Calculate_LineMaxHeight(hEle, endRow);

	if (pRichEdit->row >= beginRow)
	{
		//	RichEdit_Calculate_CaretPos(hEle);	//计算插入符新位置
		pRichEdit->bAdjustCalculate = TRUE;
		pRichEdit->bAdjustCaret = TRUE;
	}
	pRichEdit->bAdjust = TRUE;
	return TRUE;
}

/*
/// @brief 设置文字颜色.
/// @param hEle    元素句柄.
/// @param row     行索引.
/// @param column  列索引.
/// @param color   颜色.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_SetItemColor(HELE hEle,int row,int column, COLORREF color)
{
	IsRichEditDebug(hEle,__FUNCTION__);
	if(row<0 || column<0)
		return FALSE;

	richEdit_ *pRichEdit=(richEdit_*)hEle;

	if(row>=XArray_GetCount(pRichEdit->hArrayLine))
		return FALSE;

	richEdit_line_ *pLineT=(richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine,row);

	if (column>=XArray_GetCount(pLineT->hArrayItem))
		return FALSE;

	richEdit_item_ *pItem=(richEdit_item_*)XArray_GetAt(pLineT->hArrayItem,column);
	if(richEdit_itemType_char==pItem->type)
	{
		richEdit_item_char_ *pItemChar=(richEdit_item_char_*)pItem;
		pItemChar->bColor=TRUE;
		pItemChar->color=color;
	}
	return TRUE;
}*/

/// @brief 设置文字颜色.
/// @param hEle    元素句柄.
/// @param beginRow     开始行索引.
/// @param beginColumn  开始行列索引.
/// @param endRow       结束行索引.
/// @param endColumn    结束行列索引.
/// @param color        颜色.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_SetItemColorEx(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, COLORREF color)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	if (beginRow > endRow)
		return FALSE;

	if (beginRow < 0 || endRow < 0 || beginColumn < 0 || endColumn < 0)
		return FALSE;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (beginRow == endRow) //单行
	{
		return RichEdit_SetItemColorExSingleLine(hEle, beginRow, beginColumn, endRow, endColumn, color);
	}
	else	//多行
	{
		return RichEdit_SetItemColorExMultiLine(hEle, beginRow, beginColumn, endRow, endColumn, color);
	}
}

BOOL RichEdit_SetItemColorExSingleLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, COLORREF color)
{
	if (beginColumn >= endColumn)
		return FALSE;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	if (endColumn > XArray_GetCount(pLine->hArrayItem))
		return FALSE;

	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;
	int lenPixel = 0;
	for (int i = beginColumn; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			pItemChar->bColor = TRUE;
			pItemChar->color = color;
		}
	}
	return TRUE;
}

BOOL RichEdit_SetItemColorExMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, COLORREF color)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (endRow >= pRichEdit->rowCount)
		return FALSE;

	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;

	//开始行
	richEdit_line_ *pLineBegin = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	int countItemBegin = XArray_GetCount(pLineBegin->hArrayItem);
	if (beginColumn > countItemBegin)
		return FALSE;

	//结束行
	richEdit_line_ *pLineEnd = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, endRow);
	int countItemEnd = XArray_GetCount(pLineEnd->hArrayItem);
	if (endColumn > countItemEnd)
		return FALSE;

	//开始行
	for (int i = beginColumn; i < countItemBegin; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineBegin->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			pItemChar->bColor = TRUE;
			pItemChar->color = color;
		}
	}

	//中间行
	int countLine = endRow - beginRow - 1;
	for (int i = 0; i < countLine; i++)
	{
		richEdit_line_ *pLineT = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + 1 + i);
		int count = XArray_GetCount(pLineT->hArrayItem);
		for (int j = 0; j < count; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineT->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				pItemChar->bColor = TRUE;
				pItemChar->color = color;
			}
		}
	}

	//结束行
	for (int i = 0; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineEnd->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			pItemChar->bColor = TRUE;
			pItemChar->color = color;
		}
	}

	return TRUE;
}

/// @brief 设置默认行高.
/// @param hEle    元素句柄.
/// @param height   行高.
void WINAPI XRichEdit_SetRowHeight(HELE hEle, int height) //设置默认行高
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->lineHeight == height)
		return;

	richEdit_line_  *pLine = NULL;
	int countLine = XArray_GetCount(pRichEdit->hArrayLine);
	if (pRichEdit->lineHeight < height)
	{
		for (int i = 0; i < countLine; i++)
		{
			pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
			if (pLine->maxItemHeight < height)
				pLine->maxItemHeight = height;
		}
		pRichEdit->lineHeight = height;
	}
	else
	{
		int oldHeight = pRichEdit->lineHeight;
		pRichEdit->lineHeight = height;
		for (int i = 0; i < countLine; i++)
		{
			pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
			if (pLine->maxItemHeight == oldHeight)
			{
				RichEdit_Calculate_LineMaxHeight(hEle, i);
			}
		}
	}
	//RichEdit_Calculate_CaretPos(hEle);
	pRichEdit->bAdjustCalculate = TRUE;
	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;
}

/// @brief 设置内容只读.
/// @param hEle   元素句柄.
/// @param bRead   只读内容TRUE,用户可操作内容FALSE.
void WINAPI XRichEdit_SetReadOnly(HELE hEle, BOOL bRead)  //设置只读文本
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	pRichEdit->bReadOnly = bRead;
}

/// @brief 获取内容数量,包括图片,不包含回车和换行符.
/// @param hEle    元素句柄.
/// @param 内容数量.
int WINAPI XRichEdit_GetItemCount(HELE hEle) //获取内容数量,包括图片
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	richEdit_line_  *pLine = NULL;

	int count = 0;
	for (int i = 0; i < pRichEdit->rowCount; i++)
	{
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		count += XArray_GetCount(pLine->hArrayItem);
	}
	return count;
}

/// @brief 获取HTML格式内容.
/// @param hEle   元素句柄.
/// @param hString   接收内容字符串.
void WINAPI XRichEdit_GetHTMLFormat(HELE hEle, HSTRING hString)  //获取HTML格式内容
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	std::wstring    buf_html;

	richEdit_line_  *pLine = NULL;
	richEdit_item_  *pItem = NULL;
	richEdit_item_iamge_   *pItemImage = NULL;
	richEdit_item_gif_     *pItemGif = NULL;
	int             countItem = 0;
	for (int i = 0; i < pRichEdit->rowCount; i++)
	{
		if (0 != i)
		{
			buf_html += L"<br>\r\n";
		}

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				buf_html += ((richEdit_item_char_*)pItem)->ch;
			}
			else if (richEdit_itemType_image == pItem->type)
			{
				pItemImage = (richEdit_item_iamge_*)pItem;
				if (pItemImage->hString)
				{
					wchar_t *pPath = XStr_GetBuffer(pItemImage->hString);
					buf_html += L"<img src=";
					buf_html += pPath;
					buf_html += L" >";
				}
			}
			else if (richEdit_itemType_gif == pItem->type)
			{
				pItemGif = (richEdit_item_gif_*)pItem;
				if (pItemGif->hString)
				{
					wchar_t *pPath = XStr_GetBuffer(pItemGif->hString);
					buf_html += L"<img src=";
					buf_html += pPath;
					buf_html += L" >";
				}
			}
		}
	}
	int charLen = buf_html.size();
	if (charLen < 1) return;

	wchar_t EndHTML[20] = { 0 };
	wsprintf(EndHTML, L"EndHTML:%08d\r\n", 171 + charLen);

	wchar_t EndFragment[23] = { 0 };
	wsprintf(EndFragment, L"EndFragment:%08d\r\n", 134 + charLen);

	std::wstring sendbuf;
	sendbuf = L"Version:0.9\r\n";
	sendbuf += L"StartHTML:00000097\r\n"; //ok
	//sendbuf+="EndHTML:00000336\r\n";   //?  171+buf
	sendbuf += EndHTML;
	sendbuf += L"StartFragment:00000134\r\n"; //ok
	//sendbuf+="EndFragment:00000300\r\n";   //?
	sendbuf += EndFragment;
	sendbuf += L"<html><body>\r\n";
	sendbuf += L"<!--StartFragment -->\r\n";
	sendbuf += buf_html;
	sendbuf += L"\r\n<!--EndFragment -->\r\n";
	sendbuf += L"</body></html>";

	XStr_SetString(hString, (wchar_t*)sendbuf.c_str());
}

/// @brief 获取富文本数据,包含字体,图片,颜色信息.
/// @param hEle   元素句柄.
/// @return   返回数据内存指针,不用之后需要释放内容XC_Free().
void* WINAPI XRichEdit_GetData(HELE hEle)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	HARRAY    hArrayItem = XArray_Create();

	richEdit_line_         *pLine = NULL;
	richEdit_item_         *pItem = NULL;
	richEdit_item_char_    *pItemChar = NULL;
	richEdit_item_iamge_   *pItemImage = NULL;
	richEdit_item_gif_     *pItemGif = NULL;

	richEdit_clipboard_char_  *pClipboard_char = NULL;
	richEdit_clipboard_iamge_ *pClipboard_image = NULL;

	int  DataSize = 0;
	int  countItem = 0;
	for (int i = 0; i < pRichEdit->rowCount; i++)
	{
		if (0 != i)
		{
			pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
			pClipboard_char->type = richEdit_itemType_char;
			pClipboard_char->bColor = FALSE;
			pClipboard_char->color = 0;
			pClipboard_char->ch = L'\n';
			pClipboard_char->fontIndex = -1;
			XArray_Add(hArrayItem, pClipboard_char);
			DataSize += sizeof(richEdit_clipboard_char_);
		}

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
				pClipboard_char->type = richEdit_itemType_char;
				pClipboard_char->bColor = pItemChar->bColor;
				pClipboard_char->color = pItemChar->color;
				pClipboard_char->ch = pItemChar->ch;
				if (pItemChar->pFontInfo)
					pClipboard_char->fontIndex = pItemChar->pFontInfo->index;
				else
					pClipboard_char->fontIndex = -1;
				XArray_Add(hArrayItem, pClipboard_char);
				DataSize += sizeof(richEdit_clipboard_char_);
			}
			else if (richEdit_itemType_image == pItem->type)
			{
				pItemImage = (richEdit_item_iamge_*)pItem;
				if (pItemImage->hString)
				{
					wchar_t *pPath = XStr_GetBuffer(pItemImage->hString);
					int mallocSize = XStr_GetLength(pItemImage->hString) + 1;
					mallocSize = mallocSize * 2;
					mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
					pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
					pClipboard_image->type = richEdit_itemType_image;
					pClipboard_image->size = mallocSize;
					wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
					XArray_Add(hArrayItem, pClipboard_image);
					DataSize += mallocSize;
				}
			}
			else if (richEdit_itemType_gif == pItem->type)
			{
				pItemGif = (richEdit_item_gif_*)pItem;
				if (pItemGif->hString)
				{
					wchar_t *pPath = XStr_GetBuffer(pItemGif->hString);
					int mallocSize = XStr_GetLength(pItemGif->hString) + 1;
					mallocSize = mallocSize * 2;
					mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
					pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
					pClipboard_image->type = richEdit_itemType_gif;
					pClipboard_image->size = mallocSize;
					wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
					XArray_Add(hArrayItem, pClipboard_image);
					DataSize += mallocSize;
				}
			}
		}
	}

	countItem = XArray_GetCount(hArrayItem);
	if (countItem < 1)
	{
		XArray_Destroy(hArrayItem);
		return NULL;
	}
	////////////////////////////////////////////////////////
	int  byteSize = 0; //内容总大小
	richEdit_clipboard_header_  clipboard_header;
	clipboard_header.color = XEle_GetTextColor(hEle);
	clipboard_header.fontCount = XArray_GetCount(pRichEdit->hArrayFont);
	clipboard_header.itemCount = 0;
	clipboard_header.size = 0;
	clipboard_header.name;
	wcscpy(clipboard_header.name, L"XCGUI_RichEdit");
	GetObject(XEle_GetFont(hEle), sizeof(LOGFONT), &clipboard_header.font);

	richEdit_font_Info_  *pFontInfo = NULL;

	byteSize = sizeof(richEdit_clipboard_header_);
	byteSize = byteSize + clipboard_header.fontCount * sizeof(LOGFONT);

	byteSize = byteSize + DataSize;
	clipboard_header.size = byteSize;
	clipboard_header.itemCount = XArray_GetCount(hArrayItem);

	byte *pBuf = (byte*)malloc(byteSize);
	byte *pPosition = pBuf;
	memset(pBuf, 0, byteSize);

	//存储数据
	int sizeT = sizeof(richEdit_clipboard_header_);
	memcpy(pPosition, &clipboard_header, sizeT);
	pPosition += sizeT;

	for (int i = 0; i < clipboard_header.fontCount; i++)
	{
		pFontInfo = (richEdit_font_Info_*)XArray_GetAt(pRichEdit->hArrayFont, i);
		pFontInfo->info;
		memcpy(pPosition, &pFontInfo->info, sizeof(LOGFONT));
		pPosition += sizeof(LOGFONT);
	}

	for (int i = 0; i < countItem; i++)
	{
		void *p = XArray_GetAt(hArrayItem, i);
		if (richEdit_itemType_char == *(rictEdit_ItemType_*)p)
		{
			memcpy(pPosition, p, sizeof(richEdit_clipboard_char_));
			pPosition += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == *(rictEdit_ItemType_*)p)
		{
			memcpy(pPosition, p, ((richEdit_clipboard_iamge_*)p)->size);
			pPosition += ((richEdit_clipboard_iamge_*)p)->size;
		}
		else if (richEdit_itemType_gif == *(rictEdit_ItemType_*)p)
		{
			memcpy(pPosition, p, ((richEdit_clipboard_iamge_*)p)->size);
			pPosition += ((richEdit_clipboard_iamge_*)p)->size;
		}
		else
		{
			XTRACE("richEdit 剪贴板复制数据错误\n");
			exit(0);
		}
	}

	////////////////////////////////////////////////

	int hArrayCount = XArray_GetCount(hArrayItem);
	for (int i = 0; i < hArrayCount; i++)
	{
		void *pData = XArray_GetAt(hArrayItem, i);
		free(pData);
	}
	XArray_Destroy(hArrayItem);

	return pBuf;
}

/// @brief 获取文本内容.
/// @param hEle    元素句柄.
/// @param hString    接收返回的字符串.
void WINAPI XRichEdit_GetText(HELE hEle, HSTRING hString) //获取文本内容
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	std::wstring   buf_text;

	richEdit_line_  *pLine = NULL;
	richEdit_item_  *pItem = NULL;
	int             countItem = 0;
	for (int i = 0; i < pRichEdit->rowCount; i++)
	{
		if (0 != i)
		{
			buf_text += L"\r\n";
		}

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				buf_text += ((richEdit_item_char_*)pItem)->ch;
			}
		}
	}
	XStr_SetString(hString, (wchar_t*)buf_text.c_str());
}

/// @brief 获取插入符位置,当前行和列.
/// @param hEle    元素句柄.
/// @param pRow     接收行索引.
/// @param pColumn  接收列索引.
void WINAPI XRichEdit_GetCurrentPos(HELE hEle, out_ int *pRow, out_ int *pColumn)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	*pRow = pRichEdit->row;
	*pColumn = pRichEdit->column;
}

/// @brief 获取选择内容位置.
/// @param hEle         元素句柄.
/// @param pBeginRow    开始行索引.
/// @param pBeginColumn 开始列索引.
/// @param pEndRow      结束行索引.
/// @param pEndColumn   结束列索引.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_GetSelectPos(HELE hEle, out_ int *pBeginRow, out_ int *pBeginColumn, out_ int *pEndRow, out_ int *pEndColumn)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect)
	{
		if (pRichEdit->downRow == pRichEdit->endRow)
		{
			*pBeginRow = pRichEdit->downRow;
			*pEndRow = pRichEdit->endRow;
			if (pRichEdit->downColumn < pRichEdit->endColumn)
			{
				*pBeginColumn = pRichEdit->downColumn;
				*pEndColumn = pRichEdit->endColumn;
			}
			else
			{
				*pBeginColumn = pRichEdit->endColumn;
				*pEndColumn = pRichEdit->downColumn;
			}
		}
		else if (pRichEdit->downRow <= pRichEdit->endRow)
		{
			*pBeginRow = pRichEdit->downRow;
			*pBeginColumn = pRichEdit->downColumn;
			*pEndRow = pRichEdit->endRow;
			*pEndColumn = pRichEdit->endColumn;
		}
		else
		{
			*pBeginRow = pRichEdit->endRow;
			*pBeginColumn = pRichEdit->endColumn;
			*pEndRow = pRichEdit->downRow;
			*pEndColumn = pRichEdit->downColumn;
		}
		return TRUE;
	}
	return FALSE;
}

/// @brief 获取选择文本.
/// @param hEle    元素句柄.
/// @param pOut    接收内容的内存块指针.
/// @param len     内存块长度,字符为单位.
/// @return 返回接收字符实际长度.
int WINAPI XRichEdit_GetSelectText(HELE hEle, wchar_t *pOut, int len)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (FALSE == pRichEdit->bDrawSelect)
		return 0;

	if (pRichEdit->downRow == pRichEdit->endRow) //单行
	{
		return RichEdit_GetSelectSingleLine(hEle, pOut, len);
	}
	else	//多行
	{
		return RichEdit_GetSelectMultiLine(hEle, pOut, len);
	}
}

int RichEdit_GetSelectSingleLine(HELE hEle, wchar_t *pOut, int len)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	int beginRow = 0;
	int	beginColumn = 0;
	int	endRow = 0;
	int	endColumn = 0;

	if (pRichEdit->downRow == pRichEdit->endRow)
	{
		beginRow = pRichEdit->downRow;
		endRow = pRichEdit->endRow;
		if (pRichEdit->downColumn < pRichEdit->endColumn)
		{
			beginColumn = pRichEdit->downColumn;
			endColumn = pRichEdit->endColumn;
		}
		else
		{
			beginColumn = pRichEdit->endColumn;
			endColumn = pRichEdit->downColumn;
		}
	}
	else
		return 0;

	if (beginColumn >= endColumn)
		return 0;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	if (endColumn > XArray_GetCount(pLine->hArrayItem))
		return 0;

	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;

	int index = 0;
	for (int i = beginColumn; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			if (index >= (len - 1))
				break;
			pOut[index] = pItemChar->ch;
			index++;
		}
	}
	pOut[index] = 0;
	return  index;
}

int RichEdit_GetSelectMultiLine(HELE hEle, wchar_t *pOut, int len)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int beginRow = 0;
	int	beginColumn = 0;
	int	endRow = 0;
	int	endColumn = 0;

	if (pRichEdit->downRow == pRichEdit->endRow)
	{
		beginRow = pRichEdit->downRow;
		endRow = pRichEdit->endRow;
		if (pRichEdit->downColumn < pRichEdit->endColumn)
		{
			beginColumn = pRichEdit->downColumn;
			endColumn = pRichEdit->endColumn;
		}
		else
		{
			beginColumn = pRichEdit->endColumn;
			endColumn = pRichEdit->downColumn;
		}
	}
	else if (pRichEdit->downRow <= pRichEdit->endRow)
	{
		beginRow = pRichEdit->downRow;
		beginColumn = pRichEdit->downColumn;
		endRow = pRichEdit->endRow;
		endColumn = pRichEdit->endColumn;
	}
	else
	{
		beginRow = pRichEdit->endRow;
		beginColumn = pRichEdit->endColumn;
		endRow = pRichEdit->downRow;
		endColumn = pRichEdit->downColumn;
	}

	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;

	int index = 0;

	//开始行
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (beginColumn < countItem)
	{
		for (int i = beginColumn; i < countItem; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;

				if (index >= (len - 1))
				{
					pOut[index] = 0;
					return index;
				}
				pOut[index] = pItemChar->ch;
				index++;
			}
		}
		if (index >= (len - 1))
		{
			pOut[index] = 0;
			return index;
		}
		pOut[index] = L'\r'; index++;
		if (index >= (len - 1))
		{
			pOut[index] = 0;
			return index;
		}
		pOut[index] = L'\n'; index++;
	}

	//中间行
	int countLine = endRow - beginRow - 1;
	for (int i = 0; i < countLine; i++)
	{
		richEdit_line_ *pLineT = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + 1 + i);
		int count = XArray_GetCount(pLineT->hArrayItem);
		int lenPixel = 0;
		for (int j = 0; j < count; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineT->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;

				if (index >= (len - 1))
				{
					pOut[index] = 0;
					return index;
				}
				pOut[index] = pItemChar->ch;
				index++;
			}
		}

		if (index >= (len - 1))
		{
			pOut[index] = 0;
			return index;
		}
		pOut[index] = L'\r'; index++;
		if (index >= (len - 1))
		{
			pOut[index] = 0;
			return index;
		}
		pOut[index] = L'\n'; index++;
	}

	//结束行
	pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, endRow);
	countItem = XArray_GetCount(pLine->hArrayItem);
	if (endColumn <= countItem)
	{
		int lenPixel = 0;
		for (int i = 0; i < endColumn; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;

				if (index >= (len - 1))
				{
					pOut[index] = 0;
					return index;
				}
				pOut[index] = pItemChar->ch;
				index++;
			}
		}
	}
	return index;
}

/// @brief 获取总行数.
/// @param hEle    元素句柄.
/// @return 返回总行数.
int WINAPI XRichEdit_GetRowCount(HELE hEle)  //获取总行数
{
	IsRichEditDebug(hEle, __FUNCTION__);
	return ((richEdit_*)hEle)->rowCount;
}

/// @brief 获取指定行内容数量,不包含回车换行符.
/// @param hEle   元素句柄.
/// @param row    行索引.
/// @return   返回指定行内容数量,错误返回-1,
int  WINAPI XRichEdit_GetRowItemCount(HELE hEle, int row)  //获取指定行内容数量
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);
	if (pLine)
	{
		return XArray_GetCount(pLine->hArrayItem);
	}
	return -1;
}

/// @brief 获取可视行范围.
/// @param hEle       元素句柄.
/// @param pBeginRow  接收第一个可视行索引.
/// @param pEndRow    接收最后一个可视行索引.
void WINAPI XRichEdit_GetVisibleRow(HELE hEle, out_ int *pBeginRow, out_ int *pEndRow) //获取可视行范围
{
	IsRichEditDebug(hEle, __FUNCTION__);

	*pBeginRow = ((richEdit_*)hEle)->visibleBegin;
	*pEndRow = ((richEdit_*)hEle)->visibleEnd;
}

/// @brief  获取默认行高.
/// @param  hEle       元素句柄.
/// @return 返回默认行高.
int  WINAPI XRichEdit_GetRowHeight(HELE hEle)  //获取默认行高
{
	IsRichEditDebug(hEle, __FUNCTION__);
	return ((richEdit_*)hEle)->lineHeight;
}

/// @brief  获取使用字体数量.
/// @param  hEle       元素句柄.
/// @return  字体数量.
int  WINAPI XRichEdit_GetFontCount(HELE hEle)  //获取字体数量
{
	IsRichEditDebug(hEle, __FUNCTION__);
	return XArray_GetCount(((richEdit_*)hEle)->hArrayFont);
}

/// @brief 判断内容是否为空.
/// @param hEle    元素句柄.
/// @return 如果内容为空返回TRUE,否则相反.
BOOL WINAPI XRichEdit_IsEmpty(HELE hEle)  //判断内容是否为空
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	int countLine = XArray_GetCount(pRichEdit->hArrayLine);
	if (1 == countLine)
	{
		richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, 0);
		if (XArray_GetCount(pLine->hArrayItem) < 1)
			return TRUE;
	}

	return FALSE;
}

/// @brief 取消选择.
/// @param hEle    元素句柄.
/// @return 如果内容为空返回TRUE,否则相反.
BOOL WINAPI XRichEdit_CancelSelect(HELE hEle) //取消选择
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect)
	{
		pRichEdit->bDrawSelect = FALSE;
		return TRUE;
	}
	return FALSE;
}

/// @brief 全选,选择所有内容.
/// @param hEle    元素句柄.
void WINAPI XRichEdit_SelectAll(HELE hEle)  //全选  选择所有文本
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->rowCount - 1);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (1 == pRichEdit->rowCount)
	{
		if (0 == countItem)
			return;
	}

	//选择
	pRichEdit->downRow = 0;
	pRichEdit->downColumn = 0;
	pRichEdit->endRow = pRichEdit->rowCount - 1;
	pRichEdit->endColumn = countItem;
	pRichEdit->bDrawSelect = TRUE;

	//插入符
	pRichEdit->row = pRichEdit->rowCount - 1;
	pRichEdit->column = countItem;
	pRichEdit->caretPt.x = pLine->lenPixel;
	pRichEdit->caretPt.y = pLine->top;
	RichEdit_SetCaretPos(hEle);

	RichEdit_ScrollH(hEle);
	RichEdit_ScrollV(hEle);

	XEle_RedrawEle(hEle);
}

XC_API void WINAPI XRichEdit_Select(HELE hEle, int minCol, int minRow, int maxCol, int maxRow)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->rowCount - 1);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (1 == pRichEdit->rowCount)
	{
		if (0 == countItem)
			return;
	}

	if (minCol > pRichEdit->rowCount - 1 || minCol < 0)
		minCol = pRichEdit->rowCount - 1;
	if (minRow > countItem || minRow < 0)
		minRow = countItem;
	if (maxCol > pRichEdit->rowCount - 1 || maxCol < 0)
		maxCol = pRichEdit->rowCount - 1;
	if (maxRow > countItem || maxRow < 0)
		maxRow = countItem;

	//选择
	pRichEdit->downRow = minCol;
	pRichEdit->downColumn = minRow;
	pRichEdit->endRow = maxCol;
	pRichEdit->endColumn = maxRow;
	pRichEdit->bDrawSelect = TRUE;

	//插入符
	pRichEdit->row = minCol;
	pRichEdit->column = minRow;
	pRichEdit->caretPt.x = pLine->lenPixel;
	pRichEdit->caretPt.y = pLine->top;
	RichEdit_SetCaretPos(hEle);

	RichEdit_ScrollH(hEle);
	RichEdit_ScrollV(hEle);

	XEle_RedrawEle(hEle);
}

/// @brief  清理字体表,释放未使用的字体.
/// @param  hEle    元素句柄.
void WINAPI XRichEdit_ClearFontTable(HELE hEle)   //清理字体表,清理未使用的字体
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_font_Info_  *pFontInfo = NULL;
	for (int i = 0; i < XArray_GetCount(pRichEdit->hArrayFont); i++)
	{
		pFontInfo = (richEdit_font_Info_*)XArray_GetAt(pRichEdit->hArrayFont, i);
		if (RichEdit_IsUnUseFont(pRichEdit->hArrayLine, pFontInfo))
		{
			XArray_DeleteIndex(pRichEdit->hArrayFont, i);

			DeleteObject(pFontInfo->hFont);
			free(pFontInfo);
			i--;
		}
	}

	int countFont = XArray_GetCount(pRichEdit->hArrayFont);
	for (int i = 0; i < countFont; i++)
	{
		pFontInfo = (richEdit_font_Info_*)XArray_GetAt(pRichEdit->hArrayFont, i);
		pFontInfo->index = i;
	}
}

BOOL RichEdit_IsUnUseFont(HARRAY hArrayLine, richEdit_font_Info_ *pFontInfo)
{
	richEdit_line_  *pLine = NULL;
	richEdit_item_  *pItem = NULL;
	richEdit_item_char_  *pItemChar = NULL;
	int countItem = 0;
	int countLine = XArray_GetCount(hArrayLine);
	for (int i = 0; i < countLine; i++)
	{
		pLine = (richEdit_line_*)XArray_GetAt(hArrayLine, i);
		countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				if (pItemChar->pFontInfo && pFontInfo == pItemChar->pFontInfo)
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

/// @brief 删除指定内容,当前未启用.
/// @param hEle    元素句柄.
/// @param beginRow     开始行索引.
/// @param beginColumn  开始行列索引.
/// @param endRow       结束行索引
/// @param endColumn    结束行列索引
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_DeleteEx(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn) //删除指定内容
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (beginRow < 0 || beginColumn < 0 || endRow < 0 || endColumn < 0)
		return FALSE;

	if (pRichEdit->bDrawSelect)
		XRichEdit_CancelSelect(hEle);

	if (beginRow == endRow) //只有一行
	{
		return RichEdit_DeleteEx_SingleLine(hEle, beginRow, beginColumn, endRow, endColumn);
	}
	else  //多行
	{
		return RichEdit_DeleteEx_MultiLine(hEle, beginRow, beginColumn, endRow, endColumn);
	}
}

BOOL RichEdit_DeleteEx_SingleLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (beginColumn >= endColumn)
		return FALSE;

	if (beginRow >= pRichEdit->rowCount)
		return FALSE;

	richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (endColumn > countItem)
		return FALSE;

	int type = 0;
	if (beginRow == pRichEdit->row)
	{
		if (pRichEdit->column > beginColumn)
			type = 1; //插入符在后面
	}

	richEdit_item_  *pItem = NULL;
	for (int i = beginColumn; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		pLine->lenPixel -= pItem->size.cx;

		if (1 == type)
		{
			pRichEdit->column--;
		}
		RichEdit_FreeItem(pItem);
	}

	XArray_DeleteRange(pLine->hArrayItem, beginColumn, endColumn - 1);
	RichEdit_Calculate_LineMaxHeight(hEle, beginRow);

	if (pRichEdit->row >= beginRow)
	{
		//RichEdit_Calculate_CaretPos(hEle);	//计算插入符新位置
		pRichEdit->bAdjustCalculate = TRUE;
		pRichEdit->bAdjustCaret = TRUE;
	}

	pRichEdit->bAdjust = TRUE;
	return TRUE;
}

BOOL RichEdit_DeleteEx_MultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (beginRow >= endRow)
		return FALSE;

	if (endRow >= pRichEdit->rowCount)
		return FALSE;

	//开始行
	richEdit_line_  *pLineBegin = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	int countItemBegin = XArray_GetCount(pLineBegin->hArrayItem);
	if (beginColumn > countItemBegin)
		return FALSE;

	//结束行
	richEdit_line_  *pLineEnd = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, endRow);
	int countItemEnd = XArray_GetCount(pLineEnd->hArrayItem);
	if (endColumn > countItemEnd)
		return FALSE;

	//插入符,1:在删除内容中,2:在结束行删除内容后面,3:插入符在结束行之后行
	int type = 0;
	if (pRichEdit->row >= beginRow && pRichEdit->row <= endRow)
	{
		if (pRichEdit->row == beginRow)
		{
			if (pRichEdit->column > beginColumn)
			{
				type = 1;
			}
		}
		else if (pRichEdit->row == endRow)
		{
			if (pRichEdit->column <= endColumn)
			{
				type = 1;
			}
			else
				type = 2;
		}
		else
		{
			type = 1;
		}
	}

	//结束行
	richEdit_item_ *pItem = NULL;
	for (int i = 0; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineEnd->hArrayItem, i);
		pLineEnd->lenPixel -= pItem->size.cx;
		RichEdit_FreeItem(pItem);
	}
	XArray_DeleteRange(pLineEnd->hArrayItem, 0, endColumn - 1);

	//中间行
	int countLine = endRow - beginRow - 1; //行数
	for (int i = 0; i < countLine; i++)
	{
		richEdit_line_  *pLineT = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + i + 1);
		RichEdit_FreeLine(pLineT);
		pRichEdit->rowCount--;
	}
	if (countLine > 0)
		XArray_DeleteRange(pRichEdit->hArrayLine, beginRow + 1, endRow - 1);

	//开始行
	for (int i = beginColumn; i < countItemBegin; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineBegin->hArrayItem, i);
		pLineBegin->lenPixel -= pItem->size.cx;
		RichEdit_FreeItem(pItem);
	}
	XArray_DeleteEnd(pLineBegin->hArrayItem, beginColumn);

	//将开始行与结束行合并为一行
	int count = XArray_GetCount(pLineEnd->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineEnd->hArrayItem, i);
		XArray_Add(pLineBegin->hArrayItem, pItem);
		pLineBegin->lenPixel += pItem->size.cx;
	}
	XArray_DeleteIndex(pRichEdit->hArrayLine, beginRow + 1);
	XArray_Destroy(pLineEnd->hArrayItem);
	free(pLineEnd);

	pRichEdit->rowCount--;
	RichEdit_Calculate_LineMaxHeight(hEle, beginRow);

	if (1 == type)
	{
		pRichEdit->row = beginRow;
		pRichEdit->column = beginColumn;
	}
	else if (2 == type)
	{
		pRichEdit->row = beginRow;
		pRichEdit->column = beginColumn + (pRichEdit->column - endColumn);
	}
	else if (pRichEdit->row > endRow)
	{
		pRichEdit->row = pRichEdit->row - countLine - 1;
	}

	if (pRichEdit->row >= beginRow)
	{
		//	RichEdit_Calculate_CaretPos(hEle);	//计算插入符新位置
		pRichEdit->bAdjustCalculate = TRUE;
		pRichEdit->bAdjustCaret = TRUE;
	}

	pRichEdit->bAdjust = TRUE;
	return TRUE;
}

richEdit_font_Info_* RichEdit_GetFont(HELE hEle, LOGFONT *pFont)  //检查字体
{
	if (NULL == pFont)
		return NULL;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_font_Info_  *pFontInfoT = NULL;
	//检查是否在字体表
	int count = XArray_GetCount(pRichEdit->hArrayFont);
	for (int i = 0; i < count; i++)
	{
		pFontInfoT = (richEdit_font_Info_*)XArray_GetAt(pRichEdit->hArrayFont, i);
		if (pFontInfoT->info.lfHeight == pFont->lfHeight &&
			pFontInfoT->info.lfWidth == pFont->lfWidth &&
			pFontInfoT->info.lfEscapement == pFont->lfEscapement &&
			pFontInfoT->info.lfOrientation == pFont->lfOrientation &&
			pFontInfoT->info.lfWeight == pFont->lfWeight &&
			pFontInfoT->info.lfItalic == pFont->lfItalic &&
			pFontInfoT->info.lfUnderline == pFont->lfUnderline &&
			pFontInfoT->info.lfStrikeOut == pFont->lfStrikeOut &&
			pFontInfoT->info.lfCharSet == pFont->lfCharSet &&
			pFontInfoT->info.lfOutPrecision == pFont->lfOutPrecision &&
			pFontInfoT->info.lfClipPrecision == pFont->lfClipPrecision &&
			pFontInfoT->info.lfQuality == pFont->lfQuality &&
			pFontInfoT->info.lfPitchAndFamily == pFont->lfPitchAndFamily)
		{
			if (0 == wcscmp(pFontInfoT->info.lfFaceName, pFont->lfFaceName))
			{
				return pFontInfoT;
			}
		}
	}

	//如果不在,添加到字体表
	richEdit_font_Info_  *pFontInfo = NULL;
	pFontInfo = (richEdit_font_Info_*)malloc(sizeof(richEdit_font_Info_));
	pFontInfo->hFont = CreateFontIndirect(pFont);
	pFontInfo->info = *pFont;
	pFontInfo->index = XArray_Add(pRichEdit->hArrayFont, pFontInfo);

	return pFontInfo;
}

/// @brief 删除选择内容.
/// @param hEle    元素句柄.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_DeleteSelect(HELE hEle)
{
	IsRichEditDebug(hEle, __FUNCTION__);
	return RichEdit_DeleteSelect(hEle);
}

/// @brief 清空内容.
/// @param hEle    元素句柄.
void WINAPI XRichEdit_DeleteAll(HELE hEle) //清空内容
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	pRichEdit->bDrawSelect = FALSE;
	pRichEdit->row = 0;
	pRichEdit->column = 0;
	pRichEdit->rowCount = 1;

	int countLine = XArray_GetCount(pRichEdit->hArrayLine);

	richEdit_line_  *pLine = NULL;
	richEdit_item_  *pItem = NULL;

	//清除第一行数据
	pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, 0);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	for (int j = 0; j < countItem; j++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
		RichEdit_FreeItem(pItem);
	}
	pLine->lenPixel = 0;
	pLine->maxItemHeight = pRichEdit->lineHeight;
	pLine->top = 0;
	XArray_DeleteAll(pLine->hArrayItem);

	for (int i = 1; i < countLine; i++)
	{
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		int countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			RichEdit_FreeItem(pItem);
		}
		XArray_Destroy(pLine->hArrayItem);
		free(pLine);
	}
	XArray_DeleteEnd(pRichEdit->hArrayLine, 1);

	pRichEdit->caretPt.x = 0;
	pRichEdit->caretPt.y = 0;

	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;
}

/// @brief 剪切,删除选择的文本,并将选择文本拷贝到剪切板中.
/// @param hEle    元素句柄.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_Menu_Cut(HELE hEle)        //剪切  删除选择的文本,并将文本拷贝到剪切板中
{
	IsRichEditDebug(hEle, __FUNCTION__);
	BOOL bResult1 = XRichEdit_Menu_Copy(hEle);      //复制

	BOOL bResult2 = RichEdit_DeleteSelect(hEle);  //删除选择的文本
	if (bResult1 || bResult2)
		return TRUE;
	return FALSE;
}

/// @brief 复制,复制选择的文本到剪切板中.
/// @param hEle    元素句柄.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_Menu_Copy(HELE hEle)       //复制  复制选择的文本到剪切板中
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (FALSE == pRichEdit->bDrawSelect) return FALSE;

	pRichEdit->bDrawSelect = FALSE;

	if (pRichEdit->downRow == pRichEdit->endRow) //只有一行
	{
		return RichEdit_Clipboard_CopySingleLine(hEle);
	}
	else if (pRichEdit->downRow < pRichEdit->endRow)  //向下选择
	{
		return RichEdit_Clipboard_CopyMultiLine(hEle,
			pRichEdit->downRow, pRichEdit->downColumn, pRichEdit->endRow, pRichEdit->endColumn, TRUE);
	}
	else  //向上选择
	{
		return RichEdit_Clipboard_CopyMultiLine(hEle,
			pRichEdit->endRow, pRichEdit->endColumn, pRichEdit->downRow, pRichEdit->downColumn, FALSE);
	}

	return TRUE;
}

BOOL RichEdit_Clipboard_CopySingleLine(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int beginColumn = 0;
	int endColumn = 0;

	if (pRichEdit->downColumn < pRichEdit->endColumn)
	{
		beginColumn = pRichEdit->downColumn;
		endColumn = pRichEdit->endColumn;
	}
	else
	{
		beginColumn = pRichEdit->endColumn;
		endColumn = pRichEdit->downColumn;
	}

	int beginRow = pRichEdit->downRow;
	int	endRow = pRichEdit->endRow;

	if (beginColumn >= endColumn)
		return FALSE;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	if (endColumn > XArray_GetCount(pLine->hArrayItem))
		return FALSE;

	///////////////////////////////////////////////////
	std::wstring  bufText;
	std::wstring  buf_HTML_Text;
	HARRAY   hArrayItem = XArray_Create();
	int  DataSize = 0;
	richEdit_clipboard_char_   *pClipboard_char = NULL;
	richEdit_clipboard_iamge_  *pClipboard_image = NULL;
	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;

	richEdit_item_gif_    *pItemGif = NULL;
	richEdit_item_iamge_  *pItemImage = NULL;
	for (int i = beginColumn; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			buf_HTML_Text += pItemChar->ch;
			bufText += pItemChar->ch;

			pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
			pClipboard_char->type = richEdit_itemType_char;
			pClipboard_char->bColor = pItemChar->bColor;
			pClipboard_char->color = pItemChar->color;
			pClipboard_char->ch = pItemChar->ch;
			if (pItemChar->pFontInfo)
				pClipboard_char->fontIndex = pItemChar->pFontInfo->index;
			else
				pClipboard_char->fontIndex = -1;
			XArray_Add(hArrayItem, pClipboard_char);
			DataSize += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == pItem->type)
		{
			pItemImage = (richEdit_item_iamge_*)pItem;
			if (pItemImage->hString)
			{
				wchar_t *pPath = XStr_GetBuffer(pItemImage->hString);
				buf_HTML_Text += L"<img src=";
				buf_HTML_Text += pPath;
				buf_HTML_Text += L" >";

				int mallocSize = XStr_GetLength(pItemImage->hString) + 1;
				mallocSize = mallocSize * 2;
				mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
				pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
				pClipboard_image->type = richEdit_itemType_image;
				pClipboard_image->size = mallocSize;
				wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
				XArray_Add(hArrayItem, pClipboard_image);
				DataSize += mallocSize;
			}
		}
		else if (richEdit_itemType_gif == pItem->type)
		{
			pItemGif = (richEdit_item_gif_*)(pItem);
			wchar_t *pPath = XStr_GetBuffer(pItemGif->hString);
			buf_HTML_Text += L"<img src=";
			buf_HTML_Text += pPath;
			buf_HTML_Text += L" >";

			int mallocSize = XStr_GetLength(pItemGif->hString) + 1;
			mallocSize = mallocSize * 2;
			mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
			pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
			pClipboard_image->type = richEdit_itemType_gif;
			pClipboard_image->size = mallocSize;
			wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
			XArray_Add(hArrayItem, pClipboard_image);
			DataSize += mallocSize;
		}
	}
	int hArrayCount = XArray_GetCount(hArrayItem);
	if (hArrayCount < 1)
	{
		XArray_Destroy(hArrayItem);
		return FALSE;
	}

	if (OpenClipboard(((ele_*)hEle)->pWindow->hWnd))
	{
		EmptyClipboard();
		RichEdit_Clipboard_Copy_Text((wchar_t*)bufText.c_str(), bufText.size());
		RichEdit_Clipboard_Copy_HTMLFormat((wchar_t*)buf_HTML_Text.c_str(), buf_HTML_Text.size());
		RichEdit_Clipboard_Copy_Data(hEle, hArrayItem, DataSize);
		CloseClipboard();
	}

	for (int i = 0; i < hArrayCount; i++)
	{
		void *pData = XArray_GetAt(hArrayItem, i);
		free(pData);
	}
	XArray_Destroy(hArrayItem);

	return TRUE;
}

BOOL RichEdit_Clipboard_CopyMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, BOOL bForward)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	HARRAY   hArrayItem = XArray_Create();
	int  DataSize = 0;
	richEdit_clipboard_char_   *pClipboard_char = NULL;
	richEdit_clipboard_iamge_  *pClipboard_image = NULL;

	richEdit_item_iamge_  *pItemImage = NULL;
	richEdit_item_gif_ *pItemGif = NULL;

	std::wstring  buf_HTML_Text;
	std::wstring  buf_Text;
	//开始行
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);

	int itemCount = XArray_GetCount(pLine->hArrayItem);
	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;
	for (int i = beginColumn; i < itemCount; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			buf_Text += pItemChar->ch;
			buf_HTML_Text += pItemChar->ch;

			pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
			pClipboard_char->type = richEdit_itemType_char;
			pClipboard_char->bColor = pItemChar->bColor;
			pClipboard_char->color = pItemChar->color;
			pClipboard_char->ch = pItemChar->ch;
			if (pItemChar->pFontInfo)
				pClipboard_char->fontIndex = pItemChar->pFontInfo->index;
			else
				pClipboard_char->fontIndex = -1;
			XArray_Add(hArrayItem, pClipboard_char);
			DataSize += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == pItem->type)
		{
			pItemImage = (richEdit_item_iamge_*)pItem;
			if (pItemImage->hString)
			{
				wchar_t *pPath = XStr_GetBuffer(pItemImage->hString);
				buf_HTML_Text += L"<img src=";
				buf_HTML_Text += pPath;
				buf_HTML_Text += L" >";

				int mallocSize = XStr_GetLength(pItemImage->hString) + 1;
				mallocSize = mallocSize * 2;
				mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
				pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
				pClipboard_image->type = richEdit_itemType_image;
				pClipboard_image->size = mallocSize;
				wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
				XArray_Add(hArrayItem, pClipboard_image);
				DataSize += mallocSize;
			}
		}
		else if (richEdit_itemType_gif == pItem->type)
		{
			pItemGif = (richEdit_item_gif_*)(pItem);
			wchar_t *pPath = XStr_GetBuffer(pItemGif->hString);

			buf_HTML_Text += L"<img src=";
			buf_HTML_Text += pPath;
			buf_HTML_Text += L" >";

			int mallocSize = XStr_GetLength(pItemGif->hString) + 1;
			mallocSize = mallocSize * 2;
			mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
			pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
			pClipboard_image->type = richEdit_itemType_gif;
			pClipboard_image->size = mallocSize;
			wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
			XArray_Add(hArrayItem, pClipboard_image);
			DataSize += mallocSize;
		}
	}
	buf_Text += L"\r\n";
	buf_HTML_Text += L"<br>";

	pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
	pClipboard_char->type = richEdit_itemType_char;
	pClipboard_char->bColor = FALSE;
	pClipboard_char->color = 0;
	pClipboard_char->ch = L'\n';
	pClipboard_char->fontIndex = -1;
	XArray_Add(hArrayItem, pClipboard_char);
	DataSize += sizeof(richEdit_clipboard_char_);

	//中间行
	int countLine = endRow - beginRow - 1;
	for (int i = 0; i < countLine; i++)
	{
		richEdit_line_ *pLineT = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + 1 + i);
		itemCount = XArray_GetCount(pLineT->hArrayItem);
		for (int j = 0; j < itemCount; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineT->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				buf_Text += pItemChar->ch;
				buf_HTML_Text += pItemChar->ch;

				pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
				pClipboard_char->type = richEdit_itemType_char;
				pClipboard_char->bColor = pItemChar->bColor;
				pClipboard_char->color = pItemChar->color;
				pClipboard_char->ch = pItemChar->ch;
				if (pItemChar->pFontInfo)
					pClipboard_char->fontIndex = pItemChar->pFontInfo->index;
				else
					pClipboard_char->fontIndex = -1;
				XArray_Add(hArrayItem, pClipboard_char);
				DataSize += sizeof(richEdit_clipboard_char_);
			}
			else if (richEdit_itemType_image == pItem->type)
			{
				pItemImage = (richEdit_item_iamge_*)pItem;
				if (pItemImage->hString)
				{
					wchar_t *pPath = XStr_GetBuffer(pItemImage->hString);
					buf_HTML_Text += L"<img src=";
					buf_HTML_Text += pPath;
					buf_HTML_Text += L" >";

					int mallocSize = XStr_GetLength(pItemImage->hString) + 1;
					mallocSize = mallocSize * 2;
					mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
					pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
					pClipboard_image->type = richEdit_itemType_image;
					pClipboard_image->size = mallocSize;
					wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
					XArray_Add(hArrayItem, pClipboard_image);
					DataSize += mallocSize;
				}
			}
			else if (richEdit_itemType_gif == pItem->type)
			{
				pItemGif = (richEdit_item_gif_*)(pItem);
				wchar_t *pPath = XStr_GetBuffer(pItemGif->hString);

				buf_HTML_Text += L"<img src=";
				buf_HTML_Text += pPath;
				buf_HTML_Text += L" >";

				int mallocSize = XStr_GetLength(pItemGif->hString) + 1;
				mallocSize = mallocSize * 2;
				mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
				pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
				pClipboard_image->type = richEdit_itemType_gif;
				pClipboard_image->size = mallocSize;
				wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
				XArray_Add(hArrayItem, pClipboard_image);
				DataSize += mallocSize;
			}
		}
		buf_Text += L"\r\n";
		buf_HTML_Text += L"<br>";

		pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
		pClipboard_char->type = richEdit_itemType_char;
		pClipboard_char->bColor = FALSE;
		pClipboard_char->color = 0;
		pClipboard_char->ch = L'\n';
		pClipboard_char->fontIndex = -1;
		XArray_Add(hArrayItem, pClipboard_char);
		DataSize += sizeof(richEdit_clipboard_char_);
	}

	//结束行
	pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, endRow);
	for (int i = 0; i < endColumn; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (richEdit_itemType_char == pItem->type)
		{
			pItemChar = (richEdit_item_char_*)pItem;
			buf_Text += pItemChar->ch;
			buf_HTML_Text += pItemChar->ch;

			pClipboard_char = (richEdit_clipboard_char_*)malloc(sizeof(richEdit_clipboard_char_));
			pClipboard_char->type = richEdit_itemType_char;
			pClipboard_char->bColor = pItemChar->bColor;
			pClipboard_char->color = pItemChar->color;
			pClipboard_char->ch = pItemChar->ch;
			if (pItemChar->pFontInfo)
				pClipboard_char->fontIndex = pItemChar->pFontInfo->index;
			else
				pClipboard_char->fontIndex = -1;
			XArray_Add(hArrayItem, pClipboard_char);
			DataSize += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == pItem->type)
		{
			pItemImage = (richEdit_item_iamge_*)pItem;
			if (pItemImage->hString)
			{
				wchar_t *pPath = XStr_GetBuffer(pItemImage->hString);
				buf_HTML_Text += L"<img src=";
				buf_HTML_Text += pPath;
				buf_HTML_Text += L" >";

				int mallocSize = XStr_GetLength(pItemImage->hString) + 1;
				mallocSize = mallocSize * 2;
				mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
				pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
				pClipboard_image->type = richEdit_itemType_image;
				pClipboard_image->size = mallocSize;
				wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
				XArray_Add(hArrayItem, pClipboard_image);
				DataSize += mallocSize;
			}
		}
		else if (richEdit_itemType_gif == pItem->type)
		{
			pItemGif = (richEdit_item_gif_*)(pItem);
			wchar_t *pPath = XStr_GetBuffer(pItemGif->hString);

			buf_HTML_Text += L"<img src=";
			buf_HTML_Text += pPath;
			buf_HTML_Text += L" >";

			int mallocSize = XStr_GetLength(pItemGif->hString) + 1;
			mallocSize = mallocSize * 2;
			mallocSize += (sizeof(richEdit_clipboard_iamge_) - sizeof(int));
			pClipboard_image = (richEdit_clipboard_iamge_*)malloc(mallocSize);
			pClipboard_image->type = richEdit_itemType_gif;
			pClipboard_image->size = mallocSize;
			wcscpy((wchar_t*)&pClipboard_image->chs, pPath);
			XArray_Add(hArrayItem, pClipboard_image);
			DataSize += mallocSize;
		}
	}

	int hArrayCount = XArray_GetCount(hArrayItem);
	if (hArrayCount < 1)
	{
		XArray_Destroy(hArrayItem);
		return FALSE;
	}

	if (OpenClipboard(((ele_*)hEle)->pWindow->hWnd))
	{
		EmptyClipboard();
		RichEdit_Clipboard_Copy_Text((wchar_t*)buf_Text.c_str(), buf_Text.size());
		RichEdit_Clipboard_Copy_HTMLFormat((wchar_t*)buf_HTML_Text.c_str(), buf_HTML_Text.size());
		RichEdit_Clipboard_Copy_Data(hEle, hArrayItem, DataSize);
		CloseClipboard();
	}

	for (int i = 0; i < hArrayCount; i++)
	{
		void *pData = XArray_GetAt(hArrayItem, i);
		free(pData);
	}
	XArray_Destroy(hArrayItem);
	return TRUE;
}

/// @brief 粘贴,将剪切板中的文本插入当前光标位置.
/// @param hEle    元素句柄.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XRichEdit_Menu_Paste(HELE hEle)      //粘贴  将剪切板中的文本插入当前光标位置
{
	IsRichEditDebug(hEle, __FUNCTION__);
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bDrawSelect)
		RichEdit_DeleteSelect(hEle);

	if (NULL == OpenClipboard(((ele_*)hEle)->pWindow->hWnd))
		return FALSE;

	BOOL bResult = FALSE;
	if (RichEdit_Clipboard_Paste_Data(hEle))
	{
		bResult = TRUE;
		XEle_RedrawEle(hEle);
	}
	else if (RichEdit_Clipboard_Paste_Text(hEle))
	{
		bResult = TRUE;
		XEle_RedrawEle(hEle);
	}
	CloseClipboard();
	return bResult;
}

void RichEdit_Clipboard_Copy_Text(wchar_t *pText, int charLen)
{
	int lengByte = (charLen + 1) * sizeof(wchar_t);

	HGLOBAL hClipText = GlobalAlloc(GMEM_MOVEABLE, lengByte + 1);
	wchar_t *pBufText = (wchar_t*)GlobalLock(hClipText);
	wcscpy(pBufText, pText);
	GlobalUnlock(hClipText);
	SetClipboardData(CF_UNICODETEXT, hClipText);
}

void RichEdit_Clipboard_Copy_Data(HELE hEle, HARRAY hArrayItem, int DataSize)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int  byteSize = 0; //内容总大小
	richEdit_clipboard_header_  clipboard_header;
	clipboard_header.color = XEle_GetTextColor(hEle);
	clipboard_header.fontCount = XArray_GetCount(pRichEdit->hArrayFont);
	clipboard_header.itemCount = 0;
	clipboard_header.size = 0;
	clipboard_header.name;
	wcscpy(clipboard_header.name, L"XCGUI_RichEdit");
	GetObject(XEle_GetFont(hEle), sizeof(LOGFONT), &clipboard_header.font);

	richEdit_font_Info_  *pFontInfo = NULL;

	byteSize = sizeof(richEdit_clipboard_header_);
	byteSize = byteSize + clipboard_header.fontCount * sizeof(LOGFONT);

	byteSize = byteSize + DataSize;
	clipboard_header.size = byteSize;
	clipboard_header.itemCount = XArray_GetCount(hArrayItem);

	//int cfid =RegisterClipboardFormat(L"XCGUI_RichEditFormat");
	HGLOBAL hClipData = GlobalAlloc(GMEM_MOVEABLE, byteSize);
	byte *pBuf = (byte*)GlobalLock(hClipData);

	//存储数据
	int sizeT = sizeof(richEdit_clipboard_header_);
	memcpy(pBuf, &clipboard_header, sizeT);
	pBuf += sizeT;

	for (int i = 0; i < clipboard_header.fontCount; i++)
	{
		pFontInfo = (richEdit_font_Info_*)XArray_GetAt(pRichEdit->hArrayFont, i);
		pFontInfo->info;
		memcpy(pBuf, &pFontInfo->info, sizeof(LOGFONT));
		pBuf += sizeof(LOGFONT);
	}

	int countItem = XArray_GetCount(hArrayItem);
	for (int i = 0; i < countItem; i++)
	{
		void *p = XArray_GetAt(hArrayItem, i);
		if (richEdit_itemType_char == *(rictEdit_ItemType_*)p)
		{
			memcpy(pBuf, p, sizeof(richEdit_clipboard_char_));
			pBuf += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == *(rictEdit_ItemType_*)p)
		{
			memcpy(pBuf, p, ((richEdit_clipboard_iamge_*)p)->size);
			pBuf += ((richEdit_clipboard_iamge_*)p)->size;
		}
		else if (richEdit_itemType_gif == *(rictEdit_ItemType_*)p)
		{
			memcpy(pBuf, p, ((richEdit_clipboard_iamge_*)p)->size);
			pBuf += ((richEdit_clipboard_iamge_*)p)->size;
		}
		else
		{
			XTRACE("richEdit 剪贴板复制数据错误\n");
			exit(0);
		}
	}

	GlobalUnlock(hClipData);
	SetClipboardData(g_clipbroad_RichEditFormat, hClipData);
}

void RichEdit_Clipboard_Copy_HTMLFormat(wchar_t *pText, int charLen)
{
	int UTF8_len = (charLen + 1) * 3;
	char *pBuf_UTF8 = (char*)malloc(UTF8_len);
	memset(pBuf_UTF8, 0, UTF8_len);
	int len_utf8 = XC_UnicodeToUTF8(pBuf_UTF8, UTF8_len, pText, charLen);

	char EndHTML[20] = { 0 };
	sprintf(EndHTML, "EndHTML:%08d\r\n", 171 + len_utf8);

	char EndFragment[23] = { 0 };
	sprintf(EndFragment, "EndFragment:%08d\r\n", 134 + len_utf8);

	std::string sendbuf;
	sendbuf = "Version:0.9\r\n";
	sendbuf += "StartHTML:00000097\r\n"; //ok
	//sendbuf+="EndHTML:00000336\r\n";   //?  171+buf
	sendbuf += EndHTML;
	sendbuf += "StartFragment:00000134\r\n"; //ok
	//sendbuf+="EndFragment:00000300\r\n";   //?
	sendbuf += EndFragment;
	sendbuf += "<html><body>\r\n";
	sendbuf += "<!--StartFragment -->\r\n";
	sendbuf += pBuf_UTF8;
	sendbuf += "\r\n<!--EndFragment -->\r\n";
	sendbuf += "</body></html>";

	free(pBuf_UTF8);

	int len = sendbuf.size() + 1;

	//int cfid =RegisterClipboardFormat(L"HTML Format");

	HGLOBAL hClip = GlobalAlloc(GMEM_MOVEABLE, len + 1);
	char *pBuf = (char*)GlobalLock(hClip);
	strcpy(pBuf, sendbuf.c_str());
	GlobalUnlock(hClip);
	SetClipboardData(g_clipborad_HTMLFormat, hClip);
}

BOOL RichEdit_Clipboard_Paste_Data(HELE hEle)
{
	HANDLE hClipboard = GetClipboardData(g_clipbroad_RichEditFormat);
	if (NULL == hClipboard) return FALSE;

	byte *pData = (byte*)GlobalLock(hClipboard);
	byte *pPosition = pData;

	if (NULL == pData)
	{
		GlobalUnlock(hClipboard);
		return FALSE;
	}

	richEdit_clipboard_header_  *pHeader = (richEdit_clipboard_header_*)pData;
	pPosition += sizeof(richEdit_clipboard_header_);

	//字体表
	HARRAY hArrayFont = XArray_Create();
	for (int i = 0; i < pHeader->fontCount; i++)
	{
		XArray_Add(hArrayFont, pPosition);
		pPosition += sizeof(LOGFONT);
	}

	int row = 0;
	int column = 0;
	LOGFONT *pFontInfo = NULL;;

	wchar_t  ch[2] = { 0 };
	richEdit_clipboard_char_   *pItemChar = NULL;
	richEdit_clipboard_iamge_  *pItemImage = NULL;
	for (int i = 0; i < pHeader->itemCount; i++)
	{
		XRichEdit_GetCurrentPos(hEle, &row, &column);
		if (richEdit_itemType_char == *(rictEdit_ItemType_*)pPosition)
		{
			pItemChar = (richEdit_clipboard_char_*)pPosition;
			ch[0] = pItemChar->ch;
			pFontInfo = NULL;
			if (pItemChar->fontIndex >= 0)
			{
				pFontInfo = (LOGFONT*)XArray_GetAt(hArrayFont, pItemChar->fontIndex);
			}
			XRichEdit_InsertTextEx(hEle, ch, row, column, pFontInfo, pItemChar->bColor, pItemChar->color);
			pPosition += sizeof(richEdit_clipboard_char_);
		}
		else if (richEdit_itemType_image == *(rictEdit_ItemType_*)pPosition)
		{
			pItemImage = (richEdit_clipboard_iamge_*)pPosition;
			HIMAGE hImage = XImage_LoadFile((wchar_t*)&pItemImage->chs);
			if (hImage)
				XRichEdit_InsertImage(hEle, hImage, (wchar_t*)&pItemImage->chs, row, column);
			pPosition += pItemImage->size;
		}
		else if (richEdit_itemType_gif == *(rictEdit_ItemType_*)pPosition)
		{
			pItemImage = (richEdit_clipboard_iamge_*)pPosition;
			XRichEdit_InsertImageGif(hEle, (wchar_t*)&pItemImage->chs, row, column);
			pPosition += pItemImage->size;
		}
		else
		{
			XTRACE("RichEdit 剪贴板粘贴错误 \n");
			exit(0);
		}
	}
	XArray_Destroy(hArrayFont);

	GlobalUnlock(hClipboard);
	return TRUE;
}

BOOL RichEdit_Clipboard_Paste_Text(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	HANDLE hGlb = GetClipboardData(CF_UNICODETEXT);
	if (NULL == hGlb) return FALSE;

	BOOL bResult = FALSE;
	wchar_t *pText = (wchar_t*)GlobalLock(hGlb);
	if (pText && wcslen(pText) > 0)
	{
		XRichEdit_InsertText(hEle, pText, pRichEdit->row, pRichEdit->column);
		bResult = TRUE;
	}

	GlobalUnlock(hGlb);

	return bResult;
}

BOOL CALLBACK RichEdit_OnEventChar(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam)
{
	if (hEle != hEventEle)
		return FALSE;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bReadOnly) return TRUE;

	if (pRichEdit->bDown) return TRUE;

	if (VK_TAB == wParam) return TRUE;  //TAB按键

	if (VK_ESCAPE == wParam) return TRUE;

	if (0x8000 & GetKeyState(VK_CONTROL))
	{
		if (1 == wParam)  //全选
		{
			//	XEdit_SelectAll(hEle);
		}
		else if (3 == wParam) //复制
		{
			XRichEdit_Menu_Copy(hEle);
		}
		else if (22 == wParam) //粘贴
		{
			XRichEdit_Menu_Paste(hEle);
		}
		return TRUE;
	}
	wchar_t ch = wParam;

	//XTRACEW(L"char=%c \n",wParam);

	if (VK_BACK == wParam)  //退格
	{
		RichEdit_CharBackspace(hEle);
		//	XTRACEW(L"wchar=退格 \n",ch);
	}
	else if (VK_RETURN == wParam) //回车换行
	{
		//	if(pEdit->bMoreLine)

		RichEdit_CharEnter(hEle);

		//	XTRACEW(L"wchar=回车 \n");
	}
	else
	{
		RichEdit_Char(hEle, wParam);
		//	XTRACEW(L"wchar=%c \n",ch);
	}
	return TRUE;
}

BOOL CALLBACK RichEdit_OnEventKeyDown(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam)
{
	if (hEle != hEventEle)
		return FALSE;

	if (((richEdit_*)hEle)->bDown) return TRUE;

	if (VK_TAB == wParam) //TAB按键
	{
		if (((richEdit_*)hEle)->bReadOnly) return TRUE;

		RichEdit_Char(hEle, wParam);
		return TRUE;
	}

	//XTRACE("keydown %d",wParam);
	switch (wParam)
	{
	case 46:  //Delete
		RichEdit_CharDeleteKey(hEle);
		break;
	case 36:  //Home
		//	MoveCaretBegin();
		break;
	case 35:  //End
		//	MoveCaretEnd();
		break;
	case VK_LEFT: //37:  //左
		RichEidt_MouseCreatLeft(hEle); //移动插入符向左←
		break;
	case VK_UP: //38:  //上
		RichEidt_MouseCreatTop(hEle);
		break;
	case VK_RIGHT: //39:  //右
		RichEidt_MouseCreatRight(hEle);
		break;
	case VK_DOWN: //40:  //下
		RichEidt_MouseCreatBottom(hEle);
		break;
	}
	return TRUE;
}

BOOL CALLBACK RichEdit_OnEventSetFocus(HELE hEle, HELE hEventEle) //获得焦点
{
	if (hEle != hEventEle)
		return FALSE;

	//XTRACE("richEdit 获得焦点\n");
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (FALSE == pRichEdit->bCaretCreate)
	{
		RichEdit_CreateCaret(hEle);
		Wnd_DrawCaret(XEle_GetHWindow(hEle));
	}
	return TRUE;
}

BOOL CALLBACK RichEdit_OnEventKillFocus(HELE hEle, HELE hEventEle) //失去焦点
{
	if (hEle != hEventEle)
		return FALSE;
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	//XTRACE("richEdit 失去焦点\n");
	if (pRichEdit->bCaretCreate)
	{
		pRichEdit->bCaretCreate = FALSE;
		XWnd_DestroyCaret((HWINDOW)((ele_*)hEle)->pWindow);
		XEle_RedrawEle(hEle);
	}
	return TRUE;
}

BOOL CALLBACK RichEdit_OnEventSetFont(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	//字体改变,调整字符大小

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

	richEdit_line_ *pLine = NULL;
	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;
	int  lengthPixel = 0;
	int countItem = 0;
	int countLine = XArray_GetCount(pRichEdit->hArrayLine);
	for (int i = 0; i < countLine; i++)
	{
		lengthPixel = 0;
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				if (NULL == pItemChar->pFontInfo)
				{
					GetTextExtentPoint32(hdc, &pItemChar->ch, 1, &size);
					if (VK_TAB == pItemChar->ch)
						size.cx = size.cy * 2;
					lengthPixel += (size.cx - pItem->size.cx);
					pItem->size = size;
				}
			}
		}
		pLine->lenPixel += lengthPixel;
		RichEdit_Calculate_LineMaxHeight(hEle, i);
	}

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	//	RichEdit_Calculate_CaretPos(hEle);
	pRichEdit->bAdjustCalculate = TRUE;
	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;
	return FALSE;
}

void RichEdit_Char(HELE hEle, wchar_t ch) //字符
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect)
		RichEdit_DeleteSelect(hEle); //删除选择文本

	//字符长度
	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	GetTextExtentPoint32(hdc, &ch, 1, &size);
	if (VK_TAB == ch)
		size.cx = size.cy * 2;

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	richEdit_item_char_ *pItem = (richEdit_item_char_*)malloc(sizeof(richEdit_item_char_));
	pItem->item.type = richEdit_itemType_char;
	pItem->item.size = size;
	pItem->ch = ch;
	pItem->hFont = NULL;
	pItem->pFontInfo = NULL;
	pItem->bColor = FALSE;
	pItem->color = 0;

	//获取当前行
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	pItem->item.pLine = pLine;

	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (pRichEdit->column == countItem) //增加到末尾
	{
		XArray_Add(pLine->hArrayItem, pItem); //增加到行末尾
	}
	else
	{
		XArray_insert(pLine->hArrayItem, pItem, pRichEdit->column); //插入
	}

	pLine->lenPixel += size.cx;	//行长度增加

	pRichEdit->column++;	//当前列增加
	pRichEdit->caretPt.x += size.cx;

	if (size.cy > pLine->maxItemHeight)
		pLine->maxItemHeight = size.cy;


	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;

	//RichEdit_Adjust(hEle);
	//RichEdit_SetCaretPos(hEle);
	//RichEdit_ScrollH(hEle);
	XEle_RedrawEle(hEle);
}

void RichEdit_CharEnter(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect)
	{
		RichEdit_DeleteSelect(hEle); //删除选择文本
	}

	//获取当前行
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	int length = XArray_GetCount(pLine->hArrayItem); //当前行字符数

	if (length == pRichEdit->column)	//插入符后面没有内容
	{
		richEdit_line_ *pNewLine = (richEdit_line_*)malloc(sizeof(richEdit_line_));
		pNewLine->hArrayItem = XArray_Create();
		pNewLine->lenPixel = 0;
		pNewLine->maxItemHeight = pRichEdit->lineHeight;

		pRichEdit->column = 0;
		pRichEdit->row++;
		pRichEdit->rowCount++;
		XArray_insert(pRichEdit->hArrayLine, pNewLine, pRichEdit->row); //增加行到末尾

		//插入符
		pRichEdit->caretPt.x = 0;
		pRichEdit->caretPt.y += pLine->maxItemHeight;


	}
	else	//插入符后面有内容
	{
		richEdit_line_ *pNewLine = (richEdit_line_*)malloc(sizeof(richEdit_line_));
		pNewLine->hArrayItem = XArray_Create();
		pNewLine->lenPixel = 0;
		pNewLine->maxItemHeight = pRichEdit->lineHeight;

		int countItem = XArray_GetCount(pLine->hArrayItem);

		int count = countItem - pRichEdit->column;
		for (int i = pRichEdit->column; i < countItem; i++) //复制内容到下新行
		{
			richEdit_item_char_ *pItem = (richEdit_item_char_*)XArray_GetAt(pLine->hArrayItem, i);
			XArray_Add(pNewLine->hArrayItem, pItem);
			pLine->lenPixel -= pItem->item.size.cx;
			pNewLine->lenPixel += pItem->item.size.cx;
			pItem->item.pLine = pNewLine;
			if (pItem->item.size.cy > pNewLine->maxItemHeight)
			{
				pNewLine->maxItemHeight = pItem->item.size.cy;
			}
		}
		XArray_DeleteEnd(pLine->hArrayItem, pRichEdit->column);

		pRichEdit->column = 0;
		pRichEdit->row++;
		pRichEdit->rowCount++;

		XArray_insert(pRichEdit->hArrayLine, pNewLine, pRichEdit->row);

		//插入符
		pRichEdit->caretPt.x = 0;
		pRichEdit->caretPt.y += pNewLine->maxItemHeight;

	}
	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;

	//	RichEdit_Adjust(hEle);
	//	RichEdit_SetCaretPos(hEle);

		//检查是否需要滚动
	//	RichEdit_ScrollV(hEle);
	//	RichEdit_ScrollH(hEle);
	XEle_RedrawEle(hEle);
}

void RichEdit_CharBackspace(HELE hEle)  //退格
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect)
	{
		pRichEdit->bAdjust = RichEdit_DeleteSelect(hEle); //删除选择文本
		XEle_RedrawEle(hEle);
		return;
	}

	if (0 == pRichEdit->column && 0 == pRichEdit->row)
		return;

	//删除回车
	if (0 == pRichEdit->column)
	{
		RichEdit_CharBackspaceEnter(hEle);
	}
	else
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, pRichEdit->column - 1);

		pLine->lenPixel -= pItem->size.cx;

		XArray_DeleteIndex(pLine->hArrayItem, pRichEdit->column - 1);

		pRichEdit->caretPt.x -= pItem->size.cx;
		pRichEdit->column--;

		if (pItem->size.cy >= pLine->maxItemHeight)
		{
			pRichEdit->bAdjust = RichEdit_Calculate_LineMaxHeight(hEle, pRichEdit->row);
		}

		RichEdit_FreeItem(pItem);
		pItem = NULL;

		//将后面的元素位置向前移动
		int left = pRichEdit->caretPt.x;
		int countItem = XArray_GetCount(pLine->hArrayItem);
		for (int i = pRichEdit->column; i < countItem; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
			if (richEdit_itemType_ele == pItem->type)
			{
				richEdit_item_ele_ *pItemEle = (richEdit_item_ele_*)pItem;
				RECT rcEle;
				rcEle.left = left;
				rcEle.right = left + pItem->size.cx;
				rcEle.bottom = pRichEdit->caretPt.y + pLine->maxItemHeight;
				rcEle.top = rcEle.bottom - pItem->size.cy;
				XEle_SetRect(pItemEle->hEle, &rcEle);
			}
			left += pItem->size.cx;
		}

		pRichEdit->bAdjustCaret = TRUE;
		pRichEdit->bAdjust = TRUE;

		//	RichEdit_Adjust(hEle);
		//	RichEdit_SetCaretPos(hEle);
		//	RichEdit_ScrollH(hEle);

		XEle_RedrawEle(hEle);
	}
}

void RichEdit_CharBackspaceEnter(HELE hEle) //退格回车
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (0 == pRichEdit->row && 0 == pRichEdit->column)
	{
		return; //起始点
	}

	richEdit_line_ *pLineOld = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	int itemCount = XArray_GetCount(pLineOld->hArrayItem);

	if (0 == itemCount) //空行
	{
		XArray_DeleteIndex(pRichEdit->hArrayLine, pRichEdit->row);
		RichEdit_FreeLine(pLineOld);
		pRichEdit->row--;
		pRichEdit->rowCount--;

		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		pRichEdit->column = XArray_GetCount(pLine->hArrayItem);

		//插入符
		pRichEdit->caretPt.x = pLine->lenPixel;
		pRichEdit->caretPt.y -= pLine->maxItemHeight;
	}
	else //非空行
	{
		XArray_DeleteIndex(pRichEdit->hArrayLine, pRichEdit->row);
		pRichEdit->row--;
		pRichEdit->rowCount--;

		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		pRichEdit->column = XArray_GetCount(pLine->hArrayItem);

		//插入符
		pRichEdit->caretPt.x = pLine->lenPixel;
		pRichEdit->caretPt.y -= pLine->maxItemHeight;

		richEdit_item_ *pItem = NULL;
		for (int i = 0; i < itemCount; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineOld->hArrayItem, i);
			pItem->pLine = pLine;

			pLine->lenPixel += pItem->size.cx;

			if (pItem->size.cx > pLine->maxItemHeight)
			{
				pLine->maxItemHeight = pItem->size.cx;
			}
			XArray_Add(pLine->hArrayItem, pItem);
		}
		XArray_Destroy(pLineOld->hArrayItem);
		free(pLineOld);
	}
	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;

	//	RichEdit_Adjust(hEle);
	//	RichEdit_SetCaretPos(hEle);
	//	RichEdit_ScrollH(hEle);
	//	RichEdit_ScrollV(hEle);
	XEle_RedrawEle(hEle);
}

void RichEdit_CharDeleteKey(HELE hEle)   //删除键
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	int countLine = XArray_GetCount(pRichEdit->hArrayLine);

	//如果是空行
	if (countItem == pRichEdit->column)
	{
		if ((pRichEdit->rowCount - 1) == pRichEdit->row)
		{
			return;
		}
		if (0 == countItem)//删除
		{
			XArray_DeleteIndex(pRichEdit->hArrayLine, pRichEdit->row);
			RichEdit_FreeLine(pLine);
			pRichEdit->rowCount--;
		}
		else  //将下一行与当前行连接
		{
			richEdit_item_  *pItem = NULL;
			richEdit_line_  *pLineNext = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row + 1);
			int countItemT = XArray_GetCount(pLineNext->hArrayItem);
			for (int i = 0; i < countItemT; i++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLineNext->hArrayItem, i);
				XArray_Add(pLine->hArrayItem, pItem);
				pItem->pLine = pLine;
				pLine->lenPixel += pItem->size.cx;
			}
			XArray_DeleteIndex(pRichEdit->hArrayLine, pRichEdit->row + 1);
			XArray_Destroy(pLineNext->hArrayItem);
			free(pLineNext);
			pRichEdit->rowCount--;
		}
	}
	else
	{
		richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, pRichEdit->column);
		pLine->lenPixel -= pItem->size.cx;

		XArray_DeleteIndex(pLine->hArrayItem, pRichEdit->column);
		RichEdit_FreeItem(pItem);
	}

	RichEdit_Calculate_LineMaxHeight(hEle, pRichEdit->row);
	pRichEdit->bAdjustCaret = TRUE;
	pRichEdit->bAdjust = TRUE;

	//	RichEdit_Adjust(hEle);
	XEle_RedrawEle(hEle);
}

/// @brief 调整布局.
/// @param hEle  元素句柄.
/// @param startIndex  开始索引行.
void WINAPI XRichEdit_Adjust(HELE hEle, int startIndex) //调整
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	pRichEdit->bAdjust = FALSE;

	int  posY = pRichEdit->spacTop;
	int countLine = pRichEdit->rowCount;
	pRichEdit->visibleBegin = 0;
	pRichEdit->visibleEnd = 0;

	if (0 != startIndex)
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, startIndex);
		posY = pLine->top + pLine->maxItemHeight;
	}

	for (int i = startIndex; i < countLine; i++) //可视行开始
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		pLine->top = posY;
		posY += pLine->maxItemHeight;
	}
	RichEdit_Calculate_VisibleLine(hEle);

	//计算最长行
	int maxLine = 0;
	int maxLineLength = 0;
	for (int i = 0; i < countLine; i++)
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if (pLine->lenPixel > maxLineLength)
		{
			maxLineLength = pLine->lenPixel;
			maxLine = i;
		}
	}

	int cx = maxLineLength;
	richEdit_line_ *pLineEnd = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->rowCount - 1);
	int cy = pLineEnd->top + pLineEnd->maxItemHeight;

	XSView_SetSize(hEle, cx + 2, cy + 2);

	if (pRichEdit->bAdjustCaret)
	{
		RichEdit_ScrollH(hEle);
		RichEdit_ScrollV(hEle);
	}
	if (pRichEdit->bAdjustCalculate)
	{
		RichEdit_Calculate_CaretPos(hEle);
		pRichEdit->bAdjustCalculate = FALSE;
	}
	if (pRichEdit->bAdjustCaret)
	{
		RichEdit_SetCaretPos(hEle);
		pRichEdit->bAdjustCaret = FALSE;
	}
}

void RichEdit_Calculate_VisibleLine(HELE hEle) //计算可视行
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int ViewPos = XSView_GetVViewPos(hEle);
	int height = XSView_GetViewHeight(hEle);

	int countLine = pRichEdit->rowCount;
	int  i = 0;
	pRichEdit->visibleBegin = 0;
	pRichEdit->visibleEnd = 0;
	for (; i < countLine; i++) //可视行开始
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if ((pLine->top + pLine->maxItemHeight) >= (-ViewPos))
		{
			pRichEdit->visibleBegin = i;
			break;
		}
	}

	for (; i < countLine; i++) //可视行结束
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if ((pLine->top) > (-ViewPos + height))
		{
			pRichEdit->visibleEnd = i - 1;
			break;
		}
	}

	if (0 == pRichEdit->visibleEnd)
		pRichEdit->visibleEnd = countLine - 1;

	//	XTRACE("-----------可视行 begin=%d -----------------\n",pRichEdit->visibleBegin);
	//	XTRACE("-----------可视行 end=%d -----------------\n",pRichEdit->visibleEnd);
}

void RichEdit_ScrollH(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	HELE hView = XSView_GetView(hEle);

	RECT rcView;
	XEle_GetClientRect(hView, &rcView);

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);

	int posX = pRichEdit->caretPt.x + XSView_GetHViewPos(hEle);//+pLine->maxItemHeight;
	if (posX <= 0)
	{
		//XTRACE("向左滚动 \n");
		XSView_ScrollHPosX(hEle, pRichEdit->caretPt.x - 60);
	}
	else if (posX >= rcView.right)
	{
		//XTRACE("向右滚动 \n");
		XSView_ScrollHPosX(hEle, pRichEdit->caretPt.x - rcView.right + 60);
	}
}

void RichEdit_ScrollV(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	HELE hView = XSView_GetView(hEle);

	RECT rcView;
	XEle_GetClientRect(hView, &rcView);

	int posy = pRichEdit->caretPt.y + XSView_GetVViewPos(hEle);
	if (posy <= 0)
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		XSView_ScrollVPosY(hEle, pRichEdit->caretPt.y - pLine->maxItemHeight);
	}
	else
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		posy = posy + pLine->maxItemHeight;
		if (posy >= rcView.bottom)
		{
			XSView_ScrollVPosY(hEle, pRichEdit->caretPt.y + pLine->maxItemHeight - rcView.bottom + 1);
		}
	}
}

void RichEdit_SetCaretPos(HELE hEle)
{
	if (NULL == ((ele_*)hEle)->pWindow) //没有与窗口关联
		return;

	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int viewPosx = XSView_GetHViewPos(hEle);
	int viewPosy = XSView_GetVViewPos(hEle);

	int x = pRichEdit->caretPt.x + viewPosx + pRichEdit->spacLeft;
	int y = pRichEdit->caretPt.y + viewPosy + pRichEdit->spacTop;

	int caretHeight = 0;
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (0 == pRichEdit->column && 0 == countItem)
	{
		caretHeight = pLine->maxItemHeight;
	}
	else
	{
		int column = 0;
		if (pRichEdit->column > 0)
			column = pRichEdit->column - 1;
		richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, column);
		caretHeight = pItem->size.cy;
	}
	y = y + pLine->maxItemHeight; //行的下边界
	y = y - caretHeight;

	if (pRichEdit->bCaretCreate)
		XWnd_SetCaretPosEx((HWINDOW)((ele_*)hEle)->pWindow, x, y, 1, caretHeight);

}

void RichEdit_CreateCaret(HELE hEle)
{
	if (NULL == ((ele_*)hEle)->pWindow) //没有与窗口关联
		return;

	richEdit_ *pRichEdit = (richEdit_*)hEle;
	pRichEdit->bCaretCreate = TRUE;

	//插入符
	XWnd_CreateCaret((HWINDOW)((ele_*)hEle)->pWindow, ((scrollView_*)pRichEdit)->hView, 1, pRichEdit->caretHeight);

	XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow, TRUE);
	RichEdit_SetCaretPos(hEle);

	//XEle_RedrawEle(hEle);
}

//返回值:如果最大行高改变返回TRUE
BOOL RichEdit_Calculate_LineMaxHeight(HELE hEle, int row) //计算当前行最大高度值
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, row);

	richEdit_item_ *pItem = NULL;
	int maxHeight = pRichEdit->lineHeight;
	int countItem = XArray_GetCount(pLine->hArrayItem);
	for (int i = 0; i < countItem; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (pItem->size.cy > maxHeight)
		{
			maxHeight = pItem->size.cy;
		}
	}
	if (pLine->maxItemHeight != maxHeight)
	{
		pLine->maxItemHeight = maxHeight;
		return TRUE;
	}
	return FALSE;
}

BOOL RichEdit_Calculate_CaretPos(HELE hEle)  //计算插入符位置
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	richEdit_line_  *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	richEdit_item_  *pItem = NULL;
	int posX = 0;
	for (int i = 0; i < pRichEdit->column; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		posX += pItem->size.cx;
	}

	POINT pt = { pRichEdit->spacLeft + posX,pLine->top };
	pRichEdit->caretPt.x = pt.x;
	pRichEdit->caretPt.y = pt.y;

	return TRUE;
}

BOOL CALLBACK RichEdit_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE hRichEdit = XEle_GetParentEle(hEle);
	XEle_SetFocus(hRichEdit, TRUE);

	BOOL bRedraw = FALSE;

	if (RichEdit_TestDown(hRichEdit, pPt))
	{
		RichEdit_SetCaretPos(hRichEdit);
		bRedraw = TRUE;
	}

	richEdit_ *pRichEdit = (richEdit_*)hRichEdit;

	if (pRichEdit->bDrawSelect)
	{
		pRichEdit->bDrawSelect = FALSE;
		bRedraw = TRUE;
	}

	//文本选择
	pRichEdit->bDown = TRUE;
	pRichEdit->downRow = pRichEdit->row;
	pRichEdit->downColumn = pRichEdit->column;

	SetCursor(::LoadCursor(NULL, IDC_IBEAM));
	XEle_SetCapture(hEle);

	if (bRedraw)
		XEle_RedrawEle(hEle);

	return FALSE;
}

BOOL CALLBACK RichEdit_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE hRichEdit = XEle_GetParentEle(hEle);
	richEdit_ *pRichEdit = (richEdit_*)hRichEdit;
	if (pRichEdit->bDown)
	{
		pRichEdit->bDown = FALSE;
		XEle_ReleaseCapture(hEle);
	}
	SetCursor(::LoadCursor(NULL, IDC_IBEAM));
	return FALSE;
}

BOOL CALLBACK RichEdit_OnMouseMove_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE hRichEdit = XEle_GetParentEle(hEle);
	richEdit_ *pRichEdit = (richEdit_*)hRichEdit;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (pRichEdit->bDown)  //计算鼠标选择文本
	{
		if (pPt->x < rect.left)
		{
			XSView_ScrollLeftLine(hRichEdit);
			//XTRACE("edit 向左拖动滚动条 ←\n");
		}
		if (pPt->x > rect.right)
		{
			XSView_ScrollRightLine(hRichEdit);
			//XTRACE("edit 向右拖动滚动条 →\n");
		}
		if (pPt->y < rect.top)
		{
			XSView_ScrollTopLine(hRichEdit);
			//XTRACE("edit 向上拖动滚动条  ↑\n");
		}
		if (pPt->y > rect.bottom)
		{
			XSView_ScrollDownLine(hRichEdit);
			//XTRACE("edit 向下拖动滚动条  ↓\n");
		}

		int row = pRichEdit->row;
		int column = pRichEdit->column;

		if (RichEdit_TestDown(hRichEdit, pPt)) //位置改变
		{
			if (pRichEdit->downRow == pRichEdit->row  && pRichEdit->downColumn == pRichEdit->column)
			{
				pRichEdit->bDrawSelect = FALSE;
			}
			else
			{
				pRichEdit->bDrawSelect = TRUE;
			}
			pRichEdit->endRow = pRichEdit->row;
			pRichEdit->endColumn = pRichEdit->column;
			RichEdit_SetCaretPos(hRichEdit);

			XEle_RedrawEle(hEle); //绘制选择文本背景
		//	XTRACE("位置改变\n");
		}
		else
		{
			//	XTRACE("位置未改变 \n");
		}
	}
	else
	{
		SetCursor(::LoadCursor(NULL, IDC_IBEAM));
	}
	return FALSE;
}

BOOL RichEdit_TestDown(HELE hEle, POINT *pPt)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int posx = XSView_GetHViewPos(hEle);
	int posy = XSView_GetVViewPos(hEle);

	int downx = pPt->x - posx - pRichEdit->spacLeft;//-SCROLLVIEW(hEle)->left;
	int downy = pPt->y - posy - pRichEdit->spacTop;//-SCROLLVIEW(hEle)->top;

	int downLine = -1;
	int downLineY = -1;

	int downColumn = -1;
	int downLineX = -1;
	//计算点击的行
	int lineTop = 0;
	richEdit_line_ *pLine = NULL;
	int countLine = XArray_GetCount(pRichEdit->hArrayLine);
	for (int i = 0; i < countLine; i++)
	{
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if (downy >= lineTop && downy < (lineTop + pLine->maxItemHeight))
		{
			downLine = i;
			downLineY = lineTop;
			break;
		}
		lineTop += pLine->maxItemHeight;
	}

	//计算点击的列
	if (-1 == downLine) return FALSE;

	BOOL bResult = FALSE;
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (0 == countItem)
	{
		downColumn = 0;
		downLineX = 0;
		bResult = TRUE;
	}
	else
	{
		if (downx >= pLine->lenPixel)
		{
			downColumn = countItem;
			downLineX = pLine->lenPixel;
			bResult = TRUE;
		}
		else
		{
			int x = pLine->lenPixel;
			richEdit_item_ *pItem = NULL;
			for (int i = countItem - 1; i > -1; i--)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
				x -= pItem->size.cx;

				if (downx >= x)
				{
					downColumn = countItem - (countItem - i);
					downLineX = x;
					bResult = TRUE;
					break;
				}
			}
		}
	}

	if (bResult)
	{
		if (pRichEdit->row != downLine || pRichEdit->column != downColumn)
		{
			pRichEdit->row = downLine;
			pRichEdit->column = downColumn;
			pRichEdit->caretPt.x = downLineX;
			pRichEdit->caretPt.y = downLineY;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL RichEdit_GetItemRect(richEdit_item_ *pItem, RECT *pRect) //获取项坐标,如果不在绘制范围内,返回FALSE
{
	richEdit_line_ *pLine = pItem->pLine;
	richEdit_item_ *pItemT = NULL;
	int left = 0;
	int count = XArray_GetCount(pLine->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		pItemT = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (pItemT == pItem)
		{
			pRect->left = left;
			pRect->right = left + pItemT->size.cx;
			pRect->bottom = pLine->top + pLine->maxItemHeight;
			pRect->top = pRect->bottom - pItemT->size.cy;
			return TRUE;
		}
		left += pItemT->size.cx;
	}

	return FALSE;
}

BOOL RichEdit_GetItemRect2(HELE hEle, richEdit_item_ *pItem, RECT *pRect)
{
	int posX = XSView_GetHViewPos(hEle);
	int posY = XSView_GetVViewPos(hEle);

	richEdit_line_ *pLine = pItem->pLine;
	richEdit_item_ *pItemT = NULL;
	int left = 0;
	int count = XArray_GetCount(pLine->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		pItemT = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		if (pItemT == pItem)
		{
			pRect->left = left + posX;
			pRect->right = left + pItemT->size.cx + posX;
			pRect->bottom = pLine->top + pLine->maxItemHeight + posY;
			pRect->top = pRect->bottom - pItemT->size.cy + posY;
			return TRUE;
		}
		left += pItemT->size.cx;
	}

	return FALSE;
}

void RichEidt_MouseCreatLeft(HELE hEle) //移动插入符向左←
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bDrawSelect) //取消文本选择
	{
		pRichEdit->bDrawSelect = FALSE;
		XEle_RedrawEle(hEle);
	}

	if (0 == pRichEdit->column && 0 == pRichEdit->row)
		return;

	if (0 == pRichEdit->column) //移动到上一行
	{
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);

		pRichEdit->row--;
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		pRichEdit->column = XArray_GetCount(pLine->hArrayItem);

		pRichEdit->caretPt.x = pLine->lenPixel;
		pRichEdit->caretPt.y -= pLine->maxItemHeight;

		RichEdit_SetCaretPos(hEle);
		RichEdit_ScrollV(hEle);
		XEle_RedrawEle(hEle);
	}
	else //插入符前移一个字符
	{
		//当前行
		richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
		richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, pRichEdit->column - 1);

		pRichEdit->column--;
		pRichEdit->caretPt.x -= pItem->size.cx;

		RichEdit_SetCaretPos(hEle);
		RichEdit_ScrollH(hEle);
		Wnd_DrawCaret(XEle_GetHWindow(hEle));
	}
}

void RichEidt_MouseCreatRight(HELE hEle)  //移动插入符 向右 →
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect) //取消文本选择
	{
		pRichEdit->bDrawSelect = FALSE;
		XEle_RedrawEle(hEle);
	}

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	int countItem = XArray_GetCount(pLine->hArrayItem);
	if (pRichEdit->row == (pRichEdit->rowCount - 1) && pRichEdit->column == countItem)//如果插入符在末尾
	{
		return;
	}
	else if (pRichEdit->column == countItem) //换行
	{
		pRichEdit->caretPt.x = 0;
		pRichEdit->caretPt.y += pLine->maxItemHeight;
		pRichEdit->row++;
		pRichEdit->column = 0;

		RichEdit_SetCaretPos(hEle);
		RichEdit_ScrollV(hEle);
		Wnd_DrawCaret(XEle_GetHWindow(hEle));
	}
	else //当前行
	{
		richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, pRichEdit->column);

		pRichEdit->column++;
		pRichEdit->caretPt.x += pItem->size.cx;

		RichEdit_SetCaretPos(hEle);
		RichEdit_ScrollH(hEle);
		Wnd_DrawCaret(XEle_GetHWindow(hEle));
	}
}

void RichEidt_MouseCreatTop(HELE hEle)    //移动插入符 向上 ↑
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect) //取消文本选择
	{
		pRichEdit->bDrawSelect = FALSE;
		XEle_RedrawEle(hEle);
	}

	if (0 == pRichEdit->row)
		return;

	richEdit_line_ *pLineTop = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row - 1);

	if (pRichEdit->caretPt.x >= pLineTop->lenPixel) //插入符X位置比上一行大
	{
		pRichEdit->row--;
		pRichEdit->column = XArray_GetCount(pLineTop->hArrayItem);

		pRichEdit->caretPt.x = pLineTop->lenPixel;
		pRichEdit->caretPt.y -= pLineTop->maxItemHeight;

		RichEdit_SetCaretPos(hEle);
		RichEdit_ScrollH(hEle);
		RichEdit_ScrollV(hEle);
		Wnd_DrawCaret(XEle_GetHWindow(hEle));
	}
	else
	{
		pRichEdit->row--;
		pRichEdit->caretPt.y -= pLineTop->maxItemHeight;

		int countItem = XArray_GetCount(pLineTop->hArrayItem);
		int left = 0;
		richEdit_item_ *pItem = NULL;
		for (int i = 0; i < countItem; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineTop->hArrayItem, i);
			left += pItem->size.cx;
			if (pRichEdit->caretPt.x < left)
			{
				pRichEdit->column = i;
				pRichEdit->caretPt.x = left - pItem->size.cx;

				RichEdit_SetCaretPos(hEle);
				RichEdit_ScrollH(hEle);
				RichEdit_ScrollV(hEle);
				Wnd_DrawCaret(XEle_GetHWindow(hEle));
				return;
			}
		}
		XTRACE("移动插入符 向上 ↑ 错误 \n");
	}
}

void RichEidt_MouseCreatBottom(HELE hEle) //移动插入符 向下 ↓
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->bDrawSelect) //取消文本选择
	{
		pRichEdit->bDrawSelect = FALSE;
		XEle_RedrawEle(hEle);
	}

	if (pRichEdit->row == (pRichEdit->rowCount - 1))
		return;

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row);
	richEdit_line_ *pLineBottom = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->row + 1);

	if (pRichEdit->caretPt.x >= pLineBottom->lenPixel) //插入符X位置比下一行大
	{
		pRichEdit->row++;
		pRichEdit->column = XArray_GetCount(pLineBottom->hArrayItem);

		pRichEdit->caretPt.x = pLineBottom->lenPixel;
		pRichEdit->caretPt.y += pLine->maxItemHeight;

		RichEdit_SetCaretPos(hEle);
		RichEdit_ScrollH(hEle);
		RichEdit_ScrollV(hEle);
		Wnd_DrawCaret(XEle_GetHWindow(hEle));
	}
	else
	{
		pRichEdit->row++;
		pRichEdit->caretPt.y += pLine->maxItemHeight;

		int countItem = XArray_GetCount(pLineBottom->hArrayItem);
		int left = 0;
		richEdit_item_ *pItem = NULL;
		for (int i = 0; i < countItem; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineBottom->hArrayItem, i);
			left += pItem->size.cx;
			if (pRichEdit->caretPt.x < left)
			{
				pRichEdit->column = i;
				pRichEdit->caretPt.x = left - pItem->size.cx;

				RichEdit_SetCaretPos(hEle);
				RichEdit_ScrollH(hEle);
				RichEdit_ScrollV(hEle);
				Wnd_DrawCaret(XEle_GetHWindow(hEle));
				return;
			}
		}
		XTRACE("移动插入符 向下 ↓ 错误 \n");
	}
}

void RichEdit_FreeItem(richEdit_item_ *pItem)
{
	if (richEdit_itemType_char == pItem->type)
	{
	}
	else if (richEdit_itemType_ele == pItem->type)
	{
		richEdit_item_ele_ *pItemEle = (richEdit_item_ele_*)pItem;
		XEle_Destroy(pItemEle->hEle);
	}
	else if (richEdit_itemType_image == pItem->type)
	{
		richEdit_item_iamge_ *pItemImage = (richEdit_item_iamge_*)pItem;
		if (pItemImage->hString)
			XStr_Destroy(pItemImage->hString);
		XImage_Destroy(pItemImage->hImage);
	}
	else if (richEdit_itemType_gif == pItem->type)
	{
		richEdit_item_gif_ *pItemGif = (richEdit_item_gif_*)pItem;
		Animation_Remove_RichEdit(pItemGif);
		XStr_Destroy(pItemGif->hString);
		delete pItemGif->pGif;
	}
	free(pItem);
}

void RichEdit_FreeLine(richEdit_line_ *pLine)
{
	int countItem = XArray_GetCount(pLine->hArrayItem);
	richEdit_item_ *pItem = NULL;
	for (int i = 0; i < countItem; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		RichEdit_FreeItem(pItem);
	}
	XArray_Destroy(pLine->hArrayItem);
	free(pLine);
}

//return:有内容被删除返回TRUE,没有删除任何内容返回FALSE
BOOL RichEdit_DeleteSelect(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (FALSE == pRichEdit->bDrawSelect) return FALSE;

	pRichEdit->bDrawSelect = FALSE;

	if (pRichEdit->downRow == pRichEdit->endRow) //只有一行
	{
		return RichEdit_DeleteSelectSingleLine(hEle);
	}
	else if (pRichEdit->downRow < pRichEdit->endRow)  //向下选择
	{
		return RichEdit_DeleteSelectMultiLine(hEle,
			pRichEdit->downRow, pRichEdit->downColumn, pRichEdit->endRow, pRichEdit->endColumn, TRUE);
	}
	else  //向上选择
	{
		return RichEdit_DeleteSelectMultiLine(hEle,
			pRichEdit->endRow, pRichEdit->endColumn, pRichEdit->downRow, pRichEdit->downColumn, FALSE);
	}
	return TRUE;
}

//单行选择
BOOL RichEdit_DeleteSelectSingleLine(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;
	if (pRichEdit->downColumn == pRichEdit->endColumn) //没有选择
	{
		return FALSE;
	}

	int downColumn = 0;
	int endColumn = 0;
	BOOL bForward = FALSE;
	if (pRichEdit->downColumn < pRichEdit->endColumn) //向后选择
	{
		downColumn = pRichEdit->downColumn;
		endColumn = pRichEdit->endColumn;
		bForward = TRUE;
	}
	else //向前选择
	{
		downColumn = pRichEdit->endColumn;
		endColumn = pRichEdit->downColumn;
		bForward = FALSE;
	}

	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, pRichEdit->downRow);

	int lengPixel = 0;
	int countItem = XArray_GetCount(pLine->hArrayItem);
	for (int i = downColumn; i < endColumn; i++)
	{
		richEdit_item_ *pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
		lengPixel += pItem->size.cx;
		RichEdit_FreeItem(pItem);
	}
	XArray_DeleteRange(pLine->hArrayItem, downColumn, endColumn - 1);

	pLine->lenPixel -= lengPixel;
	if (bForward)
	{
		pRichEdit->column = downColumn;
		pRichEdit->caretPt.x -= lengPixel;
	}

	BOOL bChange = RichEdit_Calculate_LineMaxHeight(hEle, pRichEdit->downRow);

	if (bForward || bChange)
		RichEdit_SetCaretPos(hEle);

	return TRUE;
}

//多行选择
BOOL RichEdit_DeleteSelectMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, BOOL bForward)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	//删除中间行
	int countLine = endRow - beginRow - 1;
	if (countLine > 0)
	{
		for (int i = 0; i < countLine; i++)
		{
			richEdit_line_ *pLineT = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + 1 + i);
			richEdit_item_ *pItemT = NULL;
			int countItem = XArray_GetCount(pLineT->hArrayItem);
			for (int t = 0; t < countItem; t++)
			{
				pItemT = (richEdit_item_*)XArray_GetAt(pLineT->hArrayItem, t);
				RichEdit_FreeItem(pItemT);
			}
			if (bForward)
				pRichEdit->caretPt.y -= pLineT->maxItemHeight;
			XArray_Destroy(pLineT->hArrayItem);
			free(pLineT);
		}
		XArray_DeleteRange(pRichEdit->hArrayLine, beginRow + 1, endRow - 1);
		pRichEdit->rowCount -= countLine;
	}

	//处理开始行和结束行
	//开始行
	richEdit_line_ *pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow);
	{
		int lengPixel = 0;
		int countItem = XArray_GetCount(pLine->hArrayItem);
		richEdit_item_ *pItem = NULL;
		for (int i = beginColumn; i < countItem; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, i);
			lengPixel += pItem->size.cx;
			RichEdit_FreeItem(pItem);
		}
		XArray_DeleteEnd(pLine->hArrayItem, beginColumn);
		pLine->lenPixel -= lengPixel;
	}

	//结束行
	richEdit_line_ *pLineEnd = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, beginRow + 1);
	{
		richEdit_item_ *pItem = NULL;
		int lengPixel = 0;
		for (int i = 0; i < endColumn; i++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLineEnd->hArrayItem, i);
			lengPixel += pItem->size.cx;
			RichEdit_FreeItem(pItem);
		}
		XArray_DeleteRange(pLineEnd->hArrayItem, 0, endColumn - 1);
		pLineEnd->lenPixel -= lengPixel;
	}

	//连接内容
	pLine->hArrayItem;
	int countItem = XArray_GetCount(pLineEnd->hArrayItem);
	richEdit_item_ *pItem = NULL;
	for (int i = 0; i < countItem; i++)
	{
		pItem = (richEdit_item_*)XArray_GetAt(pLineEnd->hArrayItem, i);
		XArray_Add(pLine->hArrayItem, pItem);
	}

	int count22 = XArray_GetCount(pLine->hArrayItem);

	if (bForward)
	{
		pRichEdit->row = beginRow;
		pRichEdit->column = beginColumn;
		pRichEdit->caretPt.x = pLine->lenPixel;
		pRichEdit->caretPt.y -= pLine->maxItemHeight;
	}

	pLine->lenPixel += pLineEnd->lenPixel;

	XArray_Destroy(pLineEnd->hArrayItem);
	XArray_DeleteIndex(pRichEdit->hArrayLine, beginRow + 1);
	free(pLineEnd);

	pRichEdit->rowCount--;

	pRichEdit->bAdjust = TRUE;
	BOOL bChange = RichEdit_Calculate_LineMaxHeight(hEle, beginRow);

	if (bForward || bChange)
		RichEdit_SetCaretPos(hEle);

	return TRUE;
}

BOOL CALLBACK RichEdit_OnEventHScrollView(HELE hEle, HELE hEventEle, int pos)
{
	if (hEle != hEventEle)
		return FALSE;

	RichEdit_Calculate_VisibleLine(hEle);
	if (((richEdit_*)hEle)->bCaretCreate)
	{
		RichEdit_SetCaretPos(hEle);
		//XTRACE("x=%d,y=%d \n",XSView_GetHViewPos(hEle),XSView_GetVViewPos(hEle));
	}
	return FALSE;
}

BOOL CALLBACK RichEdit_OnEventVScrollView(HELE hEle, HELE hEventEle, int pos)
{
	if (hEle != hEventEle)
		return FALSE;

	RichEdit_Calculate_VisibleLine(hEle);
	//调整插入符位置, 超出范围隐藏
	if (((richEdit_*)hEle)->bCaretCreate)
	{
		RichEdit_SetCaretPos(hEle);
		//XTRACE("x=%d,y=%d \n",XSView_GetHViewPos(hEle),XSView_GetVViewPos(hEle));
	}
	return FALSE;
}

BOOL CALLBACK RichEdit_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	if (pRichEdit->bAdjust)
	{
		XRichEdit_Adjust(hEle, 0);
	}

	if (pRichEdit->bDrawSelect)
		XTRACE("绘制 行=%d 列=%d  总行数=%d 选择-------\n", pRichEdit->row, pRichEdit->column, pRichEdit->rowCount);
	else
		XTRACE("绘制 行=%d 列=%d  总行数=%d 未选择-------\n", pRichEdit->row, pRichEdit->column, pRichEdit->rowCount);

	//获取开始行
	//获取结束行

	//检查选择内容
	int beginRow = 0;
	int beginColumn = 0;
	int endRow = 0;
	int endColumn = 0;
	if (pRichEdit->bDrawSelect)
	{
		if (pRichEdit->downRow == pRichEdit->endRow) //一行
		{
			if (pRichEdit->downColumn < pRichEdit->endColumn)
			{
				beginRow = pRichEdit->downRow;
				beginColumn = pRichEdit->downColumn;
				endRow = pRichEdit->endRow;
				endColumn = pRichEdit->endColumn;
			}
			else if (pRichEdit->downColumn == pRichEdit->endColumn)
			{
				XTRACE("选择内容错误,没有选择内容  \n");
			}
			else
			{
				beginRow = pRichEdit->endRow;
				beginColumn = pRichEdit->endColumn;
				endRow = pRichEdit->downRow;
				endColumn = pRichEdit->downColumn;
			}
		}
		else if (pRichEdit->downRow < pRichEdit->endRow) //多行 向下拖动
		{
			beginRow = pRichEdit->downRow;
			beginColumn = pRichEdit->downColumn;
			endRow = pRichEdit->endRow;
			endColumn = pRichEdit->endColumn;
		}
		else if (pRichEdit->downRow > pRichEdit->endRow) //多行 向上拖动
		{
			beginRow = pRichEdit->endRow;
			beginColumn = pRichEdit->endColumn;
			endRow = pRichEdit->downRow;
			endColumn = pRichEdit->downColumn;
		}
	}

	int countLine = pRichEdit->rowCount;
	HDC hDC = XDraw_GetHDC_(hDraw);
	int posX = 0;
	int posY = 0;
	XDraw_GetOffset_(hDraw, &posX, &posY);

	richEdit_line_ *pLine = NULL;
	richEdit_item_ *pItem = NULL;
	richEdit_item_char_ *pItemChar = NULL;
	richEdit_item_ele_  *pItemEle = NULL;
	richEdit_item_iamge_  *pItemImage = NULL;
	richEdit_item_gif_    *pItemGif = NULL;
	int bottom = 0;
	HFONT hFont = XFont_GetHFONT(((ele_*)hEle)->hFontX);
	COLORREF color = GetTextColor(hDC);

	//SelectObject(hDC,hFont);

	if (pRichEdit->bDrawSelect)
		RichEdit_DrawSelectBG(hEle, hDraw);

	for (int i = pRichEdit->visibleBegin; i <= pRichEdit->visibleEnd; i++)
	{
		int left = pRichEdit->spacLeft;

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);

		bottom = pLine->top + pLine->maxItemHeight; //行下边界;

		int countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);

			if (richEdit_itemType_char == pItem->type)
			{
				pItemChar = (richEdit_item_char_*)pItem;
				if (pItemChar->bColor)
					SetTextColor(hDC, pItemChar->color);
				//	if(pItemChar->hFont)
				if (pItemChar->pFontInfo)
				{
					SelectObject(hDC, pItemChar->pFontInfo->hFont);
					XDraw_TextOut_(hDraw, left, bottom - pItem->size.cy, &pItemChar->ch, 1);
					SelectObject(hDC, hFont);
				}
				else
				{
					XDraw_TextOut_(hDraw, left, bottom - pItem->size.cy, &pItemChar->ch, 1);
				}
				if (pItemChar->bColor)
					SetTextColor(hDC, color);
			}
			else if (richEdit_itemType_ele == pItem->type)
			{
				//pItemEle=(richEdit_item_ele_*)pItem;
			}
			else if (richEdit_itemType_image == pItem->type)
			{
				pItemImage = (richEdit_item_iamge_*)pItem;
				XDraw_HImage_(hDraw, pItemImage->hImage, left, pLine->top + pLine->maxItemHeight - pItem->size.cy);
			}
			else if (richEdit_itemType_gif == pItem->type)
			{
				pItemGif = (richEdit_item_gif_*)pItem;
				pItemGif->ms = pItemGif->pGif->DrawFrameGIF2(hDC, left + posX, pLine->top + posY + pLine->maxItemHeight - pItem->size.cy);
			}
			left += pItem->size.cx;
		}
	}
	return TRUE;
}

void RichEdit_DrawSelectBG(HELE hEle, HDRAW hDraw)  //绘制选择内容背景
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	//检查选择内容
	int beginRow = 0;
	int beginColumn = 0;
	int endRow = 0;
	int endColumn = 0;
	if (pRichEdit->bDrawSelect)
	{
		if (pRichEdit->downRow == pRichEdit->endRow) //一行
		{
			if (pRichEdit->downColumn < pRichEdit->endColumn)
			{
				beginRow = pRichEdit->downRow;
				beginColumn = pRichEdit->downColumn;
				endRow = pRichEdit->endRow;
				endColumn = pRichEdit->endColumn;
			}
			else if (pRichEdit->downColumn == pRichEdit->endColumn)
			{
				XTRACE("选择内容错误,没有选择内容  \n");
			}
			else
			{
				beginRow = pRichEdit->endRow;
				beginColumn = pRichEdit->endColumn;
				endRow = pRichEdit->downRow;
				endColumn = pRichEdit->downColumn;
			}
		}
		else if (pRichEdit->downRow < pRichEdit->endRow) //多行 向下拖动
		{
			beginRow = pRichEdit->downRow;
			beginColumn = pRichEdit->downColumn;
			endRow = pRichEdit->endRow;
			endColumn = pRichEdit->endColumn;
		}
		else if (pRichEdit->downRow > pRichEdit->endRow) //多行 向上拖动
		{
			beginRow = pRichEdit->endRow;
			beginColumn = pRichEdit->endColumn;
			endRow = pRichEdit->downRow;
			endColumn = pRichEdit->downColumn;
		}
	}

	int i = 0;
	int end = 0;
	if (beginRow > pRichEdit->visibleBegin)
	{
		i = beginRow;
	}
	else
	{
		i = pRichEdit->visibleBegin;
	}

	if (endRow < pRichEdit->visibleEnd)
	{
		end = endRow;
	}
	else
	{
		end = pRichEdit->visibleEnd;
	}

	if (i > end)
		return;

	richEdit_line_ *pLine = NULL;
	richEdit_item_ *pItem = NULL;
	RECT  rcBK;
	int bottom = 0;

	//单行
	if (beginRow == endRow)
	{
		HBRUSH hBrush = NULL;
		if (pRichEdit->bCaretCreate)
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(83, 132, 213));
		else
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(174, 198, 236));

		int left = pRichEdit->spacLeft;

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if (pLine != NULL)
		{
			bottom = pLine->top + pLine->maxItemHeight; //行下边界;
			for (int j = 0; j < beginColumn; j++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
				if (pItem == NULL)
					continue;
				left += pItem->size.cx;
			}

			for (int j = beginColumn; j < endColumn; j++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
				if (pItem == NULL)
					continue;

				rcBK.left = left;
				rcBK.right = left + pItem->size.cx;
				rcBK.top = pLine->top;
				rcBK.bottom = bottom;
				XDraw_FillRect_(hDraw, &rcBK, hBrush);
				left += pItem->size.cx;
			}
		}
		DeleteObject(hBrush);
		return;
	}

	///////////多行//////////////////////////////////////////////
	HBRUSH hBrush = NULL;
	if (pRichEdit->bCaretCreate)
		hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(83, 132, 213));
	else
		hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(174, 198, 236));

	//开始行
	if (i == beginRow)
	{
		int left = pRichEdit->spacLeft;

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if (pLine != NULL)
		{
			bottom = pLine->top + pLine->maxItemHeight; //行下边界;
			int countItem = XArray_GetCount(pLine->hArrayItem);
			for (int j = 0; j < beginColumn; j++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
				left += pItem->size.cx;
			}

			for (int j = beginColumn; j < countItem; j++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);

				rcBK.left = left;
				rcBK.right = left + pItem->size.cx;
				rcBK.top = pLine->top;
				rcBK.bottom = bottom;
				XDraw_FillRect_(hDraw, &rcBK, hBrush);
				left += pItem->size.cx;
			}
		}
		i++;
	}
	//中间行
	for (; i <= end; i++)
	{
		if (i == endRow)
			break;

		int left = pRichEdit->spacLeft;
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if (pLine != NULL)
		{
			bottom = pLine->top + pLine->maxItemHeight; //行下边界;
			int countItem = XArray_GetCount(pLine->hArrayItem);
			for (int j = 0; j < countItem; j++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);

				rcBK.left = left;
				rcBK.right = left + pItem->size.cx;
				rcBK.top = pLine->top;
				rcBK.bottom = bottom;
				XDraw_FillRect_(hDraw, &rcBK, hBrush);
				left += pItem->size.cx;
			}
		}
	}
	//结束行
	if (i == endRow)
	{
		int left = pRichEdit->spacLeft;

		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		if (pLine != NULL)
		{
			bottom = pLine->top + pLine->maxItemHeight; //行下边界;

			for (int j = 0; j < endColumn; j++)
			{
				pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);

				rcBK.left = left;
				rcBK.right = left + pItem->size.cx;
				rcBK.top = pLine->top;
				rcBK.bottom = bottom;
				XDraw_FillRect_(hDraw, &rcBK, hBrush);
				left += pItem->size.cx;
			}
		}
	}
	DeleteObject(hBrush);
}

void CALLBACK RichEdit_OnEventDestroy(HELE hEle)
{
	richEdit_ *pRichEdit = (richEdit_*)hEle;

	int countLine = XArray_GetCount(pRichEdit->hArrayLine);

	richEdit_line_  *pLine = NULL;
	richEdit_item_  *pItem = NULL;
	for (int i = 0; i < countLine; i++)
	{
		pLine = (richEdit_line_*)XArray_GetAt(pRichEdit->hArrayLine, i);
		int countItem = XArray_GetCount(pLine->hArrayItem);
		for (int j = 0; j < countItem; j++)
		{
			pItem = (richEdit_item_*)XArray_GetAt(pLine->hArrayItem, j);
			RichEdit_FreeItem(pItem);
		}
		XArray_Destroy(pLine->hArrayItem);
		free(pLine);
	}
	XArray_Destroy(pRichEdit->hArrayLine);
	///////////////////////////////////////////////////////////////
	richEdit_font_Info_  *pFontInfo = NULL;
	int countFont = XArray_GetCount(pRichEdit->hArrayFont);
	for (int i = 0; i < countFont; i++)
	{
		pFontInfo = (richEdit_font_Info_*)XArray_GetAt(pRichEdit->hArrayFont, i);
		DeleteObject(pFontInfo->hFont);
		free(pFontInfo);
	}
	XArray_Destroy(pRichEdit->hArrayFont);
}


/// @}
