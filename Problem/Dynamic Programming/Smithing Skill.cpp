//https://codeforces.com/contest/1989/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9 + 5;

int a[N];
int b[N];
int c[N];
long long dp[N];

bool comp(pair<int, int> &a, pair<int, int> &b) {
    if (a.first - a.second != b.first - b.second) {
        return a.first - a.second > b.first - b.second;
    }
    return a.first < b.first;
}

long long calc(int c, vector<pair<int, int>> &pr) {
    if (c < N && dp[c] != -1) {
        return dp[c];
    }
    int j = upper_bound(pr.begin(), pr.end(), make_pair(c, INF)) - pr.begin() - 1;
    if (j == -1) {
        return 0;
    }
    long long ct = (c - pr[j].first) / (pr[j].first - pr[j].second) + 1;
    long long ans = 2 * ct + calc(c - ct * (pr[j].first - pr[j].second), pr);
    if (c < N) {
        dp[c] = ans;
    }
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < N; i++) {
        dp[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> tmp(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        tmp[i] = make_pair(a[i], b[i]);
    }
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    sort(tmp.begin(), tmp.end(), comp);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (st.size() && tmp[st.top()].first - tmp[st.top()].second == tmp[i].first - tmp[i].second) {
            continue;
        }
        while (st.size() && tmp[st.top()].first >= tmp[i].first) {
            st.pop();
        }
        st.push(i);
    }
    vector<pair<int, int>> pr;
    while (st.size()) {
        pr.push_back(tmp[st.top()]);
        st.pop();
    }
    reverse(pr.begin(), pr.end());
    n = pr.size();
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans += calc(c[i], pr);
    }
    cout << ans << endl;
    return 0;
}
