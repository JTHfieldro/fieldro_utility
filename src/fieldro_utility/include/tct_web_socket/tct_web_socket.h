#ifndef TCT_WEB_SOCKET_H
#define TCT_WEB_SOCKET_H

#include <string>

#include "web_socket_base.h"
#include "tct_web_socket_define.h"
#include "web_socket_response_manager.h"

#include "thread_action_info.h"
#include "logger.h"
#include "global_helper.h"

namespace frb {

class TctWebSocket : public WebSocketBase
{
public:
  TctWebSocket(const std::string& config_path, Logger* logger);
  virtual ~TctWebSocket();

  void        send_message_no_data(const TctFuncCode& function_code);
  bool        send_message(const TctFuncCode& function_code, const nlohmann::json& data);

private:
  ThreadActionInfo* _thread_info;
  WebSocketResponseManager* _response_manager;
  Logger* _logger;
  std::map<std::string, int32_t> _command_map;
  std::string                    _config_path;

  bool           _is_initialization_finish;
  uint32_t       _sequence_number;

  void update();
  void initialize();
  void initialize_tct_operation();
  void load_option(const std::string& config_path);

  void        response_message(const std::string& pay_load);
  std::string construct_message(const TctFuncCode& function_code, const nlohmann::json& data);
  std::tuple<frb::TctFuncCode, std::string> parsing_message(const std::string& pay_load);  

  void check_heartbeat();
  void update_heartbeat_recv_time(const std::time_t& last_heartbeat_recv_time);
};

}  // namespace frb

#endif  // TCT_WEB_SOCKET_H