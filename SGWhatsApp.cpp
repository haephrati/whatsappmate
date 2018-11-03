// WhatsAppSender.cpp : a c++ class for sending WhatsApp messages
// using the WhatsAppMate API https://www.whatsmate.net/whatsapp-gateway-api.html 
// By Michael Haephrati, Secured Globe, Inc.

#include "stdafx.h"
#include "SGWhatsApp.h"

#include <string>

#include <Wininet.h>
#pragma comment(lib,"wininet.lib")

#define BUFFER_LENGTH 1024


SGWhatsApp::SGWhatsApp()
{
}


SGWhatsApp::~SGWhatsApp()
{
}

bool SGWhatsApp::SendGroupMessage(LPCTSTR groupAdmin, LPCTSTR groupName, LPCTSTR message)
{
	BOOL bResults = FALSE;
	HINTERNET hOpenHandle, hConnectHandle;
	const TCHAR* szHeaders = _T("Content-Type:application/json; charset=utf-8\r\n");


	hOpenHandle = InternetOpen(_T("HTTP"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hOpenHandle == NULL)
	{
		return bResults;
	}


	hConnectHandle = InternetConnect(hOpenHandle,
		GROUP_API_SERVER,
		INTERNET_DEFAULT_HTTP_PORT,
		NULL, NULL, INTERNET_SERVICE_HTTP,
		0, 1);

	if (hConnectHandle == NULL)
	{
		InternetCloseHandle(hOpenHandle);
		return bResults;
	}

	const wchar_t *AcceptTypes[] = { _T("application/json"),NULL };
	HINTERNET hRequest = HttpOpenRequest(hConnectHandle, _T("POST"), GROUP_API_PATH, NULL, NULL, AcceptTypes, 0, 0);

	if (hRequest == NULL)
	{
		InternetCloseHandle(hConnectHandle);
		InternetCloseHandle(hOpenHandle);
		return bResults;
	}

	std::wstring HeaderData;
			
	HeaderData += _T("X-WM-CLIENT-ID: ");
	HeaderData += CLIENT_ID;
	HeaderData += _T("\r\nX-WM-CLIENT-SECRET: ");
	HeaderData += CLIENT_SECRET;
	HeaderData += _T("\r\n");
	HttpAddRequestHeaders(hRequest, HeaderData.c_str(), HeaderData.size(), NULL);
	
	std::wstring WJsonData;
	WJsonData += _T("{");
	WJsonData += _T("\"group_admin\":\"");
	WJsonData += groupAdmin;
	WJsonData += _T("\",");
	WJsonData += _T("\"group_name\":\"");
	WJsonData += groupName;
	WJsonData += _T("\",");
	WJsonData += _T("\"message\":\"");
	WJsonData += message;
	WJsonData += _T("\"");
	WJsonData += _T("}");

	const std::string JsonData(WJsonData.begin(), WJsonData.end());

	bResults = HttpSendRequest(hRequest, NULL, 0, (LPVOID)(JsonData.c_str()), JsonData.size());
	
	TCHAR StatusText[BUFFER_LENGTH] = { 0 };
	DWORD StatusTextLen = BUFFER_LENGTH;
	HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_TEXT, &StatusText, &StatusTextLen, NULL);
	bResults = (StatusTextLen && wcscmp(StatusText, L"OK")==FALSE);

	
	InternetCloseHandle(hConnectHandle);
	InternetCloseHandle(hOpenHandle);

	return bResults;
}
