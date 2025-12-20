//https://qoj.ac/contest/2668/problem/15448
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5;

int dp[26][N];
string st[N];

int to_int(string s) {
    int ans = 0, wt = 10000;
    for (int i = 0; i < 5; i++) {
        ans += wt * (s[i] - '0');
        wt /= 10;
    }
    return ans;
}

string _to_string(int n) {
    string s = "";
    while (n > 0) {
        s += '0' + (n % 10);
        n /= 10;
    }
    if (s.size()) {
        reverse(s.begin(), s.end());
    }
    while (s.size() < 5) {
        s = '0' + s;
    }
    return s;
}

char go_next(char c) {
    if (c == '9') {
        return '0';
    }
    return c + 1;
}

char go_prev(char c) {
    if (c == '0') {
        return '9';
    }
    return c - 1;
}

vector<pair<int, int>> upd[N];

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        st[i] = _to_string(i);
    }
    int n;
    cin >> n;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = n;
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        dp[0][to_int(s)] = i;
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < N; j++) {
            string s = st[j];
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            for (int d = 0; d < 5; d++) {
                s[d] = go_next(s[d]);
                dp[i + 1][to_int(s)] = min(dp[i + 1][to_int(s)], dp[i][j]);
                s[d] = go_prev(s[d]);
                s[d] = go_prev(s[d]);
                dp[i + 1][to_int(s)] = min(dp[i + 1][to_int(s)], dp[i][j]);
                s[d] = go_next(s[d]);
            }
        }
    }
    vector<int> last(N, -1);
    vector<int> ct(26, 0);

    for (int i = 25; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (dp[i][j] != n) {
                upd[dp[i][j]].push_back({i, j});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (auto [i, j] : upd[i]) {
            if (last[j] != -1) {
                ct[last[j]]--;
            }
            ct[i]++;
            last[j] = i;
        }
        int best = -1, ans = 0;
        for (int j = 0; j < 26; j++) {
            if (ct[j] > 0) {
                best = j;
                ans = ct[j];
            }
        }
        cout << best << " " << ans << endl;
    }



    return 0;
}
