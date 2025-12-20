//https://codeforces.com/contest/2180/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (k % 2 == 1) {
            for (int i = 0; i < k; i++ ){
                cout << n << " ";
            }
            cout << endl;
            continue;
        }
        int p;
        for (int i = 30; i >= 0; i--) {
            int c = (1 << i) & n;
            if (c) {
                p = i;
                break;
            }
        }
        int P = 1 << p;
        vector<int> v(k, P);
        v.back() = 0;

        for (int i = p - 1; i >= 0; i--) {
            int c = (1 << i) & n;
            if (c) {
                for (int j = 1; j < k; j += 2) {
                    int nx = v[j] + (1 << i);
                    if (nx <= n) {
                        for (int z = j; z < k; z++) {
                            v[z] += 1 << i;
                        }
                        break;
                    }
                }
            } else {
                for (int j = 0; j < k; j += 2) {
                    int nx = v[j] + (1 << i);
                    if (nx <= n) {
                        for (int z = j; z < k; z++) {
                            v[z] += 1 << i;
                        }
                        break;
                    }
                }
            }


            sort(v.begin(), v.end(), greater<int>());
        }
        for (auto x : v) {
            cout << x << " ";
        }
        cout << endl;

    }
    return 0;
}
