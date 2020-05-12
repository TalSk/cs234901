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
typedef vector<ull> vull;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

int main() {
	ull N, num;
	cin >> N;
	vull nums;
	for (ull i = 0; i < N; i++)
	{
		cin >> num;
		nums.push_back(num);
	}

	sort(nums.begin(), nums.end());
	for (ull i = 0; i < N-2; i++)
	{
		if ((nums[i] + nums[i + 1]) > nums[i + 2]) {
			cout << "possible" << endl;
			return 0;
		}

	}
		cout << "impossible" << endl;

	return 0;
}