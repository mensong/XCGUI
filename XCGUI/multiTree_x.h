/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//基于二叉树的多叉树--------------------------

/**************************
	 N-----N-----N
	 |     |
	 |     N
	 |     |
	 |     N
	 |
	 N-----N
	 |     |
	 N     N
	 |
	 N
****************************/

//Multi-tree

struct multiTree_node_
{
	//用户数据
	int    id;     //节点ID,不可重复,值大于等于0
	void   *pData; //数据

	//----------------

	multiTree_node_  *pParentItem; //父项    基于多叉树的父节点
	multiTree_node_  *pParentNode; //父节点  基于二叉树的父节点

	multiTree_node_  *pUp;         //上节点
	multiTree_node_  *pDown;       //下节点
	multiTree_node_  *pChild;      //子节点
	multiTree_node_  *pChildEnd;   //该节点的下一层子节点的最后一个节点
};

struct multiTree_node_info_
{
	//用户数据
	int    id;      //节点ID,不可重复,值大于等于0
	void   *pData;  //数据
	HXCGUI  hNode;  //节点句柄
};

struct  multiTree_
{
	multiTree_node_  *pRootNode;    //跟节点开始节点
	multiTree_node_  *pRootNodeEnd; //跟节点末尾节点

	void  *pTraverseData; //数据遍历临时指针
};

HXCGUI XMTree_Create();


//功能      : 添加节点到当前层末尾
//hMTree    : 树句柄
//parentID  : 父节点ID
//pNodeData : 插入节点数据
//nodeID    : 插入节点ID
BOOL XMTree_AddNode(HXCGUI hMTree, int parentID, void *pNodeData, int nodeID); //添加节点


//功能: 插入到指定节点前面,当前层位置
//pNodeData  : 节点数据
//nodeID     : 节点ID
//insertID   : 插入ID为到insertID节点前面位置
void XMTree_InsertNode(HXCGUI hMTree, void *pNodeData, int nodeID, int insertID);

//功能      : 插入子节点
//hMTree    : 树句柄
//parentID  : 父节点ID
//pNodeData : 插入节点数据
//nodeID    : 插入节点ID
//insertID  : 插入到指定ID节点前面
//void XMTree_InsertChildNode(HXCGUI hMTree,int parentID,void *pNodeData,int nodeID,int insertID);


//功能      : 插入子节点到首位
//hMTree    : 树句柄
//parentID  : 父节点ID
//pNodeData : 插入节点数据
//nodeID    : 插入节点ID
//void XMTree_InsertChildNodeBegin(HXCGUI hMTree,int parentID,void *pNodeData,int nodeID);

//删除节点,如果有子节点同时删除
void XMTree_DeleteNode(HXCGUI hMTree, int nodeID);

//获取节点数据
void *XMTree_GetNodeData(HXCGUI hMTree, int nodeID);

//功能     : 获取第一个子节点
//parentID : 父节点ID
void *XMTree_GetFirstChildNodeData(HXCGUI hMTree, int parentID);


//功能     : 获取当前层下一个节点
//nodeID   : 当前节点ID
//返回值   : nodeID下个节点的数据,如果没有返回NULL
void *XMTree_GetNextNodeData(HXCGUI hMTree, int nodeID);

//获取节点数量,获取nodeID节点下的总数量,包含nodeID节点
int  XMTree_GetNodeCount(HXCGUI hMTree, int nodeID);


//功能     : 遍历下一层节点,不包含子节点
//parentID : 开始遍历的父节点ID
//返回值   : 要遍历的节点数量,不包含父节点,如果失败返回-1
int  XMTree_BeginTraverse(HXCGUI hMTree, int parentID);//开始遍历
void *XMTree_GetTraverseData(HXCGUI hMTree, int index);
void XMTree_EndTraverse(HXCGUI hMTree); //结束遍历


//功能     : 遍历下一层节点,不包含子节点
//parentID : 开始遍历的父节点ID
//返回值   : 要遍历的节点数量,如果失败返回-1
int  XMTree_BeginTraverseInfo(HXCGUI hMTree, int parentID);//开始遍历
void *XMTree_GetTraverseInfo(HXCGUI hMTree, int index, HXCGUI *hOutNode = NULL, int *outID = NULL);
void XMTree_EndTraverseInfo(HXCGUI hMTree); //结束遍历


//遍历所有子节点
int  XMTree_BeginTraverseAll(HXCGUI hMTree);//开始遍历
void *XMTree_GetTraverseAll(HXCGUI hMTree, int index);
void XMTree_EndTraverseAll(HXCGUI hMTree); //结束遍历

//遍历节点数据到数组
void MTree_TraverseNodeDataToArray(multiTree_node_ *pNode, void **pArray);

//计算节点数量,该节点下的所有节点,包含传入节点,
int  MTree_GetNodeCount(multiTree_node_  *pNode);


//销毁该实例句柄
void XMTree_Destroy(HXCGUI hMTree); //销毁



//以下API,通过节点句柄操作,以便访问加速-------------------------------

//功能    : 获取节点句柄,通过句柄操作获取更快的速度
//返回值  : nodeID节点句柄
HXCGUI XMTree_GetNodeHandle(HXCGUI hMTree, int nodeID);



//功能           : 获取当前层下一个节点信息
//nodeHandle     : 当前节点句柄
//outNodeHandle  : 接收下个节点句柄
//返回值         : 下个节点ID, 错误返回-1
int XMTree_GetHandleNextNodeInfo(HXCGUI hMTree, HXCGUI nodeHandle, HXCGUI *outNodeHandle);



//功能     : 获取第一个子节点句柄
//hParentNode : 父节点句柄
HXCGUI XMTree_HandleGetFirstChildNode(HXCGUI hMTree, HXCGUI hParentNode);

//私有方法:-----------------------------------*****************************************************


//功能    : 获取指定节点
//nodeID  : 获取节点ID
multiTree_node_ *MTree_GetNode(multiTree_ *pObject, int nodeID);  //获取节点
//辅助:遍历查找节点
multiTree_node_ *MTree_TraverseNode(multiTree_node_ *pNode, int nodeID);


//辅助:遍历销毁节点
//pNode:要销毁的节点,同时销毁子节点
void MTree_TraverseDestroy(multiTree_node_ *pNode);







/*
HXCGUI XMTree_FindNode(HXCGUI hMTree,int id); //查找节点

int  XMTree_BeginTraverse(HXCGUI hMTree,int parentID);//开始遍历
void XMTree_EndTraverse(HXCGUI hMTree); //结束遍历
*/
