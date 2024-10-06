//https://codeforces.com/contest/1497/problem/E1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;

int a[N];
int spf[N];
bool is_prime[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        set<vector<int>> st;
        for (int i = 0; i < n; i++) {
            vector<int> v;
            while (a[i] > 1) {
                int p = spf[a[i]], e = 0;
                while (a[i] % p == 0) {
                    e++;
                    a[i] /= p;
                }
                if (e % 2 == 1) {
                    v.push_back(p);
                }
            }
            auto it = st.find(v);
            if (it != st.end()) {
                ans++;
                st.clear();
            }
            st.insert(v);
        }
        cout << ans + 1 << endl;
    }

    return 0;
}
