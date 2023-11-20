/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct treeNode_  //树结点
{
	treeNode_   *pParent;  //父结点      多个子结点拥有同一个父结点
	treeNode_   *pBrother; //长兄结点    同层的上一个结点
	treeNode_   *pLeft;    //左结点
	treeNode_   *pRight;   //右结点
	int         depth;     //结点深度

	//数据
	int      x;         //x坐标
	int      y;         //y坐标
	int      id;        //结点ID
	int      imageId;   //图标索引
	int      selectImageId; //选择项 图片索引
	BOOL     bExpand;   //是否展开结点
	HSTRING  hString;   //文本
	void*	 data;      //用户数据

	int      textWidth;  //文本宽度
	int      state;      //状态
	treeNode_  *pEnd;    //该节点的下一层最后一个子节点

	BOOL  bCheck;  //复选框是否选择

	RECT rcButton; //按钮坐标
	RECT rcImage;  //图片坐标
	RECT rcText;   //文本坐标
	RECT rcCheck;  //复选框坐标

	HARRAY hArrayBindEle; //绑定的元素 itemBindEle_*
};

#define XTREE_H_LINE_LENGTH     10  //水平虚线长度
#define XTREE_CHECK_SIZE        15  //复选框大小

struct tree_
{
	scrollView_  scrollView; //继承
	//-------------
	treeNode_  *pRoot;      //树根结点
	BOOL       bAdjust;     //树调整,TRUE需要调整
	BOOL       bLine;       //是否有链接线
	BOOL       bRootLine;   //连接根部的线
	BOOL       bButton;     //是否有展开按钮
	BOOL       bCheck;      //复选框
	int        uid;         //结点ID增长 防止重复,从1开始
	int        expandSize;  //展开按钮宽度高度
	int        indentation; //子项缩进宽度
	int        itemHeight;  //项高度
	int        spacingLeft;     //左间隔
	int        spacingTop;      //上间距

	HXCGUI      hImageList;   //图片列表
	treeNode_   *pCurrItem;   //当前选择项节点指针
	treeNode_   *pEnd;        //根节点的最后一个节点

//--------------------------------------
	pFunTree_DrawItem  pDrawItem;
#ifdef	XCGUI_PLUS    //C++类支持,对类成员函数注册的支持
	void    *pClass_Fun_Info;//消息事件回调函数信息指针
#endif
};

#ifdef	XCGUI_PLUS //C++类支持,对类成员函数注册的支持
XC_API void WINAPI XTree_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //设置用户自绘项
#endif

//API:
XC_API HELE WINAPI XTree_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
//parentId:0为跟节点ID; insertAfter:插入位置标识,或者是插入指定项后面,项的ID
XC_API int WINAPI XTree_InsertItem(HELE hEle, wchar_t *pText, int parentId = XTREE_ROOT, int imageId = -1, int selectImageId = -1, int insertAfter = XTREE_INSERT_LAST, BOOL bExpand = TRUE); //插入项

XC_API void WINAPI XTree_EnableButton(HELE hEle, BOOL bEnable);    //显示按钮
XC_API void WINAPI XTree_EnableLine(HELE hEle, BOOL bEnable);      //显示连接虚线
XC_API void WINAPI XTree_EnableRootLine(HELE hEle, BOOL bEnable);  //启用连接根部的线
XC_API BOOL WINAPI XTree_IsButton(HELE hEle);
XC_API BOOL WINAPI XTree_IsLine(HELE hEle);
XC_API BOOL WINAPI XTree_IsRootLine(HELE hEle);
XC_API BOOL WINAPI XTree_IsExpand(HELE hEle, int id); //判断指定项是否展开

XC_API void WINAPI XTree_SetSpacingLeft(HELE hEle, int left);   //设置左间隔
XC_API void WINAPI XTree_SetSpacingTop(HELE hEle, int top);     //设置上间隔
XC_API void WINAPI XTree_SetImageList(HELE hEle, HXCGUI hImageList); //设置图片列表
XC_API void WINAPI XTree_SetItemData(HELE hEle, int id, void* data);   //设置用户数据
XC_API void WINAPI XTree_SetExpandButtonSize(HELE hEle, int size);   //设置展开按钮大小
XC_API void WINAPI XTree_SetIndentation(HELE hEle, int width);  //设置子项缩进宽度
XC_API void WINAPI XTree_SetSelectItem(HELE hEle, int id);     //设置选择项
XC_API void WINAPI XTree_SetItemText(HELE hEle, int id, wchar_t *pText);//设置项文本
XC_API void WINAPI XTree_SetItemImage(HELE hEle, int id, int imageId);  //设置项图片
XC_API void WINAPI XTree_SetItemHeight(HELE hEle, int height); //设置项高度
XC_API BOOL WINAPI XTree_SetItemBindEle(HELE hEle, int id, itemBindEle_ *pInfo); //绑定元素

XC_API void* WINAPI XTree_GetItemData(HELE hEle, int id); //获取用户数据
XC_API int WINAPI XTree_GetItemHeight(HELE hEle);      //获取项高度
XC_API int WINAPI XTree_GetSelectItem(HELE hEle);   //获取当前选择的项
XC_API int WINAPI XTree_GetParentItem(HELE hEle, int id); //获取指定项的父项
XC_API int WINAPI XTree_GetChildItem(HELE hEle, int id);  //获取指定项的子项
XC_API int WINAPI XTree_GetNextSiblingItem(HELE hEle, int id); //获取指定项的下一个兄弟项
XC_API int WINAPI XTree_GetPrevSiblingItem(HELE hEle, int id); //获取指定项的上一个兄弟项
XC_API int WINAPI XTree_GetFirstItem(HELE hEle); //获取第一个节点
XC_API int WINAPI XTree_GetItemDepth(HELE hEle, int id);//获取节点深度

XC_API int WINAPI XTree_GetItemImage(HELE hEle, int id);  //获取项图片
XC_API wchar_t* WINAPI XTree_GetItemText(HELE hEle, int id); //获取项文本
XC_API HXCGUI WINAPI XTree_GetImageList(HELE hEle); //获取图片列表
XC_API void WINAPI XTree_Expand(HELE hEle, int id, BOOL bExpand); //展开收缩指定项
XC_API void WINAPI XTree_DeleteItem(HELE hEle, int id); //删除一个项
XC_API void WINAPI XTree_DeleteAllItems(HELE hEle); //清空树


XC_API int WINAPI XTree_HitTest(HELE hEle, POINT *pPt);  //测试点击位置,返回项ID


XC_API void WINAPI XTree_SetUserDrawItem(HELE hEle, pFunTree_DrawItem pFunDrawItem); //设置用户自绘项

XC_API void WINAPI XTree_EnableCheckBox(HELE hEle, BOOL bEnable);//启用复选框
XC_API BOOL WINAPI XTree_IsItemCheck(HELE hEle, int id); //判断项的复选框是否勾选
XC_API void WINAPI XTree_SetItemCheck(HELE hEle, int id, BOOL bCheck); //设置项的复选框

//私有方法:
void Tree_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
int  Tree_AddID(HELE hEle); //递增新ID
BOOL Tree_AddIDTest(treeNode_ *pNode, int id); //检查ID是否使用

BOOL Tree_InsertItem1(HELE hEle, treeNode_ *pNode);  //根节点
BOOL Tree_InsertItem2(HELE hEle, treeNode_ *pNode, int insertAfter);  //根节点的兄弟节点
BOOL Tree_InsertItem3(HELE hEle, treeNode_ *pNode, int parentId, int insertAfter);

treeNode_* Tree_GetTreeNode(HELE hEle, treeNode_ *pNode, int nodeId); //获取指定ID结点

void Tree_AdjustTree(HELE hEle);  //调整树
void Tree_TraversalAdjustTree(HELE hEle, treeNode_ *pNode, int x, int *pHeights, int *pWidths, BOOL bExpand); //遍历调整树

BOOL Tree_TestClick(HELE hEle, treeNode_ *pNode, POINT *pPt);   //遍历测试鼠标点击
BOOL Tree_TextDBClick(HELE hEle, treeNode_ *pNode, POINT *pPt); //遍历测试鼠标双击
void Tree_DeleteNode(treeNode_ *pNode); //遍历删除结点,包括子项
void Tree_DrawItem(HELE hEle, HDRAW hDraw, treeNode_ *pNode);
treeNode_ *Tree_HitTestNode(HELE hEle, treeNode_ *pNode, POINT *pPt);  //测试点击位置

void Tree_UserDrawItem(HELE hEle, HDRAW hDraw, treeNode_ *pNode);

//回调函数:
void CALLBACK Tree_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Tree_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Tree_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Tree_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK Tree_OnMouseDBClick(HELE hEle, POINT *pPt);

BOOL CALLBACK Tree_OnEventSetFocus(HELE hEle, HELE hEventEle);  //获得焦点
BOOL CALLBACK Tree_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点


