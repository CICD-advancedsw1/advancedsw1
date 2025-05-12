//
// Created by kan02 on 2025-05-12.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>

class Inventory;
class Beverage;
class Display {
  private:
    Inventory* inventory;

  public:
    Display(Inventory* inventory);
    void mainMenu();
    void printMenu();
    void selectMenu();
    void paymentMenu(int code, int qty);
    void paymentRequest(int price);
    void inputCertCode();
};


#endif //DISPLAY_H
