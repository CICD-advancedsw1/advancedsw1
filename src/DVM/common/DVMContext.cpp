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
  std::cout << "=== DVM System init ===" << std::endl;
  //TODO:의존성 주입필요
  this->beverageRepository = new BeverageRepository("C:/Users/kan02/CLionProjects/advancedsw1/src/DVM/database/beverages.txt");
  this->inventory = new Inventory(beverageRepository);

  this->display = new Display(inventory);
  this->broadCast = new BroadCast();

  this->paymentSystem = new PaymentSystem();
  this->prepaymentHandler = new PrepaymentHandler();
  this->purchaseHandler = new PurchaseHandler();
  std::cout << "=== Init success ===" << std::endl;
}

void DVMContext::run() {
  std::cout << "=== DVM Start ===" << std::endl;
  //TODO:Thread 처리를 통해 서버 실행
  while (true) {
    display->mainMenu();
  }
}
