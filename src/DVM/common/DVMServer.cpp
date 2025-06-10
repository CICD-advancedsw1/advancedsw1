//
// Created by kan02 on 2025-05-16.
//

#include "DVMServer.h"
//#include <winsock2.h>
//#pragma comment(lib, "ws2_32.lib") // MSVC일 때만 필요, MinGW에서는 자동 연결


#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#define WSAStartup(a, b) ((void)0)
#define WSACleanup() ((void)0)
#endif





#include "../application/domain/Inventory.h"
#include "../application/service/PrepaymentHandler.h"
#include "data/DVMNetworkData.h"

using json = nlohmann::json;

void DVMServer::handleClient(int clientFd) {
  char buffer[1024];

  // 클라이언트 메시지 읽기
  int len = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
  if (len > 0) {
    buffer[len] = '\0'; // 문자열 종료
    std::string request(buffer);

    // 요청 처리 및 응답 생성
    json jsonReq = json::parse(request);
    string response;
    if (jsonReq["msg_type"] == "req_stock") {
      response = makeResponseStock(jsonReq);
    }
    else if (jsonReq["msg_type"] == "req_prepay") {
      response = makeResponsePrepay(jsonReq);
    }
    else {
      response = R"({"error": "Unknown msg_type"})";
    }

    // 응답 전송 (전송 실패 시 로그 출력)
    if (send(clientFd, response.c_str(), response.size(), 0) == -1) {
      perror("[DVMServer] 응답 전송 실패");

      string itemCode = jsonReq["msg_content"]["item_code"];
      int qty = jsonReq["msg_content"]["item_num"];
      string certCode = jsonReq["msg_content"]["cert_code"];
      prepaymentHandler->rollBackPrepaymentRequest(certCode, stoi(itemCode), qty);
    }
  }

  // 연결 종료
  close(clientFd);
}

string DVMServer::makeResponseStock(json jsonReq) {
  string itemCode = jsonReq["msg_content"]["item_code"];
  // 응답 JSON 구성
  json resp;
  resp["msg_type"] = "resp_stock";
  resp["src_id"] = DVMNetworkData::getDVMId(); // 응답하는 자판기
  resp["dst_id"] = jsonReq["src_id"]; // 요청했던 자판기로 응답
  resp["msg_content"] = {
    {"item_code", itemCode},
    {"item_num", inventory->getBeverage(stoi(itemCode))->getStock()},
    {"coor_x", DVMNetworkData::getX()},
    {"coor_y", DVMNetworkData::getY()}
  };

  return resp.dump(); // 문자열로 변환
}

string DVMServer::makeResponsePrepay(json jsonReq) {
  string itemCode = jsonReq["msg_content"]["item_code"];
  int qty = jsonReq["msg_content"]["item_num"];
  string certCode = jsonReq["msg_content"]["cert_code"];
  string availability = "T";
  if (!prepaymentHandler->handlePrepaymentRequest(certCode, stoi(itemCode), qty)) {
    availability = "F";
  }

  // 응답 JSON 구성
  json resp;
  resp["msg_type"] = "resp_prepay";
  resp["src_id"] = DVMNetworkData::getDVMId(); // 응답하는 자판기
  resp["dst_id"] = jsonReq["src_id"]; // 요청했던 자판기로 응답
  resp["msg_content"] = {
    {"item_code", itemCode},
    {"item_num", qty},
    {"availability", availability}
  };

  return resp.dump(); // 문자열로 변환
}

DVMServer::DVMServer(Inventory* inventory, PrepaymentHandler* prepaymentHandler) {
  this->port = DVMNetworkData::getServerPort();
  this->inventory = inventory;
  this->prepaymentHandler = prepaymentHandler;
}

void DVMServer::run() {
  //WSADATA wsaData;
  //WSAStartup(MAKEWORD(2, 2), &wsaData);
  #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
  #endif

  
  

  serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd == -1) {
    perror("[DVMServer] 소켓 초기화 실패");
    return;
  }

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  if (bind(serverFd, (sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("[DVMServer] 소켓 바인드 실패");
    close(serverFd);
    return;
  }

  if (listen(serverFd, 5) == -1) {
    perror("[DVMServer] 소켓 Listen 실패");
    close(serverFd);
    return;
  }

  std::cout << "\n[DVMServer] Listening on port " << port << "...\n";

  // 무한 루프: 클라이언트 연결 수락
  while (true) {
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    // 클라이언트 연결 수락
    int clientFd = accept(serverFd, (sockaddr*)&clientAddr, &clientLen);
    if (clientFd == -1) {
      perror("[DVMServer] 클라이언트 연결 실패");
      continue;
    }
    handleClient(clientFd);
  }
}
