//https://cses.fi/problemset/task/3139/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> calc(int l, int r) {
    if (l == r) {
        return {l};
    }
    int mid = (l + r) / 2;
    vector<int> lf = calc(l, mid);
    vector<int> rt = calc(mid + 1, r);
    int i = 0, j = 0;
    vector<int> cur;
    while (i < lf.size() && j < rt.size()) {
        cout << "? " << lf[i] + 1 << " " << rt[j] + 1 << endl;
        string s;
        cin >> s;
        if (s == "YES") {
            cur.push_back(lf[i++]);
        } else {
            cur.push_back(rt[j++]);
        }
    }
    while (i < lf.size()) {
        cur.push_back(lf[i++]);
    }
    while (j < rt.size()) {
        cur.push_back(rt[j++]);
    }
    return cur;
}

int main() {
    //IOS;
    int n;
    cin >> n;
    vector<int> pi = calc(0, n - 1);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[pi[i]] = i;
    }
    cout << "! ";
    for (int i = 0; i < n; i++) {
        cout << p[i] + 1 << " ";
    }
    return 0;
}
