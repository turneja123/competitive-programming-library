//https://judge.yosupo.jp/problem/static_range_mode_query
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 450;

int a[N];
int freq[N];
int tot[N];
int is_heavy[N];
tuple<int, int, int> queries[N];
int ans[N];
int ans_ct[N];
int bl[SQ][SQ];

int freq_ct[N];
int ct = 0;

bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = get<0>(a) / SQ;
    int block2 = get<0>(b) / SQ;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}


void add(int x) {
    if (freq[x] == ct) {
        ct++;
    }
    freq_ct[freq[x]]--;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]--;
    }
    freq[x]++;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]++;
    }
    freq_ct[freq[x]]++;


}

void rem(int x) {
    if (freq[x] == ct && freq_ct[freq[x]] == 1) {
        ct--;
    }
    freq_ct[freq[x]]--;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]--;
    }
    freq[x]--;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]++;
    }
    freq_ct[freq[x]]++;


}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr.push_back(a[i]);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(compr.begin(), compr.end(), a[i]) - compr.begin();
        tot[a[i]]++;
    }
    vector<int> heavy;
    int m = compr.size();
    for (int i = 0; i < m; i++) {
        if (tot[i] >= SQ) {
            heavy.push_back(i);
            is_heavy[i] = 1;
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        auto [lq, rq, cur] = queries[i];
        while (r < rq) {
            r++;
            add(a[r]);
        }
        while (l > lq) {
            l--;
            add(a[l]);
        }
        while (r > rq) {
            rem(a[r]);
            r--;
        }
        while (l < lq) {
            rem(a[l]);
            l++;
        }
        ans[cur] = N;
        ans_ct[cur] = ct;
        for (int j = 0; j < SQ && ct < SQ; j++) {
            if (bl[j][ct]) {
                for (int k = 0; k < SQ && j * SQ + k < m; k++) {
                    if (freq[j * SQ + k] == ct) {
                        ans[cur] = j * SQ + k;
                        break;
                    }
                }
                break;
            }
        }
        for (int k : heavy) {
            if (freq[k] == ct) {
                ans[cur] = min(ans[cur], k);
                break;
            }
        }


    }
    for (int i = 0; i < q; i++) {
        cout << compr[ans[i]] << " " << ans_ct[i] << endl;
    }
    return 0;
}

