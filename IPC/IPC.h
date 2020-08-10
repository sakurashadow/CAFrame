#pragma once
#include "../include/interface.h"

int _client_shutdown();

int _client_send(const char* msg);

int init_serv_client(const char* serv_name, const char* remote_name, _CmdCallbackFunPtr callback);
