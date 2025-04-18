//https://dmoj.ca/problem/noi10p2
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 5e8 + 1;

int a[N];
int pref[N];
int pos[N];
int val[N];
pair<int, int> compr[N];

template<class T> struct BIT {
    int n;
    vector<T> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void res() {
        for (int i = 0; i <= n; i++) {
            t[i] = 0;
        }
    }
    void upd(int i, T val) {
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, T val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    T query(int i) {
        T ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


int main() {
    IOS;
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
        compr[i] = make_pair(pref[i], i);
    }
    compr[n] = make_pair(0, n);
    sort(compr, compr + n + 1);
    int m = 0;
    int last = compr[0].first;
    val[0] = last;
    for (int i = 0; i <= n; i++) {
        if (compr[i].first != last) {
            m++;
            last = compr[i].first;
            val[m] = last;
        }
        pos[compr[i].second] = m;
    }
    m++;
    int l_bin = INF, r_bin = -INF;
    deque<int> dmn, dmx;
    for (int i = L; i <= n; i++) {
        int j = i - L;
        while (!dmn.empty() && ((dmn.back() == 0 ? 0 : pref[dmn.back() - 1]) >= (j == 0 ? 0 : pref[j - 1]))) {
            dmn.pop_back();
        }
        dmn.push_back(j);
        while (!dmx.empty() && ((dmx.back() == 0 ? 0 : pref[dmx.back() - 1]) <= (j == 0 ? 0 : pref[j - 1]))) {
            dmx.pop_back();
        }
        dmx.push_back(j);
        if (i - R > 0) {
            if (dmn.front() < i - R) {
                dmn.pop_front();
            }
            if (dmx.front() < i - R) {
                dmx.pop_front();
            }
        }
        r_bin = max(r_bin, pref[i - 1] - (dmn.front() == 0 ? 0 : pref[dmn.front() - 1]));
        l_bin = min(l_bin, pref[i - 1] - (dmx.front() == 0 ? 0 : pref[dmx.front() - 1]));
    }

    pair<int, long long> ans;
    BIT<int> bit(m);
    while (l_bin <= r_bin) {
        int mid = (l_bin + r_bin) / 2;
        long long ct = 0;
        for (int i = 0, l = -1, r = -1; i < n; i++) {
            while (i - r >= L) {
                int j = (r == -1 ? pos[n] : pos[r]);
                bit.upd(j + 1, 1);
                r++;
            }
            while (i - l > R) {
                int j = (l == -1 ? pos[n] : pos[l]);
                bit.upd(j + 1, -1);
                l++;
            }
            int need = pref[i] - mid;
            int j = upper_bound(val, val + m, need) - val - 1;
            if (j >= 0) {
                ct += bit.query(j + 1);
            }
        }
        if (ct >= k) {
            ans = make_pair(mid, ct);
            l_bin = mid + 1;
        } else {
            r_bin = mid - 1;
        }
        bit.res();
    }
    int mid = ans.first;
    BIT<long long> bit_sum(m);
    BIT<int> bit_freq(m);
    long long sum = 0;
    for (int i = 0, l = -1, r = -1; i < n; i++) {
        while (i - r >= L) {
            int j = (r == -1 ? pos[n] : pos[r]);
            int s = (r == -1 ? 0 : pref[r]);
            bit_freq.upd(j + 1, 1);
            bit_sum.upd(j + 1, s);
            r++;
        }
        while (i - l > R) {
            int j = (l == -1 ? pos[n] : pos[l]);
            int s = (l == -1 ? 0 : pref[l]);
            bit_freq.upd(j + 1, -1);
            bit_sum.upd(j + 1, -s);
            l++;
        }
        int need = pref[i] - mid;
        int j = upper_bound(val, val + m, need) - val - 1;
        if (j >= 0) {
            sum += (long long)bit_freq.query(1, j + 1) * pref[i] - bit_sum.query(1, j + 1);
        }
    }
    sum -= (long long)(ans.second - k) * ans.first;
    cout << sum;
    return 0;
}
