#include "..\include\define.h"
#pragma warning(disable :4996)
#define API __declspec(dllexport) 

extern "C" int API init(t_cmdExec _cmd, t_cmdExecAsync _cmdAsyn, bool is_print_log);
extern "C" int API cmd(const char* pServerItemName, char* pParam, char* pOutput);//���庯��ָ��  
extern "C" int API cmd_ret_callback(                         //���庯��ָ��,�汾2
	ResultCallback res_cb,
	void* pThis,
	const char* pServerItemName,
	void* pParam);