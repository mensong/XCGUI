#include "StdAfx.h"
#include "zlib/unzip.h"


ImageEx::ImageEx(IStream *pStream) :Image(pStream, FALSE)
{
	Initialize();

	if (false == TestForAnimatedGIF())
		lastResult = InvalidParameter;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	ImageEx::ImageEx
// 
// DESCRIPTION:	Constructor for constructing images from a file
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
ImageEx::ImageEx(const WCHAR* filename)//, BOOL useEmbeddedColorManagement) : Image(filename, useEmbeddedColorManagement)
	: Image(filename, FALSE)
{
	Initialize();

	if (false == TestForAnimatedGIF())
		lastResult = InvalidParameter;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	ImageEx::~ImageEx
// 
// DESCRIPTION:	Free up fresources
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
ImageEx::~ImageEx()
{
	Destroy();
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	InitAnimation
// 
// DESCRIPTION:	Prepare animated GIF
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////

//bool ImageEx::InitAnimation(HWND hWnd,int x,int y)// POINT &pt)
bool ImageEx::InitAnimation(int x, int y)
{
	m_pt.x = x;
	m_pt.y = y;

	if (IsAnimatedGIF())
	{
		return true;
	}
	return false;
}



////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	GetSize
// 
// DESCRIPTION:	Returns Width and Height object
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
SIZE ImageEx::GetSize()
{
	SIZE size = { GetWidth(), GetHeight() };
	return size;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	TestForAnimatedGIF
// 
// DESCRIPTION:	Check GIF/Image for avialability of animation
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool ImageEx::TestForAnimatedGIF()
{
	UINT count = 0;
	count = GetFrameDimensionsCount();
	GUID* pDimensionIDs = new GUID[count];

	// Get the list of frame dimensions from the Image object.
	GetFrameDimensionsList(pDimensionIDs, count);

	// Get the number of frames in the first dimension.
	m_nFrameCount = GetFrameCount(&pDimensionIDs[0]);

	// Assume that the image has a property item of type PropertyItemEquipMake.
	// Get the size of that property item.
	int nSize = GetPropertyItemSize(PropertyTagFrameDelay);
	if (nSize > 0)
	{
		// Allocate a buffer to receive the property item.
		m_pPropertyItem = (PropertyItem*)malloc(nSize);

		GetPropertyItem(PropertyTagFrameDelay, nSize, m_pPropertyItem);

		delete  pDimensionIDs;
	}
	else
	{
		XTRACE("GIF图片错误\n");
		delete pDimensionIDs;
		return false;
	}

	return true;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	ImageEx::Initialize
// 
// DESCRIPTION:	Common function called from Constructors
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
void ImageEx::Initialize()
{
	m_nFramePosition = 0;
	m_nFrameCount = 0;
	m_pPropertyItem = NULL;
	m_hInst = GetModuleHandle(NULL);
}

int ImageEx::DrawFrameGIF2(HDC hdc)
{
	GUID   pageGuid = FrameDimensionTime;

	long hmWidth = GetWidth();
	long hmHeight = GetHeight();

	if (hdc)
	{
		Graphics graphics(hdc);
		graphics.DrawImage(this, m_pt.x, m_pt.y, hmWidth, hmHeight);
	}

	SelectActiveFrame(&pageGuid, m_nFramePosition++);

	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;

	int lPause = ((int*)m_pPropertyItem->value)[m_nFramePosition] * 10;

	return lPause;
}

int	ImageEx::DrawFrameGIF2(HDC hdc, int x, int y)
{
	//GUID   pageGuid = FrameDimensionTime;

	long hmWidth = GetWidth();
	long hmHeight = GetHeight();

	if (hdc)
	{
		EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
		Graphics graphics(hdc);
		Gdiplus::Status Statu = graphics.DrawImage(this, x, y, hmWidth, hmHeight);

		if (Gdiplus::Ok != Statu)
			XTRACE("绘制错误 -------------------\n");
		LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
	}

	//SelectActiveFrame(&pageGuid, m_nFramePosition++);		

	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;

	int  *p = (int*)m_pPropertyItem->value;
	int lPause = p[m_nFramePosition] * 10;
	if (lPause < 10)
		lPause = 100;
	return lPause;
}

void ImageEx::NextFrame()
{
	EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
	m_nFramePosition++;

	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;
	GUID   pageGuid = FrameDimensionTime;

	SelectActiveFrame(&pageGuid, m_nFramePosition);
	LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
}

int ImageEx::GetFrameCount2()
{
	return m_nFrameCount;
}

int ImageEx::GetCurrentFramePosition()
{
	return m_nFramePosition;
}

void ImageEx::Destroy()
{
	free(m_pPropertyItem);

	m_pPropertyItem = NULL;
}


/////////////////////////////////////

/// @defgroup gifImage GIF动画元素
/// @ingroup groupOther
/// 显示GIF动画图片.
/// @{


/// @brief 创建元素.
/// @param x  x坐标.
/// @param y  y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent  父是窗口句柄或元素句柄..
/// @return 元素句柄.
HELE WINAPI XGif_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	gif_ *pNew = (gif_*)malloc(sizeof(gif_));
	memset(pNew, 0, sizeof(gif_));

	Gif_Init((HELE)pNew, x, y, cx, cy, XC_GIF, hParent);

	return (HELE)pNew;
}

void Gif_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_GIF);

	XEle_RegisterMessage(hEle, XM_PAINT, Gif_OnDraw);
	XEle_RegisterEvent(hEle, XE_DESTROY, Gif_OnDestroy);
}

/// @brief 设置GIF动画图片,从文件中加载图片.
/// @param hEle  元素句柄.
/// @param pImageName  GIF图片名称.
void WINAPI XGif_SetImage(HELE hEle, wchar_t *pImageName)
{
	IsGifDebug(hEle, __FUNCTION__);
	gif_ *pObject = (gif_*)hEle;

	if (pObject->pGif)
	{
		delete pObject->pGif;
		pObject->pGif = NULL;
	}

	if (pImageName)
	{
		wchar_t *pFile = wcsrchr(pImageName, L'.');
		if (pFile)
		{
			if (0 == wcscmp(pFile, L".gif") || 0 == wcscmp(pFile, L".GIF"))
			{
				pObject->pGif = new ImageEx(pImageName);

				if (pObject->pGif->InitAnimation(0, 0))
					SetTimer(XEle_GetHWnd(hEle), (int)hEle, 100, Gif_TimerProc);
			}
		}
	}
}

/// @brief 设置GIF动画图片,从资源中加载图片.
/// @param hEle  元素句柄.
/// @param id    资源ID.
/// @param pType 资源类型.
void WINAPI XGif_SetImageRes(HELE hEle, int id, wchar_t *pType)
{
	IsGifDebug(hEle, __FUNCTION__);
	gif_ *pObject = (gif_*)hEle;

	if (pObject->pGif)
	{
		delete pObject->pGif;
		pObject->pGif = NULL;
	}

	if (pType)
	{
		HMODULE hInst = GetModuleHandle(NULL);
		wchar_t * lpRes = MAKEINTRESOURCE(id);
		HRSRC   hRsrc = ::FindResource(hInst, lpRes, pType);
		if (NULL == hRsrc) return;
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

		pObject->pGif = new ImageEx(pstm);

		pstm->Release();

		BOOL hrr = FreeResource(hGlobal);

		if (Gdiplus::Ok != (pObject->pGif->GetLastStatus()))
		{
			delete pObject->pGif;
			pObject->pGif = NULL;
		}

		if (pObject->pGif->InitAnimation(0, 0))
			SetTimer(XEle_GetHWnd(hEle), (int)hEle, 100, Gif_TimerProc);
	}
}

/// @brief 设置GIF动画图片,从ZIP压缩包中加载图片.
/// @param hEle  元素句柄.
/// @param pZipFileName  压缩包文件.
/// @param pImageName    GIF图片名.
/// @param pPassword     压缩包密码.
void WINAPI XGif_SetImageZip(HELE hEle, wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword)
{
	IsGifDebug(hEle, __FUNCTION__);
	gif_ *pObject = (gif_*)hEle;

	if (pObject->pGif)
	{
		delete pObject->pGif;
		pObject->pGif = NULL;
	}


	if (NULL == pZipFileName || NULL == pImageName)
	{
		return;
	}

	IsImageTypeDebug(_T(__FUNCTION__), pImageName);

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
		XTRACE("打开ZIP压缩包失败");
		return;
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
		//Image *pImg=Image::FromStream(pstm);
		pObject->pGif = new ImageEx(pstm);
		pstm->Release();

		free(data);
		if (Gdiplus::Ok != (pObject->pGif->GetLastStatus()))
		{
			delete pObject->pGif;
			pObject->pGif = NULL;
		}

		if (pObject->pGif->InitAnimation(0, 0))
			SetTimer(XEle_GetHWnd(hEle), (int)hEle, 100, Gif_TimerProc);
	}
}

///@}


void CALLBACK Gif_OnDestroy(HELE hEle)  //销毁
{
	gif_ *pObject = (gif_*)hEle;
	if (pObject->pGif)
		delete pObject->pGif;
}

void Gif_DrawFrameGif(HELE hEle, HDRAW hDraw)
{
	gif_ *pObject = (gif_*)hEle;
	if (pObject->pGif)
	{
		HDC hdc = XDraw_GetHDC_(hDraw);
		int pause = pObject->pGif->DrawFrameGIF2(hdc);
		SetTimer(XEle_GetHWnd(hEle), (int)hEle, pause, Gif_TimerProc);
	}
}

BOOL CALLBACK Gif_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	Gif_DrawFrameGif(hEle, hDraw);

	if (((ele_*)hEle)->bBorder)
	{
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, ((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw, &rect, hBrush);
		//	DeleteObject(hBrush);
	}
	return TRUE;
}

VOID CALLBACK Gif_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	gif_ *pObject = (gif_*)idEvent;

	ImageEx *pImageEx = pObject->pGif;

	//pImageEx->DrawFrameGIF();

	KillTimer(hwnd, idEvent);
	//DrawFrameGIF();
	XEle_RedrawEle((HELE)pObject);

}