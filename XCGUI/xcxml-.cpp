/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

///@defgroup groupLayout 布局文件API
///@ingroup  groupGuiDesigner
///


///@addtogroup groupLayout
///@{

///@brief 加载窗口布局文件,并创建窗口.
///@param pFileName  布局文件名.
///@param hXmlRes    资源文件句柄,如果没有为NULL.
///@param hWndParent HWND窗口句柄,如果没有为NULL.
///@return 窗口句柄.
HWINDOW WINAPI XC_LoadXML_Window(wchar_t *pFileName,HXMLRES hXmlRes,HWND hWndParent)
{
	if(NULL==pFileName)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,文件路径不能为空.");
		return NULL;
	}

	char file[MAX_PATH]={0};
	if(0==WideCharToMultiByte(CP_ACP,NULL,pFileName,wcslen(pFileName),file,MAX_PATH,NULL,NULL))
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能文件路径太长或字符编码错误.");
		return NULL;
	}

	TiXmlDocument xmlDoc(file);
	if(FALSE==xmlDoc.LoadFile())
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,文件路径错误.");
		return NULL;
	}
	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能标签错误.");
		return NULL;
	}

	return XC_LoadXML_WindowX(pRoot,hXmlRes,hWndParent);
}

///@brief 加载窗口布局文件,并创建窗口,从程序资源模块中加载.
///@param resID  资源ID.
///@param pType  资源类型.
///@param hXmlRes    资源文件句柄,如果没有为NULL.
///@param hWndParent HWND父窗口句柄,如果没有为NULL.
///@return 窗口句柄.
HWINDOW WINAPI XC_LoadXML_WindowRes(int resID,wchar_t *pType,HXMLRES hXmlRes,HWND hWndParent)
{
	HMODULE hInst=NULL;
	if(g_resourcesModule)
		hInst=g_resourcesModule;
	else
		hInst=GetModuleHandle(NULL);

	if(NULL==hInst) return NULL;

	LPCTSTR lpRes=MAKEINTRESOURCE(resID); 
	HRSRC   hRsrc=::FindResource(hInst,lpRes,pType);
	if(NULL==hRsrc) return NULL;
	HGLOBAL hGlobal=LoadResource(hInst,hRsrc);
	if(NULL==hGlobal) return NULL;
	DWORD   dwSize   =SizeofResource(hInst,hRsrc);

	HWINDOW hWindow=NULL;
	if(dwSize>0)
	{
		LPVOID   lpData  =LockResource(hGlobal);
		if(lpData)
		{
			char *pData=(char*)malloc(dwSize+1);
			if(pData)
			{
				memcpy(pData,lpData,dwSize);
				pData[dwSize]=0;
				hWindow=XC_LoadXML_WindowRes2(pData,hXmlRes,hWndParent);
				free(pData);
			}
		}
	}

	BOOL hrr=FreeResource(hGlobal);
	return hWindow;
}

HWINDOW XC_LoadXML_WindowRes2(char *pData,HXMLRES hXmlRes,HWND hWndParent)
{
	TiXmlDocument xmlDoc;
	if(NULL==xmlDoc.Parse(pData))
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败.");
		return NULL;
	}

	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能标签错误.");
		return NULL;
	}

	return XC_LoadXML_WindowX(pRoot,hXmlRes,hWndParent);
}

//载入XML布局页文件
///@brief 加载布局页文件,并创建页元素,页元素将被添加到该父元素或窗口上.
///@param hParent    窗口句柄或元素句柄,作为页元素的父.
///@param pFileName  布局页文件名.
///@param hXmlRes    资源文件句柄,如果没有为NULL.
///@return 页元素句柄.
BOOL WINAPI XC_LoadXML_Page(HXCGUI hParent,wchar_t *pFileName,HXMLRES hXmlRes)
{
	if(NULL==pFileName)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,文件路径不能为空.");
		return NULL;
	}

	char file[MAX_PATH]={0};
	if(0==WideCharToMultiByte(CP_ACP,NULL,pFileName,wcslen(pFileName),file,MAX_PATH,NULL,NULL))
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能文件路径太长或字符编码错误.");
		return NULL;
	}

	TiXmlDocument xmlDoc(file);
	if(FALSE==xmlDoc.LoadFile())
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,文件路径错误.");
		return NULL;
	}
	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能标签错误.");
		return NULL;
	}

	return XC_LoadXML_PageX(pRoot,hXmlRes,hParent);
}

//载入XML布局页文件
///@brief 加载布局页文件,并创建页元素,页元素将被添加到该父元素或窗口上,从程序资源模块中加载.
///@param hParent    窗口句柄或元素句柄,作为页元素的父.
///@param resID  资源ID.
///@param pType  资源类型.
///@param hXmlRes    资源文件句柄,如果没有为NULL.
///@return 页元素句柄.
BOOL WINAPI XC_LoadXML_PageRes(HXCGUI hParent,int resID,wchar_t *pType,HXMLRES hXmlRes)
{
	HMODULE hInst=NULL;
	if(g_resourcesModule)
		hInst=g_resourcesModule;
	else
		hInst=GetModuleHandle(NULL);

	if(NULL==hInst) return FALSE;

	LPCTSTR lpRes=MAKEINTRESOURCE(resID); 
	HRSRC   hRsrc=::FindResource(hInst,lpRes,pType);
	if(NULL==hRsrc) return FALSE;
	HGLOBAL hGlobal=LoadResource(hInst,hRsrc);
	if(NULL==hGlobal) return FALSE;
	DWORD   dwSize   =SizeofResource(hInst,hRsrc);

	BOOL bResult=FALSE;
	if(dwSize>0)
	{
		LPVOID   lpData  =LockResource(hGlobal);
		if(lpData)
		{
			char *pData=(char*)malloc(dwSize+1);
			if(pData)
			{
				memcpy(pData,lpData,dwSize);
				pData[dwSize]=0;
				bResult=XC_LoadXML_PageRes2(hParent,pData,hXmlRes);
				free(pData);
			}
		}
	}

	BOOL hrr=FreeResource(hGlobal);
	return bResult;
}

BOOL XC_LoadXML_PageRes2(HXCGUI hParent,char *pData,HXMLRES hXmlRes)
{
	TiXmlDocument xmlDoc;
	if(NULL==xmlDoc.Parse(pData))
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败.");
		return NULL;
	}

	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能标签错误.");
		return NULL;
	}

	return XC_LoadXML_PageX(pRoot,hXmlRes,hParent);
}

///@}

HWINDOW XC_LoadXML_WindowX(TiXmlElement *pRoot,HXMLRES hXmlRes,HWND hWndParent)
{
	const char *pWindow=pRoot->Value();
	if(NULL==pWindow)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能标签错误.");
		return NULL;
	}

	if(0==strcmp(pWindow,"window"))
	{
		return XML_HandleWindow(pRoot,hXmlRes,hWndParent);
	}else if(0==strcmp(pWindow,"modalWindow"))
	{
		return XML_HandleModalWindow(pRoot,hXmlRes,hWndParent);
	}else if(0==strcmp(pWindow,"frameWindow"))
	{
		return XML_HandleFrameWindow(pRoot,hXmlRes,hWndParent);
	}
	DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因没有窗口标签[<window>]或[<modalWindow>].");
	return NULL;
}

BOOL XC_LoadXML_PageX(TiXmlElement *pRoot,HXMLRES hXmlRes,HXCGUI hParent)
{
	const char *pPage=pRoot->Value();
	if(NULL==pPage)
	{
		DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因可能标签错误.");
		return NULL;
	}

	if(0==strcmp(pPage,"page"))
	{
		//处理子元素
		if(TRUE==XML_HandleChildEle(pRoot,hXmlRes,hParent,TRUE))
			return TRUE;
	}

	DebugBox(L"炫彩界面库-错误提示:加载XML文件失败,原因没有布局页标签[<page>]或其他错误.");
	return FALSE;
}



//	int  borderLeft; // 边框大小 +
//	int  borderTop;
//	int  borderRight;
//	int  borderBottom;

//	int  captionHeight; // 标题栏高度 +

//	BOOL bMinButton;    // 最小化按钮 +
//	BOOL bMaxButton;   // 最大化按钮 +
//	BOOL bCloseButton; // 关闭按钮 +
//	BOOL bCenter;     // 窗口居中 +
//	BOOL bRound;      //圆角 +
//	BOOL bDragBorder; //拖动边框 +
//	BOOL bDragWindow; //拖动窗口 +

HWINDOW XML_HandleWindow(TiXmlElement *pLabel,HXMLRES hXmlRes,HWND hWndParent)
{
	XTRACE("创建窗口\n");

	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);

	const char *borderLeft=pLabel->Attribute(STR_WIND_borderLeft);
	const char *borderTop=pLabel->Attribute(STR_WIND_borderTop);
	const char *borderRight=pLabel->Attribute(STR_WIND_borderRight);
	const char *borderBottom=pLabel->Attribute(STR_WIND_borderBottom);

	const char *captionHeight=pLabel->Attribute(STR_WIND_captionHeight);
	const char *bMinButton=pLabel->Attribute(STR_WIND_bMinButton);
	const char *bMaxButton=pLabel->Attribute(STR_WIND_bMaxButton);
	const char *bCloseButton=pLabel->Attribute(STR_WIND_bCloseButton);
	const char *bCenter=pLabel->Attribute(STR_WIND_bCenter);
	const char *bRound=pLabel->Attribute(STR_WIND_bRound);
	const char *bDragBorder=pLabel->Attribute(STR_WIND_bDragBorder);
	const char *bDragWindow=pLabel->Attribute(STR_WIND_bDragWindow);
	const char *value=pLabel->Attribute("value");

	int xcstyle= XC_SY_CAPTION | XC_SY_BORDER | XC_SY_DRAW_CAPTION_ICON | XC_SY_DRAW_CAPTION_TITLE;
	 
	if(bMinButton)
	{
		if(0==strcmp(bMinButton,"true"))
		{
			xcstyle|=XC_SY_MINIMIZE;
		}
	}else
		xcstyle|=XC_SY_MINIMIZE;
	
	if(bMaxButton)
	{
		if(0==strcmp(bMaxButton,"true"))
		{
			xcstyle|=XC_SY_MAXIMIZE;
		}
	}else
		xcstyle|=XC_SY_MAXIMIZE;

	if(bCloseButton)
	{
		if(0==strcmp(bCloseButton,"true"))
		{
			xcstyle|=XC_SY_CLOSE;
		}
	}else
		xcstyle|=XC_SY_CLOSE;

	if(bCenter)
	{
		if(0==strcmp(bCenter,"true"))
		{
			xcstyle|=XC_SY_CENTER;
		}
	}else
		xcstyle|=XC_SY_CENTER;

	if(bRound)
	{
		if(0==strcmp(bRound,"true"))
		{
			xcstyle|=XC_SY_ROUND;
		}
	}else
		xcstyle|=XC_SY_ROUND;

	if(bDragBorder)
	{
		if(0==strcmp(bDragBorder,"true"))
		{
			xcstyle|=XC_SY_DRAG_BORDER;
		}
	}else
		xcstyle|=XC_SY_DRAG_BORDER;

	if(bDragWindow)
	{
		if(0==strcmp(bDragWindow,"true"))
		{
			xcstyle|=XC_SY_DRAG_WINDOW;
		}
	}else
		xcstyle|=XC_SY_DRAG_WINDOW;

	HWINDOW hWindow=NULL;
	if(value)
	{
		wchar_t title[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);
		hWindow=XWnd_CreateWindow(left,top,width,height,title,hWndParent,xcstyle);
	}else
		hWindow=XWnd_CreateWindow(left,top,width,height,L"炫彩界面库-窗口标题",hWndParent,xcstyle);

	if(NULL==hWindow)
	{
		XTRACE("炫彩界面库-错误提示:创建窗口失败\n");
		return NULL;
	}

	if(borderLeft || borderTop || borderRight || borderBottom)
	{
		int iborderLeft=8;
		int iborderTop=8;
		int iborderRight=8;
		int iborderBottom=8;
		if(borderLeft) iborderLeft=atoi(borderLeft);
		if(borderTop) iborderTop=atoi(borderTop);
		if(borderRight) iborderRight=atoi(borderRight);
		if(borderBottom) iborderBottom=atoi(borderBottom);
		XWnd_SetBorderSize(hWindow,iborderLeft,iborderTop,iborderRight,iborderBottom);
	}

	if(captionHeight)
	{
		XWnd_SetCaptionHeight(hWindow,atoi(captionHeight));
	}

	//处理子元素
	if(FALSE==XML_HandleChildEle(pLabel,hXmlRes,hWindow,true))
		return NULL;

	return hWindow;
}

HWINDOW XML_HandleModalWindow(TiXmlElement *pLabel,HXMLRES hXmlRes,HWND hWndParent)
{
	int left=0;
	int top=0;
	int width=0;
	int height=0;

	//创建窗口pLabel...
	//XTRACE("创建模态窗口\n");

	GET_RECT(pLabel);

	HWINDOW hWindow=NULL;
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		wchar_t title[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);
		hWindow=XModalWnd_CreateWindow(width,height,title,hWndParent);
	}else
		hWindow=XModalWnd_CreateWindow(width,height,L"炫彩界面库-模态窗口标题",hWndParent);

	if(NULL==hWindow)
	{
		XTRACE("炫彩界面库-错误提示:创建模态窗口失败\n");
		return NULL;
	}
	//处理子元素
	if(FALSE==XML_HandleChildEle(pLabel,hXmlRes,hWindow,TRUE))
		return NULL;

	return hWindow;
}

HWINDOW XML_HandleFrameWindow(TiXmlElement *pLabel,HXMLRES hXmlRes,HWND hWndParent)
{
	int left=0;
	int top=0;
	int width=0;
	int height=0;

	GET_RECT(pLabel);

	HWINDOW hWindow=NULL;
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		wchar_t title[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);
		hWindow=XFrameWnd_CreateWindow(left,top,width,height,title,hWndParent);
	}else
		hWindow=XFrameWnd_CreateWindow(left,top,width,height,L"炫彩界面库-模态窗口标题",hWndParent);

	if(NULL==hWindow)
	{
		XTRACE("炫彩界面库-错误提示:创建模态窗口失败\n");
		return NULL;
	}
	//处理子元素
	if(FALSE==XML_HandleChildEle(pLabel,hXmlRes,hWindow,TRUE))
		return NULL;

	//处理窗格
	XML_HandlePanes( pLabel, hXmlRes, hWindow);

	return hWindow;
}

BOOL XML_HandlePanes(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//处理独立窗格
	TiXmlElement *p=pLabel->FirstChildElement("client");
	if(NULL==p)
		return TRUE;
	
	p=p->FirstChildElement("pane");

	const char *pValue=NULL;
	while(p)
	{
		pValue=p->Value();
		if(0==strcmp(pValue,"pane"))
		{
			XML_HandlePane(p,hWindow);
			XTRACE("pane \n");
		}else if(0==strcmp(pValue,"paneGroup"))
		{
			XML_HandlePaneGroup(p,hWindow);
		}
		p=p->NextSiblingElement();
	}

	//处理窗格组
	XFrameWnd_AdjustLayout(hWindow,TRUE);

	return TRUE;
}

BOOL XML_HandlePane(TiXmlElement *pLabel,HWINDOW hWindow)
{
	const char *pID=pLabel->Attribute("id");
	const char *pTitle=pLabel->Attribute("value");
	const char *pDestID=pLabel->Attribute("destID");
	const char *pAlign=pLabel->Attribute("align");
	const char *pProportion=pLabel->Attribute("proportion");
	const char *pBFixedSize=pLabel->Attribute("bFixedSize");

	int id=0;
	if(pID)
		id=atoi(pID);

	int destID=0;
	if(pDestID)
		destID=atoi(pDestID);

	HELE hDestPane=NULL;
	if(0!=destID)
		hDestPane=XWnd_GetEle(hWindow,destID);

	align_type_ align;
	if(0==strcmp(pAlign,"any"))
		align=align_any;
	if(0==strcmp(pAlign,"left"))
		align=align_left;
	if(0==strcmp(pAlign,"top"))
		align=align_top;
	if(0==strcmp(pAlign,"right"))
		align=align_right;
	if(0==strcmp(pAlign,"bottom"))
		align=align_bottom;

	int proportion=50;
	if(pProportion)
		proportion=atoi(pProportion);

	wchar_t titleW[MAX_PATH]={0};
	XC_AnsiToUnicode((char*)pTitle,strlen(pTitle),titleW,MAX_PATH);

	HELE hPane=XPane_Create(titleW,hWindow);
	XEle_SetId(hPane,id);
	if(pBFixedSize)
	{
		if(0==strcmp(pBFixedSize,"true"))
			XPane_SetFixedSize(hPane,TRUE);
	}

	return XFrameWnd_AddPane(hWindow,hDestPane,hPane,align,proportion);
}

//处理窗格组
BOOL XML_HandlePaneGroup(TiXmlElement *pLabel,HWINDOW hWindow)
{
	XTRACE("paneGroup \n");

	const char *pDestID=pLabel->Attribute("destID");
	const char *pAlign=pLabel->Attribute("align");

	int destID=0;
	if(pDestID)
		destID=atoi(pDestID);

	HELE hDestPane=NULL;
	if(0!=destID)
		hDestPane=XWnd_GetEle(hWindow,destID);

	align_type_ align;
	if(0==strcmp(pAlign,"any"))
		align=align_any;
	if(0==strcmp(pAlign,"left"))
		align=align_left;
	if(0==strcmp(pAlign,"top"))
		align=align_top;
	if(0==strcmp(pAlign,"right"))
		align=align_right;
	if(0==strcmp(pAlign,"bottom"))
		align=align_bottom;

	int index=0;
	HELE hNewPane=NULL;
	HPANE_GROUP hGroup=NULL;
	TiXmlElement *p=pLabel->FirstChildElement("pane");
	const char *pValue=NULL;
	while(p)
	{
		pValue=p->Value();
		if(0==strcmp(pValue,"pane"))
		{
			if(0==index)
			{
				hNewPane=XML_HandlePaneGroupMember1(p,hWindow,hDestPane,align);
			}else if(1==index)
			{
				hGroup=XML_HandlePaneGroupMember2(p,hWindow,hNewPane);
			}else
			{
				XML_HandlePaneGroupMember3(p,hWindow,hGroup);
			}
			index++;
		}
		p=p->NextSiblingElement();
	}
	return TRUE;
}

HELE XML_HandlePaneGroupMember1(TiXmlElement *pLabel,HWINDOW hWindow,HELE hDestPane,align_type_ align)
{
	const char *pID=pLabel->Attribute("id");
	const char *pTitle=pLabel->Attribute("value");
	const char *pProportion=pLabel->Attribute("proportion");
	const char *pBFixedSize=pLabel->Attribute("bFixedSize");

	int id=0;
	if(pID)
		id=atoi(pID);

	int proportion=50;
	if(pProportion)
		proportion=atoi(pProportion);

	wchar_t titleW[MAX_PATH]={0};
	XC_AnsiToUnicode((char*)pTitle,strlen(pTitle),titleW,MAX_PATH);

	HELE hPane=XPane_Create(titleW,hWindow);
	XEle_SetId(hPane,id);

	if(pBFixedSize)
	{
		if(0==strcmp(pBFixedSize,"true"))
			XPane_SetFixedSize(hPane,TRUE);
	}

	XFrameWnd_AddPane(hWindow,hDestPane,hPane,align,proportion);

	return hPane;
}
HPANE_GROUP XML_HandlePaneGroupMember2(TiXmlElement *pLabel,HWINDOW hWindow,HELE hDestPane)
{
	const char *pID=pLabel->Attribute("id");
	const char *pTitle=pLabel->Attribute("value");
	const char *pProportion=pLabel->Attribute("proportion");
	const char *pBFixedSize=pLabel->Attribute("bFixedSize");

	int id=0;
	if(pID)
		id=atoi(pID);

	int proportion=50;
	if(pProportion)
		proportion=atoi(pProportion);

	wchar_t titleW[MAX_PATH]={0};
	XC_AnsiToUnicode((char*)pTitle,strlen(pTitle),titleW,MAX_PATH);

	HELE hPane=XPane_Create(titleW,hWindow);
	XEle_SetId(hPane,id);

	if(pBFixedSize)
	{
		if(0==strcmp(pBFixedSize,"true"))
			XPane_SetFixedSize(hPane,TRUE);
	}

	return XFrameWnd_MergePane(hWindow,hDestPane,hPane,proportion);
}

BOOL XML_HandlePaneGroupMember3(TiXmlElement *pLabel,HWINDOW hWindow,HPANE_GROUP hGroup)
{
	const char *pID=pLabel->Attribute("id");
	const char *pTitle=pLabel->Attribute("value");
	const char *pProportion=pLabel->Attribute("proportion");
	const char *pBFixedSize=pLabel->Attribute("bFixedSize");

	int id=0;
	if(pID)
		id=atoi(pID);

	int proportion=50;
	if(pProportion)
		proportion=atoi(pProportion);

	wchar_t titleW[MAX_PATH]={0};
	XC_AnsiToUnicode((char*)pTitle,strlen(pTitle),titleW,MAX_PATH);

	HELE hPane=XPane_Create(titleW,hWindow);
	XEle_SetId(hPane,id);

	if(pBFixedSize)
	{
		if(0==strcmp(pBFixedSize,"true"))
			XPane_SetFixedSize(hPane,TRUE);
	}

	return XFrameWnd_MergePaneToGroup(hWindow,hGroup,hPane,proportion);
}

BOOL XML_HandleChildEle(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	//第一个子元素
	TiXmlElement *pFirstNode=pLabel->FirstChildElement();
	if(NULL==pFirstNode)
		return TRUE; //没有元素

	//处理第一个子元素,分类处理
	if(FALSE==XML_SwitchEle(pFirstNode,hXmlRes,hParent,bClient))
		return FALSE;

	//循环处理子元素直到当前层的最后一个
	TiXmlElement *pSibing=pFirstNode;
	while(1)
	{
		pSibing=pSibing->NextSiblingElement();
		if(pSibing)
		{
			//处理下一个子元素,分类处理
			if(FALSE==XML_SwitchEle(pSibing,hXmlRes,hParent,bClient))
				return FALSE;
		}else
			break;
	}
	return TRUE;
}

//子元素分类处理
BOOL XML_SwitchEle(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	const char *pEleName=pLabel->Value();
	if(pEleName)
	{
		HELE hEle=NULL;
		if(0==strcmp(pEleName,"element"))
		{	
			hEle=XML_CreateEle(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"button"))
		{
			hEle=XML_CreateButton(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"radio"))
		{
			hEle=XML_CreateRadio(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"check"))
		{
			hEle=XML_CreateCheck(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"edit"))
		{
			hEle=XML_CreateEdit(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"comboBox"))
		{
			hEle=XML_CreateComboBox(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"scrollBar"))
		{
			hEle=XML_CreateScrollBar(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"scrollView"))
		{
			hEle=XML_CreateScrollView(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"list"))
		{
			hEle=XML_CreateList(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"listBox"))
		{
			hEle=XML_CreateListBox(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"tree"))
		{
			hEle=XML_CreateTree(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"menuBar"))
		{
			hEle=XML_CreateMenuBar(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"propertyPage"))
		{
			hEle=XML_CreatePPage(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"sliderBar"))
		{
			hEle=XML_CreateSlider(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"progressBar"))
		{
			hEle=XML_CreateProgressBar(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"toolBar"))
		{
			hEle=XML_CreateToolBar(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"static"))
		{
			hEle=XML_CreateStatic(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"groupBox"))
		{
			hEle=XML_CreateGroupBox(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"picture"))
		{
			hEle=XML_CreatePicture(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"monthCal"))
		{
			hEle=XML_CreateMonthCal(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"dateTime"))
		{
			hEle=XML_CreateDateTime(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"PGrid"))
		{
			hEle=XML_CreatePGrid(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"chooseColor"))
		{
			hEle=XML_CreateChooseColor(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"propertyPageLabel"))
		{
			hEle=XML_CreatePropertyPageLabel(pLabel,hXmlRes,hParent,bClient);
			if(hEle)
				return XML_HandleChildEle(pLabel->FirstChildElement(),hXmlRes,hEle,bClient);
			else
				return FALSE;
		}else if(0==strcmp(pEleName,"NCClient"))
		{
			return XML_HandleChildEle(pLabel,hXmlRes,hParent,FALSE);
		}else if(0==strcmp(pEleName,"client"))
		{
			return XML_HandleChildEle(pLabel,hXmlRes,hParent,TRUE);
		}else if(0==strcmp(pEleName,"reference"))
		{
			return TRUE;
		}else if(0==strcmp(pEleName,"pane"))
		{
		}else if(0==strcmp(pEleName,"paneGroup"))
		{
		}else
		{
			XTRACE("炫彩界面库-错误提示:错误标签\n");
			return FALSE;
		}
	}
	return TRUE;
};

int XML_GetEleId(TiXmlElement *pLabel,HXMLRES hXmlRes)
{
	const char *pID=pLabel->Attribute("id");
	if('@'==pID[0])		//从资源中查找ID
	{
		if(NULL==hXmlRes) return 0;

		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)(&pID[1]),-1,temp,MAX_PATH);
		return XXmlRes_FindId(hXmlRes,temp);
	}else
	{
		return atoi(pID);
	}
}

///////创建元素///////////////////////////////////////////////////////
HELE XML_CreateEle(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	//创建元素...
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);

	HELE hEle=XEle_Create(left,top,width,height);
	if(XC_IsHWINDOW((HWINDOW)hParent))
	{
		if(bClient)
		{
			//hEle=XEle_Create(left,top,width,height,hParent);
			XWnd_AddEle((HWINDOW)hParent,hEle);
		}else
		{		
			XWnd_AddEleNC((HWINDOW)hParent,hEle);
		}
	}else
	{
		hEle=XEle_Create(left,top,width,height,hParent);
	}

	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Element失败\n");
		return NULL;
	}
	id=XML_GetEleId(pLabel,hXmlRes);

	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;

	//处理子元素
	//return XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient);
}


HELE XML_CreateButton(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);

	const char *value=pLabel->Attribute("value");
	const char *tooltips=pLabel->Attribute("tooltips");

	wchar_t title[MAX_PATH]={0};
	if(value)
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);

	HELE hEle=XBtn_Create(left,top,width,height,title,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Button失败\n");
		return NULL;
	}
	id=XML_GetEleId(pLabel,hXmlRes);
	XEle_SetId(hEle,id);
	if(tooltips)
	{
		wchar_t wtooltips[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,tooltips,-1,wtooltips,MAX_PATH);
		XEle_EnableToolTips(hEle,TRUE);
		XEle_SetToolTips(hEle,wtooltips);
	}

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateRadio(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);

	const char *value=pLabel->Attribute("value");

	wchar_t title[MAX_PATH]={0};
	if(value)
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);

	HELE hEle=XRadio_Create(left,top,width,height,title,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Radio失败\n");
		return NULL;
	}
	id=XML_GetEleId(pLabel,hXmlRes);
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateCheck(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	const char *value=pLabel->Attribute("value");

	wchar_t title[MAX_PATH]={0};
	if(value)
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);

	HELE hEle=XCheck_Create(left,top,width,height,title,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Check失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateEdit(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	const char *value=pLabel->Attribute("value");

	HELE hEle=XEdit_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Edit失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);
	if(value)
	{
		int len=strlen(value);
		wchar_t *pText=(wchar_t*)malloc((len+1)*sizeof(wchar_t));
		pText[len]=0;
		MultiByteToWideChar(CP_ACP,0,value,-1,pText,len);
		XEdit_SetText(hEle,pText);
		free((void*)pText);
	}

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateComboBox(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	HELE hEle=XComboBox_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建comboBox失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateScrollBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	BOOL bHorizon=TRUE;
	const char *pBHorizon=pLabel->Attribute(STRA_bHorizon);
	if(pBHorizon)
	{
		if(0==strcmp(pBHorizon,"FALSE"))
			bHorizon=FALSE;
	}

	HELE hEle=XSBar_Create(left,top,width,height,bHorizon,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建scrollBar失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateScrollView(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	HELE hEle=XSView_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建scrollView失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateList(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	HELE hEle=XList_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建list失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateListBox(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);

	HELE hEle=XListBox_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建ListBox失败\n");
		return NULL;
	}
	id=XML_GetEleId(pLabel,hXmlRes);
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateTree(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);

	HELE hEle=XTree_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Tree失败\n");
		return NULL;
	}
	id=XML_GetEleId(pLabel,hXmlRes);
	XEle_SetId(hEle,id);

	return hEle;
}

HELE XML_CreateMenuBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	HELE hEle=NULL;
	if(FALSE==bClient)
	{
		hEle=XMenuBar_Create(left,top,width,height,hParent);
	}else
	{
		hEle=XMenuBar_Create(left,top,width,height);
		XWnd_AddEle((HWINDOW)hParent,hEle);
	}

	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建MenuBar失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreatePPage(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	HELE hEle=XPPage_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	const char *labelHeight=pLabel->Attribute(STRA_labelHeight);
	if(labelHeight)
	{
		int h=atoi(labelHeight);
		XPPage_SetLabelHeight(hEle,h);
	}
	const char *labelSpacing=pLabel->Attribute(STRA_labelSpacing);
	if(labelSpacing)
	{
		int s=atoi(labelSpacing);
		XPPage_SetLabelSpacing(hEle,s);
	}
	const char *bScrollButton=pLabel->Attribute(STRA_bScrollButton);
	if(bScrollButton)
	{
		if(0==strcmp(bScrollButton,"FALSE"))
			XPPage_EnableScrollButton(hEle,FALSE);
	}

	return hEle;
}

HELE XML_CreateSlider(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	BOOL bHorizon=TRUE;
	const char *pBHorizon=pLabel->Attribute(STRA_bHorizon);
	if(pBHorizon)
	{
		if(0==strcmp(pBHorizon,"FALSE"))
			bHorizon=FALSE;
	}

	HELE hEle=XSliderBar_Create(left,top,width,height,bHorizon,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建sliderBar失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateProgressBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	BOOL bHorizon=TRUE;
	const char *pBHorizon=pLabel->Attribute(STRA_bHorizon);
	if(pBHorizon)
	{
		if(0==strcmp(pBHorizon,"FALSE"))
			bHorizon=FALSE;
	}

	HELE hEle=XProgBar_Create(left,top,width,height,bHorizon,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建progressBar失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateToolBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	HELE hEle=NULL;
	if(FALSE==bClient)
	{
		hEle=XToolBar_Create(left,top,width,height,hParent);
	}else
	{
		hEle=XToolBar_Create(left,top,width,height);
		XWnd_AddEle((HWINDOW)hParent,hEle);
	}

	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建ToolBar失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateStatic(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	const char *value=pLabel->Attribute("value");
	wchar_t title[MAX_PATH]={0};
	if(value)
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);

	HELE hEle=XStatic_Create(left,top,width,height,title,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建Static失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateGroupBox(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	const char *value=pLabel->Attribute("value");
	wchar_t title[MAX_PATH]={0};
	if(value)
		MultiByteToWideChar(CP_ACP,0,value,-1,title,MAX_PATH);

	HELE hEle=XGBox_Create(left,top,width,height,title,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建groupBox失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreatePicture(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);

	HELE hEle=XPic_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建picture失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateMonthCal(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	HELE hEle=XMonthCal_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建monthCal失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateDateTime(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	HELE hEle=XDateTime_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建dateTime失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreatePGrid(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	HELE hEle=XPGrid_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建PropertyGrid失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}

HELE XML_CreateChooseColor(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	HELE hEle=XCHColor_Create(left,top,width,height,hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建chooseColor失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}


int XML_CheckPropertyPage(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient) //检查是否为属性页元素子页
{
	//检查是否为属性页标签
	if(XC_PROPERTYPAGE==XC_GetObjectType(hParent))
	{
		TiXmlElement  *pLabelObject=pLabel;//标签

		int   LabelId=0;
		LabelId=XML_GetEleId(pLabel,hXmlRes);
		const char *pLabelName=pLabel->Attribute("value"); //标签名
		wchar_t  pWLabelName[MAX_PATH]={0};
		if(pLabelName)
			MultiByteToWideChar(CP_ACP,0,pLabelName,-1,pWLabelName,MAX_PATH);

		//子页面
		pLabel=pLabel->FirstChildElement();
		const char *pValue=pLabel->Value();
		int id=XML_GetEleId(pLabel,hXmlRes);

		HELE hEle;
		if(0==strcmp(pValue,"element"))
		{
			hEle=XEle_Create(0,0,10,10);

		}else if(0==strcmp(pValue,"scrollView"))
		{
			hEle=XSView_Create(0,0,10,10);
		}
		else  if(0==strcmp(pValue,"list"))
		{
			hEle=XList_Create(0,0,10,10);
		}
		else if(0==strcmp(pValue,"listBox"))
		{
			hEle=XListBox_Create(0,0,10,10);
		}
		else if(0==strcmp(pValue,"tree"))
		{
			hEle=XTree_Create(0,0,10,10);
		}
		else if(0==strcmp(pValue,"edit"))
		{
			hEle=XEdit_Create(0,0,10,10);
		}
		else
		{
			XTRACE("错误的属性页\n");
			return -1;
		}

		int index=XPPage_AddLabel((HELE)hParent,pWLabelName,hEle);
		HELE hLabel=XPPage_GetLabel((HELE)hParent,index);
		if(NULL==hLabel) return -1;

		if(FALSE==XML_HandleChildEle(pLabel,hXmlRes,hEle,bClient))
			return -1;
		return 1;
	}
	
	return 0;
}

HELE XML_CreatePropertyPageLabel(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	//检查是否为属性页标签
	if(XC_PROPERTYPAGE!=XC_GetObjectType(hParent)) return NULL;

	//属性页子页面 -创建子页面元素
	TiXmlElement *pLabelPage=pLabel->FirstChildElement();
	HELE hElePage;
	{
		const char *pValue=pLabelPage->Value();
		int id=XML_GetEleId(pLabelPage,hXmlRes);

		if(0==strcmp(pValue,"element"))
		{
			hElePage=XML_CreateEle(pLabelPage,hXmlRes,NULL,bClient);
		}else if(0==strcmp(pValue,"scrollView"))
		{
			hElePage=XML_CreateScrollView(pLabelPage,hXmlRes,NULL,bClient);
		}else  if(0==strcmp(pValue,"list"))
		{
			hElePage=XML_CreateList(pLabelPage,hXmlRes,NULL,bClient);
		}else if(0==strcmp(pValue,"listBox"))
		{
			hElePage=XML_CreateListBox(pLabelPage,hXmlRes,NULL,bClient);
		}else if(0==strcmp(pValue,"tree"))
		{
			hElePage=XML_CreateTree(pLabelPage,hXmlRes,NULL,bClient);
		}else if(0==strcmp(pValue,"edit"))
		{
			hElePage=XML_CreateEdit(pLabelPage,hXmlRes,NULL,bClient);
		}else if(0==strcmp(pValue,"picture"))
		{
			hElePage=XML_CreatePicture(pLabelPage,hXmlRes,NULL,bClient);
		}else
		{
			XTRACE("错误的属性页\n");
			return NULL;
		}
	}

	{
		if(NULL==hElePage) return NULL;

		//标签按钮名称
		wchar_t  pWLabelName[MAX_PATH]={0};
		{
			TiXmlElement  *pLabelObject=pLabel;//标签

			int   LabelId=0;
			LabelId=XML_GetEleId(pLabel,hXmlRes);
			const char *pLabelName=pLabel->Attribute("value"); //标签名
			if(pLabelName)
				MultiByteToWideChar(CP_ACP,0,pLabelName,-1,pWLabelName,MAX_PATH);
		}

		int index=XPPage_AddLabel((HELE)hParent,pWLabelName,hElePage);
		HELE hLabel=XPPage_GetLabel((HELE)hParent,index);
		if(NULL==hLabel) return NULL;

		int id=0;
		const char *tooltips=pLabel->Attribute("tooltips");
		id=XML_GetEleId(pLabel,hXmlRes);
		XEle_SetId(hLabel,id);

		if(tooltips)
		{
			wchar_t wtooltips[MAX_PATH]={0};
			MultiByteToWideChar(CP_ACP,0,tooltips,-1,wtooltips,MAX_PATH);
			XEle_EnableToolTips(hLabel,TRUE);
			XEle_SetToolTips(hLabel,wtooltips);
		}

		const char *pClass=pLabel->Attribute("styleClass");
		if(pClass) //套用样式
		{
			wchar_t temp[MAX_PATH]={0};
			XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
			if(NULL==((ele_*)hLabel)->hString_Style_Class)
				((ele_*)hLabel)->hString_Style_Class=XStr_Create();
			XStr_SetString(((ele_*)hLabel)->hString_Style_Class,temp);
		}

		const char *labelWidth=pLabel->Attribute(STRA_labelWidth);
		if(labelWidth)
		{
			int w=atoi(labelWidth);
			XPPage_SetLabelWidth((HELE)hParent,index,w);
		}
	}

	return hElePage;
}

HELE XML_CreatePane(TiXmlElement *pLabel,HXMLRES hXmlRes,HXCGUI hParent,BOOL bClient)
{
	int id=0;
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	GET_RECT(pLabel);
	id=XML_GetEleId(pLabel,hXmlRes);
	HELE hEle=XPane_Create(L"123",(HWINDOW)hParent);
	if(NULL==hEle)
	{
		XTRACE("炫彩界面库-错误提示:创建PropertyGrid失败\n");
		return NULL;
	}
	XEle_SetId(hEle,id);

	const char *pClass=pLabel->Attribute("styleClass");
	if(pClass) //套用样式
	{
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClass,-1,temp,MAX_PATH);
		if(NULL==((ele_*)hEle)->hString_Style_Class)
			((ele_*)hEle)->hString_Style_Class=XStr_Create();
		XStr_SetString(((ele_*)hEle)->hString_Style_Class,temp);
	}
	return hEle;
}



////////////处理样式表///////////////////////////////////////////////////////

///@defgroup groupStyle 样式文件API
///@ingroup  groupGuiDesigner
///


///@addtogroup groupStyle
///@{

///@brief 加载窗口样式文件,改变窗口及UI元素外观.
///@param hWindow    窗口句柄.
///@param pFileName  样式文件名.
///@param hXmlRes    资源文件句柄,如果没有为NULL.
///@return 如果成功返回TRUE,否则相反.
BOOL WINAPI XC_LoadXML_Style(HWINDOW hWindow,wchar_t *pFileName,HXMLRES hXmlRes)
{
	IsWindowDebug(hWindow,__FUNCTION__);

	if(NULL==pFileName)
	{
		XTRACE("炫彩界面库-错误提示:加载样式表文件失败,文件路径不能为空\n");
		return NULL;
	}

	char file[MAX_PATH]={0};
	if(0==WideCharToMultiByte(CP_ACP,NULL,pFileName,wcslen(pFileName),file,MAX_PATH,NULL,NULL))
	{
		XTRACE("炫彩界面库-错误提示:加载样式表文件失败,原因可能文件路径太长或字符编码错误\n");
		return NULL;
	}

	TiXmlDocument xmlDoc(file);
	if(FALSE==xmlDoc.LoadFile())
	{
		XTRACE("炫彩界面库-错误提示:加载样式表文件失败,文件路径错误\n");
		return NULL;
	}
	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		XTRACE("炫彩界面库-错误提示:加载样式表文件失败,原因可能标签错误\n");
		return NULL;
	}

	const char *pWindow=pRoot->Value();
	if(NULL==pWindow)
	{
		XTRACE("炫彩界面库-错误提示:加载样式表文件失败,原因可能标签错误\n");
		return NULL;
	}

	if(0==strcmp(pWindow,"style"))
	{
		return CSS_Handle_X(pRoot,hXmlRes,hWindow);
	}
	XTRACE("炫彩界面库-错误提示:加载样式表文件失败,原因没有标签[<style>]\n");
	return FALSE;
}

///@brief 加载窗口样式文件,改变窗口及UI元素外观.
///@param hWindow    窗口句柄.
///@param resID  资源ID.
///@param pType  资源类型.
///@param hXmlRes    资源文件句柄,如果没有为NULL.
///@return 如果成功返回TRUE,否则相反.
BOOL WINAPI XC_LoadXML_StyleRes(HWINDOW hWindow,int resID,wchar_t *pType,HXMLRES hXmlRes) //从资源加载
{
	IsWindowDebug(hWindow,__FUNCTION__);

	HMODULE hInst=NULL;
	if(g_resourcesModule)
		hInst=g_resourcesModule;
	else
		hInst=GetModuleHandle(NULL);

	if(NULL==hInst) return FALSE;

	LPCTSTR lpRes=MAKEINTRESOURCE(resID);
	HRSRC   hRsrc=::FindResource(hInst,lpRes,pType);
	if(NULL==hRsrc) return FALSE;
	HGLOBAL hGlobal=LoadResource(hInst,hRsrc);
	if(NULL==hGlobal) return FALSE;
	DWORD   dwSize   =SizeofResource(hInst,hRsrc);

	BOOL bRes=FALSE;
	if(dwSize>0)
	{
		LPVOID   lpData  =LockResource(hGlobal);
		if(lpData)
		{
			char *pData=(char*)malloc(dwSize+1);
			if(pData)
			{
				memcpy(pData,lpData,dwSize);
				pData[dwSize]=0;
				bRes=XC_LoadXML_StyleRes2(pData,hXmlRes,hWindow);
				free(pData);
			}
		}
	}

	BOOL hrr=FreeResource(hGlobal);
	return bRes;
}

BOOL XC_LoadXML_StyleRes2(char *pData,HXMLRES hXmlRes,HWINDOW hWindow)
{
	TiXmlDocument xmlDoc;
	if(NULL==xmlDoc.Parse(pData))
	{
		DebugBox(L"炫彩界面库-错误提示:加载样式表文件失败.");
		return FALSE;
	}

	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		DebugBox(L"炫彩界面库-错误提示:加载样式表文件失败,原因可能标签错误.");
		return FALSE;
	}

	return CSS_Handle_X(pRoot,hXmlRes,hWindow);
}

///@}

BOOL CSS_Handle_X(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//第一个子元素
	TiXmlElement *pFirstNode=pLabel->FirstChildElement();
	if(NULL==pFirstNode)
		return TRUE; //没有元素

	//处理第一个子元素,分类处理
	if(FALSE==CSS_Switch(pFirstNode,hXmlRes,hWindow))
		return FALSE;

	//循环处理子元素直到当前层的最后一个
	TiXmlElement *pSibing=pFirstNode;
	while(1)
	{
		pSibing=pSibing->NextSiblingElement();
		if(pSibing)
		{
			//处理下一个子元素,分类处理
			if(FALSE==CSS_Switch(pSibing,hXmlRes,hWindow))
				return FALSE;
		}else
			break;
	}

	return TRUE;
}

BOOL CSS_Switch(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	const char *pEleName=pLabel->Value();
	if(NULL==pEleName) return FALSE;
	
	if(0==strcmp(pEleName,"element"))
	{
		if(FALSE==CSS_HandleEle(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"button"))
	{
		if(FALSE==CSS_HandleButton(pLabel,hXmlRes,hWindow))
			return FALSE;;
	}else if(0==strcmp(pEleName,"radio"))
	{
		if(FALSE==CSS_HandleRadio(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"check"))
	{
		if(FALSE==CSS_HandleCheck(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"edit"))
	{
		if(FALSE==CSS_HandleEdit(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"comboBox"))
	{
		if(FALSE==CSS_HandleComboBox(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"scrollBar"))
	{
		if(FALSE==CSS_HandleScrollBar(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"scrollView"))
	{
		if(FALSE==CSS_HandleScrollView(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"list"))
	{
		if(FALSE==CSS_HandleList(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"listBox"))
	{
		if(FALSE==CSS_HandleListBox(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"tree"))
	{
		if(FALSE==CSS_HandleTree(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"menuBar"))
	{
		if(FALSE==CSS_HandleMenuBar(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"propertyPage"))
	{
		if(FALSE==CSS_HandlePropertyPage(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"sliderBar"))
	{
		if(FALSE==CSS_HandleSliderBar(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"progressBar"))
	{
		if(FALSE==CSS_HandleProgressBar(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"toolBar"))
	{
		if(FALSE==CSS_HandleToolBar(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"static"))
	{
		if(FALSE==CSS_HandleStatic(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"groupBox"))
	{
		if(FALSE==CSS_HandleGroupBox(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"picture"))
	{
		if(FALSE==CSS_HandlePicture(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"monthCal"))
	{
		if(FALSE==CSS_HandleMonthCal(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"dateTime"))
	{
		if(FALSE==CSS_HandleDateTime(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"PGrid"))
	{
		if(FALSE==CSS_HandlePGrid(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"chooseColor"))
	{
		if(FALSE==CSS_HandleChooseColor(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"propertyPageLabel")) 
	{
		if(FALSE==CSS_HandlePropertyPageLabel(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"window"))
	{
		if(FALSE==CSS_HandleWindow(pLabel,hXmlRes,hWindow))
			return FALSE;
	}else if(0==strcmp(pEleName,"reference"))
	{
		return TRUE;
	}else
	{
		XTRACE("炫彩界面库-错误提示:错误标签\n");
		return FALSE;
	}
	return TRUE;
}


BOOL CSS_HandleWindow(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	if(pLabel->Attribute(STR_WIND_left,&left) &&pLabel->Attribute(STR_WIND_top,&top) &&
		pLabel->Attribute(STR_WIND_width,&width) &&pLabel->Attribute(STR_WIND_height,&height))
	{
		RECT rect={left,top,left+width,top+height};
		HWND hWnd=XWnd_GetHWnd(hWindow);
		SetWindowPos(hWnd,NULL,left,top,width,height,SWP_NOZORDER | SWP_NOACTIVATE);
	}
	//bkColor
	const char *pColor=pLabel->Attribute(STR_WIND_bkColor);
	if(pColor)
	{
		if(7==strlen(pColor)) //#ff00ff
		{
			wchar_t text[7]={0};
			text[0]=pColor[5];
			text[1]=pColor[6];
			text[2]=pColor[3];
			text[3]=pColor[4];
			text[4]=pColor[1];
			text[5]=pColor[2];
			text[6]=0;
			COLORREF bkColor=XC_HexToDec(text);

			XWnd_SetBkColor(hWindow,bkColor);
		}
	}

	const char *bMinButton=pLabel->Attribute(STR_WIND_bMinButton);
	if(bMinButton)
	{
		if(0==strcmp(bMinButton,"true"))
			XWnd_EnableMinButton(hWindow,TRUE);
		else
			XWnd_EnableMinButton(hWindow,FALSE);
	}

	const char *bMaxButton=pLabel->Attribute(STR_WIND_bMaxButton);
	if(bMaxButton)
	{
		if(0==strcmp(bMaxButton,"true"))
			XWnd_EnableMaxButton(hWindow,TRUE);
		else
			XWnd_EnableMaxButton(hWindow,FALSE);
	}

	const char *bCloseButton=pLabel->Attribute(STR_WIND_bCloseButton);
	if(bCloseButton)
	{
		if(0==strcmp(bCloseButton,"true"))
			XWnd_EnableCloseButton(hWindow,TRUE);
		else
			XWnd_EnableCloseButton(hWindow,FALSE);
	}

	const char *bRound=pLabel->Attribute(STR_WIND_bRound);
	if(bRound)
	{
		if(0==strcmp(bRound,"true"))
			XWnd_EnableRound(hWindow,TRUE);
		else
			XWnd_EnableRound(hWindow,FALSE);
	}

	int captionHeight=0;
	if(pLabel->Attribute(STR_WIND_captionHeight,&captionHeight))
	{
		XWnd_SetCaptionHeight(hWindow,captionHeight);
	}

	int minWidth=0;
	if(pLabel->Attribute(STR_WIND_minWidth,&minWidth))
	{
		XWnd_SetMinWidth(hWindow,minWidth);
	}

	int minHeight=0;
	if(pLabel->Attribute(STR_WIND_minHeight,&minHeight))
	{
		XWnd_SetMinWidth(hWindow,minHeight);
	}

	int   borderLeft=0;     //边框大小
	int   borderTop=0;      //边框大小
	int   borderRight=0;    //边框大小
	int   borderBottom=0;   //边框大小
	if(pLabel->Attribute("borderLeft",&borderLeft) &&pLabel->Attribute("borderTop",&borderTop) &&
		pLabel->Attribute("borderRight",&borderRight) &&pLabel->Attribute("borderBottom",&borderBottom))
	{
		XWnd_SetBorderSize(hWindow,borderLeft,borderTop,borderRight,borderBottom);
	}

	const char *bDragBorder=pLabel->Attribute("bDragBorder");
	if(bDragBorder)
	{
		if(0==strcmp(bDragBorder,"true"))
			XWnd_EnableDragBorder(hWindow,TRUE);
		else
			XWnd_EnableDragBorder(hWindow,FALSE);
	}

	const char *bDragWindow=pLabel->Attribute("bDragWindow");
	if(bDragWindow)
	{
		if(0==strcmp(bDragWindow,"true"))
			XWnd_EnableDragWindow(hWindow,TRUE);
		else
			XWnd_EnableDragWindow(hWindow,FALSE);
	}

	const char *value=pLabel->Attribute("value");
	if(value)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH-1);

		XWnd_SetWindowText(hWindow,temp);
	}

	const char *image=pLabel->Attribute("image");
	if(image)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,image,-1,temp,MAX_PATH-1);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			XXmlRes_FildHIMAGE(hXmlRes,temp);
		else
			hImage=XImage_LoadFile(temp);

		if(hImage)
			XWnd_SetImage(hWindow,hImage);
	}

	const char *imageNC=pLabel->Attribute("imageNC");
	if(imageNC)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,imageNC,-1,temp,MAX_PATH-1);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);

		if(hImage)
			XWnd_SetImageNC(hWindow,hImage);
	}
	const char *image_caption=pLabel->Attribute("image_caption");
	if(image_caption)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,image_caption,-1,temp,MAX_PATH-1);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);

		if(hImage)
			XWnd_SetImageCaption(hWindow,hImage);
	}
	const char *image_left=pLabel->Attribute("image_left");
	if(image_left)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,image_left,-1,temp,MAX_PATH-1);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);

		if(hImage)
			XWnd_SetImageBorderLeft(hWindow,hImage);
	}

	const char *image_right=pLabel->Attribute("image_right");
	if(image_right)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,image_right,-1,temp,MAX_PATH-1);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);

		if(hImage)
			XWnd_SetImageBorderRight(hWindow,hImage);
	}
	const char *image_bottom=pLabel->Attribute("image_bottom");
	if(image_bottom)
	{
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,image_bottom,-1,temp,MAX_PATH-1);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);

		if(hImage)
			XWnd_SetImageBorderBottom(hWindow,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleBase(TiXmlElement *pLabel,HELE hEle)
{
	int left=0;
	int top=0;
	int width=0;
	int height=0;
	if(pLabel->Attribute("left",&left) &&pLabel->Attribute("top",&top) &&
		pLabel->Attribute("width",&width) &&pLabel->Attribute("height",&height))
	{
		RECT rect={left,top,left+width,top+height};
		XEle_SetRect(hEle,&rect);
	}

	const char *bFocus=pLabel->Attribute("bFocus");
	if(bFocus)
	{
		if(0==strcmp(bFocus,"true"))
			XEle_EnableFocus(hEle,TRUE);
		else
			XEle_EnableFocus(hEle,FALSE);
	}

	const char *bTransparent=pLabel->Attribute("bTransparent");
	if(bTransparent) 
	{
		if(0==strcmp(bTransparent,"true"))
			XEle_SetBkTransparent(hEle,TRUE);
		else
			XEle_SetBkTransparent(hEle,FALSE);
	}

	const char *bBorder=pLabel->Attribute("bBorder");
	if(bBorder) 
	{
		if(0==strcmp(bBorder,"true"))
			XEle_EnableBorder(hEle,TRUE);
		else
			XEle_EnableBorder(hEle,FALSE);
	}

	//bkColor
	const char *pColor=pLabel->Attribute(STRA_bkColor);
	if(pColor)
	{
		if(7==strlen(pColor)) //#ff00ff
		{
			wchar_t text[7]={0};
			text[0]=pColor[5];
			text[1]=pColor[6];
			text[2]=pColor[3];
			text[3]=pColor[4];
			text[4]=pColor[1];
			text[5]=pColor[2];
			text[6]=0;
			COLORREF color=XC_HexToDec(text);
			XEle_SetBkColor(hEle,color);
		}
	}

	//textColor
	const char *textColor=pLabel->Attribute(STRA_textColor);
	if(textColor)
	{
		if(7==strlen(textColor)) //#ff00ff
		{
			wchar_t text[7]={0};
			text[0]=textColor[5];
			text[1]=textColor[6];
			text[2]=textColor[3];
			text[3]=textColor[4];
			text[4]=textColor[1];
			text[5]=textColor[2];
			text[6]=0;
			COLORREF color=XC_HexToDec(text);
			XEle_SetTextColor(hEle,color);
		}
	}
	
	const char *tooltips=pLabel->Attribute("tooltips");
	if(tooltips)
	{	
		wchar_t temp[MAX_PATH]={0};
		MultiByteToWideChar(CP_ACP,0,tooltips,-1,temp,MAX_PATH-1);

		XEle_EnableToolTips(hEle,TRUE);
		XEle_SetToolTips(hEle,temp);
	}
	return TRUE;
}

#define  CSS_HANDLE_ALL(eleType,fun_) \
		resources_window_ *pWindow=GetResourceWindow(hWindow);\
		if(pWindow)\
		{\
			int count2=XArray_GetCount(pWindow->hArrayEle_List);\
			for(int i=0;i<count2;i++)\
			{\
				HELE hEle=(HELE)XArray_GetAt(pWindow->hArrayEle_List,i);\
				if(eleType==XC_GetObjectType(hEle))\
				{\
					if(FALSE==fun_(pLabel,hXmlRes,hWindow,hEle))\
						return FALSE;\
				}\
			}\
		}

#define  CSS_HANDLE_CLASS(eleType,fun_) \
		const char *pClassName=pLabel->Attribute("name");\
		if(NULL==pClassName) return FALSE;\
		wchar_t temp[MAX_PATH]={0};\
		XC_AnsiToUnicode((char*)pClassName,-1,temp,MAX_PATH);\
		resources_window_ *pWindow=GetResourceWindow(hWindow);\
		if(pWindow)\
		{\
			int count2=XArray_GetCount(pWindow->hArrayEle_List);\
			for(int i=0;i<count2;i++)\
			{\
				HELE hEle=(HELE)XArray_GetAt(pWindow->hArrayEle_List,i);\
				if(eleType==XC_GetObjectType(hEle))\
				{\
					HSTRING hString=((ele_*)hEle)->hString_Style_Class;\
					if(hString)\
					{\
						if(0==wcscmp(temp,XStr_GetBuffer(hString)))\
						{\
							if(FALSE==fun_(pLabel,hXmlRes,hWindow,(HELE)XArray_GetAt(pWindow->hArrayEle_List,i)))\
								return FALSE;\
						}\
					}\
				}\
			}\
		}


BOOL CSS_HandleEle(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_ELE,CSS_HandleEle2);
	/*	resources_window_ *pWindow=GetResourceWindow(hWindow);
		if(pWindow)
		{
			int count2=XArray_GetCount(pWindow->hArrayEle_List);
			for(int i=0;i<count2;i++)
			{
				HELE hEle=(HELE)XArray_GetAt(pWindow->hArrayEle_List,i);
				if(XC_ELE==XC_GetObjectType(hEle))
				{
					if(FALSE==CSS_HandleEle2(pLabel,hXmlRes,hWindow,hEle))
						return FALSE;
				}
			}
		}*/
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_ELE,CSS_HandleEle2);
	/*	const char *pClassName=pLabel->Attribute("name");
		wchar_t temp[MAX_PATH]={0};
		XC_AnsiToUnicode((char*)pClassName,-1,temp,MAX_PATH);
		resources_window_ *pWindow=GetResourceWindow(hWindow);
		if(pWindow)
		{
			int count2=XArray_GetCount(pWindow->hArrayEle_List);
			for(int i=0;i<count2;i++)
			{
				//检查元素套用样式
				HELE hEle=(HELE)XArray_GetAt(pWindow->hArrayEle_List,i);
				if(XC_ELE==XC_GetObjectType(hEle))
				{
					HSTRING hString=((ele_*)hEle)->hString_Style_Class;
					if(hString)
					{
						if(0==wcscmp(temp,XStr_GetBuffer(hString)))
						{
							if(FALSE==CSS_HandleEle2(pLabel,hXmlRes,hWindow,(HELE)XArray_GetAt(pWindow->hArrayEle_List,i)))
								return FALSE;
						}
					}
				}
			}
		}*/
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleEle2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}

BOOL CSS_HandleButton(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_BUTTON,CSS_HandleButton2);
	}else if(0==strcmp(type,"class"))  //套用类型
	{
		CSS_HANDLE_CLASS(XC_BUTTON,CSS_HandleButton2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleButton2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else return FALSE;

	return TRUE;
}

BOOL CSS_HandleRadio(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_RADIO,CSS_HandleRadio2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_RADIO,CSS_HandleRadio2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleRadio2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;

	return TRUE;
}

BOOL CSS_HandleCheck(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_CHECK,CSS_HandleCheck2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_CHECK,CSS_HandleCheck2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleCheck2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}


BOOL CSS_HandleEdit(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
 	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_EDIT,CSS_HandleEdit2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_EDIT,CSS_HandleEdit2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleEdit2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}

BOOL CSS_HandleComboBox(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_COMBOBOX,CSS_HandleComboBox2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_COMBOBOX,CSS_HandleComboBox2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleComboBox2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}

BOOL CSS_HandleScrollBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_SCROLLBAR,CSS_HandleScrollBar2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_SCROLLBAR,CSS_HandleScrollBar2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleScrollBar2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}

BOOL CSS_HandleScrollView(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_SCROLLVIEW,CSS_HandleScrollView2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_SCROLLVIEW,CSS_HandleScrollView2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleScrollView2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleList(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_LIST,CSS_HandleList2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_LIST,CSS_HandleList2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleList2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleListBox(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_LISTBOX,CSS_HandleListBox2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_LISTBOX,CSS_HandleListBox2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleListBox2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleTree(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_TREE,CSS_HandleTree2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_TREE,CSS_HandleTree2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleTree2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleMenuBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_MENUBAR,CSS_HandleMenuBar2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_MENUBAR,CSS_HandleMenuBar2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleMenuBar2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandlePropertyPage(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_PROPERTYPAGE,CSS_HandlePropertyPage2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_PROPERTYPAGE,CSS_HandlePropertyPage2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandlePropertyPage2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleSliderBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_SLIDERBAR,CSS_HandleSliderBar2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_SLIDERBAR,CSS_HandleSliderBar2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleSliderBar2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleProgressBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_PROGRESSBAR,CSS_HandleProgressBar2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_PROGRESSBAR,CSS_HandleProgressBar2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleProgressBar2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleToolBar(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_TOOLBAR,CSS_HandleToolBar2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_TOOLBAR,CSS_HandleToolBar2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleToolBar2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleStatic(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_STATIC,CSS_HandleStatic2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_STATIC,CSS_HandleStatic2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleStatic2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleGroupBox(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_GROUPBOX,CSS_HandleGroupBox2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_GROUPBOX,CSS_HandleGroupBox2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleGroupBox2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandlePicture(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_PICTURE,CSS_HandlePicture2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_PICTURE,CSS_HandlePicture2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandlePicture2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleMonthCal(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_MONTHCAL,CSS_HandleMonthCal2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_MONTHCAL,CSS_HandleMonthCal2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleMonthCal2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleDateTime(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_DATETIME,CSS_HandleDateTime2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_DATETIME,CSS_HandleDateTime2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleDateTime2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandlePGrid(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_PROPERTYGRID,CSS_HandlePGrid2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_PROPERTYGRID,CSS_HandlePGrid2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandlePGrid2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}
BOOL CSS_HandleChooseColor(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_CHOOSECOLOR,CSS_HandleChooseColor2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_CHOOSECOLOR,CSS_HandleChooseColor2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandleChooseColor2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}

BOOL CSS_HandlePropertyPageLabel(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow)
{
	//样式类型
	const char *type=pLabel->Attribute("type");
	if(NULL==type) return FALSE;

	if(0==strcmp(type,"all"))
	{
		CSS_HANDLE_ALL(XC_PROPERTYPAGE_LABEL,CSS_HandlePropertyPageLabel2);
	}else if(0==strcmp(type,"class"))
	{
		CSS_HANDLE_CLASS(XC_PROPERTYPAGE_LABEL,CSS_HandlePropertyPageLabel2);
	}else if(0==strcmp(type,"id"))
	{
		int id=XML_GetEleId(pLabel,hXmlRes);
		if(id<1) return TRUE;

		HELE hEle=XWnd_GetEle(hWindow,id);
		if(hEle)
		{
			return CSS_HandlePropertyPageLabel2(pLabel,hXmlRes,hWindow,hEle);
		}
	}else
		return FALSE;
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////
BOOL CSS_HandleEle2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(NULL==hEle) return FALSE;
	if(XC_ELE!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	return TRUE;
}
BOOL CSS_HandleButton2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_BUTTON!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XBtn_SetText(hEle,temp);
	}

	const char *bCheck=pLabel->Attribute("bCheck");
	if(bCheck)
	{
		if(0==strcmp(bCheck,"TRUE"))
			XBtn_SetCheck(hEle,TRUE);
		else
			XBtn_SetCheck(hEle,FALSE);
	}

// left
// top
// right
// bottom
// center
// vcenter
// center |vcenter
// center | top
// center | bottom
// vcenter | left
// vcenter | right
	const char *textAlign=pLabel->Attribute(STRA_textAlign);
	if(textAlign)
	{
		if(0==strcmp(textAlign,"left"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_LEFT);
		else if(0==strcmp(textAlign,"left"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_LEFT);
		else if(0==strcmp(textAlign,"top"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_TOP);
		else if(0==strcmp(textAlign,"right"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_RIGHT);
		else if(0==strcmp(textAlign,"bottom"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_BOTTOM);
		else if(0==strcmp(textAlign,"center"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER);
		else if(0==strcmp(textAlign,"vcenter"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_VCENTER);
		else if(0==strcmp(textAlign,"center|vcenter"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		else if(0==strcmp(textAlign,"center|top"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER | DT_TOP);
		else if(0==strcmp(textAlign,"center|bottom"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
		else if(0==strcmp(textAlign,"vcenter|left"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		else if(0==strcmp(textAlign,"vcenter|right"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_VCENTER | DT_RIGHT);
	}

	const char *iconAlign=pLabel->Attribute(STRA_iconAlign);
	if(iconAlign)
	{
		if(0==strcmp(iconAlign,"left"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_LEFT);
		else if(0==strcmp(iconAlign,"top"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_TOP);
		if(0==strcmp(iconAlign,"right"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_RIGHT);
		if(0==strcmp(iconAlign,"bottom"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_BOTTOM);
	}
	const char *icon=pLabel->Attribute(STRA_icon);
	if(icon)
	{
		XC_AnsiToUnicode((char*)icon,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetIcon(hEle,hImage);
	}
	const char *image_leave=pLabel->Attribute("image_leave");
	if(image_leave)
	{
		XC_AnsiToUnicode((char*)image_leave,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageLeave(hEle,hImage);
	}
	const char *image_stay=pLabel->Attribute("image_stay");
	if(image_stay)
	{
		XC_AnsiToUnicode((char*)image_stay,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageStay(hEle,hImage);
	}
	const char *image_down=pLabel->Attribute("image_down");
	if(image_down)
	{
		XC_AnsiToUnicode((char*)image_down,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageDown(hEle,hImage);
	}
	const char *image_check=pLabel->Attribute("image_check");
	if(image_check)
	{
		XC_AnsiToUnicode((char*)image_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageCheck(hEle,hImage);
	}
	const char *image_disable=pLabel->Attribute("image_disable");
	if(image_disable)
	{
		XC_AnsiToUnicode((char*)image_disable,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageDisable(hEle,hImage);
	}

	return TRUE;
}

BOOL CSS_HandleRadio2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_RADIO!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XBtn_SetText(hEle,temp);
	}
	const char *bCheck=pLabel->Attribute("bCheck");
	if(bCheck)
	{
		if(0==strcmp(bCheck,"TRUE"))
			XBtn_SetCheck(hEle,TRUE);
		else
			XBtn_SetCheck(hEle,FALSE);
	}
	const char *image_leave_uncheck=pLabel->Attribute("image_leave_uncheck");
	if(image_leave_uncheck)
	{
		XC_AnsiToUnicode((char*)image_leave_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageLeave_UnCheck(hEle,hImage);
	}
	const char *image_stay_uncheck=pLabel->Attribute("image_stay_uncheck");
	if(image_stay_uncheck)
	{
		XC_AnsiToUnicode((char*)image_stay_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageStay_UnCheck(hEle,hImage);
	}
	const char *image_down_uncheck=pLabel->Attribute("image_down_uncheck");
	if(image_down_uncheck)
	{
		XC_AnsiToUnicode((char*)image_down_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageDown_UnCheck(hEle,hImage);
	}
	const char *image_disable_uncheck=pLabel->Attribute("image_disable_uncheck");
	if(image_disable_uncheck)
	{
		XC_AnsiToUnicode((char*)image_disable_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageDisable_UnCheck(hEle,hImage);
	}
	const char *image_leave_check=pLabel->Attribute("image_leave_check");
	if(image_leave_check)
	{
		XC_AnsiToUnicode((char*)image_leave_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageLeave_Check(hEle,hImage);
	}
	const char *image_stay_check=pLabel->Attribute("image_stay_check");
	if(image_stay_check)
	{
		XC_AnsiToUnicode((char*)image_stay_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageStay_Check(hEle,hImage);
	}
	const char *image_down_check=pLabel->Attribute("image_down_check");
	if(image_down_check)
	{
		XC_AnsiToUnicode((char*)image_down_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageDown_Check(hEle,hImage);
	}
	const char *image_disable_check=pLabel->Attribute("image_disable_check");
	if(image_disable_check)
	{
		XC_AnsiToUnicode((char*)image_disable_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XRadio_SetImageDisable_Check(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleCheck2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_CHECK!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XBtn_SetText(hEle,temp);
	}
	const char *bCheck=pLabel->Attribute("bCheck");
	if(bCheck)
	{
		if(0==strcmp(bCheck,"true"))
			XBtn_SetCheck(hEle,TRUE);
		else
			XBtn_SetCheck(hEle,FALSE);
	}

	const char *image_leave_uncheck=pLabel->Attribute("image_leave_uncheck");
	if(image_leave_uncheck)
	{
		XC_AnsiToUnicode((char*)image_leave_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageLeave_UnCheck(hEle,hImage);
	}
	const char *image_stay_uncheck=pLabel->Attribute("image_stay_uncheck");
	if(image_stay_uncheck)
	{
		XC_AnsiToUnicode((char*)image_stay_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageStay_UnCheck(hEle,hImage);
	}
	const char *image_down_uncheck=pLabel->Attribute("image_down_uncheck");
	if(image_down_uncheck)
	{
		XC_AnsiToUnicode((char*)image_down_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageDown_UnCheck(hEle,hImage);
	}
	const char *image_disable_uncheck=pLabel->Attribute("image_disable_uncheck");
	if(image_disable_uncheck)
	{
		XC_AnsiToUnicode((char*)image_disable_uncheck,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageDisable_UnCheck(hEle,hImage);
	}
	const char *image_leave_check=pLabel->Attribute("image_leave_check");
	if(image_leave_check)
	{
		XC_AnsiToUnicode((char*)image_leave_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageLeave_Check(hEle,hImage);
	}
	const char *image_stay_check=pLabel->Attribute("image_stay_check");
	if(image_stay_check)
	{
		XC_AnsiToUnicode((char*)image_stay_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageStay_Check(hEle,hImage);
	}
	const char *image_down_check=pLabel->Attribute("image_down_check");
	if(image_down_check)
	{
		XC_AnsiToUnicode((char*)image_down_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageDown_Check(hEle,hImage);
	}
	const char *image_disable_check=pLabel->Attribute("image_disable_check");
	if(image_disable_check)
	{
		XC_AnsiToUnicode((char*)image_disable_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XCheck_SetImageDisable_Check(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleEdit2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_EDIT!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XEdit_SetText(hEle,temp);
	}
	const char *bMoreLine=pLabel->Attribute("bMoreLine");
	if(bMoreLine)
	{
		if(0==strcmp(bMoreLine,"true"))
			XEdit_EnableMultiLine(hEle,TRUE);
		else
			XEdit_EnableMultiLine(hEle,FALSE);
	}
	const char *bNumber=pLabel->Attribute("bNumber");
	if(bNumber)
	{
		if(0==strcmp(bNumber,"true"))
			XEdit_EnableNumber(hEle,TRUE);
		else
			XEdit_EnableNumber(hEle,FALSE);
	}
	const char *bHScrollBar=pLabel->Attribute("bHScrollBar");
	if(bHScrollBar)
	{
		if(0==strcmp(bHScrollBar,"true"))
			XSView_EnableHScroll(hEle,TRUE);
		else
			XSView_EnableHScroll(hEle,FALSE);
	}
	const char *bVScrollBar=pLabel->Attribute("bVScrollBar");
	if(bVScrollBar)
	{
		if(0==strcmp(bVScrollBar,"true"))
			XSView_EnableVScroll(hEle,TRUE);
		else
			XSView_EnableVScroll(hEle,FALSE);
	}
	const char *bReadOnly=pLabel->Attribute("bReadOnly");
	if(bReadOnly)
	{
		if(0==strcmp(bReadOnly,"true"))
			XEdit_SetReadOnly(hEle,TRUE);
		else
			XEdit_SetReadOnly(hEle,FALSE);
	}
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleComboBox2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_COMBOBOX!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	const char *bEdit=pLabel->Attribute("bEdit");
	if(bEdit)
	{
		if(0==strcmp(bEdit,"true"))
			XComboBox_EnableEdit(hEle,TRUE);
		else
			XComboBox_EnableEdit(hEle,FALSE);
	}

	int dropDownList_height=0;
	if(pLabel->Attribute("dropDownList_height",&dropDownList_height))
	{
		XComboBox_SetListHeight(hEle,dropDownList_height);
	}
	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleScrollBar2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_SCROLLBAR!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;
	
	const char *bHorizon=pLabel->Attribute("bHorizon");
	if(bHorizon)
	{
		if(0==strcmp(bHorizon,"true"))
			XSBar_SetHorizon(hEle,TRUE);
		else
			XSBar_SetHorizon(hEle,FALSE);
	}
	int range=0;
	if(pLabel->Attribute("range",&range))
	{
		XSBar_SetScrollRange(hEle,range);
	}
	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleScrollView2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_SCROLLVIEW!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	const char *bHScrollBar=pLabel->Attribute("bHScrollBar");
	if(bHScrollBar)
	{
		if(0==strcmp(bHScrollBar,"true"))
			XSView_EnableHScroll(hEle,TRUE);
		else
			XSView_EnableHScroll(hEle,FALSE);
	}
	const char *bVScrollBar=pLabel->Attribute("bVScrollBar");
	if(bVScrollBar)
	{
		if(0==strcmp(bVScrollBar,"true"))
			XSView_EnableVScroll(hEle,TRUE);
		else
			XSView_EnableVScroll(hEle,FALSE);
	}

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}


BOOL CSS_HandleList2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_LIST!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;
	const char *bHeader=pLabel->Attribute("bHeader");
	if(bHeader)
	{
		if(0==strcmp(bHeader,"true"))
			XList_ShowHeader(hEle,TRUE);
		else
			XList_ShowHeader(hEle,FALSE);
	}
	const char *bHScrollBar=pLabel->Attribute("bHScrollBar");
	if(bHScrollBar)
	{
		if(0==strcmp(bHScrollBar,"true"))
			XSView_EnableHScroll(hEle,TRUE);
		else
			XSView_EnableHScroll(hEle,FALSE);
	}
	const char *bVScrollBar=pLabel->Attribute("bVScrollBar");
	if(bVScrollBar)
	{
		if(0==strcmp(bVScrollBar,"true"))
			XSView_EnableVScroll(hEle,TRUE);
		else
			XSView_EnableVScroll(hEle,FALSE);
	}

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleListBox2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_LISTBOX!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	const char *bHScrollBar=pLabel->Attribute("bHScrollBar");
	if(bHScrollBar)
	{
		if(0==strcmp(bHScrollBar,"true"))
			XSView_EnableHScroll(hEle,TRUE);
		else
			XSView_EnableHScroll(hEle,FALSE);
	}
	const char *bVScrollBar=pLabel->Attribute("bVScrollBar");
	if(bVScrollBar)
	{
		if(0==strcmp(bVScrollBar,"true"))
			XSView_EnableVScroll(hEle,TRUE);
		else
			XSView_EnableVScroll(hEle,FALSE);
	}

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleTree2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_TREE!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	const char *bButton=pLabel->Attribute("bButton");
	if(bButton)
	{
		if(0==strcmp(bButton,"true"))
			XTree_EnableButton(hEle,TRUE);
		else
			XTree_EnableButton(hEle,FALSE);
	}
	const char *bLine=pLabel->Attribute("bLine");
	if(bLine)
	{
		if(0==strcmp(bLine,"true"))
			XTree_EnableLine(hEle,TRUE);
		else
			XTree_EnableLine(hEle,FALSE);
	}
	const char *bRootLine=pLabel->Attribute("bRootLine");
	if(bRootLine)
	{
		if(0==strcmp(bRootLine,"true"))
			XTree_EnableRootLine(hEle,TRUE);
		else
			XTree_EnableRootLine(hEle,FALSE);
	}
	const char *bHScrollBar=pLabel->Attribute("bHScrollBar");
	if(bHScrollBar)
	{
		if(0==strcmp(bHScrollBar,"true"))
			XSView_EnableHScroll(hEle,TRUE);
		else
			XSView_EnableHScroll(hEle,FALSE);
	}
	const char *bVScrollBar=pLabel->Attribute("bVScrollBar");
	if(bVScrollBar)
	{
		if(0==strcmp(bVScrollBar,"true"))
			XSView_EnableVScroll(hEle,TRUE);
		else
			XSView_EnableVScroll(hEle,FALSE);
	}

	int itemHeight=0;
	if(pLabel->Attribute("itemHeight",&itemHeight))
	{
		XTree_SetItemHeight(hEle,itemHeight);
	}
	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleMenuBar2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_MENUBAR!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

//	const char *bStretch=pLabel->Attribute("bStretch");
//	if(bStretch)
//	{
//		if(0==strcmp(bStretch,"true"))
//			XMenuBar_EnableImageStretch(hEle,TRUE);
//		else
//			XMenuBar_EnableImageStretch(hEle,FALSE);
//	}
	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XMenuBar_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandlePropertyPage2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_PROPERTYPAGE!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	int labelHeight=0;
	if(pLabel->Attribute("labelHeight",&labelHeight))
	{
		XPPage_SetLabelHeight(hEle,labelHeight);
	}
	int labelSpacing=0;
	if(pLabel->Attribute("labelSpacing",&labelSpacing))
	{
		XPPage_SetLabelSpacing(hEle,labelSpacing);
	}

	const char *bScrollButton=pLabel->Attribute(STRA_bScrollButton);
	if(bScrollButton)
	{
		if(0==strcmp(bScrollButton,"true"))
			XPPage_EnableScrollButton(hEle,TRUE);
		else
			XPPage_EnableScrollButton(hEle,FALSE);
	}
	return TRUE;
}

BOOL CSS_HandleSliderBar2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_SLIDERBAR!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	const char *bHorizon=pLabel->Attribute("bHorizon");
	if(bHorizon)
	{
		if(0==strcmp(bHorizon,"true"))
			XSliderBar_SetHorizon(hEle,TRUE);
		else
			XSliderBar_SetHorizon(hEle,FALSE);
	}
	int range=0;
	if(pLabel->Attribute("range",&range))
	{
		XSliderBar_SetRange(hEle,range);
	}

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSliderBar_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleProgressBar2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_PROGRESSBAR!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	const char *bHorizon=pLabel->Attribute("bHorizon");
	if(bHorizon)
	{
		if(0==strcmp(bHorizon,"true"))
			XProgBar_SetHorizon(hEle,TRUE);
		else
			XProgBar_SetHorizon(hEle,FALSE);
	}
	int range=0;
	if(pLabel->Attribute("range",&range))
	{
		XProgBar_SetRange(hEle,range);
	}
	return TRUE;
}

BOOL CSS_HandleToolBar2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_TOOLBAR!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XToolBar_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleStatic2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_STATIC!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XStatic_SetText(hEle,temp);
	}
	return TRUE;
}

BOOL CSS_HandleGroupBox2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_GROUPBOX!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XGBox_SetText(hEle,temp);
	}
	return TRUE;
}

BOOL CSS_HandlePicture2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_PICTURE!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,&temp[1]);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XPic_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleMonthCal2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_MONTHCAL!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	return TRUE;
}

BOOL CSS_HandleDateTime2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_DATETIME!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XDateTime_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandlePGrid2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_PROPERTYGRID!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;
	const char *bHScrollBar=pLabel->Attribute("bHScrollBar");
	if(bHScrollBar)
	{
		if(0==strcmp(bHScrollBar,"true"))
			XSView_EnableHScroll(hEle,TRUE);
		else
			XSView_EnableHScroll(hEle,FALSE);
	}
	const char *bVScrollBar=pLabel->Attribute("bVScrollBar");
	if(bVScrollBar)
	{
		if(0==strcmp(bVScrollBar,"true"))
			XSView_EnableVScroll(hEle,TRUE);
		else
			XSView_EnableVScroll(hEle,FALSE);
	}

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}

BOOL CSS_HandleChooseColor2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_CHOOSECOLOR!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *image=pLabel->Attribute("image");
	if(image)
	{
		XC_AnsiToUnicode((char*)image,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XSView_SetImage(hEle,hImage);
	}
	return TRUE;
}
BOOL CSS_HandlePropertyPageLabel2(TiXmlElement *pLabel,HXMLRES hXmlRes,HWINDOW hWindow,HELE hEle)
{
	if(XC_PROPERTYPAGE_LABEL!=XC_GetObjectType(hEle)) return FALSE;

	if(FALSE==CSS_HandleBase(pLabel,hEle)) return FALSE;

	wchar_t temp[MAX_PATH]={0};
	const char *value=pLabel->Attribute("value");
	if(value)
	{
		MultiByteToWideChar(CP_ACP,0,value,-1,temp,MAX_PATH);
		XBtn_SetText(hEle,temp);
	}

	const char *bCheck=pLabel->Attribute("bCheck");
	if(bCheck)
	{
		if(0==strcmp(bCheck,"true"))
			XBtn_SetCheck(hEle,TRUE);
		else
			XBtn_SetCheck(hEle,FALSE);
	}

// left
// top
// right
// bottom
// center
// vcenter
// center |vcenter
// center | top
// center | bottom
// vcenter | left
// vcenter | right
	const char *textAlign=pLabel->Attribute(STRA_textAlign);
	if(textAlign)
	{
		if(0==strcmp(textAlign,"left"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_LEFT);
		else if(0==strcmp(textAlign,"left"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_LEFT);
		else if(0==strcmp(textAlign,"top"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_TOP);
		else if(0==strcmp(textAlign,"right"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_RIGHT);
		else if(0==strcmp(textAlign,"bottom"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_BOTTOM);
		else if(0==strcmp(textAlign,"center"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER);
		else if(0==strcmp(textAlign,"vcenter"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_VCENTER);
		else if(0==strcmp(textAlign,"center|vcenter"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		else if(0==strcmp(textAlign,"center|top"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER | DT_TOP);
		else if(0==strcmp(textAlign,"center|bottom"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
		else if(0==strcmp(textAlign,"vcenter|left"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		else if(0==strcmp(textAlign,"vcenter|right"))
			XBtn_SetTextAlign(hEle,DT_SINGLELINE | DT_VCENTER | DT_RIGHT);
	}

	const char *iconAlign=pLabel->Attribute(STRA_iconAlign);
	if(iconAlign)
	{
		if(0==strcmp(iconAlign,"left"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_LEFT);
		else if(0==strcmp(iconAlign,"top"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_TOP);
		if(0==strcmp(iconAlign,"right"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_RIGHT);
		if(0==strcmp(iconAlign,"bottom"))
			XBtn_SetIconAlign(hEle,XC_ICON_ALIGN_BOTTOM);
	}

	const char *icon=pLabel->Attribute(STRA_icon);
	if(icon)
	{
		XC_AnsiToUnicode((char*)icon,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetIcon(hEle,hImage);
	}
	const char *image_leave=pLabel->Attribute("image_leave");
	if(image_leave)
	{
		XC_AnsiToUnicode((char*)image_leave,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageLeave(hEle,hImage);
	}
	const char *image_stay=pLabel->Attribute("image_stay");
	if(image_stay)
	{
		XC_AnsiToUnicode((char*)image_stay,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageStay(hEle,hImage);
	}
	const char *image_down=pLabel->Attribute("image_down");
	if(image_down)
	{
		XC_AnsiToUnicode((char*)image_down,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageDown(hEle,hImage);
	}
	const char *image_check=pLabel->Attribute("image_check");
	if(image_check)
	{
		XC_AnsiToUnicode((char*)image_check,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageCheck(hEle,hImage);
	}
	const char *image_disable=pLabel->Attribute("image_disable");
	if(image_disable)
	{
		XC_AnsiToUnicode((char*)image_disable,-1,temp,MAX_PATH);
		HIMAGE hImage=NULL;
		if(L'@'==temp[0]) //从资源
			hImage=XXmlRes_FildHIMAGE(hXmlRes,temp+1);
		else
			hImage=XImage_LoadFile(temp);
		
		if(hImage)
			XBtn_SetImageDisable(hEle,hImage);
	}

	const char *labelWidth=pLabel->Attribute(STRA_labelWidth);
	if(labelWidth)
	{
		int w=atoi(labelWidth);
		HELE hParent=XEle_GetParentEle(hEle);
		int index=XPPage_GetLabelIndex(hParent,hEle);
		XPPage_SetLabelWidth(hParent,index,w);
	}

	return TRUE;
}