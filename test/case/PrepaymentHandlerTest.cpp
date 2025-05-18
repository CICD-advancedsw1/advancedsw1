#include <gtest/gtest.h>

#include "../../include/nlohmann/json.hpp"
#include "../../src/DVM/application/domain/Inventory.h"
#include "../../src/DVM/application/service/PrepaymentHandler.h"
#include "../../src/DVM/common/data/DVMNetworkData.h"
#include "../../src/DVM/common/data/ResponseStock.h"
#include "../fake/FakeBeverageRepsitory.h"
#include "../fake/FakeBroadCast.h"
#include "../fake/FakeCertificationRepository.h"
//
// Created by user on 25. 5. 18.
//


TEST(PrepaymentHandlerTest, MakeRequestStockMessage_FormatsCorrectJson) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeBroadCast fakeBroadCast;
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  std::string jsonStr = handler.makeRequestStockMessage(5, 3);

  nlohmann::json parsed = nlohmann::json::parse(jsonStr);

  EXPECT_EQ(parsed["msg_type"], "req_stock");
  EXPECT_EQ(parsed["dst_id"], 0);
  EXPECT_EQ(parsed["msg_content"]["item_code"], "05");
  EXPECT_EQ(parsed["msg_content"]["item_num"], "3");
  EXPECT_EQ(parsed["src_id"], DVMNetworkData::getDVMId());

}

TEST(PrepaymentHandlerTest, MakeRequestStockMessage_TwoDigitItemCode) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeBroadCast fakeBroadCast;
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  std::string jsonStr = handler.makeRequestStockMessage(12, 3);

  nlohmann::json parsed = nlohmann::json::parse(jsonStr);

  EXPECT_EQ(parsed["msg_type"], "req_stock");
  EXPECT_EQ(parsed["dst_id"], 0);
  EXPECT_EQ(parsed["msg_content"]["item_code"], "12");
  EXPECT_EQ(parsed["msg_content"]["item_num"], "3");
  EXPECT_EQ(parsed["src_id"], DVMNetworkData::getDVMId());

}

TEST(PrepaymentHandlerTest, MakeRequestPrepaymentMessage_GeneratesCorrectJson) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeBroadCast fakeBroadCast;
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  std::string certCode = "ABC123";
  int itemCode = 5;
  int qty = 2;
  std::string dstId = "T2";

  std::string result = handler.makeRequestPrepaymentMessage(certCode, itemCode, qty, dstId);

  nlohmann::json parsed = nlohmann::json::parse(result);

  EXPECT_EQ(parsed["msg_type"], "req_prepay");
  EXPECT_EQ(parsed["src_id"], DVMNetworkData::getDVMId());
  EXPECT_EQ(parsed["dst_id"], dstId);
  EXPECT_EQ(parsed["msg_content"]["item_code"], "05");  // padding 확인
  EXPECT_EQ(parsed["msg_content"]["item_num"], "2");
  EXPECT_EQ(parsed["msg_content"]["cert_code"], certCode);
}

TEST(PrepaymentHandlerTest, MakeRequestPrepaymentMessage_TwoDigitItemCode) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeBroadCast fakeBroadCast;
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  std::string result = handler.makeRequestPrepaymentMessage("XYZ789", 15, 10, "DVM-10");
  nlohmann::json parsed = nlohmann::json::parse(result);

  EXPECT_EQ(parsed["msg_content"]["item_code"], "15"); // No padding
  EXPECT_EQ(parsed["msg_content"]["item_num"], "10");
  EXPECT_EQ(parsed["msg_content"]["cert_code"], "XYZ789");
}

TEST(PrepaymentHandlerTest, FindDistance_ReturnsCorrectDistance) {
  // 테스트용으로 DVM 위치를 고정 (예: (3, 4))
  DVMNetworkData::setX(3);
  DVMNetworkData::setY(4);

  PrepaymentHandler handler(nullptr, nullptr, nullptr);

  // 입력 좌표 (0, 0)과의 거리 = sqrt(3^2 + 4^2) = 5
  double result = handler.findDistance(0, 0);

  EXPECT_NEAR(result, 5.0, 0.0001);
}

TEST(PrepaymentHandlerTest, GenerateCertificationCode_ReturnsCorrectLengthAndCharset) {
  PrepaymentHandler handler(nullptr, nullptr, nullptr);

  std::string code = handler.generateCertificationCode(10);

  EXPECT_EQ(code.length(), 10);

  // 모든 문자들이 허용된 charset 안에 들어 있는지 확인
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "0123456789";

  for (char c : code) {
    EXPECT_NE(charset.find(c), std::string::npos) << "Invalid character in cert code: " << c;
  }
}

TEST(PrepaymentHandlerTest, PrepaymentRequest_Success_ReturnsTrue) {
  FakeBroadCast fakeBroadCast;
  fakeBroadCast.ipToResponse["127.0.0.1"] = R"(
        {
            "msg_type": "resp_prepay",
            "src_id" : "T2",
            "dst_id" : "T1",
            "msg_content": {
                "item_code" : "01",
                "item_num" : "20",
                "availability": "T"
            }
        }
    )";

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  Beverage bev("콜라", 1000, 10, 1);

  auto result = handler.prepaymentRequest(&bev, 2, "127.0.0.1", "DVM-01");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second.size(), 8);  // 인증코드 길이
}

TEST(PrepaymentHandlerTest, PrepaymentRequest_Failure_ReturnsFalse) {
  FakeBroadCast fakeBroadCast;
  fakeBroadCast.ipToResponse["127.0.0.1"] = R"(
        {
            "msg_type": "resp_prepay",
            "src_id" : "T2",
            "dst_id" : "T1",
            "msg_content": {
                "item_code" : "01",
                "item_num" : "1",
                "availability": "F"
            }
        }
    )";

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);
  Beverage bev("콜라", 1000, 10, 1);

  auto result = handler.prepaymentRequest(&bev, 2, "127.0.0.1", "DVM-01");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second.size(), 8);
}

TEST(PrepaymentHandlerTest, PrepaymentRequest_InvalidMsgType_ReturnsFalse) {
  FakeBroadCast fakeBroadCast;
  fakeBroadCast.ipToResponse["127.0.0.1"] = R"(
        {
            "msg_type": "wrong_msg_type",
            "src_id" : "T2",
            "dst_id" : "T1",
            "msg_content": {
                "item_code" : "01",
                "item_num" : "1",
                "availability": "F"
            }
        }
    )";

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  Beverage bev("콜라", 1000, 10, 1);

  auto result = handler.prepaymentRequest(&bev, 2, "127.0.0.1", "DVM-01");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second.size(), 8);
}

TEST(PrepaymentHandlerTest, PrepaymentRequest_InvalidJson_ReturnsFalse) {
  FakeBroadCast fakeBroadCast;
  fakeBroadCast.ipToResponse["127.0.0.1"] = "{invalid json!!!}";

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  Beverage bev("콜라", 1000, 10, 1);

  auto result = handler.prepaymentRequest(&bev, 2, "127.0.0.1", "DVM-01");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second.size(), 8);
}

TEST(PrepaymentHandlerTest, FindAvailableDVM_ReturnsClosestAvailableDVM) {
  // DVM 위치 기준 설정
  DVMNetworkData::setX(0);
  DVMNetworkData::setY(0);

  // 테스트용 IP 리스트
  std::vector<std::string> testIPs = {"192.168.0.1", "192.168.0.2"};
  DVMNetworkData::setDVMIPs(testIPs);  // 이 메서드가 있어야 함

  // FakeBroadCast 설정
  FakeBroadCast fakeBroadCast;
  fakeBroadCast.ipToResponse["192.168.0.1"] = R"({
        "msg_type": "resp_stock",
        "src_id": "T1",
        "msg_content": {
            "item_code": "01",
            "item_num": 5,
            "coor_x": 3,
            "coor_y": 4
        }
    })";  // 거리 5

  fakeBroadCast.ipToResponse["192.168.0.2"] = R"({
        "msg_type": "resp_stock",
        "src_id": "T2",
        "msg_content": {
            "item_code": "01",
            "item_num": 10,
            "coor_x": 1,
            "coor_y": 1
        }
    })";  // 거리 √2

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  Beverage cola("콜라", 1000, 10, 1);

  ResponseStock* result = handler.findAvailableDVM(&cola, 2);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getSrcIp(), "192.168.0.2");  // 가장 가까운 IP
  EXPECT_EQ(result->getSrcId(), "T2");
  EXPECT_EQ(result->getCoorX(), 1);
  EXPECT_EQ(result->getCoorY(), 1);

  delete result;
}

TEST(PrepaymentHandlerTest, FindAvailableDVM_AllInsufficientStock_ReturnsNullptr) {
  // DVM 위치 기준 설정
  DVMNetworkData::setX(0);
  DVMNetworkData::setY(0);

  // 테스트용 IP 리스트
  std::vector<std::string> testIPs = {"192.168.0.1"};
  DVMNetworkData::setDVMIPs(testIPs);  // 이 메서드가 있어야 함

  // FakeBroadCast 설정
  FakeBroadCast fakeBroadCast;
  fakeBroadCast.ipToResponse["192.168.0.1"] = R"({
        "msg_type": "resp_stock",
        "src_id": "DVM-01",
        "msg_content": {
            "item_code": "01",
            "item_num": 1,
            "coor_x": 1,
            "coor_y": 1
        }
    })";  // 요청 수량보다 작음

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository fakeCertRepo;

  PrepaymentHandler handler(&fakeBroadCast, &fakeCertRepo, &inventory);

  Beverage cola("콜라", 1000, 10, 1);

  ResponseStock* result = handler.findAvailableDVM(&cola, 2);

  EXPECT_EQ(result, nullptr);
}

TEST(PrepaymentHandlerTest, HandlePrepaymentRequest_Success) {

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository certRepo;

  PrepaymentHandler handler(nullptr, &certRepo, &inventory);

  int initialStock = inventory.getBeverage(1)->getStock();
  std::string certCode = "TEST123";
  int itemCode = 1;
  int qty = 2;


  bool result = handler.handlePrepaymentRequest(certCode, itemCode, qty);
  EXPECT_TRUE(result);
  EXPECT_TRUE(certRepo.saved);
  EXPECT_EQ(certRepo.savedCode, certCode);
  EXPECT_EQ(certRepo.savedItemCode, itemCode);
  EXPECT_EQ(certRepo.savedQty, qty);

  EXPECT_EQ(inventory.getBeverage(1)->getStock(), initialStock - qty );
}

TEST(PrepaymentHandlerTest, HandlePrepaymentRequest_StockUnavailable_Fails) {

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakeCertificationRepository certRepo;

  PrepaymentHandler handler(nullptr, &certRepo, &inventory);

  int initialStock = inventory.getBeverage(1)->getStock();
  std::string certCode = "TEST123";
  int itemCode = 1;
  int qty = 20;


  bool result = handler.handlePrepaymentRequest(certCode, itemCode, qty);
  EXPECT_FALSE(result);
  EXPECT_FALSE(certRepo.saved);

  EXPECT_EQ(inventory.getBeverage(1)->getStock(), initialStock);
}

TEST(PrepaymentHandlerTest, PrePaymentCheck_Success) {
  FakeCertificationRepository certRepo;
  certRepo.save("VALID123", 5, 3);  // 미리 저장

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  PrepaymentHandler handler(nullptr, &certRepo, &inventory);

  auto result = handler.PrePaymentCheck("VALID123");

  EXPECT_EQ(result.first, 5);
  EXPECT_EQ(result.second, 3);
  EXPECT_TRUE(certRepo.deleteCalled);
  EXPECT_EQ(certRepo.savedCode, "");
}

TEST(PrepaymentHandlerTest, PrePaymentCheck_CodeNotFound) {
  FakeCertificationRepository certRepo; // 아무것도 저장하지 않음

  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  PrepaymentHandler handler(nullptr, &certRepo, &inventory);

  auto result = handler.PrePaymentCheck("UNKNOWN");

  EXPECT_EQ(result.first, -1);
  EXPECT_EQ(result.second, -1);
  EXPECT_FALSE(certRepo.deleteCalled);
}