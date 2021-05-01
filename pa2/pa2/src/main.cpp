// **************************************************************************
//  File       [main.cpp]
//  Author     [Chih-Yuan Chuang]
//  Synopsis   [The main program of 2021 spring Algorithm PA2]
// **************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include "../lib/tm_usage.h"  // record running time
#include "mps_tool.h"  // solve Maximum Planar Subset

using namespace std;

void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }
    // CommonNs::TmUsage tmusg;
    // CommonNs::TmStat stat;

    // read the input file
    fstream fin(argv[1]);  // input_file
    // fstream fout;  // output_file
    // fout.open(argv[2], ios::out);
    int num_endpoints;  // number of endpoints = 2N
    fin >> num_endpoints;
    vector<int> C(num_endpoints, -1);  // chords pair. For chord ab, C[a] = b, C[b] = a
    int a, b;  // chord ab
    for (int i = 0; i < num_endpoints / 2; i++) {
        fin >> a >> b;
        C[a] = b;
        C[b] = a;
    }

    // for (int i = 0; i < num_endpoints; i++) {
    //     cout << C[i] << endl;
    // }
    // cout << C.size();



    // tmusg.periodStart();
    // MpsTool NTUMpsTool;
    
    fin.close();
    // fout.close();
}