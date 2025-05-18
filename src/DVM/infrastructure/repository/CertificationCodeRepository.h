//
// Created by kan02 on 2025-05-16.
//

#ifndef CERTIFICATIONCODEREPOSITORY_H
#define CERTIFICATIONCODEREPOSITORY_H
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct CodeInfo {
  int itemCode;
  int itemNum;
};

class CertificationCodeRepository {
  private:
    std::unordered_map<std::string, CodeInfo> codeMap;
    std::string filePath;
    std::mutex mtx;

  public:
    CertificationCodeRepository(const std::string &filePath);
    void save(const std::string &certCode, int itemCode, int itemNum);
    std::optional<CodeInfo> findByCode(const std::string &certCode);
    bool deleteByCode(const std::string &certCode);
    void loadFromFile();
    void saveToFile();
};



#endif //CERTIFICATIONCODEREPOSITORY_H
