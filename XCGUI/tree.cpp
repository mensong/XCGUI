/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup tree 列表树元素(Tree)
/// @ingroup groupElements
/// @{

/// @brief 创建树元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
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

	MessageBox(NULL, L"Tree_ 树元素分配ID出现错误!", L"炫彩界面库提示", 0);
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

void CALLBACK Tree_OnDestroy(HELE hEle)  //销毁
{
	XTree_DeleteAllItems(hEle);
	if (TREE(hEle)->hImageList)
		XImageList_Destroy(TREE(hEle)->hImageList);

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	if (TREE(hEle)->pClass_Fun_Info)
		free(TREE(hEle)->pClass_Fun_Info);
#endif
}

/// @brief 创建树元素.
/// @param hEle   元素句柄.
/// @param pText  文本内容.
/// @param parentId   父项ID.
/// @param imageId     图标索引ID.
/// @param selectImageId  选择状态图标索引ID.
/// @param insertAfter 插入位置标识,或者是插入指定项后面,项的id号,XTREE_INSERT_BEGIN:插入当前层开始,XTREE_INSERT_LAST:插入当前层末尾.
/// @param bExpand 是否展开.
/// @return 返回插入项的ID.
int WINAPI XTree_InsertItem(HELE hEle, wchar_t *pText, int parentId, int imageId, int selectImageId, int insertAfter, BOOL bExpand) //插入项
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

	//文本宽度
	HDC hdc = ::GetDC(NULL);
	HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
	SIZE size;
	GetTextExtentPoint32(hdc, XStr_GetBuffer(pNode->hString), XStr_GetLength(pNode->hString), &size);
	pNode->textWidth = size.cx;
	SelectObject(hdc, hOldFont);
	::ReleaseDC(NULL, hdc);

	//pTree->uid++;

	if (NULL == pTree->pRoot)  //根节点
	{
		if (FALSE == Tree_InsertItem1(hEle, pNode))
		{
			XStr_Destroy(pNode->hString);
			free(pNode);
			return -1;
		}
		return pNode->id;
	}
	else if (XTREE_ROOT == parentId)  //根节点的兄弟节点
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

/// @brief 启用项前面的展开收缩按钮.
/// @param hEle   元素句柄.
/// @param bEnable  TRUE启用,否则相反.
void WINAPI XTree_EnableButton(HELE hEle, BOOL bEnable)   //显示按钮
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bButton = bEnable;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 启用连接虚线.
/// @param hEle   元素句柄.
/// @param bEnable  TRUE启用,否则相反.
void WINAPI XTree_EnableLine(HELE hEle, BOOL bEnable)    //显示连接虚线
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bLine = bEnable;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 启用根部显示连接虚线.
/// @param hEle   元素句柄.
/// @param bEnable  TRUE启用,否则相反.
void WINAPI XTree_EnableRootLine(HELE hEle, BOOL bEnable)  //启用连接根部的线
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bRootLine = bEnable;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 判断是否启用了项展开收缩按钮.
/// @param hEle   元素句柄.
/// @return 如果是返回TRUE,否则相反.
BOOL WINAPI XTree_IsButton(HELE hEle)
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->bButton;
}

/// @brief 判断是否启用了连接虚线.
/// @param hEle   元素句柄.
/// @return 如果是返回TRUE,否则相反.
BOOL WINAPI XTree_IsLine(HELE hEle)
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->bLine;
}

/// @brief 判断是否启用了根部连接虚线.
/// @param hEle   元素句柄.
/// @return 如果是返回TRUE,否则相反.
BOOL WINAPI XTree_IsRootLine(HELE hEle)
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->bRootLine;
}

/// @brief 设置树左间距.
/// @param hEle  元素句柄.
/// @param left  间距大小.
void WINAPI XTree_SetSpacingLeft(HELE hEle, int left)   //设置左间隔
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->spacingLeft = left;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 设置树上间距.
/// @param hEle  元素句柄.
/// @param top  上间距大小.
void WINAPI XTree_SetSpacingTop(HELE hEle, int top)     //设置上间隔
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->spacingTop = top;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 设置关联的图标列表资源句柄.
/// @param hEle  元素句柄.
/// @param hImageList  图片列表资源句柄.
void WINAPI XTree_SetImageList(HELE hEle, HXCGUI hImageList) //设置图片列表
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

/// @brief 设置项用户数据.
/// @param hEle  元素句柄.
/// @param id  项ID.
/// @param data 用户数据.
void WINAPI XTree_SetItemData(HELE hEle, int id, int data) //设置用户数据
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		pNode->data = data;
}

/// @brief 设置展开收缩按钮大小.
/// @param hEle  元素句柄.
/// @param size  展开收缩按钮大小.
void WINAPI XTree_SetExpandButtonSize(HELE hEle, int size) //设置展开按钮大小
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->expandSize = size;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 设置子项缩进宽度.
/// @param hEle  元素句柄.
/// @param width  缩进宽度.
void WINAPI XTree_SetIndentation(HELE hEle, int width) //设置子项缩进宽度
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->indentation = width;
	TREE(hEle)->bAdjust = TRUE;
}

/// @brief 设置选择项.
/// @param hEle  元素句柄.
/// @param id  选择项ID.
void WINAPI XTree_SetSelectItem(HELE hEle, int id)  //设置选择项
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

/// @brief 设置项文本内容.
/// @param hEle  元素句柄.
/// @param id  项ID.
/// @param pText 文本内容.
void WINAPI XTree_SetItemText(HELE hEle, int id, wchar_t *pText) //设置项文本
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

/// @brief 设置项图标.
/// @param hEle  元素句柄.
/// @param id  项ID.
/// @param imageId 图标ID.
void WINAPI XTree_SetItemImage(HELE hEle, int id, int imageId)  //设置项图片
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		pNode->imageId = imageId;
}

/// @brief 设置项高度.
/// @param hEle  元素句柄.
/// @param height 项高度.
void WINAPI XTree_SetItemHeight(HELE hEle, int height) //设置项高度
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->itemHeight = height;
	XSView_SetScrollSize(hEle, 10, height);
}

/// @brief 设置项绑定元素.
/// @param hEle   元素句柄.
/// @param id       项ID.
/// @param pInfo    绑定元素信息
/// @return 成功返回TRUE,否则相反.
BOOL WINAPI XTree_SetItemBindEle(HELE hEle, int id, itemBindEle_ *pInfo) //绑定元素
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

/// @brief 获取项用户数据.
/// @param hEle  元素句柄.
/// @param id    项ID.
/// @return 用户数据.
int WINAPI XTree_GetItemData(HELE hEle, int id) //获取用户数据
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		return pNode->data;
	}
	return -1;
}

/// @brief 获取项高度.
/// @param hEle  元素句柄.
/// @return 项高度.
int WINAPI XTree_GetItemHeight(HELE hEle)     //获取项高度
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->itemHeight;
}

/// @brief 获取当前选择的项.
/// @param hEle  元素句柄.
/// @return 当前选择的项ID.
int WINAPI XTree_GetSelectItem(HELE hEle) //获取当前选择的项
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (TREE(hEle)->pCurrItem)
		return TREE(hEle)->pCurrItem->id;
	return -1;
}

/// @brief 获取指定项的父项ID.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 父项ID.
int WINAPI XTree_GetParentItem(HELE hEle, int id)  //获取指定项的父项
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pParent)
	{
		return pNode->pParent->id;
	}

	return -1;
}

/// @brief 获取指定项的子项.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 子项ID.
int WINAPI XTree_GetChildItem(HELE hEle, int id)  //获取指定项的子项
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pRight)
		return pNode->pRight->id;

	return -1;
}

/// @brief 获取指定项的下一个兄弟项.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 兄弟项ID.
int WINAPI XTree_GetNextSiblingItem(HELE hEle, int id) //获取指定项的下一个兄弟项
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pLeft)
		return pNode->pLeft->id;

	return -1;
}

/// @brief 获取指定项的上一个兄弟项.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 兄弟项ID.
int WINAPI XTree_GetPrevSiblingItem(HELE hEle, int id) //获取指定项的上一个兄弟项
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode && pNode->pBrother)
		return pNode->pBrother->id;

	return -1;
}

/// @brief 获取第一个项,也就是根项.
/// @param hEle  元素句柄.
/// @return 项ID.
int WINAPI XTree_GetFirstItem(HELE hEle) //获取第一个节点
{
	IsTreeDebug(hEle, __FUNCTION__);
	if (TREE(hEle)->pRoot)
		return TREE(hEle)->pRoot->id;
	return -1;
}

/// @brief 获取项深度.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 返回项在树节点的深度.
int WINAPI XTree_GetItemDepth(HELE hEle, int id) //获取节点深度
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return pNode->depth;
	return -1;
}

/// @brief 获取项图标.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 图标在图片列表中的索引ID.
int WINAPI XTree_GetItemImage(HELE hEle, int id)  //获取项图片
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return pNode->imageId;

	return -1;
}

/// @brief 获取项文本.
/// @param hEle  元素句柄.
/// @param id   项ID.
/// @return 项文本内容.
wchar_t* WINAPI XTree_GetItemText(HELE hEle, int id)   //获取项文本
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return XStr_GetBuffer(pNode->hString);

	return NULL;
}

/// @brief 获取图片列表.
/// @param hEle  元素句柄.
/// @return 图标列表句柄.
HXCGUI WINAPI XTree_GetImageList(HELE hEle) //获取图片列表
{
	IsTreeDebug(hEle, __FUNCTION__);
	return TREE(hEle)->hImageList;
}

/// @brief 展开收缩指定项.
/// @param hEle  元素句柄.
/// @param id 项ID.
/// @param bExpand TRUE展开,否则相反.
void WINAPI XTree_Expand(HELE hEle, int id, BOOL bExpand) //展开收缩指定项
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

/// @brief 判断指定项是否展开.
/// @param hEle  元素句柄.
/// @param id 项ID.
/// @return  如果展开返回TRUE,否则相反.
BOOL WINAPI XTree_IsExpand(HELE hEle, int id) //判断指定项是否展开
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
		return pNode->bExpand;
	return FALSE;
}

/// @brief 删除项.
/// @param hEle  元素句柄.
/// @param id 要删除的项ID.
void WINAPI XTree_DeleteItem(HELE hEle, int id) //删除一个项
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
		if (NULL == pNode->pParent) //是根结点
		{
			if (pObj->pRoot == pNode)  //根节点的第一个结点
			{
				pObj->pRoot = pNode->pLeft;
				if (pObj->pRoot)
					pObj->pRoot->pBrother = NULL;
				pObj->pEnd = NULL;
			}
			else if (NULL == pNode->pLeft) //根结点末尾结点
			{
				pNode->pBrother->pLeft = NULL;
				if (pNode->pBrother)
					pObj->pEnd = pNode->pBrother;
				else
					pObj->pEnd = NULL;
			}
			else //根结点中间结点
			{
				pNode->pBrother->pLeft = pNode->pLeft;
				pNode->pLeft->pBrother = pNode->pBrother;
			}
		}
		else if (pNode->pParent->pRight == pNode)  //父结点的第一个子结点
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
		else if (NULL == pNode->pLeft)  //父节点的末尾结点
		{
			pNode->pBrother->pLeft = NULL;
			if (pNode->pParent)
				pNode->pParent->pEnd = pNode->pBrother;
			else
				pNode->pBrother = NULL;
		}
		else //父节点的中间结点
		{
			pNode->pBrother->pLeft = pNode->pLeft;
			pNode->pLeft->pBrother = pNode->pBrother;
		}
		Tree_DeleteNode(pNode->pRight); //删除子项

		//删除该项
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

/// @brief 清空树.
/// @param hEle  元素句柄.
void WINAPI XTree_DeleteAllItems(HELE hEle) //清空树
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

/// @brief 测试坐标点所在位置,返回所在项的ID.
/// @param hEle  元素句柄.
/// @param pPt  坐标位置
/// @return 所在项的ID.
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

/// @brief 设置用户自绘树项.
/// @param hEle  元素句柄.
/// @param pFunDrawItem  自绘函数名.类型如下:
/// @code  void CALLBACK Tree_DrawItem(HELE hEle,tree_drewItem_ *pDrawItem); @endcode
void WINAPI XTree_SetUserDrawItem(HELE hEle, pFunTree_DrawItem pFunDrawItem) //设置用户自绘项
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->pDrawItem = pFunDrawItem;
#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
	TREE(hEle)->pClass_Fun_Info = NULL;
#endif
}

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
void WINAPI XTree_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //设置用户自绘项
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->pDrawItem = (pFunTree_DrawItem)pCallBackFun;
	TREE(hEle)->pClass_Fun_Info = pClass_Fun_Info;
}
#endif

/// @brief 启用或关闭复选框功能.
/// @param hEle  元素句柄.
/// @param bEnable 值为TRUE启用,否则相反.
void WINAPI XTree_EnableCheckBox(HELE hEle, BOOL bEnable) //启用复选框
{
	IsTreeDebug(hEle, __FUNCTION__);
	TREE(hEle)->bCheck = bEnable;
}

/// @brief 判断树项的复选框是否选中.
/// @param hEle  元素句柄.
/// @param id  项ID.
/// @return 如果TRUE项的复选框选中,否则相反.
BOOL WINAPI XTree_IsItemCheck(HELE hEle, int id) //判断项的复选框是否勾选
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		return pNode->bCheck;
	}
	else
	{
		XTRACE("XTree_IsItemCheck() 错误\n");
		return FALSE;
	}
}

/// @brief 设置项的复选框.
/// @param hEle  元素句柄.
/// @param id  项ID.
/// @param bCheck 值为TRUE项复选框选中,否则相反.
void WINAPI XTree_SetItemCheck(HELE hEle, int id, BOOL bCheck) //设置项的复选框
{
	IsTreeDebug(hEle, __FUNCTION__);
	treeNode_ *pNode = Tree_GetTreeNode(hEle, TREE(hEle)->pRoot, id);
	if (pNode)
	{
		pNode->bCheck = bCheck;
	}
	else
	{
		XTRACE("XTree_IsItemCheck() 错误\n");
	}
}

BOOL Tree_InsertItem1(HELE hEle, treeNode_ *pNode)  //根节点
{
	TREE(hEle)->pRoot = pNode;
	return TRUE;
}

BOOL Tree_InsertItem2(HELE hEle, treeNode_ *pNode, int insertAfter)  //根节点的兄弟节点
{
	tree_ *pTree = TREE(hEle);

	if (XTREE_INSERT_LAST == insertAfter) //最后
	{
		treeNode_ *pN = pTree->pRoot;
		treeNode_ *pEnd = NULL;  //当前层末尾节点
		while (pN)
		{
			pEnd = pN;
			pN = pN->pLeft;
		}
		pNode->pBrother = pEnd;  //长兄节点
		pEnd->pLeft = pNode;

		pTree->pEnd = pNode;
	}
	else if (XTREE_INSERT_BEGIN == insertAfter) //最前
	{
		pNode->pLeft = pTree->pRoot;
		pTree->pRoot = pNode;
		pTree->pRoot->pBrother = pNode;
	}
	else  //指定项ID后面
	{
		treeNode_ *pN = pTree->pRoot;//要插入位置节点
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

	treeNode_ *pParent = Tree_GetTreeNode(hEle, pTree->pRoot, parentId); //父节点
	if (NULL == pParent)
		return FALSE;

	if (XTREE_INSERT_LAST == insertAfter)  //最后
	{
		pNode->pParent = pParent;
		pNode->depth = pParent->depth + 1;

		//查找该父节点下最后一个兄弟节点
		treeNode_ *pN = pParent->pRight;
		if (NULL == pN)  //没有子节点
		{
			pParent->pRight = pNode;
		}
		else  //当前层末尾节点
		{
			treeNode_ *pEnd = NULL;  //当前
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
	else if (XTREE_INSERT_BEGIN == insertAfter) //开始
	{
		treeNode_ *pBegin = pParent->pRight;
		pParent->pRight = pNode;
		pNode->pParent = pParent;
		pNode->pLeft = pBegin;
		pNode->depth = pBegin->depth;
		pNode->pEnd = pBegin->pEnd;
		pBegin->pBrother = pNode;
	}
	else //指定项后面
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

treeNode_* Tree_GetTreeNode(HELE hEle, treeNode_ *pNode, int nodeId) //获取指定ID结点
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

void Tree_AdjustTree(HELE hEle) //调整树
{
	TREE(hEle)->bAdjust = FALSE;

	int heights = TREE(hEle)->spacingTop;  //总高度
	int widths = 0; //总宽度
	Tree_TraversalAdjustTree(hEle, TREE(hEle)->pRoot, TREE(hEle)->spacingLeft, &heights, &widths, TRUE);
	XSView_SetSize(hEle, widths, heights);
}

void Tree_TraversalAdjustTree(HELE hEle, treeNode_ *pNode, int x, int *pHeights, int *pWidths, BOOL bExpand) //遍历调整树
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return;

	if (pNode->hArrayBindEle) //绑定元素显示与隐藏
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
				if (pTree->bButton) //按钮坐标
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

		//绑定元素
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

		//复选框坐标
		if (pTree->bCheck)
		{
			pNode->rcCheck.left = left;
			pNode->rcCheck.top = *pHeights;
			pNode->rcCheck.right = left + XTREE_CHECK_SIZE;
			pNode->rcCheck.bottom = pNode->rcCheck.top + pTree->itemHeight;

			left += XTREE_CHECK_SIZE;
		}

		//图片坐标
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

		//文本坐标
		pNode->rcText.left = left + 3;
		pNode->rcText.top = *pHeights;
		pNode->rcText.right = pNode->rcText.left + pNode->textWidth;
		pNode->rcText.bottom = pNode->rcText.top + pTree->itemHeight;

		//左对齐坐标
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
		if (STATE_SELECT == pNode->state) //绘制选中项
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

		//绘制链接线
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

		//绘制展开按钮
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
					if (FALSE == pNode->bExpand) //收缩
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
				if (FALSE == pNode->bExpand) //收缩
				{
					XDraw_MoveToEx_(hDraw, pNode->rcButton.left + pTree->expandSize / 2, pNode->rcButton.top + 2, 0);
					XDraw_LineTo_(hDraw, pNode->rcButton.left + pTree->expandSize / 2, pNode->rcButton.bottom - 2);
				}
				//	DeleteObject(hBrush);
			}
		}

		//绘制复选框
		if (pTree->bCheck)
		{
			int top = pNode->rcCheck.top + pTree->itemHeight / 2 - 6 - 1;
			XDraw_Check_(hDraw, pNode->rcCheck.left, top, RGB(80, 80, 80), pNode->bCheck);
		}
		//绘制图片
		if (pTree->hImageList)
		{
			if (STATE_SELECT == pNode->state && -1 != pNode->selectImageId)
				XImageList_DrawImage(pTree->hImageList, hDraw, pNode->selectImageId, pNode->rcImage.left, pNode->rcImage.top);
			else
				XImageList_DrawImage(pTree->hImageList, hDraw, pNode->imageId, pNode->rcImage.left, pNode->rcImage.top);
		}

		//绘制文本
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

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
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

//回调函数:
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

BOOL Tree_TestClick(HELE hEle, treeNode_ *pNode, POINT *pPt)  //遍历测试鼠标点击
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return FALSE;


	pNode = Tree_HitTestNode(hEle, pNode, pPt);//测试鼠标点击位置
	if (pNode)
	{
		//如果点在按钮上展开或收缩
		if (pTree->bButton)
		{
			if (NULL == pNode->pParent)
			{
				if (pTree->bRootLine)
				{
					if (PtInRect(&pNode->rcButton, *pPt))
					{
						if (pNode->pRight)  //需要调整绘制
						{
							if (pNode->bExpand)
								pNode->bExpand = FALSE;
							else
								pNode->bExpand = TRUE;

							pTree->bAdjust = TRUE; //调整滚动视图大小
							XEle_RedrawEle(hEle);
						}
						//发送按钮点击展开收缩事件...
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
					if (pNode->pRight)  //需要调整绘制
					{
						if (pNode->bExpand)
							pNode->bExpand = FALSE;
						else
							pNode->bExpand = TRUE;

						pTree->bAdjust = TRUE; //调整滚动视图大小
						//RedrawEle();
						XEle_RedrawEle(hEle);
					}
					//待处理:发送按钮点击展开收缩事件...
					if (pNode->bExpand)
						Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, TRUE);
					else
						Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, FALSE);
					return TRUE;
				}
			}
		}

		if (pTree->bCheck)//复选框
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
				if (pTree->pCurrItem) //选择项
					pTree->pCurrItem->state = 0;
				pTree->pCurrItem = pNode;
				pTree->pCurrItem->state = STATE_SELECT;
				//发送项选择事件...
				Ele_SendEvent(hEle, XE_TREE_SELECT, pTree->pCurrItem->id, 0);
				XEle_RedrawEle(hEle);
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL Tree_TextDBClick(HELE hEle, treeNode_ *pNode, POINT *pPt) //遍历测试鼠标双击
{
	tree_ *pTree = TREE(hEle);

	if (NULL == pNode)
		return FALSE;

	pNode = Tree_HitTestNode(hEle, pNode, pPt);
	if (pNode)
	{
		//点在展开按钮上 跳出
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
		//展开或收缩
		if (pNode->bExpand)
			pNode->bExpand = FALSE;
		else
			pNode->bExpand = TRUE;

		if (pNode->pRight) //有子项 需要重绘
		{
			pTree->bAdjust = TRUE;
			XEle_RedrawEle(hEle);

			//有子项发送展开事件
			if (pNode->bExpand)
				Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, TRUE);
			else
				Ele_SendEvent(hEle, XE_TREE_EXPAND, pNode->id, FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

treeNode_ *Tree_HitTestNode(HELE hEle, treeNode_ *pNode, POINT *pPt)  //测试点击位置,返回项ID
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

void Tree_DeleteNode(treeNode_ *pNode) //遍历删除结点,包括子项
{
	if (NULL != pNode)
	{
		Tree_DeleteNode(pNode->pRight);
		Tree_DeleteNode(pNode->pLeft);

		//删除结点
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

BOOL CALLBACK Tree_OnEventSetFocus(HELE hEle, HELE hEventEle)  //获得焦点
{
	if (hEle != hEventEle)
		return FALSE;

	XEle_RedrawEle(hEle);
	return TRUE;
}

BOOL CALLBACK Tree_OnEventKillFocus(HELE hEle, HELE hEventEle) //失去焦点
{
	if (hEle != hEventEle)
		return FALSE;

	XEle_RedrawEle(hEle);
	return TRUE;
}

///@}