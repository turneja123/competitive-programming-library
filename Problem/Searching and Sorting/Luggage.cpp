//https://judge.beecrowd.com/en/problems/view/3235
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1005;

double a[N];

int main() {
    IOS;
    cout << setprecision(12);
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    vector<double> v{0.1, 10};
    vector<vector<double>> ans{v};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<vector<double>> add;
            int k = ceil((0.1 * (a[j] - a[i]) - d + 1) / d);
            v[0] = (a[j] - a[i]) / (d * k + d - 1), v[1] = (a[j] - a[i]) / (d * k + 1);
            while (v[1] >= 0.1) {
                add.push_back(v);
                k++;
                v[0] = (a[j] - a[i]) / (d * k + d - 1), v[1] = (a[j] - a[i]) / (d * k + 1);
            }
            reverse(add.begin(), add.end());
            vector<vector<double>> temp;
            int ip = 0, jp = 0;
            while (ip < ans.size() && jp < add.size()) {
                v[0] = max(ans[ip][0], add[jp][0]), v[1] = min(ans[ip][1], add[jp][1]);
                if (v[0] <= v[1]) {
                    temp.push_back(v);
                }
                if (ans[ip][1] < add[jp][1]) {
                    ip++;
                } else {
                    jp++;
                }
            }
            ans = temp;
            if (ans.size() == 0) {
                cout << "no fika" << endl;
                return 0;
            }
        }
    }
    cout << ans[ans.size() - 1][1] << endl;
    return 0;
}
