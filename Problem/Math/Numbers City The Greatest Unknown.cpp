//https://ocpc2025s.eolymp.space/en/compete/sk55ojcma10djasruv04qdm2fo/problem/11
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

bool is_prime[N];
int orig[N];
int freq[N];
int dp[N];
int ans[N];

vector<int> events;
vector<int> divs[N];

void calc(int l, int r, vector<int> a) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    for (int i = mid; i <= r; i++) {
        int m = divs[events[i]].size();
        for (int j = 0; j < 1 << m; j++) {
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = (1 << k) & j;
                if (c) {
                    prod *= divs[events[i]][k];
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
            ans[a[i]] = events[mid];
            rt.push_back(a[i]);
        } else {
            lf.push_back(a[i]);
        }
    }
    for (int i = mid; i <= r; i++) {
        int m = divs[events[i]].size();
        for (int j = 0; j < 1 << m; j++) {
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = (1 << k) & j;
                if (c) {
                    prod *= divs[events[i]][k];
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
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (freq[x] == 0) {
            a.push_back(x);
        }
        freq[x]++;
        orig[i] = x;
    }
    sort(a.begin(), a.end());
    events = a;
    int m = a.size();
    calc(0, m - 1, a);
    for (int i = 0; i < n; i++) {
        cout << ans[orig[i]] << " ";
    }


    return 0;
}
