//https://leetcode.com/contest/biweekly-contest-159/problems/kth-smallest-path-xor-sum/description/
const int N = 5e4 + 5;
int SQ = 220;

vector<int> adj[N];
int a[N];
int sz[N];
int pos[N];
int actual[N];
int freq[N];
int freq_block[N];
int freq_once[N];

int idx = 0;
tuple<int, int, int, int, int64_t> queries[N];

class Solution {
public:
    void dfs(int u, int p, vector<int> &vals) {
        sz[u] = 1;
        pos[u] = idx;
        a[idx++] = vals[u];
        for (int v : adj[u]) {
            if (v != p) {
                vals[v] ^= vals[u];
                dfs(v, u, vals);
                sz[u] += sz[v];
            }
        }
    }
    inline int64_t hilbert(int x, int y, int pow, int rot) {
    	if (pow == 0) {
    		return 0;
    	}
    	int hpow = 1 << (pow-1);
    	int seg = (x < hpow) ? (
    		(y < hpow) ? 0 : 3
    	) : (
    		(y < hpow) ? 1 : 2
    	);
    	seg = (seg + rot) & 3;
    	const int rotateDelta[4] = {3, 0, 0, 1};
    	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    	int nrot = (rot + rotateDelta[seg]) & 3;
    	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
    	int64_t ans = seg * subSquareSize;
    	int64_t add = hilbert(nx, ny, pow-1, nrot);
    	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    	return ans;
    }

    static bool comp(tuple<int, int, int, int, int64_t> a, tuple<int, int, int, int, int64_t> b) {
        int64_t h1 = get<4>(a);
        int64_t h2 = get<4>(b);
        return h1 < h2;
    }

    int ct = 0;

    void add(int x) {
        freq[x]++;
        if (freq[x] == 1) {
            ct++;
            freq_block[x / SQ]++;
            freq_once[x] = 1;
        }
    }

    void rem(int x) {
        freq[x]--;
        if (freq[x] == 0) {
            ct--;
            freq_block[x / SQ]--;
            freq_once[x] = 0;
        }
    }

    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& que) {
        int n = par.size();

        for (int i = 1; i < n; i++) {
            adj[i].push_back(par[i]);
            adj[par[i]].push_back(i);
        }
        dfs(0, 0, vals);
        vector<pair<int, int>> compr;
        for (int i = 0; i < n; i++) {
            compr.push_back({a[i], i});
        }
        sort(compr.begin(), compr.end());
        int m = -1, last = -1;
        for (auto [x, i] : compr) {
            if (x != last) {
                m++;
                actual[m] = x;
                last = x;
            }
            a[i] = m;
        }
        m++;
        SQ = sqrt(m);

        int q = que.size();
        for (int i = 0; i < q; i++) {
            int u = que[i][0], k = que[i][1];
            int l = pos[u], r = pos[u] + sz[u] - 1;
            queries[i] = {l, r, k, i, hilbert(l, r, 21, 0)};
        }
        sort(queries, queries + q, comp);
        vector<int> ans(q, 0);

        int l = 0;
        int r = -1;
        for (int i = 0; i < q; i++) {
            auto [lq, rq, k, cur, _] = queries[i];
            while (r < rq) {
                r++;
                add(a[r]);
            }
            while (l > lq) {
                l--;
                add(a[l]);
            }
            while (r > rq) {
                rem(a[r]);
                r--;
            }
            while (l < lq) {
                rem(a[l]);
                l++;
            }
            if (ct < k) {
                ans[cur] = -1;
                continue;
            }
            int j = 0;
            for (; j < m; j++) {
                if (freq_block[j] >= k) {
                    break;
                }
                k -= freq_block[j];
            }
            j = j * SQ;
            while (k) {
                k -= freq_once[j];
                if (k == 0) {
                    break;
                }
                j++;
            }
            ans[cur] = actual[j];
        }

        ct = 0;
        idx = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            freq[i] = 0;
            freq_block[i] = 0;
            freq_once[i] = 0;
        }
        return ans;
    }
};
