#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <climits>
#include <cstdlib>
// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

/********** Max Flow **********/


int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}


int main() {
    int n_states, n_supp, n_fact, n_trans;
    cin >> n_states >> n_supp >> n_fact >> n_trans;

    int v_ctr = 0;
    int MAKOR = v_ctr++;
    int BOR = v_ctr++;

    std::map<string,int> states;

    vector<iii> edges;
    vector<string> suppliers;
    for (int i = 0; i < n_supp; ++i) {
        string supp;
        cin >> supp;
        states[supp] = v_ctr++;
        ii e = {MAKOR, states[supp]};
        edges.push_back({1, e});
        suppliers.push_back(supp);
    }

    vector<string> factories;
    for (int i = 0; i < n_fact; ++i) {
        string fact;
        cin >> fact;
        states[fact] = v_ctr++;
        ii e = {states[fact], BOR};
        edges.push_back({1, e});
        factories.push_back(fact);
    }

    for (int i = 0; i < n_trans; ++i) {
        int n_lines;
        cin >> n_lines;
        int in_node = v_ctr++;
        int out_node = v_ctr++;
        edges.push_back({1, {in_node, out_node}}); // enforce 1 on each line service

        for (int j = 0; j < n_lines; ++j) {
            string st;
            cin >> st;
            if(states.count(st) == 0){
                states[st] = v_ctr++;
            }

            edges.push_back({1, {states[st], in_node}}); // in
            edges.push_back({1, {out_node, states[st]}}); // out
        }
    }

    cout << EdmondsKarp(v_ctr, edges, MAKOR, BOR) << endl;

    return 0;
}