//https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

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

vector<long long> minplus(vector<long long> A, vector<long long> B) { //B is convex
    if (A.empty()) {
        A.push_back(0);
    }
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
        //return fun(i, j) <= fun(i, k);
        return fun(i, j) >= fun(i, k);
    };
    vector<long long> best = smawk(comp, n + m - 1, n);
    vector<long long> ans(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        ans[i] = fun(i, best[i]);
    }
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<long long> A(n), B(m);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
    vector<long long> ans = minplus(B, A);
    for (long long x : ans) {
        cout << x << " ";
    }
    return 0;
}
