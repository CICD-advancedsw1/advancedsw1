//
// Created by user on 25. 5. 13.
//

#include "InputHandler.h"

#include <iostream>
#include <ostream>
#include <sstream>

#include "../../application/domain/Inventory.h"
int InputHandler::getMenuSelection() {
  std::cout << "Please select menu number: ";

  std::string line;
  if (!std::getline(std::cin, line)) {
    std::cout << "\n[Error] Input stream closed. Exiting.\n" << std::endl;
    exit(0);
  }

  std::stringstream ss(line);
  int choice;
  if (!(ss >> choice)) {
    std::cout << "[Input Error] Please enter a valid menu number\n" << std::endl;
  }

  if (!(choice == 1 || choice == 2)) {
    std::cout << "[Input error] Please enter a valid menu number\n" << std::endl;
  }
  return choice;
}

std::pair<Beverage*, int> InputHandler::getDrinkSelection(Inventory* inventory) {
  int code, qty;
  Beverage *beverage;
  while (true) {
    std::cout << "\nEnter drink code and quantity (ex: 01 2): ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    if (!(ss >> code >> qty)) {
      std::cout << "[Input Error] Format is invalid (ex: 01 2)\n";
      continue;
    }

    if (qty <= 0) {
      std::cout << "[Quantity Error] Quantity must be at least 1.\n";
      continue;
    }

    if (!inventory->isValidCode(code)) {
      std::cout << "[Code Error] That drink code does not exist.\n";
      continue;
    }

    beverage = inventory->getBeverage(code);
    if (!inventory->isAvailable(code, qty)) {
      int stock = beverage->getStock();
      std::cout << "[Out of Stock] Only " << stock << " remaining.\n";
      continue;
    }
    return std::pair(beverage, qty);
  }
}
std::string InputHandler::getCardNumber() {
  std::cout << "Please insert your card...\n";

  std::string cardNumber;
  std::getline(std::cin, cardNumber);

  std::cout << "Processing card payment...\n";
  return cardNumber;
}
char InputHandler::getYesOrNoForPayment() {
  while (true) {
    std::cout << "\nDo you payment? (ex: Y or N): ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    char selection;

    if (!(ss >> selection)) {
      std::cout << "[Input Error] Format is invalid\n";
    }
    if (selection == 'Y' || selection == 'y') {
      return selection;
    }
    if (selection == 'N' || selection == 'n') {
      return selection;
    }

    std::cout << "[Input Error] Select Yes or No\n";
  }
}
