//
// Created by kan02 on 2025-05-12.
//

#ifndef DVMCONTEXT_H
#define DVMCONTEXT_H

#include "../application/domain/Inventory.h"
#include "../application/service/PrepaymentHandler.h"
#include "../application/service/PurchaseHandler.h"
#include "../infrastructure/BroadCast.h"
#include "../presentation/UIFlow/Display.h"
#include "data/DVMNetworkData.h"

class DVMContext {
  private:
    Display* display;
    Inventory* inventory;
    PrepaymentHandler* prepaymentHandler;
    PurchaseHandler* purchaseHandler;
    BroadCast* broadCast;
    PaymentSystem* paymentSystem;
    BeverageRepository* beverageRepository;
    DVMNetworkData* dvmNetworkData;

  public:
    DVMContext();
    ~DVMContext();
    void dependencyInjection();
    void run();
};


#endif //DVMCONTEXT_H
