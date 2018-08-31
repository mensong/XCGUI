/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


using namespace ShockwaveFlashObjects;

struct flash_
{
	IShockwaveFlash  *m_pShwaveflash;
};


XC_API HXCGUI WINAPI XFlash_Create(HWINDOW hWindow);
XC_API void  WINAPI XFlash_OpenFlashFile(HXCGUI hFlash, wchar_t *pFlashFile);
XC_API void* WINAPI XFlash_GetControl(HXCGUI hFlash);//获取控件接口
XC_API void  WINAPI XFlash_Destroy(HXCGUI hFlash);