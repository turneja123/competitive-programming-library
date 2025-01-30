//https://codeforces.com/contest/2063/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const long long INF = 1e18;

int a[N];
int b[N];

long long calc(int ka, int kb, vector<long long> &prefa, vector<long long> &prefb, int n, int m) {
    int needa = 2 * ka + kb;
    int needb = 2 * kb + ka;
    if (needa > n || needb > m || ka > prefa.size() || kb > prefb.size()) {
        return -INF;
    }
    long long ans = (ka == 0 ? 0 : prefa[ka - 1]) + (kb == 0 ? 0 : prefb[kb - 1]);
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        sort(a, a + n);
        sort(b, b + m);
        vector<int> va, vb;
        vector<long long> prefa, prefb;
        for (int i = 0; i < n / 2; i++) {
            va.push_back(a[n - 1 - i] - a[i]);
        }
        for (int i = 0; i < m / 2; i++) {
            vb.push_back(b[m - 1 - i] - b[i]);
        }
        sort(va.begin(), va.end());
        sort(vb.begin(), vb.end());
        reverse(va.begin(), va.end());
        reverse(vb.begin(), vb.end());
        prefa.resize(va.size());
        prefb.resize(vb.size());
        for (int i = 0; i < prefa.size(); i++) {
            prefa[i] = (i == 0 ? va[i] : va[i] + prefa[i - 1]);
        }
        for (int i = 0; i < prefb.size(); i++) {
            prefb[i] = (i == 0 ? vb[i] : vb[i] + prefb[i - 1]);
        }
        vector<long long> v;
        for (int i = 1; i < n + m; i++) {
            int l = max(0, 2 * i - m), r = min(i, n - i);
            while (r - l >= 3) {
                int m1 = l + (r - l) / 3;
                int m2 = r - (r - l) / 3;

                long long f1 = calc(m1, i - m1, prefa, prefb, n, m);
                long long f2 = calc(m2, i - m2, prefa, prefb, n, m);

                if (f1 < f2) {
                    l = m1 + 1;
                } else {
                    r = m2 - 1;
                }
            }
            long long ans = -INF;
            for (; l <= r; l++) {
                ans = max(ans, calc(l, i - l, prefa, prefb, n, m));
            }
            if (ans == -INF) {
                break;
            }
            v.push_back(ans);
        }
        cout << v.size() << endl;
        for (long long x : v) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
