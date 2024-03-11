//solution for https://www.codechef.com/MAY21C/problems/MODEQ
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

vector<int> v[N];
vector<int> pos;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        pos.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int md = m % i;
            v[md].push_back(i);
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            int md = m % i;
            for (int j = md; j <= n; j += i) {
                while (pos[j] < v[j].size() && v[j][pos[j]] <= i) {
                    pos[j]++;
                }
                ans += v[j].size() - pos[j];
            }
        }
        cout << ans << endl;
        pos.clear();
        for (int i = 0; i < n; i++) {
            v[i].clear();
        }
    }
    return 0;
}
