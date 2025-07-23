#include "tct_web_socket.h"

void frb::TctWebSocket::check_heartbeat()
{
  if(_last_heartbeat_send_time + 30 > std::time(nullptr)) return;  // turm 이내에 시도한 적이 있다.

  _last_heartbeat_send_time = std::time(nullptr);
  if(_last_heartbeat_recv_time == 0) _last_heartbeat_recv_time = std::time(nullptr);

  send_message_no_data(frb::TctFuncCode::Heartbeat);
}

void frb::TctWebSocket::update_heartbeat_recv_time(const std::time_t& last_heartbeat_recv_time)
{
  if(_last_heartbeat_recv_time + 60 < std::time(nullptr))
  {
    _logger->push_log_format("WARN", "PROC", "HeartBeat Recieve Time is Over One Minute");
    // client_disconnect();
  }
  _last_heartbeat_recv_time = last_heartbeat_recv_time;
}