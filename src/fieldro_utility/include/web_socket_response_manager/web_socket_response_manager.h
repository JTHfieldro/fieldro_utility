#pragma once

#include "tct_web_socket_define.h"
#include "ros_helper.h"
#include "fieldro_utility/hw_status.h"
#include "fieldro_utility/engine_status.h"
#include "fieldro_utility/alarm_status.h"
#include <nlohmann/json.hpp>

namespace frb {

class WebSocketResponseManager : public RosHelper
{
public:
    WebSocketResponseManager(Logger* logger);
    ~WebSocketResponseManager();

    void process_message(frb::TctFuncCode function_code, const nlohmann::json& data);

private:
    Logger* _logger;
    ros::Publisher _publish_hw_status;
    ros::Publisher _publish_engine_status;
    ros::Publisher _publish_alarm_status;

    void set_subscriber() override;
    void set_publisher() override;

    void initialize();
    void publish_hw_status(const nlohmann::json& status_json);
    void publish_engine_status(const nlohmann::json& status_json);
    void publish_alarm_status(const nlohmann::json& status_json);
};
}