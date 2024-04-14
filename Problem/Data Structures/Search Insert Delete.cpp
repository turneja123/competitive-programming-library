//https://www.spoj.com/problems/SID/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

map<int, vector<int>> mp;
map<int, int> ind;

int j = 0;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ind[a] = 0;
        mp[a].push_back(j++);
    }
    for (int i = 0; i < m; i++) {
        char c; int a;
        cin >> c >> a;
        if (c == 'S') {
            if (ind[a] >= mp[a].size()) {
                cout << "NONE" << endl;
            } else {
                cout << mp[a][ind[a]] + 1 << endl;
            }
        }
        if (c == 'I') {
            mp[a].push_back(j++);
            cout << j << endl;
        }
        if (c == 'D') {
            if (ind[a] >= mp[a].size()) {
                cout << "NONE" << endl;
            } else {
                cout << mp[a][ind[a]] + 1 << endl;
                ind[a]++;
            }
        }
    }

    return 0;
}
