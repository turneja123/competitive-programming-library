//solution for https://dmoj.ca/problem/aac2p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
vector<int> pos[N];
int lf[N];
int rt[N];
int segleft[2 * N];
int segright[2 * N];

int maxq(int l, int r, int n) {
    l += n;
    r += n;
    int mx = -1;
    while (l < r) {
        if (r % 2 == 1) {
            mx = max(mx, segleft[--r]);
        }
        if (l % 2 == 1) {
            mx = max(mx, segleft[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mx;
}

int rmq(int l, int r, int n) {
    l += n;
    r += n;
    int mx = 0;
    while (l < r) {
        if (r % 2 == 1) {
            mx = max(mx, segright[--r]);
        }
        if (l % 2 == 1) {
            mx = max(mx, segright[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mx;
}

int bin(int lq, int rq, int n) {
    int l = 0;
    int r = lq - 1;
    int mn = lq;
    while (l <= r) {
        int mid = (l + r) / 2;
        int q = maxq(mid, rq + 1, n);
        if (q < mid) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mn;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pos[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (pos[i].size() == 0) {
            continue;
        }
        lf[pos[i][0]] = -1;
        for (int j = 0; j < pos[i].size(); j++) {
            if (j != 0) {
                lf[pos[i][j]] = pos[i][j - 1];
            }
            if (j != pos[i].size() - 1) {
                rt[pos[i][j]] = pos[i][j + 1];
            }
        }
        rt[pos[i][pos[i].size() - 1]] = n;
    }
    int mn = rt[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        mn = min(mn, rt[i]);
        rt[i] = mn;
    }
    for (int i = 0; i < n; i++) {
        rt[i] = rt[i] - i;
    }


    for (int i = 0; i < n; i++) {
        segleft[i + n] = lf[i];
    }
    for (int i = n - 1; i > 0; i--) {
        segleft[i] = max(segleft[2 * i], segleft[2 * i + 1]);
    }

    for (int i = 0; i < n; i++) {
        segright[i + n] = rt[i];
    }
    for (int i = n - 1; i > 0; i--) {
        segright[i] = max(segright[2 * i], segright[2 * i + 1]);
    }

    int lastAns = 0;

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l ^= lastAns;
        r ^= lastAns;
        l--, r--;
        int lq = bin(l, r, n);
        lastAns = rmq(lq, l + 1, n);
        cout << lastAns << endl;
    }
    return 0;
}
