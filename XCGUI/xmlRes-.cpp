/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

///@defgroup groupResource    资源文件API
///@ingroup  groupGuiDesigner
///


///@addtogroup groupResource
///@{

///@brief 加载资源文件.
///@param pFileName  资源文件名.
///@return 如果成功返回资源文件句柄.
HXMLRES WINAPI XXmlRes_Load(wchar_t *pFileName)
{
	if(NULL==pFileName) return NULL;

	char  file[MAX_PATH]={0};
	XC_UnicodeToAnsi(pFileName,-1,file,MAX_PATH);
	TiXmlDocument xmlDoc;

	if(FALSE==xmlDoc.LoadFile(file))
	{
		XTRACE("炫彩界面库-错误提示:加载资源文件失败,文件路径错误\n");
		return FALSE;
	}

	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		XTRACE("炫彩界面库-错误提示:加载资源文件失败,原因可能标签错误\n");
		return NULL;
	}

	return XXmlRes_LoadX(pRoot);
}

///@brief 加载资源文件,从程序资源模块中.
///@param resID  资源ID.
///@param pType  资源类型.
///@return 如果成功返回资源文件句柄.
HXMLRES WINAPI XXmlRes_LoadRes(int resID,wchar_t *pType) //从VC资源文件中加载
{
	HMODULE hInst=NULL;
	if(g_resourcesModule)
		hInst=g_resourcesModule;
	else
		hInst=GetModuleHandle(NULL);

	if(NULL==hInst) return FALSE;

	LPCTSTR lpRes=MAKEINTRESOURCE(resID); 
	HRSRC   hRsrc=::FindResource(hInst,lpRes,pType);
	if(NULL==hRsrc) return FALSE;
	HGLOBAL hGlobal=LoadResource(hInst,hRsrc);
	if(NULL==hGlobal) return FALSE;
	DWORD   dwSize   =SizeofResource(hInst,hRsrc);

	HXMLRES result=FALSE;
	if(dwSize>0)
	{
		LPVOID   lpData  =LockResource(hGlobal);
		if(lpData)
		{
			char *pData=(char*)malloc(dwSize+1);
			if(pData)
			{
				memcpy(pData,lpData,dwSize);
				pData[dwSize]=0;
				result=XXmlRes_LoadRes2(pData);
				free(pData);
			}
		}
	}

	BOOL hrr=FreeResource(hGlobal);
	return result;
}

HXMLRES XXmlRes_LoadRes2(char *pData) //从VC资源文件中加载
{
	TiXmlDocument xmlDoc;
	if(NULL==xmlDoc.Parse(pData))
	{
		DebugBox(L"炫彩界面库-错误提示:加载资源文件失败.");
		return NULL;
	}

	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(NULL==pRoot)
	{
		XTRACE("炫彩界面库-错误提示:加载资源文件失败,原因可能标签错误\n");
		return NULL;
	}

	return XXmlRes_LoadX(pRoot);
}

HXMLRES WINAPI XXmlRes_LoadX(TiXmlElement *pRoot)
{
	xmlRes_ *pObj=(xmlRes_*)malloc(sizeof(xmlRes_));
	if(pObj)
	{
		pObj->hArray_ID=XArray_Create();
		pObj->hArray_Image=XArray_Create();
		pObj->hArray_String=XArray_Create();
		pObj->hArray_Color=XArray_Create();
		if(XmlRes_LoadXml(pObj,pRoot))
		{
			return (HXMLRES)pObj;
		}
		free(pObj);
	}
	return NULL;
}

BOOL XmlRes_LoadXml(xmlRes_ *pXmlRes,TiXmlElement *pRoot)
{
	const char *pRef=pRoot->Value();
	if(NULL==pRef)
	{
		XTRACE("炫彩界面库-错误提示:加载资源文件失败,原因可能标签错误\n");
		return FALSE;
	}
	if(0!=strcmp(pRef,"resources"))
	{
		XTRACE("炫彩界面库-错误提示:加载资源文件失败,原因可能标签[resources]错误\n");
		return FALSE;
	}

	//默认ID
	{
		xmlRes_data_ *data=(xmlRes_data_*)malloc(sizeof(xmlRes_data_));
		data->name=XStr_Create();
		data->value=XStr_Create();
		XStr_SetString(data->name,L"ID_NO");
		XStr_SetString(data->value,L"0");
		XArray_Add(pXmlRes->hArray_ID,data);
	}

	wchar_t temp[MAX_PATH]={0};
	const char *pValue=NULL;
	const char *pName=NULL;
	const char *pString=NULL;
	TiXmlElement *pChild=pRoot->FirstChildElement();
	while(pChild)
	{
		pValue=pChild->Value();
		if(NULL==pValue) return FALSE;

		pName=pChild->Attribute("name");
		pString=pChild->Attribute("value");

		xmlRes_data_ *data=(xmlRes_data_*)malloc(sizeof(xmlRes_data_));
		memset(data,0,sizeof(xmlRes_data_));
		if(pName && pString)
		{
			data->name=XStr_Create();
			data->value=XStr_Create();
			XC_AnsiToUnicode((char*)pName,-1,temp,MAX_PATH);
			XStr_SetString(data->name,temp);
			XC_AnsiToUnicode((char*)pString,-1,temp,MAX_PATH);
			XStr_SetString(data->value,temp);
		}

		if(0==strcmp(pValue,"id"))
		{
			data->type=res_id;
			XArray_Add(pXmlRes->hArray_ID,data);
		}else if(0==strcmp(pValue,"image"))
		{
			XmlRes_HandImage(pXmlRes,pChild,data);
			XArray_Add(pXmlRes->hArray_Image,data);
		}else if(0==strcmp(pValue,"string"))
		{
			data->type=res_string;
			XArray_Add(pXmlRes->hArray_String,data);
		}else if(0==strcmp(pValue,"color"))
		{
			data->type=res_color;
			XArray_Add(pXmlRes->hArray_Color,data);
		}else
			return FALSE;
		pChild=pChild->NextSiblingElement();
	}

	return true;
}

BOOL XmlRes_HandImage(xmlRes_ *pXmlRes,TiXmlElement *pLabel,xmlRes_data_ *pItem)
{
	const char *pFrom=pLabel->Attribute("from");
	if(NULL==pFrom || 0==strcmp(pFrom,"file") )
	{
		const char *pZoom=pLabel->Attribute("zoom");
		if(NULL==pZoom || 0==strcmp(pZoom,"no"))
		{
			pItem->type=res_image_file;
		}else if(0==strcmp(pZoom,"stretch"))
		{
			pItem->type=res_image_file_stretch;
		}else if(0==strcmp(pZoom,"adaptive"))
		{
			pItem->type=res_image_file_adaptive;
		}
	}else if(0==strcmp(pFrom,"res"))
	{
		const char *pZoom=pLabel->Attribute("zoom");
		if(NULL==pZoom || 0==strcmp(pZoom,"no"))
		{
			pItem->type=res_image_vc;
		}else if(0==strcmp(pZoom,"stretch"))
		{
			pItem->type=res_image_vc_stretch;
		}else if(0==strcmp(pZoom,"adaptive"))
		{
			pItem->type=res_image_vc_adaptive;
		}
	}else if(0==strcmp(pFrom,"zip"))
	{
		const char *pZoom=pLabel->Attribute("zoom");
		if(NULL==pZoom || 0==strcmp(pZoom,"no"))
		{
			pItem->type=res_image_zip;
		}else if(0==strcmp(pZoom,"stretch"))
		{
			pItem->type=res_image_zip_stretch;
		}else if(0==strcmp(pZoom,"adaptive"))
		{
			pItem->type=res_image_zip_adaptive;
		}
	}

	const char *pResType=pLabel->Attribute("resType");
	const char *pResID=pLabel->Attribute("resID");
	const char *pZipFile=pLabel->Attribute("zipFile");
	const char *pPosx1=pLabel->Attribute("posx1");
	const char *pPosx2=pLabel->Attribute("posx2");
	const char *pPosy1=pLabel->Attribute("posy1");
	const char *pPosy2=pLabel->Attribute("posy2");

	wchar_t temp[MAX_PATH]={0};
	if(pResType)
	{
		XC_AnsiToUnicode((char*)pResType,-1,temp,MAX_PATH);
		pItem->resType=XStr_Create();
		XStr_SetString(pItem->resType,temp);
	}
	if(pZipFile)
	{
		XC_AnsiToUnicode((char*)pZipFile,-1,temp,MAX_PATH);
		pItem->zipFile=XStr_Create();
		XStr_SetString(pItem->zipFile,temp);
	}
	if(pResID)
	{
		pItem->resID=atoi(pResID);
	}
	if(pPosx1)
	{
		pItem->x1=atoi(pPosx1);
	}
	if(pPosx2)
	{
		pItem->x2=atoi(pPosx2);
	}
	if(pPosy1)
	{
		pItem->y1=atoi(pPosy1);
	}
	if(pPosy2)
	{
		pItem->y2=atoi(pPosy2);
	}
	return FALSE;
}

///@brief 查找ID资源,根据资源ID的名称,查找资源ID的值.
///@param hXmlRes  资源文件句柄.
///@param pName    资源ID名称.
///@return 资源ID名称对应的整型值.
int WINAPI XXmlRes_FindId(HXMLRES hXmlRes,wchar_t *pName)
{
	if(NULL==pName) return 0;

	xmlRes_ *pXmlRes=(xmlRes_*)hXmlRes;
	xmlRes_data_  *data;
	int count=XArray_GetCount(pXmlRes->hArray_ID);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_ID,i);
		if(0==wcscmp(pName,XStr_GetBuffer(data->name)))
		{
			return _wtoi(XStr_GetBuffer(data->value));;
		}
	}
	return 0;
}

///@brief 查找图片资源,根据资源图片的名称,查找图片资源的值.
///@param hXmlRes  资源文件句柄.
///@param pName    资源名称.
///@param[out] pOut     接收资源值的buffer.
///@param outLen   pOut长度
void WINAPI XXmlRes_FindImage(HXMLRES hXmlRes,wchar_t *pName,out_ wchar_t *pOut,int outLen)
{
	if(NULL==pName) return ;
	xmlRes_ *pXmlRes=(xmlRes_*)hXmlRes;
	xmlRes_data_  *data;
	int count=XArray_GetCount(pXmlRes->hArray_Image);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_Image,i);
		if(0==wcscmp(pName,XStr_GetBuffer(data->name)))
		{
			wcscpy_s(pOut,outLen,XStr_GetBuffer(data->value));
			return ;
		}
	}
}

///@brief 查找字符串资源,根据资名称,查找资源的值(当前未实现函数).
///@param hXmlRes  资源文件句柄.
///@param pName    资源名称.
///@param[out] pOut     接收资源值的buffer.
///@param outLen   pOut长度
void WINAPI XXmlRes_FindString(HXMLRES hXmlRes,wchar_t *pName,out_ wchar_t *pOut,int outLen)
{

}

//查找图片资源,返回图片句柄
///@brief 查图片资源,根据资源图片的名称,返回图片句柄.
///@param hXmlRes  资源文件句柄.
///@param pName    资源名称.
///@return 图片句柄;如果该图片句柄没有关联到元素,你需要手动释放.
HIMAGE WINAPI XXmlRes_FildHIMAGE(HXMLRES hXmlRes,wchar_t *pName)
{
	if(NULL==hXmlRes) return NULL;
	if(NULL==pName) return NULL;
	xmlRes_ *pXmlRes=(xmlRes_*)hXmlRes;
	xmlRes_data_  *data;
	int count=XArray_GetCount(pXmlRes->hArray_Image);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_Image,i);
		if(0==wcscmp(pName,XStr_GetBuffer(data->name)))
		{
			//wcscpy_s(pOut,outLen,XStr_GetBuffer(data->value));
			switch(data->type)
			{
			case res_image_file:
				if(data->value)
				{
					wchar_t *pStr=XStr_GetBuffer(data->value);
					if(pStr)
						return XImage_LoadFile(pStr);
				}break;
			case res_image_file_stretch:
				if(data->value)
				{
					wchar_t *pStr=XStr_GetBuffer(data->value);
					if(pStr)
						return XImage_LoadFile(pStr,true);
				}break;
			case res_image_file_adaptive:
				if(data->value)
				{
					wchar_t *pStr=XStr_GetBuffer(data->value);
					if(pStr)
						return XImage_LoadFileAdaptive(pStr,data->x1,data->x2,data->y1,data->y2);
				}break;
			case res_image_vc:
				if(data->resType)
				{
					wchar_t *pResType=XStr_GetBuffer(data->resType);
					if(pResType)
						return XImage_LoadRes(data->resID,pResType);
				}break;
			case res_image_vc_stretch:
				if(data->resType)
				{
					wchar_t *pResType=XStr_GetBuffer(data->resType);
					if(pResType)
						return XImage_LoadRes(data->resID,pResType,true);
				}break;
			case res_image_vc_adaptive:
				if(data->resType)
				{
					wchar_t *pResType=XStr_GetBuffer(data->resType);
					if(pResType)
						return XImage_LoadResAdaptive(data->resID,pResType,data->x1,data->x2,data->y1,data->y2);
				}break;
			case res_image_zip:
				if(data->zipFile && data->value)
				{
					wchar_t *pZipFile=XStr_GetBuffer(data->zipFile);
					wchar_t *pImageName=XStr_GetBuffer(data->value);
					if(pZipFile && pImageName)
						return XImage_LoadZip(pZipFile,pImageName);
				}break;
			case res_image_zip_stretch:
				if(data->zipFile && data->value)
				{
					wchar_t *pZipFile=XStr_GetBuffer(data->zipFile);
					wchar_t *pImageName=XStr_GetBuffer(data->value);
					if(pZipFile && pImageName)
						return XImage_LoadZip(pZipFile,pImageName,0,true);
				}break;
			case res_image_zip_adaptive:
				if(data->zipFile && data->value)
				{
					wchar_t *pZipFile=XStr_GetBuffer(data->zipFile);
					wchar_t *pImageName=XStr_GetBuffer(data->value);
					if(pZipFile && pImageName)
						return XImage_LoadZipAdaptive(pZipFile,pImageName,0,data->x1,data->x2,data->y1,data->y2);
				}break;
			}
			return NULL;
		}
	}
	return NULL;
}

///@brief 销毁资源文件句柄.
///@param hXmlRes  资源文件句柄.
void WINAPI XXmlRes_Destroy(HXMLRES hXmlRes)
{
	if(NULL==hXmlRes) return;

	xmlRes_ *pXmlRes=(xmlRes_*)hXmlRes;

	xmlRes_data_  *data;
	int count;
	//ID
	count=XArray_GetCount(pXmlRes->hArray_ID);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_ID,i);
		XStr_Destroy(data->name);
		XStr_Destroy(data->value);
		free(data);
	}
	//Image
	count=XArray_GetCount(pXmlRes->hArray_Image);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_Image,i);
		XStr_Destroy(data->name);
		XStr_Destroy(data->value);
		if(data->resType) XStr_Destroy(data->resType);
		if(data->zipFile) XStr_Destroy(data->zipFile);
		free(data);
	}
	//String
	count=XArray_GetCount(pXmlRes->hArray_String);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_String,i);
		XStr_Destroy(data->name);
		XStr_Destroy(data->value);
		free(data);
	}
	//Color
	count=XArray_GetCount(pXmlRes->hArray_Color);
	for(int i=0;i<count;i++)
	{
		data=(xmlRes_data_*)XArray_GetAt(pXmlRes->hArray_Color,i);
		XStr_Destroy(data->name);
		XStr_Destroy(data->value);
		free(data);
	}

	XArray_Destroy(pXmlRes->hArray_ID);
	XArray_Destroy(pXmlRes->hArray_Image);
	XArray_Destroy(pXmlRes->hArray_String);
	XArray_Destroy(pXmlRes->hArray_Color);
	free(pXmlRes);
}

///@}