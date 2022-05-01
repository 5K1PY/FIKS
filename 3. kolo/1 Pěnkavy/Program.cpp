#include <bits/stdc++.h>
#include <string>
using namespace std;

struct dna{
    string contents = {};
};

unsigned char c = 3 * pow(2, 6);

char letter(int x) {
    switch (x)
    {
    case 0:
        return 'a';
    case 1:
        return 'c';
    case 2:
        return 'g';
    case 3:
        return 't';
    }
}
vector<dna> dnas;

int diff_dna(int d1, int d2, int k) {
    string * dna1 = &dnas[d1].contents;
    string * dna2 = &dnas[d2].contents;
    int l1 = dna1->size()+1;
    int l2 = dna2->size()+1;
    if (abs(l1 - l2) > k) {
        return k+1;
    }
    vector<vector<int>> tab(l1);
    tab[0].resize(l2);
    for (int i=0; i<l2; i++) {
        tab[0][i] = i;    
    }
    for (int i=1; i<l1; i++) {
        tab[i].resize(l2);
        tab[i][0] = i;
        int min_diff = k+1;
        for (int j=1; j<l2; j++) {
            int replace = tab[i-1][j-1] + (dna1->at(i-1) != dna2->at(j-1));
            int remove = tab[i-1][j]+1;
            int add = tab[i][j-1]+1;
            tab[i][j] = min(min(replace, min(remove, add)), k+1);
            min_diff = min(min_diff, tab[i][j]);
        }
        if (min_diff > k)
            return k+1;
    }
    // for (int i=0; i<l1; i++) {
    //     for (int j=0; j<l2; j++) {
    //         cout << tab[i][j];
    //     }
    //     cout << endl;
    // }
    return tab[l1-1][l2-1];
}

int solve() {
    int n, diff;
    cin >> n >> diff;
    for (int i=0;i<dnas.size(); i++) {
        dnas[i].contents.clear();
    }
    dnas.resize(0);
    dnas.resize(n);
    for (int i=0; i<n; i++) {
        string s;
        // cout << "c";
        cin >> dnas[i].contents;
        // cout << dnas[i].contents << endl;
    }
    // cout << "d";
    int diffs[n][n];
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            bool skipped = false;
            for (int k=0; k<i; k++) {
                if (diffs[k][i] + diffs[k][j] <= diff) {
                    diffs[i][j] = diffs[k][i] + diffs[k][j];
                    skipped = true;
                }
            }
            if (!skipped)
                diffs[i][j] = diff_dna(i, j, diff);
            diffs[j][i] = diffs[i][j];
            // cout << diffs[i][j] << " ";
        }
        // cout << endl;
    }
    vector<int> res;
    for (int a=0; a<n; a++) {
        for (int c=a+1; c<n; c++) {
            if (diffs[a][c]<= diff)
                continue;
            for (int b=0; b<n; b++) {
                if ((b != a & b != c) && diffs[b][a]<= diff && diffs[b][c]<= diff) {
                    res.push_back(a);
                    res.push_back(b);
                    res.push_back(c);
                }
            }
        }
    }
    cout << res.size() / 3 << "\n";
    for (int i=0; i<res.size(); i+=3) {
        cout << res[i] << " " << res[i+1] << " " << res[i+2] << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        solve();
        // cout << i;
    }
}