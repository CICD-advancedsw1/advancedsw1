//
// Created by kan02 on 2025-05-12.
//

#include "Beverage.h"

Beverage::Beverage(const std::string &name, int price, int stock) {
  this->name = name;
  this->price = price;
  this->stock = stock;
}

std::string Beverage::getName() const {
  return this->name;
}

int Beverage::getPrice() const {
  return this->price;
}

int Beverage::getStock() const {
  return this->stock;
}
