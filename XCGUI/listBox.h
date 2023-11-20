/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//�ַ����б��

struct listBox_item_
{
	HSTRING hString; //�ַ����б� wchar_t*
	int   imageID;   //�ַ�����Ӧͼ��ID

	BOOL  bCheck;    //��ѡ��

	void* userData; //�û�������
	HARRAY hArrayBindEle; //�󶨵�Ԫ�� itemBindEle_*
};


#define  XLISTBOX_CHECK_SIZE   13   //��ѡ����
#define  XLISTBOX_LEFT         3    //����߼��
#define  XLISTBOX_RIGHT        3    //��Ŀ�Ҽ��
struct listBox_
{
	scrollView_  scrollView; //�̳�
	//-------------
	HARRAY  hArrayListItem; //���б� listBox_item_*
	HXCGUI  hImageList;     //ͼ���б�

	int     height;       //�и�
	int     curSel;       //��ǰѡ�����
	int     maxTextWidth; //��е��ı�����
	BOOL    bAdjust;

	BOOL    bCheck; //��ѡ���Ƿ�����

	//����ƶ�������ʾ
	BOOL  bLineHighlight; //�Ƿ����ø�����ʾ
	int   mouseStayId;    //��ǰ���ͣ������

	COLORREF selectItemColor; //ѡ������ɫ 126,206,244
	COLORREF mouseStayColor;  //���ͣ������ɫ 192,232,250

	//----------------------
	pFunListBox_DrawItem  pDrawItem; //�û��Ի�
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
XC_API void WINAPI XListBox_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի��б����
#endif

//API:
XC_API HELE WINAPI XListBox_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API int  WINAPI XListBox_AddString(HELE hEle, wchar_t *pText, int imageId = -1);  //����һ���ַ������б�
XC_API BOOL WINAPI XListBox_InsertString(HELE hEle, int index, wchar_t *pText, int imageId = -1); //������
XC_API void WINAPI XListBox_EnableCheckBox(HELE hEle, BOOL bEnable); //���ø�ѡ��
XC_API void WINAPI XLsitBox_EnableLineHighlight(HELE hEle, BOOL bEnable);  //���û�ر��и�����ʾ


XC_API wchar_t* WINAPI XListBox_GetItemText(HELE hEle, int index);   //��ȡָ�����ı�
XC_API int  WINAPI XListBox_GetItemHeight(HELE hEle);              //��ȡ�и�
XC_API int  WINAPI XListBox_GetSelectItem(HELE hEle);              //��ȡѡ����
XC_API int  WINAPI XListBox_GetItemImage(HELE hEle, int index); //��ȡ��ͼ��ID
XC_API int  WINAPI XListBox_GetItemCount(HELE hEle); //��ȡ������
XC_API HXCGUI WINAPI XListBox_GetImageList(HELE hEle); //��ȡͼƬ�б�
XC_API BOOL WINAPI XListBox_GetItemRect(HELE hEle, in_ int index, out_ RECT *pRect);  //��ȡ������...
XC_API int  WINAPI XListBox_HitTest(HELE hEle, POINT *pPt);  //�����������ĸ�����,-1û�����κ�����
XC_API void* WINAPI XListBox_GetItemData(HELE hEle, int index); //��ȡ�������

XC_API void WINAPI XListBox_SetItemText(HELE hEle, int index, wchar_t *pText);  //����ָ�����ı�
XC_API void WINAPI XListBox_SetSelectItem(HELE hEle, int index);    //����ѡ����
XC_API void WINAPI XListBox_SetItemHeight(HELE hEle, int height);   //�����и�
XC_API void WINAPI XListBox_SetImageList(HELE hEle, HXCGUI hImageList); //����ͼ���б�
XC_API void WINAPI XListBox_SetItemImage(HELE hEle, int index, int imageId); //������ͼ��ID
XC_API void WINAPI XListBox_SetItemCheck(HELE hEle, int index, BOOL bCheck); //������ĸ�ѡ��
XC_API BOOL WINAPI XListBox_SetItemBindEle(HELE hEle, int index, itemBindEle_ *pInfo); //��Ԫ��
XC_API void WINAPI XListBox_SetItemData(HELE hEle, int index, void* data); //�����������

XC_API void WINAPI XListBox_SetSelectItemColor(HELE hEle, COLORREF color); //����ѡ������ɫ
XC_API void WINAPI XListBox_SetItemMouseStayColor(HELE hEle, COLORREF color);//�������ͣ����������ɫ

XC_API void WINAPI XListBox_DeleteItem(HELE hEle, int index);  //ɾ����
XC_API void WINAPI XListBox_DeleteAll(HELE hEle);  //ɾ��������
XC_API BOOL WINAPI XListBox_IsItemCheck(HELE hEle, int index);      //�ж���ĸ�ѡ���Ƿ�ѡ
XC_API void WINAPI XListBox_Adjust(HELE hEle);

//�Ի�:
XC_API void WINAPI XListBox_SetUserDrawItem(HELE hEle, pFunListBox_DrawItem pFunDrawItem); //�����û��Ի��б����

//˽�з���:
void ListBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void ListBox_MouseDown(HELE hEle, POINT *pPt);


//�ص�����
void CALLBACK ListBox_OnDestroy(HELE hEle);  //����
BOOL CALLBACK ListBox_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK ListBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListBox_OnEleMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ListBox_OnEventMouseLeave(HELE hEle, HELE hEventEle);