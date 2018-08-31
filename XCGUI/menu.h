/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct menu_
{
	int        id;          //id
	int        parentId;    //父项ID  
	int        len;         //文本长度
	int        state;	    //状态
	RECT       rcItem;      //坐标
	HIMAGE     hImage;      //图片
	HSTRING    hString;     //文本
};

//弹出菜单数据对象
struct popupMenu_
{
	object_ object;

	HXCGUI   hMTreeData;  //数据树 multiTree_;

	int      height;       //项高
	int      leftWidth;    //左边灰色区域宽度
	int      leftText;     //菜单项文本左间隔
	//Image    *pBkImage;    //菜单背景图片
	HIMAGE   hBkImage;     //菜单背景图片
	HFONT    hFont;        //字体
	BOOL     bAutoDestroy; //是否自动销毁,在菜单退出时
	HELE     hParentEle;   //父元素
	HWINDOW  hMenuWindow;  //当前弹出菜单窗口句柄
	HELE     hMenuBar;     //菜单条句柄,特为菜单条保留数据

	//自绘
	//--------------------------------------
	pFunMenu_DrawItem  pDrawItem;
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info;//消息事件回调函数信息指针
#endif

	//绘制弹出菜单窗口背景
	pFunMenu_DrawBG  pDrawBG;
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info_drawBG;//消息事件回调函数信息指针
#endif

	//菜单项更新UI
	pFunMenu_UpdateUI   pUpdateUI;
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info_updateUI;//消息事件回调函数信息指针
#endif
};

//菜单项ID应该大于0
//删除分隔符,根据分割符的ID

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
XC_API void WINAPI XMenu_SetUserDrawItemEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘菜单项
XC_API void WINAPI XMenu_SetUserDrawBGEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘菜背景
XC_API void WINAPI XMenu_SetUserUpdateUIEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
#endif

//API:
XC_API HMENUX WINAPI XMenu_Create();
XC_API void WINAPI XMenu_AddItem(HMENUX hMenu, int id, wchar_t *pText, int parentId = XMENU_ROOT, int uFlags = 0); //添加菜单项
XC_API void WINAPI XMenu_AddItemImage(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage);

//插入菜单项到指定项前面
XC_API void WINAPI XMenu_InsertItem(HMENUX hMenu, int id, wchar_t *pText, int uFlags, int insertID);
XC_API void WINAPI XMenu_InsertItemImage(HMENUX hMenu, int id, wchar_t *pText, int uFlags, int insertID, HIMAGE hImage);

//删除项
XC_API void WINAPI XMenu_DeleteItem(HMENUX hMenu, int id);


XC_API void WINAPI XMenu_SetAutoDestroy(HMENUX hMenu, BOOL bAuto); //是否自动销毁对象,默认弹出菜单关闭后自动销毁
XC_API void WINAPI XMenu_SetItemHeight(HMENUX hMenu, int height); //设置菜单项高度
XC_API BOOL WINAPI XMenu_SetBGImage(HMENUX hMenu, HIMAGE hImage);//设置菜单背景图片
XC_API BOOL WINAPI XMenu_SetItemImage(HMENUX hMenu, int id, HIMAGE hImage); //设置项图标
XC_API BOOL WINAPI XMenu_SetItemText(HMENUX hMenu, int id, wchar_t *pText); //设置项文本
XC_API void WINAPI XMenu_SetItemFlags(HMENUX hMenu, int id, int uFlags);   //设置项属性
XC_API void WINAPI XMenu_SetItemCheck(HMENUX hMenu, int id, BOOL bCheck);

XC_API BOOL WINAPI XMenu_IsItemCheck(HMENUX hMenu, int id);

XC_API int  WINAPI XMenu_GetItemFlags(HMENUX hMenu, int id);   //获取项属性
XC_API int  WINAPI XMenu_GetItemHeight(HMENUX hMenu);  //获取菜单项高度
XC_API int  WINAPI XMenu_GetItemCount(HMENUX hMenu); //获取菜单项数量,包含子菜单项
XC_API wchar_t* WINAPI XMenu_GetItemText(HMENUX hMenu, int id); //获取菜单项文本

XC_API int  WINAPI XMenu_GetItemLeftWidth(HMENUX hMenu); //获取左侧宽度
XC_API int  WINAPI XMenu_GetItemLeftText(HMENUX hMenu);  //获取菜单项文本左间隔


//接收消息窗口或接收事件元素
//hParentEle:接收事件元素句柄,如果为NULL将发送消息到父窗口
//如果父窗口为其他程序窗口或桌面,通过设置接收消息窗口
XC_API BOOL WINAPI XMenu_Popup(HMENUX hMenu, HWND hParentWnd, int x, int y, HELE hParentEle = NULL, int uFlags = NULL); //弹出菜单
XC_API void WINAPI XMenu_Destroy(HMENUX hMenu);
XC_API void WINAPI XMenu_CloseMenu(HMENUX hMenu);

//绘菜
XC_API void WINAPI XMenu_SetUserDrawItem(HMENUX hMenu, pFunMenu_DrawItem pFunDrawItem); //设置用户自绘项
XC_API void WINAPI XMenu_SetUserDrawBG(HMENUX hMenu, pFunMenu_DrawBG pFunDrawBG); //设置用户自绘菜单背景
XC_API void WINAPI XMenu_SetUserUpdateUI(HMENUX hMenu, pFunMenu_UpdateUI pUpdateUI);

void Menu_AddItemX(HMENUX hMenu, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage); //增加菜单项

//获取当前弹出的菜单主窗口句柄
HWINDOW Menu_GetMenuHWindow(HMENUX hMenu);

//计算窗口弹出菜单窗口大小
BOOL Menu_computeWndSize(HMENUX hMenu, int parentID, SIZE &size);
void Menu_AdjustPosition(int &x, int &y, int width, int height, int uFlags);


/////////////////////////////////////////////////////
//弹出菜单窗口
struct popupMenuChildWindow_;
struct popupMenuWindow_
{
	window_ window; //继承
	//---------------------------
	popupMenu_       *pMenuData;   //菜单数据对象 HMENUX
	HXCGUI            hMTreeData;  //数据树 multiTree_;

	int               selItemID;       //当前选择的项ID, -1为空
	int               enterItemID;     //进入项ID   , -1为空 ,对比确保弹出子菜单时选择项正确
	DWORD             enterTiemr;      //鼠标进入项时间

	popupMenuChildWindow_ *pChildWnd;  //弹出子窗口指针
};



//菜单主窗口:
HWINDOW MenuWnd_CreateWindow(int x, int y, int width, int height, HWND hWndParent);


//私有方法:
BOOL MenuWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent, int exType);
void MenuWnd_UpdateUI(HWINDOW hWindow, int parentID);
BOOL MenuWnd_computeSize(HWINDOW hWindow, int &width, int &height);  //计算弹出菜单窗口大小
void MenuWnd_AdjustPosition(HWINDOW hWindow, int &x, int &y, int width, int height, int uFlags); //计算调整显示位置，以便适应显示范围
BOOL MenuWnd_CheckMouseMove(popupMenuWindow_ *pObj, POINT &pt);
void MenuWnd_DrawItem(HWINDOW hWindow, HDRAW hDraw, menu_drawItem_ *pItem);
void MenuWnd_DrawBackground(window_ *pWindow, HDRAW hDraw, HIMAGE hImage);//绘制菜单背景

void MenuWnd_OnDestroyWindow(HWND hWnd, popupMenu_ *pMenu);
void MenuWnd_OnExitMenu(HELE hParentEle, HWND hParentWnd);
BOOL MenuWnd_OnDestroyMenu(popupMenu_ *pMenu);

//回调函数
BOOL CALLBACK MenuWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK MenuWnd_OnLButtonDown(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK MenuWnd_OnLButtonUp(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK MenuWnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK MenuWnd_OnNCMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK MenuWnd_OnRButtonDown(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK MenuWnd_OnCaptureChanged(HWINDOW hWindow, HWND hWnd);
BOOL CALLBACK MenuWnd_OnWndSysKeyDown(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);

VOID CALLBACK MenuWnd_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


/////////////////////////////////////////////////////////////////
struct popupMenuChildWindow_
{
	window_ window; //继承
	//---------------------------
	popupMenuWindow_      *pMainWnd;
	popupMenuChildWindow_ *pChildWnd;   //弹出子窗口指针
	popupMenuChildWindow_ *pPreviouWnd; //上一个窗口

	DWORD             enterTiemr;       //鼠标进入项时间 , 对比确保弹出子菜单时选择项正确
	int               parentItemId;     //子窗口对应的父项菜单ID
	int               enterItemID;      //进入项ID ,  -1为空
	int               selItemID;        //当前选择的项ID, , -1为空
};
//API:
popupMenuChildWindow_* MenuChildWnd_Popup(popupMenuWindow_  *pMainWnd, window_ *pParentWnd, int parentItemId, int x, int y);

//私有方法:
BOOL MenuChildWnd_Init(HWINDOW hWindow, int x, int y, int cx, int cy, HWND hWndParent, int exType);
BOOL MenuChildWnd_computeSize(popupMenuChildWindow_ *pObj, int &width, int &height);  //计算弹出菜单窗口大小
void MenuChildWnd_AdjustPosition(popupMenuChildWindow_ *pObj, int &x, int &y, int width, int height); //计算调整显示位置，以便适应显示范围

void MenuChildWnd_OnLButtonUp(popupMenuChildWindow_ *pObj, POINT *pPt);
void MenuChildWnd_OnMouseMove(popupMenuChildWindow_ *pObj, POINT *pPt);

//回调函数:
BOOL CALLBACK MenuChildWnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);

VOID CALLBACK MenuChildWnd_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

