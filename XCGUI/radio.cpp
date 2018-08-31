/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup radio 单选按钮(Radio)
/// @ingroup groupElements
/// @{

/// @brief 创建单选按钮元素.
/// @param x  元素x坐标.
/// @param y  元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param pTitle  内容.
/// @param hParent  父为窗口句柄或元素句柄.
/// @return 单选按钮句柄.
HELE WINAPI XRadio_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent)
{
	radio_ *pRadio = (radio_*)malloc(sizeof(radio_));
	memset(pRadio, 0, sizeof(radio_));

	Radio_Init((HELE)pRadio, x, y, cx, cy, XC_RADIO, pTitle, hParent);

	return (HELE)pRadio;
}

void Radio_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent) //初始化注册
{
	Btn_Init(hEle, x, y, cx, cy, eleType, pTitle, hParent);
	AddTypeDebug(hEle, XC_RADIO);

	((button_*)hEle)->textFlag = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;

	XEle_RegisterMessage(hEle, XM_PAINT, Radio_OnDraw);
	XEle_RegisterEvent(hEle, XE_BNCLICK, Radio_OnEventBtnClick);
	XEle_RegisterEvent(hEle, XE_DESTROY, Radio_OnDestroy);
}

//贴图:

/// @brief 设置单选按钮元素,鼠标离开和未选择状态时贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageLeave_UnCheck(HELE hEle, HIMAGE hImage)  //鼠标离开时图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	XBtn_SetImageLeave(hEle, hImage);
}

/// @brief 设置单选按钮元素,鼠标停留和未选择状态时贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageStay_UnCheck(HELE hEle, HIMAGE hImage)   //鼠标停留时图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	XBtn_SetImageStay(hEle, hImage);
}
/// @brief  设置单选按钮元素,鼠标按下和未选择状态时贴图. 
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageDown_UnCheck(HELE hEle, HIMAGE hImage)   //鼠标按下时图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	XBtn_SetImageDown(hEle, hImage);
}
/// @brief 设置单选按钮元素禁用和未选择状态时贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageDisable_UnCheck(HELE hEle, HIMAGE hImage) //按钮禁用状态图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	XBtn_SetImageDisable(hEle, hImage);
}
/// @brief 设置单选按钮元素,鼠标离开和选择状态时贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageLeave_Check(HELE hEle, HIMAGE hImage)  //鼠标离开时图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_leave_check, hImage);
}
/// @brief 设置单选按钮元素,鼠标停留和选择状态时贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageStay_Check(HELE hEle, HIMAGE hImage)   //鼠标停留时图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_stay_check, hImage);
}
/// @brief 设置单选按钮元素,鼠标按下和选择状态时贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageDown_Check(HELE hEle, HIMAGE hImage)   //鼠标按下时图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_down_check, hImage);
}
/// @brief 设置单选按钮元素禁用和选择状态时的贴图.
/// @param hEle    元素句柄.
/// @param hImage  图片句柄.
void WINAPI XRadio_SetImageDisable_Check(HELE hEle, HIMAGE hImage) //按钮禁用状态图片
{
	IsRadioDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_disable_check, hImage);
}

/// @brief 设置组ID.
/// @param hEle 元素句柄.
/// @param groupID  组ID
void WINAPI XRadio_SetGroupID(HELE hEle, int groupID)  //设置组ID
{
	IsRadioDebug(hEle, __FUNCTION__);
	RADIO(hEle)->groupID = groupID;
}

/// @brief 获取组ID.
/// @param hEle 元素句柄.
/// @return  返回组ID
int  WINAPI XRadio_GetGroupID(HELE hEle)  //获取组ID
{
	IsRadioDebug(hEle, __FUNCTION__);
	return RADIO(hEle)->groupID;
}

/// @brief 启用按钮样式.
/// @param  hEle 元素句柄.
/// @param  bStyle  启用:TRUE,关闭:FALSE;
void  WINAPI XRadio_EnableButtonStyle(HELE hEle, BOOL bStyle) //启用按钮样式
{
	IsRadioDebug(hEle, __FUNCTION__);
	RADIO(hEle)->bButtonStyle = bStyle;
	if (bStyle)
		BUTTON(hEle)->textFlag = DT_VCENTER | DT_SINGLELINE | DT_CENTER | DT_END_ELLIPSIS;
	else
		BUTTON(hEle)->textFlag = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
}

/// @brief 绑定元素,当按钮被选中或取消选中,会调用XEle_ShowEle()函数,显示或隐藏绑定的元素.
/// @param  hEle 元素句柄.
/// @param  bindEle  绑定元素句柄;
void WINAPI XRadio_SetBindEle(HELE hEle, HELE bindEle)
{
	IsRadioDebug(hEle, __FUNCTION__);
	RADIO(hEle)->hBindEle = bindEle;
}

BOOL CALLBACK Radio_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (XBtn_IsCheck(hEle)) //勾选
	{
		Radio_DrawCheck(hEle, hDraw, rect);
	}
	else
	{
		Radio_DrawUnCheck(hEle, hDraw, rect);
	}

	if (((ele_*)hEle)->bDrawFocus && hEle == XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //绘制焦点
	{
		if (RADIO(hEle)->bButtonStyle)
		{
			RECT rcFocus = { 2,2,rect.right - 2,rect.bottom - 2 };
			XDraw_FocusRect_(hDraw, &rcFocus);
		}
		else
		{
			RECT rcFocus = { 0,0,rect.right,rect.bottom };
			XDraw_FocusRect_(hDraw, &rcFocus);
		}
	}
	return TRUE;
}

void Radio_DrawCheck(HELE hEle, HDRAW hDraw, RECT &rect) //绘制勾选状态
{
	int top = rect.bottom / 2 - 6;  //绘制圆顶点
	if (FALSE == ((ele_*)hEle)->bEnable)  //禁用)
	{
		if (RADIO(hEle)->hImage_disable_check)
		{
			XDraw_HImageSuper_(hDraw, RADIO(hEle)->hImage_disable_check, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDisable2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_Check2(hDraw, 2, top, RGB(100, 100, 100), RGB(80, 80, 80));
		}
		//绘制文本
	/*	COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		wchar_t *pText=XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,DT_VCENTER| DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw,color);
		return ;*/
	}
	else if (STATE_LEAVE == ((button_*)hEle)->state)	//离开
	{
		if (RADIO(hEle)->hImage_leave_check)
		{
			XDraw_HImageSuper_(hDraw, RADIO(hEle)->hImage_leave_check, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawLeave2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_Check2(hDraw, 2, top, RGB(100, 100, 100), RGB(80, 80, 80));
		}
	}
	else if (STATE_STAY == ((button_*)hEle)->state)//停留
	{
		if (RADIO(hEle)->hImage_stay_check)
		{
			XDraw_HImageSuper_(hDraw, RADIO(hEle)->hImage_stay_check, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawStay2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_Check2(hDraw, 2, top, RGB(100, 100, 100), RGB(39, 135, 194));
		}
	}
	else if (STATE_DOWN == ((button_*)hEle)->state) //按下
	{
		if (RADIO(hEle)->hImage_down_check)
		{
			XDraw_HImageSuper_(hDraw, RADIO(hEle)->hImage_down_check, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDown2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_Check2(hDraw, 2, top, RGB(100, 100, 100), RGB(39, 135, 194));
		}
	}

	if (RADIO(hEle)->bButtonStyle)
	{
		Btn_DrawIconAndText(hEle, hDraw, rect);
	}
	else
	{
		wchar_t *pText = XBtn_GetText(hEle);
		if (pText)
		{
			RECT rcText = rect;
			rcText.left += 17;
			XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, ((button_*)hEle)->textFlag);
		}
	}
}

void Radio_Draw_Check2(HDRAW hDraw, int x, int y, COLORREF color_dot, COLORREF color_border)
{
	IsDrawDebug(hDraw, __FUNCTION__);

	HDC hdc = XDraw_GetHDC_(hDraw);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	int left = x + pDraw->x;
	int top = y + pDraw->y;

	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	SolidBrush  solidbrush(Color(GetRValue(color_dot), GetGValue(color_dot), GetBValue(color_dot)));
	graphics.FillEllipse(&solidbrush, Rect(left + 3, top + 3, 6, 6));

	//边框
	Pen bluePen(Color(GetRValue(color_border), GetGValue(color_border), GetBValue(color_border)));
	Rect ellipseRect(left, top, 12, 12);
	graphics.DrawEllipse(&bluePen, ellipseRect);
}

void Radio_DrawUnCheck(HELE hEle, HDRAW hDraw, RECT &rect) //绘制未勾选状态
{
	int top = rect.bottom / 2 - 6;  //绘制圆顶点
	if (FALSE == ((ele_*)hEle)->bEnable)  //禁用)
	{
		if (BUTTON(hEle)->hImage_disable)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_disable, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDisable2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_UnCheck2(hDraw, 2, top, RGB(180, 180, 180), RGB(255, 255, 255), RGB(80, 80, 80));
		}
		/*		//绘制文本
				COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
				wchar_t *pText=XBtn_GetText(hEle);
				XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,DT_VCENTER| DT_SINGLELINE);
				XDraw_SetTextColor_(hDraw,color);
				return ;*/
	}
	else if (STATE_LEAVE == ((button_*)hEle)->state)	//离开
	{
		if (BUTTON(hEle)->hImage_leave)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_leave, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawLeave2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_UnCheck2(hDraw, 2, top, RGB(180, 180, 180), RGB(255, 255, 255), RGB(80, 80, 80));
		}
	}
	else if (STATE_STAY == ((button_*)hEle)->state)//停留
	{
		if (BUTTON(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_stay, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawStay2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_UnCheck2(hDraw, 2, top, RGB(180, 180, 180), RGB(255, 255, 255), RGB(39, 135, 194));
		}
	}
	else if (STATE_DOWN == ((button_*)hEle)->state) //按下
	{
		if (BUTTON(hEle)->hImage_down)
		{
			XDraw_HImageSuper_(hDraw, BUTTON(hEle)->hImage_down, &rect);
		}
		else
		{
			if (RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDown2(hEle, hDraw, rect);
			}
			else
				Radio_Draw_UnCheck2(hDraw, 2, top, RGB(180, 180, 180), RGB(255, 255, 255), RGB(39, 135, 194));
		}
	}

	if (RADIO(hEle)->bButtonStyle)
	{
		Btn_DrawIconAndText(hEle, hDraw, rect);
	}
	else
	{
		wchar_t *pText = XBtn_GetText(hEle);
		if (pText)
		{
			RECT rcText = rect;
			rcText.left += 17;
			XDraw_DrawText_(hDraw, pText, wcslen(pText), &rcText, ((button_*)hEle)->textFlag);
		}
	}
}

void Radio_Draw_UnCheck2(HDRAW hDraw, int x, int y, COLORREF color_dot1, COLORREF color_dot2, COLORREF color_border)
{
	IsDrawDebug(hDraw, __FUNCTION__);

	HDC hdc = XDraw_GetHDC_(hDraw);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	int left = x + pDraw->x;
	int top = y + pDraw->y;

	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	LinearGradientBrush  brush(Rect(left + 2, top, 8, 8),
		Color(GetRValue(color_dot1), GetGValue(color_dot1), GetBValue(color_dot1)),
		Color(GetRValue(color_dot2), GetGValue(color_dot2), GetBValue(color_dot2))
		, LinearGradientModeForwardDiagonal);
	graphics.FillEllipse(&brush, Rect(left + 2, top + 2, 8, 8));

	//边框
	Pen bluePen(Color(GetRValue(color_border), GetGValue(color_border), GetBValue(color_border)));
	Rect ellipseRect(left, top, 12, 12);
	graphics.DrawEllipse(&bluePen, ellipseRect);

}

BOOL CALLBACK Radio_OnEventBtnClick(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	if (XBtn_IsCheck(hEle))
		return FALSE;

	ele_ *pEle = (ele_*)hEle;

	XBtn_SetCheck(hEle, TRUE);
	XEle_RedrawEle(hEle);

	HARRAY hArrayEle = NULL;
	if (pEle->pParentEle)
	{
		hArrayEle = pEle->pParentEle->hArrayEle;
	}
	else
	{
		window_ *pWindow = (window_*)XEle_GetHWindow(hEle);
		hArrayEle = pWindow->hArrayEle;
	}

	int count = Array_GetCount(hArrayEle);
	int index = pEle->id;

	radio_  *pRadioT = NULL;
	for (int i = 0; i < count; i++)
	{
		pRadioT = (radio_*)XArray_GetAt(hArrayEle, i);
		if (XC_RADIO == ((ele_*)pRadioT)->eleType)
		{
			if (RADIO(hEle)->groupID == pRadioT->groupID && RADIO(hEle) != pRadioT)
			{
				if (BUTTON(pRadioT)->bCheck)
				{
					XBtn_SetCheck((HELE)pRadioT, FALSE);
					XEle_RedrawEle((HELE)pRadioT);
					break;
				}
			}
		}
	}

	return FALSE;
}

void CALLBACK Radio_OnDestroy(HELE hEle)  //销毁
{
	if (RADIO(hEle)->hImage_leave_check) XImage_Destroy(RADIO(hEle)->hImage_leave_check);
	if (RADIO(hEle)->hImage_stay_check) XImage_Destroy(RADIO(hEle)->hImage_stay_check);
	if (RADIO(hEle)->hImage_down_check) XImage_Destroy(RADIO(hEle)->hImage_down_check);
	if (RADIO(hEle)->hImage_disable_check) XImage_Destroy(RADIO(hEle)->hImage_disable_check);
}

///@}
