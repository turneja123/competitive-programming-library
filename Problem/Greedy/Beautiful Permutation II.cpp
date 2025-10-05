//https://cses.fi/problemset/task/3175
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

void print(vector<int> &a, int x) {
    for (int y : a) {
        cout << y + x * 5 << " ";
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION";
        return 0;
    }
    if (n == 4) {
        cout << "2 4 1 3";
        return 0;
    }
    int i = 0;
    if (n % 5 == 0) {
        for (; i < n / 5; i++) {
            vector<int> go{1, 3, 5, 2, 4};
            print(go, i);
        }
    } else if (n % 5 == 1) {
        for (; i < n / 5; i++) {
            vector<int> go{1, 3, 5, 2, 4};
            print(go, i);
        }
        cout << 1 + i * 5;
    } else if (n % 5 == 2) {
        for (; i < n / 5 - 1; i++) {
            vector<int> go{1, 3, 5, 2, 4};
            print(go, i);
        }
        vector<int> go{1, 3, 5, 2, 6, 4, 7};
        print(go, i);
    } else if (n % 5 == 3) {
        for (; i < n / 5 - 1; i++) {
            vector<int> go{1, 3, 5, 2, 4};
            print(go, i);
        }
        vector<int> go{1, 3, 5, 2, 6, 8, 4, 7};
        print(go, i);
    } else {
        for (; i < n / 5 - 1; i++) {
            vector<int> go{1, 3, 5, 2, 4};
            print(go, i);
        }
        vector<int> go{1, 3, 5, 2, 4, 7, 9, 6, 8};
        print(go, i);
    }
    return 0;
}
