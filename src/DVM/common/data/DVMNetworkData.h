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
    static string x;
    static string y;
    static map<string,string> initDataFromFile(const string& filename);
    static vector<string> splitIPs(const string& csv);

  public:
    DVMNetworkData() = delete;
    static void init(const string& filename);
    static string getDVMId();
    static vector<std::string> getDVMIPs();
    static string getX();
    static string getY();
};



#endif //DVMNETWORKDATA_H
