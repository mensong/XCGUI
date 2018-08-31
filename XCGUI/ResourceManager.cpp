/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


resource_manager_   resource_manager;

void Resource_Init()
{
	resource_manager.pWindowList = NULL;
	resource_manager.countWindow = 0;
	resource_manager.ArraySize = 10;
	resource_manager.countEle = 0;

	int size = sizeof(resource_manager_element_header_)*resource_manager.ArraySize;
	resource_manager.pArrayEle = (resource_manager_element_header_*)malloc(size);
	memset(resource_manager.pArrayEle, 0, size);
}

void Resource_AddWindow(HWINDOW hWindow)
{
	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	resource_manager_window_ *pNode = (resource_manager_window_*)malloc(sizeof(resource_manager_window_));
	pNode->hWindow = hWindow;
	pNode->pNext = NULL;

	if (NULL == resource_manager.pWindowList)
	{
		resource_manager.pWindowList = pNode;
	}
	else
	{
		pNode->pNext = resource_manager.pWindowList;
		resource_manager.pWindowList = pNode;
	}
	resource_manager.countWindow++;
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);
}

BOOL Resource_RemoveWindow(HWINDOW hWindow)
{
	EnterCriticalSection(&g_CriticalSection_WindowDraw);
	resource_manager_window_ *pNode = resource_manager.pWindowList;
	resource_manager_window_ *pRemove = NULL;
	resource_manager_window_  *pPrev = NULL;
	while (pNode)
	{
		if (hWindow == pNode->hWindow)
		{
			pRemove = pNode;
			break;
		}
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	if (pRemove)
	{
		if (resource_manager.pWindowList == pRemove)
		{
			resource_manager.pWindowList = pRemove->pNext;
		}
		else
		{
			pPrev->pNext = pRemove->pNext;
		}
		free(pRemove);
		resource_manager.countWindow--;
		LeaveCriticalSection(&g_CriticalSection_WindowDraw);
		return TRUE;
	}
	LeaveCriticalSection(&g_CriticalSection_WindowDraw);
	return FALSE;
}

int  Resource_GetWindowCount()
{
	return resource_manager.countWindow;
}

BOOL Resource_IsHWINDOW(HWINDOW hWindow)
{
	if (NULL == hWindow)
		return FALSE;
	resource_manager_window_   *pNode = resource_manager.pWindowList;
	while (pNode)
	{
		if (hWindow == pNode->hWindow)
		{
			return TRUE;
		}
		pNode = pNode->pNext;
	}
	return FALSE;
}

BOOL Resource_IsHELE(HELE hEle)   //检查元素句柄是否有效
{
	if (NULL == hEle)
		return FALSE;
	int index = Resource_Hash((int)hEle);
	resource_manager_element_   *pNode = resource_manager.pArrayEle[index].pNode;
	while (pNode)
	{
		if (hEle == pNode->hEle)
		{
			return TRUE;
		}
		pNode = pNode->pNext;
	}
	return FALSE;
}

void Resource_Allocate() //检查内存空间大小是否合适
{
	resource_manager_element_ *pNode = NULL;
	resource_manager_element_ *pNodeNew = NULL;
	if (resource_manager.countEle <= 100) //100
	{
		if (10 != resource_manager.ArraySize)
		{
			Resource_Allocate_X(10);
		}
	}
	else if (resource_manager.countEle > 100 && resource_manager.countEle <= 500) //500
	{
		if (50 != resource_manager.ArraySize)
		{
			Resource_Allocate_X(50);
		}
	}
	else if (resource_manager.countEle > 500 && resource_manager.countEle <= 1000) //1000
	{
		if (100 != resource_manager.ArraySize)
		{
			Resource_Allocate_X(100);
		}
	}
	else if (resource_manager.countEle > 1000 && resource_manager.countEle <= 2000) //2000
	{
		if (200 != resource_manager.ArraySize)
		{
			Resource_Allocate_X(200);
		}
	}
	else if (resource_manager.countEle > 2000 && resource_manager.countEle <= 5000) //5000
	{
		if (500 != resource_manager.ArraySize)
		{
			Resource_Allocate_X(500);
		}
	}
	else //5000+
	{
		if (1000 != resource_manager.ArraySize)
		{
			Resource_Allocate_X(1000);
		}
	}
}

void Resource_Allocate_X(int ArraySizeNew) //需要重新分配空间
{
	int  ArraySize = resource_manager.ArraySize;
	resource_manager_element_header_ *pArrayEle = resource_manager.pArrayEle;

	resource_manager.pArrayEle = NULL;
	resource_manager.ArraySize = ArraySizeNew;

	//转移数据
	int size = sizeof(resource_manager_element_header_)*ArraySizeNew;
	resource_manager.pArrayEle = (resource_manager_element_header_*)malloc(size);
	memset(resource_manager.pArrayEle, 0, size);

	resource_manager_element_  *pNode = NULL;
	resource_manager_element_  *pNew = NULL;
	for (int i = 0; i < ArraySize; i++)
	{
		if (pArrayEle[i].pNode)
		{
			pNode = pArrayEle[i].pNode;
			while (pNode)
			{
				pNew = pNode;
				pNode = pNode->pNext;
				Resource_Allocate_Add(pNew);  //add
			}
		}
	}
	free(pArrayEle);
}

void Resource_Allocate_Add(resource_manager_element_  *pNew)
{
	int index = Resource_Hash((int)pNew->hEle);
	pNew->pNext = NULL;

	if (NULL == resource_manager.pArrayEle[index].pNode)
	{
		resource_manager.pArrayEle[index].pNode = pNew;
		resource_manager.pArrayEle[index].count = 1;
	}
	else
	{
		pNew->pNext = resource_manager.pArrayEle[index].pNode;
		resource_manager.pArrayEle[index].pNode = pNew;
		resource_manager.pArrayEle[index].count++;
	}
}

void Resource_AddEle(HELE hEle)
{
	Resource_Allocate(); //检查是否需要重新分配空间

	int index = Resource_Hash((int)hEle);

	resource_manager_element_  *pNew = (resource_manager_element_*)malloc(sizeof(resource_manager_element_));
	pNew->hEle = hEle;
	pNew->pNext = NULL;


	if (NULL == resource_manager.pArrayEle[index].pNode)
	{
		resource_manager.pArrayEle[index].pNode = pNew;
		resource_manager.pArrayEle[index].count = 1;
	}
	else
	{
		pNew->pNext = resource_manager.pArrayEle[index].pNode;
		resource_manager.pArrayEle[index].pNode = pNew;
		resource_manager.pArrayEle[index].count++;
	}

	resource_manager.countEle++;
}

BOOL Resource_RemoveEle(HELE hEle)
{
	Resource_Allocate(); //检查是否需要重新分配空间

	int index = Resource_Hash((int)hEle);

	resource_manager_element_  *pDel = NULL;
	resource_manager_element_  *pPrev = NULL;
	resource_manager_element_  *pNode = resource_manager.pArrayEle[index].pNode;
	while (pNode)
	{
		if (hEle == pNode->hEle)
		{
			pDel = pNode;
			break;
		}
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	if (pDel)
	{
		if (resource_manager.pArrayEle[index].pNode == pDel)
		{
			resource_manager.pArrayEle[index].pNode = pDel->pNext;
		}
		else
		{
			pPrev->pNext = pDel->pNext;
		}
		free(pDel);
		return TRUE;
	}
	return FALSE;
}

int  Resource_Hash(int data)  //哈希
{
	return (data / 1024) % resource_manager.ArraySize;
}

void Resource_Test()
{
	for (int i = 0; i < resource_manager.ArraySize; i++)
	{
		XTRACE("index=%d, count=%d \n", i, resource_manager.pArrayEle[i].count);
	}
}

void Resource_Release()
{
	resource_manager_window_  *pWindowList = resource_manager.pWindowList;
	resource_manager_window_  *pDelWindow = NULL;
	while (pWindowList)
	{
		pDelWindow = pWindowList;
		pWindowList = pWindowList->pNext;
		free(pDelWindow);
	}

	resource_manager_element_  *pNode = NULL;
	resource_manager_element_  *pDel = NULL;
	for (int i = 0; i < resource_manager.ArraySize; i++)
	{
		if (resource_manager.pArrayEle[i].pNode)
		{
			pNode = resource_manager.pArrayEle[i].pNode;
			while (pNode)
			{
				pDel = pNode;
				pNode = pNode->pNext;
				free(pDel);
			}
		}
	}
	free(resource_manager.pArrayEle);
}

