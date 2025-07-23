#include "global_helper.h"
#include "logger.h"
#include "web_socket_manager.h"

int main()
{
  bool loop = true;
  char cmd_input[256];

  frb::set_current_dir_to_executable_path();

  frb::Logger* logger = frb::Logger::get("TCT_SOCKET_BRIDGE");
  logger->push_log_format("INFO", "PROC", "Start");

  frb::WebSocketManager* web_socket_manager = new frb::WebSocketManager("config/tct_socket_bridge.yaml", logger);

  while (loop)
  {
    if (!frb::check_std_in(10000)) continue;

    std::string str = frb::get_user_input();
    std::vector<std::string> input = frb::find_command_target(str, ' ');

    if (input.size() < 1) continue;

    if (input[0] == "finish") loop = false;
    else if (input[0] == "clear") system("clear");
    else if (input[0] == "tct") web_socket_manager->control(input[1]);
  }

  logger->push_log_format("INFO", "PROC", "End");
  safe_delete(web_socket_manager);
  frb::Logger::destroy();

  return 0;
}
