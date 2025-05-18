//
// Created by kan02 on 2025-05-18.
//

#ifndef FAKEBEVERAGEREPOSITORY_H
#define FAKEBEVERAGEREPOSITORY_H
#pragma once
#include "../src/DVM/infrastructure/repository/BeverageRepository.h"


class FakeBeverageRepository : public BeverageRepository{
  public:
    FakeBeverageRepository() : BeverageRepository("ignore.txt") {}
    std::vector<Beverage> loadBeveragesFromFile()  {
      return {
        Beverage("콜라", 1000, 10, 1),
        Beverage("사이다", 1200, 5, 2)
    };
    }

    void updateBeverage(Beverage* beverage) {
      updateCalled = true;
      updatedCode = beverage->getCode();
    }

    bool updateCalled;
    int updatedCode;

};



#endif //FAKEBEVERAGEREPOSITORY_H
