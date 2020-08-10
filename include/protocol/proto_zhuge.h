#pragma once
#include "../include/json/json.hpp"

using namespace std;
using json = nlohmann::json;
/**
ÉèÖÃ×Ö·û´®ÄÚÈÝ
*/
//typedef struct _param_set_strval
//{
//	header head;
//	char* pVal;
//}param_set_strval;

namespace ns
{
    struct set_strval
    {
        int type;
        string value;
    };

    void to_json(json& j, const ns::set_strval& p) {
        j = json{ {"type", p.type}, {"value", p.value} };
    }

    void from_json(const json& j, ns::set_strval& p) {
        j.at("type").get_to(p.type);
        j.at("value").get_to(p.value);
    }
}

namespace ns
{
    struct set_init
    {
        string appkey;
        string secrectkey;
        string uid;
        string token;
        string vn;
    };

    void to_json(json& j, const ns::set_init& p) {
        j = json{
            {"appkey", p.appkey}, 
            {"secrectkey", p.secrectkey},
            {"uid", p.uid},
            {"token", p.token},
            {"vn", p.vn}
        };
    }

    void from_json(const json& j, ns::set_init& p) {
        j.at("appkey").get_to(p.appkey);
        j.at("secrectkey").get_to(p.secrectkey);
        j.at("uid").get_to(p.uid);
        j.at("token").get_to(p.token);
        j.at("vn").get_to(p.vn);
    }
}

namespace ns
{
    struct events
    {
        string name;
        vector<string> keys;
        vector<string> values;
        int size;
    };

    void to_json(json& j, const ns::events& p) {
        j = json{ {"name", p.name}, {"keys", p.keys}, {"values",p.values},{"size",p.size} };
    }

    void from_json(const json& j, ns::events& p) {
        j.at("name").get_to(p.name);
        j.at("keys").get_to(p.keys);
        j.at("values").get_to(p.values);
        j.at("size").get_to(p.size);
    }
}