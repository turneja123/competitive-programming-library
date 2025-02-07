//https://codeforces.com/problemset/problem/632/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

bool comp(string a, string b) {
    string x = a + b, y = b + a;
    return x < y;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<string> a;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        a.push_back(s);
    }
    sort(a.begin(), a.end(), comp);
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
    return 0;
}
