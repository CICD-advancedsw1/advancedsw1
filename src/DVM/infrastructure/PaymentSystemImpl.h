//
// Created by kan02 on 2025-05-12.
//

#ifndef PAYMENTSYSTEMIMPL_H
#define PAYMENTSYSTEMIMPL_H
#include <string>

#include "../application/domain/repository/PaymentSystem.h"


class PaymentSystemImpl : public PaymentSystem {
  private:
    std::string path;
  public:
    explicit PaymentSystemImpl(std::string path);
    std::pair<bool, std::string> connectSystem(std::string cardNumber, int price) override;
};



#endif //PAYMENTSYSTEM_H
