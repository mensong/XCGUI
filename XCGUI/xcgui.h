/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

//v1.5

//#include <docobj.h> //当DLL文件使用该头文件时,需取消注释
#include <exdispid.h>

#ifndef XCGUI_HEADER_FILE_
#define XCGUI_HEADER_FILE_

// 用户自定义消息范围     WM_USER -  0x7000
// 炫彩内部自定义消息范围 0x7001  -  0x7FFF


#define XC_API

//接口类型

/// @defgroup groupObjectType 接口句柄类型
/// @ingroup macroDefine
/// @{
//窗口:
#define  XC_WINDOW         1   ///<窗口
#define  XC_MODALWINDOW    2   ///<模态窗口
#define  XC_FRAMEWND       3   ///<框架窗口
#define  XC_FLOATWND       4   ///<浮动窗口

//元素 :
#define  XC_ELE            20  ///<元素
#define  XC_BUTTON         21  ///<按钮
#define  XC_RADIO          22  ///<单选按钮
#define  XC_CHECK          23  ///<复选按钮元素
#define  XC_EDIT           24  ///<编辑框元素
#define  XC_RICHEDIT       25  ///<富文本编辑框
#define  XC_COMBOBOX       26  ///<下拉组合框元素
#define  XC_SCROLLBAR      27  ///<滚动条元素
#define  XC_SCROLLVIEW     28  ///<滚动视图元素
#define  XC_LIST           29  ///<列表元素
#define  XC_LISTBOX        30  ///<列表框元素
#define  XC_TREE           31  ///<树元素
#define  XC_MENUBAR        32  ///<菜单条
#define  XC_PROPERTYPAGE   33  ///<属性页
#define  XC_SLIDERBAR      34  ///<滑动条
#define  XC_PROGRESSBAR    35  ///<进度条
#define  XC_TOOLBAR        36  ///<工具条
#define  XC_STATIC         37  ///<静态文本元素
#define  XC_GROUPBOX       38  ///<组框
#define  XC_PICTURE        39  ///<图片元素
#define  XC_MONTHCAL       40  ///<月历元素
#define  XC_DATETIME       41  ///<时间元素
#define  XC_PROPERTYGRID   42  ///<属性网格
#define  XC_CHOOSECOLOR    43  ///<颜色选择元素
#define  XC_OUTLOOK        44  ///<测试内容
#define  XC_TEXTLINK       45  ///<链接文本
#define  XC_TABBAR         46  ///<TabBar
#define  XC_GIF            47  ///<GIF动画
#define  XC_EDITFILE       48  ///<文件选择编辑框
#define  XC_LISTVIEW       49  ///<列表视图,大图标
#define  XC_PANE           50  ///<布局窗格
#define  XC_DRAGBAR        51  ///<布局窗格拖动分割条

#define  XC_SCROLLVIEW_VIEW     52  ///<滚动视图元素的视


#define  XC_MENUBAR_BUTTON        60  ///<菜单条上的按钮
#define  XC_TOOLBAR_BUTTON        61  ///<工具条上按钮
#define  XC_PROPERTYPAGE_LABEL    62  ///<属性页标签按钮


#define  XC_ARRAY          70  ///<数组操作
#define  XC_STRING         71  ///<字符串操作
#define  XC_IMAGELIST      72  ///<图片列表
#define  XC_MENU           73  ///<弹出菜单
#define  XC_IMAGE          74  ///<图片操作
#define  XC_HDRAW          75  ///<绘图操作
#define  XC_FONT           76  ///<炫彩字体

#define  XC_PIER           102  ///<窗格停靠码头
#define  XC_PANE_CELL      103  

///@}



//特殊按钮:
#define XC_BUTTON_MIN     201  //最小化窗口按钮
#define XC_BUTTON_MAX     202  //最大化窗口按钮
#define XC_BUTTON_CLOSE   203  //关闭窗口按钮

//#define XC_BUTTON_HSCROLLBAR_SLIDER   104  //水平滚动条,滑块按钮
//#define XC_BUTTON_VSCROLLBAR_SLIDER   105  //垂直滚动条,滑块按钮
//#define XC_BUTTON_HSCROLLBAR_LEFT     106  //水平滚动条,左滚动按钮
//#define XC_BUTTON_HSCROLLBAR_RIGHT    107  //水平滚动条,右滚动按钮
//#define XC_BUTTON_VSCROLLBAR_TOP      108  //垂直滚动条,上滚动按钮
//#define XC_BUTTON_VSCROLLBAR_BOTTOM   109  //垂直滚动条,下滚动按钮
#define XC_BUTTON_SLIDERBAR_SLIDER    210  //滑动条,滑块按钮
//#define XC_BUTTON_COMBOBOX_POP        111  //组合框下拉列表弹出按钮
//#define XC_BUTTON_PROPERTYPAGE_LEFT   112  //属性页,左滚动按钮
//#define XC_BUTTON_PROPERTYPAGE_RIGHT  113  //属性页,右滚动按钮
//#define XC_BUTTON_PROPERTYPAGE_LABEL  114  //属性页,标签按钮
//#define XC_BUTTON_DATETIME_POP        115  //日期时间元素,弹出选择卡片按钮



///输入输出///////////////////
#define in_
#define out_
#define in_out_


#ifdef _DEBUG
#define DECLARE_HANDLEX(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
#define	DECLARE_HANDLEX(name) typedef void* name
#endif


//接口句柄类型

/// @defgroup groupHandle 句柄列表
/// @ingroup macroDefine
/// @{
typedef void*  HXCGUI;    ///<资源句柄
DECLARE_HANDLEX(HWINDOW); ///<窗口资源句柄
DECLARE_HANDLEX(HELE);    ///<元素资源句柄
DECLARE_HANDLEX(HMENUX);  ///<菜单资源句柄
DECLARE_HANDLEX(HSTRING); ///<字符串资源句柄
DECLARE_HANDLEX(HDRAW);   ///<图形绘制资源句柄
DECLARE_HANDLEX(HARRAY);  ///<数组资源句柄
DECLARE_HANDLEX(HIMAGE);  ///<图片资源句柄
DECLARE_HANDLEX(HXMLRES); ///<XML资源句柄
DECLARE_HANDLEX(HARRAY_ITERATOR); ///<数组迭代器
DECLARE_HANDLEX(HFONTX);    ///<炫彩字体句柄

DECLARE_HANDLEX(HPANE_GROUP); ///<窗格组句柄
///@}


/// @defgroup groupImageDrawType 图片绘制类型
/// @ingroup macroDefine
/// @{
#define XC_IMAGE_DEFAULT  0  ///<默认
#define XC_IMAGE_STRETCH  1  ///<拉伸
#define XC_IMAGE_ADAPTIVE 2  ///<自适应
#define XC_IMAGE_TILE     3  ///<平铺

///@}

//状态--------------------------------------
/// @defgroup groupButtonState 按钮状态
/// @ingroup macroDefine
/// @{
#define  STATE_LEAVE   0   ///<离开
#define  STATE_DOWN    1   ///<按下
#define  STATE_STAY    2   ///<停留
#define  STATE_SELECT  3   ///<选择,保留

///@}


//窗口样式----------------------------

/// @defgroup groupWindowStyle 炫彩窗口样式
/// @ingroup macroDefine
/// @{
#define  XC_SY_MINIMIZE   0x00000001  ///<最小化窗口按钮
#define  XC_SY_MAXIMIZE   0x00000002  ///<最大化窗口按钮
#define  XC_SY_CLOSE      0x00000004  ///<关闭窗口按钮
#define  XC_SY_CAPTION    0x00000008  ///<标题栏
#define  XC_SY_BORDER     0x00000010  ///<边框
#define  XC_SY_ROUND      0x00000020  ///<圆角窗口
#define  XC_SY_CENTER     0x00000040  ///<窗口居中

#define  XC_SY_DRAG_BORDER 0x00000080  ///<拖动窗口边框
#define  XC_SY_DRAG_WINDOW 0x00000100  ///<拖动窗口
#define  XC_SY_DRAW_CAPTION_ICON  0x00000200 ///<绘制窗口标题栏图标
#define  XC_SY_DRAW_CAPTION_TITLE 0x00000400 ///<绘制窗口标题栏文本

///窗口默认样式 1791
#define  XC_SY_DEFAULT (XC_SY_MINIMIZE | \
	XC_SY_MAXIMIZE | \
	XC_SY_CLOSE | \
	XC_SY_CAPTION | \
	XC_SY_BORDER | \
	XC_SY_ROUND | \
	XC_SY_CENTER | \
	XC_SY_DRAG_BORDER | \
	XC_SY_DRAW_CAPTION_ICON | \
	XC_SY_DRAW_CAPTION_TITLE)

///模态窗口
#define  XC_SY_MODAL_WINDOW (XC_SY_CLOSE | \
	XC_SY_CAPTION | \
	XC_SY_BORDER | \
	XC_SY_ROUND | \
	XC_SY_DRAW_CAPTION_ICON | \
	XC_SY_DRAW_CAPTION_TITLE)

///@}

//透明窗口
/// @defgroup groupWindowTransparent 炫彩窗口透明标识
/// @ingroup macroDefine
/// @{
#define XC_WIND_TRANSPARENT_NO       0 ///<默认窗口,不透明
#define XC_WIND_TRANSPARENT_SHAPED   1 ///<透明窗口,带透明通道,异型.
#define XC_WIND_TRANSPARENT_SHADOW   2 ///<阴影窗口,带透明通道,边框阴影,窗口透明或半透明.
#define XC_WIND_TRANSPARENT_SIMPLE   4 ///<透明窗口,不带透明通道,指定半透明度,指定透明色.
#define XC_WIND_TRANSPARENT_WIN7     8 ///<WIN7玻璃窗口,需要WIN7开启特效,当前未启用.

///@}

//弹出消息框类型
/// @defgroup groupMessageBox 弹出消息框
/// @ingroup macroDefine
/// @{
#define  XMB_OK       1  ///<确定按钮
#define  XMB_CANCEL   2  ///<取消按钮

///@}

//增加元素------------------------------------------------
/// @defgroup groupAddElement 添加元素
/// @ingroup macroDefine
/// @{
#define  XC_ADDELE_END      0    ///<增加到末尾
#define  XC_ADDELE_FRIST    1    ///<增加到第一位置
#define  XC_ADDELE_BEFORE   2    ///<增加到指定元素前面
#define  XC_ADDELE_AFTER    3    ///<增加到指定元素后面
#define  XC_ADDELE_INDEX    4    ///<增加到指定位置索引

///@}

//设置元素Z序-----------------------
/// @defgroup groupSetZOrder 元素Z序
/// @ingroup macroDefine
/// @{
#define XC_ZORDER_TOP     0  ///<最上面
#define XC_ZORDER_BOTTOM  1  ///<最下面
#define XC_ZORDER_BEFORE  2  ///<指定元素在目标元素下面
#define XC_ZORDER_AFTER   3  ///<指定元素在目标元素上面
#define XC_ZORDER_INDEX   4  ///<指定索引位置

///@}

//按钮图标对齐方式
/// @defgroup groupIconAlign 按钮图标对齐方式
/// @ingroup macroDefine
/// @{
#define XC_ICON_ALIGN_LEFT     0  ///<图标在左边
#define XC_ICON_ALIGN_TOP      1  ///<图标在顶部
#define XC_ICON_ALIGN_RIGHT    2  ///<图标在右边
#define XC_ICON_ALIGN_BOTTOM   3  ///<图标在底部

///@}

//滚动条
/// @defgroup groupScrollBar 滚动条
/// @ingroup macroDefine
/// @{
#define  SY_HSCROLL     TRUE   ///<水平滚动条
#define  SY_VSCROLL     FALSE  ///<垂直滚动条

///@}

//树元素
/// @defgroup groupTree 列表树元素
/// @ingroup macroDefine
/// @{
#define  XTREE_INSERT_BEGIN  -2  ///<插入当前层开始
#define  XTREE_INSERT_LAST   -1  ///<插入当前层末尾

#define  XTREE_ROOT  0       ///<根节点

///@}

//基于二叉树的多叉树根节点ID
#define  XMTREE_ROOT   -1            //根节点ID
//弹出菜单根节点ID
#define  XMENU_ROOT    XMTREE_ROOT   //根节点ID

/// @defgroup groupMenu 弹出菜单
/// @ingroup macroDefine
/// @{

//弹出菜单项标识
///@name 弹出菜单项标识
///@{
#define  XM_SELECT      1   ///<选择
#define  XM_DISABLED    2   ///<禁用
#define  XM_CHECK       4   ///<勾选
#define  XM_POPUP       8   ///<弹出
#define  XM_SEPARATOR   16  ///<分隔栏 ID号任意,ID号被忽略

///@}

//弹出菜单方向
///@name 弹出菜单方向
///@{
#define  XM_LEFT_TOP       0   ///<左上角
#define  XM_LEFT_BOTTOM    1   ///<左下角
#define  XM_RIGHT_TOP      2   ///<右上角
#define  XM_RIGHT_BOTTOM   3   ///<右下角
#define  XM_CENTER_LEFT    4   ///<左居中
#define  XM_CENTER_TOP     5   ///<上居中
#define  XM_CENTER_RIGHT   6   ///<右居中
#define  XM_CENTER_BOTTOM  7   ///<下居中

///@}

//菜单ID--------------------------------------
///@name 菜单ID
///@{
#define  IDM_CLIP          1000000000    ///<剪切
#define  IDM_COPY          1000000001    ///<复制
#define  IDM_PASTE         1000000002    ///<粘贴
#define  IDM_DELETE        1000000003    ///<删除
#define  IDM_SELECTALL     1000000004    ///<全选
#define  IDM_DELETEALL     1000000005    ///<清空

///@}

//窗格菜单
///@name 窗格菜单
///@{
#define  IDM_LOCK          1000000006    ///<锁定
#define  IDM_DOCK          1000000007    ///<停靠
#define  IDM_FLOAT         1000000008    ///<浮动
#define  IDM_HIDE          1000000009    ///<隐藏

///@}


///@}

//属性网格元素,项类型
/// @defgroup groupPropertyGrid 属性网格元素
/// @ingroup macroDefine
/// @{

///@name 项类型
///@{
#define  PGRID_STRING       0  ///<默认,字符串类型
#define  PGRID_EDIT         1  ///<编辑框
#define  PGRID_COMBOBOX     2  ///<组合框
#define  PGRID_CHOOSECOLOR  3  ///<颜色选择元素
#define  PGRID_EDIT_FILE    4  ///<文件选择编辑框
///@}

///@}

enum align_type_
{
	align_any = 1,
	align_left,
	align_top,
	align_right,
	align_bottom,
	align_group_member, //组成员
};

//窗格状态
enum pane_state_
{
	pane_state_any = 0,
	pane_state_lock,
	pane_state_dock,
	pane_state_float,
	pane_state_hide,
};

//窗口消息
/**
@addtogroup wndMSG

<hr>
<h2>Windows 标准消息</h2>
- @ref WM_PAINT 窗口绘制消息
- @ref WM_CLOSE 窗口关闭消息.
- @ref WM_DESTROY 窗口销毁消息.
- @ref WM_NCDESTROY 窗口非客户区销毁消息.
- @ref WM_MOUSEMOVE 窗口鼠标移动消息.
- @ref WM_LBUTTONDOWN 窗口鼠标左键按下消息
- @ref WM_LBUTTONUP 窗口鼠标左键弹起消息.
- @ref WM_RBUTTONDOWN 窗口鼠标右键按下消息.
- @ref WM_RBUTTONUP 窗口鼠标右键弹起消息.
- @ref WM_MOUSEWHEEL 窗口鼠标滚轮滚动消息.
- @ref WM_EXITSIZEMOVE 窗口退出移动或调整大小模式循环改，详情参加MSDN.
- @ref WM_MOUSELEAVE 窗口鼠标离开消息.
- @ref WM_SIZE 窗口大小改变消息.
- @ref WM_TIMER 窗口定时器消息.
- @ref WM_SETFOCUS 窗口获得焦点.
- @ref WM_KILLFOCUS 窗口失去焦点.
- @ref WM_KEYDOWN 窗口键盘按键消息.
- @ref WM_CAPTURECHANGED 窗口鼠标捕获改变消息.
- @ref other 其他Windows系统消息,包含你自定义的Windows消息.

<hr>
@anchor WM_PAINT WM_PAINT 窗口绘制消息
@code   BOOL CALLBACK WndDrawWindow(HWINDOW hWindow,HDRAW hDraw); @endcode
@param  hWindow 窗口句柄.
@param  hDraw   图形绘制句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_CLOSE WM_CLOSE 窗口关闭消息.
@code   BOOL CALLBACK WndClose(HWINDOW hWindow); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_DESTROY WM_DESTROY 窗口销毁消息.
@code   BOOL CALLBACK WndDestroy(HWINDOW hWindow);  @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_NCDESTROY WM_NCDESTROY 窗口非客户区销毁消息.
@code   BOOL CALLBACK WndNCDestroy(HWINDOW hWindow); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_MOUSEMOVE WM_MOUSEMOVE 窗口鼠标移动消息.
@code   BOOL CALLBACK WndMouseMove(HWINDOW hWindow,UINT flags,POINT *pPt);  @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_MOUSEMOVE wParam参数.
@param  pPt     鼠标坐标点.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_LBUTTONDOWN WM_LBUTTONDOWN 窗口鼠标左键按下消息
@code   BOOL CALLBACK WndLButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_LBUTTONDOWN.
@param  pPt     鼠标坐标点.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_LBUTTONUP WM_LBUTTONUP 窗口鼠标左键弹起消息.
@code   BOOL CALLBACK WndLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_LBUTTONUP.
@param  pPt     鼠标坐标点.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_RBUTTONDOWN WM_RBUTTONDOWN 窗口鼠标右键按下消息.
@code   BOOL CALLBACK WndRButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_RBUTTONDOWN.
@param  pPt     鼠标坐标点.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_RBUTTONUP WM_RBUTTONUP 窗口鼠标右键弹起消息.
@code   BOOL CALLBACK WndRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_RBUTTONUP.
@param  pPt     鼠标坐标点.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_MOUSEWHEEL WM_MOUSEWHEEL 窗口鼠标滚轮滚动消息.
@code   BOOL CALLBACK WndMouseWheel(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_MOUSEWHEEL消息wParam参数.
@param  pPt     鼠标坐标点.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_EXITSIZEMOVE WM_EXITSIZEMOVE 窗口退出移动或调整大小模式循环改，详情参加MSDN.
@code   BOOL CALLBACK WndExitSizeMove(HWINDOW hWindow); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_MOUSELEAVE WM_MOUSELEAVE 窗口鼠标离开消息.
@code   BOOL CALLBACK WndMouseLeave(HWINDOW hWindow); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_SIZE WM_SIZE 窗口大小改变消息.
@code   BOOL CALLBACK WndSize(HWINDOW hWindow,UINT flags,SIZE *pSize); @endcode
@param  hWindow 窗口句柄.
@param  flags   请参见MSDN WM_SIZE消息wParam参数.
@param  pSize   窗口大小.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_TIMER WM_TIMER 窗口定时器消息.
@code   BOOL CALLBACK WndTimer(HWINDOW hWindow,UINT_PTR nIDEvent,UINT uElapse); @endcode
@param  hWindow  窗口句柄.
@param  nIDEnent 定时器标示符.
@param  uElapse  指定所经过的系统启动以来的毫秒数,这是由GetTickCount函数的返回值.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_SETFOCUS WM_SETFOCUS 窗口获得焦点.
@code   BOOL CALLBACK WndSetFocus(HWINDOW hWindow); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_KILLFOCUS WM_KILLFOCUS 窗口失去焦点.
@code   BOOL CALLBACK WndKillFocus(HWINDOW hWindow); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor WM_KEYDOWN WM_KEYDOWN 窗口键盘按键消息.
@code   BOOL CALLBACK WndKeyDown(HWINDOW hWindow,WPARAM wParam,LPARAM lParam); @endcode
@param  hWindow 窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.
@note   wParam,lParam:请参见MSDN WM_KEYDOWN.

<hr>
@anchor WM_CAPTURECHANGED WM_CAPTURECHANGED 窗口鼠标捕获改变消息.
@code   BOOL CALLBACK WndCaptureChanged(HWINDOW hWindow,HWND hWnd); @endcode
@param  hWindow 窗口句柄.
@param  hWnd    获得鼠标捕获的窗口句柄.
@return 默认返回FALSE,如果终止消息传递返回TRUE.

<hr>
@anchor other 其他Windows系统消息,包含你自定义的Windows消息.
@code   BOOL CALLBACK WndOther(HWINDOW hWindow,WPARAM wParam,LPARAM lParam); @endcode
@param  hWindow 窗口句柄.
@param  wParam  消息参数.
@param  lParam  消息参数.
@return 默认返回FALSE,如果终止消息传递返回TRUE.
@note   参数信息请参见MSDN.
@{
*/

///@brief 鼠标单击窗口
///@code  BOOL CALLBACK WndMouseClick(HWINDOW hWindow,POINT *pPt); @endcode
#define  XWM_MOUSECLICK       0x7000+1 //wParam:x坐标, lParam:y坐标

///@brief 鼠标双击窗口
///@code  BOOL CALLBACK WndMouseDBClick(HWINDOW hWindow,POINT *pPt) @endcode
///@param hWindow 窗口句柄
///@param pPt     鼠标位置
#define  XWM_MOUSEDBCLICK     0x7000+2 //wParam:x坐标, lParam:y坐标

///@brief 重绘元素
///@code BOOL CALLBACK WndRedrawEle(HWINDOW hWindow,HELE hEle,RECT *pRect);  @endcode
#define  XWM_REDRAW_ELE       0x7000+3 //重绘元素 wParam:元素句柄, lParam:*

///@brief 菜单选择
///@code  BOOL CALLBACK WndMenuSelect(HWINDOW hWindow,int id); @endcode
#define  XWM_MENUSELECT       0x7000+4 //菜单选择 wParam:菜单项ID, lParam:0

///@brief 菜单退出
///@code  BOOL CALLBACK WndMenuExit(HWINDOW hWindow); @endcode
#define  XWM_MENUEXIT         0x7000+5 //菜单退出 wParam:0, lParam:0

///@brief 窗口字体改变
///@code  BOOL CALLBACK WndSetFont(HWINDOW hWindow);  @endcode
#define  XWM_SETFONT          0x7000+6 //窗口字体改变

//炫彩定时器
///@code  BOOL CALLBACK WndTimer2(HWINDOW hWindow,int timerID, void* userData);  @endcode
#define  XWM_TIMER            0x7000+8 //wParam:, lParam:


#define  XWM_DRAW_T           0x7000+9  //窗口绘制,内部使用, wParam:0, lParam:0


///@}



//窗口非客户区消息-逻辑上的非客户区
/// @addtogroup wndNCMSG
/// 窗口非客户区消息-逻辑上的非客户区
/// @{

/// @brief 窗口非客户区绘制消息
/// @code  BOOL CALLBACK WndNCDrawWindow(HWINDOW hWindow,HDRAW hDraw); @endcode
/// @param hWindow 窗口句柄
/// @param hDraw   图形绘制句柄.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCPAINT         0  //wParam:HDC lParam:0

/// @brief 窗口绘制完成消息,在显示之前
/// @code  BOOL CALLBACK WndNCEndDrawWindow(HWINDOW hWindow,HDRAW hDraw); @endcode
/// @param hWindow 窗口句柄
/// @param hDraw   图形绘制句柄.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCENDPAINT      1  //wParam:HDC lParam:0       窗口绘制完成后调用,便于特效合成

/// @brief 窗口非客户区鼠标移动消息.
/// @code  BOOL CALLBACK WndNCMouseMove(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param flags   请参见msdn WM_MOUSEMOVE.
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCMOUSEMOVE     2  //wParam:对应系统wParam lParam:坐标点

/// @brief 窗口非客户区鼠标左键按下消息.
/// @code  BOOL CALLBACK WndNCLButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param flags   请参见msdn WM_LBUTTONDOWN.
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCLBUTTONDOWN   3  //wParam:对应系统wParam lParam:坐标点

/// @brief 窗口非客户区鼠标左键弹起消息.
/// @code  BOOL CALLBACK WndNCLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param flags   请参见msdn MSDN WM_LBUTTONUP.
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCLBUTTONUP     4  //wParam:对应系统wParam lParam:坐标点

/// @brief 窗口非客户区鼠标右键按下消息.
/// @code  BOOL CALLBACK WndNCRButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param flags   请参见msdn MSDN WM_RBUTTONDOWN.
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCRBUTTONDOWN   5  //wParam:对应系统wParam lParam:坐标点

/// @brief 窗口非客户区鼠标右键弹起消息.
/// @code  BOOL CALLBACK WndNCRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param flags   请参见msdn MSDN WM_RBUTTONUP.
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCRBUTTONUP     6  //wParam:对应系统wParam lParam:坐标点

/// @brief 窗口非客户区鼠标左键点击消息.
/// @code  BOOL CALLBACK WndNCMouseClick(HWINDOW hWindow,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCMOUSECLICK    7  //wParam:坐标点 lParam:0    鼠标单击      非客户区

/// @brief 窗口非客户区鼠标左键双击消息.
/// @code  BOOL CALLBACK WndNCMouseDBClick(HWINDOW hWindow,POINT *pPt); @endcode
/// @param hWindow 窗口句柄
/// @param pPt     鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XWM_NCMOUSEDBCLICK  8  //wParam:坐标点 lParam:0    鼠标双击窗口  非客户区

///@}

//元素消息
/// @addtogroup eleMSG
/// @{

/// @brief 元素绘制消息.
/// @code  BOOL CALLBACK EleDraw(HELE hEle,HDRAW hDraw); @endcode
/// @param hEle 元素句柄.
/// @param hDraw 图形绘制句柄.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_PAINT          100   //wParam:hDraw,lParam:0

/// @brief 元素鼠标左键点击消息.
/// @code  BOOL CALLBACK EleMouseClick(HELE hEle,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param pPt  鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_MOUSECLICK     101   //鼠标单击  wParam:POINT坐标,lParam:0

/// @brief 元素鼠标左键双击消息.
/// @code  BOOL CALLBACK EleMouseDBClick(HELE hEle,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param pPt  鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_MOUSEDBCLICK   102   //鼠标双击  wParam:POINT坐标,lParam:0

/// @brief 元素鼠标移动消息.
/// @code  BOOL CALLBACK EleMouseMove(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param flags 请参见MSDN WM_MOUSEMOVE.
/// @param pPt   鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_MOUSEMOVE      103   //鼠标移动  wParam:标识, lParam:POINT坐标

/// @brief 元素鼠标左键按下消息.
/// @code  BOOL CALLBACK EleLButtonDown(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param flags 请参见MSDN WM_LBUTTONDOWN.
/// @param pPt   鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_LBUTTONDOWN    104   //wParam:标识, lParam:POINT坐标

/// @brief 元素鼠标左键弹起消息.
/// @code  BOOL CALLBACK EleLButtonUp(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param flags 请参见MSDN WM_LBUTTONUP.
/// @param pPt   鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_LBUTTONUP      105   //wParam:标识, lParam:POINT坐标

/// @brief 元素鼠标右键按下消息.
/// @code  BOOL CALLBACK EleRButtonDown(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param flags 请参见MSDN WM_RBUTTONDOWN.
/// @param pPt   鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_RBUTTONDOWN    106   //wParam:标识, lParam:POINT坐标

/// @brief 元素鼠标右键弹起消息.
/// @code  BOOL CALLBACK EleRButtonUp(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle 元素句柄.
/// @param flags 请参见MSDN WM_RBUTTONUP.
/// @param pPt   鼠标坐标点.
/// @return 默认返回FALSE,如果终止消息传递返回TRUE.
#define  XM_RBUTTONUP      107   //wParam:标识, lParam:POINT坐标

//炫彩定时器
// BOOL (CALLBACK *pFunEleTimerEx)(HELE hEle,UINT timerID,void* userData); //定时器消息 XWM_TIMER
#define  XM_TIMER          108


///@}

//元素事件
/// @addtogroup eleEvents
/// @{

/// @brief 元素销毁事件.
/// @code  void CALLBACK EventDestroy(HELE hEle); @endcode
/// @param hEle  元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_DESTROY        -1  //元素销毁 特殊事件

/// @brief 按钮元素点击事件.
/// @code  BOOL CALLBACK EventBtnClick(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_BNCLICK        0   //按钮点击事件,没有时间间隔 wParam:0, lParam:0

/// @brief 元素鼠标停留事件.
/// @code  BOOL CALLBACK EventMouseStay(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_MOUSESTAY      1   //鼠标停留  wParam:0,lParam:0

/// @brief 元素鼠标离开事件.
/// @code  BOOL CALLBACK EventMouseLeave(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_MOUSELEAVE     2   //鼠标离开  wParam:0,lParam:0

/// @brief 元素鼠标滚轮滚动事件.
/// @code  BOOL CALLBACK EventMouseWheel(HELE hEle,HELE hEventEle,UINT flags,POINT *pPt); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_MOUSEWHEEL     3   //鼠标滚轮  wParam:标识,lParam:POINT坐标

/// @brief 元素获得焦点事件.
/// @code  BOOL CALLBACK EventSetFocus(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_SETFOCUS       4   //获得焦点  wParam:0,lParam:0

/// @brief 元素失去焦点事件.
/// @code  BOOL CALLBACK EventKillFocus(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_KILLFOCUS      5   //失去焦点  wParam:0,lParam:0

/// @brief 元素按键事件.
/// @code  BOOL CALLBACK EventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
/// @note   wParam,lParam:请参见MSDN WM_KEYDOWN. 
#define  XE_KEYDOWN        6   //wParam和lParam参数与标准消息相同

/// @brief 通过TranslateMessage函数翻译的字符事件.
/// @code  BOOL CALLBACK EventChar(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
/// @note   wParam,lParam:请参见MSDN WM_KEYDOWN. 
#define  XE_CHAR           7   //wParam和lParam参见MSDN

/// @brief 水平滚动条元素滚动事件,滚动条触发.
/// @code  BOOL CALLBACK EventHScroll(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param pos         当前滚动点.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_HSCROLL        8   //水平滚动条滚动事件 wParam:滚动点,lParam:0 (滚动条触发)

/// @brief 垂直滚动条元素滚动事件,滚动条触发.
/// @code  BOOL CALLBACK EventVScroll(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param pos         当前滚动点.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_VSCROLL        9   //垂直滚动条滚动事件 wParam:滚动点,lParam:0 (滚动条触发)

/// @brief 滚动视图元素水平滚动事件,滚动视图触发.
/// @code  BOOL CALLBACK EventHScrollView(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param pos         当前滚动点.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_HSCROLLVIEW    10  //滚动视图 滚动事件 wParam:滚动点,lParam:0 (滚动视图触发,表明滚动视图已滚动完成)

/// @brief 滚动视图元素垂直滚动事件,滚动视图触发.
/// @code  BOOL CALLBACK EventVScrollView(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param pos         当前滚动点.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_VSCROLLVIEW    11  //滚动视图 滚动事件 wParam:滚动点,lParam:0 (滚动视图触发,表明滚动视图已滚动完成)

/// @brief 元素设置鼠标捕获事件.
/// @code  BOOL CALLBACK EventSetCapture(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_SETCAPTURE     12  //设置鼠标捕获  wParam:0,lParam:0

/// @brief 元素失去鼠标捕获事件.
/// @code  BOOL CALLBACK EventKillCapture(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_KILLCAPTURE    13  //失去鼠标捕获  wParam:0,lParam:0

/// @brief 弹出菜单项选择事件.
/// @code  BOOL CALLBACK EventMenuSelect(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          菜单项id.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_MENUSELECT     14  //菜单项选择 wParam:菜单ID,lParam:0

/// @brief 弹出菜单退出事件.
/// @code  BOOL CALLBACK EventMenuExit(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_MENUEXIT       15  //菜单退出

/// @brief 元素大小改变事件.
/// @code  BOOL CALLBACK EventSize(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_SIZE           16  //元素大小位置改变,wParam:0,lParam:0

/// @brief 元素字体改变事件.
/// @code  BOOL CALLBACK EventSetFont(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_SETFONT        17  //元素字体改变事件,wParam:0,lParam:0

/// @brief 元素显示或隐藏事件.
/// @code  BOOL CALLBACK EventShow(HELE hEle,HELE hEventEle,BOOL bShow); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param bShow       如果元素显示TRUE,隐藏FALSE.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_SHOW            18   //wParam:TRUE或FALSE, lParam:0


/// @brief 列表元素,项选择事件.
/// @code  BOOL CALLBACK EventListSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选择项索引,如果是-1没有选择项.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LIST_SELECT          50   //列表项选择, wParam:项index,如果是-1没有选择项, lParam:0

/// @brief 列表元素,列表头项点击事件.
/// @code  BOOL CALLBACK EventListHeaderClick(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index          项索引.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LIST_HEADER_CLICK    51   //列表头项点击,wParam:项index,   lParam:0

/// @brief 列表元素,列表头项宽度改变事件.
/// @code  BOOL CALLBACK EventListHeaderChange(HELE hEle,HELE hEventEle,int index,int width); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       列表头项索引.
/// @param width       项宽度.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LIST_HEADER_CHANGE   52   //列表头项宽度改变,wParam:项index, lParam:项宽度

/// @brief 树元素,项选择事件.
/// @code  BOOL CALLBACK EventTreeSelect(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          选择项id,如果是-1没有选择项.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_TREE_SELECT          53   //树项选择,  wParam:选择项id,如果是-1没有选择项, lParam:0

/// @brief 树元素,项展开或收缩事件.
/// @code  BOOL CALLBACK EventTreeExpand(HELE hEle,HELE hEventEle,int id,BOOL bExpand); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          树项id.
/// @param bExpand     TRUE展开,FALSE收缩.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_TREE_EXPAND          54   //树项展开或收缩, wParam:项id; lParam:展开TRUE,收缩FALSE

/// @brief 组合框元素,组合框弹出下拉列表项选择事件.
/// @code  BOOL CALLBACK EventComboBoxSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选中项索引,如果-1没有选中项
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_COMBOBOX_SELECT      55   //下拉组合框选择事件,wParam:选择项索引,如果-1没有选择项, lParam:0

/// @brief 组合框元素,组合框下拉列表弹出事件.
/// @code  BOOL CALLBACK EventComboBoxPopupList(HELE hEle,HELE hEventEle,HWINDOW hWindow,HELE hListBox); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param hWindow     弹出窗口句柄.
/// @param hListBox    下拉列表句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define XE_COMBOBOX_POPUP_LIST   56 //组合框下拉列表弹出事件,wParam:弹出窗口句柄, lParam:listBox句柄

/// @brief 组合框元素,组合框弹出下拉列表退出事件.
/// @code  BOOL CALLBACK EventComboBoxExitList(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define XE_COMBOBOX_EXIT_LIST   57 //组合框弹出下拉列表关闭事件,wParam:0, lParam:0

/// @brief 属性页元素,标签项选择事件.
/// @code  BOOL CALLBACK EventPPageSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选择标签索引,如果-1没有选择标签.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_PPAGE_SELECT         58   //属性页标签选择,wParam:标签索引,如果-1没有选择标签, lParam:0

/// @brief TabBar元素,标签项选择事件.
/// @code  BOOL CALLBACK EventTabBarSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选择标签索引,如果-1没有选择标签.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_TABBAR_SELECT         58   //TabBar标签选择,wParam:标签索引,如果-1没有选择标签, lParam:0


/// @brief 滑动条元素,滑块位置改变事件.
/// @code  BOOL CALLBACK EventSliderChange(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param pos         滑块当前滑动位置点.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_SLIDER_CHANGE        59   //滑动条位置改变,wParam:滑块当前滑动位置点, lParam:0

//wParam:TRUE日期发生改变; FALSE:日期未改变,与先前日期一样, 
//lParam:在月历的第一视图,通过鼠标点击日期号(1-31)选择,为TRUE; 否则在月选择视图,或年选择视图都是FALSE;
/// @brief 月历元素,日期改变事件.
/// @code  BOOL CALLBACK EventMonthChange(HELE hEle,HELE hEventEle,BOOL bChange,BOOL bDownDayNum); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param bChange     TRUE日期发生改变; FALSE日期未改变,与先前日期一样.
/// @param bDownDayNum 在月历的第一视图,通过鼠标点击日期号(1-31)选择,为TRUE; 否则在月选择视图,或年选择视图都是FALSE;
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_MONTHCAL_CHANGE      60   //月历元素,日期改变事件,

/// @brief 日期编辑框元素,日期改变事件,日期格式为:年-月-日.
/// @code  BOOL CALLBACK EventDateTimeChange(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_DATETIME_CHANGE          61   //日期元素,日期改变事件,wParam:0,lParam:0

/// @brief 日期编辑框元素,弹出日期选择窗口事件.
/// @code  BOOL CALLBACK EventDateTimePopupMonthCal(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_DATETIME_POPUP_MONTHCAL  62  //日期元素 弹出日期选择窗口事件,wParam:0,lParam:0

/// @brief 日期编辑框元素,弹出日期选择窗口退出事件.
/// @code  BOOL CALLBACK EventDateTimeExitMonthCal(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_DATETIME_EXIT_MONTHCAL   63  //日期元素 弹出日期选择窗口退出事件,wParam:0,lParam:0

/// @brief 列表框元素,项选择事件.
/// @code  BOOL CALLBACK EventListBoxSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选择项的索引,如果是-1没有选择任何项.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LISTBOX_SELECT       64   //列表框元素项选择,wParam:选择项索引,如果是-1没有选择项; lParam:0

/// @brief 属性网格元素,项选择改变事件.
/// @code  BOOL CALLBACK EventPGridSelChange(HELE hEle,HELE hEventEle,int prevID,int id); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param prevID      先前选择项id,如果是-1没有选择项.
/// @param id          当前选择项id,如果是-1没有选择项.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_PGRID_SELCHANGE      65   //属性网格 项选择改变, wParam:先前选择项id,如果是-1没有选择项; lParam:当前选择项id,如果是-1没有选择项

/// @brief 属性网格元素,项值改变事件.
/// @code  BOOL CALLBACK EventPGridValueChange(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          项ID.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_PGRID_VALUECHANGE    66   //属性网格 项值改变事件, wParam:值改变的项id; lPara:0

/// @brief 列表视图元素,项选择事件.
/// @code  BOOL CALLBACK EventListViewSelect(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          项ID.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LISTVIEW_SELECT      67 //列表视图元素,项选择事件, wParam:组索引,如果-1没有选择组, lParam:项索引，如果-1没有选择项

/// @brief 列表视图元素,组展开收缩事件
/// @code  BOOL CALLBACK EventListViewExpand(HELE hEle,HELE hEventEle,int groupIndex,BOOL bExpand); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          组ID.
/// @param bExpand     TRUE展开,FALSE收缩.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LISTVIEW_EXPAND      68 //列表视图元素,组展开收缩事件, wParam:组索引; lParam:展开TRUE,收缩FALSE

/// @brief 列表视图元素,用户拖动项插入事件
/// @code  BOOL CALLBACK EventListViewDragInsert(HELE hEle,HELE hEventEle,listView_dragInsert_ *pInfo); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param pInfo       信息结构体.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LISTVIEW_DRAG_INSERT 69  //wParam:listView_dragInsert_*; lParam:0

/// @brief 窗格锁定事件
/// @code  BOOL CALLBACK EventPaneLock(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define XE_PANE_LOACK     70   //wParam:0; lParam:0

/// @brief 窗格停靠到码头事件
/// @code  BOOL CALLBACK EventPaneDock(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_PANE_DOCK     80  //wParam:0; lParam:0

/// @brief 窗格浮动事件
/// @code  BOOL CALLBACK EventPaneFloat(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_PANE_FLOAT    81  //wParam:0; lParam:0


/// @brief 编辑框内容改变事件
/// @code  BOOL CALLBACK EventEditChange(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_EDIT_CHANGE 82  //wParam:0; lParam:0

/// @brief 下拉组合框元素,选择项正在改变.
/// @code  BOOL CALLBACK EventComboBoxSelecting(HELE hEle,HELE hEventEle,int index,BOOL *pBOOL); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选择项的索引,如果是-1没有选择任何项.
/// @param pBOOL       是否终止改变,TRUE终止.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_COMBOBOX_SELECT_ING  83  //wParam:index; lParam:pBOOL


/// @brief 列表框元素,项选择正在改变.
/// @code  BOOL CALLBACK EventListBoxSelecting(HELE hEle,HELE hEventEle,int index,BOOL *pBOOL); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param index       选择项的索引,如果是-1没有选择任何项.
/// @param pBOOL       是否终止改变,TRUE终止.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_LISTBOX_SELECT_ING       84   //列表框元素项选择,wParam:选择项索引,如果是-1没有选择项; lParam:pBOOL


/// @brief 树元素,项选择正在改变.
/// @code  BOOL CALLBACK EventTreeSelecting(HELE hEle,HELE hEventEle,int id,BOOL *pBOOL); @endcode
/// @param hEle        当前处理事件的元素句柄.
/// @param hEventEle   触发事件的元素句柄.
/// @param id          选择项id,如果是-1没有选择项.
/// @param pBOOL       是否终止改变,TRUE终止.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  XE_TREE_SELECT_ING         85   //树项选择,  wParam:选择项id,如果是-1没有选择项, lParam:pBOOL

///@}


#ifdef _DEBUG
#define XTRACE   xtrace
#define XTRACEW  xtracew
#define XERROR   XTRACE 
#define XERRORW  XTRACEW
#else
#define XTRACE
#define XTRACEW
#define XERROR 
#define XERRORW
#endif

#ifndef  GET_X_LPARAM
#define  GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#endif
#ifndef  GET_Y_LPARAM
#define  GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
#endif


///////////////////IE begin///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//IE事件:
///@defgroup IE_Event IE事件
///@details  注册IE事件,DWebBrowserEvents2接口事件,注册API: XWeb_RegEvent().
///@ingroup  msgAndEvents
///@{

/// @brief 在导航操作之前.
/// @code  BOOL CALLBACK IE_BeforeNavigate2(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl,in_ int Flags,in_ wchar_t *pTargetFrameName,in_ wchar_t *pPostData,in_ wchar_t *pHeaders,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @param hWebBrowser 浏览器控件句柄.
/// @param pDisp   请参见MSDN.
/// @param pUrl    请参见MSDN.
/// @param Flags   请参见MSDN.
/// @param pTargetFrameName 请参见MSDN.
/// @param pPostData 请参见MSDN.
/// @param pHeaders 请参见MSDN.
/// @param bCancel TRUE取消导航操作，或FALSE允许进行导航操作。
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_BEFORENAVIGATE2     DISPID_BEFORENAVIGATE2    //BeforeNavigate2

/// @brief 请求操作,客户区窗口大小转换到宿主窗口大小.
/// @code  BOOL CALLBACK IE_ClientToHostWindow(HXCGUI hWebBrowser,in_out_ long *pCx,in_out_ long *pCy); @endcode
/// @param hWebBrowser 浏览器控件句柄.
/// @param pCx 接收和指定的客户端窗口的宽度.
/// @param pCy 接收和指定的客户端窗口的高度.
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_CLIENTTOHOSTWINDOW  DISPID_CLIENTTOHOSTWINDOW //ClientToHostWindow

/// @brief 启用状态的命令更改.
/// @code BOOL CALLBACK IE_CommandStateChange(HXCGUI hWebBrowser,in_ long command,in_ VARIANT_BOOL enable); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_COMMANDSTATECHANGE  DISPID_COMMANDSTATECHANGE //CommandStateChange  

/// @brief 一个文档完全加载和初始化.
/// @code BOOL CALLBACK IE_DocumentComplete(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_DOCUMENTCOMPLETE    DISPID_DOCUMENTCOMPLETE   //DocumentComplete

/// @brief 开始导航操作.
/// @code  BOOL CALLBACK IE_DownloadBegin(HXCGUI hWebBrowser); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_DOWNLOADBEGIN       DISPID_DOWNLOADBEGIN      //DownloadBegin 

/// @brief 导航操作完成时，停止或失败.
/// @code BOOL CALLBACK IE_DownloadComplete(HXCGUI hWebBrowser); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_DOWNLOADCOMPLETE    DISPID_DOWNLOADCOMPLETE   //DownloadComplete 

/// @brief 下载文件是即将发生.
/// @code BOOL CALLBACK IE_FileDownload(HXCGUI hWebBrowser,in_ VARIANT_BOOL ActiveDocument,in_out_ VARIANT_BOOL *Cancel); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_FILEDOWNLOAD        DISPID_FILEDOWNLOAD       //FileDownload

/// @brief 导航到一个链接,一个窗口元素或一个框架元素完成.
/// @code BOOL CALLBACK IE_NavigateComplete2(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_NAVIGATECOMPLETE2   DISPID_NAVIGATECOMPLETE2 //NavigateComplete2

/// @brief 在导航过程中发生错误时触发.
/// @code BOOL CALLBACK IE_NavigateError(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl,in_ wchar_t *pTargetFrameName,in_ int statusCode,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_NAVIGATEERROR       DISPID_NAVIGATEERROR     //NavigateError

//       IE_NEWPROCESS          DISPID_NEWPROCESS        //NewProcess 找不到

/// @brief 创建一个新的窗口时触发.
/// @code BOOL CALLBACK IE_NewWindow2(HXCGUI hWebBrowser,in_out_ IDispatch **pDisp,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_NEWWINDOW2          DISPID_NEWWINDOW2        //NewWindow2

/// @brief 创建一个新窗口时触发.
/// @code BOOL (CALLBACK *pFunIE_NewWindow3)(HXCGUI hWebBrowser,in_out_ IDispatch **pDisp,in_out_ VARIANT_BOOL *bCancel,in_ DWORD dwFlags,in_ wchar_t *pUrlContext,in_ wchar_t *pUrl); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_NEWWINDOW3          DISPID_NEWWINDOW3       //NewWindow3

/// @brief IWebBrowser2::FullScreen属性被改变时触发.
/// @code BOOL CALLBACK IE_OnFullScreen(HXCGUI hWebBrowser,in_ VARIANT_BOOL bFullScreen); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONFULLSCREEN        DISPID_ONFULLSCREEN     //OnFullScreen

/// @brief IWebBrowser2::MenuBar属性被改变时触发.
/// @code BOOL CALLBACK IE_OnMenuBar(HXCGUI hWebBrowser,in_ VARIANT_BOOL bMenuBar); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONMENUBAR           DISPID_ONMENUBAR        //OnMenuBar

/// @brief Internet Explorer的应用程序退出之前触发.
/// @code BOOL CALLBACK IE_OnQuit(HXCGUI hWebBrowser); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONQUIT              DISPID_ONQUIT           //OnQuit

/// @brief IWebBrowser2::StatusBar属性被改变时触发.
/// @code BOOL CALLBACK IE_OnStatusBar(HXCGUI hWebBrowser,in_ VARIANT_BOOL bStatusBar); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONSTATUSBAR         DISPID_ONSTATUSBAR      //OnStatusBar

/// @brief IWebBrowser2::TheaterMode属性被改变时触发.
/// @code BOOL CALLBACK IE_OnTheaterMode(HXCGUI hWebBrowser,in_ VARIANT_BOOL bTheaterMode); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONTHEATERMODE       DISPID_ONTHEATERMODE     //OnTheaterMode

/// @brief IWebBrowser2::ToolBar属性被改变时触发.
/// @code BOOL CALLBACK IE_OnToolBar(HXCGUI hWebBrowser,in_ VARIANT_BOOL bToolBar); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONTOOLBAR           DISPID_ONTOOLBAR         //OnToolBar

/// @brief IWebBrowser2::Visible属性被改变时触发.
/// @code BOOL CALLBACK IE_OnVisible(HXCGUI hWebBrowser,in_ VARIANT_BOOL bVisible); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_ONVISIBLE           DISPID_ONVISIBLE         //OnVisible

/// @brief 打印模板实例化时触发.
/// @code BOOL CALLBACK IE_PrintTemplateInstantiation(HXCGUI hWebBrowser,in_ IDispatch *pDisp); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_PRINTTEMPLATEINSTANTIATION DISPID_PRINTTEMPLATEINSTANTIATION //PrintTemplateInstantiation

/// @brief 打印模板被销毁时触发.
/// @code BOOL CALLBACK IE_PrintTemplateTeardown(HXCGUI hWebBrowser,in_ IDispatch *pDisp); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_PRINTTEMPLATETEARDOWN  DISPID_PRINTTEMPLATETEARDOWN  // PrintTemplateTeardown

/// @brief 当一个受影响的私有事件,或用户导航已经受影响的远程URL时发生.
/// @code  BOOL CALLBACK IE_PrivacyImpactedStateChange(HXCGUI hWebBrowser,in_ VARIANT_BOOL bPrivacyImpacted); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_PRIVACYIMPACTEDSTATECHANGE  DISPID_PRIVACYIMPACTEDSTATECHANGE //PrivacyImpactedStateChange

/// @brief 更新对象时触发的下载操作的进度.
/// @code  BOOL CALLBACK IE_ProgressChangee(HXCGUI hWebBrowser,in_ long Progress,in_ long ProgressMax); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_PROGRESSCHANGE       DISPID_PROGRESSCHANGE   //ProgressChange

/// @brief IWebBrowser2::PutProperty对象的方法改变属性值时触发.
/// @code  BOOL CALLBACK IE_PropertyChange(HXCGUI hWebBrowser,in_ wchar_t *pProperty); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_PROPERTYCHANGE       DISPID_PROPERTYCHANGE   //PropertyChange

//       IE_REDIRECTXDOMAINBLOCKED  DISPID_REDIRECTXDOMAINBLOCKED // RedirectXDomainBlocked 找不到

/// @brief 触发表明当前网页仿冒过滤分析微软的进度和状态。.
/// @code  BOOL CALLBACK IE_SetPhishingFilterStatus(HXCGUI hWebBrowser,in_ long phishingFilterStatus); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_SETPHISHINGFILTERSTATUS DISPID_SETPHISHINGFILTERSTATUS //SetPhishingFilterStatus

/// @brief 在加密级别的变化时触发.
/// @code  BOOL CALLBACK IE_SetSecureLockIcon(HXCGUI hWebBrowser,in_ signed int SecureLockIcon); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_SETSECURELOCKICON    DISPID_SETSECURELOCKICON  //SetSecureLockIcon

/// @brief 改变对象的状态栏文本时触发.
/// @code  BOOL CALLBACK IE_StatusTextChange(HXCGUI hWebBrowser,in_ wchar_t *pText); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_STATUSTEXTCHANGE     DISPID_STATUSTEXTCHANGE    //StatusTextChange

//       IE_THIRDPARTYURLBLOCKED DISPID_THIRDPARTYURLBLOCKED //ThirdPartyUrlBlocked 找不到

/// @brief 对象的文档的标题变为可用或改变时触发.
/// @code  BOOL CALLBACK IE_TitleChange(HXCGUI hWebBrowser,in_ wchar_t *pText); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_TITLECHANGE          DISPID_TITLECHANGE        //TitleChange

//UpdatePageStatus IE没有实现

/// @brief 该对象的窗口被关闭脚本时触发.
/// @code  BOOL CALLBACK IE_WindowClosing(HXCGUI hWebBrowser,in_ VARIANT_BOOL IsChildWindow,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWCLOSING       DISPID_WINDOWCLOSING      //WindowClosing

/// @brief 当对象改变其高度的触发.
/// @code  BOOL CALLBACK IE_WindowSetHeight(HXCGUI hWebBrowser,in_ long height); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWSETHEIGHT     DISPID_WINDOWSETHEIGHT    //WindowSetHeight

/// @brief 当对象改变其左侧位置时触发.
/// @code  BOOL CALLBACK IE_WindowSetLeft(HXCGUI hWebBrowser,in_ long left); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWSETLEFT       DISPID_WINDOWSETLEFT      //WindowSetLeft

/// @brief 发生指示宿主窗口是否应该允许调整对象.
/// @code  BOOL CALLBACK IE_WindowSetResizable(HXCGUI hWebBrowser,in_ VARIANT_BOOL bResizable); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWSETRESIZABLE  DISPID_WINDOWSETRESIZABLE   //WindowSetResizable

/// @brief 当对象改变其顶部位置的触发.
/// @code  BOOL CALLBACK IE_WindowSetTop(HXCGUI hWebBrowser,in_ long top); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWSETTOP        DISPID_WINDOWSETTOP    //WindowSetTop

/// @brief 当对象改变其宽度的触发.
/// @code  BOOL CALLBACK IE_WindowSetWidth(HXCGUI hWebBrowser,in_ long width); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWSETWIDTH      DISPID_WINDOWSETWIDTH   //WindowSetWidth

/// @brief  当窗口内容的可见性状态，如浏览器窗口或选项卡，更改时触发.
/// @code   BOOL CALLBACK IE_WindowStateChanged(HXCGUI hWebBrowser,in_ DWORD dwFlags,in_ DWORD dwValidFlagsMask); @endcode
/// @return 默认返回FALSE,如果终止事件传递返回TRUE.
#define  IE_WINDOWSTATECHANGED  DISPID_WINDOWSTATECHANGED  //WindowStateChanged

///@}

//定义IE外部函数类型
typedef BOOL(CALLBACK *pFunIE_External0)(HXCGUI hWebBrowser, HSTRING hResultVal);
typedef BOOL(CALLBACK *pFunIE_External1)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1);
typedef BOOL(CALLBACK *pFunIE_External2)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2);
typedef BOOL(CALLBACK *pFunIE_External3)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3);
typedef BOOL(CALLBACK *pFunIE_External4)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4);
typedef BOOL(CALLBACK *pFunIE_External5)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5);
typedef BOOL(CALLBACK *pFunIE_External6)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5, wchar_t *pParam6);
typedef BOOL(CALLBACK *pFunIE_External7)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5, wchar_t *pParam6, wchar_t *pParam7);
typedef BOOL(CALLBACK *pFunIE_External8)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5, wchar_t *pParam6, wchar_t *pParam7, wchar_t *pParam8);


//定义IE事件回调函数类型
typedef BOOL(CALLBACK *pFunIE_BeforeNavigate2)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl, in_ int Flags, in_ wchar_t *pTargetFrameName, in_ wchar_t *pPostData, in_ wchar_t *pHeaders, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_ClientToHostWindow)(HXCGUI hWebBrowser, in_out_ long *pCx, in_out_ long *pCy);
typedef BOOL(CALLBACK *pFunIE_CommandStateChange)(HXCGUI hWebBrowser, in_ long command, in_ VARIANT_BOOL enable);
typedef BOOL(CALLBACK *pFunIE_DocumentComplete)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl);
typedef BOOL(CALLBACK *pFunIE_DownloadBegin)(HXCGUI hWebBrowser);
typedef BOOL(CALLBACK *pFunIE_DownloadComplete)(HXCGUI hWebBrowser);
typedef BOOL(CALLBACK *pFunIE_FileDownload)(HXCGUI hWebBrowser, in_ VARIANT_BOOL ActiveDocument, in_out_ VARIANT_BOOL *Cancel);
typedef BOOL(CALLBACK *pFunIE_NavigateComplete2)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl);
typedef BOOL(CALLBACK *pFunIE_NavigateError)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl, in_ wchar_t *pTargetFrameName, in_ int statusCode, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_NewWindow2)(HXCGUI hWebBrowser, in_out_ IDispatch **pDisp, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_NewWindow3)(HXCGUI hWebBrowser, in_out_ IDispatch **pDisp, in_out_ VARIANT_BOOL *bCancel, in_ DWORD dwFlags, in_ wchar_t *pUrlContext, in_ wchar_t *pUrl);
typedef BOOL(CALLBACK *pFunIE_OnFullScreen)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bFullScreen);
typedef BOOL(CALLBACK *pFunIE_OnMenuBar)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bMenuBar);
typedef BOOL(CALLBACK *pFunIE_OnQuit)(HXCGUI hWebBrowser);
typedef BOOL(CALLBACK *pFunIE_OnStatusBar)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bStatusBar);
typedef BOOL(CALLBACK *pFunIE_OnTheaterMode)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bTheaterMode);
typedef BOOL(CALLBACK *pFunIE_OnToolBar)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bToolBar);
typedef BOOL(CALLBACK *pFunIE_OnVisible)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bVisible);
typedef BOOL(CALLBACK *pFunIE_PrintTemplateInstantiation)(HXCGUI hWebBrowser, in_ IDispatch *pDisp);
typedef BOOL(CALLBACK *pFunIE_PrintTemplateTeardown)(HXCGUI hWebBrowser, in_ IDispatch *pDisp);
typedef BOOL(CALLBACK *pFunIE_PrivacyImpactedStateChange)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bPrivacyImpacted);
typedef BOOL(CALLBACK *pFunIE_ProgressChangee)(HXCGUI hWebBrowser, in_ long Progress, in_ long ProgressMax);
typedef BOOL(CALLBACK *pFunIE_PropertyChange)(HXCGUI hWebBrowser, in_ wchar_t *pProperty);
typedef BOOL(CALLBACK *pFunIE_SetPhishingFilterStatus)(HXCGUI hWebBrowser, in_ long phishingFilterStatus);
typedef BOOL(CALLBACK *pFunIE_SetSecureLockIcon)(HXCGUI hWebBrowser, in_ signed int SecureLockIcon);
typedef BOOL(CALLBACK *pFunIE_StatusTextChange)(HXCGUI hWebBrowser, in_ wchar_t *pText);
typedef BOOL(CALLBACK *pFunIE_TitleChange)(HXCGUI hWebBrowser, in_ wchar_t *pText);
typedef BOOL(CALLBACK *pFunIE_WindowClosing)(HXCGUI hWebBrowser, in_ VARIANT_BOOL IsChildWindow, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_WindowSetHeight)(HXCGUI hWebBrowser, in_ long height);
typedef BOOL(CALLBACK *pFunIE_WindowSetLeft)(HXCGUI hWebBrowser, in_ long left);
typedef BOOL(CALLBACK *pFunIE_WindowSetResizable)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bResizable);
typedef BOOL(CALLBACK *pFunIE_WindowSetTop)(HXCGUI hWebBrowser, in_ long top);
typedef BOOL(CALLBACK *pFunIE_WindowSetWidth)(HXCGUI hWebBrowser, in_ long width);
typedef BOOL(CALLBACK *pFunIE_WindowStateChanged)(HXCGUI hWebBrowser, in_ DWORD dwFlags, in_ DWORD dwValidFlagsMask);

////////////////IE end///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//窗口消息处理过程
typedef BOOL(CALLBACK *pFunWndMsgProc)(HWINDOW hWindow, UINT message, WPARAM wParam, LPARAM lParam);
//元素消息处理过程
typedef BOOL(CALLBACK *pFunEleMsgProc)(HELE hEle, UINT eleMessage, WPARAM wParam, LPARAM lParam);
//元素事件处理过程
typedef BOOL(CALLBACK *pFunEleEventProc)(HELE hEle, int type, WPARAM wParam, LPARAM lParam);
//绘制滚动视图
typedef BOOL(CALLBACK *pFunDrawScrollView)(HELE hEle, HDRAW hDraw);



//////////////////////////////////////////////////////////
//树元素自绘
///@addtogroup groupTree
///@{

///列表树元素,项自绘结构
struct tree_drewItem_
{
	HDRAW     hDraw;    ///<图形绘制句柄
	int      id;        ///<项ID
	int      imageId;   ///<图标ID
	int      state;     ///<状态
	BOOL     bExpand;   ///<是否展开结点
	wchar_t  *pText;    ///<文本内容

	RECT  rcButton; ///<按钮坐标
	RECT  rcImage;  ///<图片坐标
	RECT  rcText;   ///<文本坐标
};

///@}


///@defgroup groupList_draw 列表元素自绘
///@ingroup macroDefine
///@{

///列表元素,项自绘结构
struct list_drawItem_
{
	HDRAW hDraw;     ///<图形绘制句柄
	int   index;     ///<项索引
	int   subIndex;  ///<子项索引
	int   imageId;   ///<图标ID
	int   state;     ///<状态
	RECT  rect;      ///<项坐标
	RECT  rcCheck;   ///<复选框坐标,对subIndex索引为0的有效
	wchar_t *pText;  ///<文本内容
};

///列表元素,列表头项自绘结构
struct listHeader_drawItem_
{
	HDRAW hDraw;    ///<图形绘制句柄
	int   index;    ///<项索引
	int   imageId;  ///<图标ID
	int   state;    ///<状态 如果值为-1,那么为绘制背景
	RECT  rect;     ///<项坐标
	wchar_t *pText; ///<文本内容
};

///@}



///@defgroup groupListBox_draw 列表框元素自绘
///@ingroup macroDefine
///@{

///列表框元素,项自绘结构
struct listBox_drawItem_
{
	HDRAW hDraw;    ///<图形绘制句柄
	int   index;    ///<索引
	int   imageId;  ///<图标ID
	int   state;    ///<状态
	RECT  rcItem;   ///<项坐标
	RECT  rcCheck;  ///<复选框坐标,当复选框启用时有效
	wchar_t *pText; ///<文本内容
};
///@}


///@defgroup itemBindEle 项绑定元素信息结构
///@ingroup macroDefine
///@{

///项绑定元素信息结构.
struct itemBindEle_
{
	HELE hEle;   ///<绑定的元素,如果绑定到列表元素,那么它的父应该为列表元素.
	int left;    ///<相对于项.
	int top;     ///<相对于项.
	int width;   ///<宽度.
	int height;  ///<高度.
};

///@}

///@defgroup groupListView_draw 列表视图元素自绘
///@ingroup macroDefine
///@{

///列表视图元素,项自绘结构
struct listView_drawItem_	//绘制项
{
	HDRAW     hDraw;   ///<图形绘制句柄
	int       groupIndex; //组索引
	int       itemIndex;  //项索引
	int       imageID; ///<图片ID
	wchar_t   *pText;  ///<文本
	int       state;   ///<状态,是否选择

	HIMAGE hImage_stay;    //项停留图片
	HIMAGE hImage_select;  //项选择图标

	RECT  rcIcon; ///<图标坐标
	RECT  rcIconDraw; ///<图标实际绘制区域
	RECT  rcText; ///<文字坐标
	RECT  rect;   ///<整个区域,包含边框

	void* userData;  ///<用户数据
};

///列表视图元素,组自绘结构
struct listView_drawGroup_ //绘制组
{
	HDRAW hDraw;        ///<图形绘制句柄
	BOOL  bExpand;      ///<是否展开

	wchar_t  *pText;    ///<文本
	RECT     rcText;    ///<文本坐标
	RECT     rcButton;  ///<展开按钮坐标
	RECT     rect;      ///<组区域坐标

	void* userData;       ///<用户数据
};

///列表视图元素,用户拖动项插入
struct listView_dragInsert_
{
	int groupIndex;   ///<拖动项 - 组索引
	int itemIndex;    ///<拖动项 - 项索引

	int groupIndex_insert; ///<插入位置 - 组索引
	int itemIndex_insert;  ///<插入位置 - 项索引

	int groupIndex_new; //插入后位置 组索引
	int itemIndex_new; //插入后位置 项索引
};

///@}






///@defgroup groupMenu_draw 菜单自绘
///@ingroup macroDefine
///@{

///菜单项自绘结构
struct menu_drawItem_
{
	HWINDOW    hWindow;     ///<当前弹出菜单项的窗口句柄
	HDRAW      hDraw;       ///<图形绘制句柄
	int        id;          ///<ID
	int        state;	    ///<状态
	RECT       rcItem;      ///<坐标
	HIMAGE     hImage;      ///<图片
	wchar_t    *pText;      ///<文本
};

///菜单窗口背景自绘结构
struct menu_drawBG_
{
	HWINDOW    hWindow;       ///<当前弹出菜单项的窗口句柄
	HDRAW      hDraw;         ///<图形绘制句柄
	int        parentItemId;  ///<子菜单对应的父项菜单ID，-1没有父项
	HIMAGE     hImage;        ///<图片
};

///@}

//列表项自绘
typedef void (CALLBACK *pFunList_DrawItem)(HELE hEle, list_drawItem_ *pDrawItem);
//列表头项自绘
typedef void (CALLBACK *pFunListHeader_DrawItem)(HELE hEle, listHeader_drawItem_ *pDrawItem);

//列表框项自绘
typedef void (CALLBACK *pFunListBox_DrawItem)(HELE hEle, listBox_drawItem_ *pDrawItem);

//树项自绘
typedef void (CALLBACK *pFunTree_DrawItem)(HELE hEle, tree_drewItem_ *pDrawItem);

//列表视图项自绘
typedef void (CALLBACK *pFunListView_DrawItem)(HELE hEle, listView_drawItem_ *pDrawItem);

//列表视图组自绘
typedef void (CALLBACK *pFunListView_DrawGroup)(HELE hEle, listView_drawGroup_ *pDrawGroup);

//菜单项自绘
typedef void (CALLBACK *pFunMenu_DrawItem)(HMENUX hMenu, menu_drawItem_ *pDrawItem);

//菜单背景自绘
typedef void (CALLBACK *pFunMenu_DrawBG)(HMENUX hMenu, menu_drawBG_ *pDrawBG);

//菜单项更新UI
typedef void (CALLBACK *pFunMenu_UpdateUI)(HMENUX hMenu, int id);

//////////////////////////////////////////////////////////////////////////////////
//下面部分通常不需要改动//////////////////////////////////////////////////////////
#define XCGUI_PLUS  // C++类支持版 , C plus plus

#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
struct eventOrMsg_  //元素消息事件回调信息,C++类支持
{
	union
	{
		HELE hEle;
		HWINDOW hWindow;
		HMENUX  hMenu;
	};
	union
	{
		HELE hEventEle;
		int  xint;
	};
	WPARAM wParam;
	LPARAM lParam;
	void   *pClass_fun;  //类成员函数指针
};

//格式 xc_fun_返回类型_参数类型表...
//b:BOOL, e:HELE, w:HWINDOW, x:HXCGUI, hwnd:HWND, hdraw:HDRAW, i:int, p:void*, pt:POINT*, size:SIZE*, v:void
//pb:BOOL*;
//menu:HMENUX.
enum xcgui_fun_type //函数类型
{
	xc_fun_b_e_e,
	xc_fun_b_e_e_b,
	xc_fun_b_e_e_b_b,
	xc_fun_b_e_e_w_e,
	xc_fun_b_e_e_pb,
	xc_fun_b_e_e_i,
	xc_fun_b_e_e_i_pt,
	xc_fun_b_e_e_i_b,
	xc_fun_b_e_e_i_pb,
	xc_fun_b_e_e_i_i,
	xc_fun_b_e_i_i,
	xc_fun_b_e_i_i_i,
	xc_fun_b_e_e_listView_dragInsert,

	xc_fun_v_e, //元素销毁
	xc_fun_b_e_pt,
	xc_fun_b_e_hdraw,
	xc_fun_b_e_i_pt,
	xc_fun_b_w,
	xc_fun_b_w_e,
	xc_fun_b_w_pt,
	xc_fun_b_w_i,
	xc_fun_b_w_i_pt,
	xc_fun_b_w_i_size,
	xc_fun_b_w_i_i,
	xc_fun_b_w_hdraw,
	xc_fun_b_w_hwnd,

	xc_fun_v_e_list_item,
	xc_fun_v_e_list_header,
	xc_fun_v_e_tree,
	xc_fun_v_e_listBox,
	xc_fun_v_e_listView_item,
	xc_fun_v_e_listView_group,
	xc_fun_v_x_menu_item,
	xc_fun_v_x_menu_bg,
	xc_fun_v_x_menu_i,
};

//事件回调类型
typedef BOOL(CALLBACK *pFunClassEventMsg)(eventOrMsg_ *pEvent, xcgui_fun_type funType);

//#endif //XCGUI_PLUS


//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持

//{
//以下API内部使用
extern XC_API void* WINAPI XC_Malloc(int size);
extern XC_API void WINAPI XEle_RegisterMessageEx(HELE hEle, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
extern XC_API void WINAPI XEle_RegisterEventEx(HELE hEle, int type, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
extern XC_API void WINAPI XEle_RegisterMsgProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);    //注册元素消息处理过程
extern XC_API void WINAPI XEle_RegisterEventProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //注册事件拦截过滤函数

extern XC_API void WINAPI XWnd_RegisterMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //注册消息回调函数
extern XC_API void WINAPI XWnd_RegisterNCMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //注册非客户区消息
extern XC_API void WINAPI XWnd_RegisterMsgProcEx(HWINDOW hWindow, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);	//注册窗口消息处理过程

extern XC_API void WINAPI XSView_SetDrawScrollViewEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
extern XC_API void WINAPI XList_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘列表项
extern XC_API void WINAPI XList_SetUserDrawItemHeaderEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘列表头项
extern XC_API void WINAPI XTree_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘项
extern XC_API void WINAPI XListBox_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘列表框项
extern XC_API void WINAPI XListView_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘项
extern XC_API void WINAPI XListView_SetUserDrawGroupEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘组
extern XC_API void WINAPI XMenu_SetUserDrawItemEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘菜单项
extern XC_API void WINAPI XMenu_SetUserDrawBGEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘菜背景
extern XC_API void WINAPI XMenu_SetUserUpdateUIEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);

//}

class CXEventMsg
{
public:
	virtual void CXEventMsg__(void) {} //此函数不可删除

//注册元素事件
#define XCGUI_RegEleEvent(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_event)

//注册元素消息
#define XCGUI_RegEleMessage(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_msg)

//注册元素消息处理过程
#define XCGUI_RegEleMsgProc(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_msg_proc)

//注册元素事件处理过程
#define XCGUI_RegEleEventProc(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_event_proc)

//注册窗口消息
#define XCGUI_RegWndMessage(hWindow,type,memberFunction) \
		RegisterAll(hWindow,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),wnd_msg)

//注册窗口逻辑非客户区消息
#define XCGUI_RegWndNCMessage(hWindow,type,memberFunction) \
		RegisterAll(hWindow,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),wnd_msg_nc)

//注册窗口消息处理过程
#define XCGUI_RegWndMsgProc(hWindow,memberFunction) \
		RegisterAll(hWindow,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),wnd_msg_proc)

//注册滚动视图绘制
#define XCGUI_SView_SetDrawScrollView(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_scrollView_draw)

//注册列表项绘制
#define XCGUI_List_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_list_drawItem)

//列表头项绘制
#define XCGUI_List_SetUserDrawItemHeader(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_list_drawItemHeader)

//树项绘制
#define XCGUI_Tree_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_tree_drawItem)

//列表框项绘制
#define XCGUI_ListBox_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_listBox_drawItem)

//列表视图项绘制
#define XCGUI_ListView_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_listView_drawItem)

//列表视图组绘制
#define XCGUI_ListView_SetUserDrawGroup(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_listView_drawGroup)

//菜单项自绘
#define XCGUI_Menu_SetUserDrawItem(hMenu,memberFunction) \
	RegisterAll(hMenu,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_menu_drawItem)

//菜单背景自绘
#define XCGUI_Menu_SetUserDrawBG(hMenu,memberFunction) \
	RegisterAll(hMenu,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_menu_drawBG)

//更新菜单项
#define XCGUI_Menu_SetUserUpdateUI(hMenu,memberFunction) \
	RegisterAll(hMenu,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_menu_updateUI)

	union xcgui_functions //函数指针
	{
		void (CXEventMsg::*fun_v_v)(void);
		BOOL(CXEventMsg::*fun_b_e_e_i_i)(HELE, HELE, int, int);
		BOOL(CXEventMsg::*fun_b_e_e_i)(HELE, HELE, int);
		BOOL(CXEventMsg::*fun_b_e_e)(HELE, HELE);
		BOOL(CXEventMsg::*fun_b_e_e_pb)(HELE, HELE, BOOL*);
		BOOL(CXEventMsg::*fun_b_e_e_i_pb)(HELE, HELE, int, BOOL*);
		BOOL(CXEventMsg::*fun_b_e_e_b)(HELE, HELE, BOOL);

		BOOL(CXEventMsg::*fun_b_e_e_i_p)(HELE, HELE, int, POINT*);
		BOOL(CXEventMsg::*fun_b_e_e_i_b)(HELE, HELE, int, BOOL);
		BOOL(CXEventMsg::*fun_b_e_e_b_b)(HELE, HELE, BOOL, BOOL);
		BOOL(CXEventMsg::*fun_b_e_i_i_i)(HELE, int, int, int);
		BOOL(CXEventMsg::*fun_b_e_i_i)(HELE, int, int);
		BOOL(CXEventMsg::*fun_b_e_e_w_e)(HELE, HELE, HWINDOW, HELE);
		BOOL(CXEventMsg::*fun_b_e_e_listViewDragInsert)(HELE, HELE, listView_dragInsert_*);

		void (CXEventMsg::*fun_v_e)(HELE);

		BOOL(CXEventMsg::*fun_b_e_i_p)(HELE, int, POINT*);
		BOOL(CXEventMsg::*fun_b_e_p)(HELE, POINT*);
		BOOL(CXEventMsg::*fun_b_e_hdraw)(HELE, HDRAW);

		BOOL(CXEventMsg::*fun_b_w_hdraw)(HWINDOW, HDRAW);
		BOOL(CXEventMsg::*fun_b_w)(HWINDOW);
		BOOL(CXEventMsg::*fun_b_w_i_p)(HWINDOW, int, POINT*);
		BOOL(CXEventMsg::*fun_b_w_i_size)(HWINDOW, int, SIZE*);
		BOOL(CXEventMsg::*fun_b_w_i_i)(HWINDOW, int, int);
		BOOL(CXEventMsg::*fun_b_w_p)(HWINDOW, POINT*);
		BOOL(CXEventMsg::*fun_b_w_e)(HWINDOW, HELE);
		BOOL(CXEventMsg::*fun_b_w_hwnd)(HWINDOW, HWND);
		BOOL(CXEventMsg::*fun_b_w_i)(HWINDOW, int);

		void (CXEventMsg::*fun_v_e_list)(HELE, list_drawItem_*);
		void (CXEventMsg::*fun_v_e_listHeader)(HELE, listHeader_drawItem_*);
		void (CXEventMsg::*fun_v_e_tree)(HELE, tree_drewItem_*);
		void (CXEventMsg::*fun_v_e_listBox)(HELE, listBox_drawItem_*);
		void (CXEventMsg::*fun_v_e_listView)(HELE, listView_drawItem_*);
		void (CXEventMsg::*fun_v_e_listViewGroup)(HELE, listView_drawGroup_*);
		void (CXEventMsg::*fun_v_x_menu_drawItem)(HMENUX, menu_drawItem_*);
		void (CXEventMsg::*fun_v_x_menu_drawBG)(HMENUX, menu_drawBG_*);
		void (CXEventMsg::*fun_v_x_menu_updateUI)(HMENUX, int);
	};
	enum xcgui_reg_type //注册类型
	{
		ele_event,        //元素事件
		ele_msg,          //元素消息
		ele_msg_proc,     //元素消息处理过程
		ele_event_proc,   //元素事件处理过程
		wnd_msg,          //窗口消息
		wnd_msg_nc,       //窗口逻辑非客户区消息
		wnd_msg_proc,     //窗口消息处理过程
		//---------------
		ele_scrollView_draw,     //滚动视图自绘
		ele_list_drawItem,       //列表项自绘
		ele_list_drawItemHeader, //列表头项自绘
		ele_tree_drawItem,       //树项自绘
		ele_listBox_drawItem,    //列表框项自绘
		ele_listView_drawItem,   //列表视图项绘制
		ele_listView_drawGroup,  //列表视图组绘制
		ele_menu_drawItem,       //绘制菜单项
		ele_menu_drawBG,         //绘制菜单背景
		ele_menu_updateUI,       //菜单项更新UI
	};

	struct  xcgui_info_
	{
		CXEventMsg  *theThis;
		xcgui_functions  funs;
	};

	void RegisterAll(HXCGUI hXCGUI, int type, void (CXEventMsg::*fun)(void), int T) //注册消息事件
	{
		xcgui_info_ *pInfo = (xcgui_info_*)XC_Malloc(sizeof(xcgui_info_));
		pInfo->theThis = this;
		pInfo->funs.fun_v_v = fun;

		switch (T)
		{
		case ele_event: //注册元素事件
			XEle_RegisterEventEx((HELE)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_msg: //元素消息
			XEle_RegisterMessageEx((HELE)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_msg_proc: //元素消息处理过程
			XEle_RegisterMsgProcEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_event_proc: //元素事件处理过程
			XEle_RegisterEventProcEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case wnd_msg: //注册窗口消息
			XWnd_RegisterMessageEx((HWINDOW)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case wnd_msg_nc: //注册窗口逻辑上非客户区消息
			XWnd_RegisterNCMessageEx((HWINDOW)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case wnd_msg_proc:
			XWnd_RegisterMsgProcEx((HWINDOW)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_scrollView_draw: //滚动视图绘制
			XSView_SetDrawScrollViewEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_list_drawItem: //列表项自绘
			XList_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_list_drawItemHeader: //列表头项绘制
			XList_SetUserDrawItemHeaderEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_tree_drawItem: //树项自绘
			XTree_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_listBox_drawItem://列表框项自绘
			XListBox_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_listView_drawItem: //列表视图项自绘
			XListView_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_listView_drawGroup: //列表视图组自绘
			XListView_SetUserDrawGroupEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_menu_drawItem: //菜单项自绘
			XMenu_SetUserDrawItemEx((HMENUX)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_menu_drawBG:
			XMenu_SetUserDrawBGEx((HMENUX)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_menu_updateUI:
			XMenu_SetUserUpdateUIEx((HMENUX)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		};
	}
	static BOOL CALLBACK OnEventAndMsg(eventOrMsg_ *pEvent, xcgui_fun_type funType)//事件回调
	{
		xcgui_info_ *info = (xcgui_info_*)pEvent->pClass_fun;
		BOOL bResult = FALSE;
		switch (funType)
		{
			//////////////////////////////////////////////////
		case xc_fun_b_e_e_i_i:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_i)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_e_e_i:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam);
			break;
		case xc_fun_b_e_e:
			bResult = (info->theThis->*info->funs.fun_b_e_e)(pEvent->hEle, pEvent->hEventEle);
			break;
		case xc_fun_b_e_e_pb:
			bResult = (info->theThis->*info->funs.fun_b_e_e_pb)(pEvent->hEle, pEvent->hEventEle, (BOOL*)&pEvent->wParam);
			break;
		case xc_fun_b_e_e_i_pb:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_pb)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, (BOOL*)pEvent->lParam);
			break;
		case xc_fun_b_e_e_b:
			bResult = (info->theThis->*info->funs.fun_b_e_e_b)(pEvent->hEle, pEvent->hEventEle, (BOOL)pEvent->wParam);
			break;
		case xc_fun_b_e_e_i_pt:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_p)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, (POINT*)pEvent->lParam);
			break;
		case xc_fun_b_e_e_i_b:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_b)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, pEvent->lParam ? TRUE : FALSE);
			break;
		case xc_fun_b_e_e_b_b:
			bResult = (info->theThis->*info->funs.fun_b_e_e_b_b)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam ? TRUE : FALSE, pEvent->lParam ? TRUE : FALSE);
			break;
		case xc_fun_b_e_e_w_e:
			bResult = (info->theThis->*info->funs.fun_b_e_e_w_e)(pEvent->hEle, pEvent->hEventEle, (HWINDOW)pEvent->wParam, (HELE)pEvent->lParam);
			break;
		case xc_fun_b_e_e_listView_dragInsert:
			bResult = (info->theThis->*info->funs.fun_b_e_e_listViewDragInsert)(pEvent->hEle, pEvent->hEventEle, (listView_dragInsert_*)pEvent->wParam);
			break;
			/////////////////////////////////////////////////////////
		case xc_fun_v_e:
			(info->theThis->*info->funs.fun_v_e)(pEvent->hEle);
			break;
		case xc_fun_b_e_i_i_i:
			bResult = (info->theThis->*info->funs.fun_b_e_i_i_i)(pEvent->hEle, pEvent->xint, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_e_i_i:
			bResult = (info->theThis->*info->funs.fun_b_e_i_i)(pEvent->hEle, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_e_i_pt:
			bResult = (info->theThis->*info->funs.fun_b_e_i_p)(pEvent->hEle, pEvent->wParam, (POINT*)pEvent->lParam);
			break;
		case xc_fun_b_e_pt:
			bResult = (info->theThis->*info->funs.fun_b_e_p)(pEvent->hEle, (POINT*)pEvent->wParam);
			break;
		case xc_fun_b_e_hdraw:
			bResult = (info->theThis->*info->funs.fun_b_e_hdraw)(pEvent->hEle, (HDRAW)pEvent->wParam);
			break;
		case xc_fun_b_w_hdraw:
			bResult = (info->theThis->*info->funs.fun_b_w_hdraw)(pEvent->hWindow, (HDRAW)pEvent->wParam);
			break;
		case xc_fun_b_w:
			bResult = (info->theThis->*info->funs.fun_b_w)(pEvent->hWindow);
			break;
		case xc_fun_b_w_i_pt:
			bResult = (info->theThis->*info->funs.fun_b_w_i_p)(pEvent->hWindow, pEvent->wParam, (POINT*)pEvent->lParam);
			break;
		case xc_fun_b_w_i_size:
			bResult = (info->theThis->*info->funs.fun_b_w_i_size)(pEvent->hWindow, pEvent->wParam, (SIZE*)pEvent->lParam);
			break;
		case xc_fun_b_w_i_i:
			bResult = (info->theThis->*info->funs.fun_b_w_i_i)(pEvent->hWindow, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_w_pt:
			bResult = (info->theThis->*info->funs.fun_b_w_p)(pEvent->hWindow, (POINT*)pEvent->wParam);
			break;
		case xc_fun_b_w_e:
			bResult = (info->theThis->*info->funs.fun_b_w_e)(pEvent->hWindow, (HELE)pEvent->wParam);
			break;
		case xc_fun_b_w_hwnd:
			bResult = (info->theThis->*info->funs.fun_b_w_hwnd)(pEvent->hWindow, (HWND)pEvent->wParam);
			break;
		case xc_fun_b_w_i:
			bResult = (info->theThis->*info->funs.fun_b_w_i)(pEvent->hWindow, pEvent->wParam);
			break;
			//////////////////////////////////////////////////////
		case xc_fun_v_e_list_item:
			(info->theThis->*info->funs.fun_v_e_list)(pEvent->hEle, (list_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_list_header:
			(info->theThis->*info->funs.fun_v_e_listHeader)(pEvent->hEle, (listHeader_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_tree:
			(info->theThis->*info->funs.fun_v_e_tree)(pEvent->hEle, (tree_drewItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_listBox:
			(info->theThis->*info->funs.fun_v_e_listBox)(pEvent->hEle, (listBox_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_listView_item:
			(info->theThis->*info->funs.fun_v_e_listView)(pEvent->hEle, (listView_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_listView_group:
			(info->theThis->*info->funs.fun_v_e_listViewGroup)(pEvent->hEle, (listView_drawGroup_*)pEvent->wParam);
			break;
		case xc_fun_v_x_menu_item:
			(info->theThis->*info->funs.fun_v_x_menu_drawItem)(pEvent->hMenu, (menu_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_x_menu_bg:
			(info->theThis->*info->funs.fun_v_x_menu_drawBG)(pEvent->hMenu, (menu_drawBG_*)pEvent->wParam);
			break;
		case xc_fun_v_x_menu_i:
			(info->theThis->*info->funs.fun_v_x_menu_updateUI)(pEvent->hMenu, pEvent->wParam);
			break;
		}
		return bResult;
	}
};

#endif //XCGUI_PLUS


//这里添加导出API函数////////////////////////////////////////////////////////


#endif //XCGUI_HEADER_FILE_