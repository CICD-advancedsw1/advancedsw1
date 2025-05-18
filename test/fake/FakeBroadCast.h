//
// Created by user on 25. 5. 18.
//

#ifndef FAKEBROADCAST_H
#define FAKEBROADCAST_H
#include "../../src/DVM/application/domain/repository/BroadCast.h"

class FakeBroadCast : public BroadCast {
  public:
    std::map<std::string, std::string> ipToResponse;

    std::string broadCast(const std::string& ip, int port, const std::string& message) override {
      if (!ipToResponse.at(ip).empty()) {
        return ipToResponse[ip];
      }
      return "";
    }
};
#endif //FAKEBROADCAST_H
