//https://leetcode.com/problems/super-pow/
class Solution {
public:
    int M = 1337;
    long long modPow(long long a, long long y, long long m) {
        long long res = 1;
        while(y > 0) {
            if(y % 2 != 0) {
                res = (res * a) % m;
            }
            y /= 2;
            a = (a * a) % m;
        }
        return res;
    }

    int phi(int n) {
        int res = n;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                res -= res / i;
            }
        }
        if (n > 1) {
            res -= res / n;
        }
        return res;
    }

    int superPow(int a, vector<int>& b) {
        int p = phi(M);
        int e = 0;
        for (int i = 0; i < b.size(); i++) {
            e = (e * 10 + b[i]) % p;
        }
        return modPow(a, e + p, M);
    }
};
