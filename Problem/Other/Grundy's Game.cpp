//https://cses.fi/problemset/task/2207
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1223;

int dp[1223];

int calc(int n) {
    if (dp[n] != -1) {
        return dp[n];
    }

    set<int> mex;
    for (int i = 1; i < n; i++) {
        if (i == n - i) {
            continue;
        }
        mex.insert(calc(i) ^ calc(n - i));
    }
    int ct = 0;
    for (auto x : mex) {
        if (ct != x) {
            return dp[n] = ct;
        }
        ct++;
    }
    return dp[n] = ct;
}


int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        dp[i] = -1;
    }
    calc(N - 1);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= N || dp[n]) {
            cout << "first" << endl;
        } else {
            cout << "second" << endl;
        }
    }

    return 0;
}
