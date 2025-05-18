//
// Created by kan02 on 2025-05-12.
//

#include "PurchaseHandler.h"

#include <iostream>
#include <string>
#include <utility>


PurchaseHandler::PurchaseHandler(PaymentSystem *p, Inventory *i):paymentSystem(p), inventory(i) {
}
std::pair<bool, std::string> PurchaseHandler::purchase(std::string cardNumber, Beverage* beverage, int qty) {
  std::pair<bool, std::string> result = paymentSystem->connectSystem(cardNumber, beverage->getPrice()*qty);
  if (!result.first) {
    return result;
  }
  inventory->decreaseStock(beverage->getCode(), qty);
  return result;
}

