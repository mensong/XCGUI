/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//接口类型
#define  XC_COMBOBOXWINDOW        10   //comboBoxWindow_        组合框弹出下拉列表窗口
#define  XC_POPUPMENUWINDOW       11   //popupMenuWindow_       弹出菜单主窗口
#define  XC_POPUPMENUCHILDWINDOW  12   //popupMenuChildWindow_  弹出菜单子窗口
#define  XC_MSGBOXWINDOW          13   //弹出消息框
#define  XC_DATETIMEWINDOW        14   //时间元素,弹出日历选择窗口



//定时器
#define  IDT_CLICK             30002   //处理鼠标点击消息
#define  IDT_HSCROLL_UP        30003   //滚动按钮定时器  上滚动
#define  IDT_HSCROLL_DOWN      30004   //滚动按钮定时器  下滚动
#define  IDT_CARET             30005   //插入符
#define  IDT_LIST_DRAG_RECT    30030   //列表元素拖动选择矩形
#define  IDT_HSCROLLDELAY      30009   //滚动事件延时
#define  IDT_VSCROLLDELAY      30010   //滚动事件延时
#define  IDT_MENU              30011   //处理菜单
#define  IDT_MENU2             30012   //子菜单
#define  IDT_TOOLTIPS          30013   //工具提示
#define  IDT_TOOLTIPS_TIMEOUT  30014   //工具提示超时关闭
#define  IDT_LISTVIEW_DRAG_RECT    30030   //列表视图元素拖动选择矩形

#define  XC_WIND_SHADOW_SIZE  7  //阴影窗口边框大小

//窗口消息-包含系统非客户区消息
#define  XWM_EVENT_ALL        WM_APP+1000 //事件投递 -------不公开-------不需要注册

//wParam:left-top坐标组合; lParam:right-bottom坐标组合; 如果这2个参数为空,那么重绘整个窗口
#define  XWM_REDRAW            WM_APP+1007  //窗口重绘延时 ----不公开-----内部自定义消息


//注册窗口消息函数类型-包含系统非客户区消息
typedef BOOL(CALLBACK *pFunWndOther)(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //其他类型消息
typedef BOOL(CALLBACK *pFunWndMouseClick)(HWINDOW hWindow, POINT *pPt);    //鼠标单击
typedef BOOL(CALLBACK *pFunWndMouseDBClick)(HWINDOW hWindow, POINT *pPt);  //鼠标双击
typedef BOOL(CALLBACK *pFunWndRedrawEle)(HWINDOW hWindow, HELE hEle, RECT *pRect);
typedef BOOL(CALLBACK *pFunWndMenuSelect)(HWINDOW hWindow, int id);  //菜单选择
typedef BOOL(CALLBACK *pFunWndMenuExit)(HWINDOW hWindow); //菜单退出
typedef BOOL(CALLBACK *pFunWndSetFont)(HWINDOW hWindow); //窗口字体改变XWM_SETFONT

typedef BOOL(CALLBACK *pFunWndDrawWindow)(HWINDOW hWindow, HDRAW hDraw);  //WM_PAINT
typedef BOOL(CALLBACK *pFunWndClose)(HWINDOW hWindow);    //WM_CLOSE
typedef BOOL(CALLBACK *pFunWndDestroy)(HWINDOW hWindow);  //WM_DESTROY
typedef BOOL(CALLBACK *pFunWndNCDestroy)(HWINDOW hWindow);  //WM_NCDESTROY
typedef BOOL(CALLBACK *pFunWndMouseMove)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_MOUSEMOVE
typedef BOOL(CALLBACK *pFunWndLButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_LBUTTONDOWN
typedef BOOL(CALLBACK *pFunWndLButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt);  //WM_LBUTTONUP
typedef BOOL(CALLBACK *pFunWndRButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_RBUTTONDOWN
typedef BOOL(CALLBACK *pFunWndRButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_RBUTTONUP
typedef BOOL(CALLBACK *pFunWndMouseWheel)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_MOUSEWHEEL 滚轮消息
typedef BOOL(CALLBACK *pFunWndExitSizeMove)(HWINDOW hWindow);//WM_EXITSIZEMOVE
typedef BOOL(CALLBACK *pFunWndMouseLeave)(HWINDOW hWindow); //WM_MOUSELEAVE
typedef BOOL(CALLBACK *pFunWndSize)(HWINDOW hWindow, UINT flags, SIZE *pSize); //WM_SIZE
typedef BOOL(CALLBACK *pFunWndTimer)(HWINDOW hWindow, UINT timerID, UINT uElapse); //定时器消息 WM_TIMER
typedef BOOL(CALLBACK *pFunWndTimerEx)(HWINDOW hWindow, UINT timerID, int userData); //定时器消息 XWM_TIMER

typedef BOOL(CALLBACK *pFunWndSetFocus)(HWINDOW hWindow);    //窗口获得焦点 WM_SETFOCUS
typedef BOOL(CALLBACK *pFunWndKillFocus)(HWINDOW hWindow);   //窗口失去焦点 WM_KILLFOCUS
typedef BOOL(CALLBACK *pFunWndKeyDown)(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //WM_KEYDOWN
typedef BOOL(CALLBACK *pFunWndCaptureChanged)(HWINDOW hWindow, HWND hWnd); //WM_CAPTURECHANGED  hWnd:获得鼠标捕获的窗口句柄


//窗口非客户区-逻辑上的非客户区
typedef BOOL(CALLBACK *pFunWndNCDrawWindow)(HWINDOW hWindow, HDRAW hDraw); //非客户区绘制
typedef BOOL(CALLBACK *pFunWndNCEndDrawWindow)(HWINDOW hWindow, HDRAW hDraw); //XWM_NCENDPAINT
typedef BOOL(CALLBACK *pFunWndNCMouseMove)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCLButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCLButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCRButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCRButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCMouseClick)(HWINDOW hWindow, POINT *pPt);  //鼠标单击
typedef BOOL(CALLBACK *pFunWndNCMouseDBClick)(HWINDOW hWindow, POINT *pPt);  //鼠标双击


//注册元素消息处理函数
typedef BOOL(CALLBACK *pFunEleDraw)(HELE hEle, HDRAW hDraw);
typedef BOOL(CALLBACK *pFunEleMouseClick)(HELE hEle, POINT *pPt); //鼠标单击
typedef BOOL(CALLBACK *pFunEleMouseDBClick)(HELE hEle, POINT *pPt);//鼠标双击
typedef BOOL(CALLBACK *pFunEleMouseMove)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleLButtonDown)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleLButtonUp)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleRButtonDown)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleRButtonUp)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleTimerEx)(HELE hEle, UINT timerID, int userData);


//元素事件处理函数
typedef BOOL(CALLBACK *pFunEventBtnClick)(HELE hEle, HELE hEventEle); //按钮事件
typedef BOOL(CALLBACK *pFunEventMouseStay)(HELE hEle, HELE hEventEle); //鼠标停留
typedef BOOL(CALLBACK *pFunEventMouseLeave)(HELE hEle, HELE hEventEle); //鼠标离开
typedef BOOL(CALLBACK *pFunEventSetFocus)(HELE hEle, HELE hEventEle); //获得焦点
typedef BOOL(CALLBACK *pFunEventKillFocus)(HELE hEle, HELE hEventEle); //失去焦点
typedef BOOL(CALLBACK *pFunEventKeyDown)(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
typedef BOOL(CALLBACK *pFunEventHScroll)(HELE hEle, HELE hEventEle, int pos); //水平滚动
typedef BOOL(CALLBACK *pFunEventVScroll)(HELE hEle, HELE hEventEle, int pos); //垂直滚动
typedef BOOL(CALLBACK *pFunEventHScrollView)(HELE hEle, HELE hEventEle, int pos); //水平滚动
typedef BOOL(CALLBACK *pFunEventVScrollView)(HELE hEle, HELE hEventEle, int pos); //垂直滚动
typedef BOOL(CALLBACK *pFunEventChar)(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
typedef BOOL(CALLBACK *pFunEventSetCapture)(HELE hEle, HELE hEventEle);  //设置鼠标捕获
typedef BOOL(CALLBACK *pFunEventKillCapture)(HELE hEle, HELE hEventEle); //失去鼠标捕获
typedef BOOL(CALLBACK *pFunEventMouseWheel)(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt); //滚轮事件
typedef BOOL(CALLBACK *pFunEventMenuSelect)(HELE hEle, HELE hEventEle, int id); //菜单选择事件
typedef BOOL(CALLBACK *pFunEventMenuExit)(HELE hEle, HELE hEventEle);   //菜单退出事件
typedef BOOL(CALLBACK *pFunEventSize)(HELE hEle, HELE hEventEle);   //元素大小位置改变
typedef BOOL(CALLBACK *pFunEventSetFont)(HELE hEle, HELE hEventEle); //元素字体改变
typedef BOOL(CALLBACK *pFunEventShow)(HELE hEle, HELE hEventEle, BOOL bShow); //元素显示或隐藏事件


typedef void (CALLBACK *pFunEventDestroy)(HELE hEle);  //元素销毁 Destroy

typedef BOOL(CALLBACK *pFunEventListSelect)(HELE hEle, HELE hEventEle, int index); //列表项选择
typedef BOOL(CALLBACK *pFunEventListHeaderClick)(HELE hEle, HELE hEventEle, int index);  //列表头项点击
typedef BOOL(CALLBACK *pFunEventListHeaderChange)(HELE hEle, HELE hEventEle, int index, int width); //列表头宽度改变

typedef BOOL(CALLBACK *pFunEventTreeSelect)(HELE hEle, HELE hEventEle, int id);      //树列表选择
typedef BOOL(CALLBACK *pFunEventTreeExpand)(HELE hEle, HELE hEventEle, int id, BOOL bExpand); //树项展开或收缩

typedef BOOL(CALLBACK *pFunEventComboBoxSelect)(HELE hEle, HELE hEventEle, int index); //下拉组合框选择事件
typedef BOOL(CALLBACK *pFunEventComboBoxPopupList)(HELE hEle, HELE hEventEle, HWINDOW hWindow, HELE hListBox); //XE_COMBOBOX_POPUP_LIST
typedef BOOL(CALLBACK *pFunEventComboBoxExitList)(HELE hEle, HELE hEventEle); //XE_COMBOBOX_EXIT_LIST

typedef BOOL(CALLBACK *pFunEventPPageSelect)(HELE hEle, HELE hEventEle, int index);    //属性页标签选择
typedef BOOL(CALLBACK *pFunEventSliderChange)(HELE hEle, HELE hEventEle, int pos); //滑动条位置改变
typedef BOOL(CALLBACK *pFunEventMonthChange)(HELE hEle, HELE hEventEle, BOOL bChange, BOOL bDownDayNum); //月历元素,日期改变事件,

typedef BOOL(CALLBACK *pFunEventDateTimeChange)(HELE hEle, HELE hEventEle); //日期元素改变
typedef BOOL(CALLBACK *pFunEventDateTimePopupMonthCal)(HELE hEle, HELE hEventEle);
typedef BOOL(CALLBACK *pFunEventDateTimeExitMonthCal)(HELE hEle, HELE hEventEle);

typedef BOOL(CALLBACK *pFunEventListBoxSelect)(HELE hEle, HELE hEventEle, int index);  //XE_LISTBOX_SELECT
typedef BOOL(CALLBACK *pFunEventPGridSelChange)(HELE hEle, HELE hEventEle, int prevID, int id); //XE_PGRID_SELCHANGE
typedef BOOL(CALLBACK *pFunEventPGridValueChange)(HELE hEle, HELE hEventEle, int id); //XE_PGRID_VALUECHANGE

typedef BOOL(CALLBACK *pFunEventListViewSelect)(HELE hEle, HELE hEventEle, int groupIndex, int itemIndex); //列表视元素,项选择事件
typedef BOOL(CALLBACK *pFunEventListViewExpand)(HELE hEle, HELE hEventEle, int GroupIndex, BOOL bExpand); //列表视元素,组展开收缩事件

typedef BOOL(CALLBACK *pFunEventListViewDragInsert)(HELE hEle, HELE hEventEle, listView_dragInsert_ *pInfo);//列表视图元素,用户拖动项插入事件

typedef BOOL(CALLBACK *pFunEventPaneLock)(HELE hEle, HELE hEventEle);
typedef BOOL(CALLBACK *pFunEventPaneDock)(HELE hEle, HELE hEventEle);
typedef BOOL(CALLBACK *pFunEventPaneFloat)(HELE hEle, HELE hEventEle);

typedef BOOL(CALLBACK *pFunEventEditChange)(HELE hEle, HELE hEventEle); //XE_EDIT_CHANGE

typedef BOOL(CALLBACK *pFunEventComboBoxSelecting)(HELE hEle, HELE hEventEle, int index, BOOL *pBOOL);
typedef BOOL(CALLBACK *pFunEventListBoxSelecting)(HELE hEle, HELE hEventEle, int index, BOOL *pBOOL);
typedef BOOL(CALLBACK *pFunEventTreeSelecting)(HELE hEle, HELE hEventEle, int id, BOOL *pBOOL);



//同一个消息有多个处理函数,先处理最后注册的消息,最后处理第一个注册的函数.

#define  BUTTON(hEle)      ((button_*)hEle)      //((button_*)((ele_*)hEle)->pExtensionEle)
#define  CHECK(hEle)       ((check_*)hEle)       //((check_*)((button_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  RADIO(hEle)       ((radio_*)hEle)       //((radio_*)((button_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  SCROLLBAR(hEle)   ((scrollBar_*)hEle)   // ((scrollBar_*)((ele_*)hEle)->pExtensionEle)
#define  SCROLLVIEW(hEle)  ((scrollView_*)hEle)  // ((scrollView_*)((ele_*)hEle)->pExtensionEle)
#define  EDIT(hEle)        ((edit_*)hEle)        // ((edit_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  LIST(hEle)        ((list_*)hEle)        // ((list_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  TREE(hEle)        ((tree_*)hEle)        // ((tree_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  LISTBOX(hEle)     ((listBox_*)hEle)     // ((listBox_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  COMBOBOX(hEle)    ((comboBox_*)hEle)    // ((comboBox_*)((edit_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)->pExtensionEle)
#define  PPAGE(hEle)       ((propertyPage_*)hEle)
#define  SLIDER(hEle)      ((slider_*)hEle)
#define  TOOLBAR(hEle)     ((toolBar_*)hEle)
#define  STATIC(hEle)      ((static_*)hEle)
#define  GROUPBOX(hEle)    ((groupBox_*)hEle)
#define  PICTURE(hEle)     ((picture_*)hEle)

#define  MENUBARBUTTON(hEle)   ((menuBarButon_*)hEle)
#define  MENUBAR(hEle)         ((menuBar_*)hEle)
#define  DATETIME(hEle)         ((dateTime_*)hEle)
#define  WINDOW(hWindow)                ((window_*)hWindow)
#define  POPUPMENUWINDOW(hWindow)       ((popupMenuWindow_*)hWindow)
#define  POPUPMENUCHILDWINDOW(hWindow)  ((popupMenuChildWindow_*)hWindow)
#define  COMBOBOXWINDOW(hWindow)        ((comboBoxWindow_*)hWindow)
#define  MODALWINDOW(hWindow)           ((modalWindow_*)hWindow)

struct object_type_
{
	int type;
	object_type_  *pNext;
};

struct object_
{
	int type; //资源类型   HELE, HWINDOW ,HARRAY ,HSTRING

	object_type_  *pTypeList;  //类型列表
};


//判断浮点数是否大约为0
#define EPSILON  0.00001
#define IsFlaotZero(x) (x>= -EPSILON && x<=EPSILON)
//if(X>= -EPSINON && X<=EPSINON) X=0;


//弹出错误码
#define MsgError(error)  { MessageBox(NULL,error,L"炫彩界面库-错误提示!",0); exit(0); }

//错误码,唯一,严禁重复使用,使用后加标注
#define XC_ERROR_0001   L"code:0001"   //ok
#define XC_ERROR_0002   L"code:0002"   //ok
#define XC_ERROR_0003   L"code:0003"   //ok
#define XC_ERROR_0004   L"code:0004"   //ok
#define XC_ERROR_0005   L"code:0005"   //ok
#define XC_ERROR_0006   L"code:0006"   //ok
#define XC_ERROR_0007   L"code:0007"   //ok
#define XC_ERROR_0008   L"code:0008"   //ok
#define XC_ERROR_0009   L"code:0009"   //ok
#define XC_ERROR_0010   L"code:0010"   //ok
#define XC_ERROR_0011   L"code:0011"   //ok
#define XC_ERROR_0012   L"code:0012"   //ok