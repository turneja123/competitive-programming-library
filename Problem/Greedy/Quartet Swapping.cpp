//https://codeforces.com/contest/2101/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> comp(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] < b[i]) {
            return a;
        } else if (a[i] > b[i]) {
            return b;
        }
    }
    return a;
}

ll inv(vector<int> a) {
    ll I = 0;
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr;
    for (int i = 0; i < a.size(); i++) {
        I += tr.size() - tr.order_of_key(a[i]);
        tr.insert(a[i]);
    }
    return I;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> l, r;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (i % 2 == 0) {
                l.push_back(a);
            } else {
                r.push_back(a);
            }
        }
        int f = 0;
        if (inv(l) % 2 != inv(r) % 2) {
            f = 1;
        }
        sort(l.begin(), l.end());
        sort(r.begin(), r.end());
        vector<int> ans;
        int i = 0, j = 0, t = 0;
        while (i < l.size() && j < r.size()) {
            if (t % 2 == 0) {
                ans.push_back(l[i++]);
            } else {
                ans.push_back(r[j++]);
            }
            t++;
        }
        while (i < l.size()) {
            ans.push_back(l[i++]);
        }
        while (j < r.size()) {
            ans.push_back(r[j++]);
        }
        if (f) {
            swap(ans[n - 1], ans[n - 3]);
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
