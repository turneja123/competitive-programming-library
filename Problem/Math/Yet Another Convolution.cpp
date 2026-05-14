//https://codeforces.com/gym/102354/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

bool is_prime[N];
int a[N];
int b[N];
int dp[N];
ll ans[N];
ll c[N];

vector<pair<int, int>> events;
vector<int> divs[N];

void calc(int l, int r, vector<int> a) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    for (int i = l; i <= mid; i++) {
        int m = divs[events[i].second].size();
        for (int j = 0; j < 1 << m; j++) {
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = (1 << k) & j;
                if (c) {
                    prod *= divs[events[i].second][k];
                }
            }
            dp[prod]++;
        }
    }
    vector<int> lf, rt;
    for (int i = 0; i < a.size(); i++) {
        int m = divs[a[i]].size();
        int s = 0;
        for (int j = 0; j < 1 << m; j++) {
            int mul = 1;
            if (__builtin_popcount(j) % 2 == 1) {
                mul *= -1;
            }
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = (1 << k) & j;
                if (c) {
                    prod *= divs[a[i]][k];
                }
            }
            s += mul * dp[prod];
        }
        if (s > 0) {
            ans[a[i]] = events[mid].first;
            lf.push_back(a[i]);
        } else {
            rt.push_back(a[i]);
        }
    }
    for (int i = l; i <= mid; i++) {
        int m = divs[events[i].second].size();
        for (int j = 0; j < 1 << m; j++) {
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = (1 << k) & j;
                if (c) {
                    prod *= divs[events[i].second][k];
                }
            }
            dp[prod] = 0;
        }
    }
    if (l <= mid - 1) {
        calc(l, mid - 1, lf);
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, rt);
    }
    return;
}

ll solve(int n, int k, int t) {
    events.clear();
    vector<int> a;
    int m = n / k;
    for (int i = 1; i <= m; i++) {
        if (t == 0) {
            events.push_back({b[i * k], i});
        } else {
            events.push_back({::a[i * k], i});
        }
        a.push_back(i);
    }
    sort(events.begin(), events.end());
    calc(0, m - 1, a);
    ll ret = 0;
    for (int i = 1; i <= m; i++) {
        if (t == 0) {
            ret = max(ret, (ll)::a[i * k] - ans[i]);
        } else {
            ret = max(ret, (ll)b[i * k] - ans[i]);
        }
    }
    return ret;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            divs[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
                divs[j].push_back(i);
            }
        }
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int k = 1; k <= n; k++) {
        c[k] = max(solve(n, k, 0), solve(n, k, 1));
    }
    for (int i = 1; i <= n; i++) {
        cout << c[i] << " ";
    }


    return 0;
}
