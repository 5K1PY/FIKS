#include <iostream>
#include <vector>
using namespace std;

bool solve(int n, vector<int> req[], int needed[], vector<int> * res) {
    needed[n] = 0;
    for (int x: req[n]) {
        if (needed[x] == -1) {
            if (!solve(x, req, needed, res)) {
                return false;
            }
        } else if (needed[x] == 0) {
            return false;
        }
    }
    needed[n] = 1;
    res->push_back(n);
    return true;
}

int main() {
    int t;
    cin >> t;
    for (int i=0; i<t; i++) {
        int n, z, cil;
        cin >> n >> z >> cil;
        
        vector<int> req[n];
        int needed[n];
        for (int j=0; j<n; j++) {
            needed[j] = -1;
        }

        for (int j=0; j<z; j++) {
            int a, b;
            cin >> a >> b;
            req[a].push_back(b);
        }

        vector<int> res;
        bool success = solve(cil, req, needed, &res);
        if (success) {
            cout << "pujde to";
            for (int r: res) {
                cout << " " << r;
            }
            cout << endl;
        } else {
            cout << "ajajaj" << endl;
        }
    }
}