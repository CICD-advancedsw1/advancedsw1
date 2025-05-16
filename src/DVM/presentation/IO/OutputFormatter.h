//
// Created by user on 25. 5. 13.
//

#ifndef OUTPUTFORMATTER_H
#define OUTPUTFORMATTER_H
#include <string>
#include <vector>

#include "../../application/domain/Inventory.h"


class ResponseStock;
class Beverage;
class OutputFormatter {
  public:
    void showMainMenu();
    void showDrinkMenu(Inventory* inventory);
    void showPayAndQuantity(Beverage* beverage, int qty);
    void showPaymentMenu();
    void showPaymentStatus(const std::pair<bool, std::string>& result);
    void showGiveBeverageGuide(Beverage *beverage, int qty);
    void showGoodbye();
    void printStockShortage(Beverage *beverage);
    void printRequestingOtherDVM();
    void printTotalPrice(int total);
    void printRequestingPrepaymentOtherDVM(std::string destDVMId);
    void printAvailableOtherDVMInfo(ResponseStock* response, int qty);
    void printPrePaymentCodeAndDVMLocation(const std::string& code, ResponseStock* response);
    void showError(const std::string& message);
};



#endif //OUTPUTFORMATTER_H
