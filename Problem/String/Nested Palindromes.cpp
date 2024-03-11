//https://www.spoj.com/problems/NESPALIN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int M = 60;

int group[N];
char ans[M];
set<char> options[M];
vector<int> inds[M];
string s;

int main() {
    IOS;
    int n = 1;
    while (n) {
        long long k;
        cin >> k;
        if (!k) {
            return 0;
        }
        cin >> s;
        n = s.size();
        int l = log2(n + 1);
        if (__builtin_popcount(n + 1) != 1) {
            cout << "-1" << endl;
            continue;
        }
        int mov = 1, start = 0;
        for (int i = 1; i < l; i++) {
                for (int j = start; j < n / 2; j += mov) {
                    group[j] = i;
                    group[n - 1 - j] = i;
                }
                start += mov;
                mov *= 2;
        }
        group[n / 2] = l;
        for (int i = 0; i < n; i++) {
            inds[group[i]].push_back(i);
        }
        bool flag = true;
        set<char> available;
        char first = '0';
        for (char c = '1'; c <= '9'; c++) {
            available.insert(c);
        }

        for (int i = 1; i <= l; i++) {
            set<char> cur;

            for (int j = 0; j < inds[i].size(); j++) {
                if (i == 1 && s[inds[i][j]] == '0') {
                    flag = false;
                }
                if (s[inds[i][j]] != '?') {
                    cur.insert(s[inds[i][j]]);
                }
            }
            if (cur.size() == 0) {
                if (i != 1) {
                    set<char> all;
                    for (char c = '0'; c <= '9'; c++) {
                        all.insert(c);
                    }
                    if (first != '0') {
                        all.erase(first);
                    }
                    options[i] = all;
                }
            } else if (cur.size() == 1) {
                char ch = *(cur.begin());
                if (i == 1) {
                    first = ch;
                    options[i] = cur;
                } else {
                    if (first != '0' && first == ch) {
                        flag = false;
                    }
                    options[i] = cur;
                    available.erase(ch);
                }
            } else {
                flag = false;
            }
        }
        if (!flag || available.empty()) {
            cout << "-1" << endl;
            for (int i = 1; i <= l; i++) {
                inds[i].clear();
                options[i].clear();
            }
            continue;
        }
        if (first == '0') {
            options[1] = available;
        }
        long long tot = 1;
        long long add = 1, pos = 1;
        for (int i = 1; i <= l; i++) {
            long long mul = options[i].size();
            if (mul == 10) {
                mul--;
            }
            tot *= mul;
            if (i > 1) {
                add *= mul;
            }
        }
        if (k > tot) {
            cout << "-1" << endl;
            for (int i = 1; i <= l; i++) {
                inds[i].clear();
                options[i].clear();
            }
            continue;
        }
        for (int i = 1; i <= l; i++) {
            int ct = 0;
            if (i != 1) {
                options[i].erase(ans[1]);
                add /= (long long)(options[i].size());
            }
            for (auto it = options[i].begin(); it != options[i].end(); ++it) {
                if (pos + add <= k && ct) {
                    pos += add;
                } else if (pos + add > k && ct) {
                    break;
                }
                ans[i] = *it;
                ct++;
            }
        }

        for (int i = 1; i <= l; i++) {
            for (int j = 0; j < inds[i].size(); j++) {
                s[inds[i][j]] = ans[i];
            }
            inds[i].clear();
            options[i].clear();
        }
        cout << s << endl;
    }
    return 0;
}
