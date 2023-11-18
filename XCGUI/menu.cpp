/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup menu �����˵�
/// @ingroup groupWindows
/// @{

/// @brief �����˵�.Ĭ�ϵ����˵����ڹرպ��Զ�����.
/// @return �˵����.
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
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
void WINAPI XMenu_SetUserDrawItemEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի�˵���
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawItem = (pFunMenu_DrawItem)pCallBackFun;
	((popupMenu_*)hMenu)->pClass_Fun_Info = pClass_Fun_Info;
}

void WINAPI XMenu_SetUserDrawBGEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի�˱���
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

/// @brief ��Ӳ˵���.
/// @param hMenu �˵���Դ���.
/// @param id    �˵���ID.
/// @param pText   �ı�����.
/// @param parentId  ����ID,XMENU_ROOTΪ���ڵ�.
/// @param uFlags ��ʶ.
void WINAPI XMenu_AddItem(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	Menu_AddItemX(hMenu, id, pText, parentId, uFlags, 0);
}

/// @brief ��Ӳ˵���,��ͼ��.
/// @param hMenu �˵���Դ���.
/// @param id    �˵���ID.
/// @param pText   �ı�����.
/// @param parentId  ����ID,XMENU_ROOTΪ���ڵ�.
/// @param uFlags ��ʶ.
/// @param hImage ͼƬ���.
void WINAPI XMenu_AddItemImage(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage) //���Ӳ˵���
{
	IsMenuDebug(hMenu, __FUNCTION__);
	Menu_AddItemX(hMenu, id, pText, parentId, uFlags, hImage);
}

/// @brief ����˵��ָ����ǰ��.
/// @param hMenu �˵���Դ���.
/// @param id    �˵���ID.
/// @param pText   �ı�����.
/// @param uFlags  ��ʶ.
/// @param insertID ���뵽�����ǰ��λ��.
void WINAPI XMenu_InsertItem(HMENUX hMenu, int id, wchar_t *pText, int uFlags, int insertID)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pObj = (popupMenu_*)hMenu;

	menu_  *pItem = (menu_*)malloc(sizeof(menu_));
	memset(pItem, 0, sizeof(menu_));
	pItem->id = id;
	pItem->state = uFlags;
	pItem->hString = XStr_Create();
	if (FALSE == (XM_SEPARATOR & uFlags)) //�ָ���
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

/// @brief ����˵��ָ����ǰ��,����ָ��ͼ��.
/// @param hMenu �˵����.
/// @param id    �˵���ID.
/// @param pText   �ı�����.
/// @param uFlags  ��ʶ.
/// @param insertID ���뵽�����ǰ��λ��.
/// @param hImage   ͼƬ���.
void WINAPI XMenu_InsertItemImage(HMENUX hMenu, int id, wchar_t *pText, int uFlags, int insertID, HIMAGE hImage) //���Ӳ˵���
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
	if (hImage) //ͼƬ���ļ�
	{
		Image_AddImage(pItem->hImage, hImage);
		//	pItem->hImage=hImage; //new Image(pImageName); 
	}
	XMTree_InsertNode(pObj->hMTreeData, pItem, id, insertID);
}

/// @brief ɾ���˵���.
/// @param hMenu �˵����.
/// @param id    �˵���ID.
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

/// @brief ���ò˵�����Զ�����.
/// @param hMenu  �˵����.
/// @param bAuto  ֵΪTRUE���˵��������ڹرպ�,���Զ����ٲ˵����,�����෴.
void WINAPI XMenu_SetAutoDestroy(HMENUX hMenu, BOOL bAuto) //�Ƿ��Զ����ٶ���
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->bAutoDestroy = bAuto;
}

/// @brief ���ò˵���߶�.
/// @param hMenu  �˵����.
/// @param height �˵���߶�.
void WINAPI XMenu_SetItemHeight(HMENUX hMenu, int height) //���ò˵���߶�
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->height = height;
}

/// @brief ���ò˵����ڱ���ͼƬ.
/// @param hMenu  �˵����.
/// @param hImage ͼƬ���.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XMenu_SetBGImage(HMENUX hMenu, HIMAGE hImage) //���ò˵�����ͼƬ
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

/// @brief ���ò˵���ͼ��.
/// @param hMenu  �˵����.
/// @param id    �˵���ID.
/// @param hImage ͼƬ���
/// @return �ɹ�����TRUE,�����෴..
BOOL WINAPI XMenu_SetItemImage(HMENUX hMenu, int id, HIMAGE hImage) //������ͼ��
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

/// @brief ���ò˵����ı�.
/// @param hMenu  �˵����.
/// @param id    �˵���ID.
/// @param pText �ı�����
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XMenu_SetItemText(HMENUX hMenu, int id, wchar_t *pText) //�������ı�
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

/// @brief ���ò˵�������.
/// @param hMenu  �˵����.
/// @param id    �˵���ID.
/// @param uFlags ��ʶ.
void WINAPI XMenu_SetItemFlags(HMENUX hMenu, int id, int uFlags)   //����������
{
	IsMenuDebug(hMenu, __FUNCTION__);
	popupMenu_ *pMenu = (popupMenu_*)hMenu;
	menu_ *pItem = (menu_*)XMTree_GetNodeData(pMenu->hMTreeData, id);
	if (pItem)
	{
		pItem->state = uFlags;
	}
}

/// @brief ��ȡ�˵�������.
/// @param hMenu  �˵����.
/// @param id    �˵���ID.
/// @return uFlags ��ʶ.
int  WINAPI XMenu_GetItemFlags(HMENUX hMenu, int id)   //��ȡ������
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

/// @brief ���ò˵��ѡ״̬.
/// @param hMenu  �˵����.
/// @param id  �˵���ID
/// @param bCheck    ��ѡTRUE,�ǹ�ѡFALSE.
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

/// @brief �жϲ˵����Ƿ�ѡ.
/// @param hMenu  �˵����.
/// @param id  �˵���ID
/// @return �����ѡ����TRUE,���򷵻�FALSE.
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

/// @brief ��ȡ�˵���߶�.
/// @param hMenu  �˵����.
/// @return �˵���߶�.
int WINAPI XMenu_GetItemHeight(HMENUX hMenu)  //��ȡ�˵���߶�
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return ((popupMenu_*)hMenu)->height;
}

/// @brief ��ȡ�˵�������,�����Ӳ˵���.
/// @param hMenu  �˵����.
/// @return �˵�������.
int WINAPI XMenu_GetItemCount(HMENUX hMenu) //��ȡ�˵�������
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return XMTree_GetNodeCount(((popupMenu_*)hMenu)->hMTreeData, XMTREE_ROOT);
}

/// @brief ��ȡ���������.
/// @param hMenu  �˵����.
/// @return ���������.
int  WINAPI XMenu_GetItemLeftWidth(HMENUX hMenu) //��ȡ�����
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return ((popupMenu_*)hMenu)->leftWidth;
}

/// @brief ��ȡ�˵����ı�����.
/// @param hMenu  �˵����.
/// @return �˵����ı�����.
int  WINAPI XMenu_GetItemLeftText(HMENUX hMenu)  //��ȡ�˵����ı�����
{
	IsMenuDebug(hMenu, __FUNCTION__);
	return ((popupMenu_*)hMenu)->leftText;
}

/// @brief ��ȡ�˵����ı�����.
/// @param hMenu  �˵����.
/// @param id    �˵���ID.
/// @return �˵����ı�����..
wchar_t* WINAPI XMenu_GetItemText(HMENUX hMenu, int id) //��ȡ�˵����ı�
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

/// @brief �رյ����˵�����,�������ٲ˵����,Ĭ������µ����˵����ڹرպ�,���Զ����ٲ˵����.
/// @param hMenu  �˵����.
void WINAPI XMenu_CloseMenu(HMENUX hMenu)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	if (((popupMenu_*)hMenu)->hMenuWindow)
		PostMessage(((window_*)((popupMenu_*)hMenu)->hMenuWindow)->hWnd, WM_CLOSE, 0, 0);
}
/// @brief ���ٲ˵����,�ͷŲ˵���Դ.
/// @param hMenu  �˵����.
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

#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	if (pObj->pClass_Fun_Info)
		free(pObj->pClass_Fun_Info);
	if (pObj->pClass_Fun_Info_drawBG)
		free(pObj->pClass_Fun_Info_drawBG);
#endif

	free(hMenu);
}

/// @brief �����û��Ի�˵���.
/// @param hMenu  �˵����.
/// @param pFunDrawItem  �Ի溯����.��������:
/// @code  void CALLBACK Menu_DrawItem(HMENUX hMenu,menu_drawItem_ *pDrawItem); @endcode
void WINAPI XMenu_SetUserDrawItem(HMENUX hMenu, pFunMenu_DrawItem pFunDrawItem) //�����û��Ի���
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	((popupMenu_*)hMenu)->pClass_Fun_Info = NULL;
#endif
}

/// @brief �����û��Ի�˱���.
/// @param hMenu  �˵����.
/// @param pFunDrawBG  �Ի溯����.��������:
/// @code  void CALLBACK Menu_DrawBG(HMENUX hMenu,menu_drawBG_ *pDrawBG); @endcode
void WINAPI XMenu_SetUserDrawBG(HMENUX hMenu, pFunMenu_DrawBG pFunDrawBG) //�����û��Ի�˵�����
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pDrawBG = pFunDrawBG;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	((popupMenu_*)hMenu)->pClass_Fun_Info_drawBG = NULL;
#endif
}

void WINAPI XMenu_SetUserUpdateUI(HMENUX hMenu, pFunMenu_UpdateUI pUpdateUI)
{
	IsMenuDebug(hMenu, __FUNCTION__);
	((popupMenu_*)hMenu)->pUpdateUI = pUpdateUI;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	((popupMenu_*)hMenu)->pClass_Fun_Info_updateUI = NULL;
#endif
}

/// @brief �����˵�.
/// @param hMenu  �˵����.
/// @param hParentWnd  �����ھ��.
/// @param x  �����˵�x����.
/// @param y  �����˵�y����.
/// @param hParentEle ��Ԫ����Դ���,�����ֵ��ΪNULL,hParentEleԪ�ؽ����ղ˵���Ϣ�¼�,
///     ������hParentWindow���ڽ��ղ˵�����Ϣ�¼�
/// @param uFlags ��ʶ.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XMenu_Popup(HMENUX hMenu, HWND hParentWnd, int x, int y, HELE hParentEle, int uFlags) //�����˵�
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

		//�˵������¼�
		MenuWnd_UpdateUI(hMenuWindow, XMENU_ROOT); //����UI

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

void Menu_AddItemX(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage) //���Ӳ˵���
{
	popupMenu_ *pObj = (popupMenu_*)hMenu;

	menu_  *pItem = (menu_*)malloc(sizeof(menu_));
	pItem->id = id;
	pItem->parentId = parentId;
	pItem->hImage = NULL;
	pItem->state = uFlags;

	if (parentId > XMENU_ROOT) //���������ӵ�����ʶ
	{
		menu_ *pParentItem = (menu_*)XMTree_GetNodeData(pObj->hMTreeData, parentId);
		if (NULL == pParentItem)
		{
			MessageBox(NULL, L"�Ųʽ����-������ʾ:API:XMenu_AddItem*()�в���[parentId]����!", L"��ʾ", 0);
		}
		if (FALSE == (pParentItem->state & XM_POPUP))
		{
			pParentItem->state |= XM_POPUP;
		}
	}

	if (XM_SEPARATOR & uFlags) //�ָ���
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
		if (hImage) //ͼƬ���ļ�
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

	//������ʾλ��---
	int countItem = XMTree_BeginTraverseInfo(pObject->hMTreeData, parentID);
	if (countItem < 1) return FALSE;

	menu_  *pItem = NULL;
	//���㴰�ڿ��
	for (int i = 0; i < countItem; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseInfo(pObject->hMTreeData, i);
		if (pItem->len > size.cx)
			size.cx = pItem->len;

		//XTRACE("id=%d \n", pItem->id);
	}

	size.cx += pObject->leftWidth;  //���������ʾ�˵���ͼ���,��ɫ������
	size.cx += pObject->leftText;   //���Ӳ˵����ı�����
	size.cx += 30;           //���Ӳ˵���,������ͼ����

	int left = 2;
	for (int i = 0; i < countItem; i++)
	{
		HXCGUI hNode = NULL;
		pItem = (menu_*)XMTree_GetTraverseInfo(pObject->hMTreeData, i, &hNode);
		pItem->state &= ~XM_SELECT;
		if (pItem->state & XM_SEPARATOR) //�ָ���
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

void Menu_AdjustPosition(int &x, int &y, int width, int height, int uFlags) //���������ʾλ�ã��Ա���Ӧ��ʾ��Χ
{
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	switch (uFlags)  //��ʾ����  //��������ʾλ��
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
	break;  //λ�ñ��治��
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
	if (pObj->pMenuData->pUpdateUI) //�û��Ի�˵���
	{
		for (int i = 0; i < count; i++)
		{
			menu_ *pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
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

	if (pObj->pMenuData->pDrawBG) //�û��Ի汳��
	{
		menu_drawBG_ drawBG;
		drawBG.hWindow = hWindow;
		drawBG.hDraw = hDraw;
		drawBG.parentItemId = -1;
		drawBG.hImage = pObj->pMenuData->hBkImage;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
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
	else //ϵͳ����
	{
		MenuWnd_DrawBackground((window_*)hWindow, hDraw, pObj->pMenuData->hBkImage);
	}

	//////////////////////////////////////////////////////////////////
	int count = XMTree_BeginTraverse(pObj->hMTreeData, XMENU_ROOT);
	if (pObj->pMenuData->pDrawItem) //�û��Ի�˵���
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

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
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
	else //ϵͳ����
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

			//�Ի�
			MenuWnd_DrawItem(hWindow, hDraw, &drawItem);
		}
	}

	XMTree_EndTraverse(pObj->hMTreeData);
	return TRUE;
}

void MenuWnd_DrawItem(HWINDOW hWindow, HDRAW hDraw, menu_drawItem_ *pItem)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);
	if (pItem->state & XM_SEPARATOR) //�ָ���
	{
		HPEN hPen1 = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(200, 200, 200));
		HGDIOBJ hOld1 = XDraw_SelectObject_(hDraw, hPen1);

		XDraw_MoveToEx_(hDraw, pObj->pMenuData->leftWidth + 2, pItem->rcItem.top + 1, 0);
		XDraw_LineTo_(hDraw, pItem->rcItem.right - 5, pItem->rcItem.top + 1);

		//SelectObject(hdc,hOld1);
		//DeleteObject(hPen1);
		return;
	}

	if (pItem->state & XM_SELECT) //ѡ����
	{
		XDraw_GradientFill2_(hDraw, RGB(63, 151, 216), RGB(48, 134, 198), &pItem->rcItem, GRADIENT_FILL_RECT_V);
	}

	if (pItem->state & XM_POPUP) //������
	{
		//����������
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

	if (pItem->state &XM_CHECK) //��ѡ
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
	if (pItem->state & XM_DISABLED)//������
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

void MenuWnd_DrawBackground(window_ *pWindow, HDRAW hDraw, HIMAGE hImage) //���Ʋ˵�����
{
	RECT rc;
	GetClientRect(pWindow->hWnd, &rc);
	//���Ʊ���ɫ-----------------------
	XDraw_FillSolidRect_(hDraw, &rc, RGB(255, 255, 255));

	//������߻�ɫ����------------------
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

	if (hImage) //����ͼƬ
	{
		XDraw_HImage_(hDraw, hImage, 0, 0);
	}

	//���Ʊ߿�---------------------------
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
	//���Ͳ˵��˳���Ϣ
	if (hParentEle)
	{
		Ele_SendEvent(hParentEle, XE_MENUEXIT, 0, 0);
	}
	else if (hParentWnd)
	{
		SendMessage(hParentWnd, XWM_MENUEXIT, 0, 0);
	}
}

//pPt:��Ļ����
BOOL CALLBACK MenuWnd_OnLButtonDown(HWINDOW hWindow, POINT *pPt)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

	POINT ptScreen = *pPt;  //��Ļ����

	//�������Ƿ����Ӳ���
	RECT rcWindow;  //��������
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;

	if (pChildWnd)
	{
		while (pChildWnd->pChildWnd)    //�������һ���Ӳ˵�
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

	//����Ƿ������˵���
	GetClientRect(pObj->window.hWnd, &rcWindow);
	POINT ptClient = ptScreen; //�ͻ�������
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

	if (hMenuBar) //����Ƿ��ڲ˵�����ť��,������ڰ�ť��,�޸İ�ť״̬
	{
		menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
		if (pMenuBar->pBtnTop)
		{
			pMenuBar->pBtnTop->button.state = STATE_LEAVE;
			XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
		}
	}

	SendMessage(ptHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(ptClient2.x, ptClient2.y));

	if (hMenuBar) //�����˵��ر�
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

//pPt:��Ļ����
BOOL CALLBACK MenuWnd_OnLButtonUp(HWINDOW hWindow, POINT *pPt)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

	POINT ptSrceen = *pPt;

	RECT rcWindow;
	//�������Ƿ����Ӳ˵���
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;
	if (pChildWnd)
	{
		while (pChildWnd->pChildWnd) //�������һ���Ӳ˵�
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

	//�������Ƿ������˵���
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

		if (hMenuBar) //����Ƿ��ڲ˵�����ť��,������ڰ�ť��,�޸İ�ť״̬
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //�����˵��ر�
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

//pPt:��Ļ����
BOOL CALLBACK MenuWnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	if (FALSE == XC_IsHWINDOW(hWindow))
		return TRUE;

	//pPt: ���ڵ�ǰ���ڿͻ�������
	popupMenuWindow_ *pObj = (popupMenuWindow_*)hWindow;

	POINT pt = *pPt;
	POINT ptScreen = *pPt; //��Ļ�����
	ClientToScreen(pObj->window.hWnd, &ptScreen);
	RECT rcWindow;    //��������

	if (pObj->pMenuData->hMenuBar) //�˵���
	{
		MenuBar_OnMenuMouseMove(pObj->pMenuData->hMenuBar, &ptScreen);
	}

	//XTRACE("����ƶ� x=%d \n",pt.x);
	//---�������Ƿ����Ӵ�����
	popupMenuChildWindow_ *pChildWnd = pObj->pChildWnd;
	popupMenuChildWindow_ *pFinally = NULL; //���һ������
	if (pChildWnd)
	{
		if (FALSE == XC_IsHWINDOW(hWindow))
			return TRUE;

		while (pChildWnd->pChildWnd)  //������󴰿�
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

	//����Ƿ������˵���
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
	//pPt: ���ڵ�ǰ���ڿͻ�������
	int count = XMTree_BeginTraverse(pObj->hMTreeData, XMENU_ROOT);

	BOOL  bResult = FALSE;
	for (int i = 0; i < count; i++)
	{
		menu_ *pItem = (menu_*)XMTree_GetTraverseData(pObj->hMTreeData, i);
		if (PtInRect(&pItem->rcItem, pt))
		{
			if (pObj->selItemID != pItem->id)
			{
				if (pObj->pChildWnd) //�ر��Ӳ˵�
				{
					popupMenuChildWindow_  *pChildWnd = pObj->pChildWnd;
					while (pChildWnd)
					{
						::PostMessage(pChildWnd->window.hWnd, WM_CLOSE, 0, 0);
						pChildWnd = pChildWnd->pChildWnd;
					}
					pObj->pChildWnd = NULL;
				}
				if (pObj->selItemID >= 0) //ȡ����ǰѡ����
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
					if (pItem->state & XM_POPUP)	//����
					{
						pObj->enterTiemr = GetTickCount();
						pObj->enterItemID = pItem->id;
						SetTimer(pObj->window.hWnd, IDT_MENU, 500, MenuWnd_TimerProc);
						//	XTRACE("��������\n");
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

//pPt:��Ļ����
BOOL CALLBACK MenuWnd_OnRButtonDown(HWINDOW hWindow, POINT *pPt)
{
	popupMenuWindow_ *pObj = POPUPMENUWINDOW(hWindow);

	POINT ptScreen = *pPt;

	RECT rcWindow;
	//----�������Ƿ����Ӳ���
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

	//����Ƿ��ڴ�����
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

	if (hMenuBar) //����Ƿ��ڲ˵�����ť��,������ڰ�ť��,�޸İ�ť״̬
	{
		menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
		if (pMenuBar->pBtnTop)
		{
			pMenuBar->pBtnTop->button.state = STATE_LEAVE;
			XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
		}
	}

	SendMessage(ptHWND, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(ptClient2.x, ptClient2.y));

	if (hMenuBar) //�����˵��ر�
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

		if (hMenuBar) //����Ƿ��ڲ˵�����ť��,������ڰ�ť��,�޸İ�ť״̬
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //�����˵��ر�
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

		if (hMenuBar) //����Ƿ��ڲ˵�����ť��,������ڰ�ť��,�޸İ�ť״̬
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //�����˵��ر�
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
	if (IDT_MENU == idEvent) //�����˵�����
	{
		window_ *pWindow = (window_*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		popupMenuWindow_ *pObj = (popupMenuWindow_*)pWindow;

		if (pObj->selItemID == pObj->enterItemID) //�Ա�ȷ�������Ӳ˵�ʱѡ������ȷ
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
			//XTRACE("MenuWnd_TimerProc() ��ʱ\n");
		}
		KillTimer(hwnd, idEvent);
	}
}

BOOL MenuWnd_computeSize(HWINDOW hWindow, int &width, int &height)
{
	popupMenuWindow_ *pObj = (popupMenuWindow_*)hWindow;

	//������ʾλ��---
	int countItem = XMTree_BeginTraverseInfo(pObj->hMTreeData, XMENU_ROOT);
	if (countItem < 1) return FALSE;

	menu_  *pItem = NULL;
	//���㴰�ڿ��
	for (int i = 0; i < countItem; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseInfo(pObj->hMTreeData, i);
		if (pItem->len > width)
			width = pItem->len;

		//XTRACE("id=%d \n", pItem->id);
	}

	width += pObj->pMenuData->leftWidth;  //���������ʾ�˵���ͼ���,��ɫ������
	width += pObj->pMenuData->leftText;   //���Ӳ˵����ı�����
	width += 30;           //���Ӳ˵���,������ͼ����

	int left = 2;
	height = 3;
	for (int i = 0; i < countItem; i++)
	{
		HXCGUI hNode = NULL;
		pItem = (menu_*)XMTree_GetTraverseInfo(pObj->hMTreeData, i, &hNode);

		if (pItem->state & XM_SEPARATOR) //�ָ���
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

void MenuWnd_AdjustPosition(HWINDOW hWindow, int &x, int &y, int width, int height, int uFlags) //���������ʾλ�ã��Ա���Ӧ��ʾ��Χ
{
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	switch (uFlags)  //��ʾ����  //��������ʾλ��
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
	break;  //λ�ñ��治��
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
BOOL MenuChildWnd_computeSize(popupMenuChildWindow_ *pObj, int &width, int &height) //���㵯���˵����ڴ�С
{
	menu_ *pItem = NULL;

	int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
	if (count < 1)
	{
		XMTree_EndTraverse(pObj->pMainWnd->hMTreeData);
		return FALSE;
	}

	//������ʾλ��
	for (int i = 0; i < count; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);

		if (pItem->len > width)
			width = pItem->len;
		pItem->state &= ~XM_SELECT;
	}
	width += pObj->pMainWnd->pMenuData->leftWidth;  //���������ʾ�˵���ͼ���,��ɫ������
	width += pObj->pMainWnd->pMenuData->leftText;   //���Ӳ˵����ı�����
	width += 30;           //���Ӳ˵���,������ͼ����

	int left = 3;
	height = 3;
	for (int i = 0; i < count; i++)
	{
		pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);
		if (pItem->state & XM_SEPARATOR) //�ָ���
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
	//������ʾλ��

	int width = 0;
	int height = 0;
	BOOL res = MenuChildWnd_computeSize(pObj, width, height);
	if (FALSE == res)
	{
		free(pObj);
		return NULL;
	}

	MenuChildWnd_AdjustPosition(pObj, x, y, width, height);

	//��������
	res = MenuChildWnd_Init((HWINDOW)&pObj->window, x, y, width, height, pMainWnd->window.hWnd, XC_POPUPMENUCHILDWINDOW);
	if (res)
	{
		MenuWnd_UpdateUI((HWINDOW)&pMainWnd->window, parentItemId); //����UI
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
		if (pObj->pMainWnd->pMenuData->pUpdateUI) //�û��Ի�˵���
		{
			for (int i = 0; i < count; i++)
			{
				pItem = (menu_*)XMTree_GetTraverseData(pObj->pMainWnd->hMTreeData, i);

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
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

	if (pObj->pMainWnd->pMenuData->pDrawBG) //�û��Ի�˵�����
	{
		menu_drawBG_  drawBG;
		drawBG.hWindow = hWindow;
		drawBG.hDraw = hDraw;
		drawBG.parentItemId = pObj->parentItemId;
		drawBG.hImage = pObj->pMainWnd->pMenuData->hBkImage;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
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
	else //ϵͳ����
	{
		MenuWnd_DrawBackground((window_*)hWindow, hDraw, pObj->pMainWnd->pMenuData->hBkImage);
	}

	menu_ *pItem = NULL;
	int count = XMTree_BeginTraverse(pObj->pMainWnd->hMTreeData, pObj->parentItemId);
	if (pObj->pMainWnd->pMenuData->pDrawItem) //�û��Ի�˵���
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

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
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
	else //ϵͳ����
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

			//�Ի�
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

		if (hMenuBar) //����Ƿ��ڲ˵�����ť��,������ڰ�ť��,�޸İ�ť״̬
		{
			menuBar_ *pMenuBar = (menuBar_*)hMenuBar;
			if (pMenuBar->pBtnTop)
			{
				pMenuBar->pBtnTop->button.state = STATE_LEAVE;
				XEle_RedrawEle((HELE)&pMenuBar->pBtnTop->button);
			}
		}

		if (hMenuBar) //�����˵��ر�
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
	//pPt: ���ڵ�ǰ���ڿͻ�������
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
			if (pObj->pChildWnd) //�ر��Ӳ˵�
			{
				popupMenuChildWindow_  *pChildWnd = pObj->pChildWnd;
				while (pChildWnd)
				{
					::PostMessage(pChildWnd->window.hWnd, WM_CLOSE, 0, 0);
					pChildWnd = pChildWnd->pChildWnd;
				}
				pObj->pChildWnd = NULL;
			}
			//�޸���ǰѡ����״̬
			if (pObj->selItemID >= 0)
			{
				menu_ *pOldSelItem = (menu_*)XMTree_GetNodeData(pObj->pMainWnd->hMTreeData, pObj->selItemID);
				pOldSelItem->state &= ~XM_SELECT;
			}

			if (pItem->state & XM_SEPARATOR) //�ָ���
			{
				pObj->selItemID = -1;
			}
			else //�޸ĵ�ǰ��״̬
			{
				pItem->state |= XM_SELECT;
				pObj->selItemID = pItem->id;
				if (pItem->state & XM_POPUP) //����
				{
					if (pItem->state & XM_POPUP)	//����
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
			//XTRACE("MenuChildWnd_TimerProc() ��ʱ\n");
		}
		KillTimer(hwnd, idEvent);
	}
}
