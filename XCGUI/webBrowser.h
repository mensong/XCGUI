#pragma once
/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

//COM控件 初始化
void XCom_Add();
void XCom_Release();
void XCom_AppExit();
int  XCom_GetCount();

struct webBrowser_;
class CMyAxWindow : public CWindowImpl<CMyAxWindow, CAxWindow>
{
public:
	CMyAxWindow();
	BEGIN_MSG_MAP(CMyAxWindow)
		MESSAGE_HANDLER(WM_NCDESTROY, OnDestroy)
		//	MESSAGE_HANDLER(WM_ERASEBKGND,OnEraseBkgnd)

	END_MSG_MAP()
	webBrowser_ *m_pWebBrowser;

	void SetWebBrowser(webBrowser_ *pWebBrowser);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual void OnFinalMessage(HWND /*hWnd*/);
};


class CIEEvent : public IDispatch
{
public:
	CIEEvent();
	webBrowser_  *m_pWebBrowser;
	ULONG         m_refCount;

	void SetWebBrowser(webBrowser_  *pWebBrowser);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT *pctinfo);

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo);

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
		/* [range][in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS *pDispParams,
		/* [out] */ VARIANT *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);

	void *GetEventHeader(int Event);
};


class CDocHostUIHandler : public IDocHostUIHandler
{
public:
	CDocHostUIHandler();

	ULONG     m_refCount;
	webBrowser_    *m_pWebBrowser;

	void SetWebBrowser(webBrowser_ *pWebBrowser);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(
		/* [in] */ DWORD dwID,
		/* [in] */ POINT *ppt,
		/* [in] */ IUnknown *pcmdtReserved,
		/* [in] */ IDispatch *pdispReserved);

	virtual HRESULT STDMETHODCALLTYPE GetHostInfo(
		/* [out][in] */ DOCHOSTUIINFO *pInfo);

	virtual HRESULT STDMETHODCALLTYPE ShowUI(
		/* [in] */ DWORD dwID,
		/* [in] */ IOleInPlaceActiveObject *pActiveObject,
		/* [in] */ IOleCommandTarget *pCommandTarget,
		/* [in] */ IOleInPlaceFrame *pFrame,
		/* [in] */ IOleInPlaceUIWindow *pDoc);

	virtual HRESULT STDMETHODCALLTYPE HideUI(void);

	virtual HRESULT STDMETHODCALLTYPE UpdateUI(void);

	virtual HRESULT STDMETHODCALLTYPE EnableModeless(
		/* [in] */ BOOL fEnable);

	virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(
		/* [in] */ BOOL fActivate);

	virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(
		/* [in] */ BOOL fActivate);

	virtual HRESULT STDMETHODCALLTYPE ResizeBorder(
		/* [in] */ LPCRECT prcBorder,
		/* [in] */ IOleInPlaceUIWindow *pUIWindow,
		/* [in] */ BOOL fRameWindow);

	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(
		/* [in] */ LPMSG lpMsg,
		/* [in] */ const GUID *pguidCmdGroup,
		/* [in] */ DWORD nCmdID);

	virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(
		/* [out] */
		__out  LPOLESTR *pchKey,
		/* [in] */ DWORD dw);

	virtual HRESULT STDMETHODCALLTYPE GetDropTarget(
		/* [in] */ IDropTarget *pDropTarget,
		/* [out] */ IDropTarget **ppDropTarget);

	virtual HRESULT STDMETHODCALLTYPE GetExternal(
		/* [out] */ IDispatch **ppDispatch);

	virtual HRESULT STDMETHODCALLTYPE TranslateUrl(
		/* [in] */ DWORD dwTranslate,
		/* [in] */
		__in __nullterminated  OLECHAR *pchURLIn,
		/* [out] */
		__out  OLECHAR **ppchURLOut);

	virtual HRESULT STDMETHODCALLTYPE FilterDataObject(
		/* [in] */ IDataObject *pDO,
		/* [out] */ IDataObject **ppDORet);

};

class CExternal : public IDispatch
{
public:
	CExternal();
	ULONG    m_refCount;
	webBrowser_    *m_pWebBrowser;

	void SetWebBrowser(webBrowser_ *pWebBrowser);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT *pctinfo);

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo);

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
		/* [range][in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS *pDispParams,
		/* [out] */ VARIANT *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);

	//BOOL ReadLocalCatalog(shelf_data_ *data,VARIANT *pVarResult,wchar_t *pPath); //读取本地目录
//	BOOL GetUpdateCatalog(wchar_t *pID,wchar_t *pPath);  //获取最新章节

	//BOOL GetCatalogUrl(wchar_t *pID,std::wstring &pOut);  //根据ID查询目录URL

};

struct IE_Event_ //事件过程链表
{
	void    *pFun; //函数指针
//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
//	void  *pClass_Fun_Info;//消息事件回调函数信息指针
//#endif
	IE_Event_ *pNext;
};


struct IE_Event_Header_  //消息或事件 链表头  
{
	int   Event;      //事件类型
	IE_Event_  *pList;  //注册的消息或事件体链表  
	//pFunEventConversion  pFunEventConv; //事件转换函数
//	void *pFunEventConv;
};

struct IE_External_ //事件过程链表
{
	void    *pFun; //函数指针
//#ifdef	XCGUI_PLUS  //C++类支持,对类成员函数注册的支持
//	void  *pClass_Fun_Info;//消息事件回调函数信息指针
//#endif
	IE_External_ *pNext;
};

struct IE_External_Header_  //js外部函数 链表头  
{
	int      idspid;        //映射函数ID
	HSTRING  hString_Name;  //js调用外部函数名
	int      paramCount;    //参数个数

	IE_External_  *pList;  //注册的消息或事件体链表  
	//pFunEventConversion  pFunEventConv; //事件转换函数
//	void *pFunEventConv;
};

//IE控件
struct webBrowser_
{
	IWebBrowser2*  m_pIWebBrowser;
	CMyAxWindow    m_axWindow;
	CIEEvent       m_event;  //接收事件

	HARRAY         hArray_event;     //IE事件数组 IE_Event_Header_*
	HARRAY         hArray_external;  //IE外部js函数数组 IE_External_Header_*

	CDocHostUIHandler docHostUIHandler;
	CExternal         external;
};


//API:
XC_API HXCGUI WINAPI XWeb_Create(HWINDOW hWindow, int x, int y, int cx, int cy);
XC_API BOOL WINAPI XWeb_OpenURL(HXCGUI hWebBrowser, wchar_t *pUrl);
XC_API void WINAPI XWeb_Show(HXCGUI hWebBrowser, BOOL bShow); //显示隐藏
XC_API HWND WINAPI XWeb_GetHWnd(HXCGUI hWebBrowser);       //获取浏览器控件容器(CAxWindow)HWND句柄
XC_API void* WINAPI XWeb_GetControl(HXCGUI hWebBrowser);   //获取控件接口IWebBrowser2*
XC_API void* WINAPI XWeb_GetCAxWindow(HXCGUI hWebBrowser); //获取容器对象指针CAxWindow*
XC_API void WINAPI XWeb_Destroy(HXCGUI hWebBrowser);

XC_API BOOL WINAPI XWeb_GetClientRect(HXCGUI hWebBrowser, out_ RECT *pRect); //获取坐标
XC_API BOOL WINAPI XWeb_SetRect(HXCGUI hWebBrowser, in_ RECT *pRect); //设置坐标

//执行js脚本
XC_API BOOL WINAPI XWeb_ExeJavascript(HXCGUI hWebBrowser, wchar_t *pFun, wchar_t* pParam[], int paramCount);
//注册IE事件
XC_API void WINAPI XWeb_RegEvent(HXCGUI hWebBrowser, int type, void *pFun);

//注册js外部函数,js调用C/C++函数
XC_API void WINAPI XWeb_RegExternalFunction0(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External0 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction1(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External1 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction2(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External2 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction3(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External3 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction4(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External4 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction5(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External5 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction6(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External6 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction7(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External7 pFun);  //注册Js外部函数
XC_API void WINAPI XWeb_RegExternalFunction8(HXCGUI hWebBrowser, wchar_t *pFunName, pFunIE_External8 pFun);  //注册Js外部函数

//封装IE方法:
XC_API HRESULT WINAPI XWeb_get_AddressBar(HXCGUI hWebBrowser, out_ BOOL *pbValue);
XC_API HRESULT WINAPI XWeb_put_AddressBar(HXCGUI hWebBrowser, BOOL bValue);
XC_API HRESULT WINAPI XWeb_get_Application(HXCGUI hWebBrowser, IDispatch **ppDisp);
XC_API HRESULT WINAPI XWeb_get_Busy(HXCGUI hWebBrowser, out_ BOOL *pbBool);
XC_API HRESULT WINAPI XWeb_ClientToWindow(HXCGUI hWebBrowser, in_out_ int *pcx, in_out_ int *pcy);
XC_API HRESULT WINAPI XWeb_get_Container(HXCGUI hWebBrowser, IDispatch **ppDisp);
XC_API HRESULT WINAPI XWeb_get_Document(HXCGUI hWebBrowser, IDispatch **ppDisp);
XC_API HRESULT WINAPI XWeb_ExecWB(HXCGUI hWebBrowser, in_ OLECMDID cmdID, in_ OLECMDEXECOPT cmdexecopt, in_ VARIANT *pvaIn, in_out_ VARIANT *pvaOut);
XC_API HRESULT WINAPI XWeb_get_FullName(HXCGUI hWebBrowser, out_ wchar_t *pOut, in_ int outLen);
XC_API HRESULT WINAPI XWeb_get_FullScreen(HXCGUI hWebBrowser, BOOL *pbFullScreen);
XC_API HRESULT WINAPI XWeb_put_FullScreen(HXCGUI hWebBrowser, BOOL bFullScreen);
XC_API HRESULT WINAPI XWeb_GetProperty(HXCGUI hWebBrowser, in_ wchar_t *pProperty, out_ VARIANT *pvtValue);
XC_API HRESULT WINAPI XWeb_GoBack(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_GoForward(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_GoHome(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_GoSearch(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_get_Height(HXCGUI hWebBrowser, out_ long *pl);
XC_API HRESULT WINAPI XWeb_put_Height(HXCGUI hWebBrowser, in_ long height);
XC_API HRESULT WINAPI XWeb_get_HWND(HXCGUI hWebBrowser, out_ long *pHWND);
XC_API HRESULT WINAPI XWeb_get_Left(HXCGUI hWebBrowser, out_ long *pl);
XC_API HRESULT WINAPI XWeb_put_Left(HXCGUI hWebBrowser, in_ long left);
XC_API HRESULT WINAPI XWeb_get_LocationName(HXCGUI hWebBrowser, out_ wchar_t *pLocationName, in_ int outLen);
XC_API HRESULT WINAPI XWeb_get_LocationURL(HXCGUI hWebBrowser, out_ wchar_t *pLocationURL, in_ int outLen);
XC_API HRESULT WINAPI XWeb_get_MenuBar(HXCGUI hWebBrowser, out_ BOOL *pbValue);
XC_API HRESULT WINAPI XWeb_put_MenuBar(HXCGUI hWebBrowser, in_ BOOL bValue);
XC_API HRESULT WINAPI XWeb_get_Name(HXCGUI hWebBrowser, out_ wchar_t *pName, in_ int outLen);
XC_API HRESULT WINAPI XWeb_Navigate(HXCGUI hWebBrowser, in_ wchar_t *pUrl, in_ VARIANT *Flags, in_ VARIANT *TargetFrameName, in_ VARIANT *PostData, in_ VARIANT *Headers);
XC_API HRESULT WINAPI XWeb_Navigate2(HXCGUI hWebBrowser, in_ VARIANT *URL, in_ VARIANT *Flags, in_ VARIANT *TargetFrameName, in_ VARIANT *PostData, in_ VARIANT *Headers);
XC_API HRESULT WINAPI XWeb_get_Offline(HXCGUI hWebBrowser, out_ BOOL *pbOffline);
XC_API HRESULT WINAPI XWeb_put_Offline(HXCGUI hWebBrowser, in_ BOOL bOffline);
XC_API HRESULT WINAPI XWeb_get_Parent(HXCGUI hWebBrowser, IDispatch **ppDisp);
XC_API HRESULT WINAPI XWeb_get_Path(HXCGUI hWebBrowser, out_ wchar_t *pPath, in_ int outLen);
XC_API HRESULT WINAPI XWeb_PutProperty(HXCGUI hWebBrowser, in_ wchar_t *pProperty, in_ VARIANT vtValue);
XC_API HRESULT WINAPI XWeb_QueryStatusWB(HXCGUI hWebBrowser, in_ OLECMDID cmdID, out_ OLECMDF *pcmdf);
XC_API HRESULT WINAPI XWeb_Quit(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_get_ReadyState(HXCGUI hWebBrowser, out_ READYSTATE *plReadyState);
XC_API HRESULT WINAPI XWeb_Refresh(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_Refresh2(HXCGUI hWebBrowser, in_ int level);
XC_API HRESULT WINAPI XWeb_get_RegisterAsBrowser(HXCGUI hWebBrowser, out_ BOOL *pbRegister);
XC_API HRESULT WINAPI XWeb_put_RegisterAsBrowser(HXCGUI hWebBrowser, in_ BOOL bRegister);
XC_API HRESULT WINAPI XWeb_get_RegisterAsDropTarget(HXCGUI hWebBrowser, out_ BOOL *pbRegister);
XC_API HRESULT WINAPI XWeb_put_RegisterAsDropTarget(HXCGUI hWebBrowser, in_ BOOL bRegister);
XC_API HRESULT WINAPI XWeb_get_Resizable(HXCGUI hWebBrowser, out_ BOOL *pbValue);
XC_API HRESULT WINAPI XWeb_put_Resizable(HXCGUI hWebBrowser, in_ BOOL bValue);
XC_API HRESULT WINAPI XWeb_ShowBrowserBar(HXCGUI hWebBrowser, in_ VARIANT *pvaClsid, in_ BOOL bShow);
XC_API HRESULT WINAPI XWeb_get_Silent(HXCGUI hWebBrowser, out_ BOOL *pbSilent);
XC_API HRESULT WINAPI XWeb_put_Silent(HXCGUI hWebBrowser, in_ BOOL bSilent);
XC_API HRESULT WINAPI XWeb_get_StatusBar(HXCGUI hWebBrowser, out_ BOOL *pbBool);
XC_API HRESULT WINAPI XWeb_put_StatusBar(HXCGUI hWebBrowser, in_ BOOL bValue);
XC_API HRESULT WINAPI XWeb_get_StatusText(HXCGUI hWebBrowser, out_ wchar_t *pOut, in_ int outLen);
XC_API HRESULT WINAPI XWeb_put_StatusText(HXCGUI hWebBrowser, in_ wchar_t *pStatusText);
XC_API HRESULT WINAPI XWeb_Stop(HXCGUI hWebBrowser);
XC_API HRESULT WINAPI XWeb_get_TheaterMode(HXCGUI hWebBrowser, out_ BOOL *pbRegister);
XC_API HRESULT WINAPI XWeb_put_TheaterMode(HXCGUI hWebBrowser, in_ BOOL bRegister);
XC_API HRESULT WINAPI XWeb_get_ToolBar(HXCGUI hWebBrowser, out_ int *pValue);
XC_API HRESULT WINAPI XWeb_put_ToolBar(HXCGUI hWebBrowser, in_ int value);
XC_API HRESULT WINAPI XWeb_get_Top(HXCGUI hWebBrowser, out_ long *pl);
XC_API HRESULT WINAPI XWeb_put_Top(HXCGUI hWebBrowser, in_ long top);
XC_API HRESULT WINAPI XWeb_get_TopLevelContainer(HXCGUI hWebBrowser, out_ BOOL *pbBool);
XC_API HRESULT WINAPI XWeb_get_Type(HXCGUI hWebBrowser, out_ wchar_t *pOut, in_ int outLen);
XC_API HRESULT WINAPI XWeb_get_Visible(HXCGUI hWebBrowser, out_ BOOL *pBool);
XC_API HRESULT WINAPI XWeb_put_Visible(HXCGUI hWebBrowser, in_ BOOL bValue);
XC_API HRESULT WINAPI XWeb_get_Width(HXCGUI hWebBrowser, out_ long *pl);
XC_API HRESULT WINAPI XWeb_put_Width(HXCGUI hWebBrowser, in_ long width);

//私有方法:
void Web_RegExternalFunctionX(HXCGUI hWebBrowser, wchar_t *pFunName, void* pFun, int paramCount);  //注册Js外部函数
void Web_OnDestroy(HXCGUI hWebBrowser);



