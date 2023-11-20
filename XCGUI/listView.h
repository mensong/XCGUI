/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct listView_item_
{
	HSTRING hString; //�ַ����б� wchar_t*
	int   imageID;   //�ַ�����Ӧͼ��ID

	RECT  rcIcon; //ͼ������
	RECT  rcText; //��������
	RECT  rect; //��������,�����߿�
	RECT  rcIconDraw; //ͼ���������

	int   state;  //״̬ ѡ�� ͣ�� �뿪
	int   groupIndex; //������������ -1û����
	int   index;  //����������λ������

	//״̬��ͼ
	HIMAGE hImage_stay;
	HIMAGE hImage_select;

	void* userData; //�û�������
};

//��
struct listView_group_
{
	HARRAY hArrayList;   //listView_item_*

	HSTRING hString;
	RECT  rcText;
	RECT  rcButton;    //չ����ť rcButton
	RECT  rect;    //������

	int   index;  //����������λ������

	BOOL  bExpand;    //�Ƿ�չ��
	void* userData;   //�û�������
};

struct listView_
{
	scrollView_  scrollView; //�̳�
	//-------------

	HARRAY  hArrayList;      //δ������ listView_item_*
	HARRAY  hArrayGroupList; //�����б� listView_group_*

	HXCGUI  hImageList;      //ͼƬ�б�

	//��ǰ������λ��
	int    insertGroup;
	int    insertItem;

	SIZE  iconSize;    //��ͼ�������С
	int   left, top, right, bottom; //��߿�����С
	int   columnSpace; //���м�� X
	int   rowSpace;    //���м�� Y
	int   iconTextSpace; //ͼ�����ı����
	int   leftAlign;  //��ͼ�����
	int   topAlign;   //��ͼ�϶���
	int   groupHeight; //��߶�

	BOOL    bAdjust;
	BOOL    bExpandButton; //�Ƿ���ʾչ����ť 
	BOOL    bDragItem;     //�϶���
	HWINDOW hWndDrag;     //�����϶����


	//���ùرն�ѡѡ��
	BOOL   bMultiSelect;  //�Ƿ����ѡ�� Multi-Item
	HARRAY  hArrayCurrItem; //��ǰѡ�����б� listView_item_* ,����ѡʱ��ʹ��
	listView_item_  *pCurrItem;  //��ǰ���ʱ��ѡ�����

	listView_item_  *pCurrItemStay; //��ǰ���ͣ����

	//�϶�ѡ��---------
	BOOL   down;
	BOOL   bDrag;  //�϶�����
	POINT  dragPt;
	POINT  dragEndPt;


	//----------------------
	pFunListView_DrawItem  pDrawItem; //�û��Ի�
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif

	//----------------------
	pFunListView_DrawGroup  pDrawGroup; //�û��Ի�
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info_group;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
XC_API void WINAPI XListView_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի���
XC_API void WINAPI XListView_SetUserDrawGroupEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի���
#endif

//API:
XC_API HELE WINAPI XListView_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XListView_AddItem(HELE hEle, wchar_t *pName, int imageID = -1, int groupIndex = -1); //������
XC_API int  WINAPI XListView_AddGroup(HELE hEle, wchar_t *pName, BOOL bExpand = TRUE); //������
XC_API int  WINAPI XListView_InsertItem(HELE hEle, int groupIndex, int itemIndex, wchar_t *pName, int imageID = -1);  //������
XC_API int  WINAPI XListView_InsertGroup(HELE hEle, int groupIndex, wchar_t *pName, BOOL bExpand = TRUE);  //������

XC_API void WINAPI XListView_SetImageList(HELE hEle, HXCGUI hImageList);
XC_API BOOL WINAPI XListView_SetItemData(HELE hEle, int groupIndex, int itemIndex, void* data); //�����������
XC_API BOOL WINAPI XListView_SetGroupData(HELE hEle, int groupIndex, void* data); //�����������
XC_API BOOL WINAPI XListView_SetSelectItem(HELE hEle, int goupIndex, int itemIndex, BOOL bSelect);//����ѡ����

XC_API BOOL WINAPI XListView_SetItemText(HELE hEle, int groupIndex, int itemIndex, wchar_t *pText);//�������ı�
XC_API BOOL WINAPI XListView_SetGroupText(HELE hEle, int groupIndex, wchar_t *pText);//�������ı�
XC_API BOOL WINAPI XListView_SetItemIcon(HELE hEle, int groupIndex, int itemIndex, int imageID);//������ͼ��ID

XC_API void WINAPI XListView_SetIconSize(HELE hEle, int cx, int cy); //����ͼ�������С,������ͼ��Ĵ�С.
XC_API void WINAPI XListView_SetItemBorderSpacing(HELE hEle, int left, int top, int right, int bottom); //������߼��
XC_API void WINAPI XListView_SetColumnSpacing(HELE hEle, int width); //�������м��
XC_API void WINAPI XListView_SetRowSpacing(HELE hEle, int height);  //�������м��
XC_API void WINAPI XListView_SetItemIconTextSpacing(HELE hEle, int height);  //����ͼ�����ı����
XC_API void WINAPI XListView_SetViewLeftAlign(HELE hEle, int size);  //������ͼ�����
XC_API void WINAPI XListView_SetViewTopAlign(HELE hEle, int size); //������ͼ�϶���
XC_API void WINAPI XListView_SetGroupHeight(HELE hEle, int height); //������߶�

XC_API void WINAPI XListView_GetIconSize(HELE hEle, out_ SIZE *pSize); //��ȡͼ�������С,������ͼ��Ĵ�С.
XC_API int  WINAPI XListView_GetItemBorderLeft(HELE hEle); //��ȡ��߼��
XC_API int  WINAPI XListView_GetItemBorderTop(HELE hEle);
XC_API int  WINAPI XListView_GetItemBorderRight(HELE hEle);
XC_API int  WINAPI XListView_GetItemBorderBottom(HELE hEle);
XC_API int  WINAPI XListView_GetColumnSpacing(HELE hEle); //��ȡ���м��
XC_API int  WINAPI XListView_GetRowSpacing(HELE hEle);  //��ȡ���м��
XC_API int  WINAPI XListView_GetItemIconTextSpacing(HELE hEle);  //��ȡͼ�����ı����
XC_API int  WINAPI XListView_GetViewLeftAlign(HELE hEle);  //��ȡ��ͼ�����
XC_API int  WINAPI XListView_GetViewTopAlign(HELE hEle); //��ȡ��ͼ�϶���
XC_API int  WINAPI XListView_GetGroupHeight(HELE hEle); //��ȡ��߶�

XC_API void  WINAPI XListView_GetSelectItem(HELE hEle, out_ int *pGroupIndex, out_ int *pItemIndex);    //��ȡѡ����
XC_API int  WINAPI XListView_GetSelectCount(HELE hEle);  //��ȡѡ��������
XC_API int  WINAPI XListView_GetSelectAllItem(HELE hEle, int *pArrayGroupIndex, int *pArrayItemIndex, int arrayLength); //��ȡ����ѡ����

XC_API int  WINAPI XListView_GetGroupCount(HELE hEle); //��ȡ������
XC_API int  WINAPI XListView_GetGroupMemberCount(HELE hEle, int groupIndex); //��ȡ���Ա����
XC_API int  WINAPI XListView_GetUngroupMemberCount(HELE hEle);//��ȡδ����������

XC_API HXCGUI WINAPI XListView_GetImageList(HELE hEle); //��ȡͼƬ�б�
XC_API BOOL WINAPI XListView_GetItemRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect); //��ȡ������
XC_API BOOL WINAPI XListView_GetItemIconRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect);//��ȡ��ͼ������
XC_API BOOL WINAPI XListView_GetItemTextRect(HELE hEle, int groupIndex, int itemIndex, out_ RECT *pRect); //��ȡ���ı�����
XC_API wchar_t* WINAPI XListView_GetItemText(HELE hEle, int groupIndex, int itemIndex);//��ȡ���ı�
XC_API int  WINAPI XListView_GetItemIcon(HELE hEle, int groupIndex, int itemIndex);//��ȡ��ͼ��ID

XC_API wchar_t* WINAPI XListView_GetGroupText(HELE hEle, int groupIndex);//��ȡ���ı�
XC_API BOOL WINAPI XListView_GetGroupRect(HELE hEle, int groupIndex, out_ RECT *pRect);//��ȡ������

XC_API void* WINAPI XListView_GetItemData(HELE hEle, int groupIndex, int itemIndex); //��ȡ�������
XC_API void* WINAPI XListView_GetGroupData(HELE hEle, int groupIndex); //��ȡ�������

XC_API BOOL WINAPI XListView_DeleteItem(HELE hEle, int groupIndex, int itemIndex); //ɾ����
XC_API BOOL WINAPI XListView_DeleteGroup(HELE hEle, int groupIndex); //ɾ����
XC_API void WINAPI XListView_DeleteAllGroups(HELE hEle); //ɾ��������
XC_API void WINAPI XListView_DeleteAll(HELE hEle); //ɾ������,�������

XC_API int WINAPI XListView_IsItemSelect(HELE hEle, int groupIndex, int itemIndex);//������Ƿ�ѡ��
XC_API BOOL WINAPI XListView_HitTest(HELE hEle, POINT *pPt, out_ int *pGroupIndex, out_ int *pItemIndex);//�����û����,��,��

XC_API int WINAPI XListView_IsGroupExpand(HELE hEle, int groupIndex);//�ж����Ƿ�չ��
XC_API BOOL WINAPI XListView_SetGroupExpand(HELE hEle, int groupIndex, BOOL bExpand); //չ��ָ����

XC_API void WINAPI XListView_EnableMultiSelect(HELE hEle, BOOL bEnable); //���ùرն���ѡ��
XC_API void WINAPI XListView_EnableExpandButton(HELE hEle, BOOL bEnable); //����/�ر�չ����ť
XC_API void WINAPI XListView_CancelSelectItem(HELE hEle, int groupIndex, int itemIndex); //ȡ��ѡ��ָ����
XC_API void WINAPI XListView_CancelSelectAll(HELE hEle); //ȡ��ѡ��������

XC_API void WINAPI XListView_SetUserDrawItem(HELE hEle, pFunListView_DrawItem pFunDrawItem); //�����û��Ի���
XC_API void WINAPI XListView_SetUserDrawGroup(HELE hEle, pFunListView_DrawGroup pFunDrawGroup); //�����û��Ի���

//������ͼ
XC_API void WINAPI XListView_SetItemImageSelect(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage);
XC_API void WINAPI XListView_SetItemImageStay(HELE hEle, int groupIndex, int itemIndex, HIMAGE hImage);

XC_API void WINAPI XListView_Adjust(HELE hEle); //��������

//˽�з���:
void ListView_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
listView_group_ *ListView_CheckDownGroup(HELE hEle, POINT *pPt); //������������
listView_item_  *ListView_CheckDownItem(HELE hEle, POINT *pPt);  //������������

void ListView_DeleteItem_XC(HELE hEle, listView_item_ *pItem); //ɾ����,���APIɾ����ʹ��
void ListView_DeleteGroup_XC(HELE hEle, listView_group_ *pGroup); //ɾ����,���APIɾ����ʹ��

listView_item_  *ListView_GetItem_XC(HELE hEle, int groupIndex, int itemIndex); //��ȡ��
listView_group_  *ListView_GetGroup_XC(HELE hEle, int groupIndex); //��ȡ��

void ListView_AdjustItem(HELE hEle, listView_item_ *pItem, int x, int y);//������
void ListView_CalculateView(HELE hEle);

void ListView_DrawItem(HELE hEle, listView_drawItem_ *pItem);
void ListView_DrawGroup(HELE hEle, listView_drawGroup_ *pGroup);

void ListView_ShiftDown(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown1(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown2(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown3(HELE hEle, listView_item_ *pItem);
void ListView_ShiftDown4(HELE hEle, listView_item_ *pItem);

void ListView_MouseMoveDragBegin(HELE hEle, POINT *pPt); //׼���϶�ѡ��
void ListView_MouseMoveDrag(HELE hEle, POINT *pPt); //�϶�ѡ��


//�ص�����
void CALLBACK ListView_OnDestroy(HELE hEle);  //����
BOOL CALLBACK ListView_OnEleDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ListView_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ListView_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnEleLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnEleLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnEventKillFocus(HELE hEle, HELE hEventEle); //ʧȥ����
BOOL CALLBACK ListView_OnEventMouseLeave(HELE hEle, HELE hEventEle);


extern HELE  g_hListView;
VOID CALLBACK ListView_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


//�����϶����
BOOL CALLBACK ListView_OnDrawWindow_DragItem(HWINDOW hWindow, HDRAW hDraw);
BOOL CALLBACK ListView_OnWndMouseMove_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnWndLButtonUp_DragItem(HWINDOW hWindow, UINT flags, POINT *pPt);
BOOL CALLBACK ListView_OnWndNCDestroy_DragItem(HWINDOW hWindow);
