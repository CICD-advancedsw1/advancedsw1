//
// Created by user on 25. 5. 13.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <string>
#include "../../application/domain/Inventory.h"

class InputHandler {
  public:
    int getMenuSelection();
    std::pair<Beverage*, int> getDrinkSelection(Inventory* inventory); // code, quantity
    std::string getCardNumber();
    char getYesOrNoForPayment();
};



#endif //INPUTHANDLER_H
