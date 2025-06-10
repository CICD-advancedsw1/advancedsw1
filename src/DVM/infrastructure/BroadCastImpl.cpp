//
// Created by kan02 on 2025-05-12.
//

#include "BroadCastImpl.h"

#include "../common/data/DVMNetworkData.h"
#pragma comment(lib, "ws2_32.lib")

#define WIN32_LEAN_AND_MEAN  // 줄일 수 있는 헤더만 포함




#ifdef _WIN32
#include <ws2tcpip.h>
#endif


#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  // Optional: link library on MSVC
typedef SOCKET socket_t;
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int socket_t;
#endif




#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

BroadCastImpl::BroadCastImpl() {
}
BroadCastImpl::~BroadCastImpl() {
}
std::string BroadCastImpl::broadCast(const string &ip, int port, const string &message) {
  #ifdef _WIN32
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "[WSA Error] Failed to initialize Winsock" << std::endl;
    return "";
  }
#endif

  

  //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  socket_t sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  /* if (sock == INVALID_SOCKET) {
    std::cerr << "[Socket Error] Cannot create socket" << std::endl;
    WSACleanup();
    return "";
  }*/

  #ifdef _WIN32
    if (sock == INVALID_SOCKET) {
        std::cerr << "[Socket Error] Cannot create socket (Windows)" << std::endl;
        WSACleanup();
        return "";
    }
#else
    if (sock == -1) {
        std::cerr << "[Socket Error] Cannot create socket (Linux)" << std::endl;
        return "";
    }
#endif




  

  

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

  /* 
  if (connect(sock, (sockaddr *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    closesocket(sock);
    WSACleanup();
    return "";
  } 
  */

  #ifdef _WIN32
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "[Connect Error] Windows socket error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return "";
    }
#else
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("[Connect Error]");
        close(sock);
        return "";
    }
#endif



  

  

  send(sock, message.c_str(), static_cast<int>(message.length()), 0);

  char buffer[1024] = {0};
  int len = recv(sock, buffer, sizeof(buffer), 0);

  //closesocket(sock);
  #ifdef _WIN32
    closesocket(sock);
  #else
    close(sock);
  #endif


  
  //WSACleanup();
  #ifdef _WIN32
    WSACleanup();
  #endif

  if (len > 0) {
    return std::string(buffer, len);
  }

  return "";
}
