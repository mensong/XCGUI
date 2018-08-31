/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//炫彩界面库图片操作 

//#define  XC_IMAGE_BMP    1
//#define  XC_IMAGE_ICON   2
//#define  XC_IMAGE_PNG    3
//#define  XC_IMAGE_JPG    4
//#define  XC_IMAGE_GIF    5


//炫彩库通用图片对象
struct ximage_
{
	object_ object;
	//-----------------------
	Image  *pImage; //图片对象
	int    type;    //图片类型
	int    refCount; //引用计数,当值为0时 销毁对象
	int    flag;    //平铺
	BOOL   bAutoDestroy;

	int   imageWidth;
	int   imageHeight;
	int   imageX1;
	int   imageX2;
	int   imageY1;
	int   imageY2;

	//Bitmap
	BOOL   bBitmap; //是否为缓存位图
	Bitmap *pBitmap;

	BOOL   bTransparentColor;  //是否指定透明色
	Color transparentColor; //指定透明色
};

//当图片句柄设置到UI元素后,UI元素会自动释放该图片句柄,不需要用户手动释放.

//从内存中加载图片

XC_API HIMAGE WINAPI XImage_LoadFile(wchar_t *pImageName, BOOL bStretch = FALSE);//从文件中加载图片
XC_API HIMAGE WINAPI XImage_LoadRes(int id, wchar_t *pType, BOOL bStretch = FALSE);//从资源中加载图片
XC_API HIMAGE WINAPI XImage_LoadZip(wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword = NULL, BOOL bStretch = FALSE);//从ZIP中加载图片

//自适应图片
XC_API HIMAGE WINAPI XImage_LoadFileAdaptive(wchar_t *pImageName, int x1, int x2, int y1, int y2);//从文件中加载图片
XC_API HIMAGE WINAPI XImage_LoadResAdaptive(int id, wchar_t *pType, int x1, int x2, int y1, int y2);//从资源中加载图片
XC_API HIMAGE WINAPI XImage_LoadZipAdaptive(wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword, int x1, int x2, int y1, int y2);//从ZIP中加载图片

//加载图片,指定区域
XC_API HIMAGE WINAPI XImage_LoadFileRect(wchar_t *pImageName, int x, int y, int cx, int cy);

XC_API BOOL WINAPI XImage_IsStretch(HIMAGE hImage);   //是否拉伸图片
XC_API BOOL WINAPI XImage_IsAdaptive(HIMAGE hImage);  //是否为自适应图片
XC_API BOOL WINAPI XImage_IsTile(HIMAGE hImage);      //是否为平铺图片

XC_API BOOL WINAPI XImage_SetDrawType(HIMAGE hImage, int type);//设置图片绘制类型
XC_API BOOL WINAPI XImage_SetDrawTypeAdaptive(HIMAGE hImage, int x1, int x2, int y1, int y2);//设置图片自适应
XC_API void WINAPI XImage_SetTranColor(HIMAGE hImage, COLORREF color); //设置透明色
XC_API void WINAPI XImage_SetTranColorEx(HIMAGE hImage, COLORREF color, byte tranColor); //设置透明色
XC_API void WINAPI XImage_EnableTranColor(HIMAGE hImage, BOOL bEnable); //启用透明色

XC_API void WINAPI XImage_EnableAutoDestroy(HIMAGE hImage, BOOL bEnable); //启用或关闭自动销毁,当与UI元素关联时有效

//获取图片绘制类型
XC_API int WINAPI XImage_GetDrawType(HIMAGE hImage);

XC_API int WINAPI XImage_GetWidth(HIMAGE hImage);
XC_API int WINAPI XImage_GetHeight(HIMAGE hImage);

XC_API void WINAPI XImage_Destroy(HIMAGE hImage);

//私有方法:
void  Image_AddImage(HIMAGE &hImage, HIMAGE hImageNew); //图片与元素关联，增加引用计数
HIMAGE Image_AddRef(HIMAGE hImage); //增加引用计数

HIMAGE Image_LoadFile(wchar_t *pImageName);
HIMAGE Image_LoadRes(int id, wchar_t *pType);//从资源中加载图片
HIMAGE Image_LoadZip(wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword = NULL);//从ZIP中加载图片


void *do_extract_currentfile(void *uf, const char* password, int &outSize);
void *do_extract_onefile(void *uf, const char* filename, const char* password, int &outSize);

//*****************************************************************************
//ZIP压缩包操作


//从文件中加载ZIP包
//从资源中加载ZIP包
//从包中获取图片,返回炫彩图片句柄
//从包中获取文件
//是否ZIP句柄


BOOL ImageFromIDResource(int nID, wchar_t *pType, Image * &pImg); //资源ID,资源类型
BOOL ImageFromIDResourceToBitmap(int nID, wchar_t *pType, HBITMAP &hBitmap);