/**************************************************************************\
*
* Copyright 
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0

BOOL CALLBACK OnEventListViewDragInsert(HELE hEle,HELE hEventEle,listView_dragInsert_ *pInfo) //列表视图元素,用户拖动项插入事件
{

	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	int size=sizeof(UINT_PTR);
	XInitXCGUI();
	
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,400,L"炫彩界面库-窗口");//创建窗口
	if(hWindow)
	{
	//	HELE hButton=XBtn_Create(10,10,80,25,L"按钮",hWindow);//创建按钮
	//	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);//注册按钮点击事件

		HIMAGE hImage1 = XImage_LoadFile(L"image3//复件 1.png",0); //XImage_LoadFile(L"image3//1.png",0);
		HIMAGE hImage2 = XImage_LoadFile(L"image3//bg_Mian1.png",0); //XImage_LoadFile(L"image3//2.png",0);
		HIMAGE hImage3 = XImage_LoadFile(L"image3//3.png",0);
		HIMAGE hImage4 = XImage_LoadFile(L"image3//4.png",0);
		HIMAGE hImage5 = XImage_LoadFile(L"image3//5.png",0);
		HIMAGE hImage6 = XImage_LoadFile(L"image3//6.png",0);
		HIMAGE hImage7 = XImage_LoadFile(L"image3//bntimg//Add_But.png",0);

		HXCGUI hImageList=XImageList_Create(48,48);
		XImageList_EnableFixedSize(hImageList,false);

		XImageList_AddImage(hImageList,hImage1);
		XImageList_AddImage(hImageList,hImage2);
		XImageList_AddImage(hImageList,hImage3);
		XImageList_AddImage(hImageList,hImage4);
		XImageList_AddImage(hImageList,hImage5);
		XImageList_AddImage(hImageList,hImage6);
		XImageList_AddImage(hImageList,hImage7);

		HELE hListView=XListView_Create(10,10,300,300,hWindow);

		//XEle_SetBkColor(hListView,RGB(255,0,0));	
		XListView_SetImageList(hListView,hImageList);
		XListView_AddItem(hListView,L"网易",0);
		XListView_AddItem(hListView,L"淘宝",1);
		XListView_AddItem(hListView,L"搜狐",2);
		XListView_AddItem(hListView,L"炫彩",3);
		XListView_AddItem(hListView,L"百度",4);
	//	XListView_AddItem(hListView,L"谷歌",5);
	//	XListView_AddItem(hListView,L"添加应用",6);
		XListView_EnableMultiSelect(hListView,false);

		//XImage_LoadFileAdaptive(L"image3\\bk_select.png",12,72,12,72);
		HIMAGE hImage_Select=XImage_LoadFileAdaptive(L"image3\\bk_select.png",12,72,12,72);
		HIMAGE hImage_stay=XImage_LoadFileAdaptive(L"image3\\bk_stay.png",12,72,12,72);

		XListView_SetItemImageSelect(hListView,-1,0,hImage_Select);
		XListView_SetItemImageStay(hListView,-1,0,hImage_stay);

		XListView_SetItemImageSelect(hListView,-1,1,hImage_Select);
		XListView_SetItemImageStay(hListView,-1,1,hImage_stay);

		XListView_SetItemImageSelect(hListView,-1,2,hImage_Select);
		XListView_SetItemImageStay(hListView,-1,2,hImage_stay);


		XEle_RegisterEvent(hListView,XE_LISTVIEW_DRAG_INSERT,OnEventListViewDragInsert);

		XWnd_ShowWindow(hWindow,SW_SHOW);//显示窗口

		XRunXCGUI();
	}
	return 0;
}
#endif