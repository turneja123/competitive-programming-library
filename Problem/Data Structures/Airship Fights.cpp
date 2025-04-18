//https://dmoj.ca/problem/ichb2017p1correct
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;
const int INF = 3e5 + 5;

tuple<int, int, int> pt[N];
int suf[N];

int seg_mn[2 * N];
int seg_mx[2 * N];
int seg_val[2 * N];
int seg_pos[2 * N];


void update(int mx, int pos, int val, int n) {
    pos += n;
    if (mx == INF && val == INF) {
        seg_mn[pos] = INF;
        seg_mx[pos] = 0;
        seg_val[pos] = INF;
        seg_pos[pos] = -1;
    } else {
        seg_mn[pos] = mx;
        seg_mx[pos] = mx;
        seg_val[pos] = val;
        seg_pos[pos] = pos - n;
    }
    while (pos > 1) {
        pos /= 2;
        seg_mn[pos] = min(seg_mn[2 * pos], seg_mn[2 * pos + 1]);
        seg_mx[pos] = max(seg_mx[2 * pos], seg_mx[2 * pos + 1]);
        seg_val[pos] = min(seg_val[2 * pos], seg_val[2 * pos + 1]);
        if (seg_mn[2 * pos] < seg_mn[2 * pos + 1]) {
            seg_pos[pos] = seg_pos[2 * pos];
        } else {
            seg_pos[pos] = seg_pos[2 * pos + 1];
        }
    }
}

tuple<int, int, int, int> rmq(int l, int r, int n) {
    r++;
    l += n;
    r += n;
    int mn = INF, mx = 0, val = INF, pos = -1;
    while (l < r) {
        if (r % 2 == 1) {
            r--;
            if (seg_mn[r] <= mn) {
                mn = seg_mn[r];
                pos = seg_pos[r];
            }
            mx = max(mx, seg_mx[r]);
            val = min(val, seg_val[r]);

        }
        if (l % 2 == 1) {
            if (seg_mn[l] < mn) {
                mn = seg_mn[l];
                pos = seg_pos[l];
            }
            mx = max(mx, seg_mx[l]);
            val = min(val, seg_val[l]);
            l++;
        }
        l /= 2;
        r /= 2;
    }
    return make_tuple(mn, mx, val, pos);
}


int main() {
    IOS;
    fill(seg_mn, seg_mn + 2 * N, INF);
    fill(seg_mx, seg_mx + 2 * N, 0);
    fill(seg_val, seg_val + 2 * N, INF);
    fill(seg_pos, seg_pos + 2 * N, -1);
    int n;
    cin >> n;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int s, a, d;
        cin >> s >> a >> d;
        d++;
        pt[i] = make_tuple(s, a, d);
        mx = max(mx, d);
    }
    sort(pt, pt + n);
    int ans = INF;
    for (int i = 0; i < n; i++) {
        int last;
        auto [s, a, d] = pt[i];
        int need = 0;
        for (int k = 1; k <= d;) {
            int v = (d + k - 1) / k;
            if (v > 1) {
                last = (d - 1) / (v - 1);
            } else {
                last = d;
            }
            need += a;
            if (suf[v - 1] < need) {
                suf[v - 1] = need;
            }
            if (need > INF) {
                break;
            }
            k = last + 1;
        }
    }
    int need = 0;
    int ind;
    for (int i = mx; i > 0; i--) {
        if (suf[i] > need) {
            update(suf[i], i, (i == mx ? INF : i + 1 + need), mx + 1);
            if (get<0>(pt[n - 1]) + i + 1 + need < ans) {
                ans = get<0>(pt[n - 1]) + i + 1 + need;
                ind = i;
            }
            need = suf[i];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int last;
        auto [s, a, d] = pt[i];
        int need = a;
        if (suf[mx] < need) {
            suf[mx] = need;
            update(suf[mx], mx, INF, mx + 1);
            while (1) {
                auto [MN, MX, VAL, POS] = rmq(0, mx - 1, mx + 1);
                if (MN > need) {
                    if (POS != -1) {
                        update(suf[POS], POS, POS + 1 + need, mx + 1);
                    }
                    break;
                }
                update(INF, POS, INF, mx + 1);
            }

        }
        for (int k = 1; k <= d;) {
            int v = (d + k - 1) / k;
            if (v > 1) {
                last = (d - 1) / (v - 1);
            } else {
                last = d;
            }
            need += a;
            if (suf[v - 1] < min(need, INF - 1)) {
                suf[v - 1] = min(need, INF - 1);
                auto [MN, MX, VAL, POS] = rmq(v, mx, mx + 1);
                if (MX < min(need, INF - 1)) {
                    update(suf[v - 1], v - 1, v + MX, mx + 1);
                    while (v - 2 >= 0) {
                        auto [MN, MX, VAL, POS] = rmq(0, v - 2, mx + 1);
                        if (MN > min(need, INF - 1)) {
                            if (POS != -1) {
                                update(suf[POS], POS, POS + 1 + min(need, INF - 1), mx + 1);
                            }
                            break;
                        }
                        update(INF, POS, INF, mx + 1);
                    }
                }
            }
            if (need > INF) {
                break;
            }
            k = last + 1;
        }
        ans = min(ans, (i == 0 ? 0 : get<0>(pt[i - 1])) + get<2>(rmq(0, mx, mx + 1)));
    }
    cout << ans;

    return 0;
}
