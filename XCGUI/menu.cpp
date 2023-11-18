/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup menu 弹出菜单
/// @ingroup groupWindows
/// @{

/// @brief 创建菜单.默认弹出菜单窗口关闭后自动销毁.
/// @return 菜单句柄.
HMENUX WINAPI XMenu_Create()
{
	popupMenu_ *pObject = (popupMenu_*)malloc(sizeof(popupMenu_));
	if (pObject)
	{
		memset(pObject, 0, sizeof(popupMenu_));
		pObject->hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		pObject->hMTreeData = XMTree_Create();
		pObject->height = 22;
		pObject->leftWidth = 30;
		pObject->leftText = 10;
		pObject->bAutoDestroy = TRUE;
		pObject->hParentEle = NULL;
		pObject->hMenuWindow = NULL;
		pObject->hMenuBar = NULL;

		((object_*)pObject)->type = XC_MENU;

		return (HMENUX)pObject;
	}
	return NULL;
}
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
void WINAPI XMenu_SetUserDrawItemEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //设置用户自绘菜单项
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawItem = (pFunMenu_DrawItem)pCallBackFun;
	((popupMenu_*)hMenu)->pClass_Fun_Info = pClass_Fun_Info;
}

void WINAPI XMenu_SetUserDrawBGEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //设置用户自绘菜背景
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawBG = (pFunMenu_DrawBG)pCallBackFun;
	((popupMenu_*)hMenu)->pClass_Fun_Info_drawBG = pClass_Fun_Info;
}

void WINAPI XMenu_SetUserUpdateUIEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pUpdateUI = (pFunMenu_UpdateUI)pCallBackFun;
	((popupMenu_*)hMenu)->pClass_Fun_Info_updateUI = pClass_Fun_Info;
}

#endif

/// @brief 添加菜单项.
/// @param hMenu 菜单资源句柄.
/// @param id    菜单项ID.
/// @param pText   文本内容.
/// @param parentId  父项ID,XMENU_ROOT为跟节点.
/// @param uFlags 标识.
void WINAPI XMenu_AddItem(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	Menu_AddItemX(hMenu, id, pText, parentId, uFlags, 0);
}

/// @brief 添加菜单项,带图标.
/// @param hMenu 菜单资源句柄.
/// @param id    菜单项ID.
/// @param pText   文本内容.
/// @param parentId  父项ID,XMENU_ROOT为跟节点.
/// @param uFlags 标识.
/// @param hImage 图片句柄.
void WINAPI XMenu_AddItemImage(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage) //增加菜单项
{
	IsMenuDebug(hMenu, __FUNCTION__);
	Menu_AddItemX(hMenu, id, pText, parentId, uFlags, hImage);
}

/// @brief 插入菜单项到指定项前面.
/// @param hMenu 菜单资源句柄.
/// @param id    菜单项ID.
/// @param pText   文本内容.
/// @param uFlags  标识.
/// @param insertID 插入到该项的前面位置.
void WINAPI XMenu_InsertItem(HMENUX hMenu, int id, wchar_t *pText, int uFlags, int insertID)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pObj = (popupMenu_*)hMenu;

	menu_  *pItem = (menu_*)malloc(sizeof(menu_));
	memset(pItem, 0, sizeof(menu_));
	pItem->id = id;
	pItem->state = uFlags;
	pItem->hString = XStr_Create();
	if (FALSE == (XM_SEPARATOR & uFlags)) //分隔符
	{
		pItem->hString = XStr_Create();
		if (pText)
		{
			int leng = wcslen(pText);
			if (leng > 0)
			{
				XStr_SetString(pItem->hString, pText);
				SIZE size;
				HDC hdc = GetDC(NULL);
				HGDIOBJ hOld = SelectObject(hdc, pObj->hFont);
				GetTextExtentPoint32(hdc, pText, leng, &size);
				pItem->len = size.cx;
				SelectObject(hdc, hOld);
				ReleaseDC(NULL, hdc);
			}
		}
	}
	XMTree_InsertNode(pObj->hMTreeData, pItem, id, insertID);
}

/// @brief 插入菜单项到指定项前面,并且指定图标.
/// @param hMenu 菜单句柄.
/// @param id    菜单项ID.
/// @param pText   文本内容.
/// @param uFlags  标识.
/// @param insertID 插入到该项的前面位置.
/// @param hImage   图片句柄.
void WINAPI XMenu_InsertItemImage(HMENUX hMenu, int id, wchar_t *pText, int uFlags, int insertID, HIMAGE hImage) //增加菜单项
{
	IsMenuDebug(hMenu, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	popupMenu_ *pObj = (popupMenu_*)hMenu;

	menu_  *pItem = (menu_*)malloc(sizeof(menu_));
	memset(pItem, 0, sizeof(menu_));
	pItem->id = id;
	pItem->state = uFlags;

	pItem->hString = XStr_Create();
	if (pText)
	{
		int leng = wcslen(pText);
		if (leng > 0)
		{
			XStr_SetString(pItem->hString, pText);
			SIZE size;
			HDC hdc = GetDC(NULL);
			HGDIOBJ hOld = SelectObject(hdc, pObj->hFont);
			GetTextExtentPoint32(hdc, pText, leng, &size);
			pItem->len = size.cx;
			SelectObject(hdc, hOld);
			ReleaseDC(NULL, hdc);
		}
	}
	if (hImage) //图片从文件
	{
		Image_AddImage(pItem->hImage, hImage);
		//	pItem->hImage=hImage; //new Image(pImageName); 
	}
	XMTree_InsertNode(pObj->hMTreeData, pItem, id, insertID);
}

/// @brief 删除菜单项.
/// @param hMenu 菜单句柄.
/// @param id    菜单项ID.
void WINAPI XMenu_DeleteItem(HMENUX hMenu, int id)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pObj = (popupMenu_*)hMenu;

	menu_ *pItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, id);
	if (pItem)
	{
		if (pItem->hString) XStr_Destroy(pItem->hString);
		if (pItem->hImage) XImage_Destroy(pItem->hImage);

		XMTree_DeleteNode(pObj->hMTreeData, id);
		free(pItem);
	}
}

/// @brief 设置菜单句柄自动销毁.
/// @param hMenu  菜单句柄.
/// @param bAuto  值为TRUE当菜单弹出窗口关闭后,将自动销毁菜单句柄,否则相反.
void WINAPI XMenu_SetAutoDestroy(HMENUX hMenu, BOOL bAuto) //是否自动销毁对象
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->bAutoDestroy = bAuto;
}

/// @brief 设置菜单项高度.
/// @param hMenu  菜单句柄.
/// @param height 菜单项高度.
void WINAPI XMenu_SetItemHeight(HMENUX hMenu, int height) //设置菜单项高度
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->height = height;
}

/// @brief 设置菜单窗口背景图片.
/// @param hMenu  菜单句柄.
/// @param hImage 图片句柄.
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XMenu_SetBGImage(HMENUX hMenu, HIMAGE hImage) //设置菜单背景图片
{
	IsMenuDebug(hMenu, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	popupMenu_ *pMenu = (popupMenu_*)hMenu;

	Image_AddImage(pMenu->hBkImage, hImage);
	return FALSE;
}

/// @brief 设置菜单项图标.
/// @param hMenu  菜单句柄.
/// @param id    菜单项ID.
/// @param hImage 图片句柄
/// @return 成功返回TRUE,否则相反..
BOOL WINAPI XMenu_SetItemImage(HMENUX hMenu, int id, HIMAGE hImage) //设置项图标
{
	IsMenuDebug(hMenu, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		Image_AddImage(pItem->hImage, hImage);
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置菜单项文本.
/// @param hMenu  菜单句柄.
/// @param id    菜单项ID.
/// @param pText 文本内容
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XMenu_SetItemText(HMENUX hMenu, int id, wchar_t *pText) //设置项文本
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem && pText)
	{
		XStr_SetString(pItem->hString, pText);
		return TRUE;
	}
	return FALSE;
}

/// @brief 设置菜单项属性.
/// @param hMenu  菜单句柄.
/// @param id    菜单项ID.
/// @param uFlags 标识.
void WINAPI XMenu_SetItemFlags(HMENUX hMenu, int id, int uFlags)   //设置项属性
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		pItem->state = uFlags;
	}
}

/// @brief 获取菜单项属性.
/// @param hMenu  菜单句柄.
/// @param id    菜单项ID.
/// @return uFlags 标识.
int  WINAPI XMenu_GetItemFlags(HMENUX hMenu, int id)   //获取项属性
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		return pItem->state;
	}
	return -1;
}

/// @brief 设置菜单项勾选状态.
/// @param hMenu  菜单句柄.
/// @param id  菜单项ID
/// @param bCheck    勾选TRUE,非勾选FALSE.
void WINAPI XMenu_SetItemCheck(HMENUX hMenu, int id, BOOL bCheck)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		if (bCheck)
			pItem->state |= XM_CHECK;
		else
			pItem->state &= (~XM_CHECK);
	}
}

/// @brief 判断菜单项是否勾选.
/// @param hMenu  菜单句柄.
/// @param id  菜单项ID
/// @return 如果勾选返回TRUE,否则返回FALSE.
BOOL WINAPI XMenu_IsItemCheck(HMENUX hMenu, int id)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		if (XM_CHECK & pItem->state)
			return TRUE;
		else
			return FALSE;
	}
	return FALSE;
}

/// @brief 获取菜单项高度.
/// @param hMenu  菜单句柄.
/// @return 菜单项高度.
int WINAPI XMenu_GetItemHeight(HMENUX hMenu)  //获取菜单项高度
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return ((popupMenu_*)hMenu)->height;
}

/// @brief 获取菜单项数量,包含子菜单项.
/// @param hMenu  菜单句柄.
/// @return 菜单项数量.
int WINAPI XMenu_GetItemCount(HMENUX hMenu) //获取菜单项数量
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return XMTree_GetNodeCount(((popupMenu_*)hMenu)->hMTreeData, XMTREE_ROOT);
}

/// @brief 获取左侧区域宽度.
/// @param hMenu  菜单句柄.
/// @return 左侧区域宽度.
int  WINAPI XMenu_GetItemLeftWidth(HMENUX hMenu) //获取左侧宽度
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return ((popupMenu_*)hMenu)->leftWidth;
}

/// @brief 获取菜单项文本左间隔.
/// @param hMenu  菜单句柄.
/// @return 菜单项文本左间隔.
int  WINAPI XMenu_GetItemLeftText(HMENUX hMenu)  //获取菜单项文本左间隔
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return ((popupMenu_*)hMenu)->leftText;
}

/// @brief 获取菜单项文本内容.
/// @param hMenu  菜单句柄.
/// @param id    菜单项ID.
/// @return 菜单项文本内容..
wchar_t* WINAPI XMenu_GetItemText(HMENUX hMenu, int id) //获取菜单项文本
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		return XStr_GetBuffer(pItem->hString);
	}
	return NULL;
}

/// @brief 关闭弹出菜单窗口,并不销毁菜单句柄,默认情况下弹出菜单窗口关闭后,会自动销毁菜单句柄.
/// @param hMenu  菜单句柄.
void WINAPI XMenu_CloseMenu(HMENUX hMenu)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	if (((popupMenu_*)hMenu)->hMenuWindow)
		PostMessage(((window_*)((popupMenu_*)hMenu)->hMenuWindow)->hWnd, WM_CLOSE, 0, 0);
}
/// @brief 销毁菜单句柄,释放菜单资源.
/// @param hMenu  菜单句柄.
void WINAPI XMenu_Destroy(HMENUX hMenu)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pObj = (popupMenu_*)hMenu;

	int count = XMTree_BeginTraverseAll(pObj->hMTreeData);
	for (int i = 0; i < count; i++)
	{
		menu_ *pItem = (menu_*)XMTree_GetTraverseAll(pObj->hMTreeData, i);

		if (pItem->hImage) XImage_Destroy(pItem->hImage);

		if (pItem->hString)
			XStr_Destroy(pItem->hString);
		free(pItem);
	}
	XMTree_EndTraverseAll(pObj->hMTreeData);

	XMTree_Destroy(pObj->hMTreeData);

	if (pObj->hBkImage)
		XImage_Destroy(pObj->hBkImage);

#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	if (pObj->pClass_Fun_Info)
		free(pObj->pClass_Fun_Info);
	if (pObj->pClass_Fun_Info_drawBG)
		free(pObj->pClass_Fun_Info_drawBG);
#endif

	free(hMenu);
}

/// @brief 设置用户自绘菜单项.
/// @param hMenu  菜单句柄.
/// @param pFunDrawItem  自绘函数名.类型如下:
/// @code  void CALLBACK Menu_DrawItem(HMENUX hMenu,menu_drawItem_ *pDrawItem); @endcode
void WINAPI XMenu_SetUserDrawItem(HMENUX hMenu, pFunMenu_DrawItem pFunDrawItem) //设置用户自绘项
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	((popupMenu_*)hMenu)->pClass_Fun_Info = NULL;
#endif
}

/// @brief 设置用户自绘菜背景.
/// @param hMenu  菜单句柄.
/// @param pFunDrawBG  自绘函数名.类型如下:
/// @code  void CALLBACK Menu_DrawBG(HMENUX hMenu,menu_drawBG_ *pDrawBG); @endcode
void WINAPI XMenu_SetUserDrawBG(HMENUX hMenu, pFunMenu_DrawBG pFunDrawBG) //设置用户自绘菜单背景
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawBG = pFunDrawBG;
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	((popupMenu_*)hMenu)->pClass_Fun_Info_drawBG = NULL;
#endif
}

void WINAPI XMenu_SetUserUpdateUI(HMENUX hMenu, pFunMenu_UpdateUI pUpdateUI)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pUpdateUI = pUpdateUI;
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	((popupMenu_*)hMenu)->pClass_Fun_Info_updateUI = NULL;
#endif
}

/// @brief 弹出菜单.
/// @param hMenu  菜单句柄.
/// @param hParentWnd  父窗口句柄.
/// @param x  弹出菜单x坐标.
/// @param y  弹出菜单y坐标.
/// @param hParentEle 父元素资源句柄,如果该值不为NULL,hParentEle元素将接收菜单消息事件,
///     否则将由hParentWindow窗口接收菜单的消息事件
/// @param uFlags 标识.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XMenu_Popup(HMENUX hMenu, HWND hParentWnd, int x, int y, HELE hParentEle, int uFlags) //弹出菜单
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pObject = (popupMenu_*)hMenu;

	SIZE size;
	if (FALSE == Menu_computeWndSize(hMenu, XMENU_ROOT, size))
	{
		return FALSE;
	}
	Menu_AdjustPosition(x, y, size.cx, size.cy, uFlags);

	HWINDOW hMenuWindow = MenuWnd_CreateWindow(x, y, size.cx, size.cy, hParentWnd);
	if (hMenuWindow)
	{
		pObject->hParentEle = hParentEle;

		((popupMenuWindow_*)hMenuWindow)->pMenuData = (popupMenu_*)hMenu;
		((popupMenuWindow_*)hMenuWindow)->hMTreeData = ((popupMenu_*)hMenu)->hMTreeData;

		//菜单弹出事件
		MenuWnd_UpdateUI(hMenuWindow, XMENU_ROOT); //更新UI

		XWnd_SetWindowPos(hMenuWindow, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		HWND hWnd = XWnd_GetHWnd(hMenuWindow);
		::SetCapture(hWnd);

		pObject->hMenuWindow = hMenuWindow;

		///////////////////////////////////////////////////////
		MSG msg;
		while (IsWindow(hWnd) && GetMessage(&msg, NULL, 0, 0))
		{
			switch (msg.message)
			{
			case WM_NCMOUSEMOVE:
				break;
			case WM_KILLFOCUS:
			case WM_CAPTURECHANGED:
				//	DestroyAll();
				break;
			case WM_NCLBUTTONDOWN:
			case WM_NCRBUTTONDOWN:
			case WM_NCMBUTTONDOWN:
				break;
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
				//	OnRButtonDown(msg);
				MenuWnd_OnRButtonDown(hMenuWindow, &msg.pt);
				break;
			case WM_LBUTTONDOWN:
			{
				MenuWnd_OnLButtonDown(hMenuWindow, &msg.pt);
			}break;
			case WM_LBUTTONUP:
			{
				MenuWnd_OnLButtonUp(hMenuWindow, &msg.pt);
			}break;
			//case WM_TIMER:
			//	OnTimer(msg);
			//	break;
			case WM_RBUTTONUP:
				break;
				//case WM_KEYDOWN:
				//	DestroyAll();
				//	break;
			case WM_SYSKEYDOWN:
				//	DestroyAll();
				MenuWnd_OnWndSysKeyDown(hMenuWindow, msg.wParam, msg.lParam);
				break;
			case WM_CHAR:
				break;
			default:
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

void Menu_AddItemX(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage) //增加菜单项
{
	popupMenu_ *pObj = (popupMenu_*)hMenu;

	menu_  *pItem = (menu_*)malloc(sizeof(menu_));
	pItem->id = id;
	pItem->parentId = parentId;
	pItem->hImage = NULL;
	pItem->state = uFlags;

	if (parentId > XMENU_ROOT) //给父项增加弹出标识
	{
		menu_ *pParentItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, parentId);
		if (NULL == pParentItem)
		{
			MessageBox(NULL, L"炫彩界面库-错误提示:API:XMenu_AddItem*()中参数[parentId]错误!", L"提示", 0);
		}
		if (FALSE == (pParentItem->state & XM_POPUP))
		{
			pParentItem->state |= XM_POPUP;
		}
	}

	if (XM_SEPARATOR & uFlags) //分隔符
	{
		pItem->len = 0;
		pItem->hString = NULL;
	}
	else
	{
		pItem->hString = XStr_Create();
		if (pText)
		{
			int leng = wcslen(pText);
			if (leng > 0)
			{
				XStr_SetString(pItem->hString, pText);
				SIZE size;
				HDC hdc = GetDC(NULL);
				HGDIOBJ hOld = SelectObject(hdc, pObj->hFont);
				GetTextExtentPoint32(hdc, pText, leng, &size);
				pItem->len = size.cx;
				SelectObject(hdc, hOld);
				ReleaseDC(NULL, hdc);
			}
		}
		if (hImage) //图片从文件
		{
			Image_AddImage(pItem->hImage, hImage);
			//pItem->hImage=hImage; 
		}
	}
	XMTree_AddNode(pObj->hMTreeData, parentId, pItem, id);
}

HWINDOW Menu_GetMenuHWindow(HMENUX hMenu)
{
	return ((popupMenu_*)hMenu)->hMenuWindow;
}

BOOL Menu_computeWndSize(HMENUX hMenu, int parentID, SIZE &size)
{
	popupMenu_ *pObject = (popupMenu_*)hMenu;
	size.cx = 0;
	size.cy = 3;

	//计算显示位置---
	int countItem = XMTree_BeginTraverseInfo(pObject->hMTreeData, parentID);
	if (countItem < 1) return FALSE;

	menu_  *pItem = NULL;
	//计算窗口宽度
	for (int i = 0; i < countItem; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseInfo(pObject->hMTreeData, i);
		if (pItem->len > size.cx)
			size.cx = pItem->len;

		//XTRACE("id=%d \n", pItem->id);
	}

	size.cx += pObject->leftWidth;  //增加左边显示菜单项图标的,灰色区域宽度
	size.cx += pObject->leftText;   //增加菜单项文本左间隔
	size.cx += 30;           //增加菜单项,弹出项图标宽度

	int left = 2;
	for (int i = 0; i < countItem; i++)
	{
		HXCGUI hNode = NULL;
		pItem = (menu_*)XMTree_GetTraverseInfo(pObject->hMTreeData, i, &hNode);
		pItem->state &= ~XM_SELECT;
		if (pItem->state & XM_SEPARATOR) //分割栏
		{
			pItem->rcItem.left = left;
			pItem->rcItem.top = size.cy;
			pItem->rcItem.right = left + size.cx;
			pItem->rcItem.bottom = size.cy + 4;
			size.cy += 4;
		}
		else
		{
			pItem->rcItem.left = left;
			pItem->rcItem.top = size.cy;
			pItem->rcItem.right = left + size.cx;
			pItem->rcItem.bottom = size.cy + pObject->height;

			size.cy += pObject->height;
		}
	}

	XMTree_EndTraverseInfo(pObject->hMTreeData);

	size.cx += 6;
	size.cy += 3;
	return TRUE;
}

void Menu_AdjustPosition(int &x, int &y, int width, int height, int uFlags) //计算调整显示位置，以便适应显示范围
{
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	switch (uFlags)  //显示方向  //检测调整显示位置
	{
	case XM_LEFT_TOP:
	{
		int right = x + width;
		int bottom = y + height;
		if (right > rect.right)
		{
			x = x - width;
		}
		if (bottom > rect.bottom)
		{
			y = y - height;
		}
	}
	break;  //位置保存不变
	case XM_LEFT_BOTTOM:
	{
		y = y - height;

		int top = y;
		int right = x + width;
		if (top < rect.top)
		{
			y = top + height;
		}
		if (right > rect.right)
		{
			x = x - width;
		}
	}
	break;
	case XM_RIGHT_TOP:
	{
		x = x - width;
		int left = x;
		int bottom = y + height;
		if (left < rect.left)
		{
			x = x + width;
		}
		if (bottom > rect.bottom)
		{
			y = y - height;
		}
	}break;
	case XM_RIGHT_BOTTOM:
	{
		x = x - width; y = y - height;
		int left = x;
		int top = y;
		if (left < rect.left)
		{
			x = x + width;
		}
		if (top < rect.top)
		{
			y = y + height;
		}
	}
	break;
	case XM_CENTER_LEFT:
	{
		y = y - (height / 2);
		int right = x + width;
		if (right > rect.right)
		{
			x = x - width;
		}
	}
	break;
	case XM_CENTER_TOP:
	{
		x = x - (width / 2);
		int bottom = y + height;
		if (bottom > rect.bottom)
		{
			y = y - height;
		}
	}
	break;
	case XM_CENTER_RIGHT:
	{
		x = x - width; y = y - (height / 2);
		int left = x;
		if (left < rect.left)
		{
			x = x + width;
		}
	}
	break;
	case XM_CENTER_BOTTOM:
	{
		x = x - (width / 2); y = y - height;
		int top = y;
		if (top < rect.top)
		{
			y = y + height;
		}
	}
	break;
	}
}
///@}

//////////////////////////////////////////////////////////////////////////////////////
HWINDOW MenuWnd_CreateWindow(int x, int y, int width, int height, HWND hWndParent)
{
	popupMenuWindow_ *pObj = (popupMenuWindow_*)malloc(sizeof(popupMenuWindow_));
	memset(pObj, 0, sizeof(popupMenuWindow_));

	if (pObj)
	{
		pObj->selItemID = -1;
		pObj->hMTreeData = NULL;

		MenuWnd_Init((HWINDOW)pObj, x, y, width, height, L"popupMenu", hWndParent, XC_POPUPMENUWINDOW);
		return (HWINDOW)pObj;
	}
	return NULL;
}

BOOL MenuWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent, int exType)
{
	BOOL res = Wnd_Init(hWindow, WS_EX_TOPMOST /*| WS_EX_TOOLWINDOW*/, NULL, pTitle, WS_POPUP, x, y, cx, cy, hWndParent, 0, exType);
	if (res)
	{
		AddTypeDebug(hWindow, XC_POPUPMENUWINDOW);

		XWnd_SetCaptionHeight(hWindow, 0);
		XWnd_SetBorderSize(hWindow, 0, 0, 0, 0);

		XWnd_RegisterMessage(hWindow, WM_PAINT, MenuWnd_OnDrawWindow);
		//XWnd_RegisterMessage(hWindow,WM_LBUTTONDOWN,MenuWnd_OnLButtonDown);
	//	XWnd_RegisterNCMessage(hWindow,XWM_NCLBUTTONDOWN,MenuWnd_OnNCLButtonDown);
	//	XWnd_RegisterMessage(hWindow,WM_LBUTTONUP,MenuWnd_OnLButtonUp);
	//	XWnd_RegisterNCMessage(hWindow,XWM_NCLBUTTONUP,MenuWnd_OnNCLButtonUp);
		XWnd_RegisterMessage(hWindow, WM_MOUSEMOVE, MenuWnd_OnMouseMove);
		XWnd_RegisterNCMessage(hWindow, XWM_NCMOUSEMOVE, MenuWnd_OnNCMouseMove);
		XWnd_RegisterMessage(hWindow, WM_CAPTURECHANGED, MenuWnd_OnCaptureChanged);

		//	XWnd_RegisterMessage(hWindow,WM_RBUTTONDOWN,MenuWnd_OnRButtonDown);
		//	XWnd_RegisterNCMessage(hWindow,XWM_NCRBUTTONDOWN,MenuWnd_OnNCRButtonDown);
		//	XWnd_RegisterMessage(hWindow,WM_DESTROY,MenuWnd_OnDestroy);

			//XWnd_RegisterMessage(hWindow,WM_SYSKEYDOWN,MenuWnd_OnWndSysKeyDown);
	}
	return res;
}

void MenuWnd_UpdateUI(HWINDOW hWindow, int parentID)
{
	//////////////////////////////////////////////////////////////////
	popupMenuWindow_ *pObj = (popupMenuWindow_*)hWindow;
	int count = XMTree_BeginTraverse(pObj->hMTreeData, parentID);
	if (pObj->pMenuData->pUpdateUI) //用户自绘菜单项
	{
		for (int i = 0; i < count; i++)
		{
			menu_ *pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			if (pObj->pMenuData->pClass_Fun_Info_updateUI)
			{
				eventOrMsg_  event_;
				event_.hMenu = (HMENUX)pObj->pMenuData;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)pItem->id;
				event_.lParam = NULL;
				event_.pClass_fun = pObj->pMenuData->pClass_Fun_Info_updateUI;
				((pFunClassEventMsg)pObj->pMenuData->pUpdateUI)(&event_, xc_fun_v_x_menu_i);
			}
			else
			{
				pObj->pMenuData->pUpdateUI((HMENUX)pObj->pMenuData, pItem->id);
			}
#else
			pObj->pMenuData->pUpdateUI((HMENUX)(pObj->pMenuData), pItem->id);
#endif
		}
	}

	XMTree_EndTraverse(pObj->hMTreeData);
}

BOOL MenuWnd_OnDestroyMenu(popupMenu_ *pMenu)
{
	pMenu->hMenuWindow = NULL;

	if (pMenu->bAutoDestroy)
		XMenu_Destroy((HMENUX)pMenu);

	return FALSE;
}

BOOL CALLBACK MenuWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	popupMenuWindow_ *pObj = (popupMenuWindow_*)hWindow;

	if (pObj->pMenuData->pDrawBG) //用户自绘背景
	{
		menu_drawBG_ drawBG;
		drawBG.hWindow = hWindow;
		drawBG.hDraw = hDraw;
		drawBG.parentItemId = -1;
		drawBG.hImage = pObj->pMenuData->hBkImage;
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		if (pObj->pMenuData->pClass_Fun_Info_drawBG)
		{
			eventOrMsg_  event_;
			event_.hMenu = (HMENUX)pObj->pMenuData;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)&drawBG;
			event_.lParam = NULL;
			event_.pClass_fun = pObj->pMenuData->pClass_Fun_Info_drawBG;
			((pFunClassEventMsg)pObj->pMenuData->pDrawBG)(&event_, xc_fun_v_x_menu_bg);
		}
		else
		{
			pObj->pMenuData->pDrawBG((HMENUX)pObj->pMenuData, &drawBG);
		}
#else
		pObj->pMenuData->pDrawBG((HMENUX)(pObj->pMenuData), &drawItem);
#endif
	}
	else //系统绘制
	{
		MenuWnd_DrawBackground((window_*)hWindow, hDraw, pObj->pMenuData->hBkImage);
	}

	//////////////////////////////////////////////////////////////////
	int count = XMTree_BeginTraverse(pObj->hMTreeData, XMENU_ROOT);
	if (pObj->pMenuData->pDrawItem) //用户自绘菜单项
	{
		for (int i = 0; i < count; i++)
		{
			menu_ *pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);
			menu_drawItem_  drawItem;
			drawItem.hWindow = hWindow;
			drawItem.hDraw = hDraw;
			drawItem.id = pItem->id;
			drawItem.state = pItem->state;
			drawItem.rcItem = pItem->rcItem;
			drawItem.hImage = pItem->hImage;
			if (pItem->hString)
				drawItem.pText = XStr_GetBuffer(pItem->hString);
			else
				drawItem.pText = NULL;

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			if (pObj->pMenuData->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hMenu = (HMENUX)pObj->pMenuData;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)&drawItem;
				event_.lParam = NULL;
				event_.pClass_fun = pObj->pMenuData->pClass_Fun_Info;
				((pFunClassEventMsg)pObj->pMenuData->pDrawItem)(&event_, xc_fun_v_x_menu_item);
			}
			else
			{
				pObj->pMenuData->pDrawItem((HMENUX)pObj->pMenuData, &drawItem);
			}
#else
			pObj->pMenuData->pDrawItem((HMENUX)(pObj->pMenuData), &drawItem);
#endif
		}
	}
	else //系统绘制
	{
		for (int i = 0; i < count; i++)
		{
			menu_ *pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);
			menu_drawItem_  drawItem;
			drawItem.hWindow = hWindow;
			drawItem.hDraw = hDraw;
			drawItem.id = pItem->id;
			drawItem.state = pItem->state;
			drawItem.rcItem = pItem->rcItem;
			drawItem.hImage = pItem->hImage;
			if (pItem->hString)
				drawItem.pText = XStr_GetBuffer(pItem->hString);
			else
				drawItem.pText = NULL;

			//自绘
			MenuWnd_DrawItem(hWindow, hDraw, &drawItem);
		}
	}

	XMTree_EndTraverse(pObj->hMTreeData);
	return TRUE;
}

void MenuWnd_DrawItem(HWINDOW hWindow, HDRAW hDraw, menu_drawItem_ *pItem)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);
	if (pItem->state & XM_SEPARATOR) //分割栏
	{
		HPEN hPen1 = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(200, 200, 200));
		HGDIOBJ hOld1 = XDraw_SelectObject_(hDraw, hPen1);

		XDraw_MoveToEx_(hDraw, pObj->pMenuData->leftWidth + 2, pItem->rcItem.top + 1, 0);
		XDraw_LineTo_(hDraw, pItem->rcItem.right - 5, pItem->rcItem.top + 1);

		//SelectObject(hdc,hOld1);
		//DeleteObject(hPen1);
		return;
	}

	if (pItem->state & XM_SELECT) //选择项
	{
		XDraw_GradientFill2_(hDraw, RGB(63, 151, 216), RGB(48, 134, 198), &pItem->rcItem, GRADIENT_FILL_RECT_V);
	}

	if (pItem->state & XM_POPUP) //弹出项
	{
		//绘制右三角
		POINT  pt[3];
		pt[0].x = pItem->rcItem.right - 12;
		pt[0].y = pItem->rcItem.top + 5;
		pt[1].x = pItem->rcItem.right - 12;
		pt[1].y = pItem->rcItem.top + 15;
		pt[2].x = pItem->rcItem.right - 7;
		pt[2].y = pItem->rcItem.top + 10;
		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(0, 0, 0));
		XDraw_FillRgn_(hDraw, hRgn, hBrush);
		//DeleteObject(hRgn);
		//DeleteObject(hBrush);
	}

	if (pItem->state &XM_CHECK) //勾选
	{
		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 2, RGB(0, 0, 0));
		HGDIOBJ hOld = XDraw_SelectObject_(hDraw, hPen);
		XDraw_MoveToEx_(hDraw, pItem->rcItem.left + 5, pItem->rcItem.top + 8, 0);
		XDraw_LineTo_(hDraw, pItem->rcItem.left + 10, pItem->rcItem.top + 13);

		XDraw_MoveToEx_(hDraw, pItem->rcItem.left + 9, pItem->rcItem.top + 13, 0);
		XDraw_LineTo_(hDraw, pItem->rcItem.left + 17, pItem->rcItem.top + 5);

		//SelectObject(hdc,hOld);
		//DeleteObject(hPen);
	}

	RECT rc = pItem->rcItem;
	rc.left = pObj->pMenuData->leftWidth + pObj->pMenuData->leftText;

	wchar_t *pText = pItem->pText;
	if (pItem->state & XM_DISABLED)//禁用项
	{
		if (pText)
		{
			COLORREF color = XDraw_SetTextColor_(hDraw, RGB(100, 100, 100));
			XDraw_DrawText_(hDraw, pText, wcslen(pItem->pText), &rc, DT_VCENTER | DT_SINGLELINE);
			XDraw_SetTextColor_(hDraw, color);
		}
	}
	else
	{
		if (pItem->hImage)
		{
			int top = (pObj->pMenuData->height / 2) - XImage_GetHeight(pItem->hImage) / 2;  //(pItem->pImage->GetHeight()/2);
			int left = (pObj->pMenuData->leftWidth / 2) - XImage_GetWidth(pItem->hImage) / 2;  //(pItem->pImage->GetWidth()/2);
			if (top < 0) top = 0;
			if (left < 0) left = 0;
			//XDraw_GraphicsDrawImage(hdc,pItem->pImage,left,pItem->rcItem.top+top);
			XDraw_HImage_(hDraw, pItem->hImage, left, pItem->rcItem.top + top);
		}
		if (pText)
			XDraw_DrawText_(hDraw, pText, wcslen(pItem->pText), &rc, DT_VCENTER | DT_SINGLELINE);
	}
}

void MenuWnd_DrawBackground(window_ *pWindow, HDRAW hDraw, HIMAGE hImage) //绘制菜单背景
{
	RECT rc;
	GetClientRect(pWindow->hWnd, &rc);
	//绘制背景色-----------------------
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255));

	//绘制左边灰色区域------------------
	RECT rcLeft = rc;
	rcLeft.left = 1;
	rcLeft.top = 1;
	rcLeft.right = 30;
	rcLeft.bottom--;
	XDraw_FillSolidRect_(hDraw, &rcLeft, RGB(232, 237, 239));

	HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(200, 200, 200));
	HGDIOBJ hOld = XDraw_SelectObject_(hDraw, hPen);
	XDraw_MoveToEx_(hDraw, 29, 0, 0);
	XDraw_LineTo_(hDraw, 29, rc.bottom - 2);
	//XDraw_SelectObject_(hdc,hOld);
	//DeleteObject(hPen);

	if (hImage) //背景图片
	{
		XDraw_HImage_(hDraw, hImage, 0, 0);
	}

	//绘制边框---------------------------
	RECT rcFrame = rc;
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(130, 130, 130));
	//HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(255,0,0));
	XDraw_FrameRect_(hDraw, &rcFrame, hBrush);
	//DeleteObject(hBrush);
/*
	HPEN hPen1=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(180,180,180));
	HGDIOBJ hOld1=XDraw_SelectObject_(hDraw,hPen1);
	XDraw_MoveToEx_(hDraw,rc.right-2,1,0);
	XDraw_LineTo_(hDraw,rc.right-2,rc.bottom-2);
	XDraw_LineTo_(hDraw,0,rc.bottom-2);
	*/
	//	SelectObject(hDraw,hOld1);
	//	DeleteObject(hPen1);

}

void MenuWnd_OnDestroyWindow(HWND hWnd, popupMenu_ *pMenu)
{
	DestroyWindow(hWnd);
	pMenu->hMenuWindow = NULL;
}

void MenuWnd_OnExitMenu(HELE hParentEle, HWND hParentWnd)
{
	//发送菜单退出消息
	if (hParentEle)
	{
		Ele_SendEvent(hParentEle, XE_MENUEXIT, 0, 0);
	}
	else if (hParentWnd)
	{
		SendMessage(hParentWnd, XWM_MENUEXIT, 0, 0);
	}
}

//pPt:屏幕坐标
BOOL CALLBACK MenuWnd_OnLButtonDown(HWINDOW hWindow, POINT *pPt)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

	POINT ptScreen = *pPt;  //屏幕坐标

	//检查鼠标是否在子菜上
	RECT rcWindow;  //窗口坐标
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;

	if (pChildWnd)
	{
		while (pChildWnd->pChildWnd)    //查找最后一个子菜单
			pChildWnd = pChildWnd->pChildWnd;

		while (pChildWnd)
		{
			GetWindowRect(pChildWnd->window.hWnd, &rcWindow);
			if (PtInRect(&rcWindow, ptScreen))
			{
				return FALSE;
			}
			pChildWnd = pChildWnd->pPreviouWnd;
		}
	}

	//检查是否在主菜单上
	GetClientRect(pObj->window.hWnd, &rcWindow);
	POINT ptClient = ptScreen; //客户区坐标
	ScreenToClient(((window_*)hWindow)->hWnd, &ptClient);
	if (PtInRect(&rcWindow, ptClient))
	{
		return FALSE;
	}

	HELE        hParentEle = pObj->pMenuData->hParentEle;
	HWND        hParentWnd = GetParent(pObj->window.hWnd);
	popupMenu_  *pMenu = pObj->pMenuData;
	HELE        hMenuBar = pMenu->hMenuBar;

	HWND ptHWND = WindowFromPoint(ptScreen);
	POINT ptClient2 = ptScreen;
	ScreenToClient(ptHWND, &ptClient2);

	MenuWnd_OnDestroyWindow(pObj->window.hWnd, pMenu);
	MenuWnd_OnExitMenu(hParentEle, hParentWnd);
	MenuWnd_OnDestroyMenu(pMenu);

	if (hMenuBar) //检查是否按在菜单条按钮上,如果不在按钮上,修改按钮状态
	{
		menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
		if (pMenuBar->pBtnTop)
		{
			pMenuBar->pBtnTop->button.state = STATE_LEAVE;
			XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
		}
	}

	SendMessage(ptHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(ptClient2.x, ptClient2.y));

	if (hMenuBar) //弹出菜单关闭
	{
		menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
		if (pMenuBar->pBtnTop)
		{
			pMenuBar->bDown = FALSE;
			pMenuBar->pBtnTop = NULL;
		}
	}
	return TRUE;
}

//pPt:屏幕坐标
BOOL CALLBACK MenuWnd_OnLButtonUp(HWINDOW hWindow, POINT *pPt)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

	POINT ptSrceen = *pPt;

	RECT rcWindow;
	//检查鼠标是否在子菜单上
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;
	if (pChildWnd)
	{
		while (pChildWnd->pChildWnd) //查找最后一个子菜单
			pChildWnd = pChildWnd->pChildWnd;

		while (pChildWnd)
		{
			GetWindowRect(pChildWnd->window.hWnd, &rcWindow);
			if (PtInRect(&rcWindow, ptSrceen))
			{
				ScreenToClient(pChildWnd->window.hWnd, &ptSrceen);
				MenuChildWnd_OnLButtonUp(pChildWnd, &ptSrceen);
				return TRUE;
			}
			pChildWnd = pChildWnd->pPreviouWnd;
		}
	}

	//检查鼠标是否在主菜单上
	BOOL  bYes = FALSE;
	int  iItem = -1;
	POINT ptClient = ptSrceen;
	ScreenToClient(pObj->window.hWnd, &ptClient);
	GetClientRect(pObj->window.hWnd, &rcWindow);
	if (PtInRect(&rcWindow, ptClient))
	{
		menu_ *pItem = NULL;
		int count = XMTree_BeginTraverse(pObj->hMTreeData, XMENU_ROOT);
		for (int i = 0; i < count; i++)
		{
			pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);
			if (PtInRect(&pItem->rcItem, ptClient))
			{
				if ((pItem->state & XM_DISABLED) || (pItem->state & XM_POPUP) || (pItem->state & XM_SEPARATOR))
				{
					break;
				}
				bYes = TRUE;
				iItem = pItem->id;
				break;
			}
		}
		XMTree_EndTraverse(pObj->hMTreeData);
	}

	if (bYes)
	{
		HELE        hParentEle = pObj->pMenuData->hParentEle;
		HWND        hParentWnd = GetParent(pObj->window.hWnd);
		popupMenu_  *pMenu = pObj->pMenuData;
		HELE        hMenuBar = pMenu->hMenuBar;

		MenuWnd_OnDestroyWindow(pObj->window.hWnd, pMenu);
		if (hParentEle)
		{
			Ele_SendEvent(hParentEle, XE_MENUSELECT, iItem, 0);
		}
		else if (hParentWnd)
		{
			SendMessage(hParentWnd, XWM_MENUSELECT, iItem, 0);
		}
		MenuWnd_OnExitMenu(hParentEle, hParentWnd);
		MenuWnd_OnDestroyMenu(pMenu);

		if (hMenuBar) //检查是否按在菜单条按钮上,如果不在按钮上,修改按钮状态
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //弹出菜单关闭
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->bDown = FALSE;
				pMenuBar->pBtnTop = NULL;
			}
		}

		return TRUE;
	}
	return FALSE;
}

//pPt:屏幕坐标
BOOL CALLBACK MenuWnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	//pPt: 基于当前窗口客户区坐标
	popupMenuWindow_ *pObj = (popupMenuWindow_*)hWindow;

	POINT pt = *pPt;
	POINT ptScreen = *pPt; //屏幕坐标点
	ClientToScreen(pObj->window.hWnd, &ptScreen);
	RECT rcWindow;    //窗口坐标

	if (pObj->pMenuData->hMenuBar) //菜单条
	{
		MenuBar_OnMenuMouseMove(pObj->pMenuData->hMenuBar, &ptScreen);
	}

	//XTRACE("鼠标移动 x=%d \n",pt.x);
	//---检查鼠标是否在子窗口上
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;
	popupMenuChildWindow_ *pFinally = NULL; //最后一个窗口
	if (pChildWnd)
	{
		if (FALSE == XC_IsHWINDOW(hWindow))
			return TRUE;

		while (pChildWnd->pChildWnd)  //查找最后窗口
			pChildWnd = pChildWnd->pChildWnd;

		pFinally = pChildWnd;

		while (pChildWnd)
		{
			GetWindowRect(pChildWnd->window.hWnd, &rcWindow);
			if (PtInRect(&rcWindow, ptScreen))
			{
				ScreenToClient(pChildWnd->window.hWnd, &ptScreen);
				MenuChildWnd_OnMouseMove(pChildWnd, &ptScreen);
				return TRUE;
			}
			pChildWnd = pChildWnd->pPreviouWnd;
		}
	}

	//检查是否在主菜单上
	BOOL res = MenuWnd_CheckMouseMove(pObj, pt);

	if (FALSE == res)
	{
		if (pFinally)
		{
			if (-1 != pFinally->selItemID)
			{
				menu_ *pItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, pFinally->selItemID);
				pItem->state &= ~XM_SELECT;
				pFinally->selItemID = -1;
				XWnd_RedrawWnd((HWINDOW)&pFinally->window);
			}
		}
		else if (-1 != pObj->selItemID)
		{
			menu_ *pItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, pObj->selItemID);
			pItem->state &= ~XM_SELECT;
			pObj->selItemID = -1;
			XWnd_RedrawWnd(hWindow);
		}
	}

	return FALSE;
}

BOOL CALLBACK MenuWnd_OnNCMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	MenuWnd_OnMouseMove(hWindow, flags, pPt);
	return FALSE;
}

BOOL MenuWnd_CheckMouseMove(popupMenuWindow_ *pObj, POINT &pt)
{
	//pPt: 基于当前窗口客户区坐标
	int count = XMTree_BeginTraverse(pObj->hMTreeData, XMENU_ROOT);

	BOOL  bResult = FALSE;
	for (int i = 0; i < count; i++)
	{
		menu_ *pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);
		if (PtInRect(&pItem->rcItem, pt))
		{
			if (pObj->selItemID != pItem->id)
			{
				if (pObj->pChildWnd) //关闭子菜单
				{
					popupMenuChildWindow_  *pChildWnd = pObj->pChildWnd;
					while (pChildWnd)
					{
						::PostMessage(pChildWnd->window.hWnd, WM_CLOSE, 0, 0);
						pChildWnd = pChildWnd->pChildWnd;
					}
					pObj->pChildWnd = NULL;
				}
				if (pObj->selItemID >= 0) //取消先前选择项
				{
					menu_ *pOldSelItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, pObj->selItemID);
					pOldSelItem->state &= ~XM_SELECT;
				}

				if (pItem->state & XM_SEPARATOR)
				{
					pObj->selItemID = -1;
				}
				else
				{
					pItem->state |= XM_SELECT;
					pObj->selItemID = pItem->id;
					if (pItem->state & XM_POPUP)	//弹出
					{
						pObj->enterTiemr = GetTickCount();
						pObj->enterItemID = pItem->id;
						SetTimer(pObj->window.hWnd, IDT_MENU, 500, MenuWnd_TimerProc);
						//	XTRACE("弹出窗口\n");
					}
					XWnd_RedrawWnd((HWINDOW)&pObj->window);
				}
			}
			bResult = TRUE;
			break;
		}
	}
	XMTree_EndTraverse(pObj->hMTreeData);
	return bResult;
}

//pPt:屏幕坐标
BOOL CALLBACK MenuWnd_OnRButtonDown(HWINDOW hWindow, POINT *pPt)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

	POINT ptScreen = *pPt;

	RECT rcWindow;
	//----检查鼠标是否在子菜上
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;
	if (pChildWnd)
	{
		while (pChildWnd->pChildWnd)
			pChildWnd = pChildWnd->pChildWnd;

		while (pChildWnd)
		{
			GetWindowRect(pChildWnd->window.hWnd, &rcWindow);
			if (PtInRect(&rcWindow, ptScreen))
			{
				return TRUE;
			}
			pChildWnd = pChildWnd->pPreviouWnd;
		}
	}

	//检查是否在窗口上
	POINT ptClient = ptScreen;
	ScreenToClient(pObj->window.hWnd, &ptClient);
	GetClientRect(pObj->window.hWnd, &rcWindow);
	if (PtInRect(&rcWindow, ptClient))
	{
		return TRUE;
	}

	HELE        hParentEle = pObj->pMenuData->hParentEle;
	HWND        hParentWnd = GetParent(pObj->window.hWnd);
	popupMenu_  *pMenu = pObj->pMenuData;
	HELE        hMenuBar = pMenu->hMenuBar;

	HWND ptHWND = WindowFromPoint(ptScreen);
	POINT ptClient2 = ptScreen;
	ScreenToClient(ptHWND, &ptClient2);

	MenuWnd_OnDestroyWindow(pObj->window.hWnd, pMenu);
	MenuWnd_OnExitMenu(hParentEle, hParentWnd);
	MenuWnd_OnDestroyMenu(pMenu);

	if (hMenuBar) //检查是否按在菜单条按钮上,如果不在按钮上,修改按钮状态
	{
		menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
		if (pMenuBar->pBtnTop)
		{
			pMenuBar->pBtnTop->button.state = STATE_LEAVE;
			XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
		}
	}

	SendMessage(ptHWND, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(ptClient2.x, ptClient2.y));

	if (hMenuBar) //弹出菜单关闭
	{
		menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
		if (pMenuBar->pBtnTop)
		{
			pMenuBar->bDown = FALSE;
			pMenuBar->pBtnTop = NULL;
		}
	}

	return TRUE;
}

BOOL CALLBACK MenuWnd_OnCaptureChanged(HWINDOW hWindow, HWND hWnd)
{
	if (NULL == hWnd)
	{
		popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

		HELE        hParentEle = pObj->pMenuData->hParentEle;
		HWND        hParentWnd = GetParent(pObj->window.hWnd);
		popupMenu_  *pMenu = pObj->pMenuData;
		HELE        hMenuBar = pMenu->hMenuBar;

		MenuWnd_OnDestroyWindow(pObj->window.hWnd, pMenu);
		MenuWnd_OnExitMenu(hParentEle, hParentWnd);
		MenuWnd_OnDestroyMenu(pMenu);

		if (hMenuBar) //检查是否按在菜单条按钮上,如果不在按钮上,修改按钮状态
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //弹出菜单关闭
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->bDown = FALSE;
				pMenuBar->pBtnTop = NULL;
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK MenuWnd_OnWndSysKeyDown(HWINDOW hWindow, WPARAM wParam, LPARAM lParam)
{
	if (VK_MENU == wParam)
	{
		//XTRACE("VK_MENU  \n");

		popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

		HELE        hParentEle = pObj->pMenuData->hParentEle;
		HWND        hParentWnd = GetParent(pObj->window.hWnd);
		popupMenu_  *pMenu = pObj->pMenuData;
		HELE        hMenuBar = pMenu->hMenuBar;

		MenuWnd_OnDestroyWindow(pObj->window.hWnd, pMenu);
		MenuWnd_OnExitMenu(hParentEle, hParentWnd);
		MenuWnd_OnDestroyMenu(pMenu);

		if (hMenuBar) //检查是否按在菜单条按钮上,如果不在按钮上,修改按钮状态
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //弹出菜单关闭
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->bDown = FALSE;
				pMenuBar->pBtnTop = NULL;
			}
		}
	}
	return FALSE;
}

VOID CALLBACK MenuWnd_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (IDT_MENU == idEvent) //从主菜单弹出
	{
		window_ *pWindow = (window_*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		popupMenuWindow_ *pObj = (popupMenuWindow_*)pWindow;

		if (pObj->selItemID == pObj->enterItemID) //对比确保弹出子菜单时选择项正确
		{
			if ((GetTickCount() - pObj->enterTiemr) >= 500)
			{
				menu_ *pItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, pObj->enterItemID);
				if ((pItem->state & XM_POPUP) && NULL == pObj->pChildWnd)
				{
					pItem->state |= XM_SELECT;
					RECT rc;
					GetWindowRect(hwnd, &rc);
					pObj->pChildWnd = MenuChildWnd_Popup(pObj, &pObj->window, pItem->id, rc.right + 1, rc.top + pItem->rcItem.top);
					//XWnd_RedrawWnd(pWindow);
				}
			}
		}
		else
		{
			//XTRACE("MenuWnd_TimerProc() 超时\n");
		}
		KillTimer(hwnd, idEvent);
	}
}

BOOL MenuWnd_computeSize(HWINDOW hWindow, int &width, int &height)
{
	popupMenuWindow_ *pObj = (popupMenuWindow_*)hWindow;

	//计算显示位置---
	int countItem = XMTree_BeginTraverseInfo(pObj->hMTreeData, XMENU_ROOT);
	if (countItem < 1) return FALSE;

	menu_  *pItem = NULL;
	//计算窗口宽度
	for (int i = 0; i < countItem; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseInfo(pObj->hMTreeData, i);
		if (pItem->len > width)
			width = pItem->len;

		//XTRACE("id=%d \n", pItem->id);
	}

	width += pObj->pMenuData->leftWidth;  //增加左边显示菜单项图标的,灰色区域宽度
	width += pObj->pMenuData->leftText;   //增加菜单项文本左间隔
	width += 30;           //增加菜单项,弹出项图标宽度

	int left = 2;
	height = 3;
	for (int i = 0; i < countItem; i++)
	{
		HXCGUI hNode = NULL;
		pItem = (menu_*)XMTree_GetTraverseInfo(pObj->hMTreeData, i, &hNode);

		if (pItem->state & XM_SEPARATOR) //分割栏
		{
			pItem->rcItem.left = left;
			pItem->rcItem.top = height;
			pItem->rcItem.right = left + width;
			pItem->rcItem.bottom = height + 4;
			height += 4;
		}
		else
		{
			pItem->rcItem.left = left;
			pItem->rcItem.top = height;
			pItem->rcItem.right = left + width;
			pItem->rcItem.bottom = height + pObj->pMenuData->height;

			height += pObj->pMenuData->height;
		}
	}

	XMTree_EndTraverseInfo(pObj->hMTreeData);

	width += 6;
	height += 3;
	return TRUE;
}

void MenuWnd_AdjustPosition(HWINDOW hWindow, int &x, int &y, int width, int height, int uFlags) //计算调整显示位置，以便适应显示范围
{
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	switch (uFlags)  //显示方向  //检测调整显示位置
	{
	case XM_LEFT_TOP:
	{
		int right = x + width;
		int bottom = y + height;
		if (right > rect.right)
		{
			x = x - width;
		}
		if (bottom > rect.bottom)
		{
			y = y - height;
		}
	}
	break;  //位置保存不变
	case XM_LEFT_BOTTOM:
	{
		y = y - height;

		int top = y;
		int right = x + width;
		if (top < rect.top)
		{
			y = top + height;
		}
		if (right > rect.right)
		{
			x = x - width;
		}
	}
	break;
	case XM_RIGHT_TOP:
	{
		x = x - width;
		int left = x;
		int bottom = y + height;
		if (left < rect.left)
		{
			x = x + width;
		}
		if (bottom > rect.bottom)
		{
			y = y - height;
		}
	}break;
	case XM_RIGHT_BOTTOM:
	{
		x = x - width; y = y - height;
		int left = x;
		int top = y;
		if (left < rect.left)
		{
			x = x + width;
		}
		if (top < rect.top)
		{
			y = y + height;
		}
	}
	break;
	case XM_CENTER_LEFT:
	{
		y = y - (height / 2);
		int right = x + width;
		if (right > rect.right)
		{
			x = x - width;
		}
	}
	break;
	case XM_CENTER_TOP:
	{
		x = x - (width / 2);
		int bottom = y + height;
		if (bottom > rect.bottom)
		{
			y = y - height;
		}
	}
	break;
	case XM_CENTER_RIGHT:
	{
		x = x - width; y = y - (height / 2);
		int left = x;
		if (left < rect.left)
		{
			x = x + width;
		}
	}
	break;
	case XM_CENTER_BOTTOM:
	{
		x = x - (width / 2); y = y - height;
		int top = y;
		if (top < rect.top)
		{
			y = y + height;
		}
	}
	break;
	}
}

/////////childMenuWnd//////////////////////////////////////////////////////////
BOOL MenuChildWnd_computeSize(popupMenuChildWindow_ *pObj, int &width, int &height) //计算弹出菜单窗口大小
{
	menu_ *pItem = NULL;

	int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
	if (count < 1)
	{
		XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);
		return FALSE;
	}

	//计算显示位置
	for (int i = 0; i < count; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);

		if (pItem->len > width)
			width = pItem->len;
		pItem->state &= ~XM_SELECT;
	}
	width += pObj->pMainWnd->pMenuData->leftWidth;  //增加左边显示菜单项图标的,灰色区域宽度
	width += pObj->pMainWnd->pMenuData->leftText;   //增加菜单项文本左间隔
	width += 30;           //增加菜单项,弹出项图标宽度

	int left = 3;
	height = 3;
	for (int i = 0; i < count; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);
		if (pItem->state & XM_SEPARATOR) //分割栏
		{
			pItem->rcItem.left = left;
			pItem->rcItem.top = height;
			pItem->rcItem.right = left + width;
			pItem->rcItem.bottom = height + 4;
			height += 4;
		}
		else
		{
			pItem->rcItem.left = left;
			pItem->rcItem.top = height;
			pItem->rcItem.right = left + width;
			pItem->rcItem.bottom = height + pObj->pMainWnd->pMenuData->height;

			height += pObj->pMainWnd->pMenuData->height;
		}
	}

	XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);

	width += 6;
	height += 3;
	return TRUE;
}

void MenuChildWnd_AdjustPosition(popupMenuChildWindow_ *pObj, int &x, int &y, int width, int height)
{
	RECT rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);

	RECT rcLast;
	if (pObj->pPreviouWnd)
	{
		::GetWindowRect(pObj->pPreviouWnd->window.hWnd, &rcLast);
	}
	else
	{
		::GetWindowRect(pObj->pMainWnd->window.hWnd, &rcLast);
	}

	int top = y;
	if (top < rcWorkArea.top)
	{
		y = rcWorkArea.top;
	}

	int right = x + width;
	if (right > rcWorkArea.right)
	{
		x = rcLast.left - width - 1;
	}

	int bottom = y + height;
	if (bottom > rcWorkArea.bottom)
	{
		y = rcWorkArea.bottom - height;
	}
}

popupMenuChildWindow_* MenuChildWnd_Popup(popupMenuWindow_  *pMainWnd, window_ *pParentWnd, int parentItemId, int x, int y)
{
	popupMenuChildWindow_ *pObj = (popupMenuChildWindow_*)malloc(sizeof(popupMenuChildWindow_));

	if (NULL == pObj)
		return NULL;

	memset(pObj, 0, sizeof(popupMenuChildWindow_));
	//pObj->window.exType=XC_POPUPMENUCHILDWINDOW;

	pObj->selItemID = -1;
	pObj->pMainWnd = pMainWnd;
	pObj->parentItemId = parentItemId;
	//计算显示位置

	int width = 0;
	int height = 0;
	BOOL res = MenuChildWnd_computeSize(pObj, width, height);
	if (FALSE == res)
	{
		free(pObj);
		return NULL;
	}

	MenuChildWnd_AdjustPosition(pObj, x, y, width, height);

	//创建窗口
	res = MenuChildWnd_Init((HWINDOW)&pObj->window, x, y, width, height, pMainWnd->window.hWnd, XC_POPUPMENUCHILDWINDOW);
	if (res)
	{
		MenuWnd_UpdateUI((HWINDOW)&pMainWnd->window, parentItemId); //更新UI
		XWnd_SetWindowPos((HWINDOW)&pObj->window, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		return pObj;
	}

	return NULL;
}

BOOL MenuChildWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, HWND hWndParent, int exType)
{
	BOOL res = Wnd_Init(hWindow, WS_EX_TOPMOST | WS_EX_TOOLWINDOW, NULL, L"popupMenu", WS_POPUP, x, y, cx, cy, hWndParent, 0, exType);
	if (res)
	{
		AddTypeDebug(hWindow, XC_POPUPMENUCHILDWINDOW);

		XWnd_SetCaptionHeight(hWindow, 0);
		XWnd_SetBorderSize(hWindow, 0, 0, 0, 0);

		XWnd_RegisterMessage(hWindow, WM_PAINT, MenuChildWnd_OnDrawWindow);
		//XWnd_RegisterMessage(hWindow,WM_SYSKEYDOWN,MenuChildWnd_OnWndSysKeyDown);

		/////////////////////////////////////////////////////////
		popupMenuChildWindow_ *pObj = (popupMenuChildWindow_*)hWindow;
		menu_ *pItem = NULL;
		int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
		if (pObj->pMainWnd->pMenuData->pUpdateUI) //用户自绘菜单项
		{
			for (int i = 0; i < count; i++)
			{
				pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
				if (pObj->pMainWnd->pMenuData->pClass_Fun_Info)
				{
					eventOrMsg_  event_;
					event_.hMenu = (HMENUX)pObj->pMainWnd->pMenuData;
					event_.hEventEle = NULL;
					event_.wParam = (WPARAM)pItem->id;
					event_.lParam = NULL;
					event_.pClass_fun = pObj->pMainWnd->pMenuData->pClass_Fun_Info;
					((pFunClassEventMsg)pObj->pMainWnd->pMenuData->pDrawItem)(&event_, xc_fun_v_x_menu_i);
				}
				else
				{
					pObj->pMainWnd->pMenuData->pUpdateUI((HMENUX)pObj->pMainWnd->pMenuData, pItem->id);
				}
#else
				pObj->pMainWnd->pMenuData->pUpdateUI((HMENUX)(pObj->pMainWnd->pMainWnd->pMenuData), pItem->id);
#endif
			}
		}
		XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK MenuChildWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	popupMenuChildWindow_ *pObj = (popupMenuChildWindow_*)hWindow;

	if (pObj->pMainWnd->pMenuData->pDrawBG) //用户自绘菜单背景
	{
		menu_drawBG_  drawBG;
		drawBG.hWindow = hWindow;
		drawBG.hDraw = hDraw;
		drawBG.parentItemId = pObj->parentItemId;
		drawBG.hImage = pObj->pMainWnd->pMenuData->hBkImage;

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		if (pObj->pMainWnd->pMenuData->pClass_Fun_Info_drawBG)
		{
			eventOrMsg_  event_;
			event_.hMenu = (HMENUX)pObj->pMainWnd->pMenuData;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)&drawBG;
			event_.lParam = NULL;
			event_.pClass_fun = pObj->pMainWnd->pMenuData->pClass_Fun_Info_drawBG;
			((pFunClassEventMsg)pObj->pMainWnd->pMenuData->pDrawBG)(&event_, xc_fun_v_x_menu_item);
		}
		else
		{
			pObj->pMainWnd->pMenuData->pDrawBG((HMENUX)pObj->pMainWnd->pMenuData, &drawBG);
		}
#else
		pObj->pMainWnd->pMenuData->pDrawBG((HMENUX)(pObj->pMainWnd->pMainWnd->pMenuData), &drawItem);
#endif
	}
	else //系统绘制
	{
		MenuWnd_DrawBackground((window_*)hWindow, hDraw, pObj->pMainWnd->pMenuData->hBkImage);
	}

	menu_ *pItem = NULL;
	int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
	if (pObj->pMainWnd->pMenuData->pDrawItem) //用户自绘菜单项
	{
		for (int i = 0; i < count; i++)
		{
			//menu_ *pItem=(menu_*)XMTree_GetTraverseData(pObj->hMTreeData,i);
			pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);
			menu_drawItem_  drawItem;
			drawItem.hWindow = hWindow;
			drawItem.hDraw = hDraw;
			drawItem.id = pItem->id;
			drawItem.state = pItem->state;
			drawItem.rcItem = pItem->rcItem;
			drawItem.hImage = pItem->hImage;
			if (pItem->hString)
				drawItem.pText = XStr_GetBuffer(pItem->hString);
			else
				drawItem.pText = NULL;

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			if (pObj->pMainWnd->pMenuData->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hMenu = (HMENUX)pObj->pMainWnd->pMenuData;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)&drawItem;
				event_.lParam = NULL;
				event_.pClass_fun = pObj->pMainWnd->pMenuData->pClass_Fun_Info;
				((pFunClassEventMsg)pObj->pMainWnd->pMenuData->pDrawItem)(&event_, xc_fun_v_x_menu_item);
			}
			else
			{
				pObj->pMainWnd->pMenuData->pDrawItem((HMENUX)pObj->pMainWnd->pMenuData, &drawItem);
			}
#else
			pObj->pMainWnd->pMenuData->pDrawItem((HMENUX)(pObj->pMainWnd->pMainWnd->pMenuData), &drawItem);
#endif
		}
	}
	else //系统绘制
	{
		for (int i = 0; i < count; i++)
		{
			pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);
			menu_drawItem_  drawItem;
			drawItem.hWindow = hWindow;
			drawItem.hDraw = hDraw;
			drawItem.id = pItem->id;
			drawItem.state = pItem->state;
			drawItem.rcItem = pItem->rcItem;
			drawItem.hImage = pItem->hImage;
			if (pItem->hString)
				drawItem.pText = XStr_GetBuffer(pItem->hString);
			else
				drawItem.pText = NULL;

			//自绘
			MenuWnd_DrawItem((HWINDOW)pObj->pMainWnd, hDraw, &drawItem);
		}
	}
	XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);
	return TRUE;
}

void MenuChildWnd_OnLButtonUp(popupMenuChildWindow_ *pObj, POINT *pPt)
{
	POINT pt = { pPt->x,pPt->y };
	menu_ *pItem = NULL;

	BOOL bYes = FALSE;
	int iItem = -1;
	int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
	for (int i = 0; i < count; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);
		if (PtInRect(&pItem->rcItem, pt))
		{
			if ((pItem->state & XM_DISABLED) || (pItem->state & XM_POPUP) || (pItem->state & XM_SEPARATOR))
			{
				break;
			}
			bYes = TRUE;
			iItem = pItem->id;
			break;
		}
	}
	XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);

	if (bYes)
	{
		HELE        hParentEle = pObj->pMainWnd->pMenuData->hParentEle;
		HWND        hParentWnd = GetParent(pObj->pMainWnd->window.hWnd);
		popupMenu_  *pMenu = pObj->pMainWnd->pMenuData;
		HELE        hMenuBar = pMenu->hMenuBar;

		MenuWnd_OnDestroyWindow(pObj->pMainWnd->window.hWnd, pMenu);
		if (hParentEle)
		{
			Ele_SendEvent(hParentEle, XE_MENUSELECT, iItem, 0);
		}
		else if (hParentWnd)
		{
			SendMessage(hParentWnd, XWM_MENUSELECT, iItem, 0);
		}
		MenuWnd_OnExitMenu(hParentEle, hParentWnd);
		MenuWnd_OnDestroyMenu(pMenu);

		if (hMenuBar) //检查是否按在菜单条按钮上,如果不在按钮上,修改按钮状态
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //弹出菜单关闭
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->bDown = FALSE;
				pMenuBar->pBtnTop = NULL;
			}
		}
	}
}

void MenuChildWnd_OnMouseMove(popupMenuChildWindow_ *pObj, POINT *pPt)
{
	//pPt: 基于当前窗口客户区坐标
	POINT pt = { pPt->x,pPt->y };
	menu_ *pItem = NULL;
	int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
	for (int i = 0; i < count; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);
		if (PtInRect(&pItem->rcItem, pt))
		{
			break;
		}
		pItem = NULL;
	}

	if (pItem)
	{
		if (pObj->selItemID != pItem->id)
		{
			if (pObj->pChildWnd) //关闭子菜单
			{
				popupMenuChildWindow_  *pChildWnd = pObj->pChildWnd;
				while (pChildWnd)
				{
					::PostMessage(pChildWnd->window.hWnd, WM_CLOSE, 0, 0);
					pChildWnd = pChildWnd->pChildWnd;
				}
				pObj->pChildWnd = NULL;
			}
			//修改先前选择项状态
			if (pObj->selItemID >= 0)
			{
				menu_ *pOldSelItem = (menu_*)XMTree_GetNodeData(pObj->pMainWnd->hMTreeData, pObj->selItemID);
				pOldSelItem->state &= ~XM_SELECT;
			}

			if (pItem->state & XM_SEPARATOR) //分割栏
			{
				pObj->selItemID = -1;
			}
			else //修改当前项状态
			{
				pItem->state |= XM_SELECT;
				pObj->selItemID = pItem->id;
				if (pItem->state & XM_POPUP) //弹出
				{
					if (pItem->state & XM_POPUP)	//弹出
					{
						pObj->enterTiemr = GetTickCount();
						pObj->enterItemID = pItem->id;
						SetTimer(pObj->window.hWnd, IDT_MENU2, 500, MenuChildWnd_TimerProc);
					}
				}
			}
			XWnd_RedrawWnd((HWINDOW)&pObj->window);
		}
	}

	XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);
}

VOID CALLBACK MenuChildWnd_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (IDT_MENU2 == idEvent)
	{
		window_ *pWindow = (window_*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (NULL == pWindow)
		{
			return;
		}
		popupMenuChildWindow_ *pObj = (popupMenuChildWindow_*)pWindow;

		if (pObj->selItemID == pObj->enterItemID)
		{
			if ((GetTickCount() - pObj->enterTiemr) >= 500)
			{
				menu_ *pItem = (menu_*)XMTree_GetNodeData(pObj->pMainWnd->hMTreeData, pObj->enterItemID);
				if ((pItem->state & XM_POPUP) && NULL == pObj->pChildWnd)
				{
					RECT rc;
					GetWindowRect(pObj->window.hWnd, &rc);
					pObj->pChildWnd = MenuChildWnd_Popup(pObj->pMainWnd, &pObj->pMainWnd->window,
						pItem->id, rc.right + 1, rc.top + pItem->rcItem.top);
					pObj->pChildWnd->pPreviouWnd = pObj;
				}
			}
		}
		else
		{
			//XTRACE("MenuChildWnd_TimerProc() 超时\n");
		}
		KillTimer(hwnd, idEvent);
	}
}
