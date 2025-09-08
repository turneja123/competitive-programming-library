//https://leetcode.com/problems/sum-of-beautiful-subsequences/description/
using ll = long long;
const int N = 1e5 + 5;
const ll M = 1e9 + 7;
vector<int> divs[N];
vector<int> pos[N];
int mx[N];
ll dp[N];
bool seen[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
            t[i] = (t[i] + M) % M;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
            ans = (ans + M) % M;
        }
        return ans;
    }
    long long query(int l, int r) {
        return (query(r) - query(l - 1) + M) % M;
    }
};

class Solution {
public:
    void precalc() {
        for (int i = 1; i < N; i++) {
            for (int j = i; j < N; j += i) {
                divs[j].push_back(i);
            }
        }
    }

    int totalBeauty(vector<int>& a) {
        if (divs[1].empty()) {
            precalc();
        }
        vector<int> go;
        int n = a.size(), lim = 0;
        for (int i = 0; i < n; i++) {
            lim = max(lim, a[i]);
            for (int j : divs[a[i]]) {
                pos[j].push_back(a[i] / j);
                mx[j] = max(mx[j], a[i] / j);
                if (!seen[j]) {
                    seen[j] = true;
                    go.push_back(j);
                }
            }
        }
        for (int d : go) {
            int m = pos[d].size();
            BIT bit(mx[d] + 1);
            vector<int> is(m, 0);
            for (int i = 0; i < pos[d].size(); i++) {
                int x = pos[d][i];
                is[i] = 1;
                if (x != 1) {
                    is[i] = (is[i] + bit.query(1, x - 1)) % M;
                }
                dp[d] = (dp[d] + is[i]) % M;
                bit.upd(x, is[i]);
            }
        }
        sort(go.begin(), go.end());
        reverse(go.begin(), go.end());
        ll ans = 0;
        for (int i : go) {
            for (int j = i * 2; j <= lim; j += i) {
                dp[i] = (dp[i] - dp[j] + M) % M;
            }
            ans = (ans + dp[i] * i) % M;
        }
        for (int i : go) {
            pos[i].clear();
            dp[i] = 0;
            seen[i] = false;
            mx[i] = 0;
        }
        return ans;
    }
};
