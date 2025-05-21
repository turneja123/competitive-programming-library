//https://cses.fi/problemset/task/3423
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

bool is_prime[N];

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1, 0);
    iota(a.begin(), a.end(), 0);
    int last = n;
    for (int i = n; i >= 1; i--) {
        if (is_prime[last + i]) {
            for (int j = last, k = i; j >= i; j--, k++) {
                b[j] = k;
            }
            last = i - 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << b[i] << " ";
    }
    return 0;
}
