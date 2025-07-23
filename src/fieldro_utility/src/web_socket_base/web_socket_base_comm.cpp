#include "web_socket_base.h"

void frb::WebSocketBase::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
  try
  {
    std::string payload = msg->get_payload();
    response_message(payload);
  }
  catch(const std::exception& e)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Message Handling Failed", std::string(e.what()));
  }
}