//https://www.codechef.com/problems/MAXMINLEN
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
long long sum[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        sum[i] = (long long)i * (i + 1) / 2;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int first = a[0], last = a[0], s = 0;
        vector<tuple<int, int, int>> blocks;
        for (int i = 0; i < n; i++) {
            if (a[i] - last > 1) {
                blocks.push_back(make_tuple(s, first, last));
                s = 0;
                first = a[i];
            }
            s++;
            last = a[i];
        }
        blocks.push_back(make_tuple(s, first, last));
        long long ans = 0;
        for (int i = 0; i < blocks.size(); i++) {
            auto [s, first, last] = blocks[i];
            for (int j = 0; j < s - 2; j++) {
                ans += sum[s - 2 - j];
            }
            if (i != 0 && first - get<2>(blocks[i - 1]) == 2) {
                ans += (long long)s * get<0>(blocks[i - 1]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
