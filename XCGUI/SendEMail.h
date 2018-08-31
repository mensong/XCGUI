/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

#if 0

#ifdef _DEBUG
#ifdef XCGUI_Free_version

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> 

#define PORT 25                          
#define BUFFERLEN 1024                  
#define TEMPLEN   1024 

int WaitForRead(SOCKET socket, int seconds);
int WaitForWrite(SOCKET socket, int seconds);
int MyRecv(SOCKET socket, char *buffer, int len);
int MySend(SOCKET socket, char *buffer, int len);
char* encode(const char* in_str, char *out_str);
bool SenMail(char *subject, char *plaincontent); //主题,内容


int  GetSystemVersionInfo(char *pVersion);
bool GetHostAndIP(char *pHostName, DWORD pHostNameLen, char *pIP);

//如果需要发送报告返回 true, 否则返回false;上次启动次数
bool RegMyKey(int &pOutUserID, char *reStartCount);

bool sendEMailReport();
#else
#define sendEMailReport()
#endif //XCGUI_Free_version

#else
#define sendEMailReport()
#endif //_DEBUG

#endif