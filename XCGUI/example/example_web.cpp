/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0

HWINDOW hWindow=NULL;    //����
HELE    hToolBar=NULL;   //������
HXCGUI  hWeb=NULL;       //IE�ؼ�
HELE    hAddrBar=NULL;   //��ַ��
HELE    hAddrEdit=NULL;  //URL��ַ�༭��
HELE    hLinkBar=NULL;   //��ַ������
HELE    hStatus1=NULL;    //״̬:
HELE    hStatus=NULL;    //״̬
HELE    hOpenUrl=NULL;   //ת��URL

#define  ID_MAINPAGE   100  //��ҳ
#define  ID_BAIDU      101  //�ٶ�
#define  ID_GOOGLE     102  //�ȸ�
#define  ID_TAOBAO     103  //�Ա�
#define  ID_OPENURL    104  //ת��
#define  ID_GOFORWARD  105  //ǰ��
#define  ID_GOBACK     106  //����
#define  ID_STOP       107  //��ֹ
#define  ID_REFRESH    108  //ˢ��

//��ַ����URL
void OnAddrEditOpenURL()
{
	wchar_t url[MAX_PATH]={0};
	XEdit_GetText(hAddrEdit,url,MAX_PATH);
	int len=wcslen(url);
	if(len>0)
	{
		XWeb_OpenURL(hWeb,url);
	}
}

BOOL CALLBACK OnButtonClick(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle) return FALSE;

	int id=XEle_GetId(hEle);
	switch(id)
	{
	case ID_MAINPAGE: //��ҳ
		XWeb_OpenURL(hWeb,L"http://www.xcgui.com/");
		break;
	case ID_BAIDU: //�ٶ�
		XWeb_OpenURL(hWeb,L"http://www.baidu.com/");
		break;
	case ID_GOOGLE: //�ȸ�
		XWeb_OpenURL(hWeb,L"https://www.google.com.hk/");
		break;
	case ID_TAOBAO: //�Ա�
		XWeb_OpenURL(hWeb,L"http://www.taobao.com/");
		break;
	case ID_OPENURL:   OnAddrEditOpenURL(); break; //��URL [ת��] XWeb_OpenURL
	case ID_GOFORWARD: XWeb_GoForward(hWeb); break; //��ť [ǰ��] XWeb_GoForward
	case ID_GOBACK:    XWeb_GoBack(hWeb); break; //��ť [����] XWeb_GoBack
	case ID_STOP:      XWeb_Stop(hWeb); break; //��ť [��ֹ] XWeb_Stop
	case ID_REFRESH:   XWeb_Refresh(hWeb); break; //��ť [ˢ��] XWeb_Refresh
	}
	return TRUE;
}

BOOL CALLBACK OnEventKeyDown_AddrEdit(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam)
{
	if(hEle!=hEventEle) return FALSE;

	if(13==wParam) //�س�
	{
		OnAddrEditOpenURL();
	}
	return TRUE;
}

BOOL CALLBACK OnIE_BeforeNavigate2(HXCGUI hWebBrowser,in_ IDispatch *pDisp,in_ wchar_t *pUrl,in_ int Flags,in_ wchar_t *pTargetFrameName,in_ wchar_t *pPostData,in_ wchar_t *pHeaders,in_out_ VARIANT_BOOL *bCancel)
{
	if(pDisp==XWeb_GetControl(hWeb))
	{
		XEdit_SetText(hAddrEdit,pUrl);
		XEle_RedrawEle(hAddrEdit);
	}
	return TRUE;
}

BOOL CALLBACK OnIE_StatusTextChange(HXCGUI hWebBrowser,in_ wchar_t *pText)
{
	if(pText)
	{
		XStatic_SetText(hStatus,pText);
		XEle_RedrawEle(hStatus);
	}
	return TRUE;
}

//��������
void AdjustWindow()
{
	RECT rect;
	XWnd_GetClientRect(hWindow,&rect);

	RECT rc=rect;
	rc.bottom=28;
	XEle_SetRect(hAddrBar,&rc);
	{
		RECT rc1;
		rc1.top=3;
		rc1.bottom=3+22;
		rc1.right=rect.right-10;
		rc1.left=rc1.right-60;
		XEle_SetRect(hOpenUrl,&rc1);

		rc1.right=rc1.left-5;
		rc1.left=46;
		XEle_SetRect(hAddrEdit,&rc1);
	}

	rc.top=rc.bottom;
	rc.bottom=rc.top+28;
	XEle_SetRect(hLinkBar,&rc);

	rc.top=28+28+XWnd_GetClientTop(hWindow);
	rc.bottom=rect.bottom+XWnd_GetClientTop(hWindow);
	rc.left=XWnd_GetClientLeft(hWindow);
	rc.right+=XWnd_GetClientLeft(hWindow);
	XWeb_SetRect(hWeb,&rc);

	//״̬
	RECT rcWindow;
	XWnd_GetWindowRect(hWindow,&rcWindow);
	rc.left=260;
	rc.right=rect.right-20;
	rc.top=rcWindow.bottom-rcWindow.top-20;
	rc.bottom=rc.top+20;

	XEle_SetRect(hStatus1,&rc);
	rc.left+=32;
	XEle_SetRect(hStatus,&rc);
}

BOOL CALLBACK OnWndSize(HWINDOW hWindow,UINT flags,SIZE *pSize)
{
	AdjustWindow();
	return FALSE;
}

LONG_PTR prevProc1=NULL;
HHOOK hHook=NULL;
LRESULT CALLBACK MyWndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(WM_ERASEBKGND==message)
		return 0;

	return CallWindowProc((WNDPROC)prevProc1,hWnd,  message,  wParam,  lParam);
}

LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(HC_ACTION==nCode)
	{
		PCWPSTRUCT pInfo=(PCWPSTRUCT)lParam;
		if(WM_CREATE==pInfo->message)
		{
			char className[101]={0};
			GetClassNameA(pInfo->hwnd,className,100);

			if(0==strcmp(className,"Internet Explorer_Server"))
			{
				prevProc1=GetWindowLongPtr(pInfo->hwnd,GWLP_WNDPROC);
				SetWindowLongPtr(pInfo->hwnd,GWLP_WNDPROC,(LONG_PTR)MyWndProc1);
			}
		}
	}
	return CallNextHookEx(hHook,nCode,wParam,lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //��ʼ�������
	hWindow=XWnd_CreateWindow(0,0,600,480,L"�Ųʽ����-�����");

	hToolBar=XToolBar_Create(0,0,100,70,hWindow);

	HELE hToolBtn1=XToolBarBtn_Create(90,90,L"ǰ��");
	HELE hToolBtn2=XToolBarBtn_Create(20,20,L"����");
	HELE hToolBtn3=XToolBarBtn_Create(20,20,L"��ֹ");
	HELE hToolBtn4=XToolBarBtn_Create(20,20,L"ˢ��");
	HELE hToolBtn5=XToolBarBtn_Create(20,20,L"��ҳ");
	XEle_SetId(hToolBtn1,ID_GOFORWARD);
	XEle_SetId(hToolBtn2,ID_GOBACK);
	XEle_SetId(hToolBtn3,ID_STOP);
	XEle_SetId(hToolBtn4,ID_REFRESH);
	XEle_SetId(hToolBtn5,ID_MAINPAGE);

	XBtn_SetIcon(hToolBtn1,XImage_LoadFile(L"IE/1.png"));
	XBtn_SetIcon(hToolBtn2,XImage_LoadFile(L"IE/2.png"));
	XBtn_SetIcon(hToolBtn3,XImage_LoadFile(L"IE/3.png"));
	XBtn_SetIcon(hToolBtn4,XImage_LoadFile(L"IE/4.png"));
	XBtn_SetIcon(hToolBtn5,XImage_LoadFile(L"IE/5.png"));

	XToolBar_InsertEle(hToolBar,hToolBtn1);
	XToolBar_InsertEle(hToolBar,hToolBtn2);
	XToolBar_InsertSeparator(hToolBar,-1);
	XToolBar_InsertEle(hToolBar,hToolBtn3);
	XToolBar_InsertEle(hToolBar,hToolBtn4);
	XToolBar_InsertEle(hToolBar,hToolBtn5);

    //�Զ�������������ť��С
    XToolBarBtn_Adjust(hToolBtn1);
    XToolBarBtn_Adjust(hToolBtn2);
	XToolBarBtn_Adjust(hToolBtn3);
	XToolBarBtn_Adjust(hToolBtn4);
	XToolBarBtn_Adjust(hToolBtn5);

	RECT rect;
	XWnd_GetClientRect(hWindow,&rect);
	hAddrBar=XEle_Create(0,0,rect.right,28,hWindow);
	XEle_SetBkColor(hAddrBar,RGB(200,200,200));
	
	HELE hStatic=XStatic_Create(10,6,36,20,L"��ַ:",hAddrBar);
	XEle_SetBkColor(hStatic,RGB(200,200,200));

	hAddrEdit=XEdit_Create(46,3,400,22,hAddrBar);

	hOpenUrl=XBtn_Create(480,3,60,22,L"ת��",hAddrBar); //ת��URL
	XEle_SetBkTransparent(hOpenUrl,TRUE);
	XEle_SetId(hOpenUrl,ID_OPENURL);

	hLinkBar=XToolBar_Create(0,28,rect.right,28);
	XWnd_AddEle(hWindow,hLinkBar);

	HELE hLinkUrl1=XTextLink_Create(10,6,110,20,L"�ٶ�һ��,���֪��");
	HELE hLinkUrl2=XTextLink_Create(10,6,40,20,L"Google");
	HELE hLinkUrl3=XTextLink_Create(10,6,86,20,L"�Ա���-��!ϲ��");
	XEle_SetBkTransparent(hLinkUrl1,TRUE);
	XEle_SetBkTransparent(hLinkUrl2,TRUE);
	XEle_SetBkTransparent(hLinkUrl3,TRUE);

	XToolBar_InsertEle(hLinkBar,hLinkUrl1);
	XToolBar_InsertSeparator(hLinkBar,-1);
	XToolBar_InsertEle(hLinkBar,hLinkUrl2);
	XToolBar_InsertSeparator(hLinkBar,-1);
	XToolBar_InsertEle(hLinkBar,hLinkUrl3);

	XToolBar_Adjust(hLinkBar);

	hWeb=XWeb_Create(hWindow,0,56,rect.right,rect.bottom-56); //������ؼ�
	XWeb_OpenURL(hWeb,L"about:blank");
	XEdit_SetText(hAddrEdit,L"about:blank");

	hStatus1=XStatic_Create(260,460,300,20,L"״̬:"); //״̬
	hStatus=XStatic_Create(290,460,300,20,L"״̬"); //״̬
	XWnd_AddEleNC(hWindow,hStatus1);
	XWnd_AddEleNC(hWindow,hStatus);
	XEle_SetBkTransparent(hStatus1,TRUE);
	XEle_SetBkTransparent(hStatus,TRUE);

	XEle_SetId(hLinkUrl1,ID_BAIDU);
	XEle_SetId(hLinkUrl2,ID_GOOGLE);
	XEle_SetId(hLinkUrl3,ID_TAOBAO);
	XEle_RegisterEvent(hLinkUrl1,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hLinkUrl2,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hLinkUrl3,XE_BNCLICK,OnButtonClick);

	XEle_RegisterEvent(hToolBtn1,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hToolBtn2,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hToolBtn3,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hToolBtn4,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hToolBtn5,XE_BNCLICK,OnButtonClick);
	XEle_RegisterEvent(hOpenUrl,XE_BNCLICK,OnButtonClick);

	XEle_RegisterEvent(hAddrEdit,XE_KEYDOWN,OnEventKeyDown_AddrEdit);

	XWeb_RegEvent(hWeb,IE_BEFORENAVIGATE2,OnIE_BeforeNavigate2);
	XWeb_RegEvent(hWeb,IE_STATUSTEXTCHANGE,OnIE_StatusTextChange);

	XWnd_RegisterMessage(hWindow,WM_SIZE,OnWndSize);

	AdjustWindow();
	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����

	hHook=SetWindowsHookEx(WH_CALLWNDPROC,CallWndProc,NULL,GetCurrentThreadId());

	XRunXCGUI(); //����

	UnhookWindowsHookEx(hHook);

	return 0;
}
#endif

#if 0
//IE�ؼ�����
HXCGUI hWeb=NULL;
BOOL CALLBACK OnButtonClick_OpenURL(HELE hEle,HELE hEventEle)
{
//	XWeb_OpenURL(hWeb,L"C:\\test.html"); //�򿪱����ļ�
	XWeb_OpenURL(hWeb,L"http://www.baidu.com/");
	return TRUE;
}

BOOL CALLBACK OnButtonClick_Destroy(HELE hEle,HELE hEventEle)
{
	XWeb_Destroy(hWeb); //����������ؼ�
	return TRUE;
}

//ִ��js�ű�����
BOOL CALLBACK OnButtonClick_ExeScript(HELE hEle,HELE hEventEle)
{
	wchar_t  params1[10]=L"a";
	wchar_t  params2[10]=L"b";
	wchar_t  params3[10]=L"c";

	wchar_t  *params[3];
	params[0]=params1;
	params[1]=params2;
	params[2]=params3;
	XWeb_ExeJavascript(hWeb,L"exeTest",params,3);
	return TRUE;
}

//����
BOOL CALLBACK OnBeforeNavigate2_My(HXCGUI hWebBrowser,IDispatch *pDisp,wchar_t *pUrl,int Flags,wchar_t *TargetFrameName,wchar_t *PostData,wchar_t *Headers,VARIANT_BOOL *bCancel)
{
	return TRUE;
}

//JS�ⲿ����,JS����C/C++����
BOOL CALLBACK OnIE_External1(HXCGUI hWebBrowser,HSTRING hResultVal,wchar_t *pParam1)
{
	wchar_t *result=XStr_GetBuffer(hResultVal);
	XStr_SetString(hResultVal,L"568"); //���÷���ֵ
	return TRUE;
}

//JS�ⲿ����,JS����C/C++����
BOOL CALLBACK OnIE_External2(HXCGUI hWebBrowser,HSTRING hResultVal,wchar_t *pParam1,wchar_t *pParam2)
{
	wchar_t *result=XStr_GetBuffer(hResultVal);
	XStr_SetString(hResultVal,L"777"); //���÷���ֵ
	return TRUE;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //��ʼ�������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,420,310,L"�Ųʽ����-IE�ؼ�����");

	HELE hButtonOpenURL=XBtn_Create(320,10,70,22,L"��HTML",hWindow);
	HELE hButtonDestroy=XBtn_Create(320,50,70,22,L"����",hWindow);
	HELE hExeScript=XBtn_Create(320,90,70,22,L"ִ��js����",hWindow);

	hWeb=XWeb_Create(hWindow,10,10,300,230); //������ؼ�

	XWeb_RegEvent(hWeb,IE_BEFORENAVIGATE2,OnBeforeNavigate2_My); //ע�ᵼ���¼�
	XWeb_RegExternalFunction1(hWeb,L"Test",OnIE_External1); //ע���ⲿ����
	XWeb_RegExternalFunction2(hWeb,L"Test2",OnIE_External2); //ע���ⲿ����

	XEle_RegisterEvent(hButtonOpenURL,XE_BNCLICK,OnButtonClick_OpenURL);
	XEle_RegisterEvent(hButtonDestroy,XE_BNCLICK,OnButtonClick_Destroy);
	XEle_RegisterEvent(hExeScript,XE_BNCLICK,OnButtonClick_ExeScript);

	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����
	XRunXCGUI(); //����

	return 0;
}
#endif