#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <optional>
#include <atomic>

class InputTimeoutHandler {
public:
    InputTimeoutHandler();
    ~InputTimeoutHandler();

    // 타임아웃 기반 입력 요청 (초 단위)
    std::optional<std::string> getInput(int timeout_sec);

private:
    void inputLoop();

    std::queue<std::string> inputQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread inputThread;
    std::atomic<bool> stopFlag;
};