//solution for
//https://www.hackerearth.com/practice/algorithms/string-algorithm/string-searching/practice-problems/algorithm/make-them-equal-too-89585e71/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int inversions(int n, int arr[]) {
    int ans = 0;
    tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t;
    for (int i = 0; i < n; i++) {
        t.insert({arr[i], i});
        ans += t.size() - t.order_of_key({arr[i], INF});
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        string t1, t2;
        t1 = a;
        t2 = b;
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        if (t1 != t2) {
            cout << "NO" << endl;
            continue;
        }
        int ct[26] = { };
        bool flag = false;
        for (int i = 0; i < n; i++) {
            ct[a[i] - 'a']++;
            if (ct[a[i] -'a'] > 1) {
                flag = true;
            }
        }
        if (flag) {
            cout << "YES" << endl;
            continue;
        }
        int pos[26] = { };
        for (int i = 0; i < n; i++) {
            pos[b[i] - 'a'] = i;
        }
        int arr[n] = { };
        for (int i = 0; i < n; i++) {
            arr[i] = pos[a[i] - 'a'];
        }
        int inv = inversions(n, arr);
        if (inv % 2 == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
