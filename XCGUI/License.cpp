/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"



///////////////商业授权许可文件  Business license file///////////////////////////////////////////////////
#ifdef XCGUI_Business_license_file

void *g_pFixedKEY = NULL;  //固定版本KEY  m_fixedKEY
void *g_pBuffer = NULL;  //授权文件信息

void *g_pUnsrInfo = NULL;  //用户信息

void *g_pKeyRand = NULL;  //随机EKY

void *g_pEndKey1 = NULL; //对比KEY1
void *g_pEndKey2 = NULL; //对比KEY2

char init_key[] = XCGUI_VERSION_KEY;


void  *SN1 = NULL; //[5]={0};
void  *SN2 = NULL; //[5]={0};
void  *SN3 = NULL; //[5]={0};
void  *SN4 = NULL; //[5]={0};
void  *SN5 = NULL; //[5]={0};
void  *SN6 = NULL; //[5]={0};
void  *SN7 = NULL; //[5]={0};
void  *SN8 = NULL; //[5]={0};


BOOL T_ReadFile();
BOOL T_GetFileInfo();
BOOL T_GetRandKEY();
BOOL T_GetCMP_KEY();//提取对比KEY1-2
BOOL T_Count_Authorize();//1.计算授权信息-摘要--防止数据修改

BOOL My_Test()
{
	if (FALSE == T_ReadFile())
		return FALSE;

	if (FALSE == T_GetFileInfo())
		return FALSE;

	if (FALSE == T_GetRandKEY())
		return FALSE;

	if (FALSE == T_GetCMP_KEY())
		return FALSE;

	if (FALSE == T_Count_Authorize())
		return FALSE;

	return true;
}

//读取文件
BOOL T_ReadFile()
{
	FILE *pFile = fopen("XCGUI.txt", "rb");
	if (pFile)
	{
		g_pBuffer = malloc(XCGUI_SIZE_BUFFER);
		char *pBuffer = (char*)g_pBuffer;
		for (int i = 0; i < XCGUI_SIZE_BUFFER; i++)
		{
			pBuffer[i] = 0;
		}
		int length = fread(g_pBuffer, 1, 1022, pFile);
		if (length > 117 && length < XCGUI_SIZE_BUFFER) //39*3 90 27=117
		{
			fclose(pFile);
			return true;
		}
		free(g_pBuffer);
		g_pBuffer = NULL;
		fclose(pFile);
	}
	return FALSE;
}

//提取用户信息
BOOL T_GetFileInfo()
{
	char *buffer = (char*)g_pBuffer;
	char buf[1024] = { 0 };
	int len = 0;
	for (int i = 0; i < 1000; i++)
	{
		if ('\r' == buffer[i] || '\n' == buffer[i] || '\0' == buffer[i])
		{
			break;
		}
		buf[i] = buffer[i];
		len++;
	}
	len++;
	char *pAuthorize = (char*)malloc(len);
	for (int i = 0; i < len; i++)
	{
		pAuthorize[i] = buf[i];
	}
	pAuthorize[len - 1] = 0;
	g_pUnsrInfo = (void*)pAuthorize;
	return true;
}

//提取随机KEY
BOOL T_GetRandKEY()
{
	char *buffer = (char*)g_pBuffer;
	while ('\n' != (*buffer++));

	char buf[1024] = { 0 };
	int index = 0;
	while ('\n' != (*buffer) && '\0' != (*buffer))
	{
		if ('-' != (*buffer))
		{
			buf[index] = *buffer;
			index++;
		}
		buffer++;
	}

	char *pKeyRand = (char*)malloc(index + 1);
	for (int i = 0; i < index; i++)
	{
		pKeyRand[i] = buf[i];
	}
	pKeyRand[index] = 0;

	g_pKeyRand = (void*)pKeyRand;

	return true;
}

//提取对比KEY1-2
BOOL T_GetCMP_KEY()
{
	char *buffer = (char*)g_pBuffer;
	while ('\n' != (*buffer++)); //跳过用户信息

	while ('\n' != (*buffer++)); //跳过随机KEY

	char *pEndKey1 = (char*)malloc(33);
	for (int i = 0; i < 33; i++)
	{
		if ('-' == (*buffer))
			buffer++;
		pEndKey1[i] = *buffer;
		buffer++;
	}
	pEndKey1[32] = 0;

	for (int i = 0; i < 10; i++)
	{
		if ('\n' != (*++buffer))
			break;
	}

	char *pEndKey2 = (char*)malloc(33);
	for (int i = 0; i < 33; i++)
	{
		if ('-' == (*buffer))
			buffer++;
		pEndKey2[i] = *buffer;
		buffer++;
	}
	pEndKey2[32] = 0;

	g_pEndKey1 = pEndKey1;
	g_pEndKey2 = pEndKey2;

	return true;
}

BOOL T_HashAuthorize(unsigned char *authorize_32);
BOOL T_ResolveKey(unsigned char *authorize_32);
//1.计算授权信息-摘要--防止数据修改
BOOL T_Count_Authorize()
{
	//1.计算授权信息-摘要--防止数据修改
	//A*(1*2)+B*(2*2)+C*(3*3)=X;

	unsigned char *authorize = (unsigned char*)g_pUnsrInfo;
	unsigned int authorize_ss = 4200000000; //摘要
	unsigned int authorize_len = strlen((char*)authorize);
	for (unsigned int i = 2; i < authorize_len; i++)
	{
		authorize_ss += (authorize[i] * i*i);
	}

	//2.散列-用户信息
	unsigned char  authorize_32[33] = { 0 };
	T_HashAuthorize(authorize_32);


	//3.与摘要运行
	for (int i = 0; i < 32; i++)
	{
		authorize_32[i] = (authorize_ss + authorize_32[i]) % 255;
	}

	//4.与随机码合成
	char *keyRand = (char*)g_pKeyRand;
	for (int i = 0; i < 32; i++)
	{
		authorize_32[i] += keyRand[i];
	}

	//5.与固定key合成
	unsigned char *fixedKEY = (unsigned char*)g_pFixedKEY;
	for (int i = 0; i < 32; i++)
	{
		authorize_32[i] += fixedKEY[i];
	}

	T_ResolveKey(authorize_32);
	return true;
}

//2.散列-授权信息
BOOL T_HashAuthorize(unsigned char *authorize_32)
{
	//2.散列-用户信息
	unsigned char *authorize = (unsigned char*)g_pUnsrInfo;
	unsigned int authorize_len = strlen((char*)authorize);
	for (unsigned int i = 2; i < authorize_len; i++)
	{
		unsigned int index = authorize[i] % 32;
		authorize_32[index] += authorize[i];
	}

	//g_pFixedKEY  // 生成固定KEY
	unsigned char *FixedKEY = (unsigned char*)malloc(33);
	memcpy(FixedKEY, init_key, 32);
	FixedKEY[32] = 0;
	g_pFixedKEY = (void*)FixedKEY;

	return true;
}

//6.分8块单独加密,每个加密算法都不同,相当于8个关卡,生成对比码
BOOL T_ResolveKey(unsigned char *authorize_32)
{
	unsigned char *SN_PP1 = (unsigned char *)malloc(5);
	unsigned char *SN_PP2 = (unsigned char *)malloc(5);
	unsigned char *SN_PP3 = (unsigned char *)malloc(5);
	unsigned char *SN_PP4 = (unsigned char *)malloc(5);
	unsigned char *SN_PP5 = (unsigned char *)malloc(5);
	unsigned char *SN_PP6 = (unsigned char *)malloc(5);
	unsigned char *SN_PP7 = (unsigned char *)malloc(5);
	unsigned char *SN_PP8 = (unsigned char *)malloc(5);
	SN_PP1[4] = 0;
	SN_PP2[4] = 0;
	SN_PP3[4] = 0;
	SN_PP4[4] = 0;
	SN_PP5[4] = 0;
	SN_PP6[4] = 0;
	SN_PP7[4] = 0;
	SN_PP8[4] = 0;

	for (int i = 0; i < 4; i++)
	{
		SN_PP1[i] = authorize_32[i];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP2[i] = authorize_32[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP3[i] = authorize_32[i + 8];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP4[i] = authorize_32[i + 12];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP5[i] = authorize_32[i + 16];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP6[i] = authorize_32[i + 20];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP7[i] = authorize_32[i + 24];
	}
	for (int i = 0; i < 4; i++)
	{
		SN_PP8[i] = authorize_32[i + 28];
	}

	SN1 = SN_PP1; //[5]={0};
	SN2 = SN_PP2; //[5]={0};
	SN3 = SN_PP3; //[5]={0};
	SN4 = SN_PP4; //[5]={0};
	SN5 = SN_PP5; //[5]={0};
	SN6 = SN_PP6; //[5]={0};
	SN7 = SN_PP7; //[5]={0};
	SN8 = SN_PP8; //[5]={0};

	//	for( int i=0;i<32;i++ )
	//	{
	//		XTRACE("%02X \n",(int)(authorize_32[i]));
	//	}
	/*

	//验证
	//------1----------------------------

	int SN1_INT=SN1[0]+SN1[1]+SN1[2]+SN1[3];
	SN1_INT=SN1_INT/3;

	SN1[0]+=SN1_INT;
	SN1[1]+=SN1_INT;
	SN1[2]+=SN1_INT;
	SN1[3]+=SN1_INT;

	//------2---------------------------------------

	int SN2_INT=SN2[0]+SN2[1]+SN2[2]+SN2[3];
	SN2_INT=SN2_INT/5;

	SN2_INT=(~SN2_INT);
	SN2[0]+=SN2_INT;
	SN2[1]+=SN2_INT;
	SN2[2]+=SN2_INT;
	SN2[3]+=SN2_INT;

	//------3-------------------------------------

	SN3[0]=(SN3[0]-22)*3;
	SN3[1]=(SN3[1]-22)*3;
	SN3[2]=(SN3[2]-22)*3;
	SN3[3]=(SN3[3]-22)*3;

	SN3[0]+=(385%5);
	SN3[1]+=(385%5);
	SN3[2]+=(385%5);
	SN3[3]+=(385%5);

	SN3[0]=SN3[0]<<2;
	SN3[1]=SN3[1]<<2;
	SN3[2]=SN3[2]<<2;
	SN3[3]=SN3[3]<<2;

	//------4-------------------------------------------

	SN4[0]=SN4[0]<<1;
	SN4[1]=SN4[1]<<1;
	SN4[2]=SN4[2]<<1;
	SN4[3]=SN4[3]<<1;

	SN4[0]+=SN4[2];
	SN4[1]+=SN4[1];
	SN4[2]+=SN4[3];
	SN4[3]+=SN4[0];

	//------5--------------------------------
	SN5[0]=SN5[1]-2;
	SN5[1]=SN5[2]+10;
	SN5[2]=SN5[3]*8;
	SN5[3]=SN5[0]/9;


	//-------6-------------------
	SN6[0]+=SN6[2]+22;
	SN6[1]+=SN6[1]+31;
	SN6[2]+=SN6[3]+116;
	SN6[3]+=SN6[0]+33;

	//-------7------------------

	SN7[0]+=SN7[2]+77;
	SN7[1]+=SN7[1]+45;
	SN7[2]+=SN7[3]+12;
	SN7[3]+=SN7[0]+89;

	//------8------------

	SN8[0]+=SN8[2]+14;
	SN8[1]+=SN8[1]+67;
	SN8[2]+=SN8[3]+34;
	SN8[3]+=SN8[0]+39;
	//------------------------------------------


	char endKey1_end[40]={0};
	char endKey2_end[40]={0};
	sprintf(endKey1_end,"%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X",
	(int)SN1[0],(int)SN1[1],(int)SN1[2],(int)SN1[3],
	(int)SN2[0],(int)SN2[1],(int)SN2[2],(int)SN2[3],
	(int)SN3[0],(int)SN3[1],(int)SN3[2],(int)SN3[3],
	(int)SN4[0],(int)SN4[1],(int)SN4[2],(int)SN4[3]);

	sprintf(endKey2_end,"%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X",
	(int)SN5[0],(int)SN5[1],(int)SN5[2],(int)SN5[3],
	(int)SN6[0],(int)SN6[1],(int)SN6[2],(int)SN6[3],
	(int)SN7[0],(int)SN7[1],(int)SN7[2],(int)SN7[3],
	(int)SN8[0],(int)SN8[1],(int)SN8[2],(int)SN8[3]);

	XTRACE("key1=%s \n",endKey1_end);
	XTRACE("key2=%s \n",endKey2_end);
	*/
	return true;
}


BOOL T_Test_UU1()
{
	//验证
	//------1----------------------------

	unsigned char *pSNtY = (unsigned char *)SN1;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	int SN_INT = SNT[0] + SNT[1] + SNT[2] + SNT[3];
	SN_INT = SN_INT / 3;

	SNT[0] += SN_INT;
	SNT[1] += SN_INT;
	SNT[2] += SN_INT;
	SNT[3] += SN_INT;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = (char*)g_pEndKey1;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 111\n");
	return true;
}

BOOL T_Test_UU2()
{
	unsigned char *pSNtY = (unsigned char *)SN2;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	int SN2_INT = SNT[0] + SNT[1] + SNT[2] + SNT[3];
	SN2_INT = SN2_INT / 5;

	SN2_INT = (~SN2_INT);
	SNT[0] += SN2_INT;
	SNT[1] += SN2_INT;
	SNT[2] += SN2_INT;
	SNT[3] += SN2_INT;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = ((char*)g_pEndKey1) + 8;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 222\n");
	return true;
}
BOOL T_Test_UU3()
{
	//------3-------------------------------------
	unsigned char *pSNtY = (unsigned char *)SN3;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	SNT[0] = (SNT[0] - 22) * 3;
	SNT[1] = (SNT[1] - 22) * 3;
	SNT[2] = (SNT[2] - 22) * 3;
	SNT[3] = (SNT[3] - 22) * 3;

	SNT[0] += (385 % 5);
	SNT[1] += (385 % 5);
	SNT[2] += (385 % 5);
	SNT[3] += (385 % 5);

	SNT[0] = SNT[0] << 2;
	SNT[1] = SNT[1] << 2;
	SNT[2] = SNT[2] << 2;
	SNT[3] = SNT[3] << 2;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = ((char*)g_pEndKey1) + 16;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 333\n");
	return true;
}
BOOL T_Test_UU4()
{
	//------4-------------------------------------------
	unsigned char *pSNtY = (unsigned char *)SN4;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	SNT[0] = SNT[0] << 1;
	SNT[1] = SNT[1] << 1;
	SNT[2] = SNT[2] << 1;
	SNT[3] = SNT[3] << 1;

	SNT[0] += SNT[2];
	SNT[1] += SNT[1];
	SNT[2] += SNT[3];
	SNT[3] += SNT[0];

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = ((char*)g_pEndKey1) + 24;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 444\n");
	return true;
}
BOOL T_Test_UU5()
{
	//------5--------------------------------
	unsigned char *pSNtY = (unsigned char *)SN5;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	SNT[0] = SNT[1] - 2;
	SNT[1] = SNT[2] + 10;
	SNT[2] = SNT[3] * 8;
	SNT[3] = SNT[0] / 9;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = (char*)g_pEndKey2;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 555\n");
	return true;
}
BOOL T_Test_UU6()
{
	//-------6-------------------
	unsigned char *pSNtY = (unsigned char *)SN6;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	SNT[0] += SNT[2] + 22;
	SNT[1] += SNT[1] + 31;
	SNT[2] += SNT[3] + 116;
	SNT[3] += SNT[0] + 33;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = ((char*)g_pEndKey2) + 8;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 666\n");
	return true;
}
BOOL T_Test_UU7()
{
	//-------7------------------
	unsigned char *pSNtY = (unsigned char *)SN7;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	SNT[0] += SNT[2] + 77;
	SNT[1] += SNT[1] + 45;
	SNT[2] += SNT[3] + 12;
	SNT[3] += SNT[0] + 89;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = ((char*)g_pEndKey2) + 16;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 777\n");
	return true;
}
BOOL T_Test_UU8()
{
	//------8------------
	unsigned char *pSNtY = (unsigned char *)SN8;
	unsigned char SNT[5] = { 0 };
	SNT[0] = pSNtY[0];
	SNT[1] = pSNtY[1];
	SNT[2] = pSNtY[2];
	SNT[3] = pSNtY[3];

	SNT[0] += SNT[2] + 14;
	SNT[1] += SNT[1] + 67;
	SNT[2] += SNT[3] + 34;
	SNT[3] += SNT[0] + 39;

	char SNS[9] = { 0 };
	sprintf(SNS, "%02X%02X%02X%02X", (int)SNT[0], (int)SNT[1], (int)SNT[2], (int)SNT[3]);

	char *KEY = ((char*)g_pEndKey2) + 24;
	for (int i = 0; i < 8; i++)
	{
		if (SNS[i] != KEY[i])
			return FALSE;
	}
	//XTRACE("相等 888\n");
	return true;
}


BOOL T_XCGUI_Release()
{
	if (g_pFixedKEY) free(g_pFixedKEY);
	if (g_pBuffer) free(g_pBuffer);
	if (g_pUnsrInfo) free(g_pUnsrInfo);
	if (g_pKeyRand) free(g_pKeyRand);
	if (g_pEndKey1) free(g_pEndKey1);
	if (g_pEndKey2) free(g_pEndKey2);
	if (SN1) free(SN1);
	if (SN2) free(SN2);
	if (SN3) free(SN3);
	if (SN4) free(SN4);
	if (SN5) free(SN5);
	if (SN6) free(SN6);
	if (SN7) free(SN7);
	if (SN8) free(SN8);
	return true;
}
#endif
///////////////商业授权-序列号  Business license serial number/////////////////////////////////////////
#ifdef  XCVGUI_Business_license_serial_number
void *pSTKJJ = NULL;   //固定KEY
void *pUI_Set1 = NULL; //解密码 16
void *pUI_Set2 = NULL; //对比码 16

BOOL LL_XY_2(char *SS);
BOOL LL_YY_3();

char init_key[] = XCGUI_VERSION_KEY;

void SSLWnd_Init(char *SS)
{
	int len = 0;
	while ('\0' != SS[len])
		len++;
	if (39 != len)
		return;

	LL_XY_2(SS);
}
//分解
BOOL LL_XY_2(char *SS)
{
	char *pKEY1 = (char*)malloc(17);
	for (int i = 0; i < 16; i++)
	{
		if ('-' == *SS)
			SS++;
		pKEY1[i] = *SS;
		SS++;
	}
	pKEY1[16] = 0;


	SS++;
	char *pKEY2 = (char*)malloc(17);
	for (int i = 0; i < 16; i++)
	{
		if ('-' == *SS)
			SS++;
		pKEY2[i] = *SS;
		SS++;
	}
	pKEY2[16] = 0;

	pUI_Set1 = pKEY1;
	pUI_Set2 = pKEY2;

	LL_YY_3();

	return true;
}

BOOL  LL_GG_PPHH();

//合成KEY 16   与固定KEY合成
BOOL  LL_YY_3()
{
	pSTKJJ = malloc(33);
	memcpy(pSTKJJ, init_key, 32);
	((char*)pSTKJJ)[32] = 0;

	unsigned char *KEY = (unsigned char *)pSTKJJ;
	unsigned char *KKS_jj = (unsigned char *)pUI_Set1;

	for (int i = 0; i < 16; i++)
		KKS_jj[i] += KEY[i];

	KEY += 16;
	for (int i = 0; i < 16; i++)
		KKS_jj[i] += KEY[i];

	free(pSTKJJ);
	return true;
}


//验证
BOOL  LL_GG_PPHH()
{
	if (NULL == pUI_Set1)
		return FALSE;

	if (NULL == pUI_Set2)
		return FALSE;

	unsigned char *Set1tt = (unsigned char *)pUI_Set1;
	unsigned char *Set1 = (unsigned char *)malloc(17);
	for (int i = 0; i < 16; i++)
	{
		Set1[i] = Set1tt[i];
	}

	char *Set2 = (char *)pUI_Set2;

	Set1[0] = Set1[0] + 20;
	Set1[1] = Set1[1] + 9;
	Set1[2] = Set1[2] + 3;
	Set1[3] = Set1[3] + 56;
	Set1[4] = Set1[4] + 33;
	Set1[5] = Set1[5] + 4;
	Set1[6] = Set1[6] + 8;
	Set1[7] = Set1[7] + 2;
	Set1[8] = Set1[8] + 33;
	Set1[9] = Set1[9] + 8;
	Set1[10] = Set1[10] + 4;
	Set1[11] = Set1[11] + 7;
	Set1[12] = Set1[12] + 34;
	Set1[13] = Set1[13] + 87;
	Set1[14] = Set1[14] + 2;
	Set1[15] = Set1[15] + 3;

	Set1[0] += Set1[8];
	Set1[1] += Set1[9];
	Set1[2] += Set1[10];
	Set1[3] += Set1[11];
	Set1[4] += Set1[12];
	Set1[5] += Set1[13];
	Set1[6] += Set1[14];
	Set1[7] += Set1[15];

	char STYY[17] = { 0 };
	sprintf_s(STYY, "%02X%02X%02X%02X%02X%02X%02X%02X",
		(int)Set1[0], (int)Set1[1], (int)Set1[2], (int)Set1[3], (int)Set1[4], (int)Set1[5], (int)Set1[6], (int)Set1[7]);

	for (int i = 0; i < 16; i++)
	{
		if (STYY[i] != Set2[i])
			return FALSE;
	}
	free(Set1);
	return true;
}




#endif
///////////////免费版   Free version//////////////////////////////////////
#ifdef XCGUI_Free_version
/*
BOOL Btn_GetRect_ToWindow()
{
//加入时间控制
CTime tm1(2012,3,23,0,0,0);
CTime tm2=CTime::GetCurrentTime();
CTimeSpan span=tm2-tm1;
int iDay=(int)span.GetDays();
if(iDay>90) //90天
{
return FALSE;
}

return true;
}
*/
#endif
////////////////////////////////////////////////



