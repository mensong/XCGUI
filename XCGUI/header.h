/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#ifdef _DEBUG  //CRT内存泄漏检测  //_CrtSetBreakAlloc(int number);   //设置断点
#define   _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#include <crtdbg.h>
#endif  

#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <atltime.h>
#include <atlcomtime.h>
#include <stdio.h>
#include <assert.h>
#include <atlwin.h>  //IE控件需要使用

#define GDIPVER 0x0110
#include <unknwn.h>
#include <Imm.h>
#include <Commdlg.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib,"Imm32.lib")

#pragma warning(disable:4996)

#include "tinyxml/tinyxml.h"

#import "flash/flash11e.dll"

#define XCGUI_CLASS_NAME  L"XCGUI"


#include "xcgui.h"
#include "xcdef.h"
#include "debug.h"
#include "ResourceManager.h"
#include "string_x.h"
#include "array_x.h"
#include "multiTree_x.h"
#include "image_x.h"
#include "XCAPI.h"
#include "font_x.h"


#include "dc.h"
#include "xcapp.h"
#include "ele.h"
#include "button.h"
#include "check.h"
#include "radio.h"
#include "scrollBar.h"
#include "scrollView.h"
#include "edit.h"
#include "richEdit.h"
#include "editFile.h"
#include "imageList.h"
#include "list.h"
#include "listView.h"
#include "Tree.h"
#include "listBox.h"
#include "comboBox.h"
#include "menuBar.h"
#include "propertyPage.h"
#include "sliderBar.h"
#include "progressBar.h"
#include "toolBar.h"
#include "static_x.h"
#include "groupBox.h"
#include "picture.h"
#include "monthCal.h"
#include "propertyGrid.h"
#include "chooseColor.h"
#include "outlook.h"
#include "textLink.h"
#include "tabBar.h"
#include "gif.h"


#include "layoutCell.h"
#include "Pier.h"


#include "window.h"
#include "comboBoxWindow.h"
#include "menu.h"
#include "modalWindow.h"
#include "dateTimeWindow.h"
#include "frameWnd.h"

#include "pane.h"

//#include "sendEMail.h"
//#include "xmlRes.h"
//#include "xcxml.h"
#include "WebBrowser.h"
#include "flash.h"


#include "GuiDesigner/xml.h"
#include "GuiDesigner/xmlRes.h"
//#include "Main.h"


//-----------------------------------------------------------


/// @defgroup groupWindows UI窗口模块列表


/// @defgroup groupElements UI元素模块列表

/// @defgroup groupOther 其他模块

/// @defgroup msgAndEvents 消息及事件


/// @defgroup wndMSG  窗口消息
/// @ingroup msgAndEvents
/// @details窗口消息-包含系统非客户区消息


/// @defgroup wndNCMSG  窗口非客户区消息
/// @ingroup msgAndEvents
/// 窗口非客户区消息-逻辑上的非客户区


/// @defgroup eleMSG 元素消息
/// @ingroup msgAndEvents


/// @defgroup eleEvents  元素事件
/// @ingroup msgAndEvents

/// @defgroup macroDefine 宏定义

/// @defgroup groupGlobalAPI  全局API

/// @defgroup groupGuiDesigner  UI设计器支持


////////////////////////////////////////////////////////////////////////


