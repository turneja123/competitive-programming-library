#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
ll X[N];
ll Y[N];
ll XX[N];
ll YY[N];

int main() {
    IOS;
    ll N, K, M, A, B, S;
    cin >> N >> K >> M >> A >> B >> S;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            X[i] = (A * S + B) % M;
        } else {
            X[i] = (A * YY[i - 1] + B) % M;
        }
        Y[i] = (A * X[i] + B) % M;
        XX[i] = (A * Y[i] + B) % M;
        YY[i] = (A * XX[i] + B) % M;

        if (X[i] == XX[i]) {
            XX[i] = XX[i] + 1;
        }
        if (X[i] > XX[i]) {
            swap(X[i], XX[i]);
        }
        if (Y[i] == YY[i]) {
            YY[i] = YY[i] + 1;
        }
        if (Y[i] > YY[i]) {
            swap(Y[i], YY[i]);
        }
    }
    deque <int> x;
    deque <int> y;
    deque <int> xx;
    deque <int> yy;
    for (int i = 0; i < K; i++) {
        while (x.size() && X[i] <= X[x.back()]) {
            x.pop_back();
        }
        while (y.size() && Y[i] <= Y[y.back()]) {
            y.pop_back();
        }
        while (xx.size() && XX[i] >= XX[xx.back()]) {
            xx.pop_back();
        }
        while (yy.size() && YY[i] >= YY[yy.back()]) {
            yy.pop_back();
        }
        x.push_back(i);
        y.push_back(i);
        xx.push_back(i);
        yy.push_back(i);
    }
    ll solx = XX[xx.front()] - X[x.front()];
    ll soly = YY[yy.front()] - Y[y.front()];
    for (int i = K; i < N; i++) {
        while (x.size() && x.front() <= i - K) {
            x.pop_front();
        }
        while (xx.size() && xx.front() <= i - K) {
            xx.pop_front();
        }
        while (y.size() && y.front() <= i - K) {
            y.pop_front();
        }
        while (yy.size() && yy.front() <= i - K) {
            yy.pop_front();
        }

        while (x.size() && X[i] <= X[x.back()]) {
            x.pop_back();
        }
        while (y.size() && Y[i] <= Y[y.back()]) {
            y.pop_back();
        }
        while (xx.size() && XX[i] >= XX[xx.back()]) {
            xx.pop_back();
        }
        while (yy.size() && YY[i] >= YY[yy.back()]) {
            yy.pop_back();
        }

        x.push_back(i);
        y.push_back(i);
        xx.push_back(i);
        yy.push_back(i);

        solx = max(solx, XX[xx.front()] - X[x.front()]);
        soly = max(soly, YY[yy.front()] - Y[y.front()]);
    }
    cout << solx << " " << soly;
    return 0;

}
