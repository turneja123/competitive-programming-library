//https://www.beecrowd.com.br/judge/en/problems/view/3083
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;
const long long P = 26;
const long long Q = 53;
string a, b;
int aux[N];
int sum[N];

map<pair<long long, long long>, pair<char, long long>> mp;
map<pair<char, long long>, int> vals;

void LPS(string pat, int m, int lps[]) {
    int len = 0;
    int i = 1;
    lps[0] = 0;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = len;
                i++;
            }
        }
    }
}

int KMP(string pat, string txt) {
    int m = pat.length();
    int n = txt.length();
    int lps[m];
    int j = 0;
    LPS(pat, m, lps);
    int i = 0;
    int res = 0;
    while (i < n) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == m) {
            j = lps[j - 1];
            res++;
            aux[i] -= 1;
            aux[i - m] += 1;
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    return res;
}

long long compute_hash(string s, long long X) {
    long long hash_value = 0;
    long long p_pow = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        hash_value = (hash_value + (long long)(s[i] - 'a' + 1) * p_pow) % M;
        p_pow = (p_pow * X) % M;
    }
    return hash_value;
}

int main() {
    IOS;
    cin >> a >> b;
    int ans = KMP(b, a), s = 0;
    for (int i = 0; i < a.size(); i++) {
        s += aux[i];
        sum[i] = s;
    }
    pair<long long, long long> h = make_pair(compute_hash(b, P), compute_hash(b, Q));
    long long p_pow = 1;
    long long q_pow = 1;
    for (int i = b.size() - 1; i >= 0; i--) {
        long long p = (h.first - (long long)(b[i] - 'a' + 1) * p_pow + P * M) % M;
        long long q = (h.second - (long long)(b[i] - 'a' + 1) * q_pow + Q * M) % M;
        for (int c = 0; c < 26; c++) {
            if ('a' + c == b[i]) {
                continue;
            }
            long long temp_p = (p + (long long)(c + 1) * p_pow) % M;
            long long temp_q = (q + (long long)(c + 1) * q_pow) % M;
            pair<long long, long long> temp_h = make_pair(temp_p, temp_q);
            mp[temp_h] = make_pair(b[i], i);
        }
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
    }
    long long p = 0, q = 0;
    p_pow = 1, q_pow = 1;
    for (int i = b.size() - 1; i >= 0; i--) {
        p = (p + (long long)(a[i] - 'a' + 1) * p_pow) % M;
        q = (q + (long long)(a[i] - 'a' + 1) * q_pow) % M;
        if (i != 0) {
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
        }
    }
    pair<long long, long long> sub = make_pair(p, q);
    if (mp.find(sub) != mp.end()) {
        auto it = mp.find(sub);
        vals[make_pair((it->second).first, (it->second).second)]++;
    }

    for (int i = b.size(); i < a.size(); i++) {
        p = (((p - p_pow * (long long)(a[i - b.size()] - 'a' + 1) + P * M) % M) * P + (long long)(a[i] - 'a' + 1)) % M;
        q = (((q - q_pow * (long long)(a[i - b.size()] - 'a' + 1) + Q * M) % M) * Q + (long long)(a[i] - 'a' + 1)) % M;
        sub = make_pair(p, q);
        auto it = mp.find(sub);
        if (it != mp.end()) {
            vals[make_pair((it->second).first, (it->second).second + i - b.size() + 1)]++;
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int i;
        char c;
        cin >> i >> c;
        i--;
        if (b.size() > a.size()) {
            cout << 0 << endl;
            continue;
        }

        if (a[i] == c) {
            cout << ans << endl;
        } else {
            cout << ans - sum[i] + vals[make_pair(c, i)] << endl;
        }
    }
    return 0;
}
