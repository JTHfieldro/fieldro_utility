#include "web_socket_manager.h"

void frb::WebSocketManager::publish_hw_status(const std::string& status_json)
{
  fieldro_utility::hw_status msg;
  msg.robot_is_sensor_stable_lidar_front  = "UNKNOWN";
  msg.robot_is_sensor_stable_lidar_rear   = "UNKNOWN";
  msg.robot_is_sensor_stable_lidar_3d     = "UNKNOWN";
  msg.robot_is_sensor_stable_depth_front  = "UNKNOWN";
  msg.robot_is_sensor_stable_depth_rear   = "UNKNOWN";
  msg.robot_is_sensor_stable_motor        = "UNKNOWN";
  msg.robot_is_sensor_stable_imu          = "UNKNOWN";
  msg.robot_is_sensor_stable_tof          = "UNKNOWN";
  msg.robot_hw_switch_key_status          = "UNKNOWN";
  msg.robot_hw_switch_ems_status          = "UNKNOWN";
  msg.robot_is_charging_status            = "UNKNOWN";

  try
  {
    auto json = nlohmann::json::parse(status_json);

    if(json.contains("data"))
    {
      const auto& data = json["data"];
      msg.robot_is_sensor_stable_lidar_front =
          data.value("robot_is_sensor_stable_lidar_front", msg.robot_is_sensor_stable_lidar_front);
      msg.robot_is_sensor_stable_lidar_rear  =
          data.value("robot_is_sensor_stable_lidar_rear", msg.robot_is_sensor_stable_lidar_rear);
      msg.robot_is_sensor_stable_lidar_3d    =
          data.value("robot_is_sensor_stable_lidar_3d", msg.robot_is_sensor_stable_lidar_3d);
      msg.robot_is_sensor_stable_depth_front =
          data.value("robot_is_sensor_stable_depth_front", msg.robot_is_sensor_stable_depth_front);
      msg.robot_is_sensor_stable_depth_rear  =
          data.value("robot_is_sensor_stable_depth_rear", msg.robot_is_sensor_stable_depth_rear);
      msg.robot_is_sensor_stable_motor       =
          data.value("robot_is_sensor_stable_motor", msg.robot_is_sensor_stable_motor);
      msg.robot_is_sensor_stable_imu         =
          data.value("robot_is_sensor_stable_imu", msg.robot_is_sensor_stable_imu);
      msg.robot_is_sensor_stable_tof         =
          data.value("robot_is_sensor_stable_tof", msg.robot_is_sensor_stable_tof);
      msg.robot_hw_switch_key_status         =
          data.value("robot_hw_switch_key_status", msg.robot_hw_switch_key_status);
      msg.robot_hw_switch_ems_status         =
          data.value("robot_hw_switch_ems_status", msg.robot_hw_switch_ems_status);
      msg.robot_is_charging_status           =
          data.value("robot_is_charging_status", msg.robot_is_charging_status);
    }
  }
  catch(const std::exception&)
  {
    // JSON 파싱 오류 시 기본값 사용
  }
  _publish_hw_status.publish(msg);
}