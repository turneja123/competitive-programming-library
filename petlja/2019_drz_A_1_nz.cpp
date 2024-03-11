#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int seg[2 * N];
bool b[N];

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }
}

int rmq(int l, int r, int n) {
    l += n;
    r += n;
    int mn = 1e9;
    while (l < r) {
        if (r % 2 == 1) {
            mn = min(mn, seg[--r]);
        }
        if (l % 2 == 1) {
            mn = min(mn, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mn;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = true;
    }
    build(n);
    for (int i = 0; i < n; i++) {
        int mn = rmq(i, i + k + 1, n);
        while (a[i] != mn) {
            b[i] = false;
            k--;
            i++;
        }
    }
    int i = n - 1;
    while (k) {
        if (b[i]) {
            b[i] = false;
            k--;
        }
        i--;
    }
    for (int i = 0; i < n; i++) {
        if (b[i]) {
            cout << a[i] << " ";
        }
    }


    return 0;
}
