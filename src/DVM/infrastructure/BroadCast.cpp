//
// Created by kan02 on 2025-05-12.
//

#include "BroadCast.h"

#include "../common/data/DVMNetworkData.h"

#include <winsock2.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

BroadCast::BroadCast() {
}
BroadCast::~BroadCast() {
}
std::string BroadCast::broadCast(std::string message) {
  vector<string> targetIPs = DVMNetworkData::getDVMIPs();

  for (const string& ip : targetIPs) {
    int sock = socket()
  }
  return nullptr;
}
