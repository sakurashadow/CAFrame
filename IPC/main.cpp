// IPC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../include/interface.h"

#include <stdio.h>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include "..\include\protocol\proto_ipc.h"
#include "IPC.h"
#define printf LOG
using std::map;
using std::string;
typedef int (*funPtr2)(ResultCallback res_cb, void* pThis, void* pParam);
map<string, funPtr2> mapStringFunc2;

typedef int(*funPtr)(char*, char*);
map<string, funPtr> mapStringFunc;

t_cmdExec parentCmd;
t_cmdExecAsync parentCmdAsync;

#define REGISTER_FUN2(x) \
do{						\
	mapStringFunc2[#x] = x; \
} while (0);

#define REGISTER_FUN(x) \
do{						\
	mapStringFunc[#x] = x; \
} while (0);


//同步接口
int client_shutdown(ResultCallback res_cb, void* pThis, void* pParam)
{
	int result = _client_shutdown();
	res_cb(pThis, &result, sizeof(result));
	return 0;
}

//同步接口
int client_init(char* pIn, char* pOut)
{
	json jParam = json::parse((char*)pIn);
	ns::set_server_client_name param = jParam;
	init_serv_client(param.server.c_str(), param.client.c_str(), (_CmdCallbackFunPtr)param.callback_addr);
	return 0;
}

int client_send(ResultCallback res_cb, void* pThis, void* pParam)
{
	int result = _client_send((char*)pParam);
	res_cb(pThis, &result, sizeof(result));
	return 0;
}


//以下必须实现
int all_server_item(ResultCallback res_cb, void* pThis, void* pParam)
{
	string keys = "";
	for (auto& item : mapStringFunc2)
	{
		keys += item.first + ",";
	}
	res_cb(pThis, &keys, keys.size());
	return 0;
}

int init(t_cmdExec _cmd, t_cmdExecAsync _cmdAsyn, bool is_print_log)
{
	InitLog("IPC.log", is_print_log);
	parentCmd = _cmd;
	parentCmdAsync = _cmdAsyn;
	printf("server %s : 加载%s\n", "IPC", __FUNCTION__);
	REGISTER_FUN2(all_server_item);
	REGISTER_FUN(client_init);
	REGISTER_FUN2(client_send);
	REGISTER_FUN2(client_shutdown);
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
	auto ret = mapStringFunc.find(pServerItemName);
	if (ret != mapStringFunc.end())
	{
		printf("server :调用%s函数\n", pServerItemName);
		int len= mapStringFunc[pServerItemName](pParam, pOutput);
		return len;
	}
	return sprintf(pOutput, "调用失败，不存在%s函数\n", pServerItemName);
}