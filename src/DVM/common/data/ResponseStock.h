//
// Created by user on 25. 5. 16.
//

#ifndef RESPONSESTOCK_H
#define RESPONSESTOCK_H

#include <string>
using namespace std;

class ResponseStock {
  private:
    int coorX;
    int coorY;
    string srcId;
    string srcIp;
  public:
    ResponseStock(int coorX,  int coorY, string srcId, string srcIp);
    int getCoorX();
    int getCoorY();
    string getSrcId();
    string getSrcIp();
};



#endif //RESPONSESTOCK_H
