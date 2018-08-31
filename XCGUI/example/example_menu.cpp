/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0
BOOL CALLBACK My_OnRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt);
BOOL CALLBACK My_MenuSelect(HWINDOW hWindow,int id);
BOOL CALLBACK My_MenuExit(HWINDOW hWindow);
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    XInitXCGUI();
    //创建窗口
    HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"窗口");
	XBtn_Create(10,10,100,25,L"button",hWindow);
    ShowWindow(XWnd_GetHWnd(hWindow),SW_SHOW);
    //注册消息
    XWnd_RegisterMessage(hWindow,WM_RBUTTONUP,My_OnRButtonUp);
    XWnd_RegisterMessage(hWindow,XWM_MENUSELECT,My_MenuSelect);
    XWnd_RegisterMessage(hWindow,XWM_MENUEXIT,My_MenuExit);
    XRunXCGUI();
    return 0;
}

BOOL CALLBACK My_OnRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt)
{
    POINT pt=*pPt;

    pt.x+=XWnd_GetClientLeft(hWindow);
    pt.y+=XWnd_GetClientTop(hWindow);
    
    //创建弹出菜单
    HMENUX hMenu=XMenu_Create();
    XMenu_AddItem(hMenu,201,L"111");
    XMenu_AddItem(hMenu,202,L"222");
    XMenu_AddItem(hMenu,203,L"333");

    XMenu_AddItem(hMenu,204,L"444",203);
    XMenu_AddItem(hMenu,205,L"555",203);
    XMenu_AddItem(hMenu,206,L"666",203);

    XMenu_AddItem(hMenu,207,L"777",206);
    XMenu_AddItem(hMenu,208,L"888",206);
    XMenu_AddItem(hMenu,209,L"999",206);

    ClientToScreen(XWnd_GetHWnd(hWindow),&pt);
    XMenu_Popup(hMenu,XWnd_GetHWnd(hWindow),pt.x,pt.y);


	
/*
	ClientToScreen(XWnd_GetHWnd(hWindow),&pt);

	HMENU hMenu=CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 101,L"123"); 
	AppendMenu(hMenu, MF_STRING, 102,L"333");
	AppendMenu(hMenu, MF_STRING, 103,L"444");

	::TrackPopupMenu(hMenu,TPM_RIGHTBUTTON,pt.x,pt.y,0,XWnd_GetHWnd(hWindow),NULL);
*/
    return FALSE;
}

BOOL CALLBACK My_MenuSelect(HWINDOW hWindow,int id)  //菜单选择
{
    XTRACE("菜单ID=%d\n",id);
	//XWnd_CloseWindow(hWindow);
    return FALSE;
}

BOOL CALLBACK My_MenuExit(HWINDOW hWindow) //菜单退出
{
    XTRACE("菜单退出\n");
    return FALSE;
}

#endif 



/*
class CMyMenu : public CXEventMsg
{
public:
	HMENUX m_hMenu;
	void Init(HMENUX hMenu)
	{
		m_hMenu=hMenu;
		//XCGUI_Menu_SetUserDrawItem(m_hMenu,&CMyMenu::OnMenu_DrawItem);
		XCGUI_Menu_SetUserDrawBG(m_hMenu,&CMyMenu::OnMenu_DrawBG);
	}

	void OnMenu_DrawItem(HMENUX hMenu,menu_drawItem_ *pDrawItem)
	{
		int leftWidth=XMenu_GetItemLeftWidth(hMenu);
		int leftText=XMenu_GetItemLeftText(hMenu);
		int height=XMenu_GetItemHeight(hMenu);

		if(pDrawItem->state & XM_SEPARATOR) //分割栏
		{
			HPEN hPen1=CreatePen(PS_SOLID, 1, RGB(200,200,200));
			HGDIOBJ hOld1=SelectObject(pDrawItem->hdc,hPen1);

			MoveToEx(pDrawItem->hdc,leftWidth+2,pDrawItem->rcItem.top+1,0);
			LineTo(pDrawItem->hdc,pDrawItem->rcItem.right-5,pDrawItem->rcItem.top+1);

			SelectObject(pDrawItem->hdc,hOld1);
			DeleteObject(hPen1);
			return ;
		}

		if(pDrawItem->state & XM_SELECT) //选择项
		{
			XDraw_GradientFill2(pDrawItem->hdc,63,151,216,48,134,198,&pDrawItem->rcItem,GRADIENT_FILL_RECT_V);
		}

		if(pDrawItem->state & XM_POPUP) //弹出项
		{
			//绘制右三角
			POINT  pt[3];
			pt[0].x=pDrawItem->rcItem.right-12;
			pt[0].y=pDrawItem->rcItem.top+5;
			pt[1].x=pDrawItem->rcItem.right-12;
			pt[1].y=pDrawItem->rcItem.top+15;
			pt[2].x=pDrawItem->rcItem.right-7;
			pt[2].y=pDrawItem->rcItem.top+10;
			HRGN hRgn=CreatePolygonRgn(pt,3,ALTERNATE);
			HBRUSH hBrush=CreateSolidBrush(RGB(0,0,0));
			FillRgn(pDrawItem->hdc,hRgn,hBrush);
			DeleteObject(hRgn);
			DeleteObject(hBrush);
		}

		if(pDrawItem->state &XM_CHECK) //勾选
		{
			HPEN hPen=CreatePen(PS_SOLID,2,RGB(0,0,0));
			HGDIOBJ hOld=SelectObject(pDrawItem->hdc,hPen);
			MoveToEx(pDrawItem->hdc,pDrawItem->rcItem.left+5,pDrawItem->rcItem.top+8,0);
			LineTo(pDrawItem->hdc,pDrawItem->rcItem.left+10,pDrawItem->rcItem.top+13);

			MoveToEx(pDrawItem->hdc,pDrawItem->rcItem.left+9,pDrawItem->rcItem.top+13,0);
			LineTo(pDrawItem->hdc,pDrawItem->rcItem.left+17,pDrawItem->rcItem.top+5);

			SelectObject(pDrawItem->hdc,hOld);
			DeleteObject(hPen);
		}

		RECT rc=pDrawItem->rcItem;
		rc.left=leftWidth+leftText;

		wchar_t *pText=pDrawItem->pText;
		if(pDrawItem->state & XM_DISABLED)//禁用项
		{
			if(pText)
			{
				COLORREF color=SetTextColor(pDrawItem->hdc,RGB(100,100,100));
				DrawText(pDrawItem->hdc,pText,wcslen(pDrawItem->pText),&rc,DT_VCENTER | DT_SINGLELINE);
				SetTextColor(pDrawItem->hdc,color);
			}
		}else
		{
			if(pDrawItem->hImage)
			{
				int top=(height/2)-XImage_GetHeight(pDrawItem->hImage)/2;  //(pItem->pImage->GetHeight()/2);
				int left=(leftWidth/2)-XImage_GetWidth(pDrawItem->hImage)/2;  //(pItem->pImage->GetWidth()/2);
				if(top<0) top=0;
				if(left<0) left=0;
				//XDraw_GraphicsDrawImage(hdc,pItem->pImage,left,pItem->rcItem.top+top);
				XDraw_HImage(pDrawItem->hdc,pDrawItem->hImage,left,pDrawItem->rcItem.top+top);
			}
			if(pText)
				DrawText(pDrawItem->hdc,pText,wcslen(pDrawItem->pText),&rc,DT_VCENTER | DT_SINGLELINE);
		}
	}

	void OnMenu_DrawBG(HMENUX hMenu,menu_drawBG_ *pDrawBG) //自绘菜单背景
	{
		RECT rc;
		XWnd_GetClientRect(pDrawBG->hWindow,&rc);
		//绘制背景色-----------------------
		XDraw_FillSolidRect(pDrawBG->hdc,&rc,RGB(255,255,255));

		//绘制左边灰色区域------------------
		RECT rcLeft=rc;
		rcLeft.right=30;
		rcLeft.bottom-=2;
		XDraw_FillSolidRect(pDrawBG->hdc,&rcLeft,RGB(232,237,239));

		HPEN hPen=CreatePen(PS_SOLID,1,RGB(200,200,200));
		HGDIOBJ hOld=SelectObject(pDrawBG->hdc,hPen);
		MoveToEx(pDrawBG->hdc,29,0,0);
		LineTo(pDrawBG->hdc,29,rc.bottom-2);
		SelectObject(pDrawBG->hdc,hOld);
		DeleteObject(hPen);

		//绘制边框---------------------------
		RECT rcFrame=rc;
		HBRUSH hBrush=CreateSolidBrush(RGB(130,130,130));
		FrameRect(pDrawBG->hdc,&rcFrame,hBrush);
		DeleteObject(hBrush);

		HPEN hPen1=CreatePen(PS_SOLID,1,RGB(180,180,180));
		HGDIOBJ hOld1=SelectObject(pDrawBG->hdc,hPen1);
		MoveToEx(pDrawBG->hdc,rc.right-2,1,0);
		LineTo(pDrawBG->hdc,rc.right-2,rc.bottom-2);
		LineTo(pDrawBG->hdc,0,rc.bottom-2);
		SelectObject(pDrawBG->hdc,hOld1);
		DeleteObject(hPen1);
	}
};

void CALLBACK OnMenu_DrawItem(HMENUX hMenu,menu_drawItem_ *pDrawItem)
{
	int leftWidth=XMenu_GetItemLeftWidth(hMenu);
	int leftText=XMenu_GetItemLeftText(hMenu);
	int height=XMenu_GetItemHeight(hMenu);

	if(pDrawItem->state & XM_SEPARATOR) //分割栏
	{
		HPEN hPen1=CreatePen(PS_SOLID, 1, RGB(200,200,200));
		HGDIOBJ hOld1=SelectObject(pDrawItem->hdc,hPen1);

		MoveToEx(pDrawItem->hdc,leftWidth+2,pDrawItem->rcItem.top+1,0);
		LineTo(pDrawItem->hdc,pDrawItem->rcItem.right-5,pDrawItem->rcItem.top+1);

		SelectObject(pDrawItem->hdc,hOld1);
		DeleteObject(hPen1);
		return ;
	}

	if(pDrawItem->state & XM_SELECT) //选择项
	{
		XDraw_GradientFill2(pDrawItem->hdc,63,151,216,48,134,198,&pDrawItem->rcItem,GRADIENT_FILL_RECT_V);
	}

	if(pDrawItem->state & XM_POPUP) //弹出项
	{
		//绘制右三角
		POINT  pt[3];
		pt[0].x=pDrawItem->rcItem.right-12;
		pt[0].y=pDrawItem->rcItem.top+5;
		pt[1].x=pDrawItem->rcItem.right-12;
		pt[1].y=pDrawItem->rcItem.top+15;
		pt[2].x=pDrawItem->rcItem.right-7;
		pt[2].y=pDrawItem->rcItem.top+10;
		HRGN hRgn=CreatePolygonRgn(pt,3,ALTERNATE);
		HBRUSH hBrush=CreateSolidBrush(RGB(0,0,0));
		FillRgn(pDrawItem->hdc,hRgn,hBrush);
		DeleteObject(hRgn);
		DeleteObject(hBrush);
	}

	if(pDrawItem->state &XM_CHECK) //勾选
	{
		HPEN hPen=CreatePen(PS_SOLID,2,RGB(0,0,0));
		HGDIOBJ hOld=SelectObject(pDrawItem->hdc,hPen);
		MoveToEx(pDrawItem->hdc,pDrawItem->rcItem.left+5,pDrawItem->rcItem.top+8,0);
		LineTo(pDrawItem->hdc,pDrawItem->rcItem.left+10,pDrawItem->rcItem.top+13);

		MoveToEx(pDrawItem->hdc,pDrawItem->rcItem.left+9,pDrawItem->rcItem.top+13,0);
		LineTo(pDrawItem->hdc,pDrawItem->rcItem.left+17,pDrawItem->rcItem.top+5);

		SelectObject(pDrawItem->hdc,hOld);
		DeleteObject(hPen);
	}

	RECT rc=pDrawItem->rcItem;
	rc.left=leftWidth+leftText;

	wchar_t *pText=pDrawItem->pText;
	if(pDrawItem->state & XM_DISABLED)//禁用项
	{
		if(pText)
		{
			COLORREF color=SetTextColor(pDrawItem->hdc,RGB(100,100,100));
			DrawText(pDrawItem->hdc,pText,wcslen(pDrawItem->pText),&rc,DT_VCENTER | DT_SINGLELINE);
			SetTextColor(pDrawItem->hdc,color);
		}
	}else
	{
		if(pDrawItem->hImage)
		{
			int top=(height/2)-XImage_GetHeight(pDrawItem->hImage)/2;  //(pItem->pImage->GetHeight()/2);
			int left=(leftWidth/2)-XImage_GetWidth(pDrawItem->hImage)/2;  //(pItem->pImage->GetWidth()/2);
			if(top<0) top=0;
			if(left<0) left=0;
			//XDraw_GraphicsDrawImage(hdc,pItem->pImage,left,pItem->rcItem.top+top);
			XDraw_HImage(pDrawItem->hdc,pDrawItem->hImage,left,pDrawItem->rcItem.top+top);
		}
		if(pText)
			DrawText(pDrawItem->hdc,pText,wcslen(pDrawItem->pText),&rc,DT_VCENTER | DT_SINGLELINE);
	}
}

CMyMenu  MyMenu;
BOOL CALLBACK My_OnRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt)
{
	POINT pt=*pPt;

	pt.x+=XWnd_GetClientLeft(hWindow);
	pt.y+=XWnd_GetClientTop(hWindow);
	
	HIMAGE hImage=XImage_LoadFile(L"image\\149.gif");
	//创建弹出菜单
	HMENUX hMenu=XMenu_Create();

	XMenu_AddItemImage(hMenu,1,L"111",XMENU_ROOT,0,hImage);
	XMenu_AddItemImage(hMenu,2,L"222",XMENU_ROOT,0,hImage);
	XMenu_AddItem(hMenu,3,L"333",XMENU_ROOT);

	XMenu_AddItem(hMenu,4,L"333",3);
	XMenu_AddItem(hMenu,5,L"333",3);
	XMenu_AddItem(hMenu,6,L"333",3);
	XMenu_AddItem(hMenu,7,L"333",3);

	//int count=XMenu_GetItemCount(hMenu);
	ClientToScreen(XWnd_GetHWnd(hWindow),&pt);
	XMenu_Popup(hMenu,XWnd_GetHWnd(hWindow),pt.x,pt.y);
	
	MyMenu.Init(hMenu);
	//XMenu_SetUserDrawItem(hMenu,OnMenu_DrawItem);
	//XMenu_SetUserDrawBG(hMenu,OnMenu_DrawBG);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(378);
	XInitXCGUI();
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//注册消息
	XWnd_RegisterMessage(hWindow,WM_RBUTTONUP,My_OnRButtonUp);

	XRunXCGUI();

	return 0;
}*/