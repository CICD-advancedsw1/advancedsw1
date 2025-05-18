// Your First C++ Program

#include <iostream>
#include <windows.h>

#include "src/DVM/common/DVMContext.h"

int main() {
    // 콘솔 UTF-8 설정
    SetConsoleOutputCP(CP_UTF8);
    // DVM 에 필요한 객체들의 생성 및 의존성 주입
    auto* dvmContext = new DVMContext();
    dvmContext->run();
    return 0;
}
