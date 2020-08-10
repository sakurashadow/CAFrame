// IPC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../include/interface.h"

#include <stdio.h>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include "impl_interface.h"

//#define printf LOG
using std::map;
using std::string;
typedef int (*funPtr2)(ResultCallback res_cb, void* pThis, void* pParam);
map<string, funPtr2> mapStringFunc2;

t_cmdExec parentCmd;
t_cmdExecAsync _parentCmdAsync;

#define REGISTER_FUN2(x) \
do{						\
	mapStringFunc2[#x] = x; \
} while (0);


//以下必须实现
int all_server_item(ResultCallback res_cb, void* pThis, void* pParam)
{
	string keys = "";
	for (auto & item : mapStringFunc2)
	{
		keys += item.first + ",";
	}
	res_cb(pThis, &keys, keys.size());
	return 0;
}

int init(t_cmdExec _cmd, t_cmdExecAsync _cmdAsyn, bool is_print_log)
{
	InitLog("zhugeIO.log", is_print_log);
	parentCmd = _cmd;
	_parentCmdAsync = _cmdAsyn;
	//char filepath[MAX_PATH] = { 0 };
	////获取exe执行文件名字(去掉后缀".exe")
	//GetModuleFileNameA(NULL, filepath, MAX_PATH);
	//*strrchr(filepath, '.') = '\0';  // 从最左边开始最后一次出现"."的位置(注：strchr/strrchr函数使用)
	//char* server_name = strrchr(filepath, '\\') + 1;
	printf("server %s : 加载%s\n", "zhugeIO", __FUNCTION__);

	REGISTER_FUN2(all_server_item);
	REGISTER_FUN2(InitZhuge);
	REGISTER_FUN2(trackEvent);
	return 0;
}

int cmd_ret_callback(
	ResultCallback res_cb,
	void* pThis,
	const char* pServerItemName,
	void* pParam)
{
	auto ret = mapStringFunc2.find(pServerItemName);
	if (ret != mapStringFunc2.end())
	{
		printf("server :调用%s函数\n", pServerItemName);
		int len = mapStringFunc2[pServerItemName](res_cb, pThis, pParam);
		return len;
	}
	return 0;
}
int cmd(const char* pServerItemName, char* pParam, char* pOutput)
{
	//auto ret = mapStringFunc.find(pServerItemName);
	//if (ret != mapStringFunc.end())
	//{
	//	printf("server :调用%s函数\n", pServerItemName);
	//	int len = mapStringFunc[pServerItemName](pParam, pOutput);
	//	return len;
	//}
	//return sprintf(pOutput, "调用失败，不存在%s函数\n", pServerItemName);
	return 0;
}
//
//int main()
//{
//	getchar();
//	return 0;
//}