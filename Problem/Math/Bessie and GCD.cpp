//https://contest.joincpi.org/contest?id=Myb-ebc4AHL67vnWMucwU&tab=problem-vD1BCj6b2Fx4Xn4cuf-sy
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int phi[N];
ll ans[N];

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
    for (int i = 2; i < N; i++) {
        if (!(phi[i] == i - 1)) {
            continue;
        }
        for (int j = 2 * i; j < N; j += i) {
            ans[j] += phi[j / i];
        }
    }
    for (int i = 1; i < N; i++) {
        ans[i] += ans[i - 1];
    }
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        cout << ans[r] - ans[l - 1] << endl;
    }

	return 0;
}
