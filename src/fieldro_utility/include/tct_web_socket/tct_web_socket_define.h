#pragma once

#include <iomanip>
#include <sstream>
#include <string>

namespace frb  // fieldro_bot
{

enum class Logging
{
  No      = 0,
  Logging = 1,
  LOGGING_END,
};

enum class JogMotionType
{
  None,

  Forward,
  Backward,
  Ccw,
  Cw,
  Stop,

  JogMotionTypeEnd,
};

inline std::string jog_motion_type_to_string(frb::JogMotionType type)
{
  switch(type)
  {
    case frb::JogMotionType::Forward: return "forward";
    case frb::JogMotionType::Backward: return "backward";
    case frb::JogMotionType::Ccw: return "ccw";
    case frb::JogMotionType::Cw: return "cw";
    case frb::JogMotionType::Stop: return "stop";
    default: return "Unknown";
  }
}

enum class DrivingMethod
{
  None,

  TLP,  // 회피 주행
  OAP,
  StaticAuto,
  StaticForward,  // 비회피 경로 직진 주행
  StaticBackward,

  DrivingMethodEnd,
};

inline std::string driving_method_to_string(frb::DrivingMethod type)
{
  switch(type)
  {
    case frb::DrivingMethod::TLP: return "TLP";
    case frb::DrivingMethod::OAP: return "OAP";
    case frb::DrivingMethod::StaticAuto: return "StaticAuto";
    case frb::DrivingMethod::StaticForward: return "StaticForward";
    case frb::DrivingMethod::StaticBackward: return "StaticBackward";
    default: return "Unknown";
  }
}

enum class TctFuncCodeType
{
  State,
  Map,
  Node,
  Slam,
  ChangeTctMode,
  ManualMode,
  AutoMode,
  StopMode,
  TeachingMode,
  JogMode,
  Script,
  Lidar,
  Variable,
  ModbusTcp,
  Settings,
  UserSettings,
  NavigationParameter,
  Log,
  Restart,
  Spec,
  Heartbeat,
  Bridge,
  File,
  Traffic,
  DigitalIo,
  Mission,
  TctFuncCodeTypeEnd,
};

enum class TctFuncCode
{
  GetMapList              = 0,
  GetMapImage             = 2,
  GetCompressedMapImage   = 3,
  SaveMapImage            = 4,
  DeleteMap               = 5,
  GetNodeList             = 6,   // Get Node Information
  AddNode                 = 7,   // Add New Node
  ModifyNode              = 8,   // Edit Node Information
  DeleteNode              = 9,   // Delete Node
  AddEdge                 = 10,  // Add New Edge
  DeleteEdge              = 11,  // Delete Edge
  StartMapping            = 12,
  StopMapping             = 13,
  Set3dMapParams          = 14,
  GetCurrentMapImage      = 15,
  GetCurrentCompressedMap = 16,
  GetMergedLidarData      = 17,
  GetFrontLidarData       = 18,
  GetRearLidarData        = 19,
  GetPlannedPath          = 20,
  GetHardwareStatus       = 22,  // 하드웨어 상태 가져오기
  GetEngineStatus         = 23,  // 자율주행 엔진 상태 가져오기
  GetRealtimeStatus       = 25,  // 로봇 상태 가져오기
  GetMappingStatus        = 26,
  GetAlarmList            = 27,  // TCT 알람 상태 가져오기
  GetCommStatus           = 28,
  GetTctHistory           = 29,
  SetOperationMode        = 30,  // TCT Mode 전환
  SwitchToTeaching        = 31,  // Teaching 대기 모드 전환
  SwitchToJog             = 32,  // Jog 주행 Mode 전환
  SetLocalization         = 33,  // Manual Localization
  ControlJog              = 34,  // Jog Control
  StartAvoidanceNav       = 35,
  StartNonavoidanceNav    = 36,
  StartDocking            = 37,
  StartUndocking          = 38,
  StartPathNav            = 39,  // 등록된 노드로 주행 요청
  PauseNavigation         = 40,  // 주행 일시 정지
  CancelNavigation        = 41,  // 주행 취소
  ResumeNavigation        = 42,  // 주행 재개
  StartScript             = 43,  // Script 시작
  StopScript              = 44,  // Script 정지
  ExitScriptError         = 45,  // Script 구문 Error Reset
  GetScriptOutput         = 46,
  GetScriptList           = 47,
  GetScriptContent        = 48,
  SaveScript              = 49,
  DeleteScript            = 50,
  CheckScriptExists       = 51,
  GetEngineParams         = 52,
  GetParamList            = 53,
  SetUserParams           = 54,
  GetVaiable              = 55,
  GetMultipleVariables    = 56,
  GetVariableList         = 57,
  SetVariable             = 58,
  SetMultipleVariables    = 59,
  GetModbusMemory         = 60,
  SetModbusMemory         = 61,
  SetModbusName           = 62,
  GetLogList              = 63,
  GetLogData              = 64,
  InitRobotConfig         = 65,
  SetJogSpeed             = 66,
  SetSensorConfig         = 67,
  GetRobotConfig          = 69,
  GetRobotSpecs           = 70,
  ResetAlarm              = 71,  // 알람 초기화
  RestartEngine           = 72,
  Heartbeat               = 74,
  GetLocalizationLidar    = 83,
  GetCurrentPcd           = 84,
  GetMapPcd               = 85,
  SetRobotSpeed           = 86,
  GetBridgeConfig         = 87,
  SetBridgeConfig         = 88,
  StartBridge             = 89,
  StopBridge              = 90,
  GetMasterInfo           = 91,  // Master Server Integrated Information
  SetVariableByCondition  = 95,
  GetRealtimePcd          = 96,
  GetTctFiles             = 97,
  DeleteTctFile           = 98,
  CreateTctFile           = 99,
  CreateTctDir            = 100,
  GetMappingLidar         = 101,
  GetFileBinary           = 102,
  SetMapFloor             = 103,
  GetHighScan             = 104,
  GetLowScan              = 105,
  GetScanMerged           = 106,
  ModifyVariable          = 108,
  RequestYield            = 109,
  GetDigitalIo            = 110,
  SetDigitalOutput        = 111,
  SendMission             = 112,
  GetMissionStatus        = 113,
  DeleteMission           = 114,
  CancelMission           = 115,
  FindPath                = 116,
  TctFuncCodeEnd,
};

inline std::string api_to_string(TctFuncCode code)
{
  switch(code)
  {
    case TctFuncCode::GetMapList: return "GetMapList";
    case TctFuncCode::GetMapImage: return "GetMapImage";
    case TctFuncCode::GetCompressedMapImage: return "GetCompressedMapImage";
    case TctFuncCode::SaveMapImage: return "SaveMapImage";
    case TctFuncCode::DeleteMap: return "DeleteMap";
    case TctFuncCode::GetNodeList: return "GetNodeList";
    case TctFuncCode::AddNode: return "AddNode";
    case TctFuncCode::ModifyNode: return "ModifyNode";
    case TctFuncCode::DeleteNode: return "DeleteNode";
    case TctFuncCode::AddEdge: return "AddEdge";
    case TctFuncCode::DeleteEdge: return "DeleteEdge";
    case TctFuncCode::StartMapping: return "StartMapping";
    case TctFuncCode::StopMapping: return "StopMapping";
    case TctFuncCode::Set3dMapParams: return "Set3dMapParams";
    case TctFuncCode::GetCurrentMapImage: return "GetCurrentMapImage";
    case TctFuncCode::GetCurrentCompressedMap: return "GetCurrentCompressedMap";
    case TctFuncCode::GetMergedLidarData: return "GetMergedLidarData";
    case TctFuncCode::GetFrontLidarData: return "GetFrontLidarData";
    case TctFuncCode::GetRearLidarData: return "GetRearLidarData";
    case TctFuncCode::GetPlannedPath: return "GetPlannedPath";
    case TctFuncCode::GetHardwareStatus: return "GetHardwareStatus";
    case TctFuncCode::GetEngineStatus: return "GetEngineStatus";
    case TctFuncCode::GetRealtimeStatus: return "GetRealtimeStatus";
    case TctFuncCode::GetMappingStatus: return "GetMappingStatus";
    case TctFuncCode::GetAlarmList: return "GetAlarmList";
    case TctFuncCode::GetCommStatus: return "GetCommStatus";
    case TctFuncCode::GetTctHistory: return "GetTctHistory";
    case TctFuncCode::SetOperationMode: return "SetOperationMode";
    case TctFuncCode::SwitchToTeaching: return "SwitchToTeaching";
    case TctFuncCode::SwitchToJog: return "SwitchToJog";
    case TctFuncCode::SetLocalization: return "SetLocalization";
    case TctFuncCode::ControlJog: return "ControlJog";
    case TctFuncCode::StartAvoidanceNav: return "StartAvoidanceNav";
    case TctFuncCode::StartNonavoidanceNav: return "StartNonavoidanceNav";
    case TctFuncCode::StartDocking: return "StartDocking";
    case TctFuncCode::StartUndocking: return "StartUndocking";
    case TctFuncCode::StartPathNav: return "StartPathNav";
    case TctFuncCode::PauseNavigation: return "PauseNavigation";
    case TctFuncCode::CancelNavigation: return "CancelNavigation";
    case TctFuncCode::ResumeNavigation: return "ResumeNavigation";
    case TctFuncCode::StartScript: return "StartScript";
    case TctFuncCode::StopScript: return "StopScript";
    case TctFuncCode::ExitScriptError: return "ExitScriptError";
    case TctFuncCode::GetScriptOutput: return "GetScriptOutput";
    case TctFuncCode::GetScriptList: return "GetScriptList";
    case TctFuncCode::GetScriptContent: return "GetScriptContent";
    case TctFuncCode::SaveScript: return "SaveScript";
    case TctFuncCode::DeleteScript: return "DeleteScript";
    case TctFuncCode::CheckScriptExists: return "CheckScriptExists";
    case TctFuncCode::GetEngineParams: return "GetEngineParams";
    case TctFuncCode::GetParamList: return "GetParamList";
    case TctFuncCode::SetUserParams: return "SetUserParams";
    case TctFuncCode::GetVaiable: return "GetVaiable";
    case TctFuncCode::GetMultipleVariables: return "GetMultipleVariables";
    case TctFuncCode::GetVariableList: return "GetVariableList";
    case TctFuncCode::SetVariable: return "SetVariable";
    case TctFuncCode::SetMultipleVariables: return "SetMultipleVariables";
    case TctFuncCode::GetModbusMemory: return "GetModbusMemory";
    case TctFuncCode::SetModbusMemory: return "SetModbusMemory";
    case TctFuncCode::SetModbusName: return "SetModbusName";
    case TctFuncCode::GetLogList: return "GetLogList";
    case TctFuncCode::GetLogData: return "GetLogData";
    case TctFuncCode::InitRobotConfig: return "InitRobotConfig";
    case TctFuncCode::SetJogSpeed: return "SetJogSpeed";
    case TctFuncCode::SetSensorConfig: return "SetSensorConfig";
    case TctFuncCode::GetRobotConfig: return "GetRobotConfig";
    case TctFuncCode::GetRobotSpecs: return "GetRobotSpecs";
    case TctFuncCode::ResetAlarm: return "ResetAlarm";
    case TctFuncCode::RestartEngine: return "RestartEngine";
    case TctFuncCode::Heartbeat: return "Heartbeat";
    case TctFuncCode::GetLocalizationLidar: return "GetLocalizationLidar";
    case TctFuncCode::GetCurrentPcd: return "GetCurrentPcd";
    case TctFuncCode::GetMapPcd: return "GetMapPcd";
    case TctFuncCode::SetRobotSpeed: return "SetRobotSpeed";
    case TctFuncCode::GetBridgeConfig: return "GetBridgeConfig";
    case TctFuncCode::SetBridgeConfig: return "SetBridgeConfig";
    case TctFuncCode::StartBridge: return "StartBridge";
    case TctFuncCode::StopBridge: return "StopBridge";
    case TctFuncCode::GetMasterInfo: return "GetMasterInfo";
    case TctFuncCode::SetVariableByCondition: return "SetVariableByCondition";
    case TctFuncCode::GetRealtimePcd: return "GetRealtimePcd";
    case TctFuncCode::GetTctFiles: return "GetTctFiles";
    case TctFuncCode::DeleteTctFile: return "DeleteTctFile";
    case TctFuncCode::CreateTctFile: return "CreateTctFile";
    case TctFuncCode::CreateTctDir: return "CreateTctDir";
    case TctFuncCode::GetMappingLidar: return "GetMappingLidar";
    case TctFuncCode::GetFileBinary: return "GetFileBinary";
    case TctFuncCode::SetMapFloor: return "SetMapFloor";
    case TctFuncCode::GetHighScan: return "GetHighScan";
    case TctFuncCode::GetLowScan: return "GetLowScan";
    case TctFuncCode::GetScanMerged: return "GetScanMerged";
    case TctFuncCode::ModifyVariable: return "ModifyVariable";
    case TctFuncCode::RequestYield: return "RequestYield";
    case TctFuncCode::GetDigitalIo: return "GetDigitalIo";
    case TctFuncCode::SetDigitalOutput: return "SetDigitalOutput";
    case TctFuncCode::SendMission: return "SendMission";
    case TctFuncCode::GetMissionStatus: return "GetMissionStatus";
    case TctFuncCode::DeleteMission: return "DeleteMission";
    case TctFuncCode::CancelMission: return "CancelMission";
    case TctFuncCode::FindPath: return "FindPath";
    default: return "UNKNOWN";
  }
};

enum class TctResponseCode
{
  Success = 1,  // 요청이 성공한 경우

  // General errors (-100000 ~ -100003)
  InvalidJsonFormat = -100000,  // 클라이언트의 요청이 json 형태가 아닌 프로토콜
  UndefinedProtocol = -100001,  // 클라이언트의 요청이 json 형태이지만 정의되지 않은 프로토콜
  InvalidKeyOrType =
      -100002,                  // 클라이언트에서 요청한 json에 필요한 key가 없거나 key의 데이터타입이 다른 경우
  InvalidValueRange = -100003,  // 클라이언트에서 요청한 json에 key의 value 값이 정의된 set 안에 없거나 허용
                                // 범위를 벗어나는 경우

  // State errors (-200000 ~ -200001)
  InvalidStateMachine = -200000,  // 해당 명령/프로토콜 수행하기에 적절하지 않은 스테이트 머신 상태
  InvalidDrivingState = -200001,  // 해당 명령/프로토콜 수행하기에 적절하지 않은 주행 상태

  // File operation errors (-300000 ~ -300004)
  FileSaveFailed        = -300000,  // 파일 저장에 실패
  FileReadFailed        = -300001,  // 파일 읽기에 실패
  FileCompressionFailed = -300002,  // 파일 압축에 실패, 또는 압축된 파일을 읽는데 실패
  FileDeleteFailed      = -300003,  // 파일/경로 삭제에 실패
  PathCreateFailed      = -300004,  // 경로 생성에 실패

  // Data read errors (-400000 ~ -400007)
  LidarReadFailed    = -400000,   // 라이다 데이터 읽기 실패
  MapInfoReadFailed  = -400001,   // 지도 정보(yaml 파일) 읽기 실패
  MapImageReadFailed = -400002,   // 지도 이미지 데이터(pgm 파일) 읽기 실패
  PlcReadFailed      = -400003,   // PLC 모드버스 코일/레지스터 읽기 실패
  PlcWriteFailed     = -400004,   // PLC 모드버스 코일/레지스터 쓰기 실패
  UserVarWriteFailed = -400005,   // 유저변수 값 쓰기 실패 (자료형이 맞지 않거나 해당 변수가 존재하지 않거나
                                  // 해당 자료형 허용 범위를 벗어남)
  CameraReadFailed    = -400006,  // 카메라 데이터 읽기 실패
  RobotInfoReadFailed = -400007,  // 다른 로봇 정보 읽기 실패 (구독한 다른 로봇 데이터가 json 형태가 아님)

  // SLAM errors (-500000 ~ -500001)
  MapNameExists      = -500000,  // SLAM을 위해 입력한 지도 이름이 이미 존재하는 경우
  SlamAlreadyRunning = -500001,  // SLAM을 실행 중에 다시 SLAM 시작 명령 내리는 경우

  // Map error
  MapNotExists = -600000,  // 지도가 존재하지 않는 경우

  // Service error
  ServiceCallFailed = -700000,  // service call 실패

  // Node/Edge errors (-800000 ~ -800011)
  NodeNameExists           = -800000,  // 같은 노드 이름이 이미 존재함
  NodeNameNotExists        = -800001,  // 노드 이름이 존재하지 않음
  NodeIdExists             = -800002,  // 노드 아이디가 이미 존재함
  NodeIdNotExists          = -800003,  // 노드 아이디가 존재하지 않음
  NodeIdEmpty              = -800004,  // 노드 아이디 값이 비어있음
  SelfLinkError            = -800005,  // 동일한 노드끼리의 링크
  ChargingStationLinkError = -800006,  // 충전스테이션으로 링크 시도
  EdgeAlreadyExists        = -800007,  // 이미 링크가 존재함
  EdgeNotExists            = -800008,  // 링크가 존재하지 않음
  NodeListNotExists        = -800009,  // 노드 리스트(벡터)가 존재하지 않음
  InvalidLinkType          = -800010,  // 유효하지 않은 링크 추가 시도 (엘레베이터-엘레베이터 연결 시도,
                                       // 지도변경-지도변경 연결 시도, 문-문 또는 자동문-자동문 1개 이상 연결 시도)
  CrossMapLinkError = -800011,         // 다른 지도 위 노드끼리 링크 추가 시도

  // Path finding error
  PathFindFailed = -800100,  // 패스파인드 경로 탐색 실패

  // Configuration errors (-900000 ~ -900003)
  NoJointInUrdf         = -900000,  // urdf 파일에 joint가 존재하지 않는 경우
  ConfigFileLoadFailed  = -900001,  // 환경설정을 위한 config 파일 불러오기에 실패
  InvalidFileFormat     = -900002,  // 읽어온 파일의 형식이 맞지 않음
  DrivingDbUpdateFailed = -900003,  // 주행 DB 업데이트/저장 실패

  // Device errors
  InvalidPlcDeviceId = -1000000,  // 존재하지 않는 PLC 장치 아이디

  // Bridge-Server communication errors (-2000000 ~ -2000002)
  MacAddressNotRegistered =
      -2000000,                      // 해당 MAC_ADDRESS가 TCT 테스트 서버의 robot_list.json에 없어서 서버 연결 확립 실패
  HandshakeNotCompleted = -2000001,  // TCT 브릿지와 TCT 테스트 서버가 아직 REQ_BRIDGE_HANDSHAKE를 성공하지
                                     // 않아 TCT 프로토콜 통신을 비허용
  BridgeInvalidProtocol = -2000002,  // TCT 브릿지의 요청이 json 형태이지만 정의되지 않은 프로토콜

  // TCT Master errors (-90000001 ~ -99999999)
  MissingRequiredParam  = -90000001,  // 필수 파라미터 없음
  MissingDataField      = -90000002,  // 데이터 필드 없음
  InvalidJson           = -90000003,  // JSON 형태가 아님
  UndefinedFunctionCode = -90000004,  // 정의된 FunctionCode 없음
  InvalidCompression    = -90000005,  // 데이터 압축형식이 맞지 않음
  UnknownError          = -99999999,  // 알 수 없는 에러

  // User related errors (-10000001 ~ -10000007)
  SessionExpired          = -10000001,  // 세션 만료됨
  SessionValidationFailed = -10000002,  // 세션 유효성 체크 실패
  AccountExists           = -10000006,  // 계정이 이미 존재함
  InvalidAccount          = -10000007,  // 계정 정보가 맞지 않음

  // External module errors (-10000100 ~ -10000103)
  ModuleConnectionFailed = -10000100,  // 모듈 연결 실패
  ModuleInitFailed       = -10000101,  // 모듈 초기화 실패
  DeviceNotExists        = -10000102,  // 장치 없음
  DataAlreadyExists      = -10000103,  // 데이터가 이미 존재함

  // Elevator errors (-10000201 ~ -10000209)
  ElevatorUnavailable  = -10000201,  // 엘레베이터 사용 불가
  CarrierCheckFailed   = -10000202,  // 배송체 확인 불가
  ElevatorCheckFailed  = -10000203,  // 엘레베이터 확인 불가
  FloorInfoError       = -10000204,  // 층 정보 에러
  ElevatorOccupied     = -10000205,  // 엘레베이터가 점유중임
  OccupiedKeyMismatch  = -10000206,  // 점유된 키가 다름
  RequestFailed        = -10000207,  // 요청 실패
  ElevatorNotOccupied  = -10000208,  // 엘레베이터 점유중이 아님
  InvalidElevatorState = -10000209,  // 엘레베이터를 탑승/하차 할 수 있는 상태가 아님

  // Door errors (-10000301 ~ -10000302)
  OperationNotPossible = -10000301,  // 수행 불가
  DoorCheckFailed      = -10000302,  // 해당 도어 확인 불가

  // Proxy error
  ProxyTargetUnreachable = -10001001,  // 프록시 대상 연결 확인 불가

  // Robot error
  RobotNotExists = -10002001,  // 해당 로봇 없음

  // Management errors (-10000401 ~ -10000403)
  ConnectionNotExists = -10000401,  // 커넥션 없음
  FnCodeNotExists     = -10000402,  // 매칭되는 FN_CODE 없음
  NotDataCollectionFn = -10000403,  // 해당 FN_CODE는 데이터 수집용이 아님

  // Node errors (-10000501 ~ -10000502)
  NodeAlreadyExists = -10000501,  // 노드가 이미 있음
  NodeNotFound      = -10000502,  // 해당 노드를 찾을 수 없음

  // Delete error
  DeleteCriteriaError = -10000601  // 삭제 기준 확인
};

inline std::string error_to_string(TctResponseCode code)
{
  switch(code)
  {
    case TctResponseCode::Success: return "요청이 성공한 경우";

    // General errors
    case TctResponseCode::InvalidJsonFormat: return "클라이언트의 요청이 json 형태가 아닌 프로토콜";
    case TctResponseCode::UndefinedProtocol:
      return "클라이언트의 요청이 json 형태이지만 정의되지 않은 프로토콜";
    case TctResponseCode::InvalidKeyOrType:
      return "클라이언트에서 요청한 json에 필요한 key가 없거나 key의 데이터타입이 다른 경우";
    case TctResponseCode::InvalidValueRange:
      return "클라이언트에서 요청한 json에 key의 value 값이 정의된 set 안에 없거나 허용 범위를 벗어나는 경우";

    // State errors
    case TctResponseCode::InvalidStateMachine:
      return "해당 명령/프로토콜 수행하기에 적절하지 않은 스테이트 머신 상태";
    case TctResponseCode::InvalidDrivingState: return "해당 명령/프로토콜 수행하기에 적절하지 않은 주행 상태";

    // File operation errors
    case TctResponseCode::FileSaveFailed: return "파일 저장에 실패";
    case TctResponseCode::FileReadFailed: return "파일 읽기에 실패";
    case TctResponseCode::FileCompressionFailed: return "파일 압축에 실패, 또는 압축된 파일을 읽는데 실패";
    case TctResponseCode::FileDeleteFailed: return "파일/경로 삭제에 실패";
    case TctResponseCode::PathCreateFailed: return "경로 생성에 실패";

    // Data read errors
    case TctResponseCode::LidarReadFailed: return "라이다 데이터 읽기 실패";
    case TctResponseCode::MapInfoReadFailed: return "지도 정보(yaml 파일) 읽기 실패";
    case TctResponseCode::MapImageReadFailed: return "지도 이미지 데이터(pgm 파일) 읽기 실패";
    case TctResponseCode::PlcReadFailed: return "PLC 모드버스 코일/레지스터 읽기 실패";
    case TctResponseCode::PlcWriteFailed: return "PLC 모드버스 코일/레지스터 쓰기 실패";
    case TctResponseCode::UserVarWriteFailed:
      return "유저변수 값 쓰기 실패 (자료형이 맞지 않거나 해당 변수가 존재하지 않거나 해당 자료형 허용 "
             "범위를 벗어남)";
    case TctResponseCode::CameraReadFailed: return "카메라 데이터 읽기 실패";
    case TctResponseCode::RobotInfoReadFailed:
      return "다른 로봇 정보 읽기 실패 (구독한 다른 로봇 데이터가 json 형태가 아님)";

    // SLAM errors
    case TctResponseCode::MapNameExists: return "SLAM을 위해 입력한 지도 이름이 이미 존재하는 경우";
    case TctResponseCode::SlamAlreadyRunning: return "SLAM을 실행 중에 다시 SLAM 시작 명령 내리는 경우";

    // Map error
    case TctResponseCode::MapNotExists: return "지도가 존재하지 않는 경우";

    // Service error
    case TctResponseCode::ServiceCallFailed: return "service call 실패";

    // Node/Edge errors
    case TctResponseCode::NodeNameExists: return "같은 노드 이름이 이미 존재함";
    case TctResponseCode::NodeNameNotExists: return "노드 이름이 존재하지 않음";
    case TctResponseCode::NodeIdExists: return "노드 아이디가 이미 존재함";
    case TctResponseCode::NodeIdNotExists: return "노드 아이디가 존재하지 않음";
    case TctResponseCode::NodeIdEmpty: return "노드 아이디 값이 비어있음";
    case TctResponseCode::SelfLinkError: return "동일한 노드끼리의 링크";
    case TctResponseCode::ChargingStationLinkError: return "충전스테이션으로 링크 시도";
    case TctResponseCode::EdgeAlreadyExists: return "이미 링크가 존재함";
    case TctResponseCode::EdgeNotExists: return "링크가 존재하지 않음";
    case TctResponseCode::NodeListNotExists: return "노드 리스트(벡터)가 존재하지 않음";
    case TctResponseCode::InvalidLinkType:
      return "유효하지 않은 링크 추가 시도 (엘레베이터-엘레베이터 연결 시도, 지도변경-지도변경 연결 시도, "
             "문-문 또는 자동문-자동문 1개 이상 연결 시도)";
    case TctResponseCode::CrossMapLinkError: return "다른 지도 위 노드끼리 링크 추가 시도";

    // Path finding error
    case TctResponseCode::PathFindFailed: return "패스파인드 경로 탐색 실패";

    // Configuration errors
    case TctResponseCode::NoJointInUrdf: return "urdf 파일에 joint가 존재하지 않는 경우";
    case TctResponseCode::ConfigFileLoadFailed: return "환경설정을 위한 config 파일 불러오기에 실패";
    case TctResponseCode::InvalidFileFormat: return "읽어온 파일의 형식이 맞지 않음";
    case TctResponseCode::DrivingDbUpdateFailed: return "주행 DB 업데이트/저장 실패";

    // Device errors
    case TctResponseCode::InvalidPlcDeviceId: return "존재하지 않는 PLC 장치 아이디";

    // Bridge-Server communication errors
    case TctResponseCode::MacAddressNotRegistered:
      return "해당 MAC_ADDRESS가 TCT 테스트 서버의 robot_list.json에 없어서 서버 연결 확립 실패";
    case TctResponseCode::HandshakeNotCompleted:
      return "TCT 브릿지와 TCT 테스트 서버가 아직 REQ_BRIDGE_HANDSHAKE를 성공하지 않아 TCT 프로토콜 통신을 "
             "비허용";
    case TctResponseCode::BridgeInvalidProtocol:
      return "TCT 브릿지의 요청이 json 형태이지만 정의되지 않은 프로토콜";

    // TCT Master errors
    case TctResponseCode::MissingRequiredParam: return "필수 파라미터 없음";
    case TctResponseCode::MissingDataField: return "데이터 필드 없음";
    case TctResponseCode::InvalidJson: return "JSON 형태가 아님";
    case TctResponseCode::UndefinedFunctionCode: return "정의된 FunctionCode 없음";
    case TctResponseCode::InvalidCompression: return "데이터 압축형식이 맞지 않음";
    case TctResponseCode::UnknownError: return "알 수 없는 에러";

    // User related errors
    case TctResponseCode::SessionExpired: return "세션 만료됨";
    case TctResponseCode::SessionValidationFailed: return "세션 유효성 체크 실패";
    case TctResponseCode::AccountExists: return "계정이 이미 존재함";
    case TctResponseCode::InvalidAccount: return "계정 정보가 맞지 않음";

    // External module errors
    case TctResponseCode::ModuleConnectionFailed: return "모듈 연결 실패";
    case TctResponseCode::ModuleInitFailed: return "모듈 초기화 실패";
    case TctResponseCode::DeviceNotExists: return "장치 없음";
    case TctResponseCode::DataAlreadyExists: return "데이터가 이미 존재함";

    // Elevator errors
    case TctResponseCode::ElevatorUnavailable: return "엘레베이터 사용 불가";
    case TctResponseCode::CarrierCheckFailed: return "배송체 확인 불가";
    case TctResponseCode::ElevatorCheckFailed: return "엘레베이터 확인 불가";
    case TctResponseCode::FloorInfoError: return "층 정보 에러";
    case TctResponseCode::ElevatorOccupied: return "엘레베이터가 점유중임";
    case TctResponseCode::OccupiedKeyMismatch: return "점유된 키가 다름";
    case TctResponseCode::RequestFailed: return "요청 실패";
    case TctResponseCode::ElevatorNotOccupied: return "엘레베이터 점유중이 아님";
    case TctResponseCode::InvalidElevatorState: return "엘레베이터를 탑승/하차 할 수 있는 상태가 아님";

    // Door errors
    case TctResponseCode::OperationNotPossible: return "수행 불가";
    case TctResponseCode::DoorCheckFailed: return "해당 도어 확인 불가";

    // Proxy error
    case TctResponseCode::ProxyTargetUnreachable: return "프록시 대상 연결 확인 불가";

    // Robot error
    case TctResponseCode::RobotNotExists: return "해당 로봇 없음";

    // Management errors
    case TctResponseCode::ConnectionNotExists: return "커넥션 없음";
    case TctResponseCode::FnCodeNotExists: return "매칭되는 FN_CODE 없음";
    case TctResponseCode::NotDataCollectionFn: return "해당 FN_CODE는 데이터 수집용이 아님";

    // Node errors
    case TctResponseCode::NodeAlreadyExists: return "노드가 이미 있음";
    case TctResponseCode::NodeNotFound: return "해당 노드를 찾을 수 없음";

    // Delete error
    case TctResponseCode::DeleteCriteriaError: return "삭제 기준 확인";

    default: return "알 수 없는 에러 코드: " + std::to_string(static_cast<int>(code));
  }
}

enum class TctAlarmCode
{
  NoAlarm   = 10,  // 알람이 아님 - 엔진에서 성공적으로 명령수행이 끝난 상태 (SUCCESS)
  Executing = 1,   // 알람이 아님 - 엔진에서 명령을 수행중인 상태 (EXECUTING)
  Unknown   = 0,   // TCT 소프트웨어에서 지정하지 않은 알람이 발생

  // (-1 ~ -9999)
  EngineResponse = -1,  // 자율주행소프트웨어의 응답 코드

  // Hardware Alarms
  EmsActivated = -20000,  // EMS(비상 정지 스위치) ON 감지

  // TCT Alarms (-100000 ~ -100003)
  ScriptRuntimeError = -100000,  // 스크립트 런타임 에러
  MapNodeReadError   = -100001,  // 지도의 노드 파일 읽기 실패
  MapDataReadError   = -100002,  // 지도의 파일 읽기 실패
  WrongNodeLink      = -100003,  // 지도상에서 잘못된 노드 엣지가 연결되어 있는 경우

  // Navigation Alarms
  ServiceCallTimeout = -110000,  // 서비스 호출 타임 아웃
  ScriptFileNotFound = -120000,  // 실행하려는 스크립트 파일이 존재하지 않음

  // Critical Alarms (-200000 ~ -200002)
  ConfigFileLoadFailed = -200000,  // TCT S/W 설정 파일 읽기 실패
  InitializeFailed     = -200001,  // TCT S/W 초기화 실패 (로봇의 재부팅이 필요)
  EngineStartFailed    = -200002,  // 자율주행 S/W 시작 실패

  // Engine Alarms (-210000 ~ -210001)
  EngineOffFailed = -210000,  // TCT S/W 재시작시, 자율주행엔진 S/W OFF 실패
  EngineError     = -210001,  // 자율주행 S/W 에러 발생

  // PLC Alarms (-220000 ~ -220003)
  PlcDisconnected   = -220000,  // PLC 장치 통신 연결 해제 (로봇의 재부팅이 필요)
  TopModuleAlarm    = -220001,  // 탑 모듈 알람 발생
  TopModuleAbnormal = -220002,  // 탑 모듈 비정상 상태
  PlcConnectionFail = -220003,  // PLC 연결 실패 (로봇의 재부팅이 필요)

  // Hardware Switch Alarm
  HwSwitchDisconnected = -230000,  // 하드웨어 스위치 통신 연결 해제

  // Sensor Alarms (-240000 ~ -240007)
  Lidar3dDisconnected          = -240000,  // 3D 라이다 통신 연결 해제
  Lidar2dFrontDisconnected     = -240001,  // 2D 전면 라이다 통신 연결 해제
  Lidar2dRearDisconnected      = -240002,  // 2D 후면 라이다 통신 연결 해제
  DepthCameraFrontDisconnected = -240003,  // 전면 뎁스 카메라 통신 연결 해제
  DepthCameraRearDisconnected  = -240004,  // 후면 뎁스 카메라 통신 연결 해제
  MotorDriverDisconnected      = -240005,  // 모터 드라이버 통신 연결 해제
  ImuDisconnected              = -240006,  // IMU 센서 통신 연결 해제
  TofDisconnected              = -240007,  // TOF 센서 통신 연결 해제

  // Network Hub Alarms (-250000 ~ -250001)
  NetworkHubStationDisconnected = -250000,  // AP 공유기 통신 연결 해제
  NetworkHubClientDisconnected  = -250001   // Client 공유기 통신 연결 해제
};

inline std::string alarm_to_string(TctAlarmCode code)
{
  switch(code)
  {
    case TctAlarmCode::NoAlarm: return "알람이 아님 - 엔진에서 성공적으로 명령수행이 끝난 상태 (SUCCESS)";
    case TctAlarmCode::Executing: return "알람이 아님 - 엔진에서 명령을 수행중인 상태 (EXECUTING)";
    case TctAlarmCode::Unknown: return "TCT 소프트웨어에서 지정하지 않은 알람이 발생";
    case TctAlarmCode::EngineResponse: return "자율주행소프트웨어의 응답 코드";
    case TctAlarmCode::EmsActivated: return "EMS(비상 정지 스위치) ON 감지";
    case TctAlarmCode::ScriptRuntimeError: return "스크립트 런타임 에러";
    case TctAlarmCode::MapNodeReadError: return "지도의 노드 파일 읽기 실패";
    case TctAlarmCode::MapDataReadError: return "지도의 파일 읽기 실패";
    case TctAlarmCode::WrongNodeLink: return "지도상에서 잘못된 노드 엣지가 연결되어 있는 경우";
    case TctAlarmCode::ServiceCallTimeout: return "서비스 호출 타임 아웃";
    case TctAlarmCode::ScriptFileNotFound: return "실행하려는 스크립트 파일이 존재하지 않음";
    case TctAlarmCode::ConfigFileLoadFailed: return "TCT S/W 설정 파일 읽기 실패";
    case TctAlarmCode::InitializeFailed: return "TCT S/W 초기화 실패 (로봇의 재부팅이 필요)";
    case TctAlarmCode::EngineStartFailed: return "자율주행 S/W 시작 실패";
    case TctAlarmCode::EngineOffFailed: return "TCT S/W 재시작시, 자율주행엔진 S/W OFF 실패";
    case TctAlarmCode::EngineError: return "자율주행 S/W 에러 발생";
    case TctAlarmCode::PlcDisconnected: return "PLC 장치 통신 연결 해제 (로봇의 재부팅이 필요)";
    case TctAlarmCode::TopModuleAlarm: return "탑 모듈 알람 발생";
    case TctAlarmCode::TopModuleAbnormal: return "탑 모듈 비정상 상태";
    case TctAlarmCode::PlcConnectionFail: return "PLC 연결 실패 (로봇의 재부팅이 필요)";
    case TctAlarmCode::HwSwitchDisconnected: return "하드웨어 스위치 통신 연결 해제";
    case TctAlarmCode::Lidar3dDisconnected: return "3D 라이다 통신 연결 해제";
    case TctAlarmCode::Lidar2dFrontDisconnected: return "2D 전면 라이다 통신 연결 해제";
    case TctAlarmCode::Lidar2dRearDisconnected: return "2D 후면 라이다 통신 연결 해제";
    case TctAlarmCode::DepthCameraFrontDisconnected: return "전면 뎁스 카메라 통신 연결 해제";
    case TctAlarmCode::DepthCameraRearDisconnected: return "후면 뎁스 카메라 통신 연결 해제";
    case TctAlarmCode::MotorDriverDisconnected: return "모터 드라이버 통신 연결 해제";
    case TctAlarmCode::ImuDisconnected: return "IMU 센서 통신 연결 해제";
    case TctAlarmCode::TofDisconnected: return "TOF 센서 통신 연결 해제";
    case TctAlarmCode::NetworkHubStationDisconnected: return "AP 공유기 통신 연결 해제";
    case TctAlarmCode::NetworkHubClientDisconnected: return "Client 공유기 통신 연결 해제";
    default: return "알 수 없는 알람 코드";
  }
}

// TCT 하위 모드 (스테이트 머신 상태)
enum class TctStateMode
{
  Unknown         = 99,
  Initializing    = 100,  // 초기화 중
  Stopped         = 101,  // 정지
  ManualReady     = 102,  // 티칭 대기
  ManualMoving    = 103,  // 티칭 주행 중
  ManualJogging   = 104,  // 조그 주행 중
  ManualMapping   = 105,  // 지도 작성 중
  AutoReady       = 106,  // 스크립트 준비
  AutoCheck       = 107,  // 스크립트 확인 중
  AutoSyntaxError = 108,  // 스크립트 구문 에러
  AutoRunning     = 109,  // 스크립트 수행 중
  AutoCancel      = 110,  // 스크립트 취소
  AutoComplete    = 111,  // 스크립트 완료
  Alarm           = 112,  // 알람
  TctStateModeEnd,
};

inline std::string mode_state_to_string(TctStateMode mode)
{
  switch(mode)
  {
    case TctStateMode::Initializing: return "INITIALIZING";
    case TctStateMode::Stopped: return "STOPPED";
    case TctStateMode::ManualReady: return "MANUAL_READY";
    case TctStateMode::ManualMoving: return "MANUAL_MOVING";
    case TctStateMode::ManualJogging: return "MANUAL_JOGGING";
    case TctStateMode::ManualMapping: return "MANUAL_MAPPING";
    case TctStateMode::AutoReady: return "AUTO_READY";
    case TctStateMode::AutoCheck: return "AUTO_CHECK";
    case TctStateMode::AutoSyntaxError: return "AUTO_SYNTAX_ERROR";
    case TctStateMode::AutoRunning: return "AUTO_RUNNING";
    case TctStateMode::AutoCancel: return "AUTO_CANCEL";
    case TctStateMode::AutoComplete: return "AUTO_COMPLETE";
    case TctStateMode::Alarm: return "ALARM";
    default: return "UNKNOWN";
  }
}

inline TctStateMode string_to_mode_state(const std::string& mode)
{
  if(mode == "INITIALIZING") return TctStateMode::Initializing;
  if(mode == "STOPPED") return TctStateMode::Stopped;
  if(mode == "MANUAL_READY") return TctStateMode::ManualReady;
  if(mode == "MANUAL_MOVING") return TctStateMode::ManualMoving;
  if(mode == "MANUAL_JOGGING") return TctStateMode::ManualJogging;
  if(mode == "MANUAL_MAPPING") return TctStateMode::ManualMapping;
  if(mode == "AUTO_READY") return TctStateMode::AutoReady;
  if(mode == "AUTO_CHECK") return TctStateMode::AutoCheck;
  if(mode == "AUTO_SYNTAX_ERROR") return TctStateMode::AutoSyntaxError;
  if(mode == "AUTO_RUNNING") return TctStateMode::AutoRunning;
  if(mode == "AUTO_CANCEL") return TctStateMode::AutoCancel;
  if(mode == "AUTO_COMPLETE") return TctStateMode::AutoComplete;
  if(mode == "ALARM") return TctStateMode::Alarm;
  return TctStateMode::Unknown;
}

// 자율주행 엔진의 노드 상태
enum class EngineNodeState
{
  Unknown = 113,
  Normal  = 114,  // 정상
  Loading = 115,  // 로딩 중
  Off     = 116,  // 꺼짐
  Error   = 117,  // 에러
  EngineNodeStateEnd,
};

inline std::string node_state_to_string(EngineNodeState state)
{
  switch(state)
  {
    case EngineNodeState::Normal: return "NORMAL";
    case EngineNodeState::Loading: return "LOADING";
    case EngineNodeState::Off: return "OFF";
    case EngineNodeState::Error: return "ERROR";
    default: return "UNKNOWN";
  }
}

inline EngineNodeState string_to_node_state(const std::string& state)
{
  if(state == "NORMAL") return EngineNodeState::Normal;
  if(state == "LOADING") return EngineNodeState::Loading;
  if(state == "OFF") return EngineNodeState::Off;
  if(state == "ERROR") return EngineNodeState::Error;
  return EngineNodeState::Unknown;
}

// 로봇의 주행 상태
enum class DrivingState
{
  Unknown = 118,
  Moving  = 119,  // 주행 중
  Blocked = 120,  // 장애물 막힘
  Idle    = 121,  // 대기
  Paused  = 122,  // 주행 일시 정지
  DrivingStateEnd,
};

inline std::string driving_state_to_string(DrivingState state)
{
  switch(state)
  {
    case DrivingState::Moving: return "MOVING";
    case DrivingState::Blocked: return "BLOCKED";
    case DrivingState::Idle: return "IDLE";
    case DrivingState::Paused: return "PAUSED";
    default: return "UNKNOWN";
  }
}

inline DrivingState string_to_driving_state(const std::string& state)
{
  if(state == "MOVING") return DrivingState::Moving;
  if(state == "BLOCKED") return DrivingState::Blocked;
  if(state == "IDLE") return DrivingState::Idle;
  if(state == "PAUSED") return DrivingState::Paused;
  return DrivingState::Unknown;
}

// 로봇의 위치추정 상태
enum class LocalizationState
{
  Unknown      = 123,
  NotLocalized = 124,  // 위치추정 해제
  Localized    = 125,  // 위치추정 중
  LocalizationStateEnd,
};

inline std::string localization_state_to_string(LocalizationState state)
{
  switch(state)
  {
    case LocalizationState::NotLocalized: return "NOT_LOCALIZED";
    case LocalizationState::Localized: return "LOCALIZED";
    default: return "Unknown";
  }
}

inline LocalizationState string_to_localization_state(const std::string& state)
{
  if(state == "NOT_LOCALIZED") return LocalizationState::NotLocalized;
  if(state == "LOCALIZED") return LocalizationState::Localized;
  return LocalizationState::Unknown;
}

// 센서 상태
enum class SensorState
{
  Unknown  = 126,
  Unstable = 127,  // 불안정
  Stable   = 128,  // 안정
  Disabled = 129,  // 비활성
  SensorStateEnd,
};

inline std::string sensor_state_to_string(SensorState state)
{
  switch(state)
  {
    case SensorState::Unstable: return "UNSTABLE";
    case SensorState::Stable: return "STABLE";
    case SensorState::Disabled: return "DISABLED";
    default: return "UNKNOWN";
  }
}

inline SensorState string_to_sensor_state(const std::string& state)
{
  if(state == "UNSTABLE") return SensorState::Unstable;
  if(state == "STABLE") return SensorState::Stable;
  if(state == "DISABLED") return SensorState::Disabled;
  return SensorState::Unknown;
}

inline std::string float_to_string(const float& value)
{
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3) << value;
  return ss.str();
}

}  // namespace frb
