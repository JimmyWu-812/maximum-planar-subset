#include <cstring>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]){

    /* Read file */
    fstream fin(argv[1]);
    fstream fout;
    // fout.open(argv[2],ios::out);
    int N;
    fin >> N;
    map<int,int> data;
    int num1, num2;
    while (fin >> num1 >> num2){
        data[num1] = num2;
        data[num2] = num1;
    }
    // cout << p << endl;
    // for(map<int,int>::iterator it=data.begin(); it!=data.end(); it++){
    //     cout << it->first << " " << it->second << endl;
    // }

    /* Array for memoization */
    int** dp = new int*[N];
    for(int i=0; i<N; i++){
        dp[i] = new int[i+1];
        dp[i][i] = 0;
    }

    /* DP implementation - main part */
    int k, in, ex;
    for(int l=1; l<N; l++){
        for(int i=0, j=i+l; j<N; i++, j++){
            k = data[j];
            if(k == i){
                dp[j][i] = dp[j-1][i] + 1;
            }
            else if(k<i || k>j){
                dp[j][i] = dp[j-1][i];
            }
            else{
                in = (k+1==j ? 0 : dp[j-1][k+1]) + dp[k-1][i] + 1;
                ex = dp[j-1][i];
                dp[j][i] = in>ex ? in : ex;
            }
        }
    }
    // for(int j=0; j<N ; j++){
    //     for(int i=0; i<=j; i++){
    //         cout << dp[j][i] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << dp[N-1][0] << endl;

    /* Close file */
    fin.close();
    fout.close();
    return 0;
}