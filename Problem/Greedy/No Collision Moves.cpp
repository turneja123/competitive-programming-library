//https://atcoder.jp/contests/arc205/tasks/arc205_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int s[N];
int t[N];

bool comp1(int a, int b) {
    return s[a] < s[b];
}

bool comp2(int a, int b) {
    return s[a] > s[b];
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> vs, vt;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
        vs.push_back({s[i], i});
        vt.push_back({t[i], i});
    }
    sort(vs.begin(), vs.end());
    sort(vt.begin(), vt.end());
    for (int i = 0; i < n; i++) {
        if (vs[i].second != vt[i].second) {
            cout << "No";
            return 0;
        }
    }
    vector<int> lf, rt;
    for (int i = 0; i < n; i++) {
        if (s[i] > t[i]) {
            lf.push_back(i);
        } else {
            rt.push_back(i);
        }
    }
    sort(lf.begin(), lf.end(), comp1);
    sort(rt.begin(), rt.end(), comp2);
    cout << "Yes" << endl;
    for (int i : lf) {
        cout << i + 1 << " ";
    }
    for (int i : rt) {
        cout << i + 1 << " ";

    }
    return 0;
}
