//https://www.codechef.com/START200A/problems/LEXMATCH
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;
const int N = 3005;

int b[N];

struct Data {
    vector<ll> dp;
    vector<ll> cur;
};

int n, k;
vector<ll> tmp;

void f0(Data &d){
    tmp[0] = 0;
    for (int i = 1; i <= k; i++) {
        tmp[i] = (tmp[i - 1] + d.dp[i - 1] * d.cur[i]) % M;
    }
    d.dp.swap(tmp);
    for (int i = 0; i < d.cur.size(); i++) {
        d.cur[i] = 1;
    }
};

void f1(Data &d, vector<ll> &f){
    for (int i = 1; i <= k; i++) {
        d.cur[i] = d.cur[i] * f[i] % M;
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        tmp.clear();
        tmp.resize(k + 1);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        bool fl = b[0] == 1;
        for (int i = 0; i < n - 1; i++) {
            if (b[i + 1] - b[i] > 1) {
                fl = false;
            }
        }
        if (!fl) {
            cout << 0 << endl;
            continue;
        }
        vector<Data> st;
        vector<ll> ans;

        for (int i = 1; i <= n; i++) {
            while (st.size() > b[i - 1]) {
                f0(st.back());
                vector<ll> x = st.back().dp;
                st.pop_back();
                if (!st.empty()) {
                    f1(st.back(), x);
                } else {
                    ans = x;
                }
            }

            if (st.size() == b[i - 1] - 1) {
                Data d;
                for (int i = 0; i <= k; i++) {
                    d.dp.push_back(1);
                    d.cur.push_back(1);
                }
                st.push_back(d);
            } else if (st.size() == b[i - 1]) {
                f0(st.back());
            }
        }


        while (!st.empty()) {
            f0(st.back());
            vector<ll> x = st.back().dp;
            st.pop_back();
            if (!st.empty()) {
                f1(st.back(), x);
            } else {
                ans = x;
            }
        }
        cout << ans[k] << endl;

    }
    return 0;
}
