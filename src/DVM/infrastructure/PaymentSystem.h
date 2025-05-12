//
// Created by kan02 on 2025-05-12.
//

#ifndef PAYMENTSYSTEM_H
#define PAYMENTSYSTEM_H
#include <string>


class PaymentSystem {
  private:
    std::string path;
  public:
    PaymentSystem(std::string path);
    std::pair<bool, std::string> connectSystem(std::string cardNumber, int price);
};



#endif //PAYMENTSYSTEM_H
