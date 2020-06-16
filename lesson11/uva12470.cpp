#include <iostream>
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
typedef vector<vector<unsigned long long>> vvll;
typedef set<int> si;
typedef vector<si> vsi;
typedef unsigned long long ull;

vvll matmul(vvll& A, vvll& B, ull modulo){
    vvll res = vector<vector<ull>>(3, vector<ull>(3, 0));

    for(int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                {
                    res[i][j] += (A[i][k] * B[k][j]) % modulo;
                }
            }
        }
    }

    return res;
}

ull solution(ull s, vvll& mat, ull modulo){

    vvll A = mat;
    vvll res = vvll(3, vector<ull>(3, 0));
    res[0][0] = 1;
    res[1][1] = 1;
    res[2][2] = 1;

    while(s != 0){
        int b = s % 2;
        s /= 2;
        if(b){
            res = matmul(res, A, modulo);
        }

        A = matmul(A, A, modulo);
    }

    ull solution = ((res[0][0] * 2) % modulo + res[0][1]) % modulo;
    return solution;
}

int main() {
    ull s;
    cin >> s;
    ull modulo =  1000000009;

    vector<vector<ull>> A(3, vector<ull>(3, 0));
    A[0][0] = 1;
    A[0][1] = 1;
    A[0][2] = 1;
    A[1][0] = 1;
    A[1][1] = 0;
    A[1][2] = 0;
    A[2][0] = 0;
    A[2][1] = 1;
    A[2][2] = 0;

    while(s != 0){
        ull res;
        if (s==1) res = 0;
        else if (s==2) res = 1;
        else if (s==3) res = 2;
        else res = solution(s-3, A, modulo);
        cout << res << endl;
        cin >> s;
    }
    return 0;
}