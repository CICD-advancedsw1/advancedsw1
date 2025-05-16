//
// Created by kan02 on 2025-05-12.
//

#ifndef PREPAYMENTHANDLER_H
#define PREPAYMENTHANDLER_H
#include <string>

#include "../../infrastructure/BroadCast.h"


class ResponseStock;
class Beverage;
class PrepaymentHandler {
  private:
    BroadCast* broadCast;
    double findDistance(int x, int y);
    std::string generateCertificationCode(int length);

  public:
    PrepaymentHandler(BroadCast* broadCast);
    ~PrepaymentHandler();
    std::string makeRequestStockMessage(int code, int qty);
    std::string makeRequestPrepaymentMessage(std::string certCode,
                                             int itemCode,
                                             int qty,
                                             std::string dstId);
    std::pair<bool, std::string> prepaymentRequest(Beverage *beverage,
                                                   int qty,
                                                   std::string dstIp,
                                                   std::string dstId);
    ResponseStock* findAvailableDVM(Beverage* beverage, int qty);
    //stockCode();
};



#endif //PREPAYMENTHANDLER_H
