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
    int code;
    int maxStock;

  public:
    Beverage(const std::string &name, int price, int stock, int code, int maxStock);
    std::string getName() const;
    int getPrice() const;
    int getStock() const;
    int getCode() const;
    int getMaxStock() const;
    void decreaseStock(int qty);
    void increaseStock(int qty);
};



#endif //BEVERAGE_H
