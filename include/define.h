#ifndef CMJLIB_DEFINE
#define CMJLIB_DEFINE

#include <windows.h>
#include "log\log.h"
enum _StatusCode
{
	SUCCEED = 0,
	ERROR_UNKNOW = 1,//未知错误
	ERROR_IMPORT_DLL_FAILURE = 10001, //载入dll失败
	ERROR_CANNOT_FIND_SERVER = 10002, //找不到服务名
	ERROR_CANNOT_FIND_ENTRANCE = 10003, //找dll不到入口
	ERROR_SERVER_NAME_TOOLONG = 10004,//超出服务名字长度MAX_SERVER_NAME限制
	ERROR_NOT_ALLOC = 10005, //指针未分配空间
	ERROR_OVER_SERVER_MAXNUM = 10006, //加载服务超出MAX_SERVER_NUM上限
	ERROR_SERVER_ITEMNAME_TOOLONG = 10007, //超出服务子项名字长度MAX_SERVER_NAME限制
};

#define _in
#define _out
#define _inout


#define MAX_SERVER_NAME 20
#define MAX_SERVER_ITEM_NAME 20
#define MAX_SERVER_NUM 10

#define MAX_BUFF_SIZE 4*1024*1024

#define TEST_FUN "all_server_item"

/*------------------------------------------------------定义甲方回调，丙方入口----------------------------------------------------------------------------*/
typedef int(*t_cmdExec)(_out void* pRet, _in const char* pServerName, _in const char* pServerItemName,
	void* param);
//甲方异步回调 
typedef void(*_CmdCallbackFunPtr)(int len, void* pOutput);

//定义丙方异步入口指针
typedef int (*t_cmdExecAsync)(_CmdCallbackFunPtr callback,
	const char* pServerName, const char* pServerItemName,
	void* param,int nLenParam);

//初始化丙方并传入乙方的shell指针
typedef int(*_CmdInitFunc)(t_cmdExec cmdFunc, t_cmdExecAsync cmdFuncAsyn, bool is_print_log);//定义函数指针  

/*------------------------------------------------------定义丙方节点信息----------------------------------------------------------------------------------*/

typedef int(*_CmdFunPtr)(const char* pServerItemName, void* pParam, void* pOutput);//定义函数指针,版本1。NOTICE:该入口弃用
typedef int (*ResultCallback)(void* pThis, void* pRetData, int nLen); //retuan = status
typedef int(*_CmdFunPtrWithCallback)(                         //定义函数指针,版本2
	ResultCallback res_cb,
	void* pThis, 
	const char* pServerItemName,
	void* pParam);
/**
存储丙方节点信息
*/
typedef struct _serverNode
{
	int status; //服务状态，加载=0，加载但停用=1，未加载=-1；
	char strServName[MAX_SERVER_NAME];
	HINSTANCE hInstance;    //服务实例标识
	typedef struct _server_node_entrance //提供回调结果的方式，不涉及到同步异步的描述。
	{
		_CmdFunPtr cmdEntrance;  //服务命令入口,线程内部使用。通过已分配内存大小的指针传递给node节点操作
		_CmdFunPtrWithCallback cmdEntrance_with_cb; //通过回调来自动分配合适的空间
	}server_node_entrance;
	server_node_entrance node_entrance;
	int nodeid; //节点id，用的是gServerNodeList下标
}tServerNode;
#endif