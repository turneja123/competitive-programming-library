//https://atcoder.jp/contests/abc379/tasks/abc379_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];

long long f(long long n) {
    return n * (n + 1) / 2;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i].first;
    }
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        cin >> a[i].second;
        sum += a[i].second;
    }
    sort(a, a + m);
    if (a[0].first != 1 || sum != n) {
        cout << -1;
        return 0;
    }
    long long ans = 0, stones = a[0].second - 1;
    for (int i = 1; i < m; i++) {
        long long diff = a[i].first - a[i - 1].first - 1;
        if (diff > stones) {
            cout << -1;
            return 0;
        }
        ans += f(diff);
        stones -= diff;
        ans += stones * (diff + 1);
        stones += a[i].second - 1;
    }
    long long diff = n - a[m - 1].first;
    if (diff != stones) {
        cout << -1;
        return 0;
    }
    ans += f(diff);
    cout << ans;
    return 0;
}
