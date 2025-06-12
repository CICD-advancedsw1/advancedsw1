//
// Created by user on 25. 5. 18.
//

#include "FileCertificationCodeRepository.h"
//
// Created by kan02 on 2025-05-16.
//

#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>


FileCertificationCodeRepository::FileCertificationCodeRepository(
  const std::string &filePath) : filePath(filePath) {
  this->FileCertificationCodeRepository::loadFromFile();
}

void FileCertificationCodeRepository::save(const std::string &certCode, int itemCode, int itemNum) {
  std::lock_guard<std::mutex> lock(mtx);
  codeMap[certCode] = CodeInfo{itemCode, itemNum};
  saveToFile();
}

std::optional<CodeInfo> FileCertificationCodeRepository::findByCode(const std::string &certCode) {
  std::lock_guard<std::mutex> lock(mtx);
  auto it = codeMap.find(certCode);
  if (it != codeMap.end()) return it->second;
  return std::nullopt;
}

bool FileCertificationCodeRepository::deleteByCode(const std::string &certCode) {
  std::lock_guard<std::mutex> lock(mtx);
  auto it = codeMap.find(certCode);
  if (it != codeMap.end()) {
    CodeInfo info = it->second;
    codeMap.erase(it);
    saveToFile();
    return true;
  }
  return false;
}

void FileCertificationCodeRepository::loadFromFile() {
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << "Load Certification Codes from File...\n";
  std::ifstream file(filePath);
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string certCode;
    int itemCode, itemNum;

    if (iss >> certCode >> itemCode >> itemNum) {
      codeMap[certCode] = CodeInfo{itemCode, itemNum};
    }
  }
  std::cout << "Load Certification Codes from File Success.\n";
}

void FileCertificationCodeRepository::saveToFile() {
  std::lock_guard<std::mutex> lock(mtx);
  std::ofstream file(filePath, std::ios::trunc);
  for (const auto &[certCode, info]: codeMap) {
    file << certCode << " " << info.itemCode << " " << info.itemNum << "\n";
  }
}
