//
// Created by user on 25. 5. 13.
//

#ifndef DVMNETWORKDATA_H
#define DVMNETWORKDATA_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class DVMNetworkData {
  private:
    static string DVMId;
    static vector<std::string> DVMIPs;
    static int x;
    static int y;
    static int serverPort;
    static int requestPort;
    static map<string,string> initDataFromFile(const string& filename);
    static vector<string> splitIPs(const string& csv);

  public:
    DVMNetworkData() = delete;
    static void init(const string& filename);
    static string getDVMId();
    static vector<std::string> getDVMIPs();
    static int getX();
    static int getY();
    static int getServerPort();
    static int getRequestPort();
    static void setX(int x);
    static void setY(int y);
    static void setDVMIPs(const vector<string>& dvmIPs);
};



#endif //DVMNETWORKDATA_H
