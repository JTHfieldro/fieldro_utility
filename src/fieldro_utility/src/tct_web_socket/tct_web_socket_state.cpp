#include "tct_web_socket.h"

void frb::TctWebSocket::check_hardware_status()
{
  send_message_no_data(frb::TctFuncCode::GetHardwareStatus);
}

void frb::TctWebSocket::change_to_manual_mode()
{
  nlohmann::json data;
  data["key_state"] = "manual";

  send_message(frb::TctFuncCode::SetOperationMode, data);
}