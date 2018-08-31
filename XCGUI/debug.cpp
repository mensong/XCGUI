/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#ifdef _DEBUG

//句柄错误检查提示
void DebugBox_CheckHandle(char *pFunName, char *pHandle)
{
	char buf[MAX_PATH] = { 0 };
	sprintf_s(buf, MAX_PATH, "在API:%s()中,[%s]输入句柄可能无效", pFunName, pHandle);

	XTRACE(buf);
	XTRACE("\n");
	MessageBoxA(NULL, buf, "炫彩界面库-错误提示!", MB_OK);
}

void AddTypeDebug(HXCGUI hXCGUI, int type)
{
	object_*  pObject = (object_*)hXCGUI;

	object_type_  *pNew = (object_type_*)malloc(sizeof(object_type_));
	pNew->type = type;
	pNew->pNext = NULL;
	if (NULL == pObject->pTypeList)
	{
		pObject->pTypeList = pNew;
	}
	else
	{
		pNew->pNext = pObject->pTypeList;
		pObject->pTypeList = pNew;
	}
}

void IsWindowDebug(HWINDOW hWindow, char *pFunName)
{
	object_type_  *pNode = ((object_*)hWindow)->pTypeList;
	while (pNode)
	{
		if (XC_WINDOW == pNode->type)
			return;
		pNode = pNode->pNext;
	}

	DebugBox_CheckHandle(pFunName, "XC_WINDOW");
	exit(0);
}

void IsModalWindowDebug(HWINDOW hWindow, char *pFunName) //已处理
{
	object_type_  *pNode = ((object_*)hWindow)->pTypeList;
	while (pNode)
	{
		if (XC_MODALWINDOW == pNode->type)
			return;
		pNode = pNode->pNext;
	}

	DebugBox_CheckHandle(pFunName, "XC_MODALWINDOW");
	exit(0);
}

void IsFrameWindowDebug(HWINDOW hWindow, char *pFunName) //已处理
{
	object_type_  *pNode = ((object_*)hWindow)->pTypeList;
	while (pNode)
	{
		if (XC_FRAMEWND == pNode->type)
			return;
		pNode = pNode->pNext;
	}

	DebugBox_CheckHandle(pFunName, "XC_FRAMEWND");
	exit(0);
}

void IsEleDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_ELE == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_ELE");
	exit(0);
}

void IsButtonDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_BUTTON == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_BUTTON");
	exit(0);
}

void IsCheckDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_CHECK == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_CHECK");
	exit(0);
}

void IsRadioDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_RADIO == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_RADIO");
	exit(0);
}

void IsEditDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_EDIT == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_EDIT");
	exit(0);
}

void IsComboBoxDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_COMBOBOX == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_COMBOBOX");
	exit(0);
}

void IsScrollBarDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_SCROLLBAR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_SCROLLBAR");
	exit(0);
}

void IsScrollViewDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_SCROLLVIEW == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_SCROLLVIEW");
	exit(0);
}

void IsListDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_LIST == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_LIST");
	exit(0);
}

void IsListBoxDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_LISTBOX == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_LISTBOX");
	exit(0);
}

void IsTreeDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_TREE == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_TREE");
	exit(0);
}

void IsMenuBarDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_MENUBAR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_MENUBAR");
	exit(0);
}

void IsPropertyPageDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_PROPERTYPAGE == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_PROPERTYPAGE");
	exit(0);
}

void IsSliderDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_SLIDERBAR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_SLIDERBAR");
	exit(0);
}

void IsProgressBarDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_PROGRESSBAR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_PROGRESSBAR");
	exit(0);
}

void IsToolBarDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_TOOLBAR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_TOOLBAR");
	exit(0);
}

void IsToolBarBtnDebug(HELE hEle, char *pFunName) //已处理
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_TOOLBAR_BUTTON == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_TOOLBAR_BUTTON");
	exit(0);
}

void IsStaticDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_STATIC == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_STATIC");
	exit(0);
}

void IsGroupBoxDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_GROUPBOX == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_GROUPBOX");
	exit(0);
}

void IsPictureDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_PICTURE == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_ELE");
	exit(0);
}

void IsMonthCalDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_MONTHCAL == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_MONTHCAL");
	exit(0);
}

void IsDateTimeDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_DATETIME == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_DATETIME");
	exit(0);
}

void IsPGridDebug(HELE hEle, char *pFunName)  //属性网格
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_PROPERTYGRID == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_PROPERTYGRID");
	exit(0);
}

void IsChooseColorDebug(HELE hEle, char *pFunName)  //颜色选择
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_CHOOSECOLOR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_CHOOSECOLOR");
	exit(0);
}

void IsTextLinkDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_TEXTLINK == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_TEXTLINK");
	exit(0);
}

void IsTabBarDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_TABBAR == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_TABBAR");
	exit(0);
}

void IsGifDebug(HELE hEle, char *pFunName)  //GIF
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_GIF == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_GIF");
	exit(0);
}

void IsListViewDebug(HELE hEle, char *pFunName)  //ListView
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_LISTVIEW == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_LISTVIEW");
	exit(0);
}

void IsEditFileDebug(HELE hEle, char *pFunName)  //EditFile
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_EDITFILE == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_EDITFILE");
	exit(0);
}

void IsPaneDebug(HELE hEle, char *pFunName)
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_PANE == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_PANE");
	exit(0);
}
void IsRichEditDebug(HELE hEle, char *pFunName) //RichEdit
{
	if (Resource_IsHELE(hEle))
	{
		object_type_  *pNode = ((object_*)hEle)->pTypeList;
		while (pNode)
		{
			if (XC_RICHEDIT == pNode->type)
				return;
			pNode = pNode->pNext;
		}
	}

	DebugBox_CheckHandle(pFunName, "XC_RICHEDIT");
	exit(0);
}

void IsArrayDebug(HARRAY hArray, char *pFunName)
{
	if (hArray && (XC_ARRAY == *(UINT*)hArray))
		return;

	DebugBox_CheckHandle(pFunName, "XC_ARRAY");
	exit(0);
}

void IsDrawDebug(HDRAW hDraw, char *pFunName)
{
	if (hDraw && (XC_HDRAW == *(UINT*)hDraw))
		return;

	DebugBox_CheckHandle(pFunName, "XC_HDRAW");
	exit(0);
}

void IsStringDeBug(HSTRING hString, char *pFunName)
{
	if (hString && (XC_STRING == *(UINT*)hString))
		return;

	DebugBox_CheckHandle(pFunName, "XC_STRING");
	exit(0);
}

void IsImageListDebug(HXCGUI hImageList, char *pFunName) //已处理
{
	if (hImageList && (XC_IMAGELIST == *(UINT*)hImageList))
		return;

	DebugBox_CheckHandle(pFunName, "XC_IMAGELIST");
	exit(0);
}

void IsMenuDebug(HMENUX hMenu, char *pFunName) //检查菜单
{
	if (hMenu && (XC_MENU == *(UINT*)hMenu))
		return;

	DebugBox_CheckHandle(pFunName, "XC_MENU");
	exit(0);
}

void IsHImageDebug(HIMAGE hImage, char *pFunName) //炫彩图片
{
	if (hImage && (XC_IMAGE == *(UINT*)hImage))
		return;

	DebugBox_CheckHandle(pFunName, "XC_IMAGE");
	exit(0);
}

void IsFontDebug(HFONTX hFontX, char *pFunName) //炫彩图片
{
	if (hFontX && (XC_FONT == *(UINT*)hFontX))
		return;

	DebugBox_CheckHandle(pFunName, "XC_FONT");
	exit(0);
}

void IsImageTypeDebug(wchar_t *pFunName, wchar_t *pImageFile) //检查图片类型
{
	if (pImageFile)
	{
		wchar_t *pFile = wcsrchr(pImageFile, L'.');
		if (pFile)
		{
			if (0 != wcscmp(pFile, L".png") && 0 != wcscmp(pFile, L".PNG") &&
				0 != wcscmp(pFile, L".jpg") && 0 != wcscmp(pFile, L".JPG") &&
				0 != wcscmp(pFile, L".gif") && 0 != wcscmp(pFile, L".GIF") &&
				0 != wcscmp(pFile, L".bmp") && 0 != wcscmp(pFile, L".BMP") &&
				0 != wcscmp(pFile, L".ico") && 0 != wcscmp(pFile, L".ICO"))
			{
				wchar_t buf[MAX_PATH] = { 0 };
				swprintf_s(buf, MAX_PATH, L"在API:%s()中,图片格式错误,图片名称:[%s]!", pFunName, pImageFile);
				MessageBoxW(NULL, buf, L"炫彩界面库-错误提示!", MB_OK);

				exit(0);
			}
		}
		else
		{
			wchar_t buf[MAX_PATH] = { 0 };
			swprintf_s(buf, MAX_PATH, L"在API:%s()中,图片格式错误,图片名称:[%s]!", pFunName, pImageFile);
			MessageBoxW(NULL, buf, L"炫彩界面库-错误提示!", MB_OK);

			exit(0);
		}
	}
}

/*
#include <strsafe.h>
void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((wchar_t *)lpMsgBuf)+lstrlen((wchar_t *)lpszFunction)+40)*sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (wchar_t *)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
*/

#endif