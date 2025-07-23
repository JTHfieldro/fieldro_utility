#include "web_socket_base.h"

frb::WebSocketBase::WebSocketBase(const std::string& config_path, Logger* logger)
    : _config_path(config_path), _logger(logger)
{
  _is_initialized           = false;
  _is_connected             = false;
  _last_try_connect_time    = 0;
  _last_heartbeat_send_time = 0;
  _last_heartbeat_recv_time = 0;

  load_option(_config_path);
}

void frb::WebSocketBase::load_option(const std::string& config_path)
{
  try
  {
    std::cout << config_path << std::endl;
    // file open
    std::ifstream yaml_file(config_path);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    LOGGER->push_log_format("INFO", "PROC", config_name);

    // Option 정보
    _ip         = yaml["server_info"]["ip"].as<std::string>();
    _port       = yaml["server_info"]["port"].as<int16_t>();
    _retry_turm = yaml["connection"]["retry_turm"].as<int32_t>();

    _url = "ws://" + _ip + ":" + std::to_string(_port);
  }
  catch(YAML::Exception& e)
  {
    LOGGER->push_log_format("ERROR", "PROC", "YAML Exception", e.what());
  }
  catch(std::exception& e)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Standard Exception", e.what());
  }
  catch(...)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Unknown Exception", "");
  }
}