#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <algorithm>
#include "conclave.h"
using namespace std;

int N, M;
vector<vector<int>> riunioni;
unordered_map<int, unordered_set<int>> membroRiunioni;

// Controlla se una combinazione di membri copre tutte le riunioni
bool copreTutte(const vector<int>& selezionati, const vector<vector<int>>& riunioni) {
    unordered_set<int> selezionatiSet(selezionati.begin(), selezionati.end());

    for (const auto& r : riunioni) {
        bool coperta = false;
        for (int m : r) {
            if (selezionatiSet.count(m)) {
                coperta = true;
                break;
            }
        }
        if (!coperta)
            return false;
    }
    return true;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;
    riunioni.resize(M);

    int c, e, row = 0;
    set<int> tuttiMembri;
    while (in >> c) {
        for (int i = 0; i < c; ++i) {
            in >> e;
            riunioni[row].push_back(e);
            membroRiunioni[e].insert(row);
            tuttiMembri.insert(e);
        }
        ++row;
    }

    if (N <= 15) {
        vector<int> membri(tuttiMembri.begin(), tuttiMembri.end());
        int numMembri = membri.size();
        vector<int> soluzione;
        bool trovato = false;

        for (int k = 1; k <= numMembri && !trovato; ++k) {
            vector<bool> mask(numMembri, false);
            fill(mask.end() - k, mask.end(), true); // k elementi a true

            do {
                vector<int> selezionati;
                for (int i = 0; i < numMembri; ++i) {
                    if (mask[i])
                        selezionati.push_back(membri[i]);
                }

                if (copreTutte(selezionati, riunioni)) {
                    soluzione = selezionati;
                    trovato = true;
                    break; // esce da questo ciclo do-while
                }
            } while (next_permutation(mask.begin(), mask.end()));
        }

        sort(soluzione.begin(), soluzione.end());
        out << soluzione.size() << " ";
        for (int m : soluzione)
            out << m << " ";
        out << "#" << endl;
        return 0;
    }

    // Strategia greedy
    unordered_set<int> riunioniCoperte;
    unordered_set<int> soluzione;

    // max-heap: {quante riunioni copre, membro}
    priority_queue<pair<int, int>> heap;
    unordered_map<int, int> count;

    for (auto& [membro, riunioniDelMembro] : membroRiunioni) {
        count[membro] = riunioniDelMembro.size();
        heap.emplace(count[membro], membro);
    }

    while (riunioniCoperte.size() < M) {
        if (heap.empty()) break;

        auto [copertureStimate, membro] = heap.top();
        heap.pop();

        // Ricalcola coperture reali (lazy update)
        int copertureReali = 0;
        for (int r : membroRiunioni[membro]) {
            if (!riunioniCoperte.count(r))
                copertureReali++;
        }

        if (copertureReali < copertureStimate) {
            // Valore vecchio: aggiorna
            heap.emplace(copertureReali, membro);
            continue;
        }

        // Se è ancora valido, usalo
        soluzione.insert(membro);
        for (int r : membroRiunioni[membro])
            riunioniCoperte.insert(r);
        membroRiunioni.erase(membro); // rimuovi dal gioco
    }

    // Output ordinato
    vector<int> outMembri(soluzione.begin(), soluzione.end());
    sort(outMembri.begin(), outMembri.end());

    out << outMembri.size() << " ";
    for (int m : outMembri)
        out << m << " ";
    out << "#" << endl;

    // BACKTRACKING CASUALE PER MIGLIORARE LA SOLUZIONE
    unordered_set<int> bestSol(outMembri.begin(), outMembri.end());
    int bestSize = bestSol.size();

    // Recupera tutti i membri ancora disponibili
    vector<int> candidati;
    for (auto& [m, _] : membroRiunioni)
        candidati.push_back(m);

    srand(time(0)); // inizializza rand con il tempo corrente

    while (true) {
        vector<int> current(bestSol.begin(), bestSol.end());

        // Prova a rimuovere un membro casuale
        int idxToRemove = rand() % current.size();
        vector<int> temp = current;
        temp.erase(temp.begin() + idxToRemove);

        bool migliorato = false;
        if (copreTutte(temp, riunioni)) {
            current = temp;
            migliorato = true;
        }

        // Prova anche a rimpiazzare un membro con uno non presente
        if (!migliorato && !candidati.empty()) {
            int idxToReplace = rand() % current.size();
            int candidato = candidati[rand() % candidati.size()];
            if (!bestSol.count(candidato)) {
                temp = current;
                temp[idxToReplace] = candidato;

                if (copreTutte(temp, riunioni)) {
                    current = temp;
                    migliorato = true;
                }
            }
        }

        if (migliorato) {
            unordered_set<int> nuova(current.begin(), current.end());
            if (nuova.size() < bestSize) {
                bestSol = nuova;
                bestSize = nuova.size();

                // Stampa nuova soluzione migliore
                vector<int> nuovaSol(nuova.begin(), nuova.end());
                sort(nuovaSol.begin(), nuovaSol.end());

                out << nuovaSol.size() << " ";
                for (int m : nuovaSol)
                    out << m << " ";
                out << "#" << endl;
            }
        }
    }

    return 0;
}
