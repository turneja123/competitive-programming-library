//https://usaco.org/index.php?page=viewproblem2&cpid=674
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;
const int INF = 1e9;

vector<vector<int>> a;

int diff[N];

int ct = 0; long long sum = 0;

bool comp(vector<int> &a, vector<int> &b) {
    return a[1] - a[0] < b[1] - b[0];
}

void dfs(long long s, long long mx, int k, int j, int n) {
    if (s > mx || ct >= k) {
        return;
    }
    ct += 1;
    sum += s;
    for (int jj = j + 1; jj < n && ct < k && s + diff[jj] <= mx; jj++) {
        dfs(s + diff[jj], mx, k, jj, n);
    }
    for (int i = 2; i < a[j].size() && ct < k; i++) {
        s += a[j][i] - a[j][i - 1];
        if (s > mx) {
            break;
        }
        ct += 1;
        sum += s;
        for (int jj = j + 1; jj < n && ct < k && s + diff[jj] <= mx; jj++) {
            dfs(s + diff[jj], mx, k, jj, n);
        }
    }
    return;
}

void calc(long long s, long long mx, int k, int n) {
    if (s > mx) {
        return;
    }
    ct += 1;
    sum += s;
    for (int i = 0; i < n && ct < k; i++) {
        if (s + diff[i] <= mx) {
            dfs(s + diff[i], mx, k, i, n);
        }
    }
    return;
}

int main() {
    IOS;
    freopen("roboherd.in", "r", stdin);
    freopen("roboherd.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        a[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
        if (a[i].size() == 1) {
            a[i].push_back(INF);
        }
        sort(a[i].begin(), a[i].end());
    }
    sort(a.begin(), a.end(), comp);
    long long s = 0;
    for (int i = 0; i < n; i++) {
        diff[i] = a[i][1] - a[i][0];
        s += a[i][0];
    }
    long long l = s, r = 1e15, ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        calc(s, mid, k, n);
        if (ct < k) {
            l = mid + 1;
        } else {
            ans = mid;
            r = mid - 1;
        }
        ct = 0, sum = 0;
    }
    calc(s, ans - 1, k, n);
    cout << sum + ans * (k - ct);
    return 0;
}
