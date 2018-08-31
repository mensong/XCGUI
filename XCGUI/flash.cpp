/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup flash flash控件
/// @ingroup groupOther
/// @{

/// @brief 创建flash控件元素.
/// @param hWindow 父窗口句柄.
/// @return flash控件句柄.
HXCGUI WINAPI XFlash_Create(HWINDOW hWindow)
{
	IsWindowDebug(hWindow, __FUNCTION__);

	HWND hWnd = XWnd_GetHWnd(hWindow);

	XCom_Add();
	flash_  *pObject = new flash_;

	HRESULT hr = CoCreateInstance(__uuidof(ShockwaveFlash), NULL, CLSCTX_INPROC_SERVER, __uuidof(IShockwaveFlash), (void**)&pObject->m_pShwaveflash);
	if (S_OK == hr)
	{
		hr = AtlAxAttachControl(pObject->m_pShwaveflash, hWnd, NULL);
		if (S_OK == hr)
		{
			return pObject;
		}
	}
	return NULL;
}

/// @brief 打开播放flash文件.
/// @param hFlash     flash控件句柄.
/// @param pFlashFile flash文件.
void WINAPI XFlash_OpenFlashFile(HXCGUI hFlash, wchar_t *pFlashFile)
{
	flash_ *pObject = (flash_*)hFlash;
	BSTR str(pFlashFile);
	pObject->m_pShwaveflash->put_Movie(str);
	pObject->m_pShwaveflash->Play();
}

/// @brief 获取flash控件COM接口指针.
/// @param hFlash     flash控件句柄.
/// @return 返回flash控件COM接口指针(IShockwaveFlash*); 示例:IShockwaveFlash* pFlash=(IShockwaveFlash*)XFlash_GetControl(hFlash);
void* WINAPI XFlash_GetControl(HXCGUI hFlash) //获取控件接口
{
	flash_ *pObject = (flash_*)hFlash;
	return pObject->m_pShwaveflash;
}

/// @brief 销毁flash控件,同时你需要销毁它所依赖的父窗口.
/// @param hFlash     flash控件句柄.
void WINAPI XFlash_Destroy(HXCGUI hFlash)
{
	flash_ *pObject = (flash_*)hFlash;
	pObject->m_pShwaveflash->StopPlay();
	pObject->m_pShwaveflash->Release();
	//XCom_Release();
	delete pObject;
}

///@}

