//
// Created by user on 25. 5. 13.
//

#include "DVMNetworkData.h"

void DVMNetworkData::init(const string& filename) {
  map<string,string> data = DVMNetworkData::initDataFromFile(filename);
  x = data.at("x");
  y = data.at("y");
  DVMId = data.at("DVMId");
  DVMIPs = DVMNetworkData::splitIPs(data.at("DVMIPs"));
}

map<string, string> DVMNetworkData::initDataFromFile(const string& filename) {
  ifstream file(filename);
  map<string, string> config;

  if (!file.is_open()) {
    cerr << "[Error] Failed to open file: " << filename << endl;
    return config;
  }

  string line;
  while (std::getline(file, line)) {
    istringstream iss(line);
    string key, value;

    if (!(iss >> key >> value)) {
      cerr << "[Warning] Skipping invalid line: " << line << endl;
      continue;
    }

    config[key] = value;
  }

  file.close();
  return config;
}

vector<string> DVMNetworkData::splitIPs(const string& csv) {
  vector<string> result;
  istringstream ss(csv);
  string token;
  while (getline(ss, token, ',')) {
    result.push_back(token);
  }
  return result;
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
