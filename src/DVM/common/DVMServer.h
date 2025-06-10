//
// Created by kan02 on 2025-05-16.
//

#ifndef DVMSERVER_H
#define DVMSERVER_H

#include <string>
#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>


#ifdef _WIN32
#include <ws2tcpip.h>
#endif

#include <winsock2.h>

#include"../../../include/nlohmann/json.hpp"

class PrepaymentHandler;
class Inventory;
using namespace std;

class DVMServer {
  private:
    int serverFd;
    int port;
    Inventory* inventory;
    PrepaymentHandler* prepaymentHandler;
    void handleClient(int clientFd);
    string makeResponseStock(nlohmann::json jsonReq);
    string makeResponsePrepay(nlohmann::json jsonReq);

  public:
    DVMServer(Inventory* inventory, PrepaymentHandler* prepaymentHandler);
    void run();

};



#endif //DVMSERVER_H
