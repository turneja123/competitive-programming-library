//https://www.hackerearth.com/challenges/competitive/june-circuits-23/algorithm/no-inversions-db0ebea5/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 500;

long long a[N];
long long freq[N][M];
long long nxt[N];
string s;
vector<pair<long long, long long>> heavy;

long long calc(long long n) {
    long long seg = n * (n + 1) / (long long)2;
    return seg;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        string s;
        cin >> n >> s;
        int sum = 1;
        a[0] = sum;
        for (int i = 1; i < n; i++) {
            if (s[i] >= s[i - 1]) {
                sum++;
            } else {
                if (sum < M) {
                    freq[i - 1][sum]++;
                } else {
                    heavy.push_back({i - sum, i - 1});
                }
                for (int j = i - sum; j < i; j++) {
                    nxt[j] = i - 1;
                }
                sum = 1;
            }
            a[i] = sum;
            for (int j = 1; j < M; j++) {
                freq[i][j] += freq[i - 1][j];
            }
        }
        if (sum < M) {
            freq[n - 1][sum]++;
        } else {
            heavy.push_back({n - sum, n - 1});
        }
        for (int j = n - sum; j < n; j++) {
            nxt[j] = n - 1;
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            long long l, r;
            cin >> l >> r;
            l--, r--;
            long long ans = 0;
            ans += calc(min((long long)a[r], (long long)(r - l + 1)));
            r -= a[r];
            if (l > r) {
                cout << ans << endl;
                continue;
            }
            ans += calc((long long)(min((long long)a[nxt[l]], (long long)(nxt[l] - l + 1))));
            l = nxt[l] + 1;
            if (l > r) {
                cout << ans << endl;
                continue;
            }
            for (long long j = 1; j < M; j++) {
                long long add = freq[r][j];
                if (l > 0) {
                    add -= freq[l - 1][j];
                }
                ans += add * calc(j);
            }
            for (int j = 0; j < heavy.size(); j++) {
                if (l <= heavy[j].first && r >= heavy[j].second) {
                    ans += calc((long long)(heavy[j].second - heavy[j].first + 1));
                }
            }
            cout << ans << endl;
        }
        heavy.clear();
        for (int i = 0; i < n; i++) {
            a[i] = 0;
            nxt[i] = 0;
            for (int j = 1; j < M; j++) {
                freq[i][j] = 0;
            }
        }
    }
    return 0;
}
