//https://www.spoj.com/problems/AROPE/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    string s;
    cin >> s;
    rope<char> r;
    for (int i = 0; i < s.size(); i++) {
        r.push_back(s[i]);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 3) {
            int j;
            cin >> j;
            cout << r[j] << endl;
        } else {
            int lq, rq;
            cin >> lq >> rq;
            rope<char> sub = r.substr(lq, rq - lq + 1);
            r.erase(lq, rq - lq + 1);
            if (t == 2) {
                r += sub;
            } else {
                r.insert(0, sub);
            }
        }
    }
    return 0;
}
