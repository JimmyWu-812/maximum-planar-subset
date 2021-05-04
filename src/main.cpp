#include <cstring>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void getResult(int, int, map<int,int>&, map<int,int>&, char**);

int main(int argc, char* argv[]){

    /* Read input file */
    fstream fin(argv[1]);
    fstream fout;
    int N;
    fin >> N;
    map<int,int> chords;
    map<int,int> result;
    int point1, point2;
    while (fin >> point1 >> point2){
        chords[point1] = point2;
        chords[point2] = point1;
    }
    fin.close();
    // cout << N << endl;
    // for(map<int,int>::iterator it=chords.begin(); it!=chords.end(); it++){
    //     cout << it->first << " " << it->second << endl;
    // }

    /* Array for memoization */
    int** M = new int*[N];
    char** C = new char*[N];
    for(int i=0; i<N; i++){
        M[i] = new int[i+1];
        C[i] = new char[i+1];
        M[i][i] = 0;
        C[i][i] = 'X';
    }
    
    /* DP implementation*/
    int k, in, ex;
    for(int l=1; l<N; l++){
        for(int i=0, j=i+l; j<N; i++, j++){
            k = chords[j];
            if(k == i){
                M[j][i] = M[j-1][i] + 1;
                C[j][i] = 'A';
            }
            else if(k<i || k>j){
                M[j][i] = M[j-1][i];
                C[j][i] = 'B';
            }
            else{
                in = (k+1==j ? 0 : M[j-1][k+1]) + M[k-1][i] + 1;
                ex = M[j-1][i];
                if(in > ex){
                    M[j][i] = in;
                    C[j][i] = 'C';
                }
                else{
                    M[j][i] = ex;
                    C[j][i] = 'X';
                }
            }
            // cout << j << " " << i << " " << M[j][i] << endl;
            // cout << j << " " << i << " " << C[j][i] << endl;
        }
    }
    // for(int j=0; j<N ; j++){
    //     for(int i=0; i<=j; i++){
    //         cout << M[j][i] << " ";
    //     }
    //     cout << endl;
    // }
    // for(int j=0; j<N ; j++){
    //     for(int i=0; i<=j; i++){
    //         cout << C[j][i] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << M[N-1][0] << endl;

    /* Get result */
    getResult(0, N-1, chords, result, C);
    // for(map<int,int>::iterator it=result.begin(); it!=result.end(); it++){
    //     cout << it->first << " " << it->second << endl;
    // }

    /* Write output file */
    fout.open(argv[2],ios::out);
    fout << M[N-1][0] << endl;
    for(map<int,int>::iterator it=result.begin(); it!=result.end(); it++){
        fout << it->first << " " << it->second << endl;
    }
    fout.close();

    return 0;
}

void getResult(int i, int j, map<int,int>& chords, map<int,int>& result, char** C){
    int k;
    while(j > i+1){
        k = chords[j];
        // cout << j << " " << i << " " << C[j][i] << endl;
        if(C[j][i] == 'A'){ //k==i
            result[j] = k;
            // chords.erase(j);
            // chords.erase(k);
            // cout << "chords " << j << " " << k << " added" << endl;
            getResult(i+1, j-1, chords, result, C);
            j = i - 1;
        }
        else if(C[j][i] == 'C'){ //i<k<j
            result[j] = k;
            // chords.erase(j);
            // chords.erase(k);
            // cout << "chords " << j << " " << k << " added" << endl;
            getResult(k, j-1, chords, result, C);
            j = k - 1;
        }
        else{ //k>j, k<i or i<k<j but not included
            // cout << "chords " << j << " " << k << " not added" << endl;
            j--;
        }
    }
    return;
}