//
// Created by kan02 on 2025-05-12.
//

#ifndef BEVERAGEREPOSITORY_H
#define BEVERAGEREPOSITORY_H
#include <vector>
#include <string>

#include "../../../common/data/Beverage.h"


class BeverageRepository {
  private:
    std::string filePath;
  public:
    virtual ~BeverageRepository() = default;
    virtual std::vector<Beverage>loadBeveragesFromFile() = 0;
    virtual void updateBeverage(Beverage* beverage) = 0;
};



#endif //BEVERAGEREPOSITORY_H
