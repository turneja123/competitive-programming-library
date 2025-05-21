//https://cses.fi/problemset/task/3355/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int MAX = 1e7 + 5;

vector<int> squares;
int dp[N];
vector<int> ans[N];

int main() {
    IOS;
    for (int i = 1; i < MAX; i++) {
        if (i * i >= MAX) {
            break;
        }
        squares.push_back(i * i);
    }
    for (int i = 1; i < N; i++) {
        int s = sqrt(i);
        if (s * s == i) {
            dp[i] = 1;
            ans[i] = {i};
            continue;
        }
        dp[i] = N;
        for (int j = 0; j < squares.size(); j++) {
            if (squares[j] > i) {
                break;
            }
            if (dp[i - squares[j]] + 1 < dp[i]) {
                dp[i] = dp[i - squares[j]] + 1;
                ans[i] = ans[i - squares[j]];
                ans[i].push_back(squares[j]);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> cur;
        if (n < N) {
            cur = ans[n];
        } else {
            int s = sqrtl(n);
            if (s * s == n) {
                cur = {n};
            } else {
                int ptr = upper_bound(squares.begin(), squares.end(), n) - squares.begin() - 2;
                while (ptr--) {
                    if (n - squares[ptr] >= N) {
                        break;
                    }
                    if (dp[n - squares[ptr]] < 4) {
                        cur = ans[n - squares[ptr]];
                        cur.push_back(squares[ptr]);
                        break;
                    }
                }
                if (cur.size() == 0) {
                    for (int j : squares) {
                        int y = (n - 2 * j) / 2;
                        int s = sqrt(y);
                        if (s * s == y) {
                            cur = {j, j, y, y};
                            break;
                        }
                        y = (n - 2 * j);
                        s = sqrt(y);
                        if (s * s == y) {
                            cur = {j, j, y, 0};
                            break;
                        }
                        y = (n - 3 * j);
                        s = sqrt(y);
                        if (s * s == y) {
                            cur = {j, j, j, y};
                            break;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < cur.size(); i++) {
            int s = sqrt(cur[i]);
            cout << s << " ";
        }
        for (int i = cur.size(); i < 4; i++) {
            cout << 0 << " ";
        }
        cout << endl;
    }
    return 0;
}
