#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int a, b, c, d;
	cin >> a >> b >> c >> d;
	cout << (abs(a + d - b - c) + 1) / 2;
    return 0;
}
