//
// Created by kan02 on 2025-05-12.
//

#include "PaymentSystemImpl.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

PaymentSystemImpl::PaymentSystemImpl(std::string path)
  : path(path) {
}

std::pair<bool, std::string> PaymentSystemImpl::connectSystem(std::string cardNumber, int price) {
  std::ifstream inFile(path);

  if (!inFile.is_open()) {
    return std::pair(false, "[결제 실패] 결제 시스템에 연결할 수 없습니다.");
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
          inFile.close();
          return std::pair(false, "[결제 실패] 잔액이 부족합니다.\n");
        }
        // 카드 정보 업데이트
        line = fileCardNumber + " " + std::to_string(balance);
      }
    }

    lines.push_back(line); // 원래든 수정했든 저장
  }
  inFile.close();

  if (!updated) {
    return std::pair(false, "[결제 실패] 카드 정보를 확인할 수 없습니다.");
  }


  // 파일 덮어쓰기
  std::ofstream outFile(path);
  for (const auto &l: lines) {
    outFile << l << '\n';
  }
  outFile.close();

  return std::pair(true, "[결제 승인] 결제가 성공적으로 완료되었습니다.");
}
