#pragma once
#include "../include/json/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace ns
{
    struct set_server_client_name
    {
        string server;
        string client;
        int callback_addr;
    };

    void to_json(json& j, const ns::set_server_client_name& p) {
        j = json{ {"server", p.server}, {"client", p.client} , {"callback_addr", p.callback_addr}  };
    }

    void from_json(const json& j, ns::set_server_client_name& p) {
        j.at("server").get_to(p.server);
        j.at("client").get_to(p.client);
        j.at("callback_addr").get_to(p.callback_addr);
    }
}