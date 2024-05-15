//https://www.spoj.com/problems/CANPR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int phi[N];

vector<long long> ans[N];
vector<long long> pref[N];

int main() {
	IOS;
	for (int i = 0; i < N; i++) {
        phi[i] = i;
	}
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {
            for (int j = i; j < N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    for (int i = 1; i < N; i++) {
        ans[i].push_back(0);
        for (int j = i; j < N; j += i) {
            ans[i].push_back(phi[j / i]);
        }
        pref[i].resize(ans[i].size());
        pref[i][0] = ans[i][0];
        for (int j = 1; j < ans[i].size(); j++) {
            pref[i][j] = pref[i][j - 1] + ans[i][j];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, g;
        cin >> n >> g;
        if (g > n) {
            cout << 0 << endl;
        } else {
            long long sum = pref[g][n / g] * 2 - 1;
            cout << sum << endl;
        }
    }

	return 0;
}
