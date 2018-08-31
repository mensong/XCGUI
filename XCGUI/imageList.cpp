/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"
#include "imageList.h"

/// @defgroup imageList 图片列表
/// @ingroup groupOther
/// 图片列表用来保存多个图片,添加删除显示等,当图片列表关联到一个UI元素后,他会自动销毁接口句柄,否则需要我们手动销毁图片列表句柄.
/// @{

/// @brief 创建图片列表.
/// @param cx 图片宽度.
/// @param cy 图片高度.
/// @return 图片列表句柄.
HXCGUI WINAPI XImageList_Create(int cx, int cy)
{
	int len = sizeof(imageList_);
	imageList_  *pObject = (imageList_*)malloc(sizeof(imageList_));
	memset(pObject, 0, sizeof(imageList_));
	pObject->size.cx = cx;
	pObject->size.cy = cy;
	pObject->bFixedSize = TRUE;
	pObject->hArrayImage = XArray_Create();
	pObject->refCount = 0;

	((object_*)pObject)->type = XC_IMAGELIST;
	return pObject;
}

/// @brief 图片列表销毁.
/// @param hImageList 图片列表句柄.
void WINAPI XImageList_Destroy(HXCGUI hImageList)  //销毁
{
	IsImageListDebug(hImageList, __FUNCTION__);
	imageList_ *pObj = (imageList_*)hImageList;

	if (1 == pObj->refCount)
	{
		XImageList_DeleteAll(pObj);
		//int count=Array_GetCount(pObj->hArrayImage);
		XArray_Destroy(pObj->hArrayImage);
		free(hImageList);
	}
	else
		pObj->refCount--;
}

/// @brief 添加图片.
/// @param hImageList 图片列表句柄.
/// @param hImage  图片句柄.
void WINAPI XImageList_AddImage(HXCGUI hImageList, HIMAGE hImage) //添加图片从文件
{
	IsImageListDebug(hImageList, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
		imageListItem_ *pNew = (imageListItem_*)malloc(sizeof(imageListItem_));
		pNew->hImage = Image_AddRef(hImage);
		XArray_Add(((imageList_*)hImageList)->hArrayImage, pNew);
	}
}

/// @brief 获取图片高度.
/// @param hImageList 图片列表句柄.
/// @return 图片高度.
int  WINAPI XImageList_GetWidth(HXCGUI hImageList)
{
	IsImageListDebug(hImageList, __FUNCTION__);
	return ((imageList_*)hImageList)->size.cx;
}

/// @brief 获取图片宽度.
/// @param hImageList 图片列表句柄.
/// @return 图片宽度.
int  WINAPI XImageList_GetHeight(HXCGUI hImageList)
{
	IsImageListDebug(hImageList, __FUNCTION__);
	return ((imageList_*)hImageList)->size.cy;
}

/// @brief 获取图片列表中图片数量.
/// @param hImageList 图片列表句柄.
/// @return 图片列表中图片数量.
int  WINAPI XImageList_GetCount(HXCGUI hImageList)   //获取图片数量
{
	IsImageListDebug(hImageList, __FUNCTION__);
	return XArray_GetCount(((imageList_*)hImageList)->hArrayImage);
}

/// @brief 获取图片.
/// @param hImageList 图片列表句柄.
/// @param index 图片索引.
/// @return 图片句柄.
HIMAGE WINAPI XImageList_GetImage(HXCGUI hImageList, int index) //获取图片
{
	IsImageListDebug(hImageList, __FUNCTION__);
	if (index < 0) return NULL;

	int count = XArray_GetCount(((imageList_*)hImageList)->hArrayImage);
	if (index >= count) return NULL;

	imageListItem_ *pItem = (imageListItem_*)XArray_GetAt(((imageList_*)hImageList)->hArrayImage, index);
	if (pItem)
		return pItem->hImage;

	return NULL;
}

/// @brief 删除图片列表中,指定索引位置的图片.
/// @param hImageList 图片列表句柄.
/// @param index  要删除的图片位置索引.
void WINAPI XImageList_DeleteIndex(HXCGUI hImageList, int index)//删除指定图片
{
	IsImageListDebug(hImageList, __FUNCTION__);
	imageList_ *pImageList = (imageList_*)hImageList;

	imageListItem_ *pItem = (imageListItem_*)Array_GetAt(pImageList->hArrayImage, index);
	if (pItem)
	{
		XImage_Destroy(pItem->hImage);
		free(pItem);
	}
	XArray_DeleteIndex(pImageList->hArrayImage, index);
}

/// @brief 从图片列表中删除全部图片.
/// @param hImageList 图片列表句柄.
void WINAPI XImageList_DeleteAll(HXCGUI hImageList) //删除全部图片
{
	IsImageListDebug(hImageList, __FUNCTION__);
	imageList_ *pImageList = (imageList_*)hImageList;

	int count = Array_GetCount(pImageList->hArrayImage);
	for (int i = 0; i < count; i++)
	{
		imageListItem_ *pItem = (imageListItem_*)Array_GetAt(pImageList->hArrayImage, i);
		XImage_Destroy(pItem->hImage);
		free(pItem);
	}
	XArray_DeleteAll(pImageList->hArrayImage);
}

/// @brief 绘制图片.
/// @param hImageList 图片列表句柄.
/// @param hDraw   绘图句柄.
/// @param index  图片索引.
/// @param x   显示位置x坐标.
/// @param y   显示位置y坐标.
void WINAPI XImageList_DrawImage(HXCGUI hImageList, HDRAW hDraw, int index, int x, int y)
{
	IsImageListDebug(hImageList, __FUNCTION__);

	imageList_ *pObject = (imageList_*)hImageList;
	if (index >= 0 && index < Array_GetCount(pObject->hArrayImage))
	{
		imageListItem_ *pItem = Array_GetAtImage(pObject->hArrayImage, index);
		if (pObject->bFixedSize)
		{
			XDraw_HImageStretch_(hDraw, pItem->hImage, x, y, pObject->size.cx, pObject->size.cy);
		}
		else
		{
			int width = XImage_GetWidth(pItem->hImage);
			int height = XImage_GetHeight(pItem->hImage);

			XDraw_HImageStretch_(hDraw, pItem->hImage,
				x + (pObject->size.cx - width) / 2,
				y + (pObject->size.cy - height) / 2,
				width, height);
		}
	}
}

/// @brief 绘制图片,指定大小.
/// @param hImageList 图片列表句柄.
/// @param hDraw   绘图句柄.
/// @param index  图片索引.
/// @param pRect  坐标.
void WINAPI XImageList_DrawImage2(HXCGUI hImageList, HDRAW hDraw, int index, RECT *pRect)
{
	IsImageListDebug(hImageList, __FUNCTION__);

	imageList_ *pObject = (imageList_*)hImageList;
	if (index >= 0 && index < Array_GetCount(pObject->hArrayImage))
	{
		imageListItem_ *pItem = Array_GetAtImage(pObject->hArrayImage, index);
		XDraw_HImageStretch_(hDraw, pItem->hImage, pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top);
	}
}

/// @brief 绘制固定大小.
/// @param hImageList 图片列表句柄.
/// @param bEnable  是否启用.
void WINAPI XImageList_EnableFixedSize(HXCGUI hImageList, BOOL bEnable) //绘制固定大小 Fixed-size
{
	IsImageListDebug(hImageList, __FUNCTION__);
	((imageList_*)hImageList)->bFixedSize = bEnable;
}

/// @brief 判断图片是否被设置为固定大小.
/// @param hImageList 图片列表句柄.
/// @return 图片被设置为固定大小TRUE,否则相反FALSE.
BOOL WINAPI XImageList_IsFixedSize(HXCGUI hImageList)
{
	IsImageListDebug(hImageList, __FUNCTION__);
	return ((imageList_*)hImageList)->bFixedSize;
}

///@}


HXCGUI ImageList_AddRef(HXCGUI hImageList) //增加引用计数
{
	if (hImageList)
	{
		((imageList_*)hImageList)->refCount++;
		return hImageList;
	}
	return NULL;
}