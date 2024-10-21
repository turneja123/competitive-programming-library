#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

set<long long> st_inc[10];
set<long long> st_dec[10];

map<long long, int> mp[10][10][3];

long long calc(long long n, long long m) {
    if (n < 1) {
        return 0;
    }
    long long ans = 0;
    for (int i = 1; i < min(10ll, n); i++) {
        if (i % m == 0) {
            ans++;
        }
    }

    long long temp = n;
    int lg10 = 0;
    while (temp > 0) {
        temp /= 10;
        lg10++;
    }
    for (int k = 2; k < 10; k++) {
        if (k + k - 1 > lg10) {
            break;
        }

        for (long long x : st_dec[k]) {
            int tight;
            if (k + k - 1 == lg10) {
                string a = to_string((long long)n);
                string b = to_string((long long)x);
                a = a.substr(a.size() - k, k);
                if (a > b) {
                    tight = 0;
                } else if (a == b) {
                    tight = 2;
                } else {
                    tight = 1;
                }
            } else {
                tight = 0;
            }
            string b = to_string((long long)x);
            string f = b.substr(0, 1);
            int first = stoi(f);
            mp[first][k][tight][x % m]++;
        }
    }
    long long pw = 100;
    for (int k = 1; k < 9; k++) {
        if (k + k + 1 > lg10) {
            break;
        }
        for (long long x : st_inc[k]) {
            int tight;
            if (k + k + 1 == lg10) {
                string a = to_string((long long)n);
                string b = to_string((long long)x);
                a = a.substr(0, k);
                if (a > b) {
                    tight = 0;
                } else if (a == b) {
                    tight = 2;
                } else {
                    tight = 1;
                }
            } else {
                tight = 0;
            }
            long long md = (m - pw * x % m) % m;
            string b = to_string((long long)x);
            string f = b.substr(b.size() - 1, 1);
            int last = stoi(f);
            for (int d = last + 1; d < 10; d++) {
                if (tight == 0) {
                    ans += mp[d][k + 1][0][md];
                    ans += mp[d][k + 1][1][md];
                    ans += mp[d][k + 1][2][md];
                } else if (tight == 2) {
                    ans += mp[d][k + 1][0][md];
                    ans += mp[d][k + 1][2][md];
                }
            }
        }
        pw *= 10;
    }
    for (int k = 1; k < 10; k++) {
        for (int d = 0; d < 10; d++) {
            mp[d][k][0].clear();
            mp[d][k][1].clear();
            mp[d][k][2].clear();
        }
    }
    return ans;
}

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    for (int i = 1; i < 10; i++) {
        st_inc[1].insert(i);
    }
    for (int i = 2; i < 10; i++) {
        for (long long x : st_inc[i - 1]) {
            int d = x % 10;
            for (int j = d; j < 10; j++) {
                st_inc[i].insert(x * 10 + j);
            }
        }
    }
    for (int i = 1; i < 10; i++) {
        st_dec[1].insert(i);
    }
    for (int i = 2; i < 10; i++) {
        for (long long  x : st_dec[i - 1]) {
            int d = x % 10;
            if (i == 2) {
                d--;
            }
            for (int j = 1; j <= d; j++) {
                st_dec[i].insert(x * 10 + j);
            }
        }
        //cout << st_dec[i].size() << " ";
    }

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long a, b, m;
        cin >> a >> b >> m;

        cout << "Case #" << tt << ": " << calc(b, m) - calc(a - 1, m) << endl;
    }

    return 0;
}
