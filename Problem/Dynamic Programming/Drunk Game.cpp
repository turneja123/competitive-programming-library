//https://www.spoj.com/problems/DRUNK/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

long double a[N];
long double b[N];

int c[3];

int main() {
    IOS;
    cout << fixed;
    cout << showpoint;
    cout << setprecision(4);
    int t;
    cin >> t;
    while (t--) {
        int n; bool ba, bb;
        cin >> n >> c[0] >> c[1] >> c[2] >> ba >> bb;
        for (int i = 1; i <= n; i++) {
            long double mxa = 0, mna = 1, mxb = 0, mnb = 1;
            for (int j = 1; j <= 4 && j * j <= i; j++) {
                long double suma = 0, sumb = 0, tot = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    int x = j * j + dx;
                    if (x > 0 && x <= i) {
                        suma += c[dx + 1] * (1 - b[i - x]);
                        sumb += c[dx + 1] * (1 - a[i - x]);
                        tot += c[dx + 1];
                    }
                }
                mxa = max(mxa, suma / tot);
                mna = min(mna, suma / tot);
                mxb = max(mxb, sumb / tot);
                mnb = min(mnb, sumb / tot);
            }
            ba ? a[i] = mxa : a[i] = mna;
            bb ? b[i] = mxb : b[i] = mnb;
        }
        bb ? cout << 1 - a[n] << endl : cout << a[n] << endl;
    }

    return 0;
}
