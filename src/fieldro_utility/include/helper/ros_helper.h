#pragma once

#include <string>

#include "global_helper.h"
#include "logger.h"
#include "ros/ros.h"

namespace frb  // fieldro_bot
{
#ifndef LOGGER
#define LOGGER _logger
#endif

/**
 * @author 	Fieldro : hs8559@fieldro.tech
 * @date 		24-12-15
 * @brief	  RosHelper 클래스
 * @note 		ROS Node를 사용하기 위한 Helper Class
 * @details
 * @see
 */
class RosHelper
{
public:
  RosHelper(Logger* logger) : _logger(logger) {}
  virtual ~RosHelper() {}

protected:
  ros::NodeHandle*   _node_handle;  ///< ROS Node Handle
  ros::AsyncSpinner* _spinner;      ///< ROS Async Spinner
  Logger*            _logger;       ///< Logger 객체

protected:
  /**
   * @brief	    ROS Node 초기화 함수
   * @param[in]	node_name : ROS Node 이름
   */
  virtual void initialize_ros_node(const std::string& node_name)
  {
    int32_t argc = 0;
    ros::init(argc, nullptr, node_name.c_str());
    _node_handle = new ros::NodeHandle();

    set_subscriber();
    set_publisher();

    _spinner = new ros::AsyncSpinner(5);
    _spinner->start();

    LOGGER->push_log_format("INFO", "PROC", "ROS Node Initialized");
  }
  /**
   * @brief	    ROS Subscriber 설정 함수
   * @note      순수 가상 함수
   */
  virtual void set_subscriber() = 0;
  /**
   * @brief	    ROS Publisher 설정 함수
   * @note      순수 가상 함수
   */
  virtual void set_publisher() = 0;
  /**
   * @brief	    ROS Node 해제 함수
   */
  virtual void delete_ros_node()
  {
    safe_delete(_node_handle);
    safe_delete(_spinner);

    LOGGER->push_log_format("INFO", "PROC", "ROS Node Deleted");
  }
};
}  // namespace frb