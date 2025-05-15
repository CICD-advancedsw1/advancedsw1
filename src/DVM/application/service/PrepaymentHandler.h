//
// Created by kan02 on 2025-05-12.
//

#ifndef PREPAYMENTHANDLER_H
#define PREPAYMENTHANDLER_H
#include <string>
#include <vector>

#include "../../infrastructure/BroadCast.h"


class Beverage;
class PrepaymentHandler {
  private:
    BroadCast* broadCast;
    std::vector<std::pair<std::string, int>> Cert_code;
  public:
    PrepaymentHandler(BroadCast* broadCast);
    ~PrepaymentHandler();
    std::string findAvailableDVM(Beverage* beverage, int qty);
    void EraseCode(std::string code);
    int PrePaymentCheck(std::string code);
    //stockCode();
};



#endif //PREPAYMENTHANDLER_H
