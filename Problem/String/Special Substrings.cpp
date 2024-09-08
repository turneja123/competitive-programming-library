//https://cses.fi/problemset/task/2186/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int b[26];
int n, m;
string s;

long long light() {
    map<vector<int>, long long> mp[m];
    vector<int> cur(m, 0);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        mp[i % m][cur]++;
        cur[a[i]]++;
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
    cin >> s;
    n = s.size();
    map<char, int> mp;
    for (int i = 0; i < n; i++) {
        auto it = mp.find(s[i]);
        if (it == mp.end()) {
            mp[s[i]] = mp.size();
        }
        a[i] = mp[s[i]];
    }
    m = mp.size();
    cout << light();

    return 0;
}
