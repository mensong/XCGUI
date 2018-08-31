/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct menuBarItem_
{
	int        id;          //id
	HSTRING    hText;       //内容
	int        parentId;    //父项ID
	int        uFlags;
	HSTRING    hImageName;  //图片文件名
	int        resID;       //资源ID
	HSTRING    hResType;    //资源类型

	HARRAY     hArrayItem;   //菜单项列表 menuBarItem_* //弹出项
};

//菜单条按钮
struct menuBarButon_
{
	button_ button; //继承
	//-------------------------

	HMENUX   hMenu;  //弹出菜单
};

//默认跟节点ID为XMENU_ROOT

//API: 内部的
HELE MenuBarBtn_Create(int x, int y, int cx, int cy, wchar_t *pTitle, HXCGUI hParent = NULL);
void MenuBarBtn_AddMenuItem(HELE hEle, int id, wchar_t *pText, int parentId = XMENU_ROOT, int uFlags = 0);
void MenuBarBtn_AddMenuItemImage(HELE hEle, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage); //增加菜单项

//插入菜单项
void MenuBarBtn_InsertMenuItem(HELE hEle, int id, wchar_t *pText, int uFlags, int insertID);
void MenuBarBtn_InsertMenuItemImage(HELE hEle, int id, wchar_t *pText, int uFlags, int insertID, HIMAGE hImage); //增加菜单项

//删除菜单项
void MenuBarBtn_DeleteMenuItem(HELE hEle, int id);

//私有方法:
void MenuBarBtn_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);

//注册菜单项自绘
//注册菜单背景自绘

//公有方法:
void MenuBarBtn_PopupMenu(HELE hEle);
void MenuBarBtn_CloseMenu(HELE hEle);

//回调函数
void CALLBACK MenuBarBtn_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK MenuBarBtn_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK MenuBarBtn_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK MenuBarBtn_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK MenuBarBtn_OnEventMouseSay(HELE hEle, HELE hEventEle); //鼠标停留
BOOL CALLBACK MenuBarBtn_OnEventMouseLeave(HELE hEle, HELE hEventEle); //鼠标离开


///////////////////////////////////////////////////////////////////////////

//菜单条
struct menuBar_
{
	ele_  ele; //继承
	//----------------

	menuBarButon_   *pBtnTop;  //鼠标停留在哪个按钮上 //当前弹出菜单按钮
	BOOL   bDown;          //菜单栏按下 TRUE 自动弹出 
	int    buttonHeight;   //菜单按钮高度

	HIMAGE  hImage;
	BOOL    bAdjust;  //调整布局
};


//API:
XC_API HELE WINAPI XMenuBar_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);  //创建按钮
XC_API int WINAPI XMenuBar_AddButton(HELE hEle, wchar_t *pText);     //增加弹出菜单按钮

XC_API int WINAPI XMenuBar_InsertButton(HELE hEle, wchar_t *pText, int index);     //插入弹出菜单按钮

XC_API void WINAPI XMenuBar_AddMenuItem(HELE hEle, int index, int id, wchar_t *pText, int parentId = XMENU_ROOT, int uFlags = 0);
XC_API void WINAPI XMenuBar_AddMenuItemImage(HELE hEle, int index, int id, wchar_t *pText, int parentId, int uFlags, HIMAGE hImage); //增加菜单项


XC_API void WINAPI XMenuBar_InsertMenuItem(HELE hEle, int index, int id, wchar_t *pText, int uFlags, int insertID); //插入菜单项,插入到ID为insertID菜单项前面位置
XC_API void WINAPI XMenuBar_InsertMenuItemImage(HELE hEle, int index, int id, wchar_t *pText, int uFlags, int insertID, HIMAGE hImage); //增加菜单项

//删除节点
XC_API void WINAPI XMenuBar_DeleteMenuItem(HELE hEle, int index, int id); //删除菜单项

XC_API void WINAPI XMenuBar_SetButtonHeight(HELE hEle, int height); //设置弹出菜单按钮高度

XC_API HELE WINAPI XMenuBar_GetButton(HELE hEle, int index);  //获取弹出菜单按钮句柄
XC_API HMENUX WINAPI XMenuBar_GetMenu(HELE hEle, int index); //获取菜单句柄

XC_API void WINAPI XMenuBar_DeleteButton(HELE hEle, int index); //删除菜单项并且销毁,同时该按钮下的弹出菜单也被销毁
//移除弹出菜单按钮

//贴图:
XC_API void WINAPI XMenuBar_SetImage(HELE hEle, HIMAGE hImage = NULL);


//私有方法:
void MenuBar_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);

void MenuBar_Adjust(HELE hEle); //调整布局

//弹出菜单鼠标移动,hEle:菜单条句柄
void MenuBar_OnMenuMouseMove(HELE hEle, POINT *pPt);

//回调函数:
void CALLBACK MenuBar_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK MenuBar_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK MenuBar_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);


//插入菜单项
//修改菜单项