//
// Created by kan02 on 2025-05-12.
//

#include "PrepaymentHandler.h"

#include <algorithm>

#include "../../common/data/Beverage.h"
#include "../../common/data/DVMNetworkData.h"
#include"../../../../include/nlohmann/json.hpp"
#include <cmath>
#include <limits>
#include <random>

#include "../../common/data/ResponseStock.h"

using namespace std;
using namespace nlohmann;

PrepaymentHandler::PrepaymentHandler(BroadCast *broadCast,
                                     CertificationCodeRepository *certification,
                                     Inventory* inventory) : broadCast(
  broadCast), certificationCodeRepository(certification), inventory(inventory) {
}

PrepaymentHandler::~PrepaymentHandler() {
}

string PrepaymentHandler::makeRequestStockMessage(int code, int qty) {
  string reqCode = "";
  if (code < 10) {
    reqCode.append("0");
  }
  reqCode.append(std::to_string(code));

  json request;
  request["msg_type"] = "req_stock";
  request["src_id"] = DVMNetworkData::getDVMId();
  request["dst_id"] = 0;
  request["msg_content"] = {
    {"item_code", reqCode},
    {"item_num", to_string(qty)}
  };

  return request.dump();
}

string PrepaymentHandler::makeRequestPrepaymentMessage(string certCode,
                                                       int itemCode,
                                                       int qty,
                                                       string dstId) {
  string reqItemCode = "";
  if (itemCode < 10) {
    reqItemCode.append("0");
  }
  reqItemCode.append(std::to_string(itemCode));

  json request;
  request["msg_type"] = "req_prepay";
  request["src_id"] = DVMNetworkData::getDVMId();
  request["dst_id"] = dstId;
  request["msg_content"] = {
    {"item_code", reqItemCode},
    {"item_num", qty},
    {"cert_code", certCode}
  };

  return request.dump();
}

pair<bool, string> PrepaymentHandler::prepaymentRequest(Beverage *beverage,
                                                        int qty,
                                                        string dstIp,
                                                        string dstId) {
  string certCode = generateCertificationCode(8);
  string requestMessage = makeRequestPrepaymentMessage(certCode, beverage->getCode(), qty, dstId);
  string response = broadCast->broadCast(dstIp, DVMNetworkData::getRequestPort(), requestMessage);
  try {
    json parsed = json::parse(response);
    if (parsed["msg_type"] != "resp_prepay") {
      return pair(false, certCode);
    }

    string availability = parsed["msg_content"]["availability"];
    if (availability == "T") {
      return pair(true, certCode);
    }

    return pair(false, certCode);
  } catch (const std::exception &e) {
    std::cerr << "[JSON Parse Error] " << e.what() << std::endl;
    return pair(false, certCode);
  }
}

ResponseStock *PrepaymentHandler::findAvailableDVM(Beverage *beverage, int qty) {
  string requestMessage = makeRequestStockMessage(beverage->getCode(), qty);

  vector<string> ips = DVMNetworkData::getDVMIPs();
  string availableDVMId;
  string availableDVMIp;
  int availableDVMCoorX = 0;
  int availableDVMCoorY = 0;
  double minDistance = numeric_limits<double>::max();

  for (int i = 0; i < ips.size(); i++) {
    string response = broadCast->broadCast(ips.at(i), DVMNetworkData::getRequestPort(), requestMessage);
    if (response.empty()) {
      continue;
    }
    try {
      json parsed = json::parse(response);
      string src_id = parsed["src_id"];
      string itemCode = parsed["msg_content"]["item_code"];
      int itemNum = parsed["msg_content"]["item_num"];
      if (parsed["msg_type"] != "resp_stock") {
        continue;
      }
      if (qty > itemNum) {
        continue;
      }
      int coorX = parsed["msg_content"]["coor_x"];
      int coorY = parsed["msg_content"]["coor_y"];
      double distance = findDistance(coorX, coorY);
      if (minDistance > distance) {
        minDistance = distance;
        availableDVMId = src_id;
        availableDVMIp = ips.at(i);
        availableDVMCoorX = coorX;
        availableDVMCoorY = coorY;
      }
    } catch (const std::exception &e) {
      std::cerr << "[JSON Parse Error] " << e.what() << std::endl;
      continue;
    }
  }
  if (minDistance == numeric_limits<double>::max()) {
    return nullptr;
  }

  return new ResponseStock(availableDVMCoorX, availableDVMCoorY, availableDVMId, availableDVMIp);
}

double PrepaymentHandler::findDistance(int x, int y) {
  return sqrt(pow(x - DVMNetworkData::getX(), 2) + pow(y - DVMNetworkData::getY(), 2));
}

std::string PrepaymentHandler::generateCertificationCode(int length) {
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "0123456789";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, charset.size() - 1);

  std::string result;
  for (int i = 0; i < length; ++i) {
    result += charset[dist(gen)];
  }

  return result;
}

/**
 * @brief 입력한 certification code가 DVM내 존재하는지 확인, 확인하는 CertCode가 string에서 vector<pair<string, int>> 자료로 바뀜
 * @param code 입력받은 certification code
 * @return 해당 cert code의 음료코드 (-1 if not exist)
 */
std::pair<int, int> PrepaymentHandler::PrePaymentCheck(std::string code) {
  std::optional<CodeInfo> info = certificationCodeRepository->findByCode(code);

  if(info != std::nullopt) {
    EraseCode(code);
    return {info->itemCode, info->itemNum};
  }
  return {-1, -1};
}

void PrepaymentHandler::EraseCode(std::string code) {
  certificationCodeRepository->deleteByCode(code);
}

/**
 * @brief 코드가 올바른 구성인지 확인, 막상 만들고보니쓸곳이있나.....
 */
bool PrepaymentHandler::IsvalidCode(std::string code){
  const std::string charset =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

  for (char c : code) {
    if (charset.find(c) == std::string::npos) {
      return false; // charset에 없는 문자가 있으면 false 반환
    }
  }
  return true; // 모든 문자가 charset에 포함되면 true 반환
}

bool PrepaymentHandler::handlePrepaymentRequest(string certCode, int itemCode, int qty) {
  //재고 확인
  if (!inventory->isAvailable(itemCode, qty)) {
    return false;
  }
  //인증 코드 저장
  certificationCodeRepository->save(certCode, itemCode, qty);
  //재고 차감
  inventory->decreaseStock(itemCode, qty);
  return true;
}