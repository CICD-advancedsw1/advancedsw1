//
// Created by kan02 on 2025-05-12.
//

#ifndef PREPAYMENTHANDLER_H
#define PREPAYMENTHANDLER_H
#include <string>

#include "../../infrastructure/BroadCast.h"


class Beverage;
class PrepaymentHandler {
  private:
    BroadCast* broadCast;
  public:
    PrepaymentHandler(BroadCast* broadCast);
    ~PrepaymentHandler();
    std::string findAvailableDVM(Beverage* beverage, int qty);
    //stockCode();
};



#endif //PREPAYMENTHANDLER_H
