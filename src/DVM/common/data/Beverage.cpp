//
// Created by kan02 on 2025-05-12.
//

#include "Beverage.h"

Beverage::Beverage(const std::string &name, int price, int stock, int code) {
  this->name = name;
  this->price = price;
  this->stock = stock;
  this->code = code;
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
int Beverage::getCode() const {
  return this->code;
}
void Beverage::decreaseStock(int qty) {
  this->stock -= qty;
}
void Beverage::increaseStock(int qty) {
  this->stock += qty;
}