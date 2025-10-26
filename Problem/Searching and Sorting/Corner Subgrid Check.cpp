//https://cses.fi/problemset/task/3360/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int SQ = 200000;

char c[N][N];
int a[N][N];

int freq_all[26];
int freq[N];
int ct[N][N];
vector<int> vals[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
            ct[i][j] = -1;
            freq_all[c[i][j] - 'A']++;
        }
    }
    for (int t = 0; t < k; t++) {
        if (freq_all[t] > SQ) {
            cout << "YES" << endl;
            continue;
        }
        bool yes = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = c[i][j] == 'A' + t;
                if (a[i][j]) {
                    vals[i].push_back(j);
                }
            }
            for (int x = 0; x < vals[i].size() && !yes; x++) {
                for (int y = x + 1; y < vals[i].size() && !yes; y++) {
                    int l = vals[i][x], r = vals[i][y];
                    if (ct[l][r] == t) {
                        yes = 1;
                    }
                    ct[l][r] = t;

                }
            }
        }


        for (int i = 0; i < n; i++) {
            vals[i].clear();
        }
        if (yes) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }
    return 0;
}
