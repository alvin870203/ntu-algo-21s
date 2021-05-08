// **************************************************************************
//  File       [main.cpp]
//  Author     [Chih-Yuan Chuang]
//  Synopsis   [The main program of 2021 spring Algorithm PA2]
// **************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include "tm_usage.h"  // record running time
#include "mps_tool.h"  // solve Maximum Planar Subset

using namespace std;

void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]) {

    // check arguements
    if (argc != 3) {
        help_message();
        return 0;
    }

    // for time and memory usage record
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    tmusg.periodStart();

    // read the input file
    fstream fin(argv[1]);  // input_file
    int num_endpoints;  // number of endpoints = 2N
    fin >> num_endpoints;
    vector<int> C(num_endpoints, -1);  // chords pair. For chord ab, C[a] = b, C[b] = a
    int a, b;  // chord ab
    for (int i = 0; i < num_endpoints / 2; i++) {
        fin >> a >> b;
        C[a] = b;
        C[b] = a;
    }
    fin.close();

    // solving maximun planar subset problem & write output file
    fstream fout;  // output_file
    fout.open(argv[2], ios::out);
    MpsTool NTUMpsToll(num_endpoints);
    NTUMpsToll.MAXIMUM_PLANAR_SUBSET(C);  // calculate M, chosen_chord buttom-up
    NTUMpsToll.WRITE_ANS(fout);  // construct optim_chord recursively, write ans to fout
    fout.close();

    // print time and memory usage
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    return 0;
}