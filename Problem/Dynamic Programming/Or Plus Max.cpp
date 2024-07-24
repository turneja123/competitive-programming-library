//https://atcoder.jp/contests/arc100/tasks/arc100_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1 << 18;

multiset<int> a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    int bits = 1 << n;
    for (int j = 0; j < bits; j++) {
        int x;
        cin >> x;
        a[j].insert(x);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bits; j++) {
            int c = j & (1 << i);
            if (c) {
                auto it = a[j ^ (1 << i)].begin();
                a[j].insert(*it);
                ++it;
                a[j].insert(*it);
                while (a[j].size() > 2) {
                    a[j].erase(a[j].begin());
                }
            }
        }
    }
    int ans = 0;
    for (int j = 1; j < bits; j++) {
        auto it = a[j].begin();
        int sum = *it;
        ++it;
        sum += *it;
        ans = max(ans, sum);
        cout << ans << endl;
    }

    return 0;
}
