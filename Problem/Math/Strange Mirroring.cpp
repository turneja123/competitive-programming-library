//https://atcoder.jp/contests/abc380/tasks/abc380_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    string s;
    cin >> s;
    int q, n = s.size();
    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        long long m = (k - 1) / n + 1;
        int ct = 0;
        while (m % 2 == 0) {
            ct++;
            m /= 2;
        }
        int f = (__builtin_popcountll(m) + 1 + ct) % 2;
        char c = s[(k - 1) % n];
        if (f) {
            if (isupper(c)) {
                c = tolower(c);
            } else {
                c = toupper(c);
            }
        }
        cout << c << " ";
    }
    return 0;
}
