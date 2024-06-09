//https://www.spoj.com/problems/LEXIPOS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

class BigInt{
    string digits;
public:
    BigInt(unsigned long long n = 0);
    BigInt(string &);
    BigInt(const char *);
    BigInt(BigInt &);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);
    int operator[](const int)const;
    BigInt &operator=(const BigInt &);
    BigInt &operator++();
    BigInt operator++(int temp);
    BigInt &operator--();
    BigInt operator--(int temp);
    friend BigInt &operator+=(BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);
    friend ostream &operator<<(ostream &,const BigInt &);
};

BigInt::BigInt(string & s){
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(unsigned long long nr){
    do{
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}
BigInt::BigInt(const char *s){
    digits = "";
    for (int i = strlen(s) - 1; i >= 0;i--)
    {
        if(!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(BigInt & a){
    digits = a.digits;
}

bool Null(const BigInt& a){
    if(a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}
int Length(const BigInt & a){
    return a.digits.size();
}
int BigInt::operator[](const int index)const{
    if(digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}
bool operator==(const BigInt &a, const BigInt &b){
    return a.digits == b.digits;
}
bool operator!=(const BigInt & a,const BigInt &b){
    return !(a == b);
}
bool operator<(const BigInt&a,const BigInt&b){
    int n = Length(a), m = Length(b);
    if(n != m)
        return n < m;
    while(n--)
        if(a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}
bool operator>(const BigInt&a,const BigInt&b){
    return b < a;
}
bool operator>=(const BigInt&a,const BigInt&b){
    return !(a < b);
}
bool operator<=(const BigInt&a,const BigInt&b){
    return !(a > b);
}

BigInt &BigInt::operator=(const BigInt &a){
    digits = a.digits;
    return *this;
}

BigInt &BigInt::operator++(){
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9;i++)
        digits[i] = 0;
    if(i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}
BigInt BigInt::operator++(int temp){
    BigInt aux;
    aux = *this;
    ++(*this);
    return aux;
}

BigInt &operator+=(BigInt &a,const BigInt& b){
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if(m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n;i++){
        if(i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if(t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt &a, const BigInt &b){
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

ostream &operator<<(ostream &out,const BigInt &a){
    for (int i = a.digits.size() - 1; i >= 0;i--)
        cout << (short)a.digits[i];
    return cout;
}

BigInt dp[105][3][3]; //i, tight n, tight k

void add(int i, int xn, int yn, int ck, int d) {
    if (ck > d) {
        dp[i][xn][0] += dp[i - 1][yn][0] + dp[i - 1][yn][2];
        dp[i][xn][1] += dp[i - 1][yn][1];
    } else if (ck == d) {
        dp[i][xn][0] += dp[i - 1][yn][0];
        dp[i][xn][1] += dp[i - 1][yn][1];
        dp[i][xn][2] += dp[i - 1][yn][2];
    } else {
        dp[i][xn][0] += dp[i - 1][yn][0];
        dp[i][xn][1] += dp[i - 1][yn][1] + dp[i - 1][yn][2];
    }
    return;
}

void calc(string n, string k) {
    BigInt Z{"0"}; BigInt O{"1"};
    BigInt ans = Z;
    for (int dx = 0; dx <= 3; dx++) {
        for (int dy = 0; dy <= 3; dy++) {
            dp[0][dx][dy] = Z;
        }
    }
    for (int d = 1; d < 10; d++) {
        int cn = n[0] - '0', ck = k[0] - '0';
        if (cn > d && ck > d) {
            dp[0][0][0] += O;
        } else if (cn > d && ck == d) {
            dp[0][0][2] += O;
        } else if (cn > d && ck < d) {
            dp[0][0][1] += O;
        } else if (cn == d && ck > d) {
            dp[0][2][0] += O;
        } else if (cn == d && ck == d) {
            dp[0][2][2] += O;
        } else if (cn == d && ck < d) {
            dp[0][2][1] += O;
        } else if (cn < d && ck > d) {
            dp[0][1][0] += O;
        } else if (cn < d && ck == d) {
            dp[0][1][2] += O;
        } else if (cn < d && ck < d) {
            dp[0][1][1] += O;
        }
    }

    for (int i = 1; i < n.size(); i++) {
        for (int dx = 0; dx <= 3; dx++) {
            for (int dy = 0; dy <= 3; dy++) {
                dp[i][dx][dy] = Z;
            }
        }
        int cn  = n[i] - '0', ck = ((i >= k.size()) ? -1 : k[i] - '0');
        for (int d = 0; d < 10; d++) {
            if (cn > d) {
                add(i, 0, 0, ck, d);
                add(i, 0, 2, ck, d);
                add(i, 1, 1, ck, d);
            } else if (cn == d) {
                add(i, 0, 0, ck, d);
                add(i, 1, 1, ck, d);
                add(i, 2, 2, ck, d);
            } else {
                add(i, 0, 0, ck, d);
                add(i, 1, 1, ck, d);
                add(i, 1, 2, ck, d);
            }
        }
    }
    for (int i = 0; i < n.size(); i++) {
        ans += dp[i][0][0] + dp[i][0][2];
        ans += dp[i][2][0] + dp[i][2][2];
        if (i != n.size() - 1) {
            ans += dp[i][1][0] + dp[i][1][2];
        }
    }
    cout << ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string n, k;
        cin >> n >> k;
        calc(n, k);
        cout << endl;
    }
    return 0;
}
