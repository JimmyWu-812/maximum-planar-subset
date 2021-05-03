#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int p;
    fin >> p;
    vector<vector<int>> data;
    vector<int> tmp;
    tmp.push_back(0);
    tmp.push_back(0);
    int num1, num2;
    while (fin >> num1 >> num2){
        if(num1 > num2){
            tmp[0] = num2;
            tmp[1] = num1;
        }
        else{
            tmp[0] = num1;
            tmp[1] = num2;
        }
        data.push_back(tmp);
    }
    /*
    cout << p << endl;
    for(int i=0;i<data.size();i++){
        cout << data[i][0] << " " << data[i][1] << endl;
    }
    */
    fin.close();
    fout.close();
    return 0;
}