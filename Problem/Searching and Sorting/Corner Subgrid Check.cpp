//https://cses.fi/problemset/task/3360
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

char c[N][N];
int a[N][N];

int freq[N];
vector<int> rows[N];
vector<int> vals[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }
    for (int t = 0; t < k; t++) {
        bool yes = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = c[i][j] == 'A' + t;
                if (a[i][j]) {
                    rows[j].push_back(i);
                    vals[i].push_back(j);
                }
            }
        }

        for (int j = 0; j < n && !yes; j++) {
            vector<int> restore;
            for (int i : rows[j]) {
                if (yes) {
                    break;
                }
                for (int x : vals[i]) {
                    if (yes) {
                        break;
                    }
                    freq[x]++;
                    if (freq[x] == 1) {
                        restore.push_back(x);
                    }
                    if (freq[x] > 1 && x != j) {
                        yes = true;
                    }
                }
            }
            for (int x : restore) {
                freq[x] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            rows[i].clear();
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
