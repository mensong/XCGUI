/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup scrollView 滚动视图(ScrollView)
/// @ingroup groupElements
/// @{

/// @brief 创建滚动视图元素.
/// @param x   元素x坐标.
/// @param y   元素y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @param hParent 父是窗口资源句柄或UI元素资源句柄.如果是窗口资源句柄将被添加到窗口,
///                如果是元素资源句柄将被添加到元素.
/// @return 元素句柄.
HELE WINAPI XSView_Create(int x, int y, int cx, int cy, HXCGUI hParent)
{
	scrollView_ *pScrollView = (scrollView_*)malloc(sizeof(scrollView_));
	if (pScrollView)
	{
		memset(pScrollView, 0, sizeof(scrollView_));
		SView_Init((HELE)pScrollView, x, y, cx, cy, XC_SCROLLVIEW, hParent);
	}
	return (HELE)pScrollView;
}

void SView_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent)
{
	Ele_Init(hEle, x, y, cx, cy, eleType, hParent);
	AddTypeDebug(hEle, XC_SCROLLVIEW);
	/////////////////////////////////////////////////////////////
	scrollView_ *pScrollView = SCROLLVIEW(hEle);
	pScrollView->bHScroll = TRUE;
	pScrollView->bVScroll = TRUE;
	pScrollView->left = 2;
	pScrollView->top = 2;
	pScrollView->right = 2;
	pScrollView->bottom = 2;

	pScrollView->barWidth = 16;
	pScrollView->sizeLine.cx = 20;
	pScrollView->sizeLine.cy = 20;

	pScrollView->sizeTotal.cx = 0;
	pScrollView->sizeTotal.cy = 0;

	int width = cx - pScrollView->left - pScrollView->right;//-pScrollView->barWidth;
	int height = cy - pScrollView->top - pScrollView->bottom;//-pScrollView->barWidth;

	//视图
	ele_  *pEleView = (ele_*)malloc(sizeof(ele_));
	if (NULL == pEleView) return;
	memset(pEleView, 0, sizeof(ele_));
	Ele_Init((HELE)pEleView, pScrollView->left, pScrollView->top, width, height, XC_SCROLLVIEW_VIEW, hEle);
	pScrollView->hView = (HELE)pEleView;

	XEle_EnableFocus(pScrollView->hView, FALSE);
	XEle_EnableBorder(pScrollView->hView, FALSE);

	//创建水平滚动条
	pScrollView->pScrollBarH = (ele_*)XSBar_Create(pScrollView->left, cy - pScrollView->bottom - pScrollView->barWidth, pScrollView->sizeView.cx, pScrollView->barWidth, SY_HSCROLL);
	XEle_AddEle(hEle, (HELE)pScrollView->pScrollBarH);

	//创建垂直滚动条
	pScrollView->pScrollBarV = (ele_*)XSBar_Create(cx - pScrollView->right - pScrollView->barWidth, pScrollView->top, pScrollView->barWidth, pScrollView->sizeView.cy, SY_VSCROLL);
	XEle_AddEle(hEle, (HELE)pScrollView->pScrollBarV);

	XEle_EnableFocus(hEle, TRUE);

	XEle_RegisterMessage(hEle, XM_PAINT, SView_OnDraw);
	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, SView_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_RBUTTONDOWN, SView_OnRButtonDown);

	XEle_RegisterEvent(hEle, XE_HSCROLL, SView_OnEventHScroll);
	XEle_RegisterEvent(hEle, XE_VSCROLL, SView_OnEventVScroll);
	XEle_RegisterEvent(hEle, XE_MOUSEWHEEL, SView_OnEventMouseWheel);

	XEle_RegisterEvent(hEle, XE_DESTROY, SView_OnDestroy);
	XEle_RegisterEvent(hEle, XE_SIZE, SView_OnEventSize);

	XEle_RegisterMessage(pScrollView->hView, XM_LBUTTONDOWN, SView_OnLButtonDown_View);

	XSView_Adjust(hEle);
}

void CALLBACK SView_OnDestroy(HELE hEle) //销毁
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	drawScrollView_ *pObj = SCROLLVIEW(hEle)->pDrawScrollViewList;
	drawScrollView_ *pDel = NULL;
	while (pObj)
	{
		pDel = pObj;
		pObj = pObj->pNext;
#ifdef	XCGUI_PLUS          //C++类支持,对类成员函数注册的支持
		if (pDel->pClass_Fun_Info)
			free(pDel->pClass_Fun_Info);
#endif
		free(pDel);
	}

	if (SCROLLVIEW(hEle)->hImage_bk) XImage_Destroy(SCROLLVIEW(hEle)->hImage_bk);
}

/// @brief 注册滚动视图绘制函数,可以注册多个函数.
/// @param hEle 元素句柄.
/// @param pFun 滚动视图绘制函数名.函数类型如下:
/// @code  BOOL CALLBACK DrawScrollView(HELE hEle,HDRAW hDraw);  @endcode
void WINAPI XSView_SetDrawScrollView(HELE hEle, pFunDrawScrollView pFun)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	drawScrollView_ *pNew = (drawScrollView_*)malloc(sizeof(drawScrollView_));//new drawScrollView_;
	pNew->pFun = pFun;
	pNew->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
	pNew->pClass_Fun_Info = NULL;
#endif

	if (NULL == SCROLLVIEW(hEle)->pDrawScrollViewList)
	{
		SCROLLVIEW(hEle)->pDrawScrollViewList = pNew;
	}
	else
	{
		pNew->pNext = SCROLLVIEW(hEle)->pDrawScrollViewList;
		SCROLLVIEW(hEle)->pDrawScrollViewList = pNew;
	}

}
/// @brief 获取滚动视图视元素.
/// @param hEle 元素句柄.
/// @return 返回视元素.
HELE WINAPI XSView_GetView(HELE hEle) //获取视元素
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return ((scrollView_*)hEle)->hView;
}

/// @brief 添加元素到滚动视图,
/// @param hEle 元素句柄.
/// @param hNewEle  要添加的子元素资源句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_AddEle(HELE hEle, HELE hNewEle) //添加元素到滚动视图
{
	return XEle_AddEle(((scrollView_*)hEle)->hView, hNewEle);
}

#ifdef	XCGUI_PLUS          //C++类支持,对类成员函数注册的支持
void WINAPI XSView_SetDrawScrollViewEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	drawScrollView_ *pNew = (drawScrollView_*)malloc(sizeof(drawScrollView_));
	pNew->pFun = (pFunDrawScrollView)pCallBackFun;
	pNew->pNext = NULL;
	pNew->pClass_Fun_Info = pClass_Fun_Info;

	if (NULL == SCROLLVIEW(hEle)->pDrawScrollViewList)
	{
		SCROLLVIEW(hEle)->pDrawScrollViewList = pNew;
	}
	else
	{
		pNew->pNext = SCROLLVIEW(hEle)->pDrawScrollViewList;
		SCROLLVIEW(hEle)->pDrawScrollViewList = pNew;
	}
}
#endif

/// @brief 设置视图内容总大小(不包含边框间隔).
/// @param hEle 元素句柄.
/// @param cx  视图内容宽度.
/// @param cy  视图内容高度.
void WINAPI XSView_SetSize(HELE hEle, int cx, int cy)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	SCROLLVIEW(hEle)->sizeTotal.cx = cx;
	SCROLLVIEW(hEle)->sizeTotal.cy = cy;
	XSView_Adjust(hEle);
}

/// @brief 获取视口原点X坐标.
/// @param hEle 元素句柄.
/// @return 视口原点X坐标,值为小于或等于0,负数值.
int WINAPI XSView_GetHViewPos(HELE hEle)   //获取视口原点X坐标
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return -(SCROLLVIEW(hEle)->hPos*SCROLLVIEW(hEle)->sizeLine.cx);
}

/// @brief 获取视口原点Y坐标.
/// @param hEle 元素句柄.
/// @return 视口原点Y坐标.
int WINAPI XSView_GetVViewPos(HELE hEle)   //获取视口原点Y坐标
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return -(SCROLLVIEW(hEle)->vPos*SCROLLVIEW(hEle)->sizeLine.cy);
}

/// @brief 获取视口坐标(不含边框间隔),left为视口左间隔大小,top为视口上间隔大小,非(0,0).
/// @param hEle 元素句柄.
/// @param pRect 接收视口坐标.
void WINAPI XSView_GetViewRect(HELE hEle, RECT *pRect) //获取视图坐标
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	pRect->left = SCROLLVIEW(hEle)->left;
	pRect->top = SCROLLVIEW(hEle)->top;
	pRect->right = pRect->left + SCROLLVIEW(hEle)->sizeView.cx;
	pRect->bottom = pRect->top + SCROLLVIEW(hEle)->sizeView.cy;
}

/// @brief 获取设置的内容大小,返回的是XSView_SetSize()设置的值.
/// @param hEle 元素句柄.
/// @param pSize 接收大小.
void WINAPI XSView_GetSize(HELE hEle, SIZE *pSize)  //获取设置的内容大小
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	*pSize = SCROLLVIEW(hEle)->sizeTotal;
}

/// @brief 获取滚动视图元素上的水平滚动条.返回类型为ScrollBar元素句柄.
/// @param hEle 元素句柄.
/// @return 滚动条元素句柄.
HELE WINAPI XSView_GetHScrollBar(HELE hEle) //获取水平滚动条
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return (HELE)SCROLLVIEW(hEle)->pScrollBarH;
}

/// @brief 获取滚动视图元素上的垂直滚动条.返回类型为ScrollBar元素句柄.
/// @param hEle 元素句柄.
/// @return 滚动条元素句柄.
HELE WINAPI XSView_GetVScrollBar(HELE hEle) //获取垂直滚动条
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return (HELE)SCROLLVIEW(hEle)->pScrollBarV;
}

/// @brief 水平滚动条,滚动到指定点.
/// @param hEle 元素句柄.
/// @param pos 滚动位置
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollHPos(HELE hEle, int pos) //滚动到指定点
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollPos((HELE)SCROLLVIEW(hEle)->pScrollBarH, pos);
}

/// @brief 垂直滚动条,滚动到指定位置.
/// @param hEle 元素句柄.
/// @param pos 滚动位置
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollVPos(HELE hEle, int pos) //滚动到指定点
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollPos((HELE)SCROLLVIEW(hEle)->pScrollBarV, pos);
}

BOOL WINAPI XSView_ScrollHPosX(HELE hEle, int posX) //滚动到指定坐标
{
	IsScrollViewDebug(hEle, __FUNCTION__);

	scrollView_ *pSView = (scrollView_*)hEle;

	int pos = posX / pSView->sizeLine.cx;
	return XSView_ScrollHPos(hEle, pos + 1);
}

BOOL WINAPI XSView_ScrollVPosY(HELE hEle, int posY) //滚动到指定坐标
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	scrollView_ *pSView = (scrollView_*)hEle;
	int pos = posY / pSView->sizeLine.cy;
	return XSView_ScrollVPos(hEle, pos + 1);

}
/// @brief 向左滚动.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollLeftLine(HELE hEle)    //向左滚动
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollUp((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief 向右滚动.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollRightLine(HELE hEle)   //向右滚动
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollDown((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief 向上滚动.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollTopLine(HELE hEle)      //向上滚动
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollUp((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief 向下滚动.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollDownLine(HELE hEle)    //向下滚动
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollDown((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief 水平滚动到左侧.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollLeft(HELE hEle)    //水平滚动到左侧
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollTop((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief 水平滚动到右侧.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollRight(HELE hEle)   //水平滚动到右侧
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollBottom((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief 垂直滚动到顶部.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollTop(HELE hEle)     //滚动到顶部
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollTop((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief 垂直滚动到底部.
/// @param hEle 元素句柄.
/// @return 如果成功返回TRUE,否则相反.
BOOL WINAPI XSView_ScrollBottom(HELE hEle)  //滚动到底部
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XSBar_ScrollBottom((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief 调整滚动视图布局.
/// @param hEle 元素句柄.
void WINAPI XSView_Adjust(HELE hEle)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);
	scrollView_ *pSView = SCROLLVIEW(hEle);

	int cx = rect.right - rect.left;
	int cy = rect.bottom - rect.top;
	BOOL bShowH = FALSE, bShowV = FALSE;
	pSView->sizeView.cx = cx - pSView->left - pSView->right;
	pSView->sizeView.cy = cy - pSView->top - pSView->bottom;

	if (pSView->sizeTotal.cx > (pSView->sizeView.cx) && pSView->bHScroll) //显示水平滚动条
	{
		bShowH = TRUE;
		pSView->sizeView.cy -= pSView->barWidth;
	}
	if (pSView->sizeTotal.cy > (pSView->sizeView.cy) && pSView->bVScroll)  //显示垂直滚动条
	{
		bShowV = TRUE;
		pSView->sizeView.cx -= pSView->barWidth;
	}
	if (bShowV && FALSE == bShowH)
	{
		if ((pSView->sizeTotal.cx > pSView->sizeView.cx) && pSView->bHScroll) //显示水平滚动条
		{
			bShowH = TRUE;
			pSView->sizeView.cy -= pSView->barWidth;
		}
	}
	if (bShowH && FALSE == bShowV)
	{
		if ((pSView->sizeTotal.cy > pSView->sizeView.cy) && pSView->bVScroll)  //显示垂直滚动条
		{
			bShowV = TRUE;
			pSView->sizeView.cx -= pSView->barWidth;
		}
	}

	//水平滚动条-------------------
	//修改滚动点数

	double posd = 0;
	int size = pSView->sizeTotal.cx - pSView->sizeView.cx;
	int pos = 0;

	if (0 != size && 0 != pSView->sizeLine.cx)
	{
		posd = ((double)(size)) / pSView->sizeLine.cx;
		if (posd > 0)
		{
			pos = (int)posd;
			if (posd > pos)
				pos++;
		}
	}

	pSView->pScrollBarH->rect.left = pSView->left;
	pSView->pScrollBarH->rect.top = cy - pSView->bottom - pSView->barWidth;
	pSView->pScrollBarH->rect.right = pSView->pScrollBarH->rect.left + pSView->sizeView.cx;
	pSView->pScrollBarH->rect.bottom = cy - pSView->bottom;

	XSBar_SetScrollRange((HELE)pSView->pScrollBarH, pos);

	//修改滚动条滑块长度
	int btnLength = XSBar_GetButtonLength((HELE)pSView->pScrollBarH);

	int len = 0;
	if (0 != pSView->sizeTotal.cx)
		len = (int)(((double)pSView->sizeView.cx / pSView->sizeTotal.cx)*(pSView->sizeView.cx - btnLength - btnLength - 2));

	XSBar_SetSliderLength((HELE)pSView->pScrollBarH, len);

	XSBar_Adjust((HELE)pSView->pScrollBarH);
	if (bShowH)  //显示
		XEle_ShowEle((HELE)pSView->pScrollBarH, TRUE);
	else
		XEle_ShowEle((HELE)pSView->pScrollBarH, FALSE);

	//垂直滚动条---------------------------
	//修改滚动点数

	int size2 = pSView->sizeTotal.cy - pSView->sizeView.cy;
	pos = 0;
	if (0 != size2 && 0 != pSView->sizeLine.cy)
	{
		posd = ((double)(size2)) / pSView->sizeLine.cy;
		if (posd > 0)
		{
			pos = (int)posd;
			if (posd > pos)
				pos++;
		}
	}

	//修改滚动条坐标
	pSView->pScrollBarV->rect.left = cx - pSView->right - pSView->barWidth;
	if (XC_LIST == ((ele_*)hEle)->eleType)
	{
		pSView->pScrollBarV->rect.top = 2;
	}
	else
		pSView->pScrollBarV->rect.top = pSView->top;
	pSView->pScrollBarV->rect.right = cx - pSView->right;
	pSView->pScrollBarV->rect.bottom = pSView->top + pSView->sizeView.cy;

	XSBar_SetScrollRange((HELE)pSView->pScrollBarV, pos);

	//修改滚动条滑块长度
	btnLength = XSBar_GetButtonLength((HELE)pSView->pScrollBarV);

	int len2 = 0;
	if (0 != pSView->sizeTotal.cy)
		len2 = (int)(((double)pSView->sizeView.cy / pSView->sizeTotal.cy)*(pSView->sizeView.cy - btnLength - btnLength - 2));

	XSBar_SetSliderLength((HELE)pSView->pScrollBarV, len2);

	XSBar_Adjust((HELE)pSView->pScrollBarV);

	if (bShowV) //显示
		XEle_ShowEle((HELE)pSView->pScrollBarV, TRUE);
	else
		XEle_ShowEle((HELE)pSView->pScrollBarV, FALSE);

	RECT rcView;
	rcView.left = pSView->left;
	rcView.top = pSView->top;
	rcView.right = rcView.left + pSView->sizeView.cx;
	rcView.bottom = rcView.top + pSView->sizeView.cy;
	XEle_SetRect(pSView->hView, &rcView);

}

/// @brief 滚动视图元素,获取滚动条的宽度,如果是水平滚动条,那么获取的是高度.
/// @param hEle 元素句柄.
/// @return 垂直滚动条的宽度或水平滚动条的高度.
int WINAPI XSView_GetScrollBarWidth(HELE hEle)  //获取滚动条宽度
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->barWidth;
}

/// @brief 水平滚动条当前是否可见.
/// @param hEle 元素句柄.
/// @return 如果水平滚动条当前可见,返回TRUE,否则相反.
BOOL WINAPI XSView_IsHScrollBarVisible(HELE hEle) //水平滚动条当前是否可见
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XEle_IsShowEle((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief 滚动视图元素,垂直滚动条当前是否可见.
/// @param hEle 元素句柄.
/// @return 如果垂直滚动条当前可见,返回TRUE,否则相反.
BOOL WINAPI XSView_IsVScrollBarVisible(HELE hEle) //垂直滚动条当前是否可见
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return XEle_IsShowEle((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief 滚动视图元素,启用或禁用水平滚动条.
/// @param hEle 元素句柄.
/// @param bEnable TRUE启用,FALSE禁用.
void WINAPI XSView_EnableHScroll(HELE hEle, BOOL bEnable) //启用水平滚动条
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	SCROLLVIEW(hEle)->bHScroll = bEnable;
}

/// @brief 滚动视图元素,启用或禁用垂直滚动条.
/// @param hEle 元素句柄.
/// @param bEnable TRUE启用,FALSE禁用.
void WINAPI XSView_EnableVScroll(HELE hEle, BOOL bEnable) //启用垂直滚动条
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	SCROLLVIEW(hEle)->bVScroll = bEnable;
}

/// @brief 获取视口宽度(不含边框间隔及滚动条).
/// @param hEle 元素句柄.
/// @return 视口宽度.
int  WINAPI XSView_GetViewWidth(HELE hEle)  //获取视口宽度
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->sizeView.cx;
}

/// @brief 滚动视图元素,获取滚动视图高度(不含边框间隔及滚动条).
/// @param hEle 元素句柄.
/// @return 视口高度.
int  WINAPI XSView_GetViewHeight(HELE hEle) //获取视口高度
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->sizeView.cy;
}

/// @brief 获取内容总宽度,精确的(不含边框间隔及滚动条),当内容大小小于视口大小时,返回的是视口大小.
/// @param hEle 元素句柄.
/// @return 内容总宽度.
int  WINAPI XSView_GetHSizeTotalAccurate(HELE hEle) //获取内容总宽度,精确的,,当内容大小小于视口大小时,返回的是视口大小
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	scrollView_ *pScrollView = SCROLLVIEW(hEle);
	int range = (SCROLLBAR(pScrollView->pScrollBarH))->range;
	return range*pScrollView->sizeLine.cx + pScrollView->sizeView.cx;
}

/// @brief 获取内容总高度,精确的(不含边框间隔及滚动条),当内容大小小于视口大小时,返回的是视口大小.
/// @param hEle 元素句柄.
/// @return 内容总高度.
int  WINAPI XSView_GetVSizeTotalAccurate(HELE hEle) //获取内容总高度,精确的,,当内容大小小于视口大小时,返回的是视口大小
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	scrollView_ *pScrollView = SCROLLVIEW(hEle);
	int range = SCROLLBAR(pScrollView->pScrollBarV)->range;
	return range*pScrollView->sizeLine.cy + pScrollView->sizeView.cy;
}

/// @brief 获取滚动视图左间隔大小.
/// @param hEle 元素句柄.
/// @return 滚动视图左间隔大小.
int WINAPI XSView_GetSpacingLeft(HELE hEle)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->left;
}

/// @brief 获取滚动视图上间隔大小.
/// @param hEle 元素句柄.
/// @return 滚动视图上间隔大小.
int WINAPI XSView_GetSpacingTop(HELE hEle)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->top;
}

/// @brief 获取滚动视图右间隔大小.
/// @param hEle 元素句柄.
/// @return 滚动视图右间隔大小.
int WINAPI XSView_GetSpacingRight(HELE hEle)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->right;
}

/// @brief 获取滚动视图下间隔大小.
/// @param hEle 元素句柄.
/// @return 滚动视图下间隔大小.
int WINAPI XSView_GetSpacingBottom(HELE hEle)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	return SCROLLVIEW(hEle)->bottom;
}

/// @brief 设置视口与边框间隔.
/// @param hEle 元素句柄.
/// @param left  左间隔.
/// @param top   上间隔.
/// @param right 右间隔.
/// @param bottom 下间隔.
void WINAPI XSView_SetSpacing(HELE hEle, int left, int top, int right, int bottom)
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	scrollView_ *pScrollView = SCROLLVIEW(hEle);
	pScrollView->left = left;
	pScrollView->top = top;
	pScrollView->right = right;
	pScrollView->bottom = bottom;

	XSView_Adjust(hEle);
}

/// @brief 设置滚动视图,水平滚动和垂直滚动每个滚动点视图滚动距离.
/// @param hEle 元素句柄.
/// @param line  水平滚动每个滚动点视图滚动距离.
/// @param column 垂直滚动每个滚动点视图滚动距离.
void WINAPI XSView_SetScrollSize(HELE hEle, int line, int column)  //设置滚动行和列大小
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	SCROLLVIEW(hEle)->sizeLine.cx = line;
	SCROLLVIEW(hEle)->sizeLine.cy = column;
	XSView_Adjust(hEle);
}

/// @brief 设置滚动视图元素背景贴图.
/// @param hEle 元素句柄.
/// @param hImage 图片句柄.
void WINAPI XSView_SetImage(HELE hEle, HIMAGE hImage)  //设置贴图
{
	IsScrollViewDebug(hEle, __FUNCTION__);
	if (hImage)
	{
		IsHImageDebug(hImage, __FUNCTION__);
	}
	Image_AddImage(SCROLLVIEW(hEle)->hImage_bk, hImage);
}

BOOL CALLBACK SView_OnDraw(HELE hEle, HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle, &rect);

	if (SCROLLVIEW(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw, SCROLLVIEW(hEle)->hImage_bk, &rect);
	}

	if (((ele_*)hEle)->bBorder)
	{
		HPEN hPen = XDraw_CreatePen_(hDraw, PS_SOLID, 1, ((ele_*)hEle)->borderColor);
		HGDIOBJ hOld = XDraw_SelectObject_(hDraw, hPen);
		if (SCROLLVIEW(hEle)->left > 0)
		{
			XDraw_MoveToEx_(hDraw, 0, 0, NULL);
			XDraw_LineTo_(hDraw, 0, rect.bottom);
		}
		if (SCROLLVIEW(hEle)->top > 0)
		{
			XDraw_MoveToEx_(hDraw, 0, 0, NULL);
			XDraw_LineTo_(hDraw, rect.right, 0);
		}
		if (SCROLLVIEW(hEle)->right > 0)
		{
			XDraw_MoveToEx_(hDraw, rect.right - 1, 0, NULL);
			XDraw_LineTo_(hDraw, rect.right - 1, rect.bottom);
		}
		if (SCROLLVIEW(hEle)->bottom > 0)
		{
			XDraw_MoveToEx_(hDraw, 0, rect.bottom - 1, NULL);
			XDraw_LineTo_(hDraw, rect.right, rect.bottom - 1);
		}
	}
	return TRUE;
}

BOOL CALLBACK SView_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	//	HELE hFocus=XWnd_GetFocusEle(XEle_GetHWindow(hEle));
	//	if(hFocus)
	//	{
		//	if(XEle_IsChildEle(hEle,hFocus))
		//	{
		//		return FALSE;
		//	}else
		//	{
		//		XEle_SetFocus(hEle,TRUE);
		//		return FALSE;
		//	}
	//	}
	//	XEle_SetFocus(hEle,TRUE);
	return FALSE;
}

BOOL CALLBACK SView_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	//	HELE hFocus=XWnd_GetFocusEle(XEle_GetHWindow(hEle));
	//	if(hFocus)
	//	{
	//		if(XEle_IsChildEle(hEle,hFocus))
	//		{
	//			return FALSE;
	//		}else
	//		{
	//			XEle_SetFocus(hEle,TRUE);
	//			return FALSE;
	//		}
	//	}
	//	XEle_SetFocus(hEle,TRUE);
	return FALSE;
}

BOOL CALLBACK SView_OnEventHScroll(HELE hEle, HELE hEventEle, int pos)
{
	if (hEventEle == (HELE)SCROLLVIEW(hEle)->pScrollBarH)
	{
		SCROLLVIEW(hEle)->hPos = pos;
		XEle_RedrawEle(hEle);
		Ele_SendEvent(hEle, XE_HSCROLLVIEW, pos, 0);

		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK SView_OnEventVScroll(HELE hEle, HELE hEventEle, int pos)
{
	//XTRACE("SView_OnEventVScroll \n");
	if (hEventEle == (HELE)SCROLLVIEW(hEle)->pScrollBarV)
	{
		SCROLLVIEW(hEle)->vPos = pos;
		XEle_RedrawEle(hEle);
		Ele_SendEvent(hEle, XE_VSCROLLVIEW, pos, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK SView_OnEventMouseWheel(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt) //滚轮事件
{
	int zDelta = GET_WHEEL_DELTA_WPARAM(flags);
	if (zDelta > 0) //上滚动 //WHEEL_DELTA
	{
		XSView_ScrollVPos(hEle, SCROLLVIEW(hEle)->vPos - (zDelta / WHEEL_DELTA) * 3);
	}
	else //下滚动
	{
		XSView_ScrollVPos(hEle, SCROLLVIEW(hEle)->vPos + ((-zDelta) / WHEEL_DELTA) * 3);
	}

	return TRUE;
}

BOOL CALLBACK SView_OnEventSize(HELE hEle, HELE hEventEle)
{
	if (hEle == hEventEle)
	{
		XSView_Adjust(hEle);
	}
	return FALSE;
}

BOOL CALLBACK SView_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt)
{
	XEle_SetFocus((HELE)((ele_*)hEle)->pParentEle, TRUE);

	return FALSE;
}


///@}