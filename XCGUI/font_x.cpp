#include "StdAfx.h"

/// @defgroup font_xc  炫彩字体(FontX)
/// @ingroup groupOther
/// @{


/// @brief 创建炫彩字体,当字体句柄与元素关联后,会自动释放.
/// @param size   字体大小.
/// @return 字体句柄.
HFONTX WINAPI XFont_Create(int size)  //创建字体
{
	LOGFONT info;
	info.lfHeight = size;
	info.lfWidth = 0;
	info.lfEscapement = 0;
	info.lfOrientation = 0;
	info.lfWeight = FW_NORMAL;
	info.lfItalic = FALSE;
	info.lfUnderline = FALSE;
	info.lfStrikeOut = FALSE;
	info.lfCharSet = GB2312_CHARSET;
	info.lfOutPrecision = OUT_DEFAULT_PRECIS;
	info.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	info.lfQuality = DEFAULT_QUALITY;
	info.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(info.lfFaceName, L"宋体");

	return XFont_CreateEx(&info);
}

/// @brief 创建炫彩字体.
/// @param  pName  字体名称.
/// @param  size   字体大小.
/// @param  bBold  是否为粗体.
/// @param  bItalic  是否为斜体.
/// @param  bUnderline   是否有下划线.
/// @param  bStrikeOut   是否有删除线.
/// @return 字体句柄.
HFONTX WINAPI XFont_Create2(wchar_t *pName, int size, BOOL bBold, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut)
{
	LOGFONT info;
	DWORD nWeight = FW_NORMAL;
	if (bBold)
		nWeight = FW_BOLD;

	info.lfHeight = size;
	info.lfWidth = 0;
	info.lfEscapement = 0;
	info.lfOrientation = 0;
	info.lfWeight = nWeight;
	info.lfItalic = bItalic;
	info.lfUnderline = bUnderline;
	info.lfStrikeOut = bStrikeOut;
	info.lfCharSet = GB2312_CHARSET;
	info.lfOutPrecision = OUT_DEFAULT_PRECIS;
	info.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	info.lfQuality = DEFAULT_QUALITY;
	info.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

	wcscpy_s(info.lfFaceName, pName);

	return XFont_CreateEx(&info);
}
/// @brief 创建炫彩字体.
/// @param  pFontInfo  字体信息.
/// @return 字体句柄.
HFONTX WINAPI XFont_CreateEx(LOGFONT *pFontInfo)
{
	HFONT  hFont = CreateFontIndirect(pFontInfo);
	if (NULL == hFont)
		return NULL;

	font_xc_  *pFont_xc = (font_xc_*)malloc(sizeof(font_xc_));
	if (pFont_xc)
	{
		memset(pFont_xc, 0, sizeof(font_xc_));

		pFont_xc->hFont = hFont;
		pFont_xc->info = *pFontInfo;
		pFont_xc->refCount = 0;
		pFont_xc->object.type = XC_FONT;
	}

	return (HFONTX)pFont_xc;
}
/// @brief 销毁炫彩字体.
/// @param  hFontX 字体句柄.
void WINAPI XFont_Destroy(HFONTX hFontX)
{
	IsFontDebug(hFontX, __FUNCTION__);
	font_xc_  *pFont_xc = (font_xc_*)hFontX;

	if (pFont_xc->refCount == 1)
	{
		if (pFont_xc->hFont)
			DeleteObject(pFont_xc->hFont);

		free(pFont_xc);
	}
	else
		pFont_xc->refCount--;
}

/// @brief 获取字体HFONT句柄..
/// @param  hFontX 字体句柄.
/// @return 返回HFONT句柄.
HFONT WINAPI XFont_GetHFONT(HFONTX hFontX)
{
	if (hFontX)
		return ((font_xc_*)hFontX)->hFont;
	return (HFONT)GetStockObject(DEFAULT_GUI_FONT);
}

void Font_AddFontX(HFONTX &hFontX, HFONTX hFontXNew) //字体与元素关联，增加引用计数
{
	if (hFontX)
	{
		XFont_Destroy(hFontX);
		hFontX = NULL;
	}
	if (hFontXNew)
	{
		IsFontDebug(hFontXNew, __FUNCTION__);
		hFontX = hFontXNew;
		Font_AddRef(hFontXNew);
	}
}

HFONTX Font_AddRef(HFONTX hFontX)   //增加引用计数
{
	if (hFontX)
	{
		((font_xc_*)hFontX)->refCount++;
		return hFontX;
	}
	return NULL;
}

/// @}
