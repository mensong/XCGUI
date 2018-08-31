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

	//	res_image,  // 添加图片资源:

	res_image_file, // 从文件中加载图片
	res_image_file_stretch, // 从文件中加载图片,拉伸
	res_image_file_adaptive, // 从文件中加载图片,自适应图片
	res_image_file_jiugongge, // 从文件中加载图片,九宫格

	res_image_vc, // 从程序资源中加载图片
	res_image_vc_stretch, // 从程序资源中加载图片,拉伸
	res_image_vc_adaptive,// 从程序资源中加载图片,自适应图片
	res_image_vc_jiugongge,	// 从程序资源中加载图片,九宫格

	res_image_zip, // 从zip压缩包中加载图片
	res_image_zip_stretch, // 从zip压缩包中加载图片,拉伸
	res_image_zip_adaptive, // 从zip压缩包中加载图片,自适应图片
	res_image_zip_jiugongge,	// 从zip压缩包中加载图片,九宫格

	res_font,
};


struct xmlRes_data_
{
	res_type_     type;   //资源类型 res_type_
	HSTRING  name;   //名称
	HSTRING  value;  //值

	//图片扩展信息
	//	int zoom; //no, stretch , adaptive
	//	int from; //file, res, zip

	HSTRING  resType;  //资源类型
	int  resID;    //资源ID
	HSTRING  zipPicName;     //zipBag
	HSTRING zipPassword;

	int x1, x2, y1, y2;					//图片选择区域
	int x11, x22, y11, y22;				//九宫格
};

struct xmlRes_
{
	HARRAY  hArray_ID;      //ID资源
	HARRAY  hArray_Image;   //图片资源
	HARRAY  hArray_String;  //字符串资源
	HARRAY  hArray_Color;   //颜色资源
	HARRAY  hArray_Font;   //字体资源
};

//API:
XC_API HXMLRES WINAPI XXmlRes_Load(wchar_t *pFileName);
XC_API HXMLRES WINAPI XXmlRes_LoadRes(int resID, wchar_t *pType);//从VC资源文件中加载
XC_API void WINAPI XXmlRes_Destroy(HXMLRES hXmlRes);

//查找ID资源
XC_API int WINAPI XXmlRes_FindId(HXMLRES hXmlRes, wchar_t *pName);
//查找图片资源
XC_API void WINAPI XXmlRes_FindImage(HXMLRES hXmlRes, wchar_t *pName, out_ wchar_t *pOut, int outLen);

//查找字符串
XC_API void WINAPI XXmlRes_FindString(HXMLRES hXmlRes, wchar_t *pName, out_ wchar_t *pOut, int outLen);


//查找图片资源,返回图片句柄
XC_API HIMAGE WINAPI XXmlRes_FildHIMAGE(HXMLRES hXmlRes, wchar_t *pName);

//查找字符串资源

//查找颜色资源


//私有:
HXMLRES XXmlRes_LoadX(TiXmlElement *pRoot);
HXMLRES XXmlRes_LoadRes2(char *pData);//从VC资源文件中加载
BOOL XmlRes_LoadXml(xmlRes_ *pXmlRes, TiXmlElement *pRoot);
BOOL XmlRes_HandImage(xmlRes_ *pXmlRes, TiXmlElement *pLabel, xmlRes_data_ *pItem);

BOOL CALLBACK OnInit();    //1 UI文件解析库初始化
BOOL CALLBACK OnExit();    //2 UI文件解析库释放
BOOL CALLBACK OnCreateWindow(HWINDOW hWindow);  // 3 窗口创建
BOOL CALLBACK OnCreateElement(HELE hEle);    // 4 元素创建