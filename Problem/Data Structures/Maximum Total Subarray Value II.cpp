//https://leetcode.com/problems/maximum-total-subarray-value-ii/description/
const int K = 17;
const int N = 1e5 + 5;
int table_mn[K][N];
int table_mx[K][N];
int a[N];
class Solution {
public:
    void build(int n) {
        for (int i = 1; i <= n; i++) {
            table_mn[0][i] = a[i - 1];
            table_mx[0][i] = a[i - 1];
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                if (table_mn[k - 1][i] < table_mn[k - 1][i + (1 << (k - 1))]) {
                    table_mn[k][i] = table_mn[k - 1][i];
                } else {
                    table_mn[k][i] = table_mn[k - 1][i + (1 << (k - 1))];
                }

                if (table_mx[k - 1][i] > table_mx[k - 1][i + (1 << (k - 1))]) {
                    table_mx[k][i] = table_mx[k - 1][i];
                } else {
                    table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                }
            }
        }
        return;
    }

    pair<int, int> query(int l, int r) {
        l++, r++;
        int k = 31 - __builtin_clz(r - l + 1);
        int a, b;
        if (table_mn[k][l] < table_mn[k][r - (1 << k) + 1]) {
            a = table_mn[k][l];
        } else {
            a = table_mn[k][r - (1 << k) + 1];
        }

        if (table_mx[k][l] > table_mx[k][r - (1 << k) + 1]) {
            b = table_mx[k][l];
        } else {
            b = table_mx[k][r - (1 << k) + 1];
        }

        return {a, b};
    }

    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            a[i] = nums[i];
        }
        build(n);
        auto [mn, mx] = query(0, n - 1);
        priority_queue<tuple<int, int, int>> pq;
        pq.push({mx - mn, 0, n - 1});
        int i = 0; long long ans = 0;
        set<pair<int, int>> seen;
        seen.insert({0, n - 1});
        while (i < k) {
            auto [s, l, r] = pq.top();
            pq.pop();
            ans += s;
            l++;
            if (l <= r && seen.find({l, r}) == seen.end()) {
                seen.insert({l, r});
                auto [mn, mx] = query(l, r);
                pq.push({mx - mn, l, r});
            }
            l--;
            r--;
            if (l <= r && seen.find({l, r}) == seen.end()) {
                seen.insert({l, r});
                auto [mn, mx] = query(l, r);
                pq.push({mx - mn, l, r});
            }
            i++;
        }
        return ans;
    }
};
