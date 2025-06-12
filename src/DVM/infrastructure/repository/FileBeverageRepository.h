//
// Created by user on 25. 5. 18.
//

#ifndef BEVERAGEREPOSITORYIMPL_H
#define BEVERAGEREPOSITORYIMPL_H
#include <mutex>

#include "../../application/domain/repository/BeverageRepository.h"
#include "../../common/data/Beverage.h"


class FileBeverageRepository : public BeverageRepository{
  private:
    std::string filePath;
    std::mutex fileMutex;
  public:
    explicit FileBeverageRepository(const std::string& path);
    std::vector<Beverage> loadBeveragesFromFile() override;
    void updateBeverage(Beverage* beverage) override;
};



#endif //BEVERAGEREPOSITORYIMPL_H
