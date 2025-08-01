//https://www.spoj.com/problems/SAMER08K/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;

int freq[N];

int main() {
    IOS;
    while (1) {
        int n;
        cin >> n;
        if (!n) {
            break;
        }
        int s = 0;
        vector<int> diff(n), a(n);
        for (int i = 0; i < n; i++) {
            cin >> diff[i];
            s += diff[i];
            a[i] = (i == 0 ? 0 : a[i - 1] + diff[i - 1]);
        }
        int ans = n + 1;
        for (int i = 3; i <= n; i++) {
            if (s % i != 0) {
                continue;
            }
            int d = s / i;
            for (int j = 0; j < n; j++) {
                freq[a[j] % d]++;
                if (freq[a[j] % d] == i) {
                    ans = i;
                }
            }
            for (int j = 0; j < n; j++) {
                freq[a[j] % d] = 0;
            }
        }
        cout << n - ans << endl;
    }
    return 0;
}
