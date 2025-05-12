//
// Created by kan02 on 2025-05-12.
//

#ifndef PURCHASEHANDLER_H
#define PURCHASEHANDLER_H


class PaymentSystem;
class PurchaseHandler {
  private:
    PaymentSystem *paymentSystem;
  public:
    bool checkCard();
};


#endif //PURCHASEHANDLER_H
