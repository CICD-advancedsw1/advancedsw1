//
// Created by user on 25. 5. 18.
//

#ifndef FAKECERTIFICATIONREPOSITORY_H
#define FAKECERTIFICATIONREPOSITORY_H
#include <string>

#include "../../src/DVM/application/domain/repository/CertificationCodeRepository.h"

class FakeCertificationRepository : public CertificationCodeRepository {
  public:
    bool saved = false;
    std::string savedCode;
    int savedItemCode = -1;
    int savedQty = -1;
    std::unordered_map<std::string, CodeInfo> savedCodes;

    void save(const std::string &certCode, int itemCode, int itemNum) override {
      saved = true;
      savedCode = certCode;
      savedItemCode = itemCode;
      savedQty = itemNum;
    }

    std::optional<CodeInfo> findByCode(const std::string &certCode) override {
      auto it = savedCodes.find(certCode);
      if (it != savedCodes.end()) return it->second;
      return std::nullopt;
    }
    void loadFromFile() override {

    };

    bool deleteByCode(const std::string &certCode) override {
      return savedCodes.erase(certCode) > 0;
    }

    void saveToFile() override {

    };

    // 테스트 용도: 저장된 갯수 확인
    size_t size() const {
      return savedCodes.size();
    }
};
#endif //FAKECERTIFICATIONREPOSITORY_H
