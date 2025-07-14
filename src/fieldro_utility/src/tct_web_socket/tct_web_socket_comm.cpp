#include "tct_web_socket.h"

void frb::TctWebSocket::send_message_no_data(const TctFuncCode& function_code)
{
    nlohmann::json data = {{}};
    send_message(function_code, data);
}

bool frb::TctWebSocket::send_message(const TctFuncCode& function_code, const nlohmann::json& data)
{
  if(!_is_connected) return false;

  try
  {
    std::string message = construct_message(function_code, data);
    _end_point->send(_connection, message, websocketpp::frame::opcode::text);

    if((function_code != frb::TctFuncCode::Heartbeat) && (function_code != frb::TctFuncCode::GetEngineStatus) &&
       (function_code != frb::TctFuncCode::GetRealtimeStatus) && (function_code != frb::TctFuncCode::GetAlarmList) && (function_code != frb::TctFuncCode::GetHardwareStatus))
    {
      _logger->push_log_format("INFO", "PROC", "Send Function Code", api_to_string(function_code));
    }
    if(data.dump() != "[null]")
    {
      _logger->push_log_format("INFO", "PROC", "Send Data", data.dump());
    }
    return true;
  }
  catch(const std::exception& e)
  {
    _logger->push_log_format("ERROR", "PROC", "Failed to Send Message", std::string(e.what()));
    return false;
  }
}

std::string frb::TctWebSocket::construct_message(const TctFuncCode& function_code, const nlohmann::json& data)
{
  std::string seq_str = std::to_string(_sequence_number++);
  while(seq_str.length() < 4)
  {
    seq_str = "0" + seq_str;
  }
  // 2. Function code
  std::string fn_code = std::to_string(static_cast<int32_t>(function_code));
  while(fn_code.length() < 4)
  {
    fn_code = "0" + fn_code;
  }

  std::ostringstream ss;
  // 1. Header construction
  ss << "$$";     // STX
  ss << "100";    // Version (100)
  ss << "N";      // Compression type (N: 압축없음)
  ss << seq_str;  // Sequence number (4자리)
  ss << "Q";      // Message type (Q: Query)
  ss << "FFF";    // Reserved1
  ss << fn_code;  // Function Code (4자리)
  // 3. Reserved padding
  ss << "FFFFFFFFFFFFFFFF";  // Reserved2 (16 bytes of F)
  // 4. JSON Data
  ss << "{\"data\":" << data.dump() << "}";

  // _logger->push_log_format("INFO", "PROC", "Json Message", ss.str());

  if(seq_str == "9999")
  {
    _sequence_number = 1;
  }

  return ss.str();
}

void frb::TctWebSocket::response_message(const std::string& pay_load)
{
  try
  {
    std::tuple<frb::TctFuncCode, std::string> parsing_result = parsing_message(pay_load);
    frb::TctFuncCode fn_code_enum = std::get<0>(parsing_result);

    nlohmann::json response = nlohmann::json::parse(std::get<1>(parsing_result));

    if (response.find("code") != response.end() && response["code"] != 1)
    {
      _logger->push_log_format("WARN", "RECV", "API Failed Code", std::to_string(response["code"].get<int>()));
      return;
    }
    else
    {
      _response_manager->process_message(fn_code_enum, response["data"]);
    }
  }
  catch (const std::exception& e)
  {
    _logger->push_log_format("ERROR", "PROC", "Response Parsing Failed", std::string(e.what()));
    _logger->push_log_format("ERROR", "PROC", "Pay Load", pay_load);
  }
}

std::tuple<frb::TctFuncCode, std::string> frb::TctWebSocket::parsing_message(const std::string& pay_load)
{
  // TCT 프로토콜 파싱 (예: $$ + version + compression + seq + type + fn_code + data + $$)
  if(pay_load.substr(0, 2) != "$$" || pay_load.length() < 34)
  {
    throw std::runtime_error("Invalid TCT protocol format");
  }

  // 헤더 파싱
  std::string      version      = pay_load.substr(2, 3);
  std::string      compression  = pay_load.substr(5, 1);
  std::string      seq          = pay_load.substr(6, 4);
  std::string      type         = pay_load.substr(10, 1);
  std::string      fn_code      = pay_load.substr(14, 4);
  frb::TctFuncCode fn_code_enum = static_cast<frb::TctFuncCode>(std::stoi(fn_code));

  // JSON 데이터 파싱
  // {"code":1,"data":{}}}에 해당하는 부분
  std::string json_str = pay_load.substr(34);
  return std::tuple<frb::TctFuncCode, std::string>(fn_code_enum, json_str);
}