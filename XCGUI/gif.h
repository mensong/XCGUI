/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once



class ImageEx : public Image
{
public:
	//	ImageEx(int nID,wchar_t *pResType);
	ImageEx(const WCHAR* filename); //, BOOL useEmbeddedColorManagement = FALSE);
	ImageEx(IStream *pStream);

	~ImageEx();
public:

	SIZE GetSize();

	bool IsAnimatedGIF() { return m_nFrameCount > 1; }
	bool InitAnimation(int x, int y);
	void Destroy();

protected:

	bool TestForAnimatedGIF();
	void Initialize();

public:
	int	DrawFrameGIF2(HDC hdc);

	int	DrawFrameGIF2(HDC hdc, int x, int y); //绘制RichEdit GIF
	void NextFrame();

	int GetFrameCount2();
	int GetCurrentFramePosition();
protected:
	HINSTANCE		m_hInst;
	UINT			m_nFrameCount;
	UINT			m_nFramePosition;
	PropertyItem*	m_pPropertyItem;
	POINT			m_pt;
};


//GIF动画元素
struct gif_
{
	ele_ ele; //继承
	//-------------------

	ImageEx  *pGif;
};

//API:
XC_API HELE WINAPI XGif_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XGif_SetImage(HELE hEle, wchar_t  *pImageName);
XC_API void WINAPI XGif_SetImageRes(HELE hEle, int id, wchar_t *pType);
XC_API void WINAPI XGif_SetImageZip(HELE hEle, wchar_t *pZipFileName, wchar_t *pImageName, wchar_t *pPassword = NULL);

//私有方法:
void Gif_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);

void Gif_DrawFrameGif(HELE hEle, HDRAW hDraw);

//回调函数:
void CALLBACK Gif_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Gif_OnDraw(HELE hEle, HDRAW hDraw);

VOID CALLBACK Gif_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


///////////////////////////////////////////////

