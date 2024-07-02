//https://atcoder.jp/contests/abc250/tasks/abc250_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N], b[N];
map<int, long long> mp;
long long ha[N], hb[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

long long gen() {
    long long h = generator() + ((long long)generator() << 30);
    return h;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    set<int> st;
    long long h = 0;
    for (int i = 0; i < n; i++) {
        if (st.find(a[i]) == st.end()) {
            st.insert(a[i]);
            if (mp.find(a[i]) == mp.end()) {
                mp[a[i]] = gen();
            }
            h ^= mp[a[i]];
        }
        ha[i] = h;

    }
    st.clear();
    h = 0;
    for (int i = 0; i < n; i++) {
        if (st.find(b[i]) == st.end()) {
            st.insert(b[i]);
            if (mp.find(b[i]) == mp.end()) {
                mp[b[i]] = gen();
            }
            h ^= mp[b[i]];
        }
        hb[i] = h;
    }
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (ha[x] == hb[y]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
