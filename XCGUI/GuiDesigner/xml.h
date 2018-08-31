/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


#define GET_RECT(pLabel) pLabel->Attribute("left",&left);	pLabel->Attribute("top",&top);	pLabel->Attribute("width",&width);	pLabel->Attribute("height",&height);



//API:

//载入窗口XML布局文件
XC_API HWINDOW WINAPI XC_LoadXML_Window(wchar_t *pFileName, HXMLRES hXmlRes = NULL, HWND hWndParent = NULL);

//载入窗口XML布局文件,从资源
XC_API HWINDOW WINAPI XC_LoadXML_WindowRes(int resID, wchar_t *pType, HXMLRES hXmlRes = NULL, HWND hWndParent = NULL);

//载入XML布局页文件
XC_API BOOL WINAPI XC_LoadXML_Page(HXCGUI hParent, wchar_t *pFileName, HXMLRES hXmlRes = NULL);

//载入XML布局页文件,从资源
XC_API BOOL WINAPI XC_LoadXML_PageRes(HXCGUI hParent, int resID, wchar_t *pType, HXMLRES hXmlRes = NULL);

HWINDOW XC_LoadXML_WindowRes2(char *pData, HXMLRES hXmlRes, HWND hWndParent);
BOOL XC_LoadXML_PageRes2(HXCGUI hParent, char *pData, HXMLRES hXmlRes);

////////////////////////////////////////////////
HWINDOW XC_LoadXML_WindowX(TiXmlElement *pRoot, HXMLRES hXmlRes, HWND hWndParent);
BOOL XC_LoadXML_PageX(TiXmlElement *pRoot, HXMLRES hXmlRes, HXCGUI hParent);

HWINDOW XML_HandleWindow(TiXmlElement *pLabel, HXMLRES hXmlRes, HWND hWndParent);//处理窗口
HWINDOW XML_HandleModalWindow(TiXmlElement *pLabel, HXMLRES hXmlRes, HWND hWndParent);
HWINDOW XML_HandleFrameWindow(TiXmlElement *pLabel, HXMLRES hXmlRes, HWND hWndParent);
HWINDOW XML_HandlePage(TiXmlElement *pLabel, HXMLRES hXmlRes, HWND hWndParent);

BOOL XML_HandlePanes(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL XML_HandlePane(TiXmlElement *pLabel, HWINDOW hWindow);

BOOL XML_HandlePaneGroup(TiXmlElement *pLabel, HWINDOW hWindow);
HELE XML_HandlePaneGroupMember1(TiXmlElement *pLabel, HWINDOW hWindow, HELE hDestPane, align_type_ align);
HPANE_GROUP XML_HandlePaneGroupMember2(TiXmlElement *pLabel, HWINDOW hWindow, HELE hDestPane);
BOOL XML_HandlePaneGroupMember3(TiXmlElement *pLabel, HWINDOW hWindow, HPANE_GROUP hGroup);
//BOOL XML_HandlePaneGroupMember(TiXmlElement *pLabel,HWINDOW hWindow);

//获取ID
int XML_GetEleId(TiXmlElement *pLabel, HXMLRES hXmlRes);

//处理子元素
BOOL XML_HandleChildEle(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

//分类处理
BOOL XML_SwitchEle(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

//创建元素
HELE XML_CreateEle(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateButton(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateRadio(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateCheck(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateEdit(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

HELE XML_CreateComboBox(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateScrollBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateScrollView(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateList(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateListBox(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

HELE XML_CreateTree(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateMenuBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreatePPage(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateSlider(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateProgressBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateToolBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateStatic(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

HELE XML_CreateGroupBox(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreatePicture(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateMonthCal(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateDateTime(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreatePGrid(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreateChooseColor(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);
HELE XML_CreatePropertyPageLabel(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

HELE XML_CreatePane(TiXmlElement *pLabel, HXMLRES hXmlRes, HXCGUI hParent, BOOL bClient);

////////////处理样式表///////////////////////////////////////////////////////
XC_API BOOL WINAPI XC_LoadXML_Style(HWINDOW hWindow, wchar_t *pFileName, HXMLRES hXmlRes = NULL);
XC_API BOOL WINAPI XC_LoadXML_StyleRes(HWINDOW hWindow, int resID, wchar_t *pType, HXMLRES hXmlRes = NULL); //从资源加载

BOOL XC_LoadXML_StyleRes2(char *pData, HXMLRES hXmlRes, HWINDOW hWindow);

BOOL CSS_Handle_X(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);

//分类处理
BOOL CSS_Switch(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);

BOOL CSS_HandleWindow(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);

BOOL CSS_HandleBase(TiXmlElement *pLabel, HELE hEle);
BOOL CSS_HandleEle(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleButton(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleRadio(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleCheck(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleEdit(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);

BOOL CSS_HandleComboBox(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleScrollBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleScrollView(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleList(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleListBox(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);

BOOL CSS_HandleTree(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleMenuBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandlePropertyPage(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleSliderBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleProgressBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleToolBar(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleStatic(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);

BOOL CSS_HandleGroupBox(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandlePicture(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleMonthCal(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleDateTime(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandlePGrid(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandleChooseColor(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);
BOOL CSS_HandlePropertyPageLabel(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow);


///////////////////////////////////////////////////////////////////////////////////
BOOL CSS_HandleEle2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleButton2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleRadio2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleCheck2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);

BOOL CSS_HandleEdit2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleComboBox2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleScrollBar2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleScrollView2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);

BOOL CSS_HandleList2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleListBox2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleTree2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleMenuBar2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);

BOOL CSS_HandlePropertyPage2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleSliderBar2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleProgressBar2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleToolBar2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);

BOOL CSS_HandleStatic2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleGroupBox2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandlePicture2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleMonthCal2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);


BOOL CSS_HandleDateTime2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandlePGrid2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandleChooseColor2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);
BOOL CSS_HandlePropertyPageLabel2(TiXmlElement *pLabel, HXMLRES hXmlRes, HWINDOW hWindow, HELE hEle);


//属性标签
#define STR_WIND_left               "left"
#define STR_WIND_top                "top"
#define STR_WIND_width              "width"
#define STR_WIND_height             "height"
#define STR_WIND_bkColor            "bkColor"
#define STR_WIND_captionHeight      "captionHeight"
//#define STR_WIND_borderSize         "borderSize"
#define STR_WIND_borderLeft         "borderLeft"
#define STR_WIND_borderTop	    	"borderTop"
#define STR_WIND_borderRight        "borderRight"
#define STR_WIND_borderBottom       "borderBottom"
#define STR_WIND_minWidth           "minWidth"
#define STR_WIND_minHeight          "minHeight"
#define STR_WIND_bCenter            "bCenter"
#define STR_WIND_bDragBorder        "bDragBorder"
#define STR_WIND_bDragWindow        "bDragWindow"
#define STR_WIND_bMinButton         "bMinButton"
#define STR_WIND_bMaxButton         "bMaxButton"
#define STR_WIND_bCloseButton       "bCloseButton"
#define STR_WIND_bRound             "bRound"

#define STR_WIND_value              "value"
#define STR_WIND_image              "image"
#define STR_WIND_imageNC            "imageNC"
#define STR_WIND_image_caption      "image_caption"
#define STR_WIND_image_left         "image_left"
#define STR_WIND_image_right        "image_right"
#define STR_WIND_image_bottom       "image_bottom"


//////////////////////////////////////////
#define STRA_id              "id"
#define STRA_left            "left"
#define STRA_top             "top"
#define STRA_width           "width"
#define STRA_height          "height"
#define STRA_bTransparent    "bTransparent"
#define STRA_bkColor         "bkColor"
#define STRA_textColor       "textColor"
#define STRA_tooltips        "tooltips"


#define STRA_image           "image"
#define STRA_image_leave     "image_leave"
#define STRA_image_stay      "image_stay"
#define STRA_image_down      "image_down"
#define STRA_image_check     "image_check"
#define STRA_image_disable   "image_disable"

#define STRA_image_leave_uncheck     "image_leave_uncheck"
#define STRA_image_stay_uncheck      "image_stay_uncheck"
#define STRA_image_down_uncheck      "image_down_uncheck"
#define STRA_image_disable_uncheck   "image_disable_uncheck"

#define STRA_image_leave_check     "image_leave_check"
#define STRA_image_stay_check      "image_stay_check"
#define STRA_image_down_check      "image_down_check"
#define STRA_image_disable_check   "image_disable_check"

#define STRA_value           "value"
//#define STRA_bStretch        "bStretch"
#define STRA_textAlign       "textAlign"
#define STRA_iconAlign       "iconAlign"
#define STRA_icon            "icon"
#define STRA_bCheck          "bCheck"
#define STRA_bMoreLine		 "bMoreLine"
#define STRA_bNumber         "bNumber"
#define STRA_bHScrollBar     "bHScrollBar"
#define STRA_bVScrollBar     "bVScrollBar"
#define STRA_bHorizon        "bHorizon"
#define STRA_bReadOnly       "bReadOnly"
#define STRA_bEdit           "bEdit"
#define STRA_dropDownList_height  "dropDownList_height"
#define STRA_range           "range"
#define STRA_bHeader         "bHeader"

#define STRA_bButton         "bButton"
#define STRA_bLine           "bLine"
#define STRA_bRootLine       "bRootLine"
#define STRA_itemHeight      "itemHeight"
#define STRA_labelHeight     "labelHeight"
#define STRA_labelWidth      "labelWidth"
#define STRA_labelSpacing    "labelSpacing"
#define STRA_bScrollButton   "bScrollButton"

//元素标签
#define STRA_WINDOW         "window"
#define STRA_ELE            "element"
#define STRA_BUTTON         "button"
#define STRA_RADIO          "radio"
#define STRA_CHECK          "check"
#define STRA_EDIT           "edit"
#define STRA_COMBOBOX       "comboBox"
#define STRA_SCROLLBAR      "scrollBar"
#define STRA_SCROLLVIEW     "scrollView"
#define STRA_LIST           "list"
#define STRA_LISTBOX        "listBox"
#define STRA_TREE           "tree"
#define STRA_MENUBAR        "menuBar"
#define STRA_PROPERTYPAGE   "propertyPage"
#define STRA_SLIDERBAR      "sliderBar"
#define STRA_PROGRESSBAR    "progressBar"
#define STRA_TOOLBAR        "toolBar"
#define STRA_STATIC         "static"
#define STRA_GROUPBOX       "groupBox"
#define STRA_PICTURE        "picture"
#define STRA_MONTHCAL       "monthCal"
#define STRA_DATETIME       "dateTime"
#define STRA_PROPERTYGRID   "propertyGrid"
#define STRA_CHOOSECOLOR    "chooseColor"