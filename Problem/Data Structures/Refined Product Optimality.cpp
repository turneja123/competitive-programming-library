//https://codeforces.com/contest/2053/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const long long M = 998244353;

int a[N];
int b[N];

int a_sort[N];
int b_sort[N];

tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ta, tb;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int, int, custom_hash> cta, ctb;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cta[a[i]]++;
            ta.insert(make_pair(a[i], i));
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            ctb[b[i]]++;
            tb.insert(make_pair(b[i], i));
        }
        long long prod = 1;
        auto ita = ta.begin(), itb = tb.begin();
        while (ita != ta.end()) {
            prod = prod * min(ita->first, itb->first) % M;
            ita++, itb++;
        }
        cout << prod << " ";

        for (int i = 0; i < q; i++) {
            int o, x;
            cin >> o >> x;
            x--;
            if (o == 1) {
                int ct = cta[a[x]];
                int pos = ta.order_of_key(make_pair(a[x], -1));
                int y = tb.find_by_order(pos + ct - 1)->first;
                prod = prod * modPow(min(a[x], y), M - 2) % M;
                prod = prod * min(a[x] + 1, y) % M;
                cta[a[x]]--;
                cta[a[x] + 1]++;
                ta.erase(ta.find(make_pair(a[x], x)));
                a[x]++;
                ta.insert(make_pair(a[x], x));
            } else {
                int ct = ctb[b[x]];
                int pos = tb.order_of_key(make_pair(b[x], -1));
                int y = ta.find_by_order(pos + ct - 1)->first;
                prod = prod * modPow(min(b[x], y), M - 2) % M;
                prod = prod * min(b[x] + 1, y) % M;
                ctb[b[x]]--;
                ctb[b[x] + 1]++;
                tb.erase(tb.find(make_pair(b[x], x)));
                b[x]++;
                tb.insert(make_pair(b[x], x));
            }
            cout << prod << " ";
        }
        cout << endl;
        cta.clear(), ctb.clear();
        ta.clear(), tb.clear();

    }
    return 0;
}
