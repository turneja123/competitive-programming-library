//https://codeforces.com/contest/2207/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, l;
        cin >> n >> m >> l;
        vector<int> a(n + 1);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        multiset<int> items;
        for (int i = 0; i < m; i++) {
            items.insert(0);
        }
        for (int i = 0; i <= n; i++) {
            int add;
            if (i == 0) {
                add = a[i];
            } else if (i < n) {
                add = a[i] - a[i - 1];
            } else {
                add = l - a[i - 1];
            }
            while (items.size() > min(m, n - i + 1)) {
                items.erase(items.begin());
            }

            for (int j = 0; j < add; j++) {
                int x = *items.begin();
                items.erase(items.begin());
                items.insert(x + 1);
            }
            if (i != n) {
                int x = *items.rbegin();
                items.erase(items.find(x));
                items.insert(0);
            }
        }
        cout << *items.rbegin() << endl;
    }


    return 0;
}
