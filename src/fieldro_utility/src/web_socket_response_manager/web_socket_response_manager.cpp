#include "web_socket_response_manager.h"

frb::WebSocketResponseManager::WebSocketResponseManager() 
{
  _hw_status     = "";
  _engine_status = "";
  _alarm_status  = "";
}

frb::WebSocketResponseManager::~WebSocketResponseManager() 
{
  _hw_status.clear();
  _engine_status.clear();
  _alarm_status.clear();
}

void frb::WebSocketResponseManager::process_message(frb::TctFuncCode function_code, const nlohmann::json& data) 
{
    if(function_code == frb::TctFuncCode::GetHardwareStatus) 
    {
      _hw_status = data.dump();
    }
    else if(function_code == frb::TctFuncCode::GetEngineStatus) 
    {
      _engine_status = data.dump();
    }
    else if(function_code == frb::TctFuncCode::GetAlarmList) 
    {
      _alarm_status = data.dump();
    }
    else 
    {
        // Handle other function codes as needed
    }
}