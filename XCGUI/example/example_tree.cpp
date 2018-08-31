/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



//////////////////////////////////////////////////
//列表树//////////////////////////////////////////

#if 0

HELE hTree; //树资源句柄
HELE hEdit; //编辑框资源句柄
//隐藏按钮-按钮点击事件
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	//hEle:按钮资源句柄
	//判断树是否显示按钮
	if(XTree_IsButton(hTree))
		//树隐藏按钮
		XTree_EnableButton(hTree,FALSE);
	else
		//树显示按钮
		XTree_EnableButton(hTree,TRUE);
	//重绘更新树视图
	XEle_RedrawEle(hTree);
	return TRUE;
}

//隐藏连接线按钮-点击事件
BOOL CALLBACK MyEventBtnClick2(HELE hEle,HELE hEventEle)
{
	//hEle:按钮资源句柄
	//判断是否显示连接线
	if(XTree_IsLine(hTree))
		//隐藏链接线
		XTree_EnableLine(hTree,FALSE);
	else
		//显示连接线
		XTree_EnableLine(hTree,TRUE);
	//重绘更新树视图
	XEle_RedrawEle(hTree);
	return TRUE;
}

//取消根部线按钮-点击事件
BOOL CALLBACK MyEventBtnClick3(HELE hEle,HELE hEventEle)
{
	//hEle:按钮资源句柄
	//判断树是否显示根部连接线
	if(XTree_IsRootLine(hTree))
		//隐藏根部连接线
		XTree_EnableRootLine(hTree,FALSE);
	else
		//显示根部连接线
		XTree_EnableRootLine(hTree,TRUE);
	//重绘更新树视图
	XEle_RedrawEle(hTree);
	return TRUE;
}

//树列表选择事件
BOOL CALLBACK MyEventTreeSelect(HELE hEle,HELE hEventEle,int id)
{
	//hEle:树资源句柄
	//id:选择项id
	//确定有选择的项
	if(id>0)
	{
		wchar_t buf[50]={0};
		//获取选择项内容
		wchar_t *pText=XTree_GetItemText(hEle,id);
		wsprintf(buf,L"选择项:\n%s",pText);
		//设置编辑框内容
		XEdit_SetText(hEdit,buf);
	}else
	{
		XEdit_SetText(hEdit,L"没有选择项");
	}

	return TRUE;
}

//树项展开或收缩事件
BOOL CALLBACK MyEventTreeExpand(HELE hEle,HELE hEventEle,int id,BOOL bExpand)
{
	//hEle:树资源句柄
	//id:选择项id
	wchar_t buf[50]={0};
	//获取选择项内容
	wchar_t *pText=XTree_GetItemText(hEle,id);
	if(bExpand)
		wsprintf(buf,L"展开项:\n%s",pText);
	else
		wsprintf(buf,L"收缩项:\n%s",pText);
	//设置编辑框内容
	XEdit_SetText(hEdit,buf);

	return TRUE;
}

//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(500,200,400,260,L"测试窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//创建图标列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片资源
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2063.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2057.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2062.ico"));
	//创建树
	hTree=XTree_Create(10,10,200,200,hWindow);
	//XTree_SetSpacingLeft(hTree,10);   //设置左间隔
	//XTree_SetSpacingTop(hTree,10);    //设置上间隔
	//树关联图片列表
	XTree_SetImageList(hTree,hImageList);
	//插入树项
	//XTree_InsertItem(树资源句柄,内容,父项id,图片,图片,标识或id,是否展开)
	int root1=XTree_InsertItem(hTree,L"根节点项1",0,0,1);
	int root2=XTree_InsertItem(hTree,L"根节点项2",0,0,1);
	int root3=XTree_InsertItem(hTree,L"根节点项3",0,0,1);
	int root4=XTree_InsertItem(hTree,L"根节点项4",0,0,1);
	int root5=XTree_InsertItem(hTree,L"根节点项5",0,0,1);
	XTree_InsertItem(hTree,L"根节点项6",0,0,1);
	int child1=XTree_InsertItem(hTree,L"叶子项1",root1,2,3);
	XTree_InsertItem(hTree,L"叶子项2",root1,2,3);
	XTree_InsertItem(hTree,L"叶子项3",root1,2,3);
	XTree_InsertItem(hTree,L"叶子项4",child1,2,3);
	XTree_InsertItem(hTree,L"叶子项5",child1,2,3);
	XTree_InsertItem(hTree,L"叶子项6",root2,2,3);
	XTree_InsertItem(hTree,L"叶子项7",root2,2,3);
	XTree_InsertItem(hTree,L"叶子项8",root2,2,3);
	//创建按钮
	HELE hButton=XBtn_Create(220,10,80,20,L"隐藏按钮",hWindow);
	HELE hButton2=XBtn_Create(220,40,80,20,L"隐藏连接线",hWindow);
	HELE hButton3=XBtn_Create(220,70,80,20,L"取消根部线",hWindow);
	//创建编辑框
	hEdit=XEdit_Create(220,100,150,110,hWindow);
	XEdit_EnableMultiLine(hEdit,TRUE);
	//注册按钮点击事件
	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,MyEventBtnClick2);
	XEle_RegisterEvent(hButton3,XE_BNCLICK,MyEventBtnClick3);
	//注册树项选择事件
	XEle_RegisterEvent(hTree,XE_TREE_SELECT,MyEventTreeSelect);
	//注册树项展开收缩事件
	XEle_RegisterEvent(hTree,XE_TREE_EXPAND,MyEventTreeExpand);
	//运行程序
	XRunXCGUI();

	return 0;
}
#endif


#if 0
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//自绘树项
void CALLBACK MyTree_DrawItem(HELE hEle,tree_drewItem_ *pDrawItem)
{
	//绘制选择项背景
	if(STATE_SELECT==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rcText,RGB(197,255,197));
	}

	//绘制展开按钮
	if(pDrawItem->bExpand)
		XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rcButton,RGB(255,0,0));
	else
		XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rcButton,RGB(0,255,0));

	//绘制图标
	HXCGUI hImageList=XTree_GetImageList(hEle);
	if(hImageList)
	{
		XImageList_DrawImage(hImageList,pDrawItem->hDraw,pDrawItem->imageId,pDrawItem->rcImage.left,pDrawItem->rcImage.top);
	}

	//绘制文本
	DrawText(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&pDrawItem->rcText,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}
//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(500,200,400,260,L"炫彩界面库-窗口");

	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片资源
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2063.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico"));

	//创建树
	HELE hTree=XTree_Create(10,10,200,200,hWindow);

	//树关联图片列表
	XTree_SetImageList(hTree,hImageList);
	//插入树项
	//XTree_InsertItem(树句柄,内容,父项id,图片,图片,标识或id,是否展开)
	int root1=XTree_InsertItem(hTree,L"根节点项1",0,0,1);
	int root2=XTree_InsertItem(hTree,L"根节点项2",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root3=XTree_InsertItem(hTree,L"根节点项3",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root4=XTree_InsertItem(hTree,L"根节点项4",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root5=XTree_InsertItem(hTree,L"根节点项5",0,0,1,XTREE_INSERT_LAST,FALSE);

	XTree_InsertItem(hTree,L"叶子项1",root1,0,1);
	XTree_InsertItem(hTree,L"叶子项2",root1,0,1);
	XTree_InsertItem(hTree,L"叶子项3",root2,0,1);
	XTree_InsertItem(hTree,L"叶子项4",root3,0,1);
	XTree_InsertItem(hTree,L"叶子项5",root4,0,1);

	//设置树自绘项
	XTree_SetUserDrawItem(hTree,MyTree_DrawItem);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
#endif


#if 0

//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,450,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//创建树
	HELE hScrollView=XSView_Create(10,10,300,350,hWindow);
	XSView_SetSize(hScrollView,500,800);

	HELE hView=XSView_GetView(hScrollView);
	XEle_SetBkColor(hView,RGB(255,0,0));

	HELE hTree=XTree_Create(10,10,200,300,hView);
	HELE hTreeView=XSView_GetView(hTree);
	XEle_SetBkColor(hTreeView,RGB(0,255,0));

	XEle_SetId(hScrollView,101);
	XEle_SetId(hView,102);
	XEle_SetId(hTree,103);
	XEle_SetId(hTreeView,104);


//////////////////////////////////////////////
	HELE hTree2=XTree_Create(10,10,200,300,hTreeView);
	HELE hTreeView2=XSView_GetView(hTree2);
	XEle_SetBkColor(hTreeView2,RGB(0,0,255));

	XRunXCGUI();

	return 0;
}
#endif


#if 0

class CMyTree : public CXEventMsg
{
public:
	HELE m_hTree;
	void Init(HELE hTree)
	{
		m_hTree=hTree;
		XCGUI_Tree_SetUserDrawItem(m_hTree,&CMyTree::OnTree_DrawItem);
	}
	void OnTree_DrawItem(HELE hEle,tree_drewItem_ *pDrawItem)
	{

	}
};

BOOL CALLBACK OnEleMouseDBClick(HELE hEle,POINT *pPt)
{
	return FALSE;
}

//程序入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(469);

	//初始化界面库
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(500,200,400,260,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//创建图片列表
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//添加图片资源
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2063.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico"));

	//创建树
	HELE hTree=XTree_Create(10,10,200,200,hWindow);

	//树关联图片列表
	XTree_SetImageList(hTree,hImageList);
	//插入树项
	//XTree_InsertItem(树句柄,内容,父项id,图片,图片,标识或id,是否展开)
	int root1=XTree_InsertItem(hTree,L"根节点项1",0,0,1);
	int root2=XTree_InsertItem(hTree,L"根节点项2",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root3=XTree_InsertItem(hTree,L"根节点项3",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root4=XTree_InsertItem(hTree,L"根节点项4",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root5=XTree_InsertItem(hTree,L"根节点项5",0,0,1,XTREE_INSERT_LAST,FALSE);

	int id2=	XTree_InsertItem(hTree,L"叶子项1",root1,0,1);
	int id=	XTree_InsertItem(hTree,L"叶子项2",root1,0,1);
	XTree_InsertItem(hTree,L"叶子项3",root2,0,1);
	XTree_InsertItem(hTree,L"叶子项4",root3,0,1);
	XTree_InsertItem(hTree,L"叶子项5",root4,0,1);

	//	XTree_SetItemCheck(hTree,root2,TRUE);

	//XTree_EnableCheckBox(hTree,TRUE);
	XTree_EnableButton(hTree,FALSE);
	XTree_EnableLine(hTree,FALSE);
	XTree_SetSpacingLeft(hTree,10);

	XEle_RegisterMessage(hTree,XM_MOUSEDBCLICK,OnEleMouseDBClick);

	//	XTree_SetItemText(hTree,root1,L"1111111111111111111111122222");


	itemBindEle_ info;
	info.hEle=XBtn_Create(10,10,100,20,L"aaa",hTree);
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XTree_SetItemBindEle(hTree,id,&info);

	CMyTree MyTree;
	MyTree.Init(hTree);

	XRunXCGUI();

	return 0;
}
#endif