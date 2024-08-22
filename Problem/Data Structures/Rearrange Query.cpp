//https://atcoder.jp/contests/abc367/tasks/abc367_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;
const long long P = 26, Q = 53;

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

pair<long long, long long> prefa[N];
pair<long long, long long> prefb[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    pair<long long, long long> prod = make_pair(1, 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        prod.first = prod.first * (a + P) % M;
        prod.second = prod.second * (a + Q) % M;
        prefa[i] = prod;
    }
    prod = make_pair(1, 1);
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        prod.first = prod.first * (b + P) % M;
        prod.second = prod.second * (b + Q) % M;
        prefb[i] = prod;
    }
    for (int i = 0; i < q; i++) {
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;
        la--, ra--, lb--, rb--;
        pair<long long, long long> ha = prefa[ra];
        if (la != 0) {
            ha.first = ha.first * modInverse(prefa[la - 1].first) % M;
            ha.second = ha.second * modInverse(prefa[la - 1].second) % M;
        }
        pair<long long, long long> hb = prefb[rb];
        if (lb != 0) {
            hb.first = hb.first * modInverse(prefb[lb - 1].first) % M;
            hb.second = hb.second * modInverse(prefb[lb - 1].second) % M;
        }
        if (ha.first == hb.first && ha.second == hb.second) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
