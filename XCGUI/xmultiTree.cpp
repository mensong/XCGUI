/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HXCGUI XMTree_Create()
{
	multiTree_  *pObject = (multiTree_*)malloc(sizeof(multiTree_));
	if (NULL == pObject) return NULL;
	pObject->pRootNode = NULL;
	pObject->pRootNodeEnd = NULL;
	pObject->pTraverseData = NULL;
	return pObject;
}

void XMTree_Destroy(HXCGUI hMTree) //销毁
{
	MTree_TraverseDestroy(((multiTree_*)hMTree)->pRootNode);
	free(hMTree);
}

BOOL XMTree_AddNode(HXCGUI hMTree, int parentID, void *pNodeData, int nodeID) //添加节点
{
	if (parentID < XMTREE_ROOT) return FALSE;

	multiTree_  *pObject = (multiTree_*)hMTree;

	//新节点
	multiTree_node_ *pNewNode = (multiTree_node_*)malloc(sizeof(multiTree_node_));
	memset(pNewNode, 0, sizeof(multiTree_node_));
	pNewNode->id = nodeID;
	pNewNode->pData = pNodeData;

	//跟节点
	if (XMTREE_ROOT == parentID)
	{
		if (NULL == pObject->pRootNode)
		{
			pObject->pRootNode = pNewNode;
			pObject->pRootNodeEnd = pNewNode;
		}
		else
		{
			pNewNode->pParentNode = pObject->pRootNodeEnd;
			pObject->pRootNodeEnd->pDown = pNewNode;
			pNewNode->pUp = pObject->pRootNodeEnd;
			pObject->pRootNodeEnd = pNewNode;
		}
		return TRUE;
	}

	//子节点
	multiTree_node_ *pParentItem = MTree_GetNode(pObject, parentID);
	if (NULL == pParentItem)
	{
		free(pNewNode);
		return FALSE;
	}
	pNewNode->pParentItem = pParentItem;
	if (pParentItem->pChild)
	{
		pNewNode->pParentNode = pParentItem->pChildEnd;
		pParentItem->pChildEnd->pDown = pNewNode;
		pNewNode->pUp = pParentItem->pChildEnd;
		pParentItem->pChildEnd = pNewNode;
	}
	else
	{
		pNewNode->pParentNode = pParentItem;
		pParentItem->pChild = pNewNode;
		pParentItem->pChildEnd = pNewNode;
	}
	return TRUE;
}

void XMTree_InsertNode(HXCGUI hMTree, void *pNodeData, int nodeID, int insertID)
{
	multiTree_  *pObject = (multiTree_*)hMTree;

	//新节点
	multiTree_node_ *pNewNode = (multiTree_node_*)malloc(sizeof(multiTree_node_));
	memset(pNewNode, 0, sizeof(multiTree_node_));
	pNewNode->id = nodeID;
	pNewNode->pData = pNodeData;

	multiTree_node_ *pInsertNode = MTree_GetNode((multiTree_*)hMTree, insertID);  //获取节点
	if (pInsertNode)
	{
		if (NULL == pInsertNode->pParentItem) //根节点层
		{
			if (pObject->pRootNode == pInsertNode) //首节点
			{
				pObject->pRootNode = pNewNode;
				pNewNode->pDown = pInsertNode;
				pInsertNode->pUp = pNewNode;
			}
			else //中间节点
			{
				pInsertNode->pUp->pDown = pNewNode;
				pNewNode->pUp = pInsertNode->pUp;
				pNewNode->pParentNode = pInsertNode->pUp;
				pNewNode->pDown = pInsertNode;
				pInsertNode->pUp = pNewNode;
				pInsertNode->pParentNode = pNewNode;
			}
		}
		else
		{
			if (pInsertNode == pInsertNode->pParentItem->pChild) //当前层首节点
			{
				pNewNode->pParentItem = pInsertNode->pParentItem;
				pNewNode->pParentItem->pChild = pNewNode;
				pNewNode->pDown = pInsertNode;
				pInsertNode->pUp = pNewNode;
				pInsertNode->pParentNode = pNewNode;
			}
			else //中间节点
			{
				pNewNode->pParentItem = pInsertNode->pParentItem;
				pInsertNode->pUp->pDown = pNewNode;
				pNewNode->pUp = pInsertNode->pUp;
				pNewNode->pParentNode = pInsertNode->pUp;
				pNewNode->pDown = pInsertNode;
				pInsertNode->pUp = pNewNode;
				pInsertNode->pParentNode = pNewNode;
			}
		}
	}
}

void *XMTree_GetNodeData(HXCGUI hMTree, int nodeID)
{
	multiTree_node_ *pNode = MTree_GetNode((multiTree_*)hMTree, nodeID);
	if (pNode)
		return pNode->pData;
	return NULL;
}

void XMTree_DeleteNode(HXCGUI hMTree, int nodeID)
{
	multiTree_  *pObject = (multiTree_*)hMTree;

	multiTree_node_ *pNode = MTree_GetNode((multiTree_*)hMTree, nodeID);	//要删除的节点
	if (pNode)
	{
		if (NULL == pNode->pParentItem) //根节点层
		{
			if (pObject->pRootNode == pNode) //首节点
			{
				if (pNode->pDown)
				{
					pObject->pRootNode = pNode->pDown;
					pNode->pDown->pUp = NULL;
					pNode->pDown->pParentNode = NULL;
				}
				else //末尾节点
				{
					pObject->pRootNode = NULL;
					pObject->pRootNodeEnd = NULL;
				}
			}
			else //中间节点
			{
				if (pNode->pDown)
				{
					pNode->pUp->pDown = pNode->pDown;
					pNode->pDown->pUp = pNode->pUp;
					pNode->pDown->pParentNode = pNode->pUp;
				}
				else //末尾节点
				{
					pNode->pUp->pDown = NULL;
					pObject->pRootNodeEnd = pNode->pUp;
				}
			}
		}
		else
		{
			if (pNode == pNode->pParentItem->pChild) //当前层首节点
			{
				if (pNode->pDown)
				{
					pNode->pParentItem->pChild = pNode->pDown;
					pNode->pDown->pUp = NULL;
					pNode->pDown->pParentNode = pNode->pParentItem;
				}
				else
				{
					pNode->pParentItem->pChild = NULL;
				}
			}
			else //中间节点
			{
				if (pNode->pDown)
				{
					pNode->pUp->pDown = pNode->pDown;
					pNode->pDown->pUp = pNode->pUp;
					pNode->pDown->pParentNode = pNode->pUp;
				}
				else //末尾节点
				{
					pNode->pParentItem->pChildEnd = pNode->pUp;
					pNode->pUp->pDown = NULL;
				}
			}
		}
		//delete pNode
		pNode->pDown = NULL;
		MTree_TraverseDestroy(pNode);
	}
}

void *XMTree_GetFirstChildNodeData(HXCGUI hMTree, int parentID)
{
	if (parentID < XMTREE_ROOT) return NULL;

	multiTree_  *pObject = (multiTree_*)hMTree;
	if (XMTREE_ROOT == parentID)
	{
		return pObject->pRootNode->pData;
	}
	else
	{
		multiTree_node_ *pNode = MTree_GetNode((multiTree_*)hMTree, parentID);
		if (pNode && pNode->pChild)
			return pNode->pChild->pData;
	}
	return NULL;
}

void *XMTree_GetNextNodeData(HXCGUI hMTree, int nodeID)
{
	multiTree_node_ *pNode = MTree_GetNode((multiTree_*)hMTree, nodeID);
	if (pNode)
	{
		if (pNode->pDown)
			return pNode->pDown->pData;
	}
	return NULL;
}

int  XMTree_GetNodeCount(HXCGUI hMTree, int nodeID)
{
	multiTree_node_  *pNode = NULL;
	if (XMTREE_ROOT == nodeID)
	{
		pNode = ((multiTree_*)hMTree)->pRootNode;
	}
	else
	{
		pNode = MTree_GetNode((multiTree_*)hMTree, nodeID);
	}
	if (pNode)
		return MTree_GetNodeCount(pNode);
	else
		return 0;
}

HXCGUI XMTree_GetNodeHandle(HXCGUI hMTree, int nodeID)
{
	multiTree_node_ *pNode = MTree_GetNode((multiTree_*)hMTree, nodeID);
	return pNode;
}

int  XMTree_BeginTraverse(HXCGUI hMTree, int parentID) //开始遍历
{
	multiTree_node_  *pNode = NULL;
	if (XMTREE_ROOT == parentID)
	{
		pNode = ((multiTree_*)hMTree)->pRootNode;
	}
	else
	{
		multiTree_node_ *pParentItem = MTree_GetNode((multiTree_*)hMTree, parentID);
		if (pParentItem)
			pNode = pParentItem->pChild;
	}

	if (NULL == pNode) return -1;

	int count = 0;

	multiTree_node_ *pNodeBegin = pNode;
	while (pNodeBegin)
	{
		count++;
		pNodeBegin = pNodeBegin->pDown;
	}
	if (count > 0)
	{
		void **data = (void **)malloc(sizeof(void*)*count);

		pNodeBegin = pNode;
		for (int i = 0; i < count; i++)
		{
			data[i] = pNodeBegin->pData;
			pNodeBegin = pNodeBegin->pDown;
		}

		((multiTree_*)hMTree)->pTraverseData = data;

		return count;
	}
	else
		return -1;
}

void *XMTree_GetTraverseData(HXCGUI hMTree, int index)
{
	return ((void**)((multiTree_*)hMTree)->pTraverseData)[index];
}

void XMTree_EndTraverse(HXCGUI hMTree) //结束遍历
{
	if (((multiTree_*)hMTree)->pTraverseData)
	{
		free(((multiTree_*)hMTree)->pTraverseData);
		((multiTree_*)hMTree)->pTraverseData = NULL;
	}
}

int  XMTree_BeginTraverseInfo(HXCGUI hMTree, int parentID) //开始遍历
{
	multiTree_node_  *pNode = NULL;
	if (XMTREE_ROOT == parentID)
	{
		pNode = ((multiTree_*)hMTree)->pRootNode;
	}
	else
	{
		multiTree_node_ *pParentItem = MTree_GetNode((multiTree_*)hMTree, parentID);
		if (pParentItem)
			pNode = pParentItem->pChild;
	}

	if (NULL == pNode) return -1;

	int count = 0;

	multiTree_node_ *pNodeBegin = pNode;
	while (pNodeBegin)
	{
		count++;
		pNodeBegin = pNodeBegin->pDown;
	}
	if (count > 0)
	{
		multiTree_node_info_ *data = (multiTree_node_info_*)malloc(sizeof(multiTree_node_info_)*count);

		pNodeBegin = pNode;
		for (int i = 0; i < count; i++)
		{
			data[i].pData = pNodeBegin->pData;
			data[i].id = pNodeBegin->id;
			data[i].hNode = pNodeBegin;
			pNodeBegin = pNodeBegin->pDown;
		}

		((multiTree_*)hMTree)->pTraverseData = data;

		return count;
	}
	else
		return -1;
}

void *XMTree_GetTraverseInfo(HXCGUI hMTree, int index, HXCGUI *hOutNode, int *outID)
{
	multiTree_node_info_ *pInfo = (multiTree_node_info_*)((multiTree_*)hMTree)->pTraverseData;
	if (outID) *outID = pInfo[index].id;
	if (hOutNode) *hOutNode = pInfo[index].hNode;
	return pInfo[index].pData;
}

void XMTree_EndTraverseInfo(HXCGUI hMTree) //结束遍历
{
	if (((multiTree_*)hMTree)->pTraverseData)
	{
		free(((multiTree_*)hMTree)->pTraverseData);
		((multiTree_*)hMTree)->pTraverseData = NULL;
	}
}

int  XMTree_BeginTraverseAll(HXCGUI hMTree) //开始遍历
{
	multiTree_ *pObject = (multiTree_*)hMTree;

	//计算子节点数量
	int count = MTree_GetNodeCount(pObject->pRootNode);

	void *data = malloc(sizeof(void*)*count);

	//迭代遍历节点
	MTree_TraverseNodeDataToArray(pObject->pRootNode, (void**)data);
	((multiTree_*)hMTree)->pTraverseData = data;

	return count;
}

void *XMTree_GetTraverseAll(HXCGUI hMTree, int index)
{
	return ((void**)((multiTree_*)hMTree)->pTraverseData)[index];
}

void XMTree_EndTraverseAll(HXCGUI hMTree) //结束遍历
{
	if (((multiTree_*)hMTree)->pTraverseData)
	{
		free(((multiTree_*)hMTree)->pTraverseData);
		((multiTree_*)hMTree)->pTraverseData = NULL;
	}
}

//计算节点数量
int  MTree_GetNodeCount(multiTree_node_  *pNode)
{
	multiTree_node_ *root = pNode; //根节点

	int  nodeCount = 0;
	int  LEFT_NO = 0;   //左节点未访问
	int  LEFT_YES = 1;  //左节点已访问
	int  RIGHT_YES = 2; //右节点已访问

	int state = LEFT_NO;
	while (pNode)
	{
		if (LEFT_NO == state)
		{
			//	XTRACE("id=%d \n",pNode->id);
			nodeCount++;
			if (pNode->pDown)
			{
				pNode = pNode->pDown;
			}
			else
			{
				state = LEFT_YES;
			}
		}
		else if (LEFT_YES == state)
		{
			if (pNode->pChild)
			{
				pNode = pNode->pChild;
				state = LEFT_NO;
			}
			else
			{
				if (NULL == pNode->pParentNode) break;

				if (pNode->pParentNode->pDown && pNode == pNode->pParentNode->pDown)
					state = LEFT_YES;
				else
					state = RIGHT_YES;
				pNode = pNode->pParentNode;
			}
		}
		else if (RIGHT_YES == state)
		{
			if (NULL == pNode->pParentNode) break;

			if (pNode == pNode->pParentNode->pDown)
				state = LEFT_YES;
			else
			{
				state = RIGHT_YES;
				if (root == pNode->pParentNode) //树右节点,回溯到跟节点,遍历完成
				{
					//	XTRACE("遍历结束 \n");
					break;
				}
			}
			pNode = pNode->pParentNode;
		}
	}
	return nodeCount;
}

void MTree_TraverseNodeDataToArray(multiTree_node_ *pNode, void **pArray)
{
	multiTree_node_ *root = pNode; //根节点

	int  nodeCount = 0;
	int  LEFT_NO = 0;   //左节点未访问
	int  LEFT_YES = 1;  //左节点已访问
	int  RIGHT_YES = 2; //右节点已访问

	int state = LEFT_NO;
	while (pNode)
	{
		if (LEFT_NO == state)
		{
			//	XTRACE("id=%d \n",pNode->id);
			pArray[nodeCount] = pNode->pData;
			nodeCount++;
			if (pNode->pDown)
			{
				pNode = pNode->pDown;
			}
			else
			{
				state = LEFT_YES;
			}
		}
		else if (LEFT_YES == state)
		{
			if (pNode->pChild)
			{
				pNode = pNode->pChild;
				state = LEFT_NO;
			}
			else
			{
				if (NULL == pNode->pParentNode) break;

				if (pNode->pParentNode->pDown && pNode == pNode->pParentNode->pDown)
					state = LEFT_YES;
				else
					state = RIGHT_YES;
				pNode = pNode->pParentNode;
			}
		}
		else if (RIGHT_YES == state)
		{
			if (NULL == pNode->pParentNode) break;

			if (pNode == pNode->pParentNode->pDown)
				state = LEFT_YES;
			else
			{
				state = RIGHT_YES;
				if (root == pNode->pParentNode) //树右节点,回溯到跟节点,遍历完成
				{
					//	XTRACE("遍历结束 \n");
					break;
				}
			}
			pNode = pNode->pParentNode;
		}
	}
	return;
}

int XMTree_GetHandleNextNodeInfo(HXCGUI hMTree, HXCGUI nodeHandle, HXCGUI *outNodeHandle)
{
	if (nodeHandle && outNodeHandle && ((multiTree_node_*)nodeHandle)->pDown)
	{
		*outNodeHandle = ((multiTree_node_*)nodeHandle)->pDown;
		return ((multiTree_node_*)nodeHandle)->pDown->id;
	}
	return -1;
}

HXCGUI XMTree_HandleGetFirstChildNode(HXCGUI hMTree, HXCGUI hParentNode)
{
	if (hMTree && hParentNode)
	{
		return ((multiTree_node_*)hParentNode)->pChild;
	}
	return NULL;
}

multiTree_node_ *MTree_GetNode(multiTree_ *pObject, int nodeID)  //获取节点
{
	if (nodeID < XMTREE_ROOT) return NULL;

	return MTree_TraverseNode(pObject->pRootNode, nodeID);
}

multiTree_node_ *MTree_TraverseNode(multiTree_node_ *pNode, int nodeID)
{
	if (NULL == pNode) return NULL;

	if (pNode->id == nodeID) return pNode;

	multiTree_node_ *pCurNode = NULL;

	pCurNode = MTree_TraverseNode(pNode->pChild, nodeID);
	if (pCurNode) return pCurNode;

	pCurNode = MTree_TraverseNode(pNode->pDown, nodeID);
	if (pCurNode) return pCurNode;

	return NULL;
}

void MTree_TraverseDestroy(multiTree_node_ *pNode)
{
	if (NULL == pNode) return;

	MTree_TraverseDestroy(pNode->pChild);

	MTree_TraverseDestroy(pNode->pDown);

	//XTRACE("销毁 : %d \n",pNode->id);
	free(pNode);
}