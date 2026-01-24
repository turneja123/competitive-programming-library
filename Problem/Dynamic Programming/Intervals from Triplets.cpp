//https://qoj.ac/problem/16121
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9 + 5;

int dp[2];
int dp_nx[2];
int last[2];

struct Info {
    int a;
    int b;
    int c;
};

int main() {
    IOS;
    int n;
    cin >> n;
    vector<Info> v;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        v.push_back({a, b, c});
    }
    sort(v.begin(), v.end(), [&](auto a, auto b) {return a.b < b.b;});

    for (int i = 0; i < n; i++) {
        if (i != 0 && v[i - 1].b == v[i].b) {
            continue;
        }
        dp_nx[0] = -1, dp_nx[1] = -1;
        if (i + 2 < n && v[i].b == v[i + 2].b) {
            cout << -1;
            return 0;
        }
        if (i + 1 < n && v[i].b == v[i + 1].b) {
            for (int j = 0; j < 2; j++) {
                if (dp[j] == -1) {
                    continue;
                }
                if (v[i].a >= last[j]) {
                    dp_nx[0] = max(dp_nx[0], dp[j] + v[i + 1].c - v[i].a);
                }
                if (v[i + 1].a >= last[j]) {
                    dp_nx[1] = max(dp_nx[1], dp[j] + v[i].c - v[i + 1].a);
                }
            }
            last[0] = v[i + 1].c;
            last[1] = v[i].c;
        } else {
            for (int j = 0; j < 2; j++) {
                if (dp[j] == -1) {
                    continue;
                }
                if (v[i].a >= last[j]) {
                    dp_nx[0] = max(dp_nx[0], dp[j] + v[i].b - v[i].a);
                    dp_nx[1] = max(dp_nx[1], dp[j] + v[i].c - v[i].a);
                }
                if (v[i].b >= last[j]) {
                    dp_nx[1] = max(dp_nx[1], dp[j] + v[i].c - v[i].b);
                }
            }
            last[0] = v[i].b;
            last[1] = v[i].c;
        }
        dp[0] = dp_nx[0];
        dp[1] = dp_nx[1];
    }
    cout << max(dp[0], dp[1]);

    return 0;
}
