#include "tct_web_socket.h"

void frb::TctWebSocket::check_hardware_status()
{
  send_message_no_data(frb::TctFuncCode::GetHardwareStatus);
}