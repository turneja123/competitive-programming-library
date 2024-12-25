//https://atcoder.jp/contests/abc189/tasks/abc189_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Line {
    long double a;
    long double b;
    Line() : a(0.0), b(0.0) {}
};

Line e[N];
bool f[N];

long double suf_a[N], suf_b[N];
int suf[N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> v;
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        f[a] = true;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (f[i]) {
            e[i].b = 1.0;
        } else {
            e[i].a = (long double)1.0 + (suf_a[i + 1] - suf_a[i + 1 + m]) / (long double)m;
            e[i].b = (long double)(suf_b[i + 1] - suf_b[i + 1 + m]) / (long double)m;
        }
        suf_a[i] = suf_a[i + 1] + e[i].a;
        suf_b[i] = suf_b[i + 1] + e[i].b;
    }
    if (e[0].b >= (long double)1.0) {
        cout << -1;
        return 0;
    }
    long double ans = e[0].a / ((long double)1.0 - e[0].b);
    cout << ans;

    return 0;
}
