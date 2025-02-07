//https://atcoder.jp/contests/abc391/tasks/abc391_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

string s;

int pw[N];

pair<int, int> calc(int n, int ind) {
    if (n == 0) {
        if (s[ind] == '0') {
            return make_pair(0, 1);
        } else {
            return make_pair(1, 0);
        }
    }
    pair<int, int> x = calc(n - 1, ind);
    pair<int, int> y = calc(n - 1, ind + pw[n - 1]);
    pair<int, int> z = calc(n - 1, ind + 2 * pw[n - 1]);

    int f = min({x.first + y.first + z.second, x.first + z.first + y.second, y.first + z.first + x.second, x.first + y.first + z.first});
    int s = min({x.second + y.second + z.first, x.second + z.second + y.first, y.second + z.second + x.first, x.second + y.second + z.second});
    return make_pair(f, s);
}

int main() {
    IOS;
    int n;
    cin >> n >> s;
    pw[0] = 1;
    for (int i = 1; i < n; i++) {
        pw[i] = pw[i - 1] * 3;
    }
    pair<int, int> x = calc(n, 0);
    cout << max(x.first, x.second);
    return 0;
}
