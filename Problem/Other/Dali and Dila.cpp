//https://www.beecrowd.com.br/judge/en/problems/view/3172
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = n; i > 0; i -= 2) {
        ans ^= (a[i] - a[i - 1]) % (k + 1);
    }
    if (ans) {
        cout << "Dali\n";
    } else {
        cout << "Dila\n";
    }

    return 0;
}
