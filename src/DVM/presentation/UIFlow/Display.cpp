//
// Created by kan02 on 2025-05-12.
//

#include "Display.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "../../application/domain/Inventory.h"

Display::Display(Inventory *inventory,
                 PurchaseHandler *purchaseHandler,
                 PrepaymentHandler *prepaymentHandler) : inventory(inventory),
                                                         purchaseHandler(purchaseHandler),
                                                         prepaymentHandler(prepaymentHandler) {
  this->input = new InputHandler();
  this->output = new OutputFormatter;
}

//Main Menu
void Display::mainMenu() {
  //main Menu UI 출력
  output->showMainMenu();
  //사용자 입력 받기 (ex. 1)
  switch (input->getMenuSelection()) {
    case 1:
      printMenu(); // 음료 구매 플로우
      break;
    case 2:
      inputCertCode(); // 선결제 수령 플로우
      break;
    default:
      mainMenu(); // 이 외의 값은 재귀 호출로 다시 입력 받기
  }
}

//UseCase 1: 음료 선택 - 메뉴 출력
void Display::printMenu() {
  // 메뉴 출력
  output->showDrinkMenu(inventory);
  selectMenu();
}

//UseCase 1: 음료 선택
void Display::selectMenu() {
  //사용자에게 코드와 수량 입력 받기 (ex. 01 2)
  std::pair<Beverage *, int> result = input->getDrinkSelection(inventory);
  Beverage *beverage = result.first;
  int quantity = result.second;

  if (!inventory->isAvailable(beverage->getCode(), quantity)) {
    int stock = beverage->getStock();
    std::cout << "[Out of Stock] Only " << stock << " remaining.\n";
    prePaymentMenu(beverage, quantity);
  } else {
    paymentMenu(beverage, quantity);
  }
}

// UseCase 3: 음료 결제
void Display::paymentMenu(Beverage *beverage, int qty) {
  // 결제 화면 출력
  output->showPayAndQuantity(beverage, qty);
  // 결제를 할 것인지 사용자에게 입력 받기 (ex. Y)
  if (input->getYesOrNoForPayment() == 'Y') {
    paymentRequest(beverage, qty);
  } else {
    //종료 안내
  }
}

// UseCase 3: 음료 결제
void Display::paymentRequest(Beverage *beverage, int qty) {
  // 결제 중이라는 화면 출력
  output->showPaymentMenu();
  // 결제 로직 처리
  // 카드 잔액 확인 및 결제 -> Inventory 에서 수량 줄이기
  // 모두 DB 에 반영됨
  // TODO: Transaction 처리
  displayStatus(purchaseHandler->purchase(input->getCardNumber(), beverage, qty));
}

// UseCase 3: 음료 결제
void Display::displayStatus(std::pair<bool, std::string> status) {
  // 결제에 대한 성공 혹은 실패 상태 출력
  output->showPaymentStatus(status);
}

// UseCase 2: 선결제 물품 수령
void Display::inputCertCode() {

  std::string code = input->showPrePayInput();
  //todo: input 받기
  int result = prepaymentHandler->PrePaymentCheck(code);


  if(result != -1){
    //TODO : 인증실패, 유효하지 않은코드입니다. 다시 시도해주세요 출력 (Display에서 호출하도록 하꾸어주어야 할 것 같음)
  }else{
    //TODO : 인증성공, 음료제공하는 상태 호출하기
  }
}
void Display::prePaymentMenu(Beverage *beverage, int qty) {
  //output
  prepaymentHandler->findAvailableDVM(beverage, qty);
}
