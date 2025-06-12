//
// Created by user on 25. 5. 18.
//

#ifndef FAKEBEVERAGEREPSITORY_H
#define FAKEBEVERAGEREPSITORY_H
#include <vector>
#include "../../src/DVM/common/data/Beverage.h"

class FakeBeverageRepository: public BeverageRepository {
  public:
    std::vector<Beverage> loadBeveragesFromFile() override {
      return {
        Beverage("콜라", 1000, 10, 1, 100),
        Beverage("사이다", 1200, 5, 2, 100),
        Beverage("녹차", 1300, 10, 3, 100),
        Beverage("홍차", 1300, 10, 4, 100),
        Beverage("밀크티", 1500, 10, 5, 100),
        Beverage("탄산수", 1000, 10, 6, 100),
        Beverage("보리차", 1100, 10, 7, 100),
      };
    }

    void updateBeverage(Beverage *beverage) override {
      updateCalled = true;
      updatedCode = beverage->getCode();
    }

    bool updateCalled = false;
    int updatedCode = -1;
};
#endif //FAKEBEVERAGEREPSITORY_H
