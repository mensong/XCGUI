/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

int             g_com_refCount = 0; //引用计数,当引用计数为0时,释放CComModule
CComModule      *g_com_pModule = NULL;
void XCom_Add()
{
	if (0 == g_com_refCount)
	{
		CoInitialize(NULL);
		g_com_pModule = new CComModule;
	}
	g_com_refCount++;
}

void XCom_Release()
{
	g_com_refCount--;
	if (0 == g_com_refCount)
	{
		CoUninitialize();
		delete g_com_pModule;
		g_com_pModule = NULL;
	}
}

void XCom_AppExit()
{
	g_com_refCount = 0;
	if (g_com_pModule)
	{
		delete g_com_pModule;
		g_com_pModule = NULL;
	}
}

int XCom_GetCount()
{
	return g_com_refCount;
}

////////////////////////////////////////////////////////////////

CMyAxWindow::CMyAxWindow()
{
	m_pWebBrowser = NULL;
}

void CMyAxWindow::SetWebBrowser(webBrowser_ *pWebBrowser)
{
	m_pWebBrowser = pWebBrowser;
}

LRESULT CMyAxWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return S_OK;
}

void CMyAxWindow::OnFinalMessage(HWND /*hWnd*/)
{
	if (m_pWebBrowser)
	{
		Web_OnDestroy(m_pWebBrowser);
		delete m_pWebBrowser;
	}
}

//////////////////////////////////////////
CIEEvent::CIEEvent()
{
	m_pWebBrowser = NULL;
	m_refCount = 0;
}

void CIEEvent::SetWebBrowser(webBrowser_ *pWebBrowser)
{
	m_pWebBrowser = pWebBrowser;
}

HRESULT STDMETHODCALLTYPE CIEEvent::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown || riid == IID_IDispatch)
	{
		AddRef();
		*ppvObject = this;
		return S_OK;
	}
	else
	{
		ppvObject = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

ULONG STDMETHODCALLTYPE CIEEvent::AddRef(void)
{
	m_refCount++;
	return m_refCount;
}

ULONG STDMETHODCALLTYPE CIEEvent::Release(void)
{
	m_refCount--;
	return m_refCount;
}

HRESULT STDMETHODCALLTYPE CIEEvent::GetTypeInfoCount(
	/* [out] */ __RPC__out UINT *pctinfo)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CIEEvent::GetTypeInfo(
	/* [in] */ UINT iTInfo,
	/* [in] */ LCID lcid,
	/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CIEEvent::GetIDsOfNames(
	/* [in] */ __RPC__in REFIID riid,
	/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
	/* [range][in] */ UINT cNames,
	/* [in] */ LCID lcid,
	/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	return E_NOTIMPL;
}
/* [local] */ HRESULT STDMETHODCALLTYPE CIEEvent::Invoke(
	/* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS *pDispParams,
	/* [out] */ VARIANT *pVarResult,
	/* [out] */ EXCEPINFO *pExcepInfo,
	/* [out] */ UINT *puArgErr)
{

	switch (dispIdMember)
	{
	case DISPID_BEFORENAVIGATE2:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_BEFORENAVIGATE2);
		if (pHeader)
		{
			IDispatch *pDisp = pDispParams->rgvarg[6].pdispVal;
			wchar_t *pUrl = pDispParams->rgvarg[5].pvarVal->bstrVal; //((VARIANT*)pDispParams->rgvarg[5].byref)->bstrVal;
			int Flags = pDispParams->rgvarg[4].pvarVal->intVal; //((VARIANT*)pDispParams->rgvarg[4].byref)->intVal;
			wchar_t *TargetFrameName = pDispParams->rgvarg[3].pvarVal->bstrVal; //((VARIANT*)pDispParams->rgvarg[3].byref)->bstrVal;
			wchar_t *PostData = pDispParams->rgvarg[2].pvarVal->bstrVal;//((VARIANT*)pDispParams->rgvarg[2].byref)->bstrVal;
			wchar_t *Headers = pDispParams->rgvarg[1].pvarVal->bstrVal;//((VARIANT*)pDispParams->rgvarg[1].byref)->bstrVal;
			VARIANT_BOOL *bCancel = pDispParams->rgvarg[0].pboolVal;

			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_BeforeNavigate2)pEvent->pFun)(m_pWebBrowser, pDisp, pUrl, Flags, TargetFrameName, PostData, Headers, bCancel))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_CLIENTTOHOSTWINDOW:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_CLIENTTOHOSTWINDOW);
		if (pHeader)
		{
			long *pCx = pDispParams->rgvarg[1].plVal;//cx
			long *pCy = pDispParams->rgvarg[0].plVal;//cy
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_ClientToHostWindow)pEvent->pFun)(m_pWebBrowser, pCx, pCy))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_COMMANDSTATECHANGE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_COMMANDSTATECHANGE);
		if (pHeader)
		{
			long         Command = pDispParams->rgvarg[1].lVal;
			VARIANT_BOOL Enable = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_CommandStateChange)pEvent->pFun)(m_pWebBrowser, Command, Enable))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_DOCUMENTCOMPLETE:
	{
		CComPtr<IHTMLDocument2> pDoc;
		CComPtr<ICustomDoc> pCustomDoc;

		IDispatch  *pDisp = NULL;
		HRESULT hr = m_pWebBrowser->m_pIWebBrowser->get_Document((IDispatch **)&pDisp);
		if (S_OK == hr)
		{
			hr = pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc);
			if (S_OK != hr) return S_FALSE;
			//----------------------------------------

			hr = pDoc->QueryInterface(IID_ICustomDoc, (void**)&pCustomDoc);
			if (S_OK != hr) return S_FALSE;

			hr = pCustomDoc->SetUIHandler(&m_pWebBrowser->docHostUIHandler);
			if (S_OK != hr) return S_FALSE;

			//---------------------------------------
			IConnectionPointContainer *pCPContainer = NULL;
			hr = pDoc->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPContainer);
			if (S_OK != hr) return S_FALSE;

			IConnectionPoint *m_pConnectionPoint = NULL;
			hr = pCPContainer->FindConnectionPoint(DIID_HTMLDocumentEvents2, &m_pConnectionPoint);
			if (S_OK != hr) return S_FALSE;

			DWORD m_dwCookie;
			hr = m_pConnectionPoint->Advise(&m_pWebBrowser->m_event, &m_dwCookie);
			if (S_OK != hr) return S_FALSE;

			ULONG ulong = pCPContainer->Release();
			ulong = m_pConnectionPoint->Release();

			pDisp->Release();
		}
		{
			IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_DOCUMENTCOMPLETE);
			if (pHeader)
			{
				IDispatch *pDisp = pDispParams->rgvarg[1].pdispVal;
				wchar_t *pURL = pDispParams->rgvarg[0].pvarVal->bstrVal;
				IE_Event_ *pEvent = pHeader->pList;
				while (pEvent)
				{
					if (TRUE == ((pFunIE_DocumentComplete)pEvent->pFun)(m_pWebBrowser, pDisp, pURL))
						return S_OK;

					pEvent = pEvent->pNext;
				}
			}
		}
		XTRACE("文档 完成 \n");
	}break;
	case DISPID_DOWNLOADBEGIN:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_DOWNLOADBEGIN);
		if (pHeader)
		{
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_DownloadBegin)pEvent->pFun)(m_pWebBrowser))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_DOWNLOADCOMPLETE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_DOWNLOADCOMPLETE);
		if (pHeader)
		{
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_DownloadComplete)pEvent->pFun)(m_pWebBrowser))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
		XTRACE("下载 完成 \n");
	}break;
	case DISPID_FILEDOWNLOAD:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_FILEDOWNLOAD);
		if (pHeader)
		{
			VARIANT_BOOL ActiveDocument = pDispParams->rgvarg[1].boolVal;
			VARIANT_BOOL *Cancel = pDispParams->rgvarg[0].pboolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_FileDownload)pEvent->pFun)(m_pWebBrowser, ActiveDocument, Cancel))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_NAVIGATECOMPLETE2:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_NAVIGATECOMPLETE2);
		if (pHeader)
		{
			IDispatch *pDisp = pDispParams->rgvarg[1].pdispVal;
			wchar_t *pUrl = pDispParams->rgvarg[0].pvarVal->bstrVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_NavigateComplete2)pEvent->pFun)(m_pWebBrowser, pDisp, pUrl))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_NAVIGATEERROR:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_NAVIGATEERROR);
		if (pHeader)
		{
			IDispatch *pDisp = pDispParams->rgvarg[4].pdispVal;
			wchar_t *pUrl = pDispParams->rgvarg[3].pvarVal->bstrVal;
			wchar_t *TargetFrameName = pDispParams->rgvarg[2].pvarVal->bstrVal;
			int StatusCode = pDispParams->rgvarg[1].pvarVal->intVal;
			VARIANT_BOOL *Cancel = pDispParams->rgvarg[0].pvarVal->pboolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_NavigateError)pEvent->pFun)(m_pWebBrowser, pDisp, pUrl, TargetFrameName, StatusCode, Cancel))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_NEWWINDOW2:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_NEWWINDOW2);
		if (pHeader)
		{
			IDispatch **ppDisp = pDispParams->rgvarg[1].ppdispVal;
			VARIANT_BOOL *Cancel = pDispParams->rgvarg[0].pboolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_NewWindow2)pEvent->pFun)(m_pWebBrowser, ppDisp, Cancel))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_NEWWINDOW3:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_NEWWINDOW3);
		if (pHeader)
		{
			IDispatch **ppDisp = pDispParams->rgvarg[4].ppdispVal;
			VARIANT_BOOL *Cancel = pDispParams->rgvarg[3].pboolVal;
			DWORD dwFlags = pDispParams->rgvarg[2].intVal;
			wchar_t* bstrUrlContext = pDispParams->rgvarg[1].bstrVal;
			wchar_t* bstrUrl = pDispParams->rgvarg[0].bstrVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_NewWindow3)pEvent->pFun)(m_pWebBrowser, ppDisp, Cancel, dwFlags, bstrUrlContext, bstrUrl))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONFULLSCREEN:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONFULLSCREEN);
		if (pHeader)
		{
			VARIANT_BOOL FullScreen = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnFullScreen)pEvent->pFun)(m_pWebBrowser, FullScreen))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONMENUBAR:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONMENUBAR);
		if (pHeader)
		{
			VARIANT_BOOL MenuBar = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnMenuBar)pEvent->pFun)(m_pWebBrowser, MenuBar))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONQUIT:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONQUIT);
		if (pHeader)
		{
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnQuit)pEvent->pFun)(m_pWebBrowser))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONSTATUSBAR:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONSTATUSBAR);
		if (pHeader)
		{
			VARIANT_BOOL StatusBar = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnStatusBar)pEvent->pFun)(m_pWebBrowser, StatusBar))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONTHEATERMODE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONTHEATERMODE);
		if (pHeader)
		{
			VARIANT_BOOL TheaterMode = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnTheaterMode)pEvent->pFun)(m_pWebBrowser, TheaterMode))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONTOOLBAR:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONTOOLBAR);
		if (pHeader)
		{
			VARIANT_BOOL ToolBar = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnToolBar)pEvent->pFun)(m_pWebBrowser, ToolBar))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_ONVISIBLE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_ONVISIBLE);
		if (pHeader)
		{
			VARIANT_BOOL Visible = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_OnVisible)pEvent->pFun)(m_pWebBrowser, Visible))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_PRINTTEMPLATEINSTANTIATION:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_PRINTTEMPLATEINSTANTIATION);
		if (pHeader)
		{
			IDispatch *pDisp = pDispParams->rgvarg[0].pdispVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_PrintTemplateInstantiation)pEvent->pFun)(m_pWebBrowser, pDisp))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_PRINTTEMPLATETEARDOWN:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_PRINTTEMPLATETEARDOWN);
		if (pHeader)
		{
			IDispatch *pDisp = pDispParams->rgvarg[0].pdispVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_PrintTemplateTeardown)pEvent->pFun)(m_pWebBrowser, pDisp))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_PRIVACYIMPACTEDSTATECHANGE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_PRIVACYIMPACTEDSTATECHANGE);
		if (pHeader)
		{
			VARIANT_BOOL PrivacyImpacted = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_PrivacyImpactedStateChange)pEvent->pFun)(m_pWebBrowser, PrivacyImpacted))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_PROGRESSCHANGE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_PROGRESSCHANGE);
		if (pHeader)
		{
			long Progress = pDispParams->rgvarg[1].lVal;
			long ProgressMax = pDispParams->rgvarg[0].lVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_ProgressChangee)pEvent->pFun)(m_pWebBrowser, Progress, ProgressMax))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_PROPERTYCHANGE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_PROPERTYCHANGE);
		if (pHeader)
		{
			wchar_t* szProperty = pDispParams->rgvarg[0].bstrVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_PropertyChange)pEvent->pFun)(m_pWebBrowser, szProperty))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_SETPHISHINGFILTERSTATUS:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_SETPHISHINGFILTERSTATUS);
		if (pHeader)
		{
			long PhishingFilterStatus = pDispParams->rgvarg[0].lVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_SetPhishingFilterStatus)pEvent->pFun)(m_pWebBrowser, PhishingFilterStatus))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_SETSECURELOCKICON:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_SETSECURELOCKICON);
		if (pHeader)
		{
			signed int SecureLockIcon = pDispParams->rgvarg[0].intVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_SetSecureLockIcon)pEvent->pFun)(m_pWebBrowser, SecureLockIcon))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_STATUSTEXTCHANGE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_STATUSTEXTCHANGE);
		if (pHeader)
		{
			wchar_t* Text = pDispParams->rgvarg[0].bstrVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_StatusTextChange)pEvent->pFun)(m_pWebBrowser, Text))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_TITLECHANGE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_TITLECHANGE);
		if (pHeader)
		{
			wchar_t* Text = pDispParams->rgvarg[0].bstrVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_TitleChange)pEvent->pFun)(m_pWebBrowser, Text))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWCLOSING:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWCLOSING);
		if (pHeader)
		{
			VARIANT_BOOL IsChildWindow = pDispParams->rgvarg[1].boolVal;
			VARIANT_BOOL *Cancel = pDispParams->rgvarg[0].pboolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowClosing)pEvent->pFun)(m_pWebBrowser, IsChildWindow, Cancel))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWSETHEIGHT:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWSETHEIGHT);
		if (pHeader)
		{
			long Height = pDispParams->rgvarg[0].lVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowSetHeight)pEvent->pFun)(m_pWebBrowser, Height))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWSETLEFT:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWSETLEFT);
		if (pHeader)
		{
			long Left = pDispParams->rgvarg[0].lVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowSetLeft)pEvent->pFun)(m_pWebBrowser, Left))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWSETRESIZABLE:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWSETRESIZABLE);
		if (pHeader)
		{
			VARIANT_BOOL Resizable = pDispParams->rgvarg[0].boolVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowSetResizable)pEvent->pFun)(m_pWebBrowser, Resizable))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWSETTOP:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWSETTOP);
		if (pHeader)
		{
			long Top = pDispParams->rgvarg[0].lVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowSetTop)pEvent->pFun)(m_pWebBrowser, Top))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWSETWIDTH:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWSETWIDTH);
		if (pHeader)
		{
			long Width = pDispParams->rgvarg[0].lVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowSetWidth)pEvent->pFun)(m_pWebBrowser, Width))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	case DISPID_WINDOWSTATECHANGED:
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)GetEventHeader(IE_WINDOWSTATECHANGED);
		if (pHeader)
		{
			DWORD dwFlags = pDispParams->rgvarg[1].ulVal;
			DWORD dwValidFlagsMask = pDispParams->rgvarg[0].ulVal;
			IE_Event_ *pEvent = pHeader->pList;
			while (pEvent)
			{
				if (TRUE == ((pFunIE_WindowStateChanged)pEvent->pFun)(m_pWebBrowser, dwFlags, dwValidFlagsMask))
					return S_OK;

				pEvent = pEvent->pNext;
			}
		}
	}break;
	}
	return S_OK;
}

void *CIEEvent::GetEventHeader(int Event)
{
	int count = XArray_GetCount(m_pWebBrowser->hArray_event);
	for (int i = 0; i < count; i++)
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)XArray_GetAt(m_pWebBrowser->hArray_event, i);
		if (Event == pHeader->Event)
		{
			return pHeader;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////
/// @defgroup webBrowser 浏览器控件
/// @ingroup groupOther
/// @{

/// @brief 创建浏览器控件.
/// @param hWindow 父窗口句柄.
/// @param x   控件x坐标.
/// @param y   控件y坐标.
/// @param cx  宽度.
/// @param cy  高度.
/// @return 浏览器控件句柄.
HXCGUI WINAPI XWeb_Create(HWINDOW hWindow, int x, int y, int cx, int cy)
{
	IsWindowDebug(hWindow, __FUNCTION__);

	HWND hWnd = XWnd_GetHWnd(hWindow);
	if (NULL == hWnd) return NULL;

	webBrowser_ *pObject = new webBrowser_;
	pObject->hArray_event = XArray_Create();
	pObject->hArray_external = XArray_Create();


	XCom_Add();

	RECT rect;
	rect.left = XWnd_GetClientLeft(hWindow) + x;
	rect.top = XWnd_GetClientTop(hWindow) + y;
	rect.right = rect.left + cx;
	rect.bottom = rect.top + cy;

	LPOLESTR pszName = OLESTR("shell.Explorer.2");
	if (pObject->m_axWindow.Create(hWnd, rect, OLE2T(NULL), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS))
	{
		if (S_OK == pObject->m_axWindow.CreateControl(pszName))
		{
			if (S_OK == pObject->m_axWindow.QueryControl(__uuidof(IWebBrowser2), (void**)&pObject->m_pIWebBrowser))
			{
				pObject->m_axWindow.SetWebBrowser(pObject);

				IConnectionPointContainer *pCPContainer = NULL;
				HRESULT hr = pObject->m_axWindow.QueryControl(IID_IConnectionPointContainer, (void**)&pCPContainer);

				IConnectionPoint *m_pConnectionPoint = NULL;
				hr = pCPContainer->FindConnectionPoint(DIID_DWebBrowserEvents2, &m_pConnectionPoint);

				DWORD m_dwCookie;
				hr = m_pConnectionPoint->Advise(&pObject->m_event, &m_dwCookie);

				ULONG ulong = pCPContainer->Release();
				ulong = m_pConnectionPoint->Release();

				pObject->m_event.SetWebBrowser(pObject);
				pObject->docHostUIHandler.SetWebBrowser(pObject);
				pObject->external.SetWebBrowser(pObject);

				//		pObject->m_event.pWebBrowser=pObject;
				return pObject;
			}
		}
		return pObject;
	}
	XCom_Release();
	delete pObject;
	return NULL;
}

/// @brief 打开网页.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pUrl 打开网页URL.
BOOL WINAPI XWeb_OpenURL(HXCGUI hWebBrowser, wchar_t *pUrl)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;

	VARIANT varMyURL;
	VariantInit(&varMyURL);
	varMyURL.vt = VT_BSTR;
	varMyURL.bstrVal = SysAllocString(pUrl);
	HRESULT hr = pObject->m_pIWebBrowser->Navigate2(&varMyURL, 0, 0, 0, 0);
	SysFreeString(varMyURL.bstrVal);
	VariantClear(&varMyURL);

	if (S_OK == hr)
		return TRUE;
	return FALSE;
}

/// @brief 显示或隐藏浏览器控件.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bShow 如果为TRUE显示,否则隐藏.
void WINAPI XWeb_Show(HXCGUI hWebBrowser, BOOL bShow)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	if (bShow)
		pObject->m_axWindow.ShowWindow(SW_SHOW);
	else
		pObject->m_axWindow.ShowWindow(SW_HIDE);
}

/// @brief 获取浏览器控件容器(CAxWindow)HWND句柄.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 返回HWND句柄.
HWND WINAPI XWeb_GetHWnd(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_axWindow.m_hWnd;
}

/// @brief 获取浏览器控件COM接口IWebBrowser2指针.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 返回IWebBrowser2接口指针. 例如:IWebBrowser2 *pWebBrowser=(IWebBrowser2*)XWeb_GetControl(hWebBrowser);
void* WINAPI XWeb_GetControl(HXCGUI hWebBrowser) //获取控件接口
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser;
}

/// @brief 获取容器对象指针CAxWindow*.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 返回CAxWindow对象指针. 例如:CAxWindow *pCAxWindow=(CAxWindow*)XWeb_GetCAxWindow(hWebBrowser);
void* WINAPI XWeb_GetCAxWindow(HXCGUI hWebBrowser) //获取容器对象指针CAxWindow*
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return &pObject->m_axWindow;
}

/// @brief 销毁浏览器控件.
/// @param hWebBrowser 浏览器控件句柄.
void WINAPI XWeb_Destroy(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;

	//Web_OnDestroy(hWebBrowser);

	///////////////////////////////////////////
	pObject->m_axWindow.DestroyWindow();
	XCom_Release();
}

/// @brief 获取客户区坐标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pRect 接收返回的坐标.
/// @return 如果成功返回TRUE,失败FALSE.
BOOL WINAPI XWeb_GetClientRect(HXCGUI hWebBrowser, out_ RECT *pRect) //获取坐标
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_axWindow.GetClientRect(pRect);
}

/// @brief 设置坐标,相对于父窗口坐标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pRect 新的坐标.
/// @return 如果成功返回TRUE,失败FALSE.
BOOL WINAPI XWeb_SetRect(HXCGUI hWebBrowser, in_ RECT *pRect) //设置坐标
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_axWindow.MoveWindow(pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top);
}

/// @brief 执行js脚本.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFun 函数名.
/// @param pParam 参数数组.
/// @param paramCount 参数数量.
/// @return 如果成功返回TRUE,失败FALSE.
BOOL WINAPI XWeb_ExeJavascript(HXCGUI hWebBrowser, wchar_t *pFun, wchar_t* pParam[], int paramCount)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;

	CComPtr<IHTMLDocument2>    pDoc;
	IDispatch  *pDisp = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_Document((IDispatch **)&pDisp);
	if (S_OK == hr)
	{
		hr = pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc);

		pDisp->Release();
	}
	else
		return FALSE;

#if 0
	///////////////////////////////////////////
	///子框架页面文档

	IHTMLFramesCollection2* pFramesCol;
	hr = pDoc->get_frames(&pFramesCol);
	if (SUCCEEDED(hr))
	{
		long lo = 0;
		pFramesCol->get_length(&lo);

		VARIANT frameRequested;
		VARIANT frameOut;

		frameRequested.vt = VT_BSTR;
		frameRequested.bstrVal = L"jerichotabiframe_1";
		//	frameRequested.vt=VT_I4;
		//	frameRequested.intVal=1;

		hr = pFramesCol->item(&frameRequested, &frameOut);
		if (SUCCEEDED(hr))
		{
			IHTMLWindow2* pRightFrameWindow = NULL;
			hr = V_DISPATCH(&frameOut)->QueryInterface(IID_IHTMLWindow2,
				(void**)&pRightFrameWindow);
			//BSTR Bname;
			//pRightFrameWindow->get_name(&Bname);

			if (SUCCEEDED(hr))
			{
				IHTMLDocument2* pRightDoc;
				hr = pRightFrameWindow->get_document(&pRightDoc);
				if (SUCCEEDED(hr))
				{
					// Use the document
					//测试调用JS
					CComPtr<IDispatch>  pScript;
					hr = pRightDoc->get_Script(&pScript);

					CComBSTR bstrMember(pFun);////L"load_server");
					DISPID dispid = NULL;
					hr = pScript->GetIDsOfNames(IID_NULL, &bstrMember, 1,
						LOCALE_SYSTEM_DEFAULT, &dispid);

					//BSTR bstr1 = SysAllocString(L"This is a BSTR in a VARIANT.");

					DISPPARAMS dispparams;
					memset(&dispparams, 0, sizeof dispparams);
					dispparams.cArgs = paramCount;
					//	dispparams.rgvarg     = new VARIANT[1];
					dispparams.cNamedArgs = 0;

					dispparams.rgvarg = new VARIANT[paramCount];
					for (int i = 0; i < paramCount; i++)
					{
						dispparams.rgvarg[i].vt = VT_BSTR;
						dispparams.rgvarg[i].bstrVal = SysAllocString(pParam[i]);
					}

					//	dispparams.rgvarg[0].vt = VT_BSTR;
					//dispparams.rgvarg[0].bstrVal=bstr1;

					EXCEPINFO excepInfo;
					memset(&excepInfo, 0, sizeof excepInfo);
					UINT nArgErr = (UINT)-1;      // initialize to invalid arg
					CComVariant vaResult;
					hr = pScript->Invoke(dispid, IID_NULL, 0,
						DISPATCH_METHOD, &dispparams,
						&vaResult, &excepInfo, &nArgErr);

					//SysFreeString(bstr1);
					for (int i = 0; i < paramCount; i++)
					{
						SysFreeString(dispparams.rgvarg[i].bstrVal);
					}
					delete[] dispparams.rgvarg;

					if (FAILED(hr))
					{
						::MessageBox(NULL, L"执行脚本失败!", L"提示", 0);
						//			ShowError(GetSystemErrorMessage(hr));
						return;
					}

					pRightDoc->Release();
				}
				pRightFrameWindow->Release();
			}
		}
		pFramesCol->Release();
	}
#endif
	///////////////////////////////////////

	//调用JS
	CComPtr<IDispatch>  pScript;
	hr = pDoc->get_Script(&pScript);

	CComBSTR bstrMember(pFun);////L"load_server");
	DISPID dispid = NULL;
	hr = pScript->GetIDsOfNames(IID_NULL, &bstrMember, 1,
		LOCALE_SYSTEM_DEFAULT, &dispid);

	if (dispid < 0)
	{
		::MessageBox(NULL, L"没有找到JS函数!", L"提示", 0);
		//	exit(0);
		return FALSE;
	}
	//BSTR bstr1 = SysAllocString(L"This is a BSTR in a VARIANT.");

	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = paramCount;
	//	dispparams.rgvarg     = new VARIANT[1];
	dispparams.cNamedArgs = 0;

	dispparams.rgvarg = new VARIANT[paramCount];
	for (int i = 0; i < paramCount; i++)
	{
		dispparams.rgvarg[paramCount - i - 1].vt = VT_BSTR;
		dispparams.rgvarg[paramCount - i - 1].bstrVal = SysAllocString(pParam[i]);
	}

	//	dispparams.rgvarg[0].vt = VT_BSTR;
	//dispparams.rgvarg[0].bstrVal=bstr1;

	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
	UINT nArgErr = (UINT)-1;      // initialize to invalid arg
	CComVariant vaResult;
	hr = pScript->Invoke(dispid, IID_NULL, 0,
		DISPATCH_METHOD, &dispparams,
		&vaResult, &excepInfo, &nArgErr);

	//SysFreeString(bstr1);
	for (int i = 0; i < paramCount; i++)
	{
		SysFreeString(dispparams.rgvarg[i].bstrVal);
	}
	delete[] dispparams.rgvarg;

	if (FAILED(hr))
	{
		::MessageBox(NULL, L"执行脚本失败!", L"提示", 0);
		//ShowError(GetSystemErrorMessage(hr));
		return FALSE;
	}
	return TRUE;
}

void Web_OnDestroy(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;

	//IE事件数组表
	int Array_event_count = Array_GetCount(pObject->hArray_event);
	for (int i = 0; i < Array_event_count; i++)
	{
		IE_Event_Header_ *pHeader = (IE_Event_Header_*)Array_GetAt(pObject->hArray_event, i);
		IE_Event_ *pEvent = pHeader->pList;
		IE_Event_ *pDel = NULL;
		while (pEvent)
		{
			pDel = pEvent;
			pEvent = pEvent->pNext;

			//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			//			if(pDel->pClass_Fun_Info) free(pDel->pClass_Fun_Info);
			//#endif

			free(pDel);
		}
		free(pHeader);
	}
	XArray_Destroy(pObject->hArray_event);

	//IE外部函数数组表
	int Array_external_count = Array_GetCount(pObject->hArray_external);
	for (int i = 0; i < Array_external_count; i++)
	{
		IE_External_Header_ *pHeader = (IE_External_Header_*)Array_GetAt(pObject->hArray_external, i);
		IE_External_ *pEvent = pHeader->pList;
		IE_External_ *pDel = NULL;
		while (pEvent)
		{
			pDel = pEvent;
			pEvent = pEvent->pNext;

			//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
			//			if(pDel->pClass_Fun_Info) free(pDel->pClass_Fun_Info);
			//#endif

			free(pDel);
		}
		XStr_Destroy(pHeader->hString_Name);
		free(pHeader);
	}
	XArray_Destroy(pObject->hArray_external);
}

/// @brief 注册IE事件.
/// @param hWebBrowser 浏览器控件句柄.
/// @param type 事件类型.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegEvent(HXCGUI hWebBrowser, int type, void *pFun) //注册IE事件
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;

	//------新事件机制
	BOOL bResult = FALSE;
	int index = -1; //插入位置
	int count = Array_GetCount(pObject->hArray_event);
	if (0 == count) //需要消息头
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		if (type == ((IE_Event_Header_*)Array_GetAt(pObject->hArray_event, i))->Event)
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //需要消息头
	{
		IE_Event_Header_  *pHeader = (IE_Event_Header_*)malloc(sizeof(IE_Event_Header_));
		pHeader->Event = type;

		IE_Event_ *pMsg = (IE_Event_*)malloc(sizeof(IE_Event_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;

		//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		//		pMsg->pClass_Fun_Info=NULL;
		//#endif
		pHeader->pList = pMsg;

		//TODO:排序
		XArray_Add(pObject->hArray_event, pHeader);

	}
	else //不需要消息头
	{
		IE_Event_ *pEvent = (IE_Event_*)malloc(sizeof(IE_Event_));
		pEvent->pFun = pFun;
		pEvent->pNext = NULL;

		//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		//		pMsg->pClass_Fun_Info=NULL;
		//#endif
		IE_Event_Header_  *pHeader = (IE_Event_Header_*)Array_GetAt(pObject->hArray_event, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pEvent;
		}
		else  //插入到首位
		{
			pEvent->pNext = pHeader->pList;
			pHeader->pList = pEvent;
		}
	}
}

/// @brief 注册js外部函数,0个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction0(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External0 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 0);
}

/// @brief 注册js外部函数,1个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction1(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External1 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 1);
}

/// @brief 注册js外部函数,2个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction2(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External2 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 2);
}

/// @brief 注册js外部函数,3个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction3(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External3 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 3);
}

/// @brief 注册js外部函数,4个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction4(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External4 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 4);
}

/// @brief 注册js外部函数,5个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction5(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External5 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 5);
}

/// @brief 注册js外部函数,6个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction6(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External6 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 6);
}

/// @brief 注册js外部函数,7个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction7(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External7 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 7);
}

/// @brief 注册js外部函数,8个参数.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pFunName 函数名.
/// @param pFun 事件处理函数名.
void WINAPI XWeb_RegExternalFunction8(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External8 pFun)  //注册Js外部函数
{
	Web_RegExternalFunctionX(hWebBrowser, pFunName, pFun, 8);
}

/// @brief 获取一个值，指出对象的地址栏是否可见或隐藏。
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbValue  显示TRUE,隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_AddressBar(HXCGUI hWebBrowser, out_ BOOL *pbValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_AddressBar(&xc_bValue);
	*pbValue = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象的地址栏是否可见或隐藏。
/// @param hWebBrowser 浏览器控件句柄.
/// @param bValue  显示TRUE,隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_AddressBar(HXCGUI hWebBrowser, BOOL bValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = (bValue ? VARIANT_TRUE : VARIANT_FALSE);
	return pObject->m_pIWebBrowser->put_AddressBar(xc_bValue);
}

/// @brief 获取WebBrowser Control宿主应用程序自动化对象.
/// @param hWebBrowser 浏览器控件句柄.
/// @param ppDisp  IDispatch接口接收的自动化对象的变量的指针的地址.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Application(HXCGUI hWebBrowser, IDispatch **ppDisp)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Application(ppDisp);
}

/// @brief 获取一个值，指出对象是否是导航或下载操作.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbBool  忙碌TRUE,不忙FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Busy(HXCGUI hWebBrowser, BOOL *pbBool)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_Busy(&xc_bValue);
	*pbBool = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 计算的浏览器窗口大小时，指定内容区域的宽度和高度.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pcx  指向一个变量int类型，指定客户区的宽度。返回时，这个变量包含完整的浏览器窗口的宽度.
/// @param pcy 一个指针int类型的变量指定客户区的高度。返回时，这个变量包含完整的浏览器窗口所需的高度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_ClientToWindow(HXCGUI hWebBrowser, in_out_ int *pcx, in_out_ int *pcy)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->ClientToWindow(pcx, pcy);
}

/// @brief 获取到一个容器对象的引用.
/// @param hWebBrowser 浏览器控件句柄.
/// @param ppDisp  指针地址接收容器的IDispatch接口类型的变量
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Container(HXCGUI hWebBrowser, IDispatch **ppDisp)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Container(ppDisp);
}

/// @brief 获取活动文档的自动化对象，如果有的话.
/// @param hWebBrowser 浏览器控件句柄.
/// @param ppDisp  接收自动化对象的IDispatch接口类型的变量的指针地址.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Document(HXCGUI hWebBrowser, IDispatch **ppDisp)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Document(ppDisp);
}

/// @brief 执行命令并返回命令执行使用IOleCommandTarget接口的状态.
/// @param hWebBrowser 浏览器控件句柄.
/// @param cmdID  OLECMDID值，指定要执行的命令。命令标识符的讨论，请参阅MSHTML的命令标识符.
/// @param cmdexecopt 指定命令选项的OLECMDEXECOPT值.
/// @param pvaIn 指向一个VARIANT结构，它包含命令的输入参数。这个VARIANT结构的类型取决于命令标识符的类型。此参数可以为NULL.
/// @param pvaOut 接收并指定命令的输出到一个VARIANT结构的指针。这个VARIANT结构的类型取决于命令标识符的类型。此参数可以为NULL.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_ExecWB(HXCGUI hWebBrowser, in_ OLECMDID cmdID, in_ OLECMDEXECOPT cmdexecopt, in_ VARIANT *pvaIn, in_out_ VARIANT *pvaOut)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->ExecWB(cmdID, cmdexecopt, pvaIn, pvaOut);
}

/// @brief 检索Microsoft Internet Explorer可知道文件全路径.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pOut  接收可执行文件全路径缓冲区.
/// @param outLen 接收缓存区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_FullName(HXCGUI hWebBrowser, wchar_t *pOut, int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR bstrFullName = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_FullName(&bstrFullName);
	if (S_OK == hr)
	{
		wchar_t *pText = _bstr_t(bstrFullName);
		wcscpy_s(pOut, outLen, pText);
		SysFreeString(bstrFullName);
	}
	return hr;
}

/// @brief 获取一个值，指出Microsoft Internet Explorer中是否在全屏模式或窗口模式下.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbFullScreen  全屏TRUE,正常FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_FullScreen(HXCGUI hWebBrowser, BOOL *pbFullScreen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_FullScreen(&xc_bValue);
	*pbFullScreen = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出Microsoft Internet Explorer中是否在全屏模式或窗口模式下.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bFullScreen  全屏TRUE,正常FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_FullScreen(HXCGUI hWebBrowser, BOOL bFullScreen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bFullScreen ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_FullScreen(xc_bValue);
}

/// @brief 获取与指定的属性名称相关的值.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pProperty  输入获取属性名.
/// @param pvtValue  接收属性值.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_GetProperty(HXCGUI hWebBrowser, in_ wchar_t *pProperty, out_ VARIANT *pvtValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR bstrProperty = SysAllocString(pProperty);
	HRESULT hr = pObject->m_pIWebBrowser->GetProperty(bstrProperty, pvtValue);
	SysFreeString(bstrProperty);
	return hr;
}

/// @brief 向后导航浏览历史列表中的一个项.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_GoBack(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->GoBack();
}

/// @brief 向前导航浏览历史列表中的一个项.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_GoForward(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->GoForward();
}

/// @brief 导航到当前主页或开始页面。.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_GoHome(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->GoHome();
}

/// @brief 导航到当前搜索页.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_GoSearch(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->GoSearch();
}

/// @brief 获取高度
/// @param hWebBrowser 浏览器控件句柄.
/// @param pl 接收高度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Height(HXCGUI hWebBrowser, out_ long *pl)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Height(pl);
}

/// @brief 设置高度
/// @param hWebBrowser 浏览器控件句柄.
/// @param height 设置高度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Height(HXCGUI hWebBrowser, in_ long height)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->put_Height(height);
}

/// @brief 获取Microsoft Internet Explorer的主窗口的句柄.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pHWND 接收句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_HWND(HXCGUI hWebBrowser, out_ long *pHWND)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_HWND((SHANDLE_PTR *)pHWND);
}

/// @brief 获取对象的左边缘坐标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pl 接收坐标.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Left(HXCGUI hWebBrowser, out_ long *pl)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Left(pl);
}

/// @brief 设置对象的左边缘坐标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param left 设置坐标.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Left(HXCGUI hWebBrowser, in_ long left)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->put_Left(left);
}

/// @brief 检索当前显示的资源的路径，或标题.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pLocationName 接收位置名称.
/// @param outLen  接收缓存区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_LocationName(HXCGUI hWebBrowser, out_ wchar_t *pLocationName, in_ int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR bstrLocationName = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_LocationName(&bstrLocationName);
	if (S_OK == hr)
	{
		wcscpy_s(pLocationName, outLen, _bstr_t(bstrLocationName));
		SysFreeString(bstrLocationName);
	}
	return hr;
}

/// @brief 获取当前显示的资源的URL.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pLocationURL 接收位置名称.
/// @param outLen  接收缓存区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_LocationURL(HXCGUI hWebBrowser, out_ wchar_t *pLocationURL, in_ int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR bstrLocationURL = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_LocationURL(&bstrLocationURL);
	if (S_OK == hr)
	{
		wcscpy_s(pLocationURL, outLen, _bstr_t(bstrLocationURL));
		SysFreeString(bstrLocationURL);
	}
	return hr;
}

/// @brief 获取一个值，指出Microsoft Internet Explorer的菜单栏是否可见
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbValue 可见TRUE,不可见FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_MenuBar(HXCGUI hWebBrowser, out_ BOOL *pbValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_MenuBar(&xc_bValue);
	*pbValue = VARIANT_TRUE == xc_bValue ? TRUE : FALSE;
	return hr;
}

/// @brief 设置一个值，指出Microsoft Internet Explorer的菜单栏是否可见
/// @param hWebBrowser 浏览器控件句柄.
/// @param bValue 可见TRUE,不可见FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_MenuBar(HXCGUI hWebBrowser, in_ BOOL bValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bValue ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_MenuBar(xc_bValue);
}

/// @brief 检索对象的框架名称或应用程序的名称
/// @param hWebBrowser 浏览器控件句柄.
/// @param pName 可接收名称缓冲区.
/// @param outLen 缓冲区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Name(HXCGUI hWebBrowser, out_ wchar_t *pName, in_ int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR bstrName = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_Name(&bstrName);
	if (S_OK == hr)
	{
		wcscpy_s(pName, outLen, _bstr_t(bstrName));
		SysFreeString(bstrName);
	}
	return hr;
}

/// @brief 导航到一个URL或一个完整的路径文件.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pUrl URL文件或完整文件路径,或资源名.
/// @param Flags  BrowserNavConstants枚举标识.
/// @param TargetFrameName 包含显示资源框架名,此参数一下可能值.\n
///   _blank\n
///     Load the link into a new unnamed window.\n
///   _parent\n
///     Load the link into the immediate parent of the document the link is in.\n
///   _self\n
///     Load the link into the same window the link was clicked in.\n
///   _top\n
///     Load the link into the full body of the current window.\n
///   WindowName\n
///     A named HTML frame. If no frame or window exists that matches the specified target name, a new window is opened for the specified link.
/// @param PostData  POST数据,如果URL不是HTTP URL，则忽略此参数.
/// @param Headers  HTTP头,如果URL不是HTTP URL，则忽略此参数.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_Navigate(HXCGUI hWebBrowser, in_ wchar_t *pUrl, in_ VARIANT *Flags, in_ VARIANT *TargetFrameName, in_ VARIANT *PostData, in_ VARIANT *Headers)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR URL = SysAllocString(pUrl);
	HRESULT hr = pObject->m_pIWebBrowser->Navigate(URL, Flags, TargetFrameName, PostData, Headers);
	SysFreeString(URL);
	return hr;
}

/// @brief 导航到一个URL或一个完整的路径文件.
/// @param hWebBrowser 浏览器控件句柄.
/// @param URL 一个指针到一个VARIANT，评估资源的URL显示，文件的位置，或一个PIDL，代表了在Shell命名空间的文件夹的完整路径.
/// @param Flags  BrowserNavConstants枚举标识.
/// @param TargetFrameName 包含显示资源框架名,此参数一下可能值.\n
///   _blank\n
///     Load the link into a new unnamed window.\n
///   _parent\n
///     Load the link into the immediate parent of the document the link is in.\n
///   _self\n
///     Load the link into the same window the link was clicked in.\n
///   _top\n
///     Load the link into the full body of the current window.\n
///   WindowName\n
///     A named HTML frame. If no frame or window exists that matches the specified target name, a new window is opened for the specified link.
/// @param PostData  POST数据,如果URL不是HTTP URL，则忽略此参数.
/// @param Headers HTTP头,如果URL不是HTTP URL，则忽略此参数.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_Navigate2(HXCGUI hWebBrowser, in_ VARIANT *URL, in_ VARIANT *Flags, in_ VARIANT *TargetFrameName, in_ VARIANT *PostData, in_ VARIANT *Headers)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->Navigate2(URL, Flags, TargetFrameName, PostData, Headers);
}

/// @brief 获取一个值，指出对象是否是在脱机模式下运行.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbOffline 离线模式 TRUE,连接模式FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Offline(HXCGUI hWebBrowser, out_ BOOL *pbOffline)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_Offline(&xc_bValue);
	*pbOffline = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象是否是在脱机模式下运行.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bOffline 离线模式 TRUE,连接模式FALSE..
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Offline(HXCGUI hWebBrowser, in_ BOOL bOffline)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bOffline ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_Offline(xc_bValue);
}

/// @brief 获取该对象的父.
/// @param hWebBrowser 浏览器控件句柄.
/// @param ppDisp 接收父类型变量的指针的地址.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Parent(HXCGUI hWebBrowser, IDispatch **ppDisp)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Parent(ppDisp);
}

/// @brief 检索系统的Microsoft Internet Explorer的可执行文件夹.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pPath 接收路径缓冲区.
/// @param outLen 缓冲区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Path(HXCGUI hWebBrowser, out_ wchar_t *pPath, in_ int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR Path = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_Path(&Path);
	if (S_OK == hr)
	{
		wcscpy_s(pPath, outLen, _bstr_t(Path));
		SysFreeString(Path);
	}
	return hr;
}

/// @brief 设置与对象关联的属性值.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pProperty 设置属性名称.
/// @param vtValue 属性新值.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_PutProperty(HXCGUI hWebBrowser, in_ wchar_t *pProperty, in_ VARIANT vtValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR bstrProperty = SysAllocString(pProperty);
	HRESULT hr = pObject->m_pIWebBrowser->PutProperty(bstrProperty, vtValue);
	SysFreeString(bstrProperty);
	return hr;
}

/// @brief 查询对象的使用IOleCommandTarget命令的状态为:: QueryStatus方法.
/// @param hWebBrowser 浏览器控件句柄.
/// @param cmdID OLECMDID值呼叫者需要状态信息的命令.
/// @param pcmdf OLECMDF指针值接收命令的状态.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_QueryStatusWB(HXCGUI hWebBrowser, in_ OLECMDID cmdID, out_ OLECMDF *pcmdf)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->QueryStatusWB(cmdID, pcmdf);
}

/// @brief 关闭这个对象.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_Quit(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->Quit();
}

/// @brief 获取这个对象的读取状态..
/// @param hWebBrowser 浏览器控件句柄.
/// @param plReadyState 读取状态,READYSTATE枚举值之一.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_ReadyState(HXCGUI hWebBrowser, out_ READYSTATE *plReadyState)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_ReadyState(plReadyState);
}

/// @brief 重新加载该文件，目前正在显示的对象.
/// @param hWebBrowser 浏览器控件句柄.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_Refresh(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->Refresh();
}

/// @brief 重载刷新指定的级别，目前正在与显示的文件.
/// @param hWebBrowser 浏览器控件句柄.
/// @param level RefreshConstants枚举值.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_Refresh2(HXCGUI hWebBrowser, in_ int level)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT Level;
	Level.vt = VT_I4;
	Level.intVal = level;
	return pObject->m_pIWebBrowser->Refresh2(&Level);
}

/// @brief 获取一个值，指出对象是否注册作为一个顶级的浏览器窗口.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbRegister  注册为顶级的浏览器TRUE,非注册为顶级的浏览器FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_RegisterAsBrowser(HXCGUI hWebBrowser, out_ BOOL *pbRegister)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_RegisterAsBrowser(&xc_bValue);
	*pbRegister = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象是否注册作为一个顶级的浏览器窗口.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bRegister 注册为顶级的浏览器TRUE,非注册为顶级的浏览器FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_RegisterAsBrowser(HXCGUI hWebBrowser, in_ BOOL bRegister)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bRegister ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_RegisterAsBrowser(xc_bValue);
}

/// @brief 获取一个值，指出对象是否注册作为导航的下拉目标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbRegister 被注册为一个下拉目标TRUE,没有注册为一个下拉目标FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_RegisterAsDropTarget(HXCGUI hWebBrowser, out_ BOOL *pbRegister)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_RegisterAsDropTarget(&xc_bValue);
	*pbRegister = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象是否注册作为导航的下拉目标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bRegister 注册为一个下拉目标TRUE,没有注册为一个下拉目标FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_RegisterAsDropTarget(HXCGUI hWebBrowser, in_ BOOL bRegister)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bRegister ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_RegisterAsDropTarget(xc_bValue);
}

/// @brief 获取一个值，指出对象是否可以调整大小.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbValue 对象能够调整大小TRUE,对象不能调整大小FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Resizable(HXCGUI hWebBrowser, out_ BOOL *pbValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_Resizable(&xc_bValue);
	*pbValue = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象是否可以调整大小.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bValue 对象能够调整大小TRUE,对象不能调整大小FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Resizable(HXCGUI hWebBrowser, in_ BOOL bValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bValue ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_Resizable(xc_bValue);
}

/// @brief 显示或隐藏指定的浏览条.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pvaClsid VARIANT类型VT_BSTR指定的浏览器栏显示或隐藏的类标识符;作为的CATID_InfoBand组件类别的浏览器栏对象，这个对象必须注册. \n
///  或者，一个指定下列之一的VARIANT类型VT_I2. \n
///  0x0009 \n
///  地址栏。这个值将被忽略的Windows Internet Explorer7. \n
///  0x000A \n
///  工具栏。不支持Internet Explorer 7中. \n
///  0x000B \n
///  链接工具栏. \n
/// @param bShow 浏览条显示TRUE,浏览条隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_ShowBrowserBar(HXCGUI hWebBrowser, in_ VARIANT *pvaClsid, in_ BOOL bShow)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT Show;
	Show.vt = VT_BOOL;
	Show.boolVal = bShow ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->ShowBrowserBar(pvaClsid, &Show, NULL);
}

/// @brief 获取一个值，指出对象是否可以显示对话框.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbSilent 对话框不显示TRUE;默认,可以显示对话框和消息。不支持严重错误和安全警报FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Silent(HXCGUI hWebBrowser, out_ BOOL *pbSilent)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_Silent(&xc_bValue);
	*pbSilent = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象是否可以显示对话框.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bSilent 对话框不显示TRUE;默认,可以显示对话框和消息。不支持严重错误和安全警报FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Silent(HXCGUI hWebBrowser, in_ BOOL bSilent)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bSilent ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_Silent(xc_bValue);
}

/// @brief 获取一个值，对象的状态栏是否可见.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pBool 状态条显示TRUE,状态条隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_StatusBar(HXCGUI hWebBrowser, BOOL *pBool)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_StatusBar(&xc_bValue);
	*pBool = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，对象的状态栏是否可见.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bValue 状态条显示TRUE,状态条隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_StatusBar(HXCGUI hWebBrowser, BOOL bValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bValue ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_StatusBar(xc_bValue);
}

/// @brief 获取对象的状态栏文本.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pOut 接收状态栏文本缓冲区.
/// @param outLen 接收缓冲区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_StatusText(HXCGUI hWebBrowser, out_ wchar_t *pOut, in_ int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR StatusText = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_StatusText(&StatusText);
	if (S_OK == hr)
	{
		wcscpy_s(pOut, outLen, _bstr_t(StatusText));
		SysFreeString(StatusText);
	}
	return hr;
}

/// @brief 设置对象的状态栏文本.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pStatusText 状态栏文本.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_StatusText(HXCGUI hWebBrowser, in_ wchar_t *pStatusText)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR StatusText = SysAllocString(pStatusText);
	HRESULT hr = pObject->m_pIWebBrowser->put_StatusText(StatusText);
	SysFreeString(StatusText);
	return hr;
}

/// @brief 取消挂起的导航或下载，并停止动态页面元素，如背景声音和动画.
/// @param hWebBrowser 浏览器控件句柄..
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_Stop(HXCGUI hWebBrowser)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->Stop();
}

/// @brief 获取对象是否是在影院模式.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbRegister 对象是在影院模式TRUE;默认,对象是在正常模式下FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_TheaterMode(HXCGUI hWebBrowser, out_ BOOL *pbRegister)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_TheaterMode(&xc_bValue);
	*pbRegister = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置对象是否是在影院模式.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bRegister 对象是在影院模式TRUE;默认,对象是在正常模式下FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_TheaterMode(HXCGUI hWebBrowser, in_ BOOL bRegister)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bRegister ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_TheaterMode(xc_bValue);
}

/// @brief 获取对象的工具栏是否可见的。
/// @param hWebBrowser 浏览器控件句柄.
/// @param pValue 默认工具条可见TRUE;工具条不可见FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_ToolBar(HXCGUI hWebBrowser, out_ int *pValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_ToolBar(pValue);
}

/// @brief 设置对象的工具栏是否可见的.
/// @param hWebBrowser 浏览器控件句柄.
/// @param value 默认工具条可见TRUE;工具条不可见FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_ToolBar(HXCGUI hWebBrowser, in_ int value)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->put_ToolBar(value);
}

/// @brief 获取对象的上边缘的坐标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pl 接收窗口的顶部边缘的坐标，以像素为单位的long类型的变量的指针.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Top(HXCGUI hWebBrowser, out_ long *pl)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Top(pl);
}

/// @brief 设置对象的上边缘的坐标.
/// @param hWebBrowser 浏览器控件句柄.
/// @param top 指定窗口顶部边缘的坐标，以像素为单位.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Top(HXCGUI hWebBrowser, in_ long top)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->put_Top(top);
}

/// @brief 获取一个值，指出对象是否是一个顶层容器.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pbBool 对象是一个顶层容器TRUE;对象非顶层容器FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_TopLevelContainer(HXCGUI hWebBrowser, out_ BOOL *pbBool)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_TopLevelContainer(&xc_bValue);
	*pbBool = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 获取用户所包含的文档对象类型名称.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pOut 接收类型名称的变量的指针.
/// @param outLen 缓冲区长度.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Type(HXCGUI hWebBrowser, out_ wchar_t *pOut, in_ int outLen)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	BSTR Type = NULL;
	HRESULT hr = pObject->m_pIWebBrowser->get_Type(&Type);
	if (S_OK == hr)
	{
		wcscpy_s(pOut, outLen, _bstr_t(Type));
		SysFreeString(Type);
	}
	return hr;
}

/// @brief 获取一个值，指出对象是否是可见或隐藏.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pBool 对象显示TRUE;默认对象隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Visible(HXCGUI hWebBrowser, out_ BOOL *pBool)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue;
	HRESULT hr = pObject->m_pIWebBrowser->get_Visible(&xc_bValue);
	*pBool = (VARIANT_TRUE == xc_bValue ? TRUE : FALSE);
	return hr;
}

/// @brief 设置一个值，指出对象是否是可见或隐藏.
/// @param hWebBrowser 浏览器控件句柄.
/// @param bValue 对象显示TRUE;默认对象隐藏FALSE.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Visible(HXCGUI hWebBrowser, in_ BOOL bValue)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	VARIANT_BOOL xc_bValue = bValue ? VARIANT_TRUE : VARIANT_FALSE;
	return pObject->m_pIWebBrowser->put_Visible(xc_bValue);
}

/// @brief 获取对象的宽度.
/// @param hWebBrowser 浏览器控件句柄.
/// @param pl 接收的宽度，以像素为单位的long类型变量的指针.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_get_Width(HXCGUI hWebBrowser, out_ long *pl)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->get_Width(pl);
}

/// @brief 获取对象的宽度.
/// @param hWebBrowser 浏览器控件句柄.
/// @param width 指定宽度，以像素为单位.
/// @return 成功返回 S_OK.
HRESULT WINAPI XWeb_put_Width(HXCGUI hWebBrowser, in_ long width)
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;
	return pObject->m_pIWebBrowser->put_Width(width);
}

void Web_RegExternalFunctionX(HXCGUI hWebBrowser, wchar_t *pFunName, void* pFun, int paramCount)  //注册Js外部函数
{
	webBrowser_ *pObject = (webBrowser_*)hWebBrowser;

	//------新事件机制
	BOOL bResult = FALSE;
	int index = -1; //插入位置
	int count = Array_GetCount(pObject->hArray_external);
	if (0 == count) //需要消息头
	{
		bResult = TRUE;
	}

	for (int i = 0; i < count; i++)
	{
		wchar_t *pName = XStr_GetBuffer(((IE_External_Header_*)Array_GetAt(pObject->hArray_external, i))->hString_Name);
		if (0 == wcscmp(pName, pFunName))
		{
			index = i;
			break;
		}
	}
	if (-1 == index)
		bResult = TRUE;

	if (bResult) //需要消息头
	{
		IE_External_Header_  *pHeader = (IE_External_Header_*)malloc(sizeof(IE_External_Header_));
		pHeader->hString_Name = XStr_Create();
		//pHeader->Event=type;
		pHeader->paramCount = paramCount;
		XStr_SetString(pHeader->hString_Name, pFunName);

		IE_External_ *pMsg = (IE_External_*)malloc(sizeof(IE_External_));
		pMsg->pFun = pFun;
		pMsg->pNext = NULL;

		//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		//		pMsg->pClass_Fun_Info=NULL;
		//#endif
		pHeader->pList = pMsg;

		//TODO:排序
		XArray_Add(pObject->hArray_external, pHeader);

	}
	else //不需要消息头
	{
		IE_External_ *pEvent = (IE_External_*)malloc(sizeof(IE_External_));
		pEvent->pFun = pFun;
		pEvent->pNext = NULL;

		//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
		//		pMsg->pClass_Fun_Info=NULL;
		//#endif
		IE_External_Header_  *pHeader = (IE_External_Header_*)Array_GetAt(pObject->hArray_external, index);
		if (NULL == pHeader->pList)
		{
			pHeader->pList = pEvent;
		}
		else  //插入到首位
		{
			pEvent->pNext = pHeader->pList;
			pHeader->pList = pEvent;
		}
	}
}



///@}


////////////////////////////////////////////////////////////////
CDocHostUIHandler::CDocHostUIHandler()
{
	m_refCount = 0;
	m_pWebBrowser = NULL;
}

void CDocHostUIHandler::SetWebBrowser(webBrowser_ *pWebBrowser)
{
	m_pWebBrowser = pWebBrowser;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown || riid == IID_IDispatch || riid == IID_IDocHostUIHandler)
	{
		AddRef();
		*ppvObject = this;
		return S_OK;
	}
	else
	{
		ppvObject = NULL;
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE CDocHostUIHandler::AddRef(void)
{
	m_refCount++;
	return m_refCount;
}

ULONG STDMETHODCALLTYPE CDocHostUIHandler::Release(void)
{
	m_refCount--;
	return m_refCount;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::ShowContextMenu(
	/* [in] */ DWORD dwID,
	/* [in] */ POINT *ppt,
	/* [in] */ IUnknown *pcmdtReserved,
	/* [in] */ IDispatch *pdispReserved)
{

	return E_NOTIMPL;//S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetHostInfo(
	/* [out][in] */ DOCHOSTUIINFO *pInfo)
{
	if (pInfo)
		pInfo->dwFlags |= DOCHOSTUIFLAG_NO3DBORDER; //去出3D边框
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::ShowUI(
	/* [in] */ DWORD dwID,
	/* [in] */ IOleInPlaceActiveObject *pActiveObject,
	/* [in] */ IOleCommandTarget *pCommandTarget,
	/* [in] */ IOleInPlaceFrame *pFrame,
	/* [in] */ IOleInPlaceUIWindow *pDoc)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::HideUI(void)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::UpdateUI(void)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::EnableModeless(
	/* [in] */ BOOL fEnable)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::OnDocWindowActivate(
	/* [in] */ BOOL fActivate)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::OnFrameWindowActivate(
	/* [in] */ BOOL fActivate)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::ResizeBorder(
	/* [in] */ LPCRECT prcBorder,
	/* [in] */ IOleInPlaceUIWindow *pUIWindow,
	/* [in] */ BOOL fRameWindow)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::TranslateAccelerator(
	/* [in] */ LPMSG lpMsg,
	/* [in] */ const GUID *pguidCmdGroup,
	/* [in] */ DWORD nCmdID)
{
	return(S_FALSE);
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetOptionKeyPath(
	/* [out] */
	__out  LPOLESTR *pchKey,
	/* [in] */ DWORD dw)
{
	return(S_FALSE);
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetDropTarget(
	/* [in] */ IDropTarget *pDropTarget,
	/* [out] */ IDropTarget **ppDropTarget)
{
	return(S_FALSE);
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetExternal(
	/* [out] */ IDispatch **ppDispatch)
{
	if (m_pWebBrowser)
	{
		*ppDispatch = &m_pWebBrowser->external;
	}
	else
	{
		*ppDispatch = NULL;
		return S_FALSE;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::TranslateUrl(
	/* [in] */ DWORD dwTranslate,
	/* [in] */
	__in __nullterminated  OLECHAR *pchURLIn,
	/* [out] */
	__out  OLECHAR **ppchURLOut)
{
	*ppchURLOut = 0;
	return(S_FALSE);
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::FilterDataObject(
	/* [in] */ IDataObject *pDO,
	/* [out] */ IDataObject **ppDORet)
{
	*ppDORet = 0;
	return S_FALSE;
}


/////////////////////////////////////////////////////////////////


CExternal::CExternal()
{
	m_refCount = 0;
}

void CExternal::SetWebBrowser(webBrowser_ *pWebBrowser)
{
	m_pWebBrowser = pWebBrowser;
}

HRESULT STDMETHODCALLTYPE CExternal::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown || riid == IID_IDispatch)
	{
		AddRef();
		*ppvObject = this;
		return S_OK;
	}
	else
	{
		ppvObject = NULL;
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE CExternal::AddRef(void)
{
	m_refCount++;
	return m_refCount;
}

ULONG STDMETHODCALLTYPE CExternal::Release(void)
{
	m_refCount--;
	return m_refCount;
}

HRESULT STDMETHODCALLTYPE CExternal::GetTypeInfoCount(
	/* [out] */ __RPC__out UINT *pctinfo)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CExternal::GetTypeInfo(
	/* [in] */ UINT iTInfo,
	/* [in] */ LCID lcid,
	/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CExternal::GetIDsOfNames(
	/* [in] */ __RPC__in REFIID riid,
	/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
	/* [range][in] */ UINT cNames,
	/* [in] */ LCID lcid,
	/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{

	int count = XArray_GetCount(m_pWebBrowser->hArray_external);
	for (UINT i = 0; i < cNames; i++)
	{
		for (int index = 0; index < count; index++)
		{
			IE_External_Header_ *pHeader = (IE_External_Header_*)XArray_GetAt(m_pWebBrowser->hArray_external, index);
			wchar_t *pName = XStr_GetBuffer(pHeader->hString_Name);
			if (0 == wcscmp(pName, rgszNames[i]))
			{
				*rgDispId = index;
				pHeader->idspid = index;
			}
		}
		XTRACEW(L"function:%s() \n", rgszNames[i]);
	}
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CExternal::Invoke(
	/* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS *pDispParams,
	/* [out] */ VARIANT *pVarResult,
	/* [out] */ EXCEPINFO *pExcepInfo,
	/* [out] */ UINT *puArgErr)
{

	//HXCGUI hWebBrowser=(HXCGUI)m_pWebBrowser;
//	wchar_t *pUrl=((VARIANT*)pDispParams->rgvarg[5].byref)->bstrVal;
//	int Flags=((VARIANT*)pDispParams->rgvarg[4].byref)->intVal;
//	wchar_t *TargetFrameName=((VARIANT*)pDispParams->rgvarg[3].byref)->bstrVal;
//	wchar_t *PostData=((VARIANT*)pDispParams->rgvarg[2].byref)->bstrVal;
//	wchar_t *Headers=((VARIANT*)pDispParams->rgvarg[1].byref)->bstrVal;
//	BOOL bCancel=(0==((VARIANT*)pDispParams->rgvarg[0].byref)->boolVal) ? FALSE : TRUE ;

	int count = XArray_GetCount(m_pWebBrowser->hArray_external);
	for (int index = 0; index < count; index++)
	{
		IE_External_Header_ *pHeader = (IE_External_Header_*)XArray_GetAt(m_pWebBrowser->hArray_external, index);

		if (pHeader->idspid == dispIdMember)
		{
			IE_External_ *pExternal = pHeader->pList;
			switch (pHeader->paramCount)
			{
			case 0:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External0)pExternal->pFun)(m_pWebBrowser, hString))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External0)pExternal->pFun)(m_pWebBrowser, NULL))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 1:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External1)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External1)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 2:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External2)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External2)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 3:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External3)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External3)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 4:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External4)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External4)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 5:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External5)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External5)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 6:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External6)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[5].bstrVal, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External6)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[5].bstrVal, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 7:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External7)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[6].bstrVal, pDispParams->rgvarg[5].bstrVal, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External7)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[6].bstrVal, pDispParams->rgvarg[5].bstrVal, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			case 8:
				if (pVarResult)// 有返回值
				{
					HSTRING hString = XStr_Create();
					while (pExternal)
					{
						if (((pFunIE_External8)pExternal->pFun)(m_pWebBrowser, hString, pDispParams->rgvarg[7].bstrVal, pDispParams->rgvarg[6].bstrVal, pDispParams->rgvarg[5].bstrVal, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							break;

						pExternal = pExternal->pNext;
					}
					if (XStr_GetLength(hString) > 0)
					{
						pVarResult->vt = VT_BSTR;
						pVarResult->bstrVal = SysAllocString(XStr_GetBuffer(hString));
						XStr_Destroy(hString);
					}
				}
				else //没有返回值
				{
					while (pExternal)
					{
						if (((pFunIE_External8)pExternal->pFun)(m_pWebBrowser, NULL, pDispParams->rgvarg[7].bstrVal, pDispParams->rgvarg[6].bstrVal, pDispParams->rgvarg[5].bstrVal, pDispParams->rgvarg[4].bstrVal, pDispParams->rgvarg[3].bstrVal, pDispParams->rgvarg[2].bstrVal, pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal))
							return S_OK;
						pExternal = pExternal->pNext;
					}
				}break;
			}
		}
	}

	return S_OK;
}
