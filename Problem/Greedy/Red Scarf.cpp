//https://atcoder.jp/contests/abc171/tasks/abc171_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        sum ^= a[i] ^ a[i + 1];
    }
    for (int i = 0; i < n; i++) {
        a[i] ^= sum;
        cout << a[i] << " ";
    }
    return 0;
}
