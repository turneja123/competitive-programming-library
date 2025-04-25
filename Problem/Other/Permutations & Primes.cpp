//https://dmoj.ca/problem/dmopc21c5p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 101;
const int pop_size = 10;
const int M = 70000;

int lim = 500;
bool is_prime[N];
double mutation_chance[N];
int mutation_cutoff = 3;
double mutation_coef = 3.0;
int max_refinements = 70;

int n;
int save = 2;

//mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
mt19937 generator(3);
uniform_real_distribution<double> dis(0.0, 1.0);

struct Chrom {
    vector<int> s;
    int fit;
};

vector<Chrom> chroms;
vector<Chrom> chroms_new;

bool comp(Chrom a, Chrom b) {
    return a.fit > b.fit;
}


int calc(vector<int> &a) {
    int s = 0;
    for (int i = 1; i < n; i++) {
        if (is_prime[abs(a[i] - a[i - 1])]) {
            s += abs(a[i] - a[i - 1]);
        }
    }
    return s;
}

int tournament() {
    int best = generator() % pop_size;
    for (int i = 1; i < 5; i++){
        int x = generator() % pop_size;
        if (chroms[x].fit > chroms[best].fit) {
            best = x;
        }
    }
    return best;
}

int rank_roulette() {
    double lim = dis(generator);
    for(int i = 0; i < pop_size; i++){
        lim -= (double)(2 * (pop_size - i)) / (double)(pop_size * (pop_size + 1));
        if (lim < 0) {
            return i;
        }
    }
    return pop_size - 1;
}

void order_crossover(int x, int y, int ind) {
    int l = generator() % n, r = generator() % n;
    if (l > r) {
        swap(l, r);
    }
    vector<bool> taken_s(n, false);
    chroms_new[ind].s.resize(n);
    for (int i = l; i <= r; i++) {
        chroms_new[ind].s[i] = chroms[x].s[i];
        taken_s[chroms[x].s[i]] = true;
    }
    int js = 0;
    for (int i = 0; i < n; i++) {
        if (i >= l && i <= r) {
            continue;
        }
        while (taken_s[chroms[y].s[js]]) {
            js++;
        }
        chroms_new[ind].s[i] = chroms[y].s[js];
        taken_s[chroms[y].s[js]] = true;
    }
    chroms_new[ind].fit = calc(chroms_new[ind].s);
    return;
}

void random_chrom(int ind) {
    vector<int> x;
    for (int j = 0; j < n; j++) {
        x.push_back(j + 1);
    }
    shuffle(x.begin(), x.end(), generator);
    chroms[ind].s = x;
    chroms[ind].fit = calc(chroms[ind].s);
    return;
}

void refine(int ind) {
    int m = generator() % max_refinements;
    for (int k = 0; k < m; k++) {
        int x = -1, y = -1;
        while (x == y) {
            x = generator() % n, y = generator() % n;
        }
        int l = 0, r = 0;
        if (x != 0 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[x - 1])]) {
            l += abs(chroms[ind].s[x] - chroms[ind].s[x - 1]);
        }
        if (x != n - 1 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[x + 1])]) {
            l += abs(chroms[ind].s[x] - chroms[ind].s[x + 1]);
        }
        if (y != 0 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[y - 1])]) {
            l += abs(chroms[ind].s[y] - chroms[ind].s[y - 1]);
        }
        if (y != n - 1 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[y + 1])]) {
            l += abs(chroms[ind].s[y] - chroms[ind].s[y + 1]);
        }

        if (x != 0 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[x - 1])]) {
            r += abs(chroms[ind].s[y] - chroms[ind].s[x - 1]);
        }
        if (x != n - 1 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[x + 1])]) {
            r += abs(chroms[ind].s[y] - chroms[ind].s[x + 1]);
        }
        if (y != 0 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[y - 1])]) {
            r += abs(chroms[ind].s[x] - chroms[ind].s[y - 1]);
        }
        if (y != n - 1 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[y + 1])]) {
            r += abs(chroms[ind].s[x] - chroms[ind].s[y + 1]);
        }
        if (r > l) {
            swap(chroms[ind].s[x], chroms[ind].s[y]);
        }

    }
    return;
}

void refine2(int ind) {
    int m = generator() % (max_refinements);
    for (int k = 0; k < 20; k++) {
        int x = -1, y = -1;
        while (x == y) {
            x = generator() % n, y = generator() % n;
        }
        if (x > y) {
            swap(x, y);
        }
        int diff = 0;
        if (x != 0 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[x - 1])]) {
            diff -= abs(chroms[ind].s[x] - chroms[ind].s[x - 1]);
        }
        if (x != 0 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[x - 1])]) {
            diff += abs(chroms[ind].s[y] - chroms[ind].s[x - 1]);
        }

        if (y != n - 1 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[y + 1])]) {
            diff -= abs(chroms[ind].s[y] - chroms[ind].s[y + 1]);
        }
        if (y != n - 1 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[y + 1])]) {
            diff += abs(chroms[ind].s[x] - chroms[ind].s[y + 1]);
        }

        if (diff > 0) {
            reverse(chroms[ind].s.begin() + x, chroms[ind].s.begin() + y + 1);
        }

    }
    return;
}

void refine3(int ind) {
    int m = generator() % (max_refinements);
    for (int k = 0; k < 1000; k++) {
        int x = -1, y = -1;
        while (x == y) {
            x = generator() % n, y = generator() % n;
        }
        if (x > y) {
            swap(x, y);
        }
        int diff = 0;
        if (x != 0 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[x - 1])]) {
            diff -= abs(chroms[ind].s[x] - chroms[ind].s[x - 1]);
        }
        if (x != 0 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[x - 1])]) {
            diff += abs(chroms[ind].s[y] - chroms[ind].s[x - 1]);
        }

        if (y != n - 1 && is_prime[abs(chroms[ind].s[y] - chroms[ind].s[y + 1])]) {
            diff -= abs(chroms[ind].s[y] - chroms[ind].s[y + 1]);
        }
        if (y != n - 1 && is_prime[abs(chroms[ind].s[x] - chroms[ind].s[y + 1])]) {
            diff += abs(chroms[ind].s[x] - chroms[ind].s[y + 1]);
        }

        if (diff > 0) {
            reverse(chroms[ind].s.begin() + x, chroms[ind].s.begin() + y + 1);
            k = 0;
        }

    }
    return;
}

int main() {
    //IOS;
    cin >> n;
    for (int i = 0; i < pop_size - save; i++) {
        mutation_chance[i] = (i >= mutation_cutoff) ? min(1.0, (double)((i + 2) * sqrt(i + 2) * mutation_coef) / double(N * sqrt(N) * log(i + 2))) * 4.0 : 0;
    }
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    chroms.resize(pop_size);
	for (int i = 0; i < pop_size; i++) {
        random_chrom(i);
	}

    int best = 0, last = 0, stagnating = 0;
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < pop_size; i++) {
            //refine(i);
            //refine2(i);
            if (k % 27 == 0 && i < 15) {
                refine3(i);
            }
            chroms[i].fit = calc(chroms[i].s);
        }
        sort(chroms.begin(), chroms.end(), comp);
        best = chroms[0].fit;
        if (last == best) {
            stagnating++;
        }
        last = best;
        if (stagnating > lim) {
            stagnating = 0;
            for (int i = save; i < pop_size; i++) {
                random_chrom(i);
                //refine3(i);
                chroms[i].fit = calc(chroms[i].s);
            }
            int x = max(1, (int)generator() % save);
            random_chrom(x);
           //refine(x);
            //refine2(x);
            chroms[x].fit = calc(chroms[x].s);
            sort(chroms.begin(), chroms.end(), comp);
            best = chroms[0].fit;
        }
        /*if (k % 1000 == 0 || k < 25) {
            cout << "Iteration " << k << ": " << best << endl;
        }*/
        chroms_new.resize(pop_size - save);
        for (int i = 0; i < pop_size - save; i++) {
            int x = -1, y = -1;
            while (x == y) {
                x = tournament(), y = tournament();
            }
            order_crossover(x, y, i);
        }

        sort(chroms_new.begin(), chroms_new.end(), comp);
        for (int i = 0; i < pop_size - save; i++) {
            double mut = dis(generator);
            if (mut < mutation_chance[i]) {
                int x = -1, y = -1;
                while (x == y) {
                    x = generator() % n, y = generator() % n;
                }
                swap(chroms_new[i].s[x], chroms_new[i].s[y]);
            }
        }
        for (int i = 0; i < pop_size - save; i++) {
            double mut = dis(generator);
            if (mut < mutation_chance[i]) {
                int x = -1, y = -1;
                while (x == y) {
                    x = generator() % n, y = generator() % n;
                }
                swap(chroms_new[i].s[x], chroms_new[i].s[y]);
            }
        }
        for (int i = 0; i < pop_size - save; i++) {
            chroms[i + save] = chroms_new[i];
        }
        chroms_new.clear();
	}
	for (int i = 0; i < n; i++) {
        cout << chroms[0].s[i];
        if (i != n - 1) {
            cout << " ";
        }
	}
	cout << endl;


    return 0;
}
