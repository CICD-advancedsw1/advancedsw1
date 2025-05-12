//
// Created by kan02 on 2025-05-12.
//

#include "PrepaymentHandler.h"

#include "../../common/data/Beverage.h"

PrepaymentHandler::PrepaymentHandler(BroadCast *broadCast) : broadCast(broadCast) {
}
PrepaymentHandler::~PrepaymentHandler() {
}
std::string PrepaymentHandler::findAvailableDVM(Beverage *beverage, int qty) {
  std::string srcId = "T2";
  std::string code = "";
  if (beverage->getCode() < 10) {
    code.append("0");
  }
  code.append(std::to_string(beverage->getCode()));

  // 1. Create broadcast request
  std::string request = R"(
    {
      "msg_type": "req_stock",
      "src_id": ")" + srcId + R"(",
      "dst_id": "0",
      "msg_content": {
        "item_code": ")" + code + R"(",
        "item_num": )" + std::to_string(qty) + R"(
      }
    })";

  return broadCast->broadCast(request);
}
