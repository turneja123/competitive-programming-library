//https://contest.joincpi.org/contest?id=Myb-ebc4AHL67vnWMucwU&tab=problem-nC9OT5MNLFcYfYO-zR5UM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int diff[N];
int add[N];
vector<int> pos[N];
vector<pair<int, int>> ivals[N];
vector<int> divs[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            if (pos[i].empty()) {
                ivals[i].push_back({0, n - 1});
            } else {
                int last = 0;
                for (auto j : pos[i]) {
                    if (last < j) {
                        ivals[i].push_back({last, j - 1});
                    }
                    last = j + 1;
                }
                if (last != n) {
                    ivals[i].push_back({last, n - 1});
                }
            }
            sort(ivals[i].begin(), ivals[i].end(), [&](auto a, auto b) {return a.second - a.first + 1 > b.second - b.first + 1;});
        }
        for (int i = 1; i <= n; i++) {
            vector<int> events;
            for (int d : divs[i]) {
                for (auto [l, r] : ivals[d]) {
                    int R = r - i + 1;
                    if (l > R) {
                        break;
                    }
                    events.push_back(l);
                    events.push_back(R + 1);
                    diff[l]++;
                    diff[R + 1]--;
                }
            }
            events.push_back(n);
            sort(events.begin(), events.end());
            events.erase(unique(events.begin(), events.end()), events.end());
            int s = 0, last = -1;
            for (int j : events) {
                if (s == divs[i].size()) {
                    add[last]++;
                    add[j]--;
                }
                s += diff[j];
                diff[j] = 0;
                last = j;
            }
        }
        int s = 0;
        for (int i = 0; i < n; i++) {
            s += add[i];
            cout << s << " ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            add[i] = 0;
            pos[i].clear();
            ivals[i].clear();
        }




    }


    return 0;
}
