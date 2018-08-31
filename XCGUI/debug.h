/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


#ifdef _DEBUG

#define  DebugBox(msg) MessageBoxW(NULL,msg,L"炫彩界面库-错误提示!",MB_OK);

//句柄错误检查提示
void DebugBox_CheckHandle(char *pFunName, char *pHandle);

void AddTypeDebug(HXCGUI hXCGUI, int type);//将窗口或元素类型添加到表中

void IsWindowDebug(HWINDOW hWindow, char *pFunName); //已处理
void IsModalWindowDebug(HWINDOW hWindow, char *pFunName); //已处理
//void IsPopupMenuWindowDebug(HWINDOW hWindow,char *pFunName); //已处理
void IsFrameWindowDebug(HWINDOW hWindow, char *pFunName); //已处理

void IsEleDebug(HELE hEle, char *pFunName);  //已处理
void IsButtonDebug(HELE hEle, char *pFunName); //已处理
void IsCheckDebug(HELE hEle, char *pFunName); //已处理
void IsRadioDebug(HELE hEle, char *pFunName); //已处理
void IsEditDebug(HELE hEle, char *pFunName);  //已处理
void IsComboBoxDebug(HELE hEle, char *pFunName); //已处理
void IsScrollBarDebug(HELE hEle, char *pFunName); //已处理
void IsScrollViewDebug(HELE hEle, char *pFunName); //已处理
void IsListDebug(HELE hEle, char *pFunName); //已处理
void IsListBoxDebug(HELE hEle, char *pFunName); //已处理
void IsTreeDebug(HELE hEle, char *pFunName);  //已处理
void IsMenuBarDebug(HELE hEle, char *pFunName); //已处理
void IsPropertyPageDebug(HELE hEle, char *pFunName); //已处理
void IsSliderDebug(HELE hEle, char *pFunName); //已处理
void IsProgressBarDebug(HELE hEle, char *pFunName); //已处理
void IsToolBarDebug(HELE hEle, char *pFunName); //已处理
void IsToolBarBtnDebug(HELE hEle, char *pFunName); //已处理
void IsStaticDebug(HELE hEle, char *pFunName); //已处理
void IsGroupBoxDebug(HELE hEle, char *pFunName);  //已处理
void IsPictureDebug(HELE hEle, char *pFunName);  //已处理
void IsMonthCalDebug(HELE hEle, char *pFunName);  //已处理
void IsDateTimeDebug(HELE hEle, char *pFunName);  //已处理
void IsPGridDebug(HELE hEle, char *pFunName);  //属性网格
void IsChooseColorDebug(HELE hEle, char *pFunName);  //颜色选择
void IsTextLinkDebug(HELE hEle, char *pFunName); //静态文本链接
void IsTabBarDebug(HELE hEle, char *pFunName); //TabBar
void IsGifDebug(HELE hEle, char *pFunName);  //GIF
void IsListViewDebug(HELE hEle, char *pFunName);  //ListView
void IsEditFileDebug(HELE hEle, char *pFunName);  //EditFile
void IsPaneDebug(HELE hEle, char *pFunName); //pane
void IsRichEditDebug(HELE hEle, char *pFunName); //RichEdit

//Outlook

void IsArrayDebug(HARRAY hArray, char *pFunName); //已处理
void IsStringDeBug(HSTRING hString, char *pFunName); //已处理
void IsImageListDebug(HXCGUI hImageList, char *pFunName); //已处理
void IsMenuDebug(HMENUX hMenu, char *pFunName); //检查菜单
void IsHImageDebug(HIMAGE hImage, char *pFunName); //炫彩图片
void IsDrawDebug(HDRAW hDraw, char *pFunName);
void IsFontDebug(HFONTX hFontX, char *pFunName);

void IsImageTypeDebug(wchar_t *pFunName, wchar_t *pImageFile); //检查图片类型



#else
#define  DebugBox(msg)

#define AddTypeDebug(hXCGUI,type);//将窗口或元素类型添加到表中

#define IsWindowDebug(hWindow,pFunName); //已处理
#define IsModalWindowDebug(hWindow,pFunName);  //已处理
//#define IsPopupMenuWindowDebug(hWindow,pFunName);  //已处理
#define IsFrameWindowDebug(hWindow,pFunName);  //已处理

#define IsEleDebug(hEle,pFunName);  //已处理
#define IsButtonDebug(hEle,pFunName); //已处理
#define IsCheckDebug(hEle,pFunName); //已处理
#define IsRadioDebug(hEle,pFunName); //已处理
#define IsEditDebug(hEle,pFunName);  //已处理
#define IsComboBoxDebug(hEle,pFunName); //已处理
#define IsScrollBarDebug(hEle,pFunName); //已处理
#define IsScrollViewDebug(hEle,pFunName); //已处理
#define IsListDebug(hEle,pFunName); //已处理
#define IsListBoxDebug(hEle,pFunName); //已处理
#define IsTreeDebug(hEle,pFunName);  //已处理
#define IsMenuBarDebug(hEle,pFunName); //已处理
#define IsPropertyPageDebug(hEle,pFunName); //已处理
#define IsSliderDebug(hEle,pFunName); //已处理
#define IsProgressBarDebug(hEle,pFunName); //已处理
#define IsToolBarDebug(hEle,pFunName); //已处理
#define IsToolBarBtnDebug(hEle,pFunName);  //已处理
#define IsStaticDebug(hEle,pFunName); //已处理
#define IsGroupBoxDebug(hEle,pFunName); //已处理
#define IsPictureDebug(hEle,pFunName); //已处理
#define IsMonthCalDebug(hEle,pFunName); //已处理
#define IsDateTimeDebug(hEle,pFunName); //已处理
#define IsPGridDebug(hEle,pFunName); //已处理
#define IsChooseColorDebug(hEle,pFunName); //颜色选择
#define IsTextLinkDebug(hEle,pFunName); //静态文本链接
#define IsTabBarDebug(hEle,pFunName);  //TabBar
#define IsGifDebug(hEle,pFunName);  //GIF
#define IsListViewDebug(hEle,pFunName);  //ListView
#define IsEditFileDebug(hEle,pFunName);  //EditFile
#define IsPaneDebug(hEle,pFunName);
#define IsRichEditDebug(hEle,pFunName); //RichEdit

#define IsArrayDebug(hArray,pFunName); //已处理
#define IsStringDeBug(hString,pFunName); //已处理
#define IsImageListDebug(hImageList,pFunName); //已处理
#define IsMenuDebug(hMenu,pFunName);//已处理
#define IsHImageDebug(hImage,pFunName); //炫彩图片
#define IsDrawDebug(hDraw,pFunName);
#define IsFontDebug(hFontX,pFunName);

#define IsImageTypeDebug(pFunName,pImageFile); //检查图片类型
#endif

