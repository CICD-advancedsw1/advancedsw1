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
  public:
    virtual void save(const std::string &certCode, int itemCode, int itemNum) = 0;
    virtual std::optional<CodeInfo> findByCode(const std::string &certCode) = 0;
    virtual bool deleteByCode(const std::string &certCode) = 0;
    virtual void loadFromFile() = 0;
    virtual void saveToFile() = 0;
    virtual ~CertificationCodeRepository() = default;
};



#endif //CERTIFICATIONCODEREPOSITORY_H
