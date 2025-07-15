#pragma once

#include "tct_web_socket_define.h"
#include <nlohmann/json.hpp>

namespace frb {

class WebSocketResponseManager
{
public:
    WebSocketResponseManager();
    ~WebSocketResponseManager();

    void process_message(frb::TctFuncCode function_code, const nlohmann::json& data);
    const std::string& get_hw_status() const { return _hw_status; }
    const std::string& get_engine_status() const { return _engine_status; }
    const std::string& get_alarm_status() const { return _alarm_status; }

private:
    std::string _hw_status;
    std::string _engine_status;
    std::string _alarm_status;
};
}