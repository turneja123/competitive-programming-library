//https://www.spoj.com/problems/EC_DIVS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int seg[4 * N];
stack<int> pos[N];

int spf[N];
bool is_prime[N];

vector<int> factors;
vector<int> ans;

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void factor(int n) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        factors.push_back(p);
        n = n / p;
    }
    return;
}

void get_divs(int i, int cur, vector<pair<int, int>> &f) {
    if (i == f.size()) {
        if (!is_prime[cur]) {
            ans.push_back(cur);
        }
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, f);
        cur *= f[i].first;
    }
    return;
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        seg[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    int ln = seg[2 * node + 1], rn = seg[2 * node + 2];
    if (ln == 0) {
        seg[node] = rn;
    } else if (rn == 0) {
        seg[node] = ln;
    } else {
        seg[node] =  __gcd(ln, rn);
    }
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        seg[node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    seg[node] = 0;
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        build(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            string c;
            cin >> c;
            if (c == "UPD") {
                string x; int a;
                cin >> x >> a;
                if (x == "ADD") {
                    pos[a].push(i);
                    update(0, n - 1, i, a, 0);
                } else {
                    int ind = pos[a].top();
                    update(0, n - 1, ind, 0, 0);
                }
            } else {
                int x = seg[0];
                if (x == 0) {
                    cout << -1 << endl;
                    continue;
                }
                factor(x);
                vector<pair<int, int>> f;
                int i = 0, j = 0, m = factors.size();
                while (i < m) {
                    int cur = factors[i];
                    while (i < m && factors[i] == cur) {
                        i++;
                    }
                    f.push_back(make_pair(factors[j], i - j));
                    j = i;
                }
                get_divs(0, 1, f);
                sort(ans.begin(), ans.end());
                for (int x : ans) {
                    cout << x << " ";
                }
                cout << endl;
                factors.clear();
                ans.clear();

            }
        }
    }
    return 0;
}
