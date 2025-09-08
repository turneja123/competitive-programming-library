//https://atcoder.jp/contests/abc421/tasks/abc421_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

using ld = double;

ld a[N];
map<vector<int>, ld> states[6];
map<vector<int>, ld> dp[4];

void go(int i, vector<int> &state) {
    states[i][state] += 1.0;
    if (i == 5) {
        return;
    }
    for (int j = 0; j < 6; j++) {
        state[j]++;
        go(i + 1, state);
        state[j]--;
    }
}

ld calc(int i, vector<int> &state) {
    int m = 0;
    for (int i = 0; i < state.size(); i++) {
        m += state[i];
    }
    if (i == 3 && m != 5) {
        return 0.0;
    }
    if (m == 5) {
        ld ans = 0;
        for (int i = 0; i < 6; i++) {
            ld cur = 0;
            for (int j = 0; j < 6; j++) {
                if (a[i] == a[j]) {
                    cur += (ld)state[j] * a[j];
                }
            }
            ans = max(ans, cur);
        }
        return ans;
    }

    auto it = dp[i].find(state);
    if (it != dp[i].end()) {
        return it->second;
    }

    ld ans = 0.0;
    for (auto it : states[5 - m]) {
        vector<int> cur = it.first;
        ld prob = it.second;
        ld best = 0.0;
        for (int i0 = 0; i0 <= cur[0]; i0++) {
            for (int i1 = 0; i1 <= cur[1]; i1++) {
                for (int i2 = 0; i2 <= cur[2]; i2++) {
                    for (int i3 = 0; i3 <= cur[3]; i3++) {
                        for (int i4 = 0; i4 <= cur[4]; i4++) {
                            for (int i5 = 0; i5 <= cur[5]; i5++) {
                                state[0] += i0;
                                state[1] += i1;
                                state[2] += i2;
                                state[3] += i3;
                                state[4] += i4;
                                state[5] += i5;
                                best = max(best, calc(i + 1, state));
                                state[0] -= i0;
                                state[1] -= i1;
                                state[2] -= i2;
                                state[3] -= i3;
                                state[4] -= i4;
                                state[5] -= i5;
                            }
                        }
                    }
                }
            }
        }
        ans += best * prob;
    }
    return dp[i][state] = ans;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    for (int i = 0; i < 6; i++) {
        cin >> a[i];
    }
    vector<int> a(6, 0);
    go(0, a);
    int prod = 1;
    for (int i = 0; i <= 5; i++) {
        for (auto it = states[i].begin(); it != states[i].end(); ++it) {
            it->second /= (ld)prod;
        }
        prod *= 6;
    }
    cout << calc(0, a);

    return 0;
}
