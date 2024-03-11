//solution for https://cses.fi/problemset/task/1087/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

string s;
string sol = "";
vector <int> pos[4];

char c[4] = {'A', 'C', 'G', 'T'};
int p[4];

int main() {
    IOS;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (s[i] == c[j]) {
                pos[j].push_back(i);
            }
        }
    }
    while (1) {
        int mx = 0;
        for (int i = 0; i < 4; i++) {
            mx = max(mx, pos[i][p[i]]);
        }
        sol += s[mx];
        for (int i = 0; i < 4; i++) {
            int it = upper_bound(pos[i].begin(), pos[i].end(), mx) - pos[i].begin();
            if (it == pos[i].size()) {
                sol += c[i];
                goto endwhile;
            }
            p[i] = it;
        }
    }
    endwhile: cout << sol;

}
