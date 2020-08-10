#pragma once
#include "util/stdafx.h"
typedef size_t (*writeCb)(void* data, size_t size, size_t nmemb, string& content);
void Initcurl();
void send(string auth, string data, writeCb cb);