#include "web_socket_manager.h"

void frb::WebSocketManager::set_publisher()
{
  _publish_hw_status = _node_handle->advertise<fieldro_utility::hw_status>("hw_status", 10);
}