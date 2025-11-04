#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct nodo {
    vector<int> adj;
};

typedef vector<nodo> grafo;

bool grafo_ciclico(const grafo& G, int u, int exclude, vector<bool>& visited, vector<bool>& in_stack, vector<int>& path, int& cycle_start) {
    visited[u] = true;
    in_stack[u] = true;
    path.push_back(u);

    for (int v : G[u].adj) {
        if (v == exclude) continue; // Skip the excluded vertex
        if (!visited[v]) {
            if (grafo_ciclico(G, v, exclude, visited, in_stack, path, cycle_start)) {
                return true;
            }
        } else if (in_stack[v]) { // Found a back edge
            cycle_start = v; // Mark the start of the cycle
            path.push_back(v); // Temporarily add to the path
            return true;
        }
    }

    in_stack[u] = false;
    path.pop_back();
    return false;
}

int main() {
    int N, M;
    ifstream input("input.txt");
    ofstream output("output.txt");

    input >> N >> M;

    grafo G(N);
    for (int i = 0; i < M; i++) {
        int from, to;
        input >> from >> to;
        G[from].adj.emplace_back(to);
    }

    int result = -1;
    vector<int> final_cycle_path; // New variable to store the path of the last cycle found

    for (int exclude = 0; exclude < N; exclude++) {
        vector<bool> visited(N, false);
        vector<bool> in_stack(N, false);
        vector<int> path;
        bool acyclic = true;
        int cycle_start = -1;
        vector<int> current_cycle_path;

        for (int u = 0; u < N; u++) {
            if (u != exclude && !visited[u]) {
                if (grafo_ciclico(G, u, exclude, visited, in_stack, path, cycle_start)) {
                    // Cycle found in G \ {exclude}
                    auto it = find(path.begin(), path.end(), cycle_start);
                    current_cycle_path = vector<int>(it, path.end());
                    final_cycle_path = current_cycle_path; // Store the cycle path (This is the one we want to remove)
                    acyclic = false;
                    break;
                }
            }
        }

        if (acyclic) {
            result = exclude;
            break;
        }
    }

    output << result << endl;

    // Output the cycle path that was broken by removing the 'result' node
    if (result != -1 && !final_cycle_path.empty()) {
        // The last element is a repeat of the cycle_start, so we pop it.
        final_cycle_path.pop_back(); 
        output << final_cycle_path.size() << " ";
        for (int node : final_cycle_path) {
            output << node << " ";
        }
    }

    return 0;
}
