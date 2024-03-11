//https://dmoj.ca/problem/modernart
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const int Y = 1e3 + 5;
const int K = 25;
const long long M = 998244353;

long long w[N];
long long even[K][Y];
long long odd[K][Y];
long long t_even[K][Y];
long long t_odd[K][Y];
long long dp_even[Y];
long long dp_odd[Y];

int main() {
    IOS;
    int n, k, y;
    cin >> n >> k >> y;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < k; i++) {
        even[i][0] = 1;
        odd[i][0] = 0;
        for (int j = i; j < n; j += k) {
            for (int p = 0; p <= y; p++) {
                t_even[i][p] = even[i][p];
                t_odd[i][p] = odd[i][p];
            }

            for (int p = w[j]; p <= y; p++) {
                even[i][p] = (even[i][p] + t_odd[i][p - w[j]]) % M;
                odd[i][p] = (odd[i][p] + t_even[i][p - w[j]]) % M;

            }
        }
    }
    for (int p = 0; p <= y; p++) {
        dp_even[p] = even[0][p];
        dp_odd[p] = odd[0][p];
    }

    for (int i = 1; i < k; i++) {
        for (int p = 0; p <= y; p++) {
            t_even[0][p] = dp_even[p];
            t_odd[0][p] = dp_odd[p];
        }
        for (int p = 0; p <= y; p++) {
            dp_even[p] = 0;
            dp_odd[p] = 0;
            for (int j = 0; j <= p; j++) {
                dp_even[p] = (dp_even[p] + (t_even[0][p - j] * even[i][j]) % M) % M;
                dp_odd[p] = (dp_odd[p] + (t_odd[0][p - j] * odd[i][j]) % M) % M;
            }
        }
    }
    cout << (dp_even[y] + dp_odd[y]) % M << endl;
    return 0;
}
