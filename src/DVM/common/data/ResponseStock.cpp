//
// Created by user on 25. 5. 16.
//

#include "ResponseStock.h"
ResponseStock::ResponseStock(int coorX, int coorY, string srcId, string srcIp){
  this->coorX = coorX;
  this->coorY = coorY;
  this->srcId = srcId;
  this->srcIp = srcIp;
}
int ResponseStock::getCoorX() {
  return coorX;
}
int ResponseStock::getCoorY() {
  return coorY;
}
string ResponseStock::getSrcId() {
  return srcId;
}
string ResponseStock::getSrcIp() {
  return srcIp;
}
