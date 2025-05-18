//
// Created by user on 25. 5. 18.
//

#ifndef FAKEPAYMENTSYSTEM_H
#define FAKEPAYMENTSYSTEM_H
#include <string>

#include "../../src/DVM/application/domain/repository/PaymentSystem.h"

class FakePaymentSystem : public PaymentSystem {
  public:
    bool connected = false;
    std::string lastCard;
    int lastAmount = 0;
    bool shouldSucceed = true;

    std::pair<bool, std::string> connectSystem(std::string cardNumber, int price) override {
      connected = true;
      lastCard = cardNumber;
      lastAmount = price;
      if (shouldSucceed) return {true, "결제 성공"};
      return {false, "잔액 부족"};
    }
};
#endif //FAKEPAYMENTSYSTEM_H
