#include "tct_web_socket.h"
#include <iostream>

frb::TctWebSocket::TctWebSocket(const std::string& config_path, Logger* logger)
  : frb::WebSocketBase(config_path, logger), _config_path(config_path), _logger(logger)
{
  initialize();
  load_option(config_path);
}

frb::TctWebSocket::~TctWebSocket()
{
  _thread_info->_active = false;
  client_disconnect();
  safe_delete(_response_manager);
  safe_delete(_thread_info);
  while(_is_connected)
  {
    // on_close 응답 대기
    if(!_is_connected) break;
  }
}

void frb::TctWebSocket::update()
{
  while(_thread_info->_active)
  {
    if(!_is_connected)
    {
      client_connect();
      continue;
    }

    initialize_tct_operation();
    check_heartbeat();

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void frb::TctWebSocket::initialize()
{
  initialize_client();
  _thread_info = new ThreadActionInfo(_config_path);
  _response_manager = new WebSocketResponseManager(_logger);
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&TctWebSocket::update, this));
}

void frb::TctWebSocket::initialize_tct_operation()
{
  if(_is_initialization_finish) return;
  if(!_is_connected) return;
}

void frb::TctWebSocket::load_option(const std::string& config_path)
{
  try {
    std::ifstream yaml_file(config_path);
    YAML::Node yaml = YAML::Load(yaml_file);
    yaml_file.close();

    std::string config_name = yaml["config_name"].as<std::string>();
    LOGGER->push_log_format("INFO", "PROC", config_name);
  }
  catch(const YAML::Exception& e) {
    LOGGER->push_log_format("ERROR", "PROC", "YAML Exception", e.what());
  }
  catch(const std::exception& e) {
    LOGGER->push_log_format("ERROR", "PROC", "Standard Exception", e.what());
  }
  catch(...) {
    LOGGER->push_log_format("ERROR", "PROC", "Unknown Exception");
  }
}