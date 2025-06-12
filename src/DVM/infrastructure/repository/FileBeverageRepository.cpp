//
// Created by user on 25. 5. 18.
//

#include "FileBeverageRepository.h"
//
// Created by kan02 on 2025-05-12.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>


FileBeverageRepository::FileBeverageRepository(const std::string &path)
  :filePath(path){
}
std::vector<Beverage> FileBeverageRepository::loadBeveragesFromFile() {
  std::lock_guard<std::mutex> lock(fileMutex);
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "[Error] Failed to open inventory file: " << filePath << std::endl;
    exit(1);
  }

  std::vector<Beverage> items;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string codeStr, name, priceStr, stockStr;

    if (std::getline(ss, codeStr, ',') &&
      std::getline(ss, name, ',') &&
      std::getline(ss, priceStr, ',') &&
      std::getline(ss, stockStr)) {
      int price = std::stoi(priceStr);
      int stock = std::stoi(stockStr);
      int code = std::stoi(codeStr);

      items.emplace_back(Beverage(name, price, stock, code, 100));
      std::cout << "Loaded beverage: " << code << ", " << name << std::endl;
    }
  }

  file.close();
  return items;
}
void FileBeverageRepository::updateBeverage(Beverage *beverage) {
  std::lock_guard<std::mutex> lock(fileMutex);
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "[Error] Failed to open inventory file: " << filePath << std::endl;
    return;
  }

  std::vector<std::string> updatedLines;
  std::string line;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string codeStr, name, priceStr, stockStr;

    if (std::getline(ss, codeStr, ',') &&
      std::getline(ss, name, ',') &&
      std::getline(ss, priceStr, ',') &&
      std::getline(ss, stockStr)) {
      int code = std::stoi(codeStr);
      int price = std::stoi(priceStr);
      int stock = std::stoi(stockStr);

      if (code == beverage->getCode()) {
        stock = beverage->getStock();
      }

      std::stringstream updated;
      updated << code << "," << name << "," << price << "," << stock;
      updatedLines.push_back(updated.str());
    }
  }
  file.close();

  // 파일 덮어쓰기
  std::ofstream outFile(filePath);
  if (!outFile.is_open()) {
    std::cerr << "[Error] Failed to write to inventory file: " << filePath << std::endl;
    return;
  }

  for (const auto &l: updatedLines) {
    outFile << l << '\n';
  }

  outFile.close();
}
