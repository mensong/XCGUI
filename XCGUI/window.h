/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct windowMsg_Header_;
//��Ϣת������
typedef BOOL(*pFunConversion)(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

struct windowProc_
{
	void  *pFun; //������Ϣ������̺���
#ifdef XCGUI_PLUS  //C++��֧��
	void  *pClass_Fun_Info; //��Ϣ�¼��ص�������Ϣָ��
#endif
	windowProc_      *pNext;
};

//////////////////////////////////////
struct windowMsg_   //������Ϣ
{
	void  *pFun; //��Ϣ��Ӧ�Ĵ�����
#ifdef XCGUI_PLUS  //C++��֧��
	void  *pClass_Fun_Info; //��Ϣ�¼��ص�������Ϣָ��
#endif
	windowMsg_    *pNext;
};

struct windowMsg_Header_  //������Ϣ ����ͷ  
{
	windowMsg_  *pList;  //ע��Ĵ�����Ϣ����
	int   message;    //��Ϣ����      //��������           

	pFunConversion  pFunConv;   //��Ϣת������
};

//�����ػ��Ż�
struct draw_window_
{
	//HWINDOW hWindow;
//	BOOL    bEmpty;  //
	BOOL    bValid;  //�Ƿ���Ч,�Ƿ�Ϊ��
	HELE    hEle;    //�ػ�Ԫ��,���Ϊ���ػ洰��

//	BOOL    bRect;   //�Ƿ�Ϊ�ػ�ָ������
	RECT    rect;    //���ڴ��ڷǿͻ�������,��������
};

//������ͼ��ʽ,�ڲ�ʹ��
//#define  XC_CS_IMAGE_STRETCH                1    //�ͻ���ͼƬ����
//#define  XC_CS_IMAGENC_STRETCH              2    //�ǿͻ���ͼƬ����
//#define  XC_CS_IMAGE_CAPTION_STRETCH        4    //������ͼƬ����
//#define  XC_CS_IMAGE_BORDER_LEFT_STRETCH    8    //�߿�ͼƬ����left
//#define  XC_CS_IMAGE_BORDER_RIGHT_STRETCH   16   //�߿�ͼƬ����right
//#define  XC_CS_IMAGE_BORDER_BOTTOM_STRETCH  32   //�߿�ͼƬ����bottom
#define  XC_CS_STROKE_INNER                 64   //�Ƿ���� ��
#define  XC_CS_STROKE_OUTER                 128  //�Ƿ���� ��


struct window_ //������Ϣ
{
	object_  object;
	int      exType; //������չ����(��������)
	//---------------------------------------
	HWND    hWnd;
	HARRAY  hArrayEle;    //��Ԫ���б�
	HARRAY  hArrayEleNC;  //��Ԫ���б�,�ǿͻ���
	HELE    pCapture;     //ӵ����겶��Ȩ��Ԫ��ָ��
	ele_    *pMouseTop;   //��ǰ������ĸ�Ԫ������
	ele_    *pFocus;      //ӵ�����뽹���Ԫ��
	ele_    *pOldFocus;   //�����ڻ�ý���ʱ,���ڻָ�Ԫ�ؽ���
	void*    userData;     //�û�����

	//���ڱ�ʶ
	///////////////////////////////////////////////////
	int   captionHeight; //�������߶�
	int   borderLeft;     //��߿���
	int   borderRight;    //�ұ߿���
	int   borderBottom;   //�±߿�߶�
	int   borderTop;      //�ϱ߿�߶�,����б���������

	int   minWidth;       //������С���
	int   minHeight;      //������С�߶�

	int   roundSize;      //Բ�Ǵ���,Բ�Ǵ�С

	SIZE  iconSize;       //������ͼ����ʾ��С
	BOOL  bTrackLeave;    //����뿪����

	HELE  hClose;      //�رհ�ť
	HELE  hMaxinize;   //��󻯰�ť
	HELE  hMinimize;   //��С����ť
	HELE  hMenuBar;    //�˵���
	HELE  hToolBar;    //������

	RECT  rcOld;       //������ǰ��С
	int   xcStyle;       //������ʽ

	BOOL  bClickTimer; //��ʱ���Ƿ�����,��ֹ�ظ�����
	BOOL  bMouseUp, bMouseDown2;
	POINT mouseDown;  //����һ�ΰ���λ��
	POINT mouseUp;    //����һ�ε���λ��
	POINT mouseDown2; //���ڶ��ΰ���λ��

	scrollBar_ *pScrollBar; //������

	//�����
	int    caretWidth;   //��������
	int    caretHeight;  //������߶�
	POINT  caretPt;      //�����λ��,����Ԫ�������
	HELE   hCaretEle;    //�����Ԫ��
	BOOL   bCaretShow;   //�Ƿ���ʾ
	BOOL   bCaretErase;  //�Ƿ���Ҫ����,TRUE:��Ҫ���������
//	BOOL   bCaretIsShow;   //�������ǰ�Ƿ���ʾ

	HBITMAP  hCaretBitmap; //���������,���ڻָ�
	COLORREF caretColor;   //�������ɫ

	//���ڻ���
	HFONTX  hFontX;   //����
	RECT   rcDraw;  //��ǰ��Ҫ�ػ�����,�ǿͻ�������
	HDC    hBkDC;   //���ڱ���DC 

	COLORREF  bkColor;  //���ڱ�����ɫ

	HBITMAP hBtimap; //���ڱ�������, �ֲ㴰����Ч
	SIZE    sizeWnd; //��ǰ���ڴ�С

	//���ڻ����Ż�
	draw_window_   drawWindow;
	//DWORD          timerDraw;  //�������ʱ��

	//͸������
	int   transparentFlag;  //͸�����ڱ�ʶ
	int   transparentAlpha; //����͸���� 0-255
	int   transparentColor; //����͸��ɫ

	//��ͼ---------------------
	int    chartletStyle;  //��ͼ��ʽ
	HIMAGE hImage_client;   //�ͻ���ͼƬ
	HIMAGE hImageNC;       //�ǿͻ���ͼƬ
	HIMAGE hImageCaption;  //������ͼƬ
	HIMAGE hImageLeft;     //�߿�ͼƬleft
	HIMAGE hImageRight;    //�߿�ͼƬright
	HIMAGE hImageBottom;   //�߿�ͼƬbottom

	COLORREF  strokeOuter_color1; //�����ɫ1 �� �߿�����,���ڵ��ڲ�
	COLORREF  strokeOuter_color2; //�����ɫ2 �� �߿���ڴ�,���ڵ����

	COLORREF  strokeInner_color1; //�����ɫ1 �� ���ڵ��ڲ�
	COLORREF  strokeInner_color2; //�����ɫ2 �� ���ڵ����

	/////////////////////////////////////
	HARRAY hArray_msg;   //��Ϣ����,�Զ�����  windowMsg_Header_
	HARRAY hArray_NCmsg; //��Ϣ����,�Զ�����  windowMsg_Header_

	windowProc_ *pWndProc;    //������Ϣ�����������

	HARRAY  hArrayPGrids;  //������������ֵ�ı��¼�, �ô����ϵ�����������
};

#ifdef XCGUI_PLUS  //C++��֧��
XC_API void WINAPI XWnd_RegisterMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //ע����Ϣ�ص�����
XC_API void WINAPI XWnd_RegisterNCMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //ע��ǿͻ�����Ϣ
XC_API void WINAPI XWnd_RegisterMsgProcEx(HWINDOW hWindow, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);	//ע�ᴰ����Ϣ�������
#endif

/// @defgroup window ��ͨ����
/// @ingroup groupWindows
/// ���ڽӿ��б�

//����API:
XC_API HWINDOW WINAPI XWnd_CreateWindow(int x, int y, int cx, int cy, wchar_t *pTitle, HWND hWndParent = NULL, int XCStyle = XC_SY_DEFAULT);
XC_API HWINDOW WINAPI XWnd_CreateWindowEx(DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle = XC_SY_DEFAULT);

XC_API void WINAPI XWnd_RegisterMessage(HWINDOW hWindow, int message, void *pFun);  //ע����Ϣ�ص�����
XC_API void WINAPI XWnd_RegisterNCMessage(HWINDOW hWindow, int message, void *pFun); //ע��ǿͻ�����Ϣ
XC_API void WINAPI XWnd_RegisterMsgProc(HWINDOW hWindow, pFunWndMsgProc pFun);	//ע�ᴰ����Ϣ�������

XC_API void WINAPI XWnd_GetDrawRect(HWINDOW hWindow, out_ RECT *pRect);//��ȡ��ǰ��������(�����ǿͻ���)
XC_API HELE WINAPI XWnd_GetFocusEle(HWINDOW hWindow); //��ȡӵ�н����Ԫ��
XC_API HWND WINAPI XWnd_GetHWnd(HWINDOW hWindow); //��ȡ���ھ��
XC_API HELE WINAPI XWnd_GetEle(HWINDOW hWindow, int eleID); //ͨ��ID��ȡԪ�ؾ��
XC_API HICON WINAPI XWnd_GetIcon(HWINDOW hWindow, BOOL bBigIcon);//��ȡ����ͼ��

XC_API int WINAPI XWnd_GetWindowText(HWINDOW hWindow, wchar_t *pOut, int len);
XC_API BOOL WINAPI XWnd_SetWindowText(HWINDOW hWindow, wchar_t *pText);

XC_API void WINAPI XWnd_SetFont(HWINDOW hWindow, HFONTX hFontX);
XC_API DWORD WINAPI XWnd_SetIcon(HWINDOW hWindow, HICON hIcon, BOOL bBigIcon);
XC_API DWORD WINAPI XWnd_SetIcon2(HWINDOW hWindow, wchar_t *pFileName, BOOL bBigIcon);
XC_API void WINAPI XWnd_SetIconSize(HWINDOW hWindow, int width, int height);  //���ñ�����ͼ����ʾ��С

XC_API UINT WINAPI XWnd_SetTimer(HWINDOW hWindow, UINT nIDEvent, UINT uElapse); //���ö�ʱ��
XC_API BOOL WINAPI XWnd_KillTimer(HWINDOW hWindow, UINT nIDEvent);

XC_API UINT WINAPI XWnd_SetTimerEx(HWINDOW hWindow, UINT nIDEvent, UINT uElapse, void* userData = 0);
XC_API BOOL WINAPI XWnd_KillTimerEx(HWINDOW hWindow, UINT nIDEvent);

XC_API void WINAPI XWnd_SetMinWidth(HWINDOW hWindow, int width);  //���ô�����С���
XC_API void WINAPI XWnd_SetMinHeight(HWINDOW hWindow, int height); //���ô�����С�߶�
XC_API void WINAPI XWnd_SetRoundSize(HWINDOW hWindow, int size);    //���ô���Բ�Ǵ�С,��Բ�Ǵ�����Ч

XC_API void WINAPI XWnd_AddEle(HWINDOW hWindow, HELE hEle);
XC_API void WINAPI XWnd_AddEleNC(HWINDOW hWindow, HELE hEle); //��ӵ��ǿͻ���

XC_API void WINAPI XWnd_AddMenuBar(HWINDOW hWindow, HELE hEle); //��ӹ�����
XC_API void WINAPI XWnd_AddToolBar(HWINDOW hWindow, HELE hEle); //��ӹ�����

XC_API void WINAPI XWnd_Adjust(HWINDOW hWindow);  //�������ڲ���

XC_API void WINAPI XWnd_MaximizeWnd(HWINDOW hWindow, BOOL bMax); //��� ��ԭ����
XC_API BOOL WINAPI XWnd_IsMaximizeWnd(HWINDOW hWindow);  //�����Ƿ����
XC_API void WINAPI XWnd_RedrawWndRect(HWINDOW hWindow, RECT *pRect, BOOL bImmediately = FALSE); //�ػ洰��ָ������
XC_API void WINAPI XWnd_RedrawWnd(HWINDOW hWindow, BOOL bImmediately = FALSE); //�ػ洰��

XC_API void WINAPI XWnd_RedrawEleRectNC(HWINDOW hWindow, HELE hEle, RECT *pRect);

XC_API void WINAPI XWnd_EnableDragBorder(HWINDOW hWindow, BOOL bDrag);  //ʹ���϶��߿�
XC_API void WINAPI XWnd_EnableDragWindow(HWINDOW hWindow, BOOL bDrag);  //�϶�����

//��ȡ��������ť:
XC_API HELE WINAPI XWnd_GetButtonMin(HWINDOW hWindow);   //��С����ť
XC_API HELE WINAPI XWnd_GetButtonMax(HWINDOW hWindow);   //��󻯰�ť
XC_API HELE WINAPI XWnd_GetButtonClose(HWINDOW hWindow); //�رհ�ť

XC_API void WINAPI XWnd_EnableMinButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE); //������С����ť
XC_API void WINAPI XWnd_EnableMaxButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE); //������󻯰�ť
XC_API void WINAPI XWnd_EnableCloseButton(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE);  //���ùرհ�ť

XC_API void WINAPI XWnd_EnableRound(HWINDOW hWindow, BOOL bEnable, BOOL bRedraw = FALSE); //Բ�ǹ��ܵ�������ر�

//��������Ԫ��
XC_API int  WINAPI XWnd_GetChildEleCount(HWINDOW hWindow);
XC_API int  WINAPI XWnd_GetChildEleCountNC(HWINDOW hWindow);
XC_API HELE WINAPI XWnd_GetChildEleByIndex(HWINDOW hWindow, int index);
XC_API HELE WINAPI XWnd_GetChildEleByIndexNC(HWINDOW hWindow, int index);

//͸������
XC_API void WINAPI XWnd_SetTransparentFlag(HWINDOW hWindow, int flag);  //����͸������
XC_API void WINAPI XWnd_SetTransparentAlpha(HWINDOW hWindow, BYTE alpha); //���ô���͸����
XC_API void WINAPI XWnd_SetTransparentColor(HWINDOW hWindow, COLORREF color); //���ô���͸��ɫ

//��ͼ:
XC_API void WINAPI XWnd_SetImage(HWINDOW hWindow, HIMAGE hImage = NULL);    //�ͻ���ͼƬ
XC_API void WINAPI XWnd_SetImageNC(HWINDOW hWindow, HIMAGE hImage = NULL);  //�ǿͻ�������ͼƬ
XC_API void WINAPI XWnd_SetImageCaption(HWINDOW hWindow, HIMAGE hImage = NULL);   //������ͼƬ
XC_API void WINAPI XWnd_SetImageBorderLeft(HWINDOW hWindow, HIMAGE hImage = NULL);    //�߿�ͼƬ
XC_API void WINAPI XWnd_SetImageBorderRight(HWINDOW hWindow, HIMAGE hImage = NULL);    //�߿�ͼƬ
XC_API void WINAPI XWnd_SetImageBorderBottom(HWINDOW hWindow, HIMAGE hImage = NULL);    //�߿�ͼƬ

XC_API void WINAPI XWnd_SetBkColor(HWINDOW hWindow, COLORREF color); //���ñ�����ɫ

XC_API void WINAPI XWnd_EnableBorderStrokeInner(HWINDOW hWindow, BOOL bStroke); //���û������ ��
XC_API void WINAPI XWnd_EnableBorderStrokeOuter(HWINDOW hWindow, BOOL bStroke); //���û������ ��

XC_API void WINAPI XWnd_SetBorderStrokeInnerColor(HWINDOW hWindow, COLORREF color1, COLORREF color2); //���������ɫ ��
XC_API void WINAPI XWnd_SetBorderStrokeOuterColor(HWINDOW hWindow, COLORREF color1, COLORREF color2); //���������ɫ ��

XC_API void WINAPI XWnd_CloseWindow(HWINDOW hWindow);  //�رմ���

//�����:
XC_API void WINAPI XWnd_CreateCaret(HWINDOW hWindow, HELE hEle, int width, int height);//���������
XC_API void WINAPI XWnd_SetCaretSize(HWINDOW hWindow, int width, int height); //���ò������С
XC_API void WINAPI XWnd_SetCaretPos(HWINDOW hWindow, int x, int y); //���ò����λ��
XC_API void WINAPI XWnd_SetCaretPosEx(HWINDOW hWindow, int x, int y, int width, int height); //���ò����λ��
XC_API void WINAPI XWnd_SetCaretColor(HWINDOW hWindow, COLORREF color); //���ò������ɫ
XC_API void WINAPI XWnd_ShowCaret(HWINDOW hWindow, BOOL bShow);  //��ʾ�����
XC_API void WINAPI XWnd_DestroyCaret(HWINDOW hWindow);    //���ٲ����


void Wnd_DrawCaret(HWINDOW hWindow); //������Ʋ����������DC
void Wnd_DrawCaretMenDC(HWINDOW hWindow, HDRAW hDraw); //������Ʋ�������ڴ�DC
void Wnd_DrawCaretTransparent(HWINDOW hWindow);
void Wnd_DrawCaretTransparentMemDC(HWINDOW hWindow, HDRAW hDraw);//������Ʋ�������ڴ�DC
void Wnd_GetCaretBk(HWINDOW hWindow); //��ȡ�������������
void Wnd_EraseCaret(HWINDOW hWindow); //���������


//����API:
XC_API BOOL WINAPI XWnd_GetClientRect(HWINDOW hWindow, out_ RECT *pRect); //��ȡ�ͻ�������(���Ͻ�0,0)
XC_API void WINAPI XWnd_GetNCClientRect(HWINDOW hWindow, out_ RECT *pRect); //�ǿͻ�������,������������(���Ͻ�0,0)
XC_API int WINAPI XWnd_GetClientLeft(HWINDOW hWindow); //�ͻ�������
XC_API int WINAPI XWnd_GetClientTop(HWINDOW hWindow);  //�ͻ����ϼ��
XC_API int WINAPI XWnd_GetClientRight(HWINDOW hWindow); //�ͻ����Ҽ��
XC_API int WINAPI XWnd_GetClientBottom(HWINDOW hWindow); //�ͻ����¼��
XC_API int WINAPI XWnd_GetCaptionHeight(HWINDOW hWindow); //��ȡ�������߶�

XC_API void WINAPI XWnd_SetBorderSize(HWINDOW hWindow, int left, int top, int right, int bottom); //���ô��ڱ߿��С
XC_API void WINAPI XWnd_SetCaptionHeight(HWINDOW hWindow, int captionHeight); //���ñ������߶�

XC_API void WINAPI XWnd_WindowToClientRect(HWINDOW hWindow, in_out_ RECT *pRect); //���ڷǿͻ�������ת�����ͻ�������
XC_API void WINAPI XWnd_WindowToClientPt(HWINDOW hWindow, in_out_ POINT *pPt); //���ڷǿͻ�����ת�����ͻ��������

XC_API void WINAPI XWnd_SetUserData(HWINDOW hWindow, void* data);
XC_API void* WINAPI XWnd_GetUserData(HWINDOW hWindow);

//��װAPI:
XC_API BOOL WINAPI XWnd_ShowWindow(HWINDOW hWindow, int nCmdShow);
XC_API BOOL WINAPI XWnd_SetWindowPos(HWINDOW hWindow, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);
XC_API BOOL WINAPI XWnd_SetWindowRect(HWINDOW hWindow, in_ RECT *pRect);
XC_API BOOL WINAPI XWnd_SetWindowSize(HWINDOW hWindow, int width, int height);

XC_API BOOL WINAPI XWnd_GetWindowRect(HWINDOW hWindow, out_ RECT *pRect);

XC_API BOOL WINAPI XWnd_IsWindowVisible(HWINDOW hWindow);

//˽�з���:
BOOL Wnd_Init(HWINDOW hWindow, DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, int XCStyle, int exType);
void Wnd_AdjustCaption(HWINDOW hWindow, int cx);    //������������ť cx:���ڿ��,�����ǿͻ���

BOOL Wnd_KeyDown(HWINDOW hWindow, int key); //Ԫ�ؽ����л�����
BOOL Wnd_HandleFocusUp(HWINDOW hWindow);   //�������л�
BOOL Wnd_HandleFocusDown(HWINDOW hWindow); //�������л�
int  Wnd_GetWindowCount();//��ȡ��������
HELE Wnd_GetChildEle(HELE hEle, int eleID);

void Wnd_RedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect); //�ػ�Ԫ��ָ������
BOOL Wnd_ReDrawEle_Overlapping(HWINDOW hWindow, HELE hEle, RECT *pRect); //���Ԫ���ص�


//���ƴ���
void Wnd_DrawWindowHandle(HWINDOW hWindow, RECT *pRect);
void Wnd_DrawWindowHandle2(HWINDOW hWindow, windowMsg_Header_ *pHeader, RECT *pRect, HDC hdc);

void Wnd_DrawWindow_Optimization(HWINDOW hWindow, RECT *pRect);

void Wnd_DrawWindow_NCClient(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawWindow_Client(HWINDOW hWindow, HDRAW hDraw, windowMsg_Header_ *pHeader);//���ƿͻ���
void Wnd_DrawWindow_Shadow(HWINDOW hWindow, HDC hdc); //������Ӱ
void Wnd_DrawWindow_Caret(HWINDOW hWindow, HDRAW hDraw); //��������

//�ػ�Ԫ��
void Wnd_PaintEle(HWINDOW hWindow, HELE hEle, RECT *pRect);
void Wnd_PaintEle2(HWINDOW hWindow, HELE hEle, HDC hdc, RECT *pRect);

ele_* Wnd_PaintEle_IsDrawEle(HWINDOW hWindow, HELE hEle); //����Ƿ�ֱ���ػ�Ԫ��
void Wnd_PaintEle_Shadow(HWINDOW hWindow, HDC hdc); //������Ӱ
void Wnd_PaintEle_Caret(HWINDOW hWindow, HDRAW hDraw); //��������
HDC  Wnd_GetBkDC(HWINDOW hWindow);  //��ȡ���ڱ���DC

////////////////////////////////////////////////////////////////
void Wnd_PaintEle_Optimization(HWINDOW hWindow, HELE hEle, RECT *pRect); //�Ż�����
void Wnd_PaintEle_Optimization1(HWINDOW hWindow, HELE hEle, RECT *pRect);//��ǰΪ��
void Wnd_PaintEle_Optimization2(HWINDOW hWindow, HELE hEle, RECT *pRect);//ͬһ��Ԫ��
void Wnd_PaintEle_Optimization3(HWINDOW hWindow, HELE hEle, RECT *pRect);//��ǰΪ�ػ�ָ������
void Wnd_PaintEle_Optimization4(HWINDOW hWindow, HELE hEle, RECT *pRect);//��ǰΪ�ػ洰��


//////////////////////////////////////////////////////////////

void Wnd_DrawCaption(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawCaptionImageNC(HWINDOW hWindow, HDRAW hDraw); //���ǿͻ�����ͼʱ
void Wnd_DrawBorderLeft(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawBorderRight(HWINDOW hWindow, HDRAW hDraw);
void Wnd_DrawBorderBottom(HWINDOW hWindow, HDRAW hDraw);


BOOL Wnd_ConvPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvClose(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvDestroy(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCDestroy(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvLButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvLButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvRButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvRButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvExitSizeMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseLeave(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvSize(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvTimer(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //��ʱ��
BOOL Wnd_ConvTimer2(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //��ʱ��

BOOL Wnd_ConvSetFocus(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvKillFocus(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvCaptureChanged(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseWheel(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Wnd_ConvMouseClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMouseDBClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvRedrawEle(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMenuSelect(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvMenuExit(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvSetFont(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Wnd_ConvOther(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//�ǿͻ���
BOOL Wnd_ConvNCPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCEndPaint(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCMouseMove(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCLButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCLButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCRButtonDown(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCRButtonUp(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCMouseClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Wnd_ConvNCMouseDBClick(HWINDOW hWindow, windowMsg_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//�ص�����
BOOL CALLBACK Wnd_WindowProc(HWINDOW hWindow, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Wnd_OnDrawT(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Wnd_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK Wnd_OnRedrawEle(HWINDOW hWindow, HELE hEle, RECT *pRect);
BOOL CALLBACK Wnd_OnDestroy(HWINDOW hWindow);
BOOL CALLBACK Wnd_OnNCDestroy(HWINDOW hWindow);
BOOL CALLBACK Wnd_OnMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnRButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnRButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnMouseLeave(HWINDOW hWindow);
BOOL CALLBACK Wnd_OnSize(HWINDOW hWindow, UINT type, SIZE *pSize);//ON SIZE ���ڴ�С�ı�
BOOL CALLBACK Wnd_OnTimer(HWINDOW hWindow, UINT_PTR nIDEvent, UINT uElapse);
BOOL CALLBACK Wnd_OnMouseClick(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK Wnd_OnMouseDBClick(HWINDOW hWindow, POINT *pPt);  //OnMouseDBClick
BOOL CALLBACK Wnd_OnSetFocus(HWINDOW hWindow);  //���ڻ�ý���
BOOL CALLBACK Wnd_OnKillFocus(HWINDOW hWindow); //����ʧȥ����
BOOL CALLBACK Wnd_OnKeyDown(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);	//WM_KEDOWN
BOOL CALLBACK Wnd_OnChar(HWINDOW hWindow, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Wnd_OnCaptureChanged(HWINDOW hWindow, HWND hWnd);
BOOL CALLBACK Wnd_OnMouseWheel(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_MOUSEWHEEL ������Ϣ
BOOL CALLBACK Wnd_OnTimerEx(HWINDOW hWindow, UINT timerID, void* userData); //��ʱ����Ϣ


BOOL CALLBACK Wnd_OnRedraw(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //�Զ�����Ϣ,Ϊ���ػ��ӳ�
BOOL CALLBACK Wnd_OnMinMaxInfo(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //WM_GETMINMAXINFO ���ƴ��ڴ�С

//���ڷǿͻ���
BOOL Wnd_NCWindowProc(HWINDOW hWindow, UINT NCmessage, WPARAM wParam, LPARAM lParam);  //�ǿͻ�����Ϣ����

BOOL CALLBACK Wnd_OnNCDrawWindow(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK Wnd_OnNCMouseMove(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnNCLButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnNCLButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);

BOOL CALLBACK Wnd_OnNCRButtonDown(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK Wnd_OnNCRButtonUp(HWINDOW hWindow, UINT flags, POINT *pPt);

BOOL CALLBACK Wnd_OnNCMouseClick(HWINDOW hWindow, POINT *pPt);
BOOL CALLBACK Wnd_OnNCMouseDBClick(HWINDOW hWindow, POINT *pPt);


/////��������ť////////////////////
BOOL CALLBACK Wnd_OnBtnCloseDraw(HELE hELe, HDRAW hDraw);
BOOL CALLBACK Wnd_OnBtnMaximizeDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Wnd_OnBtnMinimizeDraw(HELE hEle, HDRAW hDraw);

//��������ť�¼�
BOOL CALLBACK Wnd_OnEventBtnCloseClick(HELE hEle, HELE hButton); //�رհ�ť
BOOL CALLBACK Wnd_OnEventBtnMaximizeClick(HELE hEle, HELE hButton); //��󻯰�ť
BOOL CALLBACK Wnd_OnEventBtnMinimizeClick(HELE hEle, HELE hButton); //��С����ť
