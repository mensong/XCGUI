/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup tree �б���Ԫ��(Tree)
/// @ingroup groupElements
/// @{

/// @brief ������Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XTree_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	tree_ *pTree = (tree_*)malloc(sizeof(tree_));
	memset(pTree, 0, sizeof(tree_));

	Tree_Init((HELE)pTree, x, y, cx, cy, XC_TREE, hParent);
	return (HELE)pTree;
}


void Tree_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	SView_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_TREE);
	tree_ *pTree = TREE(hEle);
	pTree->pRoot = NULL;
	pTree->bAdjust = FALSE;
	pTree->uid = 0;
	pTree->expandSize = 9;
	pTree->indentation = 20;
	pTree->itemHeight = 20;
	pTree->spacingLeft = 3;
	pTree->spacingTop = 3;
	pTree->pEnd = NULL;
	pTree->bLine = TRUE;
	pTree->bButton = TRUE;
	pTree->bRootLine = TRUE;

	XSView_SetScrollSize(hEle, 10, pTree->itemHeight);

	XSView_SetDrawScrollView(hEle, Tree_OnDrawScrollView);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, Tree_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_RBUTTONDOWN, Tree_OnRButtonDown);
	XEle_RegisterMessage(hEle, XM_MOUSEDBCLICK, Tree_OnMouseDBClick);
	XEle_RegisterEvent(hEle, XE_DESTROY, Tree_OnDestroy);
	XEle_RegisterEvent(hEle, XE_SETFOCUS, Tree_OnEventSetFocus);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, Tree_OnEventKillFocus);
}

int Tree_AddID(HELE hEle)
{
	int id = TREE(hEle)->uid + 1;
	if (id > 2100000000) //2100000000
		id = 1;

	while (TREE(hEle)->uid != id)
	{
		if (FALSE == Tree_AddIDTest(TREE(hEle)->pRoot, id))
		{
			TREE(hEle)->uid = id;
			return id;
		}
		id++;
		if (id > 2100000000)
			id = 1;
	}

	MessageBox(NULL, L"Tree_ ��Ԫ�ط���ID���ִ���!", L"�Ųʽ������ʾ", 0);
	exit(0);
	return -1;
}

BOOL Tree_AddIDTest(treeNode_ *pNode, int id)
{
	if (NULL == pNode)
		return NULL;

	if (id == pNode->id)
	{
		return TRUE;
	}
	BOOL res;
	res = Tree_AddIDTest(pNode->pRight, id);
	if (res) return res;
	res = Tree_AddIDTest(pNode->pLeft, id);
	if (res) return res;
	return FALSE;
}

void CALLBACK Tree_OnDestroy(HELE hEle)  //����
{
	XTree_DeleteAllItems(hEle);
	if (TREE(hEle)->hImageList)
		XImageList_Destroy(TREE(hEle)->hImageList);

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	if (TREE(hEle)->pClass_Fun_Info)
		free(TREE(hEle)->pClass_Fun_Info);
#endif
}

/// @brief ������Ԫ��.
/// @param hEle   Ԫ�ؾ��.
/// @param pText  �ı�����.
/// @param parentId   ����ID.
/// @param imageId     ͼ������ID.
/// @param selectImageId  ѡ��״̬ͼ������ID.
/// @param insertAfter ����λ�ñ�ʶ,�����ǲ���ָ�������,���id��,XTREE_INSERT_BEGIN:���뵱ǰ�㿪ʼ,XTREE_INSERT_LAST:���뵱ǰ��ĩβ.
/// @param bExpand �Ƿ�չ��.
/// @return ���ز������ID.
int WINAPI XTree_InsertItem(HELE hEle, wchar_t *pText, int parentId, int imageId, int selectImageId, int insertAfter, BOOL bExpand) //������
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (NULL == pText)
		return -1;

	tree_ *pTree = TREE(hEle);

	if (parentId < 0)
		return -1;

	pTree->bAdjust = TRUE;

	treeNode_ *pNode = (treeNode_*)malloc(sizeof(treeNode_));
	memset(pNode, 0, sizeof(treeNode_));
	pNode->hString = XStr_Create();
	XStr_SetString(pNode->hString, pText);
	pNode->imageId = imageId;
	pNode->selectImageId = selectImageId;
	pNode->bExpand = bExpand;
	pNode->id = Tree_AddID(hEle); //pTree->uid;

	//�ı����
	HDC hdc = ::GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
	SIZE size;
	GetTextExtentPoint32(hdc, XStr_GetBuffer(pNode->hString), XStr_GetLength(pNode->hString), &size);
	pNode->textWidth = size.cx;
	SelectObject(hdc, hOldFont);
	::ReleaseDC(NULL, hdc);

	//pTree->uid++;

	if (NULL == pTree->pRoot)  //���ڵ�
	{
		if (FALSE == Tree_InsertItem1(hEle, pNode))
		{
			XStr_Destroy(pNode->hString);
			free(pNode);
			return -1;
		}
		return pNode->id;
	}
	else if (XTREE_ROOT == parentId)  //���ڵ���ֵܽڵ�
	{
		if (FALSE == Tree_InsertItem2(hEle, pNode, insertAfter))
		{
			XStr_Destroy(pNode->hString);
			free(pNode);
			return -1;
		}
		return pNode->id;
	}
	else
	{
		if (FALSE == Tree_InsertItem3(hEle, pNode, parentId, insertAfter))
		{
			XStr_Destroy(pNode->hString);
			free(pNode);
			return -1;
		}
		return pNode->id;
	}
	XStr_Destroy(pNode->hString);
	free(pNode);
	return -1;
}

/// @brief ������ǰ���չ��������ť.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable  TRUE����,�����෴.
void WINAPI XTree_EnableButton(HELE hEle, BOOL bEnable)   //��ʾ��ť
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bButton = bEnable;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief ������������.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable  TRUE����,�����෴.
void WINAPI XTree_EnableLine(HELE hEle, BOOL bEnable)    //��ʾ��������
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bLine = bEnable;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief ���ø�����ʾ��������.
/// @param hEle   Ԫ�ؾ��.
/// @param bEnable  TRUE����,�����෴.
void WINAPI XTree_EnableRootLine(HELE hEle, BOOL bEnable)  //�������Ӹ�������
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bRootLine = bEnable;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief �ж��Ƿ���������չ��������ť.
/// @param hEle   Ԫ�ؾ��.
/// @return ����Ƿ���TRUE,�����෴.
BOOL WINAPI XTree_IsButton(HELE hEle)
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->bButton;
}

/// @brief �ж��Ƿ���������������.
/// @param hEle   Ԫ�ؾ��.
/// @return ����Ƿ���TRUE,�����෴.
BOOL WINAPI XTree_IsLine(HELE hEle)
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->bLine;
}

/// @brief �ж��Ƿ������˸�����������.
/// @param hEle   Ԫ�ؾ��.
/// @return ����Ƿ���TRUE,�����෴.
BOOL WINAPI XTree_IsRootLine(HELE hEle)
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->bRootLine;
}

/// @brief ����������.
/// @param hEle  Ԫ�ؾ��.
/// @param left  ����С.
void WINAPI XTree_SetSpacingLeft(HELE hEle, int left)   //��������
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->spacingLeft = left;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief �������ϼ��.
/// @param hEle  Ԫ�ؾ��.
/// @param top  �ϼ���С.
void WINAPI XTree_SetSpacingTop(HELE hEle, int top)     //�����ϼ��
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->spacingTop = top;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief ���ù�����ͼ���б���Դ���.
/// @param hEle  Ԫ�ؾ��.
/// @param hImageList  ͼƬ�б���Դ���.
void WINAPI XTree_SetImageList(HELE hEle, HXCGUI hImageList) //����ͼƬ�б�
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (TREE(hEle)->hImageList)
	{
		XImageList_Destroy(TREE(hEle)->hImageList);
		TREE(hEle)->hImageList = NULL;
	}
	if (hImageList)
	{
		IsImageListDebug(hImageList, __FUNCTION__);
		TREE(hEle)->hImageList = ImageList_AddRef(hImageList);
	}
}

/// @brief �������û�����.
/// @param hEle  Ԫ�ؾ��.
/// @param id  ��ID.
/// @param data �û�����.
void WINAPI XTree_SetItemData(HELE hEle, int id, void* data) //�����û�����
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		pNode->data = data;
}

/// @brief ����չ��������ť��С.
/// @param hEle  Ԫ�ؾ��.
/// @param size  չ��������ť��С.
void WINAPI XTree_SetExpandButtonSize(HELE hEle, int size) //����չ����ť��С
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->expandSize = size;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief ���������������.
/// @param hEle  Ԫ�ؾ��.
/// @param width  �������.
void WINAPI XTree_SetIndentation(HELE hEle, int width) //���������������
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->indentation = width;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief ����ѡ����.
/// @param hEle  Ԫ�ؾ��.
/// @param id  ѡ����ID.
void WINAPI XTree_SetSelectItem(HELE hEle, int id)  //����ѡ����
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		if (TREE(hEle)->pCurrItem)
			TREE(hEle)->pCurrItem->state = 0;
		TREE(hEle)->pCurrItem = pNode;
		TREE(hEle)->pCurrItem->state = STATE_SELECT;
		XEle_RedrawEle(hEle);
	}
}

/// @brief �������ı�����.
/// @param hEle  Ԫ�ؾ��.
/// @param id  ��ID.
/// @param pText �ı�����.
void WINAPI XTree_SetItemText(HELE hEle, int id, wchar_t *pText) //�������ı�
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (pText)
	{
		treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
		if (pNode)
		{
			XStr_SetString(pNode->hString, pText);
			HDC hdc = ::GetDC(NULL);
			HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
			SIZE size;
			GetTextExtentPoint32(hdc, XStr_GetBuffer(pNode->hString), XStr_GetLength(pNode->hString), &size);
			pNode->textWidth = size.cx;
			SelectObject(hdc, hOldFont);
			::ReleaseDC(NULL, hdc);
			TREE(hEle)->bAdjust = TRUE;
		}
	}
}

/// @brief ������ͼ��.
/// @param hEle  Ԫ�ؾ��.
/// @param id  ��ID.
/// @param imageId ͼ��ID.
void WINAPI XTree_SetItemImage(HELE hEle, int id, int imageId)  //������ͼƬ
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		pNode->imageId = imageId;
}

/// @brief ������߶�.
/// @param hEle  Ԫ�ؾ��.
/// @param height ��߶�.
void WINAPI XTree_SetItemHeight(HELE hEle, int height) //������߶�
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->itemHeight = height;
	XSView_SetScrollSize(hEle, 10, height);
}

/// @brief �������Ԫ��.
/// @param hEle   Ԫ�ؾ��.
/// @param id       ��ID.
/// @param pInfo    ��Ԫ����Ϣ
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XTree_SetItemBindEle(HELE hEle, int id, itemBindEle_ *pInfo) //��Ԫ��
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pItem = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
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

/// @brief ��ȡ���û�����.
/// @param hEle  Ԫ�ؾ��.
/// @param id    ��ID.
/// @return �û�����.
void* WINAPI XTree_GetItemData(HELE hEle, int id) //��ȡ�û�����
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		return pNode->data;
	}
	return NULL;
}

/// @brief ��ȡ��߶�.
/// @param hEle  Ԫ�ؾ��.
/// @return ��߶�.
int WINAPI XTree_GetItemHeight(HELE hEle)     //��ȡ��߶�
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->itemHeight;
}

/// @brief ��ȡ��ǰѡ�����.
/// @param hEle  Ԫ�ؾ��.
/// @return ��ǰѡ�����ID.
int WINAPI XTree_GetSelectItem(HELE hEle) //��ȡ��ǰѡ�����
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (TREE(hEle)->pCurrItem)
		return TREE(hEle)->pCurrItem->id;
	return -1;
}

/// @brief ��ȡָ����ĸ���ID.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return ����ID.
int WINAPI XTree_GetParentItem(HELE hEle, int id)  //��ȡָ����ĸ���
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pParent)
	{
		return pNode->pParent->id;
	}

	return -1;
}

/// @brief ��ȡָ���������.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return ����ID.
int WINAPI XTree_GetChildItem(HELE hEle, int id)  //��ȡָ���������
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pRight)
		return pNode->pRight->id;

	return -1;
}

/// @brief ��ȡָ�������һ���ֵ���.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return �ֵ���ID.
int WINAPI XTree_GetNextSiblingItem(HELE hEle, int id) //��ȡָ�������һ���ֵ���
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pLeft)
		return pNode->pLeft->id;

	return -1;
}

/// @brief ��ȡָ�������һ���ֵ���.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return �ֵ���ID.
int WINAPI XTree_GetPrevSiblingItem(HELE hEle, int id) //��ȡָ�������һ���ֵ���
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pBrother)
		return pNode->pBrother->id;

	return -1;
}

/// @brief ��ȡ��һ����,Ҳ���Ǹ���.
/// @param hEle  Ԫ�ؾ��.
/// @return ��ID.
int WINAPI XTree_GetFirstItem(HELE hEle) //��ȡ��һ���ڵ�
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (TREE(hEle)->pRoot)
		return TREE(hEle)->pRoot->id;
	return -1;
}

/// @brief ��ȡ�����.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return �����������ڵ�����.
int WINAPI XTree_GetItemDepth(HELE hEle, int id) //��ȡ�ڵ����
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return pNode->depth;
	return -1;
}

/// @brief ��ȡ��ͼ��.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return ͼ����ͼƬ�б��е�����ID.
int WINAPI XTree_GetItemImage(HELE hEle, int id)  //��ȡ��ͼƬ
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return pNode->imageId;

	return -1;
}

/// @brief ��ȡ���ı�.
/// @param hEle  Ԫ�ؾ��.
/// @param id   ��ID.
/// @return ���ı�����.
wchar_t* WINAPI XTree_GetItemText(HELE hEle, int id)   //��ȡ���ı�
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return XStr_GetBuffer(pNode->hString);

	return NULL;
}

/// @brief ��ȡͼƬ�б�.
/// @param hEle  Ԫ�ؾ��.
/// @return ͼ���б���.
HXCGUI WINAPI XTree_GetImageList(HELE hEle) //��ȡͼƬ�б�
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->hImageList;
}

/// @brief չ������ָ����.
/// @param hEle  Ԫ�ؾ��.
/// @param id ��ID.
/// @param bExpand TRUEչ��,�����෴.
void WINAPI XTree_Expand(HELE hEle, int id, BOOL bExpand) //չ������ָ����
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		if (pNode->bExpand != bExpand)
		{
			pNode->bExpand = bExpand;
			Tree_AdjustTree(hEle);
			XEle_RedrawEle(hEle);
			//XWnd_RedrawWnd(XEle_GetHWindow(hEle));
		}
	}
}

/// @brief �ж�ָ�����Ƿ�չ��.
/// @param hEle  Ԫ�ؾ��.
/// @param id ��ID.
/// @return  ���չ������TRUE,�����෴.
BOOL WINAPI XTree_IsExpand(HELE hEle, int id) //�ж�ָ�����Ƿ�չ��
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return pNode->bExpand;
	return FALSE;
}

/// @brief ɾ����.
/// @param hEle  Ԫ�ؾ��.
/// @param id Ҫɾ������ID.
void WINAPI XTree_DeleteItem(HELE hEle, int id) //ɾ��һ����
{
	IsTreeDebug(hEle, __FUNCTION__);
	tree_ *pObj = TREE(hEle);

	treeNode_ *pNode = Tree_GetTreeNode(hEle, pObj->pRoot, id);
	if (pNode)
	{
		if (pNode == pObj->pCurrItem)
		{
			pObj->pCurrItem = NULL;
		}
		if (NULL == pNode->pParent) //�Ǹ����
		{
			if (pObj->pRoot == pNode)  //���ڵ�ĵ�һ�����
			{
				pObj->pRoot = pNode->pLeft;
				if (pObj->pRoot)
					pObj->pRoot->pBrother = NULL;
				pObj->pEnd = NULL;
			}
			else if (NULL == pNode->pLeft) //�����ĩβ���
			{
				pNode->pBrother->pLeft = NULL;
				if (pNode->pBrother)
					pObj->pEnd = pNode->pBrother;
				else
					pObj->pEnd = NULL;
			}
			else //������м���
			{
				pNode->pBrother->pLeft = pNode->pLeft;
				pNode->pLeft->pBrother = pNode->pBrother;
			}
		}
		else if (pNode->pParent->pRight == pNode)  //�����ĵ�һ���ӽ��
		{
			if (pNode->pLeft)
			{
				pNode->pParent->pRight = pNode->pLeft;
				pNode->pParent->pRight->pBrother = NULL;
			}
			else
			{
				pNode->pParent->pRight = NULL;
				pNode->pParent->pEnd = NULL;
			}
		}
		else if (NULL == pNode->pLeft)  //���ڵ��ĩβ���
		{
			pNode->pBrother->pLeft = NULL;
			if (pNode->pParent)
				pNode->pParent->pEnd = pNode->pBrother;
			else
				pNode->pBrother = NULL;
		}
		else //���ڵ���м���
		{
			pNode->pBrother->pLeft = pNode->pLeft;
			pNode->pLeft->pBrother = pNode->pBrother;
		}
		Tree_DeleteNode(pNode->pRight); //ɾ������

		//ɾ������
		if (pNode->hString)
			XStr_Destroy(pNode->hString);

		if (pNode->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pNode->hArrayBindEle);
			for (int i = 0; i < bindEleCount; i++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pNode->hArrayBindEle, i);
				if (pBindEle->hEle)
					XEle_Destroy(pBindEle->hEle);
				free(pBindEle);
			}
			XArray_Destroy(pNode->hArrayBindEle);
		}

		free(pNode);

		pObj->bAdjust = TRUE;
	}
}

/// @brief �����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XTree_DeleteAllItems(HELE hEle) //�����
{
	IsTreeDebug(hEle, __FUNCTION__);
	while (TREE(hEle)->pRoot)
	{
		XTree_DeleteItem(hEle, TREE(hEle)->pRoot->id);
	}
	TREE(hEle)->pRoot = NULL;
	TREE(hEle)->pCurrItem = NULL;
	TREE(hEle)->pEnd = NULL;
}

/// @brief �������������λ��,�����������ID.
/// @param hEle  Ԫ�ؾ��.
/// @param pPt  ����λ��
/// @return �������ID.
int WINAPI XTree_HitTest(HELE hEle, POINT *pPt)
{
	IsTreeDebug(hEle, __FUNCTION__);

	POINT pt = *pPt;
	pt.x -= XSView_GetHViewPos(hEle);
	pt.y -= XSView_GetVViewPos(hEle);
	treeNode_ *pNode = Tree_HitTestNode(hEle, TREE(hEle)->pRoot, &pt);
	if (pNode)
		return pNode->id;
	return -1;
}

/// @brief �����û��Ի�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pFunDrawItem  �Ի溯����.��������:
/// @code  void CALLBACK Tree_DrawItem(HELE hEle,tree_drewItem_ *pDrawItem); @endcode
void WINAPI XTree_SetUserDrawItem(HELE hEle, pFunTree_DrawItem pFunDrawItem) //�����û��Ի���
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
	TREE(hEle)->pClass_Fun_Info = NULL;
#endif
}

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
void WINAPI XTree_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //�����û��Ի���
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->pDrawItem = (pFunTree_DrawItem)pCallBackFun;
	TREE(hEle)->pClass_Fun_Info = pClass_Fun_Info;
}
#endif

/// @brief ���û�رո�ѡ����.
/// @param hEle  Ԫ�ؾ��.
/// @param bEnable ֵΪTRUE����,�����෴.
void WINAPI XTree_EnableCheckBox(HELE hEle, BOOL bEnable) //���ø�ѡ��
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bCheck = bEnable;
}

/// @brief �ж�����ĸ�ѡ���Ƿ�ѡ��.
/// @param hEle  Ԫ�ؾ��.
/// @param id  ��ID.
/// @return ���TRUE��ĸ�ѡ��ѡ��,�����෴.
BOOL WINAPI XTree_IsItemCheck(HELE hEle, int id) //�ж���ĸ�ѡ���Ƿ�ѡ
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		return pNode->bCheck;
	}
	else
	{
		XTRACE("XTree_IsItemCheck() ����\n");
		return FALSE;
	}
}

/// @brief ������ĸ�ѡ��.
/// @param hEle  Ԫ�ؾ��.
/// @param id  ��ID.
/// @param bCheck ֵΪTRUE�ѡ��ѡ��,�����෴.
void WINAPI XTree_SetItemCheck(HELE hEle, int id, BOOL bCheck) //������ĸ�ѡ��
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		pNode->bCheck = bCheck;
	}
	else
	{
		XTRACE("XTree_IsItemCheck() ����\n");
	}
}

BOOL Tree_InsertItem1(HELE hEle, treeNode_ *pNode)  //���ڵ�
{
	TREE(hEle)->pRoot = pNode;
	return TRUE;
}

BOOL Tree_InsertItem2(HELE hEle, treeNode_ *pNode, int insertAfter)  //���ڵ���ֵܽڵ�
{
	tree_ *pTree = TREE(hEle);

	if (XTREE_INSERT_LAST == insertAfter) //���
	{
		treeNode_ *pN = pTree->pRoot;
		treeNode_ *pEnd = NULL;  //��ǰ��ĩβ�ڵ�
		while (pN)
		{
			pEnd = pN;
			pN = pN->pLeft;
		}
		pNode->pBrother = pEnd;  //���ֽڵ�
		pEnd->pLeft = pNode;

		pTree->pEnd = pNode;
	}
	else if (XTREE_INSERT_BEGIN == insertAfter) //��ǰ
	{
		pNode->pLeft = pTree->pRoot;
		pTree->pRoot = pNode;
		pTree->pRoot->pBrother = pNode;
	}
	else  //ָ����ID����
	{
		treeNode_ *pN = pTree->pRoot;//Ҫ����λ�ýڵ�
		while (pN)
		{
			if (pN->id == insertAfter)
			{
				break;
			}
			else
				pN = pN->pLeft;
		}

		if (NULL == pN)
			return FALSE;

		if (NULL == pN->pLeft)
		{
			pN->pLeft = pNode;
			pNode->pBrother = pN;
			pTree->pEnd = pNode;
		}
		else
		{
			pNode->pBrother = pN;
			pNode->pLeft = pN->pLeft;

			pN->pLeft = pNode;
		}
	}
	return TRUE;
}

BOOL Tree_InsertItem3(HELE hEle, treeNode_ *pNode, int parentId, int insertAfter)
{
	tree_ *pTree = TREE(hEle);

	treeNode_ *pParent = Tree_GetTreeNode(hEle, pTree->pRoot, parentId); //���ڵ�
	if (NULL == pParent)
		return FALSE;

	if (XTREE_INSERT_LAST == insertAfter)  //���
	{
		pNode->pParent = pParent;
		pNode->depth = pParent->depth + 1;

		//���Ҹø��ڵ������һ���ֵܽڵ�
		treeNode_ *pN = pParent->pRight;
		if (NULL == pN)  //û���ӽڵ�
		{
			pParent->pRight = pNode;
		}
		else  //��ǰ��ĩβ�ڵ�
		{
			treeNode_ *pEnd = NULL;  //��ǰ
			while (pN)
			{
				pEnd = pN;
				pN = pN->pLeft;
			}
			pEnd->pLeft = pNode;
			pNode->pBrother = pEnd;
		}
		pNode->pParent->pEnd = pNode;
	}
	else if (XTREE_INSERT_BEGIN == insertAfter) //��ʼ
	{
		treeNode_ *pBegin = pParent->pRight;
		pParent->pRight = pNode;
		pNode->pParent = pParent;
		pNode->pLeft = pBegin;
		pNode->depth = pBegin->depth;
		pNode->pEnd = pBegin->pEnd;
		pBegin->pBrother = pNode;
	}
	else //ָ�������
	{
		treeNode_ *pBegin = pParent->pRight;
		treeNode_ *pN = pParent->pRight;
		while (pN)
		{
			if (insertAfter == pN->id)
			{
				break;
			}
			pN = pN->pLeft;
		}

		if (NULL == pN)
			return FALSE;

		pNode->depth = pBegin->depth;
		if (NULL == pN->pLeft)
		{
			pN->pLeft = pNode;
			pNode->pBrother = pN;
			//pBegin->pEnd=pNode;
			pParent->pEnd = pNode;
		}
		else
		{
			pNode->pBrother = pN;
			pNode->pLeft = pN->pLeft;
			pN->pLeft = pNode;
		}
	}
	return TRUE;
}

treeNode_* Tree_GetTreeNode(HELE hEle, treeNode_ *pNode, int nodeId) //��ȡָ��ID���
{
	tree_ *pTree = TREE(hEle);
	if (NULL != pNode)
	{
		if (nodeId == pNode->id)
		{
			return pNode;
		}

		treeNode_ *pN = NULL;
		pN = Tree_GetTreeNode(hEle, pNode->pLeft, nodeId);
		if (pN) return pN;
		pN = Tree_GetTreeNode(hEle, pNode->pRight, nodeId);
		if (pN) return pN;
	}
	return NULL;
}

void Tree_AdjustTree(HELE hEle) //������
{
	TREE(hEle)->bAdjust = FALSE;

	int heights = TREE(hEle)->spacingTop;  //�ܸ߶�
	int widths = 0; //�ܿ��
	Tree_TraversalAdjustTree(hEle, TREE(hEle)->pRoot, TREE(hEle)->spacingLeft, &heights, &widths, TRUE);
	XSView_SetSize(hEle, widths, heights);
}

void Tree_TraversalAdjustTree(HELE hEle, treeNode_ *pNode, int x, int *pHeights, int *pWidths, BOOL bExpand) //����������
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return;

	if (pNode->hArrayBindEle) //��Ԫ����ʾ������
	{
		int bindCount = XArray_GetCount(pNode->hArrayBindEle);
		for (int i = 0; i < bindCount; i++)
		{
			itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pNode->hArrayBindEle, i);

			if (NULL == pNode->pParent || pNode->pParent->bExpand)
				XEle_ShowEle(pBindEle->hEle, TRUE);
			else
				XEle_ShowEle(pBindEle->hEle, FALSE);
		}
	}

	if ((NULL == pNode->pParent || pNode->pParent->bExpand) && bExpand)
	{
		int left = 0;
		if (pTree->bRootLine)
		{
			left = x + pNode->depth*pTree->indentation;
			pNode->x = left;

			if (pTree->bButton || pTree->bLine)
			{
				if (pTree->bButton) //��ť����
				{
					if (pNode->pRight)
					{
						pNode->rcButton.left = left;
						pNode->rcButton.top = *pHeights + pTree->itemHeight / 2 - pTree->expandSize / 2;
						pNode->rcButton.right = left + pTree->expandSize;
						pNode->rcButton.bottom = pNode->rcButton.top + pTree->expandSize;
					}
				}

				left = left + pTree->expandSize + XTREE_H_LINE_LENGTH;
			}
		}
		else
		{
			if (NULL == pNode->pParent)
			{
				left = x + pNode->depth*pTree->indentation;
				pNode->x = left;
			}
			else
			{
				left = x + (pNode->depth*pTree->indentation) - (pTree->expandSize + XTREE_H_LINE_LENGTH);
				pNode->x = left;
				if (pTree->bButton && pNode->pRight)
				{
					pNode->rcButton.left = left;
					pNode->rcButton.top = *pHeights + pTree->itemHeight / 2 - pTree->expandSize / 2;
					pNode->rcButton.right = left + pTree->expandSize;
					pNode->rcButton.bottom = pNode->rcButton.top + pTree->expandSize;
				}
				left = left + pTree->expandSize + XTREE_H_LINE_LENGTH;
			}
		}

		//��Ԫ��
		if (pNode->hArrayBindEle)
		{
			int posx = XSView_GetHViewPos(hEle);
			int posy = XSView_GetVViewPos(hEle);

			int bindCount = XArray_GetCount(pNode->hArrayBindEle);
			for (int i = 0; i < bindCount; i++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pNode->hArrayBindEle, i);
				((ele_*)pBindEle->hEle)->rect.left = left + pBindEle->left + posx;
				((ele_*)pBindEle->hEle)->rect.top = *pHeights + pBindEle->top + posy;
				((ele_*)pBindEle->hEle)->rect.right = ((ele_*)pBindEle->hEle)->rect.left + pBindEle->width;
				((ele_*)pBindEle->hEle)->rect.bottom = ((ele_*)pBindEle->hEle)->rect.top + pBindEle->height;
				((ele_*)pBindEle->hEle)->elePt.x = left + pBindEle->left;
				((ele_*)pBindEle->hEle)->elePt.y = *pHeights + pBindEle->top;
			}
		}

		//��ѡ������
		if (pTree->bCheck)
		{
			pNode->rcCheck.left = left;
			pNode->rcCheck.top = *pHeights;
			pNode->rcCheck.right = left + XTREE_CHECK_SIZE;
			pNode->rcCheck.bottom = pNode->rcCheck.top + pTree->itemHeight;

			left += XTREE_CHECK_SIZE;
		}

		//ͼƬ����
		if (pTree->hImageList)
		{
			int cy = XImageList_GetHeight(pTree->hImageList);
			int cx = XImageList_GetWidth(pTree->hImageList);
			pNode->rcImage.left = left;
			pNode->rcImage.top = *pHeights + pTree->itemHeight / 2 - cy / 2;
			pNode->rcImage.right = pNode->rcImage.left + cx;
			pNode->rcImage.bottom = pNode->rcImage.top + cy;

			left = pNode->rcImage.right + 5;
		}

		//�ı�����
		pNode->rcText.left = left + 3;
		pNode->rcText.top = *pHeights;
		pNode->rcText.right = pNode->rcText.left + pNode->textWidth;
		pNode->rcText.bottom = pNode->rcText.top + pTree->itemHeight;

		//���������
		pNode->y = *pHeights;

		if (pNode->rcText.right > (*pWidths))
			*pWidths = pNode->rcText.right;

		*pHeights += pTree->itemHeight;

		Tree_TraversalAdjustTree(hEle, pNode->pRight, x, pHeights, pWidths, TRUE);
		Tree_TraversalAdjustTree(hEle, pNode->pLeft, x, pHeights, pWidths, TRUE);
	}
	else
	{
		Tree_TraversalAdjustTree(hEle, pNode->pRight, x, pHeights, pWidths, FALSE);
		Tree_TraversalAdjustTree(hEle, pNode->pLeft, x, pHeights, pWidths, FALSE);
	}
}

void Tree_DrawItem(HELE hEle, HDRAW hDraw, treeNode_ *pNode)
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return;

	if (NULL == pNode->pParent || pNode->pParent->bExpand)
	{
		if (STATE_SELECT == pNode->state) //����ѡ����
		{
			if (pTree->bLine)
			{
				if (XEle_IsFocus(hEle))
					XDraw_FillSolidRect_(hDraw, &pNode->rcText, RGB(126, 206, 244));//49,106,197));
				else
					XDraw_FillSolidRect_(hDraw, &pNode->rcText, RGB(192, 232, 250));
			}
			else
			{
				RECT rcSel;
				rcSel.left = 3;//pTree->spacingLeft;
				rcSel.top = pNode->y;
				int right = XSView_GetViewWidth(hEle) - XSView_GetHViewPos(hEle);//XSView_GetHSizeTotalAccurate(hEle)
				rcSel.right = right - 1;
				rcSel.bottom = pNode->y + pTree->itemHeight;

				if (XEle_IsFocus(hEle))
					XDraw_FillSolidRect_(hDraw, &rcSel, RGB(192, 232, 250));
				else
					XDraw_FillSolidRect_(hDraw, &rcSel, RGB(126, 206, 244));
			}
		}
		int left = pNode->x;

		//����������
		if (pTree->bLine)
		{
			if (pNode->pRight && pNode->bExpand)
			{
				int top = pNode->y + pTree->itemHeight / 2;
				int bottom = pNode->pEnd->y + pTree->itemHeight / 2;
				XDraw_Dottedline_(hDraw, pNode->pEnd->x + pTree->expandSize / 2, top, bottom - top, RGB(0, 0, 0), FALSE);
			}

			if (NULL == pNode->pParent)
			{
				if (pTree->bRootLine)
				{
					XDraw_Dottedline_(hDraw, pNode->x + pTree->expandSize / 2, pNode->y + pTree->itemHeight / 2, pTree->expandSize / 2 + XTREE_H_LINE_LENGTH, RGB(0, 0, 0));
				}

				if (pTree->bRootLine && pTree->pRoot == pNode)
				{
					if (pTree->pEnd)
					{
						int top = pTree->pRoot->y + pTree->itemHeight / 2;
						int bottom = pTree->pEnd->y + pTree->itemHeight / 2;
						XDraw_Dottedline_(hDraw, pTree->pRoot->x + pTree->expandSize / 2, top, bottom - top, RGB(0, 0, 0), FALSE);
					}
				}
			}
			else
			{
				XDraw_Dottedline_(hDraw, pNode->x + pTree->expandSize / 2, pNode->y + pTree->itemHeight / 2, pTree->expandSize / 2 + XTREE_H_LINE_LENGTH, RGB(0, 0, 0));
			}
		}

		//����չ����ť
		if (pTree->bButton &&pNode->pRight)
		{
			if (NULL == pNode->pParent)
			{
				if (pTree->bRootLine)
				{
					HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
					XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(200, 200, 200), &pNode->rcButton, 1);
					XDraw_FrameRect_(hDraw, &pNode->rcButton, hBrush);

					XDraw_MoveToEx_(hDraw, pNode->rcButton.left + 2, pNode->rcButton.top + pTree->expandSize / 2, 0);
					XDraw_LineTo_(hDraw, pNode->rcButton.right - 2, pNode->rcButton.top + pTree->expandSize / 2);
					if (FALSE == pNode->bExpand) //����
					{
						XDraw_MoveToEx_(hDraw, pNode->rcButton.left + pTree->expandSize / 2, pNode->rcButton.top + 2, 0);
						XDraw_LineTo_(hDraw, pNode->rcButton.left + pTree->expandSize / 2, pNode->rcButton.bottom - 2);
					}
				}
			}
			else
			{
				HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
				XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(200, 200, 200), &pNode->rcButton, 1);
				XDraw_FrameRect_(hDraw, &pNode->rcButton, hBrush);

				XDraw_MoveToEx_(hDraw, pNode->rcButton.left + 2, pNode->rcButton.top + pTree->expandSize / 2, 0);
				XDraw_LineTo_(hDraw, pNode->rcButton.right - 2, pNode->rcButton.top + pTree->expandSize / 2);
				if (FALSE == pNode->bExpand) //����
				{
					XDraw_MoveToEx_(hDraw, pNode->rcButton.left + pTree->expandSize / 2, pNode->rcButton.top + 2, 0);
					XDraw_LineTo_(hDraw, pNode->rcButton.left + pTree->expandSize / 2, pNode->rcButton.bottom - 2);
				}
				//	DeleteObject(hBrush);
			}
		}

		//���Ƹ�ѡ��
		if (pTree->bCheck)
		{
			int top = pNode->rcCheck.top + pTree->itemHeight / 2 - 6 - 1;
			XDraw_Check_(hDraw, pNode->rcCheck.left, top, RGB(80, 80, 80), pNode->bCheck);
		}
		//����ͼƬ
		if (pTree->hImageList)
		{
			if (STATE_SELECT == pNode->state && -1 != pNode->selectImageId)
				XImageList_DrawImage(pTree->hImageList, hDraw, pNode->selectImageId, pNode->rcImage.left, pNode->rcImage.top);
			else
				XImageList_DrawImage(pTree->hImageList, hDraw, pNode->imageId, pNode->rcImage.left, pNode->rcImage.top);
		}

		//�����ı�
		wchar_t *pText = XStr_GetBuffer(pNode->hString);
		if (pText)
			XDraw_DrawText_(hDraw, pText, XStr_GetLength(pNode->hString), &pNode->rcText, DT_SINGLELINE | DT_VCENTER);

		XDraw_RestoreGDIOBJ_(hDraw);
		Tree_DrawItem(hEle, hDraw, pNode->pRight);
		Tree_DrawItem(hEle, hDraw, pNode->pLeft);
	}
}

void Tree_UserDrawItem(HELE hEle, HDRAW hDraw, treeNode_ *pNode)
{
	if (NULL == pNode)
		return;

	if (NULL == pNode->pParent || pNode->pParent->bExpand)
	{
		tree_drewItem_  drawItem;
		drawItem.hDraw = hDraw;
		drawItem.id = pNode->id;
		drawItem.imageId = pNode->imageId;
		drawItem.state = 0;
		drawItem.bExpand = pNode->bExpand;
		drawItem.rcButton = pNode->rcButton;
		drawItem.rcImage = pNode->rcImage;
		drawItem.rcText = pNode->rcText;

		if (pNode->hString)
			drawItem.pText = XStr_GetBuffer(pNode->hString);
		else
			drawItem.pText = NULL;

		if (TREE(hEle)->pCurrItem == pNode)
			drawItem.state = STATE_SELECT;
		else
			drawItem.state = STATE_LEAVE;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (TREE(hEle)->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)&drawItem;
			event_.lParam = NULL;
			event_.pClass_fun = TREE(hEle)->pClass_Fun_Info;
			((pFunClassEventMsg)TREE(hEle)->pDrawItem)(&event_, xc_fun_v_e_tree);
		}
		else
		{
			TREE(hEle)->pDrawItem(hEle, &drawItem);
		}
#else
		TREE(hEle)->pDrawItem(hEle, &drawItem);
#endif
		XDraw_RestoreGDIOBJ_(hDraw);
		Tree_UserDrawItem(hEle, hDraw, pNode->pRight);
		Tree_UserDrawItem(hEle, hDraw, pNode->pLeft);
	}
}

//�ص�����:
BOOL CALLBACK Tree_OnDrawScrollView(HELE hEle, HDRAW hDraw)
{
	if (TREE(hEle)->bAdjust)
	{
		Tree_AdjustTree(hEle);
	}
	/////////////////////////////////////////

	if (TREE(hEle)->pDrawItem)
	{
		Tree_UserDrawItem(hEle, hDraw, TREE(hEle)->pRoot);
	}
	else
		Tree_DrawItem(hEle, hDraw, TREE(hEle)->pRoot);

	return TRUE;
}

BOOL CALLBACK Tree_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	tree_ *pTree = TREE(hEle);

	POINT pt = { pPt->x, pPt->y };
	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (PtInRect(&rect, pt))
	{
		int posx = XSView_GetHViewPos(hEle);
		int posy = XSView_GetVViewPos(hEle);
		pt.x = pt.x + (-posx);
		pt.y = pt.y + (-posy);

		if (FALSE == Tree_TestClick(hEle, pTree->pRoot, &pt))
		{
			if (pTree->pCurrItem)
			{
				BOOL bChange = FALSE;
				Ele_SendEvent(hEle, XE_TREE_SELECT_ING, -1, (LPARAM)&bChange);
				if (!bChange)
				{
					pTree->pCurrItem->state = 0;
					pTree->pCurrItem = NULL;
					Ele_SendEvent(hEle, XE_TREE_SELECT, -1, 0);
					XEle_RedrawEle(hEle);
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK Tree_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	tree_ *pTree = TREE(hEle);

	POINT pt = { pPt->x, pPt->y };
	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (PtInRect(&rect, pt))
	{
		int posx = XSView_GetHViewPos(hEle);
		int posy = XSView_GetVViewPos(hEle);
		pt.x = pt.x + (-posx);
		pt.y = pt.y + (-posy);

		if (FALSE == Tree_TestClick(hEle, pTree->pRoot, &pt))
		{
			if (pTree->pCurrItem)
			{
				BOOL bChange = FALSE;
				Ele_SendEvent(hEle, XE_TREE_SELECT_ING, -1, (LPARAM)&bChange);
				if (!bChange)
				{
					pTree->pCurrItem->state = 0;
					pTree->pCurrItem = NULL;
					Ele_SendEvent(hEle, XE_TREE_SELECT, -1, 0);
					XEle_RedrawEle(hEle);
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK Tree_OnMouseDBClick(HELE hEle, POINT *pPt)
{
	POINT pt = { pPt->x, pPt->y };
	RECT rect;
	XSView_GetViewRect(hEle, &rect);
	if (PtInRect(&rect, pt))
	{
		int posx = XSView_GetHViewPos(hEle);
		int posy = XSView_GetVViewPos(hEle);
		pt.x = pt.x + (-posx);
		pt.y = pt.y + (-posy);

		Tree_TextDBClick(hEle, TREE(hEle)->pRoot, &pt);
	}
	return FALSE;
}

BOOL Tree_TestClick(HELE hEle, treeNode_ *pNode, POINT *pPt)  //�������������
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return FALSE;


	pNode = Tree_HitTestNode(hEle, pNode, pPt);//���������λ��
	if (pNode)
	{
		//������ڰ�ť��չ��������
		if (pTree->bButton)
		{
			if (NULL == pNode->pParent)
			{
				if (pTree->bRootLine)
				{
					if (PtInRect(&pNode->rcButton, *pPt))
					{
						if (pNode->pRight)  //��Ҫ��������
						{
							if (pNode->bExpand)
								pNode->bExpand = FALSE;
							else
								pNode->bExpand = TRUE;

							pTree->bAdjust = TRUE; //����������ͼ��С
							XEle_RedrawEle(hEle);
						}
						//���Ͱ�ť���չ�������¼�...
						if (pNode->bExpand)
							Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, TRUE);
						else
							Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, FALSE);
						return TRUE;
					}
				}
			}
			else
			{
				if (PtInRect(&pNode->rcButton, *pPt))
				{
					if (pNode->pRight)  //��Ҫ��������
					{
						if (pNode->bExpand)
							pNode->bExpand = FALSE;
						else
							pNode->bExpand = TRUE;

						pTree->bAdjust = TRUE; //����������ͼ��С
						//RedrawEle();
						XEle_RedrawEle(hEle);
					}
					//������:���Ͱ�ť���չ�������¼�...
					if (pNode->bExpand)
						Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, TRUE);
					else
						Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, FALSE);
					return TRUE;
				}
			}
		}

		if (pTree->bCheck)//��ѡ��
		{
			if (PtInRect(&pNode->rcCheck, *pPt))
			{
				pNode->bCheck = pNode->bCheck ? FALSE : TRUE;
				XEle_RedrawEle(hEle);
				return TRUE;
			}
		}
		if (pTree->pCurrItem != pNode)
		{
			BOOL bChange = FALSE;
			Ele_SendEvent(hEle, XE_TREE_SELECT_ING, pNode->id, (LPARAM)&bChange);
			if (!bChange)
			{
				if (pTree->pCurrItem) //ѡ����
					pTree->pCurrItem->state = 0;
				pTree->pCurrItem = pNode;
				pTree->pCurrItem->state = STATE_SELECT;
				//������ѡ���¼�...
				Ele_SendEvent(hEle, XE_TREE_SELECT, pTree->pCurrItem->id, 0);
				XEle_RedrawEle(hEle);
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL Tree_TextDBClick(HELE hEle, treeNode_ *pNode, POINT *pPt) //�����������˫��
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return FALSE;

	pNode = Tree_HitTestNode(hEle, pNode, pPt);
	if (pNode)
	{
		//����չ����ť�� ����
		if (pTree->bButton)
		{
			if (NULL == pNode->pParent)
			{
				if (pTree->bRootLine)
				{
					if (PtInRect(&pNode->rcButton, *pPt))
						return TRUE;
				}
			}
			else
			{
				if (PtInRect(&pNode->rcButton, *pPt))
					return TRUE;
			}
		}
		//չ��������
		if (pNode->bExpand)
			pNode->bExpand = FALSE;
		else
			pNode->bExpand = TRUE;

		if (pNode->pRight) //������ ��Ҫ�ػ�
		{
			pTree->bAdjust = TRUE;
			XEle_RedrawEle(hEle);

			//�������չ���¼�
			if (pNode->bExpand)
				Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, TRUE);
			else
				Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

treeNode_ *Tree_HitTestNode(HELE hEle, treeNode_ *pNode, POINT *pPt)  //���Ե��λ��,������ID
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return NULL;
	if (NULL == pNode->pParent || pNode->pParent->bExpand)
	{
		if (pPt->y > pNode->y && pPt->y < (pNode->y + pTree->itemHeight))
		{
			return pNode;
		}
		treeNode_ *res;
		res = Tree_HitTestNode(hEle, pNode->pRight, pPt);
		if (res) return res;
		res = Tree_HitTestNode(hEle, pNode->pLeft, pPt);
		if (res) return res;
	}
	return NULL;
}

void Tree_DeleteNode(treeNode_ *pNode) //����ɾ�����,��������
{
	if (NULL != pNode)
	{
		Tree_DeleteNode(pNode->pRight);
		Tree_DeleteNode(pNode->pLeft);

		//ɾ�����
		if (pNode->hString)
			XStr_Destroy(pNode->hString);

		if (pNode->hArrayBindEle)
		{
			int bindEleCount = XArray_GetCount(pNode->hArrayBindEle);
			for (int i = 0; i < bindEleCount; i++)
			{
				itemBindEle_ *pBindEle = (itemBindEle_*)XArray_GetAt(pNode->hArrayBindEle, i);
				free(pBindEle);
			}
			XArray_Destroy(pNode->hArrayBindEle);
		}

		free(pNode);
	}
}

BOOL CALLBACK Tree_OnEventSetFocus(HELE hEle, HELE hEventEle)  //��ý���
{
	if (hEle != hEventEle)
		return FALSE;

	XEle_RedrawEle(hEle);
	return TRUE;
}

BOOL CALLBACK Tree_OnEventKillFocus(HELE hEle, HELE hEventEle) //ʧȥ����
{
	if (hEle != hEventEle)
		return FALSE;

	XEle_RedrawEle(hEle);
	return TRUE;
}

///@}