#include "the6.h"

// do not add extra libraries here
using namespace std;

int find_structure(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) {
    int n = bond_energies.size();
    std::vector<bool> visited(n, false);
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq; // Min heap

    int start_vertex = 0;
    visited[start_vertex] = true;

    // Add all edges from the starting vertex to the priority queue
    for (auto &edge : bond_energies[start_vertex]) {
        pq.push({edge.second, {start_vertex, edge.first}});
    }

    int lowest_total_energy = 0;

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int u = top.second.first;
        int v = top.second.second;
        int weight = top.first;

        if (!visited[v]) {
            lowest_energy_structure[u].emplace_back(v, weight);
            lowest_energy_structure[v].emplace_back(u, weight);
            lowest_total_energy += weight;

            visited[v] = true;

            // Add all edges from the newly added vertex to the priority queue
            for (auto &edge : bond_energies[v]) {
                if (!visited[edge.first]) {
                    pq.push({edge.second, {v, edge.first}});
                }
            }
        }
    }

    return lowest_total_energy;
}

void bfs(int start, vector<vector<pair<int, int>>> &graph, vector<int> &distances, vector<int> &parent) {
    int n = graph.size();
    distances.assign(n, -1);
    parent.assign(n, -1);

    distances[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &edge : graph[u]) {
            int v = edge.first;

            if (distances[v] == -1) {
                distances[v] = distances[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

// Since all weights are 1, we can use bfs to find the all-pairs longest path.
int find_longest_chain(vector<vector<pair<int, int>>> &molecule_structure, vector<int> &chain) {
    int n = molecule_structure.size();
    int max_chain_size = 0;

    for (int i = 0; i < n; ++i) {
        vector<int> distances, parent;
        bfs(i, molecule_structure, distances, parent);

        if (*max_element(distances.begin(), distances.end()) + 1 > max_chain_size)
        {
            max_chain_size = *max_element(distances.begin(), distances.end()) + 1;
            chain.clear();
            
            if (max_chain_size == 1)
                chain.push_back(i);
                
            else if (max_chain_size > 1) {
                // Reconstruct the longest chain using parent array
                int last = max_element(distances.begin(), distances.end()) - distances.begin();  // index of the max element
                while (last != -1) {
                    chain.push_back(last);
                    last = parent[last];
                }
                reverse(chain.begin(), chain.end());
            }
        }
    }

    return max_chain_size;
}