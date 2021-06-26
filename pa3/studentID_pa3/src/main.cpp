// **************************************************************************
//  File       [main.cpp]
//  Author     [Chih-Yuan Chuang]
//  Synopsis   [The main program of 2021 spring Algorithm PA3]
// **************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <assert.h>
#include <algorithm>
#include <queue>
// #include "tm_usage.h"  // record running time
// #include "cb_tool.h"  // solve Cycle Breaking problem

using namespace std;

void help_message() {
    cout << "usage: cb <input_file> <output_file>" << endl;
}

class E {  // single edge (undirected graph)
    private:
        int i;  // vertex i -> j with weight w
        int j;
        int w;
    public:
        E(int _i, int _j, int _w) { i = _i; j = _j; w = _w; }
        int get_w() const { return w; }
        const bool operator < (const E& e) const { return w < e.get_w(); }
        int get_i() { return i; }
        int get_j() { return j; }
        pair<int, int> get_ij() { return pair<int, int>(i, j); }
};

class UnionFind {  // disjoint set for MST-Kruskal
    private:
        vector<int> ranks;  // ranks of each element
        vector<int> parents;  // parent of each element
        int element_num;  // total number of elements
    public:
        UnionFind(int _element_num) {
            ranks = vector<int>(_element_num, 0);
            parents = vector<int>(_element_num, 0);
            int idx = 1;
            while (idx <= _element_num) {
                parents[idx - 1] = idx - 1;
                idx = idx + 1;
            }
            element_num = _element_num;
        }
        int Find(int idx) {
            if (parents[idx] != idx) {
                return Find(parents[idx]);
            } else {
                return idx;
            }
        }
        bool SameParent(int idx1, int idx2) {
            if (Find(idx1) != Find(idx2)) {
                return false;
            } else {
                return true;
            }
        }
        void Union(int idx1, int idx2) {
            int par_idx1 = Find(idx1);
            int par_idx2 = Find(idx2);
            if (par_idx1 != par_idx2) {
                if (ranks[par_idx1] < ranks[par_idx2]) {
                    parents[par_idx1] = par_idx2;
                } else if (ranks[par_idx1] < ranks[par_idx2]) {
                    parents[par_idx2] = par_idx1;
                } else {  // ranks[par_idx1] == ranks[par_idx2]
                    parents[par_idx2] = par_idx1;
                    ranks[par_idx1]++;
                }
            }
            return;
        }
};

int main(int argc, char* argv[]) {

    // check arguements
    if (argc != 3) {
        help_message();
        return 0;
    }

    // for time and memory usage record
    // CommonNs::TmUsage tmusg;
    // CommonNs::TmStat stat;
    // tmusg.periodStart();

    // read the graph settings from input file
    fstream fin(argv[1]);  // input file
    char dir_type;  // <u, d>
    int n, m;
    fin >> dir_type >> n >> m;

    // some variabels definition
    vector<int> deg_neg(n, 0);  // indegree of each vertex
    vector<int> w_neg(n, 0);  // correspoinding weight
    vector<int> deg_pos(n, 0);  // outdegree of earch vertex
    vector<int> w_pos(n, 0);  // correspoinding weight
    vector<vector<pair<int, int>>> G;  // graph: Graph<Vertices<<Vertex, Weight>>>
    vector<vector<pair<int, int>>> G_T;  // inverse of graph: Graph<Vertices<<Vertex, Weight>>>
    vector<E> edges;  // list of edges
    vector<E> e_ans;  // removed edges to form acyclic graph
    e_ans.clear();
    int w_ans = 0;  // total weight of removed edges


    // initialize  directed graph
    if (dir_type == 'd') {
        G.clear();
        int idx = 1;
        while (idx <= n) {
            G.push_back(vector<pair<int, int>>());
            G_T.push_back(vector<pair<int, int>>());
            idx = idx + 1;
        }
    }

    // read the graph structure from input file
    int i, j, w;
    int idx = 1;
    while (idx <= m) {
        fin >> i >> j >> w;
        switch (dir_type)
        {
            case 'u':
                edges.push_back(E(i, j, w));
                cout << "un-directed" << endl;
                break;
            case 'd':
                deg_pos[i] += 1;
                w_pos[i] += w;
                deg_neg[j] += 1;
                w_neg[j] += w;
                G[i].push_back(pair<int, int>(j, w));
                G_T[j].push_back(pair<int, int>(i, w));
                cout << "directed" << endl;
                break;
            default:
                cout << "wrong dir_type, should be <u or d>" << endl;
                return 0;
                break;
        }
        idx = idx + 1;
    }
    fin.close();
    

    // solve CB
    switch (dir_type)
    {
        case 'u':  // use MST-Kruskal
        {
            UnionFind MST(n);
            vector<bool> remained(m, true);
            sort(edges.begin(), edges.end());
            int idx = m;
            while (idx >= 1) {
                int v1 = edges[idx - 1].get_i();
                int v2 = edges[idx - 1].get_j();
                if (MST.SameParent(v1, v2) != true) {
                    MST.Union(v1, v2);
                    remained[idx - 1] = false;
                }
                idx--;
            }
            idx = 1;
            while (idx <= m) {
                if (remained[idx - 1] == true) {
                    w_ans += edges[idx - 1].get_w();
                    e_ans.push_back(edges[idx - 1]);
                }
                idx++;
            }
            cout << "Kruskal alg" << endl;
            // cout << w_ans << endl;;
            break;
        }
        case 'd':  // use GA algorithm
        {
            // vertex sequence: s = concat(s1, s2)
            // vector<int> s;
            vector<int> s1;
            vector<int> s2;
            cout << "s2 origin" << s2.size() << endl;
            
            queue<int> sinks;  // deg_pos = 0
            queue<int> sources;  // deg_neg = 0
            vector<bool> remained(m, true);
            int used_num = 0;

            int idx = 1;
            while (idx <= n) {
                if (deg_neg[idx - 1] == 0) {
                    remained[idx - 1] = false;
                    sources.push(idx - 1);
                    cout << idx - 1 << endl;
                }
                if (deg_pos[idx - 1] == 0) {
                    remained[idx - 1] = false;
                    sinks.push(idx - 1);
                }
                idx++;
            }
            cout << sources.size() << endl;
            // cout << "line211" << endl;
            while (used_num <= n) {
                cout << "line213 " << used_num << endl;
                // remove source from G
                while (sources.empty() == false) {
                    int node = sources.front();
                    sources.pop();
                    cout << node << endl;
                    s1.push_back(node);
                    used_num++;
                    int idx_v = 0;
                    while (idx_v < G[node].size()) {
                        int v = G[node][idx_v].first;

                        if (remained[v]) {
                            deg_neg[v]--;
                            w_neg[v] -= G[node][idx_v].second;
                            if (deg_neg[v] == 0) {
                                remained[v] = false;
                                cout << "_" << v << endl;
                                sources.push(v);
                            }
                        }
                        idx_v++;
                    }
                }
                cout << "line 240 s2_size = " << s2.size() << endl;

                cout << "line235" << endl;
                // remove sink from G
                while (sinks.empty() == false) {
                    int node = sinks.front();
                    sinks.pop();
                    cout << "s2 " << node << endl;
                    s2.push_back(node);
                    used_num++;
                    int idx_v = 0;
                    while (idx_v < G_T[node].size()) {
                        int v = G_T[node][idx_v].first;
                        if (remained[v]) {
                            deg_pos[v]--;
                            w_pos[v] -= G_T[node][idx_v].second;
                            if (deg_pos[v] == 0) {
                                remained[v] = false;
                                sinks.push(v);
                            }
                        }
                        idx_v++;
                    }
                }
                cout << "line 264 s2_size = " << s2.size() << endl;

                cout << "line256" << endl;
                if (used_num >= n) {
                    cout << "break used num " << used_num << endl;
                    break;
                }

                // choose a vertex "node" for which delta[node] is maximum
                // remove it form G
                int delta_max = -2000000000;  // -inf
                int node_max = -1;
                int idx_node = 0;
                while (idx_node < n) {
                    if (remained[idx_node]) {
                        if (delta_max < w_pos[idx_node] - w_neg[idx_node]) {
                            node_max = idx_node;
                            delta_max =  w_pos[idx_node] - w_neg[idx_node];
                        }
                    }
                    idx_node++;
                }
                if (node_max == -1 || !remained[node_max]) {
                    continue;
                }
                remained[node_max] = false;
                s1.push_back(node_max);
                cout << node_max << endl;
                used_num++;
                int idx_v = 0;
                while (idx_v < G[node_max].size()) {
                    int v = G[node_max][idx_v].first;
                    if (remained[v]) {
                        deg_neg[v]--;
                        w_neg[v] -= G[node_max][idx_v].second;
                        if (deg_neg[v] == 0) {
                            remained[v] = false;
                            sources.push(v);
                        }
                    }
                    idx_v++;
                }
                idx_v = 0;
                while (idx_v < G_T[node_max].size()) {
                    int v = G_T[node_max][idx_v].first;
                    if (remained[v]) {
                        deg_pos[v]--;
                        w_pos[v] -= G_T[node_max][idx_v].second;
                        if (deg_pos[v] == 0) {
                            remained[v] = false;
                            sinks.push(v);
                        }
                    }
                    idx_v++;
                }
                cout << "line303" << endl;
            }
            cout << "ussed num " << used_num << endl;
            
            vector<int> s(s1);
            int s2_size = s2.size();
            cout << "s2_size = " << s2.size() << endl;
            while (s2_size >= 1) {
                s.push_back(s2[s2_size - 1]);
                s2_size--;
            }
            
            cout << "line315" << endl;
            vector<int> node2s(n, -1);
            idx = 1;
            while (idx <= n) {
                cout << "line328 " << s[idx - 1] << " " << n << endl;
                node2s[s[idx - 1]] = idx - 1;
                idx++;
            }
            cout << "line322" << endl;
            idx = 1;
            while (idx <= n) {
                cout << "line325" << endl;
                int idx_j = 1;
                while (idx_j <= G[idx - 1].size()) {
                    if (node2s[idx - 1] > node2s[G[idx - 1][idx_j - 1].first]) {
                        cout << "line329" << endl;
                        e_ans.push_back(E(idx - 1, G[idx - 1][idx_j - 1].first, G[idx - 1][idx_j - 1].second));
                        w_ans += G[idx - 1][idx_j - 1].second;
                    }
                    idx_j++;
                }
                idx++;
            }
            cout << "GR alg" << endl;
            for (int i = 0; i < s.size(); i++) {
                cout << s[i] << endl;
            }
            break;
        }
        default:
            cout << "wrong dir_type, should be <u or d>" << endl;
            return 0;
            break;
    }

    // write answear to output file
    fstream fout;  // output file
    fout.open(argv[2], ios::out);
    fout << w_ans << endl;
    idx = 1;
    while (idx <= e_ans.size()) {
        fout << e_ans[idx - 1].get_i() << " ";
        fout << e_ans[idx - 1].get_j() << " ";
        fout << e_ans[idx - 1].get_w() << endl;
        idx++;
    }
    fout.close();


    // print time and memory usage
    // tmusg.getPeriodUsage(stat);
    // cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    // cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    return 0;
}


