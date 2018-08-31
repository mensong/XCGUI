/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



#if 0


HELE hEdit;//编辑框资源句柄
//列表项选择事件
BOOL CALLBACK MyEventListSelect(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle) return FALSE;

	//hEle:列表元素句柄
	//id:当前选择项索引
	//获取选择项数量
	int count=XList_GetSelectCount(hEventEle);
	//如果有选择的项
	if(count>0)
	{
		//定义数组接收选择项索引
		int *pArr=new int[count];
		//获取选择项索引
		XList_GetSelectAllItem(hEventEle,pArr,count);
		//创建字符串资源
		HSTRING hStr=XStr_Create();
		XStr_SetString(hStr,L"当前选择的项:\n");
		for(int i=0;i<count;i++)
		{
			//获取项内容
			wchar_t *pText=XList_GetItemText(hEventEle,pArr[i],0);
			if(pText)
			{
				wchar_t buf[20]={0};
				wsprintf(buf,L"index=%d, ",pArr[i]);
				//添加到字符串资源中
				XStr_AddString(hStr,buf);
				XStr_AddString(hStr,pText);
				XStr_AddString(hStr,L"\n");
			}
			//设置编辑框内容
			XEdit_SetText(hEdit,XStr_GetBuffer(hStr));
		}
		//销毁字符串资源句柄
		XStr_Destroy(hStr);
		delete []pArr;
	}else
		XEdit_SetText(hEdit,NULL);
	//重绘编辑框视图
	XEle_RedrawEle(hEdit);
	return TRUE;
}

//列表头项点击事件
BOOL CALLBACK MyEventListHeaderClick(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle) return FALSE;
	//hEle:列表元素句柄
	//id:列表头项索引
	wchar_t buf[50]={0};
	wsprintf(buf,L"点击列表头:\nid=%d\n%s",id,XList_GetHeaderItemText(hEventEle,id));
	//设置编辑框内容,显示列表头项点击事件
	XEdit_SetText(hEdit,buf);
	//重绘编辑框视图
	XEle_RedrawEle(hEdit);
	return TRUE;
}

//列表元素-列表头项宽度改变事件
BOOL CALLBACK MyEventListHeaderChange(HELE hEle,HELE hEventEle,int id,int width)
{
	if(hEle!=hEventEle) return FALSE;
	//hEle:列表元素句柄
	//id:列表头项索引
	//width:当前项宽度
	wchar_t buf[50]={0};
	wsprintf(buf,L"列表头项宽度改变:\nid=%d\nwidth=%d\n%s",id,width,XList_GetHeaderItemText(hEventEle,id));
	//设置编辑框内容,显示列表头项宽度改变事件
	XEdit_SetText(hEdit,buf);
	//重绘编辑框视图
	XEle_RedrawEle(hEdit);
	return TRUE;
}

//弹出菜单项选择事件
BOOL CALLBACK MyEventMenuSelect(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle) return FALSE;
	//hEle:列表元素句柄
	//id:菜单项id
	switch(id)
	{
	case 1: //取消选择
		{
			//取消列表元素所有选择项
			XList_CancelSelectAll(hEle);
			//重绘更新列表元素视图
			XEle_RedrawEle(hEle);
		}break;
	case 2: //删除项
		{
			//获取列表元素当前选择的项
			int hItem=XList_GetSelectItem(hEle);
			//如果选择项不为空
			if(-1!=hItem)
			{
				//删除选择的项
				XList_DeleteItem(hEle,hItem);
				//重绘更新列表元素视图
				XEle_RedrawEle(hEle);
			}
		}break;
	case 3: //全选
		{
			//选择所有项
			XList_SetSelectItemAll(hEle);
			//重绘更新列表元素视图
			XEle_RedrawEle(hEle);
		}break;
	case 4: //清空
		{
			//删除所有项
			XList_DeleteAllItems(hEle);
			//重绘更新列表元素视图
			XEle_RedrawEle(hEle);
		}break;
	}
	//如果你不知道这里该怎么做,就返回FALSE
	return TRUE;
}

//列表元素鼠标右键弹起消息
BOOL CALLBACK MyRButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
	//hEle:列表元素资源句柄
	//获取鼠标所在项索引
	int pos=XList_HitTest(hEle,pPt); 
	//确定不是在空白区
	if(pos>=0) 
	{
		//取消所有选择项
		XList_CancelSelectAll(hEle);
		//选择鼠标所在项
		XList_SetSelectItem(hEle,pos);
		//重绘以便更新界面
		XEle_RedrawEle(hEle);
		//创建弹出菜单
		HMENUX hMenu=XMenu_Create();
		//添加菜单项
		XMenu_AddItem(hMenu,1,L"取消选择");
		XMenu_AddItem(hMenu,2,L"删除项");
		XMenu_AddItem(hMenu,3,L"全选");
		XMenu_AddItem(hMenu,4,L"清空");
		//将坐标点转换到屏幕坐标
		POINT pt=*pPt;
		XEle_PointToNCWnd(hEle,&pt);
		ClientToScreen(XEle_GetHWnd(hEle),&pt);
		//弹出菜单
		XMenu_Popup(hMenu,XEle_GetHWnd(hEle),pt.x,pt.y,hEle);
		//注册菜单项选择事件
		XEle_RegisterEvent(hEle,XE_MENUSELECT,MyEventMenuSelect);
	}
	//默认返回FALSE
	return FALSE;
}

//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,640,350,L"炫彩界面库-窗口");

	//设置窗口背景图片
	//XWnd_SetImage(hWindow,L"image\\11.jpg");
	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//创建列表元素
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//关联图片列表
	XList_SetImageList(hList,hImageList);
	//添加列表头
	XList_AddColumn(hList,160,L"列表头项-1",2);
	XList_AddColumn(hList,160,L"列表头项-2",2);
	XList_AddColumn(hList,160,L"列表头项-3",2);
	//添加列表项
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<12;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//添加项
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//设置子项内容
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}
	//创建右边编辑框,显示列表元素事件
	hEdit=XEdit_Create(465,10,150,300,hWindow);
	//启用支持多行
	XEdit_EnableMultiLine(hEdit,TRUE);
	//注册列表元素项选择事件
	XEle_RegisterEvent(hList,XE_LIST_SELECT,MyEventListSelect);
	//注册列表元素-列表头项点击事件
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CLICK,MyEventListHeaderClick);
	//注册列表元素-列表头项宽度改变事件
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CHANGE,MyEventListHeaderChange);
	//注册列表元素-鼠标右键弹起消息
	XEle_RegisterMessage(hList,XM_RBUTTONUP,MyRButtonUp);

	XEle_SetBkColor(XSView_GetView(hList),RGB(200,200,200));

	itemBindEle_ info;
	info.hEle=XBtn_Create(0,0,10,10,L"1111");
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XList_SetItemBindEle(hList,3,0,&info);

	XWnd_ShowWindow(hWindow,SW_SHOW); //显示窗口

	//运行程序
	XRunXCGUI();
	//销毁图片列表
	//XImageList_Destroy(hImageList);
	return 0;
}

#endif 

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

#if 0

BOOL CALLBACK MyEventListSelect(HELE hEle,HELE hEventEle,int id)
{	
	//hEle:列表元素句柄
	//id:当前选择项索引
	return FALSE;
}

//列表头项点击事件
BOOL CALLBACK MyEventListHeaderClick(HELE hEle,HELE hEventEle,int id)
{
	//hEle:列表元素句柄
	//id:列表头项索引
	return FALSE;
}

//列表元素-列表头项宽度改变事件
BOOL CALLBACK MyEventListHeaderChange(HELE hEle,HELE hEventEle,int id,int width)
{
	//hEle:列表元素句柄
	//id:列表头项索引
	//width:当前项宽度
	return FALSE;
}
//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,350,L"炫彩界面库-窗口");
	//显示窗口
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//创建列表元素
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//关联图片列表
	XList_SetImageList(hList,hImageList);
	//添加列表头
	XList_AddColumn(hList,160,L"列表头项-1",2);
	XList_AddColumn(hList,160,L"列表头项-2",2);
	XList_AddColumn(hList,160,L"列表头项-3",2);
	//添加列表项
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<100;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//添加项
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//设置子项内容
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}

	//注册列表元素项选择事件
	XEle_RegisterEvent(hList,XE_LIST_SELECT,MyEventListSelect);
	//注册列表元素-列表头项点击事件
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CLICK,MyEventListHeaderClick);
	//注册列表元素-列表头项宽度改变事件
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CHANGE,MyEventListHeaderChange);
	//运行程序
	XRunXCGUI();
	//销毁图片列表
	//XImageList_Destroy(hImageList);
	return 0;
}
#endif


////////////////////////////////////////////////////////////////////////////////////

#if 0

//列表头自绘
void CALLBACK MyListHeader_DrawItem(HELE hEle,listHeader_drawItem_ *pDrawItem)
{
	XTRACE("绘制背景 \n");
	RECT rect=pDrawItem->rect;
	//绘制列表头背景
	if(-1==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(0,210,0));

		HPEN hPen=XDraw_CreatePen_(pDrawItem->hDraw,PS_SOLID,2,RGB(255,0,0));
		HGDIOBJ hOldPen=XDraw_SelectObject_(pDrawItem->hDraw,hPen);
		XDraw_MoveToEx_(pDrawItem->hDraw,0,rect.bottom-1,0);
		XDraw_LineTo_(pDrawItem->hDraw,rect.right,rect.bottom-1);
		XDraw_SelectObject_(pDrawItem->hDraw,hOldPen);
		XDraw_DeleteObject_(pDrawItem->hDraw,hPen);
		return ;
	}
	rect.bottom-=2;
	//绘制列表头项
	if(STATE_LEAVE==pDrawItem->state)
	{
		rect.right--;
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(0,255,0));
	}else if(STATE_STAY==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(255,147,147));
	}else if(STATE_DOWN==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(255,202,202));
	}
	//绘制图标
	HXCGUI hImageList=XList_GetImageList(hEle);
	if(hImageList)
	{
		XImageList_DrawImage(hImageList,pDrawItem->hDraw,pDrawItem->imageId,rect.left+3,rect.top+5);
		rect.left+=22;
	}else
		rect.left+=3;
	rect.top+=3;
	//绘制文本
	XDraw_DrawText_(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&rect,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

}

//列表自绘
void CALLBACK MyList_OnDrawItem(HELE hEle,list_drawItem_ *pDrawItem)
{
	//绘制背景
	if(STATE_SELECT==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(0,255,0));
	}else
	{
		if(0==pDrawItem->index%2)
			XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(197,255,197));
		else
			XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(255,202,202));
	}
	//绘制图标
	HXCGUI hImageList=XList_GetImageList(hEle);
	RECT rect=pDrawItem->rect;
	if(hImageList)
	{
		rect.left+=3;
		XImageList_DrawImage(hImageList,pDrawItem->hDraw,pDrawItem->imageId,rect.left,pDrawItem->rect.top+3);
		rect.left+=19;
	}else
		rect.left+=3;
	//绘制文本
	XDraw_DrawText_(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&rect,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}

//基于二叉树的多叉树---测试
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,500,380,L"炫彩界面库-窗口");

	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,true);
	//添加图片

	HIMAGE hImage1=XImage_LoadFile(L"image\\2055.ico");
	HIMAGE hImage2=XImage_LoadFile(L"image\\2050.ico");
	HIMAGE hImage3=XImage_LoadFile(L"image/2063.ico");
	XImageList_AddImage(hImageList,hImage1);
	XImageList_AddImage(hImageList,hImage2);
	XImageList_AddImage(hImageList,hImage3);

	//创建列表元素
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//关联图片列表
	XList_SetImageList(hList,hImageList);
	//添加列表头
	XList_AddColumn(hList,160,L"列表头项-1",2);
	XList_AddColumn(hList,160,L"列表头项-2",2);
	XList_AddColumn(hList,160,L"列表头项-3",2);
	//添加列表项
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//添加项
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//设置子项内容
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}

	XList_SetUserDrawItem(hList,MyList_OnDrawItem);
	XList_SetUserDrawItemHeader(hList,MyListHeader_DrawItem);
	//显示窗口
	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();    //运行程序
	return 0;
}
#endif


#if 0

///带复选按钮///////////////////////////////////////////////////////////////////////////////////
//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,350,L"炫彩界面库-窗口");
	//显示窗口
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片
	XImageList_AddImage(hImageList,XImage_LoadFile( L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//创建列表元素
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//关联图片列表
	XList_SetImageList(hList,hImageList);
	//添加列表头
	XList_AddColumn(hList,160,L"列表头项-1",2);
	XList_AddColumn(hList,160,L"列表头项-2",2);
	XList_AddColumn(hList,160,L"列表头项-3",2);
	//添加列表项
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//添加项
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//设置子项内容
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}
//	XList_ShowHeader(hList,FALSE);
	XList_EnableGrid(hList,FALSE);
	XList_EnableCheckBox(hList,TRUE);

//	XList_SetHeaderHeight(hList,50);
	//运行程序
	XRunXCGUI();

	return 0;
}
#endif


#if 0

//测试:鼠标点击
HELE hList=NULL;
BOOL CALLBACK EleLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	//点击测试
	int item,sub;
	BOOL res=XList_HitTestEx(hList,pPt,&item,&sub);
	if(res)
		XTRACE("hit line=%d, column=%d \n", item,sub);

	return FALSE;
}

//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,350,L"炫彩界面库-窗口");
	//显示窗口
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片
	XImageList_AddImage(hImageList,XImage_LoadFile( L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//创建列表元素
	hList=XList_Create(10,10,450,300,hWindow);
	//关联图片列表
	XList_SetImageList(hList,hImageList);
	//添加列表头
	XList_AddColumn(hList,160,L"列表头项-1",2);
	XList_AddColumn(hList,160,L"列表头项-2",2);
	XList_AddColumn(hList,160,L"列表头项-3",2);
	//添加列表项
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//添加项
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//设置子项内容
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}
	XList_EnableGrid(hList,FALSE);
	XList_EnableCheckBox(hList,TRUE);

	XEle_RegisterMessage(hList,XM_LBUTTONDOWN,EleLButtonDown);

	//运行程序
	XRunXCGUI();

	return 0;
}
#endif


#if 0

BOOL CALLBACK OnEventSetFocus(HELE hEle,HELE hEventEle)
{
	if( hEle== hEventEle)
		XTRACE("list 获得焦点 \n");
	return FALSE;
}

//程序入口函数,测试项绑定元素
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,600,380,L"炫彩界面库-窗口");
	//显示窗口
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片
	XImageList_AddImage(hImageList,XImage_LoadFile( L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//创建列表元素
	HELE  hList=XList_Create(10,10,450,300,hWindow);
	XList_EnableCheckBox(hList,TRUE);

	//关联图片列表
	XList_SetImageList(hList,hImageList);
	//添加列表头
	XList_AddColumn(hList,160,L"列表头项-1",2);
	XList_AddColumn(hList,160,L"列表头项-2",2);
	XList_AddColumn(hList,160,L"列表头项-3",2);
	//添加列表项
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//添加项
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//设置子项内容
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}

	itemBindEle_ info;
	info.hEle=XBtn_Create(10,10,100,20,L"aaa",hList);
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XList_SetItemBindEle(hList,1,1,&info);

	XList_SetColumnMinWidth(hList,1,100);

	XBtn_Create(480,10,100,20,L"btn",hWindow);

	XEdit_Create(480,50,100,20,hWindow);

	XEle_SetId(hList,101);
	XEle_SetId(info.hEle,102);

	XEle_RegisterEvent(hList,XE_SETFOCUS,OnEventSetFocus);
	//运行程序
	XRunXCGUI();

	return 0;
}
#endif
