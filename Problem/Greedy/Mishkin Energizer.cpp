//https://codeforces.com/contest/2092/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int need[3];
int other[3][3];
int can[3];
char c[3];
map<char, int> mp;
vector<int> ans;

int main() {
    IOS;
    c[0] = 'L';
    c[1] = 'I';
    c[2] = 'T';
    mp['L'] = 0;
    mp['I'] = 1;
    mp['T'] = 2;
    other[0][1] = 2;
    other[0][2] = 1;
    other[1][2] = 0;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        need[0] = n, need[1] = n, need[2] = n;
        for (int i = 0; i < n; i++) {
            need[mp[s[i]]]--;
        }
        if (need[0] == 0 || need[1] == 0 || need[2] == 0) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 0; i < n - 1; i++) {
            int x = mp[s[i]], y = mp[s[i + 1]];
            if (x != y) {
                ans.push_back(i + 1);
                int o = other[min(x, y)][max(x, y)];
                need[o]--;
                s.insert(s.begin() + i + 1, c[o]);
                can[x] = true;
                can[y] = true;
                break;
            }
        }
        while (s.size() < 3 * n) {
            int mx = 0;
            int nx = -1;
            for (int i = 0; i < 3; i++) {
                if (can[i] && need[i] > mx) {
                    mx = need[i];
                    nx = i;
                }
            }
            int m = s.size();
            for (int i = 0; i < m - 2; i++) {
                if (s[i] != s[i + 1] && s[i] != s[i + 2] && s[i + 1] != s[i + 2] && s[i + 1] != c[nx]) {
                    if (s[i] != c[nx]) {
                        ans.push_back(i + 1);
                        s.insert(s.begin() + i + 1, c[nx]);
                    } else {
                        ans.push_back(i + 2);
                        s.insert(s.begin() + i + 2, c[nx]);
                    }

                    break;
                }
            }

            need[nx]--;
            can[0] = false, can[1] = false, can[2] = false;
            for (int i = 0; i < 3; i++) {
                if (i != nx) {
                    can[i] = true;
                }
            }

        }
        can[0] = false, can[1] = false, can[2] = false;
        cout << ans.size() << endl;
        for (int x : ans) {
            cout << x << endl;
        }
        ans.clear();
    }

    return 0;
}
