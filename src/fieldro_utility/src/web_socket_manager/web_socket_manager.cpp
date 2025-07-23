#include "web_socket_manager.h"

frb::WebSocketManager::WebSocketManager(const std::string& config_path, frb::Logger* logger)
  : _logger(logger), _config_path(config_path)
{
  _tct_ws = new frb::TctWebSocket(config_path, logger);
  _thread_info = new ThreadActionInfo(_config_path);
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&WebSocketManager::update, this));
  change_mode(frb::TctFuncCodeType::StopMode);
}

frb::WebSocketManager::~WebSocketManager()
{
  change_mode(frb::TctFuncCodeType::StopMode);
  safe_delete(_tct_ws);
  safe_delete(_thread_info);
}

void frb::WebSocketManager::update()
{
  while(_thread_info->_active)
  {
    update_hw_status();
    update_engine_status();
    update_alarm_status();
    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void frb::WebSocketManager::control(const std::string& str)
{
  std::string cmd = parsing_command_map(str, _command_map);

  if(cmd == "manual_mode") change_mode(frb::TctFuncCodeType::ManualMode);
  else if(cmd == "auto_mode") change_mode(frb::TctFuncCodeType::AutoMode);
  else if(cmd == "stop_mode") change_mode(frb::TctFuncCodeType::StopMode);
  else if(cmd == "teaching_mode") change_mode(frb::TctFuncCodeType::TeachingMode);
  else if(cmd == "jog_mode") change_mode(frb::TctFuncCodeType::JogMode);
  else if(cmd == "path_nav") start_path_navigation(static_cast<NodeList>(_command_map.find("node")->second));
  else if(cmd == "pause_path_nav") pause_path_navigation();
  else if(cmd == "resume_path_nav") resume_path_navigation();
  else if(cmd == "cancel_path_nav") cancel_path_navigation();
  else if(cmd == "script_nav") start_script_navigation(static_cast<ScriptList>(_command_map.find("script")->second));
  else if(cmd == "stop_script_nav") stop_script_navigation();
  else if(cmd == "start_docking") start_docking();
  else
  {
    _logger->push_log_format("ERROR", "PROC", "Unknown command: ", cmd.c_str());
  }
}