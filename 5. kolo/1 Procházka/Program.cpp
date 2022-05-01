#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> nodes(n);
    for (int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        nodes[a].push_back(b); nodes[b].push_back(a);
    }
    vector<int> free_nodes;
    for (int i=0; i<n; i++) {
        if (nodes[i].size() % 2 == 1) {
            free_nodes.push_back(i);
        }
    }
    if (free_nodes.size() == 0) {
        cout << "Ano." << endl;
        return;
    } else {
        cout << "Ne." << endl;
        cout << (free_nodes.size()) / 2 << endl;
        if (free_nodes.size() % 2 == 1) {
            free_nodes.push_back(0);
        }
        for (int i=0; i<free_nodes.size(); i+=2) {
            cout << free_nodes[i] << " " << free_nodes[i+1] << endl;
        }
    }
}

int main() {
    int t;
    cin >> t;
    for (int i=0; i<t; i++) {
        solve();
    }    
}