//
// Created by user on 25. 5. 13.
//

#include "OutputFormatter.h"
#include <iostream>

#include "../../common/data/ResponseStock.h"
using namespace std;
void OutputFormatter::showMainMenu() {
  cout << "\n=============================\n";
  cout << "       2팀 DVM System        \n";
  cout << "=============================\n";
  cout << " 1. 음료 구매\n";
  cout << " 2. 선결제 음료 수령\n";
  cout << "=============================\n";
}
void OutputFormatter::showDrinkMenu(Inventory* inventory) {
  cout << "==================== 음료 선택 메뉴 ====================\n";
  cout << "코드 | 이름          | 가격     | 수량\n";
  cout << "----------------------------------------------------\n";
  inventory->showBeverages();
  cout << "====================================================\n";
}
void OutputFormatter::showPayAndQuantity(Beverage *beverage, int qty) {
  cout << "\n[선택 완료]:\n" << beverage->getName() << " " << qty << "개가 선택되었습니다.\n";
  cout << "\n최종 선택 목록:\n";
  cout << "- " << beverage->getName() << " " << qty << "개\n";
  cout << "\n총 금액: " << beverage->getPrice() << "원\n";
}
void OutputFormatter::showPaymentMenu() {
  std::cout << "\n결제 단계로 진행합니다...\n";

  std::cout << "\n==============================\n";
  std::cout << "         결제 진행\n";
  std::cout << "==============================\n";
}


void OutputFormatter::showPaymentStatus(const std::pair<bool, std::string> &status) {
  if (status.first) {
    std::cout << "[결제 승인] " << status.second << std::endl;
  } else {
    std::cerr << "[결제 실패] " << status.second << std::endl;
  }
}

void OutputFormatter::showGiveBeverageGuide(Beverage* beverage, int qty) {
  cout << "음료를 준비 중입니다...";
  cout << "[음료 제공] " << beverage->getName() << qty << "개가 제공되었습니다.";
}

void OutputFormatter::showGoodbye() {
  std::cout << "\n==============================\n";
  std::cout << "         감사합니다. 또 이용해주세요! \n";
  std::cout << "==============================\n";
}

void OutputFormatter::printStockShortage(Beverage* beverage) {
  std::cout << "\n[재고 부족] '" << beverage->getName() << "'는 현재 "
            << beverage->getStock() << "개 남아 있습니다.\n";
}

void OutputFormatter::printRequestingOtherDVM() {
  std::cout << "[재고 확인 중...] 다른 DVM들에 정보 요청 중입니다...\n";
}

void OutputFormatter::printAvailableOtherDVMInfo(ResponseStock* response, int qty) {
  std::cout << "\n[재고 확인 완료] '" << qty << "개'는 아래 DVM에서 수령 가능합니다.\n";
  std::cout << "위치: x좌표 " << response->getCoorX() << "y좌표 " << response->getCoorY() <<" (" << response->getSrcId() << ")\n";
}

void OutputFormatter::printTotalPrice(int total) {
  std::cout << "총 금액: " << total << "원\n";
}

void OutputFormatter::printRequestingPrepaymentOtherDVM(string destDVMId) {
  std::cout << "[선결제 요청 중] "<< destDVMId << " 에 요청 중입니다...";
}

void OutputFormatter::printPrePaymentCodeAndDVMLocation(const std::string& code, ResponseStock* response) {
  std::cout << "발급된 인증코드: *" << code << "*\n";
  std::cout << "수령 위치: x좌표 " << response->getCoorX() << "y좌표 " << response->getCoorY() <<" (" << response->getSrcId() << ")\n";
  std::cout << "\n※ 해당 위치에서 인증코드를 입력하면 음료를 받을 수 있습니다.\n";
}
