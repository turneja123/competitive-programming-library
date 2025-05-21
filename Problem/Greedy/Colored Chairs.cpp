//https://cses.fi/problemset/task/3273
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    //IOS;
    int n;
    cin >> n;
    map<char, int> mp;
    mp['R'] = 0, mp['B'] = 1;
    cout << "? 1" << endl;
    char c;
    cin >> c;
    int x = mp[c];
    cout << "? " << n << endl;
    cin >> c;
    int y = mp[c];
    if (x == y) {
        cout << "! " << n;
        return 0;
    }
    int l = 1, r = n, spl = n;
    int last = -1;
    vector<pair<int, int>> q;
    while (l <= r) {
        int mid = (l + r) / 2;
        int j = 1 + 2 * mid;
        if (j > n) {
            r = mid - 1;
            continue;
        }
        cout << "? " << j << endl;
        cin >> c;
        y = mp[c];
        q.push_back(make_pair(j, y));
        if (y == x) {
            l = mid + 1;
        } else {
            spl = j;
            last = y;
            r = mid - 1;
        }
    }

    cout << "? " << spl - 1 << endl;
    cin >> c;
    q.push_back(make_pair(spl - 1, mp[c]));
    sort(q.begin(), q.end());
    for (int i = 1; i < q.size(); i++) {
        if (q[i].first - q[i - 1].first == 1 && q[i].second == q[i - 1].second) {
            cout << "! " << q[i - 1].first;
            return 0;
        }
    }

    if (mp[c] == last) {
        cout << "! " << spl - 1;
        return 0;
    }
    cout << "! " << spl;
    return 0;
}
