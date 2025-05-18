//
// Created by kan02 on 2025-05-12.
//

#ifndef BROADCASTIMPL_H
#define BROADCASTIMPL_H
#include <string>

#include "../application/domain/repository/BroadCast.h"


class BroadCastImpl : public BroadCast {
  public:
    explicit BroadCastImpl();
    ~BroadCastImpl();
    std::string broadCast(const std::string &ip, int port, const std::string &message) override;
};



#endif //BROADCAST_H
