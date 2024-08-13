//https://www.spoj.com/problems/GOSTONES/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 0;
        for (int i = 1; 2 * i * i <= n; i++) {
            ans = (ans + p[n - 2 * i * i] * ((i % 2 == 1) ? 1 : -1) + M) % M;
        }
        cout << ans << endl;
    }


    return 0;
}
