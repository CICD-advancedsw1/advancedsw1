//
// Created by user on 25. 5. 13.
//

#include "DVMNetworkData.h"
DVMNetworkData::DVMNetworkData() {
  initDataFromFile();
}
DVMNetworkData::~DVMNetworkData() {
}
void DVMNetworkData::initDataFromFile() {
  //TODO: file로 메타데이터 변경할 수 있도록
}
std::string DVMNetworkData::getDVMId() {
  return DVMId;
}
std::vector<std::string> DVMNetworkData::getDVMIPs() {
  return DVMIPs;
}
std::string DVMNetworkData::getX() {
  return x;
}
std::string DVMNetworkData::getY() {
  return y;
}
