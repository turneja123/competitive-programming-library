#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int ct[N];

int main() {
    IOS;
    ll a, b, s, k;
    cin >> a >> b >> s >> k;
    vector<ll> v;
    vector<ll> divs;
    for (int i = 1; i <= sqrt(k); i++) {
        if (k % i == 0) {
            divs.push_back(i);
            if (i * i != k) {
                divs.push_back(k / i);
            }
        }
    }
    for (ll i = a; i <= b; i++) {
        ll temp = i;
        ll sum = 0;
        while (temp > 0) {
            sum += temp % 10ll;
            temp /= 10ll;
        }
        if (sum == s) {
            v.push_back(i);
            for (int j = 0; j < divs.size(); j++) {
                if (i % divs[j] == 0) {
                    ct[divs[j]]++;
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ans += ct[k / __gcd(v[i], k)];
        for (int j = 0; j < divs.size(); j++) {
            if (v[i] % divs[j] == 0) {
                ct[divs[j]]--;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
