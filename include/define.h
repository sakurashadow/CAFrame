#ifndef CMJLIB_DEFINE
#define CMJLIB_DEFINE

#include <windows.h>
#include "log\log.h"
enum _StatusCode
{
	SUCCEED = 0,
	ERROR_UNKNOW = 1,//δ֪����
	ERROR_IMPORT_DLL_FAILURE = 10001, //����dllʧ��
	ERROR_CANNOT_FIND_SERVER = 10002, //�Ҳ���������
	ERROR_CANNOT_FIND_ENTRANCE = 10003, //��dll�������
	ERROR_SERVER_NAME_TOOLONG = 10004,//�����������ֳ���MAX_SERVER_NAME����
	ERROR_NOT_ALLOC = 10005, //ָ��δ����ռ�
	ERROR_OVER_SERVER_MAXNUM = 10006, //���ط��񳬳�MAX_SERVER_NUM����
	ERROR_SERVER_ITEMNAME_TOOLONG = 10007, //���������������ֳ���MAX_SERVER_NAME����
};

#define _in
#define _out
#define _inout


#define MAX_SERVER_NAME 20
#define MAX_SERVER_ITEM_NAME 20
#define MAX_SERVER_NUM 10

#define MAX_BUFF_SIZE 4*1024*1024

#define TEST_FUN "all_server_item"

/*------------------------------------------------------����׷��ص����������----------------------------------------------------------------------------*/
typedef int(*t_cmdExec)(_out void* pRet, _in const char* pServerName, _in const char* pServerItemName,
	void* param);
//�׷��첽�ص� 
typedef void(*_CmdCallbackFunPtr)(int len, void* pOutput);

//��������첽���ָ��
typedef int (*t_cmdExecAsync)(_CmdCallbackFunPtr callback,
	const char* pServerName, const char* pServerItemName,
	void* param,int nLenParam);

//��ʼ�������������ҷ���shellָ��
typedef int(*_CmdInitFunc)(t_cmdExec cmdFunc, t_cmdExecAsync cmdFuncAsyn, bool is_print_log);//���庯��ָ��  

/*------------------------------------------------------��������ڵ���Ϣ----------------------------------------------------------------------------------*/

typedef int(*_CmdFunPtr)(const char* pServerItemName, void* pParam, void* pOutput);//���庯��ָ��,�汾1��NOTICE:���������
typedef int (*ResultCallback)(void* pThis, void* pRetData, int nLen); //retuan = status
typedef int(*_CmdFunPtrWithCallback)(                         //���庯��ָ��,�汾2
	ResultCallback res_cb,
	void* pThis, 
	const char* pServerItemName,
	void* pParam);
/**
�洢�����ڵ���Ϣ
*/
typedef struct _serverNode
{
	int status; //����״̬������=0�����ص�ͣ��=1��δ����=-1��
	char strServName[MAX_SERVER_NAME];
	HINSTANCE hInstance;    //����ʵ����ʶ
	typedef struct _server_node_entrance //�ṩ�ص�����ķ�ʽ�����漰��ͬ���첽��������
	{
		_CmdFunPtr cmdEntrance;  //�����������,�߳��ڲ�ʹ�á�ͨ���ѷ����ڴ��С��ָ�봫�ݸ�node�ڵ����
		_CmdFunPtrWithCallback cmdEntrance_with_cb; //ͨ���ص����Զ�������ʵĿռ�
	}server_node_entrance;
	server_node_entrance node_entrance;
	int nodeid; //�ڵ�id���õ���gServerNodeList�±�
}tServerNode;
#endif