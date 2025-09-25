//https://codeforces.com/contest/2147/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

bool used[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> pos;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                pos.push_back(i);
            }
        }
        string ans = "YES";
        for (int i = 0; i < pos.size();) {
            int j = pos[i];
            bool bad = false;
            if ((j != 0 && s[j - 1] == '1') && (j != n - 1 && s[j + 1] == '1')) {
                bad = true;
            }
            if (bad) {
                if (j != 1 && s[j - 2] == '0' && !used[j - 2]) {
                    i++;
                } else if (j != n - 2 && s[j + 2] == '0') {
                    used[j + 2] = true;
                    i += 2;
                } else {
                    ans = "NO";
                    break;
                }
            } else {
                i++;

            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            used[i] = false;
        }
    }
    return 0;
}
