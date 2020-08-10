// IPC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "../include/interface.h"
#include "zhugeIO.h"
#include "../include/protocol/proto_zhuge.h"
#include "../include/json/json.hpp"

int InitZhuge(ResultCallback res_cb, void* pThis, void* pParam)
{
	json jParam = json::parse((char*)pParam);
	ns::set_init param = jParam;
	ZhugeIO::init(param.appkey.c_str(), param.secrectkey.c_str(), 
		param.uid.c_str(),
		param.token.c_str(),
		param.vn.c_str());
	res_cb(pThis, pParam, 0);
	return 0;
}

int trackEvent(ResultCallback res_cb, void* pThis, void* pParam)
{
	json jParam = json::parse((char*)pParam);
	ns::events param = jParam;
	const char* pRet = nullptr;
	if (param.keys.size() == 0)
	{
		pRet = ZhugeIO::trackEventRaw(param.name.c_str());
	}
	else
	{ 
		pRet = ZhugeIO::trackEvent(param.name.c_str(), param.keys, param.values, param.size);
	}
	int len = strlen(pRet) + 1;
	res_cb(pThis, (void*)pRet, len);
	return 0;
}

//string ZhugeIO::ZHUGE_APP_KEY = "0bf33dd8024248eeae434e88b0907f44";
//string ZhugeIO::ZHUGE_SECRET_KEY = "ca7184fcabe64f12be8216cb8a6bc05a";
int main()
{
	ZhugeIO::init("0bf33dd8024248eeae434e88b0907f44","ca7184fcabe64f12be8216cb8a6bc05a",
		"uid123",
		"token123",
		"vn1.0");
	auto pRet = ZhugeIO::trackEventRaw("test_click");
	return 0;
}
