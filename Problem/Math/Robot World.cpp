//solution for https://www.spoj.com/problems/ROBOWORLD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

pair<long long, long double> prayrng(string x) {
    long long _int = 0;
    long double _real = 0;
    int i = 0;
    while (i < x.size() && x[i] != '.') {
        _int *= (long long)10;
        _int += x[i] - '0';
        i++;
    }
    int dv = 10;
    while (i < x.size()) {
        if (x[i] == '.') {
            i++;
            continue;
        }
        long long num = x[i] - '0';
        _real += num / (long double)dv;
        dv *= 10;
        i++;
    }
    return {_int, _real};

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long x = 0, y = 0;
        long double realx = 0, realy = 0;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string a, b;
            cin >> a >> b;

            pair<long long, long double> sa = prayrng(a);
            pair<long long, long double> sb = prayrng(b);

            x += sa.first;
            y += sb.first;
            realx += sa.second;
            realy += sb.second;
        }

        x += (long long)(floor(realx));
        realx -= floor(realx);
        y += (long long)(floor(realy));
        realy -= floor(realy);

        string sx = to_string(realx);
        string sy = to_string(realy);

        for (int i = 2; i < 6; i++) {
            x *= (long long)10;
            x += (long long)(sx[i] - '0');
            y *= (long long)10;
            y += (long long)(sy[i] - '0');
        }


        long long gcd = __gcd(x, y);
        cout << "f(x) = " << y / gcd << "x, g(x) = " << x / gcd << "x" << endl;

    }
    return 0;
}
