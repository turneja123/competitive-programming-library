//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll INF = 1e18;

int is_prime[N];
ll pref[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pref[a] += a;
    }
    for (int i = 1; i < N; i++) {
        pref[i] *= is_prime[i];
        pref[i] += pref[i - 1];
    }
    ll best = -INF;
    vector<int> ans;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        ll cur = b - pref[min(N - 1, b)];
        if (cur == best) {
            ans.push_back(i);
        } else if (cur > best) {
            ans.clear();
            ans.push_back(i);
            best = cur;
        }
    }
    cout << best << endl;
    for (int i : ans) {
        cout << i << " ";
    }

    return 0;
}
