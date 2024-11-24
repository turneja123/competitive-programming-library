//https://arena.petlja.org/sr-Latn-RS/competition/2024-2025-kv1-testiranje#tab_137812
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;

pair<long long, long long> a[N];
long long query[N];
map<long long, long long> ans;

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        a[i].second *= -1;
    }
    for (int i = n; i < n + q; i++) {
        cin >> a[i].first;
        a[i].second = 0;
        query[i - n] = a[i].first;
    }
    sort(a, a + n + q);
    long long add = 0, last = a[0].first - 1, sum = 0;
    for (int i = 0; i < n + q; i++) {
        a[i].second *= -1;
        sum += min(add, a[i].first - last);
        add -= min(add, a[i].first - last);
        add += a[i].second;
        if (last != a[i].first && add > 0 && add == a[i].second) {
            add--, sum++;
        }
        last = a[i].first;
        ans[a[i].first] = sum;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[query[i]] << endl;
    }
    return 0;
}
