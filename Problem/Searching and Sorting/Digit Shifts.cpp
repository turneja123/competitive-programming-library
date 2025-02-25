//https://www.spoj.com/problems/DIGSHIFT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long geom[N];
long long pw[N];

int main() {
    IOS;
    pw[0] = 1;
    geom[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 10 % M;
        geom[i] = (geom[i - 1] + pw[i]) % M;
    }
    int t;
    cin >> t;
    long long lval;
    for (int tt = 1; tt <= t; tt++) {
        string l;
        vector<pair<int, int>> r;
        cin >> l;
        vector<int> b(10, 0);
        int q;
        cin >> q;
        cout << "Case " << tt << ":" << endl;
        for (int k = 0; k < q; k++) {
            int d;
            cin >> d;
            if (!b[d]) {
                b[d] = true;
                string nx = "";
                int ct = 0;

                for (int i = 0; i < l.size(); i++) {
                    if (l[i] - '0' != d) {
                        nx += l[i];
                    } else {
                        ct++;
                    }
                }
                string nx2 = "";
                int i = 0;
                while (i < nx.size() && nx[i] == '0') {
                    i++;
                }
                for (int ii = i; ii < nx.size(); ii++) {
                    nx2 += nx[ii];
                }
                l = nx2;
                if (ct) {
                    r.push_back(make_pair(d, ct));
                }
                if (r.size() && l.empty() && r[0].first == 0) {
                    r.erase(r.begin());
                }
                long long ans = 0;
                int p = 0;
                for (int i = r.size() - 1; i >= 0; i--) {
                    auto [x, e] = r[i];
                    ans = (ans + geom[e - 1] * x % M * pw[p] % M) % M;
                    p += e;
                }
                lval = 0;
                for (int i = l.size() - 1; i >= 0; i--, p++) {
                    lval = (lval + pw[p] * (long long)(l[i] - '0')) % M;
                }
                cout << (ans + lval) % M << endl;
            } else {
                int pos = -1;
                pair<int, int> val;
                for (int i = 0; i < r.size(); i++) {
                    if (r[i].first == d) {
                        pos = i;
                        val = r[i];
                        break;
                    }
                }
                if (pos != -1) {
                    r.erase(r.begin() + pos);
                    r.push_back(val);
                }
                if (r.size() && l.empty() && r[0].first == 0) {
                    r.erase(r.begin());
                }
                long long ans = 0;
                int p = 0;
                for (int i = r.size() - 1; i >= 0; i--) {
                    auto [x, e] = r[i];
                    ans = (ans + geom[e - 1] * x % M * pw[p] % M) % M;
                    p += e;
                }
                cout << (ans + lval) % M << endl;
            }
        }
    }

    return 0;
}
