//https://basecamp.eolymp.com/en/problems/11856
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int freq[N];
int pref[N];

vector<int> freq_k[N];
vector<int> pref_k[N];
vector<long long> sum_k[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    pref[0] = freq[0];
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i - 1] + freq[i];
    }
    for (int k = 1; k < N; k++) {
        int f = pref[k - 1];
        freq_k[k].push_back(f);
        for (int i = 2; i < N; i++) {
            int f = pref[min(N - 1, k * i - 1)] - pref[k * (i - 1) - 1];
            freq_k[k].push_back(f);
            if (k * i - 1 >= N) {
                break;
            }

        }
        pref_k[k].push_back(freq_k[k][0]);
        sum_k[k].push_back(0);
        for (int i = 1; i < freq_k[k].size(); i++) {
            pref_k[k].push_back(pref_k[k][i - 1] + freq_k[k][i]);
            sum_k[k].push_back(sum_k[k][i - 1] + (long long)freq_k[k][i] * i);
        }
    }
    for (int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        x /= k;
        long long ans = min((ll)n, sum_k[k].back() / x);
        int R = min(x - 1, (int)pref_k[k].size() - 1);
        long long have = n - pref_k[k][R];
        if (have >= ans) {
            cout << ans << " " << 0 << endl;
            continue;
        }
        int l = 0, r = R, spl = R;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (pref_k[k][mid] > pref_k[k][R] - (ans - have)) {
                spl = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        long long moves = (ans - have) * x - ((sum_k[k][R] - sum_k[k][spl]) + (ll)(freq_k[k][spl] - (pref_k[k][R] - (ans - have) - (spl ? pref_k[k][spl - 1] : 0))) * (ll)spl);
        cout << ans << " " << moves << endl;

    }
    return 0;
}
