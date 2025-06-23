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
  std::string status = _tct_ws->get_hw_status();
  if(!status.empty())
  {
    publish_hw_status(status);
  }
}

void frb::WebSocketManager::start_path_navigation(const std::string& node)
{
  nlohmann::json data = {
    {"driving_method", "OAP"},           // 주행 방식
    {"driving_option", ""},              // 자율 주행 경로 계획 방식
    {"goal_node_name", node},            // 목표 Node
    {"is_goal_pose_a", 0}                // 정차 후 방향 설정 여부
  };

  _tct_ws->send_message(TctFuncCode::StartPathNav, data);
}