//https://www.spoj.com/problems/ADANUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int a[N];
int freq[N];
int sz;
tuple<int, int, int> queries[N];
long long ans[N];
gp_hash_table<int, int, custom_hash> pos;

int lf[N], rt[N], ct[N];
long long sum[N];

bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = get<0>(a) / sz;
    int block2 = get<0>(b) / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    sz = sqrt(n);
    if (sz * sz != n) {
        sz++;
    }
    for (int i = 1; i < N; i++) {
        sum[i] = sum[i - 1] + i;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
        }
        rt[i] = n;
    }
    for (int i = 0; i < n; i++) {
        a[i] = pos[a[i]];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            ct[freq[a[r]]]--;
            int old_lf = lf[freq[a[r]]], old_rt = rt[freq[a[r]]];

            freq[a[r]]++;
            ct[freq[a[r]]]++;

            if (ct[freq[a[r]]] == 1) {
                lf[freq[a[r]]] = freq[a[r]] - 1;
                rt[freq[a[r]] - 1] = freq[a[r]];
                rt[freq[a[r]]] = old_rt;
                lf[old_rt] = freq[a[r]];
            }

            if (ct[freq[a[r]] - 1] == 0) {
                rt[old_lf] = freq[a[r]];
                lf[freq[a[r]]] = old_lf;
            }
        }
        while (r > rq) {
            ct[freq[a[r]]]--;
            int old_lf = lf[freq[a[r]]], old_rt = rt[freq[a[r]]];

            freq[a[r]]--;
            ct[freq[a[r]]]++;
            if (ct[freq[a[r]]] == 1) {
                rt[freq[a[r]]] = freq[a[r]] + 1;
                lf[freq[a[r]] + 1] = freq[a[r]];
                lf[freq[a[r]]] = old_lf;
                rt[old_lf] = freq[a[r]];
            }
            if (ct[freq[a[r]] + 1] == 0) {
                lf[old_rt] = freq[a[r]];
                rt[freq[a[r]]] = old_rt;
            }

            r--;
        }
        while (l < lq) {
            ct[freq[a[l]]]--;
            int old_lf = lf[freq[a[l]]], old_rt = rt[freq[a[l]]];

            freq[a[l]]--;
            ct[freq[a[l]]]++;
            if (ct[freq[a[l]]] == 1) {
                rt[freq[a[l]]] = freq[a[l]] + 1;
                lf[freq[a[l]] + 1] = freq[a[l]];
                lf[freq[a[l]]] = old_lf;
                rt[old_lf] = freq[a[l]];
            }
            if (ct[freq[a[l]] + 1] == 0) {
                lf[old_rt] = freq[a[l]];
                rt[freq[a[l]]] = old_rt;
            }

            l++;
        }
        while (l > lq) {
            l--;
            ct[freq[a[l]]]--;
            int old_lf = lf[freq[a[l]]], old_rt = rt[freq[a[l]]];

            freq[a[l]]++;
            ct[freq[a[l]]]++;

            if (ct[freq[a[l]]] == 1) {
                lf[freq[a[l]]] = freq[a[l]] - 1;
                rt[freq[a[l]] - 1] = freq[a[l]];
                rt[freq[a[l]]] = old_rt;
                lf[old_rt] = freq[a[l]];
            }

            if (ct[freq[a[l]] - 1] == 0) {
                rt[old_lf] = freq[a[l]];
                lf[freq[a[l]]] = old_lf;
            }

        }
        vector<int> freqs;
        int start = rt[0];
        while (start != n) {
            freqs.push_back(start);
            start = rt[start];
        }
        int k = 0; long long best = 0;
        for (int j = freqs.size() - 1; j >= 0; j--) {
            best += (long long)freqs[j] * (sum[k + ct[freqs[j]]] - sum[k]);
            k += ct[freqs[j]];
        }
        ans[cur] = best;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

