//
// Created by kan02 on 2025-05-12.
//

#include "Inventory.h"

Inventory::Inventory(BeverageRepository *beverageRepository): beverageRepository(
  beverageRepository) {
  loadInventoryFromFile();
}

void Inventory::loadInventoryFromFile() {
  this->items = beverageRepository->loadBeveragesFromFile();
}

int Inventory::getStock(int code) const {
  if (!isValidCode(code)) {
    return -1;
  }
  return items[code - 1].getStock();
}
std::string Inventory::getName(int code) const {
  if (!isValidCode(code)) {
    return "null";
  }
  return items[code - 1].getName();
}
int Inventory::getPrice(int code) const {
  if (!isValidCode(code)) {
    return -1;
  }
  return items[code - 1].getPrice();
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
