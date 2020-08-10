#pragma once
#include "util/stdafx.h"
#include <string>
using std::string;
class ZhugeIO
{
public:
	static string ZHUGE_APP_KEY;
	static string ZHUGE_SECRET_KEY;
	static long ZHUGE_SID;
	static string g_uidStr;
	static string g_tokenStr;
	static string gAuth;
	static string gVersion;
public:
	static const char* GetAuthority();
	static void init(const char* appkey, const char* secretkey,
		const char* uid, 
		const char* token,
		const char* vn);
	static const char* trackEventRaw(const char* eventName);
	static const char* trackEvent(const char* eventName, vector<string>& key, vector<string>& value, int size);
};

