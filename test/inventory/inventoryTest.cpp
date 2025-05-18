//
// Created by kan02 on 2025-05-18.
//

#include "inventoryTest.h"
#include <gtest/gtest.h>

#include "../../src/DVM/application/domain/Inventory.h"
#include "../FakeBeverageRepository.h"

TEST(InventoryTest, IsAvaliableWorks) {
  auto* repo = new FakeBeverageRepository();
  Inventory inventory(repo);

  EXPECT_TRUE(inventory.isAvailable(1, 3));
  EXPECT_FALSE(inventory.isAvailable(1, 100));
}