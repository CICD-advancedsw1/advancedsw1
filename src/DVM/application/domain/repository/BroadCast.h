//
// Created by user on 25. 5. 18.
//

#ifndef BROADCAST_H
#define BROADCAST_H

#include <string>

class BroadCast {
  public:
    virtual ~BroadCast() = default;
    virtual std::string broadCast(const std::string &ip, int port, const std::string &message) = 0;
};

#endif //BROADCAST_H