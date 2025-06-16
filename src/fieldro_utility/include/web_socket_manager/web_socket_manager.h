#pragma once

#include "tct_web_socket.h"
#include "tct_web_socket_define.h"
#include "ros_helper.h"
#include "fieldro_utility/hw_status.h"

namespace frb
{

class WebSocketManager
{
public:
  WebSocketManager(const std::string& congif_path, frb::Logger* logger);
  ~WebSocketManager();

  void control(const std::string& str);

private:
  ros::Publisher                 _publish_hw_status;
  ThreadActionInfo*              _thread_info;
  frb::TctWebSocket*             _tct_ws;
  std::map<std::string, int32_t> _command_map;
  std::string                    _config_path;

  void set_publisher() override;
  void publish_hw_status(const std::string& status_json);
  void update();
  void change_mode(const frb::TctFuncCodeType& type);
  void update_hw_status();
};
}