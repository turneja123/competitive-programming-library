//https://www.spoj.com/problems/SIMPGAME/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> divs[N];

int mex[N];
int dp[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }

    for (int i = 1; i < N; i++) {
        for (int x : divs[i]) {
            for (int y : divs[i]) {
                if (x == 1 || y == 1 || x == i || y == i) {
                    continue;
                }
                mex[dp[x] ^ dp[y]]++;
            }
        }
        while (mex[dp[i]]) {
            dp[i]++;
        }
        for (int x : divs[i]) {
            for (int y : divs[i]) {
                if (x == 1 || y == 1 || x == i || y == i) {
                    continue;
                }
                mex[dp[x] ^ dp[y]]--;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            ans ^= dp[a];
        }
        if (ans) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }


    return 0;
}
