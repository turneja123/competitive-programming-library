//https://atcoder.jp/contests/abc250/tasks/abc250_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const long long P = 26, Q = 53;
const int N = 2e5 + 5;

int a[N], b[N];
pair<long long, long long> ha[N], hb[N];

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
    long long p = 1, q = 1;
    for (int i = 0; i < n; i++) {
        if (st.find(a[i]) == st.end()) {
            st.insert(a[i]);
            p = p * (P + a[i]) % M;
            q = q * (Q + a[i]) % M;
        }
        ha[i] = make_pair(p, q);

    }
    p = 1, q = 1;
    st.clear();
    for (int i = 0; i < n; i++) {
        if (st.find(b[i]) == st.end()) {
            st.insert(b[i]);
            p = p * (P + b[i]) % M;
            q = q * (Q + b[i]) % M;
        }
        hb[i] = make_pair(p, q);
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
