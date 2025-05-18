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
  std::cout << "Load inventory from File Success" << std::endl;
}

Beverage* Inventory::getBeverage(int code) {
  if (!isValidCode(code)) {
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
