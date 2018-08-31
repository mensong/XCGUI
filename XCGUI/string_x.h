/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct string_
{
	object_ object;

	wchar_t *pData;   //数据
	int     count;   //当前字符数
	int     sum;     //当前可容纳字符数
	int     grow;    //增长值 //grow

};

#define STRING_SUM  8  //sum
#define STRING_GROW 8  //grow

//API:
XC_API HSTRING WINAPI XStr_Create(wchar_t *pString = NULL);
XC_API void WINAPI XStr_Destroy(HSTRING hStr);

XC_API void WINAPI XStr_InsertChar(HSTRING hStr, int index, wchar_t ch);  //插入
XC_API void WINAPI XStr_InsertString(HSTRING hStr, int index, wchar_t *pStr);
XC_API void WINAPI XStr_SetString(HSTRING hStr, wchar_t *pStr); //设置文本
XC_API void WINAPI XStr_AddString(HSTRING hStr, wchar_t *pStr); //添加文本到末尾
XC_API void WINAPI XStr_AddStringLength(HSTRING hStr, wchar_t *pStr, int strLen); //添加文本到末尾
XC_API void WINAPI XStr_SetLength(HSTRING hStr, int length); //设置字符串长度,多余的字符去掉

//pStrOld:将要替换的字符串,pStrNew:替换后的字符串
XC_API void WINAPI XStr_Replace(HSTRING hStr, wchar_t *pStrOld, wchar_t *pStrNew); //字符串替换 Replace

XC_API wchar_t* WINAPI XStr_GetBuffer(HSTRING hStr);
XC_API int WINAPI XStr_GetLength(HSTRING hStr);
XC_API wchar_t*  WINAPI XStr_Find(HSTRING hStr, wchar_t ch, int strart = 0); //查找字符
XC_API void WINAPI XStr_SetAt(HSTRING hStr, int index, wchar_t ch);//设置指定位置的一个字符
XC_API wchar_t WINAPI XStr_GetAt(HSTRING hStr, int index); //获取指定位置的一个字符
XC_API void WINAPI XStr_Empty(HSTRING hStr);    //清空
XC_API BOOL WINAPI XStr_IsEmpty(HSTRING hStr);  //判断是否为空
XC_API void WINAPI XStr_Delete(HSTRING hStr, wchar_t ch); //删除ch,全部ch删除
XC_API void WINAPI XStr_DeleteLength(HSTRING hStr, int index, int count = 1); //从index位置删除count个字符
XC_API void WINAPI XStr_DeleteFront(HSTRING hStr, int index); //删除指定位置之后的字符串
XC_API void WINAPI XStr_DeleteBack(HSTRING hStr, int index);  //删除指定位置之前的字符串

//私有方法
void Str_Init(HSTRING hStr);
void Str_Allocate(HSTRING hStr, int sum);  //空间不足 重新分配空间

//WideCharToMultiByte(CP_ACP,NULL,pInWChar,wcslen(pInWChar),pOutChar,outCharLength,NULL,NULL);
//MultiByteToWideChar(CP_ACP,0,pInChar,-1,pOutWChar,outWCharLength);

//16进制字符串转10进制
//int HexToDec(wchar_t *shex);

//isdigit();//判断是否为数字
//isalpha();//判断是否为字母
//isxdigit();//判断是否为16进制