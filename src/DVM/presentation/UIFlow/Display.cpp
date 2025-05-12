//
// Created by kan02 on 2025-05-12.
//

#include "Display.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include "../../application/domain/Beverage.h"
#include "../../application/domain/Inventory.h"

Display::Display(Inventory *inventory): inventory(inventory) {
}

void Display::mainMenu() {
  std::cout << "\n=============================\n";
  std::cout << "       Team 2 DVM System        \n";
  std::cout << "=============================\n";
  std::cout << " 1. Purchase Beverage\n";
  std::cout << " 2. Receive prepaid items\n";
  std::cout << "=============================\n";
  std::cout << "Please select menu number: ";
  std::flush(std::cout);
  // 한 줄 전체를 안전하게 입력받고
  std::string line;
  if (!std::getline(std::cin, line)) {
    // EOF나 스트림 오류 처리
    std::cout << "\n[Error] Input stream closed. Exiting.\n" << std::endl;
    exit(0);
  }

  std::stringstream ss(line);
  int choice;
  if (!(ss >> choice)) {
    std::cout << "[Input Error] Please enter a valid menu number\n" << std::endl;
  }

  switch (choice) {
    case 1:
      printMenu(); // 음료 구매 플로우
      break;
    case 2:
      inputCertCode(); // 선결제 수령 플로우
      break;
    default:
      std::cout << "[Input error] Please enter a valid menu number\n" << std::endl;
      mainMenu(); // 재귀 호출로 다시 입력 받기
  }
}
//UseCase 1: 음료 선택 - 메뉴 출력
void Display::printMenu() {
  std::cout << "==================== Drink Menu ====================\n";
  std::cout << "Code | Name          | Price     | Stock\n";
  std::cout << "----------------------------------------------------\n";

  for (size_t i = 0; i < inventory->itemCount(); ++i) {
    int code = i + 1;
    printf("%02d   | %-13s | %5d won | %2d pcs\n",
           code,
           inventory->getName(code).c_str(),
           inventory->getPrice(code),
           inventory->getStock(code));
  }

  std::cout << "====================================================\n";
  std::flush(std::cout);

  selectMenu();
}
//UseCase 1: 음료 선택
void Display::selectMenu() {
  int code, qty;
  while (true) {
    std::cout << "\nEnter drink code and quantity (ex: 01 2): ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    if (!(ss >> code >> qty)) {
      std::cout << "[Input Error] Format is invalid (ex: 01 2)\n";
      continue;
    }


    if (!inventory->isValidCode(code)) {
      std::cout << "[Code Error] That drink code does not exist.\n";
      continue;
    }

    if (qty <= 0) {
      std::cout << "[Quantity Error] Quantity must be at least 1.\n";
      continue;
    }

    if (!inventory->isAvailable(code, qty)) {
      int stock = inventory->getStock(code);
      std::cout << "[Out of Stock] Only " << stock << " remaining.\n";
      continue;
    }
    break;
  }
  //정상 입력
  paymentMenu(code, qty);
}

void Display::paymentMenu(int code, int qty) {
  std::cout << "\n[Selection Complete]:\n" << inventory->getName(code)
      << " " << qty << " selected.\n";
  std::cout << "total price: " << inventory->getPrice(code) << "won";
  std::cout << "\nDo you payment? (ex: Y or N): ";
  while (true) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    char selection;

    if (!(ss >> selection)) {
      std::cout << "[Input Error] Format is invalid (ex: Y or N)\n";
      continue;
    }

    if (selection == 'Y') {
      paymentRequest(inventory->getPrice(code));
    }

  }
}
void Display::paymentRequest(int price) {
  std::cout << "\nProceeding to payment step...\n";

  std::cout << "\n==============================\n";
  std::cout << "         Payment Process\n";
  std::cout << "==============================\n";
  std::cout << "Please insert your card...\n";

  std::string input;
  while (true) {
    if (std::cin.rdbuf()->in_avail()) {
      std::getline(std::cin, input);
      break;
    }
  }
  std::cout << "Processing card payment...\n";

}

void Display::inputCertCode() {
}
