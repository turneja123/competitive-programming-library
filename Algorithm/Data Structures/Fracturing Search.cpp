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

bool comp(vector<int> &a, vector<int> &b) {
    return a[1] - a[0] < b[1] - b[0];
}

int main() {
    IOS;
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
    int ct = 1;
    long long sum = s;
    priority_queue<tuple<long long, int, int>> pq;
    pq.push(make_tuple(-(s + diff[0]), 0, 1));
    while (pq.size() && ct < k) {
        auto [s, i, j] = pq.top();
        s = -s;
        pq.pop();
        ct++;
        sum += s;
        if (j != a[i].size() - 1) {
            pq.push(make_tuple(-(s + a[i][j + 1] - a[i][j]), i, j + 1));
        }
        if (i != a.size() - 1) {
            if (j == 1) {
                pq.push(make_tuple(-(s - (a[i][j] - a[i][j - 1]) + diff[i + 1]), i + 1, 1));
            }
            pq.push(make_tuple(-(s + diff[i + 1]), i + 1, 1));
        }
    }
    cout << sum;
    return 0;
}
