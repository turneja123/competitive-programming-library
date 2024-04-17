//https://www.spoj.com/problems/PALPRIM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

long long q[N];
pair<long long, int> queries[N];
vector<long long> ans = {2, 3, 5, 7, 11};

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};

__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries, queries + t);
    long long n = queries[t - 1].first;
    for (long long i = 1; i < N - 5; i++) {
        int y = i, c = 0, sum = 0;
        while (y > 0) {
            c = y % 10;
            sum += c;
            y /= 10;
        }
        if (c % 2 == 0 || c == 5) {
            continue;
        }
        for (int j = 0; j < 10; j++) {
            if ((2 * sum + j) % 3 == 0) {
                continue;
            }
            long long x = i * 10 + j, temp = i;
            while (temp > 0) {
                x = x * 10 + temp % 10;
                temp /= 10;
            }
            if (x % 7 == 0 || x % 11 == 0 || x % 13 == 0) {
                continue;
            }
            if (x > n) {
                break;
            }
            if (is_prime(x)) {
                ans.push_back(x);
            }
        }
    }
    int j = 0; long long mx = 2;
    for (int i = 0; i < ans.size(); i++) {
        while (j < t && ans[i] > queries[j].first) {
            q[queries[j].second] = mx;
            j++;
        }
        if (j == t) {
            break;
        }
        mx = ans[i];
    }
    while (j < t) {
        q[queries[j].second] = mx;
        j++;
    }
    for (int i = 0; i < t; i++) {
        cout << q[i] << endl;
    }

    return 0;
}
