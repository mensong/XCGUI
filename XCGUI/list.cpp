/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup list �б�(List)
/// @ingroup groupElements
/// @{

/// @brief �����б�Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XList_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	list_ *pList = (list_*)malloc(sizeof(list_));
	memset(pList, 0, sizeof(list_));

	List_Init((HELE)pList, x, y, cx, cy, XC_LIST, hParent);
	return (HELE)pList;
}

//˽�з���:
void List_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_LIST);
	list_ *pList = LIST(hEle);
	pList->headerHeight = 25;
	pList->itemHeight = 22;
	pList->spacingLeft = 10;
	pList->spacingRight = 10;
	pList->downIndex = -1;
	pList->hArrayHeader = XArray_Create();
	pList->hArrayItem = XArray_Create();
	pList->hArrayCurrItem = XArray_Create();
	pList->bGrid = TRUE; //��������
	pList->bShowHeader = TRUE;
	pList->bMultilineSelect = TRUE;
	pList->bLineHighlight = TRUE;

	XSView_SetScrollSize(hEle, 20, pList->itemHeight);
	XSView_SetSpacing(hEle, 2, pList->headerHeight, 2, 2);
	HELE hView = XSView_GetView(hEle);

	XSView_SetDrawScrollView(hEle, List_OnDrawScrollView);
	XEle_RegisterMessage(hEle, XM_PAINT, List_OnEleDraw);

	XEle_RegisterEvent(hEle, XE_DESTROY, List_OnDestroy);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, List_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, List_OnLButtonUp);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, List_OnMouseMove);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, List_OnEventMouseLeave);
	XEle_RegisterEvent(hEle, XE_KILLCAPTURE, List_OnEventKillCapture);

	XEle_RegisterMessage(hView, XM_LBUTTONDOWN, List_OnLButtonDown_View);
	XEle_RegisterMessage(hView, XM_LBUTTONUP, List_OnLButtonUp_View);
	XEle_RegisterMessage(hView, XM_MOUSEMOVE, List_OnMouseMove_View);
	XEle_RegisterEvent(hView, XE_KILLCAPTURE, List_OnEventKillCapture_View);
	XEle_RegisterEvent(hView, XE_MOUSELEAVE, List_OnEventMouseLeave_View);
}

void CALLBACK List_OnDestroy(HELE hEle) //����
{
	XList_DeleteAllColumns(hEle);
	if (LIST(hEle)->hArrayHeader)
		XArray_Destroy(LIST(hEle)->hArrayHeader);

	if (LIST(hEle)->hArrayItem)
		XArray_Destroy(LIST(hEle)->hArrayItem);

	if (LIST(hEle)->hArrayCurrItem)
		XArray_Destroy(LIST(hEle)->hArrayCurrItem);

	if (LIST(hEle)->hImageList)
		XImageList_Destroy(LIST(hEle)->hImageList);

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	if (LIST(hEle)->pClass_Fun_Info_Item)
		free(LIST(hEle)->pClass_Fun_Info_Item);
	if (LIST(hEle)->pClass_Fun_Info_ItemHeader)
		free(LIST(hEle)->pClass_Fun_Info_ItemHeader);
#endif
}

/// @brief �����.
/// @param hEle   Ԫ�ؾ��.
/// @param width  �п��.
/// @param pText  �ı�����.
/// @param imageId ͼ������ID.
/// @return ����ɹ�����������е�����,���򷵻�-1.
int WINAPI XList_AddColumn(HELE hEle, int width, wchar_t *pText, int imageId) //������
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pList = LIST(hEle);
	pList->bAdjustHeader = TRUE;
	pList->bAdjustItem = TRUE;

	listHeader_ *pHeader = (listHeader_*)malloc(sizeof(listHeader_));
	pHeader->width = width;
	pHeader->minWidth = 50;
	pHeader->hString = XStr_Create();
	XStr_SetString(pHeader->hString, pText);
	pHeader->state = 0;
	pHeader->imageId = imageId;
	XArray_Add(pList->hArrayHeader, pHeader);

	int count = Array_GetCount(pList->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		listSubItem_  *pSubItem = (listSubItem_*)malloc(sizeof(listSubItem_));
		pSubItem->hString = XStr_Create();
		pSubItem->imageId = -1;
		XArray_Add(Array_GetAtList(pList->hArrayItem, i)->hArrayItem, pSubItem);
	}
	return XArray_GetCount(pList->hArrayHeader) - 1;
}

void List_AdjustHeader(HELE hEle)  //�����б�ͷ
{
	list_ *pList = LIST(hEle);

	if (pList->bAdjustHeader)
		pList->bAdjustHeader = FALSE;

	int count = Array_GetCount(pList->hArrayHeader);
	int posX = pList->spacingLeft;
	listHeader_  *pHeader = NULL;
	for (int i = 0; i < count; i++)
	{
		pHeader = Array_GetAtListHeader(pList->hArrayHeader, i);
		pHeader->rect.left = posX;
		pHeader->rect.top = 0;
		pHeader->rect.right = posX + pHeader->width;
		pHeader->rect.bottom = pList->headerHeight;
		posX = pHeader->rect.right;
	}
}

void List_AdjustItem(HELE hEle)
{
	list_ *pList = LIST(hEle);
	int countHeader = Array_GetCount(pList->hArrayHeader);
	if (countHeader < 1)
		return;

	int countItem = Array_GetCount(pList->hArrayItem);
	int top = 0;
	//	if(pList->bShowHeader)
	//		top=pList->headerHeight;

	int posx = XSView_GetHViewPos(hEle);
	int posy = XSView_GetVViewPos(hEle);

	if (pList->bCheck) //����ѡ��ť
	{
		HXCGUI  hArrayItem = NULL;
		listItem_    *pItem = NULL;
		listSubItem_ *pChildItem = NULL;
		for (int j = 0; j < countItem; j++)
		{
			pItem = Array_GetAtList(pList->hArrayItem, j);
			pItem->index = j;

			for (int i = 0; i < countHeader; i++)
			{
				pChildItem = Array_GetAtListSubItem(pItem->hArrayItem, i);
				if (0 == i)
				{
					pChildItem->rect.left = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.left;
					pChildItem->rect.right = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.right;
					pChildItem->rect.top = top;
					pChildItem->rect.bottom = top + pList->itemHeight;

					pItem->rcCheck.left = pChildItem->rect.left + XLIST_ITEM_LEFT;
					pItem->rcCheck.right = pItem->rcCheck.left + XLIST_CHECK_SIZE;
					pItem->rcCheck.top = top;
					pItem->rcCheck.bottom = top + pList->itemHeight;
				}
				else
				{
					pChildItem->rect.left = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.left;
					pChildItem->rect.right = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.right;

					pChildItem->rect.top = top;
					pChildItem->rect.bottom = top + pList->itemHeight;
				}
				//��Ԫ��
				if (pChildItem->hArrayBindEle)
				{
					int bindCount = XArray_GetCount(pChildItem->hArrayBindEle);
					for (int j = 0; j < bindCount; j++)
					{
						itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pChildItem->hArrayBindEle, j);

						//((ele_*)pBindEle->hEle)->rect.left=pChildItem->rect.left+pBindEle->left+posx;
						//((ele_*)pBindEle->hEle)->rect.top=pChildItem->rect.top+pBindEle->top+posy;
						//((ele_*)pBindEle->hEle)->rect.right=((ele_*)pBindEle->hEle)->rect.left+pBindEle->width;
						//((ele_*)pBindEle->hEle)->rect.bottom=((ele_*)pBindEle->hEle)->rect.top+pBindEle->height;
						//((ele_*)pBindEle->hEle)->elePt.x=pChildItem->rect.left+pBindEle->left;
						//((ele_*)pBindEle->hEle)->elePt.y=pChildItem->rect.top+pBindEle->top;

						RECT rectT;
						rectT.left = pChildItem->rect.left + pBindEle->left + posx;
						rectT.top = pChildItem->rect.top + pBindEle->top + posy;
						rectT.right = rectT.left + pBindEle->width;
						rectT.bottom = rectT.top + pBindEle->height;

						XEle_SetRect(pBindEle->hEle, &rectT);
					}
				}
			}
			top += pList->itemHeight;
		}
	}
	else
	{
		HXCGUI  hArrayItem = NULL;
		listSubItem_ *pChildItem = NULL;
		for (int j = 0; j < countItem; j++)
		{
			Array_GetAtList(pList->hArrayItem, j)->index = j;
			for (int i = 0; i < countHeader; i++)
			{
				hArrayItem = Array_GetAtList(pList->hArrayItem, j)->hArrayItem;
				pChildItem = Array_GetAtListSubItem(hArrayItem, i);
				pChildItem->rect.left = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.left;
				pChildItem->rect.right = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.right;

				pChildItem->rect.top = top;
				pChildItem->rect.bottom = top + pList->itemHeight;

				//��Ԫ��
				if (pChildItem->hArrayBindEle)
				{
					int bindCount = XArray_GetCount(pChildItem->hArrayBindEle);
					for (int c = 0; c < bindCount; c++)
					{
						itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pChildItem->hArrayBindEle, c);
						//((ele_*)pBindEle->hEle)->rect.left=pChildItem->rect.left+pBindEle->left+posx;
						//((ele_*)pBindEle->hEle)->rect.top=pChildItem->rect.top+pBindEle->top+posy;
						//((ele_*)pBindEle->hEle)->rect.right=((ele_*)pBindEle->hEle)->rect.left+pBindEle->width;
						//((ele_*)pBindEle->hEle)->rect.bottom=((ele_*)pBindEle->hEle)->rect.top+pBindEle->height;
						//((ele_*)pBindEle->hEle)->elePt.x=pChildItem->rect.left+pBindEle->left;
						//((ele_*)pBindEle->hEle)->elePt.y=pChildItem->rect.top+pBindEle->top;

						RECT rectT;
						rectT.left = pChildItem->rect.left + pBindEle->left + posx;
						rectT.top = pChildItem->rect.top + pBindEle->top + posy;
						rectT.right = rectT.left + pBindEle->width;
						rectT.bottom = rectT.top + pBindEle->height;

						XEle_SetRect(pBindEle->hEle, &rectT);
					}
				}
			}
			top += pList->itemHeight;
		}
	}


	XSView_SetSize(hEle, Array_GetAtListHeader(pList->hArrayHeader, countHeader - 1)->rect.right + pList->spacingRight, top);
}

void List_AdjustDragHeader(HELE hEle, POINT &pt, int index)
{
	list_ *pList = LIST(hEle);
	//�����б�ͷ
	pList->bAdjustHeader = FALSE;

	listHeader_  *pItemHeaderCur = Array_GetAtListHeader(pList->hArrayHeader, pList->downIndex);
	int width = pt.x + XLIST_ITEM_LEFT - pItemHeaderCur->rect.left;
	if (width < pItemHeaderCur->minWidth) //������С��Χ
	{
		return;
	}

	pItemHeaderCur->rect.right = pt.x + XLIST_ITEM_LEFT;
	pItemHeaderCur->width = width;

	int countHeader = Array_GetCount(pList->hArrayHeader);
	for (int i = pList->downIndex + 1; i < countHeader; i++)
	{
		Array_GetAtListHeader(pList->hArrayHeader, i)->rect.left = Array_GetAtListHeader(pList->hArrayHeader, i - 1)->rect.right;
		Array_GetAtListHeader(pList->hArrayHeader, i)->rect.right = Array_GetAtListHeader(pList->hArrayHeader, i)->rect.left + Array_GetAtListHeader(pList->hArrayHeader, i)->width;
	}

	//�����б���/////////////////////////
	if (pList->bAdjustItem)
		pList->bAdjustItem = FALSE;

	int countItem = Array_GetCount(pList->hArrayItem);
	int height = 0;//pList->headerHeight;

	int posx = XSView_GetHViewPos(hEle);
	int posy = XSView_GetVViewPos(hEle);

	for (int j = 0; j < countItem; j++)
	{
		Array_GetAtList(pList->hArrayItem, j)->index = j;
		for (int i = pList->downIndex; i < countHeader; i++)
		{
			listItem_ *pItem = Array_GetAtList(pList->hArrayItem, j);

			listSubItem_ *pSubItem = Array_GetAtListSubItem(pItem->hArrayItem, i);
			listHeader_  *pItemHeader = Array_GetAtListHeader(pList->hArrayHeader, i);

			pSubItem->rect.left = pItemHeader->rect.left;
			pSubItem->rect.right = pItemHeader->rect.right;

			pSubItem->rect.top = height;
			pSubItem->rect.bottom = height + pList->itemHeight;

			//��Ԫ��
			if (pSubItem->hArrayBindEle)
			{
				int bindCount = XArray_GetCount(pSubItem->hArrayBindEle);
				for (int c = 0; c < bindCount; c++)
				{
					itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pSubItem->hArrayBindEle, c);

					RECT rectT;
					rectT.left = pSubItem->rect.left + pBindEle->left + posx;
					rectT.top = pSubItem->rect.top + pBindEle->top + posy;
					rectT.right = rectT.left + pBindEle->width;
					rectT.bottom = rectT.top + pBindEle->height;

					XEle_SetRect(pBindEle->hEle, &rectT);
				}
			}
		}
		height += pList->itemHeight;
	}
	XEle_RedrawEle(hEle);
}

/// @brief ����б���.
/// @param hEle   Ԫ�ؾ��.
/// @param pText  �ı�����.
/// @param imageId ͼ������ID.
/// @return ����ɹ�������������,���򷵻�-1.
int WINAPI XList_AddItem(HELE hEle, wchar_t *pText, int imageId)  //������
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pList = LIST(hEle);

	int count = Array_GetCount(pList->hArrayHeader);
	if (count < 1)
		return -1;

	listItem_  *pItem = (listItem_*)malloc(sizeof(listItem_));
	memset(pItem, 0, sizeof(listItem_));
	pItem->hArrayItem = XArray_Create();

	for (int i = 0; i < count; i++)
	{
		listSubItem_  *pSbuItem = (listSubItem_*)malloc(sizeof(listSubItem_));
		memset(pSbuItem, 0, sizeof(listSubItem_));
		pSbuItem->hString = XStr_Create();
		pSbuItem->imageId = -1;
		XArray_Add(pItem->hArrayItem, pSbuItem);
	}

	XStr_SetString(Array_GetAtListSubItem(pItem->hArrayItem, 0)->hString, pText);
	Array_GetAtListSubItem(pItem->hArrayItem, 0)->imageId = imageId;
	XArray_Add(pList->hArrayItem, pItem);

	pList->bAdjustItem = TRUE;

	return XArray_GetCount(pList->hArrayItem) - 1;
}

/// @brief �������ı�����.
/// @param hEle   Ԫ�ؾ��.
/// @param item   ������.
/// @param subItem  ��������.
/// @param pText  �ı�����.
/// @param imageId ͼ������ID.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_SetItemText(HELE hEle, int item, int subItem, wchar_t *pText, int imageId) //��������
{
	IsListDebug(hEle, __FUNCTION__);
	if (item < Array_GetCount(LIST(hEle)->hArrayItem) && subItem < Array_GetCount(LIST(hEle)->hArrayHeader))
	{
		HXCGUI hArray = Array_GetAtList(LIST(hEle)->hArrayItem, item)->hArrayItem;
		HSTRING hString = Array_GetAtListSubItem(hArray, subItem)->hString;
		Array_GetAtListSubItem(hArray, subItem)->imageId = imageId;
		if (hString)
		{
			XStr_SetString(hString, pText);
			return TRUE;
		}
	}
	return FALSE;
}

/// @brief ������.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ������λ������.
/// @param width   �п�.
/// @param pText   �ı�����
/// @param imageId ͼ������ID.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_InsertColumn(HELE hEle, int index, int width, wchar_t *pText, int imageId)  //������
{
	IsListDebug(hEle, __FUNCTION__);
	if (index < 0)
		return FALSE;

	list_ *pObj = LIST(hEle);
	int count = Array_GetCount(pObj->hArrayHeader);

	if (index > count)
		return FALSE;

	pObj->bAdjustHeader = TRUE;
	pObj->bAdjustItem = TRUE;

	listHeader_ *pHeader = (listHeader_*)malloc(sizeof(listHeader_));
	memset(pHeader, 0, sizeof(listHeader_));
	pHeader->width = width;
	pHeader->minWidth = 50;
	pHeader->hString = XStr_Create();
	XStr_SetString(pHeader->hString, pText);
	pHeader->state = 0;
	pHeader->imageId = imageId;
	XArray_insert(pObj->hArrayHeader, pHeader, index);

	count = Array_GetCount(pObj->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		listSubItem_  *pSubItem = (listSubItem_*)malloc(sizeof(listSubItem_));
		memset(pSubItem, 0, sizeof(listSubItem_));
		pSubItem->imageId = -1;
		XArray_insert(Array_GetAtList(pObj->hArrayItem, i)->hArrayItem, pSubItem, index);
	}
	return TRUE;
}

/// @brief ������.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ����λ������.
/// @param pText   �ı�����.
/// @param imageId ͼ������ID.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_InsertItem(HELE hEle, int index, wchar_t *pText, int imageId)  //������
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pObj = LIST(hEle);

	int countHeader = Array_GetCount(pObj->hArrayHeader);
	if (countHeader < 1)
		return FALSE;

	if (index < 0)
		return FALSE;

	int countItem = Array_GetCount(pObj->hArrayItem);
	if (index > countItem)
		return FALSE;

	listItem_  *pItem = (listItem_*)malloc(sizeof(listItem_));
	memset(pItem, 0, sizeof(listItem_));
	pItem->state = 0;
	pItem->hArrayItem = XArray_Create();

	for (int i = 0; i < countHeader; i++)
	{
		listSubItem_  *pSbuItem = (listSubItem_*)malloc(sizeof(listSubItem_));
		memset(pSbuItem, 0, sizeof(listSubItem_));
		pSbuItem->hString = XStr_Create();
		pSbuItem->imageId = -1;
		XArray_Add(pItem->hArrayItem, pSbuItem);
	}

	XStr_SetString(Array_GetAtListSubItem(pItem->hArrayItem, 0)->hString, pText);
	Array_GetAtListSubItem(pItem->hArrayItem, 0)->imageId = imageId;
	XArray_insert(pObj->hArrayItem, pItem, index);

	pObj->bAdjustItem = TRUE;

	return TRUE;
}

/// @brief �����п��.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ������.
/// @param width   ���.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_SetColumnWidth(HELE hEle, int index, int width)   //�����п�
{
	IsListDebug(hEle, __FUNCTION__);
	if (index < 0)
		return FALSE;

	list_ *pObj = LIST(hEle);
	int count = Array_GetCount(pObj->hArrayHeader);   //m_listHeader.m_count;
	if (count < 1)
		return FALSE;

	if (index >= count)
		return FALSE;

	pObj->bAdjustHeader = TRUE;
	pObj->bAdjustItem = TRUE;

	Array_GetAtListHeader(pObj->hArrayHeader, index)->width = width;
	return TRUE;
}

/// @brief ������ͼ��.
/// @param hEle   Ԫ�ؾ��.
/// @param item   ������.
/// @param subItem  ��������.
/// @param imageId  ͼ������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_SetItemImage(HELE hEle, int item, int subItem, int imageId)  //��������ͼƬ
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pObj = LIST(hEle);
	Array_GetAtListSubItem(Array_GetAtList(pObj->hArrayItem, item)->hArrayItem, subItem)->imageId = imageId;
	return TRUE;
}

/// @brief �����б��ͼ���б�.
/// @param hEle   Ԫ�ؾ��.
/// @param hImageList   ͼ���б���Դ���.
void WINAPI XList_SetImageList(HELE hEle, HXCGUI hImageList) //����ͼƬ�б�
{
	IsListDebug(hEle, __FUNCTION__);
	if (LIST(hEle)->hImageList)
	{
		XImageList_Destroy(LIST(hEle)->hImageList);
		LIST(hEle)->hImageList = NULL;
	}
	if (hImageList)
	{
		IsImageListDebug(hImageList, __FUNCTION__);
		LIST(hEle)->hImageList = ImageList_AddRef(hImageList);
	}
}

/// @brief ������߶�.
/// @param hEle   Ԫ�ؾ��.
/// @param height   �߶�.
void WINAPI XList_SetItemHeight(HELE hEle, int height)  //������߶�
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->itemHeight = height;
	XSView_SetScrollSize(hEle, 20, height);
}

/// @brief �����б�ͷ�߶�.
/// @param hEle   Ԫ�ؾ��.
/// @param height   �߶�.
void WINAPI XList_SetHeaderHeight(HELE hEle, int height) //�����б�ͷ�߶�
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->headerHeight = height;
	LIST(hEle)->bAdjustHeader = TRUE;
}

/// @brief ����ѡ�����.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ѡ��������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_SetSelectItem(HELE hEle, int index)   //����ѡ����
{
	IsListDebug(hEle, __FUNCTION__);
	if (index < 0)
		return FALSE;

	list_ *pObj = LIST(hEle);

	int count = Array_GetCount(pObj->hArrayItem);
	if (index >= count)
		return FALSE;

	listItem_ *pSel = Array_GetAtList(pObj->hArrayItem, index);
	pSel->state = STATE_SELECT;
	XArray_Add(pObj->hArrayCurrItem, pSel);

	if (NULL == pObj->pCurrItem)
		pObj->pCurrItem = pSel;

	Ele_SendEvent(hEle, XE_LIST_SELECT, index, 0);
	return TRUE;
}

/// @brief ѡ��������.
/// @param hEle   Ԫ�ؾ��.
void WINAPI XList_SetSelectItemAll(HELE hEle) //ȫѡ
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pList = LIST(hEle);
	int count = Array_GetCount(pList->hArrayItem);
	if (count > 0)
	{
		listItem_ *pItem = NULL;
		for (int i = 0; i < count; i++)
		{
			pItem = Array_GetAtList(pList->hArrayItem, i);
			pItem->state = STATE_SELECT;
			XArray_Add(pList->hArrayCurrItem, pItem);
		}
		pList->pCurrItem = Array_GetAtList(pList->hArrayItem, 0);
		Ele_SendEvent(hEle, XE_LIST_SELECT, 0, 0);
	}
}

/// @brief ���������������.
/// @param hEle   Ԫ�ؾ��.
/// @param spacing ����С.
void WINAPI XList_SetSpacingLeft(HELE hEle, int spacing)  //������������
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->spacingLeft = spacing;
}

/// @brief ���������Ҽ��.
/// @param hEle   Ԫ�ؾ��.
/// @param spacing ����С.
void WINAPI XList_SetSpacingRight(HELE hEle, int spacing) //���������Ҽ��
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->spacingRight = spacing;
}

/// @brief �������û�����.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ������.
/// @param data   �û�����.
void WINAPI XList_SetItemData(HELE hEle, int index, void* data)  //�����û�����
{
	IsListDebug(hEle, __FUNCTION__);
	listItem_ *pItem = (listItem_*)XArray_GetAt(LIST(hEle)->hArrayItem, index);
	pItem->userData = data;
}

/// @brief �������Ԫ��.
/// @param hEle     Ԫ�ؾ��.
/// @param item     ������.
/// @param subItem  ��������.
/// @param pInfo    ��Ԫ����Ϣ
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XList_SetItemBindEle(HELE hEle, int item, int subItem, itemBindEle_ *pInfo) //��Ԫ��
{
	IsListDebug(hEle, __FUNCTION__);
	listItem_ *pItem = (listItem_*)XArray_GetAt(LIST(hEle)->hArrayItem, item);
	if (NULL == pItem) return FALSE;

	listSubItem_ *pSubItem = (listSubItem_*)XArray_GetAt(pItem->hArrayItem, subItem);
	if (NULL == pSubItem) return FALSE;

	if (NULL == XEle_GetParentEle(pInfo->hEle))
		XSView_AddEle(hEle, pInfo->hEle);

	itemBindEle_ *pBindEle = (itemBindEle_*)malloc(sizeof(itemBindEle_));
	pBindEle->hEle = pInfo->hEle;
	pBindEle->left = pInfo->left;
	pBindEle->top = pInfo->top;
	pBindEle->width = pInfo->width;
	pBindEle->height = pInfo->height;

	if (NULL == pSubItem->hArrayBindEle)
		pSubItem->hArrayBindEle = XArray_Create();

	XArray_Add(pSubItem->hArrayBindEle, pBindEle);
	return TRUE;
}

/// @brief ��������С���.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ������.
/// @param minWidth  ��������С���.
void WINAPI XList_SetColumnMinWidth(HELE hEle, int index, int minWidth) //��������С���
{
	IsListDebug(hEle, __FUNCTION__);
	listHeader_ *pItem = Array_GetAtListHeader(LIST(hEle)->hArrayHeader, index);
	pItem->minWidth = minWidth;
}

/// @brief ��ȡ���û�����.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ������.
/// @return ��󶨵��û�����.
void* WINAPI XList_GetItemData(HELE hEle, int index)   //�����û�����
{
	IsListDebug(hEle, __FUNCTION__);

	listItem_ *pItem = (listItem_*)XArray_GetAt(LIST(hEle)->hArrayItem, index);
	if (pItem)
		return pItem->userData;

	XTRACE("API:XList_GetItemData() ����,index[%d],���ܴ���! \n", index);
	return 0;
}

/// @brief ��ʾ�����б�ͷ.
/// @param hEle   Ԫ�ؾ��.
/// @param bShow  TRUE��ʾ,FALSE����.
void WINAPI XList_ShowHeader(HELE hEle, BOOL bShow)
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->bShowHeader = bShow;
}

/// @brief �����û��Ի��б���.
/// @param hEle   Ԫ�ؾ��.
/// @param pFunDrawItem  �Ի溯����,��ʽ����:
/// @code void CALLBACK List_DrawItem(HELE hEle,list_drawItem_ *pDrawItem); @endcode
void WINAPI XList_SetUserDrawItem(HELE hEle, pFunList_DrawItem pFunDrawItem) //�����û��Ի��б���
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	LIST(hEle)->pClass_Fun_Info_Item = NULL;
#endif
}

/// @brief �����û��Ի��б�ͷ��.
/// @param hEle   Ԫ�ؾ��.
/// @param pFunDrawItem  �Ի溯����,��ʽ����:
/// @code  void CALLBACK ListHeader_DrawItem(HELE hEle,listHeader_drawItem_ *pDrawItem); @endcode
void WINAPI XList_SetUserDrawItemHeader(HELE hEle, pFunListHeader_DrawItem pFunDrawItem) //�����û��Ի��б�ͷ��
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->pDrawItemHeader = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	LIST(hEle)->pClass_Fun_Info_ItemHeader = NULL;
#endif
}

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
void WINAPI XList_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի��б���
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->pDrawItem = (pFunList_DrawItem)pCallBackFun;
	LIST(hEle)->pClass_Fun_Info_Item = pClass_Fun_Info;
}

void WINAPI XList_SetUserDrawItemHeaderEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի��б�ͷ��
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->pDrawItemHeader = (pFunListHeader_DrawItem)pCallBackFun;
	LIST(hEle)->pClass_Fun_Info_ItemHeader = pClass_Fun_Info;
}
#endif

/// @brief ���û�رո�ѡ��ť����.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable ֵΪTRUE����,�����෴.
void WINAPI XList_EnableCheckBox(HELE hEle, BOOL bEnable) //���ø�ѡ��
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->bCheck = bEnable;
	LIST(hEle)->bAdjustItem = TRUE;
}

/// @brief ���û�رն���ѡ��.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable ���ֵΪTRUE����ѡ��,������ѡ��.
void WINAPI XList_EnableMultilineSelect(HELE hEle, BOOL bEnable)
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->bMultilineSelect = bEnable;
}

/// @brief ���û�ر��и�����ʾ.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable ֵΪTRUE����,�����෴.
void WINAPI XLsit_EnableLineHighlight(HELE hEle, BOOL bEnable) //���û�ر��и�����ʾ
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->bLineHighlight = bEnable;
}

/// @brief �ж��б��ѡ���Ƿ�ѡ��.
/// @param hEle   Ԫ�ؾ��.
/// @param index  �б�������.
/// @return �����ѡ��ѡ�з���TRUE,�����෴.
BOOL WINAPI XList_IsItemCheck(HELE hEle, int index) //�ж���ĸ�ѡ���Ƿ�ѡ
{
	IsListDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(LIST(hEle)->hArrayItem);
	if (index >= 0 && index < count)
	{
		return Array_GetAtList(LIST(hEle)->hArrayItem, index)->bCheck;
	}
	else
	{
		XTRACE("XList_IsItemCheck() ����\n");
		return FALSE;
	}
}

/// @brief �����б��ѡ��.
/// @param hEle   Ԫ�ؾ��.
/// @param index  �б�������.
/// @param bCheck ֵΪTRUE��ѡ��ѡ��,�����෴.
void WINAPI XList_SetItemCheck(HELE hEle, int index, BOOL bCheck) //������ĸ�ѡ��
{
	IsListDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(LIST(hEle)->hArrayItem);
	if (index >= 0 && index < count)
		Array_GetAtList(LIST(hEle)->hArrayItem, index)->bCheck = bCheck;
}

/// @brief ��ȡ��ͼ������.
/// @param hEle   Ԫ�ؾ��.
/// @param item   ������.
/// @param subItem ��������.
/// @return ͼ������ID
int WINAPI XList_GetItemImage(HELE hEle, int item, int subItem) //��ȡ����ͼƬ
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pObj = LIST(hEle);
	return Array_GetAtListSubItem(Array_GetAtList(pObj->hArrayItem, item)->hArrayItem, subItem)->imageId;
}

/// @brief ��ȡͼƬ�б���Դ���.
/// @param hEle   Ԫ�ؾ��.
/// @return ͼ���б���Դ���
HXCGUI WINAPI XList_GetImageList(HELE hEle)  //��ȡͼƬ�б�
{
	IsListDebug(hEle, __FUNCTION__);
	return LIST(hEle)->hImageList;
}

/// @brief ��ȡ���ı�.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ������.
/// @param subItem ��������
/// @return �ı�����.
wchar_t* WINAPI XList_GetItemText(HELE hEle, int index, int subItem) //��ȡ���ı�
{
	IsListDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(LIST(hEle)->hArrayItem);
	if (index >= 0 && index < count)
	{
		int  headerCount = Array_GetCount(LIST(hEle)->hArrayHeader);
		if (subItem >= 0 && subItem < headerCount)
		{
			list_ *pObj = LIST(hEle);
			HSTRING hStr = Array_GetAtListSubItem(Array_GetAtList(pObj->hArrayItem, index)->hArrayItem, subItem)->hString;
			if (hStr)
				return XStr_GetBuffer(hStr);
		}
	}
	return NULL;
}

/// @brief ��ȡ���.
/// @param hEle   Ԫ�ؾ��.
/// @return �б���߶�.
int WINAPI XList_GetItemHeight(HELE hEle)  //��ȡ���
{
	IsListDebug(hEle, __FUNCTION__);
	return LIST(hEle)->itemHeight;
}

/// @brief ��ȡ�б�ͷ�߶�.
/// @param hEle   Ԫ�ؾ��.
/// @return �б�ͷ�߶�.
int WINAPI XList_GetHeaderHeight(HELE hEle)  //��ȡ�б�ͷ�߶�
{
	IsListDebug(hEle, __FUNCTION__);
	return LIST(hEle)->headerHeight;
}

/// @brief ��ȡ�б�ͷ���ı�.
/// @param hEle   Ԫ�ؾ��
/// @param index  ������
/// @return �ı�����.
wchar_t* WINAPI XList_GetHeaderItemText(HELE hEle, int index)  //��ȡ�б�ͷ���ı�
{
	IsListDebug(hEle, __FUNCTION__);
	int count = Array_GetCount(LIST(hEle)->hArrayHeader);
	if (index >= 0 && index < count)
	{
		HSTRING hStr = Array_GetAtListHeader(LIST(hEle)->hArrayHeader, index)->hString;
		if (hStr)
			return XStr_GetBuffer(hStr);
	}
	return NULL;
}

/// @brief ��ȡѡ��������.
/// @param hEle   Ԫ�ؾ��
/// @return ��ǰѡ���������.
int WINAPI XList_GetSelectCount(HELE hEle)  //��ȡѡ��������
{
	IsListDebug(hEle, __FUNCTION__);
	return Array_GetCount(LIST(hEle)->hArrayCurrItem);
}

/// @brief ��ȡѡ�����.
/// @param hEle Ԫ�ؾ��
/// @return ѡ��������.
int WINAPI XList_GetSelectItem(HELE hEle)  //��ȡѡ����
{
	IsListDebug(hEle, __FUNCTION__);
	if (LIST(hEle)->pCurrItem)
		return LIST(hEle)->pCurrItem->index;
	return -1;
}

/// @brief ��ȡ��ǰ����ѡ�����.
/// @param hEle Ԫ�ؾ��
/// @param pArray int��������,����ѡ���������.
/// @param arrayLength pArray����Ԫ�ظ���
/// @return ����pArray[]����ʵ��ʹ���±�Ԫ������.
int WINAPI XList_GetSelectAllItem(HELE hEle, int *pArray, int arrayLength) //��ȡ����ѡ����
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pObj = LIST(hEle);
	int count = Array_GetCount(pObj->hArrayCurrItem);

	int counts = 0;
	if (arrayLength < count)
		counts = arrayLength;
	else
		counts = count;

	for (int i = 0; i < counts; i++)
	{
		pArray[i] = Array_GetAtList(pObj->hArrayCurrItem, i)->index;
	}
	return counts;
}

/// @brief ��ȡ������.
/// @param hEle Ԫ�ؾ��
/// @return �б�Ԫ��������.
int WINAPI XList_GetItemCount(HELE hEle)   //��ȡ������
{
	IsListDebug(hEle, __FUNCTION__);
	return XArray_GetCount(LIST(hEle)->hArrayItem);
}

/// @brief ��ȡ�б�ͷ������.
/// @param hEle  Ԫ�ؾ��.
/// @param item  ������.
/// @param *pRect ��������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_GetHeaderItemRect(HELE hEle, int item, out_ RECT *pRect) //��ȡ�б�ͷ������
{
	IsListDebug(hEle, __FUNCTION__);
	if (item < 0) return FALSE;

	if (item >= XArray_GetCount(LIST(hEle)->hArrayHeader)) return FALSE;

	listHeader_ *pItem = (listHeader_*)XArray_GetAt(LIST(hEle)->hArrayHeader, item);
	*pRect = pItem->rect;

	return TRUE;
}

/// @brief ��ȡ��������.
/// @param hEle  Ԫ�ؾ��.
/// @param item  ������.
/// @param sub   ��������.
/// @param *pRect ������������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_GetSubItemRect(HELE hEle, int item, int sub, out_ RECT *pRect) //��ȡ��������
{
	IsListDebug(hEle, __FUNCTION__);

	if (item < 0 || sub < 0) return FALSE;

	if (item >= XArray_GetCount(LIST(hEle)->hArrayItem)) return FALSE;

	listItem_ *pItem = (listItem_*)XArray_GetAt(LIST(hEle)->hArrayItem, item);
	listSubItem_ *pSub = (listSubItem_*)XArray_GetAt(pItem->hArrayItem, sub);

	if (sub >= XArray_GetCount(pItem->hArrayItem)) return FALSE;

	*pRect = pSub->rect;

	return TRUE;
}

/// @brief ��ȡ��ѡ��ť����.
/// @param hEle  Ԫ�ؾ��.
/// @param item  ������.
/// @param *pRect ��������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_GetItemCheckRect(HELE hEle, int item, out_ RECT *pRect) //��ȡ��ѡ��ť����
{
	IsListDebug(hEle, __FUNCTION__);

	if (item < 0) return FALSE;

	if (item >= XArray_GetCount(LIST(hEle)->hArrayItem)) return FALSE;

	listItem_ *pItem = (listItem_*)XArray_GetAt(LIST(hEle)->hArrayItem, item);

	*pRect = pItem->rcCheck;

	return TRUE;
}

/// @brief ��ȡָ�����Ԫ������.
/// @param hEle  Ԫ�ؾ��.
/// @param item   ������.
/// @param subItem  ��������.
/// @return ���ذ�Ԫ������,ʧ�ܷ���-1.
int  WINAPI XList_GetItemBindEleCount(HELE hEle, int item, int subItem)
{
	IsListDebug(hEle, __FUNCTION__);

	int count = Array_GetCount(LIST(hEle)->hArrayItem);
	if (item >= 0 && item < count)
	{
		int  headerCount = Array_GetCount(LIST(hEle)->hArrayHeader);
		if (subItem >= 0 && subItem < headerCount)
		{
			listSubItem_ *pSubItem = Array_GetAtListSubItem(Array_GetAtList(LIST(hEle)->hArrayItem, item)->hArrayItem, subItem);
			return XArray_GetCount(pSubItem->hArrayBindEle);
		}
	}
	return -1;
}

/// @brief ��ȡָ�����Ԫ����Ϣ.
/// @param hEle  Ԫ�ؾ��.
/// @param item   ������
/// @param subItem  ��������
/// @param pInfo    ���հ�Ԫ����Ϣ
/// @param index    ��Ԫ������
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XList_GetItemBindEleInfo(HELE hEle, int item, int subItem, out_ itemBindEle_ *pInfo, int index)  //��ȡ������Ϣ
{
	IsListDebug(hEle, __FUNCTION__);

	int count = Array_GetCount(LIST(hEle)->hArrayItem);
	if (item >= 0 && item < count)
	{
		int  headerCount = Array_GetCount(LIST(hEle)->hArrayHeader);
		if (subItem >= 0 && subItem < headerCount)
		{
			listSubItem_ *pSubItem = Array_GetAtListSubItem(Array_GetAtList(LIST(hEle)->hArrayItem, item)->hArrayItem, subItem);
			if (index > 0 && index < XArray_GetCount(pSubItem->hArrayBindEle))
			{
				pInfo = (itemBindEle_*)XArray_GetAt(pSubItem->hArrayBindEle, index);
				return TRUE;
			}
		}
	}
	return FALSE;
}

/// @brief ��ȡ�п��.
/// @param hEle   Ԫ�ؾ��.
/// @param index   ������.
/// @return ����ɹ������п��,���򷵻�-1.
int WINAPI XList_GetColumnWidth(HELE hEle, int index)   //��ȡ�п�
{
	IsListDebug(hEle, __FUNCTION__);
	if (index < 0)
		return -1;

	list_ *pObj = LIST(hEle);
	int count = Array_GetCount(pObj->hArrayHeader);
	if (count < 1)
		return -1;

	if (index >= count)
		return -1;

	return Array_GetAtListHeader(pObj->hArrayHeader, index)->width;
}

/// @brief ��ȡ��������.
/// @param hEle   Ԫ�ؾ��.
/// @return ��������.
int WINAPI XList_GetSpacingLeft(HELE hEle)  //��ȡ��������
{
	IsListDebug(hEle, __FUNCTION__);
	return LIST(hEle)->spacingLeft;
}

/// @brief ��ȡ�����Ҽ��.
/// @param hEle   Ԫ�ؾ��.
/// @return �����Ҽ��.
int WINAPI XList_GetSpacingRight(HELE hEle) //��ȡ�����Ҽ��
{
	IsListDebug(hEle, __FUNCTION__);
	return LIST(hEle)->spacingRight;
}

/// @brief ɾ��ָ����.
/// @param hEle Ԫ�ؾ��
/// @param index Ҫɾ����������
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_DeleteColumn(HELE hEle, int index)  //ɾ����
{
	IsListDebug(hEle, __FUNCTION__);
	if (index < 0)
		return FALSE;

	list_ *pObj = LIST(hEle);
	int count = Array_GetCount(pObj->hArrayHeader); //m_listHeader.m_count;
	if (index >= count)
		return FALSE;

	List_CancelSelectAll(hEle);

	//ɾ��
	listHeader_ *pDel = Array_GetAtListHeader(pObj->hArrayHeader, index);
	if (pDel->hString)
		XStr_Destroy(pDel->hString);
	free(pDel);
	XArray_DeleteIndex(pObj->hArrayHeader, index);

	int countItem = Array_GetCount(pObj->hArrayItem); //m_listItem.m_count;
	for (int i = 0; i < countItem; i++)
	{
		listSubItem_ *pDelSub = Array_GetAtListSubItem(Array_GetAtList(pObj->hArrayItem, i)->hArrayItem, index);

		if (pDelSub->hString)
			XStr_Destroy(pDel->hString);

		if (pDelSub->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pDelSub->hArrayBindEle);
			for (int j = 0; j < bindEleCount; j++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pDelSub->hArrayBindEle, j);
				if (pBindEle->hEle)
					XEle_Destroy(pBindEle->hEle);
				free(pBindEle);
			}
			XArray_Destroy(pDelSub->hArrayBindEle);
		}

		free(pDelSub);
		XArray_DeleteIndex(Array_GetAtList(pObj->hArrayItem, i)->hArrayItem, index);
	}
	List_AdjustHeader(hEle);
	List_AdjustItem(hEle);
	return TRUE;
}

/// @brief ����������.
/// @param hEle Ԫ�ؾ��
/// @param bGrid TRUE��������,�����෴.
void WINAPI XList_EnableGrid(HELE hEle, BOOL bGrid) //����������ʽ
{
	IsListDebug(hEle, __FUNCTION__);
	LIST(hEle)->bGrid = bGrid;
}

/// @brief ����������ĸ�����,���û�����κ����Ϸ���-1.
/// @param hEle Ԫ�ؾ��
/// @param pPt  �����.
/// @return �������������,���û�����κ����Ϸ���-1.
int  WINAPI XList_HitTest(HELE hEle, POINT *pPt)
{
	IsListDebug(hEle, __FUNCTION__);
	POINT pt = *pPt;

	int y;
	if (LIST(hEle)->bShowHeader)
		y = pPt->y - LIST(hEle)->headerHeight - XSView_GetVViewPos(hEle);
	else
		y = pPt->y - XSView_GetVViewPos(hEle);

	int pos = y / LIST(hEle)->itemHeight;
	if (pos >= Array_GetCount(LIST(hEle)->hArrayItem))
	{
		pos = -1;
	}
	return pos;
}

/// @brief �����������ĸ����ϼ�����.
/// @param hEle Ԫ�ؾ��
/// @param pPt  �����.
/// @param *item  ���շ��ص�������.
/// @param *sub   ���շ��ص���������.
/// @return ����ɹ�����TRUE,�����෴..
BOOL WINAPI XList_HitTestEx(HELE hEle, POINT *pPt, int *item, int *sub) //�����������ĸ����ϼ�����,-1û�����κ�����
{
	IsListDebug(hEle, __FUNCTION__);
	*item = XList_HitTest(hEle, pPt);
	if (*item < 0) return FALSE;

	POINT pt = *pPt;
	pt.x = pPt->x - XSView_GetHViewPos(hEle);
	pt.y = pPt->y - XSView_GetVViewPos(hEle);

	listItem_ *pItem = (listItem_*)XArray_GetAt(LIST(hEle)->hArrayItem, *item);

	int count = XArray_GetCount(pItem->hArrayItem);
	for (int i = 0; i < count; i++)
	{
		listSubItem_ *pSub = (listSubItem_*)XArray_GetAt(pItem->hArrayItem, i);
		if (PtInRect(&pSub->rect, pt))
		{
			*sub = i;
			return TRUE;
		}
	}
	return FALSE;
}

/// @brief ɾ��������.
/// @param hEle Ԫ�ؾ��
void WINAPI XList_DeleteAllColumns(HELE hEle)   //ɾ��������
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pObj = LIST(hEle);
	List_CancelSelectAll(hEle);
	XList_DeleteAllItems(hEle);
	int count = Array_GetCount(pObj->hArrayHeader);
	for (int i = 0; i < count; i++)
	{
		listHeader_ *pDel = Array_GetAtListHeader(pObj->hArrayHeader, i);
		if (pDel->hString)
			XStr_Destroy(pDel->hString);
		free(pDel);
	}
	XArray_DeleteAll(pObj->hArrayHeader);
}

/// @brief ɾ��ָ����.
/// @param hEle Ԫ�ؾ��
/// @param index Ҫɾ����������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XList_DeleteItem(HELE hEle, int index)  //ɾ����
{
	IsListDebug(hEle, __FUNCTION__);

	list_ *pObj = LIST(hEle);
	int countHeader = Array_GetCount(pObj->hArrayHeader);
	if (countHeader < 1)
		return FALSE;

	if (index < 0)
		return FALSE;

	int countItem = Array_GetCount(pObj->hArrayItem);
	if (index >= countItem)
		return FALSE;

	XList_CancelSelect(hEle, index);//ȡ������ѡ��

	for (int i = 0; i < countHeader; i++)
	{
		listSubItem_ *pDel = Array_GetAtListSubItem(Array_GetAtList(pObj->hArrayItem, index)->hArrayItem, i);
		if (pDel->hString)
			XStr_Destroy(pDel->hString);

		if (pDel->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pDel->hArrayBindEle);
			for (int j = 0; j < bindEleCount; j++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pDel->hArrayBindEle, j);
				if (pBindEle->hEle)
					XEle_Destroy(pBindEle->hEle);
				free(pBindEle);
			}
			XArray_Destroy(pDel->hArrayBindEle);
		}

		free(pDel);
	}
	listItem_ *pDelItem = Array_GetAtList(pObj->hArrayItem, index);
	XArray_Destroy(pDelItem->hArrayItem);
	free(pDelItem);

	XArray_DeleteIndex(pObj->hArrayItem, index);

	pObj->bAdjustItem = TRUE;
	List_AdjustItem(hEle);
	return TRUE;
}

/// @brief ɾ��������.
/// @param hEle Ԫ�ؾ��
void WINAPI XList_DeleteAllItems(HELE hEle)  //ɾ��������
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pObj = LIST(hEle);
	int countHeader = Array_GetCount(pObj->hArrayHeader);
	int countItem = Array_GetCount(pObj->hArrayItem);

	List_CancelSelectAll(hEle);

	listItem_ *pDelItem = NULL;
	listSubItem_ *pDelSubItem = NULL;
	for (int i = 0; i < countItem; i++)
	{
		pDelItem = Array_GetAtList(pObj->hArrayItem, i);
		for (int j = 0; j < countHeader; j++)
		{
			pDelSubItem = Array_GetAtListSubItem(pDelItem->hArrayItem, j);
			if (pDelSubItem->hString)
				XStr_Destroy(pDelSubItem->hString);

			if (pDelSubItem->hArrayBindEle)
			{
				int bindEleCount = XArray_GetCount(pDelSubItem->hArrayBindEle);
				for (int c = 0; c < bindEleCount; c++)
				{
					itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pDelSubItem->hArrayBindEle, c);
					if (pBindEle->hEle)
						XEle_Destroy(pBindEle->hEle);
					free(pBindEle);
				}
				XArray_Destroy(pDelSubItem->hArrayBindEle);
			}

			free(pDelSubItem);
		}
		if (pDelItem->hArrayItem)
			XArray_Destroy(pDelItem->hArrayItem);
		free(pDelItem);
	}
	XArray_DeleteAll(pObj->hArrayItem);
	List_AdjustItem(hEle);
}

BOOL CALLBACK List_OnEleDraw(HELE hEle, HDRAW hDraw)
{
	list_   *pList = (list_*)hEle;

	if (pList->bAdjustHeader)
	{
		List_AdjustHeader(hEle);
		pList->bAdjustHeader = FALSE;
	}

	if (pList->bAdjustItem)
	{
		List_AdjustItem(hEle);
		pList->bAdjustItem = FALSE;
	}

	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (SCROLLVIEW(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, SCROLLVIEW(hEle)->hImage_bk, &rect);
	}

	//�����б�ͷ
	if (pList->bShowHeader)
	{
		int left = XSView_GetSpacingLeft(hEle);
		int right = XSView_GetSpacingRight(hEle);

		RECT rcHeader = { left,rect.top + 2,rect.right - right,rect.top + pList->headerHeight };
		List_DrawHeader_BG(hEle, hDraw, &rcHeader);
		int x;
		int y;
		XDraw_GetOffset_(hDraw, &x, &y);
		int posx = x + XSView_GetHViewPos(hEle);

		XDraw_SetOffset_(hDraw, posx, y);
		List_DrawItemHeader(hEle, hDraw);
		XDraw_SetOffset_(hDraw, x, y);
	}

	if (((ele_*)hEle)->bBorder)
	{
		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, ((ele_*)hEle)->borderColor);
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
	return TRUE;
}

BOOL CALLBACK List_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	list_ *pList = LIST(hEle);
	//�����б�
	List_DrawList(hEle, hDraw);

	//�����϶�����---------
	if (pList->bDrag)
	{
		RECT rcDrag;
		if (pList->dragEndPt.x > pList->dragPt.x)
		{
			rcDrag.left = pList->dragPt.x;
			rcDrag.right = pList->dragEndPt.x;
		}
		else
		{
			rcDrag.left = pList->dragEndPt.x;
			rcDrag.right = pList->dragPt.x;
		}

		if (pList->dragEndPt.y > pList->dragPt.y)
		{
			rcDrag.top = pList->dragPt.y;
			rcDrag.bottom = pList->dragEndPt.y;
		}
		else
		{
			rcDrag.top = pList->dragEndPt.y;
			rcDrag.bottom = pList->dragPt.y;
		}

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(80, 168, 220));
		XDraw_FrameRect_(hDraw, &rcDrag, hBrush);
	}
	/*
		//�����б�ͷ
		if(pList->bShowHeader)
		{
			int x;
			int y;
			XDraw_GetOffset_(hDraw,&x,&y);

			int t=XSView_GetVViewPos(hEle);
			int posy=y-XSView_GetVViewPos(hEle);
			XDraw_SetOffset_(hDraw,x,posy);
			List_DrawItemHeader(hEle,hDraw);
			XDraw_SetOffset_(hDraw,x,y);
		}*/
	return TRUE;
}

void List_DrawItemHeader(HELE hEle, HDRAW hDraw)
{
	list_ *pList = LIST(hEle);
	//List_DrawHeader_BG(hEle,hDraw); //�����б�ͷ����

	int count = Array_GetCount(pList->hArrayHeader);
	if (count < 1) return;

	if (pList->pDrawItemHeader)
	{
		List_DrawHeader_Item(hEle, hDraw);   //�û��Ի��б���
	}
	else
	{
		List_DrawHeader_Item_SYS(hEle, hDraw);  //ϵͳ�����б���
	}
}

void List_DrawHeader_BG(HELE hEle, HDRAW hDraw, RECT *pRect)  //�����б�ͷ����
{
	list_ *pList = LIST(hEle);

	//	int widths=XSView_GetHSizeTotalAccurate(hEle);
	//	if(widths<XSView_GetViewWidth(hEle))
	//		widths=XSView_GetViewWidth(hEle);

		//�б�ͷ����
	//	RECT rcHeader={0,0,widths,XSView_GetViewHeight(hEle)};
	//	rcHeader.bottom=pList->headerHeight;
	RECT rcHeader = *pRect;

	//�����б�ͷ����
	if (pList->pDrawItemHeader) //�û�����
	{
		listHeader_drawItem_ drawItem;
		drawItem.hDraw = hDraw;
		drawItem.index = 0;
		drawItem.imageId = 0;
		drawItem.state = -1;
		drawItem.rect = rcHeader;
		drawItem.pText = NULL;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pList->pClass_Fun_Info_Item)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)&drawItem;
			event_.lParam = NULL;
			event_.pClass_fun = pList->pClass_Fun_Info_ItemHeader;
			((pFunClassEventMsg)pList->pDrawItemHeader)(&event_, xc_fun_v_e_list_header);
		}
		else
		{
			pList->pDrawItemHeader(hEle, &drawItem);
		}
#else
		pList->pDrawItemHeader(hEle, &drawItem);
#endif
	}
	else //ϵͳ����
	{
		XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(220, 220, 220), &rcHeader, 1);

		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(240, 240, 240));
		HPEN hPen2 = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(128, 128, 128));

		HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);
		XDraw_MoveToEx_(hDraw, 0, pList->headerHeight - 3, 0);
		XDraw_LineTo_(hDraw, rcHeader.right, pList->headerHeight - 3);

		XDraw_SelectObject_(hDraw, hPen2);
		XDraw_MoveToEx_(hDraw, 0, pList->headerHeight - 2, 0);
		XDraw_LineTo_(hDraw, rcHeader.right, pList->headerHeight - 2);
	}
	XDraw_RestoreGDIOBJ_(hDraw);
}

void List_DrawHeader_Item(HELE hEle, HDRAW hDraw)  //�����б�ͷ��
{
	list_ *pList = LIST(hEle);
	int count = Array_GetCount(pList->hArrayHeader);

	for (int i = 0; i < count; i++)
	{
		listHeader_ *pHeader = Array_GetAtListHeader(pList->hArrayHeader, i);
		listHeader_drawItem_ drawItem;
		drawItem.hDraw = hDraw;
		drawItem.index = i;
		drawItem.imageId = pHeader->imageId;
		drawItem.state = pHeader->state;
		drawItem.rect = pHeader->rect;
		drawItem.pText = XStr_GetBuffer(pHeader->hString);

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pList->pClass_Fun_Info_Item)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)&drawItem;
			event_.lParam = NULL;
			event_.pClass_fun = pList->pClass_Fun_Info_ItemHeader;
			((pFunClassEventMsg)pList->pDrawItemHeader)(&event_, xc_fun_v_e_list_header);
		}
		else
		{
			pList->pDrawItemHeader(hEle, &drawItem);
		}
#else
		pList->pDrawItemHeader(hEle, &drawItem);
#endif
		XDraw_RestoreGDIOBJ_(hDraw);

	}
}

void List_DrawHeader_Item_SYS(HELE hEle, HDRAW hDraw) //ϵͳ�����б���
{
	list_ *pList = LIST(hEle);
	int count = Array_GetCount(pList->hArrayHeader);

	//ϵͳ�����б���
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(100, 100, 100));
	HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(180, 180, 180));

	HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);

	RECT rcText;
	RECT rcItem;
	int lineX = Array_GetAtListHeader(pList->hArrayHeader, 0)->rect.left - 1;
	XDraw_MoveToEx_(hDraw, lineX, 1, 0);
	XDraw_LineTo_(hDraw, lineX, pList->headerHeight - 3);

	for (int i = 0; i < count; i++)
	{
		listHeader_ *pHeader = Array_GetAtListHeader(pList->hArrayHeader, i);
		rcItem = pHeader->rect;
		rcItem.top++;
		rcItem.bottom -= 3;

		rcText = rcItem;
		rcText.left += 5;

		if (STATE_STAY == pHeader->state)
		{
			XDraw_GradientFill2_(hDraw, RGB(230, 230, 230), RGB(200, 200, 200), &rcItem, 1);

			if (NULL != pList->hImageList && (pHeader->imageId > -1)) //����ͼ��
			{
				int cx = XImageList_GetWidth(pList->hImageList);
				int cy = XImageList_GetHeight(pList->hImageList);
				XImageList_DrawImage(pList->hImageList, hDraw, pHeader->imageId, rcText.left, rcText.top + pList->headerHeight / 2 - cy / 2);
				rcText.left += cx + 2;
			}
			{
				HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(248, 169, 0));
				HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);

				XDraw_MoveToEx_(hDraw, rcItem.left - 1, rcItem.bottom + 1, 0);
				XDraw_LineTo_(hDraw, rcItem.right, rcItem.bottom + 1);
			}
			{
				HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(252, 194, 71));
				HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);

				XDraw_MoveToEx_(hDraw, rcItem.left - 1, rcItem.bottom, 0);
				XDraw_LineTo_(hDraw, rcItem.right, rcItem.bottom);
			}
		}
		else if (STATE_DOWN == pHeader->state)
		{
			XDraw_GradientFill2_(hDraw, RGB(200, 200, 200), RGB(230, 230, 230), &rcItem, 1);

			if (NULL != pList->hImageList && (pHeader->imageId > -1)) //����ͼ��
			{
				int cx = XImageList_GetWidth(pList->hImageList);
				int cy = XImageList_GetHeight(pList->hImageList);
				XImageList_DrawImage(pList->hImageList, hDraw, pHeader->imageId, rcText.left, rcText.top + pList->headerHeight / 2 - cy / 2);
				rcText.left += cx + 2;
			}

			rcText.left += 2;
			rcText.top += 2;
			{
				HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(248, 169, 0));
				HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);

				XDraw_MoveToEx_(hDraw, rcItem.left - 1, rcItem.bottom + 1, 0);
				XDraw_LineTo_(hDraw, rcItem.right, rcItem.bottom + 1);
			}
			{
				HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(252, 194, 71));
				HGDIOBJ hOldPen = XDraw_SelectObject_(hDraw, hPen);

				XDraw_MoveToEx_(hDraw, rcItem.left - 1, rcItem.bottom, 0);
				XDraw_LineTo_(hDraw, rcItem.right, rcItem.bottom);
			}
		}
		else
		{
			if (NULL != pList->hImageList && (pHeader->imageId > -1)) //����ͼ��
			{
				int cx = XImageList_GetWidth(pList->hImageList);
				int cy = XImageList_GetHeight(pList->hImageList);
				XImageList_DrawImage(pList->hImageList, hDraw, pHeader->imageId, rcText.left, rcText.top + pList->headerHeight / 2 - cy / 2);
				rcText.left += cx + 2;
			}
		}

		HSTRING hString = pHeader->hString;
		if (hString)
		{
			wchar_t *pText = XStr_GetBuffer(hString);
			if (pText)
				XDraw_DrawText_(hDraw, pText, XStr_GetLength(hString), &rcText, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
		}

		XDraw_MoveToEx_(hDraw, rcText.right - 1, 1, 0);
		XDraw_LineTo_(hDraw, rcText.right - 1, pList->headerHeight - 3);
	}
}

BOOL List_MouseMoveHeader(HELE hEle, POINT *pPt)
{
	list_ *pList = LIST(hEle);
	POINT pt = { (-XSView_GetHViewPos(hEle)) + pPt->x,pPt->y };
	if (-1 != pList->downIndex) //�����б�ͷ
	{
		List_AdjustDragHeader(hEle, pt, pList->downIndex);
		return TRUE;
	}

	///////////////////////////////////////////////
	if (pPt->y > pList->headerHeight)
	{
		if (pList->pCurrHeader)
		{
			pList->pCurrHeader->state = STATE_LEAVE;
			pList->pCurrHeader = NULL;
			XEle_RedrawEle(hEle);
		}
		return FALSE;
	}

	//////////////////
	int count = Array_GetCount(pList->hArrayHeader);
	for (int i = 0; i < count; i++)
	{
		listHeader_ *pHeader = Array_GetAtListHeader(pList->hArrayHeader, i);
		if (PtInRect(&pHeader->rect, pt))
		{
			if (pList->pCurrHeader != pHeader)
			{
				if (pList->pCurrHeader)
					pList->pCurrHeader->state = STATE_LEAVE;

				pList->pCurrHeader = pHeader;
				pList->pCurrHeader->state = STATE_STAY;

				XEle_RedrawEle(hEle);
			}
			if (pt.x > (pHeader->rect.right - 5)) //���϶��ָ�����
			{
				::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			}
			return TRUE;
		}
	}

	if (pList->pCurrHeader)
	{
		pList->pCurrHeader->state = STATE_LEAVE;
		pList->pCurrHeader = NULL;
		XEle_RedrawEle(hEle);
	}
	return TRUE;
}

BOOL List_LButtonDownHeader(HELE hEle, POINT *pPt)
{
	list_ *pList = LIST(hEle);

	if (pPt->y > pList->headerHeight)
		return FALSE;

	int posX = (-XSView_GetHViewPos(hEle)) + pPt->x;
	POINT pt = { posX,pPt->y };

	int countHeader = Array_GetCount(pList->hArrayHeader);
	for (int i = countHeader - 1; i > -1; i--)
	{
		if (PtInRect(&Array_GetAtListHeader(pList->hArrayHeader, i)->rect, pt))
		{
			if (pt.x > (Array_GetAtListHeader(pList->hArrayHeader, i)->rect.right - 5))
			{
				pList->downIndex = i;
				::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				XEle_SetCapture(hEle);
			}
			else
			{
				Array_GetAtListHeader(pList->hArrayHeader, i)->state = STATE_DOWN;
				XEle_RedrawEle(hEle);
			}
			return TRUE;
		}
	}
	return TRUE;
}

BOOL List_LButtonUpHeader(HELE hEle, POINT *pPt)
{
	list_ *pList = LIST(hEle);
	if (List_MouseMoveDragHeaderEnd(hEle))
		return TRUE;

	//***********************************************
	if (pPt->y > pList->headerHeight)
		return FALSE;

	POINT pt = { (-XSView_GetHViewPos(hEle)) + pPt->x,pPt->y };
	int count = Array_GetCount(pList->hArrayHeader);
	for (int i = 0; i < count; i++)
	{
		if (PtInRect(&Array_GetAtListHeader(pList->hArrayHeader, i)->rect, pt))
		{
			Array_GetAtListHeader(pList->hArrayHeader, i)->state = STATE_STAY;
			Ele_SendEvent(hEle, XE_LIST_HEADER_CLICK, i, 0);
			if (!XC_IsHELE(hEle)) return TRUE;
			XEle_RedrawEle(hEle);
			return TRUE;
		}
	}
	return TRUE;
}

BOOL List_MouseMoveDragHeaderEnd(HELE hEle)
{
	list_ *pList = LIST(hEle);
	if (-1 != pList->downIndex)
	{
		int wParam = pList->downIndex;
		pList->downIndex = -1;

		XEle_ReleaseCapture(hEle);

		int countHeader = Array_GetCount(pList->hArrayHeader);
		if (countHeader > 0)
		{
			listHeader_ *pHeader = Array_GetAtListHeader(pList->hArrayHeader, countHeader - 1);
			int height = pList->itemHeight*Array_GetCount(pList->hArrayItem);//+pList->headerHeight; //��ͼ�ܸ߶�
			XSView_SetSize(hEle, pHeader->rect.right + pList->spacingRight, height);

			pHeader = Array_GetAtListHeader(pList->hArrayHeader, wParam);
			Ele_SendEvent(hEle, XE_LIST_HEADER_CHANGE, wParam, pHeader->rect.right - pHeader->rect.left);
			if (!XC_IsHELE(hEle)) return TRUE;
			XEle_RedrawEle(hEle);
		}
		return TRUE;
	}
	return  FALSE;
}

void List_MouseLeaveHeader(HELE hEle)
{
	list_ *pList = LIST(hEle);
	if (pList->pCurrHeader)
	{
		pList->pCurrHeader->state = STATE_LEAVE;
		pList->pCurrHeader = NULL;
		XEle_RedrawEle(hEle);
	}
}

BOOL List_MouseMove_View(HELE hEleView, POINT *pPt)
{
	//list_ *pList=LIST(hEle);
	if (FALSE == ((list_*)((ele_*)hEleView)->pParentEle)->bDrag)
	{
		List_MouseMoveDragBegin_View(hEleView, pPt);
	}
	else
	{
		List_MouseMoveDrag_View(hEleView, pPt);
	}
	return FALSE;
}

void List_MouseMoveDragBegin_View(HELE hEleView, POINT *pPt) //׼���϶�ѡ��
{
	list_ *pList = (list_*)((ele_*)hEleView)->pParentEle;
	HELE  hList = (HELE)pList;

	if (FALSE == pList->bMultilineSelect)
		return;
	if (pList->down)
	{
		if (pPt->x<(pList->dragPt.x - 5) || pPt->x>(pList->dragPt.x + 5)
			|| pPt->y<(pList->dragPt.y - 5) || pPt->y>(pList->dragPt.y + 5))
		{
			pList->bDrag = TRUE;

			listItem_ *pOld = pList->pCurrItem;
			List_CancelSelectAll(hList);
			if (pOld)
			{
				XArray_Add(pList->hArrayCurrItem, pOld);
				pList->pCurrItem = pOld;
				pList->pCurrItem->state = STATE_SELECT;
			}
			pList->dragPt.x = pList->dragPt.x - XSView_GetHViewPos(hList);
			pList->dragPt.y = pList->dragPt.y - XSView_GetVViewPos(hList);
			pList->dragEndPt.x = pPt->x - XSView_GetHViewPos(hList);
			pList->dragEndPt.y = pPt->y - XSView_GetVViewPos(hList);

			g_hList = hList;
			SetTimer(XEle_GetHWnd(hList), IDT_LIST_DRAG_RECT, 50, List_TimerProc);

			XEle_SetCapture(hEleView);
		}
	}
}

void List_MouseMoveDrag_View(HELE hEleView, POINT *pPt) //�϶�ѡ��
{
	list_ *pList = (list_*)((ele_*)hEleView)->pParentEle;
	HELE  hList = (HELE)pList;

	pList->dragEndPt.x = pPt->x - XSView_GetHViewPos(hList);
	pList->dragEndPt.y = pPt->y - XSView_GetVViewPos(hList);

	//�϶�����--------------------

	RECT rcDrag;
	if (pList->dragEndPt.x > pList->dragPt.x)
	{
		rcDrag.left = pList->dragPt.x;
		rcDrag.right = pList->dragEndPt.x;
	}
	else
	{
		rcDrag.left = pList->dragEndPt.x;
		rcDrag.right = pList->dragPt.x;
	}
	if (pList->dragEndPt.y > pList->dragPt.y)
	{
		rcDrag.top = pList->dragPt.y;
		rcDrag.bottom = pList->dragEndPt.y;
	}
	else
	{
		rcDrag.top = pList->dragEndPt.y;
		rcDrag.bottom = pList->dragPt.y;
	}

	int count = Array_GetCount(pList->hArrayHeader);
	int right = Array_GetAtListHeader(pList->hArrayHeader, count - 1)->rect.right;

	int itemCout = Array_GetCount(pList->hArrayItem);
	RECT rcItems;//={pList->spacingLeft,pList->headerHeight,right-pList->spacingRight,(itemCout*pList->itemHeight)+pList->headerHeight};
//	if(pList->bShowHeader)
//		rcItems.top=pList->headerHeight;
//	else
	rcItems.top = 0;
	rcItems.left = pList->spacingLeft;
	rcItems.right = right - pList->spacingRight;
	rcItems.bottom = (itemCout*pList->itemHeight) + pList->headerHeight;

	//	HRGN hRng=CreateRectRgn(rcItems.left,rcItems.top,rcItems.right,rcItems.bottom);
	//	if(RectInRegion(hRng,&rcDrag))
	if (XC_RectInRect(&rcItems, &rcDrag))
	{
		int index1 = 0;
		int index2 = 0;
		//	if(pList->bShowHeader)
		//	{	
		//		index1=(pList->dragPt.y-pList->headerHeight)/pList->itemHeight;
		//		index2=(pList->dragEndPt.y-pList->headerHeight)/pList->itemHeight;
		//	}else
		{
			index1 = (pList->dragPt.y) / pList->itemHeight;
			index2 = (pList->dragEndPt.y) / pList->itemHeight;
		}
		if (index1 < index2) //�����϶�
		{
			//MouseMoveDragDown(index1,index2);
			List_MouseMoveDragDown(hList, index1, index2);
		}
		else if (index1 == index2) //ֻѡ����һ��
		{
			int countItem = Array_GetCount(pList->hArrayItem);
			if (index1 >= 0 && index1 <= (countItem - 1))
			{
				listItem_ *pItem = Array_GetAtList(pList->hArrayItem, index1);
				if (pList->pCurrItem)
				{
					List_CancelSelectAll(hList);
					pItem->state = STATE_SELECT;
					//pList->listCurrItem.Add(pItem);
					XArray_Add(pList->hArrayCurrItem, pItem);
					pList->pCurrItem = pItem;
				}
				else
				{
					pItem->state = STATE_SELECT;
					//pList->listCurrItem.Add(pItem);
					XArray_Add(pList->hArrayCurrItem, pItem);
					pList->pCurrItem = pItem;
				}
			}

		}
		else //�����϶�
		{
			//MouseMoveDragUp(index2,index1);
			List_MouseMoveDragUp(hList, index2, index1);
		}
	}
	else
	{
		List_CancelSelectAll(hList);
	}
	//DeleteObject(hRng);

	//������ͼ--------------------------------------
	if (pPt->y < (pList->headerHeight))
	{
		//	if(pList->bShowHeader)
		//		XSView_ScrollTopLine(hEle);
		//	else
		if (pPt->y <= 0)
			XSView_ScrollTopLine(hList);

	}
	else if (pPt->y > XSView_GetViewHeight(hList))
	{
		XSView_ScrollDownLine(hList);
	}
	else if (pPt->x < 0)
	{
		XSView_ScrollLeftLine(hList);
	}
	else if (pPt->x > XSView_GetViewWidth(hList))
	{
		XSView_ScrollRightLine(hList);
	}
}

void List_LButtonDown(HELE hEle, POINT *pPt)
{
	HELE hList = hEle;
	list_ *pList = LIST(hList);

	if (FALSE == pList->bMultilineSelect) //����ѡ��
	{
		if (0x8000 & GetKeyState(VK_CONTROL)) //ctrl ����״̬
			return;
		if (0x8000 & GetKeyState(VK_SHIFT)) //shift ����״̬
			return;
	}

	int countHeader = Array_GetCount(pList->hArrayHeader);
	if (countHeader < 1)
		return;

	int countItem = Array_GetCount(pList->hArrayItem);
	if (countItem < 1)
		return;

	int posX = pPt->x - XSView_GetHViewPos(hList);
	int posY = pPt->y - XSView_GetVViewPos(hList);

	int right = Array_GetAtListHeader(pList->hArrayHeader, countHeader - 1)->rect.right;
	int index = -1; //��ǰѡ����

	BOOL  bBlank = FALSE; //������ڿհ�����TRUE
	if (posX < pList->spacingLeft)
	{
		bBlank = TRUE;
	}
	else if (posX > (right - pList->spacingRight))
	{
		bBlank = TRUE;
	}
	else
	{
		//	if(pList->bShowHeader)
		//		index=(posY-pList->headerHeight)/pList->itemHeight;
		//	else
		index = (posY) / pList->itemHeight;
		if (index < 0 || index >= countItem)
		{
			bBlank = TRUE;
		}
	}
	//ѡ����
	if (0x8000 & GetKeyState(VK_CONTROL)) //ctrl ����״̬
	{
		if (FALSE == bBlank)
		{
			listItem_ *pItem = Array_GetAtList(pList->hArrayItem, index);
			if (STATE_SELECT != pItem->state)
			{
				pItem->state = STATE_SELECT;
				pList->pCurrItem = pItem;
				XArray_Add(pList->hArrayCurrItem, pItem);
				Ele_SendEvent(hList, XE_LIST_SELECT, pItem->index, 0);
			}
			else
			{
				if (pList->pCurrItem == pItem)
				{
					pItem->state = 0;
					XArray_Delete(pList->hArrayCurrItem, pItem);

					if (Array_GetCount(pList->hArrayCurrItem) > 0)
					{
						pList->pCurrItem = Array_GetAtList(pList->hArrayCurrItem, Array_GetCount(pList->hArrayCurrItem) - 1);
					}
					else
						pList->pCurrItem = NULL;
				}
				else
				{
					pItem->state = 0;
					XArray_Delete(pList->hArrayCurrItem, pItem);
				}

				if (pList->pCurrItem)
				{
					Ele_SendEvent(hList, XE_LIST_SELECT, pItem->index, 0);
				}
				else
				{
					Ele_SendEvent(hList, XE_LIST_SELECT, -1, 0);
				}
			}
			if (!XC_IsHELE(hEle)) return;
			XEle_RedrawEle(hEle);
		}
	}
	else if (0x8000 & GetKeyState(VK_SHIFT)) //shift ����״̬
	{
		if (FALSE == bBlank)
		{
			int count = Array_GetCount(pList->hArrayCurrItem);
			if (0 == count)
			{
				listItem_ *pItem = Array_GetAtList(pList->hArrayItem, index);
				pItem->state = STATE_SELECT;
				XArray_Add(pList->hArrayCurrItem, pItem);
				pList->pCurrItem = pItem;
				Ele_SendEvent(hList, XE_LIST_SELECT, pItem->index, 0);

				if (!XC_IsHELE(hEle)) return;

				XEle_RedrawEle(hEle);
			}
			else if (pList->pCurrItem)
			{
				listItem_ *pCurr = pList->pCurrItem;
				List_CancelSelectAll(hList);
				pList->pCurrItem = pCurr;
				pList->pCurrItem->state = STATE_SELECT;

				int begin = 0, end = 0;
				if (pList->pCurrItem->index < index)
				{
					begin = pList->pCurrItem->index;
					end = index;
				}
				else
				{
					begin = index;
					end = pList->pCurrItem->index;
				}

				if ((end - begin) > 0)
				{
					int countItem = Array_GetCount(pList->hArrayItem);
					for (int i = begin; i <= end; i++)
					{
						listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
						pItem->state = STATE_SELECT;
						XArray_Add(pList->hArrayCurrItem, pItem);
					}
					Ele_SendEvent(hList, XE_LIST_SELECT, pList->pCurrItem->index, 0);
					if (!XC_IsHELE(hEle)) return;
					XEle_RedrawEle(hEle);
				}
			}
		}
	}
	else
	{
		if (FALSE == bBlank) //ѡ����
		{
			listItem_ *pItem = Array_GetAtList(pList->hArrayItem, index);

			int count = Array_GetCount(pList->hArrayCurrItem);
			for (int i = 0; i < count; i++)
			{
				Array_GetAtList(pList->hArrayCurrItem, i)->state = 0;
			}
			XArray_DeleteAll(pList->hArrayCurrItem);

			pList->pCurrItem = pItem;

			XArray_Add(pList->hArrayCurrItem, pItem);
			pItem->state = STATE_SELECT;

			//��鸴ѡ��
			if (pList->bCheck)
			{
				POINT ptCheck = { posX,posY };
				if (PtInRect(&pItem->rcCheck, ptCheck))
				{
					pItem->bCheck = pItem->bCheck ? FALSE : TRUE;
				}
			}
			Ele_SendEvent(hList, XE_LIST_SELECT, pItem->index, 0);
			if (!XC_IsHELE(hEle)) return;
			XEle_RedrawEle(hEle);

		}
		else //�հ�����
		{
			pList->pCurrItem = NULL;
			int count = Array_GetCount(pList->hArrayCurrItem);
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					Array_GetAtList(pList->hArrayCurrItem, i)->state = 0;
				}
				XArray_DeleteAll(pList->hArrayCurrItem);

				Ele_SendEvent(hList, XE_LIST_SELECT, -1, 0);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
	}

	pList->dragPt = *pPt;
	pList->down = TRUE;
}

BOOL List_MouseMoveDragEnd_View(HELE hEleView) //����϶�����
{
	list_  *pList = (list_*)((ele_*)hEleView)->pParentEle;
	HELE   hList = (HELE)pList;

	//HELE hEleView=((scrollView_*)hEle)->hView;

	if (pList->down)
		pList->down = FALSE;

	if (pList->bDrag)
	{
		pList->bDrag = FALSE;
		KillTimer(XEle_GetHWnd(hEleView), IDT_LIST_DRAG_RECT);
		XEle_ReleaseCapture(hEleView);
		XEle_RedrawEle(hEleView);

		if (pList->pCurrItem)
			Ele_SendEvent(hList, XE_LIST_SELECT, pList->pCurrItem->index, 0);
		else
			Ele_SendEvent(hList, XE_LIST_SELECT, -1, 0);
		return TRUE;
	}
	return FALSE;
}

/// @brief ȡ������ѡ����.
/// @param hEle Ԫ�ؾ��
void WINAPI XList_CancelSelectAll(HELE hEle) //ȡ��ѡ��������
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pList = LIST(hEle);
	if (pList->pCurrItem)
	{
		int count = Array_GetCount(pList->hArrayCurrItem);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				Array_GetAtList(pList->hArrayCurrItem, i)->state = 0;
			}
			XArray_DeleteAll(pList->hArrayCurrItem);
			pList->pCurrItem = NULL;
			Ele_SendEvent(hEle, XE_LIST_SELECT, -1, 0);
		}
	}
}
/// @brief ȡ��ѡ��ָ����.
/// @param hEle Ԫ�ؾ��
/// @param index ������.
void WINAPI XList_CancelSelect(HELE hEle, int index)
{
	IsListDebug(hEle, __FUNCTION__);

	int itemCount = Array_GetCount(LIST(hEle)->hArrayItem);
	if (index >= 0 && index < itemCount)
	{
		list_ *pList = LIST(hEle);
		if (pList->pCurrItem)
		{
			pList->pCurrItem = NULL;
			int count = Array_GetCount(pList->hArrayCurrItem);
			for (int i = 0; i < count; i++)
			{
				if (index == Array_GetAtList(pList->hArrayCurrItem, i)->index)
				{
					Array_GetAtList(pList->hArrayCurrItem, i)->state = 0;
					XArray_DeleteIndex(pList->hArrayCurrItem, i);
					break;
				}
			}
		}
	}
}

void List_MouseMoveDragUp(HELE hEle, int index1, int index2) //�����϶�
{
	list_ *pList = LIST(hEle);

	int countItem = Array_GetCount(pList->hArrayItem);
	if (index1 < 0)
		index1 = 0;

	if (index2 >= countItem)
		index2 = countItem - 1;

	if ((index2 - index1) < 0)  //û��ѡ���κ���
		return;

	if (NULL == pList->pCurrItem)  //û��ѡ����
	{
		for (int i = index1; i <= index2; i++)
		{
			listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
			pItem->state = STATE_SELECT;
			//pList->listCurrItem.Add(pItem);
			XArray_Add(pList->hArrayCurrItem, pItem);
		}
		pList->pCurrItem = Array_GetAtList(pList->hArrayItem, index1);
		//	OutputDebugString(m_pCurrItem->listSub.m_data[0]->text.GetBuffer());
		//	OutputDebugStringA("\n");
	}
	else
	{
		if (pList->pCurrItem->index > index1) //���ѡ����
		{
			for (int i = index1; i < pList->pCurrItem->index; i++)
			{
				listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
				pItem->state = STATE_SELECT;
				//pList->listCurrItem.Add(pItem);
				XArray_Add(pList->hArrayCurrItem, pItem);
			}
			pList->pCurrItem = Array_GetAtList(pList->hArrayItem, index1);
		}
		else if (pList->pCurrItem->index < index1) //�Ƴ�����Ҫ��ѡ����
		{
			for (int i = pList->pCurrItem->index; i < index1; i++)
			{
				listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
				pItem->state = 0;
				//pList->listCurrItem.Delete(pItem);
				XArray_Delete(pList->hArrayCurrItem, pItem);
			}
			pList->pCurrItem = Array_GetAtList(pList->hArrayItem, index1);
		}
	}
}

void List_MouseMoveDragDown(HELE hEle, int index1, int index2) //�����϶�
{
	list_ *pList = LIST(hEle);

	int countItem = Array_GetCount(pList->hArrayItem);
	if (index1 < 0)
		index1 = 0;

	if (index2 >= countItem)
		index2 = countItem - 1;

	if ((index2 - index1) < 0) //û��ѡ���κ���
		return;

	if (NULL == pList->pCurrItem)  //û��ѡ����
	{
		for (int i = index1; i <= index2; i++)
		{
			listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
			pItem->state = STATE_SELECT;
			//pList->listCurrItem.Add(pItem);
			XArray_Add(pList->hArrayCurrItem, pItem);
		}
		pList->pCurrItem = Array_GetAtList(pList->hArrayItem, index2);
	}
	else
	{
		if (pList->pCurrItem->index < index2) //���ѡ����
		{
			for (int i = pList->pCurrItem->index + 1; i <= index2; i++)
			{
				listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
				pItem->state = STATE_SELECT;
				//pList->listCurrItem.Add(pItem);
				XArray_Add(pList->hArrayCurrItem, pItem);
			}
			pList->pCurrItem = Array_GetAtList(pList->hArrayItem, index2);
		}
		else if (pList->pCurrItem->index > index2) //�Ƴ�����Ҫ��ѡ����
		{
			for (int i = index2 + 1; i <= pList->pCurrItem->index; i++)
			{
				listItem_ *pItem = Array_GetAtList(pList->hArrayItem, i);
				pItem->state = 0;
				//pList->listCurrItem.Delete(pItem);
				XArray_Delete(pList->hArrayCurrItem, pItem);
			}
			pList->pCurrItem = Array_GetAtList(pList->hArrayItem, index2);
		}
	}
}

void List_DrawList(HELE hEle, HDRAW hDraw)
{
	//TODO::�޸�
	list_ *pList = LIST(hEle);

	int countHeader = Array_GetCount(pList->hArrayHeader);
	if (countHeader < 1)
		return;

	int countItem = Array_GetCount(pList->hArrayItem);
	if (countItem < 1)
		return;

	int height = pList->headerHeight;

	int widths = Array_GetAtListHeader(pList->hArrayHeader, countHeader - 1)->rect.right; //�б�ͷ�����ܿ��

	RECT  rcDraw;
	XEle_GetClientRect(hEle, &rcDraw);
	rcDraw.top += pList->headerHeight;
	int pos = XSView_GetVViewPos(hEle);
	int posX = XSView_GetHViewPos(hEle);

	//��������ͼ�ڵ���
	int begin = (rcDraw.top - pos - pList->headerHeight) / pList->itemHeight; //��ʼ��
	int end = (rcDraw.bottom - pos - pList->headerHeight) / pList->itemHeight; //������

	end++;

	if (begin < 0)
		begin = 0;

	if (end > countItem)
		end = countItem;

	int viewWidth = XSView_GetViewWidth(hEle);//�ӿڿ��
	int viewHeight = XSView_GetViewHeight(hEle);//�ӿڿ��

	//�û��Ի�------------------------------------------------------
	if (pList->pDrawItem)
	{
		for (int j = begin; j < end; j++) //������
		{
			listItem_ *pItem = Array_GetAtList(pList->hArrayItem, j);
			pItem->index;
			for (int i = 0; i < countHeader; i++) //��������
			{
				listSubItem_ *pSubItem = Array_GetAtListSubItem(pItem->hArrayItem, i);
				list_drawItem_  drawItem;
				drawItem.hDraw = hDraw;
				drawItem.index = pItem->index;
				drawItem.subIndex = i;
				drawItem.imageId = pSubItem->imageId;
				drawItem.state = pItem->state;
				drawItem.rect = pSubItem->rect;
				drawItem.rcCheck = pItem->rcCheck;
				drawItem.pText = XStr_GetBuffer(pSubItem->hString);

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
				if (pList->pClass_Fun_Info_Item)
				{
					eventOrMsg_  event_;
					event_.hEle = hEle;
					event_.hEventEle = NULL;
					event_.wParam = (WPARAM)&drawItem;
					event_.lParam = NULL;
					event_.pClass_fun = pList->pClass_Fun_Info_Item;
					((pFunClassEventMsg)pList->pDrawItem)(&event_, xc_fun_v_e_list_item);
				}
				else
				{
					pList->pDrawItem(hEle, &drawItem);
				}
#else
				pList->pDrawItem(hEle, &drawItem);
#endif
			}
			XDraw_RestoreGDIOBJ_(hDraw);
		}
		return;
	}
	//ϵͳ����--------------------------------------------------
	RECT rcItem;
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(220, 220, 200));
	HPEN hPen;
	HGDIOBJ hOldPen;
	if (pList->bGrid) //��������
	{
		hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, RGB(220, 220, 220));
		hOldPen = XDraw_SelectObject_(hDraw, hPen);
		//��������
		XDraw_MoveToEx_(hDraw, pList->spacingLeft - 1, -pos, 0);
		XDraw_LineTo_(hDraw, pList->spacingLeft - 1, -pos + viewHeight);
		listItem_ *pItem = Array_GetAtList(pList->hArrayItem, 0);
		for (int i = 0; i < countHeader; i++) //��������
		{
			RECT rc = Array_GetAtListSubItem(pItem->hArrayItem, i)->rect;
			XDraw_MoveToEx_(hDraw, rc.right - 1, -pos, 0);
			XDraw_LineTo_(hDraw, rc.right - 1, -pos + viewHeight);
		}
	}

	for (int j = begin; j < end; j++) //������
	{
		listItem_ *pItem = Array_GetAtList(pList->hArrayItem, j);

		//��������
		if (pList->bGrid) //��������
		{
			RECT rcSub = Array_GetAtListSubItem(pItem->hArrayItem, 0)->rect;
			XDraw_MoveToEx_(hDraw, (-posX), rcSub.bottom - 1, 0);
			XDraw_LineTo_(hDraw, (-posX) + viewWidth, rcSub.bottom - 1);
		}
		//������
		if (pList->bLineHighlight &&  pList->pItemMouseStay == pItem)
		{
			RECT rcSub = Array_GetAtListSubItem(pItem->hArrayItem, 0)->rect;
			RECT rcSelect;
			rcSelect.left = rcSub.left;
			rcSelect.top = rcSub.top;
			rcSelect.bottom = rcSub.bottom;
			rcSelect.right = widths - 1;

			rcSelect.bottom -= 1;
			XDraw_GradientFill4_(hDraw, RGB(255, 255, 255), RGB(240, 240, 240), RGB(235, 235, 235), RGB(255, 255, 255), &rcSelect, 1);
			if (FALSE == pList->bGrid)
				XDraw_FrameRect_(hDraw, &rcSelect, hBrush);
		}

		if (STATE_SELECT == pItem->state) //ѡ����
		{
			RECT rcSub = Array_GetAtListSubItem(pItem->hArrayItem, 0)->rect;
			RECT rcSelect;
			rcSelect.left = rcSub.left;
			rcSelect.top = rcSub.top;
			rcSelect.bottom = rcSub.bottom;
			rcSelect.right = widths - 1;

			rcSelect.bottom -= 1;
			XDraw_GradientFill4_(hDraw, RGB(255, 255, 255), RGB(220, 220, 220), RGB(210, 210, 210), RGB(255, 255, 255), &rcSelect, 1);
			if (FALSE == pList->bGrid)
				XDraw_FrameRect_(hDraw, &rcSelect, hBrush);
		}

		int cx, cy;
		if (pList->hImageList)
		{
			cx = XImageList_GetWidth(pList->hImageList);
			cy = XImageList_GetHeight(pList->hImageList);
		}

		//���Ƶ�һ������
		if (countHeader > 0)
		{
			listSubItem_ *pSubItem = Array_GetAtListSubItem(pItem->hArrayItem, 0);
			rcItem = pSubItem->rect;
			rcItem.left += XLIST_ITEM_LEFT;

			if (pList->bCheck) //���Ƹ�ѡ��
			{
				int top = pItem->rcCheck.top + pList->itemHeight / 2 - 6 - 1;
				XDraw_Check_(hDraw, pItem->rcCheck.left, top, RGB(80, 80, 80), pItem->bCheck);

				rcItem.left = pItem->rcCheck.left + XLIST_CHECK_SIZE + XLIST_ITEM_LEFT;
			}

			if (NULL != pList->hImageList && (pSubItem->imageId > -1))
			{
				XImageList_DrawImage(pList->hImageList, hDraw, pSubItem->imageId, rcItem.left, rcItem.top + pList->itemHeight / 2 - cy / 2);
				rcItem.left += (cx + XLIST_ITEM_LEFT);
			}

			wchar_t *pText = XStr_GetBuffer(pSubItem->hString);
			if (pText)
				XDraw_DrawText_(hDraw, pText, XStr_GetLength(pSubItem->hString), &rcItem, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
		}

		//��������
		for (int i = 1; i < countHeader; i++)
		{
			listSubItem_ *pSubItem = Array_GetAtListSubItem(pItem->hArrayItem, i);
			rcItem = pSubItem->rect;
			rcItem.left += XLIST_ITEM_LEFT;

			if (NULL != pList->hImageList && (pSubItem->imageId > -1))
			{
				XImageList_DrawImage(pList->hImageList, hDraw, pSubItem->imageId, rcItem.left, rcItem.top + pList->itemHeight / 2 - cy / 2);
				rcItem.left += (cx + XLIST_ITEM_LEFT);
			}

			wchar_t *pText = XStr_GetBuffer(pSubItem->hString);
			if (pText)
				XDraw_DrawText_(hDraw, pText, XStr_GetLength(pSubItem->hString), &rcItem, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
		}
	}
}

void List_CancelSelectAll(HELE hEle) //ȡ��ѡ��������,�������¼�
{
	IsListDebug(hEle, __FUNCTION__);
	list_ *pList = LIST(hEle);
	if (pList->pCurrItem)
	{
		int count = Array_GetCount(pList->hArrayCurrItem);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				Array_GetAtList(pList->hArrayCurrItem, i)->state = 0;
			}
			XArray_DeleteAll(pList->hArrayCurrItem);
			pList->pCurrItem = NULL;
			//	Ele_SendEvent(hEle,XE_LIST_SELECT,-1,0);
		}
	}
}

BOOL CALLBACK List_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	list_ *pList = LIST(hEle);
	if (pPt->y <= pList->headerHeight && pList->bShowHeader)
	{
		List_LButtonDownHeader(hEle, pPt);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK List_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE  hList = (HELE)((ele_*)hEle)->pParentEle;
	//	list_ *pList=LIST(hList);
	//	if(pPt->y<=pList->headerHeight && pList->bShowHeader)
	//	{
	//		List_LButtonDownHeader_View(hEle,pPt);
	//		return TRUE;
	//	}else
	//	{
		//	if(XEle_IsHitChildEle(hEle,pPt))
		//		return FALSE;

	List_LButtonDown(hList, pPt);
	//	}
	return FALSE;
}

BOOL CALLBACK List_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	list_ *pList = LIST(hEle);
	if (pPt->y < pList->headerHeight || -1 != pList->downIndex)
	{
		if (pList->bShowHeader)
		{
			List_LButtonUpHeader(hEle, pPt);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK List_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt)
{
	HELE  hList = (HELE)((ele_*)hEle)->pParentEle;
	list_ *pList = LIST(hList);
	if (TRUE == List_MouseMoveDragEnd_View(hEle))
		return FALSE;
	/*
		if(pPt->y<pList->headerHeight || -1!=pList->downIndex)
		{
			if(pList->bShowHeader)
			{
				List_LButtonUpHeader(hList,pPt);
				return TRUE;
			}
		}*/
	return FALSE;
}

BOOL CALLBACK List_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	List_MouseMoveHeader(hEle, pPt);

	return FALSE;
}

BOOL CALLBACK List_OnEventKillCapture(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	List_MouseMoveDragHeaderEnd(hEle);
	return FALSE;
}

BOOL CALLBACK List_OnMouseMove_View(HELE hEleView, UINT flags, POINT *pPt)
{
	HELE hList = (HELE)((ele_*)hEleView)->pParentEle;

	if (TRUE == List_MouseMove_View(hEleView, pPt))
		return FALSE;

	////////////////////////////////////////////////
	if (LIST(hList)->bLineHighlight)
	{
		list_ *pList = LIST(hList);

		//	if((pList->headerHeight+XSView_GetSpacingTop(hList))<pPt->y)
		{
			int countHeader = Array_GetCount(pList->hArrayHeader);
			if (countHeader < 1)
				return FALSE;

			int countItem = Array_GetCount(pList->hArrayItem);
			if (countItem < 1)
				return FALSE;

			int posX = pPt->x - XSView_GetHViewPos(hList);
			int posY = pPt->y - XSView_GetVViewPos(hList);

			int right = Array_GetAtListHeader(pList->hArrayHeader, countHeader - 1)->rect.right;

			if (posX < pList->spacingLeft)
			{
			}
			else if (posX > (right - pList->spacingRight))
			{
			}
			else
			{
				int index = -1; //��ǰѡ����
			//	if(pList->bShowHeader)
			//		index=(posY-pList->headerHeight)/pList->itemHeight;
			//	else
				index = (posY) / pList->itemHeight;
				if (index > -1 && index < countItem)
				{
					if (NULL == pList->pItemMouseStay || pList->pItemMouseStay->index != index)
					{
						pList->pItemMouseStay = (listItem_*)XArray_GetAt(pList->hArrayItem, index);
						//XTRACE("index %d \n",index);
						XEle_RedrawEle(hList);
					}
					return FALSE;
				}
			}
		}
		if (pList->pItemMouseStay)
		{
			pList->pItemMouseStay = NULL;
			XEle_RedrawEle(hList);
		}
	}
	return FALSE;
}

BOOL CALLBACK List_OnEventMouseLeave_View(HELE hEleView, HELE hEventEle) //����뿪
{
	if (hEleView != hEventEle)
		return FALSE;

	HELE hList = (HELE)((ele_*)hEleView)->pParentEle;

	if (LIST(hList)->pItemMouseStay)
	{
		LIST(hList)->pItemMouseStay = NULL;
		XEle_RedrawEle(hList);
	}

	return FALSE;
}

BOOL CALLBACK List_OnEventMouseLeave(HELE hEle, HELE hEventEle) //����뿪
{
	if (hEle != hEventEle)
		return FALSE;

	if (LIST(hEle)->bShowHeader)
		List_MouseLeaveHeader(hEle);

	return FALSE;
}

BOOL CALLBACK List_OnEventKillCapture_View(HELE hEleView, HELE hEventEle)  //ʧȥ��겶��
{
	if (hEleView != hEventEle)
		return FALSE;

	List_MouseMoveDragEnd_View(hEleView);

	XTRACE("ʧȥ��겶��---------------------\n");
	return FALSE;
}

///@}

HELE  g_hList = NULL;
VOID CALLBACK List_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (IDT_LIST_DRAG_RECT == idEvent)
	{
		XEle_RedrawEle(g_hList);
	}
}