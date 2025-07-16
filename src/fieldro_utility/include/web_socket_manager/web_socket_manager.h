#pragma once

#include <nlohmann/json.hpp>
#include "tct_web_socket.h"
#include "tct_web_socket_define.h"
#include "web_socket_response_manager.h"
#include "node_define.h"
#include "ros_helper.h"
#include "fieldro_utility/hw_status.h"
#include "fieldro_utility/engine_status.h"
#include "fieldro_utility/alarm_status.h"

namespace frb
{

class WebSocketManager : public RosHelper
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
  WebSocketResponseManager*      _response_manager;
  ThreadActionInfo*              _thread_info;
  frb::TctWebSocket*             _tct_ws;
  std::map<std::string, int32_t> _command_map;
  std::string                    _config_path;
  std::string                    _mode;

  /**
   * @brief		  ROS fieldro_utility/hw_status Publish 함수
  */
  ros::Publisher                 _publish_hw_status;
  /**
   * @brief		  ROS fieldro_utility/engine_status Publish 함수
  */
  ros::Publisher                 _publish_engine_status;
  /**
   * @brief		  ROS fieldro_utility/alarm_status Publish 함수
  */
  ros::Publisher                 _publish_alarm_status;

  /**
   * @brief		  Ros Subscriber를 설정하는 함수
   */
  void set_subscriber() override;
  /**
   * @brief		  Ros Publisher를 설정하는 함수
   */
  void set_publisher() override;
  /**
   * @brief		  User Command를 처리하는 함수
   * @param[in]	str : User Command
   */
  void publish_hw_status(const std::string& status_json);
  void publish_engine_status(const std::string& status_json);
  void publish_alarm_status(const std::string& status_json);

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