//
//  main.cpp
//  P7
//
//  Name: James Ryan Epperson
//  UIN: 927009234

#include "MatrixMultiplication.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void clearVector(vector<vector<int>> &a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            a[i][j] = 0;
        }
    }
}

void printVector(const vector<vector<int>> &vec) {
    int n = vec.size();
    int nn = 0;
    std::cout << n << "x" << n << " matrix: \n";
    for (int i = 0; i < n; i++) {

        nn = vec[i].size();
        //Takes care of non-square vectors
        //Shouldn't have to deal with it but better safe than sorry
        for (int j = 0; j < nn; j++) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, const char * argv[]) {
    // File Read Operation
    string filename = "C:\\Users\\ryane\\OneDrive\\Documents\\_Working\\Current_Classes\\CSCE312\\Project 7\\Testcases\\";
    //Had my directory in the top
    filename += "testcase_100.in";
    
    string line;
    ifstream myfile(filename);

    vector<vector<int>> a;
    vector<vector<int>> b;
    string num;
    int n = 0;

    if (myfile.is_open())
    {
        getline(myfile, line);
        n = stoi(line);

        for (int i = 0; i < 2*n; i++) {
            vector<int> vec;
            getline(myfile, line);
            if (line == "") {
                i--;
                continue;
            }
            for (char x : line) {
                if (x == ' ' || line == "") {
                    vec.push_back(stoi(num));
                    num = "";
                }
                else
                    num += x;
            }

            if (i < n) {
                a.push_back(vec);
            }
            else {
                b.push_back(vec);
            }
        }

        myfile.close();
    }
    else {
        cout << "Could not open file";
        return 0;
    }

    vector<vector<int>> result;
    for (int i = 0; i < n; i++) {
        vector<int> vec;
        for (int j = 0; j < n; j++) {
            vec.push_back(0);
        }
        result.push_back(vec);
    }

    std::cout << "Finished building matrices" << endl;

    // Matrix Mult 1
    auto start = chrono::high_resolution_clock::now();
    matrixMult1(a, b, result, n);
    auto end = chrono::high_resolution_clock::now();
    auto process_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    std::cout << endl << "Standard matrix calculation runtime (seconds): " << endl;
    std::cout << "Time to process data: " << (float)process_time.count() / 1000 << endl;

    vector<vector<int>> temp = result;
    clearVector(result);
    
    // Matrix Mult 2
    start = chrono::high_resolution_clock::now();
    matrixMult2(a, b, result, n);
    end = chrono::high_resolution_clock::now();
    process_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    std::cout << endl << "Efficient matrix calculation runtime (seconds):" << endl;
    std::cout << "Time to process data: " << (float)process_time.count() / 1000 << endl;

    vector<vector<int>> temp2 = result;
    clearVector(result);
    
    // Matrix Mult 3
    start = chrono::high_resolution_clock::now();
    matrixMult3(a, b, result, n);
    end = chrono::high_resolution_clock::now();
    process_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    std::cout << endl << "Inefficient matrix calculation runtime (seconds): " << endl;
    std::cout << "Time to process data: " << (float)process_time.count() / 1000 << endl;

    vector<vector<int>> temp3 = result;
    
    // Matrix Mult Blocking

    std::cout << "Running blocks:" << endl;
    int block = 32;
    clearVector(result);

    start = chrono::high_resolution_clock::now();
    blockingMatrixMult(a, b, result, n, block);
    end = chrono::high_resolution_clock::now();
    process_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    std::cout << endl << "Blocking matrix calculation (" << block << ") runtime (seconds): " << endl;
    std::cout << "Time to process data: " << (float)process_time.count() / 1000 << endl;
    


    std::cout << endl << "True?: " << (temp == result && temp2 == temp && temp3 == temp) << endl << endl;
    return 0;
}
