#pragma once

#include <nlohmann/json.hpp>
#include "tct_web_socket.h"
#include "tct_web_socket_define.h"
#include "web_socket_response_manager.h"
#include "node_define.h"
#include "ros_helper.h"
#include "fieldro_utility/hw_status.h"
#include "fieldro_utility/engine_status.h"

namespace frb
{

class WebSocketManager : public RosHelper
{
public:
  WebSocketManager(const std::string& congif_path, frb::Logger* logger);
  ~WebSocketManager();

  void control(const std::string& str);

private:
  Logger*                        _logger;
  WebSocketResponseManager* _response_manager;
  ros::Publisher                 _publish_hw_status;
  ros::Publisher                 _publish_engine_status;
  ThreadActionInfo*              _thread_info;
  frb::TctWebSocket*             _tct_ws;
  std::map<std::string, int32_t> _command_map;
  std::string                    _config_path;
  std::string                    _mode;

  void set_subscriber() override;
  void set_publisher() override;
  void publish_hw_status(const std::string& status_json);
  void publish_engine_status(const std::string& status_json);
  void update();
  void update_hw_status();
  void update_engine_status();

  void change_mode(const frb::TctFuncCodeType& type);
  void start_path_navigation(const NodeList& node);
  void start_script_navigation(const std::string& script_name);
  void stop_script_navigation();
  
};
}