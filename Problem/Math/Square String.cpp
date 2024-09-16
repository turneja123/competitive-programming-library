//https://www.codechef.com/problems/SQING
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const long long M = 1e9 + 7;

long long aux[N];
long long ans[N];

int main() {
    IOS;
    aux[1] = 0;
    aux[2] = 1;
    for (int i = 3; i < N; i++) {
        aux[i] = (aux[i - 1] * 2 + (long long)(i - 1) * (i - 1)) % M;
    }
    for (int i = 2; i < N; i++) {
        ans[i] = (ans[i - 1] + aux[i]) * 2 % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << ans[n] << endl;
    }



    return 0;
}
