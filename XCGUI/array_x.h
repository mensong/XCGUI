/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct ele_;

struct array_traversal_
{
	void *pData;  //数据
	BOOL  bValid; //是否有效
};

//迭代器
struct array_traversal_iterator_
{
	HARRAY  hArray;  //array_*
	BOOL  traversal_bStart;  //是否正在遍历
	BOOL  traversal_bType;   //遍历方式,从前向后遍历TRUE,从后向前遍历FALSE.
	int   traversal_index;   //Traversal//当前遍历索引
	int   traversal_count;
	array_traversal_  *data;  //复制的数据数组
};

struct array_
{
	object_ object;

	void**  data;   //元素列表指针
	int     count;  //元素实际个数
	int     sum;    //数组最大容量
	int     grow;   //增长值

	HARRAY  hArray_list;//迭代器列表array_traversal_iterator_* 
};

//API:
XC_API HARRAY WINAPI XArray_Create(); //创建
XC_API void WINAPI XArray_Destroy(HARRAY hArray); //销毁
XC_API int  WINAPI XArray_Add(HARRAY hArray, void *pElement);//增加元素到末尾
XC_API void WINAPI XArray_AddFirst(HARRAY hArray, void *pElement); //增加到开头
XC_API BOOL WINAPI XArray_insert(HARRAY hArray, void *pElement, int index); //插入到指定位置
XC_API void WINAPI XArray_DeleteIndex(HARRAY hArray, int index);
XC_API void WINAPI XArray_Delete(HARRAY hArray, void *pElement);
XC_API void WINAPI XArray_DeleteEnd(HARRAY hArray, int index); //删除末尾内容
XC_API void WINAPI XArray_DeleteRange(HARRAY hArray, int begin, int end);
XC_API void WINAPI XArray_DeleteAll(HARRAY hArray);
XC_API void WINAPI XArray_SetAt(HARRAY hArray, int index, void *pElement);

XC_API void* WINAPI XArray_GetAt(HARRAY hArray, int index);
XC_API int WINAPI XArray_GetCount(HARRAY hArray);

/////////////////////////////////////////////////////////////
//迭代器,安全遍历,在遍历中可对HARRAY数组成员添加或删除操作,遍历中忽略添加和删除的成员,.
XC_API HARRAY_ITERATOR WINAPI XArrayIterator_Create(HARRAY hArray, BOOL bType = TRUE);  //创建迭代器
XC_API void* WINAPI XArrayIterator_GetAt(HARRAY_ITERATOR hArray_Iterator);
XC_API void  WINAPI XArrayIterator_Destroy(HARRAY_ITERATOR hArray_Iterator);




//私有方法:
void Array_Allocate(HARRAY hArray);

#define Array_GetCount(hArray)                (((array_*)hArray)->count)
#define Array_GetAt(hArray,index)             (((array_*)hArray)->data[index]) 
#define Array_GetAtEle(hArray,index)          ((ele_*)((array_*)hArray)->data[index])
#define Array_GetAtWnd(hArray,index)	      ((window_*)((array_*)hArray)->data[index])
#define Array_GetAtW(hArray,index)	          ((wchar_t*)((array_*)hArray)->data[index])
#define Array_GetAtEdit(hArray,index)         ((editStrList_*)((array_*)hArray)->data[index])
#define Array_GetAtImage(hArray,index)	      ((imageListItem_*)((array_*)hArray)->data[index])
#define Array_GetAtList(hArray,index)         ((listItem_*)((array_*)hArray)->data[index])
#define Array_GetAtListHeader(hArray,index)   ((listHeader_*)((array_*)hArray)->data[index])
#define Array_GetAtListSubItem(hArray,index)  ((listSubItem_*)((array_*)hArray)->data[index])
#define Array_GetAtMenu(hArray,index)	      ((menu_*)((array_*)hArray)->data[index])
#define Array_GetAtMenuBarItem(hArray,index)  ((menuBarItem_*)((array_*)hArray)->data[index])

//Array_CheckSpace(HXCGUI hArray) //检查内存空间，如果不足分配空间
#define ARRAY_CHECK_SPACE(hArray) {if(((array_*)hArray)->count>=((array_*)hArray)->sum) Array_Allocate(hArray);} //空间不够 重新分配