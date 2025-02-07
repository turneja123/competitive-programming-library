//https://leetcode.com/contest/weekly-contest-333/problems/find-the-string-with-lcp/
const int K = 10;
struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU() {}

    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int dsu_find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = dsu_find(parent[a]);
    }

    void dsu_unite(int a, int b) {
        if (sz[b] > sz[a]) {
            swap(a, b);
        }
        sz[a] += sz[b];
        parent[b] = a;
    }
};


class Solution {
public:
    DSU dsu[K];

    void calc(int a, int b, int k) {
        int A = dsu[k].dsu_find(a), B = dsu[k].dsu_find(b);
        if (A != B) {
            dsu[k].dsu_unite(A, B);
            if (k != 0) {
                k--;
                calc(a, b, k);
                calc(a + (1 << k), b + (1 << k), k);
            }
        }
        return;
    }

    void query(int d, int a, int b) {
        if (d == 0 || a == b) {
            return;
        }
        int k = 31 - __builtin_clz(d);
        calc(a, b, k);
        calc(a + d - (1 << k), b + d - (1 << k), k);
    }

    string findTheString(vector<vector<int>>& lcp) {
        string sent = "";
        int n = lcp.size();
        vector<int> ban[n];
        for (int i = 0; i < K; i++) {
            dsu[i] = DSU(n);
        }
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (i == j && lcp[i][j] != n - i) {
                    return sent;
                }
                if (lcp[i][j] != lcp[j][i]) {
                    return sent;
                }
                if (j + lcp[i][j] > n) {
                    return sent;
                }
                query(lcp[i][j], i, j);
                if (j + lcp[i][j] != n) {
                    ban[i + lcp[i][j]].push_back(j + lcp[i][j]);
                    ban[j + lcp[i][j]].push_back(i + lcp[i][j]);
                }
            }
        }
        string ans = "";
        for (int i = 0; i < n; i++) {
            ans += "A";
        }
        vector<int> color(n, -1);
        for (int i = 0; i < n; i++) {
            int a = dsu[0].dsu_find(i);
            if (color[a] != -1) {
                ans[i] = 'a' + color[a];
                continue;
            }
            set<int> st;
            for (int j = 0; j < 26; j++) {
                st.insert(j);
            }
            for (int j : ban[i]) {
                int b = dsu[0].dsu_find(j);
                if (color[b] != -1) {
                    auto it = st.find(color[b]);
                    if (it != st.end()) {
                        st.erase(it);
                    }
                }
            }
            if (st.empty()) {
                return sent;
            }
            color[a] = *st.begin();
            ans[i] = 'a' + color[a];
        }
        for (int i = 0; i < n; i++) {
            for (int j : ban[i]) {
                if (dsu[0].dsu_find(i) == dsu[0].dsu_find(j)) {
                    return sent;
                }
            }
        }
        return ans;
    }
};
