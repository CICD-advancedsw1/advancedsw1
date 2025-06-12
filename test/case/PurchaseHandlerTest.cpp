#include <gtest/gtest.h>

#include "../../src/DVM/application/domain/Inventory.h"
#include "../../src/DVM/application/service/PurchaseHandler.h"
#include "../../src/DVM/common/data/DVMNetworkData.h"
#include "../fake/FakeBeverageRepsitory.h"
#include "../fake/FakePaymentSystem.h"

TEST(PurchaseHandlerTest, Purchase_Success) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakePaymentSystem payment;
  PurchaseHandler handler(&payment, &inventory);

  Beverage* purchaseBeverage = inventory.getBeverage(1);
  int initialStock = purchaseBeverage->getStock();
  int purchaseStock = 2;
  auto result = handler.purchase("1111-1111-1111-1111", purchaseBeverage, purchaseStock);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, "결제 성공");
  EXPECT_TRUE(payment.connected);
  EXPECT_EQ(payment.lastCard, "1111-1111-1111-1111");
  EXPECT_EQ(payment.lastAmount, 2000);

  EXPECT_EQ(inventory.getBeverage(1)->getStock(), initialStock-purchaseStock);
}

TEST(PurchaseHandlerTest, Purchase_Fail_InsufficientBalance) {
  FakeBeverageRepository fakeRepo;
  Inventory inventory(&fakeRepo);
  FakePaymentSystem payment;
  PurchaseHandler handler(&payment, &inventory);

  Beverage* purchaseBeverage = inventory.getBeverage(1);
  int initialStock = purchaseBeverage->getStock();
  int purchaseStock = 2;
  payment.shouldSucceed = false;
  auto result = handler.purchase("1111-1111-1111-1111", purchaseBeverage, purchaseStock);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, "잔액 부족");
  EXPECT_TRUE(payment.connected);
  EXPECT_EQ(inventory.getBeverage(1)->getStock(), initialStock);  // 인벤토리는 갱신되면 안 됨
}