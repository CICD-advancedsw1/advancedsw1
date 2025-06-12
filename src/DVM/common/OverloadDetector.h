//
// Created by kan02 on 2025-06-12.
//

#ifndef OVERLOADDETECTOR_H
#define OVERLOADDETECTOR_H


#include <iostream>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

class OverloadDetector {
  private:
    queue<steady_clock::time_point> timestamps;
    int thresholdPerSecond;

  public:
    OverloadDetector(int threshold) : thresholdPerSecond(threshold) {}

    bool checkOverload() {
      auto now = steady_clock::now();
      timestamps.push(now);

      // 1초 이전 타임스탬프 제거
      while (!timestamps.empty() &&
             duration_cast<milliseconds>(now - timestamps.front()).count() > 1000) {
        timestamps.pop();
             }

      return timestamps.size() >= thresholdPerSecond;
    }
};



#endif //OVERLOADDETECTOR_H
