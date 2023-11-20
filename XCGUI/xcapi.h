/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//全局API:
XC_API int WINAPI XC_GetObjectType(HXCGUI hXCGUI); //获取资源类型


XC_API BOOL WINAPI XC_IsHELE(HELE hEle); //检查句柄
XC_API BOOL WINAPI XC_IsHWINDOW(HWINDOW hWindow); //检查句柄


XC_API BOOL WINAPI XC_IsSViewExtend(HELE hEle);  //判断元素是否从滚动视图元素扩展的新元素,包含滚动视图元素

XC_API BOOL WINAPI XC_IsEditExtend(HELE hEle); //判断该元素是否从指定元素扩展而来


//字符串转换,inLen:可以默认-1
XC_API int WINAPI XC_UnicodeToAnsi(wchar_t *pIn, int inLen, char *pOut, int outLen);
XC_API int WINAPI XC_AnsiToUnicode(char *pIn, int inLen, wchar_t *pOut, int outLen);

int XC_UnicodeToUTF8(char *utf8Str, int utf8StrLen, wchar_t * unStr, int unMaxLen);
int XC_UTF8ToUnicode(unsigned char *utf8Str, short utf8StrLen, wchar_t * unStr, unsigned short unMaxLen);
short Utf8TextBytes(const unsigned char *mstr);

int XC_GDIPlus_GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

//16进制字符串转10进制
XC_API int WINAPI XC_HexToDec(wchar_t *pHex);


XC_API void WINAPI XC_SetResourcesModule(HMODULE hModule);  //设置资源模块句柄


//判断两个矩形是否相交及重叠
XC_API BOOL WINAPI XC_RectInRect(RECT *pRect1, RECT *pRect2);
//组合两个矩形区域
XC_API void WINAPI XC_CombineRect(RECT *pDest, RECT *pSrc1, RECT *pSrc2);

XC_API HMODULE WINAPI XC_GetModuleHandle(wchar_t *pModuleName);
XC_API HMODULE WINAPI XC_GetModuleHandle2();

XC_API HANDLE WINAPI XC_LoadImage(HINSTANCE hinst, wchar_t * lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad);


XC_API HFONT WINAPI XC_CreateFont(wchar_t *pName = L"宋体", int size = 12, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
XC_API void  WINAPI XC_InitFont(LOGFONT *pFont, wchar_t *pName, int size, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);

XC_API  void* WINAPI XC_Malloc(int size);
XC_API  void  WINAPI XC_Free(void *p);






////////定时器///////////////////////////////////////////
struct xc_timer_
{
	HWND    hWnd;
	HWINDOW hWindow;
	HELE    hEle;
	int     timerID;
	DWORD   timer;//上次记录时间
	DWORD   ms; //延时
};

extern HARRAY  g_hArray_Timer;//定时器列表
extern HANDLE  g_hThread_Loop;
extern CRITICAL_SECTION  g_timer_CriticalSection;
UINT Timer_SetTimerWindow(HWINDOW hWindow, UINT itemrID, UINT ms, void* userData);
UINT Timer_SetTimerElement(HELE hEle, UINT itemrID, UINT ms, void* userData);
UINT Timer_SetTimerT(HWINDOW hWindow, HELE hEle, UINT itemrID, UINT ms, void* userData);

BOOL Timer_KillTimerWindow(int itemrID);
BOOL Timer_KillTimerElement(int itemrID);
BOOL Timer_KillTimerT(int itemrID);


//////////按钮动画///////////////////////////////////////////
//动画组
struct  button_animation_group_
{
	HELE   hEle; //按钮句柄
	HARRAY hArrayItem;  //动态图片数组 button_animation_item_*
	int    index;       //当前播放帧标记

	BOOL   bClockwise;    //播放方向,TRUE顺时针,FALSE逆时针
	BOOL   bLoopPlay;     //是否循环播放

	int    countFrame;  //帧数量
	DWORD  timer;       //当前记录时间
};

//动画项
struct  button_animation_item_
{
	HIMAGE  hImage;
	DWORD   ms;  //延时时间,毫秒
};

extern HARRAY g_hArray_Animation_button;  //动画按钮类表
extern CRITICAL_SECTION  g_CriticalSection_Animation_button; //按钮动画临界区

void Animation_Add(button_animation_group_ *pButtonAnimation, BOOL bClockwise); //添加到动画列表中
void Animation_Remove(button_animation_group_ *pButtonAnimation);

///////RichEdit GIF动画图片/////////////////////////////////////////////
extern HARRAY g_hArray_Animation_RichEdit;  //动画按钮类表
extern struct richEdit_item_gif_;
extern CRITICAL_SECTION  g_CriticalSection_Animation_richEdit; //按钮动画临界区
void Animation_Add_RichEdit(richEdit_item_gif_  *pItemGif);  //添加
void Animation_Remove_RichEdit(richEdit_item_gif_  *pItemGif);//移除


///////窗口绘制优化/////////////////////////////////////
extern CRITICAL_SECTION  g_CriticalSection_WindowDraw; //窗口绘制优化

//后台循环线程
DWORD WINAPI XCGUI_Loop_ThreadProc(LPVOID lpParameter);

void XCGUI_Loop_timer(DWORD timer); //处理定时器
void XCGUI_Loop_Animation(DWORD timer); //处理按钮动画
BOOL XCGUI_Loop_Animation1(DWORD timer, button_animation_group_ *p); //处理按钮动画,顺时针
BOOL XCGUI_Loop_Animation2(DWORD timer, button_animation_group_ *p); //处理按钮动画,逆时针
void XCGUI_Loop_Animation_RichEdit(DWORD timer);

//提供给UI文件解析模块使用/////////////////////////////////

//注册函数类型
#define  XC_XML_INIT            1  // 1 UI文件解析库初始化
#define  XC_XML_EXIT            2  // 2 UI文件解析库释放
#define  XC_XML_CREATE_WINDOW   3  // 3 窗口创建
#define  XC_CML_CREATE_ELEMENT  4  // 4 元素创建


typedef BOOL(CALLBACK *pFunXml_OnInit)();  //1 UI文件解析库初始化
typedef BOOL(CALLBACK *pFunXml_OnExit)();  //2 UI文件解析库释放
typedef BOOL(CALLBACK *pFunXml_OnCreateWindow)(HWINDOW hWindow);  // 3 窗口创建
typedef BOOL(CALLBACK *pFunXml_OnCreateElement)(HELE hEle);  // 4 元素创建


extern pFunXml_OnInit  g_fun_init;
extern pFunXml_OnExit  g_fun_exit;
extern pFunXml_OnCreateWindow   g_fun_create_window;
extern pFunXml_OnCreateElement  g_fun_create_element;

XC_API BOOL WINAPI XML_Register(int type, void *pFun); //注册回调函数


//示例:
//BOOL CALLBACK OnInit();    //1 UI文件解析库初始化
//BOOL CALLBACK OnExit();    //2 UI文件解析库释放
//BOOL CALLBACK OnCreateWindow(HWINDOW hWindow);  // 3 窗口创建
//BOOL CALLBACK OnCreateElement(HELE hEle);    // 4 元素创建

