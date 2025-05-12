//
// Created by user on 25. 5. 13.
//

#ifndef DVMNETWORKDATA_H
#define DVMNETWORKDATA_H
#include <string>
#include <vector>


class DVMNetworkData {
  private:
    std::string DVMId;
    std::vector<std::string> DVMIPs;
    std::string x;
    std::string y;
  public:
    DVMNetworkData();
    ~DVMNetworkData();
    void initDataFromFile();
    std::string getDVMId();
    std::vector<std::string> getDVMIPs();
    std::string getX();
    std::string getY();
};



#endif //DVMNETWORKDATA_H
