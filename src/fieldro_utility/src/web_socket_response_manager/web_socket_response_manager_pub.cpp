#include "web_socket_response_manager.h"

void frb::WebSocketResponseManager::publish_hw_status(const nlohmann::json& status_json) 
{
  fieldro_utility::hw_status msg;

  // 기본 값 설정
  msg.robot_hw_switch_ems_status                   = "UNKNOWN";
  msg.robot_hw_switch_key_status                   = "UNKNOWN";
  msg.robot_hw_switch_reset_status                 = "UNKNOWN";
  msg.robot_hw_switch_start_stop_status            = "UNKNOWN";
  msg.robot_is_charging_status                     = "UNKNOWN";
  msg.robot_is_sensor_stable_depth_front           = "UNKNOWN";
  msg.robot_is_sensor_stable_depth_rear            = "UNKNOWN";
  msg.robot_is_sensor_stable_imu                   = "UNKNOWN";
  msg.robot_is_sensor_stable_lidar_3d              = "UNKNOWN";
  msg.robot_is_sensor_stable_lidar_front           = "UNKNOWN";
  msg.robot_is_sensor_stable_lidar_rear            = "UNKNOWN";
  msg.robot_is_sensor_stable_motor                 = "UNKNOWN";
  msg.robot_is_sensor_stable_tof                   = "UNKNOWN";

  try
  {
    msg.robot_hw_switch_ems_status =
        status_json.value("robot_hw_switch_ems_status", msg.robot_hw_switch_ems_status);
    msg.robot_hw_switch_key_status =
        status_json.value("robot_hw_switch_key_status", msg.robot_hw_switch_key_status);
    msg.robot_hw_switch_reset_status =
        status_json.value("robot_hw_switch_reset_status", msg.robot_hw_switch_reset_status);
    msg.robot_hw_switch_start_stop_status =
        status_json.value("robot_hw_switch_start_stop_status", msg.robot_hw_switch_start_stop_status);
    msg.robot_is_charging_status =
        status_json.value("robot_is_charging_status", msg.robot_is_charging_status);
    msg.robot_is_sensor_stable_depth_front =
        status_json.value("robot_is_sensor_stable_depth_front", msg.robot_is_sensor_stable_depth_front);
    msg.robot_is_sensor_stable_depth_rear =
        status_json.value("robot_is_sensor_stable_depth_rear", msg.robot_is_sensor_stable_depth_rear);
    msg.robot_is_sensor_stable_imu =
        status_json.value("robot_is_sensor_stable_imu", msg.robot_is_sensor_stable_imu);
    msg.robot_is_sensor_stable_lidar_3d =
        status_json.value("robot_is_sensor_stable_lidar_3d", msg.robot_is_sensor_stable_lidar_3d);
    msg.robot_is_sensor_stable_lidar_front =
        status_json.value("robot_is_sensor_stable_lidar_front", msg.robot_is_sensor_stable_lidar_front);
    msg.robot_is_sensor_stable_lidar_rear =
        status_json.value("robot_is_sensor_stable_lidar_rear", msg.robot_is_sensor_stable_lidar_rear);
    msg.robot_is_sensor_stable_motor =
        status_json.value("robot_is_sensor_stable_motor", msg.robot_is_sensor_stable_motor);
    msg.robot_is_sensor_stable_tof =
        status_json.value("robot_is_sensor_stable_tof", msg.robot_is_sensor_stable_tof);
  }
  catch(const std::exception&)
  {
    _logger->push_log_format("ERROR", "JSON", "Failed to parse hardware status JSON", "WebSocketResponseManager");
  }

  _publish_hw_status.publish(msg);
}

void frb::WebSocketResponseManager::publish_engine_status(const nlohmann::json& status_json)
{
  fieldro_utility::engine_status msg;

  // 기본 값 설정
  msg.autonomous_time                              = "UNKNOWN";
  msg.autonomous_receiver_status                   = "UNKNOWN";
  msg.autonomous_current_main                      = "UNKNOWN";
  msg.autonomous_current_main_state                = "UNKNOWN";
  msg.autonomous_current_util                      = "UNKNOWN";
  msg.autonomous_current_util_state                = "UNKNOWN";
  msg.autonomous_current_event                     = "UNKNOWN";
  msg.autonomous_current_event_time                = "UNKNOWN";

  try
  {
    msg.autonomous_time =
        status_json.value("autonomous_time", msg.autonomous_time);
    msg.autonomous_receiver_status =
        status_json.value("autonomous_receiver_status", msg.autonomous_receiver_status);
    msg.autonomous_current_main =
        status_json.value("autonomous_current_main", msg.autonomous_current_main);
    msg.autonomous_current_main_state =
        status_json.value("autonomous_current_main_state", msg.autonomous_current_main_state);
    msg.autonomous_current_util =
        status_json.value("autonomous_current_util", msg.autonomous_current_util);
    msg.autonomous_current_util_state =
        status_json.value("autonomous_current_util_state", msg.autonomous_current_util_state);
    msg.autonomous_current_event =
        status_json.value("autonomous_current_event", msg.autonomous_current_event);
    msg.autonomous_current_event_time =
        status_json.value("autonomous_current_event_time", msg.autonomous_current_event_time);
  }
  catch(const std::exception&)
  {
    _logger->push_log_format("ERROR", "JSON", "Failed to parse engine status JSON", "WebSocketResponseManager");
  }

  _publish_engine_status.publish(msg);
}

void frb::WebSocketResponseManager::publish_alarm_status(const nlohmann::json& status_json)
{
  fieldro_utility::alarm_status msg;

  // 기본 값 설정
  msg.info = "NONE";

  try
  {
    msg.info = status_json.value("alarm_list", msg.info);
  }
  catch(const std::exception&)
  {
    _logger->push_log_format("ERROR", "JSON", "Failed to parse alarm status JSON", "WebSocketResponseManager");
  }

  _publish_alarm_status.publish(msg);
}