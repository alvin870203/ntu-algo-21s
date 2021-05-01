// **************************************************************************
//  File       [mps_tool.cpp]
//  Author     [Chih-Yuan Chuang]
//  Synopsis   [The main program of 2021 spring Algorithm PA2]
// **************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include "mps_tool.h"

// Constructor
MpsTool::MpsTool(int num_endpoints)
    :   M(num_endpoints + 1, vector<int>(num_endpoints + 1, -1)),
        chosen_chord(num_endpoints + 1, vector<int>(num_endpoints + 1, -1)),
        optimal_chord(num_endpoints + 1, vector<int>(2, -1)),
        N(num_endpoints / 2) {
    cout << "Consturct MpsTool successfuly" << endl;
    // cout << M.size() << endl << N << endl;
}

// Calculate maximum planar subset
void MpsTool::MAXIMUM_PLANAR_SUBSET(vector<int>& C) {
    
    // initialize M[i][i] = 0
    for (int i = 0; i < 2 * N; i++) {
        M[i][i] = 0;
    }

    // initialize M[i-1][i] = 0, for j = i + 1 in case2
    for (int i = 1; i < 2 * N; i++) {
        M[i][i - 1] = 0;
    }

    // calculate MSP, record chosen_chord
    for (int length = 1; length < 2 * N; length++) {  // length = j - i, length of ij in consideration
        for (int i = 0; i < 2 * N - length; i++) {  // i in current consideration
            int j = i + length;  // length = j - i
            int k = C[j];  // chord jk in given circle graph
            if (k < i || k > j) {  // case1
                M[i][j] = M[i][j - 1];
                // cout << "case1" << endl;
            } else if (k == i) {  // case 2
                M[i][j] = M[i + 1][j - 1] + 1;
                chosen_chord[i][j] = k;
                // cout << "case2" << endl;
            } else {
                // cout << "case3" << endl;
                if (M[i][j - 1] >= M[i][k - 1] + 1 + M[k + 1][j - 1]) {
                    M[i][j] = M[i][j - 1];
                } else {
                    M[i][j] = M[i][k - 1] + 1 + M[k + 1][j - 1];
                    chosen_chord[i][j] = k;
                }
            }
        }
    }

    cout << M[0][2*N-1] << endl << chosen_chord[0][2*N-1];
}