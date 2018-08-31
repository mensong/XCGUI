/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct windowMsg_Header_;
//消息转换函数
typedef BOOL(*pFunConversion)(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

struct windowProc_
{
	void  *pFun; //窗口消息处理过程函数
#ifdef XCGUI_PLUS  //C++类支持
	void  *pClass_Fun_Info; //消息事件回调函数信息指针
#endif
	windowProc_      *pNext;
};

//////////////////////////////////////
struct windowMsg_   //窗口消息
{
	void  *pFun; //消息对应的处理函数
#ifdef XCGUI_PLUS  //C++类支持
	void  *pClass_Fun_Info; //消息事件回调函数信息指针
#endif
	windowMsg_    *pNext;
};

struct windowMsg_Header_  //窗口消息 链表头  
{
	windowMsg_  *pList;  //注册的窗口消息链表
	int   message;    //消息类型      //排序依据           

	pFunConversion  pFunConv;   //消息转换函数
};

//窗口重绘优化
struct draw_window_
{
	//HWINDOW hWindow;
//	BOOL    bEmpty;  //
	BOOL    bValid;  //是否有效,是否为空
	HELE    hEle;    //重绘元素,如果为空重绘窗口

//	BOOL    bRect;   //是否为重绘指定区域
	RECT    rect;    //基于窗口非客户区坐标,整个窗口
};

//窗口贴图样式,内部使用
//#define  XC_CS_IMAGE_STRETCH                1    //客户区图片拉伸
//#define  XC_CS_IMAGENC_STRETCH              2    //非客户区图片拉伸
//#define  XC_CS_IMAGE_CAPTION_STRETCH        4    //标题栏图片拉伸
//#define  XC_CS_IMAGE_BORDER_LEFT_STRETCH    8    //边框图片拉伸left
//#define  XC_CS_IMAGE_BORDER_RIGHT_STRETCH   16   //边框图片拉伸right
//#define  XC_CS_IMAGE_BORDER_BOTTOM_STRETCH  32   //边框图片拉伸bottom
#define  XC_CS_STROKE_INNER                 64   //是否描边 内
#define  XC_CS_STROKE_OUTER                 128  //是否描边 外


struct window_ //窗口信息
{
	object_  object;
	int      exType; //窗口扩展类型(完整类型)
	//---------------------------------------
	HWND    hWnd;
	HARRAY  hArrayEle;    //子元素列表
	HARRAY  hArrayEleNC;  //子元素列表,非客户区
	HELE    pCapture;     //拥有鼠标捕获权的元素指针
	ele_    *pMouseTop;   //当前鼠标在哪个元素上面
	ele_    *pFocus;      //拥有输入焦点的元素
	ele_    *pOldFocus;   //当窗口获得焦点时,用于恢复元素焦点
	int     userData;     //用户数据

	//窗口标识
	///////////////////////////////////////////////////
	int   captionHeight; //标题栏高度
	int   borderLeft;     //左边框宽度
	int   borderRight;    //右边框宽度
	int   borderBottom;   //下边框高度
	int   borderTop;      //上边框高度,如果有标题栏忽略

	int   minWidth;       //窗口最小宽度
	int   minHeight;      //窗口最小高度

	int   roundSize;      //圆角窗口,圆角大小

	SIZE  iconSize;       //标题栏图标显示大小
	BOOL  bTrackLeave;    //鼠标离开窗口

	HELE  hClose;      //关闭按钮
	HELE  hMaxinize;   //最大化按钮
	HELE  hMinimize;   //最小化按钮
	HELE  hMenuBar;    //菜单条
	HELE  hToolBar;    //工具条

	RECT  rcOld;       //窗口先前大小
	int   xcStyle;       //窗口样式

	BOOL  bClickTimer; //定时器是否启动,防止重复启动
	BOOL  bMouseUp, bMouseDown2;
	POINT mouseDown;  //鼠标第一次按下位置
	POINT mouseUp;    //鼠标第一次弹起位置
	POINT mouseDown2; //鼠标第二次按下位置

	scrollBar_ *pScrollBar; //滚动条

	//插入符
	int    caretWidth;   //插入符宽度
	int    caretHeight;  //插入符高度
	POINT  caretPt;      //插入符位置,基于元素坐标点
	HELE   hCaretEle;    //插入符元素
	BOOL   bCaretShow;   //是否显示
	BOOL   bCaretErase;  //是否需要擦出,TRUE:需要擦出插入符
//	BOOL   bCaretIsShow;   //插入符当前是否显示

	HBITMAP  hCaretBitmap; //插入符背景,用于恢复
	COLORREF caretColor;   //插入符颜色

	//窗口绘制
	HFONTX  hFontX;   //字体
	RECT   rcDraw;  //当前需要重绘区域,非客户区坐标
	HDC    hBkDC;   //窗口背景DC 

	COLORREF  bkColor;  //窗口背景颜色

	HBITMAP hBtimap; //窗口背景画布, 分层窗口有效
	SIZE    sizeWnd; //先前窗口大小

	//窗口绘制优化
	draw_window_   drawWindow;
	//DWORD          timerDraw;  //最近绘制时间

	//透明窗口
	int   transparentFlag;  //透明窗口标识
	int   transparentAlpha; //窗口透明度 0-255
	int   transparentColor; //窗口透明色

	//贴图---------------------
	int    chartletStyle;  //贴图样式
	HIMAGE hImage_client;   //客户区图片
	HIMAGE hImageNC;       //非客户区图片
	HIMAGE hImageCaption;  //标题栏图片
	HIMAGE hImageLeft;     //边框图片left
	HIMAGE hImageRight;    //边框图片right
	HIMAGE hImageBottom;   //边框图片bottom

	COLORREF  strokeOuter_color1; //描边颜色1 外 边框的外侧,窗口的内侧
	COLORREF  strokeOuter_color2; //描边颜色2 内 边框的内存,窗口的外侧

	COLORREF  strokeInner_color1; //描边颜色1 外 窗口的内侧
	COLORREF  strokeInner_color2; //描边颜色2 内 窗口的外侧

	/////////////////////////////////////
	HARRAY hArray_msg;   //消息数组,自动排序  windowMsg_Header_
	HARRAY hArray_NCmsg; //消息数组,自动排序  windowMsg_Header_

	windowProc_ *pWndProc;    //窗口消息处理过程链表

	HARRAY  hArrayPGrids;  //处理属性网格值改变事件, 该窗口上的属性网格句柄
};

#ifdef XCGUI_PLUS  //C++类支持
XC_API void WINAPI XWnd_RegisterMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //注册消息回调函数
XC_API void WINAPI XWnd_RegisterNCMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //注册非客户区消息
XC_API void WINAPI XWnd_RegisterMsgProcEx(HWINDOW hWindow, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);	//注册窗口消息处理过程
#endif

/// @defgroup window 普通窗口
/// @ingroup groupWindows
/// 窗口接口列表

//窗口API:
XC_API HWINDOW WINAPI XWnd_CreateWindow(int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent = NULL, int XCStyle = XC_SY_DEFAULT);
XC_API HWINDOW WINAPI XWnd_CreateWindowEx(DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle = XC_SY_DEFAULT);

XC_API void WINAPI XWnd_RegisterMessage(HWINDOW hWindow, int message, void *pFun);  //注册消息回调函数
XC_API void WINAPI XWnd_RegisterNCMessage(HWINDOW hWindow, int message, void *pFun); //注册非客户区消息
XC_API void WINAPI XWnd_RegisterMsgProc(HWINDOW hWindow, pFunWndMsgProc pFun);	//注册窗口消息处理过程

XC_API void WINAPI XWnd_GetDrawRect(HWINDOW hWindow, out_ RECT *pRect);//获取当前绘制区域(包含非客户区)
XC_API HELE WINAPI XWnd_GetFocusEle(HWINDOW hWindow); //获取拥有焦点的元素
XC_API HWND WINAPI XWnd_GetHWnd(HWINDOW hWindow); //获取窗口句柄
XC_API HELE WINAPI XWnd_GetEle(HWINDOW hWindow, int eleID); //通过ID获取元素句柄
XC_API HICON WINAPI XWnd_GetIcon(HWINDOW hWindow, BOOL bBigIcon);//获取窗口图标

XC_API int WINAPI XWnd_GetWindowText(HWINDOW hWindow, wchar_t *pOut, int len);
XC_API BOOL WINAPI XWnd_SetWindowText(HWINDOW hWindow, wchar_t *pText);

XC_API void WINAPI XWnd_SetFont(HWINDOW hWindow, HFONTX hFontX);
XC_API DWORD WINAPI XWnd_SetIcon(HWINDOW hWindow, HICON hIcon, BOOL bBigIcon);
XC_API DWORD WINAPI XWnd_SetIcon2(HWINDOW hWindow, wchar_t *pFileName, BOOL bBigIcon);
XC_API void WINAPI XWnd_SetIconSize(HWINDOW hWindow, int width, int height);  //设置标题栏图标显示大小

XC_API UINT WINAPI XWnd_SetTimer(HWINDOW hWindow, UINT nIDEvent, UINT uElapse); //设置定时器
XC_API BOOL WINAPI XWnd_KillTimer(HWINDOW hWindow, UINT nIDEvent);

XC_API UINT WINAPI XWnd_SetTimerEx(HWINDOW hWindow, UINT nIDEvent, UINT uElapse, int userData = 0);
XC_API BOOL WINAPI XWnd_KillTimerEx(HWINDOW hWindow, UINT nIDEvent);

XC_API void WINAPI XWnd_SetMinWidth(HWINDOW hWindow, int width);  //设置窗口最小宽度
XC_API void WINAPI XWnd_SetMinHeight(HWINDOW hWindow, int height); //设置窗口最小高度
XC_API void WINAPI XWnd_SetRoundSize(HWINDOW hWindow, int size);    //设置窗口圆角大小,对圆角窗口有效

XC_API void WINAPI XWnd_AddEle(HWINDOW hWindow, HELE hEle);
XC_API void WINAPI XWnd_AddEleNC(HWINDOW hWindow, HELE hEle); //添加到非客户区

XC_API void WINAPI XWnd_AddMenuBar(HWINDOW hWindow, HELE hEle); //添加工具条
XC_API void WINAPI XWnd_AddToolBar(HWINDOW hWindow, HELE hEle); //添加工具条

XC_API void WINAPI XWnd_Adjust(HWINDOW hWindow);  //调整窗口布局

XC_API void WINAPI XWnd_MaximizeWnd(HWINDOW hWindow, BOOL bMax); //最大化 还原窗口
XC_API BOOL WINAPI XWnd_IsMaximizeWnd(HWINDOW hWindow);  //窗口是否最大化
XC_API void WINAPI XWnd_RedrawWndRect(HWINDOW hWindow, RECT *pRect, BOOL bImmediately = FALSE); //重绘窗口指定区域
XC_API void WINAPI XWnd_RedrawWnd(HWINDOW hWindow, BOOL bImmediately = FALSE); //重绘窗口

XC_API void WINAPI XWnd_RedrawEleRectNC(HWINDOW hWindow, HELE hEle, RECT *pRect);

XC_API void WINAPI XWnd_EnableDragBorder(HWINDOW hWindow, BOOL bDrag);  //使用拖动边框
XC_API void WINAPI XWnd_EnableDragWindow(HWINDOW hWindow, BOOL bDrag);  //拖动窗口

//获取标题栏按钮:
XC_API HELE WINAPI XWnd_GetButtonMin(HWINDOW hWindow);   //最小化按钮
XC_API HELE WINAPI XWnd_GetButtonMax(HWINDOW hWindow);   //最大化按钮
XC_API HELE WINAPI XWnd_GetButtonClose(HWINDOW hWindow); //关闭按钮

XC_API void WINAPI XWnd_EnableMinButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE); //启用最小化按钮
XC_API void WINAPI XWnd_EnableMaxButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE); //启用最大化按钮
XC_API void WINAPI XWnd_EnableCloseButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE);  //启用关闭按钮

XC_API void WINAPI XWnd_EnableRound(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE); //圆角功能的启用与关闭

//遍历顶级元素
XC_API int  WINAPI XWnd_GetChildEleCount(HWINDOW hWindow);
XC_API int  WINAPI XWnd_GetChildEleCountNC(HWINDOW hWindow);
XC_API HELE WINAPI XWnd_GetChildEleByIndex(HWINDOW hWindow, int index);
XC_API HELE WINAPI XWnd_GetChildEleByIndexNC(HWINDOW hWindow, int index);

//透明窗口
XC_API void WINAPI XWnd_SetTransparentFlag(HWINDOW hWindow, int flag);  //设置透明窗口
XC_API void WINAPI XWnd_SetTransparentAlpha(HWINDOW hWindow, BYTE alpha); //设置窗口透明度
XC_API void WINAPI XWnd_SetTransparentColor(HWINDOW hWindow, COLORREF color); //设置窗口透明色

//贴图:
XC_API void WINAPI XWnd_SetImage(HWINDOW hWindow, HIMAGE hImage = NULL);    //客户区图片
XC_API void WINAPI XWnd_SetImageNC(HWINDOW hWindow, HIMAGE hImage = NULL);  //非客户区窗口图片
XC_API void WINAPI XWnd_SetImageCaption(HWINDOW hWindow, HIMAGE hImage = NULL);   //标题栏图片
XC_API void WINAPI XWnd_SetImageBorderLeft(HWINDOW hWindow, HIMAGE hImage = NULL);    //边框图片
XC_API void WINAPI XWnd_SetImageBorderRight(HWINDOW hWindow, HIMAGE hImage = NULL);    //边框图片
XC_API void WINAPI XWnd_SetImageBorderBottom(HWINDOW hWindow, HIMAGE hImage = NULL);    //边框图片

XC_API void WINAPI XWnd_SetBkColor(HWINDOW hWindow, COLORREF color); //设置背景颜色

XC_API void WINAPI XWnd_EnableBorderStrokeInner(HWINDOW hWindow, BOOL bStroke); //启用绘制描边 内
XC_API void WINAPI XWnd_EnableBorderStrokeOuter(HWINDOW hWindow, BOOL bStroke); //启用绘制描边 外

XC_API void WINAPI XWnd_SetBorderStrokeInnerColor(HWINDOW hWindow, COLORREF color1, COLORREF color2); //设置描边颜色 内
XC_API void WINAPI XWnd_SetBorderStrokeOuterColor(HWINDOW hWindow, COLORREF color1, COLORREF color2); //设置描边颜色 外

XC_API void WINAPI XWnd_CloseWindow(HWINDOW hWindow);  //关闭窗口

//插入符:
XC_API void WINAPI XWnd_CreateCaret(HWINDOW hWindow, HELE hEle, int width, int height);//创建插入符
XC_API void WINAPI XWnd_SetCaretSize(HWINDOW hWindow, int width, int height); //设置插入符大小
XC_API void WINAPI XWnd_SetCaretPos(HWINDOW hWindow, int x, int y); //设置插入符位置
XC_API void WINAPI XWnd_SetCaretPosEx(HWINDOW hWindow, int x, int y, int width, int height); //设置插入符位置
XC_API void WINAPI XWnd_SetCaretColor(HWINDOW hWindow, COLORREF color); //设置插入符颜色
XC_API void WINAPI XWnd_ShowCaret(HWINDOW hWindow, BOOL bShow);  //显示插入符
XC_API void WINAPI XWnd_DestroyCaret(HWINDOW hWindow);    //销毁插入符


void Wnd_DrawCaret(HWINDOW hWindow); //处理绘制插入符到窗口DC
void Wnd_DrawCaretMenDC(HWINDOW hWindow, HDRAW hDraw); //处理绘制插入符到内存DC
void Wnd_DrawCaretTransparent(HWINDOW hWindow);
void Wnd_DrawCaretTransparentMemDC(HWINDOW hWindow, HDRAW hDraw);//处理绘制插入符到内存DC
void Wnd_GetCaretBk(HWINDOW hWindow); //获取插入符背景保存
void Wnd_EraseCaret(HWINDOW hWindow); //擦出插入符


//坐标API:
XC_API BOOL WINAPI XWnd_GetClientRect(HWINDOW hWindow, out_ RECT *pRect); //获取客户区坐标(左上角0,0)
XC_API void WINAPI XWnd_GetNCClientRect(HWINDOW hWindow, out_ RECT *pRect); //非客户区坐标,整个窗口坐标(左上角0,0)
XC_API int WINAPI XWnd_GetClientLeft(HWINDOW hWindow); //客户区左间距
XC_API int WINAPI XWnd_GetClientTop(HWINDOW hWindow);  //客户区上间距
XC_API int WINAPI XWnd_GetClientRight(HWINDOW hWindow); //客户区右间距
XC_API int WINAPI XWnd_GetClientBottom(HWINDOW hWindow); //客户区下间距
XC_API int WINAPI XWnd_GetCaptionHeight(HWINDOW hWindow); //获取标题栏高度

XC_API void WINAPI XWnd_SetBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom); //设置窗口边框大小
XC_API void WINAPI XWnd_SetCaptionHeight(HWINDOW hWindow, int captionHeight); //设置标题栏高度

XC_API void WINAPI XWnd_WindowToClientRect(HWINDOW hWindow, in_out_ RECT *pRect); //窗口非客户区坐标转换到客户区坐标
XC_API void WINAPI XWnd_WindowToClientPt(HWINDOW hWindow, in_out_ POINT *pPt); //窗口非客户区点转换到客户区坐标点

XC_API void WINAPI XWnd_SetUserData(HWINDOW hWindow, int data);
XC_API int  WINAPI XWnd_GetUserData(HWINDOW hWindow);

//封装API:
XC_API BOOL WINAPI XWnd_ShowWindow(HWINDOW hWindow, int nCmdShow);
XC_API BOOL WINAPI XWnd_SetWindowPos(HWINDOW hWindow, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);
XC_API BOOL WINAPI XWnd_SetWindowRect(HWINDOW hWindow, in_ RECT *pRect);
XC_API BOOL WINAPI XWnd_SetWindowSize(HWINDOW hWindow, int width, int height);

XC_API BOOL WINAPI XWnd_GetWindowRect(HWINDOW hWindow, out_ RECT *pRect);

XC_API BOOL WINAPI XWnd_IsWindowVisible(HWINDOW hWindow);

//私有方法:
BOOL Wnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle, int exType);
void Wnd_AdjustCaption(HWINDOW hWindow, int cx);    //调整标题栏按钮 cx:窗口宽度,包含非客户区

BOOL Wnd_KeyDown(HWINDOW hWindow, int key); //元素焦点切换方向
BOOL Wnd_HandleFocusUp(HWINDOW hWindow);   //焦点上切换
BOOL Wnd_HandleFocusDown(HWINDOW hWindow); //焦点下切换
int  Wnd_GetWindowCount();//获取窗口数量
HELE Wnd_GetChildEle(HELE hEle, int eleID);

void Wnd_RedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect); //重回元素指定区域
BOOL Wnd_ReDrawEle_Overlapping(HWINDOW hWindow, HELE hEle, RECT *pRect); //检查元素重叠


//绘制窗口
void Wnd_DrawWindowHandle(HWINDOW hWindow, RECT *pRect);
void Wnd_DrawWindowHandle2(HWINDOW hWindow, windowMsg_Header_ *pHeader, RECT *pRect, HDC hdc);

void Wnd_DrawWindow_Optimization(HWINDOW hWindow, RECT *pRect);

void Wnd_DrawWindow_NCClient(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawWindow_Client(HWINDOW hWindow, HDRAW hDraw, windowMsg_Header_ *pHeader);//绘制客户区
void Wnd_DrawWindow_Shadow(HWINDOW hWindow, HDC hdc); //窗口阴影
void Wnd_DrawWindow_Caret(HWINDOW hWindow, HDRAW hDraw); //处理插入符

//重绘元素
void Wnd_PaintEle(HWINDOW hWindow, HELE hEle, RECT *pRect);
void Wnd_PaintEle2(HWINDOW hWindow, HELE hEle, HDC hdc, RECT *pRect);

ele_* Wnd_PaintEle_IsDrawEle(HWINDOW hWindow, HELE hEle); //检查是否直接重绘元素
void Wnd_PaintEle_Shadow(HWINDOW hWindow, HDC hdc); //窗口阴影
void Wnd_PaintEle_Caret(HWINDOW hWindow, HDRAW hDraw); //处理插入符
HDC  Wnd_GetBkDC(HWINDOW hWindow);  //获取窗口背景DC

////////////////////////////////////////////////////////////////
void Wnd_PaintEle_Optimization(HWINDOW hWindow, HELE hEle, RECT *pRect); //优化绘制
void Wnd_PaintEle_Optimization1(HWINDOW hWindow, HELE hEle, RECT *pRect);//先前为空
void Wnd_PaintEle_Optimization2(HWINDOW hWindow, HELE hEle, RECT *pRect);//同一个元素
void Wnd_PaintEle_Optimization3(HWINDOW hWindow, HELE hEle, RECT *pRect);//先前为重绘指定区域
void Wnd_PaintEle_Optimization4(HWINDOW hWindow, HELE hEle, RECT *pRect);//先前为重绘窗口


//////////////////////////////////////////////////////////////

void Wnd_DrawCaption(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawCaptionImageNC(HWINDOW hWindow, HDRAW hDraw); //当非客户区贴图时
void Wnd_DrawBorderLeft(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawBorderRight(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawBorderBottom(HWINDOW hWindow, HDRAW hDraw);


BOOL Wnd_ConvPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvClose(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvDestroy(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCDestroy(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvLButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvLButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvRButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvRButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvExitSizeMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseLeave(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvSize(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvTimer(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //定时器
BOOL Wnd_ConvTimer2(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //定时器

BOOL Wnd_ConvSetFocus(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvKillFocus(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvCaptureChanged(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseWheel(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Wnd_ConvMouseClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseDBClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvRedrawEle(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMenuSelect(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMenuExit(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvSetFont(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Wnd_ConvOther(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//非客户区
BOOL Wnd_ConvNCPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCEndPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCMouseMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCLButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCLButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCRButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCRButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCMouseClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCMouseDBClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//回调函数
BOOL CALLBACK Wnd_WindowProc(HWINDOW hWindow, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Wnd_OnDrawT(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Wnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK Wnd_OnRedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect);
BOOL CALLBACK Wnd_OnDestroy(HWINDOW hWindow);
BOOL CALLBACK Wnd_OnNCDestroy(HWINDOW hWindow);
BOOL CALLBACK Wnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnRButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnRButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnMouseLeave(HWINDOW hWindow);
BOOL CALLBACK Wnd_OnSize(HWINDOW hWindow, UINT type, SIZE *pSize);//ON SIZE 窗口大小改变
BOOL CALLBACK Wnd_OnTimer(HWINDOW hWindow, UINT_PTR nIDEvent, UINT uElapse);
BOOL CALLBACK Wnd_OnMouseClick(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK Wnd_OnMouseDBClick(HWINDOW hWindow, POINT *pPt);  //OnMouseDBClick
BOOL CALLBACK Wnd_OnSetFocus(HWINDOW hWindow);  //窗口获得焦点
BOOL CALLBACK Wnd_OnKillFocus(HWINDOW hWindow); //窗口失去焦点
BOOL CALLBACK Wnd_OnKeyDown(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);	//WM_KEDOWN
BOOL CALLBACK Wnd_OnChar(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Wnd_OnCaptureChanged(HWINDOW hWindow, HWND hWnd);
BOOL CALLBACK Wnd_OnMouseWheel(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_MOUSEWHEEL 滚轮消息
BOOL CALLBACK Wnd_OnTimerEx(HWINDOW hWindow, UINT timerID, int userData); //定时器消息


BOOL CALLBACK Wnd_OnRedraw(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //自定义消息,为了重绘延迟
BOOL CALLBACK Wnd_OnMinMaxInfo(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //WM_GETMINMAXINFO 控制窗口大小

//窗口非客户区
BOOL Wnd_NCWindowProc(HWINDOW hWindow, UINT NCmessage, WPARAM wParam, LPARAM lParam);  //非客户区消息调度

BOOL CALLBACK Wnd_OnNCDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK Wnd_OnNCMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnNCLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnNCLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);

BOOL CALLBACK Wnd_OnNCRButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnNCRButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);

BOOL CALLBACK Wnd_OnNCMouseClick(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK Wnd_OnNCMouseDBClick(HWINDOW hWindow, POINT *pPt);


/////标题栏按钮////////////////////
BOOL CALLBACK Wnd_OnBtnCloseDraw(HELE hELe, HDRAW hDraw);
BOOL CALLBACK Wnd_OnBtnMaximizeDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Wnd_OnBtnMinimizeDraw(HELE hEle, HDRAW hDraw);

//标题栏按钮事件
BOOL CALLBACK Wnd_OnEventBtnCloseClick(HELE hEle, HELE hButton); //关闭按钮
BOOL CALLBACK Wnd_OnEventBtnMaximizeClick(HELE hEle, HELE hButton); //最大化按钮
BOOL CALLBACK Wnd_OnEventBtnMinimizeClick(HELE hEle, HELE hButton); //最小化按钮
