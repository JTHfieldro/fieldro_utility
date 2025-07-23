#include "web_socket_response_manager.h"

frb::WebSocketResponseManager::WebSocketResponseManager(Logger* logger) : RosHelper(logger), _logger(logger)
{
  initialize();
}

frb::WebSocketResponseManager::~WebSocketResponseManager() 
{
  _publish_hw_status.shutdown();
  _publish_engine_status.shutdown();
  _publish_alarm_status.shutdown();
}

void frb::WebSocketResponseManager::initialize() 
{
  // Initialize ROS Node
  initialize_ros_node("web_socket_response_manager");
  set_subscriber();
  set_publisher();
  
}

void frb::WebSocketResponseManager::set_subscriber() 
{
  // No subscribers needed for this manager yet
}

void frb::WebSocketResponseManager::set_publisher() 
{
  _publish_hw_status     = _node_handle->advertise<fieldro_utility::hw_status>("hw_status", 10);
  _publish_engine_status = _node_handle->advertise<fieldro_utility::engine_status>("engine_status", 10);
  _publish_alarm_status  = _node_handle->advertise<fieldro_utility::alarm_status>("alarm_status", 10);
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