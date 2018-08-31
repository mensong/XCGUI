/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//XML资源处理


enum res_type_
{
	res_id,     // 1.添加ID资源
	res_string, // 2.添加字符串资源
	res_color,  // 3.添加颜色资源

	res_image_file, // 4.从文件中加载图片
	res_image_file_stretch, // 5.从文件中加载图片,拉伸
	res_image_file_adaptive, // 6.从文件中加载图片,自适应图片

	res_image_vc, // 7.从程序资源中加载图片
	res_image_vc_stretch, // 8.从程序资源中加载图片,拉伸
	res_image_vc_adaptive,// 9.从程序资源中加载图片,自适应图片

	res_image_zip, // 10.从zip压缩包中加载图片
	res_image_zip_stretch, // 11.从zip压缩包中加载图片,拉伸
	res_image_zip_adaptive, // 12.从zip压缩包中加载图片,自适应图片
};


struct xmlRes_data_
{
	res_type_     type;   //资源类型 res_type_
	HSTRING name;  //名称
	HSTRING value; //值

	HSTRING resType;
	HSTRING zipFile;
	int  resID;

	int x1,x2,y1,y2;
};

struct xmlRes_
{
	HARRAY  hArray_ID;      //ID资源
	HARRAY  hArray_Image;   //图片资源
	HARRAY  hArray_String;  //字符串资源
	HARRAY  hArray_Color;   //颜色资源
};

//API:
XC_API HXMLRES WINAPI XXmlRes_Load(wchar_t *pFileName);
XC_API HXMLRES WINAPI XXmlRes_LoadRes(int resID,wchar_t *pType);//从VC资源文件中加载
XC_API void WINAPI XXmlRes_Destroy(HXMLRES hXmlRes);

//查找ID资源
XC_API int WINAPI XXmlRes_FindId(HXMLRES hXmlRes,wchar_t *pName);
//查找图片资源
XC_API void WINAPI XXmlRes_FindImage(HXMLRES hXmlRes,wchar_t *pName,out_ wchar_t *pOut,int outLen);

//查找字符串
XC_API void WINAPI XXmlRes_FindString(HXMLRES hXmlRes,wchar_t *pName,out_ wchar_t *pOut,int outLen);


//查找图片资源,返回图片句柄
XC_API HIMAGE WINAPI XXmlRes_FildHIMAGE(HXMLRES hXmlRes,wchar_t *pName);

//查找字符串资源

//查找颜色资源


//私有:
HXMLRES WINAPI XXmlRes_LoadX(TiXmlElement *pRoot);
HXMLRES XXmlRes_LoadRes2(char *pData);//从VC资源文件中加载
BOOL XmlRes_LoadXml(xmlRes_ *pXmlRes,TiXmlElement *pRoot);
BOOL XmlRes_HandImage(xmlRes_ *pXmlRes,TiXmlElement *pLabel,xmlRes_data_ *pItem);
