//
//  MatrixMultiplication.cpp
//  P7
//
//  Name: James Ryan Epperson
//  UIN: 927009234
#define MIN(a,b) ((a)<(b) ? (a):(b))
#include "MatrixMultiplication.h"

void matrixMult1(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b, std::vector<std::vector<int> >& result, const int n) {
    //Usual way
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum = 0;

            for (int k = 0; k < n; k++) {
                sum += a[j][k] * b[k][i];
            }
            result[j][i] = sum;
        }
    }
}

void matrixMult2(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b, std::vector<std::vector<int> >& result, const int n) {
    //Most efficient using cache
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp = a[j][i];

            for (int k = 0; k < n; k++) {
                result[j][k] += temp * b[i][k];
            }
        }
    }
}

void matrixMult3(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b, std::vector<std::vector<int> >& result, const int n){
    //Ineficient use
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp = b[j][i];

            for (int k = 0; k < n; k++) {
                result[k][i] += temp * a[k][j];
            }
        }
    }
}

void blockingMatrixMult(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b, std::vector<std::vector<int> >& result, const int n, const int block_size) {
    
    int temp;
    for (int kk = 0; kk < n; kk += block_size) {
        for (int jj = 0; jj < n; jj += block_size) {

            for (int i = 0; i < n; i += 1) {
                for (int j = jj; j < MIN(jj + block_size, n); j += 1) {

                    temp = 0;
                    for (int k = kk; k < MIN(kk + block_size , n); k += 1) {
                        temp += a[i][k] * b[k][j];
                    }
                    result[i][j] += temp;
                }
            }
        }
    }
}

