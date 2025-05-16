//
// Created by kan02 on 2025-05-12.
//

#ifndef BROADCAST_H
#define BROADCAST_H
#include <string>


class BroadCast {
  public:
    BroadCast();
    ~BroadCast();
    std::string broadCast(const std::string &ip, int port, const std::string &message);
};



#endif //BROADCAST_H
