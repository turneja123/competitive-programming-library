//https://www.spoj.com/problems/INVPHI/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e8 + 1e7;

int phi[N];
int ans[N];

auto udiv = [](const uint32_t& a, const uint32_t& b) -> uint32_t {
    return (double)a / b + 1e-9;
};

int main() {
	IOS;
	for (int i = 0; i < N; i++) {
        phi[i] = i;
        ans[i] = N;
	}
	ans[1] = 1;
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {
            for (int j = i; j < N; j += i) {
                phi[j] -= udiv(phi[j], i);
            }
        }
        ans[phi[i]] = min(ans[phi[i]], i);
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (ans[n] == N) {
            cout << -1;
        } else {
            cout << ans[n];
        }
        cout << endl;
    }
	return 0;
}
