//https://codeforces.com/contest/2056/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

string s[N];

bool comp(int a, int b) {
    if (a > b) {
        if (s[a][b] == '0') {
            return true;
        }
        return false;
    }
    if (s[a][b] == '1') {
        return true;
    }
    return false;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            v[i] = i;
        }
        sort(v.begin(), v.end(), comp);
        for (int i = 0; i < n; i++) {
            cout << v[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
