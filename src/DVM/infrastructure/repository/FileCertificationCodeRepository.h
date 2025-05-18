//
// Created by user on 25. 5. 18.
//

#ifndef FILECERTIFICATIONCODEREPOSITORY_H
#define FILECERTIFICATIONCODEREPOSITORY_H

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../application/domain/repository/CertificationCodeRepository.h"


class FileCertificationCodeRepository: public CertificationCodeRepository {
  private:
    std::unordered_map<std::string, CodeInfo> codeMap;
    std::string filePath;
    std::mutex mtx;

  public:
    explicit FileCertificationCodeRepository(const std::string &filePath);
    void save(const std::string &certCode, int itemCode, int itemNum) override;
    std::optional<CodeInfo> findByCode(const std::string &certCode) override;
    bool deleteByCode(const std::string &certCode) override;
    void loadFromFile() override;
    void saveToFile() override;
};

#endif //FILECERTIFICATIONCODEREPOSITORY_H
