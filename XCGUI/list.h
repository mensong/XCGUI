/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct listHeader_  //�б�ͷ
{
	RECT rect;
	HSTRING  hString;

	int minWidth;//������С���
	int width;

	int state;  //״̬
	int imageId; //ͼƬ
};

struct listSubItem_ //����
{
	HSTRING  hString; //�ı�
	RECT  rect;
	int   imageId;   //ͼ��ID

	HARRAY hArrayBindEle; //�󶨵�Ԫ�� itemBindEle_*
};

struct listItem_  //��
{
	int state;   //״̬
	int index;   //�����б��е�����

	void*	userData;  //�û�����

	BOOL    bCheck;    //��ѡ���Ƿ�ѡ��
	RECT    rcCheck;   //��ѡ��
	HARRAY  hArrayItem;  //����
};

#define  XLIST_CHECK_SIZE   13 //��ѡ���С
#define  XLIST_ITEM_LEFT    3  //����߼��

struct list_
{
	scrollView_  scrollView; //�̳�
	//-------------
	//�б�ͷ*****************
	HARRAY        hArrayHeader;  //�б�ͷ listHeader_*
	listHeader_   *pCurrHeader;  //��ǰ��������б�ͷ��
	BOOL          bAdjustHeader; //�Ƿ���Ҫ�����б�ͷ,TRUE��Ҫ����
	BOOL          bShowHeader;   //�Ƿ���ʾ�б�ͷ
	int           headerHeight;  //�б�ͷ�߶�
	int           downIndex;     //��갴��, �����б�ͷ�϶��ָ�������
	//int           minRange;      //�б�ͷ�϶���С��Χ
	BOOL          bGrid;         //��������


	//�б���ͼ*************
	HARRAY  hArrayItem;     //���б� listItem_*
	HARRAY  hArrayCurrItem; //��ǰѡ�����б� listItem_*
	listItem_  *pCurrItem;  //��ǰ���ʱ��ѡ�����
	BOOL   bAdjustItem;   //�Ƿ���Ҫ�����б���,TRUE����
	int    spacingLeft;   //����
	int    spacingRight;  //�Ҽ��
	int    itemHeight;    //���
	HXCGUI hImageList;    //ͼƬ�б�

	//�϶�ѡ��---------
	BOOL   down;
	BOOL   bDrag;  //�϶�����
	POINT  dragPt;
	POINT  dragEndPt;

	BOOL   bMultilineSelect;  //�Ƿ����ѡ�� Multi-line

	//��ѡ��
	BOOL   bCheck;  //�Ƿ���ʾ��ѡ��

	//����ƶ�������ʾ
	BOOL  bLineHighlight; //�Ƿ����ø�����ʾ
	listItem_   *pItemMouseStay; //��ǰ���ͣ������

//-----------------------------
	pFunList_DrawItem  pDrawItem; //�û��Ի��б���
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info_Item;//��Ϣ�¼��ص�������Ϣָ��
#endif
//----------------------------
	pFunListHeader_DrawItem pDrawItemHeader;//�û��Ի��б�ͷ��
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info_ItemHeader;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
XC_API void WINAPI XList_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի��б���
XC_API void WINAPI XList_SetUserDrawItemHeaderEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի��б�ͷ��
#endif

//API:
XC_API HELE WINAPI XList_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int WINAPI XList_AddColumn(HELE hEle, int width, wchar_t *pText, int imageId = -1); //������
XC_API int WINAPI XList_AddItem(HELE hEle, wchar_t *pText, int imageId = -1);  //������
XC_API BOOL WINAPI XList_InsertColumn(HELE hEle, int index, int width, wchar_t *pText, int imageId = -1);  //������
XC_API BOOL WINAPI XList_InsertItem(HELE hEle, int index, wchar_t *pText, int imageId = -1);  //������
XC_API BOOL WINAPI XList_SetItemText(HELE hEle, int item, int subItem, wchar_t *pText, int imageId = -1); //��������
XC_API BOOL WINAPI XList_SetColumnWidth(HELE hEle, int index, int width);   //�����п�
XC_API BOOL WINAPI XList_SetItemImage(HELE hEle, int item, int subItem, int imageId);   //��������ͼƬ
XC_API void WINAPI XList_SetImageList(HELE hEle, HXCGUI hImageList); //����ͼƬ�б�
XC_API void WINAPI XList_SetItemHeight(HELE hEle, int height);  //������߶�
XC_API void WINAPI XList_SetHeaderHeight(HELE hEle, int height); //�����б�ͷ�߶�
XC_API BOOL WINAPI XList_SetSelectItem(HELE hEle, int index);   //����ѡ����
XC_API void WINAPI XList_SetSelectItemAll(HELE hEle);     //ȫѡ
XC_API void WINAPI XList_SetSpacingLeft(HELE hEle, int spacing);  //������������
XC_API void WINAPI XList_SetSpacingRight(HELE hEle, int spacing); //���������Ҽ��
XC_API void WINAPI XList_SetItemData(HELE hEle, int index, void* data);   //�����û�����
XC_API BOOL WINAPI XList_SetItemBindEle(HELE hEle, int item, int subItem, itemBindEle_ *pInfo); //��Ԫ��
XC_API void WINAPI XList_SetColumnMinWidth(HELE hEle, int index, int minWidth); //��������С���

XC_API int WINAPI XList_GetHeaderHeight(HELE hEle);        //��ȡ�б�ͷ�߶�
XC_API wchar_t* WINAPI XList_GetHeaderItemText(HELE hEle, int index);  //��ȡ�б�ͷ���ı�

XC_API int WINAPI XList_GetColumnWidth(HELE hEle, int index);     //��ȡ�п�
XC_API int WINAPI XList_GetSpacingLeft(HELE hEle);  //��ȡ��������
XC_API int WINAPI XList_GetSpacingRight(HELE hEle); //��ȡ�����Ҽ��

XC_API HXCGUI WINAPI XList_GetImageList(HELE hEle);     //��ȡͼƬ�б�
XC_API wchar_t* WINAPI XList_GetItemText(HELE hEle, int index, int subItem); //��ȡ���ı�
XC_API int WINAPI XList_GetItemImage(HELE hEle, int item, int subItem); //��ȡ����ͼƬ
XC_API int WINAPI XList_GetItemHeight(HELE hEle);       //��ȡ���
XC_API void* WINAPI XList_GetItemData(HELE hEle, int index);   //�����û�����
XC_API int WINAPI XList_GetSelectCount(HELE hEle);      //��ȡѡ��������
XC_API int WINAPI XList_GetSelectItem(HELE hEle);       //��ȡѡ����
XC_API int WINAPI XList_GetSelectAllItem(HELE hEle, out_ int *pArray, int arrayLength);  //��ȡ����ѡ����
XC_API int WINAPI XList_GetItemCount(HELE hEle);        //��ȡ������

XC_API BOOL WINAPI XList_GetHeaderItemRect(HELE hEle, int item, out_ RECT *pRect); //��ȡ�б�ͷ������
XC_API BOOL WINAPI XList_GetSubItemRect(HELE hEle, int item, int sub, out_ RECT *pRect);//��ȡ��������
XC_API BOOL WINAPI XList_GetItemCheckRect(HELE hEle, int item, out_ RECT *pRect); //��ȡ��ѡ��ť����
XC_API int  WINAPI XList_GetItemBindEleCount(HELE hEle, int item, int subItem);
XC_API BOOL WINAPI XList_GetItemBindEleInfo(HELE hEle, int item, int subItem, out_ itemBindEle_ *pInfo, int index);//��ȡ������Ϣ

XC_API void WINAPI XList_CancelSelectAll(HELE hEle); //ȡ��ѡ��������
XC_API void WINAPI XList_CancelSelect(HELE hEle, int index); //ȡ��ѡ��ָ����
XC_API BOOL WINAPI XList_DeleteItem(HELE hEle, int index);  //ɾ����
XC_API BOOL WINAPI XList_DeleteColumn(HELE hEle, int index);  //ɾ����
XC_API void WINAPI XList_DeleteAllItems(HELE hEle);  //ɾ��������
XC_API void WINAPI XList_DeleteAllColumns(HELE hEle);   //ɾ��������
XC_API void WINAPI XList_EnableGrid(HELE hEle, BOOL bGrid); //����������ʽ
XC_API int  WINAPI XList_HitTest(HELE hEle, POINT *pPt);  //�����������ĸ�����,-1û�����κ�����
XC_API BOOL WINAPI XList_HitTestEx(HELE hEle, POINT *pPt, out_ int *item, out_ int *sub); //�����������ĸ����ϼ�����,-1û�����κ�����
XC_API void WINAPI XList_ShowHeader(HELE hEle, BOOL bShow);//��ʾ�����б�ͷ

XC_API void WINAPI XList_SetUserDrawItem(HELE hEle, pFunList_DrawItem pFunDrawItem); //�����û��Ի��б���
XC_API void WINAPI XList_SetUserDrawItemHeader(HELE hEle, pFunListHeader_DrawItem pFunDrawItem); //�����û��Ի��б�ͷ��

XC_API void WINAPI XList_EnableCheckBox(HELE hEle, BOOL bEnable); //���ø�ѡ��
XC_API void WINAPI XList_EnableMultilineSelect(HELE hEle, BOOL bEnable);  //���ùرն���ѡ�� XEdit_EnableMultiLine
XC_API void WINAPI XLsit_EnableLineHighlight(HELE hEle, BOOL bEnable); //���û�ر��и�����ʾ

XC_API BOOL WINAPI XList_IsItemCheck(HELE hEle, int index); //�ж���ĸ�ѡ���Ƿ�ѡ
XC_API void WINAPI XList_SetItemCheck(HELE hEle, int index, BOOL bCheck); //������ĸ�ѡ��

//����ƶ�������ʾ

//˽�з���:
void List_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void List_AdjustHeader(HELE hEle);  //�����б�ͷ
void List_AdjustItem(HELE hEle);
void List_AdjustDragHeader(HELE hEle, POINT &pt, int index);

void List_DrawItemHeader(HELE hEle, HDRAW hDraw); //�����б�ͷ
void List_DrawHeader_BG(HELE hEle, HDRAW hDraw, RECT *pRect);   //�����б�ͷ����
void List_DrawHeader_Item(HELE hEle, HDRAW hDraw);  //�����б�ͷ��
void List_DrawHeader_Item_SYS(HELE hEle, HDRAW hDraw); //ϵͳ�����б���

void List_DrawList(HELE hEle, HDRAW hDraw);

void List_CancelSelectAll(HELE hEle); //ȡ��ѡ��������,�������¼�

BOOL List_MouseMoveHeader(HELE hEle, POINT *pPt);
BOOL List_LButtonDownHeader(HELE hEle, POINT *pPt);
BOOL List_LButtonUpHeader(HELE hEle, POINT *pPt);
BOOL List_MouseMoveDragHeaderEnd(HELE hEle);
void List_MouseLeaveHeader(HELE hEle);

BOOL List_MouseMove_View(HELE hEleView, POINT *pPt);
void List_LButtonDown(HELE hEle, POINT *pPt);

void List_MouseMoveDragBegin_View(HELE hEleView, POINT *pPt); //׼���϶�ѡ��
void List_MouseMoveDrag_View(HELE hEleView, POINT *pPt); //�϶�ѡ��
void List_MouseMoveDragUp(HELE hEle, int index1, int index2); //�����϶�
void List_MouseMoveDragDown(HELE hEle, int index1, int index2); //�����϶�

BOOL List_MouseMoveDragEnd_View(HELE hEleView); //����϶�����


//�ص�����:
void CALLBACK List_OnDestroy(HELE hEle);  //����
BOOL CALLBACK List_OnEleDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK List_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK List_OnEventMouseLeave(HELE hEle, HELE hEventEle); //����뿪
BOOL CALLBACK List_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnEventKillCapture(HELE hEle, HELE hEventEle);


BOOL CALLBACK List_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnMouseMove_View(HELE hEleView, UINT flags, POINT *pPt);
BOOL CALLBACK List_OnEventMouseLeave_View(HELE hEleView, HELE hEventEle); //����뿪
BOOL CALLBACK List_OnEventKillCapture_View(HELE hEleView, HELE hEventEle);  //ʧȥ��겶��

extern HELE  g_hList;
VOID CALLBACK List_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


