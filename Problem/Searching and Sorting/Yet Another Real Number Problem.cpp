//https://codeforces.com/contest/2035/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long a[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.second > b.second) {
        if (a.second - 30 > b.second) {
            return true;
        }
        if ((long long)a.first * modPow(2, a.second - b.second) >= b.first) {
            return true;
        }
        return false;
    }
    if (b.second - 30 > a.second) {
        return false;
    }
    if ((long long)b.first * modPow(2, b.second - a.second) > a.first) {
        return false;
    }
    return true;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long sum = 0;
        stack<pair<int, int>> s;
        for (int i = 0; i < n; i++) {
            int e = 0;
            while (a[i] % 2 == 0) {
                a[i] /= 2;
                e++;
            }
            while (s.size()) {
                if (comp(make_pair(a[i], e + s.top().second), s.top())) {
                    e += s.top().second;
                    sum = (sum - s.top().first * modPow(2, s.top().second) % M + M) % M;
                    sum += s.top().first;
                    s.pop();
                } else {
                    break;
                }
            }
            sum = (sum + a[i] * modPow(2, e)) % M;
            if (e > 0) {
                s.push(make_pair(a[i], e));
            }
            cout << sum << " ";
        }
        cout << endl;

    }
    return 0;
}

