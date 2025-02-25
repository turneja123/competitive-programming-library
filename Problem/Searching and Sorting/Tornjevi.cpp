//https://evaluator.hsin.hr/events/coci25_5/tasks/HONI242555tornjevi/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;

int a[N];
int ans[N];

vector<int> pos[N];
vector<pair<int, int>> ivals[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    map<int, int> last;
    last[a[0]] = 0;
    ivals[a[0]].push_back(make_pair(0, 0));


    for (int i = 1; i < n; i++) {
        map<int, int> mp;
        mp[a[i]] = i;
        for (auto it = last.begin(); it != last.end(); ++it) {
            int x = __gcd(it->first, a[i]);
            auto itt = mp.find(x);
            if (itt == mp.end()) {
                mp[x] = it->second;
            } else {
                mp[x] = min(mp[x], it->second);
            }
        }
        last = mp;
        vector<pair<int, int>> cur;
        for (auto it = last.begin(); it != last.end(); ++it) {
            cur.push_back(make_pair(it->first, it->second));
        }
        for (int j = cur.size() - 1; j >= 0; j--) {
            ivals[cur[j].first].push_back(make_pair(cur[j].second, i));
        }
    }
    for (int x = 1; x < N; x++) {
        if (pos[x].empty()) {
            continue;
        }
        int j = 0;
        multiset<int> best;
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < pos[x].size(); i++) {
            while (j < ivals[x].size() && ivals[x][j].first <= pos[x][i]) {
                pq.push(make_pair(-ivals[x][j].second, ivals[x][j].second - ivals[x][j].first + 1));
                best.insert(ivals[x][j].second - ivals[x][j].first + 1);
                j++;
            }
            while (pq.size() && -pq.top().first < pos[x][i]) {
                best.erase(best.find(pq.top().second));
                pq.pop();
            }
            ans[pos[x][i]] = *best.rbegin();
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
