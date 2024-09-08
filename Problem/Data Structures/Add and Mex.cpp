//https://atcoder.jp/contests/abc272/tasks/abc272_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int B = 450;

long long a[N];
int ct[N];
int freq[N];

set<int> can;

int query() {
    int j = 0;
    while (ct[j] == B) {
        j++;
    }
    for (int i = B * j; i < B * (j + 1); i++) {
        if (freq[i] == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    priority_queue<pair<long long, int>> pq;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] < 0) {
            long long d = abs(a[i]) / i - 1;
            pq.push(make_pair(-d, i));
        } else if (a[i] < N) {
            freq[a[i]]++;
            if (freq[a[i]] == 1) {
                ct[a[i] / B]++;
            }
            can.insert(i);
        }
    }
    for (int j = 1; j <= m; j++) {
        while (pq.size() && -pq.top().first <= j) {
            int i = pq.top().second;
            a[i] += (long long)(j - 1) * (long long)i;
            if (a[i] < N) {
                can.insert(i);
                if (a[i] >= 0) {
                    freq[a[i]]++;
                    if (freq[a[i]] == 1) {
                        ct[a[i] / B]++;
                    }
                }
            }
            pq.pop();
        }
        vector<int> del;
        for (int i : can) {
            if (a[i] >= 0 && a[i] < N) {
                freq[a[i]]--;
                if (freq[a[i]] == 0) {
                    ct[a[i] / B]--;
                }
            }
            a[i] += i;
            if (a[i] < N) {
                if (a[i] >= 0) {
                    freq[a[i]]++;
                    if (freq[a[i]] == 1) {
                        ct[a[i] / B]++;
                    }
                }
            } else {
                del.push_back(i);
            }
        }
        for (int i : del) {
            can.erase(i);
        }
        cout << query() << endl;
    }
    return 0;
}
