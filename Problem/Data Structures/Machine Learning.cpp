//https://codeforces.com/problemset/problem/940/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

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
int ct[N];
int sz;
long long ans[N];
int block[N];
int ind[N];
gp_hash_table<int, int, custom_hash> pos;


vector<tuple<int, int, int, int>> queries;
vector<tuple<int, int, int, int, int>> updates;


bool comp(tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
    int block1_l = block[get<0>(a)];
    int block2_l = block[get<0>(b)];
    if (block1_l != block2_l) {
        return block1_l < block2_l;
    }
    int block1_r = block[get<1>(a)];
    int block2_r = block[get<1>(b)];
    if (block1_r != block2_r) {
        return block1_r < block2_r;
    }

    int t1 = get<2>(a);
    int t2 = get<2>(b);
    return t1 < t2;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    sz = cbrt((long long)2 * n * n);
    for (int i = 0; i < n; i++) {
        block[i] = i / sz;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
        }
        ind[i] = pos[a[i]];
    }
    int t = 0;
    for (int i = 0; i < q; i++) {
        int c;
        cin >> c;
        if (c == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            queries.push_back(make_tuple(l, r, t, i - t));
        } else {
            int j, x;
            cin >> j >> x;
            j--;
            if (pos.find(x) == pos.end()) {
                pos[x] = pos.size();
            }
            updates.push_back(make_tuple(x, a[j], pos[x], pos[a[j]], j));
            a[j] = x;
            ind[j] = pos[x];
            t++;
        }
    }
    q = queries.size();
    sort(queries.begin(), queries.end(), comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        int cur = get<3>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int tq = get<2>(queries[i]);
        while (tq < t) {
            t--;
            int x = get<0>(updates[t]), old = get<1>(updates[t]), nwind = get<2>(updates[t]), oldind = get<3>(updates[t]), j = get<4>(updates[t]);
            if (j >= l && j <= r) {
                ct[freq[nwind]]--;
                freq[nwind]--;
                ct[freq[nwind]]++;

                ct[freq[oldind]]--;
                freq[oldind]++;
                ct[freq[oldind]]++;

            }
            a[j] = old;
            ind[j] = oldind;
        }
        while (tq > t) {
            int x = get<0>(updates[t]), old = get<1>(updates[t]), nwind = get<2>(updates[t]), oldind = get<3>(updates[t]), j = get<4>(updates[t]);
            if (j >= l && j <= r) {
                ct[freq[oldind]]--;
                freq[oldind]--;
                ct[freq[oldind]]++;

                ct[freq[nwind]]--;
                freq[nwind]++;
                ct[freq[nwind]]++;

            }
            a[j] = x;
            ind[j] = nwind;
            t++;
        }

        while (r < rq) {
            r++;
            ct[freq[ind[r]]]--;
            freq[ind[r]]++;
            ct[freq[ind[r]]]++;
        }
        while (r > rq) {
            ct[freq[ind[r]]]--;
            freq[ind[r]]--;
            ct[freq[ind[r]]]++;
            r--;
        }
        while (l < lq) {
            ct[freq[ind[l]]]--;
            freq[ind[l]]--;
            ct[freq[ind[l]]]++;
            l++;
        }
        while (l > lq) {
            l--;
            ct[freq[ind[l]]]--;
            freq[ind[l]]++;
            ct[freq[ind[l]]]++;
        }
        int j = 1;
        while (ct[j] != 0) {
            j++;
        }
        ans[cur] = j;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}



