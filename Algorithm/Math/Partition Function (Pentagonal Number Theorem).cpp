//https://judge.yosupo.jp/problem/partition_function
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const long long M = 998244353;

vector<pair<int, int>> g;

long long p[N];

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        g.push_back(make_pair(i * (3 * i - 1) / 2, i % 2 == 1 ? 1 : -1));
        g.push_back(make_pair(i * (3 * i + 1) / 2, i % 2 == 1 ? 1 : -1));
        if (g[g.size() - 1].first > N) {
            break;
        }
    }
    p[0] = 1, p[1] = 1;
    for (int i = 2; i < N; i++) {
        for (int j = 0; j < g.size() && g[j].first <= i; j++) {
            p[i] = (p[i] + p[i - g[j].first] * g[j].second + M) % M;
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        cout << p[i] << " ";
    }


    return 0;
}
