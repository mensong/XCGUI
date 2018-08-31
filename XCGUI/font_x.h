#pragma once



struct font_xc_
{
	object_ object;
	//-----------------------
	HFONT     hFont;
	LOGFONT   info;

	int    refCount; //引用计数,当值为0时 销毁对象
};

//炫彩字体,当字体句柄与某个元素关联后,会自动释放.


XC_API HFONTX WINAPI XFont_Create(int size);//创建字体
XC_API HFONTX WINAPI XFont_Create2(wchar_t *pName = L"宋体", int size = 12, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
XC_API HFONTX WINAPI XFont_CreateEx(LOGFONT *pFontInfo);
XC_API void  WINAPI XFont_Destroy(HFONTX hFontX);  //销毁字体
XC_API HFONT WINAPI XFont_GetHFONT(HFONTX hFontX);



//私有方法:
void  Font_AddFontX(HFONTX &hFontX, HFONTX hFontXNew); //字体与元素关联，增加引用计数
HFONTX Font_AddRef(HFONTX hFontX);   //增加引用计数