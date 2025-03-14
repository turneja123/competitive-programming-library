//https://atcoder.jp/contests/abc351/tasks/abc351_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> xe, ye, xo, yo;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if ((x + y) % 2 == 0) {
            xe.push_back(x + y);
            ye.push_back(x - y);
        } else {
            xo.push_back(x + y);
            yo.push_back(x - y);
        }
    }
    sort(xe.begin(), xe.end());
    sort(ye.begin(), ye.end());
    sort(xo.begin(), xo.end());
    sort(yo.begin(), yo.end());
    long long ans = 0;
    long long sum = 0;
    for (int i = 0; i < xe.size(); i++) {
        ans += (long long)xe[i] * i - sum;
        sum += xe[i];
    }
    sum = 0;
    for (int i = 0; i < ye.size(); i++) {
        ans += (long long)ye[i] * i - sum;
        sum += ye[i];
    }
    sum = 0;
    for (int i = 0; i < xo.size(); i++) {
        ans += (long long)xo[i] * i - sum;
        sum += xo[i];
    }
    sum = 0;
    for (int i = 0; i < yo.size(); i++) {
        ans += (long long)yo[i] * i - sum;
        sum += yo[i];
    }
    cout << ans / 2;
    return 0;
}
