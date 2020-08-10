#include "..\include\define.h"
#pragma warning(disable :4996)
#define API __declspec(dllexport) 

extern "C" int API init(t_cmdExec _cmd, t_cmdExecAsync _cmdAsyn, bool is_print_log);
extern "C" int API cmd(const char* pServerItemName, char* pParam, char* pOutput);//定义函数指针  
extern "C" int API cmd_ret_callback(                         //定义函数指针,版本2
	ResultCallback res_cb,
	void* pThis,
	const char* pServerItemName,
	void* pParam);