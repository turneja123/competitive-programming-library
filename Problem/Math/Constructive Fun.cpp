//https://basecamp.eolymp.com/en/problems/11839
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define int long long

main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (k == 0) {
            for (int i = 0; i < n; i++) {
                cout << 1 << " ";
            }
            cout << endl;
            continue;
        }
        if (n == 2) {
            cout << 1 << " " << k + 1 << endl;
            continue;
        }
        vector<pair<int, int>> a;
        vector<int> diffs(n - 1, 0);
        for (int i = 1; i < n; i++) {
            long long d = (long long)i * (n - i);
            if (d <= k) {
                a.push_back(make_pair(d, i - 1));
            }
        }
        bool found = false;
        for (int i = 0; i < a.size(); i++) {
            if (k % a[i].first == 0) {
                found = true;
                diffs[a[i].second] = k / a[i].first;
                break;
            }
        }
        if (!found) {
            for (int i = 0; i < a.size() && !found; i++) {
                for (int j = i + 1; j < a.size() && !found; j++) {
                    int d1 = a[i].first, d2 = a[j].first;
                    int A = -1, B = -1;
                    for (int x = 0; x <= k / d1; x++) {
                        if ((k - d1 * x) % d2 == 0) {
                            diffs[a[i].second] = x;
                            diffs[a[j].second] = (k - d1 * x) / d2;
                            found = true;
                            break;
                        }
                    }
                }
            }
        }

        if (!found) {
            int go = 0;
            vector<int> seen(k + 1, false);
            vector<int> head(k + 1, 0);
            vector<int> parent(k + 1, -1);
            //vector<int> haves;
            for (int i = 0; i < a.size() && !found; i++) {
                if (!seen[a[i].first]) {
                    seen[a[i].first] = true;
                    head[a[i].first] = a[i].second;
                }
                for (int j = 1; j <= k; j++) {
                    if (seen[j] && a[i].first + j <= k && !seen[a[i].first + j]) {
                        seen[a[i].first + j] = true;
                        parent[a[i].first + j] = j;
                        head[a[i].first + j] = a[i].second;
                        if (k % (a[i].first + j) == 0) {
                            found = true;
                            go = a[i].first + j;
                        }
                    }
                }

            }
            int mul = k / go;
            while (1) {
                diffs[head[go]] += mul;
                if (parent[go] == -1) {
                    break;
                }
                go = parent[go];
            }
            int s = 1;
            for (int i = 0; i < n; i++) {
                cout << s << " ";
                if (i != n - 1) {
                    s += diffs[i];
                }
            }
            cout << endl;
        } else {
            int s = 1;
            for (int i = 0; i < n; i++) {
                cout << s << " ";
                if (i != n - 1) {
                    s += diffs[i];
                }
            }
            cout << endl;
        }



    }
    return 0;
}
