//https://www.spoj.com/problems/STRINGQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 106109099;

long long inv[N];
long long fact[N];
long long factinv[N];
string a;
vector<int> segtree[4 * N];
vector<int> freq;
int setVal[4 * N];
bool setValid[4 * N];
char ans[N];

void combine(vector<int> &a, vector<int> &b, vector<int> &c) {
    for (int i = 0; i < 26; i++) {
        c[i] = a[i] + b[i];
    }
    return;
}

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        for (int i = 0; i < 26; i++) {
            segtree[node][i] = 0;
        }
        segtree[node][setVal[node]] = r - l + 1;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    combine(segtree[node * 2 + 1], segtree[node * 2 + 2], segtree[node]);
}

void query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        for (int i = 0; i < 26; i++) {
            freq[i] += segtree[node][i];
        }
        return;
    }
    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1);
    query(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    segtree[node].clear();
    segtree[node].resize(26);
    setVal[node] = 0;
    setValid[node] = false;
    if (l == r) {
        segtree[node][a[l] - 'a'] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    combine(segtree[node * 2 + 1], segtree[node * 2 + 2], segtree[node]);
}

void print(int l, int r, int node) {
    if (l > r) {
        return;
    }
    apply(node, l, r);
    if (l == r) {
        for (int i = 0; i < 26; i++) {
            if (segtree[node][i] == 1) {
                ans[l] = 'a' + i;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    print(l, mid, node * 2 + 1);
    print(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }

    int t;
    cin >> t;
    while (t--) {
        cin >> a;
        int n = a.size();
        build(0, n - 1, 0);
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            char c; int l, r;
            cin >> c >> l >> r;
            l--, r--;
            if (c == 'Q') {
                freq.clear();
                freq.resize(26);
                query(0, n - 1, l, r, 0);
                int odd = 0;
                for (int k = 0; k < 26; k++) {
                    if (freq[k] == 0) {
                        continue;
                    }
                    if (freq[k] % 2 == 1) {
                        odd++;
                    }
                }
                if (odd > 1) {
                    cout << 0 << endl;
                    continue;
                }
                int m = r - l + 1;
                if (odd) {
                    m--;
                }
                long long ans = fact[m / 2];
                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        ans = ans * factinv[freq[k] / 2] % M;
                    }
                }
                cout << ans << endl;

            } else {
                freq.clear();
                freq.resize(26);
                query(0, n - 1, l, r, 0);
                int j = l;
                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        setUpdate(0, 0, n - 1, j, j + freq[k] - 1, k);
                        j += freq[k];
                    }
                }
            }
        }
        print(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            cout << ans[i];
        }
        cout << endl;
    }

    return 0;
}
