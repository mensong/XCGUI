/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


#ifdef	XCGUI_PLUS  //C++��֧��


void WINAPI XEle_RegisterEventEx(HELE hEle, int type, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	if (XE_DESTROY == type) //Ԫ�����ٺ���
	{
		eleDestroy_ *pObj = (eleDestroy_*)malloc(sizeof(eleDestroy_));
		pObj->pFun = (pFunEventDestroy)pCallBackFun;
		if (NULL == pEle->pDestroyList)
		{
			pEle->pDestroyList = pObj;
			pObj->pNext = NULL;
		}
		else
		{
			pObj->pNext = pEle->pDestroyList;
			pEle->pDestroyList = pObj;
		}
		pObj->pClass_Fun_Info = pClass_Fun_Info;
		return;
	}

	//------���¼�����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pEle->hArray_event);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (type == ((eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)malloc(sizeof(eleMsgOrEvent_Header_));
		pHeader->Event = type;

		switch (type)
		{
		case XE_BNCLICK:             pHeader->pFunEventConv = Ele_ConvEventBtnClick; break;
		case XE_MOUSESTAY:           pHeader->pFunEventConv = Ele_ConvEventMouseStay; break;
		case XE_MOUSELEAVE:          pHeader->pFunEventConv = Ele_ConvEventMouseLeave; break;
		case XE_SETFOCUS:            pHeader->pFunEventConv = Ele_ConvEventSetFocus; break;
		case XE_KILLFOCUS:           pHeader->pFunEventConv = Ele_ConvEventKillFocus; break;
		case XE_KEYDOWN:             pHeader->pFunEventConv = Ele_ConvEventKeyDown; break;
		case XE_CHAR:               pHeader->pFunEventConv = Ele_ConvEventChar; break;
		case XE_HSCROLL:             pHeader->pFunEventConv = Ele_ConvEventHScroll; break;
		case XE_VSCROLL:             pHeader->pFunEventConv = Ele_ConvEventVScroll; break;
		case XE_HSCROLLVIEW:         pHeader->pFunEventConv = Ele_ConvEventHScrollView; break;
		case XE_VSCROLLVIEW:         pHeader->pFunEventConv = Ele_ConvEventVScrollView; break;
		case XE_SETCAPTURE:          pHeader->pFunEventConv = Ele_ConvEventSetCapture; break;
		case XE_KILLCAPTURE:         pHeader->pFunEventConv = Ele_ConvEventKillCapture; break;
		case XE_MOUSEWHEEL:          pHeader->pFunEventConv = Ele_ConvEventMouseWheel; break;
		case XE_MENUSELECT:          pHeader->pFunEventConv = Ele_ConvEventMenuSelect; break;
		case XE_MENUEXIT:            pHeader->pFunEventConv = Ele_ConvEventMenuExit; break;

		case XE_LIST_SELECT:         pHeader->pFunEventConv = Ele_ConvEventListSelect; break;
		case XE_LIST_HEADER_CLICK:   pHeader->pFunEventConv = Ele_ConvEventListHeaderClick; break;
		case XE_LIST_HEADER_CHANGE:  pHeader->pFunEventConv = Ele_ConvEventListHeaderChange; break;

		case XE_TREE_SELECT:         pHeader->pFunEventConv = Ele_ConvEventTreeSelect; break;
		case XE_TREE_EXPAND:         pHeader->pFunEventConv = Ele_ConvEventTreeExpand; break;

		case XE_COMBOBOX_SELECT:     pHeader->pFunEventConv = Ele_ConvEventComboBoxSelect; break;
		case XE_COMBOBOX_POPUP_LIST: pHeader->pFunEventConv = Ele_ConvEventComboBoxPopupList; break;
		case XE_COMBOBOX_EXIT_LIST: pHeader->pFunEventConv = Ele_ConvEventComboBoxExitList; break;

		case XE_PPAGE_SELECT:        pHeader->pFunEventConv = Ele_ConvEventPPageSelect; break;
		case XE_SLIDER_CHANGE:       pHeader->pFunEventConv = Ele_ConvEventSliderChange; break;

		case XE_MONTHCAL_CHANGE:     pHeader->pFunEventConv = Ele_ConvEventMonthChange; break;
		case XE_DATETIME_CHANGE:     pHeader->pFunEventConv = Ele_ConvEventDateTimeChange; break;
		case XE_DATETIME_POPUP_MONTHCAL: pHeader->pFunEventConv = Ele_ConvEventDateTimePopupMonthCal; break;
		case XE_DATETIME_EXIT_MONTHCAL:  pHeader->pFunEventConv = Ele_ConvEventDateTimeExitMonthCal; break;

		case XE_SETFONT:             pHeader->pFunEventConv = Ele_ConvEventSetFont; break;
		case XE_SHOW:                pHeader->pFunEventConv = Ele_ConvEventShow; break;
		case XE_SIZE:                pHeader->pFunEventConv = Ele_ConvEventSize; break;
		case XE_LISTBOX_SELECT:      pHeader->pFunEventConv = Ele_ConvEventListBoxSelect; break;
		case XE_PGRID_SELCHANGE:     pHeader->pFunEventConv = Ele_ConvEventPGridSelChange; break;
		case XE_PGRID_VALUECHANGE:   pHeader->pFunEventConv = Ele_ConvEventPGridValueChange; break;
		case XE_LISTVIEW_SELECT:     pHeader->pFunEventConv = Ele_ConvEventListViewSelect; break;
		case XE_LISTVIEW_EXPAND:     pHeader->pFunEventConv = Ele_ConvEventListViewExpand; break;
		case XE_LISTVIEW_DRAG_INSERT: pHeader->pFunEventConv = Ele_ConvEventListViewDragInsert; break;

		case XE_PANE_LOACK:          pHeader->pFunEventConv = Ele_ConvEventPaneLock; break;
		case XE_PANE_DOCK:           pHeader->pFunEventConv = Ele_ConvEventPaneDock; break;
		case XE_PANE_FLOAT:          pHeader->pFunEventConv = Ele_ConvEventPaneFloat; break;

		case XE_EDIT_CHANGE:         pHeader->pFunEventConv = Ele_ConvEventEditChange; break;
		case XE_COMBOBOX_SELECT_ING: pHeader->pFunEventConv = Ele_ConvEventComboBoxChanging; break;
		case XE_LISTBOX_SELECT_ING:  pHeader->pFunEventConv = Ele_ConvEventListBoxChanging; break;
		case XE_TREE_SELECT_ING:     pHeader->pFunEventConv = Ele_ConvEventTreeChanging; break;
		default:
			XTRACE("XCGUI_RegEleEvent() ����:δ֪�¼����� \n");
			MessageBox(NULL, L"API:XCGUI_RegEleEvent(),����[type]δ֪���¼�����", L"�Ųʽ����-������ʾ", 0);
			pHeader->pFunEventConv = NULL;
			return;
		}

		eleMsgOrEvent_ *pEvent = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pEvent->pFun = pCallBackFun;
		pEvent->pNext = NULL;
		pEvent->pClass_Fun_Info = pClass_Fun_Info;

		pHeader->pList = pEvent;

		//TODO:����
		XArray_Add(pEle->hArray_event, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		eleMsgOrEvent_ *pEvent = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pEvent->pFun = pCallBackFun;
		pEvent->pNext = NULL;
		pEvent->pClass_Fun_Info = pClass_Fun_Info;

		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pEvent;
		}
		else  //���뵽��λ
		{
			pEvent->pNext = pHeader->pList;
			pHeader->pList = pEvent;
		}
	}
}

void WINAPI XEle_RegisterMessageEx(HELE hEle, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	//---����Ϣ����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pEle->hArray_msg);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (message == ((eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_msg, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)malloc(sizeof(eleMsgOrEvent_Header_));
		pHeader->message = message;

		switch (message)
		{
		case XM_PAINT:        pHeader->pFunMsgConv = Ele_ConvMsgPaint; break;
		case XM_MOUSEMOVE:    pHeader->pFunMsgConv = Ele_ConvMsgMouseMove; break;
		case XM_LBUTTONDOWN:  pHeader->pFunMsgConv = Ele_ConvMsgLButtonDown; break;
		case XM_LBUTTONUP:    pHeader->pFunMsgConv = Ele_ConvMsgLButtonUp; break;
		case XM_RBUTTONDOWN:  pHeader->pFunMsgConv = Ele_ConvMsgRButtonDown; break;
		case XM_RBUTTONUP:    pHeader->pFunMsgConv = Ele_ConvMsgRButtonUp; break;
		case XM_MOUSECLICK:   pHeader->pFunMsgConv = Ele_ConvMsgMouseClick; break;
		case XM_MOUSEDBCLICK: pHeader->pFunMsgConv = Ele_ConvMsgMouseDBClick; break;
		case XM_TIMER:        pHeader->pFunMsgConv = Ele_ConvMsgTimerEx; break;
		default:
			XTRACE("XCGUI_RegEleMessage() ����:δ֪��Ϣ����\n");
			MessageBox(NULL, L"API:XCGUI_RegEleMessage(),����[message]δ֪����Ϣ����", L"�Ųʽ����-������ʾ", 0);
			pHeader->pFunMsgConv = NULL;
			return;
		}

		eleMsgOrEvent_ *pMsg = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;

		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pEle->hArray_msg, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		eleMsgOrEvent_ *pMsg = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pMsg->pFun = pCallBackFun;
		pMsg->pNext = NULL;
		pMsg->pClass_Fun_Info = pClass_Fun_Info;

		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_msg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XEle_RegisterMsgProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info)    //ע��Ԫ����Ϣ�������
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	eleMsgProc_ *pNew = (eleMsgProc_*)malloc(sizeof(eleMsgProc_));
	pNew->pFun = pCallBackFun;
	pNew->pClass_Fun_Info = pClass_Fun_Info;
	if (NULL == pEle->pMsgProcList)
	{
		pEle->pMsgProcList = pNew;
		pNew->pNext = NULL;
	}
	else
	{
		pNew->pNext = pEle->pMsgProcList;
		pEle->pMsgProcList = pNew;
	}
}

void WINAPI XEle_RegisterEventProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info) //ע���¼����ع��˺���
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	eleEventProc_ *pNew = (eleEventProc_*)malloc(sizeof(eleEventProc_));
	pNew->pFun = pCallBackFun;
	pNew->pClass_Fun_Info = pClass_Fun_Info;
	if (NULL == pEle->pMsgProcList)
	{
		pEle->pEventProcList = pNew;
	}
	else
	{
		pNew->pNext = pEle->pEventProcList;
		pEle->pEventProcList = pNew;
	}
}

#endif

////////////////////////////////////////////////////////
HELE WINAPI XEle_Create(int x, int y, int cx, int cy, HXCGUI hParent) //����
{
	ele_ *pEle = (ele_*)malloc(sizeof(ele_));
	if (pEle)
	{
		memset(pEle, 0, sizeof(ele_));
		Ele_Init((HELE)pEle, x, y, cx, cy, XC_ELE, hParent);

		if (g_fun_create_element && FALSE == g_fun_create_element((HELE)pEle))
		{
			MsgError(XC_ERROR_0012);
			return FALSE;
		}

		return (HELE)pEle;
	}
	return NULL;
}

BOOL WINAPI XEle_Destroy(HELE hEle)  //����
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_* pEle = (ele_*)hEle;

	if (FALSE == pEle->bDestroy)
	{
		pEle->bDestroy = TRUE;
	}
	else
	{
		MessageBox(NULL, L"��API:XEle_Destroy()�д���,�ظ�����Ԫ��", L"�Ųʽ����-������ʾ!", 0);
		exit(0);
		return FALSE; //�ظ�����
	}

	//����˳��,������������, ��������Ԫ������������,

	//1.����Ԫ�����ٺ����б�,�ͷż̳�Ԫ����չ����----------------------
	eleDestroy_  *pObjDestroy = pEle->pDestroyList;
	eleDestroy_  *pDelD = NULL;
	while (pObjDestroy)
	{
		if (pObjDestroy->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pObjDestroy->pClass_Fun_Info;
			((pFunClassEventMsg)pObjDestroy->pFun)(&event_, xc_fun_v_e);
			free(pObjDestroy->pClass_Fun_Info);
		}
		else
		{
			((pFunEventDestroy)pObjDestroy->pFun)(hEle);  //��������,����Ԫ�����ٻص�����
		}

		pDelD = pObjDestroy;
		pObjDestroy = pObjDestroy->pNext;
		free(pDelD);
	}
	pEle->pDestroyList = NULL;

	//2.������Ԫ�� ,��Ԫ������ʱ���Զ��Ӹ����Ƴ�-------------------
	int count = Array_GetCount(pEle->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		XEle_Destroy((HELE)Array_GetAtEle(pEle->hArrayEle, 0));  //������Ԫ��
	}

	//����Դ���������Ƴ�
	Resource_RemoveEle(hEle);

	XArray_Destroy(pEle->hArrayEle);
	pEle->hArrayEle = NULL;

	//3.�Ӹ����Ƴ�
	if (pEle->pParentEle)//�Ӹ�Ԫ�����Ƴ�
	{
		XArray_Delete(pEle->pParentEle->hArrayEle, hEle);
	}
	else //�Ӵ����Ƴ�
	{
		if (pEle->pWindow)
		{
			if (FALSE == pEle->bClient)
				XArray_Delete(pEle->pWindow->hArrayEleNC, hEle);
			else
				XArray_Delete(pEle->pWindow->hArrayEle, hEle);
		}
	}

	//4.�����봰�ڹ���------------
	if (pEle->pWindow)
	{
		if (hEle == (HELE)pEle->pWindow->pMouseTop)
			pEle->pWindow->pMouseTop = NULL;

		if (hEle == (HELE)pEle->pWindow->pFocus || hEle == (HELE)pEle->pWindow->pOldFocus)
		{
			pEle->pWindow->pFocus = NULL;
			pEle->pWindow->pOldFocus = NULL;
		}

		if (hEle == (HELE)pEle->pWindow->pCapture)
			pEle->pWindow->pCapture = NULL;

		//�������
		if (hEle == (HELE)pEle->pWindow->hCaretEle)
			XWnd_DestroyCaret((HWINDOW)pEle->pWindow);

		pEle->pWindow = NULL;
	}

	//5.�����븸Ԫ�ع���
	if (pEle->pParentEle)
	{
		if (hEle == (HELE)pEle->pParentEle->pMouseTop)
			pEle->pParentEle->pMouseTop = NULL;

		pEle->pParentEle = NULL;
	}

	//TODO:������,�˵���,��״̬��,���Ƴ�

	//6..�ͷ���������--------------------------------

	//��Ϣ�����
	int Array_msg_count = Array_GetCount(pEle->hArray_msg);
	for (int i = 0; i < Array_msg_count; i++)
	{
		eleMsgOrEvent_Header_ *pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_msg, i);
		eleMsgOrEvent_ *pMsg = pHeader->pList;
		eleMsgOrEvent_ *pDel = NULL;
		while (pMsg)
		{
			pDel = pMsg;
			pMsg = pMsg->pNext;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
			if (pDel->pClass_Fun_Info) free(pDel->pClass_Fun_Info);
#endif
			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pEle->hArray_msg);

	//�¼������
	int Array_event_count = Array_GetCount(pEle->hArray_event);
	for (int i = 0; i < Array_event_count; i++)
	{
		eleMsgOrEvent_Header_ *pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event, i);
		eleMsgOrEvent_ *pEvent = pHeader->pList;
		eleMsgOrEvent_ *pDel = NULL;
		while (pEvent)
		{
			pDel = pEvent;
			pEvent = pEvent->pNext;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
			if (pDel->pClass_Fun_Info) free(pDel->pClass_Fun_Info);
#endif

			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pEle->hArray_event);

	//Ԫ����Ϣ��������б�
	eleMsgProc_ *pProc = pEle->pMsgProcList;
	void *pDel = NULL;
	while (pProc)
	{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pProc->pClass_Fun_Info) free(pProc->pClass_Fun_Info);
#endif
		pDel = pProc;
		pProc = pProc->pNext;
		free(pDel);
	}
	pEle->pMsgProcList = NULL;

	//Ԫ���¼���������б�
	eleEventProc_ *pEventProc = pEle->pEventProcList;
	while (pEventProc)
	{
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		if (pEventProc->pClass_Fun_Info) free(pEventProc->pClass_Fun_Info);
#endif
		pDel = pEventProc;
		pEventProc = pEventProc->pNext;
		free(pDel);
	}
	pEle->pEventProcList = NULL;

	if (pEle->hToolTipsStr)
	{
		XStr_Destroy(pEle->hToolTipsStr);
		pEle->hToolTipsStr = NULL;
	}
	if (pEle->hString_Style_Class)
		XStr_Destroy(pEle->hString_Style_Class);


	object_type_  *pNode = pEle->object.pTypeList;
	object_type_  *pDelNode = NULL;
	while (pNode)
	{
		pDelNode = pNode;
		pNode = pNode->pNext;
		free(pDelNode);
	}

	if (pEle->hFontX)  XFont_Destroy(pEle->hFontX);

	free(hEle);
	return TRUE;
}

void Ele_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent) //��ʼ��ע��
{
	((object_*)hEle)->type = XC_ELE;
	AddTypeDebug(hEle, XC_ELE);

	Resource_AddEle(hEle);

	ele_ *pEle = (ele_*)hEle;
	pEle->hArrayEle = XArray_Create();
	pEle->rect.left = x;
	pEle->rect.top = y;
	pEle->rect.right = x + cx;
	pEle->rect.bottom = y + cy;
	pEle->bShow = TRUE;
	pEle->bEnable = TRUE;
	pEle->bDrawFocus = TRUE;
	pEle->eleType = eleType;
	pEle->elePt.x = x;
	pEle->elePt.y = y;
	pEle->hToolTipsStr = XStr_Create();
	pEle->bkColor = RGB(255, 255, 255);
	pEle->borderColor = RGB(128, 128, 128);
	pEle->bBorder = TRUE;
	pEle->hFontX = NULL;//(HFONT)GetStockObject(DEFAULT_GUI_FONT);
	pEle->bEnableFocus = FALSE;

	//AddResources(pEle,XC_ELE); //��ӵ���Դ������
	//AddResourcesElement((HWINDOW)pEle->pWindow,hEle);

	if (hParent)
	{
		int type = ((object_*)hParent)->type;
		if (XC_ELE == type)
		{
			if (XC_SCROLLVIEW_VIEW != eleType &&  XC_IsSViewExtend((HELE)hParent))
			{
				XEle_AddEle(((scrollView_*)hParent)->hView, hEle);
			}
			else
			{
				XEle_AddEle((HELE)hParent, hEle);
			}

		}
		else if (XC_WINDOW == type)
		{
			XWnd_AddEle((HWINDOW)hParent, hEle);
		}
		else
		{
#ifdef _DEBUG
			wchar_t error[256] = { 0 };
			switch (eleType)
			{
			case XC_WINDOW:
				wsprintf(error, L"����[Window]ʧ��,[hParent]����!");
				break;
			case XC_COMBOBOXWINDOW:
				wsprintf(error, L"ComboBox����ѡ���б����,[hParent]����!");
				break;
			case XC_POPUPMENUWINDOW:
				wsprintf(error, L"PopupMenu����,[hParent]����!");
				break;
			case XC_POPUPMENUCHILDWINDOW:
				wsprintf(error, L"PopupMenu����2,[hParent]����!");
				break;
			case XC_MODALWINDOW:
				wsprintf(error, L"ModalWindow����,[hParent]����!");
				break;
			case XC_MSGBOXWINDOW:
				wsprintf(error, L"XMessageBox����,[hParent]����!");
				break;
			case XC_DATETIMEWINDOW:
				wsprintf(error, L"DateTimeԪ�ص���ѡ�񴰿ڴ���,[hParent]����!");
				break;
			case XC_ELE:
				wsprintf(error, L"����[Element]����,[hParent]����!");
				break;
			case XC_BUTTON:
				wsprintf(error, L"����[Button]����,[hParent]����!");
				break;
			case XC_RADIO:
				wsprintf(error, L"����[Radio]����,[hParent]����!");
				break;
			case XC_CHECK:
				wsprintf(error, L"����[Check]����,[hParent]����!");
				break;
			case XC_EDIT:
				wsprintf(error, L"����[Edit]����,[hParent]����!");
				break;
			case XC_COMBOBOX:
				wsprintf(error, L"����[ComboBox]����,[hParent]����!");
				break;
			case XC_SCROLLBAR:
				wsprintf(error, L"����[ScrollBar]����,[hParent]����!");
				break;
			case XC_SCROLLVIEW:
				wsprintf(error, L"����[ScrollView]����,[hParent]����!");
				break;
			case XC_LIST:
				wsprintf(error, L"����[List]����,[hParent]����!");
				break;
			case XC_LISTBOX:
				wsprintf(error, L"����[ListBox]����,[hParent]����!");
				break;
			case XC_TREE:
				wsprintf(error, L"����[Tree]����,[hParent]����!");
				break;
			case XC_MENUBAR:
				wsprintf(error, L"����[MenuBar]����,[hParent]����!");
				break;
			case XC_PROPERTYPAGE:
				wsprintf(error, L"����[PropertyPage]����,[hParent]����!");
				break;
			case XC_SLIDERBAR:
				wsprintf(error, L"����[Slider]����,[hParent]����!");
				break;
			case XC_PROGRESSBAR:
				wsprintf(error, L"����[ProgressBar]����,[hParent]����!");
				break;
			case XC_TOOLBAR:
				wsprintf(error, L"����[ToolBar]����,[hParent]����!");
				break;
			case XC_STATIC:
				wsprintf(error, L"����[Static]����,[hParent]����!");
				break;
			case XC_GROUPBOX:
				wsprintf(error, L"����[GroupBox]����,[hParent]����!");
				break;
			case XC_MENUBAR_BUTTON:
				wsprintf(error, L"MenuBarԪ���ϰ�ť����,[hParent]����!");
				break;
			case XC_PICTURE:
				wsprintf(error, L"����[Picture]����,[hParent]����!");
				break;
			case XC_MONTHCAL:
				wsprintf(error, L"����[MonthCal]����,[hParent]����!");
				break;
			case XC_DATETIME:
				wsprintf(error, L"����[DateTime]����,[hParent]����!");
				break;
			default:
				wsprintf(error, L"����[UIԪ�ش���,δ֪Ԫ������]����,[hParent]����!");
				break;
			}
			MessageBox(NULL, error, L"�Ųʽ���������ʾ", MB_OK);
			exit(0);
#endif
			return;
		}
	}

	//------------------����Ϣ�������
	pEle->hArray_msg = XArray_Create();
	pEle->hArray_event = XArray_Create();

	//------------------
	XEle_RegisterMsgProc(hEle, Ele_WindowProc);
	XEle_RegisterEventProc(hEle, Ele_EventProc);

	//ע�ắ����Ϣ������
	XEle_RegisterMessage(hEle, XM_PAINT, Ele_OnDraw);
	XEle_RegisterMessage(hEle, XM_MOUSEMOVE, Ele_OnMouseMove);

	XEle_RegisterMessage(hEle, XM_MOUSECLICK, Ele_OnMouseClick);
	XEle_RegisterMessage(hEle, XM_MOUSEDBCLICK, Ele_OnMouseDBClick);

	XEle_RegisterMessage(hEle, XM_LBUTTONDOWN, Ele_OnLButtonDown);
	XEle_RegisterMessage(hEle, XM_LBUTTONUP, Ele_OnLButtonUp);

	XEle_RegisterMessage(hEle, XM_RBUTTONDOWN, Ele_OnRButtonDown);
	XEle_RegisterMessage(hEle, XM_RBUTTONUP, Ele_OnRButtonUp);

	XEle_RegisterEvent(hEle, XE_MOUSESTAY, Ele_OnEventMouseSay);
	XEle_RegisterEvent(hEle, XE_MOUSELEAVE, Ele_OnEventMouseLeave);
}

void WINAPI XEle_RegisterMessage(HELE hEle, int message, void *pFun)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	//---����Ϣ����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pEle->hArray_msg);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (message == ((eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_msg, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)malloc(sizeof(eleMsgOrEvent_Header_));
		pHeader->message = message;

		switch (message)
		{
		case XM_PAINT:        pHeader->pFunMsgConv = Ele_ConvMsgPaint; break;
		case XM_MOUSEMOVE:    pHeader->pFunMsgConv = Ele_ConvMsgMouseMove; break;
		case XM_LBUTTONDOWN:  pHeader->pFunMsgConv = Ele_ConvMsgLButtonDown; break;
		case XM_LBUTTONUP:    pHeader->pFunMsgConv = Ele_ConvMsgLButtonUp; break;
		case XM_RBUTTONDOWN:  pHeader->pFunMsgConv = Ele_ConvMsgRButtonDown; break;
		case XM_RBUTTONUP:    pHeader->pFunMsgConv = Ele_ConvMsgRButtonUp; break;
		case XM_MOUSECLICK:   pHeader->pFunMsgConv = Ele_ConvMsgMouseClick; break;
		case XM_MOUSEDBCLICK: pHeader->pFunMsgConv = Ele_ConvMsgMouseDBClick; break;
		case XM_TIMER:        pHeader->pFunMsgConv = Ele_ConvMsgTimerEx; break;
		default:
			XTRACE("XEle_RegisterMessage() ����:δ֪��Ϣ����\n");
			MessageBox(NULL, L"API:XEle_RegisterMessage(),����[message]δ֪����Ϣ����", L"�Ųʽ����-������ʾ", 0);
			pHeader->pFunMsgConv = NULL;
			return;
		}

		eleMsgOrEvent_ *pMsg = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pEle->hArray_msg, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		eleMsgOrEvent_ *pMsg = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_msg, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XEle_RegisterEvent(HELE hEle, int type, void *pFun)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	if (XE_DESTROY == type) //Ԫ�����ٺ���
	{
		eleDestroy_ *pObj = (eleDestroy_*)malloc(sizeof(eleDestroy_));
		pObj->pFun = (pFunEventDestroy)pFun;
		if (NULL == pEle->pDestroyList)
		{
			pEle->pDestroyList = pObj;
			pObj->pNext = NULL;
		}
		else
		{
			pObj->pNext = pEle->pDestroyList;
			pEle->pDestroyList = pObj;
		}
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pObj->pClass_Fun_Info = NULL;
#endif
		return;
	}

	//------���¼�����
	BOOL bResult = FALSE;
	int index = -1; //����λ��
	int count = Array_GetCount(pEle->hArray_event);
	if (0 == count) //��Ҫ��Ϣͷ
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (type == ((eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event, i))->message)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //��Ҫ��Ϣͷ
	{
		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)malloc(sizeof(eleMsgOrEvent_Header_));
		pHeader->Event = type;

		switch (type)
		{
		case XE_BNCLICK:             pHeader->pFunEventConv = Ele_ConvEventBtnClick; break;
		case XE_MOUSESTAY:           pHeader->pFunEventConv = Ele_ConvEventMouseStay; break;
		case XE_MOUSELEAVE:          pHeader->pFunEventConv = Ele_ConvEventMouseLeave; break;
		case XE_SETFOCUS:            pHeader->pFunEventConv = Ele_ConvEventSetFocus; break;
		case XE_KILLFOCUS:           pHeader->pFunEventConv = Ele_ConvEventKillFocus; break;
		case XE_KEYDOWN:             pHeader->pFunEventConv = Ele_ConvEventKeyDown; break;
		case XE_CHAR:               pHeader->pFunEventConv = Ele_ConvEventChar; break;
		case XE_HSCROLL:             pHeader->pFunEventConv = Ele_ConvEventHScroll; break;
		case XE_VSCROLL:             pHeader->pFunEventConv = Ele_ConvEventVScroll; break;
		case XE_HSCROLLVIEW:         pHeader->pFunEventConv = Ele_ConvEventHScrollView; break;
		case XE_VSCROLLVIEW:         pHeader->pFunEventConv = Ele_ConvEventVScrollView; break;
		case XE_SETCAPTURE:          pHeader->pFunEventConv = Ele_ConvEventSetCapture; break;
		case XE_KILLCAPTURE:         pHeader->pFunEventConv = Ele_ConvEventKillCapture; break;
		case XE_MOUSEWHEEL:          pHeader->pFunEventConv = Ele_ConvEventMouseWheel; break;
		case XE_MENUSELECT:          pHeader->pFunEventConv = Ele_ConvEventMenuSelect; break;
		case XE_MENUEXIT:            pHeader->pFunEventConv = Ele_ConvEventMenuExit; break;

		case XE_LIST_SELECT:         pHeader->pFunEventConv = Ele_ConvEventListSelect; break;
		case XE_LIST_HEADER_CLICK:   pHeader->pFunEventConv = Ele_ConvEventListHeaderClick; break;
		case XE_LIST_HEADER_CHANGE:  pHeader->pFunEventConv = Ele_ConvEventListHeaderChange; break;

		case XE_TREE_SELECT:         pHeader->pFunEventConv = Ele_ConvEventTreeSelect; break;
		case XE_TREE_EXPAND:         pHeader->pFunEventConv = Ele_ConvEventTreeExpand; break;
		case XE_COMBOBOX_SELECT:     pHeader->pFunEventConv = Ele_ConvEventComboBoxSelect; break;
		case XE_COMBOBOX_POPUP_LIST: pHeader->pFunEventConv = Ele_ConvEventComboBoxPopupList; break;
		case XE_COMBOBOX_EXIT_LIST:  pHeader->pFunEventConv = Ele_ConvEventComboBoxExitList; break;

		case XE_PPAGE_SELECT:        pHeader->pFunEventConv = Ele_ConvEventPPageSelect; break;
		case XE_SLIDER_CHANGE:       pHeader->pFunEventConv = Ele_ConvEventSliderChange; break;

		case XE_MONTHCAL_CHANGE:     pHeader->pFunEventConv = Ele_ConvEventMonthChange; break;
		case XE_DATETIME_CHANGE:     pHeader->pFunEventConv = Ele_ConvEventDateTimeChange; break;
		case XE_DATETIME_POPUP_MONTHCAL: pHeader->pFunEventConv = Ele_ConvEventDateTimePopupMonthCal; break;
		case XE_DATETIME_EXIT_MONTHCAL:  pHeader->pFunEventConv = Ele_ConvEventDateTimeExitMonthCal; break;

		case XE_SETFONT:             pHeader->pFunEventConv = Ele_ConvEventSetFont; break;
		case XE_SHOW:                pHeader->pFunEventConv = Ele_ConvEventShow; break;
		case XE_SIZE:                pHeader->pFunEventConv = Ele_ConvEventSize; break;
		case XE_LISTBOX_SELECT:      pHeader->pFunEventConv = Ele_ConvEventListBoxSelect; break;
		case XE_PGRID_SELCHANGE:     pHeader->pFunEventConv = Ele_ConvEventPGridSelChange; break;
		case XE_PGRID_VALUECHANGE:   pHeader->pFunEventConv = Ele_ConvEventPGridValueChange; break;
		case XE_LISTVIEW_SELECT:     pHeader->pFunEventConv = Ele_ConvEventListViewSelect; break;
		case XE_LISTVIEW_EXPAND:     pHeader->pFunEventConv = Ele_ConvEventListViewExpand; break;
		case XE_LISTVIEW_DRAG_INSERT: pHeader->pFunEventConv = Ele_ConvEventListViewDragInsert; break;

		case XE_PANE_LOACK:          pHeader->pFunEventConv = Ele_ConvEventPaneLock; break;
		case XE_PANE_DOCK:           pHeader->pFunEventConv = Ele_ConvEventPaneDock; break;
		case XE_PANE_FLOAT:          pHeader->pFunEventConv = Ele_ConvEventPaneFloat; break;

		case XE_EDIT_CHANGE:         pHeader->pFunEventConv = Ele_ConvEventEditChange; break;
		case XE_COMBOBOX_SELECT_ING: pHeader->pFunEventConv = Ele_ConvEventComboBoxChanging; break;
		case XE_LISTBOX_SELECT_ING:  pHeader->pFunEventConv = Ele_ConvEventListBoxChanging; break;
		case XE_TREE_SELECT_ING:     pHeader->pFunEventConv = Ele_ConvEventTreeChanging; break;
		default:
			pHeader->pFunEventConv = NULL;
			XTRACE("XEle_RegisterEvent() ����:δ֪�¼�����. \n");
			MessageBox(NULL, L"API:XEle_RegisterEvent() ����[type]δ֪���¼�����.", L"�Ųʽ������ʾ", 0);
			exit(0);
			return;
		}

		eleMsgOrEvent_ *pMsg = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		pHeader->pList = pMsg;

		//TODO:����
		XArray_Add(pEle->hArray_event, pHeader);

	}
	else //����Ҫ��Ϣͷ
	{
		eleMsgOrEvent_ *pMsg = (eleMsgOrEvent_*)malloc(sizeof(eleMsgOrEvent_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
		pMsg->pClass_Fun_Info = NULL;
#endif
		eleMsgOrEvent_Header_  *pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pMsg;
		}
		else  //���뵽��λ
		{
			pMsg->pNext = pHeader->pList;
			pHeader->pList = pMsg;
		}
	}
}

void WINAPI XEle_RegisterMsgProc(HELE hEle, pFunEleMsgProc pFun)    //ע��Ԫ����Ϣ�������
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	eleMsgProc_ *pNew = (eleMsgProc_*)malloc(sizeof(eleMsgProc_));
	pNew->pFun = pFun;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	pNew->pClass_Fun_Info = NULL;
#endif
	if (NULL == pEle->pMsgProcList)
	{
		pEle->pMsgProcList = pNew;
		pNew->pNext = NULL;
	}
	else
	{
		pNew->pNext = pEle->pMsgProcList;
		pEle->pMsgProcList = pNew;
	}
}

void WINAPI XEle_RegisterEventProc(HELE hEle, pFunEleEventProc pFun)  //ע��Ԫ���¼��������
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	eleEventProc_ *pNew = (eleEventProc_*)malloc(sizeof(eleEventProc_));
	pNew->pFun = pFun;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	pNew->pClass_Fun_Info = NULL;
#endif
	if (NULL == pEle->pMsgProcList)
	{
		pEle->pEventProcList = pNew;
	}
	else
	{
		pNew->pNext = pEle->pEventProcList;
		pEle->pEventProcList = pNew;
	}
}

void WINAPI XEle_SetBkTransparent(HELE hEle, BOOL bTran) //����Ԫ�ر���͸��
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bBkTransparent = bTran;
}

BOOL WINAPI XEle_AddEle(HELE hEle, HELE hNewEle, int flag, HELE hDestEle, int index) //���Ԫ��
{
#ifdef _DEBUG
	IsEleDebug(hEle, __FUNCTION__);
	IsEleDebug(hNewEle, __FUNCTION__);
	if (hDestEle)
		IsEleDebug(hDestEle, __FUNCTION__);

	//����Ƿ����и�Ԫ��
	if (((ele_*)hNewEle)->pParentEle || ((ele_*)hNewEle)->pWindow)
	{
		MessageBox(NULL, L"XEle_AddEle()�ظ����Ԫ��,��Ԫ���Ѿ��и�Ԫ�ػ򴰿�,���Ƚ��Ƴ�!", L"�Ųʽ����-������ʾ!", MB_OK);
		exit(0);
	}
	//�ж�Ԫ���Ƿ��ظ����
	int count = Array_GetCount(((ele_*)hEle)->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		if (hNewEle == Array_GetAt(((ele_*)hEle)->hArrayEle, i))
		{
			MessageBox(NULL, L"XEle_AddEle()�ظ����Ԫ��!", L"�Ųʽ����-������ʾ!", MB_OK);
			exit(0);
		}
	}
#endif

	ele_ *pEle = (ele_*)hEle;
	ele_ *pNew = (ele_*)hNewEle;

	pNew->pParentEle = pEle;
	pNew->pWindow = pEle->pWindow;

	Ele_SetWindow(hNewEle, XEle_GetHWindow(hEle), pEle->bClient);

	BOOL bResult = FALSE;
	switch (flag)
	{
	case XC_ADDELE_END:    //���ӵ�ĩβ
		XArray_Add(pEle->hArrayEle, pNew);
		bResult = TRUE;
		break;
	case XC_ADDELE_FRIST:     //���ӵ���һλ��
		XArray_AddFirst(pEle->hArrayEle, pNew);
		bResult = TRUE;
		break;
	case XC_ADDELE_BEFORE:     //���ӵ�ָ��Ԫ��ǰ��
	{
		int count = ((array_*)pEle->hArrayEle)->count;
		for (int i = 0; i < count; i++)
		{
			if ((HELE)Array_GetAtEle(pEle->hArrayEle, i) == hDestEle)
			{
				bResult = XArray_insert(pEle->hArrayEle, pNew, i);
				break;
			}
		}
	}
	break;
	case XC_ADDELE_AFTER:    //���ӵ�ָ��Ԫ�غ���
	{
		int count = ((array_*)pEle->hArrayEle)->count;
		for (int i = 0; i < count; i++)
		{
			if ((HELE)Array_GetAtEle(pEle->hArrayEle, i) == hDestEle)
			{
				bResult = XArray_insert(pEle->hArrayEle, pNew, i + 1);
				break;
			}
		}
	}
	break;
	case XC_ADDELE_INDEX:    //���ӵ�ָ��λ������
		bResult = XArray_insert(pEle->hArrayEle, pNew, index);
		break;
	}
	//	if(pEle->pWindow)
	//		Resource_AddEle(hNewEle);
	return bResult;
}

void Ele_BreakWindow(HELE hEle) //�ݹ�Ͽ��봰����ϵ,��Ԫ�ر����븸Ԫ�ع�ϵ,�Ա�����
{
	ele_ *pEle = (ele_*)hEle;

	//����ǰ�ť,�ָ���ť״̬
	if (XC_BUTTON == XC_GetObjectType(hEle))
		((button_*)hEle)->state = STATE_LEAVE;

	//4.�����봰�ڹ���------------
	if (pEle->pWindow)
	{
		if (pEle == pEle->pWindow->pMouseTop)
			pEle->pWindow->pMouseTop = NULL;

		if (pEle == pEle->pWindow->pFocus || pEle == pEle->pWindow->pOldFocus)
		{
			pEle->pWindow->pFocus = NULL;
			pEle->pWindow->pOldFocus = NULL;
		}

		if (hEle == pEle->pWindow->pCapture)
			pEle->pWindow->pCapture = NULL;

		//�������
		if (hEle == pEle->pWindow->hCaretEle)
			XWnd_DestroyCaret((HWINDOW)pEle->pWindow);

		pEle->pWindow = NULL;
	}

	//TODO:������,�˵���,��״̬��,���Ƴ�

	//�ݹ�
	HELE  hChildEle = NULL;
	int count = XArray_GetCount(pEle->hArrayEle);
	for (int i = 0; i < count; i++)
	{
		hChildEle = (HELE)XArray_GetAt(pEle->hArrayEle, i);
		Ele_BreakWindow(hChildEle);
	}
}

void WINAPI XEle_RemoveEle(HELE hEle) //�Ƴ�Ԫ��,��������
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	//�����븸Ԫ�ع���
	if (pEle->pParentEle)
	{
		if (pEle == pEle->pParentEle->pMouseTop)
			pEle->pParentEle->pMouseTop = NULL;

		XArray_Delete(((ele_*)pEle->pParentEle)->hArrayEle, hEle);
		pEle->pParentEle = NULL;
	}
	else if (pEle->pWindow && pEle->bTopLevel) //�Ӵ����Ƴ�
	{
		if (pEle->bClient)
		{
			XArray_Delete(pEle->pWindow->hArrayEle, hEle);
		}
		else
		{
			XArray_Delete(pEle->pWindow->hArrayEleNC, hEle);
		}
	}
	else
	{
		XTRACE("����:XEle_RemoveEle() \n");
		MessageBox(NULL, L"����:XEle_RemoveEle()", L"�Ųʽ���� - ������ʾ", 0);
		exit(0);
	}

	//Resource_RemoveEle(hEle);

	//TODO:������,�˵���,��״̬��,���Ƴ�

	//��Ԫ�صݹ������봰�ڹ���
	Ele_BreakWindow(hEle);
}

void Ele_SetType(HELE hEle, int type) //����Ԫ����������
{
	((ele_*)hEle)->eleType = type;
}

BOOL CALLBACK Ele_WindowProc(HELE hEle, UINT message, WPARAM wParam, LPARAM lParam)
{
	ele_ *pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_Header_ *pHeader = NULL;
	int count = Array_GetCount(pEle->hArray_msg);
	for (int i = 0; i < count; i++)
	{
		pHeader = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_msg, i);
		if (message == pHeader->message)
		{
			if (pHeader->pFunMsgConv(hEle, pHeader, wParam, lParam))
			{
				return TRUE;
			}
			if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

			if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
				return TRUE;
		}
	}
	return FALSE;
}
/*
BOOL CALLBACK Ele_EventProc(HELE hEle,int type,WPARAM wParam,LPARAM lParam)
{
	HELE hEventEle=hEle; //�����¼���Ԫ��
	HELE hCurrEle=hEle;  //��ǰ�����¼���Ԫ��
	while(hCurrEle)
	{
		ele_ *pEle=(ele_*)hCurrEle;

		//�ҵ��������¼���Ӧ�Ĵ���������ͷ
		eleMsgOrEvent_Header_  *pEventHeader=NULL;
		int count=Array_GetCount(pEle->hArray_event);
		for(int i=0;i<count;i++)
		{
			if( type==((eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event,i))->Event )
			{
				pEventHeader=((eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event,i));
				break;
			}
		}

		if(pEventHeader) //�ҵ���Ԫ�ض�Ӧ��ע�ắ��
		{
			if(FALSE==pEventHeader->pFunEventConv(hCurrEle,hEle,pEventHeader,wParam,lParam))
			{

#ifdef _DEBUG  //������
				if(NULL==hEle || 0!=IsBadReadPtr(hCurrEle,sizeof(object_)) || XC_ELE!=((object_*)hCurrEle)->type)
				{
					XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[%d]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n",type);
					exit(0);
				}
#endif

				hCurrEle=(HELE)pEle->pParentEle; //���¼����ϴ���
			}else
			{
				return TRUE;
			}
		}else //δ�ҵ�,��ѯ���ĸ�Ԫ��
		{
			hCurrEle=(HELE)pEle->pParentEle;//���¼����ϴ���
		}
	}

	return FALSE;
}
*/

BOOL CALLBACK Ele_EventProc(HELE hEle, int type, WPARAM wParam, LPARAM lParam)
{
	HELE hEventEle = hEle; //�����¼���Ԫ��
	HELE hCurrEle = hEle;  //��ǰ�����¼���Ԫ��
	while (hCurrEle)
	{
		ele_ *pEle = (ele_*)hCurrEle;

		//�ҵ��������¼���Ӧ�Ĵ���������ͷ
		eleMsgOrEvent_Header_  *pEventHeader = NULL;
		eleMsgOrEvent_Header_  *pEventHeaderT = NULL;
		int count = Array_GetCount(pEle->hArray_event);
		for (int i = 0; i < count; i++)
		{
			pEventHeaderT = (eleMsgOrEvent_Header_*)Array_GetAt(pEle->hArray_event, i);
			if (type == pEventHeaderT->Event)
			{
				pEventHeader = pEventHeaderT;
				break;
			}
		}

		if (pEventHeader) //�ҵ���Ԫ�ض�Ӧ��ע�ắ��
		{
			ele_*    pParentEle = pEle->pParentEle;
			window_* pWindow = pEle->pWindow;

			if (FALSE == pEventHeader->pFunEventConv(hCurrEle, hEle, pEventHeader, wParam, lParam))
			{
				if (!XC_IsHELE(hCurrEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

				if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
					return TRUE;

#ifdef _DEBUG  //������
				if (NULL == hEle || 0 != IsBadReadPtr(hCurrEle, sizeof(object_)) || XC_ELE != ((object_*)hCurrEle)->type)
				{
					XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[%d]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n", type);
					exit(0);
				}
#endif

				hCurrEle = (HELE)pEle->pParentEle; //���¼����ϴ���
			}
			else
			{
				return TRUE;
			}
		}
		else //δ�ҵ�,��ѯ���ĸ�Ԫ��
		{
			hCurrEle = (HELE)pEle->pParentEle;//���¼����ϴ���
		}
	}

	return FALSE;
}

void Ele_Draw_Child(HELE hEle, HDRAW hDraw)	//������Ԫ��
{
	ele_ *pEle = (ele_*)hEle;

	RECT rcEle;
	ele_ *pChild = NULL;
	int count = Array_GetCount(pEle->hArrayEle);

	for (int i = 0; i < count; i++)
	{
		pChild = Array_GetAtEle(pEle->hArrayEle, i);
		if (pChild->bShow)
		{
			XEle_GetNCWndRect((HELE)pChild, &rcEle);

			//Ԫ���Ƿ����ػ�������
			if (XC_RectInRect(&pEle->pWindow->rcDraw, &rcEle))
			{
				Ele_SendEleMsg((HELE)pChild, XM_PAINT, (WPARAM)hDraw, 0);
			}
		}
	}
}

BOOL Ele_SendEleMsg(HELE hEle, UINT eleMessage, WPARAM wParam, LPARAM lParam) //����Ԫ����Ϣ,��������
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgProc_ *pMsg = ((ele_*)hEle)->pMsgProcList;
	while (pMsg)
	{
		if (pMsg->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.xint = eleMessage;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pMsg->pClass_Fun_Info;
			if (((pFunClassEventMsg)pMsg->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else
		{
			if (((pFunEleMsgProc)pMsg->pFun)(hEle, eleMessage, wParam, lParam))
				return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

		pMsg = pMsg->pNext;
	}
	return FALSE;
}

BOOL Ele_EventDispatch(HELE hEle, int type, WPARAM wParam, LPARAM lParam) //�¼�����,���ڵ���
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleEventProc_ *pEvent = ((ele_*)hEle)->pEventProcList;
	while (pEvent)
	{
		if (pEvent->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.xint = type;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pEvent->pClass_Fun_Info;
			if (((pFunClassEventMsg)pEvent->pFun)(&event_, xc_fun_b_e_i_i_i))
				return TRUE;
		}
		else
		{
			if (((pFunEleEventProc)pEvent->pFun)(hEle, type, wParam, lParam))
				return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

		pEvent = pEvent->pNext;
	}
	return FALSE;
}

BOOL Ele_SetWindow(HELE hEle, HWINDOW hWindow, BOOL bClient)
{
	if (hEle && hWindow)
	{
		ele_ *pEle = (ele_*)hEle;
		pEle->pWindow = (window_*)hWindow;
		pEle->bClient = bClient;

		if (XC_PROPERTYGRID == pEle->eleType)
		{
			if (NULL == ((window_*)hWindow)->hArrayPGrids)
				((window_*)hWindow)->hArrayPGrids = XArray_Create();

			XArray_Add(((window_*)hWindow)->hArrayPGrids, hEle);
		}

		int count = Array_GetCount(pEle->hArrayEle);
		for (int i = 0; i < count; i++)
		{
			if (FALSE == Ele_SetWindow((HELE)Array_GetAtEle(pEle->hArrayEle, i), hWindow, bClient))
				return FALSE;
		}
		return TRUE;
	}
	else
		return FALSE;
}
void Ele_HandleScrollView(HELE hEle, HDC hdc, int srcX, int srcY)
{
	HELE hParent = XEle_GetParentEle(hEle);

	/////////////////////////////////////////////////////
	RECT rcView;
	XSView_GetViewRect(hParent, &rcView);

	int posx = XSView_GetHViewPos(hParent);
	int posy = XSView_GetVViewPos(hParent);

	int x = posx + (-srcX);
	int y = posy + (-srcY);

	//����߿���
	int top = rcView.top - srcY;
	if (top < 0)
		top = 0;

	int left = rcView.left - srcX;
	if (left < 0)
		left = 0;

	COLORREF color = SetTextColor(hdc, ((ele_*)hParent)->textColor);
	HGDIOBJ  hFont = SelectObject(hdc, XFont_GetHFONT(((ele_*)hParent)->hFontX));

	HDRAW hDraw = XDraw_Create_(hdc);
	XDraw_SetOffset_(hDraw, x, y);

	///////////////////////////////////////////////////
	ele_*    pEle = (ele_*)hParent;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	drawScrollView_ *pList = SCROLLVIEW(hParent)->pDrawScrollViewList;
	while (pList)
	{
		if (pList->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hParent;
			event_.hEventEle = hParent;
			event_.wParam = (WPARAM)hDraw;
			event_.lParam = NULL;
			event_.pClass_fun = pList->pClass_Fun_Info;
			if (((pFunClassEventMsg)pList->pFun)(&event_, xc_fun_b_e_hdraw))
				break;
		}
		else
		{
			if (((pFunDrawScrollView)pList->pFun)(hParent, hDraw))
				break;
		}

		XDraw_RestoreGDIOBJ_(hDraw);

		if (!XC_IsHELE(hEle))
		{
			MsgError(XC_ERROR_0006);
			return; //��������Ч����ֹ��Ϣ�¼�
		}
		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
		{
			MsgError(XC_ERROR_0007);
			return;
		}

		pList = pList->pNext;
	}

	XDraw_Destroy_(hDraw);
	SetTextColor(hdc, color);
	SelectObject(hdc, hFont);
}

BOOL Ele_Draw_InspectionArea(HELE hEle, RECT &rect, RECT &rcDest) //����������
{
	ele_ *pEle = (ele_*)hEle;
	HWINDOW hWindow = (HWINDOW)pEle->pWindow;
	RECT rcDraw = pEle->pWindow->rcDraw;
	RECT rcWindowCilentEle = rect; //Ԫ������,���ڴ��ڿͻ���
	/////////��ֹ������Ԫ�ط�Χ////////////////////////////////////////////////
	ele_ *pPar = pEle->pParentEle; //��Ԫ��ָ��

	RECT rcWindowCilentEle2; //��Ԫ�ػ��ڴ��ڿͻ�������
	while (pPar) //��ֹ�������Ʒ�Χ
	{
		//����ǹ�����ͼ,��ֹ�����ӿ�
		XEle_GetWndClientRect((HELE)pPar, &rcWindowCilentEle2); //��Ԫ�ػ��ڴ��ڿͻ�������

		if (rcWindowCilentEle.left < rcWindowCilentEle2.left) rcWindowCilentEle.left = rcWindowCilentEle2.left;
		if (rcWindowCilentEle.top < rcWindowCilentEle2.top) rcWindowCilentEle.top = rcWindowCilentEle2.top;
		if (rcWindowCilentEle.right > rcWindowCilentEle2.right) rcWindowCilentEle.right = rcWindowCilentEle2.right;
		if (rcWindowCilentEle.bottom > rcWindowCilentEle2.bottom) rcWindowCilentEle.bottom = rcWindowCilentEle2.bottom;

		pPar = pPar->pParentEle;
	}

	if (pEle->bClient)
	{
		//ת�����ͻ���
		int left = XWnd_GetClientLeft(hWindow);
		int top = XWnd_GetClientTop(hWindow);
		rcDraw.left -= left;
		rcDraw.right -= left;
		rcDraw.top -= top;
		rcDraw.bottom -= top;

		//��ֹ�������ڿͻ���
		RECT rcWindowClient;	//ת�������ڿͻ���
		XWnd_GetClientRect(hWindow, &rcWindowClient);
		RECT rcDraw2;
		if (0 == IntersectRect(&rcDraw2, &rcDraw, &rcWindowClient))
			return FALSE;

		rcDraw = rcDraw2;
	}

	//�����µĻ�������
	if (0 == IntersectRect(&rcDest, &rcDraw, &rcWindowCilentEle))
		return FALSE;

	return TRUE;
}

void Ele_Draw_Dispatch(HELE hEle, HDRAW hDraw, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;
	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = (WPARAM)hDraw;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_hdraw))
			{
				break;
			}
		}
		else if (((pFunEleDraw)pFunT->pFun)(hEle, hDraw))
		{
			break;
		}

		XDraw_RestoreGDIOBJ_(hDraw);

		if (!XC_IsHELE(hEle))
		{
			MsgError(XC_ERROR_0004);
			return; //��������Ч����ֹ��Ϣ�¼�
		}
		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
		{
			MsgError(XC_ERROR_0005);
			return;
		}

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			//	DeleteDC(memDC);
			//	DeleteObject(hBitmap);
			//	SelectObject(memDC,hOldFont);
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_PAINT]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			MsgError(XC_ERROR_0006);
		}
#endif
		pFunT = pFunT->pNext;
	}
}

BOOL Ele_ConvMsgPaint(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_ *pEle = (ele_*)hEle;
	HWINDOW hWindow = (HWINDOW)pEle->pWindow;

	RECT rcDest = { 0 }; //�µĻ�������
	RECT rect; //Ԫ������,���ڴ��ڿͻ���
	XEle_GetWndClientRect(hEle, &rect);

	if (FALSE == Ele_Draw_InspectionArea(hEle, rect, rcDest))
		return TRUE;

	HDRAW   hDraw = (HDRAW)wParam;   //���ڻ���DC (�����ǿͻ���)
	HDC		hdc = XDraw_GetHDC_(hDraw);
	HDC     memDC = CreateCompatibleDC(NULL);      //��������DC ����

	int srcX = rcDest.left - rect.left;
	int srcY = rcDest.top - rect.top;

	int cx = rcDest.right - rcDest.left;
	int cy = rcDest.bottom - rcDest.top;

	if (NULL == hDraw)
	{
		MessageBox(NULL, L"Ԫ�ػ��ƴ���:001", L"�Ųʽ����-������ʾ", 0);
		exit(0);
		return FALSE;
	}
	if (NULL == memDC)
	{
		MessageBox(NULL, L"Ԫ�ػ��ƴ���:002", L"�Ųʽ����-������ʾ", 0);
		exit(0);
		return FALSE;
	}
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, cx, cy); //��������λͼ
	if (NULL == hBitmap)
	{
		MessageBox(NULL, L"�����ڴ滭��ʧ��,�벻Ҫʹ�÷�UI�߳�ֱ�Ӳ���UI!", L"�Ųʽ����-������ʾ", 0);
		exit(0);
		return FALSE;
	}

	SelectObject(memDC, hBitmap);

	//ѡ��Ԫ��ʹ�õ�����
	HGDIOBJ hOldFont = NULL;
	if (pEle->hFontX)
		hOldFont = SelectObject(memDC, XFont_GetHFONT(pEle->hFontX));
	else
		hOldFont = SelectObject(memDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
	COLORREF color = SetTextColor(memDC, pEle->textColor);
	SetBkMode(memDC, TRANSPARENT);

	HDRAW hDrawMem = XDraw_Create_(memDC);

	if (pEle->bBkTransparent)
	{
		XDraw_BitBlt2_(hDrawMem, 0, 0, cx, cy, hDraw, rcDest.left, rcDest.top, SRCCOPY);
	}
	else
	{
		RECT rc = { 0,0,cx,cy };
		XDraw_FillSolidRect(memDC, &rc, pEle->bkColor);
	}

	XDraw_SetOffset_(hDrawMem, -srcX, -srcY);

	//���ƺ�������////////////////////////
	Ele_Draw_Dispatch(hEle, hDrawMem, pMsgHeader, wParam, lParam);

	XDraw_Destroy_(hDrawMem);

	//���������ͼ
//	if(XC_IsSViewExtend(hEle)) //������ͼ
	if (XC_SCROLLVIEW_VIEW == XC_GetObjectType(hEle))
	{
		Ele_HandleScrollView(hEle, memDC, srcX, srcY);
	}

	SelectObject(memDC, hOldFont);
	SetTextColor(memDC, color);

	if (FALSE == pEle->bTransparentChannel)
	{
		if (pEle->pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHADOW || pEle->pWindow->transparentFlag & XC_WIND_TRANSPARENT_SHAPED)
			Draw_SetTransparent(memDC, 255);
	}

	//����Ԫ�ػ���������
	XDraw_BitBlt_(hDraw, rcDest.left, rcDest.top, cx, cy, memDC, 0, 0, SRCCOPY);

	DeleteDC(memDC);
	DeleteObject(hBitmap);

	Ele_Draw_Child(hEle, hDraw);  //������Ԫ��

	return TRUE;
}

BOOL Ele_ConvMsgMouseClick(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_pt))
				return TRUE;
		}
		else if (((pFunEleMouseClick)pFunT->pFun)(hEle, (POINT*)wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_MOUSECLICK]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgMouseDBClick(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{

		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_pt))
				return TRUE;
		}
		else if (((pFunEleMouseDBClick)pFunT->pFun)(hEle, (POINT*)wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_MOUSEDBCLICK]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgMouseMove(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_i_pt))
				return TRUE;
		}
		else if (((pFunEleMouseMove)pFunT->pFun)(hEle, wParam, (POINT*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_MOUSEMOVE]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgLButtonDown(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_i_pt))
				return TRUE;
		}
		else if (((pFunEleLButtonDown)pFunT->pFun)(hEle, wParam, (POINT*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_LBUTTONDOWN]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgLButtonUp(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_i_pt))
				return TRUE;
		}
		else if (((pFunEleLButtonUp)pFunT->pFun)(hEle, wParam, (POINT*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_LBUTTONUP]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgRButtonDown(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_i_pt))
				return TRUE;
		}
		else if (((pFunEleRButtonDown)pFunT->pFun)(hEle, wParam, (POINT*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_RBUTTONDOWN]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgRButtonUp(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_i_pt))
				return TRUE;
		}
		else if (((pFunEleRButtonUp)pFunT->pFun)(hEle, wParam, (POINT*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_RBUTTONUP]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvMsgTimerEx(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pMsgHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = NULL;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_i_i))
				return TRUE;
		}
		else if (((pFunEleTimerEx)pFunT->pFun)(hEle, wParam, (void*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XM_RBUTTONUP]��Ϣ�������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}


//////////�¼�ת��/////////////////////////////////////////////////////

BOOL Ele_ConvEventBtnClick(HELE hEle, HELE hEleClick, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEleClick;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventBtnClick)pFunT->pFun)(hEle, hEleClick))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_BNCLICK]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventMouseStay(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //���ͣ��
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventMouseStay)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE; //����Ҫ���ϲ㴫��
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_MOUSESTAY]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventMouseLeave(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventMouseLeave)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_MOUSELEAVE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventSetFocus(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventSetFocus)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_SETFOCUS]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventKillFocus(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = NULL;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventKillFocus)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_KILLFOCUS]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventKeyDown(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_i))
				return TRUE;
		}
		else if (((pFunEventKeyDown)pFunT->pFun)(hEle, hEventEle, wParam, lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_KEYDOWN]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventChar(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_i))
				return TRUE;
		}
		else if (((pFunEventChar)pFunT->pFun)(hEle, hEventEle, wParam, lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_CHAR]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventHScroll(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventHScroll)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_HSCROLL]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventVScroll(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventVScroll)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_VSCROLL]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventHScrollView(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventHScrollView)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_HSCROLLVIEW]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventVScrollView(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventVScrollView)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_VSCROLLVIEW]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventSetCapture(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //�����겶��
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventSetCapture)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_SETCAPTURE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventKillCapture(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //ʧȥ��겶��
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventKillCapture)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_KILLCAPTURE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventMouseWheel(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)  //�����¼�
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_pt))
				return TRUE;
		}
		else if (((pFunEventMouseWheel)pFunT->pFun)(hEle, hEventEle, wParam, &pt))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_MOUSEWHEEL]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventMenuSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)  //�����¼�
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = NULL;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventMenuSelect)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_MENUSELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventMenuExit(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //�����¼�
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventMenuExit)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_MENUEXIT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventListSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventListSelect)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LIST_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventListHeaderClick(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //�б�ͷ����
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventListHeaderClick)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LIST_HEADER_CLICK]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventListHeaderChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //�б�ͷ��ȸı�
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_i))
				return TRUE;
		}
		else if (((pFunEventListHeaderChange)pFunT->pFun)(hEle, hEventEle, wParam, lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LIST_HEADER_CHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventTreeSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //���б�ѡ��ı�
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventTreeSelect)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_TREE_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventTreeExpand(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //����չ��������
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_b))
				return TRUE;
		}
		else if (((pFunEventTreeExpand)pFunT->pFun)(hEle, hEventEle, wParam, lParam == 1 ? TRUE : FALSE))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_TREE_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventComboBoxSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam) //������Ͽ�ѡ���¼�
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventComboBoxSelect)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_COMBOBOX_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventComboBoxPopupList(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_i))
				return TRUE;
		}
		else if (((pFunEventComboBoxPopupList)pFunT->pFun)(hEle, hEventEle, (HWINDOW)wParam, (HELE)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_COMBOBOX_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventComboBoxExitList(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventComboBoxExitList)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_COMBOBOX_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventPPageSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventPPageSelect)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_PPAGE_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventSliderChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventSliderChange)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_SLIDER_CHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventMonthChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_b_b))
				return TRUE;
		}
		else if (((pFunEventMonthChange)pFunT->pFun)(hEle, hEventEle, 0 == wParam ? FALSE : TRUE, 0 == lParam ? FALSE : TRUE))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_MONTHCAL_CHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventDateTimeChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventDateTimeChange)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_DATETIME_CHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventDateTimePopupMonthCal(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventDateTimePopupMonthCal)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_DATETIME_CHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventDateTimeExitMonthCal(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventDateTimeExitMonthCal)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_DATETIME_CHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventSetFont(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventSetFont)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_SETFONT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventShow(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_b))
				return TRUE;
		}
		else if (((pFunEventShow)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_SETFONT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventSize(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventSize)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_SIZE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventListBoxSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventListBoxSelect)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTBOX_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventPGridSelChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_i))
				return TRUE;
		}
		else if (((pFunEventPGridSelChange)pFunT->pFun)(hEle, hEventEle, wParam, lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_PGRID_SELCHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventPGridValueChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i))
				return TRUE;
		}
		else if (((pFunEventPGridValueChange)pFunT->pFun)(hEle, hEventEle, wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_PGRID_VALUECHANGE]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}


BOOL Ele_ConvEventListViewSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_i))
				return TRUE;
		}
		else if (((pFunEventListViewSelect)pFunT->pFun)(hEle, hEventEle, wParam, lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_SELECT]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventListViewExpand(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_b))
				return TRUE;
		}
		else if (((pFunEventListViewExpand)pFunT->pFun)(hEle, hEventEle, wParam, 0 == lParam ? FALSE : TRUE))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}


BOOL Ele_ConvEventListViewDragInsert(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_listView_dragInsert))
				return TRUE;
		}
		else if (((pFunEventListViewDragInsert)pFunT->pFun)(hEle, hEventEle, (listView_dragInsert_*)wParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventPaneLock(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventPaneLock)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventPaneDock(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventPaneDock)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventPaneFloat(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventPaneFloat)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventEditChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e))
				return TRUE;
		}
		else if (((pFunEventEditChange)pFunT->pFun)(hEle, hEventEle))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventComboBoxChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_pt))
				return TRUE;
		}
		else if (((pFunEventComboBoxSelecting)pFunT->pFun)(hEle, hEventEle, wParam, (BOOL*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventListBoxChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_pt))
				return TRUE;
		}
		else if (((pFunEventListBoxSelecting)pFunT->pFun)(hEle, hEventEle, wParam, (BOOL*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

BOOL Ele_ConvEventTreeChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam)
{
	ele_*    pEle = (ele_*)hEle;
	ele_*    pParentEle = pEle->pParentEle;
	window_* pWindow = pEle->pWindow;

	eleMsgOrEvent_ *pFunT = pHeader->pList;
	while (pFunT)
	{
		if (pFunT->pClass_Fun_Info)
		{
			eventOrMsg_  event_;
			event_.hEle = hEle;
			event_.hEventEle = hEventEle;
			event_.wParam = wParam;
			event_.lParam = lParam;
			event_.pClass_fun = pFunT->pClass_Fun_Info;
			if (((pFunClassEventMsg)pFunT->pFun)(&event_, xc_fun_b_e_e_i_pt))
				return TRUE;
		}
		else if (((pFunEventTreeSelecting)pFunT->pFun)(hEle, hEventEle, wParam, (BOOL*)lParam))
		{
			return TRUE;
		}

		if (!XC_IsHELE(hEle)) return TRUE; //��������Ч����ֹ��Ϣ�¼�

		if (pParentEle != pEle->pParentEle && pWindow != pEle->pWindow) //��ȫ���,��ֹԪ�صĸ��ı�
			return TRUE;

#ifdef _DEBUG  //������
		if (NULL == hEle || 0 != IsBadReadPtr(hEle, sizeof(object_)) || XC_ELE != ((object_*)hEle)->type)
		{
			XTRACE("�Ųʽ����-debug��ʾ-���ش���:����ע���[XE_LISTVIEW_EXPAND]�¼��������з�������,��Ԫ�ؾ��ʧЧ,����������˸�Ԫ�ؾ��[HELE],Ӧ�÷���[TRUE]\n");
			exit(0);
		}
#endif
		pFunT = pFunT->pNext;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////
BOOL CALLBACK Ele_OnMouseMove(HELE hEle, UINT flags, POINT *pPt)
{
	ele_ *pEle = (ele_*)hEle;

	int count = Array_GetCount(pEle->hArrayEle);

	if (XC_SCROLLVIEW_VIEW == XC_GetObjectType(hEle))
	{
		ele_ *pChild = NULL;
		HELE hScrollView = (HELE)((ele_*)hEle)->pParentEle;
		int posx = XSView_GetHViewPos(hScrollView);
		int posy = XSView_GetVViewPos(hScrollView);
		POINT pt = { pPt->x - posx,pPt->y - posy };

		for (int i = count - 1; i > -1; i--)  //�ж���갴���ĸ���Ԫ����
		{
			pChild = Array_GetAtEle(pEle->hArrayEle, i);
			if (pChild->bShow && FALSE == pChild->bMouseThrough)
			{
				if (PtInRect(&pChild->rect, pt))
				{
					if (pEle->pMouseTop != pChild)
					{
						if (pEle->pMouseTop) //����뿪
						{
							HELE hEleSend = (HELE)pEle->pMouseTop;
							pEle->pMouseTop = NULL;
							Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
						}

						if (!XC_IsHELE((HELE)pChild)) return TRUE;
						if (!XC_IsHELE(hEle)) return TRUE;

						if (pChild->bEnable)
						{
							pEle->pMouseTop = pChild;
							Ele_SendEvent((HELE)pEle->pMouseTop, XE_MOUSESTAY, 0, 0);

							if (!XC_IsHELE((HELE)pChild)) return TRUE;
							if (!XC_IsHELE(hEle)) return TRUE;
						}
					}
					//ת������Ԫ�ؿͻ�������
					if (pChild->bEnable)
					{
						POINT InPt = { pt.x - pChild->rect.left, pt.y - pChild->rect.top };
						Ele_SendEleMsg((HELE)pChild, XM_MOUSEMOVE, flags, (LPARAM)&InPt);
					}
					return TRUE;
				}
			}
		}
	}
	else
	{
		ele_ *pChild = NULL;
		for (int i = count - 1; i > -1; i--)  //�ж���갴���ĸ���Ԫ����
		{
			pChild = (ele_*)XArray_GetAt(pEle->hArrayEle, i);
			if (pChild->bShow && FALSE == pChild->bMouseThrough)
			{
				if (PtInRect(&pChild->rect, *pPt))
				{
					if ((pEle->pMouseTop != pChild))
					{
						if (pEle->pMouseTop) //����뿪
						{
							HELE hEleSend = (HELE)pEle->pMouseTop;
							pEle->pMouseTop = NULL;
							Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
						}

						if (!XC_IsHELE((HELE)pChild)) return TRUE;
						if (!XC_IsHELE(hEle)) return TRUE;

						if (pChild->bEnable)
						{
							pEle->pMouseTop = pChild;
							Ele_SendEvent((HELE)pEle->pMouseTop, XE_MOUSESTAY, 0, 0);

							if (!XC_IsHELE((HELE)pChild)) return TRUE;
							if (!XC_IsHELE(hEle)) return TRUE;
						}
					}
					//ת������Ԫ�ؿͻ�������
					if (pChild->bEnable)
					{
						POINT InPt = { pPt->x - pChild->rect.left,pPt->y - pChild->rect.top };
						Ele_SendEleMsg((HELE)pChild, XM_MOUSEMOVE, flags, (LPARAM)&InPt);
					}
					return TRUE;
				}
			}
		}
	}

	//���û�����κ�Ԫ��֮��
	if (pEle->pMouseTop) //����뿪
	{
		HELE hEleSend = (HELE)pEle->pMouseTop;
		pEle->pMouseTop = NULL;
		Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
	}

	return FALSE;
}

//������갴�� / ����
BOOL  Ele_HandleMousePt(HELE hEle, UINT flags, POINT *pPt, int message)
{
	ele_ *pEle = (ele_*)hEle;

	//������Ԫ���б�
	ele_ *pChild = NULL;
	int count = Array_GetCount(pEle->hArrayEle);

	if (XC_SCROLLVIEW_VIEW == XC_GetObjectType(hEle))
	{
		HELE hScrollView = (HELE)((ele_*)hEle)->pParentEle;
		int posx = XSView_GetHViewPos(hScrollView);
		int posy = XSView_GetVViewPos(hScrollView);
		POINT pt = { pPt->x - posx,pPt->y - posy };
		for (int i = count - 1; i > -1; i--)  //�ж���갴���ĸ�Ԫ����
		{
			pChild = Array_GetAtEle(pEle->hArrayEle, i);
			if (pChild->bShow && FALSE == pChild->bMouseThrough)
			{
				if (PtInRect(&pChild->rect, pt))
				{
					if (pChild->bEnable)
					{
						//ת������Ԫ�ؿͻ�������
						POINT InPt = { pt.x - pChild->rect.left,   pt.y - pChild->rect.top };
						if (XM_MOUSECLICK == message || XM_MOUSEDBCLICK == message)
							return Ele_SendEleMsg((HELE)pChild, message, (LPARAM)&InPt, 0);
						else
							return Ele_SendEleMsg((HELE)pChild, message, flags, (LPARAM)&InPt);
					}
					return FALSE;
				}
			}
		}
	}
	else
	{
		for (int i = count - 1; i > -1; i--)  //�ж���갴���ĸ�Ԫ����
		{
			pChild = Array_GetAtEle(pEle->hArrayEle, i);
			if (pChild->bShow && FALSE == pChild->bMouseThrough)
			{
				if (PtInRect(&pChild->rect, *pPt))
				{
					if (pChild->bEnable)
					{
						//ת������Ԫ�ؿͻ�������
						POINT InPt = { pPt->x - pChild->rect.left,   pPt->y - pChild->rect.top };
						if (XM_MOUSECLICK == message || XM_MOUSEDBCLICK == message)
							return Ele_SendEleMsg((HELE)pChild, message, (LPARAM)&InPt, 0);
						else
							return Ele_SendEleMsg((HELE)pChild, message, flags, (LPARAM)&InPt);
					}
					return FALSE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK Ele_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	if (FALSE == XEle_IsHitChildEle(hEle, pPt))
	{
		XEle_SetFocus(hEle, TRUE);
	}

	return	Ele_HandleMousePt(hEle, flags, pPt, XM_LBUTTONDOWN);
}

BOOL CALLBACK Ele_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	return Ele_HandleMousePt(hEle, flags, pPt, XM_LBUTTONUP);
}

BOOL CALLBACK Ele_OnMouseClick(HELE hEle, POINT *pPt)
{
	return Ele_HandleMousePt(hEle, 0, pPt, XM_MOUSECLICK);
}

BOOL CALLBACK Ele_OnMouseDBClick(HELE hEle, POINT *pPt)
{
	return Ele_HandleMousePt(hEle, 0, pPt, XM_MOUSEDBCLICK);
}

BOOL CALLBACK Ele_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt)
{
	return Ele_HandleMousePt(hEle, flags, pPt, XM_RBUTTONDOWN);
}

BOOL CALLBACK Ele_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt)
{
	return Ele_HandleMousePt(hEle, flags, pPt, XM_RBUTTONUP);
}

BOOL CALLBACK Ele_OnEventMouseSay(HELE hEle, HELE hEventEle)
{
	if (hEle != hEventEle)
		return FALSE;

	if (((ele_*)hEle)->bToolTips)
	{
		if (NULL == g_hTooltipsEle)
		{
			g_hTooltipsEle = hEle;
			SetTimer(((ele_*)hEle)->pWindow->hWnd, IDT_TOOLTIPS, 500, Ele_TimerProc);
		}
	}
	return TRUE;
}

BOOL CALLBACK Ele_OnEventMouseLeave(HELE hEle, HELE hEventEle) //����뿪
{
	if (hEle == hEventEle)
	{
		ele_ *pEle = (ele_*)hEventEle;
		if (pEle->bToolTips)
		{
			if (g_hTooltipsEle)
			{
				g_hTooltipsEle = NULL;
			}
			if (g_hToolTipsWnd)
			{
				HWND hwnd = ((window_*)g_hToolTipsWnd)->hWnd;
				PostMessage(hwnd, WM_CLOSE, 0, 0);
				g_hToolTipsWnd = NULL;
			}
		}
		if (pEle->pMouseTop)
		{
			HELE hEleSend = (HELE)pEle->pMouseTop;
			pEle->pMouseTop = NULL;
			Ele_SendEvent(hEleSend, XE_MOUSELEAVE, 0, 0);
		}
	}
	return TRUE;
}

void WINAPI XEle_GetClientRect(HELE hEle, RECT *pRect)  //�ͻ�������
{
	IsEleDebug(hEle, __FUNCTION__);
	//XTRACE("line=%s,column=%d\n",__FILE__,__LINE__);
	ele_ *pEle = (ele_*)hEle;
	pRect->left = 0;
	pRect->top = 0;
	pRect->right = pEle->rect.right - pEle->rect.left;
	pRect->bottom = pEle->rect.bottom - pEle->rect.top;
}

void WINAPI XEle_GetRect(HELE hEle, RECT *pRect)  //���ڸ�Ԫ������
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	pRect->left = pEle->rect.left;
	pRect->top = pEle->rect.top;
	pRect->right = pEle->rect.right;
	pRect->bottom = pEle->rect.bottom;
}

void WINAPI XEle_GetWndClientRect(HELE hEle, RECT *pRect)   //���ڴ��ڿͻ�������
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	pRect->left = pEle->rect.left;
	pRect->top = pEle->rect.top;
	pRect->right = pEle->rect.right;
	pRect->bottom = pEle->rect.bottom;

	if (pEle->pParentEle)
	{
		ele_ *pPar = pEle->pParentEle;
		while (pPar)
		{
			pRect->left = pPar->rect.left + pRect->left;
			pRect->top = pPar->rect.top + pRect->top;
			pRect->right = pPar->rect.left + pRect->right;
			pRect->bottom = pPar->rect.top + pRect->bottom;

			if (XC_SCROLLVIEW_VIEW == pPar->eleType)  //������ǹ�����ͼ
			{
				HELE hScrollView = (HELE)pPar->pParentEle;
				int posX = XSView_GetHViewPos(hScrollView);
				int poxY = XSView_GetVViewPos(hScrollView);

				pRect->left += posX;
				pRect->top += poxY;
				pRect->right += posX;
				pRect->bottom += poxY;
			}

			pPar = pPar->pParentEle;
		}
	}
}

void WINAPI XEle_GetNCWndRect(HELE hEle, RECT *pRect) //���ڴ�������(�����ǿͻ���)
{
	IsEleDebug(hEle, __FUNCTION__);

	ele_ *pEle = (ele_*)hEle;
	if (NULL == pEle->pWindow)
		return;

	if (FALSE == pEle->bClient) //�ǿͻ���
	{
		XEle_GetWndClientRect(hEle, pRect);
	}
	else //�ͻ���
	{
		XEle_GetWndClientRect(hEle, pRect);
		HWINDOW hWindow = XEle_GetHWindow(hEle);
		pRect->left += XWnd_GetClientLeft(hWindow);
		pRect->top += XWnd_GetClientTop(hWindow);
		pRect->right += XWnd_GetClientLeft(hWindow);
		pRect->bottom += XWnd_GetClientTop(hWindow);
	}
}

void WINAPI XEle_SetRect(HELE hEle, RECT *pRect, BOOL bRedraw)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	RECT rect = *pRect;

	RECT rcDraw_0ld;
	if (bRedraw)
	{
		XEle_GetClientRect(hEle, &rcDraw_0ld);
		XEle_RectToNCWnd(hEle, &rcDraw_0ld);
	}
	;
	/*
		if(pEle->pParentEle && XC_SCROLLVIEW_VIEW==XC_GetObjectType(pEle->pParentEle)) / //��Ԫ���ǹ�����ͼ
		{
			pEle->elePt.x=pRect->left;
			pEle->elePt.y=pRect->top;

			int posx=XSView_GetHViewPos((HELE)pEle->pParentEle);
			int posy=XSView_GetVViewPos((HELE)pEle->pParentEle);
			rect.left+=posx;
			rect.top+=posy;
			rect.right+=posx;
			rect.bottom+=posy;
		}*/

	if (pEle->pParentEle && XC_SCROLLVIEW_VIEW == XC_GetObjectType(pEle->pParentEle))  //��Ԫ���ǹ�����ͼ
	{
		HELE hParentEle = XEle_GetParentEle(hEle);

		pEle->elePt.x = pRect->left;
		pEle->elePt.y = pRect->top;

		int posx = XSView_GetHViewPos(hParentEle);
		int posy = XSView_GetVViewPos(hParentEle);
		rect.left += posx;
		rect.top += posy;
		rect.right += posx;
		rect.bottom += posy;
	}
	else
	{
		pEle->elePt.x = pRect->left;
		pEle->elePt.y = pRect->top;
	}

	pEle->rect = rect;//*pRect;

	if (bRedraw)
	{
		HWND hWnd = XEle_GetHWnd(hEle);
		InvalidateRect(hWnd, &rcDraw_0ld, FALSE);

		RECT rcDraw_new;
		XEle_GetClientRect(hEle, &rcDraw_new);
		XEle_RectToNCWnd(hEle, &rcDraw_new);
		InvalidateRect(hWnd, &rcDraw_new, FALSE);
	}

	Ele_SendEvent(hEle, XE_SIZE, 0, 0);
}

HWND WINAPI XEle_GetHWnd(HELE hEle)
{
	IsEleDebug(hEle, __FUNCTION__);
	if (((ele_*)hEle)->pWindow)
		return ((ele_*)hEle)->pWindow->hWnd;
	else
		return NULL;
}

HWINDOW WINAPI XEle_GetHWindow(HELE hEle)
{
	IsEleDebug(hEle, __FUNCTION__);
	return (HWINDOW)((ele_*)hEle)->pWindow;
}

int WINAPI XEle_GetId(HELE hEle)
{
	IsEleDebug(hEle, __FUNCTION__);
	return ((ele_*)hEle)->id;
}

COLORREF WINAPI XEle_GetBkColor(HELE hEle) //��ȡ������ɫ
{
	IsEleDebug(hEle, __FUNCTION__);
	return ((ele_*)hEle)->bkColor;
}

HFONTX WINAPI XEle_GetFont(HELE hEle) //��ȡ����
{
	IsEleDebug(hEle, __FUNCTION__);
	return ((ele_*)hEle)->hFontX;
}

//����Ԫ��Z��... Z order 
BOOL WINAPI XEle_SetZOrder(HELE hEle, HELE hDestEle, int flag, int index)
{
	IsEleDebug(hEle, __FUNCTION__);
	if (XC_ZORDER_BEFORE == flag || XC_ZORDER_AFTER == flag)
	{
		IsEleDebug(hDestEle, __FUNCTION__);
	}

	ele_* pEle = (ele_*)hEle;
	if (NULL == pEle->pWindow)
	{
		XTRACE("����:XEle_SetZOrder()Ԫ��û�й�������,����������Z�� \n");
		MessageBox(NULL, L"����:XEle_SetZOrder()Ԫ��û�й�������,����������Z��", L"�Ųʽ����-������ʾ", 0);
		exit(0);
	}
	HARRAY hArrayEle = NULL;
	if (pEle->pParentEle)
	{
		hArrayEle = pEle->pParentEle->hArrayEle;
	}
	else
	{
		hArrayEle = pEle->pWindow->hArrayEle;
	}
	BOOL bResult = FALSE;
	switch (flag)
	{
	case XC_ZORDER_BOTTOM:
		XArray_Delete(hArrayEle, hEle);
		XArray_AddFirst(hArrayEle, hEle);
		break;
	case XC_ZORDER_TOP:
		XArray_Delete(hArrayEle, hEle);
		XArray_Add(hArrayEle, hEle);
		break;
	case XC_ZORDER_BEFORE:
	{
		XArray_Delete(hArrayEle, hEle);
		int count = ((array_*)hArrayEle)->count;
		for (int i = 0; i < count; i++)
		{
			if ((HELE)Array_GetAtEle(hArrayEle, i) == hDestEle)
			{
				bResult = XArray_insert(hArrayEle, hEle, i);
				break;
			}
		}
	}
	break;
	case XC_ZORDER_AFTER:
	{
		XArray_Delete(hArrayEle, hEle);
		int count = ((array_*)hArrayEle)->count;
		for (int i = 0; i < count; i++)
		{
			if ((HELE)Array_GetAtEle(hArrayEle, i) == hDestEle)
			{
				bResult = XArray_insert(hArrayEle, hEle, i + 1);
				break;
			}
		}
	}
	break;
	case XC_ZORDER_INDEX:
		XArray_Delete(hArrayEle, hEle);
		bResult = XArray_insert(hArrayEle, hEle, index);
		break;
	}
	return bResult;
}

void WINAPI XEle_PointToParent(HELE hEle, in_out_ POINT *pPt)
{
	IsEleDebug(hEle, __FUNCTION__);
	HELE hParent = XEle_GetParentEle(hEle);
	if (hParent)
	{
		pPt->x += ((ele_*)hEle)->rect.left;
		pPt->y += ((ele_*)hEle)->rect.top;

		if (XC_SCROLLVIEW_VIEW == ((ele_*)hParent)->eleType)  //������ǹ�����ͼ
		{
			HELE hScrollView = (HELE)((ele_*)hParent)->pParentEle;
			int posX = XSView_GetHViewPos(hScrollView);
			int poxY = XSView_GetVViewPos(hScrollView);

			pPt->x += posX;
			pPt->y += poxY;
		}
	}
}

void WINAPI XEle_PointToWndClient(HELE hEle, POINT *pPt)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	pPt->x = pEle->rect.left + pPt->x;
	pPt->y = pEle->rect.top + pPt->y;

	if (pEle->pParentEle)
	{
		ele_ *pPar = pEle->pParentEle;
		while (pPar)
		{
			pPt->x += pPar->rect.left;
			pPt->y += pPar->rect.top;
			pPar = pPar->pParentEle;
		}
	}
}

void WINAPI XEle_PointToNCWnd(HELE hEle, POINT *pPt)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	pPt->x = pEle->rect.left + pPt->x;
	pPt->y = pEle->rect.top + pPt->y;

	if (pEle->pParentEle)
	{
		ele_ *pPar = pEle->pParentEle;
		while (pPar)
		{
			pPt->x += pPar->rect.left;
			pPt->y += pPar->rect.top;

			if (XC_SCROLLVIEW_VIEW == pPar->eleType)  //������ǹ�����ͼ
			{
				HELE hScrollView = (HELE)pPar->pParentEle;
				int posX = XSView_GetHViewPos(hScrollView);
				int poxY = XSView_GetVViewPos(hScrollView);

				pPt->x += posX;
				pPt->y += poxY;;
			}

			pPar = pPar->pParentEle;
		}
	}
	if (pEle->bClient)
	{
		pPt->x += XWnd_GetClientLeft((HWINDOW)pEle->pWindow);
		pPt->y += XWnd_GetClientTop((HWINDOW)pEle->pWindow);
	}
}

void WINAPI XEle_PointNCWndToEle(HELE hEle, POINT *pPt)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	if (pEle->bClient) //Ԫ���ڿͻ���,���ǿͻ�������ת�����ͻ���
	{
		XWnd_WindowToClientPt((HWINDOW)pEle->pWindow, pPt);//�ɷǿͻ���ת�����ͻ���
	}

	//�ɿͻ���ת����Ԫ������
	pPt->x = pPt->x - pEle->rect.left;
	pPt->y = pPt->y - pEle->rect.top;

	if (pEle->pParentEle)
	{
		ele_ *pParent = pEle->pParentEle;
		while (pParent)
		{
			pPt->x = pPt->x - pParent->rect.left;
			pPt->y = pPt->y - pParent->rect.top;

			if (XC_SCROLLVIEW_VIEW == pParent->eleType)  //������ǹ�����ͼ
			{
				HELE hScrollView = (HELE)pParent->pParentEle;
				int posX = XSView_GetHViewPos(hScrollView);
				int poxY = XSView_GetVViewPos(hScrollView);

				pPt->x -= posX;
				pPt->y -= poxY;;
			}

			pParent = pParent->pParentEle;
		}
	}
}

void WINAPI XEle_PointWndClientToEle(HELE hEle, POINT *pPt)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	//�ɿͻ���ת����Ԫ������
	pPt->x = pPt->x - pEle->rect.left;
	pPt->y = pPt->y - pEle->rect.top;

	if (pEle->pParentEle)
	{
		ele_ *pParent = pEle->pParentEle;
		while (pParent)
		{
			pPt->x = pPt->x - pParent->rect.left;
			pPt->y = pPt->y - pParent->rect.top;

			if (XC_SCROLLVIEW_VIEW == pParent->eleType)  //������ǹ�����ͼ
			{
				HELE hScrollView = (HELE)pParent->pParentEle;
				int posX = XSView_GetHViewPos(hScrollView);
				int poxY = XSView_GetVViewPos(hScrollView);

				pPt->x -= posX;
				pPt->y -= poxY;;
			}

			pParent = pParent->pParentEle;
		}
	}
}

void WINAPI XEle_RectToWndClient(HELE hEle, RECT *pRect)
{
	IsEleDebug(hEle, __FUNCTION__);

	ele_ *pEle = (ele_*)hEle;
	int cx = pRect->right - pRect->left;
	int cy = pRect->bottom - pRect->top;

	pRect->left = pEle->rect.left + pRect->left;
	pRect->top = pEle->rect.top + pRect->top;

	if (pEle->pParentEle)
	{
		ele_ *pPar = pEle->pParentEle;
		while (pPar)
		{
			pRect->left += pPar->rect.left;
			pRect->top += pPar->rect.top;

			if (XC_SCROLLVIEW_VIEW == pPar->eleType)  //������ǹ�����ͼ
			{
				HELE hScrollView = (HELE)pPar->pParentEle;
				int posX = XSView_GetHViewPos(hScrollView);
				int poxY = XSView_GetVViewPos(hScrollView);

				pRect->left += posX;
				pRect->top += poxY;
				pRect->right += posX;
				pRect->bottom += poxY;
			}

			pPar = pPar->pParentEle;
		}
	}
	pRect->right = pRect->left + cx;
	pRect->bottom = pRect->top + cy;
}

void WINAPI XEle_RectToNCWnd(HELE hEle, in_out_ RECT *pRect)
{
	IsEleDebug(hEle, __FUNCTION__);

	ele_ *pEle = (ele_*)hEle;
	if (NULL == pEle->pWindow)
	{
		XTRACE("����:XEle_RectToNCWnd()�޷�ת������,Ԫ��û�й������� \n");
		MessageBox(NULL, L"����:XEle_RectToNCWnd()�޷�ת������,Ԫ��û�й�������", L"�Ųʽ����-������ʾ!", 0);
		exit(0);
		return;
	}

	int cx = pRect->right - pRect->left;
	int cy = pRect->bottom - pRect->top;

	pRect->left = pEle->rect.left + pRect->left;
	pRect->top = pEle->rect.top + pRect->top;

	if (pEle->pParentEle)
	{
		ele_ *pPar = pEle->pParentEle;
		while (pPar)
		{
			pRect->left += pPar->rect.left;
			pRect->top += pPar->rect.top;

			if (XC_SCROLLVIEW_VIEW == pPar->eleType)  //������ǹ�����ͼ
			{
				HELE hScrollView = (HELE)pPar->pParentEle;
				int posX = XSView_GetHViewPos(hScrollView);
				int poxY = XSView_GetVViewPos(hScrollView);

				pRect->left += posX;
				pRect->top += poxY;
				pRect->right += posX;
				pRect->bottom += poxY;
			}
			pPar = pPar->pParentEle;
		}
	}

	if (pEle->bClient) //�ͻ���Ԫ��
	{
		pRect->left += XWnd_GetClientLeft((HWINDOW)pEle->pWindow);
		pRect->top += XWnd_GetClientTop((HWINDOW)pEle->pWindow);
	}
	pRect->right = pRect->left + cx;
	pRect->bottom = pRect->top + cy;
}

void WINAPI XEle_SetTextColor(HELE hEle, COLORREF color) //�����ı���ɫ
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->textColor = color;
}

COLORREF WINAPI XEle_GetTextColor(HELE hEle) //��ȡ�ı���ɫ
{
	IsEleDebug(hEle, __FUNCTION__);
	return ((ele_*)hEle)->textColor;
}

void WINAPI XEle_EnableMouseThrough(HELE hEle, BOOL bEnable)  //������괩͸Ԫ��
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bMouseThrough = bEnable;
}

BOOL Ele_SendEvent(HELE hEle, int type, WPARAM wParam, LPARAM lParam, BOOL bImmediately)
{
	if (NULL == ((ele_*)hEle)->pWindow)
		return FALSE;

	HWND hWnd = ((ele_*)hEle)->pWindow->hWnd;
	if (hWnd)
	{
		if (bImmediately) //��������
		{
			return Ele_EventDispatch(hEle, type, wParam, lParam);
		}

		if (TRUE == g_eventList[g_event_write_pos].bEvent)
		{
			//�����ģ̬����,�����¼��������������,��Ϊ���õ�Ԫ���޷������¼�
			//�����ͨ���ڳ����¼�����,��Ҫע�������;�ų�ʧЧ��Ԫ��,��Ԫ�ط����¼���,��Ԫ������,�����޷�����
			//XTRACE("�����¼�:����(%d)�¼�(%d)\n",g_event_write_pos,type);
		}

		g_eventList[g_event_write_pos].hEle = hEle;
		g_eventList[g_event_write_pos].type = type;
		g_eventList[g_event_write_pos].wParam = wParam;
		g_eventList[g_event_write_pos].lParam = lParam;
		g_eventList[g_event_write_pos].bEvent = TRUE;

		PostMessage(hWnd, XWM_EVENT_ALL, (WPARAM)g_event_write_pos, 0);
		//	XTRACE("����->:����(%d),�¼�(%d)\n",g_event_write_pos,type);

		g_event_write_pos++;
		if (EVENT_LIST_SIZE == g_event_write_pos)
			g_event_write_pos = 0;
	}
	return FALSE;
}

void WINAPI XEle_SetFocus(HELE hEle, BOOL bFocus) //���ý���
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	if (bFocus && FALSE == pEle->bEnableFocus)
		return;

	if (FALSE == pEle->bEnable) //����
		return;

	window_ *pWindow = (window_*)XEle_GetHWindow(hEle);

	if (pWindow->hWnd == GetFocus()) //��ǰ����ӵ�н���
	{
		if (bFocus)  //��ý���
		{
			if (pWindow->pFocus == pEle)
				return;

			if (pWindow->pFocus)
			{
				HELE hOld = (HELE)pWindow->pFocus;
				pWindow->pFocus = pEle;
				Ele_SendEvent(hOld, XE_KILLFOCUS, 0, 0);

				if (!XC_IsHWINDOW((HWINDOW)pWindow)) return;
				if (!XC_IsHELE((HELE)pWindow->pFocus)) return;

				Ele_SendEvent((HELE)pWindow->pFocus, XE_SETFOCUS, 0, 0);
			}
			else
			{
				pWindow->pFocus = pEle;
				Ele_SendEvent((HELE)pWindow->pFocus, XE_SETFOCUS, 0, 0);
			}
			return;
		}
		//ʧȥ����
		if (pEle == pWindow->pFocus)
		{
			HELE hOld = (HELE)pWindow->pFocus;
			pWindow->pFocus = NULL; //����Ԫ�ض�û�н���
			Ele_SendEvent(hOld, XE_KILLFOCUS, 0, 0);
		}
		return;
	}
	//��ǰ����û�н���
	if (bFocus)//��ý���
	{
		if (pWindow->pOldFocus == pEle)
			return;

		pWindow->pOldFocus = pEle;
		//	Ele_SendEvent((HELE)pWindow->pOldFocus,XE_SETFOCUS,0,0);
		return;
	}
	//ʧȥ����
	if (pEle == pWindow->pOldFocus)
	{
		HELE hOld = (HELE)pWindow->pOldFocus;
		pWindow->pOldFocus = NULL;
		Ele_SendEvent((HELE)hOld, XE_KILLFOCUS, 0, 0);
	}

}

void WINAPI XEle_EnableEle(HELE hEle, BOOL bEnable) //Ԫ���Ƿ���Ч
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bEnable = bEnable;
}

void WINAPI XEle_EnableFocus(HELE hEle, BOOL bFocus) //��������
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bEnableFocus = bFocus;
}

void WINAPI XEle_EnableDrawFocus(HELE hEle, BOOL bFocus) //�Ƿ���ƽ���
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bDrawFocus = bFocus;
}

void WINAPI XEle_EnableToolTips(HELE hEle, BOOL bTip)   //���ù�����ʾ
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bToolTips = bTip;
}
void WINAPI XEle_EnableBorder(HELE hEle, BOOL bEnable)
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bBorder = bEnable;
}

void WINAPI XEle_EnableTransparentChannel(HELE hEle, BOOL bEnable)
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bTransparentChannel = bEnable;
}

BOOL WINAPI XEle_IsBkTransparent(HELE hEle)
{
	IsEleDebug(hEle, __FUNCTION__);
	return ((ele_*)hEle)->bBkTransparent;
}

void WINAPI XEle_SetId(HELE hEle, int id)
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->id = id;
}

void WINAPI XEle_ShowEle(HELE hEle, BOOL bShow)
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pObj = (ele_*)hEle;

	if (bShow == pObj->bShow)
	{
		return;
	}

	pObj->bShow = bShow;

	Ele_SendEvent(hEle, XE_SHOW, bShow, 0); //Ԫ����ʾ�����¼�

	if (!XC_IsHELE(hEle)) return;

	if (pObj->pWindow  && FALSE == bShow)
	{
		//�������뽹��Ϊ��
		if (pObj->pWindow->pFocus)
		{
			ele_ *pEle = pObj->pWindow->pFocus;
			while (pEle)
			{
				if (pEle == pObj)
				{
					XEle_SetFocus((HELE)pObj->pWindow->pFocus, FALSE);
					break;
				}
				pEle = pEle->pParentEle;
			}
		}
	}
}

void WINAPI XEle_SetFont(HELE hEle, HFONTX hFontX)
{
	IsEleDebug(hEle, __FUNCTION__);
	if (hFontX)
	{
		IsFontDebug(hFontX, __FUNCTION__);
	}

	Font_AddFontX(((ele_*)hEle)->hFontX, hFontX);
}

void WINAPI XEle_SetBkColor(HELE hEle, COLORREF color) //���ñ�����ɫ
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->bkColor = color;
}
void WINAPI XEle_SetBorderColor(HELE hEle, COLORREF color) //���ñ߿���ɫ
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->borderColor = color;
}
void WINAPI XEle_SetToolTips(HELE hEle, wchar_t *pText) //���ù�����ʾ����
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	if (NULL == pEle->hToolTipsStr)
	{
		pEle->hToolTipsStr = XStr_Create();
	}
	XStr_SetString(pEle->hToolTipsStr, pText);
}

wchar_t* WINAPI XEle_GetTooltips(HELE hEle)  //��ȡ������ʾ����
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;
	if (pEle->hToolTipsStr)
	{
		return XStr_GetBuffer(pEle->hToolTipsStr);
	}
	return NULL;
}

HELE WINAPI XEle_GetParentEle(HELE hEle)  //��ȡ��Ԫ�ؾ��
{
	IsEleDebug(hEle, __FUNCTION__);
	if (((ele_*)hEle)->pParentEle && XC_SCROLLVIEW_VIEW == ((ele_*)((ele_*)hEle)->pParentEle)->eleType)
	{
		return	(HELE)((ele_*)((ele_*)hEle)->pParentEle)->pParentEle;
	}
	else
		return (HELE)((ele_*)hEle)->pParentEle;
}

BOOL WINAPI XEle_IsFocus(HELE hEle) //Ԫ���Ƿ�ӵ�н���
{
	IsEleDebug(hEle, __FUNCTION__);
	if (((ele_*)hEle)->pWindow->pFocus && hEle == (HELE)((ele_*)hEle)->pWindow->pFocus)
		return TRUE;
	else
		return FALSE;
}

BOOL WINAPI XEle_IsShowEle(HELE hEle)
{
	IsEleDebug(hEle, __FUNCTION__);

	if (FALSE == IsWindowVisible(XEle_GetHWnd(hEle)))
		return FALSE;

	ele_*  pEle = (ele_*)hEle;
	while (pEle)
	{
		if (FALSE == pEle->bShow)
			return FALSE;
		pEle = pEle->pParentEle;
	}

	return TRUE;
}

BOOL WINAPI XEle_IsHitChildEle(HELE hEle, POINT *pPt) //�ж��Ƿ�������Ԫ����
{
	IsEleDebug(hEle, __FUNCTION__);
	ele_ *pEle = (ele_*)hEle;

	//������Ԫ���б�
	int count = Array_GetCount(pEle->hArrayEle);
	for (int i = count - 1; i > -1; i--)  //�ж���갴���ĸ�Ԫ����
	{
		if (Array_GetAtEle(pEle->hArrayEle, i)->bShow && FALSE == Array_GetAtEle(pEle->hArrayEle, i)->bMouseThrough)
		{
			if (PtInRect(&(Array_GetAtEle(pEle->hArrayEle, i)->rect), *pPt))
			{
				return TRUE; //�������Ԫ����
			}
		}
	}
	return FALSE;
}

BOOL WINAPI XEle_IsChildEle(HELE hEle, HELE hChild)  //�ж�ָ��Ԫ���Ƿ�Ϊ��Ԫ��
{
	IsEleDebug(hEle, __FUNCTION__);
	IsEleDebug(hChild, __FUNCTION__);

	ele_ *pEle = (ele_*)hEle;
	ele_ *pChild = (ele_*)hChild;

	ele_ *pParent = pChild->pParentEle;
	while (pParent)
	{
		if (pEle == pParent)
			return TRUE;

		pParent = pParent->pParentEle;
	}

	return FALSE;
}

void WINAPI XEle_SetUserData(HELE hEle, void* data)  //�����û�����
{
	IsEleDebug(hEle, __FUNCTION__);
	((ele_*)hEle)->userData = data;
}

void* WINAPI XEle_GetUserData(HELE hEle)  //��ȡ�û�����
{
	IsEleDebug(hEle, __FUNCTION__);
	return ((ele_*)hEle)->userData;
}

UINT WINAPI XEle_SetTimerEx(HELE hEle, UINT nIDEvent, UINT uElapse, void* userData)
{
	IsEleDebug(hEle, __FUNCTION__);
	return Timer_SetTimerElement(hEle, nIDEvent, uElapse, userData);
}

BOOL WINAPI XEle_KillTimerEx(HELE hEle, UINT nIDEvent)
{
	IsEleDebug(hEle, __FUNCTION__);
	return Timer_KillTimerElement(nIDEvent);
}

void WINAPI XEle_SetCapture(HELE hEle)      //����Ԫ����겶��
{
	IsEleDebug(hEle, __FUNCTION__);
	HWND hWnd = GetCapture();
	HWND hWndMy = XEle_GetHWnd(hEle);
	if (hWnd != hWndMy)
	{
		::SetCapture(hWndMy);
	}

	window_ *pWindow = ((ele_*)hEle)->pWindow;
	if (hEle != pWindow->pCapture)
	{
		if (pWindow->pCapture)
		{
			HELE hEleSend = pWindow->pCapture;
			pWindow->pCapture = NULL;
			Ele_SendEvent(hEleSend, XE_KILLCAPTURE, 0, 0);
		}

		if (!XC_IsHELE(hEle)) return;
		if (!XC_IsHWINDOW((HWINDOW)pWindow)) return;

		pWindow->pCapture = hEle;
		Ele_SendEvent(pWindow->pCapture, XE_SETCAPTURE, 0, 0);
	}
}

void WINAPI XEle_ReleaseCapture(HELE hEle)  //�ͷ�Ԫ����겶��
{
	IsEleDebug(hEle, __FUNCTION__);
	::ReleaseCapture();

	window_ *pWindow = ((ele_*)hEle)->pWindow;
	if (pWindow->pCapture)
	{
		HELE hEleSend = pWindow->pCapture;
		pWindow->pCapture = NULL;
		Ele_SendEvent(hEleSend, XE_KILLCAPTURE, 0, 0);
	}
}

int  WINAPI XEle_GetChildCout(HELE hEle)  //��ȡ��Ԫ������
{
	IsEleDebug(hEle, __FUNCTION__);
	return Array_GetCount(((ele_*)hEle)->hArrayEle);
}

HELE WINAPI XEle_GetChildByIndex(HELE hEle, int index)	//��ȥָ����Ԫ��
{
	IsEleDebug(hEle, __FUNCTION__);
	int count = XArray_GetCount(((ele_*)hEle)->hArrayEle);
	if (index >= 0 && index < count)
	{
		return (HELE)XArray_GetAt(((ele_*)hEle)->hArrayEle, index);
	}
	else
		return NULL;
}

void WINAPI XEle_RedrawEle(HELE hEle, BOOL bImmediately) //�ػ�Ԫ��
{
	IsEleDebug(hEle, __FUNCTION__);
	if (((ele_*)hEle)->bShow)
	{
		//Wnd_OnRedrawEle((HWINDOW)((ele_*)hEle)->pWindow,hEle); //��������,��ֹԪ�ؾ��ʧЧ

		HWINDOW hWindow = (HWINDOW)((ele_*)hEle)->pWindow;
		if (NULL == hWindow)
			return;

		RECT rect; //Ҫ�ػ������
		XEle_GetNCWndRect(hEle, &rect); //���ڴ�������(�����ǿͻ���)
		Wnd_RedrawEle(hWindow, hEle, &rect);

		/*	if(FALSE==bImmediately)
		{
		XWnd_RedrawWnd
		::PostMessage(XEle_GetHWnd(hEle),XWM_REDRAW_ELE,(WPARAM)hEle,0);
		}else
		{
		RECT rc;
		XEle_GetClientRect(hEle,&rc);
		XEle_RectToNCWnd(hEle,&rc);
		XWnd_RedrawWndRect((HWINDOW)((ele_*)hEle)->pWindow,&rc,TRUE);
		}*/
	}
}

void WINAPI XEle_RedrawRect(HELE hEle, RECT *pRect) //Ԫ���ػ�ָ������
{
	IsEleDebug(hEle, __FUNCTION__);
	if (((ele_*)hEle)->bShow)
	{
		ele_ *pEleShow = (ele_*)hEle;
		HWINDOW hWindow = (HWINDOW)pEleShow->pWindow;
		if (NULL == hWindow)
			return;

		while (pEleShow)  //��鸸�����Ƿ���ʾ
		{
			if (pEleShow->bShow)
				pEleShow = pEleShow->pParentEle;
			else
				return;
		}

		RECT rect;
		XEle_GetClientRect(hEle, &rect);

		RECT rc = *pRect;

		if (rc.left < rect.left)
			rc.left = 0;

		if (rc.top < rect.top)
			rc.top = 0;

		if (rc.right > rect.right)
			rc.right = rect.right;

		if (rc.bottom > rect.bottom)
			rc.bottom = rect.bottom;

		if (rc.left > rc.right) return;
		if (rc.top > rc.bottom) return;

		XEle_RectToNCWnd(hEle, &rc);

		Wnd_RedrawEle(hWindow, hEle, &rc);
	}
}

BOOL CALLBACK Ele_OnDraw(HELE hEle, HDRAW hDraw)
{
	if (((ele_*)hEle)->bBorder)
	{
		RECT rect;
		XEle_GetClientRect(hEle, &rect);
		HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, ((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw, &rect, hBrush);
	}
	return TRUE;
}

HELE    g_hTooltipsEle = NULL;//��ǰ��Ϲ�����ʾ��Ԫ��
HWINDOW g_hToolTipsWnd = NULL;//������ʾ����
VOID CALLBACK Ele_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (IDT_TOOLTIPS == idEvent && g_hTooltipsEle && (NULL == g_hToolTipsWnd)) //������ʾ
	{
		ele_* pEle = (ele_*)g_hTooltipsEle;
		//���Ԫ���Ƿ���Ч
		if (FALSE == XC_IsHELE(g_hTooltipsEle)) //Ԫ��ʧЧ,����Ԫ�ر�����
		{
			HWND hwndTip = ((window_*)g_hToolTipsWnd)->hWnd;
			PostMessage(hwndTip, WM_CLOSE, 0, 0);
			g_hTooltipsEle = NULL;
			g_hToolTipsWnd = NULL;
			KillTimer(hwnd, idEvent);
			return;
		}

		RECT rect = { 0,0,30,10 };
		if (pEle->hToolTipsStr) //���㴰�ڴ�С
		{
			wchar_t *pText = XStr_GetBuffer(pEle->hToolTipsStr);
			if (pText)
			{
				int len = XStr_GetLength(pEle->hToolTipsStr);
				if (len < 1)
				{
					KillTimer(hwnd, idEvent);
					return;
				}

				HDC hdc = GetDC(NULL);
				HGDIOBJ hOldFont = SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
				::DrawText(hdc, pText, len, &rect, DT_CALCRECT);
				SelectObject(hdc, hOldFont);
				ReleaseDC(NULL, hdc);
			}
		}
		POINT pt;
		GetCursorPos(&pt);
		pt.y += 22;

		RECT rcWork;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);

		int cx = rect.right + 10;
		int cy = rect.bottom + 10;

		if ((pt.x + cx) > rcWork.right)
		{
			pt.x = rcWork.right - cx;
		}
		if (pt.y + cy > rcWork.bottom)
		{
			pt.y = pt.y - 22 - cy - 2;
		}

		g_hToolTipsWnd = XWnd_CreateWindow(pt.x, pt.y, cx, cy, L"ToolTipWnd", hwnd, 0);
		if (g_hToolTipsWnd)
		{
			XWnd_RegisterMessage(g_hToolTipsWnd, WM_PAINT, ToolTips_OnDrawWindow);
			SetWindowPos(((window_*)g_hToolTipsWnd)->hWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
			SetTimer(((window_*)g_hToolTipsWnd)->hWnd, IDT_TOOLTIPS_TIMEOUT, 3000, Ele_TimerProc);
		}
	}
	else if (IDT_TOOLTIPS_TIMEOUT == idEvent)  //������ʾ��ʾ��ʱ
	{
		HWND hwndTip = ((window_*)g_hToolTipsWnd)->hWnd;
		PostMessage(hwndTip, WM_CLOSE, 0, 0);
		g_hTooltipsEle = NULL;
		g_hToolTipsWnd = NULL;
	}
	KillTimer(hwnd, idEvent);
}

BOOL CALLBACK ToolTips_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw)
{
	RECT rect;
	XWnd_GetClientRect(hWindow, &rect);
	XDraw_GradientFill2_(hDraw, RGB(255, 255, 255), RGB(200, 200, 200), &rect, 1);
	if (g_hTooltipsEle)
	{
		ele_* pEle = (ele_*)g_hTooltipsEle;
		if (pEle->hToolTipsStr)
		{
			wchar_t *pText = XStr_GetBuffer(pEle->hToolTipsStr);
			if (pText)
			{
				RECT rc = rect;
				rc.left = 5;
				rc.top = 5;
				XDraw_DrawText_(hDraw, pText, XStr_GetLength(pEle->hToolTipsStr), &rc, 0);
			}
		}
	}
	HBRUSH hBrush = XDraw_CreateSolidBrush_(hDraw, RGB(100, 100, 100));
	HRGN hRgn = XDraw_CreateRoundRectRgn_(hDraw, 0, 0, rect.right + 1, rect.bottom + 1, 0, 0);
	XDraw_FrameRgn_(hDraw, hRgn, hBrush, 1, 1);
	//	DeleteObject(hBrush);
	//	DeleteObject(hRgn);
	return TRUE;
}
