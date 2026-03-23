//https://atcoder.jp/contests/arc216/tasks/arc216_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 20;
const long long P = 1e9 + 7;
const long long Q = 998244353;


ll pw_p[N], pw_q[N];


int table_mx[K][N];
int mx[K][N];
int a[N];

ll PP[N], QQ[N];



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

gp_hash_table<ll, vector<int>, custom_hash> pos;


void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mx[0][i] = a[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mx[k - 1][i] > table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int b;
    if (table_mx[k][l] > table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }

    return b;
}

long long calc(int l, int r) {
    if (l >= r) {
        return l == r;
    }
    int mid = query(l, r);
    long long ans = 0;
    if (mid - l + 1 <= r - mid + 1) {

        for (int j = a[mid]; j <= a[mid] + K; j++) {

            for (int i = l; i <= mid; i++) {
                ll p_our = (i == 0 ? 0 : PP[i - 1]);
                ll q_our = (i == 0 ? 0 : QQ[i - 1]);

                ll p_need = (pw_p[j] + p_our + P) % P;
                ll q_need = (pw_q[j] + q_our + Q) % Q;
                auto it = pos.find(p_need + (q_need << 32));
                if (it != pos.end()) {
                    ans += upper_bound((it->second).begin(), (it->second).end(), r + 1) - lower_bound((it->second).begin(), (it->second).end(), mid + 1);
                }
            }
        }
    } else {
        for (int j = a[mid]; j <= a[mid] + K; j++) {
            for (int i = mid; i <= r; i++) {
                ll p_our = PP[i];
                ll q_our = QQ[i];

                ll p_need = (p_our - pw_p[j] + P) % P;
                ll q_need = (q_our - pw_q[j] + Q) % Q;
                auto it = pos.find(p_need + (q_need << 32));
                if (it != pos.end()) {
                    ans += upper_bound((it->second).begin(), (it->second).end(), mid) - lower_bound((it->second).begin(), (it->second).end(), l);
                }
            }
        }
    }
    ans += calc(l, mid - 1) + calc(mid + 1, r);
    return ans;
}



int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * 2 % P;
        pw_q[i] = pw_q[i - 1] * 2 % Q;
    }

    int n;
    cin >> n;
    ll p = 0, q = 0;
    pos[p + (q << 32)].push_back(0);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        p = (p + pw_p[a[i]]) % P;
        q = (q + pw_q[a[i]]) % Q;
        pos[p + (q << 32)].push_back(i + 1);

        PP[i] = p;
        QQ[i] = q;
    }
    build(n);

    cout << calc(0, n - 1);

    return 0;
}
