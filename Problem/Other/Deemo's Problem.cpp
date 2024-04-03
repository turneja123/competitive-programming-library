//https://dmoj.ca/problem/dproblem
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int n, m;

int heavy() {
    int ans = 0;
    for (int j = m; j <= n; j += m) {
        vector<int> freq(m + 1, 0);
        int ct = 0;
        for (int i = 0; i < j; i++) {
            freq[a[i]]++;
            if (freq[a[i]] == j / m) {
                ct++;
            }
            if (freq[a[i]] == j / m + 1) {
                ct--;
            }
        }
        if (ct == m) {
            ans++;
        }
        for (int i = j; i < n; i++) {
            freq[a[i - j]]--;
            if (freq[a[i - j]] == j / m - 1) {
                ct--;
            }
            if (freq[a[i - j]] == j / m) {
                ct++;
            }
            freq[a[i]]++;
            if (freq[a[i]] == j / m) {
                ct++;
            }
            if (freq[a[i]] == j / m + 1) {
                ct--;
            }
            if (ct == m) {
                ans++;
            }
        }
    }
    return ans;
}

long long light() {
    map<vector<int>, long long> mp[m];
    vector<int> cur(m, 0);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        mp[i % m][cur]++;
        cur[a[i] - 1]++;
        int mn = n;
        for (int j = 0; j < m; j++) {
            mn = min(mn, cur[j]);
        }
        for (int j = 0; j < m; j++) {
            cur[j] -= mn;
        }
        ans += mp[(i + 1) % m][cur];
    }
    return ans;
}

int main() {
    IOS;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << ((m > sqrt(n)) ? heavy() : light());

    return 0;
}
