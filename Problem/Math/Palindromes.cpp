//https://www.spoj.com/problems/CODESPTF/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;
const ld eps = 1e-9;

int Gauss(vector<vector<ld>> a, vector<ld> &ans) {
    int n = (int)a.size(), m = (int)a[0].size() - 1;
    vector<int> pos(m, -1);
    ld det = 1; int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int mx = row;
        for (int i = row; i < n; i++) {
            if(fabs(a[i][col]) > fabs(a[mx][col])) {
                mx = i;
            }
        }
        if (fabs(a[mx][col]) < eps) {
            det = 0;
            continue;
        }
        for (int i = col; i <= m; i++) {
            swap(a[row][i], a[mx][i]);
        }
        if (row != mx) {
            det = -det;
        }
        det *= a[row][col];
        pos[col] = row;
        for (int i = 0; i < n; i++) {
            if (i != row && fabs(a[i][col]) > eps) {
                ld c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        ++row; ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) {
        if (pos[i] != -1) {
            ans[i] = a[pos[i]][m] / a[pos[i]][i];
        }
    }
    for (int i = 0; i < n; i++) {
        ld sum = 0;
        for (int j = 0; j < m; j++) {
            sum += ans[j] * a[i][j];
            if (fabs(sum - a[i][m]) > eps) {
                return -1; //no solution
            }
        }
    }
    for (int i = 0; i < m; i++) {
        if (pos[i] == -1) {
            return 2; //infinite solutions
        }
    }
    return 1; //unique solution
}

const int N = 100;

map<multiset<int>, int> partitions;
map<vector<int>, int> id[N];
vector<string> val[N];
vector<ld> ans[N];
int m = 0, e = 0;

vector<int> extract(string s) {
    int n = s.size();
    vector<int> seen(26, 0);
    vector<int> S(n);
    vector<int> id(26, 0);
    int j = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        if (!seen[x]) {
            id[x] = j++;
            seen[x] = true;
        }
        S[i] = id[x];
    }
    return S;
}

void dfs(string &s) {
    vector<int> S = extract(s);
    if (id[e].find(S) != id[e].end()) {
        return;
    }
    int n = s.size();
    val[e].push_back(s);
    id[e][S] = m++;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(s[i], s[j]);
            dfs(s);
            swap(s[i], s[j]);
        }
    }
}

bool is_pal(string &s) {
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(4);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        multiset<int> freqs;
        vector<int> f(26, 0);
        vector<int> S = extract(s);
        for (int x : S) {
            f[x]++;
        }
        for (int i = 0; i < 26 && f[i]; i++) {
            freqs.insert(f[i]);
        }
        if (partitions.find(freqs) == partitions.end()) {
            partitions[freqs] = partitions.size();
            m = 0;
            e = partitions[freqs];
            dfs(s);
            vector<vector<ld>> v(m, vector<ld>(m + 1, 0));
            for (int c = 0; c < m; c++) {
                string s = val[e][c];
                if (is_pal(s)) {
                    v[c][c] = 1.0;
                } else {
                    int all = n * (n - 1) / 2;
                    for (int i = 0; i < n; i++) {
                        for (int j = i + 1; j < n; j++) {
                            swap(s[i], s[j]);
                            vector<int> S = extract(s);
                            int u = id[e][S];
                            v[c][u] += 1.0 / (ld)all;
                            swap(s[i], s[j]);
                        }
                    }
                    v[c][c] -= 1.0;
                    v[c][m] -= 1.0;
                }
            }
            vector<ld> an;
            Gauss(v, an);
            ans[e] = an;
        }
        e = partitions[freqs];
        cout << ans[e][id[e][S]] << endl;
    }
    return 0;
}
