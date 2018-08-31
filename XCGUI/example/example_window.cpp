/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0
BOOL bbtt=TRUE;
HWINDOW hWindow;
BOOL CALLBACK OnMyEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(bbtt)
	{
		bbtt=FALSE;
		XWnd_EnableRound(hWindow,FALSE,TRUE);
	}else
	{
		bbtt=TRUE;
		XWnd_EnableRound(hWindow,TRUE,TRUE);
	}
	XTRACE("OnMyEventBtnClick() \n");
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//if(FALSE==XC_RegisterWndClass(L"TTYY")) return 0;

	//创建窗口
	//hWindow=XWnd_CreateWindowEx(NULL,L"TTYY",L"WindowNmae",NULL,400,200,400,300,NULL);
	hWindow=XWnd_CreateWindow(0,0,400,300,L"炫彩界面库-窗口");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//弹出消息框
	HELE hButton=XBtn_Create(10,90,60,25,L"按钮",hWindow);
	XBtn_SetIcon(hButton,XImage_LoadFile(L"qqImage\\7.png"));
//	XBtn_SetTextAlign(hButton,0);
	XEle_RegisterEvent(hButton,XE_BNCLICK,OnMyEventBtnClick);

	XRunXCGUI();
	return 0;
}
#endif

#if 0
//演示QQ2009
#define WINDOW_WIDTH   250 //窗口宽度
#define WINDOW_HEIGHT  600 //窗口高度
HELE hWeather=NULL;
HELE hUserSign=NULL;
HELE hButtonSkin=NULL;
HELE hButtonMsg=NULL;
HELE hTree=NULL;
HELE hTabBar=NULL;
HELE hButtonHidePane=NULL;
HELE hButtonMainMenu=NULL;
HELE hButtonTool1=NULL;
HELE hButtonTool2=NULL;
HELE hButtonTool3=NULL;
HELE hButtonTool4=NULL;
HELE hButtonTool5=NULL;
HELE hButtonTool6=NULL;
HELE hLeftPane=NULL;
HELE hSearchEdit=NULL;
int group1=0;
int group2=0;

struct xc_image_res  //图片资源
{
	HIMAGE image_bk;
	HIMAGE hImageLogo;

	HIMAGE close_leave;
	HIMAGE close_stay;
	HIMAGE close_down;

	HIMAGE max_leave;
	HIMAGE max_stay;
	HIMAGE max_down;

	HIMAGE min_leave;
	HIMAGE min_stay;
	HIMAGE min_down;

	HIMAGE weather;

	HIMAGE face_leave;
	HIMAGE face_stay;

	HIMAGE userstate_leave;
	HIMAGE userstate_stay;
	HIMAGE userstate_down;

	HIMAGE button_leave;
	HIMAGE button_stay;
	HIMAGE button_down;

	HIMAGE searchedit;

	HIMAGE search;
	HIMAGE icon1;
	HIMAGE icon2;
	HIMAGE icon3;
	HIMAGE icon7;
	HIMAGE icon8;
	HIMAGE icon9;
	HIMAGE icon10;
	HIMAGE icon11;
	HIMAGE icon15;
	HIMAGE icon16;

	HIMAGE mainMenu_leave;
	HIMAGE mainMenu_stay;

	HIMAGE hideleftpanel_leave;
	HIMAGE hideleftpanel_stay;

	HIMAGE tabLeft_leave;
	HIMAGE tabLeft_stay;
	HIMAGE tabLeft_down;

	HIMAGE leftpane;
	HIMAGE tab1;
	HIMAGE tab2;
	HIMAGE tab3;

	HIMAGE talkLabel_leave;
	HIMAGE talkLabel_stay;
	HIMAGE talkLabel_down;

	HIMAGE talktbico1;
	HIMAGE talktbico2;
	HIMAGE talktbico3;

	HIMAGE imp_shrink;
	HIMAGE imp_expand;
	HIMAGE imp_icon_1;
	HIMAGE imp_icon_2;
	HIMAGE imp_icon_3;
	HIMAGE imp_icon_4;
	HIMAGE imp_icon_5;
	HIMAGE imp_icon_6;

	HIMAGE scroll_thumb_leave;
	HIMAGE scroll_thumb_down;

	HIMAGE scroll_up_leave;
	HIMAGE scroll_up_down;
	
	HIMAGE scroll_down_leave;
	HIMAGE scroll_down_down;

};

xc_image_res  image_res;

//加载图片资源
void LoadImageRes()
{
	image_res.image_bk=XImage_LoadZipAdaptive(L"qqImage.zip",L"qqImage/back.bmp",NULL,6,174,123,140);
	image_res.hImageLogo=XImage_LoadZip(L"qqImage.zip",L"qqImage/logo2009.png");

	image_res.close_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/close_leave.png");
	image_res.close_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/close_stay.png");
	image_res.close_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/close_down.png");

	image_res.max_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/max_leave.png");
	image_res.max_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/max_stay.png");
	image_res.max_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/max_down.png");

	image_res.min_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/min_leave.png");
	image_res.min_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/min_stay.png");
	image_res.min_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/min_down.png");

	image_res.weather=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/weather.png");

	image_res.face_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/face_leave.png");
	image_res.face_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/face_stay.png");

	image_res.userstate_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/userstate_leave.png");
	image_res.userstate_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/userstate_stay.png");
	image_res.userstate_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/userstate_down.png");

	image_res.button_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button_leave.png");
	image_res.button_stay=XImage_LoadZipAdaptive(L"qqImage.zip",L"qqImage/button_stay.png",NULL,3,22,3,22);
	image_res.button_down=XImage_LoadZipAdaptive(L"qqImage.zip",L"qqImage/button_down.png",NULL,3,22,3,22);

	image_res.searchedit=XImage_LoadZipAdaptive(L"qqImage.zip",L"qqImage/searchedit.png",NULL,9,13,6,19);

	image_res.search=XImage_LoadZip(L"qqImage.zip",L"qqImage/17.png");

	image_res.icon1=XImage_LoadZip(L"qqImage.zip",L"qqImage/1.png");
	image_res.icon2=XImage_LoadZip(L"qqImage.zip",L"qqImage/2.png");
	image_res.icon3=XImage_LoadZip(L"qqImage.zip",L"qqImage/3.png");
	image_res.icon7=XImage_LoadZip(L"qqImage.zip",L"qqImage/7.png");
	image_res.icon8=XImage_LoadZip(L"qqImage.zip",L"qqImage/8.png");
	image_res.icon9=XImage_LoadZip(L"qqImage.zip",L"qqImage/9.png");
	image_res.icon10=XImage_LoadZip(L"qqImage.zip",L"qqImage/10.png");
	image_res.icon11=XImage_LoadZip(L"qqImage.zip",L"qqImage/11.png");
	image_res.icon15=XImage_LoadZip(L"qqImage.zip",L"qqImage/15.png");
	image_res.icon16=XImage_LoadZip(L"qqImage.zip",L"qqImage/16.png");

	image_res.mainMenu_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/mainMenu.png");
	image_res.mainMenu_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/mainMenu_stay.png");

	image_res.hideleftpanel_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/hideleftpanel_leave.png");
	image_res.hideleftpanel_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/hideleftpanel_stay.png");

	image_res.tabLeft_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/tabLeft_leave.png");
	image_res.tabLeft_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/tabLeft_stay.png");
	image_res.tabLeft_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/button/tabLeft_down.png");
	
	image_res.leftpane=XImage_LoadZip(L"qqImage.zip",L"qqImage/leftpane.png");
	image_res.tab1=XImage_LoadZip(L"qqImage.zip",L"qqImage/tab1.png");
	image_res.tab2=XImage_LoadZip(L"qqImage.zip",L"qqImage/tab2.png");
	image_res.tab3=XImage_LoadZip(L"qqImage.zip",L"qqImage/tab3.png");

	image_res.talkLabel_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/talkLabel_leave.png");
	image_res.talkLabel_stay=XImage_LoadZip(L"qqImage.zip",L"qqImage/talkLabel_stay.png");
	image_res.talkLabel_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/talkLabel_check.png");

	image_res.talktbico1=XImage_LoadZip(L"qqImage.zip",L"qqImage/talktbico1.png");
	image_res.talktbico2=XImage_LoadZip(L"qqImage.zip",L"qqImage/talktbico2.png");
	image_res.talktbico3=XImage_LoadZip(L"qqImage.zip",L"qqImage/talktbico3.png");

	image_res.imp_shrink=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_shrink.png");
	image_res.imp_expand=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_expand.png");
	image_res.imp_icon_1=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_icon_1.png");
	image_res.imp_icon_2=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_icon_2.png");
	image_res.imp_icon_3=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_icon_3.png");
	image_res.imp_icon_4=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_icon_4.png");
	image_res.imp_icon_5=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_icon_5.png");
	image_res.imp_icon_6=XImage_LoadZip(L"qqImage.zip",L"qqImage/avatar/imp_icon_6.png");

	image_res.scroll_thumb_leave=XImage_LoadZipAdaptive(L"qqImage.zip",L"qqImage/scroll_thumb_leave.png",NULL,3,11,3,27);
	image_res.scroll_thumb_down=XImage_LoadZipAdaptive(L"qqImage.zip",L"qqImage/scroll_thumb_down.png",NULL,3,11,3,27);

	image_res.scroll_up_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/scroll_up_leave.png");
	image_res.scroll_up_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/scroll_up_Down.png");

	image_res.scroll_down_leave=XImage_LoadZip(L"qqImage.zip",L"qqImage/scroll_down_leave.png");
	image_res.scroll_down_down=XImage_LoadZip(L"qqImage.zip",L"qqImage/scroll_down_down.png");
}


void HandleButton_Close(HELE hClose)
{
	XEle_SetBkTransparent(hClose,TRUE);
	XEle_EnableFocus(hClose,FALSE);
	RECT rc={0,1,42,18};
	XEle_SetRect(hClose,&rc);
	XBtn_SetImageLeave(hClose,image_res.close_leave);
	XBtn_SetImageStay(hClose,image_res.close_stay);
	XBtn_SetImageDown(hClose,image_res.close_down);
}

void HandleButton_Max(HELE hMax)
{
	XEle_EnableFocus(hMax,FALSE);
	RECT rc={0,1,26,18};
	XEle_SetRect(hMax,&rc);
	XBtn_SetImageLeave(hMax,image_res.max_leave);
	XBtn_SetImageStay(hMax,image_res.max_stay);
	XBtn_SetImageDown(hMax,image_res.max_down);
}

void HandleButton_Min(HELE hMin)
{
	XEle_SetBkTransparent(hMin,TRUE);
	XEle_EnableFocus(hMin,FALSE);
	RECT rc={0,1,25,18};
	XEle_SetRect(hMin,&rc);
	XBtn_SetImageLeave(hMin,image_res.min_leave);
	XBtn_SetImageStay(hMin,image_res.min_stay);
	XBtn_SetImageDown(hMin,image_res.min_down);
}

void CreateWeatherButton(HWINDOW hWindow)
{
	hWeather=XBtn_Create(WINDOW_WIDTH-38-10,10,38,38,NULL,hWindow);
	XBtn_EnableCursorHand(hWeather,TRUE);
	XEle_SetBkTransparent(hWeather,TRUE);
	XBtn_SetImageLeave(hWeather,image_res.weather);
	XBtn_SetImageStay(hWeather,image_res.weather);
	XBtn_SetImageDown(hWeather,image_res.weather);
}

void HandleButton_Face(HELE hFace)
{
	XEle_SetBkTransparent(hFace,TRUE);
	XEle_EnableFocus(hFace,FALSE);
	XBtn_SetImageLeave(hFace,image_res.face_leave);
	XBtn_SetImageStay(hFace,image_res.face_stay);
	XBtn_SetImageDown(hFace,image_res.face_stay);
}

void HandleButton_UserState(HELE hUserState)
{
	XEle_SetBkTransparent(hUserState,TRUE);
	XEle_EnableFocus(hUserState,FALSE);
	XBtn_SetImageLeave(hUserState,image_res.userstate_leave);
	XBtn_SetImageStay(hUserState,image_res.userstate_stay);
	XBtn_SetImageDown(hUserState,image_res.userstate_down);
}

void HandleButton_UserSign(HELE hUserSign)
{
	XEle_SetBkTransparent(hUserSign,TRUE);
	XEle_EnableFocus(hUserSign,FALSE);
	XBtn_SetTextAlign(hUserSign,DT_SINGLELINE | DT_VCENTER);

	XBtn_SetImageLeave(hUserSign,image_res.button_leave);
	XBtn_SetImageStay(hUserSign,image_res.button_stay);
	XBtn_SetImageDown(hUserSign,image_res.button_down);
}

void HandleEdit_Search(HELE hSearch)
{
	XSView_SetSpacing(hSearch,8,5,35,0);
	XEle_EnableBorder(hSearch,FALSE);
	XSView_SetImage(hSearch,image_res.searchedit);
}

HELE CreateToolButton(HWINDOW hWindow,int x,int y,int cx,int cy)
{
	HELE hButton=XBtn_Create(x,y,cx,cy,NULL,hWindow);
	XEle_SetBkTransparent(hButton,TRUE);
	XEle_EnableFocus(hButton,FALSE);

	XBtn_SetImageLeave(hButton,image_res.button_leave);
	XBtn_SetImageStay(hButton,image_res.button_stay);
	XBtn_SetImageDown(hButton,image_res.button_down);

	return hButton;
}

HELE CreateToolSearchButton(HWINDOW hWindow)
{
	hButtonTool6=XBtn_Create(94,WINDOW_HEIGHT-50,60,22,NULL,hWindow);
	XEle_SetBkTransparent(hButtonTool6,TRUE);
	XEle_EnableFocus(hButtonTool6,FALSE);

	XBtn_SetImageLeave(hButtonTool6,image_res.button_leave);
	XBtn_SetImageStay(hButtonTool6,image_res.button_stay);
	XBtn_SetImageDown(hButtonTool6,image_res.button_down);

	XBtn_SetText(hButtonTool6,L"Search");
	XBtn_SetIcon(hButtonTool6,image_res.search);
	return hButtonTool6;
}

void HandleCreateToolButton(HWINDOW hWindow)
{
	HELE hButton=CreateToolButton(hWindow,10,52,22,20);
	XBtn_SetIcon(hButton,image_res.icon1);

	hButton=CreateToolButton(hWindow,32,52,22,20);
	XBtn_SetIcon(hButton,image_res.icon2);

	hButton=CreateToolButton(hWindow,54,52,22,20);
	XBtn_SetIcon(hButton,image_res.icon3);
////////////////////
	hButtonSkin=CreateToolButton(hWindow,WINDOW_WIDTH-10-22,52,22,20);
	XBtn_SetIcon(hButtonSkin,image_res.icon8);

	hButtonMsg=CreateToolButton(hWindow,WINDOW_WIDTH-10-22-22,52,22,20);
	XBtn_SetIcon(hButtonMsg,image_res.icon7);

//////////////////////
	hButtonTool1=CreateToolButton(hWindow,50,WINDOW_HEIGHT-73,22,22);
	XBtn_SetIcon(hButtonTool1,image_res.icon9);

	hButtonTool2=CreateToolButton(hWindow,72,WINDOW_HEIGHT-73,22,22);
	XBtn_SetIcon(hButtonTool2,image_res.icon10);

	hButtonTool3=CreateToolButton(hWindow,94,WINDOW_HEIGHT-73,22,22);
	XBtn_SetIcon(hButtonTool3,image_res.icon11);
/////////////////////////
	hButtonTool4=CreateToolButton(hWindow,50,WINDOW_HEIGHT-50,22,22);
	XBtn_SetIcon(hButtonTool4,image_res.icon15);

	hButtonTool5=CreateToolButton(hWindow,72,WINDOW_HEIGHT-50,22,22);
	XBtn_SetIcon(hButtonTool5,image_res.icon16);

	CreateToolSearchButton(hWindow);
}

void HandleCreateMainMenuButton(HWINDOW hWindow)
{
	hButtonMainMenu=XBtn_Create(3,WINDOW_HEIGHT-68,42,42,NULL,hWindow);
	XEle_SetBkTransparent(hButtonMainMenu,TRUE);
	XEle_EnableFocus(hButtonMainMenu,FALSE);
	XBtn_SetImageLeave(hButtonMainMenu,image_res.mainMenu_leave);
	XBtn_SetImageStay(hButtonMainMenu,image_res.mainMenu_stay);
	XBtn_SetImageDown(hButtonMainMenu,image_res.mainMenu_stay);

	//隐藏左侧工具条面板按钮
	hButtonHidePane=XBtn_Create(1,WINDOW_HEIGHT-76,15,15,NULL,hWindow);
	XEle_SetBkTransparent(hButtonHidePane,TRUE);
	XEle_EnableFocus(hButtonHidePane,FALSE);
	XBtn_SetImageLeave(hButtonHidePane,image_res.hideleftpanel_leave);
	XBtn_SetImageStay(hButtonHidePane,image_res.hideleftpanel_stay);
	XBtn_SetImageDown(hButtonHidePane,image_res.hideleftpanel_stay);
}

HELE HandleCreateLeftPaneButton(HELE hPic,int x,int y,int cx,int cy)
{
	HELE hButton=XBtn_Create(x,y,cx,cy,NULL,hPic);
	XEle_SetBkTransparent(hButton,TRUE);
	XEle_EnableFocus(hButton,FALSE);

	XBtn_SetImageLeave(hButton,image_res.tabLeft_leave);
	XBtn_SetImageStay(hButton,image_res.tabLeft_stay);
	XBtn_SetImageDown(hButton,image_res.tabLeft_down);
	XBtn_SetImageCheck(hButton,image_res.tabLeft_stay);

	return hButton;
}

void HandleCreateLeftPane(HWINDOW hWindow)
{
	hLeftPane=XPic_Create(0,99,33,WINDOW_HEIGHT-99-55-22,hWindow);
	XPic_SetImage(hLeftPane,image_res.leftpane);
	//XPic_EnableImageStretch(hLeftPane,TRUE);

	HELE hButton=HandleCreateLeftPaneButton(hLeftPane,0,3,30,30);
	XBtn_SetIcon(hButton,image_res.tab1);
	hButton=HandleCreateLeftPaneButton(hLeftPane,0,33,30,30);
	XBtn_SetIcon(hButton,image_res.tab2);
	hButton=HandleCreateLeftPaneButton(hLeftPane,0,63,30,30);
	XBtn_SetIcon(hButton,image_res.tab3);
}

//好友项
BOOL CALLBACK OnFriendsLButtonUp(HELE hEle,UINT flags,POINT *pPt) 
{
	int id=XTree_HitTest(hEle,pPt);
	if(group1==id || group2==id)
	{
		if(XTree_IsExpand(hEle,id))
		{
			XTree_SetItemImage(hTree,id,0);
			XTree_Expand(hEle,id,FALSE);
		}else
		{
			XTree_SetItemImage(hTree,id,1);
			XTree_Expand(hEle,id,TRUE);
		}
	}
	return FALSE;
}

void HandleCreateMainTab(HWINDOW hWindow)
{
	hTabBar=XTabBar_Create(33,99,WINDOW_WIDTH-6-33,30,hWindow);
	XEle_SetBkColor(hTabBar,RGB(255,0,0));
	XTabBar_AddLabel(hTabBar,L"");
	XTabBar_AddLabel(hTabBar,L"");
	XTabBar_AddLabel(hTabBar,L"");
	XTabBar_EnableTile(hTabBar,TRUE);
	/////////////////////////////////////
	HELE hButton=XTabBar_GetLabel(hTabBar,0);
	XEle_EnableFocus(hButton,FALSE);
	//XBtn_EnableImageStretch(hButton,TRUE);
	XBtn_SetIcon(hButton,image_res.talktbico1);

	XBtn_SetImageLeave(hButton,image_res.talkLabel_leave);
	XBtn_SetImageStay(hButton,image_res.talkLabel_stay);
	XBtn_SetImageDown(hButton,image_res.talkLabel_down);
	XBtn_SetImageCheck(hButton,image_res.talkLabel_down);

	///////////////////////////////
	hButton=XTabBar_GetLabel(hTabBar,1);
	XEle_EnableFocus(hButton,FALSE);
	//XBtn_EnableImageStretch(hButton,TRUE);
	XBtn_SetIcon(hButton,image_res.talktbico2);

	XBtn_SetImageLeave(hButton,image_res.talkLabel_leave);
	XBtn_SetImageStay(hButton,image_res.talkLabel_stay);
	XBtn_SetImageDown(hButton,image_res.talkLabel_down);
	XBtn_SetImageCheck(hButton,image_res.talkLabel_down);
	/////////////////////////////////
	hButton=XTabBar_GetLabel(hTabBar,2);
	XEle_EnableFocus(hButton,FALSE);
	//XBtn_EnableImageStretch(hButton,TRUE);
	XBtn_SetIcon(hButton,image_res.talktbico3);

	XBtn_SetImageLeave(hButton,image_res.talkLabel_leave);
	XBtn_SetImageStay(hButton,image_res.talkLabel_stay);
	XBtn_SetImageDown(hButton,image_res.talkLabel_down);
	XBtn_SetImageCheck(hButton,image_res.talkLabel_down);

	//好友列表
	hTree=XTree_Create(33,129,WINDOW_WIDTH-6-33,WINDOW_HEIGHT-130-55-22,hWindow);
	XTabBar_SetBindEle(hTabBar,0,hTree);
	XSView_SetSpacing(hTree,0,0,0,0);
	XTree_EnableLine(hTree,FALSE);
	XTree_EnableButton(hTree,FALSE);
	XTree_SetIndentation(hTree,0);
	XTree_SetItemHeight(hTree,28);
	XTree_SetSpacingLeft(hTree,10);

	HXCGUI hImageList1=XImageList_Create(11,6);
	XImageList_EnableFixedSize(hImageList1,TRUE);
	XImageList_AddImage(hImageList1,image_res.imp_shrink);
	XImageList_AddImage(hImageList1,image_res.imp_expand);

	XImageList_AddImage(hImageList1,image_res.imp_icon_1);
	XImageList_AddImage(hImageList1,image_res.imp_icon_2);
	XImageList_AddImage(hImageList1,image_res.imp_icon_3);
	XImageList_AddImage(hImageList1,image_res.imp_icon_4);
	XImageList_AddImage(hImageList1,image_res.imp_icon_5);
	XImageList_AddImage(hImageList1,image_res.imp_icon_6);

	XTree_SetImageList(hTree,hImageList1);
	group1=XTree_InsertItem(hTree,L"我的好友[6/9]",XTREE_ROOT,1);
	group2=XTree_InsertItem(hTree,L"同事[6/10]",XTREE_ROOT,1);

	XTree_InsertItem(hTree,L"梦飞",group1,3);
	wchar_t name[100]={0};
	for(int i=0;i<8;i++)
	{
		swprintf(name,L"炫彩好友-%d",i);
		XTree_InsertItem(hTree,name,group1, i%6+2);
	}

	for(int i=0;i<10;i++)
	{
		swprintf(name,L"炫彩好友-%d",i);
		XTree_InsertItem(hTree,name,group2, i%6+2);
	}

	HELE hScrollBar=XSView_GetVScrollBar(hTree);
	XSBar_SetImageLeaveSlider(hScrollBar,image_res.scroll_thumb_leave);
	XSBar_SetImageStaySlider(hScrollBar,image_res.scroll_thumb_leave);
	XSBar_SetImageDownSlider(hScrollBar,image_res.scroll_thumb_down);

	XSBar_SetImageLeaveUp(hScrollBar,image_res.scroll_up_leave);
	XSBar_SetImageStayUp(hScrollBar,image_res.scroll_up_leave);
	XSBar_SetImageDownUp(hScrollBar,image_res.scroll_up_down);

	XSBar_SetImageLeaveDown(hScrollBar,image_res.scroll_down_leave);
	XSBar_SetImageStayDown(hScrollBar,image_res.scroll_down_leave);
	XSBar_SetImageDownDown(hScrollBar,image_res.scroll_down_down);
	
	XEle_RegisterMessage(hTree,XM_LBUTTONUP,OnFriendsLButtonUp);
}

BOOL CALLBACK OnWndNCEndDrawWindow(HWINDOW hWindow,HDRAW hDraw)
{
	XDraw_HImage_(hDraw,image_res.hImageLogo,8,3);

	XDraw_TextOut_(hDraw,100,28,L"炫彩界面库",5);

	return FALSE;
}

BOOL CALLBACK OnWndSize(HWINDOW hWindow,UINT flags,SIZE *pSize)
{
	RECT rc={pSize->cx-38-10,10,pSize->cx-10,38};
	XEle_SetRect(hWeather,&rc);

	rc.left=60;
	rc.top=25;
	rc.right=pSize->cx-60;
	rc.bottom=45;
	XEle_SetRect(hUserSign,&rc);

	rc.left=pSize->cx-10-22;
	rc.top=52;
	rc.right=rc.left+22;
	rc.bottom=rc.top+20;
	XEle_SetRect(hButtonSkin,&rc);

	rc.left=pSize->cx-10-22-22;
	rc.top=52;
	rc.right=rc.left+22;
	rc.bottom=rc.top+20;
	XEle_SetRect(hButtonMsg,&rc);

	rc.left=33;
	rc.top=99;
	rc.right=pSize->cx-6;
	rc.bottom=rc.top+30;
	XEle_SetRect(hTabBar,&rc);

	rc.left=33;
	rc.top=129;
	rc.right=pSize->cx-6;
	rc.bottom=pSize->cy-56-22;
	XEle_SetRect(hTree,&rc);

	rc.left=1;
	rc.top=pSize->cy-76;
	rc.right=rc.left+15;
	rc.bottom=rc.top+15;
	XEle_SetRect(hButtonHidePane,&rc);

	rc.left=3;
	rc.top=pSize->cy-68;
	rc.right=rc.left+42;
	rc.bottom=rc.top+42;
	XEle_SetRect(hButtonMainMenu,&rc);

	rc.left=50;
	rc.top=pSize->cy-73;
	rc.right=rc.left+22;
	rc.bottom=rc.top+22;
	XEle_SetRect(hButtonTool1,&rc);

	rc.left=72;
	rc.top=pSize->cy-73;
	rc.right=rc.left+22;
	rc.bottom=rc.top+22;
	XEle_SetRect(hButtonTool2,&rc);

	rc.left=94;
	rc.top=pSize->cy-73;
	rc.right=rc.left+22;
	rc.bottom=rc.top+22;
	XEle_SetRect(hButtonTool3,&rc);

	rc.left=50;
	rc.top=pSize->cy-50;
	rc.right=rc.left+22;
	rc.bottom=rc.top+22;
	XEle_SetRect(hButtonTool4,&rc);

	rc.left=72;
	rc.top=pSize->cy-50;
	rc.right=rc.left+22;
	rc.bottom=rc.top+22;
	XEle_SetRect(hButtonTool5,&rc);

	rc.left=94;
	rc.top=pSize->cy-50;
	rc.right=rc.left+60;
	rc.bottom=rc.top+22;
	XEle_SetRect(hButtonTool6,&rc);

	rc.left=0;
	rc.top=99;
	rc.right=33;
	rc.bottom=pSize->cy-55-22;
	XEle_SetRect(hLeftPane,&rc);

	rc.left=1;
	rc.top=73;
	rc.right=pSize->cx-8;
	rc.bottom=rc.top+26;
	XEle_SetRect(hSearchEdit,&rc);
	return FALSE;
}

BOOL CALLBACK OnWndDestroy(HWINDOW hWindow) 
{
	if(image_res.hImageLogo)
		XImage_Destroy(image_res.hImageLogo);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	int style=XC_SY_DEFAULT&~XC_SY_DRAW_CAPTION_ICON;
	style&=~XC_SY_DRAW_CAPTION_TITLE;
	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,L"炫彩界面库-窗口",NULL,style);
	XWnd_EnableDragWindow(hWindow,TRUE);
	XWnd_SetBorderSize(hWindow,3,3,3,3);
	XWnd_SetRoundSize(hWindow,9);
	XWnd_SetCaptionHeight(hWindow,22);
	XWnd_SetMinWidth(hWindow,250);
	XWnd_SetMinHeight(hWindow,300);

	XWnd_EnableBorderStrokeInner(hWindow,FALSE);
	XWnd_EnableBorderStrokeOuter(hWindow,FALSE);

	LoadImageRes(); //加载图片资源

	//窗口背景图片
	XWnd_SetImageNC(hWindow,image_res.image_bk);

	//关闭按钮
	HELE hClose=XWnd_GetButtonClose(hWindow);
	HandleButton_Close(hClose);

	//最大化按钮
	HELE hMax=XWnd_GetButtonMax(hWindow);
	HandleButton_Max(hMax);

	//最小化按钮
	HELE hMin=XWnd_GetButtonMin(hWindow);
	HandleButton_Min(hMin);

	//天气
	CreateWeatherButton(hWindow);

	//头像
	HELE hFace=XBtn_Create(10,0,48,48,NULL,hWindow);
	XBtn_EnableCursorHand(hFace,TRUE);
	HandleButton_Face(hFace);

	//状态
	HELE hUserState=XBtn_Create(60,0,32,22,NULL,hWindow);
	HandleButton_UserState(hUserState);

	//签名
	hUserSign=XBtn_Create(60,25,WINDOW_WIDTH-60-62,20,L"签名:www.xcgui.com",hWindow);
	HandleButton_UserSign(hUserSign);

	//搜索框
	hSearchEdit=XEdit_Create(1,73,WINDOW_WIDTH-8,28,hWindow);
	HandleEdit_Search(hSearchEdit);

	//创建工具按钮
	HandleCreateToolButton(hWindow);

	//主菜单按钮
	HandleCreateMainMenuButton(hWindow);

	//创建左边工具面板
	HandleCreateLeftPane(hWindow);

	//tab页
	HandleCreateMainTab(hWindow);

	XWnd_Adjust(hWindow);

	XWnd_RegisterNCMessage(hWindow,XWM_NCENDPAINT,OnWndNCEndDrawWindow);
	XWnd_RegisterMessage(hWindow,WM_SIZE,OnWndSize);
	XWnd_RegisterMessage(hWindow,WM_DESTROY,OnWndDestroy);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}
#endif