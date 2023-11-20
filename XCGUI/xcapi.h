/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//ȫ��API:
XC_API int WINAPI XC_GetObjectType(HXCGUI hXCGUI); //��ȡ��Դ����


XC_API BOOL WINAPI XC_IsHELE(HELE hEle); //�����
XC_API BOOL WINAPI XC_IsHWINDOW(HWINDOW hWindow); //�����


XC_API BOOL WINAPI XC_IsSViewExtend(HELE hEle);  //�ж�Ԫ���Ƿ�ӹ�����ͼԪ����չ����Ԫ��,����������ͼԪ��

XC_API BOOL WINAPI XC_IsEditExtend(HELE hEle); //�жϸ�Ԫ���Ƿ��ָ��Ԫ����չ����


//�ַ���ת��,inLen:����Ĭ��-1
XC_API int WINAPI XC_UnicodeToAnsi(wchar_t *pIn, int inLen, char *pOut, int outLen);
XC_API int WINAPI XC_AnsiToUnicode(char *pIn, int inLen, wchar_t *pOut, int outLen);

int XC_UnicodeToUTF8(char *utf8Str, int utf8StrLen, wchar_t * unStr, int unMaxLen);
int XC_UTF8ToUnicode(unsigned char *utf8Str, short utf8StrLen, wchar_t * unStr, unsigned short unMaxLen);
short Utf8TextBytes(const unsigned char *mstr);

int XC_GDIPlus_GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

//16�����ַ���ת10����
XC_API int WINAPI XC_HexToDec(wchar_t *pHex);


XC_API void WINAPI XC_SetResourcesModule(HMODULE hModule);  //������Դģ����


//�ж����������Ƿ��ཻ���ص�
XC_API BOOL WINAPI XC_RectInRect(RECT *pRect1, RECT *pRect2);
//���������������
XC_API void WINAPI XC_CombineRect(RECT *pDest, RECT *pSrc1, RECT *pSrc2);

XC_API HMODULE WINAPI XC_GetModuleHandle(wchar_t *pModuleName);
XC_API HMODULE WINAPI XC_GetModuleHandle2();

XC_API HANDLE WINAPI XC_LoadImage(HINSTANCE hinst, wchar_t * lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad);


XC_API HFONT WINAPI XC_CreateFont(wchar_t *pName = L"����", int size = 12, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
XC_API void  WINAPI XC_InitFont(LOGFONT *pFont, wchar_t *pName, int size, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);

XC_API  void* WINAPI XC_Malloc(int size);
XC_API  void  WINAPI XC_Free(void *p);






////////��ʱ��///////////////////////////////////////////
struct xc_timer_
{
	HWND    hWnd;
	HWINDOW hWindow;
	HELE    hEle;
	int     timerID;
	DWORD   timer;//�ϴμ�¼ʱ��
	DWORD   ms; //��ʱ
};

extern HARRAY  g_hArray_Timer;//��ʱ���б�
extern HANDLE  g_hThread_Loop;
extern CRITICAL_SECTION  g_timer_CriticalSection;
UINT Timer_SetTimerWindow(HWINDOW hWindow, UINT itemrID, UINT ms, void* userData);
UINT Timer_SetTimerElement(HELE hEle, UINT itemrID, UINT ms, void* userData);
UINT Timer_SetTimerT(HWINDOW hWindow, HELE hEle, UINT itemrID, UINT ms, void* userData);

BOOL Timer_KillTimerWindow(int itemrID);
BOOL Timer_KillTimerElement(int itemrID);
BOOL Timer_KillTimerT(int itemrID);


//////////��ť����///////////////////////////////////////////
//������
struct  button_animation_group_
{
	HELE   hEle; //��ť���
	HARRAY hArrayItem;  //��̬ͼƬ���� button_animation_item_*
	int    index;       //��ǰ����֡���

	BOOL   bClockwise;    //���ŷ���,TRUE˳ʱ��,FALSE��ʱ��
	BOOL   bLoopPlay;     //�Ƿ�ѭ������

	int    countFrame;  //֡����
	DWORD  timer;       //��ǰ��¼ʱ��
};

//������
struct  button_animation_item_
{
	HIMAGE  hImage;
	DWORD   ms;  //��ʱʱ��,����
};

extern HARRAY g_hArray_Animation_button;  //������ť���
extern CRITICAL_SECTION  g_CriticalSection_Animation_button; //��ť�����ٽ���

void Animation_Add(button_animation_group_ *pButtonAnimation, BOOL bClockwise); //��ӵ������б���
void Animation_Remove(button_animation_group_ *pButtonAnimation);

///////RichEdit GIF����ͼƬ/////////////////////////////////////////////
extern HARRAY g_hArray_Animation_RichEdit;  //������ť���
extern struct richEdit_item_gif_;
extern CRITICAL_SECTION  g_CriticalSection_Animation_richEdit; //��ť�����ٽ���
void Animation_Add_RichEdit(richEdit_item_gif_  *pItemGif);  //���
void Animation_Remove_RichEdit(richEdit_item_gif_  *pItemGif);//�Ƴ�


///////���ڻ����Ż�/////////////////////////////////////
extern CRITICAL_SECTION  g_CriticalSection_WindowDraw; //���ڻ����Ż�

//��̨ѭ���߳�
DWORD WINAPI XCGUI_Loop_ThreadProc(LPVOID lpParameter);

void XCGUI_Loop_timer(DWORD timer); //����ʱ��
void XCGUI_Loop_Animation(DWORD timer); //����ť����
BOOL XCGUI_Loop_Animation1(DWORD timer, button_animation_group_ *p); //����ť����,˳ʱ��
BOOL XCGUI_Loop_Animation2(DWORD timer, button_animation_group_ *p); //����ť����,��ʱ��
void XCGUI_Loop_Animation_RichEdit(DWORD timer);

//�ṩ��UI�ļ�����ģ��ʹ��/////////////////////////////////

//ע�ắ������
#define  XC_XML_INIT            1  // 1 UI�ļ��������ʼ��
#define  XC_XML_EXIT            2  // 2 UI�ļ��������ͷ�
#define  XC_XML_CREATE_WINDOW   3  // 3 ���ڴ���
#define  XC_CML_CREATE_ELEMENT  4  // 4 Ԫ�ش���


typedef BOOL(CALLBACK *pFunXml_OnInit)();  //1 UI�ļ��������ʼ��
typedef BOOL(CALLBACK *pFunXml_OnExit)();  //2 UI�ļ��������ͷ�
typedef BOOL(CALLBACK *pFunXml_OnCreateWindow)(HWINDOW hWindow);  // 3 ���ڴ���
typedef BOOL(CALLBACK *pFunXml_OnCreateElement)(HELE hEle);  // 4 Ԫ�ش���


extern pFunXml_OnInit  g_fun_init;
extern pFunXml_OnExit  g_fun_exit;
extern pFunXml_OnCreateWindow   g_fun_create_window;
extern pFunXml_OnCreateElement  g_fun_create_element;

XC_API BOOL WINAPI XML_Register(int type, void *pFun); //ע��ص�����


//ʾ��:
//BOOL CALLBACK OnInit();    //1 UI�ļ��������ʼ��
//BOOL CALLBACK OnExit();    //2 UI�ļ��������ͷ�
//BOOL CALLBACK OnCreateWindow(HWINDOW hWindow);  // 3 ���ڴ���
//BOOL CALLBACK OnCreateElement(HELE hEle);    // 4 Ԫ�ش���

