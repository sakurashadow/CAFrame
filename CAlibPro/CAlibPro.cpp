// CAlibPro.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../include/json/json.hpp"
#include <vector>
#include <map>
using namespace std;
using json = nlohmann::json;

namespace ns 
{
    struct msg
    {
        string name;
        vector<string> keys;
        vector<string> values;
        int size;
    };

    void to_json(json& j, const ns::msg& p) {
        j = json{ {"name", p.name}, {"keys", p.keys}, {"values",p.values},{"size",p.size} };
    }

    void from_json(const json& j, ns::msg& p) {
        j.at("name").get_to(p.name);
        j.at("keys").get_to(p.keys);
        j.at("values").get_to(p.values);
        j.at("size").get_to(p.size);
    }
} 

#include <crtdbg.h>

int main()
{
    _CrtDumpMemoryLeaks();
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    char* p = (char*)malloc(sizeof(char) * 10);
    getchar();
    return 0;

  /*  json j2 = {
  {"pi", 3.141},
  {"happy", true},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", 42}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", 42.99}
  }}
    };
    std::string str = j2.dump();


    json j3 = json::parse( str) ;
    auto d = j3["name"].get<std::string>();
    auto p = j3["pi"].get<int>();
    auto e = j3["list"];
    std::cout << e[0] << e[1] << e[2] << endl;
    auto f = j3["object"];
    std::cout << f["currency"] << f["value"] << endl;*/

    ns::msg m;
    m.name = "cmj";
    m.keys.push_back("001"); m.keys.push_back("002");
    m.values.push_back("00A"); m.values.push_back("00B");
    m.size = 2;

    json j = m;
    //m.to_json(j);
    cout << j["keys"][1] << endl;
    cout << j["values"][1]<<endl;

    ns::msg k = j;
   // k.from_json(j);

   //auto ret =  j.get<msg>();

    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
