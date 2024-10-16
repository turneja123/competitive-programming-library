//https://cses.fi/problemset/task/1087
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e6 + 5;

vector<int> a{'A' - 'A', 'C' - 'A', 'T' - 'A', 'G' - 'A'};
int last[26];
pair<int, int> nx[N];


int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    for (int j : a) {
        last[j] = n;
    }
    for (int i = n - 1; i >= 0; i--) {
        nx[i].first = -1;
        for (int j : a) {
            if (last[j] > nx[i].first) {
                nx[i] = make_pair(last[j], j);
            }
        }
        last[s[i] - 'A'] = i;
    }
    string ans = "";
    int i = -1, c;
    for (int j : a) {
        if (last[j] > i) {
            i = last[j];
            c = j;
        }
    }
    ans += 'A' + c;
    while (i != n) {
        ans += 'A' + nx[i].second;
        i = nx[i].first;
    }
    cout << ans;

    return 0;
}
