//
// Created by kan02 on 2025-05-12.
//

#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <string>

class Beverage {
  private:
    std::string name;
    int price;
    int stock;
  public:
    Beverage(const std::string &name, int price, int stock);
    std::string getName() const;
    int getPrice() const;
    int getStock() const;
};



#endif //BEVERAGE_H
