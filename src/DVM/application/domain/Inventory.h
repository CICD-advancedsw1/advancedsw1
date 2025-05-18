//
// Created by kan02 on 2025-05-12.
//

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "repository/BeverageRepository.h"

class Inventory {
  private:
    std::vector<Beverage> items;
    BeverageRepository* beverageRepository;
  public:
    Inventory(BeverageRepository* beverageRepository);
    void loadInventoryFromFile();
    Beverage* getBeverage(int code);
    int itemCount() const;
    bool isValidCode(int code) const;
    bool isAvailable(int code, int qty) const;
    void showBeverages();
    void decreaseStock(int code, int qty);
};



#endif //INVENTORY_H
