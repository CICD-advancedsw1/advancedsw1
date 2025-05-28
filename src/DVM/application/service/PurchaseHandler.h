//
// Created by kan02 on 2025-05-12.
//

#ifndef PURCHASEHANDLER_H
#define PURCHASEHANDLER_H
#include <string>
#include <utility>
#include "../../common/data/Beverage.h"
#include "../../application/domain/Inventory.h"
#include "../domain/repository/PaymentSystem.h"

class PurchaseHandler {
  private:
    PaymentSystem *paymentSystem;
    Inventory* inventory;
  public:
    PurchaseHandler(PaymentSystem *p, Inventory *i);
    std::pair<bool, std::string> purchase(std::string cardNumber, Beverage* beverage, int qty);
    bool isValidCardFormat(const std::string &cardNumber);
};


#endif //PURCHASEHANDLER_H
