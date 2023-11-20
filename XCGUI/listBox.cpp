/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup listBox �б��(ListBox)
/// @ingroup groupElements
/// @{

/// @brief �����б��Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XListBox_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	listBox_ *pObj = (listBox_*)malloc(sizeof(listBox_));
	memset(pObj, 0, sizeof(listBox_));

	ListBox_Init((HELE)pObj, x, y, cx, cy, XC_LISTBOX, hParent);
	return (HELE)pObj;
}

void ListBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_LISTBOX);
	listBox_ *pListBox = LISTBOX(hEle);
	pListBox->height = 20;
	pListBox->curSel = -1;
	pListBox->hImageList = NULL;
	pListBox->bAdjust = FALSE;
	pListBox->hArrayListItem = XArray_Create();
	pListBox->bLineHighlight = TRUE;
	pListBox->mouseStayId = -1;
	pListBox->selectItemColor = RGB(126, 206, 244);
	pListBox->mouseStayColor = RGB(192, 232, 250);

	XSView_SetDrawScrollView(hEle, ListBox_OnDrawScrollView);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, ListBox_OnLButtonDown);
	XEle_RegisterEvent(hEle, XE_DESTROY, ListBox_OnDestroy);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, ListBox_OnEleMouseMove);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, ListBox_OnEventMouseLeave);
}

void CALLBACK ListBox_OnDestroy(HELE hEle)  //����
{
	listBox_item_ *pItem = NULL;
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	for (int i = 0; i < count; i++)
	{
		pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, i);
		XStr_Destroy(pItem->hString);

		if (pItem->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pItem->hArrayBindEle);
			for (int j = 0; j < bindEleCount; j++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, j);
				free(pBindEle);
			}
			XArray_Destroy(pItem->hArrayBindEle);
		}

		free(pItem);
	}
	XArray_Destroy(LISTBOX(hEle)->hArrayListItem);

	if (LISTBOX(hEle)->hImageList)
		XImageList_Destroy(LISTBOX(hEle)->hImageList);

#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	if (LISTBOX(hEle)->pClass_Fun_Info)
		free(LISTBOX(hEle)->pClass_Fun_Info);
#endif
}

/// @brief ���һ���ַ������б�.
/// @param hEle   Ԫ�ؾ��.
/// @param pText  �ı�����.
/// @param imageId  ��ͼ��ID.
/// @return ������λ��.
int WINAPI XListBox_AddString(HELE hEle, wchar_t *pText, int imageId)  //����һ���ַ������б�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);

	if (NULL == pText) return -1;

	int len = wcslen(pText);
	//	if(len<1) return -1;

	if (len > 0)
	{
		HDC hdc;
		SIZE size;
		hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
		GetTextExtentPoint32(hdc, pText, len, &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

		if (size.cx > pObj->maxTextWidth)
			pObj->maxTextWidth = size.cx;
	}

	listBox_item_ *pItem = (listBox_item_*)malloc(sizeof(listBox_item_));
	memset(pItem, 0, sizeof(listBox_item_));
	pItem->hString = XStr_Create();
	XStr_SetString(pItem->hString, pText);
	pItem->imageID = imageId;

	XArray_Add(pObj->hArrayListItem, pItem);

	pObj->bAdjust = TRUE;
	return XArray_GetCount(pObj->hArrayListItem) - 1;
}

/// @brief ����һ���ַ������б�.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ����λ������.
/// @param pText  �ı�����.
/// @param imageId  ��ͼ��ID.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListBox_InsertString(HELE hEle, int index, wchar_t *pText, int imageId)
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);

	if (NULL == pText) return FALSE;

	int len = wcslen(pText);
	if (len < 1) return FALSE;

	if (index < 0)
		return FALSE;

	if (index > XArray_GetCount(pObj->hArrayListItem))
		return FALSE;

	HDC hdc;
	SIZE size;
	hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
	GetTextExtentPoint32(hdc, pText, len, &size);
	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (size.cx > pObj->maxTextWidth)
		pObj->maxTextWidth = size.cx;

	listBox_item_ *pItem = (listBox_item_*)malloc(sizeof(listBox_item_));
	memset(pItem, 0, sizeof(listBox_item_));
	pItem->hString = XStr_Create();
	XStr_SetString(pItem->hString, pText);
	pItem->imageID = imageId;

	XArray_insert(pObj->hArrayListItem, pItem, index);

	pObj->bAdjust = TRUE;
	return TRUE;;
}

/// @brief ��������.
/// @param hEle   Ԫ�ؾ��.
void WINAPI XListBox_Adjust(HELE hEle)
{
	IsListBoxDebug(hEle, __FUNCTION__);

	listBox_ *pObj = LISTBOX(hEle);

	pObj->bAdjust = FALSE;
	int count = Array_GetCount(pObj->hArrayListItem);

	int left = XSView_GetSpacingLeft(hEle) + 1 + XLISTBOX_LEFT;
	if (pObj->bCheck)
	{
		left += XLISTBOX_CHECK_SIZE;
		left += 3;
	}

	if (pObj->hImageList)
	{
		left += XImageList_GetWidth(pObj->hImageList);
		left += 3;
	}

	int right = XSView_GetSpacingRight(hEle) + 1 + XLISTBOX_RIGHT;
	XSView_SetSize(hEle, pObj->maxTextWidth + left + right, count*pObj->height);

	int posx = XSView_GetHViewPos(hEle);
	int posy = XSView_GetVViewPos(hEle);

	//�󶨵�Ԫ��
	for (int i = 0; i < count; i++)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, i);
		if (pItem->hArrayBindEle)
		{
			int bandEleCount = XArray_GetCount(pItem->hArrayBindEle);
			for (int j = 0; j < bandEleCount; j++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, j);
				((ele_*)pBindEle->hEle)->rect.left = pBindEle->left + posx;
				((ele_*)pBindEle->hEle)->rect.top = i*pObj->height + pBindEle->top + posy;
				((ele_*)pBindEle->hEle)->rect.right = ((ele_*)pBindEle->hEle)->rect.left + pBindEle->width;
				((ele_*)pBindEle->hEle)->rect.bottom = ((ele_*)pBindEle->hEle)->rect.top + pBindEle->height;
				((ele_*)pBindEle->hEle)->elePt.x = pBindEle->left;
				((ele_*)pBindEle->hEle)->elePt.y = i*pObj->height + pBindEle->top;
			}
		}
	}

}

/// @brief �����û��Ի��б����.
/// @param hEle   Ԫ�ؾ��.
/// @param pFunDrawItem �Ի溯����,��ʽ����:
/// @code void CALLBACK ListBox_DrawItem(HELE hEle,listBox_drawItem_ *pDrawItem); @endcode
void WINAPI XListBox_SetUserDrawItem(HELE hEle, pFunListBox_DrawItem pFunDrawItem) //�����û��Ի��б���
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	LISTBOX(hEle)->pClass_Fun_Info = NULL;
#endif
}

#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
void WINAPI XListBox_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի��б����
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->pDrawItem = (pFunListBox_DrawItem)pCallBackFun;
	LISTBOX(hEle)->pClass_Fun_Info = pClass_Fun_Info;
}
#endif

/// @brief ���û�رո�ѡ����.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable ֵΪTRUE����,�����෴.
void WINAPI XListBox_EnableCheckBox(HELE hEle, BOOL bEnable) //���ø�ѡ��
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->bCheck = bEnable;
	LISTBOX(hEle)->bAdjust = TRUE;
}

/// @brief ���û�ر��и�����ʾ.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable ֵΪTRUE����,�����෴.
void WINAPI XLsitBox_EnableLineHighlight(HELE hEle, BOOL bEnable)  //���û�ر��и�����ʾ
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->bLineHighlight = bEnable;
}

/// @brief �ж��б���ѡ���Ƿ�ѡ��.
/// @param hEle   Ԫ�ؾ��.
/// @param index  �б�������.
/// @return �����ѡ��ѡ��ΪTRUE,�����෴.
BOOL WINAPI XListBox_IsItemCheck(HELE hEle, int index)      //�ж���ĸ�ѡ���Ƿ�ѡ
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		return pItem->bCheck;
	}
	else
	{
		XERROR("XListBox_IsItemCheck(),����[index]����\n");
	}
	return FALSE;
}

/// @brief �����б����ĸ�ѡ��.
/// @param hEle   Ԫ�ؾ��.
/// @param index  �б�������.
/// @param bCheck ֵΪTRUE��ѡ��ѡ��,�����෴.
void WINAPI XListBox_SetItemCheck(HELE hEle, int index, BOOL bCheck) //������ĸ�ѡ��
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		pItem->bCheck = bCheck;
	}
	else
	{
		XERROR("XListBox_SetItemCheck(),����[index]����\n");
	}
}

/// @brief �������Ԫ��.
/// @param hEle   Ԫ�ؾ��.
/// @param index    ������.
/// @param pInfo    ��Ԫ����Ϣ
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListBox_SetItemBindEle(HELE hEle, int index, itemBindEle_ *pInfo) //��Ԫ��
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		if (NULL == pItem) return FALSE;

		if (NULL == XEle_GetParentEle(pInfo->hEle))
			XSView_AddEle(hEle, pInfo->hEle);

		itemBindEle_ *pBindEle = (itemBindEle_*)malloc(sizeof(itemBindEle_));
		pBindEle->hEle = pInfo->hEle;
		pBindEle->left = pInfo->left;
		pBindEle->top = pInfo->top;
		pBindEle->width = pInfo->width;
		pBindEle->height = pInfo->height;

		if (NULL == pItem->hArrayBindEle)
			pItem->hArrayBindEle = XArray_Create();

		XArray_Add(pItem->hArrayBindEle, pBindEle);
		return TRUE;
	}
	else
	{
		XERROR("XListBox_SetItemCheck(),����[index]����\n");
	}
	return FALSE;
}

/// @brief ��ȡ�и�.
/// @param hEle   Ԫ�ؾ��.
/// @return �и�.
int WINAPI XListBox_GetItemHeight(HELE hEle) //��ȡ�и�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return  LISTBOX(hEle)->height;
}

/// @brief ��ȡѡ����.
/// @param hEle   Ԫ�ؾ��.
/// @return ѡ��������,�������-1û��ѡ����.
int WINAPI XListBox_GetSelectItem(HELE hEle) //��ȡѡ����
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return LISTBOX(hEle)->curSel;
}

/// @brief ��ȡָ�����ı�.
/// @param hEle   Ԫ�ؾ��.
/// @param index ָ��������.
/// @return �ı�����.
wchar_t* WINAPI XListBox_GetItemText(HELE hEle, int index) //��ȡָ�����ı�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (count > 0)
	{
		if (index >= 0 && index < count)
		{
			listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
			if (pItem)
			{
				return XStr_GetBuffer(pItem->hString);
			}
		}
	}
	return NULL;
}

/// @brief ����ָ�����ı�.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ָ��������.
/// @param pText �ı�����.
void WINAPI XListBox_SetItemText(HELE hEle, int index, wchar_t *pText) //����ָ�����ı�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);
	int count = Array_GetCount(pObj->hArrayListItem);
	if (index >= 0 && index < count)
	{
		int len = wcslen(pText);
		if (len < 1) return;

		HDC hdc;
		SIZE size;
		hdc = GetDC(NULL);
		HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
		GetTextExtentPoint32(hdc, pText, len, &size);
		SelectObject(hdc, hOldFont);
		ReleaseDC(NULL, hdc);

		if (size.cx > pObj->maxTextWidth)
			pObj->maxTextWidth = size.cx;

		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, index);
		XStr_SetString(pItem->hString, pText);

		XSView_SetSize(hEle, pObj->maxTextWidth, count*pObj->height);
	}
}

/// @brief ����ѡ����.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ѡ��������,���indexΪ-1��ô��ѡ���κ���.
void WINAPI XListBox_SetSelectItem(HELE hEle, int index) //����ѡ����
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		LISTBOX(hEle)->curSel = index;
	}
	else if (-1 == index)
	{
		LISTBOX(hEle)->curSel = -1;
	}
}

/// @brief �����и�.
/// @param hEle   Ԫ�ؾ��.
/// @param height  �и�.
void WINAPI XListBox_SetItemHeight(HELE hEle, int height) //�����и�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->height = height;
}

/// @brief ɾ����.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ������.
void WINAPI XListBox_DeleteItem(HELE hEle, int index)  //ɾ����
{
	IsListBoxDebug(hEle, __FUNCTION__);
	if (index < 0) return;
	int count = Array_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		XStr_Destroy(pItem->hString);

		if (pItem->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pItem->hArrayBindEle);
			for (int i = 0; i < bindEleCount; i++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, i);
				if (pBindEle->hEle)
					XEle_Destroy(pBindEle->hEle);
				free(pBindEle);
			}
			XArray_Destroy(pItem->hArrayBindEle);
		}

		free(pItem);

		XArray_DeleteIndex(LISTBOX(hEle)->hArrayListItem, index);
	}
}

/// @brief ɾ��������.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XListBox_DeleteAll(HELE hEle) //ɾ��������
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);
	int count = Array_GetCount(pObj->hArrayListItem);
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, i);
			XStr_Destroy(pItem->hString);

			if (pItem->hArrayBindEle)
			{
				int bindEleCount = XArray_GetCount(pItem->hArrayBindEle);
				for (int j = 0; j < bindEleCount; j++)
				{
					itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pItem->hArrayBindEle, j);
					if (pBindEle->hEle)
						XEle_Destroy(pBindEle->hEle);
					free(pBindEle);
				}
				XArray_Destroy(pItem->hArrayBindEle);
			}

			free(pItem);
		}
		XArray_DeleteAll(LISTBOX(hEle)->hArrayListItem);
	}
}

/// @brief �����б��Ԫ�ع���ͼƬ�б�.
/// @param hEle  Ԫ�ؾ��.
/// @param hImageList  ͼƬ�б�Ԫ�ؾ��.
void WINAPI XListBox_SetImageList(HELE hEle, HXCGUI hImageList) //����ͼ���б�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_ *pObj = LISTBOX(hEle);
	if (pObj->hImageList)
	{
		XImageList_Destroy(pObj->hImageList);
		pObj->hImageList = NULL;
	}
	if (hImageList)
	{
		IsImageListDebug(hImageList, __FUNCTION__);
		pObj->hImageList = ImageList_AddRef(hImageList);
	}
}

/// @brief ������ͼ��.
/// @param hEle  Ԫ�ؾ��.
/// @param index  ������.
/// @param imageId ͼ��ID.
void WINAPI XListBox_SetItemImage(HELE hEle, int index, int imageId) //������ͼ��
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		pItem->imageID = imageId;
	}
}

/// @brief ��ȡ��ͼ��ID.
/// @param hEle  Ԫ�ؾ��.
/// @param index  ������.
/// @return ͼ��ID.
int WINAPI XListBox_GetItemImage(HELE hEle, int index) //��ȡ��ͼ��
{
	IsListBoxDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
	if (index >= 0 && index < count)
	{
		listBox_item_  *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, index);
		return pItem->imageID;
	}
	return -1;
}

/// @brief ��ȡ������.
/// @param hEle  Ԫ�ؾ��.
/// @return ������.
int WINAPI XListBox_GetItemCount(HELE hEle) //��ȡ������
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return XArray_GetCount(LISTBOX(hEle)->hArrayListItem);
}

/// @brief ��ȡͼƬ�б�.
/// @param hEle  Ԫ�ؾ��.
/// @return ͼƬ�б���.
HXCGUI WINAPI XListBox_GetImageList(HELE hEle) //��ȡͼƬ�б�
{
	IsListBoxDebug(hEle, __FUNCTION__);
	return LISTBOX(hEle)->hImageList;
}

/// @brief ��ȡ�������������.
/// @param hEle  Ԫ�ؾ��.
/// @param index  ������.
/// @param pRect  ���շ�������.
/// @return �����ɼ�����FALSE,�����෴..
BOOL WINAPI XListBox_GetItemRect(HELE hEle, in_ int index, out_ RECT *pRect)  //��ȡ������...
{
	if (index > -1 && index < Array_GetCount(LISTBOX(hEle)->hArrayListItem))
	{
		int y = index*LISTBOX(hEle)->height;
		y = y - XSView_GetVViewPos(hEle);
		y = y + XSView_GetSpacingTop(hEle);

		RECT rcView;
		XSView_GetViewRect(hEle, &rcView);

		pRect->left = rcView.left;
		pRect->right = rcView.right;
		pRect->top = y;
		pRect->bottom = y + LISTBOX(hEle)->height;

		if (pRect->top >= rcView.bottom)
		{
			pRect->top = rcView.bottom;
			pRect->bottom = rcView.bottom;
			return FALSE;
		}
		else if (pRect->bottom > rcView.bottom)
		{
			pRect->bottom = rcView.bottom;
		}
		return TRUE;
	}
	return FALSE;
}

/// @brief ����������ĸ�����,���û�����κ����Ϸ���-1.
/// @param hEle Ԫ�ؾ��
/// @param pPt  �����.
/// @return �������������,���û�����κ����Ϸ���-1.
int  WINAPI XListBox_HitTest(HELE hEle, POINT *pPt)  //�����������ĸ�����,-1û�����κ�����
{
	IsListBoxDebug(hEle, __FUNCTION__);
	POINT pt = *pPt;
	int pos = -1;

	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (PtInRect(&rect, pt))
	{
		int y = pPt->y - XSView_GetVViewPos(hEle) - XSView_GetSpacingTop(hEle) - 1;

		pos = y / LISTBOX(hEle)->height;
		if (pos >= Array_GetCount(LISTBOX(hEle)->hArrayListItem))
		{
			pos = -1;
		}
	}
	return pos;
}

/// @brief ��ȡ�������.
/// @param hEle   Ԫ�ؾ��
/// @param index  ������.
/// @return �������,���ʧ�ܷ���-1.
void* WINAPI XListBox_GetItemData(HELE hEle, int index) //��ȡ�������
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_  *pListBox = LISTBOX(hEle);
	int count = XArray_GetCount(pListBox->hArrayListItem);

	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pListBox->hArrayListItem, index);
		return pItem->userData;
	}
	return NULL;
}

/// @brief �����������.
/// @param hEle   Ԫ�ؾ��
/// @param index  ������.
/// @param data   �������.
void WINAPI XListBox_SetItemData(HELE hEle, int index, void* data) //�����������
{
	IsListBoxDebug(hEle, __FUNCTION__);
	listBox_  *pListBox = LISTBOX(hEle);
	int count = XArray_GetCount(pListBox->hArrayListItem);

	if (index >= 0 && index < count)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pListBox->hArrayListItem, index);
		pItem->userData = data;
	}
}

/// @brief ����ѡ������ɫ.
/// @param hEle   Ԫ�ؾ��
/// @param color  RGB��ɫ.
void WINAPI XListBox_SetSelectItemColor(HELE hEle, COLORREF color) //����ѡ������ɫ
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->selectItemColor = color;
}

/// @brief �������ͣ������ɫ.
/// @param hEle   Ԫ�ؾ��
/// @param color  RGB��ɫ.
void WINAPI XListBox_SetItemMouseStayColor(HELE hEle, COLORREF color) //�������ͣ����������ɫ
{
	IsListBoxDebug(hEle, __FUNCTION__);
	LISTBOX(hEle)->mouseStayColor = color;
}

///@}


BOOL CALLBACK ListBox_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	listBox_ *pObj = LISTBOX(hEle);
	if (pObj->bAdjust)
	{
		XListBox_Adjust(hEle);
	}
	int right = XSView_GetViewWidth(hEle) - XSView_GetHViewPos(hEle) - 1;

	//�����б���
	RECT rcItem;
	rcItem.left = XSView_GetSpacingLeft(hEle) + 1;
	rcItem.right = right;
	int y = XSView_GetSpacingTop(hEle) + 1;
	int count = Array_GetCount(pObj->hArrayListItem);

	//�û��Ի�----------------------------------------------
	if (pObj->pDrawItem)
	{
		for (int i = 0; i < count; i++)
		{
			listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, i);
			rcItem.top = y;
			y += pObj->height;
			rcItem.bottom = y;

			listBox_drawItem_ drawItem;
			memset(&drawItem, 0, sizeof(drawItem));
			drawItem.hDraw = hDraw;
			drawItem.index = i;
			drawItem.imageId = pItem->imageID;
			if (pObj->curSel == i) //ѡ����
				drawItem.state = STATE_SELECT;
			else
				drawItem.state = STATE_LEAVE;
			drawItem.rcItem = rcItem;
			drawItem.pText = XStr_GetBuffer(pItem->hString);

			if (pObj->bCheck)
			{
				int left = XSView_GetSpacingLeft(hEle) + 1;
				int top = XSView_GetSpacingTop(hEle) + 1;
				drawItem.rcCheck.left = left + XLISTBOX_LEFT;
				drawItem.rcCheck.top = top + i*pObj->height;
				drawItem.rcCheck.right = left + XLISTBOX_CHECK_SIZE;
				drawItem.rcCheck.bottom = drawItem.rcCheck.top + pObj->height;
			}
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
			if (pObj->pClass_Fun_Info)
			{
				eventOrMsg_  event_;
				event_.hEle = hEle;
				event_.hEventEle = NULL;
				event_.wParam = (WPARAM)&drawItem;
				event_.lParam = NULL;
				event_.pClass_fun = pObj->pClass_Fun_Info;
				((pFunClassEventMsg)pObj->pDrawItem)(&event_, xc_fun_v_e_listBox);
			}
			else
			{
				pObj->pDrawItem(hEle, &drawItem);
			}
#else
			pObj->pDrawItem(hEle, &drawItem);
#endif
			XDraw_RestoreGDIOBJ_(hDraw);
		}
		return TRUE;
	}
	//---ϵͳ�Ի�---------------------------------------------
	RECT rcText;
	int  imageWidth = 0;
	if (pObj->hImageList)
	{
		imageWidth = XImageList_GetWidth(pObj->hImageList) + 3;
	}

	for (int i = 0; i < count; i++)
	{
		listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(pObj->hArrayListItem, i);

		int  left = rcItem.left + XLISTBOX_LEFT;
		rcItem.top = y;
		y += pObj->height;
		rcItem.bottom = y;

		rcText = rcItem;

		//������
		if (pObj->bLineHighlight && pObj->mouseStayId == i)
		{
			XDraw_FillSolidRect_(hDraw, &rcItem, pObj->mouseStayColor);//200,200,200));
		}

		if (pObj->curSel == i) //ѡ����
		{
			XDraw_FillSolidRect_(hDraw, &rcItem, pObj->selectItemColor);//83,132,213));//126,206,244
		}

		//���Ƹ�ѡ��
		if (pObj->bCheck)
		{
			int top = rcItem.top + pObj->height / 2 - 6 - 1;
			XDraw_Check_(hDraw, left, top, RGB(80, 80, 80), pItem->bCheck);

			left += (XLISTBOX_CHECK_SIZE + 3);
		}

		//����ͼ��
		if (pObj->hImageList && pItem->imageID != -1)
		{
			XImageList_DrawImage(pObj->hImageList, hDraw, pItem->imageID, left, rcItem.top + (pObj->height / 2) - imageWidth / 2);
			left += imageWidth;
		}

		wchar_t *pText = XStr_GetBuffer(pItem->hString);
		if (pText)
		{
			rcText.left = left;
			XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_VCENTER | DT_SINGLELINE);
		}
	}
	return TRUE;
}

void ListBox_MouseDown(HELE hEle, POINT *pPt)
{
	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (FALSE == PtInRect(&rect, *pPt))
		return;

	int posy = XSView_GetVViewPos(hEle) + XSView_GetSpacingTop(hEle) + 1;

	int y = pPt->y + (-posy);
	int line = y / LISTBOX(hEle)->height;

	if (line < Array_GetCount(LISTBOX(hEle)->hArrayListItem))
	{
		if (LISTBOX(hEle)->bCheck)
		{
			int left = XSView_GetSpacingLeft(hEle) + 1;
			int posx = XSView_GetHViewPos(hEle);
			int x = pPt->x + (-posx);
			if (x > (left + XLISTBOX_LEFT) && x < (left + XLISTBOX_LEFT + XLISTBOX_CHECK_SIZE))
			{
				listBox_item_ *pItem = (listBox_item_*)XArray_GetAt(LISTBOX(hEle)->hArrayListItem, line);
				pItem->bCheck = pItem->bCheck ? FALSE : TRUE;
				XEle_RedrawEle(hEle);
				return;
			}
		}
		if (LISTBOX(hEle)->curSel != line)
		{
			BOOL bChange = FALSE;
			Ele_SendEvent(hEle, XE_LISTBOX_SELECT_ING, line, (LPARAM)&bChange);
			if (!bChange)
			{
				LISTBOX(hEle)->curSel = line;
				Ele_SendEvent(hEle, XE_LISTBOX_SELECT, line, 0);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
	}
	else
	{
		if (LISTBOX(hEle)->curSel != -1)
		{
			BOOL bChange = FALSE;
			Ele_SendEvent(hEle, XE_LISTBOX_SELECT_ING, line, (LPARAM)&bChange);
			if (!bChange)
			{
				LISTBOX(hEle)->curSel = -1;
				Ele_SendEvent(hEle, XE_LISTBOX_SELECT, -1, 0);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
	}
}

BOOL CALLBACK ListBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	ListBox_MouseDown(hEle, pPt);
	return FALSE;
}

BOOL CALLBACK ListBox_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	if (LISTBOX(hEle)->bLineHighlight)
	{
		RECT rect;
		XSView_GetViewRect(hEle, &rect);
		if (PtInRect(&rect, *pPt))
		{
			int posy = XSView_GetVViewPos(hEle) + XSView_GetSpacingTop(hEle) + 1;

			int y = pPt->y + (-posy);
			int line = y / LISTBOX(hEle)->height;

			if (line < Array_GetCount(LISTBOX(hEle)->hArrayListItem))
			{
				if (LISTBOX(hEle)->mouseStayId != line)
				{
					LISTBOX(hEle)->mouseStayId = line;
					XEle_RedrawEle(hEle);
				}
				return FALSE;
			}
		}
		if (-1 != LISTBOX(hEle)->mouseStayId)
		{
			LISTBOX(hEle)->mouseStayId = -1;
			XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK ListBox_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	if (-1 != LISTBOX(hEle)->mouseStayId)
	{
		LISTBOX(hEle)->mouseStayId = -1;
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}