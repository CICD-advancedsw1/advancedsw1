//
// Created by kan02 on 2025-05-16.
//

#include "CertificationCodeRepository.h"
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>

CertificationCodeRepository::CertificationCodeRepository(const std::string& filePath)
    : filePath(filePath) {
  loadFromFile();
}

void CertificationCodeRepository::save(const std::string& certCode, int itemCode, int itemNum) {
  std::lock_guard<std::mutex> lock(mtx);
  codeMap[certCode] = CodeInfo{itemCode, itemNum};
  saveToFile();
}

std::optional<CodeInfo> CertificationCodeRepository::findByCode(const std::string& certCode) {
  std::lock_guard<std::mutex> lock(mtx);
  auto it = codeMap.find(certCode);
  if (it != codeMap.end()) return it->second;
  return std::nullopt;
}

bool CertificationCodeRepository::deleteByCode(const std::string& certCode) {
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

void CertificationCodeRepository::loadFromFile() {
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

void CertificationCodeRepository::saveToFile() {
  std::ofstream file(filePath, std::ios::trunc);
  for (const auto& [certCode, info] : codeMap) {
    file << certCode << " " << info.itemCode << " " << info.itemNum << "\n";
  }
}