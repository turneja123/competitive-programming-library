//https://codeforces.com/contest/2055/problem/D
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
    int t;
    cin >> t;
    while (t--) {
        int n, k, len;
        cin >> n >> k >> len;
        k *= 2, len *= 2; //prolintac trik
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] *= 2;
        }
        int tim = a[0];
        int pos = k;
        for (int i = 1; i < n && pos < len; i++) {
            int l = a[i] - tim;
            int r = a[i] + tim;
            if (l <= pos && r >= pos) {
                pos += k;
            } else if (l > pos) {
                int diff = (l - pos) / 2;
                if (pos + diff >= len) {
                    tim += len - pos;
                    pos = len;
                    break;
                }
                tim += diff;
                pos += diff + k;
            } else {
                pos = max(pos, r + k);
            }
        }
        tim += max(0, len - pos);
        cout << tim << endl;
    }
    return 0;
}
