//
// Created by kan02 on 2025-05-12.
//

#ifndef PREPAYMENTHANDLER_H
#define PREPAYMENTHANDLER_H
#include <string>
#include <vector>

#include "../../infrastructure/BroadCastImpl.h"
#include "../domain/Inventory.h"
#include "../domain/repository/CertificationCodeRepository.h"


class ResponseStock;
class Beverage;
class PrepaymentHandler {
  private:
    BroadCast* broadCast;
    CertificationCodeRepository* certificationCodeRepository;
    Inventory* inventory;
    std::vector<std::pair<std::string, int>> Cert_code;
  public:
    PrepaymentHandler(BroadCast* broadCast, CertificationCodeRepository* certificationCodeRepository, Inventory* inventory);
    ~PrepaymentHandler();
    ResponseStock *findAvailableDVM(Beverage *beverage, int qty);
    std::string generateCertificationCode(int length);
    void EraseCode(std::string code);
    bool handlePrepaymentRequest(std::string certCode, int itemCode, int qty);
    bool rollBackPrepaymentRequest(std::string certCode, int itemCode, int qty);
    double findDistance(int x, int y);
    std::pair<int,int> PrePaymentCheck(std::string code);
    std::string makeRequestStockMessage(int code, int qty);
    std::string makeRequestPrepaymentMessage(std::string certCode,
                                             int itemCode,
                                             int qty,
                                             std::string dstId);
    std::pair<bool, std::string> prepaymentRequest(Beverage *beverage,
                                                   int qty,
                                                   std::string dstIp,
                                                   std::string dstId);
    bool IsvalidCode(std::string code);
};



#endif //PREPAYMENTHANDLER_H
