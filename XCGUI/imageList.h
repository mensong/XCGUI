/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct  imageListItem_
{
	//HANDLE  handle;  //句柄  位图或图标句柄
	//类型  0位图  1带透明色位图  2图标 3其他格式图片,如png
	//4 从文件加载图标
 //  int     type;  

//   COLORREF color;  //透明色
//	Image   *pImage; //其他格式图片,如PNG图片

	HIMAGE  hImage;//图片
};

struct imageList_
{
	object_ object;
	int    refCount; //引用计数,当值为0时 销毁对象

	HARRAY hArrayImage; //图片列表 imageListItem_*
	SIZE  size; //图片大小

	BOOL bFixedSize; //绘制固定大小
};

//位图销毁 图标销毁

//API:
XC_API HXCGUI WINAPI XImageList_Create(int cx, int cy);
XC_API void WINAPI XImageList_Destroy(HXCGUI hImageList); //销毁
XC_API void WINAPI XImageList_AddImage(HXCGUI hImageList, HIMAGE hImage); //添加图片

XC_API int  WINAPI XImageList_GetWidth(HXCGUI hImageList);   //获取图片宽度
XC_API int  WINAPI XImageList_GetHeight(HXCGUI hImageList);  //获取图片高度
XC_API int  WINAPI XImageList_GetCount(HXCGUI hImageList);   //获取图片数量
XC_API HIMAGE WINAPI XImageList_GetImage(HXCGUI hImageList, int index); //获取图片

XC_API void WINAPI XImageList_DeleteIndex(HXCGUI hImageList, int index); //删除指定图片
XC_API void WINAPI XImageList_DeleteAll(HXCGUI hImageList);  //删除全部图片

XC_API void WINAPI XImageList_DrawImage(HXCGUI hImageList, HDRAW hDraw, int index, int x, int y);
XC_API void WINAPI XImageList_DrawImage2(HXCGUI hImageList, HDRAW hDraw, int index, RECT *pRect);

XC_API void WINAPI XImageList_EnableFixedSize(HXCGUI hImageList, BOOL bEnable); //绘制固定大小 Fixed-size
XC_API BOOL WINAPI XImageList_IsFixedSize(HXCGUI hImageList);
//私有方法:
HXCGUI ImageList_AddRef(HXCGUI hImageList); //增加引用计数