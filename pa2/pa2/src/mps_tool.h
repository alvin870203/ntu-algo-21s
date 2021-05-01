// **************************************************************************
//  File       [mps_tool.h]
//  Author     [Chih-Yuan Chuang]
//  Synopsis   [The main program of 2021 spring Algorithm PA2]
// **************************************************************************

#ifndef _MPS_TOOL_H
#define _MPS_TOOL_H

#include <vector>
#include <fstream>
using namespace std;

class MpsTool {
    public:
                MpsTool(int);  // Constructor
        void    MAXIMUM_PLANAR_SUBSET(vector<int>&);  // calculate maximum planar subset
        void    WRITE_ANS();//fstream&);  // write answer to output file
        
    private:
        int                     N;  // number of chords, N = num_endpoints / 2
        vector<vector<int>>     M;  // table to record maximum planar subset
        vector<vector<int>>     chosen_chord;  // table to record k of optimal chord jk
        vector<vector<int>>     optimal_chord;  // vector to store optimal chords for M[0, 2N-1]
        void    PRINT_CHORD(int, int);  // consturct optimal chord
};

#endif