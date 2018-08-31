/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//字符串列表框

struct listBox_item_
{
	HSTRING hString; //字符串列表 wchar_t*
	int   imageID;   //字符串对应图标ID

	BOOL  bCheck;    //复选框

	int   userData; //用户绑定数据
	HARRAY hArrayBindEle; //绑定的元素 itemBindEle_*
};


#define  XLISTBOX_CHECK_SIZE   13   //复选框宽度
#define  XLISTBOX_LEFT         3    //项左边间隔
#define  XLISTBOX_RIGHT        3    //项目右间隔
struct listBox_
{
	scrollView_  scrollView; //继承
	//-------------
	HARRAY  hArrayListItem; //项列表 listBox_item_*
	HXCGUI  hImageList;     //图标列表

	int     height;       //行高
	int     curSel;       //当前选择的行
	int     maxTextWidth; //最长行的文本长度
	BOOL    bAdjust;

	BOOL    bCheck; //复选框是否启用

	//鼠标移动高亮显示
	BOOL  bLineHighlight; //是否启用高亮显示
	int   mouseStayId;    //当前鼠标停留的项

	COLORREF selectItemColor; //选择项颜色 126,206,244
	COLORREF mouseStayColor;  //鼠标停留项颜色 192,232,250

	//----------------------
	pFunListBox_DrawItem  pDrawItem; //用户自绘
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
};

#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
XC_API void WINAPI XListBox_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘列表框项
#endif

//API:
XC_API HELE WINAPI XListBox_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XListBox_AddString(HELE hEle, wchar_t *pText, int imageId = -1);  //增加一个字符串到列表
XC_API BOOL WINAPI XListBox_InsertString(HELE hEle, int index, wchar_t *pText, int imageId = -1); //插入项
XC_API void WINAPI XListBox_EnableCheckBox(HELE hEle, BOOL bEnable); //启用复选框
XC_API void WINAPI XLsitBox_EnableLineHighlight(HELE hEle, BOOL bEnable);  //启用或关闭行高亮显示


XC_API wchar_t* WINAPI XListBox_GetItemText(HELE hEle, int index);   //获取指定行文本
XC_API int  WINAPI XListBox_GetItemHeight(HELE hEle);              //获取行高
XC_API int  WINAPI XListBox_GetSelectItem(HELE hEle);              //获取选择行
XC_API int  WINAPI XListBox_GetItemImage(HELE hEle, int index); //获取项图标ID
XC_API int  WINAPI XListBox_GetItemCount(HELE hEle); //获取项数量
XC_API HXCGUI WINAPI XListBox_GetImageList(HELE hEle); //获取图片列表
XC_API BOOL WINAPI XListBox_GetItemRect(HELE hEle, in_ int index, out_ RECT *pRect);  //获取项坐标...
XC_API int  WINAPI XListBox_HitTest(HELE hEle, POINT *pPt);  //测试鼠标点在哪个项上,-1没有在任何项上
XC_API int  WINAPI XListBox_GetItemData(HELE hEle, int index); //获取项绑定数据

XC_API void WINAPI XListBox_SetItemText(HELE hEle, int index, wchar_t *pText);  //设置指定行文本
XC_API void WINAPI XListBox_SetSelectItem(HELE hEle, int index);    //设置选择行
XC_API void WINAPI XListBox_SetItemHeight(HELE hEle, int height);   //设置行高
XC_API void WINAPI XListBox_SetImageList(HELE hEle, HXCGUI hImageList); //设置图标列表
XC_API void WINAPI XListBox_SetItemImage(HELE hEle, int index, int imageId); //设置项图标ID
XC_API void WINAPI XListBox_SetItemCheck(HELE hEle, int index, BOOL bCheck); //设置项的复选框
XC_API BOOL WINAPI XListBox_SetItemBindEle(HELE hEle, int index, itemBindEle_ *pInfo); //绑定元素
XC_API void WINAPI XListBox_SetItemData(HELE hEle, int index, int data); //设置项绑定数据

XC_API void WINAPI XListBox_SetSelectItemColor(HELE hEle, COLORREF color); //设置选择项颜色
XC_API void WINAPI XListBox_SetItemMouseStayColor(HELE hEle, COLORREF color);//设置鼠标停留高亮项颜色

XC_API void WINAPI XListBox_DeleteItem(HELE hEle, int index);  //删除行
XC_API void WINAPI XListBox_DeleteAll(HELE hEle);  //删除所有行
XC_API BOOL WINAPI XListBox_IsItemCheck(HELE hEle, int index);      //判断项的复选框是否勾选
XC_API void WINAPI XListBox_Adjust(HELE hEle);

//自绘:
XC_API void WINAPI XListBox_SetUserDrawItem(HELE hEle, pFunListBox_DrawItem pFunDrawItem); //设置用户自绘列表框项

//私有方法:
void ListBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void ListBox_MouseDown(HELE hEle, POINT *pPt);


//回调函数
void CALLBACK ListBox_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK ListBox_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ListBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListBox_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListBox_OnEventMouseLeave(HELE hEle, HELE hEventEle);