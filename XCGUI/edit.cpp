/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"
#include "edit.h"

/// @defgroup edit 编辑框(Edit)
/// @ingroup groupElements
/// @{

/// @brief 创建编辑框元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XEdit_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	edit_ *pEdit = (edit_*)malloc(sizeof(edit_));
	if (pEdit)
	{
		memset(pEdit, 0, sizeof(edit_));
		Edit_Init((HELE)pEdit, x, y, cx, cy, XC_EDIT, hParent);
	}
	return (HELE)pEdit;
}

void Edit_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_EDIT);

	edit_  *pEdit = EDIT(hEle);
	pEdit->spacLeft = 3;
	pEdit->spacTop = 3;
	pEdit->hArrayEdit = XArray_Create();
	pEdit->bNumber = FALSE;
	pEdit->bMenu = TRUE;
	pEdit->caretWidth = 1;
	pEdit->selColor = RGB(83, 132, 213);

	HDC hdc = GetDC(NULL);
	HGDIOBJ hOld = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	EDIT(hEle)->rowHeight = tm.tmHeight; //行高

	SIZE size;
	GetTextExtentPoint32W(hdc, L"*", 1, &size);
	EDIT(hEle)->sizePass.cx = size.cx;
	EDIT(hEle)->sizePass.cy = size.cy;

	SelectObject(hdc, hOld);
	ReleaseDC(NULL, hdc);

	editStrList_  *pList = (editStrList_*)malloc(sizeof(editStrList_));
	memset(pList, 0, sizeof(editStrList_));

	pList->hString = XStr_Create();
	XArray_Add(pEdit->hArrayEdit, pList);

	SCROLLVIEW(hEle)->sizeLine.cy = tm.tmHeight;
	SCROLLVIEW(hEle)->sizeLine.cx = tm.tmMaxCharWidth;

	if (cy < EDIT(hEle)->rowHeight * 3)  //隐藏滚动条
	{
		XSView_EnableHScroll(hEle, FALSE);
		XSView_EnableVScroll(hEle, FALSE);
	}

	HELE hView = ((scrollView_*)hEle)->hView;
	XEle_RegisterMessage(hView, XM_LBUTTONDOWN, Edit_OnLButtonDown_View);
	XEle_RegisterMessage(hView, XM_LBUTTONUP, Edit_OnLButtonUp_View);
	XEle_RegisterMessage(hView, XM_MOUSEMOVE, Edit_OnMouseMove_View);
	XEle_RegisterMessage(hView, XM_RBUTTONDOWN, Edit_OnRButtonDown_View);
	XEle_RegisterMessage(hView, XM_RBUTTONUP, Edit_OnRButtonUp_View);

	XSView_SetDrawScrollView(hEle, Edit_OnDrawScrollView);

	XEle_RegisterMessage(hEle, XM_PAINT, Edit_OnDraw);

	XEle_RegisterEvent(hEle, XE_HSCROLLVIEW, Edit_OnEventHScrollView);
	XEle_RegisterEvent(hEle, XE_VSCROLLVIEW, Edit_OnEventVScrollView);
	XEle_RegisterEvent(hEle, XE_SETFOCUS, Edit_OnEventSetFocus);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, Edit_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_CHAR, Edit_OnEventChar);
	XEle_RegisterEvent(hEle, XE_KEYDOWN, Edit_OnEventKeyDown);
	XEle_RegisterEvent(hEle, XE_MENUSELECT, Edit_OnEventMenuSelect);
	XEle_RegisterEvent(hEle, XE_DESTROY, Edit_OnDestroy);
	XEle_RegisterEvent(hEle, XE_SIZE, Edit_OnEventSize);
	XEle_RegisterEvent(hEle, XE_SETFONT, Edit_OnEventSetFont);

	XEle_RegisterEvent(hEle, XE_MOUSESTAY, Edit_OnEventMouseStay);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, Edit_OnEventMouseLeave);
}

void CALLBACK Edit_OnDestroy(HELE hEle)  //销毁
{
	int count = XArray_GetCount(EDIT(hEle)->hArrayEdit);
	editStrList_ *pObj = NULL;
	for (int i = 0; i < count; i++)
	{
		pObj = Array_GetAtEdit(EDIT(hEle)->hArrayEdit, i);
		if (pObj->hString)
			XStr_Destroy(pObj->hString);
		free(pObj);
	}
	XArray_Destroy(EDIT(hEle)->hArrayEdit);

	if (EDIT(hEle)->hImage_stay) XImage_Destroy(EDIT(hEle)->hImage_stay);
}

/// @brief 启用编辑框元素多行输入功能.
/// @param hEle  元素句柄.
/// @param b    TRUE支持多行输入,否则相反.
void WINAPI XEdit_EnableMultiLine(HELE hEle, BOOL b) //启用多行输入
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->bMoreLine = b;
}

/// @brief 启用只接收数字功能.
/// @param hEle  元素句柄.
/// @param bNumber  如果值为TRUE只能接收数字,否则相反.
void WINAPI XEdit_EnableNumber(HELE hEle, BOOL bNumber) //只能输入数字
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->bNumber = bNumber;
}

/// @brief 编辑框元素启用输入密码功能,密码只能单行输入.
/// @param hEle  元素句柄.
/// @param bPass  TRUE为密码框,否则相反.
void WINAPI XEdit_EnablePassBox(HELE hEle, BOOL bPass)   //启用密码框
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->bPass = bPass;
}

/// @brief 编辑框启用或关闭鼠标右键弹出菜单.
/// @param hEle  元素句柄.
/// @param bEnable  值为TRUE启用,否则相反.
void WINAPI XEdit_EnablePopupMenu(HELE hEle, BOOL bEnable)  //启用鼠标右键菜单
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->bMenu = bEnable;
}

/// @brief 删除选择的文本,当只读属性时,也可以删除文本.
/// @param hEle  元素句柄.
void WINAPI XEdit_DeleteSelectText(HELE hEle)      //删除选择文本
{
	IsEditDebug(hEle, __FUNCTION__);

	if (Edit_DeleteSelectText(hEle))
		Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
}

//检查字符串是否为数字
BOOL Edit_SetText_ExamineStringNumber(HELE hEle, wchar_t *pText)
{
	edit_ *pEdit = EDIT(hEle);

	if (pEdit->bNumber) //数字
	{
		wchar_t *pCeck = pText;
		while (pCeck)
		{
			if (0 == *pCeck)
				break;

			if ((L'\r' != *pCeck) && (L'\n' != *pCeck))
			{
				if (*pCeck < 48 || *pCeck>57)
				{
					XTRACE("edit 不能接收字符\n");
					return FALSE;
				}
			}
			pCeck++;
		}
	}
	return TRUE;
}

//单行模式
void Edit_SetText_SingleLine(HELE hEle, wchar_t *pText)
{
	edit_ *pEdit = EDIT(hEle);

	wchar_t *pWChar = pText;
	int len = 0;
	while (1)
	{
		if (VK_TAB == *pWChar)//把TAB替换成空格
			*pWChar = L' ';
		if (L'\n' == *pWChar) //遇到换行截断
		{
			len = pWChar - pText;
			if (L'\r' == *(pWChar - 1))
			{
				len--;
			}
			break;
		}
		else if (0 == *pWChar)
		{
			len = pWChar - pText;
			break;
		}
		pWChar++;
	}
	if (len > 0)
	{
		pEdit->row = 0;
		pEdit->rows = 0;

		editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row);
		XStr_AddStringLength(pST->hString, pText, len);

		if (pEdit->bPass) //密码框
		{
			pST->len = pEdit->sizePass.cx*len;
			pEdit->caretPt.x = pEdit->sizePass.cx*len;
		}
		else //单行输入
		{
			SIZE size; //字符串长度
			HDC hdc = GetDC(NULL);
			HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32W(hdc, pText, len, &size);
			SelectObject(hdc, hOldFont);
			ReleaseDC(NULL, hdc);
			pST->len = size.cx;
			pEdit->caretPt.x += size.cx;
		}
		pEdit->column = len;
		Edit_SetCaretPos(hEle);
	}
	else
	{
		//XTRACE("edit 空值\n");
		return;
	}

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);
}

//多行模式
void Edit_SetText_MoreLine(HELE hEle, wchar_t *pText)
{
	edit_ *pEdit = EDIT(hEle);

	SIZE size; //字符串长度
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

	wchar_t *pBegin = pText;
	wchar_t *pWChar = pText;
	while (1)
	{
		if (VK_TAB == *pWChar)//把TAB替换成空格
			*pWChar = L' ';
		if (L'\n' == *pWChar) //换行
		{
			int len = pWChar - pBegin;
			if (L'\r' == *(pWChar - 1))
			{
				len--;
			}
			if (len > 0)
			{
				editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row);
				XStr_AddStringLength(pST->hString, pBegin, len);
				//字符串长度
				GetTextExtentPoint32W(hdc, pBegin, len, &size);
				pST->len = size.cx;

				editStrList_ *pNew = (editStrList_*)malloc(sizeof(editStrList_));
				pNew->hString = XStr_Create();
				pNew->len = 0;

				XArray_Add(pEdit->hArrayEdit, pNew);
				pEdit->row++;
				pEdit->rows++;

				pBegin = pWChar + 1;
			}
			else if (0 == len)
			{			//XTRACE("错误\n");
				editStrList_ *pNew = (editStrList_*)malloc(sizeof(editStrList_));
				pNew->hString = XStr_Create();
				pNew->len = 0;

				XArray_Add(pEdit->hArrayEdit, pNew);
				pEdit->row++;
				pEdit->rows++;

				pBegin = pWChar + 1;
			}
			else
			{
				XTRACE("错误1\n");
				break;
			}
		}
		else if (0 == *pWChar)
		{
			int len = pWChar - pBegin;
			if (len > 0)
			{
				editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row);
				XStr_AddStringLength(pST->hString, pBegin, len);
				//字符串长度
				GetTextExtentPoint32W(hdc, pBegin, len, &size);
				pST->len = size.cx;
				pEdit->column = len;
			}
			else if (0 == len) //空行
			{
			}
			else
			{
				XTRACE("错误2\n");
			}
			break;
		}
		pWChar++;
	}
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	//检查最长的行
	for (int i = 0; i <= pEdit->rows; i++)
	{
		if (Array_GetAtEdit(pEdit->hArrayEdit, i)->len > Array_GetAtEdit(pEdit->hArrayEdit, pEdit->maxLine)->len)
		{
			pEdit->maxLine = i;
		}
	}

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);

	editStrList_ *pSTS = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row);
	pEdit->caretPt.x = pSTS->len;
	pEdit->caretPt.y = pEdit->rows*pEdit->rowHeight;

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
}

/// @brief 设置文本内容.
/// @param hEle  元素句柄.
/// @param pText 文本内容.
void WINAPI XEdit_SetText(HELE hEle, wchar_t *pText)  //设置文本
{
	IsEditDebug(hEle, __FUNCTION__);
	edit_ *pEdit = EDIT(hEle);

	BOOL bSendEvent = FALSE; //是否发送事件

	if (FALSE == XEdit_IsEmpty(hEle))
	{
		XEdit_DeleteAll(hEle);//清空文本
		bSendEvent = TRUE;
	}
	pEdit->maxLine = 0;

	do 
	{
		if (NULL == pText)
		{
			if (bSendEvent)
				Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
			break;
		}

		if (pEdit->bNumber) //数字
		{
			if (FALSE == Edit_SetText_ExamineStringNumber(hEle, pText))
				break;
		}

		if (pEdit->bPass || FALSE == pEdit->bMoreLine) //密码框 或者 单行
		{
			Edit_SetText_SingleLine(hEle, pText);
			Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
			break;
		}
		else
		{
			Edit_SetText_MoreLine(hEle, pText);
			Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
		}
	} while (0);
	XEle_RedrawEle(hEle);
}


/// @brief 设置内容整形(int).
/// @param hEle  元素句柄.
/// @param value 文本内容.
void WINAPI XEdit_SetInt(HELE hEle, int value)  //设置整形内容
{
	IsEditDebug(hEle, __FUNCTION__);
	wchar_t text[MAX_PATH] = { 0 };
	_itow_s(value, text, 10);
	XEdit_SetText(hEle, text);
}

void Edit_InsertText_SingleLine(HELE hEle, wchar_t *pText, wchar_t *pBuf, int row, int column)
{
	edit_ *pEdit = EDIT(hEle);
	wchar_t *pBegin = pText;
	wchar_t *pWChar = pText;
	int len = 0;
	while (1)
	{
		if (VK_TAB == *pWChar)//把TAB替换成空格
			*pWChar = L' ';
		if (L'\n' == *pWChar) //换行
		{
			len = pWChar - pBegin;
			if (L'\r' == *(pWChar - 1))
			{
				len--;
			}
			break;
		}
		else if (0 == *pWChar)
		{
			len = pWChar - pBegin;
			break;
		}
		pWChar++;
	}
	if (len > 0)
	{
		editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, row);
		XStr_AddStringLength(pST->hString, pBegin, len);

		if (pBuf) //添加插入位置后面的字符串
		{
			XStr_AddString(pST->hString, pBuf);
			free(pBuf);
		}

		if (pEdit->bPass) //密码框
		{
			pST->len += pEdit->sizePass.cx*len;
			pEdit->caretPt.x += pEdit->sizePass.cx*len;
		}
		else //单行输入
		{
			SIZE size; //字符串长度
			HDC hdc = GetDC(NULL);
			HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32W(hdc, pBegin, len, &size);
			SelectObject(hdc, hOldFont);
			ReleaseDC(NULL, hdc);
			pST->len += size.cx;
			pEdit->caretPt.x += size.cx;
		}
		pEdit->column = column + len;
		Edit_SetCaretPos(hEle);
	}
	else
	{
		XTRACE("错误\n"); return;
	}

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);

	//向右拖到滚动条滚动,水平滚动
	Edit_ScrollH(hEle);

	XEle_RedrawEle(hEle);
}

void Edit_InsertText_MoreLine(HELE hEle, wchar_t *pText, wchar_t *pBuf, int row, int column)
{
	edit_ *pEdit = EDIT(hEle);
	{
		SIZE size; //字符串长度
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

		wchar_t *pBegin = pText;
		wchar_t *pWChar = pText;
		while (1)
		{
			if (VK_TAB == *pWChar)//把TAB替换成空格
				*pWChar = L' ';
			if (L'\n' == *pWChar) //换行
			{
				int len = pWChar - pBegin;
				if (L'\r' == *(pWChar - 1))
				{
					len--;
				}

				if (len > 0)
				{
					editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, row);
					XStr_AddStringLength(pST->hString, pBegin, len);

					wchar_t *pStr = XStr_GetBuffer(pST->hString);
					len = XStr_GetLength(pST->hString);
					//字符串长度
					GetTextExtentPoint32W(hdc, pStr, len, &size);
					pST->len = size.cx;

					editStrList_ *pNew = (editStrList_*)malloc(sizeof(editStrList_));
					pNew->hString = XStr_Create();
					pNew->len = 0;

					XArray_insert(pEdit->hArrayEdit, pNew, row + 1);
					row++;
					pEdit->rows++;

					pBegin = pWChar + 1;
				}
				else if (0 == len) //空行
				{
					//XTRACE("错误\n");
					editStrList_ *pNew = (editStrList_*)malloc(sizeof(editStrList_));
					pNew->hString = XStr_Create();
					pNew->len = 0;

					XArray_insert(pEdit->hArrayEdit, pNew, row + 1);
					row++;
					pEdit->rows++;

					pBegin = pWChar + 1;
				}
				else
				{
					XTRACE("错误1\n");
					return;
				}
			}
			else if (0 == *pWChar)
			{
				int len = pWChar - pBegin;
				if (len > 0)
				{
					editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, row);
					XStr_AddStringLength(pST->hString, pBegin, len);

					wchar_t *pStr = XStr_GetBuffer(pST->hString);
					len = XStr_GetLength(pST->hString);
					//调整插入符位置
					GetTextExtentPoint32W(hdc, pStr, len, &size);
					column = len;
					pEdit->caretPt.x = size.cx;
					pST->len = size.cx;

					if (pBuf) //添加插入位置后面的字符串
					{
						XStr_AddString(pST->hString, pBuf);
						free(pBuf);
						pStr = XStr_GetBuffer(pST->hString);
						len = XStr_GetLength(pST->hString);
						if (pStr) //字符串长度
						{
							GetTextExtentPoint32W(hdc, pStr, len, &size);
							pST->len = size.cx;
						}
					}
				}
				else if (0 == len) //空内容
				{
					column = 0;
					pEdit->caretPt.x = 0;
				}
				else
				{
					XTRACE("错误2\n");
					return;
				}
				break;
			}
			pWChar++;
		}
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);
	}
	///////////////////////////////////////////////////

	//将插入的几行和最长行比较
	int index = 0;
	for (int i = pEdit->row; i <= row; i++)
	{
		if (Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row + index)->len > Array_GetAtEdit(pEdit->hArrayEdit, pEdit->maxLine)->len)
		{
			pEdit->maxLine = pEdit->row + index;
		}
		index++;
	}

	pEdit->row = row;
	pEdit->column = column;

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);

	pEdit->caretPt.y = row*pEdit->rowHeight;
	Edit_SetCaretPos(hEle);

	//向右拖到滚动条滚动,水平滚动
	Edit_ScrollH(hEle);
	Edit_ScrollV(hEle);

	//XEle_RedrawEle(hEle);
}

/// @brief 编辑框插入文本内容.
/// @param hEle   元素句柄.
/// @param pText  插入的文本内容.
/// @param row    插入的行位置,如果值为-1插入到末尾行.
/// @param column  插入的列位置,如果值为-1插入末尾列
void WINAPI XEdit_InsertText(HELE hEle, wchar_t *pText, int row, int column) //插入文本
{
	IsEditDebug(hEle, __FUNCTION__);

	if (Edit_InsertText(hEle, pText, row, column))
		Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
}

void Edit_GetSelectTextHandle(HELE hEle, HSTRING hString, int beginRow, int endRow, int beginColumn, int endColumn)
{
	edit_ *pEdit = EDIT(hEle);
	int lines = endRow - beginRow;
	//开始行
	HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, beginRow)->hString;
	wchar_t *pBuf = XStr_GetBuffer(hStr);
	XStr_AddString(hString, pBuf + beginColumn);
	XStr_AddString(hString, L"\r\n");

	//中间行
	if (lines > 1)
	{
		int rows = lines;
		for (int i = 1; i < rows; i++)
		{
			hStr = Array_GetAtEdit(pEdit->hArrayEdit, beginRow + i)->hString;
			pBuf = XStr_GetBuffer(hStr);
			XStr_AddString(hString, pBuf);
			XStr_AddString(hString, L"\r\n");
		}
	}

	//结束行
	hStr = Array_GetAtEdit(pEdit->hArrayEdit, endRow)->hString;
	pBuf = XStr_GetBuffer(hStr);
	XStr_AddStringLength(hString, pBuf, endColumn);
}

//return:如果内容改变返回TRUE
BOOL Edit_InsertText(HELE hEle, wchar_t *pText, int row, int column)
{
	edit_ *pEdit = EDIT(hEle);

	if (row < -1 || column < -1)
	{
		return FALSE;
	}
	if (row > pEdit->rows)
	{
		return FALSE;
	}
	if (-1 == row) //末尾行
	{
		row = pEdit->rows;
	}
	if (-1 == column) //末尾列
	{
		editStrList_ *pStruct = (editStrList_*)XArray_GetAt(pEdit->hArrayEdit, row);
		column = XStr_GetLength(pStruct->hString);
	}

	if (pEdit->bNumber) //数字
	{
		if (FALSE == Edit_SetText_ExamineStringNumber(hEle, pText))
			return FALSE;
	}

	//将插入位置后面内容临时保存
	wchar_t *pBuf = NULL;
	{
		editStrList_ *pSTIN = (editStrList_*)XArray_GetAt(pEdit->hArrayEdit, row);
		if (NULL == pSTIN) return FALSE;

		int len = XStr_GetLength(pSTIN->hString);
		len = len - column; //需要拷贝长度
		if (len > 0)
		{
			pBuf = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
			wchar_t *pSrc = XStr_GetBuffer(pSTIN->hString);
			wmemcpy(pBuf, pSrc + column, len);
			pBuf[len] = 0;
			XStr_SetLength(pSTIN->hString, column);
		}
	}
	/////////密码框 -或-单行输入/////////////////////////////////////////////
	if (pEdit->bPass || FALSE == pEdit->bMoreLine)
	{
		Edit_InsertText_SingleLine(hEle, pText, pBuf, row, column);
	}
	else
	{
		Edit_InsertText_MoreLine(hEle, pText, pBuf, row, column);
	}
	return TRUE;
}

/// @brief 获取选择的文本内容.
/// @param hEle  元素句柄.
/// @param pOut  接收内容缓冲区.
/// @param len   pOut缓冲区长度,以字符为长度单位.
void WINAPI XEdit_GetSelectText(HELE hEle, wchar_t *pOut, int len)
{
	IsEditDebug(hEle, __FUNCTION__);

	HSTRING hString = Edit_GetSelectText(hEle);
	if (hString)
	{
		int length = XStr_GetLength(hString);
		if (length > 0)
			wcscpy_s(pOut, len, XStr_GetBuffer(hString));

		XStr_Destroy(hString);
	}
}

/// @brief 获取编辑框内容长度,包含回车换行符,不包含空终止符.
/// @param hEle  元素句柄.
/// @return 内容字符数量.
int WINAPI XEdit_GetTextLength(HELE hEle) //获取内容长度
{
	IsEditDebug(hEle, __FUNCTION__);
	edit_ *pEdit = EDIT(hEle);

	int length = 0;
	if (0 == pEdit->rows) //只有一行
	{
		editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, 0);
		if (0 == pST->len)  //没有内容
		{
			return 0;
		}
	}

	editStrList_ *pST = NULL;
	int count = pEdit->rows + 1;
	for (int i = 0; i < count; i++)
	{
		pST = Array_GetAtEdit(pEdit->hArrayEdit, i);
		length += XStr_GetLength(pST->hString);

		if (i != pEdit->rows) //换行
		{
			length += 2;
		}
	}
	return length;
}


/// @brief 获取文本内容.
/// @param hEle  元素句柄.
/// @param pOut 接收内容缓冲区.
/// @param len  pOut缓冲区长度,以字符为长度单位.
void WINAPI XEdit_GetText(HELE hEle, wchar_t *pOut, int len) //获取选择文本
{
	IsEditDebug(hEle, __FUNCTION__);
	edit_ *pEdit = EDIT(hEle);

	if (0 == pEdit->rows) //只有一行
	{
		editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, 0);
		if (0 == pST->len)  //没有内容
		{
			return;
		}
	}

	int pos = 0;
	editStrList_ *pST = NULL;
	wchar_t  *pBuf = NULL;
	int count = pEdit->rows + 1;
	for (int i = 0; i < count; i++)
	{
		pST = Array_GetAtEdit(pEdit->hArrayEdit, i);
		pBuf = XStr_GetBuffer(pST->hString);
		int length = XStr_GetLength(pST->hString);
		if ((pos + length) < len)
		{
			wmemcpy(pOut + pos, pBuf, length);
			pos += length;
		}
		else
		{
			length = len - pos;
			wmemcpy(pOut + pos, pBuf, length);
			pos += length;
			break;
		}
		if (i != pEdit->rows) //换行
		{
			if ((pos + 1) < len)
			{
				pOut[pos] = '\r';
				pos++;
				if ((pos + 1) < len)
				{
					pOut[pos] = '\n';
					pos++;
				}
			}
			else
				break;
		}
	}
	if (pos < len)
		pOut[pos] = 0;
}

/// @brief 获取整形(int)内容值.
/// @param hEle  元素句柄.
/// @return 返回整形内容值.
int WINAPI XEdit_GetInt(HELE hEle) //获取整形内容
{
	IsEditDebug(hEle, __FUNCTION__);
	wchar_t text[MAX_PATH] = { 0 };
	XEdit_GetText(hEle, text, MAX_PATH - 1);
	return _wtoi(text);
}

/// @brief 获取编辑框文本总行数.
/// @param hEle  元素句柄.
/// @return 编辑框文本总行数.
int WINAPI XEdit_GetRowCount(HELE hEle)   //获取总行数
{
	IsEditDebug(hEle, __FUNCTION__);
	return EDIT(hEle)->rows;
}

/// @brief 获取编辑框指定行字符总数.
/// @param hEle  元素句柄.
/// @param row  行号,基于0的索引.
/// @return 指定行字符总数.
int WINAPI XEdit_GetColumnCount(HELE hEle, int row) //获取指定行字符数,row=-1末尾行;
{
	IsEditDebug(hEle, __FUNCTION__);
	if (row > EDIT(hEle)->rows || row < -1)
	{
		return -1;
	}
	if (-1 == row) //末尾行
	{
		row = EDIT(hEle)->rows;
	}
	editStrList_ *pStruct = (editStrList_*)XArray_GetAt(EDIT(hEle)->hArrayEdit, row);
	if (pStruct)
	{
		return XStr_GetLength(pStruct->hString);
	}
	return -1;
}

/// @brief 获取插入符位置当前行(基于0索引).
/// @param hEle  元素句柄.
/// @return  插入符当前行.
int WINAPI XEdit_GetCurrentRow(HELE hEle) //获取插入符位置当前行
{
	IsEditDebug(hEle, __FUNCTION__);
	return EDIT(hEle)->row;
}

/// @brief 获取插入符位置当前列(基于0索引).一个字符占一列.
/// @param hEle  元素句柄.
/// @return  插入符当前列.
int WINAPI XEdit_GetCurrentColumn(HELE hEle) //获取插入符位置当前列
{
	IsEditDebug(hEle, __FUNCTION__);
	return EDIT(hEle)->column;
}

/// @brief 判断编辑框内容是否为空.
/// @param hEle  元素句柄.
/// @return  如果内容为空返回TRUE,否则相反.
BOOL WINAPI XEdit_IsEmpty(HELE hEle) //判断内容是否为空
{
	IsEditDebug(hEle, __FUNCTION__);
	edit_ *pEdit = EDIT(hEle);

	int count = XArray_GetCount(pEdit->hArrayEdit);
	if (count < 1) return TRUE;

	if (1 == count)
	{
		editStrList_ *pItem = (editStrList_*)XArray_GetAt(pEdit->hArrayEdit, 0);
		if (NULL == pItem) return TRUE;

		if (NULL == pItem->hString) return TRUE;

		if (XStr_GetLength(pItem->hString) < 1)
		{
			return TRUE; //内容为空
		}
	}
	return FALSE;
}

void WINAPI XEdit_DeleteAll(HELE hEle)  //清空  删除所有文本
{
	IsEditDebug(hEle, __FUNCTION__);

	edit_ *pEdit = EDIT(hEle);
	int count = Array_GetCount(pEdit->hArrayEdit);
	HSTRING hString;
	for (int i = count - 1; i > 0; i--)
	{
		hString = Array_GetAtEdit(pEdit->hArrayEdit, i)->hString;
		XStr_Destroy(hString);
		delete Array_GetAtEdit(pEdit->hArrayEdit, i);
		XArray_DeleteIndex(pEdit->hArrayEdit, i);
	}

	hString = Array_GetAtEdit(pEdit->hArrayEdit, 0)->hString;
	Array_GetAtEdit(pEdit->hArrayEdit, 0)->len = 0;
	XStr_Empty(hString);

	if (pEdit->bDrawSelect)
		pEdit->bDrawSelect = FALSE;
	pEdit->row = 0;
	pEdit->column = 0;
	pEdit->rows = 0;

	pEdit->caretPt.x = 0;
	pEdit->caretPt.y = 0;
	pEdit->maxLine = 0;

	Edit_SetCaretPos(hEle);
	Edit_AdjustViewSize(hEle); //调整视图内容大小
}

/// @brief 清空编辑框内容.
/// @param hEle  元素句柄.
void WINAPI XEdit_Menu_DeleteAll(HELE hEle) //清空  删除所有文本
{
	IsEditDebug(hEle, __FUNCTION__);
	if (EDIT(hEle)->bReadOnly)
		return;

	XEdit_DeleteAll(hEle);
}

/// @brief 设置鼠标离开状态显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
void WINAPI XEdit_SetImageLeave(HELE hEle, HIMAGE hImage) //鼠标离开
{
	IsEditDebug(hEle, __FUNCTION__);
	XSView_SetImage(hEle, hImage);
}

/// @brief 设置鼠标在元素上停留状态时显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
void WINAPI XEdit_SetImageStay(HELE hEle, HIMAGE hImage) //鼠标停留
{
	IsEditDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(EDIT(hEle)->hImage_stay, hImage);
}

HSTRING Edit_GetSelectText(HELE hEle)
{
	edit_ *pEdit = EDIT(hEle);
	if (FALSE == pEdit->bDrawSelect) return NULL;

	HSTRING hString = XStr_Create();
	if (pEdit->downRow == pEdit->endRow)  //单行
	{
		HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->downRow)->hString;
		wchar_t *pBuf = XStr_GetBuffer(hStr);
		if (pEdit->downX < pEdit->endX) //向后选择
		{
			int len = pEdit->endColumn - pEdit->downColumn;
			XStr_AddStringLength(hString, pBuf + pEdit->downColumn, len);
		}
		else //向前选择
		{
			int len = pEdit->downColumn - pEdit->endColumn;
			XStr_AddStringLength(hString, pBuf + pEdit->endColumn, len);
		}
	}
	else if (pEdit->downRow < pEdit->endRow) //向下选择
	{
		Edit_GetSelectTextHandle(hEle, hString, pEdit->downRow, pEdit->endRow, pEdit->downColumn, pEdit->endColumn);
	}
	else   //向上选择
	{
		Edit_GetSelectTextHandle(hEle, hString, pEdit->endRow, pEdit->downRow, pEdit->endColumn, pEdit->downColumn);
	}
	return hString;
}

//return:有内容被删除返回TRUE,没有删除任何内容返回FALSE
BOOL Edit_DeleteSelectText(HELE hEle)
{
	edit_ *pEdit = EDIT(hEle);

	if (FALSE == pEdit->bDrawSelect) return FALSE;

	pEdit->bDrawSelect = FALSE;

	if (pEdit->downRow == pEdit->endRow) //只有一行
	{
		if (pEdit->downColumn == pEdit->endColumn) //没有选择
		{
			return FALSE;
		}
		else if (pEdit->downColumn < pEdit->endColumn) //向后选择
		{
			HSTRING hString = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->downRow)->hString;
			XStr_DeleteLength(hString, pEdit->downColumn, pEdit->endColumn - pEdit->downColumn);
			pEdit->column = pEdit->downColumn;
			pEdit->caretPt.x = pEdit->downX;

			//调整
			wchar_t *pText = XStr_GetBuffer(hString);
			SIZE size = { 0,0 };
			if (pText) //字符长度
			{
				if (FALSE == pEdit->bPass)
				{
					HDC hdc = GetDC(NULL);
					HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
					GetTextExtentPoint32W(hdc, pText, XStr_GetLength(hString), &size);
					SelectObject(hdc, hOldFont);
					ReleaseDC(NULL, hdc);
				}
				else
				{
					size.cx = pEdit->sizePass.cx;
				}
			}
			Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len = size.cx;

			Edit_SetCaretPos(hEle);
		}
		else //向前选择
		{
			HSTRING hString = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->downRow)->hString;
			XStr_DeleteLength(hString, pEdit->endColumn, pEdit->downColumn - pEdit->endColumn);
			pEdit->column = pEdit->endColumn;
			pEdit->caretPt.x = pEdit->endX;

			//调整
			wchar_t *pText = XStr_GetBuffer(hString);
			SIZE size = { 0,0 };
			if (pText) //字符长度
			{
				if (FALSE == pEdit->bPass)
				{
					HDC hdc = GetDC(NULL);
					HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
					GetTextExtentPoint32W(hdc, pText, XStr_GetLength(hString), &size);
					SelectObject(hdc, hOldFont);
					ReleaseDC(NULL, hdc);
				}
				else
				{
					size.cx = pEdit->sizePass.cx;
				}
			}
			Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len = size.cx;

			Edit_SetCaretPos(hEle);
		}
	}
	else if (pEdit->downRow < pEdit->endRow)  //向下选择
	{
		Edit_DeleteSelectTextHandle(hEle, pEdit->downRow, pEdit->endRow,
			pEdit->downColumn, pEdit->endColumn, pEdit->downX);
	}
	else  //向上选择
	{
		Edit_DeleteSelectTextHandle(hEle, pEdit->endRow, pEdit->downRow,
			pEdit->endColumn, pEdit->downColumn, pEdit->endX);
	}

	//最长行检查
	//设置视图内容大小
	if (pEdit->maxLine > pEdit->rows)
	{
		pEdit->maxLine = 0;
	}

	//检查最长的行
	if (pEdit->row != pEdit->maxLine)
	{
		if (Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len > Array_GetAtEdit(pEdit->hArrayEdit, pEdit->maxLine)->len)
		{
			pEdit->maxLine = pEdit->row;
		}
	}

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);

	//向右拖到滚动条滚动,水平滚动
	Edit_ScrollH(hEle);
	return TRUE;
}

void Edit_DeleteSelectTextHandle(HELE hEle, int beginRow, int endRow, int beginColumn, int endColumn, int beginX) //删除选择文本(向下选择)
{
	edit_ *pEdit = EDIT(hEle);
	int lines = endRow - beginRow;  //选择总行数

	if (lines > 1)	//删除中间行
	{
		int dels = lines - 1;
		for (int i = 0; i < dels; i++)
		{
			HSTRING hString = Array_GetAtEdit(pEdit->hArrayEdit, beginRow + 1)->hString;
			XStr_Destroy(hString);
			delete Array_GetAtEdit(pEdit->hArrayEdit, beginRow + 1);
			XArray_DeleteIndex(pEdit->hArrayEdit, beginRow + 1);
			endRow--;

			pEdit->rows--;
		}
	}

	//删除开始行选择字符
	HSTRING hString = Array_GetAtEdit(pEdit->hArrayEdit, beginRow)->hString;
	int len = XStr_GetLength(hString);
	if (beginColumn < len)
	{
		XStr_DeleteFront(hString, beginColumn - 1);
	}

	HSTRING hString2 = Array_GetAtEdit(pEdit->hArrayEdit, endRow)->hString;
	//删除结束行选择字符
	if (endColumn > 0)
	{
		XStr_DeleteBack(hString2, endColumn); //
	}
	//将开始行与结束行合并
	wchar_t *pText = XStr_GetBuffer(hString2);
	XStr_AddString(hString, pText);

	//删除结束行
	XStr_Destroy(hString2);
	delete Array_GetAtEdit(pEdit->hArrayEdit, endRow);
	XArray_DeleteIndex(pEdit->hArrayEdit, endRow);
	pEdit->rows--;

	//调整
	pText = XStr_GetBuffer(hString);
	SIZE size = { 0,0 };
	if (pText) //字符长度
	{
		if (FALSE == pEdit->bPass)
		{
			HDC hdc = GetDC(NULL);
			HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32W(hdc, pText, XStr_GetLength(hString), &size);
			SelectObject(hdc, hOldFont);
			ReleaseDC(NULL, hdc);
		}
		else
		{
			size.cx = pEdit->sizePass.cx;
		}
	}
	Array_GetAtEdit(pEdit->hArrayEdit, beginRow)->len = size.cx;
	pEdit->row = beginRow;
	pEdit->column = beginColumn;

	pEdit->caretPt.x = beginX;
	pEdit->caretPt.y = pEdit->row*pEdit->rowHeight;
	Edit_SetCaretPos(hEle);
}

/// @brief 设置编辑框元素为只读类型,不可以通过键盘输入及粘贴.
/// @param hEle  元素句柄.
/// @param bRead TRUE只读内容,否则相反.
void WINAPI XEdit_SetReadOnly(HELE hEle, BOOL bRead)  //设置只读文本
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->bReadOnly = bRead;
}

/// @brief 设置文本左对齐间距.
/// @param hEle  元素句柄.
/// @param spacing 间距大小.
void WINAPI XEdit_SetTextSpacingLeft(HELE hEle, int spacing)  //设置字体左对齐间隔
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->spacLeft = spacing;
}

/// @brief 设置文本上对齐间距.
/// @param hEle  元素句柄.
/// @param spacing 间距大小.
void WINAPI XEdit_SetTextSpacingTop(HELE hEle, int spacing)  //设置字体上对齐间隔
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->spacTop = spacing;
}

/// @brief 设置插入符位置
/// @param hEle  元素句柄.
/// @param line   行位置,基于0索引,0代表第一行.
/// @param column  列位置,基于0索引,0代表第一列.
void WINAPI XEdit_SetPos(HELE hEle, int line, int column) //设置插入符位置
{
	IsEditDebug(hEle, __FUNCTION__);

	if (line < 0 || column < 0) return;

	edit_ *pObject = EDIT(hEle);

	int lineCount = XArray_GetCount(pObject->hArrayEdit);
	if (line >= lineCount) return;

	editStrList_ *pInfo = (editStrList_*)XArray_GetAt(pObject->hArrayEdit, line);

	int charLen = XStr_GetLength(pInfo->hString);

	if (column > charLen) return;

	wchar_t *pStr = XStr_GetBuffer(pInfo->hString);

	SIZE size;
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	int posx = 0;
	for (int i = 0; i < column; i++)
	{
		GetTextExtentPoint32(hdc, pStr + i, 1, &size);
		posx += size.cx;

	}
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	pObject->row = line;
	pObject->column = column;

	pObject->caretPt.x = posx;
	pObject->caretPt.y = pObject->rowHeight*line;

	Edit_SetCaretPos(hEle);

	//滚动视图
	//Edit_ScrollVTop(hEle);
	Edit_ScrollH(hEle);
	Edit_ScrollV(hEle);
}

/// @brief 设置编辑框插入符宽度.
/// @param hEle  元素句柄.
/// @param width 插入符宽度,默认为1.
void WINAPI XEdit_SetCaretWidth(HELE hEle, int width) //设置编辑框插入符宽度
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->caretWidth = width;
}

/// @brief 退格,删除插入符前面的一个字符..
/// @param hEle  元素句柄.
void WINAPI XEdit_SetBackspace(HELE hEle)  //退格
{
	IsEditDebug(hEle, __FUNCTION__);
	Edit_CharBackspace(hEle);
}

/// @brief 设置选择文本背景颜色..
/// @param hEle  元素句柄.
/// @param color 选择文本背景颜色.
void WINAPI XEdit_SetSelectTextBkColor(HELE hEle, COLORREF color) //设置选择文本背景颜色
{
	IsEditDebug(hEle, __FUNCTION__);
	EDIT(hEle)->selColor = color;
}

//void WINAPI XEdit_SetSelectText(HELE hEle, int startRow, int startCol, int endRow, int endCol)
//{
//	edit_ *pObject = EDIT(hEle);
//
//	//XEdit_SetPos(hEle, startRow, startCol);
//	//Gergul
//
//	pObject->bDown = TRUE;
//	pObject->downRow = startRow;
//	pObject->downColumn = startCol;
//
//	pObject->endRow = endRow;
//	pObject->endColumn = endCol;
//
//	XEle_RedrawEle(hEle);
//	pObject->bDown = FALSE;
//}

/// @brief 剪切选择的文本.
/// @param hEle  元素句柄.
void WINAPI XEdit_Menu_Cut(HELE hEle) //剪切  删除选择的文本,并将文本拷贝到剪切板中
{
	IsEditDebug(hEle, __FUNCTION__);
	XEdit_Menu_Copy(hEle);              //复制
	if (FALSE == EDIT(hEle)->bReadOnly)
	{
		if (Edit_DeleteSelectText(hEle))  //删除选择的文本
			Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
	}
}

/// @brief 复制选择的文本到剪切板.
/// @param hEle  元素句柄.
void WINAPI XEdit_Menu_Copy(HELE hEle) //复制  复制选择的文本到剪切板中
{
	IsEditDebug(hEle, __FUNCTION__);
	HSTRING hString = Edit_GetSelectText(hEle);
	if (NULL == hString)
		return;
	int len = XStr_GetLength(hString);
	wchar_t *pStr = XStr_GetBuffer(hString);
	if (OpenClipboard(((ele_*)hEle)->pWindow->hWnd))
	{
		EmptyClipboard();
		HGLOBAL hClip = GlobalAlloc(GMEM_MOVEABLE, sizeof(wchar_t)*(len + 1));
		wchar_t *pBuf = (wchar_t*)GlobalLock(hClip);
		wmemcpy(pBuf, pStr, len);
		pBuf[len] = 0;
		GlobalUnlock(hClip);
		SetClipboardData(CF_UNICODETEXT, hClip);
		CloseClipboard();
	}
	XStr_Destroy(hString);
}

/// @brief 将剪切板中的文本,粘贴到当前插入符位置.
/// @param hEle  元素句柄.
void WINAPI XEdit_Menu_Paste(HELE hEle) //粘贴  将剪切板中的文本插入当前光标位置
{
	IsEditDebug(hEle, __FUNCTION__);
	if (EDIT(hEle)->bReadOnly)
		return;

	BOOL bSendEvent = Edit_DeleteSelectText(hEle);

	if (NULL == OpenClipboard(((ele_*)hEle)->pWindow->hWnd))
		return;
	HANDLE hGlb = GetClipboardData(CF_UNICODETEXT);
	if (NULL == hGlb) return;
	wchar_t *pText = (wchar_t*)GlobalLock(hGlb);
	if (NULL == pText) return;

	int len = wcslen(pText);
	if (len > 0)
	{
		//	XEdit_InsertText(hEle,pText,EDIT(hEle)->row,EDIT(hEle)->column); //插入文本
		if (bSendEvent || Edit_InsertText(hEle, pText, EDIT(hEle)->row, EDIT(hEle)->column))
		{
			Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
		}
	}
	GlobalUnlock(hGlb);
	CloseClipboard();
}

/// @brief 删除选择的文本内容.当只读属性时无法删除文本.例如:鼠标右键弹出菜单项,[删除选择文本]功能.
/// @param hEle  元素句柄.
void WINAPI XEdit_Menu_Clear(HELE hEle) //删除  删除选择的文本
{
	IsEditDebug(hEle, __FUNCTION__);
	if (EDIT(hEle)->bReadOnly)
		return;
	if (Edit_DeleteSelectText(hEle))
		Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
}

/// @brief 选择所有文本内容.
/// @param hEle  元素句柄.
void WINAPI XEdit_Menu_SelectAll(HELE hEle) //全选  选择所有文本
{
	IsEditDebug(hEle, __FUNCTION__);
	edit_ *pEdit = EDIT(hEle);

	if (0 == Array_GetAtEdit(pEdit->hArrayEdit, 0)->len)
		return;

	pEdit->downX = 0;
	pEdit->downRow = 0;
	pEdit->downColumn = 0;

	editStrList_ *pST = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->rows);
	pEdit->endX = pST->len;
	pEdit->endRow = pEdit->rows;
	pEdit->endColumn = XStr_GetLength(pST->hString);
	pEdit->bDrawSelect = TRUE;

	XEle_RedrawEle(hEle);
}

BOOL CALLBACK Edit_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (EDIT(hEle)->bMouseStay || XEle_IsFocus(hEle))
	{
		if (EDIT(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw, EDIT(hEle)->hImage_stay, &rect);
		}
	}
	else
	{
		if (SCROLLVIEW(hEle)->hImage_bk)
		{
			XDraw_HImageSuper_(hDraw, SCROLLVIEW(hEle)->hImage_bk, &rect);
		}
	}

	if (((ele_*)hEle)->bBorder)
	{
		COLORREF color = ((ele_*)hEle)->borderColor;
		if (XEle_IsFocus(hEle) || EDIT(hEle)->bMouseStay)
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

	return TRUE;
}

BOOL CALLBACK Edit_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	edit_ *pEdit = EDIT(hEle);

	//绘制选择文本背景
	Edit_DrawSelect(hEle, hDraw);

	int left = pEdit->spacLeft;//+SCROLLVIEW(hEle)->left;
	int top = pEdit->spacTop;//+SCROLLVIEW(hEle)->top;

	int count = Array_GetCount(pEdit->hArrayEdit);
	editStrList_ *pStrT = NULL;

	if (FALSE == pEdit->bPass)
	{
		for (int i = 0; i < count; i++)
		{
			pStrT = Array_GetAtEdit(pEdit->hArrayEdit, i);
			if (pStrT)
			{
				XDraw_TextOut_(hDraw, left, top, XStr_GetBuffer(pStrT->hString), XStr_GetLength(pStrT->hString));
				top += pEdit->rowHeight;
			}
		}
	}
	else //密码
	{
		pStrT = Array_GetAtEdit(pEdit->hArrayEdit, 0);
		if (pStrT)
		{
			int len = XStr_GetLength(pStrT->hString);
			if (len < MAX_PATH)
			{
				wchar_t pass[MAX_PATH] = { 0 };
				wmemset(pass, L'*', len);
				XDraw_TextOut_(hDraw, left, top, pass, len);
			}
		}
	}

	//	XTRACE("行%d ,列%d ,总行数%d\n",pEdit->row,pEdit->column,pEdit->rows);
	//	XTRACE("column %d\n",pEdit->endColumn);
	return TRUE;
}

BOOL CALLBACK Edit_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt)
{
	if (XEle_IsHitChildEle(hEle, pPt))
		return FALSE;

	HELE hEdit = XEle_GetParentEle(hEle);

	XEle_SetFocus(hEdit, TRUE);

	edit_ *pEdit = (edit_*)hEdit;

	SetCursor(::LoadCursor(NULL, IDC_IBEAM));

	Edit_TestDown(hEdit, pPt);
	if (EDIT(hEdit)->bCaretCreate)
	{
		Edit_SetCaretPos(hEdit);
	}
	if (EDIT(hEdit)->bDrawSelect)
	{
		EDIT(hEdit)->bDrawSelect = FALSE;
	}

	//文本选择
	pEdit->bDown = TRUE;
	pEdit->downX = pEdit->caretPt.x;
	pEdit->downRow = pEdit->row;
	pEdit->downColumn = pEdit->column;

	XEle_SetCapture(hEle);
	XEle_RedrawEle(hEle);

	return FALSE;
}

BOOL CALLBACK Edit_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE hEdit = XEle_GetParentEle(hEle);
	if (EDIT(hEdit)->bDown)
	{
		EDIT(hEdit)->bDown = FALSE;
		XEle_ReleaseCapture(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnMouseMove_View(HELE hEle, UINT flags, POINT *pPt)
{
	if (XEle_IsHitChildEle(hEle, pPt))
		return FALSE;

	HELE hEdit = XEle_GetParentEle(hEle);

	RECT rect;
	XSView_GetViewRect(hEdit, &rect);
	if (EDIT(hEdit)->bDown)  //计算鼠标选择文本
	{
		SetCursor(::LoadCursor(NULL, IDC_IBEAM));
		if (pPt->x < rect.left)
		{
			XSView_ScrollLeftLine(hEdit);
			//XTRACE("edit 向左拖动滚动条 ←\n");
		}
		if (pPt->x > rect.right)
		{
			XSView_ScrollRightLine(hEdit);
			//XTRACE("edit 向右拖动滚动条 →\n");
		}
		if (pPt->y < rect.top)
		{
			XSView_ScrollTopLine(hEdit);
			//XTRACE("edit 向上拖动滚动条  ↑\n");
		}
		if (pPt->y > rect.bottom)
		{
			XSView_ScrollDownLine(hEdit);
			//XTRACE("edit 向下拖动滚动条  ↓\n");
		}

		int row = EDIT(hEdit)->row;
		int column = EDIT(hEdit)->column;

		Edit_TestDown(hEdit, pPt);

		if (row != EDIT(hEle)->row || column != EDIT(hEle)->column) //位置改变
		{
			Edit_SetCaretPos(hEdit);
			EDIT(hEdit)->bDrawSelect = TRUE;

			EDIT(hEdit)->endX = EDIT(hEdit)->caretPt.x;
			EDIT(hEdit)->endRow = EDIT(hEdit)->row;
			EDIT(hEdit)->endColumn = EDIT(hEdit)->column;
			XEle_RedrawEle(hEle); //绘制选择文本背景
			//XTRACE("位置改变\n");
		}
	}
	else
	{
		SetCursor(::LoadCursor(NULL, IDC_IBEAM));
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnRButtonDown_View(HELE hEle, UINT flags, POINT *pPt)
{
	if (XEle_IsHitChildEle(hEle, pPt))
		return FALSE;

	HELE hEdit = XEle_GetParentEle(hEle);

	//	if(FALSE==XEle_IsFocus(hEle))
	//	{
	XEle_SetFocus(hEdit, TRUE);
	//XTRACE("edit setFocus\n");
//	}

	RECT rect;
	XSView_GetViewRect(hEdit, &rect);
	//	if(PtInRect(&rect,*pPt))  //在视图内
	//	{
	SetCursor(::LoadCursor(NULL, IDC_IBEAM));

	Edit_TestDown(hEdit, pPt);
	if (EDIT(hEdit)->bCaretCreate)
	{
		Edit_SetCaretPos(hEdit);
	}
	if (EDIT(hEdit)->bDrawSelect)
	{
		EDIT(hEdit)->bDrawSelect = FALSE;
		if (EDIT(hEdit)->bCaretCreate)
			XEle_RedrawEle(hEle);
	}
	//	}

	return TRUE;
}

BOOL CALLBACK Edit_OnRButtonUp_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE hEdit = XEle_GetParentEle(hEle);
	if (EDIT(hEdit)->bMenu)
	{
		if (XEle_IsHitChildEle(hEle, pPt))
			return FALSE;

		POINT pt = *pPt;
		XEle_PointToNCWnd(hEle, &pt);

		HMENUX hMenu = XMenu_Create();
		XMenu_AddItem(hMenu, IDM_CLIP, L"剪切");
		XMenu_AddItem(hMenu, IDM_COPY, L"复制");
		XMenu_AddItem(hMenu, IDM_PASTE, L"粘贴");
		XMenu_AddItem(hMenu, IDM_DELETE, L"删除");
		XMenu_AddItem(hMenu, 0, NULL, XMENU_ROOT, XM_SEPARATOR);
		XMenu_AddItem(hMenu, IDM_SELECTALL, L"全选");
		XMenu_AddItem(hMenu, IDM_DELETEALL, L"清空");

		window_* pWindow = ((ele_*)hEle)->pWindow;
		ClientToScreen(pWindow->hWnd, &pt);
		XMenu_Popup(hMenu, pWindow->hWnd, pt.x, pt.y, hEdit);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventMouseStay(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		EDIT(hEle)->bMouseStay = TRUE;
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		EDIT(hEle)->bMouseStay = FALSE;
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventChar(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam)
{
	if (hEle != hEventEle)
		return FALSE;

	edit_ *pEdit = EDIT(hEle);
	if (pEdit->bDown) return TRUE;

	if (VK_TAB == wParam) return TRUE;  //TAB按键

	if (VK_ESCAPE == wParam) return TRUE;

	if (pEdit->bReadOnly) return TRUE; //只读

	if (0x8000 & GetKeyState(VK_CONTROL))
	{
		if (1 == wParam)  //全选
		{
			XEdit_Menu_SelectAll(hEle);
		}
		else if (3 == wParam) //复制
		{
			XEdit_Menu_Copy(hEle);
		}
		else if (22 == wParam) //粘贴
		{
			XEdit_Menu_Paste(hEle);
		}
		return TRUE;
	}

	wchar_t ch[2] = { 0 };
	ch[0] = wParam;

	//XTRACEW(L"char=%c \n",wParam);

	if (VK_BACK == wParam)  //退格
	{
		Edit_CharBackspace(hEle);
		//	XTRACEW(L"wchar=退格 \n",ch);
	}
	else if (VK_RETURN == wParam) //回车换行
	{
		if (pEdit->bMoreLine)
			Edit_CharEnter(hEle);
		//	XTRACEW(L"wchar=回车");
	}
	else
	{
		Edit_Char(hEle, wParam);
		//	XTRACEW(L"wchar=%s \n",ch);
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventKeyDown(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam)
{
	if (hEle != hEventEle)
		return FALSE;
	//XTRACE("keydown %d",wParam);
	switch (wParam)
	{
	case 46:  //Delete
		Edit_CharDeleteKey(hEle);
		break;
	case 36:  //Home
		//	MoveCaretBegin();
		break;
	case 35:  //End
		//	MoveCaretEnd();
		break;
	case VK_LEFT: //37:  //左
		Eidt_MouseCreatLeft(hEle); //移动插入符向左←
		break;
	case VK_UP: //38:  //上
		Eidt_MouseCreatTop(hEle);
		break;
	case VK_RIGHT: //39:  //右
		Eidt_MouseCreatRight(hEle);
		break;
	case VK_DOWN: //40:  //下
		Eidt_MouseCreatBottom(hEle);
		break;
	}
	return TRUE;
}

void Eidt_MouseCreatLeft(HELE hEle) //移动插入符向左←
{
	edit_ *pEdit = EDIT(hEle);

	if (pEdit->bDrawSelect) //取消文本选择
		pEdit->bDrawSelect = FALSE;

	if (0 == pEdit->column && 0 == pEdit->row)
		return;
	if (0 == pEdit->column) //移动到上一行
	{
		//TODO:...
		pEdit->row--;

		HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;//上一行
		pEdit->column = XStr_GetLength(hStr);
		pEdit->caretPt.x = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len;
		pEdit->caretPt.y -= pEdit->rowHeight;
		Edit_SetCaretPos(hEle);
		//Edit_ScrollVTop(hEle);
		Edit_ScrollV(hEle);
		//Edit_ScrollHRight(hEle);
		Edit_ScrollH(hEle);
	}
	else //插入符前移一个字符
	{
		HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString; //当前行
		wchar_t ch = XStr_GetAt(hStr, pEdit->column - 1);//前一个字符

		SIZE size;   //字符长度
		if (FALSE == pEdit->bPass)
		{
			HDC hdc = GetDC(NULL);
			HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32(hdc, &ch, 1, &size);
			SelectObject(hdc, hOldFont);
			ReleaseDC(NULL, hdc);
		}
		else
		{
			size.cx = pEdit->sizePass.cx;
		}

		pEdit->column--;

		pEdit->caretPt.x -= size.cx;
		Edit_SetCaretPos(hEle);

		//滚动视图
		Edit_ScrollH(hEle);

		XEle_RedrawEle(hEle);
	}
}

void Eidt_MouseCreatRight(HELE hEle)  //移动插入符 向右 →
{
	edit_ *pEdit = EDIT(hEle);
	if (pEdit->bDrawSelect) //取消文本选择
		pEdit->bDrawSelect = FALSE;

	HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString; //当前行
	if (pEdit->row == pEdit->rows && pEdit->column == XStr_GetLength(hStr))//如果插入符在末尾
	{
		return;
	}
	else if (pEdit->column == XStr_GetLength(hStr)) //换行
	{
		pEdit->row++;
		pEdit->column = 0;
		pEdit->caretPt.x = 0;
		pEdit->caretPt.y += pEdit->rowHeight;
		Edit_SetCaretPos(hEle);
		//滚动视图
		Edit_ScrollV(hEle);
		XSView_ScrollHPos(hEle, 0);
	}
	else //当前行
	{
		wchar_t ch = XStr_GetAt(hStr, pEdit->column);//前一个字符

		//字符长度
		SIZE size;
		if (FALSE == pEdit->bPass)
		{
			HDC hdc = GetDC(NULL);
			HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32(hdc, &ch, 1, &size);
			SelectObject(hdc, hOldFont);
			ReleaseDC(NULL, hdc);
		}
		else
		{
			size.cx = pEdit->sizePass.cx;
		}

		pEdit->caretPt.x += size.cx;
		pEdit->column++;
		Edit_SetCaretPos(hEle);
		XEle_RedrawEle(hEle);
		//滚动视图
		//Edit_ScrollHRight(hEle);
		Edit_ScrollH(hEle);
	}
}

void Eidt_MouseCreatTop(HELE hEle)    //移动插入符 向上 ↑
{
	edit_ *pEdit = EDIT(hEle);
	if (pEdit->bDrawSelect) //取消文本选择
		pEdit->bDrawSelect = FALSE;

	if (0 == pEdit->row)
		return;

	int lenx = pEdit->caretPt.x;
	int lenLast = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row - 1)->len;
	if (lenx > lenLast) //插入符X位置比上一行大
	{
		HSTRING hStrLast = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row - 1)->hString; //上一行
		pEdit->caretPt.x = lenLast;
		pEdit->column = XStr_GetLength(hStrLast);
	}

	pEdit->caretPt.y -= pEdit->rowHeight;
	pEdit->row--;
	Edit_SetCaretPos(hEle);
	//滚动视图
	//	Edit_ScrollVTop(hEle);
	Edit_ScrollV(hEle);
	Edit_ScrollH(hEle);
	XEle_RedrawEle(hEle);
}

void Eidt_MouseCreatBottom(HELE hEle) //移动插入符 向下 ↓
{
	edit_ *pEdit = EDIT(hEle);
	if (pEdit->bDrawSelect) //取消文本选择
		pEdit->bDrawSelect = FALSE;

	if (pEdit->row == pEdit->rows)
		return;

	int lenx = pEdit->caretPt.x;
	int lenNext = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row + 1)->len;
	if (lenx > lenNext) //插入符X位置比下一行大
	{
		HSTRING hStrNext = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row + 1)->hString;
		pEdit->caretPt.x = lenNext;
		pEdit->column = XStr_GetLength(hStrNext);
	}

	pEdit->caretPt.y += pEdit->rowHeight;
	pEdit->row++;
	Edit_SetCaretPos(hEle);
	//滚动视图
	Edit_ScrollV(hEle);
	Edit_ScrollH(hEle);
	XEle_RedrawEle(hEle);
}

void Edit_CreateCaret(HELE hEle)
{
	if (NULL == ((ele_*)hEle)->pWindow) //没有与窗口关联
		return;

	EDIT(hEle)->bCaretCreate = TRUE;

	//插入符
	XWnd_CreateCaret((HWINDOW)((ele_*)hEle)->pWindow, ((scrollView_*)hEle)->hView, EDIT(hEle)->caretWidth, EDIT(hEle)->rowHeight);

	XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow, TRUE);
	Edit_SetCaretPos(hEle);

	XEle_RedrawEle(hEle);
}

void Edit_SetCaretPos(HELE hEle)
{
	if (NULL == ((ele_*)hEle)->pWindow) //没有与窗口关联
		return;

	int viewPosx = XSView_GetHViewPos(hEle);
	int viewPosy = XSView_GetVViewPos(hEle);

	int x = EDIT(hEle)->caretPt.x + EDIT(hEle)->spacLeft +/*SCROLLVIEW(hEle)->left*/+viewPosx;
	int y = EDIT(hEle)->caretPt.y + EDIT(hEle)->spacTop +/*SCROLLVIEW(hEle)->top*/+viewPosy;

	XWnd_SetCaretPos((HWINDOW)((ele_*)hEle)->pWindow, x, y);
	/*
		//检测插入符显示范围
		int cx=SCROLLVIEW(hEle)->left+XSView_GetViewWidth(hEle);
		int cy=SCROLLVIEW(hEle)->top+XSView_GetViewHeight(hEle);

		if(x<cx && (y+((ele_*)hEle)->pWindow->caretHeight)<=cy)
		{
			if(FALSE==((ele_*)hEle)->pWindow->bCaretShow)
				XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow,TRUE);
			//XTRACE("x=%d,显示\n",x);
		}else
		{
			if(((ele_*)hEle)->pWindow->bCaretShow)
				XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow,FALSE);
			//XTRACE("x=%d,不显示\n",x);
		}*/
}

void Edit_TestDown(HELE hEle, POINT *pPt)
{
	edit_ *pEdit = EDIT(hEle);

	int posx = XSView_GetHViewPos(hEle);
	int posy = XSView_GetVViewPos(hEle);

	int downx = pPt->x - posx - EDIT(hEle)->spacLeft;//-SCROLLVIEW(hEle)->left;
	int downy = pPt->y - posy - EDIT(hEle)->spacTop;//-SCROLLVIEW(hEle)->top;

	//点击行号
	pEdit->row = downy / pEdit->rowHeight;
	if (pEdit->row > pEdit->rows)
		pEdit->row = pEdit->rows;
	else if (pEdit->row < 0)
		pEdit->row = 0;

	//当前行字符串
	HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;
	wchar_t *pStr = XStr_GetBuffer(hStr);
	//列
	int strCount = XStr_GetLength(hStr);//当前行字符数量
	if (strCount < 1)
	{
		pEdit->column = 0;
		pEdit->caretPt.x = 0;
		pEdit->caretPt.y = pEdit->rowHeight*pEdit->row;
	}
	else
	{
		int x = 0;
		SIZE size;
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
		int mouseX = downx;  //鼠标X坐标
		BOOL skip = FALSE;
		for (int i = 0; i < strCount; i++)
		{
			if (FALSE == pEdit->bPass)
			{
				GetTextExtentPoint32(hdc, pStr, 1, &size);
			}
			else
			{
				size.cx = pEdit->sizePass.cx;
			}
			if (mouseX < (x + size.cx / 2))
			{
				pEdit->column = i;
				skip = TRUE;
				break;
			}
			x += size.cx;
			pStr++;
		}
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

		if (FALSE == skip)
		{
			pEdit->column = strCount;
		}

		pEdit->caretPt.x = x;
		pEdit->caretPt.y = pEdit->rowHeight*pEdit->row;
	}
}

void Edit_AdjustViewSize(HELE hEle) //调整视图内容大小
{
	//设置视图内容大小
	int cx = EDIT(hEle)->spacLeft + 2;
	int cy = EDIT(hEle)->spacTop + 2;

	cx = cx + Array_GetAtEdit(EDIT(hEle)->hArrayEdit, EDIT(hEle)->maxLine)->len;
	if (FALSE == EDIT(hEle)->bMoreLine || EDIT(hEle)->bPass)
		cy = EDIT(hEle)->rowHeight;
	else
		cy = cy + (EDIT(hEle)->rows + 1)*EDIT(hEle)->rowHeight;

	XSView_SetSize(hEle, cx, cy);
}

void Edit_ScrollH(HELE hEle)   //向左拖到滚动条滚动,水平滚动
{
	int posx = EDIT(hEle)->caretPt.x + XSView_GetHViewPos(hEle) + EDIT(hEle)->spacLeft;
	if (posx < 0) //左滚动
	{
		//	int posx=EDIT(hEle)->caretPt.x+XSView_GetHViewPos(hEle)+EDIT(hEle)->spacLeft;
		int left = EDIT(hEle)->spacLeft;
		if (posx <= left)
		{
			int viewWidth = XSView_GetViewWidth(hEle);
			int pos = (EDIT(hEle)->caretPt.x + EDIT(hEle)->spacLeft) - viewWidth / 2;
			pos = pos / SCROLLVIEW(hEle)->sizeLine.cx;
			if (pos < 0)
				pos = 0;
			XSView_ScrollHPos(hEle, pos);
			//XTRACE("测试 滚动\n");
		}
	}
	else //右滚动
	{
		int viewWidth = XSView_GetViewWidth(hEle);
		int posx = EDIT(hEle)->caretPt.x + XSView_GetHViewPos(hEle) + EDIT(hEle)->spacLeft;
		if (posx >= viewWidth)
		{
			int pos = ((EDIT(hEle)->caretPt.x + EDIT(hEle)->spacLeft) - viewWidth) / SCROLLVIEW(hEle)->sizeLine.cx;

			XSView_ScrollHPos(hEle, pos + 1);
		}
	}
}


/*
void Edit_ScrollVTop(HELE hEle)
{
int posy=EDIT(hEle)->caretPt.y+XSView_GetVViewPos(hEle)+EDIT(hEle)->spacTop;
int t2=EDIT(hEle)->spacTop;
if(posy<=t2)
{
int viewHeight=XSView_GetViewHeight(hEle);
int pos=(EDIT(hEle)->caretPt.y+EDIT(hEle)->spacTop)-viewHeight/2;
if(pos<0)
pos=0;
XSView_ScrollVPos(hEle,pos);
}
}*/

void Edit_ScrollV(HELE hEle)
{
	int posy = EDIT(hEle)->caretPt.y + XSView_GetVViewPos(hEle) + EDIT(hEle)->spacTop;
	if (posy > 0) //向下滚动
	{
		int viewHeight = XSView_GetViewHeight(hEle);
		posy = (EDIT(hEle)->row + 1) * EDIT(hEle)->rowHeight;
		posy = posy + EDIT(hEle)->spacTop;
		int top = posy - XSView_GetVViewPos(hEle);
		if (top >= viewHeight)
		{
			int pos = (posy - viewHeight) / SCROLLVIEW(hEle)->sizeLine.cy;
			XSView_ScrollVPos(hEle, pos + 1);
			//XTRACE("回车 滚动... \n");
		}
	}
	else //向上滚动
	{
		int top = EDIT(hEle)->spacTop;
		if (posy <= top)
		{
			int viewHeight = XSView_GetViewHeight(hEle);
			int pos = (EDIT(hEle)->caretPt.y + EDIT(hEle)->spacTop) - viewHeight / 2;
			if (pos < 0)
				pos = 0;
			XSView_ScrollVPos(hEle, pos);
		}
	}
}

void Edit_Char(HELE hEle, wchar_t ch)
{
	edit_ *pEdit = EDIT(hEle);

	if (pEdit->bNumber) //数子 48 - 57
	{
		if (ch < 48 || ch>57)
			return;
	}

	if (pEdit->bDrawSelect)
	{
		Edit_DeleteSelectText(hEle); //删除选择文本
	}

	SIZE size;   //字符长度
	if (FALSE == pEdit->bPass)
	{
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
		GetTextExtentPoint32(hdc, &ch, 1, &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

	}
	else //密码框
	{
		size.cx = pEdit->sizePass.cx;
	}

	HSTRING hString = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;
	XStr_InsertChar(hString, pEdit->column, ch);
	pEdit->column++;

	pEdit->caretPt.x += size.cx;
	Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len += size.cx;
	if (pEdit->maxLine > pEdit->rows)
	{
		pEdit->maxLine = 0;
	}

	//检查最长的行
	if (pEdit->row != pEdit->maxLine)
	{
		if (Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len > Array_GetAtEdit(pEdit->hArrayEdit, pEdit->maxLine)->len)
		{
			pEdit->maxLine = pEdit->row;
		}
	}

	//设置视图内容大小
	if (pEdit->row == pEdit->maxLine)
	{
		Edit_AdjustViewSize(hEle);
	}

	//向右拖到滚动条滚动,水平滚动
	//Edit_ScrollHRight(hEle);
	Edit_ScrollH(hEle);

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);

	XEle_RedrawEle(hEle);
}

void Edit_CharEnter(HELE hEle)
{
	edit_ *pEdit = EDIT(hEle);

	if (pEdit->bDrawSelect)
	{
		Edit_DeleteSelectText(hEle); //删除选择文本
	}

	HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;
	//当前行字符串
	wchar_t *pStr = XStr_GetBuffer(hStr);
	wchar_t *pStrAdd = pStr + pEdit->column;
	int strLen = XStr_GetLength(hStr);

	editStrList_ *pNew = (editStrList_*)malloc(sizeof(editStrList_));
	pNew->hString = XStr_Create();
	pNew->len = 0;

	XStr_SetString(pNew->hString, pStrAdd);

	//添加一行
	XArray_insert(pEdit->hArrayEdit, pNew, pEdit->row + 1);

	//新行字符串长度
	SIZE size;   //字符长度
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	GetTextExtentPoint32(hdc, pStrAdd, strLen - pEdit->column, &size);
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len -= size.cx;
	pNew->len = size.cx;

	XStr_SetLength(hStr, pEdit->column);

	//检查最长行
	int maxcx = 0;
	for (int i = 0; i <= (pEdit->rows + 1); i++)
	{
		if (Array_GetAtEdit(pEdit->hArrayEdit, i)->len > maxcx)
		{
			maxcx = Array_GetAtEdit(pEdit->hArrayEdit, i)->len;
			pEdit->maxLine = i;
		}
	}

	pEdit->row++;
	pEdit->rows++;
	pEdit->column = 0;

	//插入符
	pEdit->caretPt.x = 0;
	pEdit->caretPt.y += pEdit->rowHeight;

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);

	//向下拖动滚动条,垂直滚动
	Edit_ScrollV(hEle);

	XSView_ScrollHPos(hEle, 0);  //滚动左侧

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);

	XEle_RedrawEle(hEle);
}

void Edit_CharBackspaceEnter(HELE hEle) //退格回车
{
	edit_ *pEdit = EDIT(hEle);
	//当前行
	HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;

	if (0 == XStr_GetLength(hStr)) //空行
	{
		editStrList_ *pDel = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row);
		//pEdit->pStringList.Delete(pDel);
		XArray_DeleteIndex(pEdit->hArrayEdit, pEdit->row);
		XStr_Destroy(pDel->hString);
		free(pDel);

		pEdit->row--;
		pEdit->rows--;

		hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;
		pEdit->column = XStr_GetLength(hStr);

		pEdit->caretPt.x = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len;
		pEdit->caretPt.y = pEdit->row * pEdit->rowHeight;

		//最长行检查
		if (pEdit->maxLine > pEdit->row)
		{
			pEdit->maxLine--;
		}
	}
	else //非空行
	{
		//上一行
		HSTRING hLastRow = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row - 1)->hString;
		pEdit->column = XStr_GetLength(hLastRow);//列

		//插入符移动到上一行末尾
		pEdit->caretPt.x = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row - 1)->len;
		pEdit->caretPt.y = (pEdit->row - 1) * pEdit->rowHeight;

		XStr_AddString(hLastRow, XStr_GetBuffer(hStr)); //将当前行字符加添到上一行

		//上一行字符显示长度增加
		Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row - 1)->len += Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len;

		//删除当前行
		editStrList_ *pDel = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row);
		XArray_DeleteIndex(pEdit->hArrayEdit, pEdit->row);
		XStr_Destroy(pDel->hString);
		free(pDel);

		pEdit->row--;
		pEdit->rows--;

		//最长行检查
		int maxcx = 0;
		pEdit->maxLine = 0;
		for (int i = 0; i <= pEdit->rows; i++)
		{
			if (Array_GetAtEdit(pEdit->hArrayEdit, i)->len > maxcx)
			{
				maxcx = Array_GetAtEdit(pEdit->hArrayEdit, i)->len;
				pEdit->maxLine = i;
			}
		}
	}

	//设置视图内容大小
	Edit_AdjustViewSize(hEle);

	//向左拖到滚动条
	//Edit_ScrollHRight(hEle);
	Edit_ScrollH(hEle);

	Edit_SetCaretPos(hEle);
	XEle_RedrawEle(hEle);
}

//Delete键
void Edit_CharDeleteKey(HELE hEle)
{
	//	edit_ *pEdit=EDIT(hEle);
}

void Edit_CharBackspace(HELE hEle)
{
	edit_ *pEdit = EDIT(hEle);

	if (pEdit->bDrawSelect) //删除选择内容
	{
		if (Edit_DeleteSelectText(hEle))
			Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
		XEle_RedrawEle(hEle);
		return;
	}

	if (0 == pEdit->column && 0 == pEdit->row)
		return;

	//删除回车
	if (0 == pEdit->column)
	{
		Edit_CharBackspaceEnter(hEle);
		Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);
		return;
	}

	//当前行
	HSTRING hStr = Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->hString;

	wchar_t ch = XStr_GetAt(hStr, pEdit->column - 1); //要删除的字符
	XStr_DeleteLength(hStr, pEdit->column - 1, 1); //删除字符

	//新行字符长度
	SIZE size;   //字符长度
	if (FALSE == pEdit->bPass)
	{
		HDC hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
		GetTextExtentPoint32(hdc, &ch, 1, &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);
	}
	else
	{
		size.cx = pEdit->sizePass.cx;
	}

	Array_GetAtEdit(pEdit->hArrayEdit, pEdit->row)->len -= size.cx;
	/////////////
	pEdit->column--;

	//最长行检查
	if (pEdit->row == pEdit->maxLine)
	{
		int maxcx = 0;
		for (int i = 0; i <= pEdit->rows; i++)
		{
			if (Array_GetAtEdit(pEdit->hArrayEdit, i)->len > maxcx)
			{
				maxcx = Array_GetAtEdit(pEdit->hArrayEdit, i)->len;
				pEdit->maxLine = i;
			}
		}
	}

	pEdit->caretPt.x -= size.cx;

	//设置视图内容大小
	if (pEdit->row == pEdit->maxLine)
	{
		Edit_AdjustViewSize(hEle);
	}

	//向右拖到滚动条
	Edit_ScrollH(hEle);

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle, XE_EDIT_CHANGE, 0, 0);

	XEle_RedrawEle(hEle);
}

void Edit_DrawSelect(HELE hEle, HDRAW hDraw) //会在选择文本背景
{
	if (EDIT(hEle)->bDrawSelect)
	{
		HBRUSH hBrush = NULL;
		if (EDIT(hEle)->bCaretCreate)
			hBrush = XDraw_CreateSolidBrush_(hDraw, EDIT(hEle)->selColor);//RGB(83,132,213));
		else
			hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(200, 200, 200));

		edit_ *pEdit = EDIT(hEle);
		//当前行
		if (pEdit->downRow == pEdit->endRow)
		{
			int top = pEdit->spacTop;//+XSView_GetSpacingTop(hEle);
			int left = pEdit->spacLeft;//+XSView_GetSpacingLeft(hEle);
			RECT rc;
			if (pEdit->downX < pEdit->endX)
			{
				rc.left = left + pEdit->downX;
				rc.top = top + pEdit->downRow*pEdit->rowHeight;
				rc.right = left + pEdit->endX;
				rc.bottom = rc.top + pEdit->rowHeight;
			}
			else
			{
				rc.left = left + pEdit->endX;
				rc.top = top + pEdit->downRow*pEdit->rowHeight;
				rc.right = left + pEdit->downX;
				rc.bottom = rc.top + pEdit->rowHeight;
			}
			XDraw_FillRect_(hDraw, &rc, hBrush);
		}
		else //多行
		{
			if (pEdit->downRow < pEdit->endRow) //向下选择
			{
				Edit_DrawSelectBottom(hEle, hDraw, hBrush);

			}
			else //向上选择
			{
				Edit_DrawSelectTop(hEle, hDraw, hBrush);
			}
		}
	}
}


void Edit_DrawSelectBottom(HELE hEle, HDRAW hDraw, HBRUSH hBrush)
{
	edit_ *pEdit = EDIT(hEle);
	RECT rc;
	int top = pEdit->spacTop;//+XSView_GetSpacingTop(hEle);
	int left = pEdit->spacLeft;//+XSView_GetSpacingLeft(hEle);
	//第一行
	rc.left = left + pEdit->downX;
	rc.top = top + pEdit->downRow*pEdit->rowHeight;
	rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit, pEdit->downRow)->len;
	rc.bottom = rc.top + pEdit->rowHeight;
	XDraw_FillRect_(hDraw, &rc, hBrush);

	//最后行
	rc.left = left;
	rc.top = top + pEdit->endRow*pEdit->rowHeight;
	rc.right = left + pEdit->endX;
	rc.bottom = rc.top + pEdit->rowHeight;
	XDraw_FillRect_(hDraw, &rc, hBrush);

	//中间行
	int rows = pEdit->endRow - pEdit->downRow;
	if (rows > 1)
	{
		for (int i = 1; i < rows; i++)
		{
			rc.left = left;
			rc.top = top + (pEdit->downRow + i)*pEdit->rowHeight;
			rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit, pEdit->downRow + i)->len;
			rc.bottom = rc.top + pEdit->rowHeight;
			XDraw_FillRect_(hDraw, &rc, hBrush);
		}
	}
}

void Edit_DrawSelectTop(HELE hEle, HDRAW hDraw, HBRUSH hBrush)
{
	edit_ *pEdit = EDIT(hEle);
	RECT rc;
	int top = pEdit->spacTop;//+XSView_GetSpacingTop(hEle);
	int left = pEdit->spacLeft;//+XSView_GetSpacingLeft(hEle);
	//第一行
	rc.left = left + pEdit->endX;
	rc.top = top + pEdit->endRow*pEdit->rowHeight;
	rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit, pEdit->endRow)->len;
	rc.bottom = rc.top + pEdit->rowHeight;
	XDraw_FillRect_(hDraw, &rc, hBrush);

	//最后行
	rc.left = left;
	rc.top = top + pEdit->downRow*pEdit->rowHeight;
	rc.right = left + pEdit->downX;
	rc.bottom = rc.top + pEdit->rowHeight;
	XDraw_FillRect_(hDraw, &rc, hBrush);

	//中间行
	int rows = pEdit->downRow - pEdit->endRow;
	if (rows > 1)
	{
		for (int i = 1; i < rows; i++)
		{
			rc.left = left;
			rc.top = top + (pEdit->endRow + i)*pEdit->rowHeight;
			rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit, pEdit->endRow + i)->len;
			rc.bottom = rc.top + pEdit->rowHeight;
			XDraw_FillRect_(hDraw, &rc, hBrush);
		}
	}
}

BOOL CALLBACK Edit_OnEventHScrollView(HELE hEle, HELE hEventEle, int pos)
{
	if (hEle != hEventEle)
		return FALSE;
	if (EDIT(hEle)->bCaretCreate)
	{
		Edit_SetCaretPos(hEle);
		//XTRACE("x=%d,y=%d \n",XSView_GetHViewPos(hEle),XSView_GetVViewPos(hEle));
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventVScrollView(HELE hEle, HELE hEventEle, int pos)
{
	if (hEle != hEventEle)
		return FALSE;

	//调整插入符位置, 超出范围隐藏
	if (EDIT(hEle)->bCaretCreate)
	{
		Edit_SetCaretPos(hEle);
		//XTRACE("x=%d,y=%d \n",XSView_GetHViewPos(hEle),XSView_GetVViewPos(hEle));
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventSetFocus(HELE hEle, HELE hEventEle) //获得焦点
{
	if (hEle != hEventEle)
		return FALSE;
	//XTRACE("edit 获得焦点\n");

	if (FALSE == EDIT(hEle)->bCaretCreate)
	{
		Edit_CreateCaret(hEle);
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventKillFocus(HELE hEle, HELE hEventEle) //失去焦点
{
	//XTRACE("edit 失去焦点\n");
	if (hEle != hEventEle)
		return FALSE;

	if (EDIT(hEle)->bCaretCreate)
	{
		EDIT(hEle)->bCaretCreate = FALSE;
		XWnd_DestroyCaret((HWINDOW)((ele_*)hEle)->pWindow);
		XEle_RedrawEle(hEle);
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventMenuSelect(HELE hEle, HELE hEventEle, int id) //菜单选择事件
{
	if (hEle == hEventEle)
	{
		switch (id)
		{
		case IDM_CLIP: XEdit_Menu_Cut(hEle); //XTRACE("剪切\n");
			break;
		case IDM_COPY: XEdit_Menu_Copy(hEle); //XTRACE("复制\n");
			break;
		case IDM_PASTE: XEdit_Menu_Paste(hEle); //XTRACE("粘贴\n");
			break;
		case IDM_DELETE: XEdit_Menu_Clear(hEle); //XTRACE("删除\n");
			break;
		case IDM_SELECTALL: XEdit_Menu_SelectAll(hEle); //XTRACE("全选\n");
			break;
		case IDM_DELETEALL: XEdit_Menu_DeleteAll(hEle); //XTRACE("清空\n");
			break;
		}
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventSize(HELE hEle, HELE hEventEle)  //元素大小位置改变
{
	if (hEle != hEventEle)
		return FALSE;

	Edit_AdjustViewSize(hEle);
	return FALSE;
}

BOOL CALLBACK Edit_OnEventSetFont(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;
	//XTRACE("Edit font changed \n");
	edit_  *pObject = (edit_*)hEle;

	//改变字体
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOld = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	EDIT(hEle)->rowHeight = tm.tmHeight; //行高

	SIZE size;
	GetTextExtentPoint32W(hdc, L"*", 1, &size);
	EDIT(hEle)->sizePass.cx = size.cx;
	EDIT(hEle)->sizePass.cy = size.cy;

	SelectObject(hdc, hOld);
	ReleaseDC(NULL, hdc);

	int row = pObject->row;
	int column = pObject->column;

	////重新加载内容/////////////////////////////////////
	int len = XEdit_GetTextLength(hEle);
	if (len > 0)
	{
		wchar_t *temp = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
		temp[len] = 0;

		XEdit_GetText(hEle, temp, len);
		XEdit_DeleteAll(hEle);

		XEdit_SetText(hEle, temp);
		free(temp);
	}

	//调整插入符
	if (EDIT(hEle)->bCaretCreate)
	{
		XWnd_DestroyCaret((HWINDOW)((ele_*)hEle)->pWindow);
		Edit_CreateCaret(hEle);

		XEdit_SetPos(hEle, row, column);
	}

	return FALSE;
}
///@}