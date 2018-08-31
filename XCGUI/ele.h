/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct eleMsgOrEvent_Header_;
//事件转换函数
typedef BOOL(*pFunEleEventConversion)(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//消息转换函数2
typedef BOOL(*pFunEleMsgConversion)(HELE hEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);


////////////////////

struct eleMsgProc_   //消息过程链表
{
	void     *pFun; //函数指针
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
	void  *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
	eleMsgProc_ *pNext;
};

struct eleEventProc_ //事件过程链表
{
	void      *pFun; //函数指针
#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
	void  *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
	eleEventProc_ *pNext;
};

struct eleDestroy_ //元素销毁 Destroy
{
	void    *pFun; //函数指针
	eleDestroy_ *pNext;

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
	void  *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
};

//-------------------
struct eleMsgOrEvent_   //消息或事件
{
	void              *pFun; //消息事件对应的处理函数
	eleMsgOrEvent_    *pNext;

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
	void  *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
};

struct eleMsgOrEvent_Header_  //消息或事件 链表头  
{
	eleMsgOrEvent_  *pList;  //注册的消息或事件体链表
	union   //排序依据
	{
		int   message;    //消息类型                 
		int   Event;      //事件类型
	};
	union
	{
		pFunEleMsgConversion    pFunMsgConv;   //消息转换函数
		pFunEleEventConversion  pFunEventConv; //事件转换函数
	};
};

//-------------------
struct window_;
struct ele_  //T1 元素基类
{
	object_ object;
	int     eleType;     //元素完整类型

	//-----------------------------------
	ele_ *pParentEle;    //父元素
	RECT rect;
	int  id;              //元素ID
	BOOL bShow;           //元素是否显示
	BOOL bEnable;         //元素是否有效
	BOOL bClient;         //元素是否在非客户区, TRUE:客户区 ,FALSE:非客户区
	BOOL bBkTransparent;  //元素背景透明
	BOOL bTopLevel;       //是否为顶级元素
	BOOL bEnableFocus;    //可以获得焦点
	BOOL bDrawFocus;      //是否绘制焦点
	BOOL bToolTips;       //是否启用工具提示
	BOOL bTransparentChannel;//启用透明通道,Transparent channel
	BOOL bDestroy;         //防止重复调用销毁函数
	BOOL bMouseThrough;    //鼠标穿透

	int  userData;         //用户数据,内部不使用

	ele_     *pMouseTop;   //当前鼠标在哪个子元素上面,该元素的顶级子元素,不包含子元素的子元素
	POINT    elePt;        //配合滚动视图,元素实际坐标.
	HSTRING  hToolTipsStr; //工具提示内容
	COLORREF bkColor;      //背景颜色
//	HFONT    hFont;        //字体
	//LOGFONT  fontInfo;   //当前字体信息
	HFONTX   hFontX;

	COLORREF textColor;    //字体颜色
	window_  *pWindow;     //所属窗口指针

	BOOL     bBorder; //是否启用边框,该边框只是起到描边作用
	COLORREF borderColor; //边框颜色

	HARRAY hArray_msg;    //消息数组,自动排序  eleMsgOrEvent_Header_
	HARRAY hArray_event;  //事件数组,自动排序  eleMsgOrEvent_Header_
	HARRAY hArrayEle;     //子元素列表   ele_*

	eleMsgProc_      *pMsgProcList;   //元素消息处理过程列表
	eleEventProc_    *pEventProcList; //元素事件处理过程列表
	eleDestroy_      *pDestroyList;   //元素析构函数列表

	//样式:
	HSTRING  hString_Style_Class; //套用样式名
};

#ifdef XCGUI_PLUS  //C++类支持
XC_API void WINAPI XEle_RegisterEventEx(HELE hEle, int type, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);

XC_API void WINAPI XEle_RegisterMessageEx(HELE hEle, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //注册消息
XC_API void WINAPI XEle_RegisterMsgProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);    //注册元素消息处理过程
XC_API void WINAPI XEle_RegisterEventProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //注册事件拦截过滤函数

#endif


//元素API:

/// @defgroup element 基础元素(Element)
/// @ingroup  groupElements
/// 基础元素接口列表
/// @{

/// @brief    创建基础元素
/// @param x  元素x坐标
/// @param y  元素y坐标
/// @param cx 宽度
/// @param cy 高度
/// @param hParent 父是窗口句柄或元素句柄.
/// @return 元素句柄.
XC_API HELE WINAPI XEle_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL); //创建

/// @brief 销毁UI元素,该元素会自动从父(元素或窗口)中移除,同时销毁该元素的子元素.
/// @param hEle 元素句柄
/// @return 成功返回TRUE,如果元素已经销毁或正在销毁返回FALSE.
XC_API BOOL WINAPI XEle_Destroy(HELE hEle);  //销毁

//注册
///@name 注册
///@{

/// @brief 注册元素消息处理函数.
/// @param hEle 元素句柄.
/// @param message 元素消息类型.
/// @param pFun    处理消息函数名.
XC_API void WINAPI XEle_RegisterMessage(HELE hEle, int message, void *pFun);

/// @brief 注册元素事件处理函数.
/// @param hEle 元素句柄.
/// @param type 事件类型.
/// @param pFun 事件处理函数名.
XC_API void WINAPI XEle_RegisterEvent(HELE hEle, int type, void *pFun);

/// @brief 注册元素消息处理过程.
/// @param hEle 元素句柄.
/// @param pFun 处理过程函数名.参数类型如下:
/// @code BOOL CALLBACK EleMsgProc(HELE hEle,UINT eleMessage,WPARAM wParam,LPARAM lParam); @endcode
XC_API void WINAPI XEle_RegisterMsgProc(HELE hEle, pFunEleMsgProc pFun);    //注册元素消息处理过程

/// @brief 注册元素事件处理过程.
/// @param hEle 元素句柄
/// @param pFun 事件处理过程函数名.参数类型如下:
/// @code  BOOL CALLBACK EleEventProc(HELE hEle,int type,WPARAM wParam,LPARAM lParam); @endcode
XC_API void WINAPI XEle_RegisterEventProc(HELE hEle, pFunEleEventProc pFun);  //注册元素事件处理过程

///@}

/// @brief  设置元素背景透明.
/// @param hEle 元素句柄.
/// @param bTran TRUE背景透明,否则不透明.
XC_API void WINAPI XEle_SetBkTransparent(HELE hEle, BOOL bTran);   //设置元素背景透明

/// @brief 设置元素焦点.
/// @param hEle 元素句柄.
/// @param bFocus TRUE设置该元素拥有焦点,否则相反.
XC_API void WINAPI XEle_SetFocus(HELE hEle, BOOL bFocus); //设置焦点

/// @brief 设置元素id标识符.
/// @param hEle 元素句柄
/// @param id 标识符.
XC_API void WINAPI XEle_SetId(HELE hEle, int id);

/// @brief 设置元素字体.
/// @param hEle 元素句柄
/// @param hFontX 字体句柄.
XC_API void WINAPI XEle_SetFont(HELE hEle, HFONTX hFontX);

/// @brief 获取元素字体.
/// @param hEle 元素句柄
/// @return 字体句柄.
XC_API HFONTX WINAPI XEle_GetFont(HELE hEle); //获取字体

/// @brief 设置元素Z序,hEle和hDestEle必须是同级元素,相同的父.
/// @param hEle 元素句柄
/// @param hDestEle 目标元素句柄.
/// @param flag  标识
/// @param index 索引
/// @return 成功返回TRUE,失败FALSE.
XC_API BOOL WINAPI XEle_SetZOrder(HELE hEle, HELE hDestEle = NULL, int flag = XC_ZORDER_TOP, int index = NULL);

/// @brief 设置元素背景颜色.
/// @param hEle 元素句柄
/// @param color RGB颜色值.
XC_API void WINAPI XEle_SetBkColor(HELE hEle, COLORREF color); //设置背景颜色

/// @brief 获取元素背景颜色.
/// @param hEle 元素句柄.
/// @return 元素背景颜色.
XC_API COLORREF WINAPI XEle_GetBkColor(HELE hEle); //获取背景颜色

/// @brief 设置边框颜色.
/// @param hEle  元素句柄
/// @param color 颜色值.
XC_API void WINAPI XEle_SetBorderColor(HELE hEle, COLORREF color); //设置边框颜色

/// @brief 设置元素工具提示内容,然后调用 XEle_EnableToolTips()启用.
/// @param hEle 元素句柄
/// @param pText 文本内容.
XC_API void WINAPI XEle_SetToolTips(HELE hEle, wchar_t *pText); //设置工具提示内容

/// @brief 设置元素鼠标捕获.
/// @param hEle 元素句柄
XC_API void WINAPI XEle_SetCapture(HELE hEle);   //设置元素鼠标捕获

/// @brief 获取工具提示内容.
/// @param hEle 元素句柄.
/// @return 工具提示内容.
XC_API wchar_t* WINAPI XEle_GetTooltips(HELE hEle);  //获取工具提示内容

/// @brief 获取父元素句柄.
/// @param hEle 元素句柄
/// @return 父元素句柄.
XC_API HELE WINAPI XEle_GetParentEle(HELE hEle);  //获取父元素句柄

/// @brief 获取子元素数量,不包含子元素的子元素.
/// @param hEle 元素句柄.
/// @return 子元素数量.
XC_API int  WINAPI XEle_GetChildCout(HELE hEle);  //获取子元素数量

/// @brief 获取指定索引子元素.
/// @param hEle 元素句柄.
/// @param index 子元素索引.
/// @return 子元素句柄.
XC_API HELE WINAPI XEle_GetChildByIndex(HELE hEle, int index);	//获取指定子元素

/// @brief 获取元素所在窗口句柄.
/// @param hEle 元素句柄
/// @return 窗口句柄HWND.
XC_API HWND WINAPI XEle_GetHWnd(HELE hEle);  //获取窗口句柄

/// @brief 获取元素所在窗口的窗口句柄.
/// @param hEle 元素句柄.
/// @return 窗口资源句柄.
XC_API HWINDOW WINAPI XEle_GetHWindow(HELE hEle); //获取窗口资源句柄

/// @brief 获取用户数据.
/// @param hEle 元素句柄
/// @return 用户数据.
XC_API int  WINAPI XEle_GetUserData(HELE hEle);  //获取用户数据

/// @brief获取元素ID
/// @param hEle 元素句柄
/// @return 元素ID.
XC_API int WINAPI XEle_GetId(HELE hEle);

/// @brief 释放元素鼠标捕获.
/// @param hEle 元素句柄
XC_API void WINAPI XEle_ReleaseCapture(HELE hEle);   //释放元素鼠标捕获

/// @brief 元素是否有效.
/// @param hEle 元素句柄
/// @param bEnable TRUE元素有效,否则相反.
XC_API void WINAPI XEle_EnableEle(HELE hEle, BOOL bEnable); //元素是否有效

/// @brief 元素允许获得焦点.
/// @param hEle 元素句柄
/// @param bFocus  TRUE允许获得焦点,否则相反.
XC_API void WINAPI XEle_EnableFocus(HELE hEle, BOOL bFocus); //开启焦点

/// @brief 是否绘制焦点.
/// @param hEle 元素句柄
/// @param bFocus  如果值为TRUE绘制焦点,否则相反.
XC_API void WINAPI XEle_EnableDrawFocus(HELE hEle, BOOL bFocus); //是否绘制焦点

/// @brief 元素启用工具提示功能.
/// @param hEle 元素句柄
/// @param bTips TRUE启用工具提示,否则相反
XC_API void WINAPI XEle_EnableToolTips(HELE hEle, BOOL bTips);  //启用工具提示

/// @brief 启用或关闭绘制元素边框.
/// @param hEle 元素句柄.
/// @param bEnable  如果为TRUE启用,否则相反.
XC_API void WINAPI XEle_EnableBorder(HELE hEle, BOOL bEnable); //绘制边框

/// @brief 启用透明通道,当窗口透明,并且元素背景透明时有效,需要用户自己设置PNG图片来处理元素的透明通道.
/// @param hEle 元素句柄.
/// @param bEnable  如果为TRUE启用,否则相反.
XC_API void WINAPI XEle_EnableTransparentChannel(HELE hEle, BOOL bEnable);

/// @brief 添加元素.添加一个子元素,到当前元素下.
/// @param hEle 元素句柄.
/// @param hNewEle  要添加的子元素资源句柄.
/// @param flag     标识.
/// @param hDestEle  hDestEle为添加元素的相对位置;flag当为XC_ADDELE_AFTER或XC_ADDELE_BEFORE标识时有效.
/// @param index   为添加元素的基于0索引位置,flag当为XC_ADDELE_INDEX标识时有效.
/// @return 如果成功返回TRUE,否则相反.
XC_API BOOL WINAPI XEle_AddEle(HELE hEle, HELE hNewEle, int flag = XC_ADDELE_END, HELE hDestEle = 0, int index = 0); //添加元素

/// @brief 移除元素,但是不销毁.
/// @param hEle 元素句柄.
XC_API void WINAPI XEle_RemoveEle(HELE hEle);   //移除元素,但不销毁

/// @brief 重绘该元素.
/// @param hEle 元素句柄.
/// @param bImmediately   TRUE立即重绘,FALSE放入消息队列延迟重绘.
XC_API void WINAPI XEle_RedrawEle(HELE hEle, BOOL bImmediately = FALSE); //重绘元素

/// @brief 重绘元素指定区域,立即重绘,该元素重绘时并不绘制它的父元素,只有当父元素透明时,才会绘制父元素.
/// @param hEle 元素句柄.
/// @param pRect 重绘区域.
XC_API void WINAPI XEle_RedrawRect(HELE hEle, RECT *pRect); //元素重绘指定区域

/// @brief 显示隐藏元素.
/// @param hEle 元素句柄.
/// @param bShow  TRUE显示元素,否则相反.
XC_API void WINAPI XEle_ShowEle(HELE hEle, BOOL bShow);

/// @brief 判断元素背景是否透明.
/// @param hEle 元素句柄
/// @return 如果元素背景透明返回TRUE,否则相反.
XC_API BOOL WINAPI XEle_IsBkTransparent(HELE hEle); //元素背景是否透明

/// @brief 判断元素是否拥有焦点 .
/// @param hEle 元素句柄
/// @return 如果元素拥有焦点返回TRUE,否则相反.
XC_API BOOL WINAPI XEle_IsFocus(HELE hEle); //元素是否拥有焦点

/// @brief 元素是否显示.
/// @param hEle 元素句柄.
/// @return 如果显示返回TRUE,否则返回FALSE.
XC_API BOOL WINAPI XEle_IsShowEle(HELE hEle); //元素是否显示

/// @brief 判断指定坐标点是否在子元素之上.
/// @param hEle 元素句柄
/// @param pPt  坐标点位置.
/// @return 坐标点在子元素上返回TRUE,否则返回FALSE.
XC_API BOOL WINAPI XEle_IsHitChildEle(HELE hEle, POINT *pPt); //判断是否点击在子元素上

/// @brief 判断指定元素是否为子元素.
/// @param hEle 元素句柄
/// @param hChild   子元素句柄.
/// @return hChild如果是hEle的子元素返回TRUE,否则返回FALSE.
XC_API BOOL WINAPI XEle_IsChildEle(HELE hEle, HELE hChild);  //判断指定元素是否为子元素

/// @brief 设置元素用户数据.
/// @param hEle 元素句柄.
/// @param data 用户数据.
XC_API void WINAPI XEle_SetUserData(HELE hEle, int data);  //设置用户数据

/// @brief 设置定时器,非系统定时器.
/// @param hEle       元素句柄.
/// @param nIDEvent   定时器标识符.
/// @param uElapse    间隔时间毫秒.
/// @param userData   绑定数据.
/// @param userData   用户数据.
/// @return 成功返回TRUE,否则相反.
XC_API UINT WINAPI XEle_SetTimerEx(HELE hEle, UINT nIDEvent, UINT uElapse, int userData = 0);

/// @brief 关闭定时器,非系统定时器.
/// @param hEle       元素句柄.
/// @param nIDEvent 定时器标识符.
/// @return 成功返回TRUE,否则相反.
XC_API BOOL WINAPI XEle_KillTimerEx(HELE hEle, UINT nIDEvent);


//坐标API:
///@name 坐标
///@{

/// @brief 设置元素坐标.
/// @param hEle 元素句柄
/// @param[in] pRect  元素坐标.
/// @param bRedraw 如果值为TRUE重绘元素,否则相反.
XC_API void WINAPI XEle_SetRect(HELE hEle, in_ RECT *pRect, BOOL bRedraw = FALSE);

/// @brief 获取元素大小,左上角(0,0).
/// @param hEle 元素句柄
/// @param[out] pRect  接收元素坐标.
XC_API void WINAPI XEle_GetClientRect(HELE hEle, out_ RECT *pRect);   //元素客户区坐标 xy(0,0) ,如果元素有边框,包含边框区域

/// @brief 获取元素坐标,基于父元素坐标系.
/// @param hEle 元素句柄
/// @param[out] pRect  接收元素坐标.
XC_API void WINAPI XEle_GetRect(HELE hEle, out_ RECT *pRect);         //基于父元素坐标

/// @brief 获取元素基于窗口客户区坐标.
/// @param hEle 元素句柄
/// @param[out] pRect  接收元素坐标.
XC_API void WINAPI XEle_GetWndClientRect(HELE hEle, out_ RECT *pRect); //元素基于窗口客户区坐标(不包含非客户区)

/// @brief 获取元素坐标,基于窗口非客户区坐标,包含非客户区.
/// @param hEle 元素句柄
/// @param[out] pRect  接收元素坐标.
XC_API void WINAPI XEle_GetNCWndRect(HELE hEle, out_ RECT *pRect); //基于窗口非客户区坐标(包含非客户区)

/// @元素坐标,转换到父元素坐标
/// @param hEle 元素句柄
/// @param[in,out] pPt  输入坐标点转换输出.
XC_API void WINAPI XEle_PointToParent(HELE hEle, in_out_ POINT *pPt);

/// @brief 元素坐标点转换到窗口客户区坐标点,不包含非客户区.
/// @param hEle 元素句柄
/// @param[in,out] pPt  输入坐标点转换输出.
XC_API void WINAPI XEle_PointToWndClient(HELE hEle, in_out_ POINT *pPt);     //元素坐标点转换到窗口客户区坐标点(不包含非客户区)

/// @brief 元素坐标点转换到窗口非客户区坐标点,包含非客户区.
/// @param hEle 元素句柄
/// @param[in,out] pPt  输入坐标转换输出.
XC_API void WINAPI XEle_PointToNCWnd(HELE hEle, in_out_ POINT *pPt);

/// @brief 窗口非客户区坐标转换到元素坐标.
/// @param hEle 元素句柄
/// @param[in,out] pPt  输入基于窗口非客户区的坐标点(包含非客户区),输出基于元素坐标点.
XC_API void WINAPI XEle_PointNCWndToEle(HELE hEle, in_out_ POINT *pPt);

/// @brief 窗口客户区坐标转换到元素坐标,不包含非客户区.
/// @param hEle 元素句柄
/// @param[in,out] pPt  输入基于窗口坐标点(不包含非客户区),输出基于元素坐标点.
XC_API void WINAPI XEle_PointWndClientToEle(HELE hEle, in_out_ POINT *pPt);

/// @brief 元素坐标转换到窗口客户区坐标,不包含非客户区.
/// @param hEle 元素句柄
/// @param[in,out] pRect 输入元素坐标,返回基于窗口的坐标,不包含标题栏和边框区域.
XC_API void WINAPI XEle_RectToWndClient(HELE hEle, in_out_ RECT *pRect);

/// @brief 元素坐标系转换为窗口非客户区坐标系.
/// @param hEle 元素句柄
/// @param[in,out] pRect 输入元素客户区坐标 ,输出基于窗口非客户区坐标,包含标题栏和边框区域.
XC_API void WINAPI XEle_RectToNCWnd(HELE hEle, in_out_ RECT *pRect);


///@}

/// @brief 设置文本颜色.
/// @param hEle  元素句柄.
/// @param color 文本颜色
XC_API void WINAPI XEle_SetTextColor(HELE hEle, COLORREF color); //设置文本颜色

/// @brief 获取文本颜色.
/// @param hEle  元素句柄.
/// @return 文本颜色
XC_API COLORREF WINAPI XEle_GetTextColor(HELE hEle); //获取文本颜色

/// @brief 启用鼠标穿透元素,该元素将不接收鼠标消息,鼠标消息从该元素穿过;与元素禁用不同,禁用的元素会终止鼠标消息不能穿透.
/// @param hEle  元素句柄.
/// @param bEnable  是否启用.
XC_API void WINAPI XEle_EnableMouseThrough(HELE hEle, BOOL bEnable);  //启用鼠标穿透元素

///@}


//TODO:待改进
//BOOL Ele_SendEvent(HELE hEle,int type,WPARAM wParam,LPARAM lParam); //发生事件,立即处理并返回结果
//void Ele_PostEvent(HELE hEle,int type,WPARAM wParam,LPARAM lParam); //发生事件,延时处理无返回结果

BOOL Ele_SendEvent(HELE hEle, int type, WPARAM wParam, LPARAM lParam, BOOL bImmediately = TRUE); //发生事件
BOOL Ele_SendEleMsg(HELE hEle, UINT eleMessage, WPARAM wParam, LPARAM lParam); //发送元素消息

//私有方法:
void Ele_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent); //初始化注册

BOOL Ele_Draw_InspectionArea(HELE hEle, RECT &rect, RECT &rcDest); //检查绘制区域
void Ele_Draw_Dispatch(HELE hEle, HDRAW hDraw, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
void Ele_Draw_Child(HELE hEle, HDRAW hDraw); //绘制子元素

BOOL Ele_EventDispatch(HELE hEle, int type, WPARAM wParam, LPARAM lParam); //事件调度,窗口调用
BOOL Ele_SetWindow(HELE hEle, HWINDOW hWindow, BOOL bClient = TRUE); //设置父窗口
void Ele_BreakWindow(HELE hEle); //递归断开与窗口联系,子元素保持与父元素关系,以便重用, XEle_RemoveEle()专用
BOOL Ele_HandleMousePt(HELE hEle, UINT flags, POINT *pPt, int message);  //处理鼠标按下/弹起 
void Ele_SetType(HELE hEle, int type); //设置元素最终类型

void Ele_HandleScrollView(HELE hEle, HDC hdc, int srcX, int srcY); //处理滚动视图


//消息转换:
BOOL Ele_ConvMsgPaint(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgMouseClick(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgMouseDBClick(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgMouseMove(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgLButtonDown(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgLButtonUp(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgRButtonDown(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgRButtonUp(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgTimerEx(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);

//事件转换:
BOOL Ele_ConvEventBtnClick(HELE hEle, HELE hEleClick, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventMouseStay(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //鼠标停留
BOOL Ele_ConvEventMouseLeave(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSetFocus(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventKillFocus(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventKeyDown(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventChar(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventHScroll(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventVScroll(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventHScrollView(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventVScrollView(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSetCapture(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //获得鼠标捕获
BOOL Ele_ConvEventKillCapture(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //失去鼠标捕获
BOOL Ele_ConvEventMouseWheel(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);  //滚轮事件
BOOL Ele_ConvEventMenuSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);  //滚轮事件
BOOL Ele_ConvEventMenuExit(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);  //滚轮事件
BOOL Ele_ConvEventListSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListHeaderClick(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //列表头项点击
BOOL Ele_ConvEventListHeaderChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //列表头宽度改变
BOOL Ele_ConvEventTreeSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //树列表选择改变
BOOL Ele_ConvEventTreeExpand(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //树项展开或收缩
BOOL Ele_ConvEventComboBoxSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //下拉组合框选择事件
BOOL Ele_ConvEventComboBoxPopupList(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventComboBoxExitList(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventPPageSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSliderChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventMonthChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventDateTimeChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventDateTimePopupMonthCal(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventDateTimeExitMonthCal(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventSetFont(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventShow(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSize(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListBoxSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPGridSelChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPGridValueChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventListViewSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListViewExpand(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListViewDragInsert(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventPaneLock(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPaneDock(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPaneFloat(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventEditChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventComboBoxChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListBoxChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventTreeChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//回调函数:
BOOL CALLBACK Ele_WindowProc(HELE hEle, UINT message, WPARAM wParam, LPARAM lParam); //元素消息处理过程
BOOL CALLBACK Ele_EventProc(HELE hEle, int type, WPARAM wParam, LPARAM lParam);  //事件过程

//消息回调
BOOL CALLBACK Ele_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Ele_OnMouseClick(HELE hEle, POINT *pPt);
BOOL CALLBACK Ele_OnMouseDBClick(HELE hEle, POINT *pPt);
BOOL CALLBACK Ele_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt);


//事件回调函数:
BOOL CALLBACK Ele_OnEventMouseSay(HELE hEle, HELE hEventEle); //鼠标停留
BOOL CALLBACK Ele_OnEventMouseLeave(HELE hEle, HELE hEventEle); //鼠标离开


//工具提示
extern HELE g_hTooltipsEle;     //当前配合工具提示的元素
extern HWINDOW g_hToolTipsWnd;  //工具提示窗口
VOID CALLBACK Ele_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
BOOL CALLBACK ToolTips_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);

#if 0
//继承模型
struct T1 //基类
{
	int data;
	//----------------------
	int  type;    //元素完整类型
	void *pChild; //子类->T2
};

struct T2 //public : T1  //继承T1
{
	T1  t1; //继承
	//--------------------
	int data;
	//---------------
	void *pChid;  //子类->T3
};

struct T3  //public : T2    //继承T2
{
	T2 t2; //继承
	//-------------------------
	int data;
	//----------------------
	void *pChild;  //子类->T4
};
#endif