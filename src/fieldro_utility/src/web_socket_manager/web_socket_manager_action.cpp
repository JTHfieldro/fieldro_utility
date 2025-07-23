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
      _mode = "manual";
      break;
    }
    case frb::TctFuncCodeType::AutoMode:
    {
      data["key_state"] = "auto";
      _tct_ws->send_message(frb::TctFuncCode::SetOperationMode, data);
      _mode = "auto";
      break;
    }
    case frb::TctFuncCodeType::StopMode:
    {
      data["key_state"] = "stop";
      _tct_ws->send_message(frb::TctFuncCode::SetOperationMode, data);
      _mode = "stop";
      break;
    }
    case frb::TctFuncCodeType::TeachingMode:
    {
      if(_mode != "manual") 
      {
        _logger->push_log_format("ERROR", "PROC", "Teaching mode can only be in manual mode.");
        return;
      }
      _tct_ws->send_message_no_data(frb::TctFuncCode::SwitchToTeaching);
      _mode = "teaching";
      break;
    }
    case frb::TctFuncCodeType::JogMode:
    {
      if(_mode != "manual") 
      {
        _logger->push_log_format("ERROR", "PROC", "Jog mode can only be in manual mode.");
        return;
      }
      _tct_ws->send_message_no_data(frb::TctFuncCode::SwitchToJog);
      _mode = "jog";
      break;
    }
  }
}

void frb::WebSocketManager::start_path_navigation(const NodeList& node)
{
  if(_mode != "teaching") 
  {
    _logger->push_log_format("ERROR", "PROC", "Path navigation can only be started in teaching mode.");
    return;
  }

  nlohmann::json data = {
    {"driving_method", "OAP"},                 // 주행 방식
    {"driving_option", ""},                    // 자율 주행 경로 계획 방식
    {"goal_node_name", node_to_string(node)},  // 목표 Node
    {"is_goal_pose_a", 0}                      // 정차 후 방향 설정 여부
  };

  _tct_ws->send_message(TctFuncCode::StartPathNav, data);
}

void frb::WebSocketManager::pause_path_navigation()
{
  _tct_ws->send_message_no_data(TctFuncCode::PauseNavigation);
}

void frb::WebSocketManager::resume_path_navigation()
{
  _tct_ws->send_message_no_data(TctFuncCode::ResumeNavigation);
}

void frb::WebSocketManager::cancel_path_navigation()
{
  _tct_ws->send_message_no_data(TctFuncCode::CancelNavigation);
}

void frb::WebSocketManager::start_script_navigation(const ScriptList& script)
{
  if(_mode != "auto")
  {
    _logger->push_log_format("ERROR", "PROC", "Script navigation can only be started in auto mode.");
    return;
  }

  nlohmann::json data = {
    {"script_name", script_to_string(script)}
  };

  _tct_ws->send_message(TctFuncCode::StartScript, data);
}

void frb::WebSocketManager::stop_script_navigation()
{ 
  _tct_ws->send_message_no_data(TctFuncCode::StopScript);
}

void frb::WebSocketManager::start_docking()
{
  if(_mode != "teaching") 
  {
    _logger->push_log_format("ERROR", "PROC", "Path navigation can only be started in teaching mode.");
    return;
  }
  
  nlohmann::json data = {
    {"marker_id", 10050},
    {"driving_option", "AUTO_STATIC"}
  };

  _tct_ws->send_message(TctFuncCode::StartDocking, data);
}