//https://cses.fi/problemset/task/1745/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

bitset<N> b;

int main() {
	IOS;
	int n;
	cin >> n;
	b.set(0);
	for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b |= (b << x);
	}
	b.reset(0);
	cout << b.count() << endl;
	for (int i = 0; i < N; i++) {
        if (b[i]) {
            cout << i << " ";
        }
	}


	return 0;
}
