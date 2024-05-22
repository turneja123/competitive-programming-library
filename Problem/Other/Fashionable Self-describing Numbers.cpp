//https://www.spoj.com/problems/SELFNUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 12;

int pw[N];
int f[N];

vector<pair<vector<int>, int>> selfnums; //<num,mask>
vector<pair<long long, int>> all;
vector<long long> ans[10];
long long tot = 0, ind = 0;

void print() {
    for (int i = 0; i < selfnums.size(); i++) {
        /*for (int x : selfnums[i].first) {
            cout << x;
        }
        cout << " " ;
        for (int j = 0; j < 10; j++) {
            int c = selfnums[i].second & pw[j];
            cout << min(c, 1);
        }
        cout << endl;*/
        tot += f[selfnums[i].first.size()];
    }
}

void get() {
    for (int i = 0; i < selfnums.size(); i++) {
        vector<int> v = selfnums[i].first; int s = v.size();
        vector<int> pos(s);
        for (int j = 0; j < s; j++) {
            pos[j] = j + 1;
        }
        do {
            long long m = 0;
            for (int j = 0; j < s; j++) {
                m += v[pos[j] - 1];
                if (j != s - 1) {
                    m *= (long long)((v[pos[j + 1] - 1] == 111) ? 1000 : 100);
                }
            }
            all[ind++] = make_pair(m, selfnums[i].second);
        } while (next_permutation(pos.begin(), pos.end()));
    }
    return;
}

int main() {
    IOS;
    pw[0] = 1, f[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2;
        f[i] = f[i - 1] * i;
    }
    //22
    selfnums.push_back(make_pair(vector<int>{22}, pw[2]));
    //2132231x
    int mask = pw[1] + pw[2] + pw[3];
    vector<int> v{21, 32, 23};
    for (int i = 0; i < 10; i++) {
        int c = mask & pw[i];
        if (c != 0) {
            continue;
        }
        mask ^= pw[i];
        v.push_back(10 + i);
        selfnums.push_back(make_pair(v, mask));
        mask ^= pw[i];
        v.pop_back();
    }
    //31331x1x
    v = {31, 33};
    mask = pw[1] + pw[3];
    for (int i = 0; i < 10; i++) {
        int c = mask & pw[i];
        if (c != 0) {
            continue;
        }
        mask ^= pw[i];
        v.push_back(10 + i);
        for (int j = i + 1; j < 10; j++) {
            int c = mask & pw[j];
            if (c != 0) {
                continue;
            }
            mask ^= pw[j];
            v.push_back(10 + j);
            selfnums.push_back(make_pair(v, mask));
            mask ^= pw[j];
            v.pop_back();
        }
        mask ^= pw[i];
        v.pop_back();
    }
    //3133221x1x
    v = {31, 33, 22};
    mask = pw[1] + pw[2] + pw[3];
    for (int i = 0; i < 10; i++) {
        int c = mask & pw[i];
        if (c != 0) {
            continue;
        }
        mask ^= pw[i];
        v.push_back(10 + i);
        for (int j = i + 1; j < 10; j++) {
            int c = mask & pw[j];
            if (c != 0) {
                continue;
            }
            mask ^= pw[j];
            v.push_back(10 + j);
            selfnums.push_back(make_pair(v, mask));
            mask ^= pw[j];
            v.pop_back();
        }
        mask ^= pw[i];
        v.pop_back();
    }
    //412432231x1x1x
    v = {41, 24, 32, 23};
    mask = pw[1] + pw[2] + pw[3] + pw[4];
    for (int i = 0; i < 10; i++) {
        int c = mask & pw[i];
        if (c != 0) {
            continue;
        }
        mask ^= pw[i];
        v.push_back(10 + i);
        for (int j = i + 1; j < 10; j++) {
            int c = mask & pw[j];
            if (c != 0) {
                continue;
            }
            mask ^= pw[j];
            v.push_back(10 + j);
            for (int k = j + 1; k < 10; k++) {
                int c = mask & pw[k];
                if (c != 0) {
                    continue;
                }
                mask ^= pw[k];
                v.push_back(10 + k);
                selfnums.push_back(make_pair(v, mask));
                mask ^= pw[k];
                v.pop_back();
            }
            mask ^= pw[j];
            v.pop_back();
        }
        mask ^= pw[i];
        v.pop_back();
    }
    //512532231x1x1x1x
    v = {51, 25, 32, 23};
    mask = pw[1] + pw[2] + pw[3] + pw[5];
    for (int i = 0; i < 10; i++) {
        int c = mask & pw[i];
        if (c != 0) {
            continue;
        }
        mask ^= pw[i];
        v.push_back(10 + i);
        for (int j = i + 1; j < 10; j++) {
            int c = mask & pw[j];
            if (c != 0) {
                continue;
            }
            mask ^= pw[j];
            v.push_back(10 + j);
            for (int k = j + 1; k < 10; k++) {
                int c = mask & pw[k];
                if (c != 0) {
                    continue;
                }
                mask ^= pw[k];
                v.push_back(10 + k);
                for (int x = k + 1; x < 10; x++) {
                    int c = mask & pw[x];
                    if (c != 0) {
                        continue;
                    }
                    mask ^= pw[x];
                    v.push_back(10 + x);
                    selfnums.push_back(make_pair(v, mask));
                    mask ^= pw[x];
                    v.pop_back();
                }
                mask ^= pw[k];
                v.pop_back();
            }
            mask ^= pw[j];
            v.pop_back();
        }
        mask ^= pw[i];
        v.pop_back();
    }
    //612632231x1x1x1x1x
    v = {61, 26, 32, 23};
    mask = pw[1] + pw[2] + pw[3] + pw[6];
    for (int i = 0; i < 10; i++) {
        int c = mask & pw[i];
        if (c != 0) {
            continue;
        }
        mask ^= pw[i];
        v.push_back(10 + i);
        for (int j = i + 1; j < 10; j++) {
            int c = mask & pw[j];
            if (c != 0) {
                continue;
            }
            mask ^= pw[j];
            v.push_back(10 + j);
            for (int k = j + 1; k < 10; k++) {
                int c = mask & pw[k];
                if (c != 0) {
                    continue;
                }
                mask ^= pw[k];
                v.push_back(10 + k);
                for (int x = k + 1; x < 10; x++) {
                    int c = mask & pw[x];
                    if (c != 0) {
                        continue;
                    }
                    mask ^= pw[x];
                    v.push_back(10 + x);
                    for (int y = x + 1; y < 10; y++) {
                        int c = mask & pw[y];
                        if (c != 0) {
                            continue;
                        }
                        mask ^= pw[y];
                        v.push_back(10 + y);
                        selfnums.push_back(make_pair(v, mask));
                        mask ^= pw[y];
                        v.pop_back();
                    }
                    mask ^= pw[x];
                    v.pop_back();
                }
                mask ^= pw[k];
                v.pop_back();
            }
            mask ^= pw[j];
            v.pop_back();
        }
        mask ^= pw[i];
        v.pop_back();
    }
    //712732231x1x1x1x1x1x ne moze jer sadrzi sve cifre a jedna je zabr.
    //1111x1x1x1x1x1x1x1x
    for (int i = 0; i < 10; i++) {
        if (i == 1) {
            continue;
        }
        v = {111};
        for (int j = 0; j < 10; j++) {
            if (j == 1 || j == i) {
                continue;
            }
            v.push_back(10 + j);
        }
        selfnums.push_back(make_pair(v, (pw[10] - 1) ^ pw[i]));
    }
    print();
    all.resize(tot);
    get();
    sort(all.begin(), all.end());
    for (int i = 0; i < all.size(); i++) {
        for (int j = 0; j < 10; j++) {
            int c = all[i].second & pw[j];
            if (c == 0) {
                ans[j].push_back(all[i].first);
            }
        }
    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long n, d;
        cin >> n >> d;
        cout << ans[d][n - 1] << endl;
    }
    return 0;
}
