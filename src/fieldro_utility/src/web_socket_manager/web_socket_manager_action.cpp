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
      _tct_ws->send_message_no_data(frb::TctFuncCode::SwitchToTeaching);
      _mode = "teaching";
      break;
    }
    case frb::TctFuncCodeType::JogMode:
    {
      _tct_ws->send_message_no_data(frb::TctFuncCode::SwitchToJog);
      _mode = "jog";
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

void frb::WebSocketManager::update_engine_status()
{
  _tct_ws->send_message_no_data(frb::TctFuncCode::GetEngineStatus);
  std::string status = _tct_ws->get_engine_status();
  if(!status.empty())
  {
    publish_engine_status(status);
  }
}

void frb::WebSocketManager::start_path_navigation(const NodeList& node)
{
  if(_mode != "teaching") change_mode(frb::TctFuncCodeType::TeachingMode);
  
  nlohmann::json data = {
    {"driving_method", "OAP"},                 // 주행 방식
    {"driving_option", ""},                    // 자율 주행 경로 계획 방식
    {"goal_node_name", node_to_string(node)},  // 목표 Node
    {"is_goal_pose_a", 0}                      // 정차 후 방향 설정 여부
  };

  _tct_ws->send_message(TctFuncCode::StartPathNav, data);
}

void frb::WebSocketManager::control_jog()
{
  termios oldt;
  termios newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  _logger->push_log_format("INFO", "PROC", "press 'w', 'a', 's', 'd' to control jog");

  bool loop = true;
  while(loop)
  {
    if(frb::check_std_in(100))
    {
      char ch;
      if(read(STDIN_FILENO, &ch, 1) > 0)
      {
        nlohmann::json data;
        if(ch == 'w')
        {
          data = {
            {"input_type", "button"},
            {"motion_type", "forward"},
            {"speed_level", "low"}
          };
        }
        else if(ch == 'a')
        {
          data = {
            {"input_type", "button"},
            {"motion_type", "ccw"},
            {"speed_level", "low"}
          };
        }
        else if(ch == 'd')
        {
          data = {
            {"input_type", "button"},
            {"motion_type", "cw"},
            {"speed_level", "low"}
          };
        }
        else if(ch == 'x')
        {
          data = {
            {"input_type", "button"},
            {"motion_type", "backward"},
            {"speed_level", "low"}
          };
        }
        else if(ch == 'o')
        {
          loop = false;
        }
        _tct_ws->send_message(frb::TctFuncCode::ControlJog, data);
      }
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}