//https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/description/
class Solution {
public:
    int K = 16;
    int N = 1 << K;

    void t(vector<long long> &a, int sgn) {
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                int c = j & (1 << i);
                if (c) {
                    a[j ^ (1 << i)] += a[j] * sgn;
                }
            }
        }
    }

    int countTriplets(vector<int>& nums) {
        vector<long long> a(N, 0);
        for (int x : nums) {
            a[x]++;
        }
        t(a, 1);
        vector<long long> doubles(N, 0);
        for (int i = 0; i < N; i++) {
            doubles[i] = a[i] * a[i];
        }
        t(doubles, -1);
        t(doubles, 1);
        vector<long long> triples(N, 0);
        for (int i = 0; i < N; i++) {
            triples[i] = a[i] * doubles[i];
        }
        t(triples, -1);
        return triples[0];
    }
};
