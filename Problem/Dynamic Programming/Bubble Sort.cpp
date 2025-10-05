//https://codeforces.com/contest/2146/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 5005;
const ll M = 998244353;

int mx[N];
int mn[N];
ll dp[K][K];
ll dp_tmp[K];
bool seen[N];

int id[N];
int val[K];

long long inv[N];
long long fact[N];
long long factinv[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

ll trans(int p, int q, int k) {
    if (k + 1 <= p) {
        return modPow(k + 1, q - p);
    }
    if (k + 1 >= q) {
        return fact[q] * factinv[p] % M;
    }
    return fact[k + 1] * factinv[p] % M * modPow(k + 1, q - k - 1) % M;

}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    for (int i = 1; i < N; i++) {
        mx[i] = i - 1;
        mn[i] = 0;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> idx;
        for (int i = 0; i < m; i++) {
            int k, l, r;
            cin >> k >> l >> r;
            mx[l] = min(mx[l], k);
            if (r + 1 != n + 1) {
                mn[r + 1] = max(mn[r + 1], k + 1);
            }
            if (l != 1 && !seen[l]) {
                idx.push_back(l);
                seen[l] = true;
            }
            if (r + 1 != n + 1 && !seen[r + 1]) {
                idx.push_back(r + 1);
                seen[r + 1] = true;
            }
        }
        if (!seen[n]) {
            idx.push_back(n);
        }
        int k = 0;
        sort(idx.begin(), idx.end());
        set<int> st;
        for (int j : idx) {
            if (mn[j] - 1 >= 0) {
                st.insert(mn[j] - 1);
            }
            st.insert(mx[j]);
        }
        st.insert(n - 1);
        for (int j : st) {
            val[k] = j;
            id[j] = k++;
        }
        for (int j = 0; j < k; j++) {
            dp[0][j] = 1;
        }
        int p = 1;
        for (int i = 1; i <= idx.size(); i++) {
            int q = idx[i - 1];
            for (int j = 0; j < k; j++) {
                dp_tmp[j] = dp[i - 1][j] * trans(p, q, val[j]) % M;
            }
            for (int j = k - 1; j >= 0; j--) {
                if (mn[q] > mx[q]) {
                    dp[i][j] = 0;
                    continue;
                }
                if (val[j] < mn[q]) {
                    dp[i][j] = 0;
                } else if (mn[q] <= val[j] && val[j] <= mx[q]) {
                    dp[i][j] = (dp_tmp[j] - (mn[q] == 0 ? 0 : dp_tmp[id[mn[q] - 1]]) + M) % M;
                } else {
                    dp[i][j] = (dp_tmp[id[mx[q]]] - (mn[q] == 0 ? 0 : dp_tmp[id[mn[q] - 1]]) + M) % M;
                }
            }
            p = q;
        }
        cout << dp[idx.size()][k - 1] << endl;
        for (int i : idx) {
            mx[i] = i - 1;
            mn[i] = 0;
            seen[i] = 0;
        }

    }
    return 0;
}
