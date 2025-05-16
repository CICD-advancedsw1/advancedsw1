//
// Created by kan02 on 2025-05-12.
//

#ifndef PREPAYMENTHANDLER_H
#define PREPAYMENTHANDLER_H
#include <string>
#include <vector>

#include "../../infrastructure/BroadCast.h"


class ResponseStock;
class Beverage;
class PrepaymentHandler {
  private:
    BroadCast* broadCast;
    double findDistance(int x, int y);
    std::string generateCertificationCode(int length);
    std::vector<std::pair<std::string, int>> Cert_code;
  public:
    PrepaymentHandler(BroadCast* broadCast);
    ~PrepaymentHandler();
    ResponseStock *findAvailableDVM(Beverage *beverage, int qty);
    void EraseCode(std::string code);
    int PrePaymentCheck(std::string code);
    std::string makeRequestStockMessage(int code, int qty);
    std::string makeRequestPrepaymentMessage(std::string certCode,
                                             int itemCode,
                                             int qty,
                                             std::string dstId);
    std::pair<bool, std::string> prepaymentRequest(Beverage *beverage,
                                                   int qty,
                                                   std::string dstIp,
                                                   std::string dstId);
    //stockCode();
};



#endif //PREPAYMENTHANDLER_H
