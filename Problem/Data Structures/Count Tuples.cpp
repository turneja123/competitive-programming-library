//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/median-triplets-2-6c348ffa/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int freql[N];
int freqr[N];
tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> l, r;

void r_erase(int v){
    int rk = r.order_of_key(v);
    auto it = r.find_by_order(rk);
    r.erase(it);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            r.insert(a[i]);
            freqr[a[i]]++;
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            r_erase(a[i]);
            freqr[a[i]]--;
            ans += (long long)(freql[a[i]] + l.order_of_key(a[i])) * (long long)(r.size() - r.order_of_key(a[i]));
            ans += (long long)(l.size() - l.order_of_key(a[i])) * (long long)(r.order_of_key(a[i]) + freqr[a[i]]);
            ans -= (long long)(freql[a[i]]) * (long long)(freqr[a[i]]);
            freql[a[i]]++;
            l.insert(a[i]);

        }
        l.clear();
        for (int i = 0; i < n; i++) {
            freql[a[i]] = 0;
            a[i] = 0;
        }
        cout << ans << endl;
    }

    return 0;
}
