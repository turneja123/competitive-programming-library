//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136690
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

bool good[N];
vector<int> facts[N];

int freq[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        good[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (facts[i].empty()) {
            facts[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                facts[j].push_back(i);
                int ct = 0, k = j;
                while (k % i == 0) {
                    k /= i;
                    ct++;
                }
                if (ct > 1) {
                    good[j] = false;
                }
            }
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    long long ans = 0;
    long long all_prime = 0;
    vector<long long> f;
    for (int i = 2; i < N; i++) {
        if (good[i]) {
            if (facts[i].size() == 1) {
                f.push_back(freq[i]);
                all_prime += freq[i];
            }
            if (facts[i].size() == 3) {
                ans += freq[i];
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (good[i]) {
            if (facts[i].size() == 2) {
                ans += (long long)freq[i] * (all_prime - freq[facts[i][0]] - freq[facts[i][1]]);
                ans %= M;
            }
        }
    }
    long long sum = 0, doubles = 0;
    for (int x : f) {
        ans = (ans + (long long)x * doubles) % M;
        doubles = (doubles + (long long)x * sum) % M;
        sum += x;
    }
    for (int i = 0; i < freq[1]; i++) {
        ans = (ans * 2) % M;
    }
    cout << ans;
    return 0;
}
