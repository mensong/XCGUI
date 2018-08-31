/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


#if 0

//基于二叉树的多叉树---测试
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	HXCGUI hMTree=XMTree_Create();

	malloc(1);

	XMTree_AddNode(hMTree,XMTREE_ROOT,NULL,1);
	XMTree_AddNode(hMTree,XMTREE_ROOT,NULL,2);
	XMTree_AddNode(hMTree,XMTREE_ROOT,NULL,3);

	XMTree_AddNode(hMTree,2,NULL,4);

	XMTree_AddNode(hMTree,1,NULL,5);
	XMTree_AddNode(hMTree,1,NULL,6);

	XMTree_AddNode(hMTree,5,NULL,7);
	XMTree_AddNode(hMTree,5,NULL,8);

	XMTree_AddNode(hMTree,7,NULL,9);

	XMTree_AddNode(hMTree,6,NULL,10);
	
	int count=MTree_GetNodeCount(((multiTree_*)hMTree)->pRootNode);

	XMTree_DeleteNode(hMTree,5);
	//XMTree_DeleteNode(hMTree,6);
	//XMTree_DeleteNode(hMTree,7);
	//XMTree_DeleteNode(hMTree,8);
	//XMTree_DeleteNode(hMTree,9);
	
	XMTree_Destroy(hMTree);

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	return 0;
}

#endif