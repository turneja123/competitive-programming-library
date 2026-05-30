//https://atcoder.jp/contests/arc220/tasks/arc220_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

void go(vector<int> &d, int j, int l, int &ok) {
    if (ok) {
        return;
    }
    if (j == d.size()) {
        ll lcm = d[0];
        for (int i = 1; i < d.size(); i++) {
            lcm = lcm * d[i] / __gcd(lcm, (ll)d[i]);
        }
        ll s = 0;
        for (int i = 0; i < d.size(); i++) {
            s += lcm / d[i];
        }
        if (s == lcm) {
            ok = 1;
        }

        return;
    }

    for (int i = l; i < 30; i++) {
        d[j] = i * i;
        go(d, j + 1, i, ok);
        if (ok) {
            return;
        }
    }
}


int main() {
    IOS;
    vector<int> ans[3];
    for (int i = 2; i < 9; i++) {
        if (!ans[i % 3].empty()) {
            continue;
        }
        vector<int> d(i, 0);
        int ok = 0;
        go(d, 0, 2, ok);
        if (ok) {
            for (int j = 0; j < i; j++) {
                d[j] = sqrt(d[j]);
            }
            ans[i % 3] = d;
        }

    };
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "Yes" << endl;
            cout << 1 << endl;
            continue;
        }
        if (n == 2 || n == 3 || n == 5) {
            cout << "No" << endl;
            continue;
        }
        priority_queue<int> pq;
        for (int i = 0; i < ans[n % 3].size(); i++) {
            pq.push(-ans[n % 3][i]);
        }
        while (pq.size() < n) {
            int x = -pq.top();
            pq.pop();
            for (int i = 0; i < 4; i++) {
                pq.push(-2 * x);
            }
        }
        cout << "Yes" << endl;
        while (pq.size()) {
            cout << -pq.top() << " ";
            pq.pop();
        }
        cout << endl;

    }


    return 0;
}
