#pragma once

// C++ standard library
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <tuple>

// Third-party libraries
#include <yaml-cpp/yaml.h>

#include <nlohmann/json.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>
#include <websocketpp/common/chrono.hpp>


// Local headers
#include "global_helper.h"
#include "logger.h"

namespace frb  // fieldro_bot
{
#ifndef LOGGER
#define LOGGER _logger
#endif

// WebScoket++ Library using 선언
// Call-Back or Event Handler Binding 시 사용
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

/**
 * @author		Fieldro : hs8559@fieldro.tech
 * @date			24-12-14
 * @brief	    WebSocket Base Class
 * @note		  WebSocket++ Library를 사용한 WebSocket 통신을 위한 Base Class
 * @details
 * @see
 */
class WebSocketBase
{
private:
  WebSocketBase() {}

public:
  WebSocketBase(const std::string& config_path, Logger* logger);
  virtual ~WebSocketBase() {}

public:
  /**
   * @brief   현재 Client 연결 상태 반환
   * @return  연결 상태 반환
   * @note
   */
  bool is_connected() const { return _is_connected; }

protected:
  Logger* _logger;  ///< Logger 객체

  using client = websocketpp::client<websocketpp::config::asio_client>;  ///< type alias(타입 별칭) 선언
  // 비동기 I/O 작업을 위한 Asio 기반 설정 사용
  // WebSocket 연결 관리, Message 송수신, Event Handling 등의 기능 제공
  client*                     _end_point;
  websocketpp::connection_hdl _connection;  ///< 현재 활성화된 WebSocket 연결에 대한 Handler
  ///< ASIO 이벤트 루프를 위한 스레드, _endpoint.run() Blocking 탈출을 위한 스레드
  // 비동기 I/O 작업 처리
  std::thread _asio_thread;
  std::mutex  _mtx;  ///< mutex 객체

  std::string _config_path;  ///< yaml file path 저장 변수
  std::string _ip;           ///< Server ip 저장 변수
  int16_t     _port;         ///< Server port 저장 변수
  int32_t     _retry_turm;   ///< 재연결 시도 간격(s)

  std::string _url;                        ///< WebSocket 저장 변수
  bool        _is_initialized;             ///< _endpoint 객체 초기화 여부
  bool        _is_connected;               ///< 현재 Client 연결 상태 Flag
  std::time_t _last_try_connect_time;      ///< 최근 재연결 시도 시간(s)
  std::time_t _last_heartbeat_send_time;   ///< 최근 Heartbeat 수신 시간(s)
  std::time_t _last_heartbeat_recv_time;   ///< 최근 Heartbeat 수신 시간(s)
  uint16_t    _connect_logging_count = 5;  ///< 연결 시도 로깅 횟수 제한

protected:
  /**
   * @brief		  Config 설정 파일 로드 함수
   * @param[in] config_path: 설정 파일 경로
   */
  virtual void load_option(const std::string& config_path);
  /**
   * @brief		  초기화 함수
   */
  virtual void initialize() = 0;
  /**
   * @brief		  Client 객체 초기화 함수
   */
  void initialize_client();
  /**
   * @brief			Client WebSocket 연결 요청 함수
   */
  bool client_connect();
  /**
   * @brief			Client WebSocket 연결 종료 함수
   */
  void client_disconnect();
  /**
   * @brief			연결이 성공적으로 수립되었을 때 호출
   * @param[in] 연결 Handler
   */
  void on_open(websocketpp::connection_hdl hdl);
  /**
   * @brief			정상적인 연결 종료 시 호출
   * @param[in] 연결 Handler
   */
  void on_close(websocketpp::connection_hdl hdl);
  /**
   * @brief			연결 시도 실패나 에러 발생 시 호출
   * @param[in] 연결 Handler
   */
  void on_fail(websocketpp::connection_hdl hdl);
  /**
   * @brief		  Message 수신 시 호출
   * @param[in] 연결 Handler
   * @param[in] 수신 Message
   */
  void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
  /**
   * @brief			수신 Message Parsing 및 Handler 호출 함수
   * @param[in]	수신 Message
   */
  virtual void response_message(const std::string& pay_load) = 0;
};
}  // namespace frb