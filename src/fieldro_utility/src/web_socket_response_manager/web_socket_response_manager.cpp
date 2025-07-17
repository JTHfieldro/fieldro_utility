#include "web_socket_response_manager.h"

frb::WebSocketResponseManager::WebSocketResponseManager() 
{
  initialize();
}

frb::WebSocketResponseManager::~WebSocketResponseManager() 
{
  initialize_ros_node("web_socket_response_manager");
  _publish_hw_status.shutdown();
  _publish_engine_status.shutdown();
  _publish_alarm_status.shutdown();
}

void frb::WebSocketResponseManager::initialize() 
{
  _publish_hw_status     = _nh.advertise<fieldro_utility::hw_status>("hw_status", 10);
  _publish_engine_status = _nh.advertise<fieldro_utility::engine_status>("engine_status", 10);
  _publish_alarm_status  = _nh.advertise<fieldro_utility::alarm_status>("alarm_status", 10);
}

void frb::WebSocketResponseManager::process_message(frb::TctFuncCode function_code, const nlohmann::json& data) 
{
    if(function_code == frb::TctFuncCode::GetHardwareStatus) 
    {
      publish_hw_status(data);
    }
    else if(function_code == frb::TctFuncCode::GetEngineStatus) 
    {
      publish_engine_status(data);
    }
    else if(function_code == frb::TctFuncCode::GetAlarmList) 
    {
      publish_alarm_status(data);
    }
    else
    {
      // Handle other function codes as needed
    }
}