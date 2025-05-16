//
// Created by kan02 on 2025-05-12.
//

#include "DVMContext.h"
#include <iostream>

DVMContext::DVMContext()
  : display(nullptr),
    inventory(nullptr),
    prepaymentHandler(nullptr),
    purchaseHandler(nullptr),
    broadCast(nullptr),
    paymentSystem(nullptr),
    beverageRepository(nullptr) {
  dependencyInjection();
}

DVMContext::~DVMContext() {
  delete display;
  delete inventory;
  delete prepaymentHandler;
  delete purchaseHandler;
  delete broadCast;
  delete paymentSystem;
  delete beverageRepository;
}

void DVMContext::dependencyInjection() {
  std::cout << "\n=== DVM System init ===" << std::endl;
  //TODO:의존성 주입필요
  this->beverageRepository = new BeverageRepository("C:/Users/user/CLionProjects/advancedsw1/src/DVM/database/beverages.txt");
  this->inventory = new Inventory(beverageRepository);
  this->broadCast = new BroadCast();
  this->paymentSystem = new PaymentSystem("C:/Users/user/CLionProjects/advancedsw1/src/DVM/database/paymentInformation.txt");
  this->prepaymentHandler = new PrepaymentHandler(broadCast);
  this->purchaseHandler = new PurchaseHandler(paymentSystem, inventory);
  this->display = new Display(inventory, purchaseHandler, prepaymentHandler);
  std::cout << "=== Init success ===" << std::endl;
}

void DVMContext::run() {
  std::cout << "=== DVM Start ===" << std::endl;
  //TODO:Thread 처리를 통해 서버 실행
  while (true) {
    display->mainMenu();
  }
}
