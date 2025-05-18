//
// Created by user on 25. 5. 13.
//

#include "InputHandler.h"

#include <iostream>
#include <ostream>
#include <sstream>

#include "../../application/domain/Inventory.h"
int InputHandler::getMenuSelection() {
  std::cout << "> 메뉴를 선택해주세요: ";

  std::string line;
  if (!std::getline(std::cin, line)) {
    std::cout << "\n[Error] Input stream closed. Exiting.\n" << std::endl;
    exit(0);
  }

  std::stringstream ss(line);
  int choice;
  if (!(ss >> choice)) {
    std::cout << "[입력 오류] 유효한 번호를 선택해주세요.\n" << std::endl;
  }

  if (!(choice == 1 || choice == 2)) {
    std::cout << "[입력 오류] 유효한 번호를 선택해주세요.\n" << std::endl;
  }
  return choice;
}

std::pair<Beverage*, int> InputHandler::getDrinkSelection(Inventory* inventory) {
  int code, qty;
  Beverage *beverage;
  while (true) {
    std::cout << "\n> 음료 코드와 수량을 입력하세요 (예: 01 2): ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    if (!(ss >> code >> qty)) {
      std::cout << "\n[입력 오류] 입력 형식이 잘못되었습니다. (예: 01 2)\n";
      std::cout << "다시 입력해주세요.\n";
      std::cout << "-------------------------------------------\n";
      continue;
    }

    if (qty <= 0) {
      std::cout << "\n[수량 오류] 수량은 1 이상으로 입력해주세요.\n";
      std::cout << "다시 입력해주세요.\n";
      std::cout << "-------------------------------------------\n";
      continue;
    }

    if (!inventory->isValidCode(code)) {
      std::cout << "\n[입력 오류] 해당 음료 코드는 존재하지 않습니다.\n";
      std::cout << "다시 입력해주세요.\n";
      std::cout << "-------------------------------------------\n";
      continue;
    }

    beverage = inventory->getBeverage(code);

    return std::pair(beverage, qty);
  }
}
std::string InputHandler::getCardNumber() {
  std::cout << "카드를 삽입해주세요...\n";

  std::string cardNumber;
  std::getline(std::cin, cardNumber);

  std::cout << "\n카드 결제 중입니다...\n\n";
  return cardNumber;
}
char InputHandler::getYesOrNoForPayment() {
  while (true) {
    std::cout << "\n> 결제를 진행하시겠습니까? (예: Y or N): ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    char selection;

    if (!(ss >> selection)) {
      std::cout << "[입력 오류] 입력 형식이 잘못되었습니다. (예: Y or N)\n";
    }
    if (selection == 'Y' || selection == 'y') {
      return selection;
    }
    if (selection == 'N' || selection == 'n') {
      return selection;
    }

    std::cout << "[입력 오류] 입력 형식이 잘못되었습니다. (예: Y or N)\n";
  }
}


std::string InputHandler::showPrePayInput(){
  std::string line;

  std::cout << "\n==========================\n";
  std::cout << "    선결제 물품 수령\n";
  std::cout << "==========================\n";
  std::cout << "\n인증 코드를 입력해주세요 : \n";

  std::getline(std::cin, line);

  return line;
}
