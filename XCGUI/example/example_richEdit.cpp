/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


//////////////////RichEdit////////////////////////////////////////////
#if 0

HELE hRichEdit=NULL;
LOGFONT  Font1;
LOGFONT  Font2;
LOGFONT  Font3;
LOGFONT  Font4;
LOGFONT  Font5;
LOGFONT  Font6;
LOGFONT  Font7;

BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle) //按钮点击事件
{
	XRichEdit_Select(hRichEdit, 0, 0, 10000, 1000);
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick2(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int row=0;
	int column=0;
	XRichEdit_GetCurrentPos(hRichEdit,&row,&column);
	HIMAGE hImage=XImage_LoadFile(L"image\\touxiang.jpg");
	XRichEdit_InsertImage(hRichEdit,hImage,L"image\\touxiang.jpg",row,column);
	XEle_RedrawEle(hRichEdit);
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick3(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int row=0;
	int column=0;
	XRichEdit_GetCurrentPos(hRichEdit,&row,&column);
	XRichEdit_InsertImageGif(hRichEdit,L"image\\hearts.gif",row,column);
	XEle_RedrawEle(hRichEdit);
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick4(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int row=0;
	int column=0;
	XRichEdit_GetCurrentPos(hRichEdit,&row,&column);
	XRichEdit_InsertImageGif(hRichEdit,L"gif\\111.gif",row,column);
	XEle_RedrawEle(hRichEdit);
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick5(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int row=0;
	int column=0;
	XRichEdit_GetCurrentPos(hRichEdit,&row,&column);
	XRichEdit_InsertImageGif(hRichEdit,L"gif\\222.gif",row,column);
	XEle_RedrawEle(hRichEdit);
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick6(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font1);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}
BOOL CALLBACK MyEventBtnClick7(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font2);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick8(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font3);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick9(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font4);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick10(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font5);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick11(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font6);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick12(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int	BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemFontEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,&Font7);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

HELE hColor=NULL;
BOOL CALLBACK OnEventEditChange(HELE hEle,HELE hEventEle)
{
	COLORREF color=XCHColor_GetColor(hColor);

	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		XRichEdit_SetItemColorEx(hRichEdit,BeginRow,BeginColumn,EndRow,EndColumn,color);
		XEle_RedrawEle(hRichEdit);
	}
	return TRUE;
}

BOOL CALLBACK MyEventBtnClick1_Test(HELE hEle,HELE hEventEle) //按钮点击事件
{
	int row=0;
	int column=1;

	XRichEdit_SelectAll(hRichEdit);

	XEle_RedrawEle(hRichEdit);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,550,450,L"炫彩界面库-窗口");
	XWnd_EnableDragBorder(hWindow,FALSE);

	HELE hButton=XBtn_Create(10,10,60,22,L"插入元素",hWindow);
	//XEle_EnableEle(hButton,FALSE);
	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	HELE hButton2=XBtn_Create(80,10,60,22,L"插入图片",hWindow);
	XEle_EnableFocus(hButton2,FALSE);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,MyEventBtnClick2);

	HELE hButton3=XBtn_Create(150,10,60,22,L"插入GIF",hWindow);
	XEle_EnableFocus(hButton3,FALSE);
	XEle_RegisterEvent(hButton3,XE_BNCLICK,MyEventBtnClick3);

	HELE hButton4=XBtn_Create(220,10,60,22,L"插入GIF",hWindow);
	XEle_EnableFocus(hButton4,FALSE);
	XEle_RegisterEvent(hButton4,XE_BNCLICK,MyEventBtnClick4);

	HELE hButton5=XBtn_Create(290,10,60,22,L"插入GIF",hWindow);
	XEle_EnableFocus(hButton5,FALSE);
	XEle_RegisterEvent(hButton5,XE_BNCLICK,MyEventBtnClick5);

	hRichEdit=XRichEdit_Create(10,40,390,350,hWindow); //创建RichEdit

	HELE hView=XSView_GetView(hRichEdit);
	XEle_SetBkColor(hView,RGB(220,220,220));

	//创建字体
	XC_InitFont(&Font1,L"宋体",12);
	XC_InitFont(&Font2,L"宋体",16);
	XC_InitFont(&Font3,L"宋体",20);
	XC_InitFont(&Font4,L"宋体",28);
	XC_InitFont(&Font5,L"宋体",16,TRUE);
	XC_InitFont(&Font6,L"宋体",16,FALSE,TRUE);
	XC_InitFont(&Font7,L"宋体",16,FALSE,FALSE,TRUE);

	XStatic_Create(420,30,100,20,L"设置字体:",hWindow);

	HELE hButtonFont1=XBtn_Create(420,50,100,22,L"字体 12号",hWindow);	//12
	HELE hButtonFont2=XBtn_Create(420,80,100,22,L"字体 16号",hWindow); //16
	HELE hButtonFont3=XBtn_Create(420,110,100,22,L"字体 20号",hWindow); //20
	HELE hButtonFont4=XBtn_Create(420,140,100,22,L"字体 28号",hWindow); //28

	HELE hButtonFont5=XBtn_Create(420,170,100,22,L"粗体 16号",hWindow);//粗体16号
	HELE hButtonFont6=XBtn_Create(420,200,100,22,L"斜体 16号",hWindow);//斜体16号
	HELE hButtonFont7=XBtn_Create(420,230,100,22,L"下划线 16号",hWindow);//下弧线16号

	XEle_EnableFocus(hButtonFont1,FALSE);
	XEle_EnableFocus(hButtonFont2,FALSE);
	XEle_EnableFocus(hButtonFont3,FALSE);
	XEle_EnableFocus(hButtonFont4,FALSE);
	XEle_EnableFocus(hButtonFont5,FALSE);
	XEle_EnableFocus(hButtonFont6,FALSE);
	XEle_EnableFocus(hButtonFont7,FALSE);

	XEle_RegisterEvent(hButtonFont1,XE_BNCLICK,MyEventBtnClick6);
	XEle_RegisterEvent(hButtonFont2,XE_BNCLICK,MyEventBtnClick7);
	XEle_RegisterEvent(hButtonFont3,XE_BNCLICK,MyEventBtnClick8);
	XEle_RegisterEvent(hButtonFont4,XE_BNCLICK,MyEventBtnClick9);
	XEle_RegisterEvent(hButtonFont5,XE_BNCLICK,MyEventBtnClick10);
	XEle_RegisterEvent(hButtonFont6,XE_BNCLICK,MyEventBtnClick11);
	XEle_RegisterEvent(hButtonFont7,XE_BNCLICK,MyEventBtnClick12);

	XStatic_Create(420,265,100,20,L"设置颜色:",hWindow);
	hColor=XCHColor_Create(420,290,100,22,hWindow);
	XEle_RegisterEvent(hColor,XE_EDIT_CHANGE,OnEventEditChange);

	HELE hButtonTest=XBtn_Create(420,320,100,20,L"测试",hWindow);
	XEle_EnableFocus(hButtonTest,FALSE);
	XEle_RegisterEvent(hButtonTest,XE_BNCLICK,MyEventBtnClick1_Test);

	//XRichEdit_SetText(hRichEdit,L"123456");

	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();

	return 0;
}

#endif

///////////////////////////////////////////
///////////////////////////////////////////

#if 0

HELE hRichEdit1=NULL;       //RichEdit  1
HELE hRichEdit2=NULL;       //RichEdit  2
HELE hColor=NULL;           //当前默认字体颜色
HELE hCombox_fontName=NULL; //默认字体名称
HELE hFontSize=NULL;        //默认字体大小
HELE hBold=NULL;            //默认属性 粗体
HELE hItalic=NULL;          //默认属性 斜体
HELE hUnderline=NULL;       //默认属性 下划线

HFONT hFont=NULL;           //默认字体
BOOL  bBold=FALSE;          //粗体
BOOL  bItalic=FALSE;        //斜体
BOOL  bUnderline=FALSE;     //下划线

void OnFontChangT() //字体改变
{
	wchar_t name[MAX_PATH]={0};

	XComboBox_GetText(hCombox_fontName,name,MAX_PATH);;
	int   size=XEdit_GetInt(hFontSize);

	HFONT hFontT=XC_CreateFont(name,size,bBold,bItalic,bUnderline);
	XEle_SetFont(hRichEdit2,hFontT);

	if (hFont) //释放先前字体
		DeleteObject(hFont);
	hFont=hFontT;
	XEle_RedrawEle(hRichEdit2);
}

//默认字体颜色改变
BOOL CALLBACK OnEventEditChange_default_color(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	COLORREF color1=XEle_GetTextColor(hRichEdit2);
	COLORREF color2=XCHColor_GetColor(hColor);
	if (color1!=color2)
	{
		XEle_SetTextColor(hRichEdit2,color2);
		XEle_RedrawEle(hRichEdit2);
	}
	return TRUE;
}

//默认字体名称改变
BOOL CALLBACK OnEventComboBoxSelect_default_fontName(HELE hEle,HELE hEventEle,int index)
{
	if(hEle != hEventEle) return FALSE;

	OnFontChangT(); //字体改变
	return TRUE;
}

//默认字体大小改变
BOOL CALLBACK OnEventComboBoxSelect_default_fontSize(HELE hEle,HELE hEventEle,int index)
{
	if(hEle != hEventEle) return FALSE;
	OnFontChangT(); //字体改变
	return TRUE;
}

//默认设置 粗体
BOOL CALLBACK OnEventBtnClick_default_bold(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;
	bBold=~bBold;
	if(bBold)
		XBtn_SetText(hBold,L"B√");
	else
		XBtn_SetText(hBold,L"B");
	OnFontChangT(); //字体改变
	return TRUE;
}

//默认设置 斜体
BOOL CALLBACK OnEventBtnClick_default_italic(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	bItalic=~bItalic;
	if(bItalic)
		XBtn_SetText(hItalic,L"/√");
	else
		XBtn_SetText(hItalic,L"/");
	OnFontChangT(); //字体改变
	return TRUE;
}

//默认设置 下划线
BOOL CALLBACK OnEventBtnClick_default_underline(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	bUnderline=~bUnderline;
	if(bUnderline)
		XBtn_SetText(hUnderline,L"&U√");
	else
		XBtn_SetText(hUnderline,L"&U");
	OnFontChangT(); //字体改变
	return TRUE;
}
////////设置选择内容////////////////////////////////////////////////////////////
HELE hColor2=NULL;           //当前默认字体颜色
HELE hCombox_fontName2=NULL; //默认字体名称  
HELE hFontSize2=NULL;        //默认字体大小
HELE hBold2=NULL;            //默认属性 粗体
HELE hItalic2=NULL;          //默认属性 斜体
HELE hUnderline2=NULL;       //默认属性 下划线

HFONT hFont2=NULL; //默认字体
BOOL  bBold2=FALSE;
BOOL  bItalic2=FALSE;
BOOL  bUnderline2=FALSE;

//选择内容颜色改变
BOOL CALLBACK OnEventEditChange_select_color(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	COLORREF color1=XEle_GetTextColor(hRichEdit2);
	COLORREF color2=XCHColor_GetColor(hColor2);
	if (color1!=color2)
	{
		int BeginRow=0;
		int	BeginColumn=0;
		int	EndRow=0;
		int	EndColumn=0;
		if(XRichEdit_GetSelectPos(hRichEdit2,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
		{
			XRichEdit_SetItemColorEx(hRichEdit2,BeginRow,BeginColumn,EndRow,EndColumn,color2);
			XEle_RedrawEle(hRichEdit2);
		}

	}
	return TRUE;
}

void OnFontChangT2() //选择内容 字体改变
{
	wchar_t name[MAX_PATH]={0};

	XComboBox_GetText(hCombox_fontName2,name,MAX_PATH);;
	int   size=XEdit_GetInt(hFontSize2);

	int BeginRow=0;
	int	BeginColumn=0;
	int	EndRow=0;
	int	EndColumn=0;
	if(XRichEdit_GetSelectPos(hRichEdit2,&BeginRow,&BeginColumn,&EndRow,&EndColumn))
	{
		LOGFONT  font;
		XC_InitFont(&font,name,size,bBold2,bItalic2,bUnderline2);
		XRichEdit_SetItemFontEx(hRichEdit2,BeginRow,BeginColumn,EndRow,EndColumn,&font);
		XEle_RedrawEle(hRichEdit2);
	}
}

//选择内容 字体名称改变
BOOL CALLBACK OnEventComboBoxSelect_select_fontName(HELE hEle,HELE hEventEle,int index)
{
	if(hEle != hEventEle) return FALSE;

	OnFontChangT2(); //字体改变
	return TRUE;
}

//选择内容  字体大小改变
BOOL CALLBACK OnEventComboBoxSelect_select_fontSize(HELE hEle,HELE hEventEle,int index)
{
	if(hEle != hEventEle) return FALSE;
	OnFontChangT2(); //字体改变
	return TRUE;
}

//选择内容  设置粗体
BOOL CALLBACK OnEventBtnClick_select_bold(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;
	bBold2=~bBold2;
	if(bBold2)
		XBtn_SetText(hBold2,L"B√");
	else
		XBtn_SetText(hBold2,L"B");
	OnFontChangT2(); //字体改变
	return TRUE;
}

//选择内容 设置 斜体
BOOL CALLBACK OnEventBtnClick_select_italic(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	bItalic2=~bItalic2;
	if(bItalic2)
		XBtn_SetText(hItalic2,L"/√");
	else
		XBtn_SetText(hItalic2,L"/");
	OnFontChangT2(); //字体改变
	return TRUE;
}

//选择内容  设置 下划线
BOOL CALLBACK OnEventBtnClick_select_underline(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	bUnderline2=~bUnderline2;
	if(bUnderline2)
		XBtn_SetText(hUnderline2,L"&U√");
	else
		XBtn_SetText(hUnderline2,L"&U");
	OnFontChangT2(); //字体改变
	return TRUE;
}

//插入图片
BOOL CALLBACK OnEventBtnClick_Image(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	int row=0;
	int column=0;
	XRichEdit_GetCurrentPos(hRichEdit2,&row,&column);
	HIMAGE hImage=XImage_LoadFile(L"image\\tou.jpg");
	XRichEdit_InsertImage(hRichEdit2,hImage,L"image\\tou.jpg",row,column);
	XEle_RedrawEle(hRichEdit2);
	return TRUE;
}

//插入GIF
BOOL CALLBACK OnEventBtnClick_GIF(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	int row=0;
	int column=0;
	XRichEdit_GetCurrentPos(hRichEdit2,&row,&column);
	XRichEdit_InsertImageGif(hRichEdit2,L"gif\\222.gif",row,column);
	XEle_RedrawEle(hRichEdit2);
	return TRUE;
}

BOOL CALLBACK OnEventBtnClick_Send(HELE hEle,HELE hEventEle)
{
	if(hEle != hEventEle) return FALSE;

	SYSTEMTIME timeT;
	GetLocalTime(&timeT);

	wchar_t name[MAX_PATH];
	wsprintf(name,L"炫彩界面库(154460336) %d:%d:%d\n",timeT.wHour,timeT.wMinute,timeT.wSecond);

	int row=XRichEdit_GetRowCount(hRichEdit1)-1;
	int column=XRichEdit_GetRowItemCount(hRichEdit1,row);
	XRichEdit_InsertTextEx(hRichEdit1,name,row,column,NULL,TRUE,RGB(0,0,255));

	row=XRichEdit_GetRowCount(hRichEdit1)-1;
	column=XRichEdit_GetRowItemCount(hRichEdit1,row);
	void *data=XRichEdit_GetData(hRichEdit2);
	XRichEdit_InsertData(hRichEdit1,data,row,column);
	XC_Free(data);

	row=XRichEdit_GetRowCount(hRichEdit1)-1;
	column=XRichEdit_GetRowItemCount(hRichEdit1,row);
	XRichEdit_InsertText(hRichEdit1,L"\n",row,column);

	XRichEdit_Adjust(hRichEdit1);
	XSView_ScrollBottom(hRichEdit1);
	XEle_RedrawEle(hRichEdit1);

	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//创建窗口
	HWINDOW hWindow=XWnd_CreateWindow(0,0,550,450,L"炫彩界面库-窗口-RichEdit");
	XWnd_EnableDragBorder(hWindow,FALSE);
	XWnd_SetBkColor(hWindow,RGB(230,242,253));

	int top=2;
	hRichEdit1=XRichEdit_Create(2,top,530,200,hWindow); //创建RichEdit 1
	XEle_SetBkColor(XSView_GetView(hRichEdit1),RGB(240,240,240));
	XRichEdit_SetReadOnly(hRichEdit1,TRUE);
	top+=200;

	HELE hToolBarEle=XEle_Create(2,top,530,68,hWindow);
	XEle_SetBkColor(hToolBarEle,RGB(230,242,253));
	XEle_EnableBorder(hToolBarEle,FALSE);
	top+=68;

	hRichEdit2=XRichEdit_Create(2,top,530,110,hWindow); //创建RichEdit 2
	XRichEdit_SetText(hRichEdit2,L"待发送的文本内容123456.");
	top+=112;
	HELE hBtnSend=XBtn_Create(530-60,top,60,22,L"发送",hWindow);
	XEle_EnableFocus(hBtnSend,FALSE);

	////////默认属性///////////////////////////////
	int left=5;
	HELE hStatic1=XStatic_Create(left,2,60,20,L"默认属性:",hToolBarEle);	//默认属性
	XEle_SetBkTransparent(hStatic1,TRUE);
	left+=62;

	hColor=XCHColor_Create(left,2,75,20,hToolBarEle); //颜色
	XCHColor_SetColor(hColor,RGB(0,0,0));
	left+=77;

	//字体名称
	hCombox_fontName=XComboBox_Create(left,2,80,20,hToolBarEle);
	XComboBox_EnableEdit(hCombox_fontName,FALSE);
	XComboBox_AddString(hCombox_fontName,L"宋体");
	XComboBox_AddString(hCombox_fontName,L"隶书");
	XComboBox_AddString(hCombox_fontName,L"方正舒体");
	XComboBox_AddString(hCombox_fontName,L"华文彩云");
	XComboBox_SetSelectItem(hCombox_fontName,0);
	left+=82;

	hFontSize=XComboBox_Create(left,2,60,20,hToolBarEle); //字体大小
	XComboBox_EnableEdit(hFontSize,FALSE);
	XComboBox_AddString(hFontSize,L"12");
	XComboBox_AddString(hFontSize,L"14");
	XComboBox_AddString(hFontSize,L"16");
	XComboBox_AddString(hFontSize,L"18");
	XComboBox_AddString(hFontSize,L"20");
	XComboBox_SetSelectItem(hFontSize,0);
	left+=62;

	hBold=XBtn_Create(left,2,30,20,L"B",hToolBarEle); //粗体
	left+=32;

	hItalic=XBtn_Create(left,2,30,20,L"/",hToolBarEle); //斜体
	left+=32;
	hUnderline=XBtn_Create(left,2,30,20,L"&U",hToolBarEle); //下划线

	//////////选择属性//////////////////////////////////////
	left=5;
	HELE hStatic2=XStatic_Create(left,24,60,20,L"选择属性:",hToolBarEle);
	XEle_SetBkTransparent(hStatic2,TRUE);
	left+=62;
	hColor2=XCHColor_Create(left,24,75,20,hToolBarEle); //颜色
	left+=77;

	//字体名称
	hCombox_fontName2=XComboBox_Create(left,24,80,20,hToolBarEle);
	XComboBox_EnableEdit(hCombox_fontName2,FALSE);
	XComboBox_AddString(hCombox_fontName2,L"宋体");
	XComboBox_AddString(hCombox_fontName2,L"隶书");
	XComboBox_AddString(hCombox_fontName2,L"方正舒体");
	XComboBox_AddString(hCombox_fontName2,L"华文彩云");
	XComboBox_SetSelectItem(hCombox_fontName2,0);
	left+=82;

	hFontSize2=XComboBox_Create(left,24,60,20,hToolBarEle); //字体大小
	XComboBox_EnableEdit(hFontSize2,FALSE);
	XComboBox_AddString(hFontSize2,L"12");
	XComboBox_AddString(hFontSize2,L"14");
	XComboBox_AddString(hFontSize2,L"16");
	XComboBox_AddString(hFontSize2,L"18");
	XComboBox_AddString(hFontSize2,L"20");
	XComboBox_SetSelectItem(hFontSize2,0);
	left+=62;

	hBold2=XBtn_Create(left,24,30,20,L"B",hToolBarEle); //粗体
	left+=32;

	hItalic2=XBtn_Create(left,24,30,20,L"/",hToolBarEle); //斜体
	left+=32;
	hUnderline2=XBtn_Create(left,24,30,20,L"&U",hToolBarEle); //下划线

	///////////////////////////////////////////////////
	left=5;
	HELE hBtnImage=XBtn_Create(left,46,60,20,L"图片",hToolBarEle); //插入图片
	left+=64;
	HELE hBtnGif=XBtn_Create(left,46,60,20,L"GIF",hToolBarEle);//插入GIF

	XEle_RegisterEvent(hCombox_fontName,XE_COMBOBOX_SELECT,OnEventComboBoxSelect_default_fontName);
	XEle_RegisterEvent(hColor,XE_EDIT_CHANGE,OnEventEditChange_default_color);
	XEle_RegisterEvent(hFontSize,XE_COMBOBOX_SELECT,OnEventComboBoxSelect_default_fontSize);
	XEle_RegisterEvent(hBold,XE_BNCLICK,OnEventBtnClick_default_bold);
	XEle_RegisterEvent(hItalic,XE_BNCLICK,OnEventBtnClick_default_italic);
	XEle_RegisterEvent(hUnderline,XE_BNCLICK,OnEventBtnClick_default_underline);

	XEle_RegisterEvent(hCombox_fontName2,XE_COMBOBOX_SELECT,OnEventComboBoxSelect_select_fontName);
	XEle_RegisterEvent(hColor2,XE_EDIT_CHANGE,OnEventEditChange_select_color);
	XEle_RegisterEvent(hFontSize2,XE_COMBOBOX_SELECT,OnEventComboBoxSelect_select_fontSize);
	XEle_RegisterEvent(hBold2,XE_BNCLICK,OnEventBtnClick_select_bold);
	XEle_RegisterEvent(hItalic2,XE_BNCLICK,OnEventBtnClick_select_italic);
	XEle_RegisterEvent(hUnderline2,XE_BNCLICK,OnEventBtnClick_select_underline);

	XEle_RegisterEvent(hBtnImage,XE_BNCLICK,OnEventBtnClick_Image);
	XEle_RegisterEvent(hBtnGif,XE_BNCLICK,OnEventBtnClick_GIF);
	XEle_RegisterEvent(hBtnSend,XE_BNCLICK,OnEventBtnClick_Send);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}


#endif