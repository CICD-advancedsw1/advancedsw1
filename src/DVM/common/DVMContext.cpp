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
    beverageRepository(nullptr),
    certificationCodeRepository(nullptr),
    dvmServer(nullptr) {
  dependencyInjection();
}

DVMContext::~DVMContext() {
  delete certificationCodeRepository;
  delete beverageRepository;
  delete paymentSystem;
  delete broadCast;
  delete inventory;
  delete prepaymentHandler;
  delete dvmServer;
  delete purchaseHandler;
  delete display;
}

void DVMContext::dependencyInjection() {
  std::cout << "\n=== DVM System Initialize ===" << std::endl;
  this->certificationCodeRepository = new CertificationCodeRepository("../src/DVM/database/certification-codes.txt");
  DVMNetworkData::init("../src/DVM/database/DVMData.txt");
  this->beverageRepository = new BeverageRepository("../src/DVM/database/beverages.txt");
  this->paymentSystem = new PaymentSystem("../src/DVM/database/paymentInformation.txt");
  this->broadCast = new BroadCast();

  this->inventory = new Inventory(beverageRepository);
  this->prepaymentHandler = new PrepaymentHandler(broadCast, certificationCodeRepository, inventory);
  this->dvmServer = new DVMServer(inventory, prepaymentHandler);
  this->purchaseHandler = new PurchaseHandler(paymentSystem, inventory);
  this->display = new Display(inventory, purchaseHandler, prepaymentHandler);
  std::cout << "=== Success Initialize ===" << std::endl;
}

void DVMContext::run() {
  std::cout << "=== DVM Server Initialize ===" << std::endl;
  std::thread serverThread(&DVMServer::run, dvmServer);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "=== DVM Start ===" << std::endl;
  while (true) {
    display->mainMenu();
  }
}
