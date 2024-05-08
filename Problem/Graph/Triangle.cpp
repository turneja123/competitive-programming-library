//https://atcoder.jp/contests/abc258/tasks/abc258_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

bitset<N> b[N];

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                b[i].set(j);
            }
        }
	}
	long long ans = 0;
	for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (b[i][j]) {
                ans += (b[i] & b[j]).count();
            }
        }
	}
	cout << ans / 3;
	return 0;
}
