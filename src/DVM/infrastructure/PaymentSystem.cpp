//
// Created by kan02 on 2025-05-12.
//

#include "PaymentSystem.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

PaymentSystem::PaymentSystem(std::string path)
  : path(path) {
}

std::pair<bool, std::string> PaymentSystem::connectSystem(std::string cardNumber, int price) {
  std::ifstream inFile(path);

  if (!inFile.is_open()) {
    std::cerr << "[Payment Error] Cannot open file: " << this->path << std::endl;
    return std::pair(false, "[Payment Error] Cannot connect system:");
  }

  std::vector<std::string> lines;
  std::string line;

  bool updated = false;

  while (std::getline(inFile, line)) {
    std::istringstream iss(line);
    std::string fileCardNumber;
    int balance;

    if (iss >> fileCardNumber >> balance) {
      if (fileCardNumber == cardNumber) {
        if (balance >= price) {
          balance -= price;
          updated = true;
        } else {
          std::cout << "[Payment Failed] Not enough balance.\n";
          inFile.close();
          return std::pair(false, "[Payment Failed] Not enough balance.");
        }
        // 카드 정보 업데이트
        line = fileCardNumber + " " + std::to_string(balance);
      }
    }

    lines.push_back(line); // 원래든 수정했든 저장
  }
  inFile.close();

  if (!updated) {
    std::cout << "[Error] Card not found.\n";
    return std::pair(false, "[Error] Card not found.");
  }


  // 파일 덮어쓰기
  std::ofstream outFile(path);
  for (const auto &l: lines) {
    outFile << l << '\n';
  }
  outFile.close();

  std::cout << "[Payment Success] Payment Success.\n";
  return std::pair(true, "[Payment Success] Payment Success.");
}
