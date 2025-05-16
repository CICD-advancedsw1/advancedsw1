//
// Created by kan02 on 2025-05-12.
//

#include "Inventory.h"

#include <iostream>

Inventory::Inventory(BeverageRepository *beverageRepository): beverageRepository(
  beverageRepository) {
  loadInventoryFromFile();
}

void Inventory::loadInventoryFromFile() {
  std::cout << "Load inventory from File..." << std::endl;
  this->items = beverageRepository->loadBeveragesFromFile();
}

Beverage* Inventory::getBeverage(int code) {
  if (!isValidCode(code)) {
    std::cout << "Inventory Not contains beverage code " << code << std::endl;
    return nullptr;
  }
  return &items[code - 1];
}

int Inventory::itemCount() const {
  return this->items.size();
}

bool Inventory::isValidCode(int code) const {
  return code <= items.size() && code > 0;
}

bool Inventory::isAvailable(int code, int qty) const {
  if (!isValidCode(code)) {
    return false;
  }
  return qty <= items[code - 1].getStock();
}

void Inventory::showBeverages() {
  for (size_t i = 0; i < items.size(); ++i) {
    printf("%02d   | %-13s | %5d 원 | %2d 개\n",
           items[i].getCode(),
           items[i].getName().c_str(),
           items[i].getPrice(),
           items[i].getStock());
  }
}

void Inventory::decreaseStock(int code, int qty) {
  if (!isValidCode(code)) {
    return;
  }
  items[code - 1].decreaseStock(qty);
  beverageRepository->updateBeverage(&items[code-1]);
}

/**
 * @brief use case2 ssd와 msg 내용이 달라짐 msg == -1 일때와 아닐때로 변경됨
 */
void Inventory::CodeInput(std::string code){
  int result = prepaymentHandler->PrePaymentCheck(code);

  
  if(result != -1){
    //TODO : 인증실패, 유효하지 않은코드입니다. 다시 시도해주세요 출력 (Display에서 호출하도록 하꾸어주어야 할 것 같음)
  }else{
    //TODO : 인증성공, 음료제공하는 상태 호출하기
  }
}
