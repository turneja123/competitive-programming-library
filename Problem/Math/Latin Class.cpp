//solution for https://dmoj.ca/problem/utso21p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 1e9 + 7;
int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = a[0];
    ll mul = 1;
    ll ans = 1;
    for (int i = 1; i < n; i++) {
        mul++;
        if (a[i] >= mx) {
            mx = a[i];
            ans *= mul;
            ans %= M;
            mul = 1;
        }
    }
    cout << ans << endl;


    return 0;
}
