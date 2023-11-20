/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

//v1.5

//#include <docobj.h> //��DLL�ļ�ʹ�ø�ͷ�ļ�ʱ,��ȡ��ע��
#include <exdispid.h>

#ifndef XCGUI_HEADER_FILE_
#define XCGUI_HEADER_FILE_

// �û��Զ�����Ϣ��Χ     WM_USER -  0x7000
// �Ų��ڲ��Զ�����Ϣ��Χ 0x7001  -  0x7FFF


#define XC_API

//�ӿ�����

/// @defgroup groupObjectType �ӿھ������
/// @ingroup macroDefine
/// @{
//����:
#define  XC_WINDOW         1   ///<����
#define  XC_MODALWINDOW    2   ///<ģ̬����
#define  XC_FRAMEWND       3   ///<��ܴ���
#define  XC_FLOATWND       4   ///<��������

//Ԫ�� :
#define  XC_ELE            20  ///<Ԫ��
#define  XC_BUTTON         21  ///<��ť
#define  XC_RADIO          22  ///<��ѡ��ť
#define  XC_CHECK          23  ///<��ѡ��ťԪ��
#define  XC_EDIT           24  ///<�༭��Ԫ��
#define  XC_RICHEDIT       25  ///<���ı��༭��
#define  XC_COMBOBOX       26  ///<������Ͽ�Ԫ��
#define  XC_SCROLLBAR      27  ///<������Ԫ��
#define  XC_SCROLLVIEW     28  ///<������ͼԪ��
#define  XC_LIST           29  ///<�б�Ԫ��
#define  XC_LISTBOX        30  ///<�б��Ԫ��
#define  XC_TREE           31  ///<��Ԫ��
#define  XC_MENUBAR        32  ///<�˵���
#define  XC_PROPERTYPAGE   33  ///<����ҳ
#define  XC_SLIDERBAR      34  ///<������
#define  XC_PROGRESSBAR    35  ///<������
#define  XC_TOOLBAR        36  ///<������
#define  XC_STATIC         37  ///<��̬�ı�Ԫ��
#define  XC_GROUPBOX       38  ///<���
#define  XC_PICTURE        39  ///<ͼƬԪ��
#define  XC_MONTHCAL       40  ///<����Ԫ��
#define  XC_DATETIME       41  ///<ʱ��Ԫ��
#define  XC_PROPERTYGRID   42  ///<��������
#define  XC_CHOOSECOLOR    43  ///<��ɫѡ��Ԫ��
#define  XC_OUTLOOK        44  ///<��������
#define  XC_TEXTLINK       45  ///<�����ı�
#define  XC_TABBAR         46  ///<TabBar
#define  XC_GIF            47  ///<GIF����
#define  XC_EDITFILE       48  ///<�ļ�ѡ��༭��
#define  XC_LISTVIEW       49  ///<�б���ͼ,��ͼ��
#define  XC_PANE           50  ///<���ִ���
#define  XC_DRAGBAR        51  ///<���ִ����϶��ָ���

#define  XC_SCROLLVIEW_VIEW     52  ///<������ͼԪ�ص���


#define  XC_MENUBAR_BUTTON        60  ///<�˵����ϵİ�ť
#define  XC_TOOLBAR_BUTTON        61  ///<�������ϰ�ť
#define  XC_PROPERTYPAGE_LABEL    62  ///<����ҳ��ǩ��ť


#define  XC_ARRAY          70  ///<�������
#define  XC_STRING         71  ///<�ַ�������
#define  XC_IMAGELIST      72  ///<ͼƬ�б�
#define  XC_MENU           73  ///<�����˵�
#define  XC_IMAGE          74  ///<ͼƬ����
#define  XC_HDRAW          75  ///<��ͼ����
#define  XC_FONT           76  ///<�Ų�����

#define  XC_PIER           102  ///<����ͣ����ͷ
#define  XC_PANE_CELL      103  

///@}



//���ⰴť:
#define XC_BUTTON_MIN     201  //��С�����ڰ�ť
#define XC_BUTTON_MAX     202  //��󻯴��ڰ�ť
#define XC_BUTTON_CLOSE   203  //�رմ��ڰ�ť

//#define XC_BUTTON_HSCROLLBAR_SLIDER   104  //ˮƽ������,���鰴ť
//#define XC_BUTTON_VSCROLLBAR_SLIDER   105  //��ֱ������,���鰴ť
//#define XC_BUTTON_HSCROLLBAR_LEFT     106  //ˮƽ������,�������ť
//#define XC_BUTTON_HSCROLLBAR_RIGHT    107  //ˮƽ������,�ҹ�����ť
//#define XC_BUTTON_VSCROLLBAR_TOP      108  //��ֱ������,�Ϲ�����ť
//#define XC_BUTTON_VSCROLLBAR_BOTTOM   109  //��ֱ������,�¹�����ť
#define XC_BUTTON_SLIDERBAR_SLIDER    210  //������,���鰴ť
//#define XC_BUTTON_COMBOBOX_POP        111  //��Ͽ������б�����ť
//#define XC_BUTTON_PROPERTYPAGE_LEFT   112  //����ҳ,�������ť
//#define XC_BUTTON_PROPERTYPAGE_RIGHT  113  //����ҳ,�ҹ�����ť
//#define XC_BUTTON_PROPERTYPAGE_LABEL  114  //����ҳ,��ǩ��ť
//#define XC_BUTTON_DATETIME_POP        115  //����ʱ��Ԫ��,����ѡ��Ƭ��ť



///�������///////////////////
#define in_
#define out_
#define in_out_


#ifdef _DEBUG
#define DECLARE_HANDLEX(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
#define	DECLARE_HANDLEX(name) typedef void* name
#endif


//�ӿھ������

/// @defgroup groupHandle ����б�
/// @ingroup macroDefine
/// @{
typedef void*  HXCGUI;    ///<��Դ���
DECLARE_HANDLEX(HWINDOW); ///<������Դ���
DECLARE_HANDLEX(HELE);    ///<Ԫ����Դ���
DECLARE_HANDLEX(HMENUX);  ///<�˵���Դ���
DECLARE_HANDLEX(HSTRING); ///<�ַ�����Դ���
DECLARE_HANDLEX(HDRAW);   ///<ͼ�λ�����Դ���
DECLARE_HANDLEX(HARRAY);  ///<������Դ���
DECLARE_HANDLEX(HIMAGE);  ///<ͼƬ��Դ���
DECLARE_HANDLEX(HXMLRES); ///<XML��Դ���
DECLARE_HANDLEX(HARRAY_ITERATOR); ///<���������
DECLARE_HANDLEX(HFONTX);    ///<�Ų�������

DECLARE_HANDLEX(HPANE_GROUP); ///<��������
///@}


/// @defgroup groupImageDrawType ͼƬ��������
/// @ingroup macroDefine
/// @{
#define XC_IMAGE_DEFAULT  0  ///<Ĭ��
#define XC_IMAGE_STRETCH  1  ///<����
#define XC_IMAGE_ADAPTIVE 2  ///<����Ӧ
#define XC_IMAGE_TILE     3  ///<ƽ��

///@}

//״̬--------------------------------------
/// @defgroup groupButtonState ��ť״̬
/// @ingroup macroDefine
/// @{
#define  STATE_LEAVE   0   ///<�뿪
#define  STATE_DOWN    1   ///<����
#define  STATE_STAY    2   ///<ͣ��
#define  STATE_SELECT  3   ///<ѡ��,����

///@}


//������ʽ----------------------------

/// @defgroup groupWindowStyle �Ųʴ�����ʽ
/// @ingroup macroDefine
/// @{
#define  XC_SY_MINIMIZE   0x00000001  ///<��С�����ڰ�ť
#define  XC_SY_MAXIMIZE   0x00000002  ///<��󻯴��ڰ�ť
#define  XC_SY_CLOSE      0x00000004  ///<�رմ��ڰ�ť
#define  XC_SY_CAPTION    0x00000008  ///<������
#define  XC_SY_BORDER     0x00000010  ///<�߿�
#define  XC_SY_ROUND      0x00000020  ///<Բ�Ǵ���
#define  XC_SY_CENTER     0x00000040  ///<���ھ���

#define  XC_SY_DRAG_BORDER 0x00000080  ///<�϶����ڱ߿�
#define  XC_SY_DRAG_WINDOW 0x00000100  ///<�϶�����
#define  XC_SY_DRAW_CAPTION_ICON  0x00000200 ///<���ƴ��ڱ�����ͼ��
#define  XC_SY_DRAW_CAPTION_TITLE 0x00000400 ///<���ƴ��ڱ������ı�

///����Ĭ����ʽ 1791
#define  XC_SY_DEFAULT (XC_SY_MINIMIZE | \
	XC_SY_MAXIMIZE | \
	XC_SY_CLOSE | \
	XC_SY_CAPTION | \
	XC_SY_BORDER | \
	XC_SY_ROUND | \
	XC_SY_CENTER | \
	XC_SY_DRAG_BORDER | \
	XC_SY_DRAW_CAPTION_ICON | \
	XC_SY_DRAW_CAPTION_TITLE)

///ģ̬����
#define  XC_SY_MODAL_WINDOW (XC_SY_CLOSE | \
	XC_SY_CAPTION | \
	XC_SY_BORDER | \
	XC_SY_ROUND | \
	XC_SY_DRAW_CAPTION_ICON | \
	XC_SY_DRAW_CAPTION_TITLE)

///@}

//͸������
/// @defgroup groupWindowTransparent �Ųʴ���͸����ʶ
/// @ingroup macroDefine
/// @{
#define XC_WIND_TRANSPARENT_NO       0 ///<Ĭ�ϴ���,��͸��
#define XC_WIND_TRANSPARENT_SHAPED   1 ///<͸������,��͸��ͨ��,����.
#define XC_WIND_TRANSPARENT_SHADOW   2 ///<��Ӱ����,��͸��ͨ��,�߿���Ӱ,����͸�����͸��.
#define XC_WIND_TRANSPARENT_SIMPLE   4 ///<͸������,����͸��ͨ��,ָ����͸����,ָ��͸��ɫ.
#define XC_WIND_TRANSPARENT_WIN7     8 ///<WIN7��������,��ҪWIN7������Ч,��ǰδ����.

///@}

//������Ϣ������
/// @defgroup groupMessageBox ������Ϣ��
/// @ingroup macroDefine
/// @{
#define  XMB_OK       1  ///<ȷ����ť
#define  XMB_CANCEL   2  ///<ȡ����ť

///@}

//����Ԫ��------------------------------------------------
/// @defgroup groupAddElement ���Ԫ��
/// @ingroup macroDefine
/// @{
#define  XC_ADDELE_END      0    ///<���ӵ�ĩβ
#define  XC_ADDELE_FRIST    1    ///<���ӵ���һλ��
#define  XC_ADDELE_BEFORE   2    ///<���ӵ�ָ��Ԫ��ǰ��
#define  XC_ADDELE_AFTER    3    ///<���ӵ�ָ��Ԫ�غ���
#define  XC_ADDELE_INDEX    4    ///<���ӵ�ָ��λ������

///@}

//����Ԫ��Z��-----------------------
/// @defgroup groupSetZOrder Ԫ��Z��
/// @ingroup macroDefine
/// @{
#define XC_ZORDER_TOP     0  ///<������
#define XC_ZORDER_BOTTOM  1  ///<������
#define XC_ZORDER_BEFORE  2  ///<ָ��Ԫ����Ŀ��Ԫ������
#define XC_ZORDER_AFTER   3  ///<ָ��Ԫ����Ŀ��Ԫ������
#define XC_ZORDER_INDEX   4  ///<ָ������λ��

///@}

//��ťͼ����뷽ʽ
/// @defgroup groupIconAlign ��ťͼ����뷽ʽ
/// @ingroup macroDefine
/// @{
#define XC_ICON_ALIGN_LEFT     0  ///<ͼ�������
#define XC_ICON_ALIGN_TOP      1  ///<ͼ���ڶ���
#define XC_ICON_ALIGN_RIGHT    2  ///<ͼ�����ұ�
#define XC_ICON_ALIGN_BOTTOM   3  ///<ͼ���ڵײ�

///@}

//������
/// @defgroup groupScrollBar ������
/// @ingroup macroDefine
/// @{
#define  SY_HSCROLL     TRUE   ///<ˮƽ������
#define  SY_VSCROLL     FALSE  ///<��ֱ������

///@}

//��Ԫ��
/// @defgroup groupTree �б���Ԫ��
/// @ingroup macroDefine
/// @{
#define  XTREE_INSERT_BEGIN  -2  ///<���뵱ǰ�㿪ʼ
#define  XTREE_INSERT_LAST   -1  ///<���뵱ǰ��ĩβ

#define  XTREE_ROOT  0       ///<���ڵ�

///@}

//���ڶ������Ķ�������ڵ�ID
#define  XMTREE_ROOT   -1            //���ڵ�ID
//�����˵����ڵ�ID
#define  XMENU_ROOT    XMTREE_ROOT   //���ڵ�ID

/// @defgroup groupMenu �����˵�
/// @ingroup macroDefine
/// @{

//�����˵����ʶ
///@name �����˵����ʶ
///@{
#define  XM_SELECT      1   ///<ѡ��
#define  XM_DISABLED    2   ///<����
#define  XM_CHECK       4   ///<��ѡ
#define  XM_POPUP       8   ///<����
#define  XM_SEPARATOR   16  ///<�ָ��� ID������,ID�ű�����

///@}

//�����˵�����
///@name �����˵�����
///@{
#define  XM_LEFT_TOP       0   ///<���Ͻ�
#define  XM_LEFT_BOTTOM    1   ///<���½�
#define  XM_RIGHT_TOP      2   ///<���Ͻ�
#define  XM_RIGHT_BOTTOM   3   ///<���½�
#define  XM_CENTER_LEFT    4   ///<�����
#define  XM_CENTER_TOP     5   ///<�Ͼ���
#define  XM_CENTER_RIGHT   6   ///<�Ҿ���
#define  XM_CENTER_BOTTOM  7   ///<�¾���

///@}

//�˵�ID--------------------------------------
///@name �˵�ID
///@{
#define  IDM_CLIP          1000000000    ///<����
#define  IDM_COPY          1000000001    ///<����
#define  IDM_PASTE         1000000002    ///<ճ��
#define  IDM_DELETE        1000000003    ///<ɾ��
#define  IDM_SELECTALL     1000000004    ///<ȫѡ
#define  IDM_DELETEALL     1000000005    ///<���

///@}

//����˵�
///@name ����˵�
///@{
#define  IDM_LOCK          1000000006    ///<����
#define  IDM_DOCK          1000000007    ///<ͣ��
#define  IDM_FLOAT         1000000008    ///<����
#define  IDM_HIDE          1000000009    ///<����

///@}


///@}

//��������Ԫ��,������
/// @defgroup groupPropertyGrid ��������Ԫ��
/// @ingroup macroDefine
/// @{

///@name ������
///@{
#define  PGRID_STRING       0  ///<Ĭ��,�ַ�������
#define  PGRID_EDIT         1  ///<�༭��
#define  PGRID_COMBOBOX     2  ///<��Ͽ�
#define  PGRID_CHOOSECOLOR  3  ///<��ɫѡ��Ԫ��
#define  PGRID_EDIT_FILE    4  ///<�ļ�ѡ��༭��
///@}

///@}

enum align_type_
{
	align_any = 1,
	align_left,
	align_top,
	align_right,
	align_bottom,
	align_group_member, //���Ա
};

//����״̬
enum pane_state_
{
	pane_state_any = 0,
	pane_state_lock,
	pane_state_dock,
	pane_state_float,
	pane_state_hide,
};

//������Ϣ
/**
@addtogroup wndMSG

<hr>
<h2>Windows ��׼��Ϣ</h2>
- @ref WM_PAINT ���ڻ�����Ϣ
- @ref WM_CLOSE ���ڹر���Ϣ.
- @ref WM_DESTROY ����������Ϣ.
- @ref WM_NCDESTROY ���ڷǿͻ���������Ϣ.
- @ref WM_MOUSEMOVE ��������ƶ���Ϣ.
- @ref WM_LBUTTONDOWN ����������������Ϣ
- @ref WM_LBUTTONUP ����������������Ϣ.
- @ref WM_RBUTTONDOWN ��������Ҽ�������Ϣ.
- @ref WM_RBUTTONUP ��������Ҽ�������Ϣ.
- @ref WM_MOUSEWHEEL ���������ֹ�����Ϣ.
- @ref WM_EXITSIZEMOVE �����˳��ƶ��������Сģʽѭ���ģ�����μ�MSDN.
- @ref WM_MOUSELEAVE ��������뿪��Ϣ.
- @ref WM_SIZE ���ڴ�С�ı���Ϣ.
- @ref WM_TIMER ���ڶ�ʱ����Ϣ.
- @ref WM_SETFOCUS ���ڻ�ý���.
- @ref WM_KILLFOCUS ����ʧȥ����.
- @ref WM_KEYDOWN ���ڼ��̰�����Ϣ.
- @ref WM_CAPTURECHANGED ������겶��ı���Ϣ.
- @ref other ����Windowsϵͳ��Ϣ,�������Զ����Windows��Ϣ.

<hr>
@anchor WM_PAINT WM_PAINT ���ڻ�����Ϣ
@code   BOOL CALLBACK WndDrawWindow(HWINDOW hWindow,HDRAW hDraw); @endcode
@param  hWindow ���ھ��.
@param  hDraw   ͼ�λ��ƾ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_CLOSE WM_CLOSE ���ڹر���Ϣ.
@code   BOOL CALLBACK WndClose(HWINDOW hWindow); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_DESTROY WM_DESTROY ����������Ϣ.
@code   BOOL CALLBACK WndDestroy(HWINDOW hWindow);  @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_NCDESTROY WM_NCDESTROY ���ڷǿͻ���������Ϣ.
@code   BOOL CALLBACK WndNCDestroy(HWINDOW hWindow); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_MOUSEMOVE WM_MOUSEMOVE ��������ƶ���Ϣ.
@code   BOOL CALLBACK WndMouseMove(HWINDOW hWindow,UINT flags,POINT *pPt);  @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_MOUSEMOVE wParam����.
@param  pPt     ��������.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_LBUTTONDOWN WM_LBUTTONDOWN ����������������Ϣ
@code   BOOL CALLBACK WndLButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_LBUTTONDOWN.
@param  pPt     ��������.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_LBUTTONUP WM_LBUTTONUP ����������������Ϣ.
@code   BOOL CALLBACK WndLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_LBUTTONUP.
@param  pPt     ��������.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_RBUTTONDOWN WM_RBUTTONDOWN ��������Ҽ�������Ϣ.
@code   BOOL CALLBACK WndRButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_RBUTTONDOWN.
@param  pPt     ��������.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_RBUTTONUP WM_RBUTTONUP ��������Ҽ�������Ϣ.
@code   BOOL CALLBACK WndRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_RBUTTONUP.
@param  pPt     ��������.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_MOUSEWHEEL WM_MOUSEWHEEL ���������ֹ�����Ϣ.
@code   BOOL CALLBACK WndMouseWheel(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_MOUSEWHEEL��ϢwParam����.
@param  pPt     ��������.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_EXITSIZEMOVE WM_EXITSIZEMOVE �����˳��ƶ��������Сģʽѭ���ģ�����μ�MSDN.
@code   BOOL CALLBACK WndExitSizeMove(HWINDOW hWindow); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_MOUSELEAVE WM_MOUSELEAVE ��������뿪��Ϣ.
@code   BOOL CALLBACK WndMouseLeave(HWINDOW hWindow); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_SIZE WM_SIZE ���ڴ�С�ı���Ϣ.
@code   BOOL CALLBACK WndSize(HWINDOW hWindow,UINT flags,SIZE *pSize); @endcode
@param  hWindow ���ھ��.
@param  flags   ��μ�MSDN WM_SIZE��ϢwParam����.
@param  pSize   ���ڴ�С.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_TIMER WM_TIMER ���ڶ�ʱ����Ϣ.
@code   BOOL CALLBACK WndTimer(HWINDOW hWindow,UINT_PTR nIDEvent,UINT uElapse); @endcode
@param  hWindow  ���ھ��.
@param  nIDEnent ��ʱ����ʾ��.
@param  uElapse  ָ����������ϵͳ���������ĺ�����,������GetTickCount�����ķ���ֵ.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_SETFOCUS WM_SETFOCUS ���ڻ�ý���.
@code   BOOL CALLBACK WndSetFocus(HWINDOW hWindow); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_KILLFOCUS WM_KILLFOCUS ����ʧȥ����.
@code   BOOL CALLBACK WndKillFocus(HWINDOW hWindow); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor WM_KEYDOWN WM_KEYDOWN ���ڼ��̰�����Ϣ.
@code   BOOL CALLBACK WndKeyDown(HWINDOW hWindow,WPARAM wParam,LPARAM lParam); @endcode
@param  hWindow ���ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
@note   wParam,lParam:��μ�MSDN WM_KEYDOWN.

<hr>
@anchor WM_CAPTURECHANGED WM_CAPTURECHANGED ������겶��ı���Ϣ.
@code   BOOL CALLBACK WndCaptureChanged(HWINDOW hWindow,HWND hWnd); @endcode
@param  hWindow ���ھ��.
@param  hWnd    �����겶��Ĵ��ھ��.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.

<hr>
@anchor other ����Windowsϵͳ��Ϣ,�������Զ����Windows��Ϣ.
@code   BOOL CALLBACK WndOther(HWINDOW hWindow,WPARAM wParam,LPARAM lParam); @endcode
@param  hWindow ���ھ��.
@param  wParam  ��Ϣ����.
@param  lParam  ��Ϣ����.
@return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
@note   ������Ϣ��μ�MSDN.
@{
*/

///@brief ��굥������
///@code  BOOL CALLBACK WndMouseClick(HWINDOW hWindow,POINT *pPt); @endcode
#define  XWM_MOUSECLICK       0x7000+1 //wParam:x����, lParam:y����

///@brief ���˫������
///@code  BOOL CALLBACK WndMouseDBClick(HWINDOW hWindow,POINT *pPt) @endcode
///@param hWindow ���ھ��
///@param pPt     ���λ��
#define  XWM_MOUSEDBCLICK     0x7000+2 //wParam:x����, lParam:y����

///@brief �ػ�Ԫ��
///@code BOOL CALLBACK WndRedrawEle(HWINDOW hWindow,HELE hEle,RECT *pRect);  @endcode
#define  XWM_REDRAW_ELE       0x7000+3 //�ػ�Ԫ�� wParam:Ԫ�ؾ��, lParam:*

///@brief �˵�ѡ��
///@code  BOOL CALLBACK WndMenuSelect(HWINDOW hWindow,int id); @endcode
#define  XWM_MENUSELECT       0x7000+4 //�˵�ѡ�� wParam:�˵���ID, lParam:0

///@brief �˵��˳�
///@code  BOOL CALLBACK WndMenuExit(HWINDOW hWindow); @endcode
#define  XWM_MENUEXIT         0x7000+5 //�˵��˳� wParam:0, lParam:0

///@brief ��������ı�
///@code  BOOL CALLBACK WndSetFont(HWINDOW hWindow);  @endcode
#define  XWM_SETFONT          0x7000+6 //��������ı�

//�Ųʶ�ʱ��
///@code  BOOL CALLBACK WndTimer2(HWINDOW hWindow,int timerID, void* userData);  @endcode
#define  XWM_TIMER            0x7000+8 //wParam:, lParam:


#define  XWM_DRAW_T           0x7000+9  //���ڻ���,�ڲ�ʹ��, wParam:0, lParam:0


///@}



//���ڷǿͻ�����Ϣ-�߼��ϵķǿͻ���
/// @addtogroup wndNCMSG
/// ���ڷǿͻ�����Ϣ-�߼��ϵķǿͻ���
/// @{

/// @brief ���ڷǿͻ���������Ϣ
/// @code  BOOL CALLBACK WndNCDrawWindow(HWINDOW hWindow,HDRAW hDraw); @endcode
/// @param hWindow ���ھ��
/// @param hDraw   ͼ�λ��ƾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCPAINT         0  //wParam:HDC lParam:0

/// @brief ���ڻ��������Ϣ,����ʾ֮ǰ
/// @code  BOOL CALLBACK WndNCEndDrawWindow(HWINDOW hWindow,HDRAW hDraw); @endcode
/// @param hWindow ���ھ��
/// @param hDraw   ͼ�λ��ƾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCENDPAINT      1  //wParam:HDC lParam:0       ���ڻ�����ɺ����,������Ч�ϳ�

/// @brief ���ڷǿͻ�������ƶ���Ϣ.
/// @code  BOOL CALLBACK WndNCMouseMove(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param flags   ��μ�msdn WM_MOUSEMOVE.
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCMOUSEMOVE     2  //wParam:��ӦϵͳwParam lParam:�����

/// @brief ���ڷǿͻ���������������Ϣ.
/// @code  BOOL CALLBACK WndNCLButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param flags   ��μ�msdn WM_LBUTTONDOWN.
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCLBUTTONDOWN   3  //wParam:��ӦϵͳwParam lParam:�����

/// @brief ���ڷǿͻ���������������Ϣ.
/// @code  BOOL CALLBACK WndNCLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param flags   ��μ�msdn MSDN WM_LBUTTONUP.
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCLBUTTONUP     4  //wParam:��ӦϵͳwParam lParam:�����

/// @brief ���ڷǿͻ�������Ҽ�������Ϣ.
/// @code  BOOL CALLBACK WndNCRButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param flags   ��μ�msdn MSDN WM_RBUTTONDOWN.
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCRBUTTONDOWN   5  //wParam:��ӦϵͳwParam lParam:�����

/// @brief ���ڷǿͻ�������Ҽ�������Ϣ.
/// @code  BOOL CALLBACK WndNCRButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param flags   ��μ�msdn MSDN WM_RBUTTONUP.
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCRBUTTONUP     6  //wParam:��ӦϵͳwParam lParam:�����

/// @brief ���ڷǿͻ��������������Ϣ.
/// @code  BOOL CALLBACK WndNCMouseClick(HWINDOW hWindow,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCMOUSECLICK    7  //wParam:����� lParam:0    ��굥��      �ǿͻ���

/// @brief ���ڷǿͻ���������˫����Ϣ.
/// @code  BOOL CALLBACK WndNCMouseDBClick(HWINDOW hWindow,POINT *pPt); @endcode
/// @param hWindow ���ھ��
/// @param pPt     ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XWM_NCMOUSEDBCLICK  8  //wParam:����� lParam:0    ���˫������  �ǿͻ���

///@}

//Ԫ����Ϣ
/// @addtogroup eleMSG
/// @{

/// @brief Ԫ�ػ�����Ϣ.
/// @code  BOOL CALLBACK EleDraw(HELE hEle,HDRAW hDraw); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param hDraw ͼ�λ��ƾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_PAINT          100   //wParam:hDraw,lParam:0

/// @brief Ԫ�������������Ϣ.
/// @code  BOOL CALLBACK EleMouseClick(HELE hEle,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param pPt  ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_MOUSECLICK     101   //��굥��  wParam:POINT����,lParam:0

/// @brief Ԫ��������˫����Ϣ.
/// @code  BOOL CALLBACK EleMouseDBClick(HELE hEle,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param pPt  ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_MOUSEDBCLICK   102   //���˫��  wParam:POINT����,lParam:0

/// @brief Ԫ������ƶ���Ϣ.
/// @code  BOOL CALLBACK EleMouseMove(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param flags ��μ�MSDN WM_MOUSEMOVE.
/// @param pPt   ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_MOUSEMOVE      103   //����ƶ�  wParam:��ʶ, lParam:POINT����

/// @brief Ԫ��������������Ϣ.
/// @code  BOOL CALLBACK EleLButtonDown(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param flags ��μ�MSDN WM_LBUTTONDOWN.
/// @param pPt   ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_LBUTTONDOWN    104   //wParam:��ʶ, lParam:POINT����

/// @brief Ԫ��������������Ϣ.
/// @code  BOOL CALLBACK EleLButtonUp(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param flags ��μ�MSDN WM_LBUTTONUP.
/// @param pPt   ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_LBUTTONUP      105   //wParam:��ʶ, lParam:POINT����

/// @brief Ԫ������Ҽ�������Ϣ.
/// @code  BOOL CALLBACK EleRButtonDown(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param flags ��μ�MSDN WM_RBUTTONDOWN.
/// @param pPt   ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_RBUTTONDOWN    106   //wParam:��ʶ, lParam:POINT����

/// @brief Ԫ������Ҽ�������Ϣ.
/// @code  BOOL CALLBACK EleRButtonUp(HELE hEle,UINT flags,POINT *pPt); @endcode
/// @param hEle Ԫ�ؾ��.
/// @param flags ��μ�MSDN WM_RBUTTONUP.
/// @param pPt   ��������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ��Ϣ���ݷ���TRUE.
#define  XM_RBUTTONUP      107   //wParam:��ʶ, lParam:POINT����

//�Ųʶ�ʱ��
// BOOL (CALLBACK *pFunEleTimerEx)(HELE hEle,UINT timerID,void* userData); //��ʱ����Ϣ XWM_TIMER
#define  XM_TIMER          108


///@}

//Ԫ���¼�
/// @addtogroup eleEvents
/// @{

/// @brief Ԫ�������¼�.
/// @code  void CALLBACK EventDestroy(HELE hEle); @endcode
/// @param hEle  Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_DESTROY        -1  //Ԫ������ �����¼�

/// @brief ��ťԪ�ص���¼�.
/// @code  BOOL CALLBACK EventBtnClick(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_BNCLICK        0   //��ť����¼�,û��ʱ���� wParam:0, lParam:0

/// @brief Ԫ�����ͣ���¼�.
/// @code  BOOL CALLBACK EventMouseStay(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_MOUSESTAY      1   //���ͣ��  wParam:0,lParam:0

/// @brief Ԫ������뿪�¼�.
/// @code  BOOL CALLBACK EventMouseLeave(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_MOUSELEAVE     2   //����뿪  wParam:0,lParam:0

/// @brief Ԫ�������ֹ����¼�.
/// @code  BOOL CALLBACK EventMouseWheel(HELE hEle,HELE hEventEle,UINT flags,POINT *pPt); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_MOUSEWHEEL     3   //������  wParam:��ʶ,lParam:POINT����

/// @brief Ԫ�ػ�ý����¼�.
/// @code  BOOL CALLBACK EventSetFocus(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_SETFOCUS       4   //��ý���  wParam:0,lParam:0

/// @brief Ԫ��ʧȥ�����¼�.
/// @code  BOOL CALLBACK EventKillFocus(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_KILLFOCUS      5   //ʧȥ����  wParam:0,lParam:0

/// @brief Ԫ�ذ����¼�.
/// @code  BOOL CALLBACK EventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
/// @note   wParam,lParam:��μ�MSDN WM_KEYDOWN. 
#define  XE_KEYDOWN        6   //wParam��lParam�������׼��Ϣ��ͬ

/// @brief ͨ��TranslateMessage����������ַ��¼�.
/// @code  BOOL CALLBACK EventChar(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
/// @note   wParam,lParam:��μ�MSDN WM_KEYDOWN. 
#define  XE_CHAR           7   //wParam��lParam�μ�MSDN

/// @brief ˮƽ������Ԫ�ع����¼�,����������.
/// @code  BOOL CALLBACK EventHScroll(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param pos         ��ǰ������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_HSCROLL        8   //ˮƽ�����������¼� wParam:������,lParam:0 (����������)

/// @brief ��ֱ������Ԫ�ع����¼�,����������.
/// @code  BOOL CALLBACK EventVScroll(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param pos         ��ǰ������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_VSCROLL        9   //��ֱ�����������¼� wParam:������,lParam:0 (����������)

/// @brief ������ͼԪ��ˮƽ�����¼�,������ͼ����.
/// @code  BOOL CALLBACK EventHScrollView(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param pos         ��ǰ������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_HSCROLLVIEW    10  //������ͼ �����¼� wParam:������,lParam:0 (������ͼ����,����������ͼ�ѹ������)

/// @brief ������ͼԪ�ش�ֱ�����¼�,������ͼ����.
/// @code  BOOL CALLBACK EventVScrollView(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param pos         ��ǰ������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_VSCROLLVIEW    11  //������ͼ �����¼� wParam:������,lParam:0 (������ͼ����,����������ͼ�ѹ������)

/// @brief Ԫ��������겶���¼�.
/// @code  BOOL CALLBACK EventSetCapture(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_SETCAPTURE     12  //������겶��  wParam:0,lParam:0

/// @brief Ԫ��ʧȥ��겶���¼�.
/// @code  BOOL CALLBACK EventKillCapture(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_KILLCAPTURE    13  //ʧȥ��겶��  wParam:0,lParam:0

/// @brief �����˵���ѡ���¼�.
/// @code  BOOL CALLBACK EventMenuSelect(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          �˵���id.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_MENUSELECT     14  //�˵���ѡ�� wParam:�˵�ID,lParam:0

/// @brief �����˵��˳��¼�.
/// @code  BOOL CALLBACK EventMenuExit(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_MENUEXIT       15  //�˵��˳�

/// @brief Ԫ�ش�С�ı��¼�.
/// @code  BOOL CALLBACK EventSize(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_SIZE           16  //Ԫ�ش�Сλ�øı�,wParam:0,lParam:0

/// @brief Ԫ������ı��¼�.
/// @code  BOOL CALLBACK EventSetFont(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_SETFONT        17  //Ԫ������ı��¼�,wParam:0,lParam:0

/// @brief Ԫ����ʾ�������¼�.
/// @code  BOOL CALLBACK EventShow(HELE hEle,HELE hEventEle,BOOL bShow); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param bShow       ���Ԫ����ʾTRUE,����FALSE.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_SHOW            18   //wParam:TRUE��FALSE, lParam:0


/// @brief �б�Ԫ��,��ѡ���¼�.
/// @code  BOOL CALLBACK EventListSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ��������,�����-1û��ѡ����.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LIST_SELECT          50   //�б���ѡ��, wParam:��index,�����-1û��ѡ����, lParam:0

/// @brief �б�Ԫ��,�б�ͷ�����¼�.
/// @code  BOOL CALLBACK EventListHeaderClick(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index          ������.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LIST_HEADER_CLICK    51   //�б�ͷ����,wParam:��index,   lParam:0

/// @brief �б�Ԫ��,�б�ͷ���ȸı��¼�.
/// @code  BOOL CALLBACK EventListHeaderChange(HELE hEle,HELE hEventEle,int index,int width); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       �б�ͷ������.
/// @param width       ����.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LIST_HEADER_CHANGE   52   //�б�ͷ���ȸı�,wParam:��index, lParam:����

/// @brief ��Ԫ��,��ѡ���¼�.
/// @code  BOOL CALLBACK EventTreeSelect(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          ѡ����id,�����-1û��ѡ����.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_TREE_SELECT          53   //����ѡ��,  wParam:ѡ����id,�����-1û��ѡ����, lParam:0

/// @brief ��Ԫ��,��չ���������¼�.
/// @code  BOOL CALLBACK EventTreeExpand(HELE hEle,HELE hEventEle,int id,BOOL bExpand); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          ����id.
/// @param bExpand     TRUEչ��,FALSE����.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_TREE_EXPAND          54   //����չ��������, wParam:��id; lParam:չ��TRUE,����FALSE

/// @brief ��Ͽ�Ԫ��,��Ͽ򵯳������б���ѡ���¼�.
/// @code  BOOL CALLBACK EventComboBoxSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ��������,���-1û��ѡ����
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_COMBOBOX_SELECT      55   //������Ͽ�ѡ���¼�,wParam:ѡ��������,���-1û��ѡ����, lParam:0

/// @brief ��Ͽ�Ԫ��,��Ͽ������б����¼�.
/// @code  BOOL CALLBACK EventComboBoxPopupList(HELE hEle,HELE hEventEle,HWINDOW hWindow,HELE hListBox); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param hWindow     �������ھ��.
/// @param hListBox    �����б���.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define XE_COMBOBOX_POPUP_LIST   56 //��Ͽ������б����¼�,wParam:�������ھ��, lParam:listBox���

/// @brief ��Ͽ�Ԫ��,��Ͽ򵯳������б��˳��¼�.
/// @code  BOOL CALLBACK EventComboBoxExitList(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define XE_COMBOBOX_EXIT_LIST   57 //��Ͽ򵯳������б�ر��¼�,wParam:0, lParam:0

/// @brief ����ҳԪ��,��ǩ��ѡ���¼�.
/// @code  BOOL CALLBACK EventPPageSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ���ǩ����,���-1û��ѡ���ǩ.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_PPAGE_SELECT         58   //����ҳ��ǩѡ��,wParam:��ǩ����,���-1û��ѡ���ǩ, lParam:0

/// @brief TabBarԪ��,��ǩ��ѡ���¼�.
/// @code  BOOL CALLBACK EventTabBarSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ���ǩ����,���-1û��ѡ���ǩ.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_TABBAR_SELECT         58   //TabBar��ǩѡ��,wParam:��ǩ����,���-1û��ѡ���ǩ, lParam:0


/// @brief ������Ԫ��,����λ�øı��¼�.
/// @code  BOOL CALLBACK EventSliderChange(HELE hEle,HELE hEventEle,int pos); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param pos         ���鵱ǰ����λ�õ�.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_SLIDER_CHANGE        59   //������λ�øı�,wParam:���鵱ǰ����λ�õ�, lParam:0

//wParam:TRUE���ڷ����ı�; FALSE:����δ�ı�,����ǰ����һ��, 
//lParam:�������ĵ�һ��ͼ,ͨ����������ں�(1-31)ѡ��,ΪTRUE; ��������ѡ����ͼ,����ѡ����ͼ����FALSE;
/// @brief ����Ԫ��,���ڸı��¼�.
/// @code  BOOL CALLBACK EventMonthChange(HELE hEle,HELE hEventEle,BOOL bChange,BOOL bDownDayNum); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param bChange     TRUE���ڷ����ı�; FALSE����δ�ı�,����ǰ����һ��.
/// @param bDownDayNum �������ĵ�һ��ͼ,ͨ����������ں�(1-31)ѡ��,ΪTRUE; ��������ѡ����ͼ,����ѡ����ͼ����FALSE;
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_MONTHCAL_CHANGE      60   //����Ԫ��,���ڸı��¼�,

/// @brief ���ڱ༭��Ԫ��,���ڸı��¼�,���ڸ�ʽΪ:��-��-��.
/// @code  BOOL CALLBACK EventDateTimeChange(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_DATETIME_CHANGE          61   //����Ԫ��,���ڸı��¼�,wParam:0,lParam:0

/// @brief ���ڱ༭��Ԫ��,��������ѡ�񴰿��¼�.
/// @code  BOOL CALLBACK EventDateTimePopupMonthCal(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_DATETIME_POPUP_MONTHCAL  62  //����Ԫ�� ��������ѡ�񴰿��¼�,wParam:0,lParam:0

/// @brief ���ڱ༭��Ԫ��,��������ѡ�񴰿��˳��¼�.
/// @code  BOOL CALLBACK EventDateTimeExitMonthCal(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_DATETIME_EXIT_MONTHCAL   63  //����Ԫ�� ��������ѡ�񴰿��˳��¼�,wParam:0,lParam:0

/// @brief �б��Ԫ��,��ѡ���¼�.
/// @code  BOOL CALLBACK EventListBoxSelect(HELE hEle,HELE hEventEle,int index); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ���������,�����-1û��ѡ���κ���.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LISTBOX_SELECT       64   //�б��Ԫ����ѡ��,wParam:ѡ��������,�����-1û��ѡ����; lParam:0

/// @brief ��������Ԫ��,��ѡ��ı��¼�.
/// @code  BOOL CALLBACK EventPGridSelChange(HELE hEle,HELE hEventEle,int prevID,int id); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param prevID      ��ǰѡ����id,�����-1û��ѡ����.
/// @param id          ��ǰѡ����id,�����-1û��ѡ����.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_PGRID_SELCHANGE      65   //�������� ��ѡ��ı�, wParam:��ǰѡ����id,�����-1û��ѡ����; lParam:��ǰѡ����id,�����-1û��ѡ����

/// @brief ��������Ԫ��,��ֵ�ı��¼�.
/// @code  BOOL CALLBACK EventPGridValueChange(HELE hEle,HELE hEventEle,int id); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          ��ID.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_PGRID_VALUECHANGE    66   //�������� ��ֵ�ı��¼�, wParam:ֵ�ı����id; lPara:0

/// @brief �б���ͼԪ��,��ѡ���¼�.
/// @code  BOOL CALLBACK EventListViewSelect(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          ��ID.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LISTVIEW_SELECT      67 //�б���ͼԪ��,��ѡ���¼�, wParam:������,���-1û��ѡ����, lParam:�����������-1û��ѡ����

/// @brief �б���ͼԪ��,��չ�������¼�
/// @code  BOOL CALLBACK EventListViewExpand(HELE hEle,HELE hEventEle,int groupIndex,BOOL bExpand); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          ��ID.
/// @param bExpand     TRUEչ��,FALSE����.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LISTVIEW_EXPAND      68 //�б���ͼԪ��,��չ�������¼�, wParam:������; lParam:չ��TRUE,����FALSE

/// @brief �б���ͼԪ��,�û��϶�������¼�
/// @code  BOOL CALLBACK EventListViewDragInsert(HELE hEle,HELE hEventEle,listView_dragInsert_ *pInfo); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param pInfo       ��Ϣ�ṹ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LISTVIEW_DRAG_INSERT 69  //wParam:listView_dragInsert_*; lParam:0

/// @brief ���������¼�
/// @code  BOOL CALLBACK EventPaneLock(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define XE_PANE_LOACK     70   //wParam:0; lParam:0

/// @brief ����ͣ������ͷ�¼�
/// @code  BOOL CALLBACK EventPaneDock(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_PANE_DOCK     80  //wParam:0; lParam:0

/// @brief ���񸡶��¼�
/// @code  BOOL CALLBACK EventPaneFloat(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_PANE_FLOAT    81  //wParam:0; lParam:0


/// @brief �༭�����ݸı��¼�
/// @code  BOOL CALLBACK EventEditChange(HELE hEle,HELE hEventEle); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_EDIT_CHANGE 82  //wParam:0; lParam:0

/// @brief ������Ͽ�Ԫ��,ѡ�������ڸı�.
/// @code  BOOL CALLBACK EventComboBoxSelecting(HELE hEle,HELE hEventEle,int index,BOOL *pBOOL); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ���������,�����-1û��ѡ���κ���.
/// @param pBOOL       �Ƿ���ֹ�ı�,TRUE��ֹ.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_COMBOBOX_SELECT_ING  83  //wParam:index; lParam:pBOOL


/// @brief �б��Ԫ��,��ѡ�����ڸı�.
/// @code  BOOL CALLBACK EventListBoxSelecting(HELE hEle,HELE hEventEle,int index,BOOL *pBOOL); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param index       ѡ���������,�����-1û��ѡ���κ���.
/// @param pBOOL       �Ƿ���ֹ�ı�,TRUE��ֹ.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_LISTBOX_SELECT_ING       84   //�б��Ԫ����ѡ��,wParam:ѡ��������,�����-1û��ѡ����; lParam:pBOOL


/// @brief ��Ԫ��,��ѡ�����ڸı�.
/// @code  BOOL CALLBACK EventTreeSelecting(HELE hEle,HELE hEventEle,int id,BOOL *pBOOL); @endcode
/// @param hEle        ��ǰ�����¼���Ԫ�ؾ��.
/// @param hEventEle   �����¼���Ԫ�ؾ��.
/// @param id          ѡ����id,�����-1û��ѡ����.
/// @param pBOOL       �Ƿ���ֹ�ı�,TRUE��ֹ.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  XE_TREE_SELECT_ING         85   //����ѡ��,  wParam:ѡ����id,�����-1û��ѡ����, lParam:pBOOL

///@}


#ifdef _DEBUG
#define XTRACE   xtrace
#define XTRACEW  xtracew
#define XERROR   XTRACE 
#define XERRORW  XTRACEW
#else
#define XTRACE
#define XTRACEW
#define XERROR 
#define XERRORW
#endif

#ifndef  GET_X_LPARAM
#define  GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#endif
#ifndef  GET_Y_LPARAM
#define  GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
#endif


///////////////////IE begin///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//IE�¼�:
///@defgroup IE_Event IE�¼�
///@details  ע��IE�¼�,DWebBrowserEvents2�ӿ��¼�,ע��API: XWeb_RegEvent().
///@ingroup  msgAndEvents
///@{

/// @brief �ڵ�������֮ǰ.
/// @code  BOOL CALLBACK IE_BeforeNavigate2(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl,in_ int Flags,in_ wchar_t *pTargetFrameName,in_ wchar_t *pPostData,in_ wchar_t *pHeaders,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @param hWebBrowser ������ؼ����.
/// @param pDisp   ��μ�MSDN.
/// @param pUrl    ��μ�MSDN.
/// @param Flags   ��μ�MSDN.
/// @param pTargetFrameName ��μ�MSDN.
/// @param pPostData ��μ�MSDN.
/// @param pHeaders ��μ�MSDN.
/// @param bCancel TRUEȡ��������������FALSE������е���������
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_BEFORENAVIGATE2     DISPID_BEFORENAVIGATE2    //BeforeNavigate2

/// @brief �������,�ͻ������ڴ�Сת�����������ڴ�С.
/// @code  BOOL CALLBACK IE_ClientToHostWindow(HXCGUI hWebBrowser,in_out_ long *pCx,in_out_ long *pCy); @endcode
/// @param hWebBrowser ������ؼ����.
/// @param pCx ���պ�ָ���Ŀͻ��˴��ڵĿ��.
/// @param pCy ���պ�ָ���Ŀͻ��˴��ڵĸ߶�.
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_CLIENTTOHOSTWINDOW  DISPID_CLIENTTOHOSTWINDOW //ClientToHostWindow

/// @brief ����״̬���������.
/// @code BOOL CALLBACK IE_CommandStateChange(HXCGUI hWebBrowser,in_ long command,in_ VARIANT_BOOL enable); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_COMMANDSTATECHANGE  DISPID_COMMANDSTATECHANGE //CommandStateChange  

/// @brief һ���ĵ���ȫ���غͳ�ʼ��.
/// @code BOOL CALLBACK IE_DocumentComplete(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_DOCUMENTCOMPLETE    DISPID_DOCUMENTCOMPLETE   //DocumentComplete

/// @brief ��ʼ��������.
/// @code  BOOL CALLBACK IE_DownloadBegin(HXCGUI hWebBrowser); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_DOWNLOADBEGIN       DISPID_DOWNLOADBEGIN      //DownloadBegin 

/// @brief �����������ʱ��ֹͣ��ʧ��.
/// @code BOOL CALLBACK IE_DownloadComplete(HXCGUI hWebBrowser); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_DOWNLOADCOMPLETE    DISPID_DOWNLOADCOMPLETE   //DownloadComplete 

/// @brief �����ļ��Ǽ�������.
/// @code BOOL CALLBACK IE_FileDownload(HXCGUI hWebBrowser,in_ VARIANT_BOOL ActiveDocument,in_out_ VARIANT_BOOL *Cancel); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_FILEDOWNLOAD        DISPID_FILEDOWNLOAD       //FileDownload

/// @brief ������һ������,һ������Ԫ�ػ�һ�����Ԫ�����.
/// @code BOOL CALLBACK IE_NavigateComplete2(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_NAVIGATECOMPLETE2   DISPID_NAVIGATECOMPLETE2 //NavigateComplete2

/// @brief �ڵ��������з�������ʱ����.
/// @code BOOL CALLBACK IE_NavigateError(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl,in_ wchar_t *pTargetFrameName,in_ int statusCode,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_NAVIGATEERROR       DISPID_NAVIGATEERROR     //NavigateError

//       IE_NEWPROCESS          DISPID_NEWPROCESS        //NewProcess �Ҳ���

/// @brief ����һ���µĴ���ʱ����.
/// @code BOOL CALLBACK IE_NewWindow2(HXCGUI hWebBrowser,in_out_ IDispatch **pDisp,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_NEWWINDOW2          DISPID_NEWWINDOW2        //NewWindow2

/// @brief ����һ���´���ʱ����.
/// @code BOOL (CALLBACK *pFunIE_NewWindow3)(HXCGUI hWebBrowser,in_out_ IDispatch **pDisp,in_out_ VARIANT_BOOL *bCancel,in_ DWORD dwFlags,in_ wchar_t *pUrlContext,in_ wchar_t *pUrl); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_NEWWINDOW3          DISPID_NEWWINDOW3       //NewWindow3

/// @brief IWebBrowser2::FullScreen���Ա��ı�ʱ����.
/// @code BOOL CALLBACK IE_OnFullScreen(HXCGUI hWebBrowser,in_ VARIANT_BOOL bFullScreen); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONFULLSCREEN        DISPID_ONFULLSCREEN     //OnFullScreen

/// @brief IWebBrowser2::MenuBar���Ա��ı�ʱ����.
/// @code BOOL CALLBACK IE_OnMenuBar(HXCGUI hWebBrowser,in_ VARIANT_BOOL bMenuBar); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONMENUBAR           DISPID_ONMENUBAR        //OnMenuBar

/// @brief Internet Explorer��Ӧ�ó����˳�֮ǰ����.
/// @code BOOL CALLBACK IE_OnQuit(HXCGUI hWebBrowser); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONQUIT              DISPID_ONQUIT           //OnQuit

/// @brief IWebBrowser2::StatusBar���Ա��ı�ʱ����.
/// @code BOOL CALLBACK IE_OnStatusBar(HXCGUI hWebBrowser,in_ VARIANT_BOOL bStatusBar); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONSTATUSBAR         DISPID_ONSTATUSBAR      //OnStatusBar

/// @brief IWebBrowser2::TheaterMode���Ա��ı�ʱ����.
/// @code BOOL CALLBACK IE_OnTheaterMode(HXCGUI hWebBrowser,in_ VARIANT_BOOL bTheaterMode); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONTHEATERMODE       DISPID_ONTHEATERMODE     //OnTheaterMode

/// @brief IWebBrowser2::ToolBar���Ա��ı�ʱ����.
/// @code BOOL CALLBACK IE_OnToolBar(HXCGUI hWebBrowser,in_ VARIANT_BOOL bToolBar); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONTOOLBAR           DISPID_ONTOOLBAR         //OnToolBar

/// @brief IWebBrowser2::Visible���Ա��ı�ʱ����.
/// @code BOOL CALLBACK IE_OnVisible(HXCGUI hWebBrowser,in_ VARIANT_BOOL bVisible); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_ONVISIBLE           DISPID_ONVISIBLE         //OnVisible

/// @brief ��ӡģ��ʵ����ʱ����.
/// @code BOOL CALLBACK IE_PrintTemplateInstantiation(HXCGUI hWebBrowser,in_ IDispatch *pDisp); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_PRINTTEMPLATEINSTANTIATION DISPID_PRINTTEMPLATEINSTANTIATION //PrintTemplateInstantiation

/// @brief ��ӡģ�屻����ʱ����.
/// @code BOOL CALLBACK IE_PrintTemplateTeardown(HXCGUI hWebBrowser,in_ IDispatch *pDisp); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_PRINTTEMPLATETEARDOWN  DISPID_PRINTTEMPLATETEARDOWN  // PrintTemplateTeardown

/// @brief ��һ����Ӱ���˽���¼�,���û������Ѿ���Ӱ���Զ��URLʱ����.
/// @code  BOOL CALLBACK IE_PrivacyImpactedStateChange(HXCGUI hWebBrowser,in_ VARIANT_BOOL bPrivacyImpacted); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_PRIVACYIMPACTEDSTATECHANGE  DISPID_PRIVACYIMPACTEDSTATECHANGE //PrivacyImpactedStateChange

/// @brief ���¶���ʱ���������ز����Ľ���.
/// @code  BOOL CALLBACK IE_ProgressChangee(HXCGUI hWebBrowser,in_ long Progress,in_ long ProgressMax); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_PROGRESSCHANGE       DISPID_PROGRESSCHANGE   //ProgressChange

/// @brief IWebBrowser2::PutProperty����ķ����ı�����ֵʱ����.
/// @code  BOOL CALLBACK IE_PropertyChange(HXCGUI hWebBrowser,in_ wchar_t *pProperty); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_PROPERTYCHANGE       DISPID_PROPERTYCHANGE   //PropertyChange

//       IE_REDIRECTXDOMAINBLOCKED  DISPID_REDIRECTXDOMAINBLOCKED // RedirectXDomainBlocked �Ҳ���

/// @brief ����������ǰ��ҳ��ð���˷���΢��Ľ��Ⱥ�״̬��.
/// @code  BOOL CALLBACK IE_SetPhishingFilterStatus(HXCGUI hWebBrowser,in_ long phishingFilterStatus); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_SETPHISHINGFILTERSTATUS DISPID_SETPHISHINGFILTERSTATUS //SetPhishingFilterStatus

/// @brief �ڼ��ܼ���ı仯ʱ����.
/// @code  BOOL CALLBACK IE_SetSecureLockIcon(HXCGUI hWebBrowser,in_ signed int SecureLockIcon); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_SETSECURELOCKICON    DISPID_SETSECURELOCKICON  //SetSecureLockIcon

/// @brief �ı�����״̬���ı�ʱ����.
/// @code  BOOL CALLBACK IE_StatusTextChange(HXCGUI hWebBrowser,in_ wchar_t *pText); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_STATUSTEXTCHANGE     DISPID_STATUSTEXTCHANGE    //StatusTextChange

//       IE_THIRDPARTYURLBLOCKED DISPID_THIRDPARTYURLBLOCKED //ThirdPartyUrlBlocked �Ҳ���

/// @brief ������ĵ��ı����Ϊ���û�ı�ʱ����.
/// @code  BOOL CALLBACK IE_TitleChange(HXCGUI hWebBrowser,in_ wchar_t *pText); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_TITLECHANGE          DISPID_TITLECHANGE        //TitleChange

//UpdatePageStatus IEû��ʵ��

/// @brief �ö���Ĵ��ڱ��رսű�ʱ����.
/// @code  BOOL CALLBACK IE_WindowClosing(HXCGUI hWebBrowser,in_ VARIANT_BOOL IsChildWindow,in_out_ VARIANT_BOOL *bCancel); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWCLOSING       DISPID_WINDOWCLOSING      //WindowClosing

/// @brief ������ı���߶ȵĴ���.
/// @code  BOOL CALLBACK IE_WindowSetHeight(HXCGUI hWebBrowser,in_ long height); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWSETHEIGHT     DISPID_WINDOWSETHEIGHT    //WindowSetHeight

/// @brief ������ı������λ��ʱ����.
/// @code  BOOL CALLBACK IE_WindowSetLeft(HXCGUI hWebBrowser,in_ long left); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWSETLEFT       DISPID_WINDOWSETLEFT      //WindowSetLeft

/// @brief ����ָʾ���������Ƿ�Ӧ�������������.
/// @code  BOOL CALLBACK IE_WindowSetResizable(HXCGUI hWebBrowser,in_ VARIANT_BOOL bResizable); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWSETRESIZABLE  DISPID_WINDOWSETRESIZABLE   //WindowSetResizable

/// @brief ������ı��䶥��λ�õĴ���.
/// @code  BOOL CALLBACK IE_WindowSetTop(HXCGUI hWebBrowser,in_ long top); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWSETTOP        DISPID_WINDOWSETTOP    //WindowSetTop

/// @brief ������ı����ȵĴ���.
/// @code  BOOL CALLBACK IE_WindowSetWidth(HXCGUI hWebBrowser,in_ long width); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWSETWIDTH      DISPID_WINDOWSETWIDTH   //WindowSetWidth

/// @brief  ���������ݵĿɼ���״̬������������ڻ�ѡ�������ʱ����.
/// @code   BOOL CALLBACK IE_WindowStateChanged(HXCGUI hWebBrowser,in_ DWORD dwFlags,in_ DWORD dwValidFlagsMask); @endcode
/// @return Ĭ�Ϸ���FALSE,�����ֹ�¼����ݷ���TRUE.
#define  IE_WINDOWSTATECHANGED  DISPID_WINDOWSTATECHANGED  //WindowStateChanged

///@}

//����IE�ⲿ��������
typedef BOOL(CALLBACK *pFunIE_External0)(HXCGUI hWebBrowser, HSTRING hResultVal);
typedef BOOL(CALLBACK *pFunIE_External1)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1);
typedef BOOL(CALLBACK *pFunIE_External2)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2);
typedef BOOL(CALLBACK *pFunIE_External3)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3);
typedef BOOL(CALLBACK *pFunIE_External4)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4);
typedef BOOL(CALLBACK *pFunIE_External5)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5);
typedef BOOL(CALLBACK *pFunIE_External6)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5, wchar_t *pParam6);
typedef BOOL(CALLBACK *pFunIE_External7)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5, wchar_t *pParam6, wchar_t *pParam7);
typedef BOOL(CALLBACK *pFunIE_External8)(HXCGUI hWebBrowser, HSTRING hResultVal, wchar_t *pParam1, wchar_t *pParam2, wchar_t *pParam3, wchar_t *pParam4, wchar_t *pParam5, wchar_t *pParam6, wchar_t *pParam7, wchar_t *pParam8);


//����IE�¼��ص���������
typedef BOOL(CALLBACK *pFunIE_BeforeNavigate2)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl, in_ int Flags, in_ wchar_t *pTargetFrameName, in_ wchar_t *pPostData, in_ wchar_t *pHeaders, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_ClientToHostWindow)(HXCGUI hWebBrowser, in_out_ long *pCx, in_out_ long *pCy);
typedef BOOL(CALLBACK *pFunIE_CommandStateChange)(HXCGUI hWebBrowser, in_ long command, in_ VARIANT_BOOL enable);
typedef BOOL(CALLBACK *pFunIE_DocumentComplete)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl);
typedef BOOL(CALLBACK *pFunIE_DownloadBegin)(HXCGUI hWebBrowser);
typedef BOOL(CALLBACK *pFunIE_DownloadComplete)(HXCGUI hWebBrowser);
typedef BOOL(CALLBACK *pFunIE_FileDownload)(HXCGUI hWebBrowser, in_ VARIANT_BOOL ActiveDocument, in_out_ VARIANT_BOOL *Cancel);
typedef BOOL(CALLBACK *pFunIE_NavigateComplete2)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl);
typedef BOOL(CALLBACK *pFunIE_NavigateError)(HXCGUI hWebBrowser, in_ IDispatch *pDisp, in_ wchar_t *pUrl, in_ wchar_t *pTargetFrameName, in_ int statusCode, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_NewWindow2)(HXCGUI hWebBrowser, in_out_ IDispatch **pDisp, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_NewWindow3)(HXCGUI hWebBrowser, in_out_ IDispatch **pDisp, in_out_ VARIANT_BOOL *bCancel, in_ DWORD dwFlags, in_ wchar_t *pUrlContext, in_ wchar_t *pUrl);
typedef BOOL(CALLBACK *pFunIE_OnFullScreen)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bFullScreen);
typedef BOOL(CALLBACK *pFunIE_OnMenuBar)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bMenuBar);
typedef BOOL(CALLBACK *pFunIE_OnQuit)(HXCGUI hWebBrowser);
typedef BOOL(CALLBACK *pFunIE_OnStatusBar)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bStatusBar);
typedef BOOL(CALLBACK *pFunIE_OnTheaterMode)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bTheaterMode);
typedef BOOL(CALLBACK *pFunIE_OnToolBar)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bToolBar);
typedef BOOL(CALLBACK *pFunIE_OnVisible)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bVisible);
typedef BOOL(CALLBACK *pFunIE_PrintTemplateInstantiation)(HXCGUI hWebBrowser, in_ IDispatch *pDisp);
typedef BOOL(CALLBACK *pFunIE_PrintTemplateTeardown)(HXCGUI hWebBrowser, in_ IDispatch *pDisp);
typedef BOOL(CALLBACK *pFunIE_PrivacyImpactedStateChange)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bPrivacyImpacted);
typedef BOOL(CALLBACK *pFunIE_ProgressChangee)(HXCGUI hWebBrowser, in_ long Progress, in_ long ProgressMax);
typedef BOOL(CALLBACK *pFunIE_PropertyChange)(HXCGUI hWebBrowser, in_ wchar_t *pProperty);
typedef BOOL(CALLBACK *pFunIE_SetPhishingFilterStatus)(HXCGUI hWebBrowser, in_ long phishingFilterStatus);
typedef BOOL(CALLBACK *pFunIE_SetSecureLockIcon)(HXCGUI hWebBrowser, in_ signed int SecureLockIcon);
typedef BOOL(CALLBACK *pFunIE_StatusTextChange)(HXCGUI hWebBrowser, in_ wchar_t *pText);
typedef BOOL(CALLBACK *pFunIE_TitleChange)(HXCGUI hWebBrowser, in_ wchar_t *pText);
typedef BOOL(CALLBACK *pFunIE_WindowClosing)(HXCGUI hWebBrowser, in_ VARIANT_BOOL IsChildWindow, in_out_ VARIANT_BOOL *bCancel);
typedef BOOL(CALLBACK *pFunIE_WindowSetHeight)(HXCGUI hWebBrowser, in_ long height);
typedef BOOL(CALLBACK *pFunIE_WindowSetLeft)(HXCGUI hWebBrowser, in_ long left);
typedef BOOL(CALLBACK *pFunIE_WindowSetResizable)(HXCGUI hWebBrowser, in_ VARIANT_BOOL bResizable);
typedef BOOL(CALLBACK *pFunIE_WindowSetTop)(HXCGUI hWebBrowser, in_ long top);
typedef BOOL(CALLBACK *pFunIE_WindowSetWidth)(HXCGUI hWebBrowser, in_ long width);
typedef BOOL(CALLBACK *pFunIE_WindowStateChanged)(HXCGUI hWebBrowser, in_ DWORD dwFlags, in_ DWORD dwValidFlagsMask);

////////////////IE end///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//������Ϣ�������
typedef BOOL(CALLBACK *pFunWndMsgProc)(HWINDOW hWindow, UINT message, WPARAM wParam, LPARAM lParam);
//Ԫ����Ϣ�������
typedef BOOL(CALLBACK *pFunEleMsgProc)(HELE hEle, UINT eleMessage, WPARAM wParam, LPARAM lParam);
//Ԫ���¼��������
typedef BOOL(CALLBACK *pFunEleEventProc)(HELE hEle, int type, WPARAM wParam, LPARAM lParam);
//���ƹ�����ͼ
typedef BOOL(CALLBACK *pFunDrawScrollView)(HELE hEle, HDRAW hDraw);



//////////////////////////////////////////////////////////
//��Ԫ���Ի�
///@addtogroup groupTree
///@{

///�б���Ԫ��,���Ի�ṹ
struct tree_drewItem_
{
	HDRAW     hDraw;    ///<ͼ�λ��ƾ��
	int      id;        ///<��ID
	int      imageId;   ///<ͼ��ID
	int      state;     ///<״̬
	BOOL     bExpand;   ///<�Ƿ�չ�����
	wchar_t  *pText;    ///<�ı�����

	RECT  rcButton; ///<��ť����
	RECT  rcImage;  ///<ͼƬ����
	RECT  rcText;   ///<�ı�����
};

///@}


///@defgroup groupList_draw �б�Ԫ���Ի�
///@ingroup macroDefine
///@{

///�б�Ԫ��,���Ի�ṹ
struct list_drawItem_
{
	HDRAW hDraw;     ///<ͼ�λ��ƾ��
	int   index;     ///<������
	int   subIndex;  ///<��������
	int   imageId;   ///<ͼ��ID
	int   state;     ///<״̬
	RECT  rect;      ///<������
	RECT  rcCheck;   ///<��ѡ������,��subIndex����Ϊ0����Ч
	wchar_t *pText;  ///<�ı�����
};

///�б�Ԫ��,�б�ͷ���Ի�ṹ
struct listHeader_drawItem_
{
	HDRAW hDraw;    ///<ͼ�λ��ƾ��
	int   index;    ///<������
	int   imageId;  ///<ͼ��ID
	int   state;    ///<״̬ ���ֵΪ-1,��ôΪ���Ʊ���
	RECT  rect;     ///<������
	wchar_t *pText; ///<�ı�����
};

///@}



///@defgroup groupListBox_draw �б��Ԫ���Ի�
///@ingroup macroDefine
///@{

///�б��Ԫ��,���Ի�ṹ
struct listBox_drawItem_
{
	HDRAW hDraw;    ///<ͼ�λ��ƾ��
	int   index;    ///<����
	int   imageId;  ///<ͼ��ID
	int   state;    ///<״̬
	RECT  rcItem;   ///<������
	RECT  rcCheck;  ///<��ѡ������,����ѡ������ʱ��Ч
	wchar_t *pText; ///<�ı�����
};
///@}


///@defgroup itemBindEle ���Ԫ����Ϣ�ṹ
///@ingroup macroDefine
///@{

///���Ԫ����Ϣ�ṹ.
struct itemBindEle_
{
	HELE hEle;   ///<�󶨵�Ԫ��,����󶨵��б�Ԫ��,��ô���ĸ�Ӧ��Ϊ�б�Ԫ��.
	int left;    ///<�������.
	int top;     ///<�������.
	int width;   ///<���.
	int height;  ///<�߶�.
};

///@}

///@defgroup groupListView_draw �б���ͼԪ���Ի�
///@ingroup macroDefine
///@{

///�б���ͼԪ��,���Ի�ṹ
struct listView_drawItem_	//������
{
	HDRAW     hDraw;   ///<ͼ�λ��ƾ��
	int       groupIndex; //������
	int       itemIndex;  //������
	int       imageID; ///<ͼƬID
	wchar_t   *pText;  ///<�ı�
	int       state;   ///<״̬,�Ƿ�ѡ��

	HIMAGE hImage_stay;    //��ͣ��ͼƬ
	HIMAGE hImage_select;  //��ѡ��ͼ��

	RECT  rcIcon; ///<ͼ������
	RECT  rcIconDraw; ///<ͼ��ʵ�ʻ�������
	RECT  rcText; ///<��������
	RECT  rect;   ///<��������,�����߿�

	void* userData;  ///<�û�����
};

///�б���ͼԪ��,���Ի�ṹ
struct listView_drawGroup_ //������
{
	HDRAW hDraw;        ///<ͼ�λ��ƾ��
	BOOL  bExpand;      ///<�Ƿ�չ��

	wchar_t  *pText;    ///<�ı�
	RECT     rcText;    ///<�ı�����
	RECT     rcButton;  ///<չ����ť����
	RECT     rect;      ///<����������

	void* userData;       ///<�û�����
};

///�б���ͼԪ��,�û��϶������
struct listView_dragInsert_
{
	int groupIndex;   ///<�϶��� - ������
	int itemIndex;    ///<�϶��� - ������

	int groupIndex_insert; ///<����λ�� - ������
	int itemIndex_insert;  ///<����λ�� - ������

	int groupIndex_new; //�����λ�� ������
	int itemIndex_new; //�����λ�� ������
};

///@}






///@defgroup groupMenu_draw �˵��Ի�
///@ingroup macroDefine
///@{

///�˵����Ի�ṹ
struct menu_drawItem_
{
	HWINDOW    hWindow;     ///<��ǰ�����˵���Ĵ��ھ��
	HDRAW      hDraw;       ///<ͼ�λ��ƾ��
	int        id;          ///<ID
	int        state;	    ///<״̬
	RECT       rcItem;      ///<����
	HIMAGE     hImage;      ///<ͼƬ
	wchar_t    *pText;      ///<�ı�
};

///�˵����ڱ����Ի�ṹ
struct menu_drawBG_
{
	HWINDOW    hWindow;       ///<��ǰ�����˵���Ĵ��ھ��
	HDRAW      hDraw;         ///<ͼ�λ��ƾ��
	int        parentItemId;  ///<�Ӳ˵���Ӧ�ĸ���˵�ID��-1û�и���
	HIMAGE     hImage;        ///<ͼƬ
};

///@}

//�б����Ի�
typedef void (CALLBACK *pFunList_DrawItem)(HELE hEle, list_drawItem_ *pDrawItem);
//�б�ͷ���Ի�
typedef void (CALLBACK *pFunListHeader_DrawItem)(HELE hEle, listHeader_drawItem_ *pDrawItem);

//�б�����Ի�
typedef void (CALLBACK *pFunListBox_DrawItem)(HELE hEle, listBox_drawItem_ *pDrawItem);

//�����Ի�
typedef void (CALLBACK *pFunTree_DrawItem)(HELE hEle, tree_drewItem_ *pDrawItem);

//�б���ͼ���Ի�
typedef void (CALLBACK *pFunListView_DrawItem)(HELE hEle, listView_drawItem_ *pDrawItem);

//�б���ͼ���Ի�
typedef void (CALLBACK *pFunListView_DrawGroup)(HELE hEle, listView_drawGroup_ *pDrawGroup);

//�˵����Ի�
typedef void (CALLBACK *pFunMenu_DrawItem)(HMENUX hMenu, menu_drawItem_ *pDrawItem);

//�˵������Ի�
typedef void (CALLBACK *pFunMenu_DrawBG)(HMENUX hMenu, menu_drawBG_ *pDrawBG);

//�˵������UI
typedef void (CALLBACK *pFunMenu_UpdateUI)(HMENUX hMenu, int id);

//////////////////////////////////////////////////////////////////////////////////
//���沿��ͨ������Ҫ�Ķ�//////////////////////////////////////////////////////////
#define XCGUI_PLUS  // C++��֧�ְ� , C plus plus

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
struct eventOrMsg_  //Ԫ����Ϣ�¼��ص���Ϣ,C++��֧��
{
	union
	{
		HELE hEle;
		HWINDOW hWindow;
		HMENUX  hMenu;
	};
	union
	{
		HELE hEventEle;
		int  xint;
	};
	WPARAM wParam;
	LPARAM lParam;
	void   *pClass_fun;  //���Ա����ָ��
};

//��ʽ xc_fun_��������_�������ͱ�...
//b:BOOL, e:HELE, w:HWINDOW, x:HXCGUI, hwnd:HWND, hdraw:HDRAW, i:int, p:void*, pt:POINT*, size:SIZE*, v:void
//pb:BOOL*;
//menu:HMENUX.
enum xcgui_fun_type //��������
{
	xc_fun_b_e_e,
	xc_fun_b_e_e_b,
	xc_fun_b_e_e_b_b,
	xc_fun_b_e_e_w_e,
	xc_fun_b_e_e_pb,
	xc_fun_b_e_e_i,
	xc_fun_b_e_e_i_pt,
	xc_fun_b_e_e_i_b,
	xc_fun_b_e_e_i_pb,
	xc_fun_b_e_e_i_i,
	xc_fun_b_e_i_i,
	xc_fun_b_e_i_i_i,
	xc_fun_b_e_e_listView_dragInsert,

	xc_fun_v_e, //Ԫ������
	xc_fun_b_e_pt,
	xc_fun_b_e_hdraw,
	xc_fun_b_e_i_pt,
	xc_fun_b_w,
	xc_fun_b_w_e,
	xc_fun_b_w_pt,
	xc_fun_b_w_i,
	xc_fun_b_w_i_pt,
	xc_fun_b_w_i_size,
	xc_fun_b_w_i_i,
	xc_fun_b_w_hdraw,
	xc_fun_b_w_hwnd,

	xc_fun_v_e_list_item,
	xc_fun_v_e_list_header,
	xc_fun_v_e_tree,
	xc_fun_v_e_listBox,
	xc_fun_v_e_listView_item,
	xc_fun_v_e_listView_group,
	xc_fun_v_x_menu_item,
	xc_fun_v_x_menu_bg,
	xc_fun_v_x_menu_i,
};

//�¼��ص�����
typedef BOOL(CALLBACK *pFunClassEventMsg)(eventOrMsg_ *pEvent, xcgui_fun_type funType);

//#endif //XCGUI_PLUS


//#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��

//{
//����API�ڲ�ʹ��
extern XC_API void* WINAPI XC_Malloc(int size);
extern XC_API void WINAPI XEle_RegisterMessageEx(HELE hEle, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
extern XC_API void WINAPI XEle_RegisterEventEx(HELE hEle, int type, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
extern XC_API void WINAPI XEle_RegisterMsgProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);    //ע��Ԫ����Ϣ�������
extern XC_API void WINAPI XEle_RegisterEventProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //ע���¼����ع��˺���

extern XC_API void WINAPI XWnd_RegisterMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //ע����Ϣ�ص�����
extern XC_API void WINAPI XWnd_RegisterNCMessageEx(HWINDOW hWindow, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //ע��ǿͻ�����Ϣ
extern XC_API void WINAPI XWnd_RegisterMsgProcEx(HWINDOW hWindow, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);	//ע�ᴰ����Ϣ�������

extern XC_API void WINAPI XSView_SetDrawScrollViewEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);
extern XC_API void WINAPI XList_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի��б���
extern XC_API void WINAPI XList_SetUserDrawItemHeaderEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի��б�ͷ��
extern XC_API void WINAPI XTree_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի���
extern XC_API void WINAPI XListBox_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի��б����
extern XC_API void WINAPI XListView_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի���
extern XC_API void WINAPI XListView_SetUserDrawGroupEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի���
extern XC_API void WINAPI XMenu_SetUserDrawItemEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի�˵���
extern XC_API void WINAPI XMenu_SetUserDrawBGEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի�˱���
extern XC_API void WINAPI XMenu_SetUserUpdateUIEx(HMENUX hMenu, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);

//}

class CXEventMsg
{
public:
	virtual void CXEventMsg__(void) {} //�˺�������ɾ��

//ע��Ԫ���¼�
#define XCGUI_RegEleEvent(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_event)

//ע��Ԫ����Ϣ
#define XCGUI_RegEleMessage(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_msg)

//ע��Ԫ����Ϣ�������
#define XCGUI_RegEleMsgProc(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_msg_proc)

//ע��Ԫ���¼��������
#define XCGUI_RegEleEventProc(hEle,type,memberFunction) \
		RegisterAll(hEle,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_event_proc)

//ע�ᴰ����Ϣ
#define XCGUI_RegWndMessage(hWindow,type,memberFunction) \
		RegisterAll(hWindow,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),wnd_msg)

//ע�ᴰ���߼��ǿͻ�����Ϣ
#define XCGUI_RegWndNCMessage(hWindow,type,memberFunction) \
		RegisterAll(hWindow,type,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),wnd_msg_nc)

//ע�ᴰ����Ϣ�������
#define XCGUI_RegWndMsgProc(hWindow,memberFunction) \
		RegisterAll(hWindow,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),wnd_msg_proc)

//ע�������ͼ����
#define XCGUI_SView_SetDrawScrollView(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_scrollView_draw)

//ע���б������
#define XCGUI_List_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_list_drawItem)

//�б�ͷ�����
#define XCGUI_List_SetUserDrawItemHeader(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_list_drawItemHeader)

//�������
#define XCGUI_Tree_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_tree_drawItem)

//�б�������
#define XCGUI_ListBox_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_listBox_drawItem)

//�б���ͼ�����
#define XCGUI_ListView_SetUserDrawItem(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_listView_drawItem)

//�б���ͼ�����
#define XCGUI_ListView_SetUserDrawGroup(hEle,memberFunction) \
		RegisterAll(hEle,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_listView_drawGroup)

//�˵����Ի�
#define XCGUI_Menu_SetUserDrawItem(hMenu,memberFunction) \
	RegisterAll(hMenu,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_menu_drawItem)

//�˵������Ի�
#define XCGUI_Menu_SetUserDrawBG(hMenu,memberFunction) \
	RegisterAll(hMenu,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_menu_drawBG)

//���²˵���
#define XCGUI_Menu_SetUserUpdateUI(hMenu,memberFunction) \
	RegisterAll(hMenu,0,reinterpret_cast<void (CXEventMsg::*)(void)>(memberFunction),ele_menu_updateUI)

	union xcgui_functions //����ָ��
	{
		void (CXEventMsg::*fun_v_v)(void);
		BOOL(CXEventMsg::*fun_b_e_e_i_i)(HELE, HELE, int, int);
		BOOL(CXEventMsg::*fun_b_e_e_i)(HELE, HELE, int);
		BOOL(CXEventMsg::*fun_b_e_e)(HELE, HELE);
		BOOL(CXEventMsg::*fun_b_e_e_pb)(HELE, HELE, BOOL*);
		BOOL(CXEventMsg::*fun_b_e_e_i_pb)(HELE, HELE, int, BOOL*);
		BOOL(CXEventMsg::*fun_b_e_e_b)(HELE, HELE, BOOL);

		BOOL(CXEventMsg::*fun_b_e_e_i_p)(HELE, HELE, int, POINT*);
		BOOL(CXEventMsg::*fun_b_e_e_i_b)(HELE, HELE, int, BOOL);
		BOOL(CXEventMsg::*fun_b_e_e_b_b)(HELE, HELE, BOOL, BOOL);
		BOOL(CXEventMsg::*fun_b_e_i_i_i)(HELE, int, int, int);
		BOOL(CXEventMsg::*fun_b_e_i_i)(HELE, int, int);
		BOOL(CXEventMsg::*fun_b_e_e_w_e)(HELE, HELE, HWINDOW, HELE);
		BOOL(CXEventMsg::*fun_b_e_e_listViewDragInsert)(HELE, HELE, listView_dragInsert_*);

		void (CXEventMsg::*fun_v_e)(HELE);

		BOOL(CXEventMsg::*fun_b_e_i_p)(HELE, int, POINT*);
		BOOL(CXEventMsg::*fun_b_e_p)(HELE, POINT*);
		BOOL(CXEventMsg::*fun_b_e_hdraw)(HELE, HDRAW);

		BOOL(CXEventMsg::*fun_b_w_hdraw)(HWINDOW, HDRAW);
		BOOL(CXEventMsg::*fun_b_w)(HWINDOW);
		BOOL(CXEventMsg::*fun_b_w_i_p)(HWINDOW, int, POINT*);
		BOOL(CXEventMsg::*fun_b_w_i_size)(HWINDOW, int, SIZE*);
		BOOL(CXEventMsg::*fun_b_w_i_i)(HWINDOW, int, int);
		BOOL(CXEventMsg::*fun_b_w_p)(HWINDOW, POINT*);
		BOOL(CXEventMsg::*fun_b_w_e)(HWINDOW, HELE);
		BOOL(CXEventMsg::*fun_b_w_hwnd)(HWINDOW, HWND);
		BOOL(CXEventMsg::*fun_b_w_i)(HWINDOW, int);

		void (CXEventMsg::*fun_v_e_list)(HELE, list_drawItem_*);
		void (CXEventMsg::*fun_v_e_listHeader)(HELE, listHeader_drawItem_*);
		void (CXEventMsg::*fun_v_e_tree)(HELE, tree_drewItem_*);
		void (CXEventMsg::*fun_v_e_listBox)(HELE, listBox_drawItem_*);
		void (CXEventMsg::*fun_v_e_listView)(HELE, listView_drawItem_*);
		void (CXEventMsg::*fun_v_e_listViewGroup)(HELE, listView_drawGroup_*);
		void (CXEventMsg::*fun_v_x_menu_drawItem)(HMENUX, menu_drawItem_*);
		void (CXEventMsg::*fun_v_x_menu_drawBG)(HMENUX, menu_drawBG_*);
		void (CXEventMsg::*fun_v_x_menu_updateUI)(HMENUX, int);
	};
	enum xcgui_reg_type //ע������
	{
		ele_event,        //Ԫ���¼�
		ele_msg,          //Ԫ����Ϣ
		ele_msg_proc,     //Ԫ����Ϣ�������
		ele_event_proc,   //Ԫ���¼��������
		wnd_msg,          //������Ϣ
		wnd_msg_nc,       //�����߼��ǿͻ�����Ϣ
		wnd_msg_proc,     //������Ϣ�������
		//---------------
		ele_scrollView_draw,     //������ͼ�Ի�
		ele_list_drawItem,       //�б����Ի�
		ele_list_drawItemHeader, //�б�ͷ���Ի�
		ele_tree_drawItem,       //�����Ի�
		ele_listBox_drawItem,    //�б�����Ի�
		ele_listView_drawItem,   //�б���ͼ�����
		ele_listView_drawGroup,  //�б���ͼ�����
		ele_menu_drawItem,       //���Ʋ˵���
		ele_menu_drawBG,         //���Ʋ˵�����
		ele_menu_updateUI,       //�˵������UI
	};

	struct  xcgui_info_
	{
		CXEventMsg  *theThis;
		xcgui_functions  funs;
	};

	void RegisterAll(HXCGUI hXCGUI, int type, void (CXEventMsg::*fun)(void), int T) //ע����Ϣ�¼�
	{
		xcgui_info_ *pInfo = (xcgui_info_*)XC_Malloc(sizeof(xcgui_info_));
		pInfo->theThis = this;
		pInfo->funs.fun_v_v = fun;

		switch (T)
		{
		case ele_event: //ע��Ԫ���¼�
			XEle_RegisterEventEx((HELE)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_msg: //Ԫ����Ϣ
			XEle_RegisterMessageEx((HELE)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_msg_proc: //Ԫ����Ϣ�������
			XEle_RegisterMsgProcEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_event_proc: //Ԫ���¼��������
			XEle_RegisterEventProcEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case wnd_msg: //ע�ᴰ����Ϣ
			XWnd_RegisterMessageEx((HWINDOW)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case wnd_msg_nc: //ע�ᴰ���߼��Ϸǿͻ�����Ϣ
			XWnd_RegisterNCMessageEx((HWINDOW)hXCGUI, type, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case wnd_msg_proc:
			XWnd_RegisterMsgProcEx((HWINDOW)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_scrollView_draw: //������ͼ����
			XSView_SetDrawScrollViewEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_list_drawItem: //�б����Ի�
			XList_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_list_drawItemHeader: //�б�ͷ�����
			XList_SetUserDrawItemHeaderEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_tree_drawItem: //�����Ի�
			XTree_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_listBox_drawItem://�б�����Ի�
			XListBox_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_listView_drawItem: //�б���ͼ���Ի�
			XListView_SetUserDrawItemEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_listView_drawGroup: //�б���ͼ���Ի�
			XListView_SetUserDrawGroupEx((HELE)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_menu_drawItem: //�˵����Ի�
			XMenu_SetUserDrawItemEx((HMENUX)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_menu_drawBG:
			XMenu_SetUserDrawBGEx((HMENUX)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		case ele_menu_updateUI:
			XMenu_SetUserUpdateUIEx((HMENUX)hXCGUI, CXEventMsg::OnEventAndMsg, pInfo);
			break;
		};
	}
	static BOOL CALLBACK OnEventAndMsg(eventOrMsg_ *pEvent, xcgui_fun_type funType)//�¼��ص�
	{
		xcgui_info_ *info = (xcgui_info_*)pEvent->pClass_fun;
		BOOL bResult = FALSE;
		switch (funType)
		{
			//////////////////////////////////////////////////
		case xc_fun_b_e_e_i_i:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_i)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_e_e_i:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam);
			break;
		case xc_fun_b_e_e:
			bResult = (info->theThis->*info->funs.fun_b_e_e)(pEvent->hEle, pEvent->hEventEle);
			break;
		case xc_fun_b_e_e_pb:
			bResult = (info->theThis->*info->funs.fun_b_e_e_pb)(pEvent->hEle, pEvent->hEventEle, (BOOL*)&pEvent->wParam);
			break;
		case xc_fun_b_e_e_i_pb:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_pb)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, (BOOL*)pEvent->lParam);
			break;
		case xc_fun_b_e_e_b:
			bResult = (info->theThis->*info->funs.fun_b_e_e_b)(pEvent->hEle, pEvent->hEventEle, (BOOL)pEvent->wParam);
			break;
		case xc_fun_b_e_e_i_pt:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_p)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, (POINT*)pEvent->lParam);
			break;
		case xc_fun_b_e_e_i_b:
			bResult = (info->theThis->*info->funs.fun_b_e_e_i_b)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam, pEvent->lParam ? TRUE : FALSE);
			break;
		case xc_fun_b_e_e_b_b:
			bResult = (info->theThis->*info->funs.fun_b_e_e_b_b)(pEvent->hEle, pEvent->hEventEle, pEvent->wParam ? TRUE : FALSE, pEvent->lParam ? TRUE : FALSE);
			break;
		case xc_fun_b_e_e_w_e:
			bResult = (info->theThis->*info->funs.fun_b_e_e_w_e)(pEvent->hEle, pEvent->hEventEle, (HWINDOW)pEvent->wParam, (HELE)pEvent->lParam);
			break;
		case xc_fun_b_e_e_listView_dragInsert:
			bResult = (info->theThis->*info->funs.fun_b_e_e_listViewDragInsert)(pEvent->hEle, pEvent->hEventEle, (listView_dragInsert_*)pEvent->wParam);
			break;
			/////////////////////////////////////////////////////////
		case xc_fun_v_e:
			(info->theThis->*info->funs.fun_v_e)(pEvent->hEle);
			break;
		case xc_fun_b_e_i_i_i:
			bResult = (info->theThis->*info->funs.fun_b_e_i_i_i)(pEvent->hEle, pEvent->xint, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_e_i_i:
			bResult = (info->theThis->*info->funs.fun_b_e_i_i)(pEvent->hEle, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_e_i_pt:
			bResult = (info->theThis->*info->funs.fun_b_e_i_p)(pEvent->hEle, pEvent->wParam, (POINT*)pEvent->lParam);
			break;
		case xc_fun_b_e_pt:
			bResult = (info->theThis->*info->funs.fun_b_e_p)(pEvent->hEle, (POINT*)pEvent->wParam);
			break;
		case xc_fun_b_e_hdraw:
			bResult = (info->theThis->*info->funs.fun_b_e_hdraw)(pEvent->hEle, (HDRAW)pEvent->wParam);
			break;
		case xc_fun_b_w_hdraw:
			bResult = (info->theThis->*info->funs.fun_b_w_hdraw)(pEvent->hWindow, (HDRAW)pEvent->wParam);
			break;
		case xc_fun_b_w:
			bResult = (info->theThis->*info->funs.fun_b_w)(pEvent->hWindow);
			break;
		case xc_fun_b_w_i_pt:
			bResult = (info->theThis->*info->funs.fun_b_w_i_p)(pEvent->hWindow, pEvent->wParam, (POINT*)pEvent->lParam);
			break;
		case xc_fun_b_w_i_size:
			bResult = (info->theThis->*info->funs.fun_b_w_i_size)(pEvent->hWindow, pEvent->wParam, (SIZE*)pEvent->lParam);
			break;
		case xc_fun_b_w_i_i:
			bResult = (info->theThis->*info->funs.fun_b_w_i_i)(pEvent->hWindow, pEvent->wParam, pEvent->lParam);
			break;
		case xc_fun_b_w_pt:
			bResult = (info->theThis->*info->funs.fun_b_w_p)(pEvent->hWindow, (POINT*)pEvent->wParam);
			break;
		case xc_fun_b_w_e:
			bResult = (info->theThis->*info->funs.fun_b_w_e)(pEvent->hWindow, (HELE)pEvent->wParam);
			break;
		case xc_fun_b_w_hwnd:
			bResult = (info->theThis->*info->funs.fun_b_w_hwnd)(pEvent->hWindow, (HWND)pEvent->wParam);
			break;
		case xc_fun_b_w_i:
			bResult = (info->theThis->*info->funs.fun_b_w_i)(pEvent->hWindow, pEvent->wParam);
			break;
			//////////////////////////////////////////////////////
		case xc_fun_v_e_list_item:
			(info->theThis->*info->funs.fun_v_e_list)(pEvent->hEle, (list_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_list_header:
			(info->theThis->*info->funs.fun_v_e_listHeader)(pEvent->hEle, (listHeader_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_tree:
			(info->theThis->*info->funs.fun_v_e_tree)(pEvent->hEle, (tree_drewItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_listBox:
			(info->theThis->*info->funs.fun_v_e_listBox)(pEvent->hEle, (listBox_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_listView_item:
			(info->theThis->*info->funs.fun_v_e_listView)(pEvent->hEle, (listView_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_e_listView_group:
			(info->theThis->*info->funs.fun_v_e_listViewGroup)(pEvent->hEle, (listView_drawGroup_*)pEvent->wParam);
			break;
		case xc_fun_v_x_menu_item:
			(info->theThis->*info->funs.fun_v_x_menu_drawItem)(pEvent->hMenu, (menu_drawItem_*)pEvent->wParam);
			break;
		case xc_fun_v_x_menu_bg:
			(info->theThis->*info->funs.fun_v_x_menu_drawBG)(pEvent->hMenu, (menu_drawBG_*)pEvent->wParam);
			break;
		case xc_fun_v_x_menu_i:
			(info->theThis->*info->funs.fun_v_x_menu_updateUI)(pEvent->hMenu, pEvent->wParam);
			break;
		}
		return bResult;
	}
};

#endif //XCGUI_PLUS


//������ӵ���API����////////////////////////////////////////////////////////


#endif //XCGUI_HEADER_FILE_