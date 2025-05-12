//
// Created by user on 25. 5. 13.
//

#ifndef OUTPUTFORMATTER_H
#define OUTPUTFORMATTER_H
#include <string>
#include <vector>

#include "../../application/domain/Inventory.h"


class Beverage;
class OutputFormatter {
  public:
    void showMainMenu();
    void showDrinkMenu(Inventory* inventory);
    void showPayAndQuantity(Beverage* beverage, int qty);
    void showPaymentMenu();
    void showPaymentStatus(const std::pair<bool, std::string>& result);
    void showError(const std::string& message);
};



#endif //OUTPUTFORMATTER_H
