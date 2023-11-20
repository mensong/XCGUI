/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//�ӿ�����
#define  XC_COMBOBOXWINDOW        10   //comboBoxWindow_        ��Ͽ򵯳������б���
#define  XC_POPUPMENUWINDOW       11   //popupMenuWindow_       �����˵�������
#define  XC_POPUPMENUCHILDWINDOW  12   //popupMenuChildWindow_  �����˵��Ӵ���
#define  XC_MSGBOXWINDOW          13   //������Ϣ��
#define  XC_DATETIMEWINDOW        14   //ʱ��Ԫ��,��������ѡ�񴰿�



//��ʱ��
#define  IDT_CLICK             30002   //�����������Ϣ
#define  IDT_HSCROLL_UP        30003   //������ť��ʱ��  �Ϲ���
#define  IDT_HSCROLL_DOWN      30004   //������ť��ʱ��  �¹���
#define  IDT_CARET             30005   //�����
#define  IDT_LIST_DRAG_RECT    30030   //�б�Ԫ���϶�ѡ�����
#define  IDT_HSCROLLDELAY      30009   //�����¼���ʱ
#define  IDT_VSCROLLDELAY      30010   //�����¼���ʱ
#define  IDT_MENU              30011   //����˵�
#define  IDT_MENU2             30012   //�Ӳ˵�
#define  IDT_TOOLTIPS          30013   //������ʾ
#define  IDT_TOOLTIPS_TIMEOUT  30014   //������ʾ��ʱ�ر�
#define  IDT_LISTVIEW_DRAG_RECT    30030   //�б���ͼԪ���϶�ѡ�����

#define  XC_WIND_SHADOW_SIZE  7  //��Ӱ���ڱ߿��С

//������Ϣ-����ϵͳ�ǿͻ�����Ϣ
#define  XWM_EVENT_ALL        WM_APP+1000 //�¼�Ͷ�� -------������-------����Ҫע��

//wParam:left-top�������; lParam:right-bottom�������; �����2������Ϊ��,��ô�ػ���������
#define  XWM_REDRAW            WM_APP+1007  //�����ػ���ʱ ----������-----�ڲ��Զ�����Ϣ


//ע�ᴰ����Ϣ��������-����ϵͳ�ǿͻ�����Ϣ
typedef BOOL(CALLBACK *pFunWndOther)(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //����������Ϣ
typedef BOOL(CALLBACK *pFunWndMouseClick)(HWINDOW hWindow, POINT *pPt);    //��굥��
typedef BOOL(CALLBACK *pFunWndMouseDBClick)(HWINDOW hWindow, POINT *pPt);  //���˫��
typedef BOOL(CALLBACK *pFunWndRedrawEle)(HWINDOW hWindow, HELE hEle, RECT *pRect);
typedef BOOL(CALLBACK *pFunWndMenuSelect)(HWINDOW hWindow, int id);  //�˵�ѡ��
typedef BOOL(CALLBACK *pFunWndMenuExit)(HWINDOW hWindow); //�˵��˳�
typedef BOOL(CALLBACK *pFunWndSetFont)(HWINDOW hWindow); //��������ı�XWM_SETFONT

typedef BOOL(CALLBACK *pFunWndDrawWindow)(HWINDOW hWindow, HDRAW hDraw);  //WM_PAINT
typedef BOOL(CALLBACK *pFunWndClose)(HWINDOW hWindow);    //WM_CLOSE
typedef BOOL(CALLBACK *pFunWndDestroy)(HWINDOW hWindow);  //WM_DESTROY
typedef BOOL(CALLBACK *pFunWndNCDestroy)(HWINDOW hWindow);  //WM_NCDESTROY
typedef BOOL(CALLBACK *pFunWndMouseMove)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_MOUSEMOVE
typedef BOOL(CALLBACK *pFunWndLButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_LBUTTONDOWN
typedef BOOL(CALLBACK *pFunWndLButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt);  //WM_LBUTTONUP
typedef BOOL(CALLBACK *pFunWndRButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_RBUTTONDOWN
typedef BOOL(CALLBACK *pFunWndRButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_RBUTTONUP
typedef BOOL(CALLBACK *pFunWndMouseWheel)(HWINDOW hWindow, UINT flags, POINT *pPt); //WM_MOUSEWHEEL ������Ϣ
typedef BOOL(CALLBACK *pFunWndExitSizeMove)(HWINDOW hWindow);//WM_EXITSIZEMOVE
typedef BOOL(CALLBACK *pFunWndMouseLeave)(HWINDOW hWindow); //WM_MOUSELEAVE
typedef BOOL(CALLBACK *pFunWndSize)(HWINDOW hWindow, UINT flags, SIZE *pSize); //WM_SIZE
typedef BOOL(CALLBACK *pFunWndTimer)(HWINDOW hWindow, UINT timerID, UINT uElapse); //��ʱ����Ϣ WM_TIMER
typedef BOOL(CALLBACK *pFunWndTimerEx)(HWINDOW hWindow, UINT timerID, void* userData); //��ʱ����Ϣ XWM_TIMER

typedef BOOL(CALLBACK *pFunWndSetFocus)(HWINDOW hWindow);    //���ڻ�ý��� WM_SETFOCUS
typedef BOOL(CALLBACK *pFunWndKillFocus)(HWINDOW hWindow);   //����ʧȥ���� WM_KILLFOCUS
typedef BOOL(CALLBACK *pFunWndKeyDown)(HWINDOW hWindow, WPARAM wParam, LPARAM lParam); //WM_KEYDOWN
typedef BOOL(CALLBACK *pFunWndCaptureChanged)(HWINDOW hWindow, HWND hWnd); //WM_CAPTURECHANGED  hWnd:�����겶��Ĵ��ھ��


//���ڷǿͻ���-�߼��ϵķǿͻ���
typedef BOOL(CALLBACK *pFunWndNCDrawWindow)(HWINDOW hWindow, HDRAW hDraw); //�ǿͻ�������
typedef BOOL(CALLBACK *pFunWndNCEndDrawWindow)(HWINDOW hWindow, HDRAW hDraw); //XWM_NCENDPAINT
typedef BOOL(CALLBACK *pFunWndNCMouseMove)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCLButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCLButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCRButtonDown)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCRButtonUp)(HWINDOW hWindow, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunWndNCMouseClick)(HWINDOW hWindow, POINT *pPt);  //��굥��
typedef BOOL(CALLBACK *pFunWndNCMouseDBClick)(HWINDOW hWindow, POINT *pPt);  //���˫��


//ע��Ԫ����Ϣ������
typedef BOOL(CALLBACK *pFunEleDraw)(HELE hEle, HDRAW hDraw);
typedef BOOL(CALLBACK *pFunEleMouseClick)(HELE hEle, POINT *pPt); //��굥��
typedef BOOL(CALLBACK *pFunEleMouseDBClick)(HELE hEle, POINT *pPt);//���˫��
typedef BOOL(CALLBACK *pFunEleMouseMove)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleLButtonDown)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleLButtonUp)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleRButtonDown)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleRButtonUp)(HELE hEle, UINT flags, POINT *pPt);
typedef BOOL(CALLBACK *pFunEleTimerEx)(HELE hEle, UINT timerID, void* userData);


//Ԫ���¼�������
typedef BOOL(CALLBACK *pFunEventBtnClick)(HELE hEle, HELE hEventEle); //��ť�¼�
typedef BOOL(CALLBACK *pFunEventMouseStay)(HELE hEle, HELE hEventEle); //���ͣ��
typedef BOOL(CALLBACK *pFunEventMouseLeave)(HELE hEle, HELE hEventEle); //����뿪
typedef BOOL(CALLBACK *pFunEventSetFocus)(HELE hEle, HELE hEventEle); //��ý���
typedef BOOL(CALLBACK *pFunEventKillFocus)(HELE hEle, HELE hEventEle); //ʧȥ����
typedef BOOL(CALLBACK *pFunEventKeyDown)(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
typedef BOOL(CALLBACK *pFunEventHScroll)(HELE hEle, HELE hEventEle, int pos); //ˮƽ����
typedef BOOL(CALLBACK *pFunEventVScroll)(HELE hEle, HELE hEventEle, int pos); //��ֱ����
typedef BOOL(CALLBACK *pFunEventHScrollView)(HELE hEle, HELE hEventEle, int pos); //ˮƽ����
typedef BOOL(CALLBACK *pFunEventVScrollView)(HELE hEle, HELE hEventEle, int pos); //��ֱ����
typedef BOOL(CALLBACK *pFunEventChar)(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
typedef BOOL(CALLBACK *pFunEventSetCapture)(HELE hEle, HELE hEventEle);  //������겶��
typedef BOOL(CALLBACK *pFunEventKillCapture)(HELE hEle, HELE hEventEle); //ʧȥ��겶��
typedef BOOL(CALLBACK *pFunEventMouseWheel)(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt); //�����¼�
typedef BOOL(CALLBACK *pFunEventMenuSelect)(HELE hEle, HELE hEventEle, int id); //�˵�ѡ���¼�
typedef BOOL(CALLBACK *pFunEventMenuExit)(HELE hEle, HELE hEventEle);   //�˵��˳��¼�
typedef BOOL(CALLBACK *pFunEventSize)(HELE hEle, HELE hEventEle);   //Ԫ�ش�Сλ�øı�
typedef BOOL(CALLBACK *pFunEventSetFont)(HELE hEle, HELE hEventEle); //Ԫ������ı�
typedef BOOL(CALLBACK *pFunEventShow)(HELE hEle, HELE hEventEle, BOOL bShow); //Ԫ����ʾ�������¼�


typedef void (CALLBACK *pFunEventDestroy)(HELE hEle);  //Ԫ������ Destroy

typedef BOOL(CALLBACK *pFunEventListSelect)(HELE hEle, HELE hEventEle, int index); //�б���ѡ��
typedef BOOL(CALLBACK *pFunEventListHeaderClick)(HELE hEle, HELE hEventEle, int index);  //�б�ͷ����
typedef BOOL(CALLBACK *pFunEventListHeaderChange)(HELE hEle, HELE hEventEle, int index, int width); //�б�ͷ��ȸı�

typedef BOOL(CALLBACK *pFunEventTreeSelect)(HELE hEle, HELE hEventEle, int id);      //���б�ѡ��
typedef BOOL(CALLBACK *pFunEventTreeExpand)(HELE hEle, HELE hEventEle, int id, BOOL bExpand); //����չ��������

typedef BOOL(CALLBACK *pFunEventComboBoxSelect)(HELE hEle, HELE hEventEle, int index); //������Ͽ�ѡ���¼�
typedef BOOL(CALLBACK *pFunEventComboBoxPopupList)(HELE hEle, HELE hEventEle, HWINDOW hWindow, HELE hListBox); //XE_COMBOBOX_POPUP_LIST
typedef BOOL(CALLBACK *pFunEventComboBoxExitList)(HELE hEle, HELE hEventEle); //XE_COMBOBOX_EXIT_LIST

typedef BOOL(CALLBACK *pFunEventPPageSelect)(HELE hEle, HELE hEventEle, int index);    //����ҳ��ǩѡ��
typedef BOOL(CALLBACK *pFunEventSliderChange)(HELE hEle, HELE hEventEle, int pos); //������λ�øı�
typedef BOOL(CALLBACK *pFunEventMonthChange)(HELE hEle, HELE hEventEle, BOOL bChange, BOOL bDownDayNum); //����Ԫ��,���ڸı��¼�,

typedef BOOL(CALLBACK *pFunEventDateTimeChange)(HELE hEle, HELE hEventEle); //����Ԫ�ظı�
typedef BOOL(CALLBACK *pFunEventDateTimePopupMonthCal)(HELE hEle, HELE hEventEle);
typedef BOOL(CALLBACK *pFunEventDateTimeExitMonthCal)(HELE hEle, HELE hEventEle);

typedef BOOL(CALLBACK *pFunEventListBoxSelect)(HELE hEle, HELE hEventEle, int index);  //XE_LISTBOX_SELECT
typedef BOOL(CALLBACK *pFunEventPGridSelChange)(HELE hEle, HELE hEventEle, int prevID, int id); //XE_PGRID_SELCHANGE
typedef BOOL(CALLBACK *pFunEventPGridValueChange)(HELE hEle, HELE hEventEle, int id); //XE_PGRID_VALUECHANGE

typedef BOOL(CALLBACK *pFunEventListViewSelect)(HELE hEle, HELE hEventEle, int groupIndex, int itemIndex); //�б���Ԫ��,��ѡ���¼�
typedef BOOL(CALLBACK *pFunEventListViewExpand)(HELE hEle, HELE hEventEle, int GroupIndex, BOOL bExpand); //�б���Ԫ��,��չ�������¼�

typedef BOOL(CALLBACK *pFunEventListViewDragInsert)(HELE hEle, HELE hEventEle, listView_dragInsert_ *pInfo);//�б���ͼԪ��,�û��϶�������¼�

typedef BOOL(CALLBACK *pFunEventPaneLock)(HELE hEle, HELE hEventEle);
typedef BOOL(CALLBACK *pFunEventPaneDock)(HELE hEle, HELE hEventEle);
typedef BOOL(CALLBACK *pFunEventPaneFloat)(HELE hEle, HELE hEventEle);

typedef BOOL(CALLBACK *pFunEventEditChange)(HELE hEle, HELE hEventEle); //XE_EDIT_CHANGE

typedef BOOL(CALLBACK *pFunEventComboBoxSelecting)(HELE hEle, HELE hEventEle, int index, BOOL *pBOOL);
typedef BOOL(CALLBACK *pFunEventListBoxSelecting)(HELE hEle, HELE hEventEle, int index, BOOL *pBOOL);
typedef BOOL(CALLBACK *pFunEventTreeSelecting)(HELE hEle, HELE hEventEle, int id, BOOL *pBOOL);



//ͬһ����Ϣ�ж��������,�ȴ������ע�����Ϣ,������һ��ע��ĺ���.

#define  BUTTON(hEle)      ((button_*)hEle)      //((button_*)((ele_*)hEle)->pExtensionEle)
#define  CHECK(hEle)       ((check_*)hEle)       //((check_*)((button_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  RADIO(hEle)       ((radio_*)hEle)       //((radio_*)((button_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  SCROLLBAR(hEle)   ((scrollBar_*)hEle)   // ((scrollBar_*)((ele_*)hEle)->pExtensionEle)
#define  SCROLLVIEW(hEle)  ((scrollView_*)hEle)  // ((scrollView_*)((ele_*)hEle)->pExtensionEle)
#define  EDIT(hEle)        ((edit_*)hEle)        // ((edit_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  LIST(hEle)        ((list_*)hEle)        // ((list_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  TREE(hEle)        ((tree_*)hEle)        // ((tree_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  LISTBOX(hEle)     ((listBox_*)hEle)     // ((listBox_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)
#define  COMBOBOX(hEle)    ((comboBox_*)hEle)    // ((comboBox_*)((edit_*)((scrollView_*)((ele_*)hEle)->pExtensionEle)->pExtensionEle)->pExtensionEle)
#define  PPAGE(hEle)       ((propertyPage_*)hEle)
#define  SLIDER(hEle)      ((slider_*)hEle)
#define  TOOLBAR(hEle)     ((toolBar_*)hEle)
#define  STATIC(hEle)      ((static_*)hEle)
#define  GROUPBOX(hEle)    ((groupBox_*)hEle)
#define  PICTURE(hEle)     ((picture_*)hEle)

#define  MENUBARBUTTON(hEle)   ((menuBarButon_*)hEle)
#define  MENUBAR(hEle)         ((menuBar_*)hEle)
#define  DATETIME(hEle)         ((dateTime_*)hEle)
#define  WINDOW(hWindow)                ((window_*)hWindow)
#define  POPUPMENUWINDOW(hWindow)       ((popupMenuWindow_*)hWindow)
#define  POPUPMENUCHILDWINDOW(hWindow)  ((popupMenuChildWindow_*)hWindow)
#define  COMBOBOXWINDOW(hWindow)        ((comboBoxWindow_*)hWindow)
#define  MODALWINDOW(hWindow)           ((modalWindow_*)hWindow)

struct object_type_
{
	int type;
	object_type_  *pNext;
};

struct object_
{
	int type; //��Դ����   HELE, HWINDOW ,HARRAY ,HSTRING

	object_type_  *pTypeList;  //�����б�
};


//�жϸ������Ƿ��ԼΪ0
#define EPSILON  0.00001
#define IsFlaotZero(x) (x>= -EPSILON && x<=EPSILON)
//if(X>= -EPSINON && X<=EPSINON) X=0;


//����������
#define MsgError(error)  { MessageBox(NULL,error,L"�Ųʽ����-������ʾ!",0); exit(0); }

//������,Ψһ,�Ͻ��ظ�ʹ��,ʹ�ú�ӱ�ע
#define XC_ERROR_0001   L"code:0001"   //ok
#define XC_ERROR_0002   L"code:0002"   //ok
#define XC_ERROR_0003   L"code:0003"   //ok
#define XC_ERROR_0004   L"code:0004"   //ok
#define XC_ERROR_0005   L"code:0005"   //ok
#define XC_ERROR_0006   L"code:0006"   //ok
#define XC_ERROR_0007   L"code:0007"   //ok
#define XC_ERROR_0008   L"code:0008"   //ok
#define XC_ERROR_0009   L"code:0009"   //ok
#define XC_ERROR_0010   L"code:0010"   //ok
#define XC_ERROR_0011   L"code:0011"   //ok
#define XC_ERROR_0012   L"code:0012"   //ok