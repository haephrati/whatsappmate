// WhatsAppSender.cpp : a c++ class for sending WhatsApp messages
// using the WhatsAppMate API https://www.whatsmate.net/whatsapp-gateway-api.html 
// By Michael Haephrati, Secured Globe, Inc.

#include "stdafx.h"

#include "SGWhatsApp.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	SGWhatsApp sender;
	sender.SendGroupMessage(GroupAdmin, GroupName, _T("hi"));
	return 0;
}

