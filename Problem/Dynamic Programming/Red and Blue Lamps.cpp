//https://atcoder.jp/contests/abc218/tasks/abc218_h
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

long long val[N];
vector<long long> dp[4 * N][2][2];

vector<long long> smawk(auto f, vector<long long> &rows, vector<long long> &cols) {
    vector<long long> ans(rows.size(), -1);
    if (max(rows.size(), cols.size()) <= 2) {
        for (int i = 0; i < rows.size(); i++) {
            for (auto j : cols) {
                if (ans[i] == -1 || f(rows[i], ans[i], j)) {
                    ans[i] = j;
                }
            }
        }
    } else if (rows.size() < cols.size()) {
        vector<long long> st;
        for (long long j : cols) {
            while (1) {
                if (st.empty()) {
                    st.push_back(j);
                    break;
                } else if (f(rows[st.size() - 1], st.back(), j)) {
                    st.pop_back();
                } else if (st.size() < rows.size()) {
                    st.push_back(j);
                    break;
                } else {
                    break;
                }
            }
        }
        ans = smawk(f, rows, st);
    } else {
        vector<long long> newRows;
        for (int i = 1; i < rows.size(); i += 2) {
            newRows.push_back(rows[i]);
        }
        auto otherAns = smawk(f, newRows, cols);
        for (int i = 0; i < newRows.size(); i++) {
            ans[2 * i + 1] = otherAns[i];
        }
        for (int i = 0, l = 0, r = 0; i < rows.size(); i += 2) {
            if (i + 1 == rows.size()) {
                r = cols.size();
            }
            while (r < cols.size() && cols[r] <= ans[i + 1]) {
                r++;
            }
            ans[i] = cols[l++];
            for (; l < r; l++) {
                if (f(rows[i], ans[i], cols[l])) {
                    ans[i] = cols[l];
                }
            }
            l--;
        }
    }
    return ans;
}


vector<long long> smawk(auto f, int n, int m) {
    vector<long long> rows(n), cols(m);
    for (int i = 0; i < n; i++) {
        rows[i] = i;
    }
    for (int i = 0; i < m; i++) {
        cols[i] = i;
    }
    return smawk(f, rows, cols);
}

vector<long long> maxplus(vector<long long> &A, vector<long long> &B) { //B is convex
    int n = A.size(), m = B.size();
    auto fun = [&](int i, int j) {
        return A[j] + B[i - j];
    };
    auto comp = [&](int i, int j, int k) {
        if (i < k) {
            return false;
        }
        if (i - j >= m) {
            return true;
        }
        return fun(i, j) <= fun(i, k);
    };
    vector<long long> best = smawk(comp, n + m - 1, n);
    for (int i = 0; i < n + m - 1; i++) {
        best[i] = fun(i, best[i]);
    }
    return best;
}

void calc(int l, int r, int node) {
    if (l == r) {
        dp[node][0][0] = {0};
        dp[node][0][1] = {};
        dp[node][1][0] = {};
        dp[node][1][1] = {0};
        return;
    }
    int mid = (l + r) / 2;
    if (l <= mid) {
        calc(l, mid, 2 * node + 1);
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, 2 * node + 2);
    }
    int s = r - l + 1;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            dp[node][x][y].resize(s + 1, -INF);
            if (x == 1) {
                dp[node][x][y].pop_back();
            }
            if (y == 1) {
                dp[node][x][y].pop_back();
            }
            if (x == 0 && y == 0) {
                dp[node][x][y].pop_back();
                dp[node][x][y].pop_back();
            }
        }
    }
    for (int lx = 0; lx < 2; lx++) {
        for (int ly = 0; ly < 2; ly++) {
            for (int rx = 0; rx < 2; rx++) {
                for (int ry = 0; ry < 2; ry++) {
                    if (dp[2 * node + 1][lx][ly].empty() || dp[2 * node + 2][rx][ry].empty()) {
                        continue;
                    }
                    vector<long long> nw = maxplus(dp[2 * node + 1][lx][ly], dp[2 * node + 2][rx][ry]);
                    int pom = 0;
                    if (ly == 1 && l != mid) {
                        pom++;
                    }
                    if (rx == 1 && mid + 1 != r) {
                        pom++;
                    }
                    for (int i = 0; i < nw.size(); i++) {
                        dp[node][lx][ry][i + pom] = max(dp[node][lx][ry][i + pom], nw[i] + ((ly != rx) ? val[mid] : 0));
                    }
                }
            }
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<long long> A(n), B(m);
    for (int i = 0; i < n - 1; i++) {
        cin >> val[i];
    }
    calc(0, n - 1, 0);
    long long ans = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int pom = i + j;
            if (m - pom < dp[0][i][j].size() && m - pom >= 0) {
                ans = max(ans, dp[0][i][j][m - pom]);
            }
        }
    }
    cout << ans;
    return 0;
}
