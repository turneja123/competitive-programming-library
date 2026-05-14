//https://atcoder.jp/contests/arc218/tasks/arc218_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


vector<pair<int, int>> rle(vector<int> &a) {
    int n = a.size();
    vector<pair<int, int>> v;
    int last = -1, ct = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != last) {
            if (ct) {
                v.push_back({last, ct});
            }
            last = a[i];
            ct = 1;
        } else {
            ct++;
        }
    }
    v.push_back({last, ct});
    return v;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<pair<int, int>> v = rle(a);
        int ok = 0, f = 0;
        if (v[0].first == 0 && v[0].second > 1) {
            cout << "Alice" << endl;
            continue;
        }
        if (v[0].first == 0) {
            f = 1;
        }
        for (int i = 0; i < v.size(); i++) {
            if (v[i].first == 0) {
                continue;
            }
            int last = (i == 0 ? 0 : v[i - 1].first);
            if (v[i].first - last > 1) {
                if (!f) {
                    cout << "Alice" << endl;
                } else {
                    cout << "Bob" << endl;
                }
                ok = 1;
                break;
            }
            if (v[i].second > 1) {
                if (f) {
                    cout << "Alice" << endl;
                } else {
                    cout << "Bob" << endl;
                }
                ok = 1;
                break;
            }

        }
        if (!ok) {
            if (f) {
                cout << "Alice" << endl;
            } else {
                cout << "Bob" << endl;
            }
        }



    }

    return 0;
}
