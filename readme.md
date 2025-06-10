# FieldRo TCT Websocket Bridge PRD

![ROS Topic Browser Screenshot](src/fieldro_utility/document/picture/fieldro_utility_Architecture_dark.png)

## 1. 개요
TCT(Twin Control Technology) 웹소켓 브릿지는 ROS 기반 로봇 시스템과 웹소켓 클라이언트 간의 통신을 처리하는 중계 시스템

## 2. 핵심 기능

### 2.1 웹소켓 통신
- 웹소켓 서버 연결 (ws://127.0.0.1:5435)
- 클라이언트 연결 상태 관리
- JSON 기반 메시지 전송

### 2.2 로봇 제어 기능
- 조그 모드 전환 및 제어
- 경로 계획 및 네비게이션
- 장애물 회피 주행
- 비회피 주행
- 경로 주행
- 도킹/언도킹 제어
- 스크립트 관리 및 실행

### 2.3 시스템 모니터링
- ROS 노드 상태 모니터링
- 로봇 위치 정보 관리
- 스크립트 실행 상태 관리

## 3. 기술 명세

### 3.1 개발 환경
- C++11 이상
- ROS 기반
- CMake 빌드 시스템

### 3.2 의존성
ROS 패키지:
- geometry_msgs
- nav_msgs
- roscpp
- sensor_msgs
- std_msgs
- message_runtime

## 4. 오류 처리
```bash
응답 코드 체계:
- Success (1): 정상 처리
- InvalidJsonFormat (-100000): 잘못된 JSON 형식
- UndefinedProtocol (-100001): 정의되지 않은 프로토콜
- InvalidKeyOrType (-100002): 잘못된 키 또는 데이터 타입
```

## 5. 로깅
- 시간 기반 로그 기록 (YYYY-MM-DD_HH:MM:SS 형식)
- 이벤트 레벨 로깅 (정보, 오류)
- 로그 저장 위치: fieldro_utility

## 6. 보안
- 로컬호스트 기반 통신
- 웹소켓 연결 인증 시스템
- 명령어 유효성 검증