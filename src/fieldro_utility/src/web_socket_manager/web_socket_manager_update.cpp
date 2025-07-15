#include "web_socket_manager.h"

void frb::WebSocketManager::update_hw_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetHardwareStatus);
  std::string status = _response_manager->get_hw_status();
  if(!status.empty())
  {
    publish_hw_status(status);
  }
}

void frb::WebSocketManager::update_engine_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetEngineStatus);
  std::string status = _response_manager->get_engine_status();
  if(!status.empty())
  {
    publish_engine_status(status);
  }
}

void frb::WebSocketManager::update_alarm_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetAlarmList);
  std::string status = _response_manager->get_alarm_status();
  if(!status.empty())
  {
    publish_alarm_status(status);
  }
}