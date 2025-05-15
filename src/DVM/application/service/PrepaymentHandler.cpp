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
      "dst_id": "0",ㅇ
      "msg_content": {
        "item_code": ")" + code + R"(",
        "item_num": )" + std::to_string(qty) + R"(
      }
    })";

  return broadCast->broadCast(request);
}

/**
 * @brief 입력한 certification code가 DVM내 존재하는지 확인, 확인하는 CertCode가 string에서 vector<pair<string, int>> 자료로 바뀜
 * @param code 입력받은 certification code
 * @return 해당 cert code의 음료코드 (-1 if not exist)
 */
int PrepaymentHandler::PrePaymentCheck(std::string code){
  for(const auto& p : Cert_code){
    if(p.first == code){
      EraseCode(code);
      return p.second;
    }
  }

  return -1;
}

void PrepaymentHandler::EraseCode(std::string code){
  auto it = std::find(Cert_code.begin(), Cert_code.end(), code);
  if(it != Cert_code.end()){
    Cert_code.erase(it);
  }
}