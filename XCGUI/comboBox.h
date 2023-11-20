/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//��Ͽ�
struct comboBox_
{
	edit_  edit; //�̳�
	//-------------
	HWINDOW hPopupWnd; //��������ָ��
	HARRAY  hArrayStr;  //�ַ����б� new wchar_t*
	HARRAY  hArrayData; //�û�������
	BOOL    bEdit;      //�ɱ༭����
	int     heights;    //�ܸ߶�
	int     height;     //���
	int     curSel;     //��ǰѡ�������� ...

	DWORD   listEndTime; //�����б����ر�ʱ��

	//������ť:
	struct
	{
		RECT rcButton;//������ť
		int  state;   //״̬
	}button_;

	//��ͼ
	HIMAGE hImage_stay; //���ͣ��
	HIMAGE hImage_down; //��갴��
};

//API:
XC_API HELE WINAPI XComboBox_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API BOOL WINAPI XComboBox_AddString(HELE hEle, wchar_t *pText, void* data = 0);  //����һ���ַ�������Ͽ�

XC_API void WINAPI XComboBox_DeleteItem(HELE hEle, int index);//ɾ����
XC_API void WINAPI XComboBox_DeleteItemAll(HELE hEle);  //ɾ��������
XC_API void WINAPI XComboBox_EnableEdit(HELE hEle, BOOL bEdit);  //�����༭����

XC_API void WINAPI XComboBox_SetSelectItem(HELE hEle, int index);  //����ѡ����
XC_API void WINAPI XComboBox_SetText(HELE hEle, wchar_t *pText);     //���ñ༭������
XC_API void WINAPI XComboBox_SetItemHeight(HELE hEle, int height); //���������б����
XC_API void WINAPI XComboBox_SetListHeight(HELE hEle, int height);   //���������б�߶�
XC_API void WINAPI XComboBox_SetButtonWidth(HELE hEle, int width); //����������ť���
XC_API void WINAPI XComboBox_SetItemData(HELE hEle, int index, void* data);

XC_API int  WINAPI XComboBox_GetButtonWidth(HELE hEle); //��ȡ������ť���
XC_API void WINAPI XComboBox_GetText(HELE hEle, wchar_t *pOut, int len);  //��ȡ�༭���ı�
XC_API int  WINAPI XComboBox_GetItemHeight(HELE hEle);  //��ȡ���
XC_API int  WINAPI XComboBox_GetListHeight(HELE hEle); //��ȡ�����б�߶�
XC_API wchar_t* WINAPI XComboBox_GetItemText(HELE hEle, int index); //��ȡ�����б��ı�
XC_API int  WINAPI XComboBox_GetSelectItem(HELE hEle);  //��ȡ��ǰѡ��������
XC_API void* WINAPI XComboBox_GetItemData(HELE hEle, int index);
XC_API int WINAPI XComboBox_GetItemCount(HELE hEle); //��ȡ������

XC_API void WINAPI XComboBox_PopupDropDownList(HELE hEle); //���������б�

//��ͼ
XC_API void WINAPI XComboBox_SetImageLeave(HELE hEle, HIMAGE hImage = NULL); //����뿪
XC_API void WINAPI XComboBox_SetImageStay(HELE hEle, HIMAGE hImage = NULL); //���ͣ��
XC_API void WINAPI XComboBox_SetImageDown(HELE hEle, HIMAGE hImage = NULL); //��갴��

//˽�з���:
void ComboBox_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void ComboBox_PopupDropDownList(HELE hEle); //���������б�
void ComboBox_DestroyPopupWnd(HELE hEle);  //���ٵ�������
void ComboBox_DrawBk(HELE hEle, HDRAW hDraw); //���Ʊ���
void ComboBox_Adjust(HELE hEle);

//�ص�����:
void CALLBACK ComboBox_OnDestroy(HELE hEle);  //����
BOOL CALLBACK ComboBox_OnDraw(HELE hEle, HDRAW hDraw);

BOOL CALLBACK ComboBox_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnEventMouseLeave(HELE hEle, HELE hEventEle);
BOOL CALLBACK ComboBox_OnEventKillFocus(HELE hEle, HELE hEventEle);

BOOL CALLBACK ComboBox_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK ComboBox_OnEventSetFocus(HELE hEle, HELE hEventEle);
BOOL CALLBACK ComboBox_OnEventSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK ComboBox_OnEventMouseWheel(HELE hEle, HELE hEventEle, UINT flags, POINT *pPt);

BOOL CALLBACK ComboBox_OnDrawButton(HELE hEle, HDRAW hDraw); //����������ť

