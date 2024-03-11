//solution for https://atcoder.jp/contests/abc185/tasks/abc185_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int seg[2 * N];

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = seg[2 * i] ^ seg[2 * i + 1];
    }
}

void update(int pos, int val, int n) {
    pos += n;
    seg[pos] = val;
    while (pos > 1) {
        pos >>= 1;
        seg[pos] = seg[2 * pos] ^ seg[2 * pos + 1];
    }
}

int rxor(int l, int r, int n) {
    l += n;
    r += n;
    int x = 0;
    while (l < r) {
        if (l % 2 == 1) {
            x ^= seg[l++];
        }
        if (r % 2 == 1) {
            x ^= seg[--r];
        }
        l /= 2;
        r /= 2;
    }
    return x;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        x--, y--;
        if (t == 1) {
            int nw = seg[x + n] ^ (y + 1);
            update(x, nw, n);
        }
        if (t == 2)
            cout << rxor(x, y + 1, n) << endl;
    }
    return 0;

}
