//
// Created by kan02 on 2025-05-12.
//

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Beverage.h"
#include "../../infrastructure/repository/BeverageRepository.h"

class Inventory {
  private:
    std::vector<Beverage> items;
    BeverageRepository* beverageRepository;
  public:
    Inventory(BeverageRepository* beverageRepository);
    void loadInventoryFromFile();
    int getStock(int code) const;
    std::string getName(int code) const;
    int getPrice(int code) const;
    int itemCount() const;
    bool isValidCode(int code) const;
    bool isAvailable(int code, int qty) const;
};



#endif //INVENTORY_H
