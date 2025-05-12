//
// Created by kan02 on 2025-05-12.
//

#ifndef DVMCONTEXT_H
#define DVMCONTEXT_H

#include "../application/domain/Inventory.h"
#include "../application/service/PrepaymentHandler.h"
#include "../application/service/PurchaseHandler.h"
#include "../infrastructure/BroadCast.h"
#include "../infrastructure/PaymentSystem.h"
#include "../presentation/UIFlow/Display.h"

class DVMContext {
  private:
    Display* display;
    Inventory* inventory;
    PrepaymentHandler* prepaymentHandler;
    PurchaseHandler* purchaseHandler;
    BroadCast* broadCast;
    PaymentSystem* paymentSystem;
    BeverageRepository* beverageRepository;

  public:
    DVMContext();
    ~DVMContext();
    void dependencyInjection();
    void run();
};


#endif //DVMCONTEXT_H
