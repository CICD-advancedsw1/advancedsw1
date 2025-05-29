#include "InputTimeoutHandler.h"
#include <iostream>
#include <chrono>

InputTimeoutHandler::InputTimeoutHandler() : stopFlag(false) {
    inputThread = std::thread(&InputTimeoutHandler::inputLoop, this);
}

InputTimeoutHandler::~InputTimeoutHandler() {
    stopFlag = true;
    if (inputThread.joinable()) inputThread.join();
}

std::optional<std::string> InputTimeoutHandler::getInput(int timeout_sec) {
    std::unique_lock<std::mutex> lock(mtx);

    if (cv.wait_for(lock, std::chrono::seconds(timeout_sec), [&]() { return !inputQueue.empty(); })) {
        std::string result = inputQueue.front();
        inputQueue.pop();
        return result;
    } else {
        return std::nullopt;
    }
}

void InputTimeoutHandler::inputLoop() {
    while (!stopFlag) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            stopFlag = true;
            break;
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            inputQueue.push(line);
        }
        cv.notify_one();
    }
}