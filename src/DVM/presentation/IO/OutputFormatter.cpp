//
// Created by user on 25. 5. 13.
//

#include "OutputFormatter.h"

#include <iostream>
void OutputFormatter::showMainMenu() {
  std::cout << "\n=============================\n";
  std::cout << "       Team 2 DVM System        \n";
  std::cout << "=============================\n";
  std::cout << " 1. Purchase Beverage\n";
  std::cout << " 2. Receive prepaid items\n";
  std::cout << "=============================\n";
}
void OutputFormatter::showDrinkMenu(Inventory* inventory) {
  std::cout << "==================== Drink Menu ====================\n";
  std::cout << "Code | Name          | Price     | Stock\n";
  std::cout << "----------------------------------------------------\n";
  inventory->showBeverages();
  std::cout << "====================================================\n";
}
void OutputFormatter::showPayAndQuantity(Beverage *beverage, int qty) {
  std::cout << "\n[Selection Complete]:\n" << beverage->getName() << " " << qty << " selected.\n";
  std::cout << "total price: " << beverage->getPrice() << "won";
}
void OutputFormatter::showPaymentMenu() {
  std::cout << "\nProceeding to payment step...\n";

  std::cout << "\n==============================\n";
  std::cout << "         Payment Process\n";
  std::cout << "==============================\n";
}
void OutputFormatter::showPaymentStatus(const std::pair<bool, std::string> &status) {
  if (status.first) {
    std::cout << "[Success] " << status.second << std::endl;
  } else {
    std::cerr << "[Failure] " << status.second << std::endl;
  }
}
