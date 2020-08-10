// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include "rapidjson/document.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/encodedstream.h"
#include "util/TransCoding.h"
#include "util/Base64.h"
using namespace std;
using namespace rapidjson;


// 走查测试环境请务必用DEBUG下的KEY和SECRET_KEY，防止污染线上数据
//#ifdef DEBUG
//#define ZHUGE_APP_KEY string("b3b666a0da5e4d4492da5dea8a11cffa")
//#define ZHUGE_SECRET_KEY string("1e1e120993904f6dabfd9d93a40ba0b2")
//#else
//#define ZHUGE_APP_KEY string("2cfb9bb9141f43d8805ace08bbbec326")
//#define ZHUGE_SECRET_KEY string("0561b1ac25ff44c1af999152887c97a9")
//#endif
#define ZHUGE_ADDRESS string("http://127.0.0.1:9999/test") //string("https://zgd.ekwing.com/open/v2/event_statis_srv/upload_event")