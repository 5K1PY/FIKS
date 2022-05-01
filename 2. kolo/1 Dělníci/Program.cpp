#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

struct event {
    int cena;
    int bod;
    int odkud;
};

struct cmp_events{
    bool operator()(const event& a, const event& b) const{
        if (a.cena != b.cena) {
            return a.cena > b.cena;
        } else if (a.bod != b.bod) {
            return a.bod > b.bod;
        }
        return a.odkud > b.odkud;
    }
};

struct bod {
    int id;
    vector<int> hrany;
    int cena = 0;
    int cena_cesty = -1;
    int odkud = -1;
};

void solve() {
    int jazyku;
    cin >> jazyku;
    vector<bod> body(jazyku);
    map<string, int> jazyky;
    string jazyky_inverse[jazyku];
    for (int i=0; i<jazyku; i++) {
        string jazyk;
        cin >> jazyk;
        jazyky.insert({jazyk, i});
        jazyky_inverse[i] = jazyk;

        body[i].id = i;
    }

    int prekladatelu;
    cin >> prekladatelu;
    body.resize(jazyku+prekladatelu);
    for (int i=jazyku; i<jazyku+prekladatelu; i++) {
        body[i].id = i;
        int n;
        cin >> n >> body[i].cena;
        body[i].hrany.resize(n);
        for (int j=0; j<n; j++) {
            string jazyk;
            cin >> jazyk;
            body[i].hrany[j] = jazyky[jazyk];
            body[jazyky[jazyk]].hrany.push_back(i);
        }
    }

    string s, c;
    cin >> s >> c;
    int start = jazyky[s];
    int cil = jazyky[c];

    vector<event> heap = {{0, start, -1}};

    while (heap.size()) {
        pop_heap(heap.begin(),heap.end(), cmp_events());
        event e = heap[heap.size()-1];
        heap.pop_back();


        if (body[e.bod].cena_cesty != -1) {
            continue;
        }
        body[e.bod].cena_cesty = e.cena;
        body[e.bod].odkud = e.odkud;

        // cout << e.bod << " " << e.cena << " " << e.odkud << endl;
        if (e.bod == cil) {
            break;
        }
        for (int kam: body[e.bod].hrany) {
            heap.push_back({e.cena + body[e.bod].cena, kam, e.bod});
            push_heap(heap.begin(),heap.end(), cmp_events());
        }
    }
    if (body[cil].cena_cesty == -1) {
        cout << "Takove prekladatele nemame.\n";
        return;
    }
    cout << "To nas bude stat " << body[cil].cena_cesty << ",-.\n";
    vector<int> cesta = {cil};
    while (cesta[cesta.size()-1] != start) {
        int prekladatel = body[cesta[cesta.size()-1]].odkud;
        int jazyk = body[prekladatel].odkud;
        cesta.push_back(jazyk);
    }
    reverse(cesta.begin(), cesta.end());
    cout << "Pocet prekladu: " << cesta.size() - 1 << ".\n";
    for (int jazyk: cesta) {
        cout << jazyky_inverse[jazyk] << "\n";
    }
}


int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        solve();
    }
}