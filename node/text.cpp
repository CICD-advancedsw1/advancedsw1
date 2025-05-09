#include<iostream>
#include<fstream>
#include<string>using namespace std;
 int main(void){
    ifstream readFile;
    readFile.open("test.txt");    //파일 열기
     if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            string str;
            getline(readFile, str);
            cout << str << endl;
        }
        readFile.close();
    }
    return 0;
}