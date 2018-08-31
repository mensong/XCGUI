/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0

#ifdef _DEBUG
#ifdef XCGUI_Free_version
int  GetSystemVersionInfo(char *pVersion)
{
	typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

	int pos = 0;
	char buffer[256] = { 0 };
	DWORD bufferSize = 256;

	OSVERSIONINFOEXA osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	BOOL bOsVersionInfoEx;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);

	if (!(bOsVersionInfoEx = GetVersionExA((OSVERSIONINFOA *)&osvi)))
	{
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
		if (!GetVersionExA((OSVERSIONINFOA *)&osvi))
			return FALSE;
	}

	// Call GetNativeSystemInfo if supported
	// or GetSystemInfo otherwise.
	pGNSI = (PGNSI)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetNativeSystemInfo");
	if (NULL != pGNSI)
		pGNSI(&si);
	else
		GetSystemInfo(&si);

	switch (osvi.dwPlatformId)
	{
		// Test for the Windows NT product family.
	case VER_PLATFORM_WIN32_NT:

		// Test for the specific product.
		if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
		{
			if (osvi.wProductType == VER_NT_WORKSTATION)
			{
				//  printf ("Windows Vista ");
				strcpy(pVersion + pos, "Windows Vista ");
				pos = strlen(pVersion);
			}
			else
			{
				// printf ("Windows Server \"Longhorn\" " );
				strcpy(pVersion + pos, "Windows Server \"Longhorn\" ");
				pos = strlen(pVersion);
			}
		}

		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
		{
			if (GetSystemMetrics(SM_SERVERR2))
			{
				// printf( "Microsoft Windows Server 2003 \"R2\" ");
				strcpy(pVersion + pos, "Microsoft Windows Server 2003 \"R2\" ");
				pos = strlen(pVersion);
			}
			else if (osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			{
				// printf( "Microsoft Windows XP Professional x64 Edition ");

				strcpy(pVersion + pos, "Microsoft Windows XP Professional x64 Edition ");
				pos = strlen(pVersion);
			}
			else
			{
				//printf ("Microsoft Windows Server 2003, ");
				strcpy(pVersion + pos, "Microsoft Windows Server 2003, ");
				pos = strlen(pVersion);
			}
		}

		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
		{
			//printf ("Microsoft Windows XP ");
			strcpy(pVersion + pos, "Microsoft Windows XP ");
			pos = strlen(pVersion);
		}
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
		{
			//printf ("Microsoft Windows 2000 ");
			strcpy(pVersion + pos, "Microsoft Windows 2000 ");
			pos = strlen(pVersion);
		}
		if (osvi.dwMajorVersion <= 4)
		{
			//printf ("Microsoft Windows NT ");
			strcpy(pVersion + pos, "Microsoft Windows NT ");
			pos = strlen(pVersion);
		}
		// Test for specific product on Windows NT 4.0 SP6 and later.
		if (bOsVersionInfoEx)
		{
			// Test for the workstation type.
			if (osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64)
			{
				if (osvi.dwMajorVersion == 4)
				{
					//	printf ( "Workstation 4.0 " );
					strcpy(pVersion + pos, "Workstation 4.0 ");
					pos = strlen(pVersion);
				}
				else if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
				{
					//	printf ( "Home Edition " );
					strcpy(pVersion + pos, "Home Edition ");
					pos = strlen(pVersion);
				}
				else
				{
					//	printf ( "Professional " );
					strcpy(pVersion + pos, "Professional ");
					pos = strlen(pVersion);
				}
			}
			// Test for the server type.
			else if (osvi.wProductType == VER_NT_SERVER || osvi.wProductType == VER_NT_DOMAIN_CONTROLLER)
			{
				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
				{
					if (si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_IA64)
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
						{
							//	printf ( "Datacenter Edition for Itanium-based Systems" );
							strcpy(pVersion + pos, "Datacenter Edition for Itanium-based Systems");
							pos = strlen(pVersion);
						}
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						{
							//	printf ( "Enterprise Edition for Itanium-based Systems" );
							strcpy(pVersion + pos, "Enterprise Edition for Itanium-based Systems");
							pos = strlen(pVersion);
						}
					}
					else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
						{
							//	printf ( "Datacenter x64 Edition " );
							strcpy(pVersion + pos, "Datacenter x64 Edition ");
							pos = strlen(pVersion);
						}
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						{
							//	printf ( "Enterprise x64 Edition " );
							strcpy(pVersion + pos, "Enterprise x64 Edition ");
							pos = strlen(pVersion);
						}
						else
						{
							//	printf( "Standard x64 Edition " );
							strcpy(pVersion + pos, "Standard x64 Edition ");
							pos = strlen(pVersion);
						}
					}
					else
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
						{
							//	printf ( "Datacenter Edition " );
							strcpy(pVersion + pos, "Datacenter Edition ");
							pos = strlen(pVersion);
						}
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						{
							//	printf ( "Enterprise Edition " );
							strcpy(pVersion + pos, "Enterprise Edition ");
							pos = strlen(pVersion);
						}
						else if (osvi.wSuiteMask & VER_SUITE_BLADE)
						{
							//	printf ( "Web Edition " );
							strcpy(pVersion + pos, "Web Edition ");
							pos = strlen(pVersion);
						}
						else
						{
							//	printf ( "Standard Edition " );
							strcpy(pVersion + pos, "Standard Edition ");
							pos = strlen(pVersion);
						}
					}
				}
				else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
				{
					if (osvi.wSuiteMask & VER_SUITE_DATACENTER)

					{
						//	printf ( "Datacenter Server " );
						strcpy(pVersion + pos, "Datacenter Server ");
						pos = strlen(pVersion);
					}
					else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
					{
						//	printf ( "Advanced Server " );
						strcpy(pVersion + pos, "Advanced Server ");
						pos = strlen(pVersion);

					}
					else
					{
						//	printf ( "Server " );
						strcpy(pVersion + pos, "Server ");
						pos = strlen(pVersion);
					}
				}
				else  // Windows NT 4.0 
				{
					if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
					{
						//printf ("Server 4.0, Enterprise Edition " );
						strcpy(pVersion + pos, "Server 4.0, Enterprise Edition ");
						pos = strlen(pVersion);
					}
					else
					{
						//	printf ( "Server 4.0 " );
						strcpy(pVersion + pos, "Server 4.0 ");
						pos = strlen(pVersion);
					}
				}
			}
		}
		// Test for specific product on Windows NT 4.0 SP5 and earlier
		else
		{
			HKEY hKey;
			//	TCHAR buffer[80];
			DWORD dwBufLen = bufferSize;
			LONG lRet;

			lRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &hKey);
			if (lRet != ERROR_SUCCESS)
				return FALSE;

			lRet = RegQueryValueExA(hKey, "ProductType", NULL, NULL, (LPBYTE)buffer, &dwBufLen);
			RegCloseKey(hKey);

			if ((lRet != ERROR_SUCCESS) || (dwBufLen > bufferSize))
				return FALSE;

			if (lstrcmpiA("WINNT", buffer) == 0)
			{
				//	printf( "Workstation " );
				strcpy(pVersion + pos, "Workstation ");
				pos = strlen(pVersion);
			}
			if (lstrcmpiA("LANMANNT", buffer) == 0)
			{
				//	printf( "Server " );
				strcpy(pVersion + pos, "Server ");
				pos = strlen(pVersion);
			}
			if (lstrcmpiA("SERVERNT", buffer) == 0)
			{
				//	printf( "Advanced Server " );
				//	printf( "%d.%d ", osvi.dwMajorVersion, osvi.dwMinorVersion );

				strcpy(pVersion + pos, "Advanced Server ");
				pos = strlen(pVersion);

				sprintf(buffer, "%d.%d ", osvi.dwMajorVersion, osvi.dwMinorVersion);
				strcpy(pVersion + pos, buffer);
				pos = strlen(pVersion);
			}
		}

		// Display service pack (if any) and build number.

		if (osvi.dwMajorVersion == 4 && lstrcmpiA(osvi.szCSDVersion, "Service Pack 6") == 0)
		{
			HKEY hKey;
			LONG lRet;

			// Test for SP6 versus SP6a.
			lRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009", 0, KEY_QUERY_VALUE, &hKey);
			if (lRet == ERROR_SUCCESS)
			{
				// printf( "Service Pack 6a (Build %d)\n", osvi.dwBuildNumber & 0xFFFF ); 
				sprintf(buffer, "Service Pack 6a (Build %d)\n", osvi.dwBuildNumber & 0xFFFF);
				strcpy(pVersion + pos, buffer);
				pos = strlen(pVersion);
			}
			else // Windows NT 4.0 prior to SP6a
			{
				//_tprintf( TEXT("%s (Build %d)\n"),osvi.szCSDVersion,osvi.dwBuildNumber & 0xFFFF);
				sprintf(buffer, "%s (Build %d)\n", osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
				strcpy(pVersion + pos, buffer);
				pos = strlen(pVersion);
			}

			RegCloseKey(hKey);
		}
		else // not Windows NT 4.0 
		{
			//_tprintf( TEXT("%s (Build %d)\n"),osvi.szCSDVersion,osvi.dwBuildNumber & 0xFFFF);
			sprintf(buffer, "%s (Build %d)\n", osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
			strcpy(pVersion + pos, buffer);
			pos = strlen(pVersion);
		}

		break;

		// Test for the Windows Me/98/95.
	case VER_PLATFORM_WIN32_WINDOWS:

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
		{
			//printf ("Microsoft Windows 95 ");
			strcpy(pVersion + pos, "Microsoft Windows 95 ");
			pos = strlen(pVersion);

			if (osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B')
			{
				//printf("OSR2 " );
				strcpy(pVersion + pos, "OSR2 ");
				pos = strlen(pVersion);
			}
		}
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
		{
			//printf ("Microsoft Windows 98 ");
			strcpy(pVersion + pos, "Microsoft Windows 98 ");
			pos = strlen(pVersion);
			if (osvi.szCSDVersion[1] == 'A' || osvi.szCSDVersion[1] == 'B')
			{
				printf("SE ");
				strcpy(pVersion + pos, "SE ");
				pos = strlen(pVersion);
			}
		}

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
		{
			//printf ("Microsoft Windows Millennium Edition\n");
			strcpy(pVersion + pos, "Microsoft Windows Millennium Edition\n");
			pos = strlen(pVersion);
		}
		break;

	case VER_PLATFORM_WIN32s:

		//printf ("Microsoft Win32s\n");
		strcpy(pVersion + pos, "Microsoft Win32s\n");
		pos = strlen(pVersion);
		break;
	}
	return TRUE;
}



bool GetHostAndIP(char *pHostName, DWORD pHostNameLen, char *pIP)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return false;
	}

	if (::GetComputerNameA(pHostName, &pHostNameLen))
	{
		hostent   *pHost;
		pHost = ::gethostbyname(pHostName);

		char*   psz;
		psz = inet_ntoa(*(struct   in_addr   *)pHost->h_addr_list[0]);

		sprintf(pIP, "%s", psz);
		return true;
	}
	WSACleanup();
	return false;
}

bool SenMail(char *subject, char *plaincontent)
{

#define SEND_EMAIL    "error_1.3.1@xcgui.com"
#define SEND_EMAIL_PASS   "kadfko45nj45n2"

	SOCKET srvrSocket;
	struct sockaddr_in srvrAddr;
	WORD ver;
	WSAData data;
	int z, len;
	char buffer[BUFFERLEN];
	char temp[TEMPLEN];
	char hostname[] = "smtp.ym.163.com"; //邮件服务器
	char username[] = SEND_EMAIL;        //发件人邮箱
	char password[] = SEND_EMAIL_PASS;   //密码 
	char sendname[] = "test";            //发件人昵称 
	char recvname[] = "user";            //收件人昵称
	char sendaddr[] = SEND_EMAIL; //发件人邮箱
	char recvaddr[] = SEND_EMAIL; //收件人邮箱

//	char subject[] = "Test mail";        //主题
//	char plaincontent[] = "Test content !!!"; //邮件内容

	ver = MAKEWORD(2, 0);
	z = WSAStartup(ver, &data);
	if (z < 0)
	{
		fprintf(stderr, "WSAStartup() error!\n");
		return false;
	}

	struct hostent* host = gethostbyname(hostname);
	if (NULL == host)
	{
		fprintf(stderr, "gethostbyname() error!\n");
		return false;
	}

	//srvrSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP ); 
	srvrSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (srvrSocket < 0)
	{
		fprintf(stderr, "Alloc socket handle failed!\n");
		return false;
	}

	memset(&srvrAddr, 0, sizeof srvrAddr);
	srvrAddr.sin_family = AF_INET;
	srvrAddr.sin_port = htons(PORT);
	srvrAddr.sin_addr.s_addr = *(ULONG *)host->h_addr;
	if (srvrAddr.sin_addr.s_addr == INADDR_NONE)
	{
		fprintf(stderr, "inet_addr() error!\n");
		return false;
	}

	len = sizeof srvrAddr;

	z = connect(srvrSocket, (struct sockaddr *) &srvrAddr, len);
	if (z < 0)
	{
		fprintf(stderr, "connet() error!\n");
		return false;
	}

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "220", 3) != 0) return false;

	//hello 
	if (gethostname(temp, TEMPLEN) != 0)
	{
		fprintf(stderr, "gethostname() error");
	}

	sprintf(buffer, "HELO %s\r\n", temp);
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "250", 3) != 0) return false;

	//login 
	strcpy(buffer, "AUTH LOGIN\r\n");
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "334", 3) != 0) return false;

	sprintf(buffer, "%s\r\n", encode(username, temp));
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "334", 3) != 0) return false;

	sprintf(buffer, "%s\r\n", encode(password, temp));
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "235", 3) != 0) return false;

	//send header 
	sprintf(buffer, "MAIL FROM: <%s>\r\n", sendaddr);
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "250", 3) != 0) return false;

	sprintf(buffer, "RCPT TO: <%s>\r\n", recvaddr);
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "250", 3) != 0) return false;

	//begin data
	strcpy(buffer, "DATA\r\n");
	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "354", 3) != 0) return false;


	sprintf(buffer, "From: \"%s\" <%s>\r\n", sendname, sendaddr);

	sprintf(temp, "To: \"%s\" <%s>\r\n", recvname, recvaddr);
	strcat(buffer, temp);

	time_t seconds;
	time(&seconds);
	strftime(temp, TEMPLEN, "%a, %d %b %y %H:%M:%S", localtime(&seconds));
	strcat(buffer, "Date: ");
	strcat(buffer, temp);
	strcat(buffer, "\r\n");

	sprintf(temp, "Subject: %s\r\n", subject);
	strcat(buffer, temp);

	strcat(buffer, "X-Mailer: SMailer\r\n");

	strcat(buffer, "X-Priority: 3\r\n");

	strcat(buffer, "MIME-Version: 1.0\r\n");
	strcat(buffer, "Content-type: multipart/mixed; boundary=\"");
	strcat(buffer, "#BOUNDARY#\"\r\n\r\n");

	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	//发送邮件正文
	//plainttxt 
	strcpy(buffer, "--#BOUNDARY#\r\n");
	strcat(buffer, "Content-Type: text/plain; charset=gb2312\r\n");

	strcat(buffer, "Content-Transfer-Encoding: 8bit\r\n\r\n");

	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	strcpy(buffer, plaincontent);

	strcat(buffer, "\r\n\r\n");

	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	//end data 
	strcpy(buffer, "\r\n--#BOUNDARY#--\r\n.\r\n");

	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "250", 3) != 0) return false;


	//quit 
	strcpy(buffer, "QUIT\r\n");

	z = MySend(srvrSocket, buffer, strlen(buffer));
	if (z < 0) return false;

	z = MyRecv(srvrSocket, buffer, BUFFERLEN);
	if (z < 0) return false;

	if (strncmp(buffer, "221", 3) != 0) return false;


	fprintf(stdout, "Successful end!!!\n");
	closesocket(srvrSocket);
	WSACleanup();

	return true;
}

char* encode(const char* in_str, char *out_str)
{
	const char base64_encode_chars[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned char c1, c2, c3;
	int i = 0;
	int j = 0;
	int len = strlen(in_str);


	while (i < len)
	{
		// read the first byte 
		c1 = in_str[i++];
		if (i == len)       // pad with "=" 
		{
			out_str[j++] = base64_encode_chars[c1 >> 2];
			out_str[j++] = base64_encode_chars[(c1 & 0x3) << 4];
			out_str[j++] = '=';
			out_str[j++] = '=';
			break;
		}

		// read the second byte 
		c2 = in_str[i++];
		if (i == len)       // pad with "=" 
		{
			out_str[j++] = base64_encode_chars[c1 >> 2];
			out_str[j++] = base64_encode_chars[((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4)];
			out_str[j++] = base64_encode_chars[(c2 & 0xF) << 2];
			out_str[j++] = '=';
			break;
		}

		// read the third byte 
		c3 = in_str[i++];
		// convert into four bytes string 
		out_str[j++] = base64_encode_chars[c1 >> 2];
		out_str[j++] = base64_encode_chars[((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4)];
		out_str[j++] = base64_encode_chars[((c2 & 0xF) << 2) | ((c3 & 0xC0) >> 6)];
		out_str[j++] = base64_encode_chars[c3 & 0x3F];
	}
	out_str[j] = 0;

	return out_str;
}

int MyRecv(SOCKET socket, char *buffer, int len)
{
	int z;

	z = WaitForRead(socket, 100);

	if (z < 0)
	{
		fprintf(stderr, "Select() faield!\n");
		closesocket(socket);
		return -1;
	}
	else if (z == 0)
	{
		fprintf(stdout, "Receive Time Out!\n");
		closesocket(socket);
		return -1;
	}

	z = recv(socket, buffer, len, 0);

	if (z < 0)
	{
		fprintf(stderr, "Receive failed!\n");
		closesocket(socket);
		return -1;
	}
	else if (z == 0)
	{
		fprintf(stdout, "Break by remote!\n");
		closesocket(socket);
		return -1;
	}

	buffer[z] = 0;

	fprintf(stdout, "[INFO]RECV(   ):%s\n", buffer);
	return z;
}

int MySend(SOCKET socket, char *buffer, int len)
{
	int z;

	z = WaitForWrite(socket, 100);

	if (z < 0)
	{
		fprintf(stderr, "Select() faield!\n");
		closesocket(socket);
		return -1;
	}
	else if (z == 0)
	{
		fprintf(stdout, "Receive Time Out!\n");
		closesocket(socket);
		return -1;
	}

	z = send(socket, buffer, len, 0);

	if (z < 0)
	{
		fprintf(stderr, "Receive failed!\n");
		closesocket(socket);
		return -1;
	}
	else if (z == 0)
	{
		fprintf(stdout, "Break by remote!\n");
		closesocket(socket);
		return -1;
	}

	fprintf(stdout, "[INFO]SEND:%s\n", buffer);
	return z;
}

int WaitForRead(SOCKET socket, int seconds)
{
	fd_set fds;
	struct timeval timeOut;
	int z;

	FD_ZERO(&fds);
	FD_SET(socket, &fds);

	timeOut.tv_sec = seconds;
	timeOut.tv_usec = 0;

	z = select(socket + 1, &fds, NULL, NULL, &timeOut);
	return z;
}

int WaitForWrite(SOCKET socket, int seconds)
{
	fd_set fds;
	struct timeval timeOut;
	int z;

	FD_ZERO(&fds);
	FD_SET(socket, &fds);

	timeOut.tv_sec = seconds;
	timeOut.tv_usec = 0;

	z = select(socket + 1, NULL, &fds, NULL, &timeOut);
	return z;
}

//如果需要发送报告返回 true, 否则返回false
bool RegMyKey(int &pOutUserID, char *reStartCount)
{
	HKEY hKEYResult;
	wchar_t * lpszSubKey;
	LONG ret;
	DWORD dwDisp;

	lpszSubKey = _T("SOFTWARE\\XCGUI");

	ret = RegOpenKeyEx(HKEY_CURRENT_USER, lpszSubKey, 0, KEY_WRITE | KEY_READ, &hKEYResult);
	if (ret != ERROR_SUCCESS) // 若打开失败，则进行创建
	{
		ret = RegCreateKeyEx(HKEY_CURRENT_USER, lpszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKEYResult, &dwDisp);
		if (ret != ERROR_SUCCESS) //创建失败
		{
			RegCloseKey(hKEYResult);
			return false;
		}
		else //创建成功
		{
			//写入日期
			char cur_date[50] = { 0 };
			time_t seconds;
			time(&seconds);
			strftime(cur_date, 50, "%Y-%m-%d", localtime(&seconds));

			ret = RegSetValueExA(hKEYResult, "date", 0, REG_SZ, (const BYTE *)cur_date, 50);
			if (ret != ERROR_SUCCESS) //创建失败
			{
				RegCloseKey(hKEYResult);
				return false;
			}

			//生成随机ID
			srand((unsigned)time(NULL));
			int userIDI = 0;
			userIDI = rand();
			userIDI += rand();
			userIDI += rand();
			userIDI += rand();

			ret = RegSetValueExA(hKEYResult, "user", 0, REG_DWORD, (const BYTE *)&userIDI, sizeof(DWORD));
			if (ret != ERROR_SUCCESS) //创建失败
			{
				RegCloseKey(hKEYResult);
				return false;
			}

			//初始索引,启动次数
			int index = 1;
			ret = RegSetValueExA(hKEYResult, "index", 0, REG_DWORD, (const BYTE *)&index, sizeof(DWORD));
			if (ret != ERROR_SUCCESS) //创建失败
			{
				RegCloseKey(hKEYResult);
				return false;
			}

			RegCloseKey(hKEYResult);

			sprintf(reStartCount, "启动次数,新用户");
			pOutUserID = userIDI;
			return true;  //发送报告
		}
	}
	else // 如打开成功，则进行查询
	{
		//查询日期
		DWORD dwType = REG_SZ;
		DWORD dwSize = 50;
		char date[50] = { 0 };
		ret = RegQueryValueExA(hKEYResult, "date", 0, &dwType, (LPBYTE)date, &dwSize);
		if (ret != ERROR_SUCCESS)
		{
			//	RegCloseKey(hKEYResult);
			//	return false;
		}

		//查询启动次数
		dwType = REG_DWORD;
		dwSize = sizeof(DWORD);
		int index = 1;
		ret = RegQueryValueExA(hKEYResult, "index", 0, &dwType, (LPBYTE)&index, &dwSize);
		if (ret != ERROR_SUCCESS)
		{
			//RegCloseKey(hKEYResult);
			//return false;
		}

		//当前日期
		char cur_date[50] = { 0 };
		time_t seconds;
		time(&seconds);
		strftime(cur_date, 50, "%Y-%m-%d", localtime(&seconds));

		//比较日期
		if (0 == strcmp(cur_date, date))
		{
			index++; //索引加1
			//更新索引
			ret = RegSetValueExA(hKEYResult, "index", 0, REG_DWORD, (const BYTE *)&index, sizeof(DWORD));
			if (ret != ERROR_SUCCESS) //创建失败
			{
				RegCloseKey(hKEYResult);
				return false;
			}

			RegCloseKey(hKEYResult);
			return false;
		}

		//重置启动索引
		int curIndex = 1;
		ret = RegSetValueExA(hKEYResult, "index", 0, REG_DWORD, (const BYTE *)&curIndex, sizeof(DWORD));
		if (ret != ERROR_SUCCESS) //创建失败
		{
			RegCloseKey(hKEYResult);
			return false;
		}

		//更新日期
		ret = RegSetValueExA(hKEYResult, "date", 0, REG_SZ, (const BYTE *)cur_date, 50);
		if (ret != ERROR_SUCCESS) //创建失败
		{
			RegCloseKey(hKEYResult);
			return false;
		}

		//查询userID
		dwType = REG_DWORD;
		dwSize = sizeof(DWORD);
		int userIDI = 0;
		ret = RegQueryValueExA(hKEYResult, "user", 0, &dwType, (LPBYTE)&userIDI, &dwSize);
		if (ret != ERROR_SUCCESS)
		{
			RegCloseKey(hKEYResult);
			return false;
		}

		RegCloseKey(hKEYResult);

		sprintf(reStartCount, "上次于[%s]日,启动[%d]次调试.", date, index);
		pOutUserID = userIDI;
		return true; //发送报告
	}
	return false;
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	//检查注册表,今天是否已经发送报告
	int  userID = 0;
	char reStartCount[100] = { 0 };
	if (false == RegMyKey(userID, reStartCount))
		return 0;
	//	printf("userID=%d \n",userID);

	char hostName[256] = { 0 };
	char MyIP[20] = { 0 };
	GetHostAndIP(hostName, 256, MyIP);
	//	printf("主机名=%s,IP=%s \n",hostName,MyIP);

		//获取系统版本信息
	char version[256] = { 0 };
	GetSystemVersionInfo(version);
	//	printf("systemVersion=%s",version);

		//VC版本
	char VC_VER[100] = { 0 };
	//int vcVer=_MSC_VER;
	switch (_MSC_VER)
	{
	case 1500: sprintf(VC_VER, "MS VC++9.0(%d)", _MSC_VER);  break;
	case 1400: sprintf(VC_VER, "MS VC++8.0(%d)", _MSC_VER); break;
	case 1310: sprintf(VC_VER, "MS VC++7.1(%d)", _MSC_VER); break;
	case 1300: sprintf(VC_VER, "MS VC++7.0(%d)", _MSC_VER); break;
	case 1200: sprintf(VC_VER, "MS VC++6.0(%d)", _MSC_VER); break;
	case 1100: sprintf(VC_VER, "MS VC++5.0(%d)", _MSC_VER); break;
	default:  sprintf(VC_VER, "MS VC++其他版本(%d)", _MSC_VER); break;
	}

	//	printf("VC=%s \n",VC_VER);

	char subject[500] = { 0 };
	sprintf(subject, "v1.3.5,用户ID:%d,主机名:%s,启动次数:%s", userID, hostName, reStartCount);

	char  buffer[1024] = { 0 };
	sprintf(buffer, "用户ID:%d,\r\n 主机名:%s,\r\n IP:%s,\r\n 操作系统版本:%s VC版本:%s, \r\n启动次数:%s",
		userID, hostName, MyIP, version, VC_VER, reStartCount);

	printf("-------------------------\n");
	printf(buffer);
	printf("-------------------------\n");
	//邮箱主题:用户名,主机名,启动次数
	if (true == SenMail(subject, buffer))
	{
		printf("发送成功-----\n");
	}

	//getchar();
	return 0;
}

bool sendEMailReport()
{
	if (0 != IsDebuggerPresent())
	{
		printf("调试模式\n");
	}
	else
	{
		printf("非调试模式\n");
		return false;
	}

	CreateThread(NULL, NULL, ThreadProc, NULL, NULL, NULL);

	return 0;
}

#endif  //XCGUI_Free_version
#endif  //_DEBUG

#endif