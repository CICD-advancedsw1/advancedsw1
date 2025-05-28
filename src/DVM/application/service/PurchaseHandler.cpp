//
// Created by kan02 on 2025-05-12.
//

#include "PurchaseHandler.h"

#include <iostream>
#include <regex>
#include <string>
#include <utility>


PurchaseHandler::PurchaseHandler(PaymentSystem *p, Inventory *i):paymentSystem(p), inventory(i) {
}
std::pair<bool, std::string> PurchaseHandler::purchase(std::string cardNumber, Beverage* beverage, int qty) {
  if (!isValidCardFormat(cardNumber)) {
    return {false, "카드 형식이 잘못되었습니다."};
  }
  std::pair<bool, std::string> result = paymentSystem->connectSystem(cardNumber, beverage->getPrice()*qty);
  if (!result.first) {
    return result;
  }
  inventory->decreaseStock(beverage->getCode(), qty);
  return result;
}

bool PurchaseHandler::isValidCardFormat(const std::string& cardNumber) {
  // 허용 포맷: 16자리 숫자 or "1234-5678-9012-3456" 형식
  std::regex simpleFormat("^\\d{16}$");
  std::regex hyphenFormat("^\\d{4}-\\d{4}-\\d{4}-\\d{4}$");
  return std::regex_match(cardNumber, simpleFormat) || std::regex_match(cardNumber, hyphenFormat);
}