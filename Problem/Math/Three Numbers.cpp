//https://codeforces.com/contest/1311/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e4 + 5;

vector<int> divs[N];
vector<int> muls[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
            muls[i].push_back(j);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        int best = 1e5;
        tuple<int, int, int> ans;
        for (int i = 1; i < N; i++) {
            int x = lower_bound(divs[i].begin(), divs[i].end(), a) - divs[i].begin();
            int y = lower_bound(muls[i].begin(), muls[i].end(), c) - muls[i].begin();
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (x + dx >= 0 && x + dx < divs[i].size() && y + dy >= 0 && y + dy < muls[i].size()) {
                        int cur = abs(a - divs[i][x + dx]) + abs(b - i) + abs(c - muls[i][y + dy]);
                        if (cur < best) {
                            best = cur;
                            ans = make_tuple(divs[i][x + dx], i, muls[i][y + dy]);
                        }
                    }
                }
            }
        }
        cout << best << endl;
        cout << get<0>(ans) << " " << get<1>(ans) << " " << get<2>(ans) << endl;
    }
    return 0;
}
