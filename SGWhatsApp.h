// WhatsAppSender.cpp : a c++ class for sending WhatsApp messages
// using the WhatsAppMate API https://www.whatsmate.net/whatsapp-gateway-api.html 
// By Michael Haephrati, Secured Globe, Inc.

#pragma once

#include <tchar.h>

#define	GroupAdmin				L"<YOUR GROUP ADMIN MOBILE PHONE>"
#define GroupName				L"<YOUR GROUP NAME>"
#define CLIENT_ID				L"<YOUR CLIENT ID>"
#define CLIENT_SECRET			L"<YOUR CLIENT SECRET>"

#define GROUP_API_SERVER		L"api.whatsmate.net"
#define GROUP_API_PATH          L"/v3/whatsapp/group/text/message/12"
#define IMAGE_SINGLE_API_URL	L"http://api.whatsmate.net/v3/whatsapp/group/image/message/12"

class SGWhatsApp
{
public:
	SGWhatsApp();
	~SGWhatsApp();
	bool SendGroupMessage(LPCTSTR groupAdmin, LPCTSTR groupName, LPCTSTR message);
};

