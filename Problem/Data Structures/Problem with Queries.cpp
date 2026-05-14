//https://codeforces.com/contest/2043/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 1300;

int a[N];
int b[N];
ll blk[N / SQ + 5][N];
int ct[N / SQ + 5][N];

int f[N];

void rebuild(int n) {
    for (int j = 0; j * SQ < n; j++) {
        ll s = 0;
        vector<int> f(n, 0);
        for (int i = j * SQ; i < n; i++) {
            s += f[a[i]];
            f[a[i]]++;
            blk[j][i] = s;
        }
    }
    vector<int> f(n, 0);
    for (int i = 0, j = 0; i < n; i++) {
        f[a[i]]++;
        if (i + 1 == (j + 1) * SQ) {
            for (int k = 0; k < n; k++) {
                ct[j][k] = f[k];
            }
            j++;
        }

    }

}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        b[i] = a[i];
    }
    rebuild(n);
    ll last = 0;
    set<int> buf;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l = (l + last) % n;
        r = (r + last) % n;
        if (t == 1) {
            b[l] = r;
            buf.insert(l);
        } else {
            if (l > r) {
                swap(l, r);
            }
            int bl = l / SQ;
            if (bl * SQ != l) {
                bl++;
            }
            int br = r / SQ;
            if ((r + 1) % SQ != 0) {
                br--;
            }

            if (bl > br) {
                last = 0;
                for (int j = l; j <= r; j++) {
                    last += f[b[j]];
                    f[b[j]]++;
                }
                for (int j = l; j <= r; j++) {
                    f[b[j]] = 0;
                }
                last = (ll)(r - l + 1) * (r - l) / 2 - last;
                cout << last << " ";
                continue;
            }

            auto freq = [&](int x) -> ll {
                ll C = ct[br][x] - (bl == 0 ? 0 : ct[bl - 1][x]) + f[x];
                return C * (C - 1) / 2;
            };

            last = blk[bl][r];
            for (int j = (br + 1) * SQ; j <= r; j++) {
                f[a[j]]++;
            }

            for (int j = l; j < bl * SQ; j++) {
                last -= freq(a[j]);
                f[a[j]]++;
                last += freq(a[j]);
            }


            for (int j : buf) {
                if (l <= j && j <= r && a[j] != b[j]) {
                    last -= freq(a[j]);
                    f[a[j]]--;
                    last += freq(a[j]);
                    last -= freq(b[j]);
                    f[b[j]]++;
                    last += freq(b[j]);
                }
            }
            for (int j = l; j < bl * SQ; j++) {
                f[a[j]] = 0;
            }
            for (int j = (br + 1) * SQ; j <= r; j++) {
                f[a[j]] = 0;
            }
            for (int j : buf) {
                f[a[j]] = 0;
                f[b[j]] = 0;
            }
            last = (ll)(r - l + 1) * (r - l) / 2 - last;
            cout << last << " ";

        }
        if (buf.size() > SQ) {
            for (int j : buf) {
                a[j] = b[j];
            }
            buf.clear();
            rebuild(n);
        }

    }

    return 0;
}
