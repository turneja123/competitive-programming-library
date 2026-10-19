//https://atcoder.jp/contests/arc231/tasks/arc231_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int x, y, z;
        cin >> x >> y >> z;
        vector<int> a(x), b(y), c;
        iota(a.begin(), a.end(), 0);
        iota(b.begin(), b.end(), 0);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                c.push_back(i ^ j);
            }
        }
        sort(c.begin(), c.end());
        c.erase(unique(c.begin(), c.end()), c.end());
        if (binary_search(c.begin(), c.end(), z)) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        a.push_back(1024);
        for (int i = 0; i < z; i++) {
            if (!binary_search(c.begin(), c.end(), i)) {
                b.push_back(1024 ^ i);
            }
        }
        cout << a.size() << " ";
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        cout << b.size() << " ";
        for (int i = 0; i < b.size(); i++) {
            cout << b[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
