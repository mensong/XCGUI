/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct eleMsgOrEvent_Header_;
//�¼�ת������
typedef BOOL(*pFunEleEventConversion)(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//��Ϣת������2
typedef BOOL(*pFunEleMsgConversion)(HELE hEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);


////////////////////

struct eleMsgProc_   //��Ϣ��������
{
	void     *pFun; //����ָ��
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	void  *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
	eleMsgProc_ *pNext;
};

struct eleEventProc_ //�¼���������
{
	void      *pFun; //����ָ��
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	void  *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
	eleEventProc_ *pNext;
};

struct eleDestroy_ //Ԫ������ Destroy
{
	void    *pFun; //����ָ��
	eleDestroy_ *pNext;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	void  *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

//-------------------
struct eleMsgOrEvent_   //��Ϣ���¼�
{
	void              *pFun; //��Ϣ�¼���Ӧ�Ĵ�����
	eleMsgOrEvent_    *pNext;

#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	void  *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

struct eleMsgOrEvent_Header_  //��Ϣ���¼� ����ͷ  
{
	eleMsgOrEvent_  *pList;  //ע�����Ϣ���¼�������
	union   //��������
	{
		int   message;    //��Ϣ����                 
		int   Event;      //�¼�����
	};
	union
	{
		pFunEleMsgConversion    pFunMsgConv;   //��Ϣת������
		pFunEleEventConversion  pFunEventConv; //�¼�ת������
	};
};

//-------------------
struct window_;
struct ele_  //T1 Ԫ�ػ���
{
	object_ object;
	int     eleType;     //Ԫ����������

	//-----------------------------------
	ele_ *pParentEle;    //��Ԫ��
	RECT rect;
	int  id;              //Ԫ��ID
	BOOL bShow;           //Ԫ���Ƿ���ʾ
	BOOL bEnable;         //Ԫ���Ƿ���Ч
	BOOL bClient;         //Ԫ���Ƿ��ڷǿͻ���, TRUE:�ͻ��� ,FALSE:�ǿͻ���
	BOOL bBkTransparent;  //Ԫ�ر���͸��
	BOOL bTopLevel;       //�Ƿ�Ϊ����Ԫ��
	BOOL bEnableFocus;    //���Ի�ý���
	BOOL bDrawFocus;      //�Ƿ���ƽ���
	BOOL bToolTips;       //�Ƿ����ù�����ʾ
	BOOL bTransparentChannel;//����͸��ͨ��,Transparent channel
	BOOL bDestroy;         //��ֹ�ظ��������ٺ���
	BOOL bMouseThrough;    //��괩͸

	void* userData;         //�û�����,�ڲ���ʹ��

	ele_     *pMouseTop;   //��ǰ������ĸ���Ԫ������,��Ԫ�صĶ�����Ԫ��,��������Ԫ�ص���Ԫ��
	POINT    elePt;        //��Ϲ�����ͼ,Ԫ��ʵ������.
	HSTRING  hToolTipsStr; //������ʾ����
	COLORREF bkColor;      //������ɫ
//	HFONT    hFont;        //����
	//LOGFONT  fontInfo;   //��ǰ������Ϣ
	HFONTX   hFontX;

	COLORREF textColor;    //������ɫ
	window_  *pWindow;     //��������ָ��

	BOOL     bBorder; //�Ƿ����ñ߿�,�ñ߿�ֻ�����������
	COLORREF borderColor; //�߿���ɫ

	HARRAY hArray_msg;    //��Ϣ����,�Զ�����  eleMsgOrEvent_Header_
	HARRAY hArray_event;  //�¼�����,�Զ�����  eleMsgOrEvent_Header_
	HARRAY hArrayEle;     //��Ԫ���б�   ele_*

	eleMsgProc_      *pMsgProcList;   //Ԫ����Ϣ��������б�
	eleEventProc_    *pEventProcList; //Ԫ���¼���������б�
	eleDestroy_      *pDestroyList;   //Ԫ�����������б�

	//��ʽ:
	HSTRING  hString_Style_Class; //������ʽ��
};

#ifdef XCGUI_PLUS  //C++��֧��
XC_API void WINAPI XEle_RegisterEventEx(HELE hEle, int type, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);

XC_API void WINAPI XEle_RegisterMessageEx(HELE hEle, int message, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //ע����Ϣ
XC_API void WINAPI XEle_RegisterMsgProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);    //ע��Ԫ����Ϣ�������
XC_API void WINAPI XEle_RegisterEventProcEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info);  //ע���¼����ع��˺���

#endif


//Ԫ��API:

/// @defgroup element ����Ԫ��(Element)
/// @ingroup  groupElements
/// ����Ԫ�ؽӿ��б�
/// @{

/// @brief    ��������Ԫ��
/// @param x  Ԫ��x����
/// @param y  Ԫ��y����
/// @param cx ���
/// @param cy �߶�
/// @param hParent ���Ǵ��ھ����Ԫ�ؾ��.
/// @return Ԫ�ؾ��.
XC_API HELE WINAPI XEle_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL); //����

/// @brief ����UIԪ��,��Ԫ�ػ��Զ��Ӹ�(Ԫ�ػ򴰿�)���Ƴ�,ͬʱ���ٸ�Ԫ�ص���Ԫ��.
/// @param hEle Ԫ�ؾ��
/// @return �ɹ�����TRUE,���Ԫ���Ѿ����ٻ��������ٷ���FALSE.
XC_API BOOL WINAPI XEle_Destroy(HELE hEle);  //����

//ע��
///@name ע��
///@{

/// @brief ע��Ԫ����Ϣ������.
/// @param hEle Ԫ�ؾ��.
/// @param message Ԫ����Ϣ����.
/// @param pFun    ������Ϣ������.
XC_API void WINAPI XEle_RegisterMessage(HELE hEle, int message, void *pFun);

/// @brief ע��Ԫ���¼�������.
/// @param hEle Ԫ�ؾ��.
/// @param type �¼�����.
/// @param pFun �¼���������.
XC_API void WINAPI XEle_RegisterEvent(HELE hEle, int type, void *pFun);

/// @brief ע��Ԫ����Ϣ�������.
/// @param hEle Ԫ�ؾ��.
/// @param pFun ������̺�����.������������:
/// @code BOOL CALLBACK EleMsgProc(HELE hEle,UINT eleMessage,WPARAM wParam,LPARAM lParam); @endcode
XC_API void WINAPI XEle_RegisterMsgProc(HELE hEle, pFunEleMsgProc pFun);    //ע��Ԫ����Ϣ�������

/// @brief ע��Ԫ���¼��������.
/// @param hEle Ԫ�ؾ��
/// @param pFun �¼�������̺�����.������������:
/// @code  BOOL CALLBACK EleEventProc(HELE hEle,int type,WPARAM wParam,LPARAM lParam); @endcode
XC_API void WINAPI XEle_RegisterEventProc(HELE hEle, pFunEleEventProc pFun);  //ע��Ԫ���¼��������

///@}

/// @brief  ����Ԫ�ر���͸��.
/// @param hEle Ԫ�ؾ��.
/// @param bTran TRUE����͸��,����͸��.
XC_API void WINAPI XEle_SetBkTransparent(HELE hEle, BOOL bTran);   //����Ԫ�ر���͸��

/// @brief ����Ԫ�ؽ���.
/// @param hEle Ԫ�ؾ��.
/// @param bFocus TRUE���ø�Ԫ��ӵ�н���,�����෴.
XC_API void WINAPI XEle_SetFocus(HELE hEle, BOOL bFocus); //���ý���

/// @brief ����Ԫ��id��ʶ��.
/// @param hEle Ԫ�ؾ��
/// @param id ��ʶ��.
XC_API void WINAPI XEle_SetId(HELE hEle, int id);

/// @brief ����Ԫ������.
/// @param hEle Ԫ�ؾ��
/// @param hFontX ������.
XC_API void WINAPI XEle_SetFont(HELE hEle, HFONTX hFontX);

/// @brief ��ȡԪ������.
/// @param hEle Ԫ�ؾ��
/// @return ������.
XC_API HFONTX WINAPI XEle_GetFont(HELE hEle); //��ȡ����

/// @brief ����Ԫ��Z��,hEle��hDestEle������ͬ��Ԫ��,��ͬ�ĸ�.
/// @param hEle Ԫ�ؾ��
/// @param hDestEle Ŀ��Ԫ�ؾ��.
/// @param flag  ��ʶ
/// @param index ����
/// @return �ɹ�����TRUE,ʧ��FALSE.
XC_API BOOL WINAPI XEle_SetZOrder(HELE hEle, HELE hDestEle = NULL, int flag = XC_ZORDER_TOP, int index = NULL);

/// @brief ����Ԫ�ر�����ɫ.
/// @param hEle Ԫ�ؾ��
/// @param color RGB��ɫֵ.
XC_API void WINAPI XEle_SetBkColor(HELE hEle, COLORREF color); //���ñ�����ɫ

/// @brief ��ȡԪ�ر�����ɫ.
/// @param hEle Ԫ�ؾ��.
/// @return Ԫ�ر�����ɫ.
XC_API COLORREF WINAPI XEle_GetBkColor(HELE hEle); //��ȡ������ɫ

/// @brief ���ñ߿���ɫ.
/// @param hEle  Ԫ�ؾ��
/// @param color ��ɫֵ.
XC_API void WINAPI XEle_SetBorderColor(HELE hEle, COLORREF color); //���ñ߿���ɫ

/// @brief ����Ԫ�ع�����ʾ����,Ȼ����� XEle_EnableToolTips()����.
/// @param hEle Ԫ�ؾ��
/// @param pText �ı�����.
XC_API void WINAPI XEle_SetToolTips(HELE hEle, wchar_t *pText); //���ù�����ʾ����

/// @brief ����Ԫ����겶��.
/// @param hEle Ԫ�ؾ��
XC_API void WINAPI XEle_SetCapture(HELE hEle);   //����Ԫ����겶��

/// @brief ��ȡ������ʾ����.
/// @param hEle Ԫ�ؾ��.
/// @return ������ʾ����.
XC_API wchar_t* WINAPI XEle_GetTooltips(HELE hEle);  //��ȡ������ʾ����

/// @brief ��ȡ��Ԫ�ؾ��.
/// @param hEle Ԫ�ؾ��
/// @return ��Ԫ�ؾ��.
XC_API HELE WINAPI XEle_GetParentEle(HELE hEle);  //��ȡ��Ԫ�ؾ��

/// @brief ��ȡ��Ԫ������,��������Ԫ�ص���Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @return ��Ԫ������.
XC_API int  WINAPI XEle_GetChildCout(HELE hEle);  //��ȡ��Ԫ������

/// @brief ��ȡָ��������Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @param index ��Ԫ������.
/// @return ��Ԫ�ؾ��.
XC_API HELE WINAPI XEle_GetChildByIndex(HELE hEle, int index);	//��ȡָ����Ԫ��

/// @brief ��ȡԪ�����ڴ��ھ��.
/// @param hEle Ԫ�ؾ��
/// @return ���ھ��HWND.
XC_API HWND WINAPI XEle_GetHWnd(HELE hEle);  //��ȡ���ھ��

/// @brief ��ȡԪ�����ڴ��ڵĴ��ھ��.
/// @param hEle Ԫ�ؾ��.
/// @return ������Դ���.
XC_API HWINDOW WINAPI XEle_GetHWindow(HELE hEle); //��ȡ������Դ���

/// @brief ��ȡ�û�����.
/// @param hEle Ԫ�ؾ��
/// @return �û�����.
XC_API void* WINAPI XEle_GetUserData(HELE hEle);  //��ȡ�û�����

/// @brief��ȡԪ��ID
/// @param hEle Ԫ�ؾ��
/// @return Ԫ��ID.
XC_API int WINAPI XEle_GetId(HELE hEle);

/// @brief �ͷ�Ԫ����겶��.
/// @param hEle Ԫ�ؾ��
XC_API void WINAPI XEle_ReleaseCapture(HELE hEle);   //�ͷ�Ԫ����겶��

/// @brief Ԫ���Ƿ���Ч.
/// @param hEle Ԫ�ؾ��
/// @param bEnable TRUEԪ����Ч,�����෴.
XC_API void WINAPI XEle_EnableEle(HELE hEle, BOOL bEnable); //Ԫ���Ƿ���Ч

/// @brief Ԫ�������ý���.
/// @param hEle Ԫ�ؾ��
/// @param bFocus  TRUE�����ý���,�����෴.
XC_API void WINAPI XEle_EnableFocus(HELE hEle, BOOL bFocus); //��������

/// @brief �Ƿ���ƽ���.
/// @param hEle Ԫ�ؾ��
/// @param bFocus  ���ֵΪTRUE���ƽ���,�����෴.
XC_API void WINAPI XEle_EnableDrawFocus(HELE hEle, BOOL bFocus); //�Ƿ���ƽ���

/// @brief Ԫ�����ù�����ʾ����.
/// @param hEle Ԫ�ؾ��
/// @param bTips TRUE���ù�����ʾ,�����෴
XC_API void WINAPI XEle_EnableToolTips(HELE hEle, BOOL bTips);  //���ù�����ʾ

/// @brief ���û�رջ���Ԫ�ر߿�.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable  ���ΪTRUE����,�����෴.
XC_API void WINAPI XEle_EnableBorder(HELE hEle, BOOL bEnable); //���Ʊ߿�

/// @brief ����͸��ͨ��,������͸��,����Ԫ�ر���͸��ʱ��Ч,��Ҫ�û��Լ�����PNGͼƬ������Ԫ�ص�͸��ͨ��.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable  ���ΪTRUE����,�����෴.
XC_API void WINAPI XEle_EnableTransparentChannel(HELE hEle, BOOL bEnable);

/// @brief ���Ԫ��.���һ����Ԫ��,����ǰԪ����.
/// @param hEle Ԫ�ؾ��.
/// @param hNewEle  Ҫ��ӵ���Ԫ����Դ���.
/// @param flag     ��ʶ.
/// @param hDestEle  hDestEleΪ���Ԫ�ص����λ��;flag��ΪXC_ADDELE_AFTER��XC_ADDELE_BEFORE��ʶʱ��Ч.
/// @param index   Ϊ���Ԫ�صĻ���0����λ��,flag��ΪXC_ADDELE_INDEX��ʶʱ��Ч.
/// @return ����ɹ�����TRUE,�����෴.
XC_API BOOL WINAPI XEle_AddEle(HELE hEle, HELE hNewEle, int flag = XC_ADDELE_END, HELE hDestEle = 0, int index = 0); //���Ԫ��

/// @brief �Ƴ�Ԫ��,���ǲ�����.
/// @param hEle Ԫ�ؾ��.
XC_API void WINAPI XEle_RemoveEle(HELE hEle);   //�Ƴ�Ԫ��,��������

/// @brief �ػ��Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @param bImmediately   TRUE�����ػ�,FALSE������Ϣ�����ӳ��ػ�.
XC_API void WINAPI XEle_RedrawEle(HELE hEle, BOOL bImmediately = FALSE); //�ػ�Ԫ��

/// @brief �ػ�Ԫ��ָ������,�����ػ�,��Ԫ���ػ�ʱ�����������ĸ�Ԫ��,ֻ�е���Ԫ��͸��ʱ,�Ż���Ƹ�Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @param pRect �ػ�����.
XC_API void WINAPI XEle_RedrawRect(HELE hEle, RECT *pRect); //Ԫ���ػ�ָ������

/// @brief ��ʾ����Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @param bShow  TRUE��ʾԪ��,�����෴.
XC_API void WINAPI XEle_ShowEle(HELE hEle, BOOL bShow);

/// @brief �ж�Ԫ�ر����Ƿ�͸��.
/// @param hEle Ԫ�ؾ��
/// @return ���Ԫ�ر���͸������TRUE,�����෴.
XC_API BOOL WINAPI XEle_IsBkTransparent(HELE hEle); //Ԫ�ر����Ƿ�͸��

/// @brief �ж�Ԫ���Ƿ�ӵ�н��� .
/// @param hEle Ԫ�ؾ��
/// @return ���Ԫ��ӵ�н��㷵��TRUE,�����෴.
XC_API BOOL WINAPI XEle_IsFocus(HELE hEle); //Ԫ���Ƿ�ӵ�н���

/// @brief Ԫ���Ƿ���ʾ.
/// @param hEle Ԫ�ؾ��.
/// @return �����ʾ����TRUE,���򷵻�FALSE.
XC_API BOOL WINAPI XEle_IsShowEle(HELE hEle); //Ԫ���Ƿ���ʾ

/// @brief �ж�ָ��������Ƿ�����Ԫ��֮��.
/// @param hEle Ԫ�ؾ��
/// @param pPt  �����λ��.
/// @return ���������Ԫ���Ϸ���TRUE,���򷵻�FALSE.
XC_API BOOL WINAPI XEle_IsHitChildEle(HELE hEle, POINT *pPt); //�ж��Ƿ�������Ԫ����

/// @brief �ж�ָ��Ԫ���Ƿ�Ϊ��Ԫ��.
/// @param hEle Ԫ�ؾ��
/// @param hChild   ��Ԫ�ؾ��.
/// @return hChild�����hEle����Ԫ�ط���TRUE,���򷵻�FALSE.
XC_API BOOL WINAPI XEle_IsChildEle(HELE hEle, HELE hChild);  //�ж�ָ��Ԫ���Ƿ�Ϊ��Ԫ��

/// @brief ����Ԫ���û�����.
/// @param hEle Ԫ�ؾ��.
/// @param data �û�����.
XC_API void WINAPI XEle_SetUserData(HELE hEle, void* data);  //�����û�����

/// @brief ���ö�ʱ��,��ϵͳ��ʱ��.
/// @param hEle       Ԫ�ؾ��.
/// @param nIDEvent   ��ʱ����ʶ��.
/// @param uElapse    ���ʱ�����.
/// @param userData   ������.
/// @param userData   �û�����.
/// @return �ɹ�����TRUE,�����෴.
XC_API UINT WINAPI XEle_SetTimerEx(HELE hEle, UINT nIDEvent, UINT uElapse, void* userData = 0);

/// @brief �رն�ʱ��,��ϵͳ��ʱ��.
/// @param hEle       Ԫ�ؾ��.
/// @param nIDEvent ��ʱ����ʶ��.
/// @return �ɹ�����TRUE,�����෴.
XC_API BOOL WINAPI XEle_KillTimerEx(HELE hEle, UINT nIDEvent);


//����API:
///@name ����
///@{

/// @brief ����Ԫ������.
/// @param hEle Ԫ�ؾ��
/// @param[in] pRect  Ԫ������.
/// @param bRedraw ���ֵΪTRUE�ػ�Ԫ��,�����෴.
XC_API void WINAPI XEle_SetRect(HELE hEle, in_ RECT *pRect, BOOL bRedraw = FALSE);

/// @brief ��ȡԪ�ش�С,���Ͻ�(0,0).
/// @param hEle Ԫ�ؾ��
/// @param[out] pRect  ����Ԫ������.
XC_API void WINAPI XEle_GetClientRect(HELE hEle, out_ RECT *pRect);   //Ԫ�ؿͻ������� xy(0,0) ,���Ԫ���б߿�,�����߿�����

/// @brief ��ȡԪ������,���ڸ�Ԫ������ϵ.
/// @param hEle Ԫ�ؾ��
/// @param[out] pRect  ����Ԫ������.
XC_API void WINAPI XEle_GetRect(HELE hEle, out_ RECT *pRect);         //���ڸ�Ԫ������

/// @brief ��ȡԪ�ػ��ڴ��ڿͻ�������.
/// @param hEle Ԫ�ؾ��
/// @param[out] pRect  ����Ԫ������.
XC_API void WINAPI XEle_GetWndClientRect(HELE hEle, out_ RECT *pRect); //Ԫ�ػ��ڴ��ڿͻ�������(�������ǿͻ���)

/// @brief ��ȡԪ������,���ڴ��ڷǿͻ�������,�����ǿͻ���.
/// @param hEle Ԫ�ؾ��
/// @param[out] pRect  ����Ԫ������.
XC_API void WINAPI XEle_GetNCWndRect(HELE hEle, out_ RECT *pRect); //���ڴ��ڷǿͻ�������(�����ǿͻ���)

/// @Ԫ������,ת������Ԫ������
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pPt  ���������ת�����.
XC_API void WINAPI XEle_PointToParent(HELE hEle, in_out_ POINT *pPt);

/// @brief Ԫ�������ת�������ڿͻ��������,�������ǿͻ���.
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pPt  ���������ת�����.
XC_API void WINAPI XEle_PointToWndClient(HELE hEle, in_out_ POINT *pPt);     //Ԫ�������ת�������ڿͻ��������(�������ǿͻ���)

/// @brief Ԫ�������ת�������ڷǿͻ��������,�����ǿͻ���.
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pPt  ��������ת�����.
XC_API void WINAPI XEle_PointToNCWnd(HELE hEle, in_out_ POINT *pPt);

/// @brief ���ڷǿͻ�������ת����Ԫ������.
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pPt  ������ڴ��ڷǿͻ����������(�����ǿͻ���),�������Ԫ�������.
XC_API void WINAPI XEle_PointNCWndToEle(HELE hEle, in_out_ POINT *pPt);

/// @brief ���ڿͻ�������ת����Ԫ������,�������ǿͻ���.
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pPt  ������ڴ��������(�������ǿͻ���),�������Ԫ�������.
XC_API void WINAPI XEle_PointWndClientToEle(HELE hEle, in_out_ POINT *pPt);

/// @brief Ԫ������ת�������ڿͻ�������,�������ǿͻ���.
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pRect ����Ԫ������,���ػ��ڴ��ڵ�����,�������������ͱ߿�����.
XC_API void WINAPI XEle_RectToWndClient(HELE hEle, in_out_ RECT *pRect);

/// @brief Ԫ������ϵת��Ϊ���ڷǿͻ�������ϵ.
/// @param hEle Ԫ�ؾ��
/// @param[in,out] pRect ����Ԫ�ؿͻ������� ,������ڴ��ڷǿͻ�������,�����������ͱ߿�����.
XC_API void WINAPI XEle_RectToNCWnd(HELE hEle, in_out_ RECT *pRect);


///@}

/// @brief �����ı���ɫ.
/// @param hEle  Ԫ�ؾ��.
/// @param color �ı���ɫ
XC_API void WINAPI XEle_SetTextColor(HELE hEle, COLORREF color); //�����ı���ɫ

/// @brief ��ȡ�ı���ɫ.
/// @param hEle  Ԫ�ؾ��.
/// @return �ı���ɫ
XC_API COLORREF WINAPI XEle_GetTextColor(HELE hEle); //��ȡ�ı���ɫ

/// @brief ������괩͸Ԫ��,��Ԫ�ؽ������������Ϣ,�����Ϣ�Ӹ�Ԫ�ش���;��Ԫ�ؽ��ò�ͬ,���õ�Ԫ�ػ���ֹ�����Ϣ���ܴ�͸.
/// @param hEle  Ԫ�ؾ��.
/// @param bEnable  �Ƿ�����.
XC_API void WINAPI XEle_EnableMouseThrough(HELE hEle, BOOL bEnable);  //������괩͸Ԫ��

///@}


//TODO:���Ľ�
//BOOL Ele_SendEvent(HELE hEle,int type,WPARAM wParam,LPARAM lParam); //�����¼�,�����������ؽ��
//void Ele_PostEvent(HELE hEle,int type,WPARAM wParam,LPARAM lParam); //�����¼�,��ʱ�����޷��ؽ��

BOOL Ele_SendEvent(HELE hEle, int type, WPARAM wParam, LPARAM lParam, BOOL bImmediately = TRUE); //�����¼�
BOOL Ele_SendEleMsg(HELE hEle, UINT eleMessage, WPARAM wParam, LPARAM lParam); //����Ԫ����Ϣ

//˽�з���:
void Ele_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent); //��ʼ��ע��

BOOL Ele_Draw_InspectionArea(HELE hEle, RECT &rect, RECT &rcDest); //����������
void Ele_Draw_Dispatch(HELE hEle, HDRAW hDraw, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
void Ele_Draw_Child(HELE hEle, HDRAW hDraw); //������Ԫ��

BOOL Ele_EventDispatch(HELE hEle, int type, WPARAM wParam, LPARAM lParam); //�¼�����,���ڵ���
BOOL Ele_SetWindow(HELE hEle, HWINDOW hWindow, BOOL bClient = TRUE); //���ø�����
void Ele_BreakWindow(HELE hEle); //�ݹ�Ͽ��봰����ϵ,��Ԫ�ر����븸Ԫ�ع�ϵ,�Ա�����, XEle_RemoveEle()ר��
BOOL Ele_HandleMousePt(HELE hEle, UINT flags, POINT *pPt, int message);  //������갴��/���� 
void Ele_SetType(HELE hEle, int type); //����Ԫ����������

void Ele_HandleScrollView(HELE hEle, HDC hdc, int srcX, int srcY); //���������ͼ


//��Ϣת��:
BOOL Ele_ConvMsgPaint(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgMouseClick(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgMouseDBClick(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgMouseMove(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgLButtonDown(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgLButtonUp(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgRButtonDown(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgRButtonUp(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvMsgTimerEx(HELE hEle, eleMsgOrEvent_Header_ *pMsgHeader, WPARAM wParam, LPARAM lParam);

//�¼�ת��:
BOOL Ele_ConvEventBtnClick(HELE hEle, HELE hEleClick, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventMouseStay(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //���ͣ��
BOOL Ele_ConvEventMouseLeave(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSetFocus(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventKillFocus(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventKeyDown(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventChar(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventHScroll(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventVScroll(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventHScrollView(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventVScrollView(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSetCapture(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //�����겶��
BOOL Ele_ConvEventKillCapture(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //ʧȥ��겶��
BOOL Ele_ConvEventMouseWheel(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);  //�����¼�
BOOL Ele_ConvEventMenuSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);  //�����¼�
BOOL Ele_ConvEventMenuExit(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);  //�����¼�
BOOL Ele_ConvEventListSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListHeaderClick(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //�б�ͷ����
BOOL Ele_ConvEventListHeaderChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //�б�ͷ��ȸı�
BOOL Ele_ConvEventTreeSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //���б�ѡ��ı�
BOOL Ele_ConvEventTreeExpand(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //����չ��������
BOOL Ele_ConvEventComboBoxSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam); //������Ͽ�ѡ���¼�
BOOL Ele_ConvEventComboBoxPopupList(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventComboBoxExitList(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventPPageSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSliderChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventMonthChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventDateTimeChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventDateTimePopupMonthCal(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventDateTimeExitMonthCal(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventSetFont(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventShow(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventSize(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListBoxSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPGridSelChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPGridValueChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventListViewSelect(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListViewExpand(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListViewDragInsert(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventPaneLock(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPaneDock(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventPaneFloat(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

BOOL Ele_ConvEventEditChange(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventComboBoxChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventListBoxChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);
BOOL Ele_ConvEventTreeChanging(HELE hEle, HELE hEventEle, eleMsgOrEvent_Header_ *pHeader, WPARAM wParam, LPARAM lParam);

//�ص�����:
BOOL CALLBACK Ele_WindowProc(HELE hEle, UINT message, WPARAM wParam, LPARAM lParam); //Ԫ����Ϣ�������
BOOL CALLBACK Ele_EventProc(HELE hEle, int type, WPARAM wParam, LPARAM lParam);  //�¼�����

//��Ϣ�ص�
BOOL CALLBACK Ele_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Ele_OnMouseClick(HELE hEle, POINT *pPt);
BOOL CALLBACK Ele_OnMouseDBClick(HELE hEle, POINT *pPt);
BOOL CALLBACK Ele_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Ele_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt);


//�¼��ص�����:
BOOL CALLBACK Ele_OnEventMouseSay(HELE hEle, HELE hEventEle); //���ͣ��
BOOL CALLBACK Ele_OnEventMouseLeave(HELE hEle, HELE hEventEle); //����뿪


//������ʾ
extern HELE g_hTooltipsEle;     //��ǰ��Ϲ�����ʾ��Ԫ��
extern HWINDOW g_hToolTipsWnd;  //������ʾ����
VOID CALLBACK Ele_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
BOOL CALLBACK ToolTips_OnDrawWindow(HWINDOW hWindow, HDRAW hDraw);

#if 0
//�̳�ģ��
struct T1 //����
{
	int data;
	//----------------------
	int  type;    //Ԫ����������
	void *pChild; //����->T2
};

struct T2 //public : T1  //�̳�T1
{
	T1  t1; //�̳�
	//--------------------
	int data;
	//---------------
	void *pChid;  //����->T3
};

struct T3  //public : T2    //�̳�T2
{
	T2 t2; //�̳�
	//-------------------------
	int data;
	//----------------------
	void *pChild;  //����->T4
};
#endif