//https://codeforces.com/contest/575/problem/I
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int SQ = 64;
const int K = N / SQ + 5;

int a[N][N];
int X[K][N];
int D1[K][2 * N];
int D2[K][2 * N];

void add(int dir, int x, int y, int len) {
    int l = (dir == 1 || dir == 3 ? y : y - len);
    int r = (dir == 1 || dir == 3 ? y + len : y);
    int x1 = (dir <= 2 ? x : x + 1);
    int val = (dir <= 2 ? 1 : -1);
    int dx = (dir == 1 || dir == 4 ? -1 : 1);
    int x2 = (dir == 1 ? x + len + 1 : dir == 2 ? x + 1 : dir == 3 ? x - len : x);

    int i = l;
    while (i <= r && (i - 1) % SQ != 0) {
        a[i][x1] += val;
        a[i][x2] -= val;
        i++;
        x2 += dx;
    }
    while (i + SQ - 1 <= r) {
        int k = (i - 1) / SQ;
        X[k][x1] += val;
        if (dx == -1) {
            D1[k][x2 + i] -= val;
        } else {
            D2[k][x2 - i + N] -= val;
        }
        i += SQ;
        x2 += SQ * dx;
    }
    while (i <= r) {
        a[i][x1] += val;
        a[i][x2] -= val;
        i++;
        x2 += dx;
    }
}

int query(int x, int y) {
    int k = (y - 1) / SQ;
    const int *p1 = a[y] + 1;
    const int *p2 = X[k] + 1;
    const int *p3 = D1[k] + y + 1;
    const int *p4 = D2[k] + N - y + 1;

    int ans = 0;
    for (int i = 0; i < x; i++) {
        ans += p1[i] + p2[i] + p3[i] + p4[i];
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int dir, x, y, len;
            cin >> dir >> x >> y >> len;
            add(dir, x, y, len);
        } else {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << endl;
        }
    }
    return 0;
}
