//https://judge.beecrowd.com/en/problems/view/2580
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 30;
const int W = 150;


ld dp[N * W];
ld dp_nx[N * W];
ld prob[N * W];
ld prob_nx[N * W];

struct Item {
    int a;
    ld p;
    vector<ld> probs;
    Item() {
    }
    bool operator < (const Item &x) const { return (ld)a * (1.0 - p) > (ld)x.a * (1.0 - x.p);}
};

Item items[N];


int main() {
    IOS;
    cout << fixed;
    cout << setprecision(4);
    int n, w;
    cin >> n >> w;
    w = min(w, N * W - 1);
    for (int i = 0; i < n; i++) {
        string s; int m;
        cin >> s >> m >> items[i].a >> items[i].p;
        items[i].probs.resize(m);
        for (int j = 0; j < m; j++) {
            cin >> items[i].probs[j];
        }
        int z = 0;
        while (items[i].probs.size() < W) {
            items[i].probs.push_back(items[i].probs[z % m]);
            z++;
        }
        while (items[i].probs.size() > W) {
            items[i].probs.pop_back();
        }
    }
    sort(items, items + n);
    prob[0] = 1.0;
    for (int i = 0; i < n; i++) {
        ld alive = 1.0;
        for (int j = 1; j <= W; j++) {
            for (int k = w; k - j >= 0; k--) {
                dp_nx[k] += (dp[k - j] + prob[k - j] * (ld)items[i].a) * alive * (1.0 - items[i].p);
                dp_nx[k] += dp[k - j] * alive * items[i].p * items[i].probs[j - 1];
                if (k == w) {
                    dp_nx[k] += dp[k - j] * alive * items[i].p * (1.0 - items[i].probs[j - 1]);
                }
                prob_nx[k] += prob[k - j] * alive * (1.0 - items[i].p + items[i].p * items[i].probs[j - 1]);
            }
            alive *= items[i].p * (1.0 - items[i].probs[j - 1]);
        }
        for (int k = 0; k <= w; k++) {
            if (k != w) {
                dp[k] = 0;
                prob[k] = 0;
            }
            dp[k] += dp_nx[k];
            prob[k] += prob_nx[k];
            dp_nx[k] = 0;
            prob_nx[k] = 0;
        }
    }
    ld ans = 0;
    for (int k = 0; k <= w; k++) {
        ans += dp[k];
    }
    cout << ans << endl;

    return 0;
}
