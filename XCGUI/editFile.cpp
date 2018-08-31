#include "StdAfx.h"


HELE WINAPI XEditFile_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	editFile_ *pObj = (editFile_*)malloc(sizeof(editFile_));
	if (pObj)
	{
		memset(pObj, 0, sizeof(editFile_));

		EditFile_Init((HELE)pObj, x, y, cx, cy, XC_EDITFILE, hParent);
		return (HELE)pObj;
	}
	return NULL;
}


void EditFile_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Edit_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_EDITFILE);

	editFile_ *pEditFile = (editFile_*)hEle;
	pEditFile->bEdit = TRUE;
	pEditFile->heights = 0;
	pEditFile->bOpenBrowseFile = FALSE;
	pEditFile->hType = XStr_Create();
	pEditFile->hDefaultFile = XStr_Create();
	XSView_SetSpacing(hEle, 2, 2, cy - 2, 2);
	EditFile_Adjust(hEle);

	XStr_SetString(pEditFile->hType, L"All Files(*.*)|*.*|Text Files(*.txt)|*.txt|");

	XEle_RegisterMessage(hEle, XM_PAINT, EditFile_OnDraw);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, EditFile_OnMouseMove);

	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, EditFile_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, EditFile_OnLButtonUp);

	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, EditFile_OnEventMouseLeave);

	XEle_RegisterMessage(hEle, XM_RBUTTONDOWN, EditFile_OnRButtonDown);
	XEle_RegisterMessage(hEle, XM_RBUTTONUP, EditFile_OnRButtonUp);

	XEle_RegisterEvent(hEle, XE_DESTROY, EditFile_OnDestroy);
	XEle_RegisterEvent(hEle, XE_SIZE, EditFile_OnEventSize);
	XEle_RegisterEvent(hEle, XE_SETFOCUS, EditFile_OnEventSetFocus);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, EditFile_OnEventKillFocus);
}

//"All Files(*.*)|*.*|Text Files(*.txt)|*.txt|"
void WINAPI XEditFile_SetOpenFileType(HELE hEle, wchar_t *pType) //设置打开文件类型
{
	IsEditFileDebug(hEle, __FUNCTION__);
	XStr_SetString(((editFile_*)hEle)->hType, pType);
}

void WINAPI XEditFile_SetDefaultFile(HELE hEle, wchar_t *pFile) //设置默认目录
{
	IsEditFileDebug(hEle, __FUNCTION__);
	XStr_SetString(((editFile_*)hEle)->hDefaultFile, pFile);
}

void WINAPI XEditFile_SetRelativeDir(HELE hEle, wchar_t *pDir) //设置相对路径
{
	IsEditFileDebug(hEle, __FUNCTION__);
	if (pDir)
	{
		if (NULL == ((editFile_*)hEle)->hRelativeDir)
			((editFile_*)hEle)->hRelativeDir = XStr_Create();
		XStr_SetString(((editFile_*)hEle)->hRelativeDir, pDir);
	}
	else
	{
		if (((editFile_*)hEle)->hRelativeDir)
		{
			XStr_Destroy(((editFile_*)hEle)->hRelativeDir);
			((editFile_*)hEle)->hRelativeDir = NULL;
		}
	}
}

void CALLBACK EditFile_OnDestroy(HELE hEle) //销毁
{
	editFile_ *pObject = (editFile_*)hEle;
	if (pObject->hType) XStr_Destroy(pObject->hType);
	if (pObject->hDefaultFile) XStr_Destroy(pObject->hDefaultFile);
	if (((editFile_*)hEle)->hRelativeDir) XStr_Destroy(((editFile_*)hEle)->hRelativeDir);
	if (pObject->hImage_stay) XImage_Destroy(pObject->hImage_stay);
	if (pObject->hImage_down) XImage_Destroy(pObject->hImage_down);
}

void EditFile_Adjust(HELE hEle)
{
	//调整下拉按钮
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	editFile_ *pObject = (editFile_*)hEle;

	pObject->button_.rcButton.right = rect.right;
	pObject->button_.rcButton.left = rect.right - XSView_GetSpacingRight(hEle);
	pObject->button_.rcButton.top = XSView_GetSpacingTop(hEle) + 1;
	pObject->button_.rcButton.bottom = rect.bottom - XSView_GetSpacingBottom(hEle) - 1;
}

BOOL CALLBACK EditFile_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	editFile_ *pObject = (editFile_*)hEle;
	if (FALSE == pObject->bEdit)
	{
		pObject->button_.state = STATE_DOWN;
		//XEle_SetFocus(hEle,TRUE);
		//XEle_RedrawEle(hEle);

		//弹出
		EditFile_BrowseFile(hEle);
		return TRUE;
	}
	else
	{
		if (PtInRect(&pObject->button_.rcButton, *pPt))
		{
			pObject->button_.state = STATE_DOWN;
			//XEle_SetFocus(hEle,TRUE);
			//XEle_RedrawEle(hEle);

			//弹出
			EditFile_BrowseFile(hEle);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	editFile_ *pObject = (editFile_*)hEle;
	//	if(NULL==pObject->hPopupWnd)
	//	{
	pObject->button_.state = STATE_STAY;
	XEle_RedrawEle(hEle);
	//	}

	if (FALSE == pObject->bEdit)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	editFile_ *pObject = (editFile_*)hEle;
	//	if(NULL==pObject->hPopupWnd)
	//	{
	if (STATE_STAY != pObject->button_.state)
	{
		pObject->button_.state = STATE_STAY;
		XEle_RedrawEle(hEle);
	}
	//	}

	if (FALSE == pObject->bEdit) //不可以编辑
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CALLBACK EditFile_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	if (FALSE == ((editFile_*)hEle)->bEdit) //不可以编辑
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	if (FALSE == ((editFile_*)hEle)->bEdit) //不可以编辑
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		editFile_ *pObject = (editFile_*)hEle;
		//		if(NULL==pObject->hPopupWnd)
		//		{
		if (STATE_LEAVE != pObject->button_.state)
		{
			if (FALSE == XEle_IsFocus(hEle))
			{
				pObject->button_.state = STATE_LEAVE;
				XEle_RedrawEle(hEle);
			}
		}
		//		}
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnEventKillFocus(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		editFile_ *pObject = (editFile_*)hEle;
		//		if(NULL==pObject->hPopupWnd)
		//		{
		if (STATE_LEAVE != pObject->button_.state)
		{
			pObject->button_.state = STATE_LEAVE;
			XEle_RedrawEle(hEle);
		}
		//		}
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnEventSetFocus(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (FALSE == ((editFile_*)hEle)->bEdit) //不可以编辑
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK EditFile_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		//调整下拉按钮
		EditFile_Adjust(hEle);
	}
	return FALSE;
}


BOOL CALLBACK EditFile_OnDraw(HELE hEle, HDRAW hDraw)
{
	EditFile_DrawBk(hEle, hDraw);
	return TRUE;
}

//绘制背景
void EditFile_DrawBk(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	editFile_ *pObject = (editFile_*)hEle;
	switch (pObject->button_.state)
	{
	case STATE_LEAVE:
	{
		if (SCROLLVIEW(hEle)->hImage_bk)
		{
			XDraw_HImageSuper_(hDraw, SCROLLVIEW(hEle)->hImage_bk, &rect);
		}
		else //绘制下拉按钮
			EditFile_OnDrawButton(hEle, hDraw);
	}break;
	case STATE_STAY:
	{
		if (pObject->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw, pObject->hImage_stay, &rect);
		}
		else //绘制下拉按钮
			EditFile_OnDrawButton(hEle, hDraw);
	}
	break;
	case STATE_DOWN:
	{
		if (pObject->hImage_down)
		{
			XDraw_HImageSuper_(hDraw, pObject->hImage_down, &rect);
		}
		else //绘制下拉按钮
			EditFile_OnDrawButton(hEle, hDraw);
	}
	break;
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
			DeleteObject(hPen);

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

			//	SelectObject(hdc,hOld);
			//	DeleteObject(hPen2);
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
			//SelectObject(hdc,hOld);
			//DeleteObject(hPen);
		}
	}
}

BOOL CALLBACK EditFile_OnDrawButton(HELE hEle, HDRAW hDraw) //绘制下拉按钮
{
	editFile_ *pObject = (editFile_*)hEle;
	RECT rect = pObject->button_.rcButton;
	rect.right -= 3;

	switch (pObject->button_.state)
	{
	case STATE_LEAVE:
	{
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		//DeleteObject(hBrush);

		int centerX = rect.left + (rect.right - rect.left) / 2;
		int centerY = rect.top + (rect.bottom - rect.top) / 2;
		XDraw_SetPixel_(hDraw, centerX - 2, centerY, RGB(130, 130, 130));
		XDraw_SetPixel_(hDraw, centerX, centerY, RGB(130, 130, 130));
		XDraw_SetPixel_(hDraw, centerX + 2, centerY, RGB(130, 130, 130));
	}
	break;
	case STATE_STAY:
	{
		RECT rcBer = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(200, 200, 200));
		XDraw_FrameRect_(hDraw, &rcBer, hBrush1);
		//DeleteObject(hBrush1);

		//按钮边框
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rect, hBrush2);
		//DeleteObject(hBrush2);

		int centerX = rect.left + (rect.right - rect.left) / 2;
		int centerY = rect.top + (rect.bottom - rect.top) / 2;
		XDraw_SetPixel_(hDraw, centerX - 2, centerY, RGB(130, 130, 130));
		XDraw_SetPixel_(hDraw, centerX, centerY, RGB(130, 130, 130));
		XDraw_SetPixel_(hDraw, centerX + 2, centerY, RGB(130, 130, 130));
	}
	break;
	case STATE_DOWN:
	{
		RECT rcBer = { rect.left + 1,rect.top + 1,rect.right - 1,rect.bottom - 1 };
		HBRUSH hBrush1 = XDraw_CreateSolidBrush_(hDraw, RGB(200, 200, 200));
		XDraw_FrameRect_(hDraw, &rcBer, hBrush1);
		//DeleteObject(hBrush1);

		//按钮边框
		HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
		XDraw_FrameRect_(hDraw, &rect, hBrush2);
		//DeleteObject(hBrush2);

		int centerX = rect.left + (rect.right - rect.left) / 2 + 1;
		int centerY = rect.top + (rect.bottom - rect.top) / 2 + 1;
		XDraw_SetPixel_(hDraw, centerX - 2, centerY, RGB(130, 130, 130));
		XDraw_SetPixel_(hDraw, centerX, centerY, RGB(130, 130, 130));
		XDraw_SetPixel_(hDraw, centerX + 2, centerY, RGB(130, 130, 130));
	}
	break;
	}
	return TRUE;
}

void EditFile_BrowseFile(HELE hEle) //浏览文件
{
	editFile_ *pObject = (editFile_*)hEle;
	if (pObject->bOpenBrowseFile) return;

	wchar_t *pType = XStr_GetBuffer(pObject->hType);
	if (NULL == pType)
	{
		XTRACE("空的文件类型字符串");
		return;
	}
	wchar_t TYPE[MAX_PATH] = { 0 };

	int len = wcslen(pType);
	if (len >= MAX_PATH)
	{
		XTRACE("文件类型字符串太长");
		return;
	}
	memcpy(TYPE, pType, len*(sizeof(wchar_t)));

	for (int i = 0; i < len; i++)
	{
		if (L'|' == TYPE[i])
			TYPE[i] = '\0';
	}

	pObject->bOpenBrowseFile = TRUE;

	OPENFILENAME ofn;
	wchar_t szFile[MAX_PATH] = { 0 };

	len = XStr_GetLength(pObject->hDefaultFile);
	if (len > 0 && len < MAX_PATH)
		wmemcpy(szFile, XStr_GetBuffer(pObject->hDefaultFile), len);

	wchar_t path[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, path);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TYPE;// L"images(*.img)\0*.png;*.jpg;*.ico;*.bmp\0\0";// TYPE; //文件类型
	ofn.nFilterIndex = 1;    //定义首选项是哪一个
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.hwndOwner = XEle_GetHWnd(hEle);
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		//	MessageBox(NULL,szFile,L"123",0);

			//转换为相对路径
		if (pObject->hRelativeDir)
		{
			wchar_t *pRelativeDir = XStr_GetBuffer(pObject->hRelativeDir);
			if (pRelativeDir)
			{
				wchar_t tempW[MAX_PATH] = { 0 };
				if (TRUE == PathRelativePathTo(tempW, pRelativeDir, FILE_ATTRIBUTE_DIRECTORY, szFile, FILE_ATTRIBUTE_NORMAL))
				{
					wcscpy_s(szFile, tempW);
				}
			}
		}
		XEdit_SetText(hEle, szFile);
	}

	pObject->bOpenBrowseFile = FALSE;

	BOOL  res = SetCurrentDirectory(path);
	XEle_RedrawEle(hEle);
}
