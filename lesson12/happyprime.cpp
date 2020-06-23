#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

bool isPrime(ll n) {
    if (n < 2)
        return false;
    ll sqrtn = sqrt(n);
    for (ll i = 2; i <= sqrtn; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int getit(int n) {
    int res = 0;
    while (n != 0) {
        res += pow(n % 10, 2);
        n /= 10;
    }
    return res;
}

int main() {
	int P, m, K;
    cin >> P;
    for (size_t i = 0; i < P; i++)
    {
        cin >> K >> m;
        cout << K << " " << m << " ";
        if (!isPrime(m)) {
            cout << "NO";
        }
        else {
            while (m >= 10) {
                m = getit(m);
            }
            switch (m)
            {
            case 1:
            case 7:
                cout << "YES";
                break;
            default:
                cout << "NO";
                break;
            }
        }
        cout << endl;
    }

	return 0;
}