//
// Created by kan02 on 2025-05-12.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>

#include "../../application/service/PrepaymentHandler.h"
#include "../../application/service/PurchaseHandler.h"
#include "../../common/data/Beverage.h"
#include "../IO/InputHandler.h"
#include "../IO/OutputFormatter.h"
class Display {
  private:
    InputHandler* input;
    OutputFormatter* output;
    Inventory* inventory;
    PurchaseHandler* purchaseHandler;
    PrepaymentHandler* prepaymentHandler;

  public:
    Display(Inventory* inventory, PurchaseHandler* purchaseHandler, PrepaymentHandler* prepaymentHandler);
    void mainMenu();
    void printMenu();
    void selectMenu();
    void paymentMenu(Beverage* beverage, int qty);
    void paymentRequest(Beverage* beverage, int qty);
    void inputCertCode();
    void prePaymentMenu(Beverage *beverage, int qty);
    void displayStatus(std::pair<bool, std::string> status);
};


#endif //DISPLAY_H
