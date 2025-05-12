//
// Created by kan02 on 2025-05-12.
//

#ifndef BEVERAGEREPOSITORY_H
#define BEVERAGEREPOSITORY_H
#include <vector>
#include <string>
#include "../../common/data/Beverage.h"


class BeverageRepository {
  private:
    std::string filePath;
  public:
    BeverageRepository(std::string filePath);
    std::vector<Beverage>loadBeveragesFromFile();
    void updateBeverage(Beverage* beverage);
};



#endif //BEVERAGEREPOSITORY_H
