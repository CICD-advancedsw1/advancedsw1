cmake_minimum_required(VERSION 3.10)
project(DVM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-fexec-charset=CP949")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE

)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main
        main.cpp
        src/DVM/common/DVMContext.cpp
        src/DVM/presentation/UIFlow/Display.cpp
        src/DVM/application/domain/Inventory.cpp
        src/DVM/infrastructure/BroadCast.cpp
        src/DVM/infrastructure/PaymentSystem.cpp
        src/DVM/application/service/PrepaymentHandler.cpp
        src/DVM/application/service/PurchaseHandler.cpp
        src/DVM/common/data/Beverage.cpp
        src/DVM/common/data/Beverage.h
        src/DVM/infrastructure/repository/BeverageRepository.cpp
        src/DVM/infrastructure/repository/BeverageRepository.h
        src/DVM/presentation/IO/InputHandler.cpp
        src/DVM/presentation/IO/InputHandler.h
        src/DVM/presentation/IO/OutputFormatter.cpp
        src/DVM/presentation/IO/OutputFormatter.h
        src/DVM/common/data/DVMNetworkData.cpp
        src/DVM/common/data/DVMNetworkData.h
        include/nlohmann/json.hpp
        src/DVM/common/data/ResponseStock.cpp
        src/DVM/common/data/ResponseStock.h
        src/DVM/common/DVMServer.cpp
        src/DVM/common/DVMServer.h
        src/DVM/infrastructure/repository/CertificationCodeRepository.cpp
        src/DVM/infrastructure/repository/CertificationCodeRepository.h
)



# 테스트 실행 파일
add_executable(MyTests

        src/DVM/application/domain/Inventory.cpp
        src/DVM/infrastructure/repository/BeverageRepository.cpp
        src/DVM/infrastructure/repository/BeverageRepository.h
        src/DVM/common/data/Beverage.cpp
        src/DVM/common/data/Beverage.h

        test/inventory/inventoryTest.cpp
        test/FakeBeverageRepository.cpp
        test/FakeBeverageRepository.h  # 테스트 파일들 여기에 추가
)
target_link_libraries(MyTests
        gtest
        gtest_main
)
include(GoogleTest)
gtest_discover_tests(MyTests)

target_link_libraries(main PRIVATE ws2_32)
