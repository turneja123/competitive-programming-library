//https://qoj.ac/contest/2509/problem/14095
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

bool comp(pair<int, int> &a, pair<int, int> &b) {
    return a.second + a.first > b.second + b.first;
}

int main() {
	IOS;
	int n;
	cin >> n;
	n *= 2;
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        if (l > r) {
            swap(l, r);
        }
        a[i] = {l, r};
	}
	sort(a.begin(), a.end(), comp);
	ll ans = 0;
	for (int i = 0; i < n / 2; i++) {

        ans += a[i].second;
	}
	for (int i = n / 2; i < n; i++) {
        ans -= a[i].first;
	}
	cout << ans;

	return 0;
}
