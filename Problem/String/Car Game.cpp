//https://www.spoj.com/problems/UCBINTB/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;
const int N = 5005;

string s[N];
bool b1[N][26];
bool b2[N][26][26];
bool b3[N][26][26][26];
int first[26][26][26];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int x = 0; x < 26; x++) {
        for (int y = 0; y < 26; y++) {
            for (int z = 0; z < 26; z++) {
                first[x][y][z] = -1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < s[i].size(); j++) {
            for (int x = 0; x < 26; x++) {
                for (int y = 0; y < 26; y++) {
                    if (b2[i][x][y]) {
                        b3[i][x][y][s[i][j] - 'a'] = true;
                    }
                }
            }
            for (int x = 0; x < 26; x++) {
                if (b1[i][x]) {
                    b2[i][x][s[i][j] - 'a'] = true;
                }
            }
            b1[i][s[i][j] - 'a'] = true;
        }
        for (int x = 0; x < 26; x++) {
            for (int y = 0; y < 26; y++) {
                for (int z = 0; z < 26; z++) {
                    if (first[x][y][z] == -1 && b3[i][x][y][z]) {
                        first[x][y][z] = i;
                    }
                }
            }
        }
    }
    for (int i = 0; i < m; i++) {
        string a;
        cin >> a;
        int ans = first[a[0] - 'A'][a[1] - 'A'][a[2] - 'A'];
        if (ans == -1) {
            cout << "No valid word" << endl;
        } else {
            cout << s[ans] << endl;
        }
    }

    return 0;
}
