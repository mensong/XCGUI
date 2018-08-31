/**************************************************************************\
*
* Copyright (c)  ìÅ²Ê½çÃæ¿â. All Rights Reserved.
*
* ìÅ²Ê½çÃæ¿â - ¹Ù·½ÍøÕ¾ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup check ¸´Ñ¡°´Å¥(Check)
/// @ingroup groupElements
/// @{

/// @brief ´´½¨¸´Ñ¡°´Å¥ÔªËØ.
/// @param x  ÔªËØx×ø±ê.
/// @param y  ÔªËØy×ø±ê.
/// @param cx  ¿í¶È.
/// @param cy  ¸ß¶È.
/// @param pTitle  ÄÚÈÝ.
/// @param hParent  ¸¸Îª´°¿Ú¾ä±ú»òÔªËØ¾ä±ú.
/// @return ¸´Ñ¡°´Å¥¾ä±ú.
HELE WINAPI XCheck_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent)  //´´½¨°´Å¥
{
	check_ *pCheck = (check_*)malloc(sizeof(check_));
	memset(pCheck, 0, sizeof(check_));

	Check_Init((HELE)pCheck, x, y, cx, cy, XC_CHECK, pTitle, hParent);
	return (HELE)pCheck;
}


void Check_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent) //³õÊ¼»¯×¢²á
{
	Btn_Init(hEle, x, y, cx, cy, eleType, pTitle, hParent);

	AddTypeDebug(hEle, XC_CHECK);

	((button_*)hEle)->textFlag = DT_VCENTER | DT_SINGLELINE;

	XEle_RegisterMessage(hEle, XM_PAINT, Check_OnDraw);
	XEle_RegisterEvent(hEle, XE_BNCLICK, Check_OnEventBtnClick);
	XEle_RegisterEvent(hEle, XE_DESTROY, Check_OnDestroy);
}

//ÌùÍ¼:

/// @brief ÉèÖÃÊó±êÀë¿ªºÍÎ´Ñ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle   ÔªËØ¾ä±ú.
/// @param hImage Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageLeave_UnCheck(HELE hEle, HIMAGE hImage)  //Êó±êÀë¿ªÊ±Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	XBtn_SetImageLeave(hEle, hImage);
}

/// @brief ÉèÖÃÊó±êÍ£ÁôºÍÎ´Ñ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageStay_UnCheck(HELE hEle, HIMAGE hImage)   //Êó±êÍ£ÁôÊ±Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	XBtn_SetImageStay(hEle, hImage);
}

/// @brief ÉèÖÃÊó±ê°´ÏÂºÍÎ´Ñ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageDown_UnCheck(HELE hEle, HIMAGE hImage)   //Êó±ê°´ÏÂÊ±Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	XBtn_SetImageDown(hEle, hImage);
}

/// @brief ÉèÖÃ½ûÓÃºÍÎ´Ñ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageDisable_UnCheck(HELE hEle, HIMAGE hImage) //°´Å¥½ûÓÃ×´Ì¬Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	XBtn_SetImageDisable(hEle, hImage);
}

/// @brief ÉèÖÃÊó±êÀë¿ªºÍÑ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageLeave_Check(HELE hEle, HIMAGE hImage)  //Êó±êÀë¿ªÊ±Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_leave_check, hImage);
}

/// @brief ÉèÖÃÊó±êÍ£ÁôºÍÑ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageStay_Check(HELE hEle, HIMAGE hImage)   //Êó±êÍ£ÁôÊ±Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_stay_check, hImage);
}
/// @brief ÉèÖÃÊó±ê°´ÏÂºÍÑ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageDown_Check(HELE hEle, HIMAGE hImage)  //Êó±ê°´ÏÂÊ±Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_down_check, hImage);
}

/// @brief ÉèÖÃ½ûÓÃºÍÑ¡Ôñ×´Ì¬Ê±ÌùÍ¼.
/// @param hEle    ÔªËØ¾ä±ú.
/// @param hImage  Í¼Æ¬¾ä±ú.
void WINAPI XCheck_SetImageDisable_Check(HELE hEle, HIMAGE hImage) //°´Å¥½ûÓÃ×´Ì¬Í¼Æ¬
{
	IsCheckDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_disable_check, hImage);
}

BOOL CALLBACK Check_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (XBtn_IsCheck(hEle)) //¹´Ñ¡
	{
		Check_DrawCheck(hEle, hDraw, rect);
	}
	else
	{
		Check_DrawUnCheck(hEle, hDraw, rect);
	}

	if (((ele_*)hEle)->bDrawFocus && hEle == XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //»æÖÆ½¹µã
	{
		RECT rcFocus = { 0,0,rect.right,rect.bottom };
		XDraw_FocusRect_(hDraw, &rcFocus);
	}
	return TRUE;
}

void Check_DrawCheck(HELE hEle, HDRAW hDraw, RECT &rect) //»æÖÆ¹´Ñ¡×´Ì¬
{
	RECT rcText = rect;
	rcText.left += 17;
	int top = rect.bottom / 2 - 6;  //»æÖÆÔ²¶¥µã
	if (FALSE == ((ele_*)hEle)->bEnable)  //½ûÓÃ)
	{
		if (CHECK(hEle)->hImage_disable_check)
		{
			XDraw_HImageSuper_(hDraw, CHECK(hEle)->hImage_disable_check, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(80, 80, 80), TRUE);
		}
		//»æÖÆÎÄ±¾
		COLORREF color = XDraw_SetTextColor_(hDraw, RGB(128, 128, 128));
		wchar_t *pText = XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_VCENTER | DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw, color);
		return;
	}
	else if (STATE_LEAVE == ((button_*)hEle)->state)	//Àë¿ª
	{
		if (CHECK(hEle)->hImage_leave_check)
		{
			XDraw_HImageSuper_(hDraw, CHECK(hEle)->hImage_leave_check, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(80, 80, 80), TRUE);
		}
	}
	else if (STATE_STAY == ((button_*)hEle)->state)//Í£Áô
	{
		if (CHECK(hEle)->hImage_stay_check)
		{
			XDraw_HImageSuper_(hDraw, CHECK(hEle)->hImage_stay_check, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(39, 135, 194), TRUE);
		}
	}
	else if (STATE_DOWN == ((button_*)hEle)->state) //°´ÏÂ
	{
		if (CHECK(hEle)->hImage_down_check)
		{
			XDraw_HImageSuper_(hDraw, CHECK(hEle)->hImage_down_check, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(39, 135, 194), TRUE);
		}
		rcText.top += 2;
	}
	//»æÖÆÎÄ±¾
	wchar_t *pText = XBtn_GetText(hEle);
	if (pText)
	{
		XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, ((button_*)hEle)->textFlag);//DT_VCENTER| DT_SINGLELINE);
	}
}

void Check_DrawUnCheck(HELE hEle, HDRAW hDraw, RECT &rect) //»æÖÆÎ´¹´Ñ¡×´Ì¬
{
	RECT rcText = rect;
	rcText.left += 17;
	int top = rect.bottom / 2 - 6;  //»æÖÆÔ²¶¥µã

	if (FALSE == ((ele_*)hEle)->bEnable)  //½ûÓÃ)
	{
		if (BUTTON(hEle)->hImage_disable)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_disable, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(80, 80, 80), FALSE);
		}
		//»æÖÆÎÄ±¾
		COLORREF color = XDraw_SetTextColor_(hDraw, RGB(128, 128, 128));
		wchar_t *pText = XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, DT_VCENTER | DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw, color);
		return;
	}
	else if (STATE_LEAVE == ((button_*)hEle)->state)	//Àë¿ª
	{
		if (BUTTON(hEle)->hImage_leave)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_leave, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(80, 80, 80), FALSE);
		}
	}
	else if (STATE_STAY == ((button_*)hEle)->state)//Í£Áô
	{
		if (BUTTON(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_stay, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(39, 135, 194), FALSE);
		}
	}
	else if (STATE_DOWN == ((button_*)hEle)->state) //°´ÏÂ
	{
		if (BUTTON(hEle)->hImage_down)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_down, &rect);
		}
		else
		{
			XDraw_Check_(hDraw, 2, top, RGB(39, 135, 194), FALSE);
		}
		rcText.top += 2;
	}

	//»æÖÆÎÄ±¾
	wchar_t *pText = XBtn_GetText(hEle);
	if (pText)
	{
		XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, ((button_*)hEle)->textFlag);
	}
}

BOOL CALLBACK Check_OnEventBtnClick(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		XBtn_SetCheck(hEle, !XBtn_IsCheck(hEle));
		XEle_RedrawEle(hEle);
		return TRUE;
	}
	return FALSE;
}

void CALLBACK Check_OnDestroy(HELE hEle)  //Ïú»Ù
{
	if (CHECK(hEle)->hImage_leave_check)   XImage_Destroy(CHECK(hEle)->hImage_leave_check);
	if (CHECK(hEle)->hImage_stay_check)    XImage_Destroy(CHECK(hEle)->hImage_stay_check);
	if (CHECK(hEle)->hImage_down_check)    XImage_Destroy(CHECK(hEle)->hImage_down_check);
	if (CHECK(hEle)->hImage_disable_check) XImage_Destroy(CHECK(hEle)->hImage_disable_check);
}

///@}