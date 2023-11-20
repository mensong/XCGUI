/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#include "StdAfx.h"

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��

void WINAPI XListView_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի���
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawItem = (pFunListView_DrawItem)pCallBackFun;
	((listView_*)hEle)->pClass_Fun_Info = pClass_Fun_Info;
}

void WINAPI XListView_SetUserDrawGroupEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի���
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawGroup = (pFunListView_DrawGroup)pCallBackFun;
	((listView_*)hEle)->pClass_Fun_Info_group = pClass_Fun_Info;
}

#endif

/// @defgroup listView �б���ͼ(ListView)
/// @ingroup groupElements
/// @{

/// @brief �����б���ͼԪ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����U IԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XListView_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	listView_ *pObj = (listView_*)malloc(sizeof(listView_));
	memset(pObj, 0, sizeof(listView_));

	ListView_Init((HELE)pObj, x, y, cx, cy, XC_LISTVIEW, hParent);
	return (HELE)pObj;
}

void ListView_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_LISTVIEW);
	listView_ *pListView = (listView_*)hEle;
	pListView->hArrayList = XArray_Create();
	pListView->hArrayGroupList = XArray_Create();
	pListView->hArrayCurrItem = XArray_Create();
	pListView->pCurrItem = NULL;
	pListView->bExpandButton = TRUE;
	pListView->bMultiSelect = TRUE;
	pListView->bDragItem = TRUE;
	pListView->hWndDrag = NULL;
	pListView->insertGroup = -1;
	pListView->insertItem = -1;

	pListView->iconSize.cx = 100;
	pListView->iconSize.cy = 100;
	pListView->left = 5;
	pListView->top = 5;
	pListView->right = 5;
	pListView->bottom = 5;
	pListView->columnSpace = 5;
	pListView->rowSpace = 5;
	pListView->iconTextSpace = 5;
	pListView->leftAlign = 5;
	pListView->topAlign = 5;
	pListView->groupHeight = 20;

	XSView_SetDrawScrollView(hEle, ListView_OnDrawScrollView);

	XEle_RegisterEvent(hEle, XE_DESTROY, ListView_OnDestroy);

	XEle_RegisterMessage(hEle, XM_PAINT, ListView_OnEleDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, ListView_OnEleLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, ListView_OnEleLButtonUp);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, ListView_OnEleMouseMove);

	XEle_RegisterEvent(hEle, XE_KILLFOCUS, ListView_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, ListView_OnEventMouseLeave);
}

/// @brief ������.
/// @param hEle Ԫ�ؾ��.
/// @param pName ����.
/// @param imageID ͼƬID.
/// @param groupIndex ������.
/// @return ������������ʧ�ܷ���-1.
int WINAPI XListView_AddItem(HELE hEle, wchar_t *pName, int imageID, int groupIndex) //������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	listView_item_ *pItem = (listView_item_*)malloc(sizeof(listView_item_));
	memset(pItem, 0, sizeof(listView_item_));
	pItem->imageID = imageID;
	pItem->hString = XStr_Create(pName);

	HDC hdc;
	hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	pItem->rcText.left = 0;
	pItem->rcText.top = 0;
	pItem->rcText.right = ((listView_*)hEle)->iconSize.cx;
	pItem->rcText.bottom = 100;

	DrawText(hdc, (LPCWSTR)pName, wcslen(pName), &pItem->rcText, DT_CALCRECT);

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	int index = -1;
	if (groupIndex >= 0)
	{
		int countGroup = XArray_GetCount(pListView->hArrayGroupList);
		if (groupIndex < countGroup)
		{
			listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
			index = XArray_Add(pGroup->hArrayList, pItem);
		}
		else
		{
			XStr_Destroy(pItem->hString);
			free(pItem);
			return -1;
		}
	}
	else
	{
		index = XArray_Add(((listView_*)hEle)->hArrayList, pItem);
	}
	((listView_*)hEle)->bAdjust = TRUE;

	return index;
}

/// @brief ������.
/// @param hEle Ԫ�ؾ��.
/// @param pName ����.
/// @param bExpand ���Ƿ�չ��.
/// @return ������������ʧ�ܷ���-1.
int  WINAPI XListView_AddGroup(HELE hEle, wchar_t *pName, BOOL bExpand) //������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = (listView_group_*)malloc(sizeof(listView_group_));
	memset(pGroup, 0, sizeof(listView_group_));
	pGroup->hArrayList = XArray_Create();
	pGroup->hString = XStr_Create(pName);
	pGroup->bExpand = bExpand;
	int index = XArray_Add(((listView_*)hEle)->hArrayGroupList, pGroup);
	return index;
}

/// @brief ������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������
/// @param itemIndex ������
/// @param pName ����.
/// @param imageID ͼƬID.
/// @return ������������ʧ�ܷ���-1.
int WINAPI XListView_InsertItem(HELE hEle, int groupIndex, int itemIndex, wchar_t *pName, int imageID)  //������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	listView_item_ *pItem = (listView_item_*)malloc(sizeof(listView_item_));
	memset(pItem, 0, sizeof(listView_item_));
	pItem->imageID = imageID;
	pItem->hString = XStr_Create(pName);

	HDC hdc;
	hdc = GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));
	pItem->rcText.left = 0;
	pItem->rcText.top = 0;
	pItem->rcText.right = ((listView_*)hEle)->iconSize.cx;
	pItem->rcText.bottom = 100;

	DrawText(hdc, (LPCWSTR)pName, wcslen(pName), &pItem->rcText, DT_CALCRECT);

	SelectObject(hdc, hOldFont);
	ReleaseDC(NULL, hdc);

	if (-1 == groupIndex) //û�з���
	{
		int count = XArray_GetCount(pListView->hArrayList);
		if (groupIndex >= 0 && groupIndex < count)
		{
			int index = XArray_insert(pListView->hArrayList, pItem, groupIndex);
			pListView->bAdjust = TRUE;
			return index;
		}
	}
	else //����
	{
		int countGroup = XArray_GetCount(pListView->hArrayGroupList);
		if (groupIndex >= 0 && groupIndex < countGroup)
		{
			listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
			int index = XArray_insert(pGroup->hArrayList, pItem, itemIndex);
			pListView->bAdjust = TRUE;
			return index;
		}
	}

	if (pItem->hString) XStr_Destroy(pItem->hString);
	free(pItem);

	return -1;
}

/// @brief ������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������
/// @param pName ����.
/// @param bExpand �Ƿ�չ����.
/// @return ������������ʧ�ܷ���-1.
int WINAPI XListView_InsertGroup(HELE hEle, int groupIndex, wchar_t *pName, BOOL bExpand)  //������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)malloc(sizeof(listView_group_));
		memset(pGroup, 0, sizeof(listView_group_));
		pGroup->hArrayList = XArray_Create();
		pGroup->hString = XStr_Create(pName);
		pGroup->bExpand = bExpand;
		pListView->bAdjust = TRUE;

		XArray_insert(pListView->hArrayGroupList, pGroup, groupIndex);
		return groupIndex;
	}
	return -1;
}

/// @brief ����ͼƬ�б�.
/// @param hEle Ԫ�ؾ��.
/// @param hImageList ͼƬ�б�
void WINAPI XListView_SetImageList(HELE hEle, HXCGUI hImageList)
{
	IsListViewDebug(hEle, __FUNCTION__);
	IsImageListDebug(hImageList, "��API:XListView_SetImageList()����[hImageList]������Ч");

	listView_  *pListView = ((listView_*)hEle);
	if (pListView->hImageList)
	{
		XImageList_Destroy(pListView->hImageList);
		pListView->hImageList = NULL;
	}
	if (hImageList)
	{
		IsImageListDebug(hImageList, __FUNCTION__);
		pListView->hImageList = ImageList_AddRef(hImageList);
	}
}

/// @brief ���û�ر�չ����ť.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable ����TRUE���ر�FALSE.
void WINAPI XListView_EnableExpandButton(HELE hEle, BOOL bEnable) //����/�ر�չ����ť
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->bExpandButton = bEnable;
	((listView_*)hEle)->bAdjust = TRUE;
}

/// @brief ȡ��ѡ��ָ����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex  ������.
void WINAPI XListView_CancelSelectItem(HELE hEle, int groupIndex, int itemIndex) //ȡ��ѡ��ָ����
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	if (pListView->bMultiSelect)
	{
		if (pListView->pCurrItem)
		{
			int count = Array_GetCount(pListView->hArrayCurrItem);
			if (count > 0)
			{
				listView_item_ *pItem = NULL;
				for (int i = 0; i < count; i++)
				{
					pItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i);
					if (groupIndex == pItem->groupIndex && itemIndex == pItem->index)
					{
						XArray_DeleteIndex(pListView->hArrayCurrItem, i);

						if (pItem == pListView->pCurrItem)
						{
							if (Array_GetCount(pListView->hArrayCurrItem) > 0)
								pListView->pCurrItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, 0);
							else
								pListView->pCurrItem = NULL;
						}
						if (STATE_SELECT == pItem->state)
							pItem->state = STATE_LEAVE;

						break;
					}
				}
			}
		}
	}
	else if (pListView->pCurrItem)
	{
		if (groupIndex == pListView->pCurrItem->groupIndex && itemIndex == pListView->pCurrItem->index)
		{
			if (STATE_SELECT == pListView->pCurrItem->state)
				pListView->pCurrItem->state = STATE_LEAVE;
			pListView->pCurrItem = NULL;
		}
	}
}

/// @brief ȡ��ѡ��������.
/// @param hEle Ԫ�ؾ��.
void WINAPI XListView_CancelSelectAll(HELE hEle) //ȡ��ѡ��������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	if (pListView->bMultiSelect)
	{
		if (pListView->pCurrItem)
		{
			int count = Array_GetCount(pListView->hArrayCurrItem);
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					((listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
				}
				XArray_DeleteAll(pListView->hArrayCurrItem);
				pListView->pCurrItem = NULL;
			}
		}
	}
	else if (pListView->pCurrItem)
	{
		if (STATE_SELECT == pListView->pCurrItem->state)
			pListView->pCurrItem->state = STATE_LEAVE;
		pListView->pCurrItem = NULL;
	}
}

/// @brief ��ȡѡ����.
/// @param hEle Ԫ�ؾ��.
/// @param pGroupIndex ����������.
/// @param pItemIndex ����������.
void WINAPI XListView_GetSelectItem(HELE hEle, out_ int *pGroupIndex, out_ int *pItemIndex)  //��ȡѡ����
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (((listView_*)hEle)->pCurrItem)
	{
		*pGroupIndex = ((listView_*)hEle)->pCurrItem->groupIndex;
		*pItemIndex = ((listView_*)hEle)->pCurrItem->index;
	}
	else
	{
		*pGroupIndex = -1;
		*pItemIndex = -1;
	}
}

/// @brief ��ȡѡ��������.
/// @param hEle Ԫ�ؾ��.
/// @return ѡ��������.
int  WINAPI XListView_GetSelectCount(HELE hEle)  //��ȡѡ��������
{
	IsListViewDebug(hEle, __FUNCTION__);

	if (((listView_*)hEle)->bMultiSelect)
	{
		return Array_GetCount(((listView_*)hEle)->hArrayCurrItem);
	}

	if (((listView_*)hEle)->pCurrItem)
		return 1;
	return 0;
}

/// @brief ��ȡ����ѡ����.
/// @param hEle Ԫ�ؾ��.
/// @param pArrayGroupIndex ��������������.
/// @param pArrayItemIndex ��������������.
/// @param arrayLength �����С.
/// @return ���ص���ʵ������.
int WINAPI XListView_GetSelectAllItem(HELE hEle, int *pArrayGroupIndex, int *pArrayItemIndex, int arrayLength) //��ȡ����ѡ����
{
	IsListViewDebug(hEle, __FUNCTION__);

	if (arrayLength < 1)
	{
		MessageBox(NULL, L"API:XListView_GetSelectAllItem(),����[arrayLength]����", L"�Ųʽ����-������ʾ", 0);
		exit(0);
	}

	listView_ *pListView = (listView_*)hEle;

	if (pListView->bMultiSelect)
	{
		int count = Array_GetCount(pListView->hArrayCurrItem);

		int counts = 0;
		if (arrayLength < count)
			counts = arrayLength;
		else
			counts = count;

		for (int i = 0; i < counts; i++)
		{
			listView_item_ *pItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i);
			pArrayGroupIndex[i] = pItem->groupIndex;
			pArrayItemIndex[i] = pItem->index;
		}

		return counts;
	}

	if (pListView->pCurrItem)
	{
		pArrayGroupIndex[0] = pListView->pCurrItem->groupIndex;
		pArrayItemIndex[0] = pListView->pCurrItem->index;
		return 1;
	}
	return 0;
}

/// @brief ��ȡ������.
/// @param hEle Ԫ�ؾ��.
/// @return ������.
int  WINAPI XListView_GetGroupCount(HELE hEle) //��ȡ������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	return XArray_GetCount(pListView->hArrayGroupList);
}

/// @brief ��ȡ���Ա����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������
/// @return ���Ա����.
int  WINAPI XListView_GetGroupMemberCount(HELE hEle, int groupIndex) //��ȡ���Ա����
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	if (-1 == groupIndex)
	{
		return XArray_GetCount(pListView->hArrayList);
	}

	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
		return XArray_GetCount(pGroup->hArrayList);
	return -1;
}

/// @brief ��ȡδ����������.
/// @param hEle Ԫ�ؾ��.
/// @return ��Ա����.
int  WINAPI XListView_GetUngroupMemberCount(HELE hEle)  //��ȡδ����������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	return XArray_GetCount(pListView->hArrayList);
}

/// @brief ��ȡͼƬ�б�.
/// @param hEle Ԫ�ؾ��.
/// @return ͼƬ�б���.
HXCGUI WINAPI XListView_GetImageList(HELE hEle) //��ȡͼƬ�б�
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	return pListView->hImageList;
}

/// @brief ��ȡ������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param pRect ��������.
/// @return �ɹ�����TRUE�������෴.
BOOL WINAPI XListView_GetItemRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect) //��ȡ������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		*pRect = pItem->rect;
		return TRUE;
	}
	return FALSE;
}

/// @brief ��ȡ��ͼ������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param pRect ��������.
/// @return �ɹ�����TRUE�������෴.
BOOL WINAPI XListView_GetItemIconRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect) //��ȡ��ͼ������
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		*pRect = pItem->rcIcon;
		return TRUE;
	}
	return FALSE;
}

/// @brief ��ȡ���ı�����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param pRect ��������.
/// @return �ɹ�����TRUE�������෴.
BOOL WINAPI XListView_GetItemTextRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect) //��ȡ���ı�����
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		*pRect = pItem->rcText;
		return TRUE;
	}
	return FALSE;
}

/// @brief ��ȡ���ı�.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @return �ı�����.
wchar_t* WINAPI XListView_GetItemText(HELE hEle, int groupIndex, int itemIndex) //��ȡ���ı�
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return XStr_GetBuffer(pItem->hString);
	}
	return NULL;
}

/// @brief ��ȡ��ͼ��ID.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @return ��ͼ��ID,ʧ�ܷ���-1.
int WINAPI XListView_GetItemIcon(HELE hEle, int groupIndex, int itemIndex) //��ȡ��ͼ��ID
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return pItem->imageID;
	}
	return -1;
}

/// @brief ��ȡ���ı�.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @return �ı�����.
wchar_t* WINAPI XListView_GetGroupText(HELE hEle, int groupIndex)  //��ȡ���ı�
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		return XStr_GetBuffer(pGroup->hString);
	}
	return NULL;
}

/// @brief ��ȡ������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param pRect  ����������.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_GetGroupRect(HELE hEle, int groupIndex, out_ RECT *pRect)  //��ȡ������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		*pRect = pGroup->rect;
		return TRUE;
	}
	return NULL;
}

/// @brief �����������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param data ������.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetItemData(HELE hEle, int groupIndex, int itemIndex, void* data) //�����������
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		pItem->userData = data;
		return TRUE;
	}
	return FALSE;
}

/// @brief ��ȡ�������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @return ������ݣ�ʧ�ܷ���-1.
void* WINAPI XListView_GetItemData(HELE hEle, int groupIndex, int itemIndex) //��ȡ�������
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return pItem->userData;
	}
	return NULL;
}

/// @brief �����������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param data ������.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetGroupData(HELE hEle, int groupIndex, void* data) //�����������
{
	IsListViewDebug(hEle, __FUNCTION__);
	//listView_ *pListView=(listView_*)hEle;
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		pGroup->userData = data;
		return TRUE;
	}
	return FALSE;
}

/// @brief ����ѡ����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param bSelect ѡ��TRUE.δѡ��FALSE.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetSelectItem(HELE hEle, int groupIndex, int itemIndex, BOOL bSelect) //����ѡ����
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		if (bSelect)
		{
			if (STATE_SELECT != pItem->state)
			{
				if (pListView->bMultiSelect)
				{
					XArray_Add(pListView->hArrayCurrItem, pItem);
				}
				else
				{
					if (pListView->pCurrItem)
						pListView->pCurrItem->state = STATE_LEAVE;
				}
				pItem->state = STATE_SELECT;
				pListView->pCurrItem = pItem;
			}
		}
		else
		{
			if (STATE_SELECT == pItem->state)
			{
				if (pListView->bMultiSelect)
				{
					pItem->state = STATE_LEAVE;
					XArray_Delete(pListView->hArrayCurrItem, pItem);
					if (pItem == pListView->pCurrItem)
					{
						pListView->pCurrItem = NULL;
						if (XArray_GetCount(pListView->hArrayCurrItem) > 0)
							pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
					}
				}
				else
				{
					if (pItem == pListView->pCurrItem)
					{
						pListView->pCurrItem->state = STATE_LEAVE;
						pListView->pCurrItem = NULL;
					}
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

/// @brief �������ı�.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param pText �ı�����.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetItemText(HELE hEle, int groupIndex, int itemIndex, wchar_t *pText) //�������ı�
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem && pText)
	{
		XStr_SetString(pItem->hString, pText);
		return TRUE;
	}
	return FALSE;
}

/// @brief �������ı�.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������..
/// @param pText �ı�����.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetGroupText(HELE hEle, int groupIndex, wchar_t *pText) //�������ı�
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup && pText)
	{
		XStr_SetString(pGroup->hString, pText);
		return TRUE;
	}
	return FALSE;
}

/// @brief ������ͼ��ID.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @param imageID ͼ��ID.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetItemIcon(HELE hEle, int groupIndex, int itemIndex, int imageID) //������ͼ��ID
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		pItem->imageID = imageID;
		return TRUE;
	}
	return FALSE;
}

/// @brief ����ͼ�������С,������ͼ��Ĵ�С.
/// @param hEle Ԫ�ؾ��.
/// @param cx ���.
/// @param cy �߶�.
void WINAPI XListView_SetIconSize(HELE hEle, int cx, int cy)
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->iconSize.cx = cx;
	((listView_*)hEle)->iconSize.cy = cy;
}

/// @brief ������߼��
/// @param hEle   Ԫ�ؾ��.
/// @param left   ��߼��.
/// @param top    �ϱ߼��.
/// @param right  �ұ߼��.
/// @param bottom �±߼��.
void WINAPI XListView_SetItemBorderSpacing(HELE hEle, int left, int top, int right, int bottom) //������߼��
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->left = left;
	((listView_*)hEle)->top = top;
	((listView_*)hEle)->right = right;
	((listView_*)hEle)->bottom = bottom;
}

/// @brief �������м��
/// @param hEle   Ԫ�ؾ��.
/// @param width  �м��.
void WINAPI XListView_SetColumnSpacing(HELE hEle, int width) //�������м��
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->columnSpace = width;
}

/// @brief �������м��
/// @param hEle   Ԫ�ؾ��.
/// @param height  �м��.
void WINAPI XListView_SetRowSpacing(HELE hEle, int height)  //�������м��
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->rowSpace = height;
}

/// @brief ����ͼ�����ı����
/// @param hEle   Ԫ�ؾ��.
/// @param height  �����С.
void WINAPI XListView_SetItemIconTextSpacing(HELE hEle, int height) //����ͼ�����ı����
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->iconTextSpace = height;
}

/// @brief ������ͼ�������
/// @param hEle   Ԫ�ؾ��.
/// @param size  �����С.
void WINAPI XListView_SetViewLeftAlign(HELE hEle, int size)  //������ͼ�����
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->leftAlign = size;
}

/// @brief ������ͼ�϶�����
/// @param hEle   Ԫ�ؾ��.
/// @param size  �����С.
void WINAPI XListView_SetViewTopAlign(HELE hEle, int size) //������ͼ�϶���
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->topAlign = size;
}

/// @brief ������߶�
/// @param hEle   Ԫ�ؾ��.
/// @param height  ��߶�.
void WINAPI XListView_SetGroupHeight(HELE hEle, int height) //������߶�
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->groupHeight = height;
}

/// @brief ��ȡͼ�������С,������ͼ��Ĵ�С.
/// @param hEle   Ԫ�ؾ��.
/// @param pSize  ����ͼ�������С.
void WINAPI XListView_GetIconSize(HELE hEle, out_ SIZE *pSize) //��ȡͼ�������С,������ͼ��Ĵ�С.
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (pSize)
		*pSize = ((listView_*)hEle)->iconSize;
}

/// @brief ��ȡ����߼��.
/// @param hEle   Ԫ�ؾ��.
/// @return ������߼����С.
int  WINAPI XListView_GetItemBorderLeft(HELE hEle) //��ȡ��߼��
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->left;
}

/// @brief ��ȡ���ϱ߼��.
/// @param hEle   Ԫ�ؾ��.
/// @return �����ϱ߼����С.
int  WINAPI XListView_GetItemBorderTop(HELE hEle)
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->top;
}

/// @brief ��ȡ���ұ߼��.
/// @param hEle   Ԫ�ؾ��.
/// @return �����ұ߼����С.
int  WINAPI XListView_GetItemBorderRight(HELE hEle)
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->right;
}

/// @brief ��ȡ���±߼��.
/// @param hEle   Ԫ�ؾ��.
/// @return �����±߼����С.
int  WINAPI XListView_GetItemBorderBottom(HELE hEle)
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->bottom;
}

/// @brief ��ȡ���м��.
/// @param hEle   Ԫ�ؾ��.
/// @return �������м����С.
int  WINAPI XListView_GetColumnSpacing(HELE hEle) //��ȡ���м��
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->columnSpace;
}

/// @brief ��ȡ���м��.
/// @param hEle   Ԫ�ؾ��.
/// @return �������м����С.
int  WINAPI XListView_GetRowSpacing(HELE hEle)  //��ȡ���м��
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->rowSpace;
}

/// @brief ��ȡͼ�����ı����.
/// @param hEle   Ԫ�ؾ��.
/// @return ����ͼ�����ı������С.
int  WINAPI XListView_GetItemIconTextSpacing(HELE hEle)  //��ȡͼ�����ı����
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->iconTextSpace;
}

/// @brief ��ȡ��ͼ�������.
/// @param hEle   Ԫ�ؾ��.
/// @return ������ͼ���������С.
int  WINAPI XListView_GetViewLeftAlign(HELE hEle)  //��ȡ��ͼ�����
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->leftAlign;
}

/// @brief ��ȡ��ͼ�϶�����.
/// @param hEle   Ԫ�ؾ��.
/// @return ������ͼ�϶�������С.
int  WINAPI XListView_GetViewTopAlign(HELE hEle) //��ȡ��ͼ�϶���
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->topAlign;
}

/// @brief ��ȡ��߶�.
/// @param hEle   Ԫ�ؾ��.
/// @return ������߶�.
int  WINAPI XListView_GetGroupHeight(HELE hEle) //��ȡ��߶�
{
	IsListViewDebug(hEle, __FUNCTION__);
	return ((listView_*)hEle)->groupHeight;
}

/// @brief ��ȡ�������.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @return �������,ʧ�ܷ���-1.
void* WINAPI XListView_GetGroupData(HELE hEle, int groupIndex) //��ȡ�������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		return pGroup->userData;
	}
	return NULL;
}

/// @brief ɾ����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex  ������.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_DeleteItem(HELE hEle, int groupIndex, int itemIndex) //ɾ����
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
		int count = XArray_GetCount(pGroup->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, itemIndex);
			XArray_DeleteIndex(pGroup->hArrayList, itemIndex);
			ListView_DeleteItem_XC(hEle, pItem); //���ѡ�����Ƿ�ı�,�����ͷ���
			pListView->bAdjust = TRUE;
			return TRUE;
		}
	}
	else if (-1 == groupIndex)
	{
		int count = XArray_GetCount(pListView->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, itemIndex);
			XArray_DeleteIndex(pListView->hArrayList, itemIndex);
			ListView_DeleteItem_XC(hEle, pItem); //���ѡ�����Ƿ�ı�,�����ͷ���
			pListView->bAdjust = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}

/// @brief ɾ����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_DeleteGroup(HELE hEle, int groupIndex) //ɾ����
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex <= countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
		XArray_DeleteIndex(pListView->hArrayGroupList, groupIndex);
		ListView_DeleteGroup_XC(hEle, pGroup);//���ѡ�����Ƿ�ı�,�����ͷ��鼰����
		pListView->bAdjust = TRUE;
		return TRUE;
	}
	return FALSE;
}

/// @brief ɾ��������.
/// @param hEle Ԫ�ؾ��.
void WINAPI XListView_DeleteAllGroups(HELE hEle) //ɾ��������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = 0; i < countGroup; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		ListView_DeleteGroup_XC(hEle, pGroup);
	}
	XArray_DeleteAll(pListView->hArrayGroupList);
}

/// @brief ɾ������,����б���ͼ.
/// @param hEle Ԫ�ؾ��.
void WINAPI XListView_DeleteAll(HELE hEle) //ɾ������,�������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	XListView_DeleteAllGroups(hEle);

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		ListView_DeleteItem_XC(hEle, pItem);
	}
	XArray_DeleteAll(pListView->hArrayList);
}

/// @brief �ж����Ƿ�ѡ��.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex ������.
/// @return ѡ��1,δѡ��0,ʧ��-1.
int WINAPI XListView_IsItemSelect(HELE hEle, int groupIndex, int itemIndex)  //�ж����Ƿ�ѡ��
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	listView_item_ *pItem = ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		return STATE_SELECT == pItem->state ? 1 : 0;
	}
	return -1;
}

/// @brief ���������,��,��.
/// @param hEle Ԫ�ؾ��.
/// @param pPt �����.
/// @param pGroupIndex ����������.
/// @param pItemIndex ����������.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_HitTest(HELE hEle, POINT *pPt, out_ int *pGroupIndex, out_ int *pItemIndex) //���������,��,��
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;

	POINT  pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);

	//��
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		if (PtInRect(&pGroup->rcButton, pt)) //�鰡չ������
		{
			*pGroupIndex = g;
			*pItemIndex = -1;
			return TRUE;
		}
		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (PtInRect(&pItem->rect, pt)) //ѡ����
				{
					*pGroupIndex = g;
					*pItemIndex = i;
					return TRUE;
				}
			}
		}
	}

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (PtInRect(&pItem->rect, pt))
		{
			*pGroupIndex = -1;
			*pItemIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

/// @brief �ж����Ƿ�չ��.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @return չ��1,δչ��0,ʧ��-1.
int WINAPI XListView_IsGroupExpand(HELE hEle, int groupIndex) //�ж����Ƿ�չ��
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		return pGroup->bExpand ? 1 : 0;
	}
	return -1;
}

/// @brief չ��ָ����.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param bExpand չ��TRUE,��չ��FALSE.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XListView_SetGroupExpand(HELE hEle, int groupIndex, BOOL bExpand) //չ��ָ����
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_group_ *pGroup = ListView_GetGroup_XC(hEle, groupIndex);
	if (pGroup)
	{
		pGroup->bExpand = bExpand;
		return TRUE;
	}
	return FALSE;
}

void ListView_DeleteItem_XC(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	BOOL  bSelItemChange = FALSE; //ѡ����ı�

	int countSelItem = XArray_GetCount(pListView->hArrayCurrItem);
	for (int i = 0; i < countSelItem; i++)
	{
		if (pItem == ((listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, i)))
		{
			XArray_DeleteIndex(pListView->hArrayCurrItem, i);
			bSelItemChange = TRUE;
			break;
		}
	}

	if (pItem == pListView->pCurrItem)
	{
		bSelItemChange = TRUE;
		pListView->pCurrItem = NULL;

		int count = XArray_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
			pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
	}

	if (pItem->hString) XStr_Destroy(pItem->hString);
	if (pItem->hImage_select) XImage_Destroy(pItem->hImage_select);
	if (pItem->hImage_stay) XImage_Destroy(pItem->hImage_stay);
	free(pItem);

	if (bSelItemChange)
	{
		//		if(pListView->pCurrItem)
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,pListView->pCurrItem->id,0);
		//		else
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,-1,0);
	}
}

void ListView_DeleteGroup_XC(HELE hEle, listView_group_ *pGroup)
{
	listView_ *pListView = (listView_*)hEle;

	BOOL  bSelItemChange = FALSE; //ѡ����ı�

	int count = XArray_GetCount(pGroup->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
		int countSelItem = XArray_GetCount(pListView->hArrayCurrItem);
		for (int s = 0; s < countSelItem; s++)
		{
			listView_item_ *pSelItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, s);
			if (pSelItem == pItem)
			{
				XArray_DeleteIndex(pListView->hArrayCurrItem, s);
				bSelItemChange = TRUE;
				break;
			}
		}
		if (pListView->pCurrItem == pItem)
		{
			bSelItemChange = TRUE;
			pListView->pCurrItem = NULL;

			int count = XArray_GetCount(pListView->hArrayCurrItem);
			if (count > 0)
				pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
		}

		if (pItem->hString) XStr_Destroy(pItem->hString);
		free(pItem);
	}
	XArray_Destroy(pGroup->hArrayList);
	if (pGroup->hString) XStr_Destroy(pGroup->hString);
	free(pGroup);

	if (bSelItemChange)
	{
		//		if(pListView->pCurrItem)
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,pListView->pCurrItem->id,0);
		//		else
		//			Ele_SendEvent(hEle,XE_LISTVIEW_SELECT,-1,0);
	}
}

listView_item_  *ListView_GetItem_XC(HELE hEle, int groupIndex, int itemIndex) //��ȡ��
{
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
		int count = XArray_GetCount(pGroup->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			return (listView_item_*)XArray_GetAt(pGroup->hArrayList, itemIndex);
		}
	}
	else if (-1 == groupIndex)
	{
		int count = XArray_GetCount(pListView->hArrayList);
		if (itemIndex >= 0 && itemIndex < count)
		{
			return (listView_item_*)XArray_GetAt(pListView->hArrayList, itemIndex);
		}
	}
	return NULL;
}

listView_group_  *ListView_GetGroup_XC(HELE hEle, int groupIndex) //��ȡ��
{
	listView_ *pListView = (listView_*)hEle;
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	if (groupIndex >= 0 && groupIndex < countGroup)
	{
		return (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, groupIndex);
	}
	return NULL;
}

/// @brief ���û�رն���ѡ��.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable ����TRUE,�ر�FALSE.
void WINAPI XListView_EnableMultiSelect(HELE hEle, BOOL bEnable) //���ùرն���ѡ��
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	if (bEnable)
	{
		if (bEnable != pListView->bMultiSelect)
		{
			pListView->bMultiSelect = bEnable;
			int count = XArray_GetCount(pListView->hArrayCurrItem);
			if (count < 1)
				XArray_Add(pListView->hArrayCurrItem, pListView->pCurrItem);
		}
	}
	else if (bEnable != pListView->bMultiSelect)
	{
		pListView->bMultiSelect = bEnable;
		int count = XArray_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				((listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
			}
			XArray_DeleteAll(pListView->hArrayCurrItem);
			pListView->pCurrItem->state = STATE_SELECT;
		}
	}
}

/// @brief �����û��Ի���.
/// @param hEle Ԫ�ؾ��.
/// @param pFunDrawItem �Ի溯����,��ʽ����:
/// @code void CALLBACK ListView_DrawItem(HELE hEle,listView_drawItem_ *pDrawItem); @endcode
void WINAPI XListView_SetUserDrawItem(HELE hEle, pFunListView_DrawItem pFunDrawItem) //�����û��Ի���
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	((listView_*)hEle)->pClass_Fun_Info = NULL;
#endif
}

/// @brief �����û��Ի���.
/// @param hEle Ԫ�ؾ��.
/// @param pFunDrawGroup �Ի溯����,��ʽ����:
/// @code void CALLBACK ListView_DrawGroup(HELE hEle,listView_drawGroup_ *pDrawGroup); @endcode
void WINAPI XListView_SetUserDrawGroup(HELE hEle, pFunListView_DrawGroup pFunDrawGroup) //�����û��Ի���
{
	IsListViewDebug(hEle, __FUNCTION__);
	((listView_*)hEle)->pDrawGroup = pFunDrawGroup;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	((listView_*)hEle)->pClass_Fun_Info_group = NULL;
#endif
}

/// @brief ������ѡ��״̬��ͼ.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex  ������.
/// @param hImage    ͼƬ���.
void WINAPI XListView_SetItemImageSelect(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage)
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	listView_item_ *pItem = (listView_item_*)ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		Image_AddImage(pItem->hImage_select, hImage);
	}
}

/// @brief ���������ͣ��״̬��ͼ.
/// @param hEle Ԫ�ؾ��.
/// @param groupIndex ������.
/// @param itemIndex  ������.
/// @param hImage   ͼƬ���.
void WINAPI XListView_SetItemImageStay(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage)
{
	IsListViewDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}

	listView_item_ *pItem = (listView_item_*)ListView_GetItem_XC(hEle, groupIndex, itemIndex);
	if (pItem)
	{
		Image_AddImage(pItem->hImage_stay, hImage);
	}
}

//������ͼ��С
void ListView_CalculateView(HELE hEle)
{
	listView_ *pListView = (listView_*)hEle;

	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	int right = rect.right - XSView_GetSpacingRight(hEle);
	right = right - XSView_GetScrollBarWidth(hEle);

	int t1 = XSView_GetSpacingLeft(hEle);
	int t2 = XSView_GetSpacingTop(hEle);

	//���������
	int leftSpace = t1 + pListView->leftAlign; //�߿�����
	int topSpace = t2 + pListView->topAlign;  //�߿��ϼ��

	int x = leftSpace; //X����
	int y = topSpace;  //Y����
	int y2 = topSpace; //����ÿ������bottomֵ

	int count = XArray_GetCount(pListView->hArrayList);
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	int itemCX = pListView->iconSize.cx + pListView->left + pListView->right; //����

	//������ͼ//////////////////////////////////////////////////
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		y += pListView->groupHeight;
		int countItem = XArray_GetCount(pGroup->hArrayList);
		if (pGroup->bExpand)
		{
			if (countItem < 1)
			{
				y += pListView->groupHeight; //���и߶�
			}
			else
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);

					x = x + itemCX + pListView->columnSpace;
					int bottpm = y + pListView->top + pListView->bottom + pListView->iconSize.cy + pListView->iconTextSpace + (pItem->rcText.bottom - pItem->rcText.top);

					if (bottpm > y2)
					{
						y2 = bottpm;
					}

					if ((x + itemCX + pListView->columnSpace) > right) //����
					{
						x = leftSpace;
						y = y2 + pListView->rowSpace; //�м��
					}
				}
				y = y2 + pListView->rowSpace; //�м��
				x = leftSpace;
			}
		}
	}
	y2 = y;
	//����δ������
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);

		x = x + itemCX + pListView->columnSpace;

		int bottom = y + pListView->top + pListView->bottom + pListView->iconSize.cy + pListView->iconTextSpace + (pItem->rcText.bottom - pItem->rcText.top);

		if (bottom > y2)
		{
			y2 = bottom;
		}

		if ((x + itemCX + pListView->columnSpace) > right) //����
		{
			x = leftSpace;
			y = y2 + pListView->rowSpace; //�м��
		}
	}
	y = y2 + pListView->rowSpace; //�м��
	XSView_SetSize(hEle, 10, y);
	XTRACE("y2= %d \n", y2);
}

/// @brief ��������.
/// @param hEle Ԫ�ؾ��.
void WINAPI XListView_Adjust(HELE hEle) //��������
{
	IsListViewDebug(hEle, __FUNCTION__);
	listView_ *pListView = (listView_*)hEle;
	pListView->bAdjust = FALSE;

	ListView_CalculateView(hEle); //������ͼ��С

	int count = XArray_GetCount(pListView->hArrayList);
	int viewWidth = XSView_GetViewWidth(hEle);

	int t1 = XSView_GetSpacingLeft(hEle);
	int t2 = XSView_GetSpacingTop(hEle);

	//���������
	int leftSpace = t1 + pListView->leftAlign; //�߿�����
	int topSpace = t2 + pListView->topAlign;  //�߿��ϼ��

	int x = leftSpace; //X����
	int y = topSpace;  //Y����
	int y2 = topSpace; //����ÿ������bottomֵ

	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	int itemCX = pListView->iconSize.cx + pListView->left + pListView->right; //����
	//��������//////////////////////////////////////////////////////
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		pGroup->index = g;

		pGroup->rect.left = x;
		pGroup->rect.top = y;
		pGroup->rect.right = viewWidth;
		pGroup->rect.bottom = y + pListView->groupHeight - 1;

		if (pListView->bExpandButton) //չ����ť
		{
			pGroup->rcButton.left = x + 3;
			pGroup->rcButton.top = y + (pListView->groupHeight - 12) / 2;
			pGroup->rcButton.right = pGroup->rcButton.left + 12;
			pGroup->rcButton.bottom = pGroup->rcButton.top + 12;

			//���ı�����
			pGroup->rcText.left = pGroup->rcButton.left + 15;
			pGroup->rcText.top = y;
			pGroup->rcText.right = viewWidth;
			pGroup->rcText.bottom = (y += pListView->groupHeight);
		}
		else
		{
			//���ı�����
			pGroup->rcText.left = x + 3;
			pGroup->rcText.top = y;
			pGroup->rcText.right = viewWidth;
			pGroup->rcText.bottom = (y += pListView->groupHeight);
		}

		int countItem = XArray_GetCount(pGroup->hArrayList);
		if (pGroup->bExpand)
		{
			if (countItem < 1)
			{
				y += pListView->groupHeight; //���и߶�
			}
			else
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
					pItem->index = i;
					pItem->groupIndex = g;

					ListView_AdjustItem(hEle, pItem, x, y);

					if (pItem->rect.bottom > y2)
					{
						y2 = pItem->rect.bottom;
					}
					x = pItem->rect.right + pListView->columnSpace;

					if ((x + itemCX + pListView->columnSpace) > viewWidth)
					{
						x = leftSpace;
						y = y2 + pListView->rowSpace; //�м��
					}
				}
				y = y2 + pListView->rowSpace; //�м��
				x = leftSpace;
			}
		}
		else
		{
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				pItem->index = i;
				pItem->groupIndex = g;
			}
		}
	}

	//����δ������
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		pItem->index = i;
		pItem->groupIndex = -1;

		ListView_AdjustItem(hEle, pItem, x, y);

		if (pItem->rect.bottom > y2)
		{
			y2 = pItem->rect.bottom;
		}
		x = pItem->rect.right + pListView->columnSpace;

		if ((x + itemCX + pListView->columnSpace) > viewWidth)
		{
			x = leftSpace;
			y = y2 + pListView->rowSpace; //�м��
		}
	}
	XTRACE("x2= %d \n", y2);
}

void ListView_AdjustItem(HELE hEle, listView_item_ *pItem, int x, int y)  //������
{
	listView_ *pListView = (listView_*)hEle;

	pItem->rcIcon.left = x + pListView->left;
	pItem->rcIcon.top = y + pListView->top;
	pItem->rcIcon.right = pItem->rcIcon.left + pListView->iconSize.cx;
	pItem->rcIcon.bottom = pItem->rcIcon.top + pListView->iconSize.cy;

	//����ͼ���������
	if (pListView->hImageList)
	{
		int imageWidth = 0;
		int imageHeight = 0;
		if (XImageList_IsFixedSize(pListView->hImageList))
		{
			imageWidth = XImageList_GetWidth(pListView->hImageList);
			imageHeight = XImageList_GetHeight(pListView->hImageList);
		}
		else
		{
			HIMAGE hImage = XImageList_GetImage(pListView->hImageList, pItem->imageID);
			if (hImage)
			{
				imageWidth = XImage_GetWidth(hImage);
				imageHeight = XImage_GetHeight(hImage);
			}
		}

		int width = pListView->iconSize.cx;
		int height = pListView->iconSize.cy;
		if (imageWidth > width || imageHeight > height)
		{
			if (imageWidth > imageHeight)
			{
				int imageHeight2 = 0;
				if (0 != imageWidth && 0 != width)
				{
					double  t = ((double)width) / imageWidth;
					if (FALSE == IsFlaotZero(t))
						imageHeight2 = (int)(imageHeight*t);
				}

				pItem->rcIconDraw.top = pItem->rcIcon.bottom - imageHeight2;
				pItem->rcIconDraw.bottom = pItem->rcIcon.bottom;

				pItem->rcIconDraw.left = x + pListView->left;
				pItem->rcIconDraw.right = pItem->rcIconDraw.left + width;
			}
			else
			{
				int imageWidth2 = 0;
				if (0 != imageHeight && 0 != height)
				{
					double  t = ((double)height) / imageHeight;
					if (FALSE == IsFlaotZero(t))
						imageWidth2 = (int)(imageWidth*t);
				}

				pItem->rcIconDraw.left = x + pListView->left + (width - imageWidth2) / 2;
				pItem->rcIconDraw.right = pItem->rcIconDraw.left + imageWidth2;
				pItem->rcIconDraw.top = pItem->rcIcon.bottom - height;
				pItem->rcIconDraw.bottom = pItem->rcIcon.bottom;
			}
		}
		else
		{
			pItem->rcIconDraw.left = x + pListView->left + (width - imageWidth) / 2;
			pItem->rcIconDraw.right = pItem->rcIconDraw.left + imageWidth;
			pItem->rcIconDraw.top = pItem->rcIcon.bottom - imageHeight;
			pItem->rcIconDraw.bottom = pItem->rcIcon.bottom;
		}
	}

	int textHeight = pItem->rcText.bottom - pItem->rcText.top;

	pItem->rcText.left = x;
	pItem->rcText.right = pItem->rcIcon.right + pListView->right;
	pItem->rcText.top = pItem->rcIcon.bottom + pListView->iconTextSpace;
	pItem->rcText.bottom = pItem->rcText.top + textHeight;

	pItem->rect.left = x;
	pItem->rect.top = y;
	pItem->rect.right = pItem->rcIcon.right + pListView->right;
	pItem->rect.bottom = pItem->rcText.bottom + pListView->bottom;
}

void CALLBACK ListView_OnDestroy(HELE hEle) //����
{
	//ɾ��������
	listView_ *pListView = (listView_*)hEle;

	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		int countItem = XArray_GetCount(pGroup->hArrayList);
		for (int i = 0; i < countItem; i++)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
			if (pItem->hString) XStr_Destroy(pItem->hString);
			if (pItem->hImage_select) XImage_Destroy(pItem->hImage_select);
			if (pItem->hImage_stay) XImage_Destroy(pItem->hImage_stay);
			free(pItem);
		}
		XArray_Destroy(pGroup->hArrayList);
		if (pGroup->hString) XStr_Destroy(pGroup->hString);
		free(pGroup);
	}

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (pItem->hString) XStr_Destroy(pItem->hString);
		if (pItem->hImage_select) XImage_Destroy(pItem->hImage_select);
		if (pItem->hImage_stay) XImage_Destroy(pItem->hImage_stay);
		free(pItem);
	}

	XArray_Destroy(pListView->hArrayList);
	XArray_Destroy(pListView->hArrayGroupList);
	if (pListView->hArrayCurrItem) XArray_Destroy(pListView->hArrayCurrItem);
	if (pListView->hImageList) XImageList_Destroy(pListView->hImageList);

#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	if (pListView->pClass_Fun_Info)
		free(pListView->pClass_Fun_Info);
	if (pListView->pClass_Fun_Info_group)
		free(pListView->pClass_Fun_Info_group);
#endif
}

BOOL CALLBACK ListView_OnEleDraw(HELE hEle, HDRAW hDraw)
{
	if (((listView_*)hEle)->bAdjust)
		XListView_Adjust(hEle);
	return FALSE;
}

BOOL CALLBACK ListView_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	listView_ *pListView = (listView_*)hEle;

	//������
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);

		listView_drawGroup_ group;
		group.bExpand = pGroup->bExpand;
		group.hDraw = hDraw;
		group.rcButton = pGroup->rcButton;
		group.rcText = pGroup->rcText;
		group.pText = XStr_GetBuffer(pGroup->hString);
		group.userData = pGroup->userData;
		group.rect = pGroup->rect;
		ListView_DrawGroup(hEle, &group);

		XDraw_RestoreGDIOBJ_(hDraw);

		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++) //������
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				listView_drawItem_  item;
				item.hDraw = hDraw;
				item.groupIndex = g;
				item.itemIndex = i;
				item.imageID = pItem->imageID;
				item.pText = XStr_GetBuffer(pItem->hString);
				item.rcIcon = pItem->rcIcon;
				item.rcIconDraw = pItem->rcIconDraw;
				item.rcText = pItem->rcText;
				item.rect = pItem->rect;
				item.userData = pItem->userData;
				item.state = pItem->state;
				item.hImage_select = pItem->hImage_select;
				item.hImage_stay = pItem->hImage_stay;

				ListView_DrawItem(hEle, &item);

				XDraw_RestoreGDIOBJ_(hDraw);
			}
		}
	}

	//����δ������
	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);

		listView_drawItem_  item;
		item.hDraw = hDraw;
		item.groupIndex = -1;
		item.itemIndex = i;
		item.imageID = pItem->imageID;
		item.pText = XStr_GetBuffer(pItem->hString);
		item.rcIcon = pItem->rcIcon;
		item.rcIconDraw = pItem->rcIconDraw;
		item.rcText = pItem->rcText;
		item.rect = pItem->rect;
		item.userData = pItem->userData;
		item.state = pItem->state;
		item.hImage_select = pItem->hImage_select;
		item.hImage_stay = pItem->hImage_stay;

		ListView_DrawItem(hEle, &item);

		XDraw_RestoreGDIOBJ_(hDraw);
	}

	//�����϶�����---------
	if (pListView->bDrag)
	{
		RECT rcDrag;
		if (pListView->dragEndPt.x > pListView->dragPt.x)
		{
			rcDrag.left = pListView->dragPt.x;
			rcDrag.right = pListView->dragEndPt.x;
		}
		else
		{
			rcDrag.left = pListView->dragEndPt.x;
			rcDrag.right = pListView->dragPt.x;
		}

		if (pListView->dragEndPt.y > pListView->dragPt.y)
		{
			rcDrag.top = pListView->dragPt.y;
			rcDrag.bottom = pListView->dragEndPt.y;
		}
		else
		{
			rcDrag.top = pListView->dragEndPt.y;
			rcDrag.bottom = pListView->dragPt.y;
		}

		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(80, 168, 220));
		XDraw_FrameRect_(hDraw, &rcDrag, hBrush);
		XDraw_DeleteObject_(hDraw, hBrush);
	}

	return TRUE;
}

void ListView_DrawItem(HELE hEle, listView_drawItem_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	if (pListView->pDrawItem)	//�û��Ի�
	{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pListView->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)pItem;
			event_.lParam = NULL;
			event_.pClass_fun = pListView->pClass_Fun_Info;
			((pFunClassEventMsg)pListView->pDrawItem)(&event_, xc_fun_v_e_listView_item);
		}
		else
		{
			pListView->pDrawItem(hEle, pItem);
		}
#else
		pList->pDrawItem(hEle, &pItem);
#endif
	}
	else  //ϵͳ����
	{
		if (STATE_SELECT == pItem->state)
		{
			if (pItem->hImage_select)
			{
				XDraw_HImageSuper_(pItem->hDraw, pItem->hImage_select, &pItem->rect);
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(pItem->hDraw, pItem->rect.left, pItem->rect.top, pItem->rect.right + 1, pItem->rect.bottom + 1, 3, 3);
				XDraw_GradientFill2_(pItem->hDraw, RGB(250, 250, 250), RGB(200, 200, 200), &pItem->rect, GRADIENT_FILL_RECT_V);
				HBRUSH hBrush = XDraw_CreateSolidBrush_(pItem->hDraw, RGB(160, 160, 160));
				XDraw_FrameRgn_(pItem->hDraw, hRgn, hBrush, 1, 1);
			}
		}
		else if (STATE_STAY == pItem->state)
		{
			if (pItem->hImage_stay)
			{
				XDraw_HImageSuper_(pItem->hDraw, pItem->hImage_stay, &pItem->rect);
			}
			else
			{
				HRGN hRgn = XDraw_CreateRoundRectRgn_(pItem->hDraw, pItem->rect.left, pItem->rect.top, pItem->rect.right + 1, pItem->rect.bottom + 1, 3, 3);
				XDraw_GradientFill2_(pItem->hDraw, RGB(255, 255, 255), RGB(230, 230, 230), &pItem->rect, GRADIENT_FILL_RECT_V);
				HBRUSH hBrush = XDraw_CreateSolidBrush_(pItem->hDraw, RGB(220, 220, 220));
				XDraw_FrameRgn_(pItem->hDraw, hRgn, hBrush, 1, 1);
			}
		}

		if (pListView->hImageList)
			XImageList_DrawImage2(pListView->hImageList, pItem->hDraw, pItem->imageID, &pItem->rcIconDraw);

		if (pItem->pText)
			XDraw_DrawText_(pItem->hDraw, pItem->pText, wcslen(pItem->pText), &pItem->rcText, DT_CENTER);

		//���Ʋ����
		if (pListView->hWndDrag)
		{
			if ((pListView->insertGroup == pItem->groupIndex) && (pListView->insertItem == pItem->itemIndex))
			{
				HPEN hPen = XDraw_CreatePen_(pItem->hDraw, PS_SOLID, 2, RGB(0, 162, 232));
				HGDIOBJ hOldPen = XDraw_SelectObject_(pItem->hDraw, hPen);

				XDraw_MoveToEx_(pItem->hDraw, pItem->rect.left - 2, pItem->rect.top);
				XDraw_LineTo_(pItem->hDraw, pItem->rect.left - 2, pItem->rect.bottom);

				XDraw_SelectObject_(pItem->hDraw, hOldPen);
				XDraw_DeleteObject_(pItem->hDraw, hPen);
			}
			else if (pListView->insertGroup == pItem->groupIndex)
			{
				int memberCount = XListView_GetGroupMemberCount(hEle, pItem->groupIndex);
				if (memberCount > 0 && pListView->insertItem > 0)
				{
					if (pListView->insertItem == memberCount && pItem->itemIndex + 1 == memberCount)
					{
						HPEN hPen = XDraw_CreatePen_(pItem->hDraw, PS_SOLID, 2, RGB(0, 162, 232));
						HGDIOBJ hOldPen = XDraw_SelectObject_(pItem->hDraw, hPen);

						XDraw_MoveToEx_(pItem->hDraw, pItem->rect.right + 2, pItem->rect.top);
						XDraw_LineTo_(pItem->hDraw, pItem->rect.right + 2, pItem->rect.bottom);

						XDraw_SelectObject_(pItem->hDraw, hOldPen);
						XDraw_DeleteObject_(pItem->hDraw, hPen);
					}
				}
			}
		}
	}
}

void ListView_DrawGroup(HELE hEle, listView_drawGroup_ *pGroup)
{
	listView_  *pListView = (listView_*)hEle;

	if (pListView->pDrawGroup)	//�û��Ի�
	{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pListView->pClass_Fun_Info_group)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)pGroup;
			event_.lParam = NULL;
			event_.pClass_fun = pListView->pClass_Fun_Info_group;
			((pFunClassEventMsg)pListView->pDrawGroup)(&event_, xc_fun_v_e_listView_group);
		}
		else
		{
			pListView->pDrawGroup(hEle, pGroup);
		}
#else
		pList->pDrawGroup(hEle, &pGroup);
#endif
	}
	else  //ϵͳ����
	{

		//���Ʊ���
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(pGroup->hDraw, RGB(200, 200, 200));
			XDraw_GradientFill2_(pGroup->hDraw, RGB(255, 255, 255), RGB(230, 230, 230), &pGroup->rect, 1);
			XDraw_FrameRect_(pGroup->hDraw, &pGroup->rect, hBrush);
			XDraw_DeleteObject_(pGroup->hDraw, hBrush);
		}

		//��չ����ť
		if (pListView->bExpandButton)
		{
			HBRUSH hBrush = XDraw_CreateSolidBrush_(pGroup->hDraw, RGB(128, 128, 128));
			XDraw_GradientFill2_(pGroup->hDraw, RGB(255, 255, 255), RGB(200, 200, 200), &pGroup->rcButton, 1);
			XDraw_FrameRect_(pGroup->hDraw, &pGroup->rcButton, hBrush);

			XDraw_MoveToEx_(pGroup->hDraw, pGroup->rcButton.left + 2, pGroup->rcButton.top + (pGroup->rcButton.bottom - pGroup->rcButton.top) / 2, NULL);
			XDraw_LineTo_(pGroup->hDraw, pGroup->rcButton.right - 2, pGroup->rcButton.top + (pGroup->rcButton.bottom - pGroup->rcButton.top) / 2);
			if (!pGroup->bExpand)  //����
			{
				XDraw_MoveToEx_(pGroup->hDraw, pGroup->rcButton.left + (pGroup->rcButton.right - pGroup->rcButton.left) / 2, pGroup->rcButton.top + 2, NULL);
				XDraw_LineTo_(pGroup->hDraw, pGroup->rcButton.left + (pGroup->rcButton.right - pGroup->rcButton.left) / 2, pGroup->rcButton.bottom - 2);
			}
		}

		//����
		if (pGroup->pText)
			XDraw_DrawText_(pGroup->hDraw, pGroup->pText, wcslen(pGroup->pText), &pGroup->rcText, DT_VCENTER | DT_SINGLELINE);
	}
}


BOOL CALLBACK ListView_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	listView_ *pListView = (listView_*)hEle;
	if (pListView->bDragItem && FALSE == pListView->bMultiSelect)//�϶���
	{
		//�����갴��,��ѡ��Ԫ��,��ô�϶���
		//�����϶����
		//����ƶ����� 

		if (pListView->down && pListView->pCurrItem && NULL == pListView->hWndDrag)
		{

			if (pListView->dragPt.x > (pPt->x - 5) && pListView->dragPt.x < (pPt->x + 5))
			{
				if (pListView->dragPt.y > (pPt->y - 5) && pListView->dragPt.y < (pPt->y + 5))
				{
					return FALSE;
				}
			}

			pListView->down = FALSE;

			//�����϶�����
			POINT pt;
			GetCursorPos(&pt);
			int cx = pListView->pCurrItem->rect.right - pListView->pCurrItem->rect.left + 14;
			int cy = pListView->pCurrItem->rect.bottom - pListView->pCurrItem->rect.top + 14;
			int y = pt.y - cy / 2; //+20-cy;
			int x = pt.x - cx / 2; //-cx/2;
			HWND hWnd = XEle_GetHWnd(hEle);

			HWINDOW hWindow = XWnd_CreateWindowEx(WS_EX_TOOLWINDOW, NULL, L"dragItem", WS_POPUP, x, y, cx, cy, hWnd, 0);

			XWnd_SetUserData(hWindow, (void*)hEle);
			XWnd_RegisterMessage(hWindow, WM_PAINT, ListView_OnDrawWindow_DragItem);

			XWnd_RegisterMessage(hWindow, WM_MOUSEMOVE, ListView_OnWndMouseMove_DragItem);
			XWnd_RegisterNCMessage(hWindow, XWM_NCMOUSEMOVE, ListView_OnWndMouseMove_DragItem);

			XWnd_RegisterMessage(hWindow, WM_LBUTTONUP, ListView_OnWndLButtonUp_DragItem);
			XWnd_RegisterNCMessage(hWindow, XWM_NCLBUTTONUP, ListView_OnWndLButtonUp_DragItem);

			XWnd_RegisterMessage(hWindow, WM_NCDESTROY, ListView_OnWndNCDestroy_DragItem);
			XWnd_ShowWindow(hWindow, SW_SHOW);

			XWnd_SetTransparentAlpha(hWindow, 128);
			XWnd_SetTransparentFlag(hWindow, XC_WIND_TRANSPARENT_SHADOW);//����͸������,�߿���Ӱ

			pListView->hWndDrag = hWindow;

			//������겶��
			SetCapture(XWnd_GetHWnd(hWindow));

			//	if(0!=SendMessage(XWnd_GetHWnd(hWindow),WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(0,0)))
			//	{
			//	XTRACE("SendMessage ʧ�� \n");
			//	}//else
			//	XTRACE("SendMessage �ɹ� \n");

			//	XWnd_CloseWindow(hWindow);

			return FALSE;
		}
		else if (pListView->hWndDrag)
		{
			pListView->down = FALSE;

			XWnd_CloseWindow(pListView->hWndDrag);
			//pListView->hWndDrag=NULL;
			XTRACE("if(pListView->hWndDrag) \n");
			return FALSE;
		}
	}
	if (FALSE == ((listView_*)hEle)->bDrag)
	{
		ListView_MouseMoveDragBegin(hEle, pPt);

		//���ͣ����
		listView_item_ *pItem = ListView_CheckDownItem(hEle, pPt);
		if (pItem)
		{
			if (pItem == pListView->pCurrItemStay)
			{
				return FALSE;
			}

			if (STATE_SELECT == pItem->state)
			{
				if (pListView->pCurrItemStay)
				{
					if (pListView->pCurrItemStay != pItem)
					{
						pListView->pCurrItemStay->state = STATE_LEAVE;
					}
				}

				pListView->pCurrItemStay = pItem;
				XEle_RedrawEle(hEle);
				return FALSE;
			}

			if (pListView->pCurrItemStay)
			{
				if (STATE_SELECT != pListView->pCurrItemStay->state)
					pListView->pCurrItemStay->state = STATE_LEAVE;
			}

			pListView->pCurrItemStay = pItem;
			pListView->pCurrItemStay->state = STATE_STAY;

			XEle_RedrawEle(hEle);
		}
		else
		{
			if (pListView->pCurrItemStay)
			{
				if (STATE_SELECT != pListView->pCurrItemStay->state)
					pListView->pCurrItemStay->state = STATE_LEAVE;

				pListView->pCurrItemStay = NULL;

				XEle_RedrawEle(hEle);
			}
		}
	}
	else
	{
		ListView_MouseMoveDrag(hEle, pPt);
	}
	return FALSE;
}

void ListView_MouseMoveDragBegin(HELE hEle, POINT *pPt) //׼���϶�ѡ��
{
	listView_ *pListView = (listView_*)hEle;
	if (FALSE == pListView->bMultiSelect)
		return;
	if (pListView->down)
	{
		if (pPt->x<(pListView->dragPt.x - 5) || pPt->x>(pListView->dragPt.x + 5)
			|| pPt->y<(pListView->dragPt.y - 5) || pPt->y>(pListView->dragPt.y + 5))
		{
			pListView->bDrag = TRUE;

			pListView->dragPt.x = pListView->dragPt.x - XSView_GetHViewPos(hEle);
			pListView->dragPt.y = pListView->dragPt.y - XSView_GetVViewPos(hEle);
			pListView->dragEndPt.x = pPt->x - XSView_GetHViewPos(hEle);
			pListView->dragEndPt.y = pPt->y - XSView_GetVViewPos(hEle);

			g_hListView = hEle;
			SetTimer(XEle_GetHWnd(hEle), IDT_LISTVIEW_DRAG_RECT, 50, ListView_TimerProc);
			XEle_SetCapture(hEle);
		}
	}
}


void ListView_MouseMoveDrag(HELE hEle, POINT *pPt) //�϶�ѡ��
{
	listView_ *pListView = (listView_*)hEle;
	pListView->dragEndPt.x = pPt->x - XSView_GetHViewPos(hEle);
	pListView->dragEndPt.y = pPt->y - XSView_GetVViewPos(hEle);

	//�϶�����--------------------
	RECT rcDrag;
	if (pListView->dragEndPt.x > pListView->dragPt.x)
	{
		rcDrag.left = pListView->dragPt.x;
		rcDrag.right = pListView->dragEndPt.x;
	}
	else
	{
		rcDrag.left = pListView->dragEndPt.x;
		rcDrag.right = pListView->dragPt.x;
	}
	if (pListView->dragEndPt.y > pListView->dragPt.y)
	{
		rcDrag.top = pListView->dragPt.y;
		rcDrag.bottom = pListView->dragEndPt.y;
	}
	else
	{
		rcDrag.top = pListView->dragEndPt.y;
		rcDrag.bottom = pListView->dragPt.y;
	}

	//������Щ�����϶�����
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (XC_RectInRect(&pItem->rect, &rcDrag))
				{
					pItem->state = STATE_SELECT;
				}
				else
				{
					pItem->state = STATE_LEAVE;
				}
			}
		}
	}

	int countItem = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < countItem; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (XC_RectInRect(&pItem->rect, &rcDrag))
		{
			pItem->state = STATE_SELECT;
		}
		else
		{
			pItem->state = STATE_LEAVE;
		}
	}
}

BOOL CALLBACK ListView_OnEleLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	listView_ *pListView = (listView_*)hEle;

	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (FALSE == PtInRect(&rect, *pPt))
		return FALSE;

	listView_group_ *pGroup = ListView_CheckDownGroup(hEle, pPt);
	if (pGroup)
	{
		if (pGroup->bExpand)
		{
			pGroup->bExpand = FALSE;
		}
		else
		{
			pGroup->bExpand = TRUE;
		}
		XListView_Adjust(hEle);
		Ele_SendEvent(hEle, XE_LISTVIEW_EXPAND, pGroup->index, pGroup->bExpand);
		if (!XC_IsHELE(hEle)) return FALSE;
		XEle_RedrawEle(hEle);
		return FALSE;
	}

	pListView->down = TRUE;
	pListView->dragPt = *pPt;

	listView_item_ *pItem = ListView_CheckDownItem(hEle, pPt);
	//����ѡ��//////////////////////////////////////////////////////
	if (FALSE == pListView->bMultiSelect)
	{
		if (0x8000 & GetKeyState(VK_CONTROL)) //ctrl ����״̬
			return FALSE;
		if (0x8000 & GetKeyState(VK_SHIFT)) //shift ����״̬
			return FALSE;

		if (pItem)
		{
			if (pItem != pListView->pCurrItem)
			{
				if (pListView->pCurrItem)
					pListView->pCurrItem->state = STATE_LEAVE;
				pListView->pCurrItem = pItem;
				pListView->pCurrItem->state = STATE_SELECT;
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
				if (!XC_IsHELE(hEle)) return FALSE;
				XEle_RedrawEle(hEle);
			}
		}
		else
		{
			if (pListView->pCurrItem)
			{
				pListView->pCurrItem->state = STATE_LEAVE;
				pListView->pCurrItem = NULL;
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
				if (!XC_IsHELE(hEle)) return FALSE;
				XEle_RedrawEle(hEle);
			}
		}
		return FALSE;
	}

	//��ѡѡ��////////////////////////////////////////////////////////////
	if (0x8000 & GetKeyState(VK_CONTROL) && pItem) //ctrl ����״̬
	{
		if (STATE_SELECT != pItem->state)
		{
			pItem->state = STATE_SELECT;
			pListView->pCurrItem = pItem;
			XArray_Add(pListView->hArrayCurrItem, pItem);
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
		}
		else
		{
			if (pListView->pCurrItem == pItem)
			{
				pItem->state = 0;
				XArray_Delete(pListView->hArrayCurrItem, pItem);

				if (Array_GetCount(pListView->hArrayCurrItem) > 0)
				{
					pListView->pCurrItem = (listView_item_*)Array_GetAt(pListView->hArrayCurrItem, Array_GetCount(pListView->hArrayCurrItem) - 1);
				}
				else
					pListView->pCurrItem = NULL;
			}
			else
			{
				pItem->state = STATE_LEAVE;
				XArray_Delete(pListView->hArrayCurrItem, pItem);
			}

			if (pListView->pCurrItem)
			{
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
			}
			else
			{
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
			}
		}
		if (!XC_IsHELE(hEle)) return FALSE;
		XEle_RedrawEle(hEle);

	}
	else if (0x8000 & GetKeyState(VK_SHIFT) && pItem) //shift ����״̬
	{
		ListView_ShiftDown(hEle, pItem);
	}
	else if (pItem)
	{
		BOOL bDraw = FALSE;
		if (STATE_SELECT == pItem->state)
			bDraw = FALSE;
		else
			bDraw = TRUE;

		int count = Array_GetCount(pListView->hArrayCurrItem);
		for (int i = 0; i < count; i++)
		{
			((listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
		}
		XArray_DeleteAll(pListView->hArrayCurrItem);

		pListView->pCurrItem = pItem;
		XArray_Add(pListView->hArrayCurrItem, pItem);

		Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
		if (bDraw || count > 0)
		{
			pItem->state = STATE_SELECT;
			XEle_RedrawEle(hEle);
		}
	}
	else  //�հ�����
	{
		pListView->pCurrItem = NULL;
		int count = Array_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				((listView_item_*)Array_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
			}
			XArray_DeleteAll(pListView->hArrayCurrItem);
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
			if (!XC_IsHELE(hEle)) return FALSE;
			XEle_RedrawEle(hEle);
		}
	}

	return FALSE;
}

BOOL CALLBACK ListView_OnEleLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	listView_ *pListView = (listView_*)hEle;

	if (pListView->down)
		pListView->down = FALSE;

	if (pListView->bDrag)
	{
		XArray_DeleteAll(pListView->hArrayCurrItem);
		pListView->pCurrItem = NULL;

		pListView->bDrag = FALSE;
		KillTimer(XEle_GetHWnd(hEle), IDT_LISTVIEW_DRAG_RECT);
		XEle_ReleaseCapture(hEle);
		XEle_RedrawEle(hEle);

		int countGroup = XArray_GetCount(pListView->hArrayGroupList);
		for (int g = 0; g < countGroup; g++)
		{
			listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (STATE_SELECT == pItem->state)
				{
					//add
					XArray_Add(pListView->hArrayCurrItem, pItem);
				}
			}
		}

		int countItem = XArray_GetCount(pListView->hArrayList);
		for (int i = 0; i < countItem; i++)
		{
			listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
			if (STATE_SELECT == pItem->state)
			{
				//add
				XArray_Add(pListView->hArrayCurrItem, pItem);
			}
		}

		int count = XArray_GetCount(pListView->hArrayCurrItem);
		if (count > 0)
		{
			pListView->pCurrItem = (listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, 0);
		}

		if (pListView->pCurrItem)
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pListView->pCurrItem->groupIndex, pListView->pCurrItem->index);
		else
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, -1, -1);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK ListView_OnEventKillFocus(HELE hEle, HELE hEventEle) //ʧȥ����
{
	if (hEle == hEventEle)
	{
		listView_ *pListView = (listView_*)hEle;
		if (pListView->bDrag)
		{
			((listView_*)hEle)->bDrag = FALSE;
		}

		if (pListView->pCurrItemStay)
		{
			if (STATE_SELECT != pListView->pCurrItemStay->state)
				pListView->pCurrItemStay->state = STATE_LEAVE;

			pListView->pCurrItemStay = NULL;

			XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK ListView_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	listView_ *pListView = (listView_*)hEle;
	if (pListView->pCurrItemStay)
	{
		if (STATE_SELECT != pListView->pCurrItemStay->state)
			pListView->pCurrItemStay->state = STATE_LEAVE;

		pListView->pCurrItemStay = NULL;

		XEle_RedrawEle(hEle);
	}
	return FALSE;
}

listView_group_ *ListView_CheckDownGroup(HELE hEle, POINT *pPt) //������������
{
	listView_ *pListView = (listView_*)hEle;

	POINT  pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);

	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		if (PtInRect(&pGroup->rcButton, pt)) //�鰡չ������
		{
			return pGroup;
		}
	}
	return NULL;
}

listView_item_ *ListView_CheckDownItem(HELE hEle, POINT *pPt)  //������������
{
	listView_ *pListView = (listView_*)hEle;

	POINT  pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);

	//��
	int countGroup = XArray_GetCount(pListView->hArrayGroupList);
	for (int g = 0; g < countGroup; g++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, g);
		/*	if(PtInRect(&pGroup->rcButton,pt)) //�鰡չ������
		{
		if(pGroup->bExpand)
		{
		pGroup->bExpand=FALSE;
		}else
		{
		pGroup->bExpand=TRUE;
		}
		ListView_Adjust(hEle);
		XEle_RedrawEle(hEle);
		return (listView_item_*)1;
		}*/
		if (pGroup->bExpand)
		{
			int countItem = XArray_GetCount(pGroup->hArrayList);
			for (int i = 0; i < countItem; i++)
			{
				listView_item_ *pItem = (listView_item_*)XArray_GetAt(pGroup->hArrayList, i);
				if (PtInRect(&pItem->rect, pt)) //ѡ����
				{
					return pItem;
				}
			}
		}
	}

	int count = XArray_GetCount(pListView->hArrayList);
	for (int i = 0; i < count; i++)
	{
		listView_item_ *pItem = (listView_item_*)XArray_GetAt(pListView->hArrayList, i);
		if (PtInRect(&pItem->rect, pt))
		{
			return pItem;
		}
	}
	return NULL;
}

void ListView_ShiftDown(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	int count = Array_GetCount(pListView->hArrayCurrItem);
	if (0 == count)
	{
		pItem->state = STATE_SELECT;
		XArray_Add(pListView->hArrayCurrItem, pItem);
		pListView->pCurrItem = pItem;
		Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pItem->groupIndex, pItem->index);
		if (!XC_IsHELE(hEle)) return;
		XEle_RedrawEle(hEle);
	}
	else if (pListView->pCurrItem)
	{
		int count = XArray_GetCount(pListView->hArrayCurrItem);
		for (int i = 0; i < count; i++)
		{
			((listView_item_*)XArray_GetAt(pListView->hArrayCurrItem, i))->state = STATE_LEAVE;
		}
		XArray_DeleteAll(pListView->hArrayCurrItem);
		pListView->pCurrItem->state = STATE_SELECT;
		XArray_Add(pListView->hArrayCurrItem, pListView->pCurrItem);

		if (pItem->groupIndex == pListView->pCurrItem->groupIndex)//ѡ������ͬһ����
		{
			int begin = 0, end = 0;
			if (pListView->pCurrItem->index < pItem->index)
			{
				begin = pListView->pCurrItem->index;
				end = pItem->index;
			}
			else
			{
				begin = pItem->index;
				end = pListView->pCurrItem->index;
			}
			if ((end - begin) > 0)
			{
				HARRAY hArray = NULL;
				if (-1 == pItem->groupIndex) //û����
					hArray = pListView->hArrayList;
				else
				{
					listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
					hArray = pGroup->hArrayList;
				}

				int countItem = Array_GetCount(hArray);
				for (int i = begin; i <= end; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pListView->pCurrItem->groupIndex, pListView->pCurrItem->index);
				if (!XC_IsHELE(hEle)) return;
				XEle_RedrawEle(hEle);
			}
		}
		else  //ѡ�����ڲ�ͬ��
		{
			if (-1 == pListView->pCurrItem->groupIndex)
			{
				ListView_ShiftDown1(hEle, pItem);
			}
			else if (-1 == pItem->groupIndex)
			{
				ListView_ShiftDown2(hEle, pItem);
			}
			else if (pListView->pCurrItem->groupIndex < pItem->groupIndex)
			{
				ListView_ShiftDown3(hEle, pItem);
			}
			else if (pListView->pCurrItem->groupIndex > pItem->groupIndex)
			{
				ListView_ShiftDown4(hEle, pItem);
			}
			Ele_SendEvent(hEle, XE_LISTVIEW_SELECT, pListView->pCurrItem->groupIndex, pListView->pCurrItem->index);
		}
	}
}

void ListView_ShiftDown1(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;

	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pItem->index; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pItem->groupIndex + 1; i < groupCount; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	hArray = pListView->hArrayList;
	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i <= pListView->pCurrItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

void ListView_ShiftDown2(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pListView->pCurrItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pListView->pCurrItem->index + 1; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pListView->pCurrItem->groupIndex + 1; i < groupCount; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	hArray = pListView->hArrayList;
	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i <= pItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

void ListView_ShiftDown3(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pListView->pCurrItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pListView->pCurrItem->index + 1; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pListView->pCurrItem->groupIndex + 1; i < pItem->groupIndex; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
	hArray = pGroup->hArrayList;

	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i <= pItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

void ListView_ShiftDown4(HELE hEle, listView_item_ *pItem)
{
	listView_ *pListView = (listView_*)hEle;
	listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pListView->pCurrItem->groupIndex);
	HARRAY hArray = pGroup->hArrayList;

	BOOL bRedraw = FALSE;
	int countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = 0; i < pListView->pCurrItem->index; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	int groupCount = XArray_GetCount(pListView->hArrayGroupList);
	for (int i = pItem->groupIndex + 1; i < pListView->pCurrItem->groupIndex; i++)
	{
		listView_group_ *pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, i);
		if (pGroup->bExpand)
		{
			HARRAY hArray = pGroup->hArrayList;

			int countItem = Array_GetCount(hArray);
			if (countItem > 0)
			{
				for (int i = 0; i < countItem; i++)
				{
					listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
					pItemTemp->state = STATE_SELECT;
					XArray_Add(pListView->hArrayCurrItem, pItemTemp);
				}
				bRedraw = TRUE;
			}
		}
	}

	pGroup = (listView_group_*)XArray_GetAt(pListView->hArrayGroupList, pItem->groupIndex);
	hArray = pGroup->hArrayList;

	countItem = Array_GetCount(hArray);
	if (countItem > 0)
	{
		for (int i = pItem->index; i < countItem; i++)
		{
			listView_item_ *pItemTemp = (listView_item_*)Array_GetAt(hArray, i);
			pItemTemp->state = STATE_SELECT;
			XArray_Add(pListView->hArrayCurrItem, pItemTemp);
		}
		bRedraw = TRUE;
	}

	if (bRedraw)
		XEle_RedrawEle(hEle);
}

///@}


HELE  g_hListView = NULL;
VOID CALLBACK ListView_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (IDT_LISTVIEW_DRAG_RECT == idEvent)
	{
		XEle_RedrawEle(g_hListView);
	}
}

BOOL CALLBACK ListView_OnDrawWindow_DragItem(HWINDOW hWindow, HDRAW hDraw)
{
	listView_ *pListView = (listView_*)XWnd_GetUserData(hWindow);

	listView_item_ *pItem = pListView->pCurrItem;
	RECT rcIcon = pItem->rcIcon;

	RECT rc = pItem->rect;
	RECT rcIconDraw = pItem->rcIconDraw;
	RECT rcText = pItem->rcText;

	int cx = rcIconDraw.right - rcIconDraw.left;
	int cy = rcIconDraw.bottom - rcIconDraw.top;
	rcIconDraw.left = rcIconDraw.left - rc.left;
	rcIconDraw.top = rcIconDraw.top - rc.top;
	rcIconDraw.right = rcIconDraw.left + cx;
	rcIconDraw.bottom = rcIconDraw.top + cy;

	cx = rcText.right - rcText.left;
	cy = rcText.bottom - rcText.top;
	rcText.left = rcText.left - rc.left;
	rcText.top = rcText.top - rc.top;
	rcText.right = rcText.left + cx;
	rcText.bottom = rcText.top + cy;

	if (pListView->hImageList)
		XImageList_DrawImage2(pListView->hImageList, hDraw, pItem->imageID, &rcIconDraw);

	if (pItem->hString)
	{
		wchar_t *pText = XStr_GetBuffer(pItem->hString);
		if (pText)
			XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_CENTER);
	}
	return TRUE;
}

//����ƶ�
BOOL CALLBACK ListView_OnWndMouseMove_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	POINT pt;
	GetCursorPos(&pt);

	RECT rect;
	XWnd_GetWindowRect(hWindow, &rect);

	int x = pt.x - (rect.right - rect.left) / 2;
	int y = pt.y - (rect.bottom - rect.top) / 2;

	XWnd_SetWindowPos(hWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	////////////////////////////////////////////////////////////////////
	listView_ *pListView = (listView_*)XWnd_GetUserData(hWindow);
	HELE hListView = (HELE)pListView;

	//ת������������
	ScreenToClient(XEle_GetHWnd(hListView), &pt);

	//ת����listView����
	XEle_PointNCWndToEle(hListView, &pt);

	RECT rcListView;
	XEle_GetClientRect(hListView, &rcListView);

	if (PtInRect(&rcListView, pt)) //���б���ͼ��
	{
		int groupIndex = -1;
		int itemIndex = -1;
		XListView_HitTest(hListView, &pt, &groupIndex, &itemIndex);
		listView_item_ *pHitItem = ListView_GetItem_XC(hListView, groupIndex, itemIndex);
		if (pHitItem)
		{
			if (pt.x > (pHitItem->rect.left + (pHitItem->rect.right - pHitItem->rect.left) / 2))
			{
				itemIndex++;
				//	XTRACE("�� \n");
			}
			else
			{
				//	XTRACE("�� \n");
			}
		}

		if (groupIndex != pListView->insertGroup || itemIndex != pListView->insertItem)
		{
			//XTRACE("XEle_RedrawEle(hListView) \n");
			pListView->insertGroup = groupIndex;
			pListView->insertItem = itemIndex;
			XEle_RedrawEle(hListView);
		}

	}
	else //���б���ͼ��
	{
		pListView->insertGroup = -1;
		pListView->insertItem = -1;
		if (pt.y > (rcListView.bottom - 10)) //���¹���
		{
			XSView_ScrollDownLine(hListView);
		}
		else if (pt.y < 10)
		{
			XSView_ScrollTopLine(hListView);
		}
	}

	return FALSE;
}

BOOL CALLBACK ListView_OnWndLButtonUp_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt)
{
	XWnd_CloseWindow(hWindow);
	return TRUE;
}

BOOL CALLBACK ListView_OnWndNCDestroy_DragItem(HWINDOW hWindow)
{
	//XTRACE("ListView_OnWndNCDestroy_DragItem() \n");
	listView_ *pListView = (listView_*)XWnd_GetUserData(hWindow);
	pListView->hWndDrag = NULL;

	if (pListView->insertGroup == pListView->pCurrItem->groupIndex && pListView->insertItem == pListView->pCurrItem->index)
	{
		XEle_RedrawEle((HELE)pListView);
		return FALSE;
	}

	if (-1 == pListView->insertItem || NULL == pListView->pCurrItem)
	{
		XEle_RedrawEle((HELE)pListView);
		return FALSE;
	}

	listView_item_ *pItem = pListView->pCurrItem;
	listView_dragInsert_  info;
	info.groupIndex = pItem->groupIndex;
	info.itemIndex = pItem->index;

	if (-1 == pItem->groupIndex)
	{
		XArray_DeleteIndex(pListView->hArrayList, pItem->index);
	}
	else
	{
		listView_group_ *pGroup = ListView_GetGroup_XC((HELE)pListView, pItem->groupIndex);
		XArray_DeleteIndex(pGroup->hArrayList, pItem->index);
	}

	if (-1 == pListView->insertGroup) //û�з���
	{
		if (-1 != pItem->groupIndex) //�з���
		{
			XArray_insert(pListView->hArrayList, pItem, pListView->insertItem);
		}
		else //û����
		{
			if (pListView->insertItem < pItem->index)
			{
				XArray_insert(pListView->hArrayList, pItem, pListView->insertItem);
			}
			else
			{
				XArray_insert(pListView->hArrayList, pItem, pListView->insertItem - 1);
			}
		}
	}
	else //�з���
	{

		if (pListView->insertGroup == pItem->groupIndex) //��ͬһ������
		{
			listView_group_ *pGroup = ListView_GetGroup_XC((HELE)pListView, pItem->groupIndex);
			if (pListView->insertItem < pItem->index)
			{
				XArray_insert(pGroup->hArrayList, pItem, pListView->insertItem);
			}
			else
			{
				XArray_insert(pGroup->hArrayList, pItem, pListView->insertItem - 1);
			}
		}
		else //��ͬ����
		{
			listView_group_ *pGroup = ListView_GetGroup_XC((HELE)pListView, pListView->insertGroup);

			XArray_insert(pGroup->hArrayList, pItem, pListView->insertItem);

		}
	}

	XListView_Adjust((HELE)pListView);

	info.groupIndex_new = pItem->groupIndex;
	info.itemIndex_new = pItem->index;

	info.groupIndex_insert = pListView->insertGroup;
	info.itemIndex_insert = pListView->insertItem;

	pListView->insertGroup = -1;
	pListView->insertItem = -1;

	//�����¼�
	Ele_SendEvent((HELE)pListView, XE_LISTVIEW_DRAG_INSERT, (WPARAM)&info, 0);
	if (!XC_IsHELE((HELE)pListView)) return FALSE;
	XEle_RedrawEle((HELE)pListView);
	return FALSE;
}
