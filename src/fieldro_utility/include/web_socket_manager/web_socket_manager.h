#ifndef WEB_SOCKET_MANAGER_H
#define WEB_SOCKET_MANAGER_H

#include "tct_web_socket.h"
#include "tct_web_socket_define.h"
#include "ros/ros.h"

namespace frb
{

class WebSocketManager
{
public:
  WebSocketManager(const std::string& congif_path, frb::Logger* logger);
  ~WebSocketManager();

  void control(const std::string& str);

private:
  ThreadActionInfo*              _thread_info;
  frb::TctWebSocket*             _tct_ws;
  std::map<std::string, int32_t> _command_map;
  std::string                    _config_path;

  void update();
  void change_mode(const frb::TctFuncCodeType& type);
  void update_hw_status();

  
};
}

#endif