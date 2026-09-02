//https://codeforces.com/contest/1599/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e9;

int main() {
    //IOS;
    int lu;
    cout << "? 1 1" << endl;
    cin >> lu;
    int l = 2, r = N, x1;
    while (l <= r) {
        int mid = (l + r) / 2;
        cout << "? 1 " << mid << endl;
        int x;
        cin >> x;
        if (lu - x == mid - 1) {
            x1 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    int ru;
    cout << "? 1 " << N << endl;
    cin >> ru;
    int k = lu - ru;
    int x2 = k - x1 + N + 1;

    int y1 = lu - x1 + 2;

    int ld;
    cout << "? " <<N << " " << 1 << endl;
    cin >> ld;
    k = lu - ld;
    int y2 = k - y1 + N + 1;
    cout << "! " << y1 << " " << x1 << " " << y2 << " " << x2 << endl;

    return 0;
}
