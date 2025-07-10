#include "web_socket_manager.h"

void frb::WebSocketManager::publish_hw_status(const std::string& status_json)
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
    // get_hw_status() 에서 전달되는 문자열은 data 객체만 포함한다
    const auto data = nlohmann::json::parse(status_json);

    msg.robot_hw_switch_ems_status =
        data.value("robot_hw_switch_ems_status", msg.robot_hw_switch_ems_status);
    msg.robot_hw_switch_key_status =
        data.value("robot_hw_switch_key_status", msg.robot_hw_switch_key_status);
    msg.robot_hw_switch_reset_status =
        data.value("robot_hw_switch_reset_status", msg.robot_hw_switch_reset_status);
    msg.robot_hw_switch_start_stop_status =
        data.value("robot_hw_switch_start_stop_status", msg.robot_hw_switch_start_stop_status);
    msg.robot_is_charging_status =
        data.value("robot_is_charging_status", msg.robot_is_charging_status);
    msg.robot_is_sensor_stable_depth_front =
        data.value("robot_is_sensor_stable_depth_front", msg.robot_is_sensor_stable_depth_front);
    msg.robot_is_sensor_stable_depth_rear =
        data.value("robot_is_sensor_stable_depth_rear", msg.robot_is_sensor_stable_depth_rear);
    msg.robot_is_sensor_stable_imu =
        data.value("robot_is_sensor_stable_imu", msg.robot_is_sensor_stable_imu);
    msg.robot_is_sensor_stable_lidar_3d =
        data.value("robot_is_sensor_stable_lidar_3d", msg.robot_is_sensor_stable_lidar_3d);
    msg.robot_is_sensor_stable_lidar_front =
        data.value("robot_is_sensor_stable_lidar_front", msg.robot_is_sensor_stable_lidar_front);
    msg.robot_is_sensor_stable_lidar_rear =
        data.value("robot_is_sensor_stable_lidar_rear", msg.robot_is_sensor_stable_lidar_rear);
    msg.robot_is_sensor_stable_motor =
        data.value("robot_is_sensor_stable_motor", msg.robot_is_sensor_stable_motor);
    msg.robot_is_sensor_stable_tof =
        data.value("robot_is_sensor_stable_tof", msg.robot_is_sensor_stable_tof);
  }
  catch(const std::exception&)
  {
    // JSON 파싱 오류 시 기본값 사용
  }

  _publish_hw_status.publish(msg);
}

void frb::WebSocketManager::publish_engine_status(const std::string& status_json)
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
    // get_engine_status() 에서 전달되는 문자열은 data 객체만 포함한다
    const auto data = nlohmann::json::parse(status_json);

    msg.autonomous_time =
        data.value("autonomous_time", msg.autonomous_time);
    msg.autonomous_receiver_status =
        data.value("autonomous_receiver_status", msg.autonomous_receiver_status);
    msg.autonomous_current_main =
        data.value("autonomous_current_main", msg.autonomous_current_main);
    msg.autonomous_current_main_state =
        data.value("autonomous_current_main_state", msg.autonomous_current_main_state);
    msg.autonomous_current_util =
        data.value("autonomous_current_util", msg.autonomous_current_util);
    msg.autonomous_current_util_state =
        data.value("autonomous_current_util_state", msg.autonomous_current_util_state);
    msg.autonomous_current_event =
        data.value("autonomous_current_event", msg.autonomous_current_event);
    msg.autonomous_current_event_time =
        data.value("autonomous_current_event_time", msg.autonomous_current_event_time);
  }
  catch(const std::exception&)
  {
    // JSON 파싱 오류 시 기본값 사용
  }

  _publish_engine_status.publish(msg);
}