//https://www.spoj.com/problems/PAIRSUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long long a[N];
long long pref[N];
long long pref_sq[N];

__int128 get(int l, int r) {
    long long ans = pref[r];
    if (l != 0) {
        ans -= pref[l - 1];
    }
    return ans;
}

__int128 get_sq(int l, int r) {
    long long ans = pref_sq[r];
    if (l != 0) {
        ans -= pref_sq[l - 1];
    }
    return ans;
}

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = ((i == 0) ? a[i] : pref[i - 1] + a[i]);
        pref_sq[i] = ((i == 0) ? a[i] * a[i] : pref_sq[i - 1] + a[i] * a[i]);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        __int128 ans = ((__int128)get(l, r) * get(l, r) - get_sq(l, r)) / 2 + get_sq(l, r);
        print(ans);
        printf("\n");
    }



    return 0;
}
