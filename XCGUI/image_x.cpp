/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

//#include <direct.h>
//#include <errno.h>

#include "zlib/unzip.h"
//#pragma comment(lib,"unzip.lib")

#define CASESENSITIVITY   (0)
#define MAXFILENAME       (256)
#define WRITEBUFFERSIZE   (8192)


/// @defgroup image 图片操作
/// @ingroup groupOther
/// 图片操作接口,提供了图片的加载,销毁及配合UI元素的贴图显示,当图片接口关联到一个UI元素后,它会自动销毁图片接口,否则需要你手动销毁.<br>
/// 主要支持:加载图片文件格式,bmp,jpg,png,gif,ico.从文件加载,从程序资源加载,从压缩包中加载,自适应图片,平铺,透明色支持.
/// @{

void *do_extract_currentfile(void *uf, const char* password, int &outSize)
{
	char  filename_inzip[256];
	int   err = UNZ_OK;
	void* buf;
	unsigned int size_buf;
	unz_file_info64 file_info;
	err = unzGetCurrentFileInfo64(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);//获取文件信息
	if (err != UNZ_OK)
	{
		XTRACE("error %d with zipfile in unzGetCurrentFileInfo\n", err);
		return NULL;
	}

	//检查密码
	err = unzOpenCurrentFilePassword(uf, password);
	if (err != UNZ_OK)
	{
		XTRACE("error %d with zipfile in unzOpenCurrentFilePassword\n", err);
		return NULL;
	}

	//分配内存
	size_buf = (unsigned int)file_info.uncompressed_size; // WRITEBUFFERSIZE;
	buf = (void*)malloc(size_buf);
	if (buf == NULL)
	{
		printf("Error allocating memory\n");
		return NULL;
	}

	//读取数据
	err = unzReadCurrentFile(uf, buf, size_buf);
	if (err < 0)
	{
		XTRACE("error %d with zipfile in unzReadCurrentFile\n", err);
	}
	outSize = err;

	//关闭当前文件
	if (err >= 0)
	{
		err = unzCloseCurrentFile(uf);
		if (err != UNZ_OK)
		{
			XTRACE("error %d with zipfile in unzCloseCurrentFile\n", err);
		}
		else
		{
			return buf;
		}
	}
	else
	{
		unzCloseCurrentFile(uf);
	}

	free(buf);
	return NULL;
}


//提取一个文件
void *do_extract_onefile(void *uf, const char* filename, const char* password, int &outSize)
{
	int err = UNZ_OK;
	if (unzLocateFile(uf, filename, CASESENSITIVITY) != UNZ_OK)
	{
		XTRACE("file %s not found in the zipfile\n", filename);
		return NULL;
	}

	return do_extract_currentfile(uf, password, outSize);
}

/// @brief 加载图片从ZIP压缩包.
/// @param pZipFileName  ZIP压缩包文件名.
/// @param pImageName 图片文件名.
/// @param pPassword  ZIP压缩包密码.
/// @param bStretch   是否拉伸图片
/// @return  图片句柄.
HIMAGE WINAPI XImage_LoadZip(wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword, BOOL bStretch)
{
	if (NULL == pZipFileName || NULL == pImageName)
	{
		return NULL;
	}

	IsImageTypeDebug(_T(__FUNCTION__), pImageName);

	HIMAGE hImage = Image_LoadZip(pZipFileName, pImageName, pPassword);
	if (hImage)
	{
		if (bStretch)
			((ximage_*)hImage)->flag = XC_IMAGE_STRETCH;
		return hImage;
	}
	return NULL;
}

/// @brief 加载图片从ZIP压缩包,自适应图片.
/// @param pZipFileName  ZIP压缩包文件名.
/// @param pImageName 图片文件名.
/// @param pPassword  ZIP压缩包密码,如果没有填NULL.
/// @param x1 坐标.
/// @param x2 坐标.
/// @param y1 坐标.
/// @param y2 坐标.
/// @return  图片句柄.
HIMAGE WINAPI XImage_LoadZipAdaptive(wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword, int x1, int x2, int y1, int y2) //从ZIP中加载图片
{
	if (x1 > x2) return NULL;
	if (y1 > y2) return NULL;

	HIMAGE hImage = XImage_LoadZip(pZipFileName, pImageName, pPassword);
	if (hImage)
	{
		ximage_ *pXImage = (ximage_*)hImage;

		pXImage->flag = XC_IMAGE_ADAPTIVE;
		pXImage->imageWidth = pXImage->pImage->GetWidth();
		pXImage->imageHeight = pXImage->pImage->GetHeight();
		pXImage->imageX1 = x1;
		pXImage->imageX2 = x2;
		pXImage->imageY1 = y1;
		pXImage->imageY2 = y2;
		return hImage;
	}
	return NULL;
}

/// @brief 加载图片从文件.
/// @param pImageName 图片文件.
/// @param bStretch   是否拉伸图片
/// @return  图片句柄.
HIMAGE WINAPI XImage_LoadFile(wchar_t *pImageName, BOOL bStretch)
{
	if (NULL == pImageName) return NULL;

	IsImageTypeDebug(_T(__FUNCTION__), pImageName);

	HIMAGE hImage = Image_LoadFile(pImageName);
	if (hImage)
	{
		if (bStretch)
			((ximage_*)hImage)->flag = XC_IMAGE_STRETCH;
		return hImage;
	}
	return NULL;
}

/// @brief 加载图片从文件,自适应图片.
/// @param pImageName 图片文件.
/// @param x1 坐标.
/// @param x2 坐标.
/// @param y1 坐标.
/// @param y2 坐标.
/// @return  图片句柄.
HIMAGE WINAPI XImage_LoadFileAdaptive(wchar_t *pImageName, int x1, int x2, int y1, int y2) //从文件中加载图片
{
	if (x1 > x2) return NULL;
	if (y1 > y2) return NULL;

	HIMAGE hImage = XImage_LoadFile(pImageName);
	if (hImage)
	{
		ximage_ *pXImage = (ximage_*)hImage;
		pXImage->flag = XC_IMAGE_ADAPTIVE;
		pXImage->imageWidth = pXImage->pImage->GetWidth();
		pXImage->imageHeight = pXImage->pImage->GetHeight();
		pXImage->imageX1 = x1;
		pXImage->imageX2 = x2;
		pXImage->imageY1 = y1;
		pXImage->imageY2 = y2;

		return hImage;
	}
	return NULL;
}

/// @brief 加载图片,指定区位置及大小.
/// @param pImageName 图片文件.
/// @param x 坐标.
/// @param y 坐标.
/// @param cx 宽度.
/// @param cy 高度.
/// @return 图片句柄.
HIMAGE WINAPI XImage_LoadFileRect(wchar_t *pImageName, int x, int y, int cx, int cy)
{
	//加载图片
	Image image(pImageName);
	if (Gdiplus::Ok != image.GetLastStatus())
	{
		XTRACEW(L"XImage_LoadFileRect(\"%s\"),可能图片路径错误 \n", pImageName);
		return NULL;
	}

	//缓存图片
	Bitmap *pBitmap = new Bitmap(cx, cy);

	//将图片绘制到缓存
	Graphics* imageGraphics = Graphics::FromImage(pBitmap);

	Rect destRect;
	destRect.X = 0;
	destRect.Y = 0;
	destRect.Width = cx;
	destRect.Height = cy;

	ImageAttributes ImgAtt;

	if (Gdiplus::Ok != imageGraphics->DrawImage(&image,
		destRect,
		x,    //srcX
		y,    //srcY
		cx,   //cx
		cy,   //cy
		UnitPixel, &ImgAtt, NULL, NULL))
	{
		XTRACE("XImage_LoadFileSize() 错误 \n");

		delete imageGraphics;
		return NULL;
	}

	ximage_ *pXImage = (ximage_*)malloc(sizeof(ximage_));
	memset(pXImage, 0, sizeof(ximage_));
	pXImage->object.type = XC_IMAGE;
	pXImage->type = 0;
	pXImage->refCount = 0;
	pXImage->flag = XC_IMAGE_DEFAULT;
	pXImage->pImage = NULL;
	pXImage->bBitmap = TRUE;
	pXImage->pBitmap = pBitmap;
	pXImage->bAutoDestroy = TRUE;

	delete imageGraphics;
	return (HIMAGE)pXImage;
}

/// @brief 是否为拉伸图片句柄
/// @param hImage  图片句柄.
/// @return  如果是返回TRUE,否则相反.
BOOL WINAPI XImage_IsStretch(HIMAGE hImage) //是否拉伸图片
{
	IsHImageDebug(hImage, __FUNCTION__);
	return XC_IMAGE_STRETCH == ((ximage_*)hImage)->flag ? TRUE : FALSE;
}

/// @brief 是否为自适应图片句柄
/// @param hImage  图片句柄.
/// @return  如果是返回TRUE,否则相反.
BOOL WINAPI XImage_IsAdaptive(HIMAGE hImage) //是否为自适应图片
{
	IsHImageDebug(hImage, __FUNCTION__);
	return XC_IMAGE_ADAPTIVE == ((ximage_*)hImage)->flag ? TRUE : FALSE;
}

/// @brief 是否为平铺图片
/// @param hImage  图片句柄.
/// @return  如果是返回TRUE,否则相反.
BOOL WINAPI XImage_IsTile(HIMAGE hImage)
{
	IsHImageDebug(hImage, __FUNCTION__);
	return XC_IMAGE_TILE == ((ximage_*)hImage)->flag ? TRUE : FALSE;
}

/// @brief 设置图片绘制类型
/// @param hImage  图片句柄.
/// @param type  图片绘制类型.
/// @return  如果是返回TRUE,否则相反.
BOOL WINAPI XImage_SetDrawType(HIMAGE hImage, int type)
{
	IsHImageDebug(hImage, __FUNCTION__);

	if (XC_IMAGE_DEFAULT || XC_IMAGE_STRETCH | XC_IMAGE_TILE)
	{
		((ximage_*)hImage)->flag = type;
		return TRUE;
	}
	else
	{
		::MessageBox(NULL, L"错误: XImage_SetDrawType() 函数不接受的类型", L"提示", 0);
	}
	return NULL;
}

/// @brief 设置图片自适应
/// @param hImage  图片句柄.
/// @param x1 坐标.
/// @param x2 坐标.
/// @param y1 坐标.
/// @param y2 坐标.
/// @return  如果是返回TRUE,否则相反.
BOOL WINAPI XImage_SetDrawTypeAdaptive(HIMAGE hImage, int x1, int x2, int y1, int y2) //设置图片自适应
{
	IsHImageDebug(hImage, __FUNCTION__);
	if (x1 > x2) return FALSE;
	if (y1 > y2) return FALSE;

	((ximage_*)hImage)->imageX1 = x1;
	((ximage_*)hImage)->imageX2 = x2;
	((ximage_*)hImage)->imageY1 = y1;
	((ximage_*)hImage)->imageY1 = y2;
	return TRUE;
}

/// @brief 指定图片透明颜色.
/// @param hImage  图片句柄.
/// @param color   RGB颜色.
void WINAPI XImage_SetTranColor(HIMAGE hImage, COLORREF color) //设置透明色
{
	IsHImageDebug(hImage, __FUNCTION__);
	((ximage_*)hImage)->transparentColor.SetFromCOLORREF(color);
}

/// @brief 指定图片透明颜色及透明度.
/// @param hImage  图片句柄.
/// @param color   RGB颜色.
/// @param tranColor  透明色的透明度.
void WINAPI XImage_SetTranColorEx(HIMAGE hImage, COLORREF color, byte tranColor) //设置透明色
{
	IsHImageDebug(hImage, __FUNCTION__);
	((ximage_*)hImage)->transparentColor = Color(tranColor, GetRValue(color), GetGValue(color), GetBValue(color));
}

/// @brief 启用或关闭图片透明色.
/// @param hImage  图片句柄.
/// @param bEnable   启用TRUE,关闭FALSE.
void WINAPI XImage_EnableTranColor(HIMAGE hImage, BOOL bEnable) //启用透明色
{
	IsHImageDebug(hImage, __FUNCTION__);
	((ximage_*)hImage)->bTransparentColor = bEnable;
}

/// @brief 启用或关闭自动销毁,当与UI元素关联时有效
/// @param hImage  图片句柄.
/// @param bEnable   启用自动销毁TRUE,关闭自动销毁FALSE.
void WINAPI XImage_EnableAutoDestroy(HIMAGE hImage, BOOL bEnable) //启用或关闭自动销毁,当与UI元素关联时有效
{
	IsHImageDebug(hImage, __FUNCTION__);
	ximage_ *pImage = (ximage_*)hImage;
	if (bEnable == pImage->bAutoDestroy)
		return;

	pImage->bAutoDestroy = bEnable;

	if (bEnable)
	{
		pImage->refCount--;
	}
	else
	{
		pImage->refCount++;
	}
}

/// @brief 获取图片绘制类型
/// @param hImage  图片句柄.
/// @return  图片绘制类型.
int WINAPI XImage_GetDrawType(HIMAGE hImage)
{
	IsHImageDebug(hImage, __FUNCTION__);
	return ((ximage_*)hImage)->flag;
}

/// @brief 加载图片从资源.
/// @param id     资源ID.
/// @param pType  资源类型.
/// @param bStretch 是否拉伸图片
/// @return  图片句柄.
HIMAGE WINAPI XImage_LoadRes(int id, wchar_t *pType, BOOL bStretch)
{
	if (NULL == pType) return NULL;

	HIMAGE hImage = Image_LoadRes(id, pType);
	if (hImage)
	{
		if (bStretch)
			((ximage_*)hImage)->flag = XC_IMAGE_STRETCH;
		return hImage;
	}
	return NULL;
}

/// @brief 加载图片从资源,自适应图片.
/// @param id     资源ID.
/// @param pType  资源类型.
/// @param x1 坐标.
/// @param x2 坐标.
/// @param y1 坐标.
/// @param y2 坐标.
/// @return  图片句柄.
HIMAGE WINAPI XImage_LoadResAdaptive(int id, wchar_t *pType, int x1, int x2, int y1, int y2) //从资源中加载图片
{
	if (x1 > x2) return NULL;
	if (y1 > y2) return NULL;

	HIMAGE hImage = XImage_LoadRes(id, pType);
	if (hImage)
	{
		ximage_ *pXImage = (ximage_*)hImage;

		pXImage->flag = XC_IMAGE_ADAPTIVE;
		pXImage->imageWidth = pXImage->pImage->GetWidth();
		pXImage->imageHeight = pXImage->pImage->GetHeight();
		pXImage->imageX1 = x1;
		pXImage->imageX2 = x2;
		pXImage->imageY1 = y1;
		pXImage->imageY2 = y2;

		return hImage;
	}
	return NULL;
}

/// @brief 获取图片宽度.
/// @param hImage 图片句柄.
/// @return  图片宽度.
int WINAPI XImage_GetWidth(HIMAGE hImage)
{
	IsHImageDebug(hImage, __FUNCTION__);
	ximage_  *pImage = (ximage_*)hImage;
	return pImage->pImage->GetWidth();
}

/// @brief 获取图片高度.
/// @param hImage 图片句柄.
/// @return  图片高度.
int WINAPI XImage_GetHeight(HIMAGE hImage)
{
	IsHImageDebug(hImage, __FUNCTION__);
	ximage_  *pImage = (ximage_*)hImage;
	return pImage->pImage->GetHeight();
}

/// @brief 销毁图片接口.
/// @param hImage 图片句柄.
void WINAPI XImage_Destroy(HIMAGE hImage)
{
	IsHImageDebug(hImage, __FUNCTION__);

	ximage_  *pImage = (ximage_*)hImage;
	if (pImage->refCount == 1)
	{
		if (pImage->pImage)
		{
			delete pImage->pImage;
		}
		else if (pImage->bBitmap && pImage->pBitmap)
		{
			delete pImage->pBitmap;
		}

		free(pImage);
	}
	else
		pImage->refCount--;
}


///@}

void Image_AddImage(HIMAGE &hImage, HIMAGE hImageNew)
{
	if (hImage)
	{
		XImage_Destroy(hImage);
		hImage = NULL;
	}
	if (hImageNew)
	{
		IsHImageDebug(hImageNew, __FUNCTION__);
		hImage = hImageNew;
		Image_AddRef(hImageNew);
	}
}

HIMAGE Image_AddRef(HIMAGE hImage) //增加引用计数
{
	if (hImage)
	{
		((ximage_*)hImage)->refCount++;
		return hImage;
	}
	return NULL;
}

HIMAGE Image_LoadFile(wchar_t *pImageName)
{
	Image *pImg = new Image(pImageName);
	if (NULL == pImg) return NULL;
	if (Gdiplus::Ok == pImg->GetLastStatus())
	{
		ximage_ *pXImage = (ximage_*)malloc(sizeof(ximage_));
		memset(pXImage, 0, sizeof(ximage_));
		pXImage->object.type = XC_IMAGE;
		pXImage->type = 0;
		pXImage->refCount = 0;
		pXImage->flag = XC_IMAGE_DEFAULT;//bStretch ? XC_IMAGE_STRETCH : XC_IMAGE_DEFAULT;
		pXImage->bAutoDestroy = TRUE;

		pXImage->pImage = pImg;
		return (HIMAGE)pXImage;
	}
	XTRACEW(L"XImage_LoadFile(\"%s\"),可能图片路径错误 \n", pImageName);
	delete pImg;
	return NULL;
}

HIMAGE Image_LoadRes(int id, wchar_t *pType)
{
	Image *pImg = NULL;
	BOOL bResult = ImageFromIDResource(id, pType, pImg);
	if (pImg)
	{
		if (Gdiplus::Ok == pImg->GetLastStatus())
		{
			ximage_ *pXImage = (ximage_*)malloc(sizeof(ximage_));
			memset(pXImage, 0, sizeof(ximage_));
			pXImage->object.type = XC_IMAGE;
			pXImage->type = 0;
			pXImage->refCount = 0;
			pXImage->flag = XC_IMAGE_DEFAULT;//bStretch ? XC_IMAGE_STRETCH : XC_IMAGE_DEFAULT;
			pXImage->pImage = pImg;
			pXImage->bAutoDestroy = TRUE;

			return (HIMAGE)pXImage;
		}
		delete pImg;
	}
	return NULL;
}

HIMAGE Image_LoadZip(wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword)//从ZIP中加载图片
{
	char zipfilename[MAX_PATH] = { 0 };
	WideCharToMultiByte(CP_ACP, NULL, pZipFileName, wcslen(pZipFileName), zipfilename, MAX_PATH, NULL, NULL);

	char filename_to_extract[MAX_PATH] = { 0 };
	WideCharToMultiByte(CP_ACP, NULL, pImageName, wcslen(pImageName), filename_to_extract, MAX_PATH, NULL, NULL);

	char password[MAX_PATH] = { 0 };
	if (pPassword)
		WideCharToMultiByte(CP_ACP, NULL, pPassword, wcslen(pPassword), password, MAX_PATH, NULL, NULL);

	//const char *password=NULL;
	//char *zipfilename="C:\\Users\\mengfei\\Desktop\\myzip.zip";  //压缩包
	//char *filename_to_extract="dirtt/123.txt";   //提取文件名
	//char *filename_to_extract="btn.bmp";   //提取文件名

	unzFile zipFile = NULL;
	zipFile = unzOpen64(zipfilename); //打开压缩包
	if (zipFile == NULL)
	{
		return NULL;
	}

	int outSize = 0;
	void  *data = NULL;
	if (pPassword)
		data = do_extract_onefile(zipFile, filename_to_extract, password, outSize);
	else
		data = do_extract_onefile(zipFile, filename_to_extract, NULL, outSize);

	unzClose(zipFile);

	if (data)
	{
		HGLOBAL   hJPG = ::GlobalAlloc(GMEM_MOVEABLE, outSize);
		LPVOID   lpJGP = ::GlobalLock(hJPG);
		memcpy(lpJGP, data, outSize);
		::GlobalUnlock(hJPG);
		LPSTREAM   pstm = NULL;
		HRESULT   hr = CreateStreamOnHGlobal(hJPG, TRUE, &pstm);
		assert(SUCCEEDED(hr) && pstm);
		Image *pImg = Image::FromStream(pstm);
		pstm->Release();

		free(data);
		if (pImg)
		{
			if (Gdiplus::Ok == pImg->GetLastStatus())
			{
				ximage_  *pXImage = (ximage_*)malloc(sizeof(ximage_));
				memset(pXImage, 0, sizeof(ximage_));
				pXImage->object.type = XC_IMAGE;
				pXImage->type = 0;
				pXImage->refCount = 0;
				pXImage->flag = XC_IMAGE_DEFAULT; //bStretch ? XC_IMAGE_STRETCH : XC_IMAGE_DEFAULT;
				pXImage->pImage = pImg;
				pXImage->bAutoDestroy = TRUE;

				return (HIMAGE)pXImage;
			}
			else
				delete pImg;
		}
	}
	return NULL;
}

////////////////////////////////////
BOOL ImageFromIDResource(int nID, wchar_t *pType, Image * &pImg)
{
	HMODULE hInst = GetModuleHandle(NULL);
	if (RT_BITMAP == pType)
	{
		Bitmap BkImage(hInst, MAKEINTRESOURCEW(nID));
		RectF sourceRect(0.0f, 0.0f, (REAL)(BkImage.GetWidth()), (REAL)(BkImage.GetHeight()));
		pImg = BkImage.Clone(sourceRect, PixelFormatDontCare);
	}
	else
	{
		wchar_t * lpRes = MAKEINTRESOURCE(nID);
		HRSRC   hRsrc = ::FindResource(hInst, lpRes, pType);
		if (NULL == hRsrc) return FALSE;
		HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
		DWORD   dwSize = SizeofResource(hInst, hRsrc);
		LPVOID   lpData = LockResource(hGlobal);
		HGLOBAL   hJPG = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
		LPVOID   lpJGP = ::GlobalLock(hJPG);
		memcpy(lpJGP, lpData, dwSize);
		::GlobalUnlock(hJPG);
		LPSTREAM   pstm = NULL;
		HRESULT   hr = CreateStreamOnHGlobal(hJPG, TRUE, &pstm);
		assert(SUCCEEDED(hr) && pstm);
		pImg = Image::FromStream(pstm);//new Image(pstm);
		pstm->Release();

		BOOL hrr = FreeResource(hGlobal);
	}
	return TRUE;
}

BOOL ImageFromIDResourceToBitmap(int nID, wchar_t *pType, HBITMAP &hBitmap)
{
	HMODULE hInst = GetModuleHandle(NULL);

	Bitmap BkImage(hInst, MAKEINTRESOURCEW(nID));
	Gdiplus::Status result = BkImage.GetHBITMAP(NULL, &hBitmap);
	if (result == Gdiplus::Ok)
		return TRUE;
	else
		return FALSE;
}