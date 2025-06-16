#include "web_socket_manager.h"

frb::WebSocketManager::WebSocketManager(const std::string& config_path, frb::Logger* logger)
  : RosHelper(logger), _config_path(config_path)
{
  _tct_ws = new frb::TctWebSocket(config_path, logger);
  _thread_info = new ThreadActionInfo(_config_path);
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&WebSocketManager::update, this));
  initialize_ros_node("tct_socket_bidge");
}

frb::WebSocketManager::~WebSocketManager()
{
  safe_delete(_tct_ws);
}

void frb::WebSocketManager::update()
{
  while(_thread_info->_active)
  {
    update_hw_status();

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
}