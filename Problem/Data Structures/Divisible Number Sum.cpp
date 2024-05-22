//https://www.spoj.com/problems/NAJ0001/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int D = 1005;

int a[N];
int spf[N];
bool is_prime[N];
int ind = 0;
vector<int> pos[D];
vector<long long> pref[D];

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

int factor(int n, vector<pair<int, int>> &f) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        if (p != last) {
            if (last != -1) {
                f.push_back(make_pair(last, ct));
            }
            last = p;
            cnt *= ct + 1;
            ct = 1;
        } else {
            ct++;
        }
        n = n / p;
    }
    if (ct > 0) {
        cnt *= ct + 1;
        f.push_back(make_pair(last, ct));
    }
    return cnt;
}

void get_divs(int i, int cur, int n, vector<pair<int, int>> &f, vector<int> &divs) {
    if (cur >= D) {
        return;
    }
    if (i == f.size()) {
        divs[ind++] = cur;
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, n, f, divs);
        cur *= f[i].first;
    }
    return;
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            vector<pair<int, int>> f;
            int d = factor(a[i], f);
            vector<int> divs;
            divs.resize(d);
            get_divs(0, 1, i, f, divs);
            for (int d : divs) {
                pos[d].push_back(i);
            }
            f.clear();
            ind = 0;
        }
        for (int d = 1; d < D; d++) {
            if (pos[d].size() != 0) {
                pref[d].resize(pos[d].size());
                pref[d][0] = a[pos[d][0]];
                for (int j = 1; j < pos[d].size(); j++) {
                    pref[d][j] = pref[d][j - 1] + a[pos[d][j]];
                }
            }
        }
        cout << "Case #" << tt << endl;
        for (int i = 0; i < q; i++) {
            int l, r, d;
            cin >> d >> l >> r;
            l--, r--;
            long long ans, m = pos[d].size();
            if (m == 0) {
                cout << 0 << endl;
                continue;
            }
            int lq = lower_bound(pos[d].begin(), pos[d].end(), l) - pos[d].begin();
            int rq = upper_bound(pos[d].begin(), pos[d].end(), r) - pos[d].begin();
            rq--;
            if (lq == m || lq > rq) {
                ans = 0;
            } else {
                ans = pref[d][rq] - ((lq == 0) ? 0 : pref[d][lq - 1]);
            }
            cout << ans << endl;
        }
        for (int d = 1; d < D; d++) {
            pos[d].clear();
            pref[d].clear();
        }
        if (tt != t) {
            cout << endl;
        }
    }

    return 0;
}
