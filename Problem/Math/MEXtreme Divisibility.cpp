//https://www.codechef.com/problems/ONEDIF
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int freq[N];
int ct[N];

vector<int> divs[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= m; j += i) {
                ct[i] += freq[j];
                divs[j].push_back(i);
            }
        }
        set<int> need;
        for (int i = 1; i <= m + 1; i++) {
            if (ct[i] == 0) {
                need.insert(i);
            }
            if (need.size() > 25) {
                break;
            }
        }
        int ans = *need.begin();
        for (int i = 0; i < n; i++) {
            set<int> temp = need;
            for (int j : divs[a[i]]) {
                if (ct[j] == 1) {
                    need.insert(j);
                }
                if (need.size() > 50) {
                    break;
                }
            }
            long long prod = 1;
            while (prod <= m) {
                long long x = *need.begin();
                long long g = __gcd(prod, x);
                prod = prod * x / g;
                if (prod > m) {
                    break;
                } else {
                    need.erase(need.begin());
                }
            }
            ans = max(ans, *need.begin());
            need = temp;
        }
        cout << ans << endl;
        for (int i = 1; i <= m; i++) {
            freq[i] = 0;
            ct[i] = 0;
            divs[i].clear();
        }


    }
    return 0;
}
