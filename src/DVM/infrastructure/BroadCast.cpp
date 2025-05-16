//
// Created by kan02 on 2025-05-12.
//

#include "BroadCast.h"

#include "../common/data/DVMNetworkData.h"
#pragma comment(lib, "ws2_32.lib")

#define WIN32_LEAN_AND_MEAN  // 줄일 수 있는 헤더만 포함
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

BroadCast::BroadCast() {
}
BroadCast::~BroadCast() {
}
std::string BroadCast::broadCast(const string &ip, int port, const string &message) {
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "[WSA Error] Failed to initialize Winsock" << std::endl;
    return "";
  }

  SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == INVALID_SOCKET) {
    std::cerr << "[Socket Error] Cannot create socket" << std::endl;
    WSACleanup();
    return "";
  }

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

  if (connect(sock, (sockaddr *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    std::cerr << "[Connect Error] Cannot connect to " << ip << std::endl;
    closesocket(sock);
    WSACleanup();
    return "";
  }

  send(sock, message.c_str(), static_cast<int>(message.length()), 0);

  char buffer[1024] = {0};
  int len = recv(sock, buffer, sizeof(buffer), 0);

  closesocket(sock);
  WSACleanup();

  if (len > 0) {
    return std::string(buffer, len);
  }

  return "";
}
