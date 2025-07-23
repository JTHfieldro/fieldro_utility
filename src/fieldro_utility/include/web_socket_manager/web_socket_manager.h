#pragma once

#include "tct_web_socket.h"
#include "tct_web_socket_define.h"
#include "web_socket_response_manager.h"
#include "node_define.h"

namespace frb
{

class WebSocketManager
{
public:
  WebSocketManager(const std::string& congif_path, frb::Logger* logger);
  ~WebSocketManager();

  /**
   * @brief		  User Command를 받아서 처리하는 함수
   * @param[in]	str : User Command
   */
  void control(const std::string& str);

private:
  Logger*                        _logger;
  ThreadActionInfo*              _thread_info;
  frb::TctWebSocket*             _tct_ws;
  std::map<std::string, int32_t> _command_map;
  std::string                    _config_path;
  std::string                    _mode;

  void update();
  void update_hw_status();
  void update_engine_status();
  void update_alarm_status();

  void change_mode(const frb::TctFuncCodeType& type);
  void start_path_navigation(const NodeList& node);
  void pause_path_navigation();
  void resume_path_navigation();
  void cancel_path_navigation();
  void start_script_navigation(const ScriptList& script);
  void stop_script_navigation();
  void start_docking();
};
}