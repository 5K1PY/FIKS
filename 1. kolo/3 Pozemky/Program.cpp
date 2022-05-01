#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        int m;
        cin >> m;
        long long res = 0;
        for (int j=0; j<m; j++) {
            string s;
            int a, b;
            cin >> s >> a >> b;
            res += a*b;
        }
        cout << res << endl;
    }
}