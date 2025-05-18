//
// Created by user on 25. 5. 18.
//

#ifndef PAYMENTSYSTEM_H
#define PAYMENTSYSTEM_H
#include <string>
class PaymentSystem {
  public:
    virtual std::pair<bool, std::string> connectSystem(std::string cardNumber, int price) = 0;
    virtual ~PaymentSystem() = default;
};
#endif //PAYMENTSYSTEM_H
