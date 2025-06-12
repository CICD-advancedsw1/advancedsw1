//
// Created by kan02 on 2025-05-18.
//

#include <gtest/gtest.h>

#include "../../src/DVM/application/domain/Inventory.h"
#include "../fake/FakeBeverageRepsitory.h"

TEST(InventoryTest, LoadInventory_Success) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  EXPECT_EQ(inventory.itemCount(), 7);
  EXPECT_EQ(inventory.getBeverage(1)->getName(), "콜라");
  EXPECT_EQ(inventory.getBeverage(2)->getName(), "사이다");
  EXPECT_EQ(inventory.getBeverage(3)->getName(), "녹차");
  EXPECT_EQ(inventory.getBeverage(4)->getName(), "홍차");
  EXPECT_EQ(inventory.getBeverage(5)->getName(), "밀크티");
  EXPECT_EQ(inventory.getBeverage(6)->getName(), "탄산수");
  EXPECT_EQ(inventory.getBeverage(7)->getName(), "보리차");
}

// getBeverage 에서 코드를 잘못 입력했을 경우 테스트
TEST(InventoryTest, GetBeverage_InvalidCode_ReturnsNullptr) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  EXPECT_EQ(inventory.getBeverage(0), nullptr);
  EXPECT_EQ(inventory.getBeverage(99999), nullptr);
}


// 수량 확인 메소드 테스트
TEST(InventoryTest, IsAvailable_WorksCorrectly) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  EXPECT_TRUE(inventory.isAvailable(1, 5));    // 충분
  EXPECT_FALSE(inventory.isAvailable(1, 15));  // 부족
  EXPECT_TRUE(inventory.isAvailable(2, 5));    // 충분
  EXPECT_FALSE(inventory.isAvailable(2, 10));  // 부족
  EXPECT_FALSE(inventory.isAvailable(99, 1));  // 잘못된 코드
  EXPECT_FALSE(inventory.isAvailable(0, 1));  // 잘못된 코드
}

// 코드 확인 메소드 테스트
TEST(InventoryTest, IsValidCode_WorksCorrectly) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  EXPECT_FALSE(inventory.isValidCode(100)); //items.size() 보다 큰 경우 실패
  EXPECT_FALSE(inventory.isValidCode(-1)); //0 보다 작을 경우 실패
  EXPECT_FALSE(inventory.isValidCode(0)); // 0일 경우 실패
  EXPECT_TRUE(inventory.isValidCode(1));
  EXPECT_TRUE(inventory.isValidCode(2));
  EXPECT_TRUE(inventory.isValidCode(3));
}

// Stock 업데이트 메소드 테스트
TEST(InventoryTest, DecreaseStock_Updates_Repository_And_Inventory) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  inventory.decreaseStock(1, 3);

  EXPECT_TRUE(fakeRepo.updateCalled);
  EXPECT_EQ(fakeRepo.updatedCode, 1);
  EXPECT_EQ(inventory.getBeverage(1)->getStock(), 7);
}

// Stock 업데이트 메소드 테스트
TEST(InventoryTest, DecreaseStock_Fail_Invalid_Code) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  inventory.decreaseStock(0, 3);

  EXPECT_FALSE(fakeRepo.updateCalled);
}

// Stock 업데이트 메소드 테스트
TEST(InventoryTest, DecreaseStock_Fail_NOT_ENOUGH_Qty) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);

  inventory.decreaseStock(1, 100);

  EXPECT_FALSE(fakeRepo.updateCalled);
}

// MAX STOCK 보다 크게 증가시켰을 시
TEST(InventoryTest, IncreaseStock_MAX) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  Beverage* testBeverage = inventory.getBeverage(1);
  int testBeverageQty = testBeverage->getStock();
  inventory.increaseStock(1, testBeverage->getMaxStock() + 1);

  EXPECT_EQ(testBeverage->getStock(), testBeverageQty);
}

// MAX STOCK 보다 작게 증가시켰을 때
TEST(InventoryTest, IncreaseStock_Success) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  Beverage* testBeverage = inventory.getBeverage(1);
  int testBeverageQty = testBeverage->getStock();
  inventory.increaseStock(1, 10);

  EXPECT_EQ(testBeverage->getStock(), testBeverageQty + 10);
}