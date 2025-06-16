#include "web_socket_manager.h"

void frb::WebSocketManager::publish_hw_status(const std::string& status_json)
{
  fieldro_utility::hw_status msg;
  msg.json = status_json;
  _hw_status_pub.publish(msg);
}