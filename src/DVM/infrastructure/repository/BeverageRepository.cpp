//
// Created by kan02 on 2025-05-12.
//

#include "BeverageRepository.h"

#include <fstream>
#include <iostream>
#include <sstream>
BeverageRepository::BeverageRepository(std::string filePath)
  : filePath(std::move(filePath)) {
}

std::vector<Beverage> BeverageRepository::loadBeveragesFromFile() {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "[Error] Failed to open inventory file: " << filePath << std::endl;
    exit(1);
  }

  std::vector<Beverage> items;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string name, priceStr, stockStr;

    if (std::getline(ss, name, ',') &&
      std::getline(ss, priceStr, ',') &&
      std::getline(ss, stockStr)) {
      int price = std::stoi(priceStr);
      int stock = std::stoi(stockStr);

      items.emplace_back(Beverage(name, price, stock));
    }
  }

  file.close();
  return items;
}
