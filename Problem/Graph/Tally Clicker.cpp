//https://dmoj.ca/problem/othscc2p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4;

int dist[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        dist[i] = N;
    }
    queue<int> q;
    q.push(n);
    dist[n] = 0;
    while (q.size()) {
        int n = q.front();
        q.pop();
        bool can = true;
        int temp = n;
        for (int i = 0; i < 4; i++) {
            if (temp % 10 == 0) {
                can = false;
            }
            temp /= 10;
        }
        if (can && dist[n - 1111] > dist[n] + 1) {
            dist[n - 1111] = dist[n] + 1;
            q.push(n - 1111);
        }
        if (dist[n - 1] > dist[n] + 1) {
            dist[n - 1] = dist[n] + 1;
            q.push(n - 1);
        }
    }
    cout << dist[0];
    return 0;
}
