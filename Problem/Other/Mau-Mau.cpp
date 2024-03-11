//https://www.spoj.com/problems/MAUMAU/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int n;
int p;
int penalty = 0;

bool effect = true;
char suit = 'X';

map<char, int> suitcomp;
map<char, int> cardcomp;

vector<string> draw;
vector<string> discard;
vector<string> players[10];

bool comp(string a, string b) {
    if (cardcomp[a[1]] != cardcomp[b[1]]) {
        return cardcomp[a[1]] >= cardcomp[b[1]];
    }
    return suitcomp[a[0]] >= suitcomp[b[0]];
}

void binding(int cur) {
    int maxcount = 0;
    char maxsuit = 'C';
    map<char, int> suitcount;

    for (auto card : players[cur]) {
        if (card[1] == 'J') {
            continue;
        }
        suitcount[card[0]]++;
        if (suitcount[card[0]] > maxcount) {
            maxcount = suitcount[card[0]];
            maxsuit = card[0];
        } else if (suitcount[card[0]] == maxcount) {
            if (suitcomp[card[0]] > suitcomp[maxsuit]) {
                maxsuit = card[0];
            }
        }
    }
    suit = maxsuit;
    return;
}

void take(int cur) {
    players[cur].push_back(draw[p++]);
    if (p == draw.size()) {
        draw.clear();
        for (int i = 0; i < discard.size() - 1; i++) {
            draw.push_back(discard[i]);
        }
        p = 0;
        string card = discard[discard.size() - 1];
        discard.clear();
        discard.push_back(card);
    }
    return;
}

int turn(int cur) {
    sort(players[cur].begin(), players[cur].end(), comp);
    if (discard[discard.size() - 1][1] == 'S' && effect) {
        penalty += 2;
        for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
            if ((*it)[1] == 'S') {
                cout << (*it) << " ";
                discard.push_back(*it);
                effect = true;
                players[cur].erase(it);
                if (players[cur].empty()) {
                    return -1;
                }
                return (cur + 1) % n;
            }
        }

        for (int i = 0; i < penalty; i++) {
            take(cur);
        }
        penalty = 0;
        effect = false;
        return (cur + 1) % n;
    }

    if (discard[discard.size() - 1][1] == 'E' && effect) {
        effect = false;
        return (cur + 1) % n;
    }

    if (discard[discard.size() - 1][1] == 'J') {
        for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
            if ((*it)[1] == 'J') {
                continue;
            }
            if (suit != 'X' && (*it)[0] != suit) {
                continue;
            }
            cout << (*it) << " ";
            discard.push_back(*it);
            effect = true;
            players[cur].erase(it);
            if (players[cur].empty()) {
                return -1;
            }
            return (cur + 1) % n;
        }
        take(cur);
        for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
            if ((*it)[1] == 'J') {
                continue;
            }
            if (suit != 'X' && (*it)[0] != suit) {
                continue;
            }
            cout << (*it) << " ";
            discard.push_back(*it);
            effect = true;
            players[cur].erase(it);
            return (cur + 1) % n;
        }
        return (cur + 1) % n;
    }

    bool has = false, hasjack = false;
    for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
        if ((*it)[1] == 'J') {
            hasjack = true;
        } else if ((*it)[0] == discard[discard.size() - 1][0] || (*it)[1] == discard[discard.size() - 1][1]) {
            has = true;
        }
    }
    if (!has && !hasjack) {
        take(cur);
        for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
            if ((*it)[1] == 'J') {
                hasjack = true;
            } else if ((*it)[0] == discard[discard.size() - 1][0] || (*it)[1] == discard[discard.size() - 1][1]) {
                has = true;
            }
        }
        if (!has && !hasjack) {
            return (cur + 1) % n;
        }
    }

    if (!has || (hasjack && players[(cur + 1) % n].size() == 1)) {
        binding(cur);
        for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
            if ((*it)[1] == 'J') {
                cout << (*it) << " ";
                discard.push_back(*it);
                effect = true;
                players[cur].erase(it);
                if (players[cur].empty()) {
                    return -1;
                }
                return (cur + 1) % n;
            }
        }
        return -1;
    }
    for (auto it = players[cur].begin(); it != players[cur].end(); ++it) {
        if ((*it)[1] == 'J') {
            continue;
        }
        if ((*it)[0] == discard[discard.size() - 1][0] || (*it)[1] == discard[discard.size() - 1][1]) {
            cout << (*it) << " ";
            discard.push_back(*it);
            effect = true;
            players[cur].erase(it);
            if (players[cur].empty()) {
                return -1;
            }
            return (cur + 1) % n;
        }
    }
    return -1;
}

int main() {
    IOS;
    suitcomp['X'] = 0;
    suitcomp['C'] = 4;
    suitcomp['S'] = 3;
    suitcomp['H'] = 2;
    suitcomp['D'] = 1;
    cardcomp['S'] = 7;
    cardcomp['E'] = 8;
    cardcomp['N'] = 9;
    cardcomp['T'] = 10;
    cardcomp['J'] = 20;
    cardcomp['Q'] = 3;
    cardcomp['K'] = 4;
    cardcomp['A'] = 11;
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < 32; i++) {
            string s;
            cin >> s;
            draw.push_back(s);
        }
        int f = 14;
        f = (n == 3) ? 18 : f;
        f = (n == 4) ? 20 : f;
        for (p = 0; p < f; p++) {
            players[p % n].push_back(draw[p]);
        }
        discard.push_back(draw[p++]);
        cout << discard[0] << " ";
        int cur = 0;
        while (cur != -1) {
            cur = turn(cur);
        }
        cout << endl;
        cout << "Score: ";
        for (int i = 0; i < n; i++) {
            int score = 0;
            for (auto card : players[i]) {
                score += cardcomp[card[1]];
            }
            if (discard[discard.size() - 1][1] == 'J') {
                score *= 2;
            }
            cout << score << " ";
            players[i].clear();
        }
        cout << endl;
        draw.clear();
        discard.clear();
        suit = 'X';
    }
    return 0;
}
