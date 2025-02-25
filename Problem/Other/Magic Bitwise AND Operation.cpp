//https://www.spoj.com/problems/AND/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 40;
const int pop_size = 25;

long long a[N];

int mutation_cutoff = 3;
double mutation_coef = 3.0;

int n, k;
double mutation_chance[pop_size];

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

struct Chrom {
    vector<int> s;
    vector<int> t;
    long long fit;
};

vector<Chrom> chroms;

bool comp(Chrom a, Chrom b) {
    return a.fit < b.fit;
}

long long calc(vector<int> &s) {
    long long ans = (1ll << 60) - 1;
    for (int i = 0; i < k; i++) {
        ans &= a[s[i]];
    }

    return ans;

}

void random_chrom(int ind) {
    vector<int> y;
    for (int i = 0; i < n; i++) {
        y.push_back(i);
    }
    shuffle(y.begin(), y.end(), gen);
    chroms[ind].s.resize(k);
    chroms[ind].t.resize(n - k);
    for (int i = 0; i < k; i++) {
        chroms[ind].s[i] = y[i];
    }
    for (int i = k; i < n; i++) {
        chroms[ind].t[i - k] = y[i];
    }
    return;
}

void optimize(Chrom &chrom) {
    bool f = true;
    while (f) {
        f = false;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n - k; j++) {
                swap(chrom.s[i], chrom.t[j]);
                long long nw = calc(chrom.s);
                if (nw < chrom.fit) {
                    chrom.fit = nw;
                    f = true;
                    break;
                } else {
                    swap(chrom.s[i], chrom.t[j]);
                }
            }
            if (f) {
                break;
            }
        }
    }
}


int main() {
    IOS;
    for (int i = 0; i < pop_size; i++) {
        mutation_chance[i] = (i >= mutation_cutoff) ? min(1.0, 0.5 + (double)((i + 2) * sqrt(i + 2) * mutation_coef) / double(N * sqrt(N) * log(i + 2))) : 0;
    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        chroms.resize(pop_size);
        for (int i = 0; i < pop_size; i++) {
            random_chrom(i);
        }
        int lim = n < 10 ? 100 : 100;
        for (int j = 0; j < lim; j++) {
            for (int i = 0; i < pop_size; i++) {
                chroms[i].fit = calc(chroms[i].s);
            }
            if (n == k) {
                break;
            }
            sort(chroms.begin(), chroms.end(), comp);
            long long best = chroms[0].fit;
            if (best == 0) {
                break;
            }
            uniform_real_distribution<double> dis(0.0, 1.0);
            for (int i = 0; i < pop_size; i++) {
                double mut = dis(gen);
                if (mut > mutation_chance[i]) {
                    continue;
                }
                int l = gen() % k, r = gen() % (n - k);
                swap(chroms[i].s[l], chroms[i].t[r]);
            }
            for (int i = 0; i < pop_size; i++) {
                optimize(chroms[i]);
            }
        }
        sort(chroms.begin(), chroms.end(), comp);
        long long best = chroms[0].fit;
        cout << "Case #" << tt << ": " << best << endl;
        chroms.clear();
    }
    return 0;
}
