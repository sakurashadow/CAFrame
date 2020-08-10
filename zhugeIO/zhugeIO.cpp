// zhuge.cpp : 定义 DLL 应用程序的导出函数。
//

#include <chrono>
#include "zhugeIO.h"
#include "curl_manager.h"
//string ZhugeIO::ZHUGE_APP_KEY = "0bf33dd8024248eeae434e88b0907f44";
//string ZhugeIO::ZHUGE_SECRET_KEY = "ca7184fcabe64f12be8216cb8a6bc05a";
//long ZhugeIO::ZHUGE_SID = 0;
//string ZhugeIO::g_uidStr = "";
//string ZhugeIO::g_tokenStr = "";
//string ZhugeIO::gAuth = "";
//string ZhugeIO::gVersion = "";

const char* ZhugeIO::GetAuthority()
{
	string key = ZHUGE_APP_KEY + ":" + ZHUGE_SECRET_KEY;
	gAuth = "Authorization: Basic " + CBase64::Encode((const unsigned char*)key.c_str(), key.size());
	OutputDebugStringA(gAuth.c_str());
	return gAuth.c_str();
}

void ZhugeIO::init(const char* appkey, const char* secretkey,
	const char* uid,
	const char* token,
	const char* vn)
{
	ZhugeIO::ZHUGE_APP_KEY = appkey;
	ZhugeIO::ZHUGE_SECRET_KEY = secretkey;
	ZhugeIO::gVersion = vn;
	ZhugeIO::g_uidStr = uid;
	ZhugeIO::g_tokenStr = token;
	if (ZHUGE_SID == 0)
	{
		ZHUGE_SID = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	Initcurl();
	auto strOutput = "appkey = " + ZHUGE_APP_KEY + ",secretkey = " + ZHUGE_SECRET_KEY;
	OutputDebugStringA(strOutput.c_str());
}
//size_t writeCb(void* data, size_t size, size_t nmemb, string& content)
//{
//	long sizes = size * nmemb;
//	string url = CTransCoding::UTF8_To_GBK(string((char*)data));
//	//	content += string((char*)data, sizes);
//	printf("content = %s", url.c_str());
//	return sizes;
//};
const char* postEvent(const char* EventName, vector<string> key, vector<string> value, int size, writeCb cb) {
	Document doc;
	doc.SetObject();    //key-value 相当与map
	Document::AllocatorType& allocator = doc.GetAllocator(); //获取分配器
	Value pr_data(kObjectType);
	Value usr_data(kObjectType);
	string appKey = CTransCoding::GBK_To_UTF8(ZhugeIO::ZHUGE_APP_KEY);
	doc.AddMember("ak", rapidjson::StringRef(appKey.c_str()), allocator);
	doc.AddMember("dt", "evt", allocator);
	doc.AddMember("pl", "js", allocator);
	pr_data.AddMember("$ct", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(), allocator);
	string strEventLog = string("事件名：") + EventName;
	OutputDebugStringA(strEventLog.c_str());
	string event = CTransCoding::GBK_To_UTF8(EventName);
	pr_data.AddMember("$eid", rapidjson::StringRef(event.c_str()), allocator);
	if (ZhugeIO::g_uidStr.empty() || ZhugeIO::g_uidStr == "")
	{
		pr_data.AddMember("$cuid", rapidjson::StringRef("000000"), allocator);
	}
	else
	{
		pr_data.AddMember("$cuid", rapidjson::StringRef(ZhugeIO::g_uidStr.c_str()), allocator);
	}

	pr_data.AddMember("$sid", ZhugeIO::ZHUGE_SID, allocator);
	pr_data.AddMember("$vn", rapidjson::StringRef(ZhugeIO::gVersion.c_str()), allocator);
	pr_data.AddMember("$os", "windows", allocator);
	usr_data.AddMember("did", rapidjson::StringRef(ZhugeIO::g_tokenStr.substr(0, 15).c_str()), allocator);
	if (key.size() && value.size())
	{
		for (int i = 0; i < size; i++)
		{
			pr_data.AddMember(rapidjson::StringRef(key[i].c_str()),
				rapidjson::StringRef(value[i].c_str()), allocator);
		}
	}
	doc.AddMember("pr", pr_data, allocator);
	doc.AddMember("usr", usr_data, allocator);
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	send(ZhugeIO::gAuth, buffer.GetString(), cb);
	//ZhugeIO::gAuth = buffer.GetString();
	return "";
}


const char* ZhugeIO::trackEventRaw(const char* eventName)
{
	return postEvent(eventName, vector<string>(), vector<string>(), 0);
};

const char* ZhugeIO::trackEvent(const char* eventName, vector<string>& key, vector<string>& value, int size)
{
	return postEvent(eventName, key, value, size);
};
