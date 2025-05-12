// Your First C++ Program

#include <iostream>

#include "src/DVM/common/DVMContext.h"

int main() {
    std::cout << "Hello World!";
    std::cout << "nunsori testing2";

    // DVM 에 필요한 객체들의 의존성 주입 및 생성 (조립)
    auto* dvmContext = new DVMContext();
    dvmContext->run();
    return 0;
}
