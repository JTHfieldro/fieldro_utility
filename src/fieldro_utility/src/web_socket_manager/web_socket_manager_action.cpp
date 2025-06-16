#include "web_socket_manager.h"

void frb::WebSocketManager::change_mode(const frb::TctFuncCodeType& type)
{
  nlohmann::json data;
  switch(type)
  {
    case frb::TctFuncCodeType::ManualMode:
    {
      data["key_state"] = "manual";
      _tct_ws->send_message(frb::TctFuncCode::SetOperationMode, data);
      break;
    }
    case frb::TctFuncCodeType::AutoMode:
    {
      data["key_state"] = "auto";
      _tct_ws->send_message(frb::TctFuncCode::SetOperationMode, data);
      break;
    }
    case frb::TctFuncCodeType::StopMode:
    {
      data["key_state"] = "stop";
      _tct_ws->send_message(frb::TctFuncCode::SetOperationMode, data);
      break;
    }
  }
}

void frb::WebSocketManager::update_hw_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetHardwareStatus);
  std::string status = _tct_ws->get_hardware_status();
  if(!status.empty())
  {
    publish_hw_status(status);
  }
}