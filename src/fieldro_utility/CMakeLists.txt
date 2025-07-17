cmake_minimum_required(VERSION 3.0.2)
project(fieldro_utility)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
)

find_package(YAML-CPP REQUIRED)

add_message_files(
  FILES
  hw_status.msg
  engine_status.msg
  alarm_status.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
)

include_directories(
  include
  include/helper
  include/tct_web_socket
  include/web_socket_base
  include/web_socket_manager
  include/web_socket_response_manager
  ${catkin_INCLUDE_DIRS}
  /usr/include  # for nlohmann/json.hpp
  /usr/include/websocketpp
)

set(WS_SOURCES
  src/web_socket_base/web_socket_base.cpp
  src/web_socket_base/web_socket_base_connect.cpp
  src/web_socket_base/web_socket_base_comm.cpp
)

set(HELPER_SOURCES
  src/helper/logger.cpp
  src/helper/thread_action_info.cpp
)

add_executable(tct_web_socket_node
  ${WS_SOURCES}
  ${HELPER_SOURCES}
  src/tct_web_socket/tct_web_socket.cpp
  src/tct_web_socket/tct_web_socket_comm.cpp
  src/tct_web_socket/tct_web_socket_connect.cpp
  src/_node/tct_socket_bridge_node.cpp
  src/web_socket_manager/web_socket_manager.cpp
  src/web_socket_manager/web_socket_manager_action.cpp
  src/web_socket_manager/web_socket_manager_update.cpp
  src/web_socket_response_manager/web_socket_response_manager.cpp
  src/web_socket_response_manager/web_socket_response_manager_pub.cpp
)

target_link_libraries(tct_web_socket_node
  ${catkin_LIBRARIES}
  yaml-cpp
  pthread
)

# 설정 파일 자동 복사
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config
     DESTINATION ${CATKIN_DEVEL_PREFIX}/lib/${PROJECT_NAME})
