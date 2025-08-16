//https://www.codechef.com/problems/DSP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;

int spf[N];
bool seen[N];

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        spf[i] = i;
    }
    for (int i = 2; i < N; i++) {
        if (spf[i] == i) {
            for (int j = 2 * i; j < N; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        vector<int> rem;
        do {
            if (a[0] == '0') {
                continue;
            }
            int x = 0;
            for (int i = 0; i < a.size(); i++) {
                x *= 10;
                x += a[i] - '0';
            }
            while (x > 1) {
                int p = spf[x];
                if (!seen[p]) {
                    seen[p] = true;
                    rem.push_back(p);
                }
                x /= spf[x];
            }

        } while (next_permutation(a.begin(), a.end()));
        int ans = 1;
        a = b;
        do {
            if (a[0] == '0') {
                continue;
            }
            int x = 0;
            for (int i = 0; i < a.size(); i++) {
                x *= 10;
                x += a[i] - '0';
            }
            while (x > 1) {
                int p = spf[x];
                if (seen[p]) {
                    ans = max(ans, p);
                }
                x /= spf[x];
            }

        } while (next_permutation(a.begin(), a.end()));
        for (int p : rem) {
            seen[p] = false;
        }
        cout << ans << endl;
    }

    return 0;
}
