//https://www.spoj.com/problems/FREQ2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int freq[N];
int ct[N];
int sz;
tuple<int, int, int> queries[N];
long long ans[N];

int block[N];

bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = block[get<0>(a)];
    int block2 = block[get<0>(b)];
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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = make_tuple(l, r, i);
    }
    for (int i = 0; i < n; i++) {
        block[i] = i / sz;
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    int mx = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            ct[freq[a[r]]]--;
            freq[a[r]]++;
            ct[freq[a[r]]]++;
            mx = max(mx, freq[a[r]]);
        }
        while (r > rq) {
            ct[freq[a[r]]]--;
            if (ct[freq[a[r]]] == 0 && mx == freq[a[r]]) {
                mx--;
            }
            freq[a[r]]--;
            ct[freq[a[r]]]++;
            r--;
        }
        while (l < lq) {
            ct[freq[a[l]]]--;
            if (ct[freq[a[l]]] == 0 && mx == freq[a[l]]) {
                mx--;
            }
            freq[a[l]]--;
            ct[freq[a[l]]]++;
            l++;
        }
        while (l > lq) {
            l--;
            ct[freq[a[l]]]--;
            freq[a[l]]++;
            ct[freq[a[l]]]++;
            mx = max(mx, freq[a[l]]);
        }
        ans[cur] = mx;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
