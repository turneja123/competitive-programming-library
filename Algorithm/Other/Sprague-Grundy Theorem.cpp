//https://codeforces.com/contest/2004/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e7 + 5;

int grundy[N];
bool is_prime[N];

void brute(int n) {
    grundy[0] = 0;
    for (int i = 1; i <= n; i++) {
        vector<bool> seen(i + 1, false);
        for (int j = 1; j <= i; j++) {
            if (__gcd(i, j) == 1) {
                seen[grundy[i - j]] = true;
            }
        }
        for (int j = 0; j <= i + 1; j++) {
            if (!seen[j]) {
                grundy[i] = j;
                break;
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        cout << i << " " << grundy[i] << endl;
    }
}

int main() {
    IOS;
    //brute(100);
    grundy[1] = 1;
    for (int i = 0; i < N; i += 2) {
        grundy[i] = 0;
    }
    for (int i = 3; i < N; i += 2) {
        grundy[i] = N;
        is_prime[i] = true;
    }
    for (int i = 3, p = 2; i < N; i += 2) {
        if (is_prime[i]) {
            grundy[i] = p++;
            for (int j = 3 * i; j < N; j += 2 * i) {
                is_prime[j] = false;
                grundy[j] = min(grundy[j], grundy[i]);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, sum = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            sum ^= grundy[a];
        }
        if (sum > 0) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
    return 0;
}
