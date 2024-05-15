//https://www.spoj.com/problems/GCDEX/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int phi[N];
long long ans[N];
long long pref[N];

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
        for (int j = i; j < N; j += i) {
            ans[j] += (long long)i * phi[j / i];
        }
    }
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i - 1] + ans[i] - i;
    }
    int t;
    cin >> t;
    while (t != 0) {
        cout << pref[t] << endl;
        cin >> t;
    }

	return 0;
}
