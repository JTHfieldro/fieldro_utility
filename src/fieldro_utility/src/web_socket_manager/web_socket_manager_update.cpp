#include "web_socket_manager.h"

void frb::WebSocketManager::update_hw_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetHardwareStatus);
}

void frb::WebSocketManager::update_engine_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetEngineStatus);
}

void frb::WebSocketManager::update_alarm_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetAlarmList);
}