/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HELE WINAPI XBtn_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent)
{
	button_ *pNew = (button_*)malloc(sizeof(button_));
	if (pNew)
	{
		memset(pNew, 0, sizeof(button_));

		Btn_Init((HELE)pNew, x, y, cx, cy, XC_BUTTON, pTitle, hParent);

		return (HELE)pNew;
	}
	return NULL;
}

void Btn_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);

	AddTypeDebug(hEle, XC_BUTTON);
	BUTTON(hEle)->textFlag = DT_VCENTER | DT_SINGLELINE | DT_CENTER | DT_END_ELLIPSIS;
	XEle_EnableFocus(hEle, TRUE);
	XBtn_SetText(hEle, pTitle);

	XEle_RegisterMessage(hEle, XM_PAINT, Btn_OnDraw);

	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, Btn_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, Btn_OnLButtonUp);
	XEle_RegisterEvent(hEle, XE_KEYDOWN, Btn_OnEventKeyDown);

	XEle_RegisterEvent(hEle, XE_MOUSESTAY, Btn_OnEventMouseStay);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, Btn_OnEventMouseLeave);
	XEle_RegisterEvent(hEle, XE_SETFOCUS, Btn_OnEventSetFocus);
	XEle_RegisterEvent(hEle, XE_KILLFOCUS, Btn_OnEventKillFocus);
	XEle_RegisterEvent(hEle, XE_DESTROY, Btn_OnDestroy);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, Btn_OnMouseMove);
}

void CALLBACK Btn_OnDestroy(HELE hEle)  //销毁
{
	button_ *pButton = BUTTON(hEle);
	if (pButton->hString)
		XStr_Destroy(pButton->hString);

	if (pButton->hImage_leave) XImage_Destroy(pButton->hImage_leave);
	if (pButton->hImage_stay) XImage_Destroy(pButton->hImage_stay);
	if (pButton->hImage_down) XImage_Destroy(pButton->hImage_down);
	if (pButton->hImage_check) XImage_Destroy(pButton->hImage_check);
	if (pButton->hImage_disable) XImage_Destroy(pButton->hImage_disable);
	if (pButton->hImage_icon) XImage_Destroy(pButton->hImage_icon);

	if (pButton->pAnimation)
	{
		Animation_Remove(pButton->pAnimation);

		int count = XArray_GetCount(pButton->pAnimation->hArrayItem);
		for (int i = 0; i < count; i++)
		{
			button_animation_item_ *pItem = (button_animation_item_*)XArray_GetAt(pButton->pAnimation->hArrayItem, i);
			if (pItem->hImage) XImage_Destroy(pItem->hImage);
			free(pItem);
		}
		XArray_Destroy(pButton->pAnimation->hArrayItem);
		free(pButton->pAnimation);
		pButton->pAnimation = NULL;
	}
}

wchar_t * WINAPI XBtn_GetText(HELE hEle)
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (BUTTON(hEle)->hString)
		return XStr_GetBuffer(BUTTON(hEle)->hString);
	return NULL;
}

void WINAPI XBtn_SetText(HELE hEle, wchar_t *pText)
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (pText)
	{
		if (NULL == BUTTON(hEle)->hString)
			BUTTON(hEle)->hString = XStr_Create();
		XStr_SetString(BUTTON(hEle)->hString, pText);
	}
}

int WINAPI XBtn_GetState(HELE hEle)
{
	IsButtonDebug(hEle, __FUNCTION__);
	return BUTTON(hEle)->state;
}

void WINAPI XBtn_SetCheck(HELE hEle, BOOL bCheck)
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (BUTTON(hEle)->bCheck == bCheck)
		return;

	BUTTON(hEle)->bCheck = bCheck;
	if (XC_RADIO == ((ele_*)hEle)->eleType)
	{
		if (RADIO(hEle)->hBindEle)
		{
			if (BUTTON(hEle)->bCheck)
			{
				XEle_ShowEle(RADIO(hEle)->hBindEle, TRUE);
				XEle_RedrawEle(RADIO(hEle)->hBindEle);
			}
			else
			{
				XEle_RedrawEle(RADIO(hEle)->hBindEle);
				XEle_ShowEle(RADIO(hEle)->hBindEle, FALSE);
			}
		}
	}
}

BOOL WINAPI XBtn_IsCheck(HELE hEle) //按钮是否被选中
{
	IsButtonDebug(hEle, __FUNCTION__);
	return BUTTON(hEle)->bCheck;
}

//贴图
void WINAPI XBtn_SetImageLeave(HELE hEle, HIMAGE hImage)  //鼠标离开时图片
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(BUTTON(hEle)->hImage_leave, hImage);
}

void WINAPI XBtn_SetImageStay(HELE hEle, HIMAGE hImage) //鼠标停留时图片
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(BUTTON(hEle)->hImage_stay, hImage);
}

void WINAPI XBtn_SetImageDown(HELE hEle, HIMAGE hImage) //鼠标按下时图片
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(BUTTON(hEle)->hImage_down, hImage);
}

void WINAPI XBtn_SetImageCheck(HELE hEle, HIMAGE hImage) //选中时图片
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(BUTTON(hEle)->hImage_check, hImage);
}

void WINAPI XBtn_SetImageDisable(HELE hEle, HIMAGE hImage) //按钮禁用状态图片
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(BUTTON(hEle)->hImage_disable, hImage);
}

void WINAPI XBtn_SetTextAlign(HELE hEle, int flag) //设置文本对齐
{
	IsButtonDebug(hEle, __FUNCTION__);
	BUTTON(hEle)->textFlag = flag;
}

void WINAPI XBtn_SetIcon(HELE hEle, HIMAGE hImage) //设置图标
{
	IsButtonDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(BUTTON(hEle)->hImage_icon, hImage);
}

void WINAPI XBtn_SetIconAlign(HELE hEle, int align)
{
	IsButtonDebug(hEle, __FUNCTION__);
	BUTTON(hEle)->iconAlign = align;
}

void WINAPI XBtn_EnableCursorHand(HELE hEle, BOOL bEnable) //鼠标停留,光标变为手型
{
	IsButtonDebug(hEle, __FUNCTION__);
	BUTTON(hEle)->bCursorHand = bEnable;
}

void WINAPI XBtn_EnableAnimation(HELE hEle, BOOL bEnable, BOOL bLoopPlay)
{
	IsButtonDebug(hEle, __FUNCTION__);
	button_  *pButton = BUTTON(hEle);

	if (pButton->bAnimation == bEnable)
		return;

	pButton->bAnimation = bEnable;
	if (FALSE == bEnable)
	{
		Animation_Remove(pButton->pAnimation);
		return;
	}

	if (pButton->pAnimation)
	{
		pButton->pAnimation->bLoopPlay = bLoopPlay;
	}
	if (bLoopPlay)
	{
		Btn_StartAnimation(hEle);
	}
}

// TODO: 按钮动画
void WINAPI XBtn_AddAnimationFrame(HELE hEle, HIMAGE hImage, UINT uElapse)
{
	IsButtonDebug(hEle, __FUNCTION__);
	button_  *pButton = BUTTON(hEle);

	EnterCriticalSection(&g_CriticalSection_Animation_button);
	if (NULL == pButton->pAnimation)
	{
		pButton->pAnimation = (button_animation_group_*)malloc(sizeof(button_animation_group_));
		pButton->pAnimation->hEle = hEle;
		pButton->pAnimation->hArrayItem = XArray_Create();
		pButton->pAnimation->index = -1;
		pButton->pAnimation->countFrame = 0;
		pButton->pAnimation->timer = 0;
	}

	button_animation_item_ *pItem = (button_animation_item_*)malloc(sizeof(button_animation_item_));
	pItem->ms = uElapse;
	pItem->hImage = NULL;

	Image_AddImage(pItem->hImage, hImage);

	XArray_Add(pButton->pAnimation->hArrayItem, pItem);
	pButton->pAnimation->countFrame++;
	LeaveCriticalSection(&g_CriticalSection_Animation_button);
}

void WINAPI XBtn_SetOffset(HELE hEle, int x, int y) //设置内容坐标偏移量
{
	IsButtonDebug(hEle, __FUNCTION__);
	BUTTON(hEle)->offset.x = x;
	BUTTON(hEle)->offset.y = y;
}

BOOL CALLBACK Btn_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	button_ *pButton = BUTTON(hEle);
	if (pButton->bAnimation) //绘制动画
	{
		int index = pButton->pAnimation->index;
		if (-1 == index)
			index = 0;
		else if (index >= pButton->pAnimation->countFrame)
			index = pButton->pAnimation->countFrame - 1;

		XTRACE("绘制动画 %d \n", index);
		button_animation_item_ *pItem = (button_animation_item_*)XArray_GetAt(pButton->pAnimation->hArrayItem, index);

		if (pItem->hImage)
			XDraw_HImageSuper_(hDraw, pItem->hImage, &rect);
	}
	else
	{
		if (FALSE == ((ele_*)hEle)->bEnable) //禁用
		{
			Btn_DrawDisable(hEle, hDraw, rect);
		}
		else if (pButton->bCheck && pButton->hImage_check) //选中 有图片
		{
			Btn_DrawCheck(hEle, hDraw, rect);
		}
		else if (STATE_LEAVE == pButton->state)
		{
			Btn_DrawLeave(hEle, hDraw, rect);
		}
		else if (STATE_STAY == pButton->state)
		{
			Btn_DrawStay(hEle, hDraw, rect);
		}
		else if (STATE_DOWN == pButton->state || pButton->bCheck)
		{
			Btn_DrawDown(hEle, hDraw, rect);
		}
	}

	Btn_DrawIconAndText(hEle, hDraw, rect);

	if (((ele_*)hEle)->bDrawFocus &&  hEle == XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //绘制焦点
	{
		RECT rcFocus = { 2,2,rect.right - 2,rect.bottom - 2 };
		XDraw_FocusRect_(hDraw, &rcFocus);
	}

	return TRUE;
}

void Btn_DrawDisable(HELE hEle, HDRAW hDraw, RECT &rect)
{
	if (BUTTON(hEle)->hImage_disable)
	{
		XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_disable, &rect);
	}
	else
	{
		Btn_DrawDisable2(hEle, hDraw, rect);
	}
}

void Btn_DrawDisable2(HELE hEle, HDRAW hDraw, RECT &rect)
{
	//设置绘制区域
	HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 3, 3);
	XDraw_SelectClipRgn_(hDraw, hRgn);

	//渐变填充
	XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);

	//绘制内边线
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
	HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom, 3, 3);

	XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

	//绘制外边线
	hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
	XDraw_SelectClipRgn_(hDraw, NULL);

	if (BUTTON(hEle)->bCheck)
	{
		RECT rcCheck = { rect.left + 2,rect.top + 2,rect.right - 2,rect.bottom - 2 };
		HBRUSH hBrush = CreateSolidBrush(RGB(249, 141, 235));
		XDraw_FrameRect_(hDraw, &rcCheck, hBrush);
		DeleteObject(hBrush);
	}
}

void Btn_DrawCheck(HELE hEle, HDRAW hDraw, RECT &rect)
{
	button_ *pObj = BUTTON(hEle);

	XDraw_HImageSuper_(hDraw, pObj->hImage_check, &rect);
}

void Btn_DrawLeave(HELE hEle, HDRAW hDraw, RECT &rect)
{
	if (BUTTON(hEle)->hImage_leave)
	{
		XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_leave, &rect);
	}
	else
	{
		Btn_DrawLeave2(hEle, hDraw, rect);
	}
}

void Btn_DrawLeave2(HELE hEle, HDRAW hDraw, RECT &rect)
{
	//设置绘制区域
	HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 3, 3);

	HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom, 3, 3);
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
	HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));

	XDraw_SelectClipRgn_(hDraw, hRgn);

	//渐变填充
	XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);

	//绘制内边线
	XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

	//绘制外边线
	XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);

	XDraw_SelectClipRgn_(hDraw, NULL);


	if (BUTTON(hEle)->bCheck)
	{
		RECT rcCheck = { rect.left + 2,rect.top + 2,rect.right - 2,rect.bottom - 2 };
		HBRUSH hBrush = CreateSolidBrush(RGB(249, 141, 235));
		XDraw_FrameRect_(hDraw, &rcCheck, hBrush);
		DeleteObject(hBrush);
	}
}

void Btn_DrawStay(HELE hEle, HDRAW hDraw, RECT &rect)
{
	if (BUTTON(hEle)->hImage_stay)
	{
		XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_stay, &rect);
	}
	else
	{
		Btn_DrawStay2(hEle, hDraw, rect);
	}
}

void Btn_DrawStay2(HELE hEle, HDRAW hDraw, RECT &rect)
{
	HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 3, 3);
	HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom, 3, 3);
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(252, 194, 71));

	XDraw_SelectClipRgn_(hDraw, hRgn);

	XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(210, 210, 210), &rect, GRADIENT_FILL_RECT_V);

	XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
	XDraw_FrameRgn_(hDraw, hRgn2, hBrush2, 1, 1);

	XDraw_SelectClipRgn_(hDraw, NULL);


	if (BUTTON(hEle)->bCheck)
	{
		RECT rcCheck = { rect.left + 2,rect.top + 2,rect.right - 2,rect.bottom - 2 };
		HBRUSH hBrush = CreateSolidBrush(RGB(249, 141, 235));
		XDraw_FrameRect_(hDraw, &rcCheck, hBrush);
		DeleteObject(hBrush);
	}
}

void Btn_DrawDown(HELE hEle, HDRAW hDraw, RECT &rect)
{
	if (BUTTON(hEle)->hImage_down)
	{
		XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_down, &rect);
	}
	else
	{
		Btn_DrawDown2(hEle, hDraw, rect);
	}
}

void Btn_DrawDown2(HELE hEle, HDRAW hDraw, RECT &rect)
{
	HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 3, 3);
	XDraw_SelectClipRgn_(hDraw, hRgn);
	XDraw_GradientFill2_(hDraw, RGB(210, 210, 210), RGB(255, 255, 255), &rect, GRADIENT_FILL_RECT_V);

	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(240, 240, 240));
	HRGN hRgn2 = XDraw_CreateRoundRectRgn_(hDraw, 1, 1, rect.right, rect.bottom + 1, 3, 3);
	XDraw_FrameRgn_(hDraw, hRgn2, hBrush, 1, 1);

	HBRUSH hBrush2 = XDraw_CreateSolidBrush_(hDraw, RGB(128, 128, 128));
	XDraw_FrameRgn_(hDraw, hRgn, hBrush2, 1, 1);
	XDraw_SelectClipRgn_(hDraw, NULL);


	if (BUTTON(hEle)->bCheck)
	{
		RECT rcCheck = { rect.left + 2,rect.top + 2,rect.right - 2,rect.bottom - 2 };
		HBRUSH hBrush = CreateSolidBrush(RGB(249, 141, 235));
		XDraw_FrameRect_(hDraw, &rcCheck, hBrush);
		DeleteObject(hBrush);
	}
}


// center h
// center v
// center h | center v
// center h | top
// center h | bottom
// center v | left
// center v | right
// left
// top
// right
// bottom
/*
void Btn_DrawIconAndText(HELE hEle,HDRAW hDraw,RECT &rect) //绘制图标和文本
{
	button_ *pObj=BUTTON(hEle);
	wchar_t *pText=XBtn_GetText(hEle);
	int textFlag=pObj->textFlag;
	RECT rcText=rect;

	//绘制图标
	if(pObj->hImage_icon)
	{
		int width=XImage_GetWidth(pObj->hImage_icon);
		int height=XImage_GetHeight(pObj->hImage_icon);
		int iconX=0;
		int iconY=0;
		if(pText)
		{
			//获取文本大小
			RECT rcArea=rect;
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcArea,DT_CALCRECT);

			switch(pObj->iconAlign)
			{
			case XC_ICON_ALIGN_LEFT:
				{
					int half=(rect.right-(rcArea.right+width))/2;
					iconX=half-1;
					iconY=(rect.bottom-height)/2;
					rcText.left=width+half+1;
				}break;
			case XC_ICON_ALIGN_TOP:
				{
					int half=(rect.bottom-(rcArea.bottom+height))/2;
					iconX=(rect.right-width)/2;
					iconY=half-1;
					rcText.top=height+half+1;
				}break;
			case XC_ICON_ALIGN_RIGHT:
				{
					int half=(rect.right-(rcArea.right+width))/2;
					iconX=rect.right-width-half+1;
					iconY=(rect.bottom-height)/2;
					rcText.right=rect.right-width-half-1;
				}break;
			case XC_ICON_ALIGN_BOTTOM:
				{
					int half=(rect.bottom-(rcArea.bottom+height))/2;
					iconX=(rect.right-width)/2;
					iconY=rect.bottom-height-half+1;
					rcText.bottom=rect.bottom-height-half-1;
				}break;
			}
		}else
		{
			iconX=(rect.right-width)/2;
			iconY=(rect.bottom-height)/2;
		}

		if(STATE_DOWN==BUTTON(hEle)->state)
			XDraw_HImageStretch_(hDraw,pObj->hImage_icon,iconX+1,iconY+1,width,height);
		else
			XDraw_HImageStretch_(hDraw,pObj->hImage_icon,iconX,iconY,width,height);
	}

	//绘制文本
	if(pText)
	{
		if(FALSE==((ele_*)hEle)->bEnable) //禁用
		{
			COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,pObj->textFlag);
			XDraw_SetTextColor_(hDraw,color);
		}else
		{
			//防止文本绘制到边界
			if(rcText.left<3) rcText.left+=3;
			if(rcText.top<3) rcText.top+=3;
			if(rcText.right>(rect.right-3)) rcText.right-=3;
			if(rcText.bottom>(rect.bottom-3)) rcText.bottom-=3;

			if(STATE_DOWN==BUTTON(hEle)->state)
			{
				rcText.left++;
				rcText.top++;
				rcText.right++;
				rcText.bottom++;
			}
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,textFlag);

			//XTRACEW(L"绘制 %s \n",pText);
		}
	}
}*/

void Btn_DrawIconAndText(HELE hEle, HDRAW hDraw, RECT &rect) //绘制图标和文本
{
	button_ *pButton = BUTTON(hEle);
	wchar_t *pText = XBtn_GetText(hEle);
	int textFlag = pButton->textFlag;
	RECT rcText = rect;

	//绘制图标
	if (pButton->hImage_icon)
	{
		int width = XImage_GetWidth(pButton->hImage_icon);
		int height = XImage_GetHeight(pButton->hImage_icon);
		int iconX = 0;
		int iconY = 0;
		if (pText)
		{
			//获取文本大小
			RECT rcArea = rect;
			XDraw_DrawText_(hDraw, pText, XStr_GetLength(pButton->hString), &rcArea, DT_CALCRECT);

			switch (pButton->iconAlign)
			{
			case XC_ICON_ALIGN_LEFT:
			{
				int half = (rect.right - (rcArea.right + width)) / 2;
				iconX = half - 1;
				iconY = (rect.bottom - height) / 2;
				rcText.left = width + half + 1;
			}break;
			case XC_ICON_ALIGN_TOP:
			{
				int half = (rect.bottom - (rcArea.bottom + height)) / 2;
				iconX = (rect.right - width) / 2;
				iconY = half - 1;
				rcText.top = height + half + 1;
			}break;
			case XC_ICON_ALIGN_RIGHT:
			{
				int half = (rect.right - (rcArea.right + width)) / 2;
				iconX = rect.right - width - half + 1;
				iconY = (rect.bottom - height) / 2;
				rcText.right = rect.right - width - half - 1;
			}break;
			case XC_ICON_ALIGN_BOTTOM:
			{
				int half = (rect.bottom - (rcArea.bottom + height)) / 2;
				iconX = (rect.right - width) / 2;
				iconY = rect.bottom - height - half + 1;
				rcText.bottom = rect.bottom - height - half - 1;
			}break;
			}
		}
		else
		{
			iconX = (rect.right - width) / 2;
			iconY = (rect.bottom - height) / 2;
		}

		if (STATE_DOWN == BUTTON(hEle)->state)
			XDraw_HImageStretch_(hDraw, pButton->hImage_icon, iconX + 1 + pButton->offset.x, iconY + 1 + pButton->offset.y, width, height);
		else
			XDraw_HImageStretch_(hDraw, pButton->hImage_icon, iconX + pButton->offset.x, iconY + pButton->offset.y, width, height);
	}

	//绘制文本
	if (pText)
	{
		//	if(FALSE==((ele_*)hEle)->bEnable) //禁用
		//	{
		//		COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		//		XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,pObj->textFlag);
		//		XDraw_SetTextColor_(hDraw,color);
		//	}else
		//	{
				//防止文本绘制到边界
		if (rcText.left < 3) rcText.left += 3;
		if (rcText.top < 3) rcText.top += 3;
		if (rcText.right > (rect.right - 3)) rcText.right -= 3;
		if (rcText.bottom > (rect.bottom - 3)) rcText.bottom -= 3;

		if (STATE_DOWN == BUTTON(hEle)->state)
		{
			rcText.left++;
			rcText.top++;
			rcText.right++;
			rcText.bottom++;
		}

		rcText.left += pButton->offset.x;
		rcText.right += pButton->offset.x;
		rcText.top += pButton->offset.y;
		rcText.bottom += pButton->offset.y;
		XDraw_DrawText_(hDraw, pText, XStr_GetLength(pButton->hString), &rcText, textFlag);

		//XTRACEW(L"绘制 %s \n",pText);
//	}
	}
}

void Btn_StartAnimation(HELE hEle, BOOL bClockwise)  //开始动画
{
	button_ *pButton = BUTTON(hEle);

	if (NULL == pButton->pAnimation)
		return;
	Animation_Add(pButton->pAnimation, bClockwise);
}

BOOL CALLBACK Btn_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	if (((ele_*)hEle)->bEnable)
	{
		if (BUTTON(hEle)->bCursorHand)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		if (FALSE == XEle_IsHitChildEle(hEle, pPt))
		{
			BUTTON(hEle)->state = STATE_DOWN;
			BUTTON(hEle)->bDown = TRUE;
			XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	if (((ele_*)hEle)->bEnable)
	{
		if (BUTTON(hEle)->bCursorHand)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		if (BUTTON(hEle)->bDown)
		{
			BUTTON(hEle)->state = STATE_STAY;
			XEle_RedrawEle(hEle);

			BUTTON(hEle)->bDown = FALSE;
			Ele_SendEvent(hEle, XE_BNCLICK, 0, 0);
		}
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnEventKeyDown(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam)
{
	if (hEle == hEventEle)
	{
		if (VK_RETURN == wParam)
		{
			Ele_SendEvent(hEle, XE_BNCLICK, 0, 0);
		}
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	if (BUTTON(hEle)->bCursorHand)
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnEventMouseStay(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (((ele_*)hEle)->bEnable)
		{
			BUTTON(hEle)->state = STATE_STAY;

			//XTRACE("停留 \n");
//TODO:开始动画
			if (((button_*)hEle)->bAnimation)
			{
				if (FALSE == BUTTON(hEle)->pAnimation->bLoopPlay)
				{
					//XTRACE("开始 顺时针动画 --------\n");
					Btn_StartAnimation(hEle);
				}
			}
			else
				XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnEventMouseLeave(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		if (((ele_*)hEle)->bEnable)
		{
			BUTTON(hEle)->state = STATE_LEAVE;
			if (BUTTON(hEle)->bDown)
				BUTTON(hEle)->bDown = FALSE;

			//XTRACE("离开 \n");

	//TODO:开始动画,逆时针
			if (((button_*)hEle)->bAnimation)
			{
				if (FALSE == BUTTON(hEle)->pAnimation->bLoopPlay)
				{
					//XTRACE("开始 逆时针动画 --------\n");
					Btn_StartAnimation(hEle, FALSE);
				}
			}
			else
				XEle_RedrawEle(hEle);
		}
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnEventSetFocus(HELE hEle, HELE hEventEle) //获得焦点
{
	if (hEle == hEventEle)
	{
		if (((ele_*)hEle)->bDrawFocus)
			XEle_RedrawEle(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Btn_OnEventKillFocus(HELE hEle, HELE hEventEle) //失去焦点
{
	if (hEle == hEventEle)
	{
		if (((ele_*)hEle)->bEnable)
		{
			if (STATE_STAY == BUTTON(hEle)->state)
			{
				BUTTON(hEle)->state = STATE_LEAVE;
			}
		}
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}