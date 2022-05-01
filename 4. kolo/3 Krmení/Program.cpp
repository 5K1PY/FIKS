#include <bits/stdc++.h>

using namespace std;

struct node {
    vector<int> sons;
    int id;
    int father;
    int depth=-1;
    int question=-1;
    bool flag=false;
    int count=0;
};

vector<node> nodes;
vector<vector<pair<int, int>>> rmq;
long long q_n;

int count(int x) {
    node n1 = nodes[x];
    int res = n1.flag;
    for (int i=0; i<n1.sons.size(); i++) {
        res += count(n1.sons[i]);
    }
    nodes[x].count = res;
    return res;
}


int calc_node(int x, int sum) {
    // cout << x << ": " << sum << endl;
    int best = sum;
    node n1 = nodes[x];
    for (int i=0; i<n1.sons.size(); i++) {
        best = min(best, calc_node(n1.sons[i], sum + q_n - 2*nodes[n1.sons[i]].count));
    }
    return best;
}

void calc_depth(int father, int node1, int depth=0) {
    nodes[node1].father = father;
    nodes[node1].depth = depth;
    for (int i=0; i<nodes[node1].sons.size(); i++) {
        if (nodes[node1].sons[i] == father)
            nodes[node1].sons.erase(nodes[node1].sons.begin() + i);
    }
    nodes[node1].question = rmq[0].size();
    for (int i=0; i<nodes[node1].sons.size(); i++) {
        rmq[0].push_back({depth, node1});
        //cout << node1 << " ";
        calc_depth(node1, nodes[node1].sons[i], depth+1);
    }
    rmq[0].push_back({depth, node1});
    //cout << node1 << " ";
}

int lca(int a, int b) {
    if (a == b) {
        return a;
    }
    if (nodes[a].question > nodes[b].question) {
        return lca(b, a);
    }
    int start = nodes[a].question;
    int lenght = nodes[b].question - start;
    int order = 0;
    while (lenght > 1) {
        lenght >>= 1;
        order++;
    }
    //cout << a << " " << b << ": " << order << " " << lenght << " " << rmq[order][start].first << " " << rmq[order][nodes[b].question - (1 << order)].first << endl;
    if (rmq[order][start].first <= rmq[order][nodes[b].question - (1 << order)].first) {
        return rmq[order][start].second;
    } else {
        return rmq[order][nodes[b].question - (1 << order)].second;
    }
}

long long dist(int a, int b) {
    int c = lca(a, b);
    return nodes[a].depth + nodes[b].depth - 2*nodes[c].depth;
}

long long total(int center, vector<int> * question) {
    long long res=0;
    //cout << center << ": ";
    for (int i=0; i<question->size(); i++) {
        res += dist(center, question->at(i));
        //cout << question->at(i) << " " << dist(center, question->at(i)) << " ";
    }
     //cout << ": " << res << endl;
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;
    nodes.resize(n);
    rmq.resize(1);
    int a, b;
    for (int i=0; i<n-1; i++) {
        cin >> a >> b;
        a--; b--;
        nodes[a].sons.push_back(b);
        nodes[b].sons.push_back(a);
    }
    for (int i=0; i<n; i++) {
        nodes[i].id = i;
    }
    calc_depth(-1, 0);
    //cout << endl;
    int i, j;
    while ((1 << (rmq.size())) < rmq[0].size()) {
        j = 1 << (rmq.size()-1);
        rmq.push_back({});
        for (i=0; j<rmq[rmq.size()-2].size();) {
            if (rmq[rmq.size()-2][i].first < rmq[rmq.size()-2][j].first) {
                rmq[rmq.size()-1].push_back(rmq[rmq.size()-2][i]);
            } else {
                rmq[rmq.size()-1].push_back(rmq[rmq.size()-2][j]);
            }
            //cout << rmq[rmq.size()-1][rmq[rmq.size()-1].size()-1].second << " ";
            i++; j++;
        }
        for (;i<rmq[0].size(); i++) {
            rmq[rmq.size()-1].push_back(rmq[0][0]);
            //cout << rmq[rmq.size()-1][rmq[rmq.size()-1].size()-1].second << " ";
        }
        //cout << endl;
    }
    long long start, optimal, best, now;
    for (int i=0; i<q; i++) {
        // cout << i << " ";
        best=std::numeric_limits<long long int>::max();
        start=0, optimal=0;
        cin >> q_n;
        vector<int> question(q_n);
        for (int j=0; j<q_n; j++) {
            cin >> question[j];
            --question[j];
            start += nodes[question[j]].depth;
        }
        //cout << "s" << start << endl;
        if (q_n == 1) {
            cout << start << endl;
        } else if (q_n <= 100) {
            for (int j=0; j<q_n; j++) {
                for (int k=j+1; k<q_n; k++) {
                    //cout << lca(question[j], question[k]) << endl;
                    best = min(best, total(lca(question[j], question[k]), &question));
                    //cout << best << endl;
                }
            }
            cout << start - best << endl;
        } else {
            for (int i=0; i<n; i++) {
                nodes[i].flag = false;
            }
            for (int i=0; i<q_n; i++) {
                nodes[question[i]].flag = true;
            }
            count(0);
            cout << start - calc_node(0, start) << endl;

        }
    }
}