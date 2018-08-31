/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

///@addtogroup groupGlobalAPI
///@{

///@brief 获取句柄类型
///@param hXCGUI 资源句柄.
///@return 句柄类型
int WINAPI XC_GetObjectType(HXCGUI hXCGUI) //获取资源类型
{
	if (NULL == hXCGUI) return -1;

	if (XC_ELE == ((object_*)hXCGUI)->type)
	{
		return ((ele_*)hXCGUI)->eleType;

	}
	else if (XC_WINDOW == ((object_*)hXCGUI)->type)
	{
		return ((window_*)hXCGUI)->exType;
	}
	else
	{
		return ((object_*)hXCGUI)->type;
	}
	return -1; //错误资源类型
}

///@brief 判断是否为元素句柄.
///@param hEle 元素句柄.
///@return 成功返回TRUE,否则相反.
BOOL WINAPI XC_IsHELE(HELE hEle) //检查句柄
{
	return Resource_IsHELE(hEle);
}

///@brief 判断是否为窗口句柄.
///@param hWindow 窗口句柄.
///@return 成功返回TRUE,否则相反.
BOOL WINAPI XC_IsHWINDOW(HWINDOW hWindow) //检查句柄
{
	return Resource_IsHWINDOW(hWindow);
}

///@brief 判断元素是否从滚动视图元素扩展的新元素,包含滚动视图元素.
///@param hEle 元素句柄.
///@return 如果是返回TRUE,否则相反.
BOOL WINAPI XC_IsSViewExtend(HELE hEle)
{
	if (NULL == hEle) return FALSE;

	if (XC_ELE != ((object_*)hEle)->type)
		return FALSE;

	switch (((ele_*)hEle)->eleType)
	{
	case XC_EDIT:          break;
	case XC_RICHEDIT:      break;
	case XC_COMBOBOX:      break;
	case XC_SCROLLVIEW:    break;
	case XC_LIST:          break;
	case XC_LISTBOX:       break;
	case XC_LISTVIEW:      break;
	case XC_TREE:          break;
	case XC_PROPERTYGRID:  break;
	case XC_CHOOSECOLOR:   break;
	case XC_EDITFILE:     break;
	default:
		return FALSE;
	}
	return TRUE;
}

///@brief 判断元素是否从编辑框元素扩展的新元素,包含编辑框元素.
///@param hEle 元素句柄.
///@return 如果是返回TRUE,否则相反.
BOOL WINAPI XC_IsEditExtend(HELE hEle) //判断该元素是否从指定元素扩展而来
{
	if (NULL == hEle) return FALSE;

	if (XC_ELE != ((object_*)hEle)->type)
		return FALSE;

	switch (((ele_*)hEle)->eleType)
	{
	case XC_EDIT:          break;
	case XC_COMBOBOX:      break;
	case XC_CHOOSECOLOR:   break;
	case XC_EDITFILE:      break;
	case XC_DATETIME:      break;
	case XC_MONTHCAL:      break;
	case XC_RICHEDIT:      break;
	default:
		return FALSE;
	}
	return TRUE;
}

///@brief Unicode转换Ansi编码,
///@param[in]  pIn    指向待转换的Unicode字符串指针.
///@param[in]  inLen  pIn字符数量.
///@param[out] pOut   指向接收转换后的Ansi字符串缓冲区指针.
///@param[in]  outLen  pOut缓冲区大小,字节单位.
///@return 如果成功,返回写入接收缓冲区字节数量.
int WINAPI XC_UnicodeToAnsi(wchar_t *pIn, int inLen, char *pOut, int outLen)
{
	return WideCharToMultiByte(CP_ACP, NULL, pIn, inLen, pOut, outLen, NULL, NULL);
}

///@brief Ansi转换Unicode编码,
///@param[in]  pIn    指向待转换的Ansi字符串指针.
///@param[in]  inLen  pIn字符数量.
///@param[out] pOut   指向接收转换后的Unicode字符串缓冲区指针.
///@param[in]  outLen pOut缓冲区大小,字符wchar_t单位.
///@return 如果成功,返回写入接收缓冲区字符wchar_t数量.
int WINAPI XC_AnsiToUnicode(char *pIn, int inLen, wchar_t *pOut, int outLen)
{
	return MultiByteToWideChar(CP_ACP, 0, pIn, inLen, pOut, outLen);
}


//utf8Str     --UTF8 dest code
//   utf8strlen    --max utf8 length
//   unStr     -- Unicode Str Source
//   unMaxlen  --Unicode 最大个数 
//    return :  --实际转换的长度
int XC_UnicodeToUTF8(char *utf8Str, int utf8StrLen, wchar_t * unStr, int unMaxLen)
{
	int unlen = 0;
	int utflen = 0;

	WORD *src;
	src = (WORD *)unStr;
	for (; (unlen <= unMaxLen - 1) && (*src != 0x00) && (utflen <= utf8StrLen);)
	{
		if (((*src) & 0xff80) == 0) //1byte
		{
			*utf8Str = (char)(*src);
			utflen += 1;
		}
		else if (((*src) & 0xf800) == 0) //2bytes
		{
			*utf8Str = (char)((((*src) >> 6) & 0x1f) | 0xc0);
			utf8Str++;
			*utf8Str = (char)(((*src) & 0x003f) | 0x80);
			utflen += 2;
		}
		else                    //3bytes
		{
			*utf8Str = (char)((((*src) >> 12) & 0x000f) | 0xe0);
			utf8Str++;
			*utf8Str = (char)((((*src) >> 6) & 0x3f) | 0x80);
			utf8Str++;
			*utf8Str = (char)(((*src) & 0x003f) | 0x80);
			utflen += 3;
		}
		unlen++;
		src++;
		utf8Str++;
	}

	*utf8Str = 0x00;
	return utflen;
}

short Utf8TextBytes(const unsigned char *mstr)
{
	short textbytes = 0;
	if (mstr == 0)
	{                           //Returns 0 if mstr contains a null string or if there is
		return 0;               //no valid character in mstr.
	}
	/* code checking.
	because all unicode used now is lower than 0xffff, only 1~3 bytes UTF-8 has means,
	the other length will not be dealed with in other functions */
	if (((*mstr) & 0x80) == 0)
	{
		textbytes = 1;          //0xxxxxxx, normal ASCII code
	}
	else if ((((*mstr) & 0xe0) == 0xc0) && (((*(mstr + 1)) & 0xc0) == 0x80))
	{
		if (((*mstr) & 0xfe) == 0xc0) //1100,000x is illegal data,
		{
			textbytes = 0;
		}
		else
		{
			textbytes = 2;      //110xxxxx 10xxxxxx
		}
	}
	else if ((((*mstr) & 0xf0) == 0xe0) && (((*(mstr + 1)) & 0xc0) == 0x80) && (((*(mstr + 2)) & 0xc0) == 0x80))
	{
		if ((*mstr == (char)0xe0) && (((*(mstr + 1)) & 0xe0) == 0x80)) //1110,0000,100x,xxxx is illegal data
		{
			textbytes = 0;
		}
		else
		{
			textbytes = 3;      //1110xxxx 10xxxxxx 10xxxxxx
		}
	}
	else if ((((*mstr) & 0xf8) == 0xf0) && (((*(mstr + 1)) & 0xc0) == 0x80) && (((*(mstr + 2)) & 0xc0) == 0x80)
		&& (((*(mstr + 3)) & 0xc0) == 0x80))
	{
		if (((*mstr) == (char)0xf0) && (((*(mstr + 1)) & 0xf0) == 0x80)) // 1111,0000,1000,xxxx is illegal data
		{
			textbytes = 0;
		}
		else
		{
			textbytes = 4;      // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		}
	}
	else if ((((*mstr) & 0xfc) == 0xf8) && (((*(mstr + 1)) & 0xc0) == 0x80) &&
		(((*(mstr + 2)) & 0xc0) == 0x80) && (((*(mstr + 3)) & 0xc0) == 0x80) && (((*(mstr + 4)) & 0xc0) == 0x80))
	{
		if ((*mstr == (char)0xf8) && (((*(mstr + 1)) & 0xf8) == 0x80)) //1111,1000,1000,0xxx is illegal data
		{
			textbytes = 0;
		}
		else
		{
			textbytes = 5;      //111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		}
	}
	else if ((((*mstr) & 0xfe) == 0xfc) && (((*(mstr + 1)) & 0xc0) == 0x80) &&
		(((*(mstr + 2)) & 0xc0) == 0x80) && (((*(mstr + 3)) & 0xc0) == 0x80) && (((*(mstr + 4)) & 0xc0) == 0x80) &&
		(((*(mstr + 5)) & 0xc0) == 0x80))
	{
		if ((*mstr == (char)0xfc) && (((*(mstr + 1)) & 0xfc) == 0x80)) //1111,1100,1000,00xx is illegal data
		{
			textbytes = 0;
		}
		else
		{
			textbytes = 6;      //1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		}
	}
	else
	{
		textbytes = 0;          //illegal formal, return 0
	}

	return textbytes;
}

//utf8Str     --UTF8 source string
//utf8strlen    --max utf8 length
//unStr     -- Unicode Str dest
//unMaxlen  --Unicode 最大个数 
//return :  --实际转化的长度
int XC_UTF8ToUnicode(unsigned char *utf8Str, short utf8StrLen, wchar_t * unStr, unsigned short unMaxLen)
{
	int zen_han, len_dest;
	unsigned char *p_src;
	unsigned char utf8_len = 0;
	len_dest = 0;
	p_src = (unsigned char *)(utf8Str);

	/* limit the total bytes of the *mstr */
	if (utf8StrLen <= 0)
	{
		return (0);
	}

	/* converting at here utf8_len <= utf8StrLen 改为 utf8_len < utf8StrLen*/
	for (; (*p_src != 0x00) && (len_dest <= unMaxLen - 1) && (utf8_len < utf8StrLen);)
	{
		zen_han = Utf8TextBytes((const unsigned char *)p_src);
		if (zen_han == 1)       //ASCII, just add 0x00 at beginning
		{
			(*unStr) = *(p_src);
			unStr++;
			p_src++;
			utf8_len++;
			len_dest += 1;
		}
		else if (zen_han == 2)
		{
			*unStr = (((((*p_src) >> 2) & (unsigned char)0x07)) & 0x00ff) << 8;
			*unStr |= ((((*p_src) << 6) | ((*(p_src + 1)) & (unsigned char)0x3f))) & 0x00ff;
			unStr++;
			p_src += 2;
			utf8_len += 2;
			len_dest += 1;

		}
		else if (zen_han == 3)
		{
			*(unStr) = ((((*(p_src)) << 4) | (((*(p_src + 1)) >> 2) & 0x0f)) & 0x00ff) << 8;

			*unStr |= ((((*(p_src + 1)) << 6) | ((*(p_src + 2)) & (unsigned char)0x3f))) & 0x00ff;
			unStr++;
			p_src += 3;
			utf8_len += 3;
			len_dest += 1;
		}
		else if (zen_han == 4)  //
		{
			*unStr = (*(p_src)) & 0x7;
			for (int i = 1; i < 4; i++)
			{
				*unStr <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
				*unStr = *unStr | ((*(p_src + i)) & 0x3f);//先与后或
			}
			unStr++;
			p_src += 4;
			utf8_len += 4;
			len_dest += 1;
		}
		else if (zen_han == 5)  //
		{
			*unStr = (*(p_src)) & 0x3;
			for (int i = 1; i < 5; i++)
			{
				*unStr <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
				*unStr = *unStr | ((*(p_src + i)) & 0x3f);//先与后或
			}
			unStr++;
			p_src += 5;
			utf8_len += 5;
			len_dest += 1;
		}
		else if (zen_han == 6)  //
		{
			*unStr = (*(p_src)) & 0x1;
			for (int i = 1; i < 6; i++)
			{
				*unStr <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
				*unStr = *unStr | ((*(p_src + i)) & 0x3f);//先与后或
			}
			unStr++;
			p_src += 6;
			utf8_len += 6;
			len_dest += 1;
		}
		else                    //treated as illegal character, search the next character
		{
			p_src++;
			utf8_len++;
		}
	}
	*(unStr) = 0x0000;
	return (len_dest);

}

int XC_GDIPlus_GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;
	UINT size = 0;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1;
	}
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
	{
		return -1;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1;
}

///@brief 16进制字符串转10进制.
///@param[in] pHex 16进制字符串.
///@return  返回10进制.
int WINAPI XC_HexToDec(wchar_t *pHex)
{
	int i, mid, idec;
	int   len = wcslen(pHex);
	if (len > 8)   return 0;
	mid = 0;   idec = 0;
	for (i = 0; i < len; i++)
	{
		if (pHex[i] >= L'0'&&pHex[i] <= L'9')
			mid = pHex[i] - L'0';
		else
			if (pHex[i] >= L'a'&&pHex[i] <= L'f')
				mid = pHex[i] - L'a' + 10;
			else
				if (pHex[i] >= L'A'&&pHex[i] <= L'F')
					mid = pHex[i] - L'A' + 10;
				else
					return   FALSE;
		mid <<= ((len - i - 1) << 2);
		idec |= mid;
	}
	return   idec;
}

///@brief 设置资源模块句柄.
///@param hModule 资源模块句柄.
void WINAPI XC_SetResourcesModule(HMODULE hModule)  //设置资源模块句柄
{
	g_resourcesModule = hModule;
}

///@brief 判断两个矩形是否相交及重叠.
///@param pRect1  矩形1.
///@param pRect2  矩形2.
///@return  如果两个矩形相交返回TRUE,否则相反.
BOOL WINAPI XC_RectInRect(RECT *pRect1, RECT *pRect2)
{
	//  if(B.Left > A.Right || A.Left > B.Right || B.Top > A.Bottom || A.Top > B.Bottom) 

	if (pRect1->left >= pRect2->right)
		return FALSE;

	if (pRect1->top >= pRect2->bottom)
		return FALSE;

	if (pRect1->right <= pRect2->left)
		return FALSE;

	if (pRect1->bottom <= pRect2->top)
		return FALSE;

	return TRUE;
}

///@brief 组合两个矩形区域.
///@param pDest   新的矩形区域.
///@param pSrc1  源矩形1.
///@param pSrc2  源矩形2.
void WINAPI XC_CombineRect(RECT *pDest, RECT *pSrc1, RECT *pSrc2)
{
	if (pSrc1->left < pSrc2->left)
		pDest->left = pSrc1->left;
	else
		pDest->left = pSrc2->left;

	if (pSrc1->top < pSrc2->top)
		pDest->top = pSrc1->top;
	else
		pDest->top = pSrc2->top;

	if (pSrc1->right > pSrc2->right)
		pDest->right = pSrc1->right;
	else
		pDest->right = pSrc2->right;

	if (pSrc1->bottom > pSrc2->bottom)
		pDest->bottom = pSrc1->bottom;
	else
		pDest->bottom = pSrc2->bottom;
}

///@brief 获取模块文件句柄,exe或dll文件.
///@param pModuleName  模块文件名,如果参数为NULL,那么为当前应用程序模块文件.
///@return  如果成功返回模块句柄,失败返回NULL.
HMODULE WINAPI XC_GetModuleHandle(wchar_t *pModuleName)
{
	return GetModuleHandle(pModuleName);
}

///@brief   获取用户当前设置的资源模块句柄.
///@return  如果成功返回模块句柄,失败返回NULL.
HMODULE WINAPI XC_GetModuleHandle2()
{
	if (g_resourcesModule)
		return g_resourcesModule;
	else
		return GetModuleHandle(NULL);
}

///@brief 加载图片,参见MSDN,LoadImage().
///@param hinst   参见MSDN.
///@param lpszName 参见MSDN.
///@param uType   参见MSDN.
///@param cxDesired  参见MSDN.
///@param cyDesired 参见MSDN.
///@param fuLoad  参见MSDN.
///@return  如果成功返回图片句柄,失败返回NULL.
HANDLE WINAPI XC_LoadImage(HINSTANCE hinst, wchar_t * lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad)
{
	return LoadImage(hinst, lpszName, uType, cxDesired, cyDesired, fuLoad);
}

//字体大小,字体名称,粗体,斜体,下划线,删除线

/// @brief  创建字体.
/// @param  pName  字体名称.
/// @param  size   字体大小.
/// @param  bBold  是否为粗体.
/// @param  bItalic  是否为斜体.
/// @param  bUnderline   是否有下划线.
/// @param  bStrikeOut   是否有删除线.
/// @return 返回字体句柄.
HFONT WINAPI XC_CreateFont(wchar_t *pName, int size, BOOL bBold, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut)
{
	DWORD nWeight = FW_NORMAL;
	if (bBold)
		nWeight = FW_BOLD;

	HFONT hFont = CreateFont(
		size,                      // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		nWeight,                   // nWeight
		bItalic,                   // bItalic
		bUnderline,                // bUnderline
		bStrikeOut,                // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily
		pName);                    // lpszFacename _T("Arial")

	return hFont;
}

/// @brief  初始化LOGFONT结构体.
/// @param  pFont LOGFONT结构体指针.
/// @param  pName  字体名称.
/// @param  size   字体大小.
/// @param  bBold  是否为粗体.
/// @param  bItalic  是否为斜体.
/// @param  bUnderline   是否有下划线.
/// @param  bStrikeOut   是否有删除线.
void WINAPI XC_InitFont(LOGFONT *pFont, wchar_t *pName, int size, BOOL bBold, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut)
{
	DWORD nWeight = FW_NORMAL;
	if (bBold)
		nWeight = FW_BOLD;

	pFont->lfHeight = size;
	pFont->lfWidth = 0;
	pFont->lfEscapement = 0;
	pFont->lfOrientation = 0;
	pFont->lfWeight = nWeight;
	pFont->lfItalic = bItalic;
	pFont->lfUnderline = bUnderline;
	pFont->lfStrikeOut = bStrikeOut;
	pFont->lfCharSet = GB2312_CHARSET;
	pFont->lfOutPrecision = OUT_DEFAULT_PRECIS;
	pFont->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	pFont->lfQuality = DEFAULT_QUALITY;
	pFont->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;//DEFAULT_PITCH | FF_SWISS;

	wcscpy_s(pFont->lfFaceName, pName);
}

void* WINAPI XC_Malloc(int size)
{
	return malloc(size);
}

void  WINAPI XC_Free(void *p)
{
	free(p);
}

///@}

//////////定时器////////////////////////////////////////////////////
HARRAY  g_hArray_Timer = NULL;
HANDLE  g_hThread_Loop = NULL;
CRITICAL_SECTION  g_timer_CriticalSection;
UINT  Timer_SetTimerWindow(HWINDOW hWindow, UINT itemrID, UINT ms, int userData)
{
	return Timer_SetTimerT(hWindow, NULL, itemrID, ms, userData);
}

UINT  Timer_SetTimerElement(HELE hEle, UINT itemrID, UINT ms, int userData)
{
	return Timer_SetTimerT(NULL, hEle, itemrID, ms, userData);
}

UINT Timer_SetTimerT(HWINDOW hWindow, HELE hEle, UINT itemrID, UINT ms, int userData)
{
	//检查ID是否有效
	if (g_hArray_Timer)
	{
		int count = XArray_GetCount(g_hArray_Timer);
		EnterCriticalSection(&g_timer_CriticalSection);
		for (int i = 0; i < count; i++)
		{
			xc_timer_ *p = (xc_timer_*)XArray_GetAt(g_hArray_Timer, i);
			if (itemrID == p->timerID)
				return 0;
		}
		LeaveCriticalSection(&g_timer_CriticalSection);
	}

	xc_timer_ *p = (xc_timer_*)malloc(sizeof(xc_timer_));
	if (hWindow)
	{
		p->hWindow = hWindow;
		p->hWnd = XWnd_GetHWnd(hWindow);
	}
	else
	{
		p->hWindow = XEle_GetHWindow(hEle);
		p->hWnd = XWnd_GetHWnd(p->hWindow);
	}

	p->hEle = hEle;
	p->timerID = itemrID;
	p->timer = GetTickCount();
	p->ms = ms;

	if (NULL == g_hArray_Timer)
		g_hArray_Timer = XArray_Create();

	EnterCriticalSection(&g_timer_CriticalSection);
	XArray_Add(g_hArray_Timer, p);
	LeaveCriticalSection(&g_timer_CriticalSection);

	return itemrID;
}

BOOL  Timer_KillTimerWindow(int itemrID)
{
	return Timer_KillTimerT(itemrID);
}

BOOL  Timer_KillTimerElement(int itemrID)
{
	return Timer_KillTimerT(itemrID);
}

BOOL Timer_KillTimerT(int itemrID)
{
	if (NULL == g_hArray_Timer)
		return FALSE;

	int count = XArray_GetCount(g_hArray_Timer);
	for (int i = 0; i < count; i++)
	{
		xc_timer_ *p = (xc_timer_*)XArray_GetAt(g_hArray_Timer, i);
		if (itemrID == p->timerID)
		{
			EnterCriticalSection(&g_timer_CriticalSection);
			XArray_DeleteIndex(g_hArray_Timer, i);
			LeaveCriticalSection(&g_timer_CriticalSection);
			free(p);
			break;
		}
	}
	count = XArray_GetCount(g_hArray_Timer);

	if (count > 0) return TRUE;

	if (g_hArray_Timer)
	{
		XArray_Destroy(g_hArray_Timer);
		g_hArray_Timer = NULL;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////
HARRAY g_hArray_Animation_button = NULL;  //动画按钮类表
CRITICAL_SECTION  g_CriticalSection_Animation_button; //按钮动画临界区

void Animation_Add(button_animation_group_ *pButtonAnimation, BOOL bClockwise) //添加到动画列表中
{
	EnterCriticalSection(&g_CriticalSection_Animation_button);
	if (NULL == g_hArray_Animation_button)
		g_hArray_Animation_button = XArray_Create();

	pButtonAnimation->bClockwise = bClockwise;

	if (pButtonAnimation->bClockwise)
	{
		pButtonAnimation->index = 0;
	}
	else
	{
		pButtonAnimation->index = pButtonAnimation->countFrame - 1;
	}
	pButtonAnimation->timer = GetTickCount();

	//防止重复添加
	int count = XArray_GetCount(g_hArray_Animation_button);
	button_animation_group_  *pT = NULL;
	for (int i = 0; i < count; i++)
	{
		pT = (button_animation_group_*)XArray_GetAt(g_hArray_Animation_button, i);
		if (pT == pButtonAnimation)
		{
			LeaveCriticalSection(&g_CriticalSection_Animation_button);
			return; //重复添加
		}
	}

	XArray_Add(g_hArray_Animation_button, pButtonAnimation);
	LeaveCriticalSection(&g_CriticalSection_Animation_button);
}

void Animation_Remove(button_animation_group_ *pButtonAnimation)
{
	EnterCriticalSection(&g_CriticalSection_Animation_button);
	if (g_hArray_Animation_button)
	{
		int count = XArray_GetCount(g_hArray_Animation_button);
		button_animation_group_  *pT = NULL;
		for (int i = 0; i < count; i++)
		{
			pT = (button_animation_group_*)XArray_GetAt(g_hArray_Animation_button, i);
			if (pT == pButtonAnimation)
			{
				XArray_DeleteIndex(g_hArray_Animation_button, i);
				break;
			}
		}
	}
	LeaveCriticalSection(&g_CriticalSection_Animation_button);
}

///////////RichEdit GIF//////////////////////////////////////////////
HARRAY g_hArray_Animation_RichEdit = NULL;  //动画按钮类表
CRITICAL_SECTION  g_CriticalSection_Animation_richEdit; //按钮动画临界区
void Animation_Add_RichEdit(richEdit_item_gif_  *pItemGif)  //添加
{
	EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
	if (NULL == g_hArray_Animation_RichEdit)
		g_hArray_Animation_RichEdit = XArray_Create();

	pItemGif->timer = GetTickCount();
	XArray_Add(g_hArray_Animation_RichEdit, pItemGif);
	LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
}

void Animation_Remove_RichEdit(richEdit_item_gif_  *pItemGif) //移除
{
	EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
	if (NULL == g_hArray_Animation_RichEdit)
	{
		LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
		return;
	}
	XArray_Delete(g_hArray_Animation_RichEdit, pItemGif);
	LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
}

//////////////////////////////////////////////////////////////////
CRITICAL_SECTION  g_CriticalSection_WindowDraw; //窗口绘制优化

/////////////////////////////////////////////////////////////////////
DWORD WINAPI XCGUI_Loop_ThreadProc(LPVOID lpParameter)
{
	DWORD ms = 20;//USER_TIMER_MINIMUM*2; //最小延时单位

	while (1)
	{
		Sleep(ms);

		if (NULL == g_hThread_Loop)
			break;

		DWORD timer = GetTickCount();

		//处理定时器
		EnterCriticalSection(&g_timer_CriticalSection);
		if (g_hArray_Timer)
			XCGUI_Loop_timer(timer);
		LeaveCriticalSection(&g_timer_CriticalSection);

		//////////////////////////////////////////////////////////////////////

		//处理按钮动画
		EnterCriticalSection(&g_CriticalSection_Animation_button);
		if (g_hArray_Animation_button)
			XCGUI_Loop_Animation(timer);
		LeaveCriticalSection(&g_CriticalSection_Animation_button);

		//////////RichEdit GIF/////////////////////////////////////////////////

		//	EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
		//	if(g_hArray_Animation_RichEdit)
		XCGUI_Loop_Animation_RichEdit(timer);
		//	LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);

		/////////处理窗口绘制优化////////////////////

		EnterCriticalSection(&g_CriticalSection_WindowDraw);
		resource_manager_window_  *pWindowNode = resource_manager.pWindowList;
		while (pWindowNode)
		{
			window_ *pWindow = (window_*)pWindowNode->hWindow;
			if (pWindow->drawWindow.bValid)
			{
				PostMessage(pWindow->hWnd, XWM_DRAW_T, 0, 0);
			}
			pWindowNode = pWindowNode->pNext;
		}
		LeaveCriticalSection(&g_CriticalSection_WindowDraw);
	}

	if (g_hThread_Loop)
	{
		CloseHandle(g_hThread_Loop);
		g_hThread_Loop = NULL;
	}

	return 0;
}

void XCGUI_Loop_timer(DWORD timer) //处理定时器
{
	int count = XArray_GetCount(g_hArray_Timer);
	if (count < 1)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		xc_timer_ *p = (xc_timer_*)XArray_GetAt(g_hArray_Timer, i);
		if (timer < p->timer)
		{
			p->timer = timer;
			PostMessage(p->hWnd, XWM_TIMER, p->timerID, 0);
		}
		else
		{
			DWORD t = timer - p->timer;
			if (t >= p->ms)
			{
				p->timer = timer;
				PostMessage(p->hWnd, XWM_TIMER, p->timerID, 0);
			}
		}
	}
}

void XCGUI_Loop_Animation(DWORD timer) //处理按钮动画
{
	int count = XArray_GetCount(g_hArray_Animation_button);
	if (count < 1)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		button_animation_group_ *p = (button_animation_group_*)XArray_GetAt(g_hArray_Animation_button, i);

		if (p->bClockwise || p->bLoopPlay) //顺时针
		{
			if (FALSE == XCGUI_Loop_Animation1(timer, p))
			{
				XArray_DeleteIndex(g_hArray_Animation_button, i);
				count--;
			}
		}
		else  //逆时针
		{
			if (FALSE == XCGUI_Loop_Animation2(timer, p))
			{
				XArray_DeleteIndex(g_hArray_Animation_button, i);
				count--;
			}
		}
	}
}

BOOL XCGUI_Loop_Animation1(DWORD timer, button_animation_group_ *p) //处理按钮动画,顺时针
{
	int index = p->index + 1; //下次要绘制的帧
	if (index >= 0 && index < p->countFrame)
	{
		button_animation_item_  *pItem = (button_animation_item_*)XArray_GetAt(p->hArrayItem, index);

		if (timer < p->timer)
		{
			p->index = index;
			p->timer = timer;

			if (XEle_IsShowEle(p->hEle))
			{
				::PostMessage(XEle_GetHWnd(p->hEle), XWM_REDRAW_ELE, (WPARAM)p->hEle, 0);
				XTRACE("后台线程 发送绘制动画消息 %d \n", index);
			}
		}
		else
		{
			UINT t = timer - p->timer;
			if (t > pItem->ms)
			{
				p->index = index;
				p->timer = timer;

				if (XEle_IsShowEle(p->hEle))
				{
					::PostMessage(XEle_GetHWnd(p->hEle), XWM_REDRAW_ELE, (WPARAM)p->hEle, 0);
					XTRACE("后台线程 发送绘制动画消息 %d \n", index);
				}
			}
		}
	}
	else //终止动画
	{
		if (p->bLoopPlay) //循环播放
		{
			p->index = -1;
		}
		else
		{
			XTRACE("后台线程 结束动画 \n");
			return FALSE;
		}
	}
	return TRUE;
}

BOOL XCGUI_Loop_Animation2(DWORD timer, button_animation_group_ *p) //处理按钮动画,逆时针
{
	int index = p->index - 1; //下次要绘制的帧
	if (index >= 0 && index < p->countFrame)
	{
		button_animation_item_  *pItem = (button_animation_item_*)XArray_GetAt(p->hArrayItem, index);

		if (timer < p->timer)
		{
			p->index = index;
			p->timer = timer;
			if (XEle_IsShowEle(p->hEle))
			{
				::PostMessage(XEle_GetHWnd(p->hEle), XWM_REDRAW_ELE, (WPARAM)p->hEle, 0);
				XTRACE("后台线程 发送绘制动画消息 %d \n", index);
			}
		}
		else
		{
			UINT t = timer - p->timer;
			if (t > pItem->ms)
			{
				p->index = index;
				p->timer = timer;
				if (XEle_IsShowEle(p->hEle))
				{
					::PostMessage(XEle_GetHWnd(p->hEle), XWM_REDRAW_ELE, (WPARAM)p->hEle, 0);
					XTRACE("后台线程 发送绘制动画消息 %d \n", index);
				}
			}
		}
	}
	else //终止动画
	{
		XTRACE("后台线程 结束动画 \n");
		return FALSE;
	}
	return TRUE;
}

void XCGUI_Loop_Animation_RichEdit(DWORD timer)
{
	EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
	if (g_hArray_Animation_RichEdit)
	{
		richEdit_item_gif_  *pItemGif = NULL;
		for (int i = 0; i < XArray_GetCount(g_hArray_Animation_RichEdit); i++)
		{
			pItemGif = (richEdit_item_gif_*)XArray_GetAt(g_hArray_Animation_RichEdit, i);
			if (timer < pItemGif->timer)
			{
				pItemGif->timer = timer;
				pItemGif->pGif->NextFrame();

				HELE hRichEdit = XEle_GetParentEle(pItemGif->hView);
				RECT rect;
				RichEdit_GetItemRect2(hRichEdit, (richEdit_item_*)pItemGif, &rect);
				XEle_RectToNCWnd(pItemGif->hView, &rect);

				LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
				::SendMessage(XEle_GetHWnd(pItemGif->hView), XWM_REDRAW_ELE, (WPARAM)pItemGif->hView, (LPARAM)&rect);
				EnterCriticalSection(&g_CriticalSection_Animation_richEdit);

				//InvalidateRect(XEle_GetHWnd(pItemGif->hView),&rect,FALSE);
			}
			else
			{
				DWORD t = timer - pItemGif->timer;
				if (t >= pItemGif->ms)
				{
					pItemGif->timer = timer;
					pItemGif->pGif->NextFrame();

					HELE hRichEdit = XEle_GetParentEle(pItemGif->hView);
					RECT rect;
					RichEdit_GetItemRect2(hRichEdit, (richEdit_item_*)pItemGif, &rect);
					XEle_RectToNCWnd(pItemGif->hView, &rect);
					//InvalidateRect(XEle_GetHWnd(pItemGif->hView),&rect,FALSE);

					LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
					::SendMessage(XEle_GetHWnd(pItemGif->hView), XWM_REDRAW_ELE, (WPARAM)pItemGif->hView, (LPARAM)&rect);
					EnterCriticalSection(&g_CriticalSection_Animation_richEdit);
				}
			}
		}
	}
	LeaveCriticalSection(&g_CriticalSection_Animation_richEdit);
}

///////////////////////////////////////////////////////

pFunXml_OnInit  g_fun_init = NULL;
pFunXml_OnExit  g_fun_exit = NULL;
pFunXml_OnCreateWindow   g_fun_create_window = NULL;
pFunXml_OnCreateElement  g_fun_create_element = NULL;

BOOL WINAPI XML_Register(int type, void *pFun) //注册回调函数
{
	switch (type)
	{
	case XC_XML_INIT: g_fun_init = (pFunXml_OnInit)pFun; break;
	case XC_XML_EXIT: g_fun_exit = (pFunXml_OnInit)pFun; break;
	case XC_XML_CREATE_WINDOW:  g_fun_create_window = (pFunXml_OnCreateWindow)pFun;  break;
	case XC_CML_CREATE_ELEMENT: g_fun_create_element = (pFunXml_OnCreateElement)pFun;  break;
	default: return FALSE;
	}
	return TRUE;
}