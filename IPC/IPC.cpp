#include <assert.h>
#include <iostream>
#include "nanomsg/reqrep.h"
#include "nanomsg/pubsub.h"
#include "IPC.h"
#define addr "ipc:///tmp/reqrep%s.ipc"
//"tcp://127.0.0.1:5555"
#include <thread>
#include "..\include\log\log.h"
#define printf LOG
using namespace std;
_CmdCallbackFunPtr _callback;
typedef void (*msgProc)(const char* msg, int len);


void server_callback(const char* msg,int len)
{
	if(msg != nullptr)
		_callback(len, (void*)msg);
}

int server(const char* url, const char* server_name, msgProc proc)
{
	std::thread th([&](const char* url, const char* server_name, msgProc proc)
		{
			int sock = nn_socket(AF_SP, NN_SUB);
			assert(sock >= 0);
			assert(nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) >= 0);
			char local_addr[100] = { 0 };
			sprintf(local_addr, url, server_name);
			auto ret = nn_bind(sock, local_addr) >= 0;
			assert(ret);
			printf("进入server线程的处理入口内\n");
			while (true)
			{
				printf("进入server线程的while内\n");
				char* buf = NULL;
				int len = nn_recv(sock, &buf, NN_MSG, 0);
				assert(len >= 0);
				printf("接收字符串长度=%d\n", len);
				/*printf("入口地址=%x\n", proc);*/
				if(proc != nullptr)
					proc(buf, len);
				printf(buf);
				nn_freemsg(buf);
				printf("释放内存完成");
			}
			return nn_shutdown(sock, 0);
		}, url, server_name, proc);
	th.detach();
	return 0;
}

int sock = -1;
int create_client(const char* url, const char* remote_name)
{
	sock = nn_socket(AF_SP, NN_PUB);
	assert(sock >= 0);
	char remote_addr[100] = { 0 };
	sprintf(remote_addr, url, remote_name);
	return nn_connect(sock, remote_addr) >= 0;
}

int _client_shutdown()
{
	int ret = -1;
	if (sock != -1)
	{
		ret = nn_shutdown(sock, 0);
	}
	return ret;
}

int _client_send(const char* msg)
{
	int bytes = -1;
	if (sock != -1)
	{
		bytes = nn_send(sock, msg, strlen(msg), 0);
	}
	return bytes;
}

int init_serv_client(const char* serv_name, const char* remote_name, _CmdCallbackFunPtr callback)
{
	_callback = callback;
	server(addr, serv_name, server_callback);
	return create_client(addr, remote_name);
}