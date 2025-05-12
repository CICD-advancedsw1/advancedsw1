//
// Created by kan02 on 2025-05-12.
//

#ifndef PURCHASEHANDLER_H
#define PURCHASEHANDLER_H
#include <string>
#include <utility>
#include "../../infrastructure/PaymentSystem.h"
#include "../../common/data/Beverage.h"
#include "../../application/domain/Inventory.h"

class PurchaseHandler {
  private:
    PaymentSystem *paymentSystem;
    Inventory* inventory;
  public:
    PurchaseHandler(PaymentSystem *p, Inventory *i);
    std::pair<bool, std::string> purchase(std::string cardNumber, Beverage* beverage, int qty);
};


#endif //PURCHASEHANDLER_H
