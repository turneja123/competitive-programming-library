//https://codeforces.com/contest/2157/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int freq[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            freq[a]++;
        }
        set<int> st;
        set<int> big;
        for (int i = 1; i <= 3 * n + 5; i++) {
            if (freq[i] == 0) {
                st.insert(i);
            }
            if (freq[i] > 1) {
                big.insert(i);
            }
        }
        int ans = 0;
        for (int i = 2 * n; i > 0; i--) {
            if (freq[i] > k) {
                int j = freq[i] - k;
                auto it = st.upper_bound(i);
                auto z = big.upper_bound(i);

                int last = i;
                while (j--) {
                    last = *it;

                    ans = max(ans, *it - i);
                    while (z != big.end() && *z <= *it) {
                        j += freq[*z] - 1;
                        z = big.erase(z);
                    }

                    it = st.erase(it);
                }
                big.erase(big.find(i));
                freq[last] = k;
                big.insert(last);
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= 3 * n + 5; i++) {
            freq[i] = 0;
        }

    }

    return 0;
}
