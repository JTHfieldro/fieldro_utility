#include "web_socket_base.h"

void frb::WebSocketBase::initialize_client()
{
  if(_is_initialized) return;
  if(_is_connected) return;
  if(_end_point != nullptr) return;

  _end_point = new websocketpp::client<websocketpp::config::asio_client>();

  // WebSocket++ 초기화
  _end_point->clear_access_channels(websocketpp::log::alevel::all);
  // _end_point->set_access_channels(websocketpp::log::alevel::connect);
  // _end_point->set_access_channels(websocketpp::log::alevel::disconnect);
  // _end_point->set_access_channels(websocketpp::log::alevel::app);
  _end_point->clear_error_channels(websocketpp::log::elevel::all);

  // 콜백 설정
  _end_point->set_message_handler(
      std::bind(&WebSocketBase::on_message, this, std::placeholders::_1, std::placeholders::_2));
  _end_point->set_open_handler(std::bind(&WebSocketBase::on_open, this, std::placeholders::_1));
  _end_point->set_close_handler(std::bind(&WebSocketBase::on_close, this, std::placeholders::_1));
  _end_point->set_fail_handler(std::bind(&WebSocketBase::on_fail, this, std::placeholders::_1));

  _end_point->init_asio();
  _end_point->start_perpetual();

  _is_initialized = true;
  LOGGER->push_log_format("INFO", "PROC", "Success to Client Initialization");
}

bool frb::WebSocketBase::client_connect()
{
  if(_last_try_connect_time + _retry_turm > std::time(nullptr))
  {
    return false;  // turm 이내에 시도한 적이 있다.
  }
  initialize_client();

  if(_connect_logging_count > 0)
  {
    LOGGER->push_log_format("INFO", "PROC", "Attempting to Connect Server", _url);
  }
  _last_try_connect_time = std::time(nullptr);
  websocketpp::lib::error_code ec;

  // 1. 연결 객체 생성 - 아직 실제 연결은 이루어지지 않음
  client::connection_ptr connection = _end_point->get_connection(_url, ec);

  if(ec)
  {
    if(_connect_logging_count > 0)
    {
      LOGGER->push_log_format("ERROR", "PROC", "Connection Initialization Error", ec.message());
      _connect_logging_count--;
    }
    return false;
  }

  // 2. 연결 핸들 저장
  _connection = connection->get_handle();
  // 3. 실제 연결 시도 시작 - 비동기 연결 시작
  _end_point->connect(connection);
  // 연결 상태 확인
  websocketpp::client<websocketpp::config::asio_client>::connection_ptr curr_conn =
      _end_point->get_con_from_hdl(_connection);

  // 4. ASIO 이벤트 루프 시작 - 이 호출은 블로킹됨
  // run()을 별도 스레드에서 실행
  _asio_thread = std::thread(
      [this]()
      {
        try
        {
          if(_end_point && _is_initialized)
          {
            _end_point->run();
          }
        }
        catch(const std::exception& e)
        {
          LOGGER->push_log_format("ERROR", "PROC", "ASIO thread Error", std::string(e.what()));
          _is_connected = false;
        }
      });
  // _asio_thread.detach();  // 스레드 분리

  _connect_logging_count = 5;
  return true;
}

void frb::WebSocketBase::client_disconnect()
{
  if(!_is_connected) return;
  if(_end_point == nullptr) return;

  {
    std::lock_guard<std::mutex> lock(_mtx);
    _is_connected = false;

    websocketpp::lib::error_code ec;
    _end_point->close(_connection, websocketpp::close::status::normal, "Closing connection", ec);

    if(ec)
    {
      LOGGER->push_log_format("ERROR", "PROC", "Close Error", ec.message());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // // ASIO 이벤트 루프 중지
  // _end_point->stop();
  // // endpoint 정리
  // _end_point->get_io_service().stop();
  // _end_point->stop_perpetual();

  // std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // if(_asio_thread.joinable())
  // {
  //   _asio_thread.join();
  // }
  // std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // _end_point->reset();  // endpoint 내부 상태 초기화

  // 스레드에 시그널 보내기 (ASIO 작업 중지)
  // 순서 중요: 스레드가 실행 중인 작업부터 중지해야 함
  if(_end_point)
  {
    // 2. 먼저 ASIO 이벤트 루프 중지 시그널 전송
    _end_point->stop();

    // 3. IO 서비스 중지
    try
    {
      _end_point->get_io_service().stop();
    }
    catch(...)
    {
      LOGGER->push_log_format("ERROR", "PROC", "Error stopping IO service");
    }

    // 4. 영구 루프 중지
    _end_point->stop_perpetual();
  }

  // ASIO 스레드가 종료될 때까지 대기
  // 이 부분은 뮤텍스 외부에서 실행하여 데드락 방지
  if(_asio_thread.joinable())
  {
    LOGGER->push_log_format("INFO", "PROC", "Waiting for ASIO Thread to Finish");

    // 스레드 조인 타임아웃 설정 (최대 3초)
    bool        joined = false;
    std::thread timeout_thread([&]()
                               {
      std::this_thread::sleep_for(std::chrono::seconds(3));
      if(!joined) {
        LOGGER->push_log_format("WARN", "PROC", "ASIO Thread Join Timeout");
      } });
    timeout_thread.detach();

    _asio_thread.join();
    joined = true;

    LOGGER->push_log_format("INFO", "PROC", "ASIO Thread Terminated Successfully");
  }

  LOGGER->push_log_format("INFO", "PROC", "Success to Disconnection");
}

void frb::WebSocketBase::on_open(websocketpp::connection_hdl hdl)
{
  websocketpp::client<websocketpp::config::asio_client>::connection_ptr conn =
      _end_point->get_con_from_hdl(hdl);

  if(conn)
  {
    LOGGER->push_log_format("INFO", "PROC", "Connection Established");
    LOGGER->push_log_format("INFO", "PROC", "                  Host", _ip);
    LOGGER->push_log_format("INFO", "PROC", "                  Port", std::to_string(_port));
    LOGGER->push_log_format("INFO", "PROC", "Message", conn->get_ec().message());
    LOGGER->push_log_format("INFO", "PROC", "Remote IP", conn->get_remote_endpoint());
  }
  _is_connected = true;
}

void frb::WebSocketBase::on_close(websocketpp::connection_hdl hdl)
{
  std::lock_guard<std::mutex> lock(_mtx);

  if(_end_point == nullptr)
  {
    _is_initialized = false;
    _is_connected   = false;
    return;
  }

  websocketpp::client<websocketpp::config::asio_client>::connection_ptr conn;
  try
  {
    conn = _end_point->get_con_from_hdl(hdl);
  }
  catch(...)
  {
    // _end_point가 이미 해제 과정 중일 수 있음
    _is_initialized = false;
    _is_connected   = false;
    return;
  }

  if(conn)
  {
    LOGGER->push_log_format("INFO", "PROC", "Connection Closed");

    // 종료 사유와 상태 코드 로깅
    try
    {
      websocketpp::close::status::value code   = conn->get_remote_close_code();
      std::string                       reason = conn->get_remote_close_reason();

      LOGGER->push_log_format("INFO", "PROC", "Close Code", std::to_string(code));
      LOGGER->push_log_format("INFO", "PROC", "Close Reason", reason);

      websocketpp::lib::error_code ec = conn->get_ec();
      if(ec)
      {
        LOGGER->push_log_format("ERROR", "PROC", "Error Message", ec.message());
      }
    }
    catch(...)
    {
      LOGGER->push_log_format("ERROR", "PROC", "Error Accessing Connection Data");
    }

    // ASIO 스레드가 종료되었는지 확인 후 삭제
    if(!_asio_thread.joinable())
    {
      LOGGER->push_log_format("INFO", "PROC", "Cleaning Up end_point");
      safe_delete(_end_point);
    }
    else
    {
      LOGGER->push_log_format("WARN", "PROC", "ASIO Thread Still Running, Deferring end_point Cleanup");
    }
  }
  _is_initialized = false;
}

void frb::WebSocketBase::on_fail(websocketpp::connection_hdl hdl)
{
  websocketpp::client<websocketpp::config::asio_client>::connection_ptr conn =
      _end_point->get_con_from_hdl(hdl);

  if(conn)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Connection Failed");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", conn->get_ec().message());
    LOGGER->push_log_format("ERROR", "PROC", "Error Code", std::to_string(conn->get_ec().value()));
    LOGGER->push_log_format("ERROR", "PROC", "Remote IP", conn->get_remote_endpoint());
    LOGGER->push_log_format("ERROR", "PROC", "State", std::to_string(conn->get_state()));
  }
  _is_connected = false;
}